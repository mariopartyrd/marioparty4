#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "rel_sqrt_consts.h"

#include "REL/m438Dll.h"

typedef struct M438MainWork {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    char unk08[2];
    u8 unk_0A;
    u8 unk_0B;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    s32 unk_10;
    s32 unk_14;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
    float unk_24;
    float unk_28;
    float unk_2C;
    float unk_30;
    s32 unk_34;
    s32 unk_38;
    float unk_3C;
    u32 unk_40;
    u32 unk_44;
    float unk_48;
    Vec unk_4C;
    Vec unk_58;
    s32 unk_64;
    s32 unk_68;
    Vec unk_6C;
    float unk_78;
    float unk_7C;
    float unk_80;
    float unk_84;
    float unk_88;
    float unk_8C;
    Vec unk_90;
    float unk_9C;
    float unk_A0;
    s32 unk_A4;
    s32 unk_A8;
    float unk_AC;
    float unk_B0;
    float unk_B4;
    char unkB8[0x34];
    u8 unk_EC;
    u8 unk_ED;
    char unkEE[2];
    char unk_F0[0x40]; // unknown type
} M438MainWork; /* size = 0x130 */

typedef struct M438MainWork2 {
    char unk00[0x6C];
    Vec unk_6C;
    char unk78[0x0C];
    Vec unk_84;
    Vec unk_90;
} M438MainWork2; /* size =  */ // TODO maybe same as M438MainWork?

typedef struct M438MainWork3 {
    u8 unk_00;
    Vec unk_04;
    Vec unk_10;
    Vec unk_1C;
    Vec unk_28;
    Vec unk_34;
    Vec unk_40;
    Vec unk_4C;
    Vec unk_58;
    Vec unk_64[3];
    float unk_88[3][3];
    Vec unk_AC[3];
    float unk_D0[3][3];
    float unk_F4[3];
    float unk_100[3];
    float unk_10C[3];
    float unk_118[3];
    float unk_124[3];
    float unk_130;
    float unk_134;
    float unk_138;
    float unk_13C;
    float unk_140;
    float unk_144;
    float unk_148;
    float unk_14C[3];
    float unk_158[3];
    float unk_164[3];
    float unk_170[3];
    float unk_17C[3];
    u16 unk_188[3];
} M438MainWork3; /* size =  */

typedef struct M438MainWork4 {
    s8 unk_00;
    char unk04[11];
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    float unk_20;
    float unk_24;
    char unk28[4];
    float unk_2C;
    char unk30[4];
    Vec unk_34;
    char unk40[0xC];
} M438MainWork4; /* size = 0x4C */

typedef struct M438StructBss298 {
    /* 0x00 */ u8 unk_00;
    u8 unk_01;
    s8 unk_02;
    char unk03;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    float unk_0C;
    float unk_10;
    float unk_14;
    Vec unk_18;
    Vec unk_24;
} M438StructBss298; /* size = 0x30 */

typedef struct M438UnkStruct {
    char unk00[0x5C];
    s8 unk_5C;
    char unk5D[0x3B];
} M438UnkStruct; /* size = 0x98 */

typedef struct M438UnkStruct2 {
    char unk00[0x30];
    void *unk_30; // TODO type
    char unk34[8];
    M438UnkStruct *unk_3C;
    char unk40[0x3C];
    s16 unk_7C;
    s16 unk_7E;
    float unk_80;
    float unk_84;
    float unk_88;
    float unk_8C;
    float unk_90;
    char unk94[0x28];
} M438UnkStruct2; /* size = 0xBC */

typedef struct M438StructBssDE4 {
    /* 0x00 */ char unk00[0x36];
    s16 unk_36;
    s16 unk_38;
    s16 unk_3A;
    char unk3C[4];
    M438UnkStruct2 *unk_40;
} M438StructBssDE4; /* size =  */

void fn_1_1174(omObjData *object);
void fn_1_1204(omObjData *object);
void fn_1_13A0(omObjData *object);
void fn_1_1F0C(omObjData *object);
void fn_1_2070(omObjData *);
void fn_1_2564(float arg8, Vec *arg0, Vec *arg1, float arg9);
void fn_1_28E4(u8 arg0, u16 arg1, float arg9, float argA, float argB);
void fn_1_2964(omObjData *object);
void fn_1_2D50(omObjData *object);
void fn_1_2E4C(omObjData *object);
void fn_1_35BC(omObjData *object);
void fn_1_35C0(omObjData *object);
void fn_1_4374(omObjData *object);
void fn_1_4724(omObjData *object);
void fn_1_4984(omObjData *object);
void fn_1_4DC(omObjData *object);
void fn_1_4F50(omObjData *object);
void fn_1_4FC(omObjData *object);
void fn_1_5D4C(void *arg0);
void fn_1_62BC(void *arg0);
void fn_1_63B0(void *arg0);
void fn_1_6A3C(void *arg0);
void fn_1_7300(void *arg0);
void fn_1_7B58(omObjData *object);
void fn_1_7BBC(void);
void *fn_1_7BFC(s32 arg0);
void fn_1_7D30(void);
s32 fn_1_7DB4(void);
void fn_1_7DD8(s32 arg0, s32 *arg1);
float fn_1_7EDC(float arg8, float arg9, float argA);
void fn_1_8164(float *arg0, Vec *arg1);
void fn_1_8C34(float *arg0, float *arg1, float *arg2, s32 arg3);
float fn_1_8EEC(float *arg0, float *arg1, float *arg2, float arg8);
void fn_1_9040(float *arg0, Vec *arg1, float arg2[3][3], s32 arg3);
void fn_1_9420(float *arg0, float *arg1, float arg2[3][3], float arg3[3][3], s32 arg4, float arg8);
float fn_1_9634(Vec *arg0);
void fn_1_974(omObjData *object);
float fn_1_9960(Vec *arg0, Vec *arg1, Vec *arg2);
float fn_1_A14C(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3);
void fn_1_A60C(omObjData *object);
void fn_1_A688(omObjData *object);
void fn_1_A68C(ModelData *model, Mtx matrix);
s32 fn_1_AE18(u32 arg0, Vec *arg1, Vec *arg2);
float fn_1_B440(Vec *arg0, Vec *arg1, Vec *arg2);

Vec lbl_1_data_0 = { 1000.0f, 3000.0f, 1000.0f };
Vec lbl_1_data_C = { -0.4f, -0.6f, -0.1f };
GXColor lbl_1_data_18 = { 0xFF, 0xD0, 0xD0, 0xFF };
Vec lbl_1_data_1C = { 500.0f, 3000.0f, 500.0f };
Vec lbl_1_data_28 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_34 = { 0.0f, 0.0f, 0.0f };

s32 lbl_1_data_64 = -1;
Vec lbl_1_data_68[10][8]; // TODO not right
s32 lbl_1_data_488[0xB] = { 0, 2, 3, 8, 0xA, 9, 0x13, 0xD, 0x10, 0x17, 0x18 };

Vec lbl_1_data_4B4[4] = {
    { -400.0f, 1600.0f, -400.0f },
    { 400.0f, 1600.0f, -400.0f },
    { -400.0f, 1600.0f, 400.0f },
    { 400.0f, 1600.0f, 400.0f },
};

Vec lbl_1_data_514 = { -850.0f, 0.0f, -850.0f };

s32 lbl_1_data_520[0x19] = {
    0xFFFFFF9E,
    0xFFFFFF9F,
    0xFFFFFFA0,
    0xFFFFFFA1,
    0xFFFFFFA2,
    0xFFFFFFCE,
    0xFFFFFFCF,
    0xFFFFFFD0,
    0xFFFFFFD1,
    0xFFFFFFD2,
    0xFFFFFFFE,
    0xFFFFFFFF,
    0,
    1,
    2,
    0x2E,
    0x2F,
    0x30,
    0x31,
    0x32,
    0x5E,
    0x5F,
    0x60,
    0x61,
    0x62,
};

u32 lbl_1_data_584[0x19] = {
    0x50,
    0x64,
    0x78,
    0x64,
    0x50,
    0x64,
    0x8C,
    0xA0,
    0x8C,
    0x64,
    0x78,
    0xA0,
    0xB4,
    0xA0,
    0x78,
    0x64,
    0x8C,
    0xA0,
    0x8C,
    0x64,
    0x50,
    0x64,
    0x78,
    0x64,
    0x50,
};

s32 lbl_1_data_5E8[9] = { 0, 0xFFFFFFCF, 0xFFFFFFD0, 0xFFFFFFD1, 0xFFFFFFFF, 1, 0x2F, 0x30, 0x31 };

Vec lbl_1_data_60C[9] = {
    { 0.0f, 0.0f, 0.0f },
    { -35.416668f, 0.0f, -35.416668f },
    { 0.0f, 0.0f, -35.416668f },
    { 35.416668f, 0.0f, -35.416668f },
    { -35.416668f, 0.0f, 0.0f },
    { 35.416668f, 0.0f, 0.0f },
    { -35.416668f, 0.0f, 35.416668f },
    { 0.0f, 0.0f, 35.416668f },
    { 35.416668f, 0.0f, 35.416668f },
};

s32 lbl_1_data_678[9] = { 0, 0xFFFFFF9E, 0xFFFFFF70, 0xFFFFFFA2, 0xFFFFFFFD, 3, 0x5E, 0x90, 0x62 };

Vec lbl_1_data_69C[9] = {
    { 0.0f, 0.0f, 0.0f },
    { -70.833336f, 0.0f, -70.833336f },
    { 0.0f, 0.0f, -106.25f },
    { 70.833336f, 0.0f, -70.833336f },
    { -106.25f, 0.0f, 0.0f },
    { 106.25f, 0.0f, 0.0f },
    { -70.833336f, 0.0f, 70.833336f },
    { 0.0f, 0.0f, 106.25f },
    { 70.833336f, 0.0f, 70.833336f },
};

s32 lbl_1_data_708[9] = { 0, 0xFFFFFFED, 0xFFFFFFEE, 0xFFFFFFEF, 0xFFFFFFFF, 1, 0x11, 0x12, 0x13 };
s32 lbl_1_data_72C[9] = { 0, 0xFFFFFFDA, 0xFFFFFFCA, 0xFFFFFFDE, 0xFFFFFFFD, 3, 0x22, 0x36, 0x26 };

M438StructBssDE4 lbl_1_bss_DE4;
omObjData *lbl_1_bss_DE0;
omObjData *lbl_1_bss_DDC;
omObjData *lbl_1_bss_DD8;
omObjData *lbl_1_bss_DD4;
omObjData *lbl_1_bss_DC4[4];
omObjData *lbl_1_bss_DC0;
omObjData *lbl_1_bss_DBC;
u16 lbl_1_bss_DBA;
s16 lbl_1_bss_DB8;
s16 lbl_1_bss_DB6;
s16 lbl_1_bss_DB4;
s16 lbl_1_bss_DB2;
s16 lbl_1_bss_DAA[4];
s16 lbl_1_bss_DA8;
s32 lbl_1_bss_DA4;
void *lbl_1_bss_BA4[0x80];
u32 lbl_1_bss_B98;
M438StructBss298 lbl_1_bss_298[48];
s32 lbl_1_bss_294;
u16 lbl_1_bss_C[0x144];
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;

void ObjectSetup(void)
{
    Process *var_r31;
    s32 var_r30;
    omObjData *var_r29;
    s32 var_r28;
    LightData *var_r27;
    s32 var_r26;

    OSReport("******* M438ObjectSetup *********\n");
    Hu3DLighInit();
    var_r28 = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_18);
    Hu3DGLightSpotSet(var_r28, 80.0f, 2);
    Hu3DGLightInfinitytSet(var_r28);
    var_r27 = Hu3DGlobalLight;
    var_r27->unk_00 |= 0x8000;
    var_r31 = omInitObjMan(0x32, 0x2000);
    var_r26 = frand() & 0x1F;
    for (var_r30 = 0; var_r30 < var_r26; var_r30++) {
        fn_1_7DB4();
    }
    CRot.x = -40.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = -10.0f;
    Center.z = 50.0f;
    CZoom = 2075.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 50.0f, 8000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 0x280, 0x1E0);
    lbl_1_bss_DDC = omAddObjEx(var_r31, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_DE0 = omAddObjEx(var_r31, 0x10, 8, 0, -1, fn_1_4DC);
    lbl_1_bss_DD4 = omAddObjEx(var_r31, 0x20, 0x10, 0, -1, fn_1_1204);
    lbl_1_bss_DD8 = omAddObjEx(var_r31, 0x50, 0x10, 0, -1, fn_1_1F0C);
    lbl_1_bss_DC0 = omAddObjEx(var_r31, 0x40, 2, 4, -1, fn_1_4724);
    omAddObjEx(var_r31, 0x60, 0, 0, -1, fn_1_7B58);
    omMakeGroupEx(var_r31, 0, 4);
    omGetGroupMemberListEx(var_r31, 0);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        var_r29 = omAddObjEx(var_r31, 0x30, 2, 0xB, 0, fn_1_2964);
        lbl_1_bss_DC4[var_r30] = var_r29;
        var_r29->work[0] = var_r30;
        var_r29->work[1] = var_r30;
    }
    lbl_1_bss_DBC = omAddObjEx(var_r31, 0x30, 1, 0, 0, fn_1_A60C);
    Hu3DShadowCreate(30.0f, 100.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.4f);
    Hu3DShadowPosSet(&lbl_1_data_1C, &lbl_1_data_28, &lbl_1_data_34);
    fn_1_B4D8(var_r31);
    omGameSysInit(var_r31);
    HuAudSndGrpSet(0x40);
    WipeCreate(1, 0, 60);
    fn_1_7BBC();
    fn_1_E658(0x60, 0x40);
}

void fn_1_4DC(omObjData *object)
{
    lbl_1_bss_DBA = 0;
    object->func = fn_1_4FC;
}

void fn_1_4FC(omObjData *object)
{
    Vec sp14;
    Vec sp8;

    float var_f31;

    switch (lbl_1_bss_DBA) {
        case 0:
            sp14.x = 0.0f;
            sp14.y = 80.0f;
            sp14.z = -1850.0f;

            sp8.x = 6.0f;
            sp8.y = 0.0f;
            sp8.z = 0.0f;
            var_f31 = 800.0f;
            fn_1_2564(1.0f, &sp14, &sp8, var_f31);
            lbl_1_bss_DB2 = 0x48;
            fn_1_28E4(1, 24.0f + lbl_1_bss_DB2, 10.0f, 0.999f, 90.0f);
            fn_1_28E4(2, 24.0f + lbl_1_bss_DB2, 20.0f, 0.999f, 180.0f);
            lbl_1_bss_DBA += 1;
            fn_1_10910(DATA_MAKE_NUM(DATADIR_M438, 15), 0, 0);
            fn_1_10910(DATA_MAKE_NUM(DATADIR_M438, 9), 0x40, 0x40);
            fn_1_10910(DATA_MAKE_NUM(DATADIR_M438, 10), 0x40, 0x40);
            break;
        case 1:
            if (--lbl_1_bss_DB2 == 0) {
                lbl_1_bss_DB2 = 0x14;
                lbl_1_bss_DBA += 1;
            }
            break;
        case 3:
            if (--lbl_1_bss_DB2 == 0) {
                sp14.x = 0.0f;
                sp14.y = -10.0f;
                sp14.z = 50.0f;

                sp8.x = -40.0f;
                sp8.y = 0.0f;
                sp8.z = 0.0f;
                var_f31 = 2075.0f;
                lbl_1_bss_DB2 = 0x3C;
                fn_1_2564(lbl_1_bss_DB2, &sp14, &sp8, var_f31);
                lbl_1_bss_DBA += 1;
            }
            break;
        case 4:
            if (--lbl_1_bss_DB2 == 0) {
                lbl_1_bss_DBA += 1;
            }
            break;
        case 5:
            lbl_1_bss_DBA = 6;
            lbl_1_bss_DB8 = lbl_1_bss_DB6 = -1;
            object->func = fn_1_974;
            break;
    }
    if (omSysExitReq != 0 && WipeStatGet() == 0) {
        WipeCreate(2, 0, 60);
        object->func = fn_1_1174;
    }
}

void fn_1_974(omObjData *object)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;
    s16 var_r28;
    s32 var_r27;
    M438MainWork *var_r25;
    s32 var_r24;

    switch (lbl_1_bss_DBA) {
        case 6:
            if (lbl_1_bss_DB6 == -1) {
                lbl_1_bss_DB4 = 0xE10;
                lbl_1_bss_DB6 = MGSeqCreate(3, 0);
                MGSeqPosSet(lbl_1_bss_DB6, 320.0f, 240.0f);
            }
            else {
                if (MGSeqStatGet(lbl_1_bss_DB6) == 0) {
                    lbl_1_bss_DB8 = MGSeqCreate(1, lbl_1_bss_DB4 / 60, -1, -1);
                    for (var_r31 = 0; var_r31 < 4; var_r31++) {
                        lbl_1_bss_DAA[var_r31] = 0;
                    }
                    lbl_1_bss_DA8 = 4;
                    lbl_1_bss_DB6 = -1;
                    lbl_1_bss_DBA += 1;
                    lbl_1_bss_DB2 = 0;
                }
            }
            if (lbl_1_data_64 == -1 && (MGSeqStatGet(lbl_1_bss_DB6) & 0x10) != 0) {
                lbl_1_data_64 = HuAudSeqPlay(0x49);
            }
            lbl_1_bss_B98 = 0x12C;
            break;
        case 7:
            var_r29 = 0;
            lbl_1_bss_DB4--;
            MGSeqParamSet(lbl_1_bss_DB8, 1, (lbl_1_bss_DB4 + 0x3B) / 60);
            if (lbl_1_bss_DB4 == 0) {
                var_r29++;
            }
            var_r28 = 0;
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (lbl_1_bss_DAA[var_r31] == 0) {
                    var_r28++;
                }
            }
            if (var_r28 < 2) {
                var_r29++;
            }
            if (var_r29 != 0) {
                lbl_1_bss_DBA += 1;
            }
            break;
        case 8:
            if (lbl_1_bss_B98 != 0) {
                lbl_1_bss_B98--;
            }
            var_r24 = 0;
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (lbl_1_bss_DAA[var_r31] != 0) {
                    var_r25 = lbl_1_bss_DC4[var_r31]->data;
                    if (var_r25->unk_10 == 0) {
                        var_r24 = 1;
                    }
                }
            }
            if (lbl_1_bss_DB6 == -1) {
                lbl_1_bss_DB6 = MGSeqCreate(3, 1);
                MGSeqPosSet(lbl_1_bss_DB6, 320.0f, 240.0f);
                if (lbl_1_bss_DB8 >= 0) {
                    MGSeqParamSet(lbl_1_bss_DB8, 2, -1);
                    lbl_1_bss_DB8 = -1;
                }
                HuAudSeqFadeOut(lbl_1_data_64, 0x3C);
            }
            else if ((MGSeqStatGet(lbl_1_bss_DB6) == 0) && (var_r24 == 0 || lbl_1_bss_B98 == 0)) {
                lbl_1_bss_DB6 = -1;
                lbl_1_bss_DB2 = 0x3C;
                lbl_1_bss_DBA += 1;
            }
            break;
        case 9:
            if (--lbl_1_bss_DB2 == 0) {
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    if (lbl_1_bss_DAA[var_r31] == 0) {
                        break;
                    }
                }
                if (var_r31 < 4) {
                    for (var_r31 = 0; var_r31 < 4; var_r31++) {
                        var_r27 = 0;
                        for (var_r30 = 0; var_r30 < 4; var_r30++) {
                            if (lbl_1_bss_DAA[var_r30] < lbl_1_bss_DAA[var_r31]) {
                                var_r27++;
                            }
                        }
                        GWPlayerCoinWinSet(var_r31, var_r27);
                    }
                }
                else {
                    for (var_r31 = 0; var_r31 < 4; var_r31++) {
                        GWPlayerCoinWinSet(var_r31, 3);
                    }
                }
                var_r31 = 0;
                var_r30 = 0;
                for (; var_r31 < 4; var_r31++) {
                    if (lbl_1_bss_DAA[var_r31] == 0) {
                        lbl_1_bss_DAA[var_r30++] = GWPlayerCfg[var_r31].character;
                    }
                }
                for (; var_r30 < 4; var_r30++) {
                    lbl_1_bss_DAA[var_r30] = -1;
                }
                lbl_1_bss_DA4 = 0;
                lbl_1_bss_DB2 = 0x3C;
                lbl_1_bss_DBA += 1;
            }
            break;
        case 10:
            lbl_1_bss_DA4++;
            if (lbl_1_bss_DB6 == -1) {
                if (lbl_1_bss_DAA[0] == -1) {
                    HuAudSStreamPlay(4);
                }
                else {
                    HuAudSStreamPlay(1);
                }
                lbl_1_bss_DB6 = 0;
            }
            else if (lbl_1_bss_DA4 > 210.0f) {
                lbl_1_bss_DB2 = 0xB4;
                lbl_1_bss_DB6 = -1;
                lbl_1_bss_DBA += 1;
            }
            break;
        case 11:
            WipeCreate(2, 0, 0x3C);
            object->func = fn_1_1174;
            break;
    }
    if (omSysExitReq != 0 && WipeStatGet() == 0) {
        WipeCreate(2, 0, 0x3C);
        object->func = fn_1_1174;
    }
}

void fn_1_1174(omObjData *object)
{
    if (WipeStatGet() == 0) {
        CharModelKill(-1);
        fn_1_11658();
        fn_1_7D30();
        fn_1_B548();
        HuAudFXListnerKill();
        if (lbl_1_bss_DB8 >= 0) {
            MGSeqKill(lbl_1_bss_DB8);
            lbl_1_bss_DB8 = -1;
        }
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_1204(omObjData *object)
{
    M438StructBss298 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;

    object->func = fn_1_13A0;

    for (var_r31 = lbl_1_bss_298, var_r30 = 0, var_r28 = 0; var_r30 < 10; var_r31++, var_r30++) {
        for (var_r29 = 0; var_r29 < 8; var_r29++) {
            if (lbl_1_data_68[var_r30][var_r29 + 1].y != 0.0f) {
                break;
            }
            var_r31->unk_00 = 0;
            var_r31->unk_02 = var_r30;
            var_r31->unk_01 = var_r28 + 1;

            var_r31->unk_18 = lbl_1_data_68[var_r30][var_r29];
            VECSubtract(&lbl_1_data_68[var_r30][var_r29 + 1], &lbl_1_data_68[var_r30][var_r29], &var_r31->unk_24);
            var_r31->unk_14 = VECMag(&var_r31->unk_24);
            VECNormalize(&var_r31->unk_24, &var_r31->unk_24);
            var_r31->unk_08 = var_r31->unk_0A = 0;
            var_r31->unk_06 = 0;
            var_r31->unk_0C = 0.0f;
            var_r31++;
            var_r28++;
        }
        var_r31--;
        var_r31->unk_01 = 0;
    }
    for (; var_r28 < 48; var_r28++, var_r31++) {
        var_r31->unk_02 = -1;
    }
}

void fn_1_13A0(omObjData *object)
{
    s32 sp8[48];

    M438StructBss298 *var_r31;
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;

    switch (lbl_1_bss_DBA) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;
        case 6:
            lbl_1_bss_294 = 0x1E;
            break;
        case 7:
            if (--lbl_1_bss_294 == 0) {
                fn_1_7DD8(10, sp8);
                if (lbl_1_bss_DB4 > 0x960) {
                    var_r27 = 1;
                }
                else if (lbl_1_bss_DB4 > 0x258) {
                    var_r27 = 2;
                }
                else {
                    var_r27 = 3;
                }
                for (var_r31 = lbl_1_bss_298, var_r30 = 0; var_r30 < 0x30; var_r30++, var_r31++) {
                    if (var_r31->unk_02 == -1) {
                        break;
                    }
                    if (var_r31->unk_01 == 0 && var_r31->unk_00) {
                        var_r27--;
                    }
                }
                for (var_r28 = 0, var_r26 = 0; var_r26 < var_r27; var_r28++) {
                    var_r25 = sp8[var_r28];
                    var_r24 = (s32)(80.0f * (0.000015258789f * fn_1_7DB4())) + 0x3C;
                    for (var_r31 = lbl_1_bss_298, var_r30 = 0; var_r30 < 0x30; var_r30++, var_r31++) {
                        if (var_r31->unk_02 == var_r25) {
                            if (var_r31->unk_00 != 0) {
                                break;
                            }
                            var_r31->unk_00 = 1;
                            var_r31->unk_04 = var_r24;
                        }
                    }
                    if (var_r30 == 0x30) {
                        var_r26++;
                    }
                }
                lbl_1_bss_294 = 60;
            }
            break;
    }
    for (var_r31 = lbl_1_bss_298, var_r28 = 0; var_r28 < 0x30; var_r28++, var_r31++) {
        switch (var_r31->unk_00) {
            case 0:
                break;
            case 1:
                if (var_r31->unk_01 == 0) {
                    HuAudFXPlay(0x6FB);
                }
                if (var_r31->unk_08 != 0) {
                    fn_1_108E4(var_r31->unk_08, 0, 0);
                }
                else {
                    var_r31->unk_08 = fn_1_10258(1, 1);
                    fn_1_11018(lbl_1_bss_DE4.unk_36, 0, 0x450009);
                }
                fn_1_1204C(var_r31->unk_08, 4);
                fn_1_118FC(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, var_r31->unk_18.x, var_r31->unk_18.y, var_r31->unk_18.z);
                fn_1_11E18(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, 0.0f, (atan2d(var_r31->unk_24.x, var_r31->unk_24.z)) - 90.0, 0.0f);
                fn_1_11B78(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, 32.0f, 32.0f, 0.0f);
                fn_1_11F68(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, var_r31->unk_14 / 64, 0.78125f, 1.0f);
                fn_1_12538(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, 0);
                fn_1_1274C(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, lbl_1_bss_DE4.unk_3A, 0x21);
                fn_1_128C8(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, lbl_1_bss_DE4.unk_3A, 0.5f);
                if (var_r31->unk_0A == 0) {
                    var_r31->unk_0A = fn_1_10258(0x64, 1);
                }
                var_r29 = var_r31->unk_0A;
                fn_1_12174(var_r31->unk_0A, 4);
                fn_1_11018(var_r29, 0, 0x45000A);
                lbl_1_bss_DE4.unk_40[var_r29].unk_30 = fn_1_63B0;
                fn_1_11890(var_r29, var_r31->unk_18.x, var_r31->unk_18.y, var_r31->unk_18.z);
                fn_1_124CC(var_r29, 1);
                lbl_1_bss_DE4.unk_40[var_r29].unk_7C = 0;
                lbl_1_bss_DE4.unk_40[var_r29].unk_80 = var_r31->unk_24.x;
                lbl_1_bss_DE4.unk_40[var_r29].unk_84 = var_r31->unk_24.z;
                lbl_1_bss_DE4.unk_40[var_r29].unk_88 = var_r31->unk_14;
                lbl_1_bss_DE4.unk_40[var_r29].unk_8C = 10.0f;
                lbl_1_bss_DE4.unk_40[var_r29].unk_90 = 0.02f;
                var_r31->unk_06 = 0x3C;
                var_r31->unk_10 = 0.2f;
                var_r31->unk_0C = 10.0f;
                var_r31->unk_00++;
                break;
            case 2:
                var_r31->unk_10 += 0.015f;
                if (var_r31->unk_10 >= 0.6f) {
                    var_r31->unk_10 = 0.6f;
                }
                lbl_1_bss_DE4.unk_40[var_r31->unk_0A].unk_90 = var_r31->unk_10;
                if (lbl_1_bss_DBA != 7) {
                    var_r31->unk_00 = 5;
                }
                else {
                    if (--var_r31->unk_06 == 0) {
                        lbl_1_bss_DE4.unk_40[var_r31->unk_0A].unk_7E = 1;
                        fn_1_12174(var_r31->unk_08, 4);
                        lbl_1_bss_DE4.unk_40[var_r31->unk_0A].unk_90 = 1.0f;
                        var_r31->unk_00++;
                    }
                }
                break;
            case 3:
                var_r31->unk_10 += 0.06f;
                if (var_r31->unk_10 >= 1.0f) {
                    var_r31->unk_10 = 1.0f;
                }
                lbl_1_bss_DE4.unk_40[var_r31->unk_0A].unk_90 = var_r31->unk_10;
                var_r31->unk_0C += 7.5000005f;
                fn_1_11F68(var_r31->unk_08, 0, var_r31->unk_14 / 64, var_r31->unk_0C / 64, 1.0f);
                lbl_1_bss_DE4.unk_40[var_r31->unk_0A].unk_8C = var_r31->unk_0C;
                if (var_r31->unk_0C >= 200.0f) {
                    var_r31->unk_00++;
                }
                if (lbl_1_bss_DBA != 7) {
                    var_r31->unk_00 = 5;
                }
                break;
            case 4:
                if (lbl_1_bss_DBA != 7) {
                    var_r31->unk_00 = 5;
                }
                else {
                    if (--var_r31->unk_04 == 0) {
                        var_r31->unk_00++;
                    }
                }
                break;
            case 5:
                var_r31->unk_0C = var_r31->unk_0C - 7.5000005f;
                fn_1_11F68(var_r31->unk_08, 0, var_r31->unk_14 / 64, var_r31->unk_0C / 64, 1.0f);
                lbl_1_bss_DE4.unk_40[var_r31->unk_0A].unk_8C = var_r31->unk_0C;
                var_r31->unk_10 = var_r31->unk_10 - 0.03f;
                if (var_r31->unk_10 <= 0.0f) {
                    var_r31->unk_10 = 0.01f;
                }
                lbl_1_bss_DE4.unk_40[var_r31->unk_0A].unk_90 = var_r31->unk_10;
                if (!(var_r31->unk_0C > 0.0f)) {
                    for (var_r30 = 0; var_r30 < 0x5A; var_r30++) {
                        lbl_1_bss_DE4.unk_40[var_r31->unk_0A].unk_3C[var_r30].unk_5C = 0;
                    }
                    fn_1_1204C(var_r31->unk_08, 4);
                    fn_1_1204C(var_r31->unk_0A, 4);
                    var_r31->unk_00 = 0;
                }
                break;
        }
    }
}

u8 fn_1_1D60(omObjData *object)
{
    Vec sp18;
    Vec spC;
    float sp8;

    float var_f31;
    float var_f30;

    M438StructBss298 *var_r31;
    M438MainWork2 *var_r30;
    s32 var_r29;

    var_r30 = object->data;
    sp8 = VECMag(&var_r30->unk_84);
    for (var_r31 = lbl_1_bss_298, var_r29 = 0; var_r29 < 0x30; var_r29++, var_r31++) {
        if (var_r31->unk_00 > 2 && var_r31->unk_00 < 5) {
            spC.x = var_r31->unk_24.x * var_r31->unk_14;
            spC.y = 0.0f;
            spC.z = var_r31->unk_24.z * var_r31->unk_14;
            var_f31 = fn_1_A14C(&var_r30->unk_90, &var_r30->unk_84, &var_r31->unk_18, &spC);
            if (var_f31 <= 1.0 && var_f31 > 0.0) {
                sp18.x = var_r30->unk_90.x + (var_f31 * var_r30->unk_84.x);
                var_f31 = (sp18.x - var_r31->unk_18.x) / spC.x;
                if (var_f31 > 1.0) {
                    continue;
                }
                if (!(var_f31 < 0.0)) {
                    break;
                }
            }
            else {
                var_f30 = fn_1_9960(&var_r30->unk_6C, &var_r31->unk_18, &spC);
                if (!(var_f30 > 3600.0005f)) {
                    break;
                }
            }
        }
    }
    if (var_r29 == 0x30) {
        return 0;
    }
    return 1;
}

void fn_1_1F0C(omObjData *object)
{
    M438MainWork3 *var_r31;

    var_r31 = fn_1_7BFC(0x190);
    object->data = var_r31;
    var_r31->unk_148 = var_r31->unk_144 = 0.0f;
    var_r31->unk_140 = 1.0f;
    var_r31->unk_10.x = var_r31->unk_28.x = -40.0f;
    var_r31->unk_10.y = var_r31->unk_28.y = 0.0f;
    var_r31->unk_10.z = var_r31->unk_28.z = 0.0f;
    var_r31->unk_04.x = var_r31->unk_1C.x = 0.0f;
    var_r31->unk_04.y = var_r31->unk_1C.y = -10.0f;
    var_r31->unk_04.z = var_r31->unk_1C.z = 50.0f;
    var_r31->unk_130 = var_r31->unk_134 = 2075.0f;
    var_r31->unk_188[0] = var_r31->unk_188[1] = var_r31->unk_188[2] = 0;
    object->func = fn_1_2070;
    HuAudFXListnerSetEX(&Hu3DCamera->pos, &Hu3DCamera->up, 10000.0f, 4166.6665f, 0.0f, 300.0f, 0.0f);
}

void fn_1_2070(omObjData *object)
{
    Vec sp8;

    float var_f31;

    M438MainWork3 *var_r31;
    s32 var_r30;

    var_r31 = object->data;
    if (var_r31->unk_148 > 0.0f) {
        var_r31->unk_148 = var_r31->unk_148 - var_r31->unk_140;
        var_f31 = (var_r31->unk_144 - var_r31->unk_148) / var_r31->unk_144;
        var_f31 = sind((90.0f * var_f31));
        if (var_r31->unk_00 == 0) {
            var_r31->unk_04.x = var_r31->unk_1C.x + (var_f31 * (var_r31->unk_34.x - var_r31->unk_1C.x));
            var_r31->unk_04.y = var_r31->unk_1C.y + (var_f31 * (var_r31->unk_34.y - var_r31->unk_1C.y));
            var_r31->unk_04.z = var_r31->unk_1C.z + (var_f31 * (var_r31->unk_34.z - var_r31->unk_1C.z));
            var_r31->unk_10.x = var_r31->unk_28.x + (var_f31 * (var_r31->unk_40.x - var_r31->unk_28.x));
            var_r31->unk_10.y = var_r31->unk_28.y + (var_f31 * (var_r31->unk_40.y - var_r31->unk_28.y));
            var_r31->unk_10.z = var_r31->unk_28.z + (var_f31 * (var_r31->unk_40.z - var_r31->unk_28.z));
            var_r31->unk_130 = var_r31->unk_134 + (var_f31 * (var_r31->unk_138 - var_r31->unk_134));
        }
        else {
            fn_1_9420((float *)&var_r31->unk_04, var_r31->unk_F4, (float(*)[3]) & var_r31->unk_64, var_r31->unk_88, 3, 2.0f * var_f31);
            fn_1_9420((float *)&var_r31->unk_10, var_r31->unk_100, (float(*)[3]) & var_r31->unk_AC, var_r31->unk_D0, 3, 2.0f * var_f31);
            var_r31->unk_130 = fn_1_8EEC(var_r31->unk_124, var_r31->unk_10C, var_r31->unk_118, 2.0f * var_f31);
        }
    }
    CRot.x = var_r31->unk_10.x;
    CRot.y = var_r31->unk_10.y;
    CRot.z = var_r31->unk_10.z;
    Center.x = var_r31->unk_04.x;
    Center.y = var_r31->unk_04.y;
    Center.z = var_r31->unk_04.z;
    CZoom = var_r31->unk_130;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        var_r31->unk_17C[var_r30] = 0.0f;
        if (var_r31->unk_188[var_r30] != 0) {
            var_r31->unk_17C[var_r30] = var_r31->unk_14C[var_r30] * sind(var_r31->unk_164[var_r30]);
            var_r31->unk_164[var_r30] += var_r31->unk_170[var_r30];
            var_r31->unk_14C[var_r30] *= var_r31->unk_158[var_r30];
            var_r31->unk_188[var_r30]--;
        }
    }
    Center.x += var_r31->unk_17C[0];
    Center.y += var_r31->unk_17C[1];
    Center.z += var_r31->unk_17C[2];
    sp8.x = -(sind(CRot.y) * cosd(CRot.x));
    sp8.y = sind(CRot.x);
    sp8.z = -(cosd(CRot.y) * cosd(CRot.x));
    HuAudFXListnerUpdate(&Hu3DCamera->pos, &sp8);
}

void fn_1_2564(float arg8, Vec *arg0, Vec *arg1, float arg9)
{
    M438MainWork3 *var_r31;

    var_r31 = lbl_1_bss_DD8->data;
    var_r31->unk_00 = 0;
    var_r31->unk_144 = arg8;
    var_r31->unk_148 = arg8;
    var_r31->unk_1C = var_r31->unk_04;
    var_r31->unk_34.x = arg0->x;
    var_r31->unk_34.y = arg0->y;
    var_r31->unk_34.z = arg0->z;
    var_r31->unk_28 = var_r31->unk_10;
    var_r31->unk_40.x = arg1->x;
    var_r31->unk_40.y = arg1->y;
    var_r31->unk_40.z = arg1->z;
    var_r31->unk_134 = var_r31->unk_130;
    var_r31->unk_138 = arg9;
}

void fn_1_2604(float arg8, Vec *arg0, Vec *arg1, float arg9, Vec *arg2, Vec *arg3, float argA)
{
    float var_f31;
    float var_f30;

    M438MainWork3 *var_r31;

    var_r31 = lbl_1_bss_DD8->data;
    var_r31->unk_00 = 1;
    var_r31->unk_148 = var_r31->unk_144 = arg8;
    var_r31->unk_1C = var_r31->unk_04;

    var_r31->unk_34.x = arg0->x;
    var_r31->unk_34.y = arg0->y;
    var_r31->unk_34.z = arg0->z;

    var_r31->unk_4C.x = arg2->x;
    var_r31->unk_4C.y = arg2->y;
    var_r31->unk_4C.z = arg2->z;

    var_r31->unk_28 = var_r31->unk_10;

    var_r31->unk_40.x = arg1->x;
    var_r31->unk_40.y = arg1->y;
    var_r31->unk_40.z = arg1->z;

    var_r31->unk_58.x = arg3->x;
    var_r31->unk_58.y = arg3->y;
    var_r31->unk_58.z = arg3->z;

    var_r31->unk_134 = var_r31->unk_130;
    var_r31->unk_138 = arg9;
    var_r31->unk_13C = argA;
    var_r31->unk_64[0] = var_r31->unk_1C;
    var_r31->unk_64[1] = var_r31->unk_4C;
    var_r31->unk_64[2] = var_r31->unk_34;
    var_r31->unk_AC[0] = var_r31->unk_28;
    var_r31->unk_AC[1] = var_r31->unk_58;
    var_r31->unk_AC[2] = var_r31->unk_40;

    var_r31->unk_10C[0] = var_r31->unk_134;
    var_r31->unk_10C[1] = var_r31->unk_13C;
    var_r31->unk_10C[2] = var_r31->unk_138;

    var_r31->unk_124[0] = 0.0f;
    if ((var_r31->unk_10C[1] - var_r31->unk_10C[0]) < 0.0f) {
        var_f31 = -(var_r31->unk_10C[1] - var_r31->unk_10C[0]);
    }
    else {
        var_f31 = var_r31->unk_10C[1] - var_r31->unk_10C[0];
    }
    var_r31->unk_124[1] = var_f31;
    if ((var_r31->unk_10C[2] - var_r31->unk_10C[1]) < 0.0f) {
        var_f30 = -(var_r31->unk_10C[2] - var_r31->unk_10C[1]);
    }
    else {
        var_f30 = var_r31->unk_10C[2] - var_r31->unk_10C[1];
    }
    var_r31->unk_124[2] = var_r31->unk_124[1] + var_f30;
    fn_1_9040(var_r31->unk_F4, var_r31->unk_64, var_r31->unk_88, 3);
    fn_1_9040(var_r31->unk_100, var_r31->unk_AC, var_r31->unk_D0, 3);
    fn_1_8C34(var_r31->unk_124, var_r31->unk_10C, var_r31->unk_118, 3);
}

void fn_1_28BC(float arg8)
{
    M438MainWork3 *var_r31;

    var_r31 = lbl_1_bss_DD8->data;
    var_r31->unk_140 = arg8;
}

void fn_1_28E4(u8 arg0, u16 arg1, float arg9, float argA, float arg4)
{
    M438MainWork3 *var_r31 = lbl_1_bss_DD8->data;

    var_r31->unk_188[arg0] = arg1;
    var_r31->unk_14C[arg0] = arg9;
    var_r31->unk_158[arg0] = argA;
    var_r31->unk_170[arg0] = arg4;
    var_r31->unk_164[arg0] = 90.0f;
}

void fn_1_2964(omObjData *object)
{
    M438MainWork *var_r31;
    s32 var_r29;
    u32 var_r28;
    s32 var_r27;

    float sp8[4] = { 0.25f, 0.5f, 0.75f, 1.0f };
    var_r31 = fn_1_7BFC(sizeof(M438MainWork));
    object->data = var_r31;
    memset(var_r31, 0, sizeof(M438MainWork));
    var_r31->unk_00 = object->work[0];
    var_r31->unk_01 = GWPlayerCfg[var_r31->unk_00].character;
    var_r31->unk_02 = var_r31->unk_00 >> 1;
    var_r31->unk_03 = var_r31->unk_00 & 1;
    var_r31->unk_04 = GWPlayerCfg[var_r31->unk_00].pad_idx;
    var_r31->unk_05 = GWPlayerCfg[var_r31->unk_00].iscom;
    var_r31->unk_06 = GWPlayerCfg[var_r31->unk_00].diff;
    var_r31->unk_20 = var_r31->unk_22 = 0;
    var_r31->unk_3C = sp8[var_r31->unk_06];
    var_r31->unk_40 = (2700.0f * (var_r31->unk_3C - 0.075f)) + (0.6f * frandmod(0x3E8));
    if (var_r31->unk_40 > 0xEA60) {
        var_r31->unk_40 = 0xB4;
    }
    var_r31->unk_44 = frandmod(0xB4);
    var_r31->unk_07 = 1;
    var_r31->unk_0D = 1;
    var_r31->unk_0E = 0;
    var_r31->unk_0B = 0;
    var_r31->unk_ED = 0;
    var_r31->unk_EC = 0;
    var_r31->unk_0F = 0;
    var_r31->unk_0A = 0;
    var_r28 = object->work[1];
    var_r31->unk_6C.x = lbl_1_data_4B4[var_r28].x;
    var_r31->unk_6C.y = lbl_1_data_4B4[var_r28].y + 100.0f * (0.000030517578f * (fn_1_7DB4() - 0x8000));
    var_r31->unk_6C.z = lbl_1_data_4B4[var_r28].z;
    var_r31->unk_84 = var_r31->unk_88 = var_r31->unk_8C = 0.0f;
    var_r31->unk_78 = var_r31->unk_7C = var_r31->unk_80 = 0.0f;
    var_r31->unk_28 = var_r31->unk_7C;
    var_r31->unk_2C = 0.0f;
    var_r31->unk_24 = 0.0f;
    var_r31->unk_30 = 1.0f;
    memset(var_r31->unk_F0, 0, sizeof(var_r31->unk_F0));
    var_r27 = CharModelCreate(var_r31->unk_01, 8);
    object->model[0] = var_r27;
    Hu3DModelAttrSet(var_r27, 0x40000001);
    Hu3DModelShadowSet(var_r27);
    CharModelStepTypeSet(var_r31->unk_01, 0);
    var_r31->unk_A4 = -1;
    var_r31->unk_A8 = -1;
    for (var_r29 = 0; var_r29 < 11; var_r29++) {
        object->motion[var_r29] = CharModelMotionCreate(var_r31->unk_01, lbl_1_data_488[var_r29]);
    }
    CharModelVoiceEnableSet(var_r31->unk_01, object->motion[3], 0);
    CharModelMotionDataClose(var_r31->unk_01);
    CharModelMotionSet(var_r31->unk_01, object->motion[var_r31->unk_20]);
    object->func = fn_1_2D50;
}

void fn_1_2D50(omObjData *object)
{
    s32 sp8;
    M438MainWork *var_r31;

    sp8 = object->model[0];
    var_r31 = object->data;
    var_r31->unk_18 = var_r31->unk_1A = 0;
    var_r31->unk_1C = var_r31->unk_1E = 0;
    switch (lbl_1_bss_DBA) {
        case 1:
        case 4:
            break;
        case 3:
            var_r31->unk_20 = 3;
            var_r31->unk_88 = 0.0f;
            var_r31->unk_0D = 0;
            break;
        case 6:
            object->func = fn_1_2E4C;
            break;
    }
    if (var_r31->unk_6C.y <= 0.0f) {
        var_r31->unk_6C.y = 0.0f;
        var_r31->unk_0D = 1;
    }
    fn_1_35C0(object);
}

void fn_1_2E4C(omObjData *object)
{
    Vec sp30;
    Vec sp24;

    float var_f30;
    float var_f29;
    float var_f28;

    s32 var_r25 = object->model[0];
    M438MainWork *var_r31 = object->data;
    if (var_r31->unk_07 != 0) {
        if (lbl_1_bss_DBA == 7 && (var_r31->unk_07 & 2) == 0) {
            if (var_r31->unk_05 != 0) {
                fn_1_4374(object);
            }
            else {
                var_r31->unk_18 = HuPadStkX[var_r31->unk_04];
                var_r31->unk_1A = HuPadStkY[var_r31->unk_04];
                var_r31->unk_1C = HuPadBtnDown[var_r31->unk_04];
                var_r31->unk_1E = HuPadBtn[var_r31->unk_04];
            }
        }
        else {
            var_r31->unk_18 = var_r31->unk_1A = 0;
            var_r31->unk_1C = var_r31->unk_1E = 0;
        }
        switch (lbl_1_bss_DBA) {
            case 6:
                var_r31->unk_AC = var_r31->unk_B0 = var_r31->unk_B4 = 0.0f;
                break;
            case 7:
                if (fn_1_1D60(object) && (var_r31->unk_07 & 2) == 0) {
                    omVibrate(var_r31->unk_00, 0xC, 6, 6);
                    var_r31->unk_20 = 6;
                    var_r31->unk_07 = var_r31->unk_07 | 2;
                    var_r31->unk_0D = 0;
                    var_r31->unk_28 = atan2d(var_r31->unk_6C.x, var_r31->unk_6C.z);
                    var_r31->unk_88 = 22.458334f;
                    lbl_1_bss_DAA[var_r31->unk_00] = lbl_1_bss_DA8--;
                }
                break;
            case 8:
            case 9:
                var_r31->unk_7C = fn_1_7EDC(var_r31->unk_7C, 0.0f, 0.9f);
                break;
            case 10:
                if ((var_r31->unk_07 & 2) == 0) {
                    var_r31->unk_20 = 9;
                }
                break;
        }
        if (var_r31->unk_20 != 7) {
            sp30 = var_r31->unk_6C;
            sp30.y = 0.0f;
            var_f30 = VECMag(&sp30);
            if (var_f30 > 700.0f) {
                var_f29 = -100.0f;
            }
            else {
                var_f29 = 0.0f;
            }
            if (var_r31->unk_6C.y < var_f29) {
                var_r31->unk_6C.y = var_f29;
                var_r31->unk_0D = 1;
            }
            if (((var_r31->unk_07 & 2) == 0) && (var_f30 > 675.0f)) {
                var_f28 = atan2d(sp30.x, sp30.z);
                if (fn_1_DEA0(var_f28) != 0) {
                    fn_1_9634(&sp30);
                    var_r31->unk_6C.x = 675.0f * sp30.x;
                    var_r31->unk_6C.z = 675.0f * sp30.z;
                }
                else if (var_f30 > 700.0f) {
                    omVibrate(var_r31->unk_00, 0xC, 6, 6);
                    var_r31->unk_07 = var_r31->unk_07 | 2;
                    var_r31->unk_20 = 6;
                    var_r31->unk_0D = 0;
                    var_r31->unk_28 = var_f28;
                    var_r31->unk_88 = 22.458334f;
                    lbl_1_bss_DAA[var_r31->unk_00] = lbl_1_bss_DA8--;
                }
            }
        }
        fn_1_35C0(object);
        if ((var_r31->unk_07 & 2) != 0 && var_r31->unk_10 == 0) {
            sp30 = var_r31->unk_6C;
            sp30.y = 0.0f;
            if (sp30.z < 0.0f) {
                sp30.z *= 0.25f;
            }
            var_f30 = VECMag(&sp30);
            Hu3D3Dto2D(&var_r31->unk_6C, 1, &sp24);
            sp24.x = sp24.x - 288.0f;
            sp24.y -= 240.0f;
            if (fabs(sp24.x) > 308.0 || sp24.y < -260.0f || sp24.y > 290.0f || var_r31->unk_6C.y < -300.0f || var_f30 > 1400.0f) {
                var_r31->unk_10 = 1;
            }
        }
        if (var_r31->unk_10 != 0) {
            var_r31->unk_07 = 0;
            Hu3DModelAttrSet(var_r25, 1);
            object->func = fn_1_35BC;
        }
    }
}

void fn_1_35BC(omObjData *object) { }

void fn_1_35C0(omObjData *object)
{
    Vec sp10;
    float spC;
    s16 sp0A;
    s16 sp8;

    float var_f31;
    float var_f30;
    float var_f29;

    M438MainWork *var_r31;
    s16 var_r30;
    s16 var_r29;
    s16 var_r28;
    s16 var_r27;
    s32 var_r25;
    s32 var_r24;
    M438MainWork4 *var_r23;

    var_r23 = lbl_1_bss_DC0->data;
    var_r31 = object->data;
    var_r25 = object->model[0];
    var_r28 = var_r31->unk_20;
    var_r31->unk_90 = var_r31->unk_6C;
    var_r30 = var_r31->unk_18;
    var_r29 = var_r31->unk_1A;
    sp0A = var_r31->unk_1C;
    sp8 = var_r31->unk_1E;
    switch (var_r31->unk_20) {
        case 0:
        case 1:
        case 2:
            var_r31->unk_24 = 0.14f * sqrtf((var_r30 * var_r30) + (var_r29 * var_r29));
            if (var_r31->unk_24 > 0.1f) {
                if (var_r31->unk_24 >= 6.0f) {
                    var_r28 = 2;
                    var_r27 = 1;
                }
                else {
                    var_r28 = 1;
                    var_r27 = 1;
                }
                var_f30 = atan2d(var_r30, -var_r29);
                if (var_r31->unk_05 != 0) {
                    var_r31->unk_7C = fn_1_E488(var_r31->unk_7C, var_f30, 0.15f);
                }
                else {
                    var_r31->unk_7C = fn_1_E488(var_r31->unk_7C, var_f30, 0.2f);
                }
                var_r31->unk_28 = fn_1_7EDC(var_r31->unk_28, var_f30, 0.5f);
                var_r31->unk_2C += 1.0f;
                if (var_r31->unk_2C >= (0.5f * var_r31->unk_30)) {
                    var_r31->unk_2C = var_r31->unk_2C - (0.5f * var_r31->unk_30);
                }
                var_r31->unk_24 = var_r31->unk_24 * (1.0 + (0.25 * cosd((90.0f * (var_r31->unk_2C / (0.5f * var_r31->unk_30))))));
                var_r31->unk_38 = 0;
                var_r31->unk_34 = 60.0f * (0.3f + (0.00040000002f * frandmod(0x3E8)));
            }
            else {
                var_r31->unk_2C = 0.0f;
                var_r31->unk_24 = 0.0f;
                var_r28 = 0;
                var_r27 = 1;
                if (lbl_1_bss_DBA == 7) {
                    var_r31->unk_38++;
                    if (var_r31->unk_38 > var_r31->unk_34) {
                        VECSubtract(&var_r23->unk_34, &var_r31->unk_6C, &sp10);
                        var_f29 = atan2d(sp10.x, sp10.z);
                        if (fabs(fn_1_E5A4(var_r31->unk_7C, var_f29)) > 10.0) {
                            var_r28 = 1;
                        }
                        var_r31->unk_7C = fn_1_E488(var_r31->unk_7C, var_f29, 0.15f);
                    }
                }
            }
            var_r31->unk_88 = -2.0416667f;
            break;
        case 3:
            var_r27 = 0;
            if (Hu3DData[var_r25].unk_0C == -1 && CharModelMotionEndCheck(var_r31->unk_01)) {
                var_r31->unk_88 += -2.0416667f;
            }
            else {
                var_r31->unk_88 = 0.0f;
            }
            if (var_r31->unk_0D != 0) {
                if (var_r31->unk_0E != 0) {
                    var_r31->unk_88 = 0.0f;
                    var_r31->unk_0E = 0;
                    var_r28 = 5;
                    var_r27 = 0;
                }
                else {
                    var_r31->unk_88 *= -0.1f;
                    var_r31->unk_0D = 0;
                    var_r28 = 4;
                    var_r27 = 0;
                }
            }
            break;
        case 4:
            var_r31->unk_88 += -2.0416667f;
            if (var_r31->unk_0D != 0 && CharModelMotionEndCheck(var_r31->unk_01)) {
                var_r28 = 5;
                var_r27 = 0;
            }
            break;
        case 5:
            if (CharModelMotionEndCheck(var_r31->unk_01) != 0) {
                var_r28 = 0;
                var_r27 = 1;
            }
            break;
        case 6:
            var_r27 = 1;
            var_r31->unk_24 = 12.0f;
            var_r31->unk_88 += -2.0416667f;
            var_r31->unk_7C = fn_1_7EDC(var_r31->unk_7C, var_r31->unk_28, 0.5f);
            if (var_r31->unk_A4 < 0) {
                var_r31->unk_A4 = HuAudCharVoicePlayPos(var_r31->unk_01, 0x123, &var_r31->unk_6C);
            }
            if (var_r31->unk_0D != 0) {
                var_r31->unk_0D = 0;
                var_r31->unk_88 = 22.458334f;
                if (var_r31->unk_07 != 0 && var_r31->unk_10 == 0) {
                    HuAudCharVoicePlayPos(var_r31->unk_01, 0x11C, &var_r31->unk_6C);
                }
            }
            if ((fn_1_7DB4() & 3) == 0) {
                var_r24 = fn_1_10258(1, 1);
                fn_1_11018(lbl_1_bss_DE4.unk_36, 0, 0x45000A);
                lbl_1_bss_DE4.unk_40[var_r24].unk_30 = fn_1_62BC;
                fn_1_118FC(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, var_r31->unk_6C.x, var_r31->unk_6C.y, var_r31->unk_6C.z);
                fn_1_11CC8(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, sind(var_r31->unk_28), 0.0f, cosd(var_r31->unk_28));
                fn_1_11F68(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, 1.0f, 1.0f, 1.0f);
                fn_1_12090(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, 0x80000004);
                fn_1_12378(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, 0, 0, 0, 0xFF);
                fn_1_1274C(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, lbl_1_bss_DE4.unk_3A, 0x11);
                fn_1_128C8(lbl_1_bss_DE4.unk_36, lbl_1_bss_DE4.unk_38, lbl_1_bss_DE4.unk_3A, 0.5f);
                fn_1_107BC(var_r24);
            }
            break;
        case 7:
            if (var_r31->unk_A4 < 0) {
                var_r31->unk_A4 = HuAudCharVoicePlayPos(var_r31->unk_01, 0x123, &var_r31->unk_6C);
            }
            if (var_r31->unk_A8 < 0) {
                var_r31->unk_A8 = HuAudFXPlay(0x701);
            }
            var_r27 = 1;
            var_r31->unk_24 += 2.0;
            var_r31->unk_88 += -2.0416667f;
            break;
        case 9:
        case 10:
            var_r27 = 0;
            var_r31->unk_88 = -2.0416667f;
            break;
    }
    if ((var_r31->unk_07 & 4) != 0) {
        if ((var_r31->unk_0B & 2) != 0) {
            Hu3DModelAttrSet(var_r25, 1);
        }
        else {
            Hu3DModelAttrReset(var_r25, 1);
        }
        if (--var_r31->unk_0B == 0) {
            var_r31->unk_07 = var_r31->unk_07 & 0xFFFFFFFB;
        }
    }
    var_r31->unk_84 = var_r31->unk_24 * sind(var_r31->unk_28);
    var_r31->unk_8C = var_r31->unk_24 * cosd(var_r31->unk_28);
    var_r31->unk_6C.x += var_r31->unk_84;
    if (var_r31->unk_0D == 0) {
        var_r31->unk_6C.y += var_r31->unk_88;
    }
    var_r31->unk_6C.z += var_r31->unk_8C;
    if (var_r28 != var_r31->unk_22) {
        if (var_r31->unk_20 == 7 && var_r31->unk_14 != 0) {
            var_r31->unk_22 = var_r28;
            var_r31->unk_20 = var_r28;
            CharModelMotionShiftSet(var_r31->unk_01, object->motion[8], 0.0f, 8.0f, var_r27);
        }
        else if (var_r28 < 3) {
            if (var_r28 < 0 || var_r31->unk_20 == 0 || CharModelMotionShiftIDGet(var_r31->unk_01) < 0) {
                var_r31->unk_22 = var_r28;
                var_r31->unk_20 = var_r28;
                CharModelMotionShiftSet(var_r31->unk_01, object->motion[var_r31->unk_20], 0.0f, 8.0f, var_r27);
            }
        }
        var_r31->unk_30 = CharModelMotionMaxTimeGet(var_r31->unk_01);
    }
    omSetTra(object, var_r31->unk_6C.x, var_r31->unk_6C.y, var_r31->unk_6C.z);
    omSetRot(object, var_r31->unk_78, var_r31->unk_7C, var_r31->unk_80);
    if (var_r31->unk_A4 >= 0) {
        HuAudFXEmiterUpDate(var_r31->unk_A4, &var_r31->unk_6C);
    }
}

void fn_1_4374(omObjData *object)
{
    Vec sp1C;
    Vec sp10;
    float spC;
    s32 sp8;

    float var_f31;
    float var_f30;
    float var_f29;

    M438MainWork *var_r31;
    s16 var_r30;
    s16 var_r29;
    s16 var_r28;
    s16 var_r27;

    sp8 = 1;
    var_r31 = object->data;
    var_r30 = var_r29 = var_r28 = var_r27 = 0;
    spC = var_f29 = 0.0f;
    if (var_r31->unk_40 != 0) {
        var_r31->unk_40--;
    }
    if (var_r31->unk_40 < 0x258) {
        var_f31 = 0.0016666667f * (0x258 - var_r31->unk_40);
        var_f31 *= 0.6f + (0.4f * (1.0f - var_r31->unk_3C));
        var_r31->unk_48 = 200.0f * var_f31;
    }
    var_r31->unk_44++;
    if (var_r31->unk_44 > 0xB4) {
        var_r31->unk_44 -= 0xB4;
    }
    if (var_r31->unk_64) {
        VECSubtract(&var_r31->unk_58, &var_r31->unk_4C, &sp1C);
        VECSubtract(&sp1C, &var_r31->unk_6C, &sp10);
        sp10.y = 0.0f;
        var_f30 = VECMag(&sp10);
        if (var_f30 > 10.0f) {
            if (var_f30 > 20.0f) {
                var_f30 = 20.0f;
            }
            var_f30 *= 0.05f;
            var_f31 = atan2d(sp10.x, sp10.z);
            var_r31->unk_9C = var_f31;
            var_f29 = var_f30;
            var_f31 = 2.0f * var_r31->unk_44;
            var_r31->unk_4C.x = var_r31->unk_48 * sind(var_f31);
            var_r31->unk_4C.z = var_r31->unk_48 * cosd(var_f31);
        }
    }
    var_r31->unk_A0 += 0.25f * (var_f29 - var_r31->unk_A0);
    if (var_r31->unk_A0 > 0.2f) {
        var_r30 = 80.0 * (var_r31->unk_A0 * sind(var_r31->unk_9C));
        var_r29 = 80.0 * (var_r31->unk_A0 * -cosd(var_r31->unk_9C));
    }
    var_r31->unk_18 = var_r30;
    var_r31->unk_1A = var_r29;
    var_r31->unk_1C = var_r28;
    var_r31->unk_1E = var_r27;
    var_r31->unk_68 = 1;
    var_r31->unk_64 = 0;
}

void fn_1_4724(omObjData *object)
{
    M438MainWork4 *var_r31;

    s32 var_r29 = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M438, 3));
    object->model[0] = var_r29;
    Hu3DModelReflectTypeSet(var_r29, 4);
    object->motion[0] = Hu3DJointMotionFile(var_r29, DATA_MAKE_NUM(DATADIR_M438, 5));
    object->motion[1] = Hu3DJointMotionFile(var_r29, DATA_MAKE_NUM(DATADIR_M438, 4));
    object->motion[2] = Hu3DJointMotionFile(var_r29, DATA_MAKE_NUM(DATADIR_M438, 6));
    object->motion[3] = Hu3DJointMotionFile(var_r29, DATA_MAKE_NUM(DATADIR_M438, 7));
    Hu3DModelScaleSet(var_r29, 1.5f, 1.5f, 1.5f);
    Hu3DMotionSet(var_r29, object->motion[0]);
    Hu3DMotionSpeedSet(var_r29, 2.0f);
    Hu3DModelAttrSet(var_r29, 0x40000001);
    Hu3DModelShadowSet(var_r29);
    var_r31 = fn_1_7BFC(sizeof(M438MainWork4));
    object->data = var_r31;
    memset(var_r31, 0, sizeof(M438MainWork4));
    var_r31->unk_10 = 0.0f;
    var_r31->unk_14 = -450.0f;
    var_r31->unk_18 = -1550.0f;
    var_r31->unk_1C = var_r31->unk_20 = var_r31->unk_24 = 0.0f;
    var_r31->unk_2C = 35.0f;
    var_r31->unk_0C = 0.0f;
    var_r31->unk_00 = 0;
    omSetTra(object, var_r31->unk_10, var_r31->unk_14, var_r31->unk_18);
    omSetRot(object, var_r31->unk_1C, var_r31->unk_20, var_r31->unk_24);
    omSetSca(object, 1.25f, 1.25f, 1.25f);
    object->func = fn_1_4984;
}

// void fn_1_4984(omObjData *object)
// {
//     float sp10;
//     float spC;
//     float sp8;
//     float temp_f0;
//     float temp_f0_2;
//     float var_f31;
//     omObjData *var_r29;
//     s16 var_r27;
//     void *var_r28;
//     void *var_r30;
//     void *var_r31;

//     var_r29 = object;
//     var_r31 = var_r29->data;
//     switch (lbl_1_bss_DBA) {
//         case 1:
//             if (lbl_1_bss_4 == 0) {
//                 lbl_1_bss_4 = fn_1_10258(0x90, 1);
//                 fn_1_11018(lbl_1_bss_4, 0, 0x45000A);
//                 *(lbl_1_bss_DE4.unk_40 + ((lbl_1_bss_4 * 0xBC) + 0x30)) = fn_1_6A3C;
//                 fn_1_11890(lbl_1_bss_4, var_r31->unk_10, -80.0f, var_r31->unk_18);
//                 fn_1_12100(lbl_1_bss_4, 4);
//                 fn_1_124CC(lbl_1_bss_4, 1);
//                 *(lbl_1_bss_DE4.unk_40 + ((lbl_1_bss_4 * 0xBC) + 0x7C)) = 0;
//             }
//             break;
//         case 2:
//             var_r31->unk_14 = var_r31->unk_14 + var_r31->unk_2C;
//             var_r31->unk_2C = var_r31->unk_2C - -2.0416667f;
//             if (var_r31->unk_14 >= -350.0f) {
//                 HuAudFXPlay(0x6FA);
//                 *(lbl_1_bss_DE4.unk_40 + ((lbl_1_bss_4 * 0xBC) + 0x7C)) = 1;
//             }
//             if (var_r31->unk_14 > 0.0f) {
//                 HuAudFXEmiterPlay(0x700, var_r31 + 0x10);
//                 lbl_1_bss_DB2 = 0x78;
//                 lbl_1_bss_DBA += 1;
//                 var_r31->unk_30 = 20.0f;
//             }
//             break;
//         case 3:
//             var_r31->unk_14 = var_r31->unk_14 + var_r31->unk_2C;
//             var_r31->unk_18 = var_r31->unk_18 + var_r31->unk_30;
//             var_r31->unk_2C = var_r31->unk_2C + -2.0416667f;
//             if (var_r31->unk_14 < 0.0f) {
//                 var_r31->unk_30 = var_r31->unk_30 - 0.5f;
//                 if (var_r31->unk_30 < 0.0f) {
//                     var_r31->unk_30 = 0.0f;
//                 }
//                 var_r31->unk_14 = 0.0f;
//                 if (lbl_1_bss_8 == 0) {
//                     HuAudFXPlay(0x6FE);
//                     var_r28 = lbl_1_bss_DD8->data;
//                     var_r28->unk_18A = 0x3C;
//                     var_r28->unk_150 = 25.0f;
//                     var_r28->unk_15C = 0.95f;
//                     var_r28->unk_174 = 90.0f;
//                     var_r28->unk_168 = 90.0f;
//                     for (var_r27 = 0; var_r27 < 4; var_r27++) {
//                         omVibrate(var_r27, 0x36, 0xC, 0);
//                     }
//                     lbl_1_bss_4 = fn_1_10258(0x3C, 1);
//                     fn_1_11018(lbl_1_bss_4, 0, 0x45000F);
//                     *(lbl_1_bss_DE4.unk_40 + ((lbl_1_bss_4 * 0xBC) + 0x30)) = fn_1_5D4C;
//                     fn_1_11890(lbl_1_bss_4, var_r31->unk_10, 50.0f + var_r31->unk_14, var_r31->unk_18);
//                     fn_1_124CC(lbl_1_bss_4, 1);
//                     lbl_1_bss_8++;
//                 }
//             }
//             sp8 = var_r31->unk_10;
//             spC = var_r31->unk_14;
//             sp10 = var_r31->unk_18;
//             temp_f0 = spC + 120.00001f;
//             spC = temp_f0;
//             temp_f0_2 = sp10 - 300.0f;
//             sp10 = temp_f0_2;
//             var_f31 = CZoom;
//             var_r30 = lbl_1_bss_DD8->data;
//             var_r30->unk_00 = 0;
//             var_r30->unk_144 = 1.0f;
//             var_r30->unk_148 = 1.0f;
//             var_r30->unk_1C = var_r30->unk_04;
//             var_r30->unk_20 = var_r30->unk_08;
//             var_r30->unk_24 = var_r30->unk_0C;
//             var_r30->unk_34 = sp8;
//             var_r30->unk_38 = temp_f0;
//             var_r30->unk_3C = temp_f0_2;
//             var_r30->unk_28 = var_r30->unk_10;
//             var_r30->unk_2C = var_r30->unk_14;
//             var_r30->unk_30 = var_r30->unk_18;
//             var_r30->unk_40 = CRot.x;
//             var_r30->unk_44 = CRot.y;
//             var_r30->unk_48 = CRot.z;
//             var_r30->unk_134 = var_r30->unk_130;
//             var_r30->unk_138 = var_f31;
//             break;
//         case 5:
//             Hu3DModelAttrReset(*var_r29->model, 0x40000001);
//             Hu3DModelAttrSet(*var_r29->model, 0x40000004);
//             var_r29->func = fn_1_4F50;
//             var_r29->work[0] = 0xA;
//             var_r29->work[1] = 0;
//             break;
//     }
//     omSetTra(var_r29, var_r31->unk_10, var_r31->unk_14, var_r31->unk_18);
//     omSetRot(var_r29, var_r31->unk_1C, var_r31->unk_20, var_r31->unk_24);
// }

// void fn_1_4F50(omObjData *object)
// {
//     Vec sp18;
//     float var_f24;
//     float var_f25;
//     float var_f26;
//     float var_f27;
//     float var_f28;
//     float var_f29;
//     float var_f30;
//     float var_f31;
//     omObjData *var_r30;
//     s16 temp_r0;
//     s16 temp_r3_3;
//     s16 temp_r6;
//     s16 var_r28;
//     s32 temp_r3_2;
//     s32 var_r26;
//     u8 temp_r3;
//     void *var_r27;
//     void *var_r29;
//     void *var_r31;

//     var_r30 = object;
//     var_r31 = var_r30->data;
//     switch (lbl_1_bss_DBA) {
//         case 7:
//             temp_r3 = var_r31->unk_00;
//             switch (temp_r3) {
//                 case 0:
//                     var_r31->unk_34 = var_r31->unk_10;
//                     var_r31->unk_38 = var_r31->unk_14;
//                     var_r31->unk_3C = var_r31->unk_18;
//                     Hu3DMotionShiftSet(*var_r30->model, var_r30->motion->unk_06, 0.0f, 8.0f, 0);
//                     var_r31->unk_00 = var_r31->unk_00 + 1;

//                 case 1:
//                     var_r31->unk_34 = var_r31->unk_10;
//                     var_r31->unk_38 = var_r31->unk_14;
//                     var_r31->unk_3C = var_r31->unk_18;
//                     var_r28 = 0;
//                     var_r26 = 0;
//                 loop_21:
//                     if (var_r28 < 4) {
//                         var_r29 = lbl_1_bss_DC4[var_r28]->data;
//                         if ((var_r29->unk_07 != 0) && ((var_r29->unk_07 & 2) == 0)) {
//                             VECSubtract(var_r29 + 0x6C, var_r31 + 0x10, &sp18);
//                             temp_r3_2 = var_r26;
//                             var_r26++;
//                             (&sp8[0])[temp_r3_2] = atan2d(sp18, sp18.z);
//                         }
//                         var_r28++;
//                         goto loop_21;
//                     }
//                     var_r31->unk_20 = var_r31->unk_20 + (18.0f + var_r30->work[1]);
//                     if (var_r31->unk_20 > 180.0f) {
//                         var_r31->unk_20 = var_r31->unk_20 - 360.0f;
//                     }
//                     if (var_r31->unk_20 <= -180.0f) {
//                         var_r31->unk_20 = var_r31->unk_20 + 360.0f;
//                     }
//                     var_r28 = 0;
//                 loop_35:
//                     if (var_r28 >= var_r26) { }
//                     else {
//                         var_f31 = fn_1_E5A4((&sp8[0])[var_r28], var_r30->rot.y);
//                         if (var_f31 < 0.0f) {
//                             var_f27 = -var_f31;
//                         }
//                         else {
//                             var_f27 = var_f31;
//                         }
//                         if (!(var_f27 > (20.0f + var_r30->work[1]))
//                             && ((var_r30->work[0] -= 1, ((var_r30->work[0] == 0) != 0)) || ((fn_1_7DB4() & 0xF) == 0))) {
//                             var_r31->unk_08 = (&sp8[0])[var_r28];
//                             var_r31->unk_20 = (&sp8[0])[var_r28];
//                             var_r31->unk_2C = 16.333334f;
//                             var_r31->unk_0C = 6.0 + (0.5 * var_r30->work[1]);
//                             var_r31->unk_34 = var_r31->unk_10;
//                             var_r31->unk_38 = var_r31->unk_14;
//                             var_r31->unk_3C = var_r31->unk_18;
//                             var_r31->unk_40 = 20.0f;
//                             var_r31->unk_44 = 0.0f;
//                             var_r31->unk_02 = 0x1E;
//                             Hu3DMotionShiftSet(*var_r30->model, var_r30->motion->unk_00, 0.0f, 8.0f, 0x40000002);
//                             var_r31->unk_00 = var_r31->unk_00 + 1;
//                         }
//                         else {
//                             var_r28++;
//                             goto loop_35;
//                         }
//                     }
//                     break;
//                 case 2:
//                     var_r31->unk_44 = var_r31->unk_44 + 10.0f;
//                     if (var_r31->unk_44 > 90.0f) {
//                         var_r31->unk_44 = 0.0f;
//                     }
//                     var_f29 = cosd(var_r31->unk_44);
//                     var_r31->unk_1C = var_r31->unk_40 * var_f29;
//                     var_r31->unk_10 = var_r31->unk_34 + ((50.0f * var_f29) * sind(var_r31->unk_20));
//                     var_r31->unk_18 = var_r31->unk_3C + ((50.0f * var_f29) * cosd(var_r31->unk_20));
//                     temp_r0 = var_r31->unk_02 - 1;
//                     var_r31->unk_02 = temp_r0;
//                     if (temp_r0 == 0) {
//                         HuAudFXEmiterPlay(0x700, var_r31 + 0x10);
//                         Hu3DModelAttrReset(*var_r30->model, 0x40000002);
//                         Hu3DModelAttrSet(*var_r30->model, 0x40000001);
//                         var_r31->unk_1C = 0.0f;
//                         var_r31->unk_00 = var_r31->unk_00 + 1;
//                     }
//                     break;
//                 case 3:
//                     var_r31->unk_0C = var_r31->unk_0C + 0.5;
//                     var_r31->unk_2C = var_r31->unk_2C + -3.0625f;
//                     var_f28 = var_r31->unk_0C + (0.8f * var_r31->unk_2C);
//                     var_r31->unk_28 = var_f28 * sind(var_r31->unk_08);
//                     var_r31->unk_30 = var_f28 * cosd(var_r31->unk_08);
//                     var_r31->unk_10 = var_r31->unk_10 + var_r31->unk_28;
//                     var_r31->unk_14 = var_r31->unk_14 + var_r31->unk_2C;
//                     var_r31->unk_18 = var_r31->unk_18 + var_r31->unk_30;
//                     var_r31->unk_34 = var_r31->unk_10;
//                     var_r31->unk_38 = var_r31->unk_14;
//                     var_r31->unk_3C = var_r31->unk_18;
//                     if (var_r31->unk_14 < 0.0f) {
//                         var_r31->unk_14 = 0.0f;
//                         var_r31->unk_2C = 16.333334f;
//                     }
//                     sp18 = var_r31->unk_10;
//                     sp18.y = var_r31->unk_14;
//                     sp18.z = var_r31->unk_18;
//                     sp18.y = 0.0f;
//                     var_f30 = VECMag(&sp18);
//                     if (!(var_f30 <= 700.0f)) {
//                         var_r31->unk_02 = 1;
//                         if (fn_1_DA64(atan2d(sp18, sp18.z)) != 0) {
//                             var_r31->unk_02 = 0x78;
//                             for (var_r28 = 0; var_r28 < 4; var_r28++) {
//                                 var_r29 = lbl_1_bss_DC4[var_r28]->data;
//                                 if ((var_r29->unk_07 != 0) && ((var_r29->unk_07 & 2) == 0)) {
//                                     omVibrate(var_r28, 0xC, 4, 2);
//                                 }
//                             }
//                             var_r27 = lbl_1_bss_DD8->data;
//                             var_r27->unk_188 = 0x3C;
//                             var_r27->unk_14C = 25.0f;
//                             var_r27->unk_158 = 0.95f;
//                             var_r27->unk_170 = 90.0f;
//                             var_r27->unk_164 = 90.0f;
//                             HuAudFXEmiterPlay(0x6FC, var_r31 + 0x10);
//                             HuAudFXPlay(0x6FE);
//                         }
//                         fn_1_9634(&sp18);
//                         var_r31->unk_10 = 700.0f * sp18;
//                         var_r31->unk_18 = 700.0f * sp18.z;
//                         var_r31->unk_40 = var_r31->unk_1C;
//                         var_r31->unk_44 = var_r31->unk_20;
//                         var_r31->unk_48 = var_r31->unk_24;
//                         var_r31->unk_00 = var_r31->unk_00 + 1;
//                     }
//                     break;
//                 case 4:
//                     var_r31->unk_2C = var_r31->unk_2C + -3.0625f;
//                     var_r31->unk_14 = var_r31->unk_14 + var_r31->unk_2C;
//                     if (!(var_r31->unk_14 > 0.0f)) {
//                         var_r31->unk_14 = 0.0f;
//                         var_r31->unk_34 = var_r31->unk_10;
//                         var_r31->unk_38 = var_r31->unk_14;
//                         var_r31->unk_3C = var_r31->unk_18;
//                         Hu3DModelAttrReset(*var_r30->model, 0x40000001);
//                         Hu3DModelAttrSet(*var_r30->model, 0x40000004);
//                         var_r31->unk_44 = var_r31->unk_44 + 8.0f;
//                         var_r31->unk_40 = 10.0 * sind(var_r31->unk_44);
//                         var_r31->unk_48 = 10.0 * cosd(var_r31->unk_44);
//                         mtxRot(&sp24[0], 0.0f, 360.0f - var_r31->unk_08, var_r31->unk_48);
//                         mtxRotCat(&sp24[0], var_r31->unk_40, 0.0f, 0.0f);
//                         fn_1_8164(&sp24[0], var_r31 + 0x1C);
//                         temp_r3_3 = var_r31->unk_02 - 1;
//                         var_r31->unk_02 = temp_r3_3;
//                         if (temp_r3_3 == 0) {
//                             var_r31->unk_24 = 0.0f;
//                             var_r31->unk_1C = 0.0f;
//                             var_r31->unk_20 = var_r31->unk_08;
//                             var_r30->work[0] = 0.5f * (lbl_1_bss_DB4 / 60.0f);
//                             var_r30->work[1] += 1;
//                             var_r31->unk_00 = 0;
//                         }
//                     }
//                     break;
//             }
//             break;
//         case 8:
//             var_r31->unk_24 = 0.0f;
//             var_r31->unk_1C = 0.0f;
//             Hu3DModelAttrReset(*var_r30->model, 0x40000001);
//             Hu3DModelAttrSet(*var_r30->model, 0x40000004);
//             break;
//         case 9:
//             var_r31->unk_20 = fn_1_7EDC(var_r31->unk_20, 0.0f, 0.9f);
//             break;
//         case 10:
//             if (var_r31->unk_04 == 0) {
//                 Hu3DModelAttrReset(*var_r30->model, 0x40000006);
//                 Hu3DMotionSet(*var_r30->model, var_r30->motion->unk_02);
//                 Hu3DMotionSpeedSet(*var_r30->model, 1.0f);
//                 Hu3DModelAttrSet(*var_r30->model, 0x40000001);
//                 var_r31->unk_04 = 1;
//             }
//             break;
//     }
//     if (lbl_1_bss_DBA == 7) {
//         var_r28 = 0;
//         var_r26 = 0;
//     loop_72:
//         if (var_r28 < 4) {
//             var_r29 = lbl_1_bss_DC4[var_r28]->data;
//             VECSubtract(var_r29 + 0x6C, var_r31 + 0x10, &sp18);
//             var_f30 = VECMag(&sp18);
//             if (!(var_f30 >= 200.0f) && (var_r29->unk_20 != 7)) {
//                 omVibrate(var_r29->unk_00, 0xC, 4, 2);
//                 var_r29->unk_07 = var_r29->unk_07 | 2;
//                 var_r29->unk_0D = 0;
//                 var_r29->unk_20 = 7;
//                 var_r29->unk_28 = atan2d(sp18, sp18.z);
//                 if (var_r29->unk_28 >= 360.0f) {
//                     var_r29->unk_28 = var_r29->unk_28 - 360.0f;
//                 }
//                 var_f26 = fn_1_E5A4(var_r29->unk_28, var_r29->unk_7C);
//                 var_f25 = fabs(var_f26);
//                 var_f24 = var_f25;
//                 if (var_f24 > 90.0) {
//                     var_r29->unk_7C = 180.0f + var_r29->unk_28;
//                     var_r29->unk_14 = 0;
//                 }
//                 else {
//                     var_r29->unk_7C = var_r29->unk_28;
//                     var_r29->unk_14 = 1;
//                 }
//                 var_r29->unk_24 = 10.0f;
//                 var_r29->unk_88 = 53.083336f;
//                 if (lbl_1_bss_DAA[var_r28] == 0) {
//                     temp_r6 = lbl_1_bss_DA8;
//                     lbl_1_bss_DA8 = temp_r6 - 1;
//                     lbl_1_bss_DAA[var_r28] = temp_r6;
//                 }
//             }
//             var_r28++;
//             goto loop_72;
//         }
//     }
//     omSetTra(var_r30, var_r31->unk_10, var_r31->unk_14, var_r31->unk_18);
//     omSetRot(var_r30, var_r31->unk_1C, var_r31->unk_20, var_r31->unk_24);
// }

// void fn_1_5D4C(void *arg0)
// {
//     s16 sp8;
//     float var_f26;
//     float var_f27;
//     float var_f28;
//     float var_f29;
//     float var_f30;
//     float var_f31;
//     s32 var_r29;
//     u8 temp_r0;
//     void *var_r30;
//     void *var_r31;

//     var_r30 = arg0;
//     sp8 = 0;
//     temp_r0 = var_r30->unk_60;
//     switch (temp_r0) {
//         case 0:
//             var_f27 = 360.0f / var_r30->unk_02;
//             for (var_r31 = var_r30->unk_3C; var_r29 = 0; var_r31 < var_r30->unk_02; var_r29++; var_r31 += 0x98) {
//                 var_f26 = 0.8f + (0.1f * (2.0f * (0.000030517578f * (fn_1_7DB4() - 0x8000))));
//                 var_r31->unk_6C = sind((var_f27 * var_r29)) * var_f26;
//                 var_r31->unk_70 = 0.0f;
//                 var_f26 = 0.8f + (0.1f * (2.0f * (0.000030517578f * (fn_1_7DB4() - 0x8000))));
//                 var_r31->unk_74 = cosd((var_f27 * var_r29)) * var_f26;
//                 var_r31->unk_00 = 40.0f * var_r31->unk_6C;
//                 var_r31->unk_04 = 6.0f;
//                 var_r31->unk_08 = 40.0f * var_r31->unk_74;
//                 var_f29 = 0.01f * (100.0f * (0.000015258789f * fn_1_7DB4()));
//                 var_r31->unk_54 = 80.0f + (60.0f * var_f29);
//                 var_r31->unk_55 = 64.0f + (60.0f * var_f29);
//                 var_r31->unk_56 = 56.0f + (60.0f * var_f29);
//             }
//             var_r30->unk_7C = 0x30;
//             var_r30->unk_60 = var_r30->unk_60 + 1;

//         case 1:
//             var_r30->unk_7C = var_r30->unk_7C - 1;
//             var_f31 = (48.0f - var_r30->unk_7C) / 48.0f;
//             var_f28 = var_r30->unk_7C / 48.0f;
//             for (var_r31 = var_r30->unk_3C; var_r29 = 0; var_r31 < var_r30->unk_02; var_r29++; var_r31 += 0x98) {
//                 var_r31->unk_00 = var_r31->unk_00 + (12.5f * var_f28 * var_r31->unk_6C);
//                 var_r31->unk_08 = var_r31->unk_08 + (12.5f * var_f28 * var_r31->unk_74);
//                 var_f30 = 2.4f + (6.0f * var_f31);
//                 var_r31->unk_18 = var_f30;
//                 var_r31->unk_1C = var_f30;
//                 var_r31->unk_20 = var_f30;
//                 var_r31->unk_57 = 96.0f * (1.0f - (var_f31 * var_f31));
//             }
//             if (var_r30->unk_7C == 0) {
//                 var_r30->unk_60 = var_r30->unk_60 + 1;
//                 return;
//             }
//             return;
//         case 2:
//             fn_1_107BC(var_r30->unk_00);
//             break;
//     }
// }

void fn_1_62BC(void *arg0)
{
    // s16 sp8;

    // void *var_r31;
    // void *var_r30;

    // var_r30 = arg0;
    // sp8 = 0;
    // switch (var_r30->unk_60) {
    //     case 0:
    //         var_r31 = var_r30->unk_3C;
    //         var_r31->unk_70 = 5.0f;
    //         var_r31->unk_6C *= -2.0f;
    //         var_r31->unk_74 *= -2.0f;
    //         var_r30->unk_60++;

    //     case 1:
    //         var_r31 = var_r30->unk_3C;
    //         var_r31->unk_00 += var_r31->unk_6C;
    //         var_r31->unk_04 += var_r31->unk_70;
    //         var_r31->unk_08 += var_r31->unk_74;
    //         return;
    //     case 2:
    //         fn_1_107BC(var_r30->unk_00);
    //         return;
    // }
}

// void fn_1_63B0(void *arg0)
// {
//     float sp10;
//     float spC;
//     float sp8;
//     float temp_f0;
//     float temp_f0_2;
//     float temp_f0_3;
//     float var_f28;
//     float var_f29;
//     float var_f30;
//     float var_f31;
//     double var_f27;
//     s16 temp_r0_2;
//     s32 var_r29;
//     u8 temp_r0;
//     void *var_r30;
//     void *var_r31;

//     var_r30 = arg0;
//     for (var_r31 = var_r30->unk_3C; var_r29 = 0; var_r31 < var_r30->unk_02; var_r29++; var_r31 += 0x98) {
//         temp_r0 = var_r31->unk_5C;
//         switch (temp_r0) {
//             case 0:
//                 if ((atan2d(var_r30->unk_80, var_r30->unk_84)) < 0.0) {
//                     var_f27 = -(atan2d(var_r30->unk_80, var_r30->unk_84));
//                 }
//                 else {
//                     var_f27 = atan2d(var_r30->unk_80, var_r30->unk_84);
//                 }
//                 var_f29 = var_f27;
//                 if (var_f29 > 90.0f) {
//                     var_f29 = 180.0f - var_f29;
//                 }
//                 var_f28 = 40.0f * (0.1f + ((0.9f * var_f29) / 90.0f));
//                 var_f31 = (0.5f * var_f28) + ((var_r30->unk_88 - var_f28) * (0.000015258789f * fn_1_7DB4()));
//                 temp_f0 = var_f31 * var_r30->unk_80;
//                 sp8 = temp_f0;
//                 temp_f0_2 = var_f31 * var_r30->unk_84;
//                 sp10 = temp_f0_2;
//                 var_r31->unk_00 = temp_f0;
//                 var_r31->unk_04 = 0.0f;
//                 var_r31->unk_08 = temp_f0_2;
//                 var_f31 = 0.0f;
//                 spC = 0.0f;
//             loop_14:
//                 if (var_f31 < (var_r30->unk_8C - 40.0f)) {
//                     temp_f0_3 = spC + 0.8f;
//                     spC = temp_f0_3;
//                     var_f31 += temp_f0_3;
//                     goto loop_14;
//                 }
//                 var_r31->unk_6C = 0.0f;
//                 var_r31->unk_70 = spC + (1.5f * (0.000015258789f * fn_1_7DB4()));
//                 var_r31->unk_74 = 0.0f;
//                 if ((fn_1_7DB4() & 7) != 0) {
//                     var_r31->unk_33 = 1;
//                     var_r31->unk_54 = 0x40;
//                     var_r31->unk_55 = 0x10;
//                     var_r31->unk_56 = 4;
//                     var_r31->unk_57 = 0xFF;
//                     var_f30 = 3.75f + (1.75f * (0.000015258789f * fn_1_7DB4()));
//                     var_r31->unk_60 = var_f30 * (0.1f + ((0.9f * var_f29) / 90.0f));
//                     var_r31->unk_68 = var_f30;
//                     var_r31->unk_64 = var_f30;
//                 }
//                 else {
//                     var_r31->unk_33 = 0;
//                     var_r31->unk_54 = 0;
//                     var_r31->unk_55 = 0;
//                     var_r31->unk_56 = 0;
//                     var_r31->unk_57 = 0xFF;
//                     var_f30 = 0.25f + (0.25f * (0.000015258789f * fn_1_7DB4()));
//                     var_r31->unk_64 = 1.5f * var_f30;
//                     var_r31->unk_68 = var_f30;
//                     var_r31->unk_60 = var_f30;
//                 }
//                 var_r31->unk_58->unk_24 = 0;
//                 var_r31->unk_78 = (60.0f * (0.000015258789f * fn_1_7DB4())) + 1;
//                 var_r31->unk_5C = var_r31->unk_5C + 1;

//             case 1:
//                 temp_r0_2 = var_r31->unk_78 - 1;
//                 var_r31->unk_78 = temp_r0_2;
//                 if (temp_r0_2 == 0) {
//                     var_r31->unk_58->unk_24 = 0x11;
//                     var_r31->unk_58->unk_28 = 0.5f;
//                     var_r31->unk_58->unk_2C = 0.0f;
//                     var_r31->unk_58->unk_00 = 0;
//                     var_r31->unk_5C = var_r31->unk_5C + 1;
//                 }
//                 break;
//             case 2:
//                 var_r31->unk_00 = var_r31->unk_00 + var_r31->unk_6C;
//                 var_r31->unk_04 = var_r31->unk_04 + var_r31->unk_70;
//                 var_r31->unk_08 = var_r31->unk_08 + var_r31->unk_74;
//                 if (var_r31->unk_04 < 0.0f) {
//                     var_r31->unk_04 = 0.0f;
//                 }
//                 var_r31->unk_60 = var_r31->unk_60 * 0.95f;
//                 var_r31->unk_64 = var_r31->unk_64 * 0.95f;
//                 var_r31->unk_68 = var_r31->unk_68 * 0.95f;
//                 var_r31->unk_70 = var_r31->unk_70 - 0.8f;
//                 if ((var_r31->unk_58->unk_24 & 8) != 0) {
//                     var_r31->unk_5C = 0;
//                 }
//                 break;
//         }
//         var_r31->unk_18 = var_r31->unk_60 * var_r30->unk_90;
//         var_r31->unk_1C = var_r31->unk_64 * var_r30->unk_90;
//         var_r31->unk_20 = var_r31->unk_68 * var_r30->unk_90;
//     }
// }

// void fn_1_6A3C(void *arg0)
// {
//     float sp10;
//     float spC;
//     float sp8;
//     float temp_f0;
//     float temp_f0_2;
//     float temp_f0_3;
//     float temp_f0_4;
//     float var_f29;
//     float var_f30;
//     float var_f31;
//     s16 temp_r0_2;
//     s16 var_r29;
//     s32 var_r27;
//     s32 var_r28;
//     u8 temp_r0;
//     void *var_r30;
//     void *var_r31;

//     var_r30 = arg0;
//     var_r31 = var_r30->unk_3C;
//     var_r28 = 0;
//     var_r27 = 0;
// loop_35:
//     if (var_r27 < var_r30->unk_02) {
//         if ((var_r30->unk_7C != 0) && (var_r31->unk_7A == 0)) {
//             var_r31->unk_5C = 0;
//         }
//         temp_r0 = var_r31->unk_5C;
//         switch (temp_r0) {
//             case 0:
//                 if (var_r30->unk_7C != 0) {
//                     var_f30 = (180.0f * (0.000015258789f * fn_1_7DB4())) - 90.0f;
//                     var_f29 = 125.0f;
//                     temp_f0 = sind(var_f30);
//                     sp8 = temp_f0;
//                     temp_f0_2 = cosd(var_f30);
//                     sp10 = temp_f0_2;
//                     var_r31->unk_00 = 125.0f * temp_f0;
//                     var_r31->unk_04 = 0.0f;
//                     var_r31->unk_08 = 125.0f * temp_f0_2;
//                     spC = 25.0f;
//                     var_r31->unk_6C = 100.0f * (0.1f * temp_f0);
//                     var_r31->unk_70 = 25.0f + (2.5f * (0.000015258789f * fn_1_7DB4()));
//                     var_r31->unk_74 = 100.0f * (0.1f * temp_f0_2);
//                     var_r31->unk_78 = (24.0f * (0.000015258789f * fn_1_7DB4())) + 1;
//                     var_r31->unk_7A = 1;
//                 }
//                 else {
//                     var_f30 = (180.0f * (0.000015258789f * fn_1_7DB4())) - 90.0f;
//                     var_f29 = 125.0f * (0.000015258789f * fn_1_7DB4());
//                     temp_f0_3 = sind(var_f30);
//                     sp8 = temp_f0_3;
//                     temp_f0_4 = cosd(var_f30);
//                     sp10 = temp_f0_4;
//                     var_r31->unk_00 = var_f29 * temp_f0_3;
//                     var_r31->unk_04 = 0.0f;
//                     var_r31->unk_08 = var_f29 * temp_f0_4;
//                     spC = 5.0f;
//                     var_r31->unk_6C = 100.0 * (0.015 * temp_f0_3);
//                     var_r31->unk_70 = 5.0f + (0.000015258789f * fn_1_7DB4());
//                     var_r31->unk_74 = 100.0f * (0.015f * temp_f0_4);
//                     var_r31->unk_78 = (60.0f * (0.000015258789f * fn_1_7DB4())) + 1;
//                     var_r31->unk_7A = 0;
//                 }
//                 var_r31->unk_38 = var_r31->unk_38 & 0xFFFFFFFB;
//                 if ((fn_1_7DB4() & 0xF) != 0) {
//                     var_r31->unk_33 = 1;
//                     var_r31->unk_54 = 0x40;
//                     var_r31->unk_55 = 0x10;
//                     var_r31->unk_56 = 4;
//                     var_r31->unk_57 = 0xFF;
//                     var_f31 = 1.8f + (0.000015258789f * fn_1_7DB4());
//                     var_r31->unk_18 = var_f31;
//                     var_r31->unk_1C = var_f31;
//                     var_r31->unk_20 = var_f31;
//                     goto block_19;
//                 }
//                 if (var_r30->unk_7C != 0) {
//                     var_r31->unk_33 = 0;
//                     var_r31->unk_54 = 0;
//                     var_r31->unk_55 = 0;
//                     var_r31->unk_56 = 0;
//                     var_r31->unk_57 = 0xFF;
//                     var_f31 = 0.25f + (0.25f * (0.000015258789f * fn_1_7DB4()));
//                     var_r31->unk_18 = var_f31;
//                     var_r31->unk_1C = 1.5f * var_f31;
//                     var_r31->unk_20 = var_f31;
//                 block_19:
//                     var_r31->unk_58->unk_24 = 0;
//                     var_r31->unk_5C = var_r31->unk_5C + 1;
//                 }
//                 else {
//                     var_r29 = fn_1_10258(8, 1);
//                     fn_1_11018(var_r29, 0, 0x45000A);
//                     *(lbl_1_bss_DE4.unk_40 + ((var_r29 * 0xBC) + 0x30)) = fn_1_7300;
//                     fn_1_11890(var_r29, var_r30->unk_0C + var_r31->unk_00, var_r30->unk_10 + var_r31->unk_04, var_r30->unk_14 + var_r31->unk_08);
//                     fn_1_12100(var_r29, 4);
//                     fn_1_124CC(var_r29, 1);
//                     var_r31->unk_38 = var_r31->unk_38 | 4;
//                 }
//                 break;
//             case 1:
//                 if (var_r31->unk_7A != 0) {
//                     var_r31->unk_70 = var_r31->unk_70 - 0.5f;
//                 }
//                 temp_r0_2 = var_r31->unk_78 - 1;
//                 var_r31->unk_78 = temp_r0_2;
//                 if (temp_r0_2 == 0) {
//                     var_r31->unk_58->unk_24 = 0x11;
//                     if (var_r31->unk_7A != 0) {
//                         var_r31->unk_58->unk_28 = 0.5f;
//                     }
//                     else {
//                         var_r31->unk_58->unk_28 = 0.5f;
//                     }
//                     var_r31->unk_58->unk_2C = 0.0f;
//                     var_r31->unk_58->unk_00 = 0;
//                     var_r31->unk_5C = var_r31->unk_5C + 1;
//                 }
//                 break;
//             case 2:
//                 var_r31->unk_00 = var_r31->unk_00 + var_r31->unk_6C;
//                 var_r31->unk_04 = var_r31->unk_04 + var_r31->unk_70;
//                 var_r31->unk_08 = var_r31->unk_08 + var_r31->unk_74;
//                 if (var_r31->unk_04 < 0.0f) {
//                     var_r31->unk_04 = 0.0f;
//                 }
//                 var_r31->unk_18 = var_r31->unk_18 * 0.95f;
//                 var_r31->unk_1C = var_r31->unk_1C * 0.95f;
//                 var_r31->unk_20 = var_r31->unk_20 * 0.95f;
//                 var_r31->unk_70 = var_r31->unk_70 - 1.5f;
//                 if ((var_r31->unk_58->unk_24 & 8) != 0) {
//                     if (var_r31->unk_7A != 0) {
//                         var_r31->unk_5C = 3;
//                     }
//                     else {
//                         var_r31->unk_5C = 0;
//                     }
//                 }
//                 break;
//             case 3:
//                 var_r28++;
//                 break;
//         }
//         var_r27++;
//         var_r31 += 0x98;
//         goto loop_35;
//     }
//     if (var_r28 >= var_r30->unk_02) {
//         fn_1_107BC(var_r30->unk_00);
//     }
// }

// void fn_1_7300(void *arg0)
// {
//     float sp10;
//     float spC;
//     float sp8;
//     float temp_f0;
//     float temp_f0_2;
//     float temp_f0_3;
//     float var_f29;
//     float var_f30;
//     float var_f31;
//     s16 temp_r0_2;
//     s32 var_r28;
//     s32 var_r29;
//     u8 temp_r0;
//     u8 temp_r0_3;
//     void *var_r30;
//     void *var_r31;

//     var_r30 = arg0;
//     var_r31 = var_r30->unk_3C;
//     temp_r0 = var_r30->unk_60;
//     switch (temp_r0) {
//         case 0:
//             var_f31 = 0.01f;
//             var_r30->unk_2C = 0.01f;
//             var_r30->unk_28 = 0.01f;
//             var_r30->unk_24 = 0.01f;
//             var_r30->unk_7C = Hu3DModelCreateFile(0x45000B);
//             var_r30->unk_7E = (30.0f * (0.000015258789f * fn_1_7DB4())) + 0x1E;
//             var_r29 = 0;
//         loop_6:
//             if (var_r29 < var_r30->unk_02) {
//                 var_r31->unk_38 = var_r31->unk_38 | 4;
//                 var_r29++;
//                 var_r31 += 0x98;
//                 goto loop_6;
//             }
//             var_r30->unk_60 = var_r30->unk_60 + 1;

//         case 1:
//             var_r30->unk_2C = var_r30->unk_2C + 0.008f;
//             temp_f0 = var_r30->unk_2C;
//             var_r30->unk_28 = temp_f0;
//             var_r30->unk_24 = temp_f0;
//             Hu3DModelPosSetV(var_r30->unk_7C, var_r30 + 0xC);
//             Hu3DModelScaleSetV(var_r30->unk_7C, var_r30 + 0x24);
//             temp_r0_2 = var_r30->unk_7E - 1;
//             var_r30->unk_7E = temp_r0_2;
//             if (temp_r0_2 == 0) {
//                 Hu3DModelKill(var_r30->unk_7C);
//                 var_r30->unk_7C = 0;
//                 var_r29 = 0;
//             loop_11:
//                 if (var_r29 < var_r30->unk_02) {
//                     var_r31->unk_5C = 1;
//                     var_r29++;
//                     var_r31 += 0x98;
//                     goto loop_11;
//                 }
//                 var_r30->unk_80 = var_r30->unk_24;
//                 var_r30->unk_2C = 1.0f;
//                 var_r30->unk_28 = 1.0f;
//                 var_r30->unk_24 = 1.0f;
//                 var_r30->unk_60 = var_r30->unk_60 + 1;
//             }
//             break;
//     }
//     var_r28 = 0;
//     for (var_r31 = var_r30->unk_3C; var_r29 = 0; var_r31 < var_r30->unk_02; var_r29++; var_r31 += 0x98) {
//         temp_r0_3 = var_r31->unk_5C;
//         switch (temp_r0_3) {
//             case 1:
//                 var_r31->unk_38 = var_r31->unk_38 & 0xFFFFFFFB;
//                 var_r31->unk_33 = 1;
//                 var_r31->unk_54 = 0x60;
//                 var_r31->unk_55 = 0x20;
//                 var_r31->unk_56 = 0x10;
//                 var_r31->unk_57 = 0xFF;
//                 var_f31 = 0.4f + (0.15f * (0.000015258789f * fn_1_7DB4()));
//                 var_r31->unk_18 = var_f31;
//                 var_r31->unk_1C = var_f31;
//                 var_r31->unk_20 = var_f31;
//                 var_f29 = 360.0f * (0.000015258789f * fn_1_7DB4());
//                 var_f30 = 50.0f * var_r30->unk_80;
//                 temp_f0_2 = sind(var_f29);
//                 sp8 = temp_f0_2;
//                 temp_f0_3 = cosd(var_f29);
//                 sp10 = temp_f0_3;
//                 var_r31->unk_00 = var_f30 * temp_f0_2;
//                 var_r31->unk_04 = var_f30;
//                 var_r31->unk_08 = var_f30 * temp_f0_3;
//                 spC = 6.0f;
//                 var_r31->unk_6C = 100.0f * (0.015f * temp_f0_2);
//                 var_r31->unk_70 = 6.0f + (1.5f * (0.000015258789f * fn_1_7DB4()));
//                 var_r31->unk_74 = 100.0f * (0.015f * temp_f0_3);
//                 var_r31->unk_58->unk_24 = 0x11;
//                 var_r31->unk_58->unk_28 = 0.75f;
//                 var_r31->unk_5C = var_r31->unk_5C + 1;
//                 break;
//             case 2:
//                 var_r31->unk_00 = var_r31->unk_00 + var_r31->unk_6C;
//                 var_r31->unk_04 = var_r31->unk_04 + var_r31->unk_70;
//                 var_r31->unk_08 = var_r31->unk_08 + var_r31->unk_74;
//                 var_r31->unk_70 = var_r31->unk_70 - 0.75f;
//                 if ((var_r31->unk_58->unk_24 & 8) != 0) {
//                     var_r31->unk_5C = var_r31->unk_5C + 1;
//                 }
//                 break;
//             case 3:
//                 var_r28++;
//                 break;
//         }
//     }
//     if (var_r28 >= var_r30->unk_02) {
//         fn_1_107BC(var_r30->unk_00);
//     }
//     if (lbl_1_bss_DBA == 2) {
//         if (var_r30->unk_7C != 0) {
//             Hu3DModelKill(var_r30->unk_7C);
//         }
//         fn_1_107BC(var_r30->unk_00);
//     }
// }

void fn_1_7858(omObjData *object)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    M438MainWork *var_r31;
    M438MainWork *var_r30;
    s32 var_r29;

    var_r31 = object->data;
    if (var_r31->unk_07 == 0 || (var_r31->unk_07 & 2) != 0) {
        return;
    }
    VECSubtract(&var_r31->unk_6C, &var_r31->unk_90, &sp2C);
    var_f29 = VECMag(&sp2C);
    if (var_f29 == 0.0f) {
        return;
    }
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if (var_r29 == var_r31->unk_00) {
            continue;
        }
        var_r30 = lbl_1_bss_DC4[var_r29]->data;
        if (var_r30->unk_07 == 0 || (var_r30->unk_07 & 2) != 0) {
            continue;
        }
        sp14.x = var_r31->unk_6C.x;
        sp14.y = var_r31->unk_6C.y;
        sp14.z = var_r31->unk_6C.z;
        sp14.y = 0.0f;

        sp8.x = var_r30->unk_6C.x;
        sp8.y = var_r30->unk_6C.y;
        sp8.z = var_r30->unk_6C.z;
        sp8.y = 0.0f;
        VECSubtract(&sp14, &sp8, &sp2C);
        var_f31 = VECMag(&sp2C);
        if (var_f31 >= 119.40001f) {
            continue;
        }
        VECSubtract(&var_r30->unk_6C, &var_r30->unk_90, &sp2C);
        var_f28 = VECMag(&sp2C);
        VECSubtract(&sp14, &sp8, &sp20);
        VECNormalize(&sp20, &sp20);
        var_f31 = 120.00001f - var_f31;
        var_f30 = ((0.6f * var_f28) + (0.4f * var_f29)) / (var_f29 + var_f28);
        var_r31->unk_6C.x = var_r31->unk_6C.x + (var_f30 * (var_f31 * sp20.x));
        var_r31->unk_6C.y = var_r31->unk_6C.y + (var_f30 * (var_f31 * sp20.y));
        var_r31->unk_6C.z = var_r31->unk_6C.z + (var_f30 * (var_f31 * sp20.z));

        var_f30 = ((0.6f * var_f29) + (0.4f * var_f29)) / (var_f29 + var_f28);
        var_r30->unk_6C.x = var_r30->unk_6C.x + (var_f30 * (var_f31 * -sp20.x));
        var_r30->unk_6C.y = var_r30->unk_6C.y + (var_f30 * (var_f31 * -sp20.y));
        var_r30->unk_6C.z = var_r30->unk_6C.z + (var_f30 * (var_f31 * -sp20.z));
        fn_1_7858(lbl_1_bss_DC4[var_r29]);
    }
}

void fn_1_7B58(omObjData *object)
{
    s32 var_r31;

    if (lbl_1_bss_DBA >= 7) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            fn_1_7858(lbl_1_bss_DC4[var_r31]);
        }
    }
}

void fn_1_7BBC(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x80; var_r31++) {
        lbl_1_bss_BA4[var_r31] = NULL;
    }
}

void *fn_1_7BFC(s32 arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 128; var_r31++) {
        if (!lbl_1_bss_BA4[var_r31]) {
            break;
        }
    }
    if (var_r31 == 0x80) {
        return NULL;
    }
    lbl_1_bss_BA4[var_r31] = HuMemDirectMallocNum(HEAP_SYSTEM, arg0, MEMORY_DEFAULT_NUM);
    return lbl_1_bss_BA4[var_r31];
}

void fn_1_7C9C(void *arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 128; var_r31++) {
        if (lbl_1_bss_BA4[var_r31] == arg0) {
            break;
        }
    }
    if (var_r31 != 128) {
        HuMemDirectFree(lbl_1_bss_BA4[var_r31]);
        lbl_1_bss_BA4[var_r31] = NULL;
    }
}

void fn_1_7D30(void)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 128; var_r31++) {
        if (lbl_1_bss_BA4[var_r31]) {
            HuMemDirectFree(lbl_1_bss_BA4[var_r31]);
            lbl_1_bss_BA4[var_r31] = NULL;
        }
    }
}

s32 fn_1_7DB4(void)
{
    return frand() & 0xFFFF;
}

void fn_1_7DD8(s32 arg0, s32 *arg1)
{
    s32 var_r31;
    s32 var_r29;
    s32 var_r27;
    s32 var_r26;

    for (var_r31 = 0; var_r31 < arg0; var_r31++) {
        arg1[var_r31] = var_r31;
    }
    for (var_r31 = 0; var_r31 < (arg0 - 1); var_r31++) {
        var_r26 = frand() & 0xFFFF;
        var_r29 = arg0 * (0.000015258789f * var_r26);
        if (var_r29 >= arg0) {
            var_r29 = arg0 - 1;
        }
        var_r27 = arg1[var_r31];
        arg1[var_r31] = arg1[var_r29];
        arg1[var_r29] = var_r27;
    }
}

float fn_1_7EDC(float arg8, float arg9, float argA)
{
    float var_f1;
    float var_f31;

    if (arg8 > 180.0f) {
        arg8 -= 360.0f;
    }
    else if (arg8 <= -180.0f) {
        arg8 += 360.0f;
    }
    if (arg9 > 180.0f) {
        arg9 -= 360.0f;
    }
    else if (arg9 <= -180.0f) {
        arg9 += 360.0f;
    }
    var_f31 = arg8 - arg9;
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    else if (var_f31 <= -180.0f) {
        var_f31 += 360.0f;
    }
    var_f1 = arg9 + (var_f31 * argA);
    if (var_f1 > 180.0f) {
        return var_f1 - 360.0f;
    }
    if (var_f1 <= -180.0f) {
        var_f1 += 360.0f;
    }
    return var_f1;
}

// void fn_1_8044(Mtx arg0, float arg8, float arg9, float argA)
// {
//     Mtx var_r31;
//     float var_f29;
//     float var_f30;
//     float var_f31;

//     var_r31 = arg0;
//     var_f29 = arg8;
//     var_f30 = arg9;
//     var_f31 = argA;
//     if (var_f31 != 0.0f) {
//         PSMTXRotRad(var_r31, 0x5A, 0.017453292f * var_f31);
//     }
//     else {
//         PSMTXIdentity(var_r31);
//     }
//     if (var_f29 != 0.0f) {
//         PSMTXRotRad(&sp38[0], 0x58, 0.017453292f * var_f29);
//         PSMTXConcat(&sp38[0], var_r31, var_r31);
//     }
//     if (var_f30 != 0.0f) {
//         PSMTXRotRad(&sp8[0], 0x59, 0.017453292f * var_f30);
//         PSMTXConcat(&sp8[0], var_r31, var_r31);
//     }
// }

// void fn_1_8164(float *arg0, Vec *arg1)
// {
//     float sp8;
//     Vec *var_r31;
//     float *var_r30;
//     float var_f27;
//     float var_f28;
//     float var_f29;
//     double var_f30;
//     double var_f31;

//     var_r30 = arg0;
//     var_r31 = arg1;
//     var_r31->x = atan2d(var_r30->unk_18, var_r30->unk_28);
//     if (var_r31->x < 0.0f) {
//         var_r31->x += 360.0f;
//     }
//     var_r31->z = atan2d(var_r30->unk_04, var_r30->unk_00);
//     if (var_r31->z < 0.0f) {
//         var_r31->z += 360.0f;
//     }
//     var_f29 = -var_r30->unk_08;
//     if ((1.0 - (var_f29 * var_f29)) < 0.0) {
//         var_f30 = -(1.0 - (var_f29 * var_f29));
//     }
//     else {
//         var_f30 = 1.0 - (var_f29 * var_f29);
//     }
//     if (var_f30 > 0.0f) {
//         var_f31 = __frsqrte(var_f30);
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         sp8 = var_f30 * var_f31;
//         var_f27 = sp8;
//     }
//     else {
//         var_f27 = var_f30;
//     }
//     var_f28 = var_f27;
//     if ((var_r31->x > 90.0f) && (var_r31->x < 270.0f) && (var_r31->z > 90.0f) && (var_r31->z < 270.0f)) {
//         var_r31->x = fmod(180.0f + var_r31->x, 360.0);
//         var_r31->z = fmod(180.0f + var_r31->z, 360.0);
//         var_f28 = -var_f28;
//     }
//     var_r31->y = atan2d(var_f29, var_f28);
//     if (var_r31->y < 0.0f) {
//         var_r31->y += 360.0f;
//     }
// }

// void fn_1_8500(void *arg0, void *arg1)
// {
//     float sp8;
//     float var_f27;
//     float var_f28;
//     float var_f29;
//     double var_f30;
//     double var_f31;
//     void *var_r30;
//     void *var_r31;

//     var_r31 = arg0;
//     var_r30 = arg1;
//     var_r30->unk_08 = atan2d(var_r31->unk_04, var_r31->unk_14);
//     var_r30->unk_04 = atan2d(var_r31->unk_20, var_r31->unk_28);
//     var_f29 = -var_r31->unk_24;
//     if ((1.0 - (var_f29 * var_f29)) < 0.0) {
//         var_f30 = -(1.0 - (var_f29 * var_f29));
//     }
//     else {
//         var_f30 = 1.0 - (var_f29 * var_f29);
//     }
//     if (var_f30 > 0.0f) {
//         var_f31 = __frsqrte(var_f30);
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         sp8 = var_f30 * var_f31;
//         var_f28 = sp8;
//     }
//     else {
//         var_f28 = var_f30;
//     }
//     var_f27 = var_f28;
//     var_r30->unk_00 = atan2d(var_f29, var_f27);
// }

// double fn_1_8750(double arg8, float arg9, float argA, float argB)
// {
//     double var_f30;
//     double var_f31;

//     var_f31 = 1.0 - arg8;
//     var_f31 = var_f31;
//     var_f30 = (argB * (arg8 * arg8)) + ((arg9 * (var_f31 * var_f31)) + (2.0 * (argA * (var_f31 * arg8))));
//     var_f30 = var_f30;
//     return var_f30;
// }

// void fn_1_87C8(float *arg0, float *arg1, float *arg2, float *arg3, double arg8)
// {
//     float *var_r3;
//     float *var_r4;
//     float *var_r5;
//     float *var_r6;
//     float var_f26;
//     float var_f27;
//     float var_f28;
//     float var_f29;
//     double var_f24;
//     double var_f25;
//     double var_f30;
//     double var_f31;
//     s32 var_r31;

//     var_r3 = arg0;
//     var_r4 = arg1;
//     var_r5 = arg2;
//     var_r6 = arg3;
//     for (var_r31 = 0; var_r31 < 3; var_r31++) {
//         var_f27 = *var_r5;
//         var_r5 += 4;
//         var_f28 = *var_r4;
//         var_r4 += 4;
//         var_f29 = *var_r3;
//         var_r3 += 4;
//         var_f26 = var_f29;
//         var_f31 = 1.0 - arg8;
//         var_f31 = var_f31;
//         var_f30 = (var_f27 * (arg8 * arg8)) + ((var_f29 * (var_f31 * var_f31)) + (2.0 * (var_f28 * (var_f31 * arg8))));
//         var_f30 = var_f30;
//         var_f25 = var_f30;
//         var_f24 = var_f25;
//         *var_r6 = var_f24;
//         var_r6 += 4;
//     }
// }

// double fn_1_88E4(float arg8, double arg9, double argA, float argB)
// {
//     double var_f31;

//     var_f31 = 2.0 * ((arg8 * argB) + (((arg8 - 1.0) * arg9) + ((1.0 - (2.0 * arg8)) * argA)));
//     var_f31 = var_f31;
//     return var_f31;
// }

// void fn_1_895C(float *arg0, float *arg1, float *arg2, float *arg3, float arg8)
// {
//     float sp8;
//     float *temp_r6;
//     float *var_r3;
//     float *var_r4;
//     float *var_r5;
//     float *var_r6;
//     float var_f23;
//     float var_f24;
//     float var_f25;
//     float var_f26;
//     float var_f28;
//     float var_f29;
//     float var_f30;
//     double var_f21;
//     double var_f22;
//     double var_f27;
//     double var_f31;
//     s32 var_r31;

//     var_r3 = arg0;
//     var_r4 = arg1;
//     var_r5 = arg2;
//     var_r6 = arg3;
//     for (var_r31 = 0; var_r31 < 3; var_r31++) {
//         var_f24 = *var_r5;
//         var_r5 += 4;
//         var_f25 = *var_r4;
//         var_r4 += 4;
//         var_f26 = *var_r3;
//         var_r3 += 4;
//         var_f23 = var_f26;
//         var_f27 = 2.0 * ((arg8 * var_f24) + (((arg8 - 1.0) * var_f26) + ((1.0 - (2.0 * arg8)) * var_f25)));
//         var_f27 = var_f27;
//         var_f22 = var_f27;
//         var_f21 = var_f22;
//         (&spC[0])[var_r31] = var_f21;
//     }
//     var_f30 = (sp14 * sp14) + ((spC[0] * spC[0]) + (sp10 * sp10));
//     if (var_f30 > 0.0f) {
//         var_f31 = __frsqrte(var_f30);
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         sp8 = var_f30 * var_f31;
//         var_f28 = sp8;
//     }
//     else {
//         var_f28 = var_f30;
//     }
//     var_f29 = var_f28;
//     if (var_f29 != 0.0f) {
//         var_f29 = 1.0 / var_f29;
//         var_f29 = var_f29;
//         for (var_r31 = 0; var_r31 < 3; var_r31++) {
//             *var_r6 = var_f29 * (&spC[0])[var_r31];
//             var_r6 += 4;
//         }
//         return;
//     }
//     *var_r6 = 0.0f;
//     temp_r6 = var_r6 + 4;
//     *temp_r6 = 0.0f;
//     *(temp_r6 + 4) = 1.0f;
// }

void fn_1_8C34(float *arg0, float *arg1, float *arg2, s32 arg3)
{
    float sp48[16];
    float sp8[16];
    double var_f31;
    s32 var_r31;

    arg2[0] = 0.0f;
    arg2[arg3 - 1] = 0.0f;

    for (var_r31 = 0; var_r31 < (arg3 - 1); var_r31++) {
        sp48[var_r31] = arg0[var_r31 + 1] - arg0[var_r31];
        if (sp48[var_r31] == 0.0f) {
            sp8[var_r31 + 1] = 0.0f;
        }
        else {
            sp8[var_r31 + 1] = (arg1[var_r31 + 1] - arg1[var_r31]) / sp48[var_r31];
        }
    }
    arg2[1] = sp8[2] - sp8[1];
    sp8[1] = 2.0f * (arg0[2] - arg0[0]);

    for (var_r31 = 1; var_r31 < (arg3 - 2); var_r31++) {
        var_f31 = sp48[var_r31] / sp8[var_r31];
        arg2[var_r31 + 1] = (sp8[var_r31 + 2] - sp8[var_r31 + 1]) - (var_f31 * arg2[var_r31]);
        sp8[var_r31 + 1] = (2.0f * (arg0[var_r31 + 2] - arg0[var_r31])) - (var_f31 * sp48[var_r31]);
    }
    arg2[arg3 - 2] -= sp48[arg3 - 2] * arg2[arg3 - 1];

    for (var_r31 = arg3 - 2; var_r31 > 0; var_r31--) {
        if (sp8[var_r31] == 0.0f) {
            arg2[var_r31] = 0.0f;
        }
        else {
            arg2[var_r31] = (arg2[var_r31] - (sp48[var_r31] * arg2[var_r31 + 1])) / sp8[var_r31];
        }
    }
}

float fn_1_8EEC(float *arg0, float *arg1, float *arg2, float arg8)
{
    float var_f31;
    float var_f30;
    float var_f29;

    s32 var_r31 = arg8;

    arg8 = (arg8 - var_r31);
    var_f31 = arg0[var_r31 + 1] - arg0[var_r31];
    var_f30 = var_f31 * arg8;
    var_f29 = arg1[var_r31]
        + (var_f30
            * ((var_f30 * ((3.0f * arg2[var_r31]) + ((var_f30 * (arg2[var_r31 + 1] - arg2[var_r31])) / var_f31)))
                + (((arg1[var_r31 + 1] - arg1[var_r31]) / var_f31) - (var_f31 * ((2.0f * arg2[var_r31]) + arg2[var_r31 + 1])))));
    if (var_f31 == 0.0f) {
        var_f29 = arg1[var_r31];
    }
    return var_f29;
}

void fn_1_9040(float *arg0, Vec *arg1, float arg2[3][3], s32 arg3)
{
    float spD4[16];
    float sp94[16];
    float sp54[16];
    float sp14[16];
    Vec sp8;

    double var_f31;

    s32 var_r31;
    s32 var_r30;
    s32 var_r27;

    arg0[0] = 0.0f;
    for (var_r30 = 1; var_r30 < arg3; var_r30++) {
        VECSubtract(&arg1[var_r30], &arg1[var_r30 - 1], &sp8);
        arg0[var_r30] = arg0[var_r30 - 1] + VECMag(&sp8);
    }
    for (var_r27 = 0; var_r27 < 3; var_r27++) {
        for (var_r30 = 0; var_r30 < arg3; var_r30++) {
            spD4[var_r30] = ((float *)&arg1[var_r30])[var_r27]; // TODO
        }
        sp94[0] = 0.0f;
        sp94[arg3 - 1] = 0.0f;
        for (var_r31 = 0; var_r31 < (arg3 - 1); var_r31++) {
            sp14[var_r31] = arg0[var_r31 + 1] - arg0[var_r31];
            if (sp14[var_r31] == 0.0f) {
                sp54[var_r31 + 1] = 0.0f;
            }
            else {
                sp54[var_r31 + 1] = (spD4[var_r31 + 1] - spD4[var_r31]) / sp14[var_r31];
            }
        }
        sp94[1] = sp54[2] - sp54[1];
        sp54[1] = 2.0f * (arg0[2] - arg0[0]);
        for (var_r31 = 1; var_r31 < (arg3 - 2); var_r31++) {
            var_f31 = sp14[var_r31] / sp54[var_r31];
            sp94[var_r31 + 1] = (sp54[var_r31 + 2] - sp54[var_r31 + 1]) - (var_f31 * sp94[var_r31]);
            sp54[var_r31 + 1] = (2.0f * (arg0[var_r31 + 2] - arg0[var_r31])) - (var_f31 * sp14[var_r31]);
        }
        sp94[arg3 - 2] -= sp14[arg3 - 2] * sp94[arg3 - 1];
        for (var_r31 = arg3 - 2; var_r31 > 0; var_r31--) {
            if (sp54[var_r31] == 0.0f) {
                sp94[var_r31] = 0.0f;
            }
            else {
                sp94[var_r31] = (sp94[var_r31] - (sp14[var_r31] * sp94[var_r31 + 1])) / sp54[var_r31];
            }
        }
        for (var_r30 = 0; var_r30 < arg3; var_r30++) {
            arg2[var_r30][var_r27] = sp94[var_r30];
        }
    }
}

void fn_1_9420(float *arg0, float *arg1, float arg2[3][3], float arg3[3][3], s32 arg4, float arg8)
{
    float sp48[16];
    float sp8[16];

    float var_f29;

    s32 var_r30;
    s32 var_r29;

    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        for (var_r30 = 0; var_r30 < arg4; var_r30++) {
            sp48[var_r30] = arg2[var_r30][var_r29];
            sp8[var_r30] = arg3[var_r30][var_r29];
        }
        arg0[var_r29] = fn_1_8EEC(arg1, sp48, sp8, arg8);
    }
}

// float fn_1_9634(Vec *arg0)
// {
//     float sp8;
//     float var_f28;
//     float var_f29;
//     float var_f30;
//     double var_f31;

//     var_f30 = (arg0->z * arg0->z) + ((arg0->x * arg0->x) + (arg0->y * arg0->y));
//     if (var_f30 > 0.0f) {
//         var_f31 = __frsqrte(var_f30);
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f30 * (var_f31 * var_f31)));
//         sp8 = var_f30 * var_f31;
//         var_f28 = sp8;
//     }
//     else {
//         var_f28 = var_f30;
//     }
//     var_f30 = var_f28;
//     if (var_f30 != 0.0f) {
//         var_f29 = 1.0f / var_f30;
//         arg0->x *= var_f29;
//         arg0->y *= var_f29;
//         arg0->z *= var_f29;
//     }
//     else {
//         arg0->z = 0.0f;
//         arg0->y = 0.0f;
//         arg0->x = 0.0f;
//     }
//     return var_f30;
// }

// float fn_1_97CC(void *arg0, void *arg1, void *arg2, float arg8)
// {
//     if (arg8 <= 0.0f) {
//         arg2->unk_00 = arg0->unk_00;
//         arg2->unk_04 = arg0->unk_04;
//         arg2->unk_08 = arg0->unk_08;
//         return 0.0f;
//     }
//     if (arg8 >= 1.0f) {
//         arg2->unk_00 = arg0->unk_00 + arg1->unk_00;
//         arg2->unk_04 = arg0->unk_04 + arg1->unk_04;
//         arg2->unk_08 = arg0->unk_08 + arg1->unk_08;
//         return 1.0f;
//     }
//     arg2->unk_00 = arg0->unk_00 + (arg8 * arg1->unk_00);
//     arg2->unk_04 = arg0->unk_04 + (arg8 * arg1->unk_04);
//     arg2->unk_08 = arg0->unk_08 + (arg8 * arg1->unk_08);
//     return arg8;
// }

// float fn_1_98A4(void *arg0, void *arg1, void *arg2)
// {
//     float var_f30;
//     float var_f31;

//     var_f31 = (arg2->unk_08 * (arg1->unk_08 - arg0->unk_08))
//         + ((arg2->unk_00 * (arg1->unk_00 - arg0->unk_00)) + (arg2->unk_04 * (arg1->unk_04 - arg0->unk_04)));
//     var_f30 = -((arg2->unk_08 * arg2->unk_08) + ((arg2->unk_00 * arg2->unk_00) + (arg2->unk_04 * arg2->unk_04)));
//     if (var_f30 != 0.0f) {
//         var_f31 /= var_f30;
//     }
//     return var_f31;
// }

// float fn_1_9960(Vec *arg0, Vec *arg1, Vec *arg2)
// {
//     float sp4C;
//     float sp48;
//     float sp44;
//     float sp40;
//     float sp3C;
//     float sp38;
//     float sp34;
//     float sp30;
//     float sp2C;
//     float sp28;
//     float sp24;
//     float sp20;
//     float sp1C;
//     float sp18;
//     float sp14;
//     float sp10;
//     float spC;
//     float sp8;
//     float var_f27;
//     float var_f28;
//     float var_f29;
//     float var_f30;
//     float var_f31;

//     if (((arg2->z * arg2->z) + ((arg2->x * arg2->x) + (arg2->y * arg2->y))) == 0.0f) {
//         return ((arg0->z - arg1->z) * (arg0->z - arg1->z))
//             + (((arg0->x - arg1->x) * (arg0->x - arg1->x)) + ((arg0->y - arg1->y) * (arg0->y - arg1->y)));
//     }
//     sp38 = arg0->x;
//     sp3C = arg0->y;
//     sp40 = arg0->z;
//     sp2C = arg1->x;
//     sp30 = arg1->y;
//     sp34 = arg1->z;
//     sp20 = arg2->x;
//     sp24 = arg2->y;
//     sp28 = arg2->z;
//     var_f30 = (sp28 * (sp34 - sp40)) + ((sp20 * (sp2C - sp38)) + (sp24 * (sp30 - sp3C)));
//     var_f29 = -((sp28 * sp28) + ((sp20 * sp20) + (sp24 * sp24)));
//     if (var_f29 != 0.0f) {
//         var_f30 /= var_f29;
//     }
//     var_f27 = var_f30;
//     var_f28 = var_f27;
//     var_f31 = var_f28;
//     sp8 = arg2->x;
//     spC = arg2->y;
//     sp10 = arg2->z;
//     sp14 = arg1->x;
//     sp18 = arg1->y;
//     sp1C = arg1->z;
//     if (var_f31 <= 0.0f) {
//         sp44 = sp14;
//         sp48 = sp18;
//         sp4C = sp1C;
//         var_f31 = 0.0f;
//     }
//     else if (var_f31 >= 1.0f) {
//         sp44 = sp14 + sp8;
//         sp48 = sp18 + spC;
//         sp4C = sp1C + sp10;
//         var_f31 = 1.0f;
//     }
//     else {
//         sp44 = sp14 + (var_f31 * sp8);
//         sp48 = sp18 + (var_f31 * spC);
//         sp4C = sp1C + (var_f31 * sp10);
//     }
//     return ((arg0->z - sp4C) * (arg0->z - sp4C)) + (((arg0->x - sp44) * (arg0->x - sp44)) + ((arg0->y - sp48) * (arg0->y - sp48)));
// }

// float fn_1_9C9C(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4)
// {
//     float sp44;
//     float sp40;
//     float sp3C;
//     float sp38;
//     float sp34;
//     float sp30;
//     float sp2C;
//     float sp28;
//     float sp24;
//     float sp20;
//     float sp1C;
//     float sp18;
//     float sp14;
//     float sp10;
//     float spC;
//     float sp8;
//     float var_f22;
//     float var_f23;
//     float var_f24;
//     float var_f25;
//     float var_f26;
//     float var_f27;
//     float var_f28;
//     float var_f29;
//     float var_f30;
//     double var_f31;

//     if (((arg2->unk_08 * arg2->unk_08) + ((arg2->unk_00 * arg2->unk_00) + (arg2->unk_04 * arg2->unk_04))) == 0.0f) {
//         return ((arg0->unk_08 - arg1->unk_08) * (arg0->unk_08 - arg1->unk_08))
//             + (((arg0->unk_00 - arg1->unk_00) * (arg0->unk_00 - arg1->unk_00)) + ((arg0->unk_04 - arg1->unk_04) * (arg0->unk_04 -
//             arg1->unk_04)));
//     }
//     sp3C = arg0->unk_00;
//     sp40 = arg0->unk_04;
//     sp44 = arg0->unk_08;
//     sp30 = arg1->unk_00;
//     sp34 = arg1->unk_04;
//     sp38 = arg1->unk_08;
//     sp24 = arg2->unk_00;
//     sp28 = arg2->unk_04;
//     sp2C = arg2->unk_08;
//     var_f27 = (sp2C * (sp38 - sp44)) + ((sp24 * (sp30 - sp3C)) + (sp28 * (sp34 - sp40)));
//     var_f25 = -((sp2C * sp2C) + ((sp24 * sp24) + (sp28 * sp28)));
//     if (var_f25 != 0.0f) {
//         var_f27 /= var_f25;
//     }
//     var_f22 = var_f27;
//     var_f23 = var_f22;
//     var_f30 = var_f23;
//     spC = arg2->unk_00;
//     sp10 = arg2->unk_04;
//     sp14 = arg2->unk_08;
//     sp18 = arg1->unk_00;
//     sp1C = arg1->unk_04;
//     sp20 = arg1->unk_08;
//     if (var_f30 <= 0.0f) {
//         arg3->unk_00 = sp18;
//         arg3->unk_04 = sp1C;
//         arg3->unk_08 = sp20;
//         var_f30 = 0.0f;
//     }
//     else if (var_f30 >= 1.0f) {
//         arg3->unk_00 = sp18 + spC;
//         arg3->unk_04 = sp1C + sp10;
//         arg3->unk_08 = sp20 + sp14;
//         var_f30 = 1.0f;
//     }
//     else {
//         arg3->unk_00 = sp18 + (var_f30 * spC);
//         arg3->unk_04 = sp1C + (var_f30 * sp10);
//         arg3->unk_08 = sp20 + (var_f30 * sp14);
//     }
//     arg4->unk_00 = arg0->unk_00 - arg3->unk_00;
//     arg4->unk_04 = arg0->unk_04 - arg3->unk_04;
//     arg4->unk_08 = arg0->unk_08 - arg3->unk_08;
//     var_f28 = (arg4->unk_08 * arg4->unk_08) + ((arg4->unk_00 * arg4->unk_00) + (arg4->unk_04 * arg4->unk_04));
//     var_f29 = var_f28;
//     if (var_f29 > 0.0f) {
//         var_f31 = __frsqrte(var_f29);
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f29 * (var_f31 * var_f31)));
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f29 * (var_f31 * var_f31)));
//         var_f31 = 0.5 * var_f31 * (3.0 - (var_f29 * (var_f31 * var_f31)));
//         sp8 = var_f29 * var_f31;
//         var_f24 = sp8;
//     }
//     else {
//         var_f24 = var_f29;
//     }
//     var_f28 = var_f24;
//     if (var_f28 != 0.0f) {
//         var_f26 = 1.0f / var_f28;
//         arg4->unk_00 = arg4->unk_00 * var_f26;
//         arg4->unk_04 = arg4->unk_04 * var_f26;
//         arg4->unk_08 = arg4->unk_08 * var_f26;
//     }
//     else {
//         arg4->unk_08 = 0.0f;
//         arg4->unk_04 = 0.0f;
//         arg4->unk_00 = 0.0f;
//     }
//     return var_f28;
// }

// float fn_1_A14C(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3)
// {
//     float var_f23;
//     float var_f24;
//     float var_f25;
//     float var_f26;
//     float var_f27;
//     float var_f28;
//     float var_f29;
//     float var_f30;
//     float var_f31;
//     s32 var_r29;
//     s32 var_r30;
//     s32 var_r31;

//     var_f30 = -1.0f;
//     var_r31 = 0;
//     if (arg3->unk_00 < 0.0f) {
//         var_f25 = -arg3->unk_00;
//     }
//     else {
//         var_f25 = arg3->unk_00;
//     }
//     var_f28 = var_f25;
//     if (arg3->unk_04 < 0.0f) {
//         var_f24 = -arg3->unk_04;
//     }
//     else {
//         var_f24 = arg3->unk_04;
//     }
//     var_f27 = var_f24;
//     if (arg3->unk_08 < 0.0f) {
//         var_f23 = -arg3->unk_08;
//     }
//     else {
//         var_f23 = arg3->unk_08;
//     }
//     var_f26 = var_f23;
//     if (var_f28 >= var_f27) {
//         if (var_f28 >= var_f26) {
//             var_r30 = 1;
//         }
//         else {
//             var_r30 = 0x100;
//         }
//         var_r31 = var_r30;
//     }
//     else {
//         if (var_f27 >= var_f26) {
//             var_r29 = 0x10;
//         }
//         else {
//             var_r29 = 0x100;
//         }
//         var_r31 = var_r29;
//     }
//     if ((var_r31 & 3) != 0) {
//         if ((arg1->x != 0.0f) || (arg1->z != 0.0f)) {
//             var_f31 = (arg3->unk_00 * arg1->z) - (arg3->unk_08 * arg1->x);
//             if (var_f31 == 0.0f) {
//                 return -1.0f;
//             }
//             var_f29 = ((arg3->unk_08 * (arg0->x - arg2->x)) - (arg3->unk_00 * (arg0->z - arg2->z))) / var_f31;
//             goto block_44;
//         }
//         var_f31 = (arg3->unk_04 * arg1->x) - (arg3->unk_00 * arg1->y);
//         if (var_f31 == 0.0f) {
//             return -1.0f;
//         }
//         var_f29 = ((arg3->unk_00 * (arg0->y - arg2->y)) - (arg3->unk_04 * (arg0->x - arg2->x))) / var_f31;
//         goto block_44;
//     }
//     if ((var_r31 & 0x30) != 0) {
//         if ((arg1->x != 0.0f) || (arg1->y != 0.0f)) {
//             var_f31 = (arg3->unk_04 * arg1->x) - (arg3->unk_00 * arg1->y);
//             if (var_f31 == 0.0f) {
//                 return -1.0f;
//             }
//             var_f29 = ((arg3->unk_00 * (arg0->y - arg2->y)) - (arg3->unk_04 * (arg0->x - arg2->x))) / var_f31;
//             goto block_44;
//         }
//         var_f31 = (arg3->unk_08 * arg1->y) - (arg3->unk_04 * arg1->z);
//         if (var_f31 == 0.0f) {
//             return -1.0f;
//         }
//         var_f29 = ((arg3->unk_04 * (arg0->z - arg2->z)) - (arg3->unk_08 * (arg0->y - arg2->y))) / var_f31;
//         goto block_44;
//     }
//     if ((arg1->x != 0.0f) || (arg1->z != 0.0f)) {
//         var_f31 = (arg3->unk_00 * arg1->z) - (arg3->unk_08 * arg1->x);
//         if (var_f31 == 0.0f) {
//             return -1.0f;
//         }
//         var_f29 = ((arg3->unk_08 * (arg0->x - arg2->x)) - (arg3->unk_00 * (arg0->z - arg2->z))) / var_f31;
//         goto block_44;
//     }
//     var_f31 = (arg3->unk_08 * arg1->y) - (arg3->unk_04 * arg1->z);
//     if (var_f31 == 0.0f) {
//         return -1.0f;
//     }
//     var_f29 = ((arg3->unk_04 * (arg0->z - arg2->z)) - (arg3->unk_08 * (arg0->y - arg2->y))) / var_f31;
// block_44:
//     return var_f29;
// }

void fn_1_A60C(omObjData *object)
{
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x900, MEMORY_DEFAULT_NUM);
    memset(object->data, 0, 0x900);
    object->model[0] = Hu3DHookFuncCreate(fn_1_A68C);
    Hu3DModelLayerSet(object->model[0], 7);
    object->func = fn_1_A688;
}

void fn_1_A688(omObjData *object) { }

// void fn_1_A68C(ModelData *model, Mtx matrix)
// {
//     Vec sp14;
//     Vec sp8;
//     ? *var_r30;
//     float var_f31;
//     omObjData *var_r27;
//     s32 var_r24;
//     s32 var_r28;
//     s32 var_r29;
//     u8 *var_r26;
//     void *var_r25;
//     void *var_r31;

//     if (omPauseChk() == 0) {
//         memset(lbl_1_bss_DBC->data, 0, 0x900);
//         if (lbl_1_bss_DBA == 7) {
//             for (var_r30 = &lbl_1_bss_298; var_r29 = 0; var_r30 < 0x30; var_r29++; var_r30 += 0x30) {
//                 if ((var_r30->unk_00 > 1) && (var_r30->unk_00 < 5)) {
//                     var_f31 = 0.0f;
//                     for (var_f31 = 0.0f; var_f31 < (35.416668f + var_r30->unk_14); var_f31 += 35.416668f) {
//                         VECScale(var_r30 + 0x24, &sp8, var_f31);
//                         VECAdd(var_r30 + 0x18, &sp8, &sp14);
//                         VECSubtract(&sp14, &lbl_1_data_514, &sp14);
//                         var_r24 = (0.028235294f * sp14.z) * 0x30;
//                         var_r25 = (0.028235294f * sp14) + var_r24;
//                         var_r25 += lbl_1_bss_DBC->data;
//                         for (var_r28 = 0; var_r28 < 0x19; var_r28++) {
//                             var_r26 = var_r25 + lbl_1_data_520[var_r28];
//                             if (*var_r26 < lbl_1_data_584[var_r28]) {
//                                 *var_r26 = lbl_1_data_584[var_r28];
//                             }
//                         }
//                     }
//                 }
//             }
//             for (var_r29 = 0; var_r29 < 4; var_r29++) {
//                 if (lbl_1_bss_DC4[var_r29] != NULL) {
//                     var_r27 = lbl_1_bss_DC4[var_r29];
//                     var_r31 = var_r27->data;
//                     if ((var_r31 != NULL) && (var_r31->unk_68 != 0)) {
//                         var_r31->unk_68 = 0;
//                         VECAdd(var_r31 + 0x6C, var_r31 + 0x4C, &sp14);
//                         var_r31->unk_64 = fn_1_AE18(var_r27->work[0], &sp14, var_r31 + 0x58);
//                     }
//                 }
//             }
//         }
//     }
// }

// u16 fn_1_A8FC(Vec *arg0, float arg8)
// {
//     s32 sp34;
//     float sp30;
//     s32 sp2C;
//     Vec sp20;
//     Vec sp14;
//     float sp10;
//     float spC;
//     float sp8;
//     Vec *var_r29;
//     float var_f25;
//     float var_f28;
//     float var_f29;
//     float var_f30;
//     float var_f31;
//     double var_f26;
//     double var_f27;
//     s32 var_r28;
//     u16 var_r30;
//     u8 temp_r0;
//     void *var_r31;

//     var_r29 = arg0;
//     var_f25 = arg8;
//     var_r30 = 0;
//     var_r28 = 0;
//     var_f28 = 100.0f * (4.5f - (2.0f * var_f25));
//     var_f31 = VECMag(var_r29);
//     if (var_f31 > 280.0f) {
//         if (var_f31 > 560.0f) {
//             var_r28 = 1;
//             VECNormalize(var_r29, &sp14);
//         }
//         var_f31 -= 280.0f;
//         var_f31 *= 0.12987013f;
//         if (var_f31 > 50.0f) {
//             var_f31 = 500.0f;
//         }
//         var_r30 = var_f31;
//     }
//     if (lbl_1_bss_DBA == 7) {
//         var_r31 = lbl_1_bss_DC0->data;
//         sp2C = var_r31->unk_34;
//         sp30 = var_r31->unk_38;
//         sp34 = var_r31->unk_3C;
//         sp30 = 0.0f;
//         temp_r0 = var_r31->unk_00;
//         if (temp_r0 < 4) {
//             if (temp_r0 < 2) {
//                 goto block_18;
//             }
//             sp8 = sind(var_r31->unk_08);
//             spC = 0.0f;
//             sp10 = cosd(var_r31->unk_08);
//             VECScale(&sp8, &sp20, 600.0f + (100.0f * (8.0f * var_f25)));
//             var_f30 = fn_1_B440(var_r29, &sp2C, &sp20);
//             if ((var_f30 > -0.2f) && (var_f30 < 1.0f)) {
//                 VECScale(&sp20, &sp20, var_f30);
//                 VECAdd(&sp2C, &sp20, &sp2C);
//                 VECSubtract(&sp2C, var_r29, &sp20);
//                 var_f31 = VECMag(&sp20);
//                 if (var_f31 < var_f28) {
//                     var_f29 = 0.0f;
//                     if (var_r28 != 0) {
//                         var_f29 = VECDotProduct(&sp14, &sp8);
//                         var_f27 = fabs(var_f29);
//                         var_f29 = 1.0 - var_f27;
//                         var_f29 = var_f29;
//                     }
//                     var_f31 = (1.0f / var_f28) * (var_f28 - var_f31);
//                     var_f31 = 0.5f * (var_f31 + (1.0f - ((1.0f - var_f31) * (1.0f - var_f31))));
//                     var_f31 += (1.0f - var_f31) * var_f29;
//                     var_f31 = 100.0f + (50.0f * var_f31);
//                     var_f26 = fabs(var_f30);
//                     var_f30 = 0.5 + (0.5 * (1.0 - var_f26));
//                     var_f30 = var_f30;
//                     var_f31 *= var_f30;
//                     if (var_f31 > 150.0f) {
//                         var_f31 = 150.0f;
//                     }
//                     var_r30 = var_r30 + var_f31;
//                 }
//             }
//         }
//         else {
//         block_18:
//             VECSubtract(var_r29, &sp2C, &sp20);
//             var_f31 = VECMag(&sp20);
//             if (var_f31 < 600.0f) {
//                 var_f31 = 800.0f - var_f31;
//                 var_f31 = 20.0f + (0.1f * var_f31);
//                 if (var_f31 > 100.0f) {
//                     var_f31 = 100.0f;
//                 }
//                 var_r30 = var_r30 + var_f31;
//             }
//         }
//     }
//     return var_r30;
// }

// s32 fn_1_AE18(u32 arg0, Vec *arg1, Vec *arg2)
// {
//     Vec sp4C;
//     float sp48;
//     float sp44;
//     float sp40;
//     Vec sp34;
//     float sp30;
//     float sp2C;
//     s32 sp28;
//     Vec sp1C;
//     void *sp18;
//     u32 sp14;
//     u32 sp10;
//     Vec *spC;
//     u32 sp8;
//     Vec *var_r20;
//     float temp_r0;
//     float temp_r3;
//     float var_f22;
//     float var_f23;
//     float var_f24;
//     float var_f25;
//     float var_f26;
//     float var_f27;
//     float var_f28;
//     float var_f29;
//     float var_f30;
//     float var_f31;
//     s32 var_r18;
//     s32 var_r23;
//     s32 var_r26;
//     s32 var_r28;
//     s32 var_r30;
//     u16 *var_r21;
//     u16 *var_r27;
//     u16 var_r31;
//     u32 temp_r3_2;
//     u32 var_r19;
//     u32 var_r29;
//     u8 *var_r24;
//     void *var_r17;
//     void *var_r22;
//     void *var_r25;

//     sp8 = arg0;
//     spC = arg1;
//     var_r20 = arg2;
//     memset(lbl_1_bss_C, 0, 0x288);
//     temp_r3 = arg1->x;
//     sp40 = temp_r3;
//     sp44 = arg1->y;
//     temp_r0 = arg1->z;
//     sp48 = temp_r0;
//     temp_r3_2 = 0.028235294f * (sp40 - -850.0f);
//     sp10 = temp_r3_2;
//     sp14 = 0.028235294f * (sp48 - -850.0f);
//     var_r17 = temp_r3_2 + (sp14 * 0x30);
//     var_r17 += lbl_1_bss_DBC->data;
//     sp44 = 0.0f;
//     var_r20->x = temp_r3;
//     var_r20->y = sp44;
//     var_r20->z = temp_r0;
//     var_r25 = lbl_1_bss_DC4[sp8]->data;
//     var_f28 = var_r25->unk_3C;
//     var_r19 = 0x2710;
//     var_r18 = 0;
//     for (var_r30 = 0; var_r30 < 9; var_r30++) {
//         VECAdd(&sp40, &lbl_1_data_60C[var_r30], &sp34);
//         sp18 = var_r17 + lbl_1_data_5E8[var_r30];
//         var_r21 = &lbl_1_bss_C[lbl_1_data_708[var_r30]] + 0x156;
//         var_f31 = 0.0f;
//         var_r29 = 0;
//         var_r22 = sp18;
//         sp28 = sp34;
//         sp2C = sp34.y;
//         sp30 = sp34.z;
//         for (var_r23 = 0; var_r23 < 3; var_r23++) {
//             for (var_r28 = 0; var_r28 < 9; var_r28++) {
//                 var_r24 = var_r22 + lbl_1_data_5E8[var_r28];
//                 VECAdd(&sp28, &lbl_1_data_60C[var_r28], &sp4C);
//                 if ((lbl_1_bss_DBC->data <= var_r24) && ((lbl_1_bss_DBC->data + 0x900) > var_r24)) {
//                     var_f27 = sp4C;
//                     var_f25 = fabs(var_f27);
//                     var_f24 = var_f25;
//                     if (var_f24 < 850.0) {
//                         var_f26 = sp4C.z;
//                         var_f23 = fabs(var_f26);
//                         var_f22 = var_f23;
//                         if (var_f22 < 850.0) {
//                             var_f31 += 1.0f;
//                             var_r27 = &var_r21[lbl_1_data_708[var_r28]];
//                             if (*var_r27 == 0) {
//                                 var_r31 = fn_1_A8FC(&sp4C, var_f28);
//                                 var_r31 += *var_r24;
//                                 var_f29 = 0.0f;
//                                 if (var_r31 < 0x3C) {
//                                     var_f29 = 0.016666668f * (0x3C - var_r31);
//                                 }
//                                 var_f29 = 80.0f + (100.0f * (2.5f * var_f29));
//                                 for (var_r26 = 0; var_r26 < 4; var_r26++) {
//                                     if (var_r26 != sp8) {
//                                         var_r25 = lbl_1_bss_DC4[var_r26]->data;
//                                         VECSubtract(&sp4C, var_r25 + 0x6C, &sp1C);
//                                         sp1C.y = 0.0f;
//                                         var_f30 = VECMag(&sp1C);
//                                         if (var_f30 < var_f29) {
//                                             var_f30 = var_f29 - var_f30;
//                                             var_f30 *= 40.0f / var_f29;
//                                             var_r31 = var_r31 + var_f30;
//                                         }
//                                     }
//                                 }
//                                 var_r31++;
//                                 *var_r27 = var_r31;
//                             }
//                             else {
//                                 var_r31 = *var_r27;
//                             }
//                             var_r29 += var_r31;
//                             if ((var_r28 == 0) && (var_r23 == 0)) {
//                                 var_r29 += var_r31 * 3;
//                                 var_f31 += 3.0f;
//                             }
//                         }
//                     }
//                 }
//             }
//             VECAdd(&sp28, &lbl_1_data_69C[var_r30], &sp28);
//             var_r22 += lbl_1_data_678[var_r30];
//             var_r21 = &var_r21[lbl_1_data_72C[var_r30]];
//             var_f31 *= 2.0f;
//             var_r29 = var_r29 * 2.0f;
//         }
//         if (var_f31 > 1.0f) {
//             var_r29 = var_r29 / var_f31;
//         }
//         if (var_r19 > var_r29) {
//             var_r18 = var_r30;
//             var_r19 = var_r29;
//             var_r20->x = sp34;
//             var_r20->y = sp34.y;
//             var_r20->z = sp34.z;
//         }
//         (&sp58[0])[var_r30] = var_r29;
//     }
//     if (var_r18 != 0) {
//         return 1;
//     }
//     return 0;
// }

// float fn_1_B440(Vec *arg0, Vec *arg1, Vec *arg2)
// {
//     Vec sp10;
//     Vec *spC;
//     Vec *sp8;
//     Vec *var_r31;
//     float var_f30;
//     float var_f31;

//     sp8 = arg0;
//     spC = arg1;
//     var_r31 = arg2;
//     VECSubtract(spC, sp8, &sp10);
//     var_f31 = VECDotProduct(&sp10, var_r31);
//     var_f30 = -VECSquareMag(var_r31);
//     if (var_f30 != 0.0f) {
//         var_f31 /= var_f30;
//     }
//     return var_f31;
// }
