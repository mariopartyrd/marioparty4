#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "dolphin.h"
#include "ext_math.h"
#include "version.h"

#define frand7() (frand() & 0x7F)

extern u32 GlobalCounter;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ void *unk10;
} StructBssD0Data; // Size 0x14

typedef struct {
    /* 0x00 */ Vec unk00;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ float unk18;
} StructData0; // Size 0x1C

typedef struct {
    /* 0x00 */ StructBssD0Data *unk00;
    /* 0x04 */ AnimData *unk04;
} StructM423_00; // Size 8

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ Vec unk08;
} StructM423_01; // Size 0x14

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec unk08;
    /* 0x14 */ Vec *unk14;
    /* 0x18 */ Vec *unk18;
    /* 0x1C */ GXColor *unk1C;
    /* 0x20 */ StructM423_01 *unk20;
    /* 0x24 */ float unk24[4];
    /* 0x34 */ u32 unk34;
    /* 0x38 */ void *unk38;
} StructM423_02; // Size 0x3C

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ StructM423_02 *unk04;
} StructM423_03; // Size 8

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ Vec unk04;
    /* 0x10 */ char unk10[8];
    /* 0x18 */ float unk18;
    /* 0x1C */ char unk1C[0xC];
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ Vec unk38;
    /* 0x44 */ GXColor unk44;
    /* 0x48 */ s32 unk48;
} StructM423_04; // Size 0x4C

typedef struct struct_m423_05 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x00 */ char unk04[0x1C];
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ s8 unk23;
    /* 0x24 */ char unk24[2];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ AnimData *unk38;
    /* 0x3C */ StructM423_04 *unk3C;
    /* 0x40 */ Vec *unk40;
    /* 0x44 */ float (*unk44)[2];
    /* 0x48 */ void *unk48;
    /* 0x4C */ void *unk4C;
    /* 0x50 */ ModelData *unk50;
} StructM423_05; // Size 0x54

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ float unk04;
    /* 0x08 */ char unk08[4];
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ char unk14[4];
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ char unk20[4];
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ char unk2C[4];
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ char unk38[4];
} StructM423_08; // Size 0x3C

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
} StructM423_09; // Size 0x28

typedef struct {
    /* 0x000 */ u16 unk00;
    /* 0x002 */ u16 unk02;
    /* 0x004 */ float unk04;
    /* 0x008 */ float unk08;
    /* 0x00C */ float unk0C;
    /* 0x010 */ float unk10;
    /* 0x014 */ Vec unk14;
} StructM423_0A; // Size 0x20

typedef struct {
    /* 0x000 */ StructM423_0A unk00[16];
    /* 0x200 */ AnimData *unk200;
    /* 0x204 */ s32 unk204;
    /* 0x208 */ void *unk208;
    /* 0x20C */ StructM423_08 *unk20C;
    /* 0x210 */ StructM423_09 *unk210;
    /* 0x214 */ GXColor *unk214;
    /* 0x218 */ s32 unk218;
    /* 0x21C */ s32 unk21C;
    /* 0x220 */ void *unk220;
} StructM423_0B; // Size 0x224

typedef struct {
    /* 0x000 */ s32 unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C;
    /* 0x010 */ s32 unk10[24];
    /* 0x070 */ s32 unk70[24][3];
    /* 0x190 */ s16 unk190[10][2];
} StructM423_0C; // Size 0x1B8

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ Vec unk20;
    /* 0x2C */ Vec unk2C;
    /* 0x38 */ Vec unk38;
    /* 0x44 */ float unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ Vec unk68;
    /* 0x74 */ Vec unk74;
    /* 0x80 */ Vec unk80;
    /* 0x8C */ float unk8C;
    /* 0x90 */ float unk90;
} StructBssA8Data; // Size 0x94

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
} StructBssCCData; // Size 0xC

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char unk1A[2];
    /* 0x1C */ float unk1C[15];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ float unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ float unk78;
    /* 0x7C */ float unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ float unk88;
    /* 0x8C */ float unk8C;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ s32 unk9C;
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ float unkA8;
    /* 0xAC */ s32 unkAC;
    /* 0xB0 */ float unkB0;
    /* 0xB4 */ float unkB4;
    /* 0xB8 */ float unkB8;
    /* 0xBC */ float unkBC;
    /* 0xC0 */ float unkC0;
    /* 0xC4 */ float unkC4;
    /* 0xC8 */ Vec unkC8;
    /* 0xD4 */ Vec unkD4;
    /* 0xE0 */ float unkE0;
    /* 0xE4 */ float unkE4;
    /* 0xE8 */ float unkE8;
    /* 0xEC */ float unkEC;
    /* 0xF0 */ float unkF0;
    /* 0xF4 */ float unkF4;
} StructBssBCData; // Size 0xF8

typedef struct {
    /* 0x000 */ s16 unk00;
    /* 0x002 */ s16 unk02;
    /* 0x004 */ Vec unk04;
    /* 0x010 */ Vec unk10;
    /* 0x004 */ char unk1C[0xC];
    /* 0x028 */ float unk28;
    /* 0x02C */ float unk2C;
    /* 0x030 */ float unk30;
    /* 0x034 */ float unk34;
    /* 0x038 */ char unk38[4];
    /* 0x03C */ float unk3C;
    /* 0x040 */ s32 unk40;
    /* 0x044 */ float unk44[12][4];
    /* 0x104 */ Vec unk104[12][3];
} StructBss94Data; // Size 0x2B4

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ AnimData *unk08;
} StructBssA4Data; // Size 0xC

void fn_1_318(omObjData *arg0);
void fn_1_3B0(omObjData *arg0);
void fn_1_DFC(omObjData *arg0);
void fn_1_E60(omObjData *arg0);
void fn_1_F10(void);
void fn_1_F60(omObjData *arg0);
void fn_1_11A4(omObjData *arg0);
void fn_1_1238(void);
void fn_1_12A0(ModelData *arg0, Mtx arg1);
s32 fn_1_13A0(StructBssD0Data *arg0);
void fn_1_1444(s32 arg0);
void fn_1_14A0(ModelData *arg0, Mtx arg1);
s32 fn_1_18FC(void);
void fn_1_1B5C(ModelData *arg0, StructM423_02 *arg1);
void fn_1_1F5C(ModelData *arg0, StructM423_02 *arg1);
void fn_1_2290(ModelData *arg0, StructM423_02 *arg1);
void fn_1_2624(ModelData *arg0, StructM423_02 *arg1);
void fn_1_29B8(s32 arg0);
void fn_1_29BC(ModelData *arg0, Mtx arg1);
void fn_1_2C08(s32 arg0);
void fn_1_34D8(void);
void fn_1_3528(omObjData *arg0);
void fn_1_3898(omObjData *arg0);
void fn_1_3A64(void);
void fn_1_3A8C(void);
void fn_1_3BFC(void);
void fn_1_3FE0(omObjData *arg0);
void fn_1_4778(omObjData *arg0);
void fn_1_5D18(omObjData *arg0);
void fn_1_77D0(void);
s32 fn_1_781C(void);
s32 fn_1_791C(void);
void fn_1_7AA8(s32 arg0);
void fn_1_82C8(s32 arg0, s32 arg1, s32 arg2);
void fn_1_8338(omObjData *arg0);
void fn_1_8CB4(omObjData *arg0);
void fn_1_95C4(void);
void fn_1_9614(omObjData *arg0);
void fn_1_98A0(omObjData *arg0);
void fn_1_A9AC(void);
s32 fn_1_A9D4(s32 arg0, Vec arg1, Vec arg2);
void fn_1_AC0C(s32 arg0, Vec arg1);
void fn_1_AC80(s32 arg0, Vec arg1);
s32 fn_1_AE64(s32 arg0);
void fn_1_AEE8(s32 arg0);
StructBssA8Data *fn_1_B13C(s32 arg0);
void fn_1_B1A4(void);
s32 fn_1_B304(StructBssA8Data **arg0);
void fn_1_B430(void);
void fn_1_BCD8(Vec *arg0, Vec *arg1, Vec *arg2, float arg3, s32 arg4, s32 arg5);
s32 fn_1_C498(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, float arg4, s32 arg5);
void fn_1_D930(void);
void fn_1_DA38(omObjData *arg0);
void fn_1_DBC8(void);
s32 fn_1_DC24(Vec arg0, Vec arg1, float arg2, float arg3, float arg4, GXColor arg5);
s32 fn_1_DD70(Vec arg0, Vec arg1, float arg2, float arg3, float arg4, float arg5, GXColor arg6);
void fn_1_E1BC(void);
void fn_1_E290(omObjData *arg0);
void fn_1_E330(void);
s32 fn_1_E334(Vec arg0, Vec arg1, float arg2);
void fn_1_E460(void);
void fn_1_E4EC(omObjData *arg0);
void fn_1_E60C(void);
s32 fn_1_E678(void);
void fn_1_EF44(ModelData *arg0, Mtx arg1);
s32 fn_1_F574(Vec arg0, float arg1, s32 arg2);
void fn_1_F690(void);
void fn_1_F6E0(omObjData *arg0);
void fn_1_FA40(omObjData *arg0);
void fn_1_FF98(void);
void fn_1_10028(s32 arg0);
void fn_1_100DC(void);
void fn_1_10480(omObjData *arg0);
void fn_1_10540(s32 arg0, s32 arg1, s32 arg2, float arg3);
void fn_1_106D8(s32 arg0);
void fn_1_10BC8(void);
void fn_1_11008(StructBssD0Data *arg0, void *arg1, s16 arg2, GXTexWrapMode arg3, s32 arg4, s32 arg5);
s16 fn_1_11114(AnimData *arg0, s16 arg1);
void fn_1_11900(ModelData *arg0, Mtx arg1);
float fn_1_121DC(float arg0, float arg1);
float fn_1_122F4(float arg0, float arg1, float arg2);
float fn_1_12544(float arg0, float arg1, float arg2);
void fn_1_1293C(Mtx arg0, Vec *arg1);
s32 fn_1_12C6C(Vec *arg0, Vec *arg1, float *arg2);
float fn_1_12E68(Vec *arg0, Vec *arg1, s32 arg2);
void fn_1_129F0(Vec *arg0, Vec *arg1, Vec *arg2, float *arg3);
void fn_1_1334C(float *arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4);
float fn_1_1367C(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, float *arg4);
s32 fn_1_137C4(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, float arg4, s32 arg5);

Process *lbl_1_bss_120;
s32 lbl_1_bss_11C;
s32 lbl_1_bss_118;
s32 lbl_1_bss_114;
s32 lbl_1_bss_110;
s32 lbl_1_bss_10C; // unused
s32 lbl_1_bss_108;
s32 lbl_1_bss_104;
s32 lbl_1_bss_100;
s32 lbl_1_bss_FC;
s32 lbl_1_bss_EC[4];
s32 lbl_1_bss_DC[4];
s32 lbl_1_bss_D8;
omObjData *lbl_1_bss_D4;
omObjData *lbl_1_bss_D0;
omObjData *lbl_1_bss_CC;
omObjData *lbl_1_bss_BC[4];
omObjData *lbl_1_bss_B8;
omObjData *lbl_1_bss_AC[3];
omObjData *lbl_1_bss_A8;
omObjData *lbl_1_bss_A4;
omObjData *lbl_1_bss_A0;
omObjData *lbl_1_bss_9C;
omObjData *lbl_1_bss_98;
StructBss94Data *lbl_1_bss_94;
s32 lbl_1_bss_90;
omObjData *lbl_1_bss_8C;
s32 lbl_1_bss_88;
s32 lbl_1_bss_84;
s32 lbl_1_bss_80;
s32 lbl_1_bss_7C;
StructBssA8Data *lbl_1_bss_40[15];
StructBssA8Data *lbl_1_bss_4[15];
s32 lbl_1_bss_0;

StructData0 lbl_1_data_0[]
    = { { { 342.45f, 0.0f, 0.0f }, { 0.0f, 275.0f, 128.0f }, 550.0f }, { { 6.0f, 0.0f, 0.0f }, { 0.0f, 190.0f, 0.0f }, 550.0f } };

StructData0 lbl_1_data_38[]
    = { { { 22.0f, 180.0f, 0.0f }, { -250.0f, 120.00001f, 0.0f }, 160.0f }, { { 22.0f, 180.0f, 0.0f }, { 0.0f, 120.00001f, 0.0f }, 160.0f },
          { { 22.0f, 180.0f, 0.0f }, { 250.0f, 120.00001f, 0.0f }, 160.0f }, { { -45.0f, 180.0f, 0.0f }, { -250.0f, 75.0f, 0.0f }, 180.0f },
          { { -45.0f, 180.0f, 0.0f }, { 0.0f, 75.0f, 0.0f }, 180.0f }, { { -45.0f, 180.0f, 0.0f }, { 250.0f, 75.0f, 0.0f }, 180.0f },
          { { -45.0f, 0.0f, 0.0f }, { -250.0f, 95.0f, 0.0f }, 150.0f }, { { -45.0f, 0.0f, 0.0f }, { 0.0f, 95.0f, 0.0f }, 150.0f },
          { { -45.0f, 0.0f, 0.0f }, { 250.0f, 95.0f, 0.0f }, 150.0f }, { { -45.0f, 0.0f, 0.0f }, { 0.0f, 95.0f, -850.0f }, 150.0f } };

Vec lbl_1_data_150[] = { 0.0f, 0.0f, -850.0f, -250.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 250.0f, 0.0f, 0.0f };

Vec lbl_1_data_180[] = { 0.0f, 0.0f, -850.0f, 850.0f, 0.0f, 0.0f, 1200.0f, 0.0f, 0.0f, 1650.0f, 0.0f, 0.0f };

Vec lbl_1_data_1B0[] = { { -250.0f, 45.0f, 500.0f }, { 0.0f, 45.0f, 500.0f }, { 250.0f, 45.0f, 500.0f } };

Vec lbl_1_data_1D4 = { 1000.0f, 2000.0f, 1000.0f };
Vec lbl_1_data_1E0 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_1EC = { 0.0f, 0.0f, -450.0f };

void ObjectSetup(void)
{
    Process *var_r30;
    CameraData *var_r29;
    s32 i;

    OSReport("******* M426ObjectSetup *********\n");
    var_r30 = omInitObjMan(50, 0x2000);
    lbl_1_bss_120 = var_r30;
    omGameSysInit(var_r30);
    fn_1_100DC();
    Hu3DLightAllKill();
    Hu3DLighInit();
    HuAudSndGrpSet(0x30);
    lbl_1_bss_D4 = omAddObjEx(var_r30, 0xFF, 2, 0, -1, fn_1_318);
    lbl_1_bss_11C = lbl_1_bss_118 = -1;
    lbl_1_bss_D0 = NULL;
    lbl_1_bss_CC = NULL;
    lbl_1_bss_A8 = NULL;
    lbl_1_bss_B8 = NULL;
    lbl_1_bss_AC[0] = lbl_1_bss_AC[1] = lbl_1_bss_AC[2] = NULL;
    lbl_1_bss_114 = 0;
    lbl_1_bss_110 = 0;
    lbl_1_bss_108 = 0;
    lbl_1_bss_104 = 10;
    lbl_1_bss_100 = -1;
    lbl_1_bss_FC = 0;
    lbl_1_bss_90 = -1;
    lbl_1_bss_D8 = -1;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_DC[i] = 0;
        lbl_1_bss_EC[i] = -1;
    }
    Hu3DShadowCreate(30.0f, 1000.0f, 250000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_data_1D4, &lbl_1_data_1E0, &lbl_1_data_1EC);
    for (i = 0; i < 3; i++) {
        var_r29 = &Hu3DCamera[i];
        var_r29->fov = -1.0f;
    }
}

Vec lbl_1_data_21C = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_228 = { -1.0f, -2.0f, -1.0f };
GXColor lbl_1_data_234 = { 0xFF, 0xFF, 0xFF, 0xFF };

void fn_1_318(omObjData *arg0)
{
    s32 var_r31;

    var_r31 = Hu3DGLightCreateV(&lbl_1_data_21C, &lbl_1_data_228, &lbl_1_data_234);
    Hu3DGLightStaticSet(var_r31, 1);
    Hu3DGLightInfinitytSet(var_r31);
    fn_1_F10();
    fn_1_34D8();
    fn_1_3BFC();
    fn_1_95C4();
    fn_1_D930();
    fn_1_E1BC();
    fn_1_E460();
    fn_1_F690();
    HuAudFXPlay(0x618);
    arg0->func = fn_1_3B0;
}

s32 lbl_1_data_238[] = { 0, 4, 2, 3, 1, 5 };
s32 lbl_1_data_250[] = {
    3.1 * REFRESH_RATE, 3.1 * REFRESH_RATE, 3.1 * REFRESH_RATE,
    4 * REFRESH_RATE, 4 * REFRESH_RATE, 4 * REFRESH_RATE
};

void fn_1_3B0(omObjData *arg0)
{
    CameraData *var_r28;
    float var_f31;
    s32 temp_r27;
    s32 var_r30;
    s32 var_r29;
    s32 i;

    switch (lbl_1_bss_114) {
        case 0:
            fn_1_10540(2, 1, 1, 0.0f);
            if (++lbl_1_bss_110 > 3) {
                for (i = 0; i < 3; i++) {
                    var_r28 = &Hu3DCamera[i];
                    var_r28->fov = 45.0f;
                }
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                lbl_1_bss_114 = 1;
                lbl_1_bss_110 = 0;
            }
            break;
        case 1:
            fn_1_10540(2, 1, 1, 0.0f);
            if (WipeStatGet() == 0) {
                lbl_1_bss_114 = 2;
                lbl_1_bss_110 = 0;
            }
            break;
        case 2:
            if (++lbl_1_bss_110 >= REFRESH_RATE_F / 2) {
                lbl_1_bss_114 = 3;
                lbl_1_bss_110 = 0;
            }
            break;
        case 3:
            var_f31 = lbl_1_bss_110 / (REFRESH_RATE_F * 1.5f);
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            var_f31 = sind(90.0f * var_f31);
            var_f31 *= var_f31;
            fn_1_10540(2, 1, 0, var_f31);
            if (++lbl_1_bss_110 >= (REFRESH_RATE_F * 1.5f)) {
                lbl_1_bss_114 = 4;
                lbl_1_bss_110 = 0;
            }
            break;
        case 4:
            if (fn_1_781C() != 0) {
                lbl_1_bss_11C = MGSeqStartCreate();
                lbl_1_bss_114 = 5;
                lbl_1_bss_110 = 0;
            }
            break;
        case 5:
            if (lbl_1_bss_11C != -1) {
                var_r30 = MGSeqStatGet(lbl_1_bss_11C);
                if ((var_r30 & 0x10) && lbl_1_bss_D8 == -1) {
                    lbl_1_bss_D8 = HuAudSeqPlay(0x46);
                }
            }
            else {
                var_r30 = 0;
            }
            if (lbl_1_bss_11C == -1 || var_r30 == 0) {
                lbl_1_bss_11C = -1;
                lbl_1_bss_114 = 6;
                lbl_1_bss_110 = 0;
                lbl_1_bss_108 = REFRESH_RATE * 30;
                fn_1_10028(1);
                lbl_1_bss_118 = MGSeqTimerCreate(lbl_1_bss_108 / REFRESH_RATE);
            }
            break;
        case 6:
            temp_r27 = lbl_1_data_238[lbl_1_bss_0];
            fn_1_106D8(temp_r27);
            if (lbl_1_bss_80 >= lbl_1_data_250[temp_r27] && ++lbl_1_bss_0 > 5) {
                lbl_1_bss_0 = 0;
            }
            var_r29 = (lbl_1_bss_108 + REFRESH_RATE - 1) / REFRESH_RATE;
            if (var_r29 < 0) {
                var_r29 = 0;
            }
            MGSeqParamSet(lbl_1_bss_118, 1, var_r29);
            if (--lbl_1_bss_108 < -1 || lbl_1_bss_104 <= 0) {
                MGSeqParamSet(lbl_1_bss_118, 2, -1);
                lbl_1_bss_118 = -1;
                fn_1_B1A4();
                if (lbl_1_bss_D8 != -1) {
                    HuAudSeqFadeOut(lbl_1_bss_D8, 100);
                }
                lbl_1_bss_11C = MGSeqFinishCreate();
                lbl_1_bss_114 = 7;
                lbl_1_bss_110 = 0;
            }
            break;
        case 7:
            if (fn_1_791C() != 0 && (lbl_1_bss_11C == -1 || MGSeqStatGet(lbl_1_bss_11C) == 0)) {
                lbl_1_bss_114 = 9;
                lbl_1_bss_110 = 0;
            }
            break;
        case 9:
            if (lbl_1_bss_104 <= 0) {
                lbl_1_bss_11C = MGSeqWinCreate(lbl_1_bss_EC[0], lbl_1_bss_EC[1], lbl_1_bss_EC[2], -1);
                fn_1_7AA8(1);
                for (i = 0; i < 4; i++) {
                    if (lbl_1_bss_EC[3] != GWPlayerCfg[i].character) {
                        GWPlayerCoinWinAdd(i, 10);
                    }
                }
                if (lbl_1_bss_DC[0] > lbl_1_bss_DC[1] && lbl_1_bss_DC[0] > lbl_1_bss_DC[2]) {
                    i = 0;
                }
                else if (lbl_1_bss_DC[1] > lbl_1_bss_DC[0] && lbl_1_bss_DC[1] > lbl_1_bss_DC[2]) {
                    i = 1;
                }
                else if (lbl_1_bss_DC[2] > lbl_1_bss_DC[0] && lbl_1_bss_DC[2] > lbl_1_bss_DC[1]) {
                    i = 2;
                }
                else {
                    i = frand() & 3;
                    if (i > 2) {
                        i = 2;
                    }
                    else if (i < 0) {
                        i = 0;
                    }
                }
                fn_1_106D8(i + 6);
                lbl_1_bss_114 = 10;
                lbl_1_bss_108 = 0;
            }
            else {
                lbl_1_bss_11C = MGSeqWinCreate(lbl_1_bss_EC[3], -1, -1, -1);
                fn_1_7AA8(0);
                for (i = 0; i < 4; i++) {
                    if (lbl_1_bss_EC[3] == GWPlayerCfg[i].character) {
                        GWPlayerCoinWinAdd(i, 10);
                    }
                }
                fn_1_106D8(9);
                lbl_1_bss_114 = 10;
                lbl_1_bss_108 = 0;
            }
            HuAudSStreamPlay(1);
            HuAudFXPlay(0x618);
            break;
        case 10:
            fn_1_3A8C();
            if (++lbl_1_bss_108 >= REFRESH_RATE_F * 3.5f) {
                lbl_1_bss_11C = -1;
                lbl_1_bss_114 = 11;
                lbl_1_bss_108 = 0;
            }
            break;
        case 11:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            arg0->func = fn_1_DFC;
            break;
    }
    fn_1_E60(arg0);
}

void fn_1_DFC(omObjData *arg0)
{
    if (WipeStatGet() == 0) {
        fn_1_1238();
        fn_1_3A64();
        fn_1_77D0();
        fn_1_A9AC();
        fn_1_DBC8();
        fn_1_E330();
        fn_1_E60C();
        fn_1_FF98();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_E60(omObjData *arg0)
{
    s32 var_r30;

    var_r30 = 0;
    if (WipeStatGet() != 0 || arg0->func == fn_1_DFC) {
        return;
    }
    if (omSysExitReq != 0) {
        var_r30 = 1;
    }
    if (var_r30 != 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        HuAudStreamFadeOut(30);
        arg0->func = fn_1_DFC;
    }
}

s32 fn_1_F00(void)
{
    return lbl_1_bss_114;
}

void fn_1_F10(void)
{
    lbl_1_bss_D0 = omAddObjEx(lbl_1_bss_120, 0x7F, 8, 0, -1, fn_1_F60);
}

void fn_1_F60(omObjData *arg0)
{
    StructBssD0Data *temp_r30;
    ModelData *temp_r29;

    temp_r30 = arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r30), MEMORY_DEFAULT_NUM);
    memset(temp_r30, 0, sizeof(*temp_r30));
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M423, 0));
    Hu3DModelCameraSet(arg0->model[0], 5);
    Hu3DModelShadowMapSet(arg0->model[0]);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M423, 1));
    Hu3DModelCameraSet(arg0->model[1], 5);
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M423, 2));
    Hu3DModelScaleSet(arg0->model[2], 1.125f, 1.0f, 1.0f);
    Hu3DModelCameraSet(arg0->model[2], 5);
    Hu3DModelShadowSet(arg0->model[2]);
    arg0->model[3] = Hu3DHookFuncCreate(fn_1_12A0);
    Hu3DModelCameraSet(arg0->model[3], 2);
    temp_r29 = &Hu3DData[arg0->model[3]];
    temp_r29->unk_120 = temp_r30;
    temp_r30->unk00 = 160;
    temp_r30->unk04 = 160;
    temp_r30->unk08 = GXGetTexBufferSize(temp_r30->unk00, temp_r30->unk04, 5, 0, 0);
    temp_r30->unk10 = HuMemDirectMallocNum(HEAP_DATA, temp_r30->unk08, (u32)temp_r29->unk_48);
    temp_r30->unk0C = 0.0f;
    arg0->model[4] = fn_1_13A0(temp_r30);
    Hu3DModelCameraSet(arg0->model[4], 5);
    Hu3DModelPosSet(arg0->model[4], 0.0f, 200.0f, -1700.0f);
    arg0->model[5] = fn_1_18FC();
    Hu3DModelCameraSet(arg0->model[5], 4);
    arg0->func = fn_1_11A4;
}

void fn_1_11A4(omObjData *arg0)
{
    fn_1_2C08(arg0->model[5]);
}

void fn_1_11D8(omObjData *arg0)
{
    fn_1_1444(arg0->model[4]);
    arg0->model[4] = -1;
    fn_1_29B8(arg0->model[5]);
    arg0->model[5] = -1;
    arg0->func = NULL;
}

void fn_1_1238(void)
{
    fn_1_11D8(lbl_1_bss_D0);
}

GXColor lbl_1_data_298 = { 0x00, 0x00, 0x00, 0xFF };

void fn_1_12A0(ModelData *arg0, Mtx arg1)
{
    StructBssD0Data *temp_r31;
    CameraData *var_r30;

    temp_r31 = arg0->unk_120;
    var_r30 = &Hu3DCamera[1];
    if (var_r30->fov <= 0.0f) {
        return;
    }
    GXSetTexCopySrc(0, 0, 320, 240);
    GXSetTexCopyDst(temp_r31->unk00, temp_r31->unk04, GX_TF_RGB5A3, GX_TRUE);
    GXSetCopyClear(lbl_1_data_298, 0xFFFFFF);
    GXCopyTex(temp_r31->unk10, GX_TRUE);
    DCFlushRange(temp_r31->unk10, temp_r31->unk08);
    GXPixModeSync();
    temp_r31->unk0C = 1;
    fn_1_10BC8();
}

s32 fn_1_13A0(StructBssD0Data *arg0)
{
    StructM423_00 *var_r31;
    ModelData *temp_r30;
    s32 var_r29;

    var_r29 = Hu3DHookFuncCreate(fn_1_14A0);
    temp_r30 = &Hu3DData[var_r29];
    var_r31 = temp_r30->unk_120 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r31), temp_r30->unk_48);
    memset(var_r31, 0, sizeof(*var_r31));
    var_r31->unk00 = arg0;
    var_r31->unk04 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M423, 21), MEMORY_DEFAULT_NUM));
    return var_r29;
}

void fn_1_1444(s32 arg0)
{
    StructM423_00 *var_r31;
    ModelData *var_r30;

    if (arg0 >= 0) {
        var_r30 = &Hu3DData[arg0];
        var_r31 = var_r30->unk_120;
        HuSprAnimKill(var_r31->unk04);
    }
}

f32 lbl_1_data_29C[] = { -400.0f, 400.0f, 0.0f, 400.0f, 400.0f, 0.0f, 400.0f, 0.0f, 0.0f, -400.0f, 0.0f, 0.0f };

f32 lbl_1_data_2CC[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.75f, 0.0f, 0.75f };

f32 lbl_1_data_2EC[] = { 0.0f, 0.0f, 1.2f, 0.0f, 1.2f, 0.75f, 0.0f, 0.75f };

GXColor lbl_1_data_30C[] = { { 0x40, 0x40, 0x40, 0xFF } };

GXColor lbl_1_data_310 = { 0x00, 0x00, 0x00, 0x80 };

void fn_1_14A0(ModelData *arg0, Mtx arg1)
{
    CameraData *var_r28;
    StructM423_00 *temp_r29;
    StructBssD0Data *temp_r30;
    Mtx spC;
    s16 i;

    var_r28 = &Hu3DCamera[2];
    temp_r29 = arg0->unk_120;
    temp_r30 = temp_r29->unk00;
    if (temp_r30->unk0C != 0) {
        if (var_r28->fov <= 0.0f) {
            return;
        }
        GXLoadPosMtxImm(arg1, GX_PNMTX0);
        MTXInvXpose(arg1, spC);
        GXLoadNrmMtxImm(spC, GX_PNMTX0);
        GXSetTevColor(GX_TEVREG2, lbl_1_data_310);
        GXSetNumTevStages(2);
        GXSetNumTexGens(2);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        if (Hu3DCameraNo != 0) {
            GXSetTevOp(GX_TEVSTAGE1, GX_REPLACE);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_C2, GX_CC_TEXA, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
        else {
            GXSetTevOp(GX_TEVSTAGE1, GX_REPLACE);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        fn_1_11008(temp_r30, temp_r30->unk10, GX_TEXMAP0, GX_CLAMP, 0, 1);
        HuSprTexLoad(temp_r29->unk04, 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(GX_FALSE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetArray(GX_VA_POS, lbl_1_data_29C, 12);
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetArray(GX_VA_CLR0, lbl_1_data_30C, 4);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetArray(GX_VA_TEX0, lbl_1_data_2CC, 8);
        GXSetVtxDesc(GX_VA_TEX1, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
        GXSetArray(GX_VA_TEX1, lbl_1_data_2EC, 8);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        for (i = 0; i < 4; i++) {
            GXPosition1x16(i);
            GXColor1x16(0);
            GXTexCoord1x16(i);
            GXTexCoord1x16(i);
        }
        GXEnd();
    }
}

s32 lbl_1_data_314[][2] = { { 20, 10 }, { 20, 7 }, { 10, 10 }, { 10, 10 } };

Vec lbl_1_data_334[] = { { 0.0f, 100.0f, -1100.0f }, { 0.0f, 200.0f, -1000.0f }, { -225.0f, 100.0f, -1000.0f }, { 225.0f, 100.0f, -1000.0f } };

s32 fn_1_18FC(void)
{
    ModelData *temp_r30;
    StructM423_03 *var_r29;
    StructM423_02 *temp_r31;
    s32 var_r27;
    s32 i;

    var_r27 = Hu3DHookFuncCreate(fn_1_29BC);
    temp_r30 = &Hu3DData[var_r27];
    var_r29 = temp_r30->unk_120 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r29), temp_r30->unk_48);
    memset(var_r29, 0, sizeof(*var_r29));
    var_r29->unk00 = var_r27;
    var_r29->unk02 = 4;
    temp_r31 = var_r29->unk04 = HuMemDirectMallocNum(HEAP_DATA, var_r29->unk02 * sizeof(*temp_r31), temp_r30->unk_48);
    memset(temp_r31, 0, var_r29->unk02 * sizeof(*temp_r31));
    for (i = 0; i < var_r29->unk02; i++) {
        temp_r31 = &var_r29->unk04[i];
        temp_r31->unk02 = lbl_1_data_314[i][0];
        temp_r31->unk04 = lbl_1_data_314[i][1];
        temp_r31->unk00 = temp_r31->unk02 * temp_r31->unk04;
        temp_r31->unk08 = lbl_1_data_334[i];
        temp_r31->unk14 = HuMemDirectMallocNum(HEAP_DATA, temp_r31->unk00 * sizeof(*temp_r31->unk14), temp_r30->unk_48);
        memset(temp_r31->unk14, 0, temp_r31->unk00 * sizeof(*temp_r31->unk14));
        temp_r31->unk18 = HuMemDirectMallocNum(HEAP_DATA, temp_r31->unk00 * sizeof(*temp_r31->unk18), temp_r30->unk_48);
        memset(temp_r31->unk18, 0, temp_r31->unk00 * sizeof(*temp_r31->unk18));
        temp_r31->unk1C = HuMemDirectMallocNum(HEAP_DATA, temp_r31->unk00 * sizeof(*temp_r31->unk1C), temp_r30->unk_48);
        memset(temp_r31->unk1C, 0, temp_r31->unk00 * sizeof(*temp_r31->unk1C));
        temp_r31->unk20 = HuMemDirectMallocNum(HEAP_DATA, temp_r31->unk00 * sizeof(*temp_r31->unk20), temp_r30->unk_48);
        memset(temp_r31->unk20, 0, temp_r31->unk00 * sizeof(*temp_r31->unk20));
        switch (i) {
            case 0:
                fn_1_1B5C(temp_r30, temp_r31);
                break;
            case 1:
                fn_1_1F5C(temp_r30, temp_r31);
                break;
            case 2:
                fn_1_2290(temp_r30, temp_r31);
                break;
            default:
                fn_1_2624(temp_r30, temp_r31);
                break;
        }
    }
    return var_r27;
}

Vec lbl_1_data_364[] = { { -200.0f, 0.0f, -1100.0f }, { -200.0f, 200.0f, -1050.0f }, { 200.0f, 200.0f, -1050.0f } };

GXColor lbl_1_data_388 = { 0xFF, 0xFF, 0xFF, 0xFF };

void fn_1_1B5C(ModelData *arg0, StructM423_02 *arg1)
{
    float var_f31;
    float var_f30;
    float var_f29;
    Vec *var_r27;
    GXColor *var_r26;
    StructM423_01 *var_r28;
    void *var_r25;
    void *var_r23;
    s32 i;
    s32 j;

    var_r27 = arg1->unk14;
    var_r26 = arg1->unk1C;
    var_r28 = arg1->unk20;
    for (i = 0; i < 10; i++) {
        var_f30 = 200.0f * (i / 9.0f);
        var_f29 = -1100.0f + 50.0f * (i / 9.0f);
        for (j = 0; j < 20; var_r27++, var_r26++, var_r28++, j++) {
            var_f31 = -225.0f + 450.0f * (j / 19.0f);
            var_r27->x = var_f31;
            var_r27->y = var_f30;
            var_r27->z = var_f29;
            *var_r26 = lbl_1_data_388;
            var_r28->unk00 = j;
            var_r28->unk02 = i;
            if (i == 0 || i == 9 || j == 0 || j == 19) {
                var_r28->unk04 = 1;
            }
            else {
                var_r28->unk04 = 0;
            }
            var_r28->unk06 = 0;
            var_r28->unk08.x = var_r28->unk08.y = var_r28->unk08.z = 0.0f;
        }
    }
    memcpy(arg1->unk18, arg1->unk14, arg1->unk00 * sizeof(*arg1->unk14));
    DCFlushRangeNoSync(arg1->unk14, arg1->unk00 * sizeof(*arg1->unk14));
    DCFlushRangeNoSync(arg1->unk1C, arg1->unk00 * sizeof(*arg1->unk1C));
    PPCSync();
    var_r23 = var_r25 = HuMemDirectMallocNum(HEAP_DATA, 0x10000, arg0->unk_48);
    DCFlushRange(var_r25, 0x10000);
    GXBeginDisplayList(var_r23, 0x10000);
    GXBegin(GX_LINES, GX_VTXFMT0, 9 * 19 * 4);
    for (i = 1; i < 10; i++) {
        for (j = 1; j < 20; j++) {
            GXPosition1x16(i * 20 + j);
            GXColor1x16(i * 20 + j);

            GXPosition1x16(i * 20 + (j - 1));
            GXColor1x16(i * 20 + (j - 1));

            GXPosition1x16(i * 20 + j);
            GXColor1x16(i * 20 + j);

            GXPosition1x16((i - 1) * 20 + j);
            GXColor1x16((i - 1) * 20 + j);
        }
    }
    GXEnd();
    arg1->unk34 = GXEndDisplayList();
    if (arg1->unk34 >= 0x10000) {
        OSReport("ERROR! GList test size over! \n");
    }
    arg1->unk38 = HuMemDirectMallocNum(HEAP_DATA, arg1->unk34, arg0->unk_48);
    memcpy(arg1->unk38, var_r25, arg1->unk34);
    DCFlushRange(arg1->unk38, arg1->unk34);
    HuMemDirectFree(var_r25);
    fn_1_129F0(&lbl_1_data_364[0], &lbl_1_data_364[1], &lbl_1_data_364[2], arg1->unk24);
}

GXColor lbl_1_data_3AB = { 0xFF, 0xFF, 0xFF, 0xFF };

void fn_1_1F5C(ModelData *arg0, StructM423_02 *arg1)
{
    float var_f31;
    float var_f30;
    float var_f29;
    Vec *var_r27;
    GXColor *var_r26;
    void *var_r25;
    void *var_r23;
    s32 i;
    s32 j;

    var_r27 = arg1->unk14;
    var_r26 = arg1->unk1C;
    for (i = 0; i < 7; i++) {
        var_f30 = 200.0f;
        var_f29 = -900.0f - 150.0f * (i / 6.0f);
        for (j = 0; j < 20; var_r27++, var_r26++, j++) {
            var_f31 = -225.0f + 450.0f * (j / 19.0f);
            var_r27->x = var_f31;
            var_r27->y = var_f30;
            var_r27->z = var_f29;
            *var_r26 = lbl_1_data_3AB;
        }
    }
    memcpy(arg1->unk18, arg1->unk14, arg1->unk00 * sizeof(*arg1->unk14));
    DCFlushRangeNoSync(arg1->unk14, arg1->unk00 * sizeof(*arg1->unk14));
    DCFlushRangeNoSync(arg1->unk1C, arg1->unk00 * sizeof(*arg1->unk1C));
    PPCSync();
    var_r23 = var_r25 = HuMemDirectMallocNum(HEAP_DATA, 0x10000, arg0->unk_48);
    DCFlushRange(var_r25, 0x10000);
    GXBeginDisplayList(var_r23, 0x10000);
    GXBegin(GX_LINES, GX_VTXFMT0, 6 * 19 * 4);
    for (i = 1; i < 7; i++) {
        for (j = 1; j < 20; j++) {
            GXPosition1x16(i * 20 + j);
            GXColor1x16(i * 20 + j);

            GXPosition1x16(i * 20 + (j - 1));
            GXColor1x16(i * 20 + (j - 1));

            GXPosition1x16(i * 20 + j);
            GXColor1x16(i * 20 + j);

            GXPosition1x16((i - 1) * 20 + j);
            GXColor1x16((i - 1) * 20 + j);
        }
    }
    GXEnd();
    arg1->unk34 = GXEndDisplayList();
    if (arg1->unk34 >= 0x10000) {
        OSReport("ERROR! GList test size over! \n");
    }
    arg1->unk38 = HuMemDirectMallocNum(HEAP_DATA, arg1->unk34, arg0->unk_48);
    memcpy(arg1->unk38, var_r25, arg1->unk34);
    DCFlushRange(arg1->unk38, arg1->unk34);
    HuMemDirectFree(var_r25);
}

GXColor lbl_1_data_3AF = { 0xFF, 0xFF, 0xFF, 0xFF };

void fn_1_2290(ModelData *arg0, StructM423_02 *arg1)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    Vec *var_r27;
    GXColor *var_r26;
    void *var_r25;
    void *var_r23;
    s32 i;
    s32 j;

    var_r27 = arg1->unk14;
    var_r26 = arg1->unk1C;
    for (i = 0; i < 10; i++) {
        var_f28 = 200.0f * (i / 9.0f);
        var_f29 = -225.0f;
        var_f30 = -1100.0f + 50.0f * (i / 9.0f);
        for (j = 0; j < 10; var_r27++, var_r26++, j++) {
            var_f31 = -900.0f - 200.0f * (j / 9.0f);
            if (var_f31 < var_f30) {
                var_f31 = var_f30;
            }
            var_r27->x = var_f29;
            var_r27->y = var_f28;
            var_r27->z = var_f31;
            *var_r26 = lbl_1_data_3AF;
        }
    }
    memcpy(arg1->unk18, arg1->unk14, arg1->unk00 * sizeof(*arg1->unk14));
    DCFlushRangeNoSync(arg1->unk14, arg1->unk00 * sizeof(*arg1->unk14));
    DCFlushRangeNoSync(arg1->unk1C, arg1->unk00 * sizeof(*arg1->unk1C));
    PPCSync();
    var_r23 = var_r25 = HuMemDirectMallocNum(HEAP_DATA, 0x10000, arg0->unk_48);
    DCFlushRangeNoSync(var_r25, 0x10000);
    GXBeginDisplayList(var_r23, 0x10000);
    GXBegin(GX_LINES, GX_VTXFMT0, 9 * 9 * 4);
    for (i = 1; i < 10; i++) {
        for (j = 1; j < 10; j++) {
            GXPosition1x16(i * 10 + j);
            GXColor1x16(i * 10 + j);

            GXPosition1x16(i * 10 + (j - 1));
            GXColor1x16(i * 10 + (j - 1));

            GXPosition1x16(i * 10 + j);
            GXColor1x16(i * 10 + j);

            GXPosition1x16((i - 1) * 10 + j);
            GXColor1x16((i - 1) * 10 + j);
        }
    }
    GXEnd();
    arg1->unk34 = GXEndDisplayList();
    if (arg1->unk34 >= 0x10000) {
        OSReport("ERROR! GList test size over! \n");
    }
    arg1->unk38 = HuMemDirectMallocNum(HEAP_DATA, arg1->unk34, arg0->unk_48);
    memcpy(arg1->unk38, var_r25, arg1->unk34);
    DCFlushRange(arg1->unk38, arg1->unk34);
    HuMemDirectFree(var_r25);
}

GXColor lbl_1_data_3B3 = { 0xFF, 0xFF, 0xFF, 0xFF };

void fn_1_2624(ModelData *arg0, StructM423_02 *arg1)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    Vec *var_r27;
    GXColor *var_r26;
    void *var_r25;
    void *var_r23;
    s32 i;
    s32 j;

    var_r27 = arg1->unk14;
    var_r26 = arg1->unk1C;
    for (i = 0; i < 10; i++) {
        var_f28 = 200.0f * (i / 9.0f);
        var_f29 = 225.0f;
        var_f30 = -1100.0f + 50.0f * (i / 9.0f);
        for (j = 0; j < 10; var_r27++, var_r26++, j++) {
            var_f31 = -900.0f - 200.0f * (j / 9.0f);
            if (var_f31 < var_f30) {
                var_f31 = var_f30;
            }
            var_r27->x = var_f29;
            var_r27->y = var_f28;
            var_r27->z = var_f31;
            *var_r26 = lbl_1_data_3B3;
        }
    }
    memcpy(arg1->unk18, arg1->unk14, arg1->unk00 * sizeof(*arg1->unk14));
    DCFlushRangeNoSync(arg1->unk14, arg1->unk00 * sizeof(*arg1->unk14));
    DCFlushRangeNoSync(arg1->unk1C, arg1->unk00 * sizeof(*arg1->unk1C));
    PPCSync();
    var_r23 = var_r25 = HuMemDirectMallocNum(HEAP_DATA, 0x10000, arg0->unk_48);
    DCFlushRange(var_r25, 0x10000);
    GXBeginDisplayList(var_r23, 0x10000);
    GXBegin(GX_LINES, GX_VTXFMT0, 9 * 9 * 4);
    for (i = 1; i < 10; i++) {
        for (j = 1; j < 10; j++) {
            GXPosition1x16(i * 10 + j);
            GXColor1x16(i * 10 + j);

            GXPosition1x16(i * 10 + (j - 1));
            GXColor1x16(i * 10 + (j - 1));

            GXPosition1x16(i * 10 + j);
            GXColor1x16(i * 10 + j);

            GXPosition1x16((i - 1) * 10 + j);
            GXColor1x16((i - 1) * 10 + j);
        }
    }
    GXEnd();
    arg1->unk34 = GXEndDisplayList();
    if (arg1->unk34 >= 0x10000) {
        OSReport("ERROR! GList test size over! \n");
    }
    arg1->unk38 = HuMemDirectMallocNum(HEAP_DATA, arg1->unk34, arg0->unk_48);
    memcpy(arg1->unk38, var_r25, arg1->unk34);
    DCFlushRange(arg1->unk38, arg1->unk34);
    HuMemDirectFree(var_r25);
}

void fn_1_29B8(s32 arg0) { }

void fn_1_29BC(ModelData *arg0, Mtx arg1)
{
    StructM423_03 *temp_r30;
    StructM423_02 *temp_r31;
    Mtx sp8;
    s16 i;

    temp_r30 = arg0->unk_120;
    GXLoadPosMtxImm(arg1, GX_PNMTX0);
    MTXInvXpose(arg1, sp8);
    GXLoadNrmMtxImm(sp8, GX_PNMTX0);
    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    for (i = 0; i < temp_r30->unk02; i++) {
        temp_r31 = &temp_r30->unk04[i];
        if (temp_r31->unk38 && temp_r31->unk34 != 0) {
            DCFlushRangeNoSync(temp_r31->unk14, temp_r31->unk00 * sizeof(*temp_r31->unk14));
            DCFlushRangeNoSync(temp_r31->unk1C, temp_r31->unk00 * sizeof(*temp_r31->unk1C));
            PPCSync();
            GXSetArray(GX_VA_POS, temp_r31->unk14, sizeof(*temp_r31->unk14));
            GXSetArray(GX_VA_CLR0, temp_r31->unk1C, sizeof(*temp_r31->unk1C));
            GXCallDisplayList(temp_r31->unk38, temp_r31->unk34);
        }
    }
}

void fn_1_2C08(s32 arg0)
{
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec *var_r25;
    Vec *var_r24;
    Vec *temp_r27;
    Vec *temp_r29;
    float temp_f31;
    float temp_f28;
    float temp_f30;
    float var_f29;
    float var_f27;
    StructM423_02 *temp_r30;
    StructM423_01 *var_r28;
    StructBssA8Data *var_r31;
    StructM423_03 *var_r17;
    ModelData *sp20;
    ModelData *sp1C;
    StructM423_01 *sp18;
    s32 var_r20;
    s32 temp_r19;
    s32 temp_r18;
    s32 i;
    s32 j;
    s32 k;
    s32 temp_r21;
    s32 sp14;
    s32 sp10;
    s32 spC;
    Mtx sp48;

    sp20 = &Hu3DData[arg0];
    var_r17 = sp20->unk_120;
    temp_r30 = var_r17->unk04;
    var_r25 = temp_r30->unk14;
    var_r24 = temp_r30->unk18;
    var_r28 = temp_r30->unk20;
    if (lbl_1_bss_A8 == NULL) {
        return;
    }
    var_r31 = lbl_1_bss_A8->data;
    for (i = 0; i < temp_r30->unk00; i++, var_r25++, var_r24++, var_r28++) {
        if (var_r28->unk04 != 0) {
            continue;
        }
        VECSubtract(var_r24, var_r25, &sp30);
        temp_f31 = VECMag(&sp30);
        if (temp_f31 >= 0.0f) {
            VECScale(&sp30, &sp30, 0.05f);
            VECAdd(&var_r28->unk08, &sp30, &var_r28->unk08);
            temp_f31 = VECMag(&var_r28->unk08);
            if (temp_f31 > 10.0f) {
                VECNormalize(&var_r28->unk08, &var_r28->unk08);
                VECScale(&var_r28->unk08, &var_r28->unk08, 10.0f);
            }
        }
        VECAdd(var_r25, &var_r28->unk08, var_r25);
        VECScale(&var_r28->unk08, &var_r28->unk08, 0.5f);
    }
    for (i = 0; i < 15; i++, var_r31++) {
        if (var_r31->unk06 == 0 || var_r31->unk0C != 3) {
            continue;
        }
        spC = 0;
        VECSubtract(&var_r31->unk38, &var_r31->unk74, &sp30);
        if (var_r31->unk38.x > -225.0f && var_r31->unk38.x < 225.0f && var_r31->unk38.y > 0.0f && var_r31->unk38.y < 200.0f
            && var_r31->unk38.z > -1150.0f && var_r31->unk38.z < -950.0f) {
            var_f27 = 0.005f * var_r31->unk38.y;
            var_f29 = -900.0f - (150.0f + var_f27 * 50.0f);
            if (var_r31->unk38.z - 20.0 < var_f29) {
                if (var_r31->unk38.z < 20.0 + (var_f29 - 75.0f)) {
                    var_r31->unk38.z = 20.0 + (var_f29 - 75.0f);
                }
                spC = 1;
            }
        }
        if (spC != 0) {
            if (var_r31->unk0A == 0 && var_r31->unk08 == 0) {
                fn_1_AEE8(i);
            }
            if (var_r31->unk10 == 0) {
                var_r31->unk5C = var_r31->unk50;
                var_r31->unk10 = 1;
            }
            sp1C = &Hu3DData[var_r31->unk00];
            sp24.x = var_r31->unk5C.z;
            sp24.z = -var_r31->unk5C.x;
            sp24.y = 0.0f;
            temp_f31 = 0.05 * VECMag(&sp24);
            if (temp_f31 > 0.00001f) {
                MTXRotAxisRad(sp48, &sp24, temp_f31);
                MTXConcat(sp48, sp1C->unk_F0, sp1C->unk_F0);
            }
            temp_f31 = 0.0133333336f * fabs(var_f29 - (var_r31->unk38.z - 20.0));
            var_r31->unk50.z += temp_f31 * 0.4f;
            VECScale(&var_r31->unk50, &var_r31->unk50, 0.95f);
            var_r31->unk50.y *= 0.0f;
            var_r31->unk50.x *= 0.75f;
            sp14 = (var_r31->unk38.x - -225.0f) / 22.5f;
            sp10 = var_r31->unk38.y / 20.0f;
            var_r20 = sp14 + sp10 * temp_r30->unk02;
            var_r25 = &temp_r30->unk14[var_r20];
            var_r24 = &temp_r30->unk18[var_r20];
            var_r28 = &temp_r30->unk20[var_r20];
            temp_f28 = var_r24->z - (var_r31->unk38.z - 20.0);
            sp3C = var_r31->unk38;
            if (temp_f28 < 0.0f) {
                continue;
            }
            for (j = -19; j < 20; j++) {
                for (k = -19; k < 20; k++) {
                    temp_r19 = sp14 + k;
                    temp_r18 = sp10 + j;
                    temp_r21 = temp_r19 + temp_r18 * temp_r30->unk02;
                    if (temp_r19 < 0 || temp_r19 >= temp_r30->unk02 || temp_r18 < 0 || temp_r18 >= temp_r30->unk04 || temp_r21 >= temp_r30->unk00) {
                        continue;
                    }
                    sp18 = &temp_r30->unk20[temp_r21];
                    if (sp18->unk04 != 0) {
                        continue;
                    }
                    temp_r29 = &temp_r30->unk14[temp_r21];
                    temp_r27 = &temp_r30->unk18[temp_r21];
                    VECSubtract(&sp3C, temp_r29, &sp30);
                    sp30.z = 0.0f;
                    temp_f31 = VECMag(&sp30);
                    if (temp_f31 > 400.0f) {
                        continue;
                    }
                    if (temp_f31 > 20.0) {
                        temp_f30 = 0.0025f * (400.0f - temp_f31);
                        temp_f30 = temp_f30 * temp_f30;
                        VECNormalize(&sp30, &sp30);
                        VECScale(&sp30, &sp30, 20.0f * (temp_f30 * temp_f30));
                        temp_r29->x += 0.5f * (temp_r27->x + sp30.x - temp_r29->x);
                        temp_r29->y += 0.5f * (temp_r27->y + sp30.y - temp_r29->y);
                        temp_r29->z += 0.5f * (temp_r27->z - temp_f30 * temp_f28 - temp_r29->z);
                    }
                    else {
                        temp_f30 = cosd(0.0025f * temp_f31 * 90.0f);
                        if (temp_f31 != 0.0f) {
                            VECNormalize(&sp30, &sp30);
                        }
                        else {
                            sp30.x = sp30.y = sp30.z = 0.0f;
                        }
                        VECScale(&sp30, &sp30, temp_f30 * temp_f30 * 20.0f);
                        temp_r29->z += 0.5f * (temp_r27->z - temp_f30 * temp_f28 - temp_r29->z);
                    }
                }
            }
        }
        else {
            var_r31->unk10 = 0;
        }
    }
    DCFlushRangeNoSync(temp_r30->unk14, temp_r30->unk00 * sizeof(*temp_r30->unk14));
    PPCSync();
}

void fn_1_34D8(void)
{
    lbl_1_bss_CC = omAddObjEx(lbl_1_bss_120, 0x81, 20, 6, -1, fn_1_3528);
}

Vec lbl_1_data_3B8[] = { -1300.0f, 300.0f, -2350.0f, -800.0f, 200.0f, -2250.0f, 800.0f, 200.0f, -2250.0f, 1300.0f, 300.0f, -2350.0f, -1000.0f, 300.0f,
    -2350.0f, 1000.0f, 300.0f, -2350.0f, -1200.0f, 400.0f, -2450.0f, -800.0f, 400.0f, -2450.0f, 800.0f, 400.0f, -2450.0f, 1200.0f, 400.0f, -2450.0f,
    -1400.0f, 200.0f, -2250.0f, 1400.0f, 200.0f, -2250.0f, -1400.0f, 400.0f, -2450.0f, 1400.0f, 400.0f, -2450.0f, -900.0f, 500.0f, -2550.0f, 900.0f,
    500.0f, -2550.0f, -1200.0f, 500.0f, -2550.0f, 1200.0f, 500.0f, -2550.0f, -1100.0f, 200.0f, -2250.0f, 1100.0f, 200.0f, -2250.0f };

s32 lbl_1_data_4A8[] = { 0, 1, 0, 1, 2, 2, 1, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 1, 0 };

s32 lbl_1_data_4FC[] = { DATA_MAKE_NUM(DATADIR_M423, 12), DATA_MAKE_NUM(DATADIR_M423, 15), DATA_MAKE_NUM(DATADIR_M423, 18) };

s32 lbl_1_data_508[] = { DATA_MAKE_NUM(DATADIR_M423, 13), DATA_MAKE_NUM(DATADIR_M423, 14), DATA_MAKE_NUM(DATADIR_M423, 16),
    DATA_MAKE_NUM(DATADIR_M423, 17), DATA_MAKE_NUM(DATADIR_M423, 19), DATA_MAKE_NUM(DATADIR_M423, 20) };

s16 lbl_1_data_520[] = { 0, 2, 4 };

void fn_1_3528(omObjData *arg0)
{
    float var_f30;
    float var_f29;
    float temp_f31;
    StructBssCCData *var_r30;
    s32 temp_r27;
    s32 var_r28;
    s32 i;

    var_r30 = arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 20 * sizeof(*var_r30), MEMORY_DEFAULT_NUM);
    memset(var_r30, 0, 20 * sizeof(*var_r30));
    for (i = 0; i < 6; i++) {
        arg0->motion[i] = Hu3DMotionCreateFile(lbl_1_data_508[i]);
    }
    for (i = 0; i < 20; i++, var_r30++) {
        temp_r27 = lbl_1_data_4A8[i];
        var_r30->unk00 = temp_r27;
        var_r30->unk02 = 0;
        var_r30->unk04 = 0;
        var_r30->unk08 = 0;
        var_r30->unk0A = 0;
        var_r30->unk06 = (REFRESH_RATE_F * 3.5f) + (1.0f / 127) * frand7() * REFRESH_RATE_F;
        var_f30 = -lbl_1_data_3B8[i].x;
        var_f29 = -lbl_1_data_3B8[i].z;
        temp_f31 = atan2d(var_f30, var_f29);
        var_r28 = Hu3DModelCreateFile(lbl_1_data_4FC[temp_r27]);
        arg0->model[i] = var_r28;
        Hu3DModelCameraSet(var_r28, 4);
        Hu3DModelPosSet(var_r28, lbl_1_data_3B8[i].x, lbl_1_data_3B8[i].y, lbl_1_data_3B8[i].z);
        if (var_r30->unk00 != 1) {
            Hu3DModelRotSet(var_r28, 0.0f, temp_f31, 0.0f);
        }
        else {
            Hu3DModelRotSet(var_r28, 10.0f, temp_f31, 0.0f);
        }
        Hu3DModelScaleSet(var_r28, 1.8f, 1.8f, 1.8f);
        Hu3DMotionSet(arg0->model[i], arg0->motion[lbl_1_data_520[var_r30->unk00]]);
        if ((i >= 14 && i <= 17) || i == 11 || i == 10) {
            Hu3DModelAttrSet(var_r28, 1);
        }
    }
    arg0->stat |= 0x100;
    arg0->func = fn_1_3898;
}

s16 lbl_1_data_526[] = { 0, 2, 4 };
s16 lbl_1_data_52C[] = { 1, 3, 5, 0 };

void fn_1_3898(omObjData *arg0)
{
    StructBssCCData *var_r31;
    s32 var_r28;
    s32 i;

    var_r31 = arg0->data;
    for (i = 0; i < 20; i++, var_r31++) {
        var_r28 = 0;
        if (var_r31->unk06 > 0) {
            var_r28 = 1;
            var_r31->unk06--;
        }
        else if (var_r31->unk0A > 0) {
            if (var_r31->unk08 > 0) {
                var_r31->unk08--;
            }
            else if (var_r31->unk0A > 0) {
                var_r28 = 1;
                var_r31->unk0A--;
            }
            else {
                var_r31->unk08 = 0;
                var_r31->unk0A = 0;
            }
        }
        if (var_r28 != var_r31->unk02 && Hu3DMotionShiftIDGet(arg0->model[i]) == -1) {
            var_r31->unk02 = var_r28;
            if (var_r31->unk02 == 0) {
                Hu3DMotionShiftSet(arg0->model[i], arg0->motion[lbl_1_data_526[var_r31->unk00]], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
            else {
                Hu3DMotionShiftSet(arg0->model[i], arg0->motion[lbl_1_data_52C[var_r31->unk00]], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
        }
    }
}

void fn_1_3A58(omObjData *arg0)
{
    arg0->func = NULL;
}

void fn_1_3A64(void)
{
    fn_1_3A58(lbl_1_bss_CC);
}

void fn_1_3A8C(void)
{
    omObjData *var_r29;
    StructBssCCData *var_r31;
    s32 i;

    if (lbl_1_bss_CC == NULL) {
        return;
    }
    var_r29 = lbl_1_bss_CC;
    var_r31 = var_r29->data;
    for (i = 0; i < 20; i++, var_r31++) {
        if (var_r31->unk06 > 0 || var_r31->unk0A > 0) {
            var_r31->unk08 = 0;
        }
        else {
            var_r31->unk08 = (1.0f / 127) * frand7() * 0.25f * REFRESH_RATE_F;
        }
        var_r31->unk0A = ((1.0f / 127) * frand7() + 2.0f) * REFRESH_RATE_F;
    }
}

void fn_1_3BFC(void)
{
    s32 sp8[4];
    s32 temp_r28;
    s32 temp_r27;
    s32 var_r25;
    s32 var_r26;
    s32 var_r29;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        sp8[i] = -1;
    }
    for (i = 0, var_r29 = 0; i < 4; i++) {
        if (GWPlayerCfgGroupGet(i) == 0) {
            sp8[3] = i;
        }
        else {
            sp8[var_r29] = i;
            var_r29++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (sp8[i] == -1) {
            break;
        }
    }
    if (i < 4) {
        sp8[0] = 1;
        sp8[1] = 2;
        sp8[2] = 3;
        sp8[3] = 0;
    }
    else {
        for (i = 0; i < 32; i++) {
            temp_r28 = (s16)(frand() & 0xFFF) % 3;
            temp_r27 = (s16)(frand() & 0xFFF) % 3;
            if (temp_r28 != temp_r27) {
                var_r29 = sp8[temp_r27];
                sp8[temp_r27] = sp8[temp_r28];
                sp8[temp_r28] = var_r29;
            }
        }
    }
    var_r25 = 1;
    for (i = 0, var_r26 = 0; i < 4; i++) {
        lbl_1_bss_BC[i] = omAddObjEx(lbl_1_bss_120, 0x40, 4, 11, -1, fn_1_3FE0);
        lbl_1_bss_BC[i]->work[0] = i;
        if (i == sp8[3]) {
            lbl_1_bss_EC[3] = GWPlayerCfg[lbl_1_bss_BC[i]->work[0]].character;
            lbl_1_bss_BC[i]->work[1] = 0;
            lbl_1_bss_BC[i]->work[2] = 0;
            if (GWPlayerCfg[lbl_1_bss_BC[i]->work[0]].iscom) {
                lbl_1_bss_FC = 1;
            }
        }
        else {
            lbl_1_bss_EC[var_r26] = GWPlayerCfg[lbl_1_bss_BC[i]->work[0]].character;
            var_r26++;
            lbl_1_bss_BC[i]->work[1] = 1;
            for (j = 0; j < 3; j++) {
                if (i == sp8[j]) {
                    break;
                }
            }
            if (j >= 3) {
                j = i - 1;
            }
            lbl_1_bss_BC[i]->work[2] = j;
            lbl_1_bss_AC[j] = lbl_1_bss_BC[i];
            if (!GWPlayerCfg[lbl_1_bss_BC[i]->work[0]].iscom) {
                var_r25 = 0;
            }
        }
    }
    if (var_r25 != 0) {
        lbl_1_bss_FC = 0;
    }
}

u32 lbl_1_data_534[][2]
    = { { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), -1 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 2), -1 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 3), -1 }, { 0, 0 },
          { 0, 1 }, { 0, 2 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 23), -1 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 24), -1 } };

s32 lbl_1_data_574[] = { DATA_MAKE_NUM(DATADIR_M423, 58), DATA_MAKE_NUM(DATADIR_M423, 26), DATA_MAKE_NUM(DATADIR_M423, 34) };

u32 lbl_1_data_580[][2] = { { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), -1 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 2), -1 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 3), -1 }, { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 11), -1 },
    { DATA_MAKE_NUM(DATADIR_MARIOMOT, 6), -1 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 23), -1 }, { DATA_MAKE_NUM(DATADIR_MARIOMOT, 24), -1 } };

s32 lbl_1_data_5D8[]
    = { DATA_MAKE_NUM(DATADIR_M423, 42), DATA_MAKE_NUM(DATADIR_M423, 66), DATA_MAKE_NUM(DATADIR_M423, 50), DATA_MAKE_NUM(DATADIR_M423, 74) };

void fn_1_3FE0(omObjData *arg0)
{
    float var_f31;
    StructBssBCData *temp_r31;
    s32 i;

    temp_r31 = arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*temp_r31), MEMORY_DEFAULT_NUM);
    memset(temp_r31, 0, sizeof(*temp_r31));
    temp_r31->unk00 = arg0->work[0];
    temp_r31->unk02 = GWPlayerCfg[arg0->work[0]].character;
    temp_r31->unk04 = GWPlayerCfg[arg0->work[0]].pad_idx;
    temp_r31->unk06 = GWPlayerCfg[arg0->work[0]].iscom;
    temp_r31->unk08 = GWPlayerCfg[arg0->work[0]].diff;
    temp_r31->unk0A = arg0->work[1];
    temp_r31->unk0C = arg0->work[2];
    memset(&temp_r31->unk1C, 0, sizeof(temp_r31->unk1C));
    temp_r31->unk58 = 0;
    temp_r31->unk5C = -1;
    temp_r31->unk60 = 0.0f;
    temp_r31->unk64 = -1;
    temp_r31->unk68 = 0;
    temp_r31->unk6C = 0;
    temp_r31->unk70 = 0;
    temp_r31->unk74 = 0;
    temp_r31->unk16 = -1;
    temp_r31->unk88 = 0.0f;
    temp_r31->unk8C = 0.0f;
    temp_r31->unk90 = 0;
    temp_r31->unk94 = 0;
    temp_r31->unk98 = 0;
    temp_r31->unk9C = 0;
    temp_r31->unkA0 = 0;
    temp_r31->unkA4 = 0;
    temp_r31->unkA8 = 0.0f;
    temp_r31->unkAC = 0;
    arg0->model[0] = CharModelCreate(temp_r31->unk02, 4);
    Hu3DModelCameraSet(arg0->model[0], 5);
    Hu3DModelShadowSet(arg0->model[0]);
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_CURVE_MOTOFF);
    CharModelStepTypeSet(temp_r31->unk02, 2);
    if (temp_r31->unk0A == 0) {
        for (i = 0; i < 11; i++) {
            if (lbl_1_data_580[i][1] == -1) {
                arg0->motion[i] = CharModelMotionCreate(temp_r31->unk02, lbl_1_data_580[i][0]);
            }
            else {
                arg0->motion[i] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_5D8[lbl_1_data_580[i][1]] + temp_r31->unk02);
            }
        }
        temp_r31->unk16 = 0;
        temp_r31->unk18 = 0;
        CharModelMotionSet(temp_r31->unk02, arg0->motion[temp_r31->unk16]);
        Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
        temp_r31->unkB0 = arg0->trans.x = lbl_1_data_150[0].x;
        temp_r31->unkB4 = arg0->trans.y = lbl_1_data_150[0].y;
        temp_r31->unkB8 = arg0->trans.z = lbl_1_data_150[0].z;
        temp_r31->unkBC = lbl_1_data_180[0].x;
        temp_r31->unkC0 = lbl_1_data_180[0].y;
        temp_r31->unkC4 = lbl_1_data_180[0].z;
        temp_r31->unk78 = 0.0f;
        temp_r31->unk7C = 0.0f;
        temp_r31->unkE0 = temp_r31->unkE4 = temp_r31->unkE8 = 0.0f;
        temp_r31->unkEC = temp_r31->unkF0 = temp_r31->unkF4 = 0.0f;
        temp_r31->unk7C = 6.5f;
        var_f31 = 0.0f;
        for (i = 0; i < 1000; i++) {
            var_f31 += temp_r31->unk7C;
            temp_r31->unk7C -= (VERSION_PAL) ? 29.4f / REFRESH_RATE_OFF_BY_1 : 29.4f * REFRESH_FREQ;
            if (var_f31 <= 0.0f) {
                break;
            }
        }
        temp_r31->unk80 = i;
        temp_r31->unk7C = 10.5f;
        var_f31 = 0.0f;
        for (i = 0; i < 1000; i++) {
            var_f31 += temp_r31->unk7C;
            temp_r31->unk7C -= (VERSION_PAL) ? 39.2f / REFRESH_RATE_F : 0.65333337f;
            if (var_f31 <= 0.0f) {
                break;
            }
        }
        temp_r31->unk84 = i;
        arg0->func = fn_1_5D18;
    }
    else {
        for (i = 0; i < 8; i++) {
            if (lbl_1_data_534[i][1] == -1) {
                arg0->motion[i] = CharModelMotionCreate(temp_r31->unk02, lbl_1_data_534[i][0]);
            }
            else {
                arg0->motion[i] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_574[lbl_1_data_534[i][1]] + temp_r31->unk02);
            }
        }
        temp_r31->unk16 = 0;
        temp_r31->unk18 = 0;
        CharModelMotionSet(temp_r31->unk02, arg0->motion[temp_r31->unk16]);
        Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
        temp_r31->unkB0 = lbl_1_data_150[temp_r31->unk0C + 1].x;
        temp_r31->unkB4 = lbl_1_data_150[temp_r31->unk0C + 1].y;
        temp_r31->unkB8 = lbl_1_data_150[temp_r31->unk0C + 1].z;
        temp_r31->unkBC = arg0->trans.x = lbl_1_data_180[temp_r31->unk0C + 1].x;
        temp_r31->unkC0 = arg0->trans.y = lbl_1_data_180[temp_r31->unk0C + 1].y;
        temp_r31->unkC4 = arg0->trans.z = lbl_1_data_180[temp_r31->unk0C + 1].z;
        temp_r31->unk78 = atan2d(lbl_1_data_150[0].x - temp_r31->unkB0, lbl_1_data_150[0].z - temp_r31->unkB8);
        temp_r31->unk7C = 0.0f;
        temp_r31->unk98 = 0;
        temp_r31->unk9C = (REFRESH_RATE_F * 5) + (1.0f / 127) * frand7() * REFRESH_RATE_F * 15.0f;
        if (lbl_1_bss_FC != 0) {
            temp_r31->unk08 = 3;
        }
        arg0->func = fn_1_4778;
    }
    CharModelMotionDataClose(temp_r31->unk02);
}

Vec lbl_1_data_5E8 = { 0.0f, 20.0f, 50.0f };
GXColor lbl_1_data_5F4 = { 0xFF, 0xFF, 0xFF, 0x10 };
GXColor lbl_1_data_5F8 = { 0xFF, 0xFF, 0xFF, 0x40 };

void fn_1_4778(omObjData *arg0)
{
    Mtx sp11C;
    Vec sp110;
    Vec sp104;
    Vec spF8;
    float temp_f27;
    float temp_f29;
    float temp_f30;
    float var_f25;
    StructBssBCData *temp_r31;
    ModelData *temp_r27;
    s32 temp_r26;
    s16 var_r25;
    s16 var_r24;
    s16 var_r29;
    s16 var_r28;

    temp_r31 = arg0->data;
    temp_r27 = &Hu3DData[arg0->model[0]];
    temp_r31->unk0E = HuPadBtn[temp_r31->unk04];
    temp_r31->unk10 = HuPadBtnDown[temp_r31->unk04];
    temp_r31->unk12 = HuPadStkX[temp_r31->unk04];
    temp_r31->unk14 = HuPadStkY[temp_r31->unk04];
    if (fn_1_F00() == 6) {
        if (temp_r31->unk06 != 0) {
            temp_r31->unk0E &= ~PAD_BUTTON_A;
            temp_r31->unk10 &= ~PAD_BUTTON_A;
            temp_r31->unk12 = 0;
            temp_r31->unk14 = 0;
            fn_1_8338(arg0);
        }
        var_r25 = temp_r31->unk0E;
        var_r24 = temp_r31->unk10;
        var_r29 = temp_r31->unk12;
        var_r28 = temp_r31->unk14;
    }
    if (fabs(var_r29) < 8.0) {
        var_r29 = 0;
    }
    if (fabs(var_r29) > 80.0) {
        var_r29 = 80;
    }
    if (fabs(var_r28) < 8.0) {
        var_r28 = 0;
    }
    if (fabs(var_r28) > 80.0) {
        var_r28 = 80;
    }
    if (fn_1_F00() != 6) {
        var_r29 = var_r28 = 0;
        var_r25 = var_r24 = 0;
    }
    switch (temp_r31->unk18) {
        case 0:
            if (fn_1_F00() < 3) {
                break;
            }
            spF8.x = temp_r31->unkB0 - arg0->trans.x;
            spF8.z = temp_r31->unkB8 - arg0->trans.z;
            temp_f29 = VECMagXZ(&spF8);
            if (temp_f29 > (VERSION_PAL ? 30.000002f : 25.0f)) {
                spF8.x = temp_r31->unkB0 - arg0->trans.x;
                spF8.z = temp_r31->unkB8 - arg0->trans.z;
                temp_f30 = atan2d(spF8.x, spF8.z);
                arg0->rot.y = fn_1_122F4(temp_f30, arg0->rot.y, 15.0f);
#if VERSION_PAL
                arg0->trans.x += 25.0 * sind(arg0->rot.y) * 0.5 * 1.2000000476837158;
                arg0->trans.z += 25.0 * cosd(arg0->rot.y) * 0.5 * 1.2000000476837158;
#else
                arg0->trans.x += 25.0 * sind(arg0->rot.y) * 0.5;
                arg0->trans.z += 25.0 * cosd(arg0->rot.y) * 0.5;
#endif
                if (temp_r31->unk16 != 2) {
                    temp_r31->unk16 = 2;
                    CharModelMotionSet(temp_r31->unk02, arg0->motion[temp_r31->unk16]);
                    Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
                }
                break;
            }
            arg0->trans.x = temp_r31->unkB0;
            arg0->trans.z = temp_r31->unkB8;
            temp_r31->unk18 = 1;
            if (temp_r31->unk16 != 0) {
                temp_r31->unk16 = 0;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_LOOP);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
            }
            break;
        case 1:
            arg0->rot.y = fn_1_122F4(0.0f, arg0->rot.y, VERSION_PAL ? 6.0f : 5.0f);
            if (fabs(fn_1_121DC(arg0->rot.y, 0.0f)) < 1.0) {
                arg0->rot.y = 0.0f;
                temp_r31->unk18 = 2;
            }
            break;
        case 2:
            temp_r31->unk18 = 3;
            break;
        case 3:
            arg0->rot.y = fn_1_122F4(0.0f, arg0->rot.y, VERSION_PAL ? 12.0f : 10.0f);
            if (fn_1_F00() >= 7) {
                temp_r31->unk18 = 10;
                temp_r31->unk68 = 0;
                break;
            }
            if (fabs(fn_1_121DC(arg0->rot.y, 0.0f)) < 1.0) {
                arg0->rot.y = 0.0f;
                sp104 = lbl_1_data_5E8;
                mtxRot(sp11C, arg0->rot.x, arg0->rot.y, arg0->rot.z);
                fn_1_1293C(sp11C, &sp104);
                sp104.x += arg0->trans.x;
                sp104.y += arg0->trans.y;
                sp104.z += arg0->trans.z;
                if (fn_1_F00() <= 6 && (temp_r31->unk5C = fn_1_A9D4(temp_r31->unk02, lbl_1_data_1B0[temp_r31->unk0C], sp104)) != -1) {
                    temp_r31->unk18 = 4;
                    temp_r31->unk68 = 0;
                }
            }
            break;
        case 4:
            temp_r26 = fn_1_AE64(temp_r31->unk5C);
            if (fn_1_F00() >= 7) {
                temp_r31->unk18 = 10;
                temp_r31->unk68 = 0;
                break;
            }
            if (temp_r26 == -1 || temp_r31->unk5C == -1) {
                temp_r31->unk18 = 3;
                break;
            }
            if (temp_r26 == 2) {
                if (++temp_r31->unk68 >= REFRESH_RATE_F / 10.0f) {
                    HuAudFXPlay(0x61A);
                    temp_r31->unk18 = 5;
                    temp_r31->unk68 = 0;
                }
                break;
            }
            if (++temp_r31->unk68 >= (0.9f * REFRESH_RATE_F) && temp_r31->unk16 != 3) {
                temp_r31->unk16 = 3;
                CharModelMotionSet(temp_r31->unk02, arg0->motion[temp_r31->unk16]);
#if VERSION_PAL
                CharModelMotionSpeedSet(temp_r31->unk02, 1.2f);
#endif
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
            }
            break;
        case 5:
            temp_f30 = fabs(fn_1_121DC(arg0->rot.y, temp_r31->unk78));
            if (temp_f30 < 10.0f) {
                arg0->rot.y += temp_f30;
            }
            else {
                arg0->rot.y += VERSION_PAL ? 12.0f : 10.0f;
            }
            sp104 = lbl_1_data_5E8;
            mtxRot(sp11C, arg0->rot.x, arg0->rot.y, arg0->rot.z);
            fn_1_1293C(sp11C, &sp104);
            sp104.x += arg0->trans.x;
            sp104.y += arg0->trans.y;
            sp104.z += arg0->trans.z;
            fn_1_AC0C(temp_r31->unk5C, sp104);
            spF8.x = 0.0f;
            spF8.y = 1.0f;
            spF8.z = 1.0f;
            sp104.y = 0.0f;
            fn_1_DD70(sp104, spF8, 50.0f, -0.5f, 10.0f, 1.0f, lbl_1_data_5F4);
            if (fn_1_F00() >= 7) {
                temp_r31->unk18 = 10;
                temp_r31->unk68 = 0;
                break;
            }
            if (fabs(fn_1_121DC(arg0->rot.y, temp_r31->unk78)) < 1.0) {
                temp_r31->unkC8 = sp104;
                temp_r31->unk18 = 6;
                temp_r31->unk68 = 0;
            }
            break;
        case 6:
            sp110.x = 0.0125f * var_r29 * 300.0f;
            sp110.y = -900.0f;
            sp110.z = -900.0f;
            temp_f30 = atan2d(sp110.x - temp_r31->unkC8.x, sp110.z - temp_r31->unkC8.z);
            arg0->rot.y = fn_1_122F4(temp_f30, arg0->rot.y, 5.0f);
            if (fn_1_F00() >= 7) {
                temp_r31->unk18 = 10;
                temp_r31->unk68 = 0;
                break;
            }
            if (var_r24 & PAD_BUTTON_A) {
                temp_r31->unk16 = 4;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_NONE);
                temp_r27->unk_88 = VERSION_PAL ? 0.6f : 0.5f;
                temp_r31->unkD4 = sp110;
                temp_r31->unk18 = 7;
                temp_r31->unk68 = 0;
            }
            break;
        case 7:
            temp_r31->unk68++;
            if (temp_r31->unk68 > REFRESH_RATE_F * 1.5f) {
                temp_r31->unk68 = REFRESH_RATE * 1.5;
            }
            temp_f29 = (0.6666667f / REFRESH_RATE_F) * temp_r31->unk68;
            sp110.x = 0.0125f * var_r29 * 300.0f;
            sp110.y = -900.0f;
            sp110.z = -900.0f;
            temp_f30 = atan2d(sp110.x - temp_r31->unkC8.x, sp110.z - temp_r31->unkC8.z);
            arg0->rot.y = fn_1_122F4(temp_f30, arg0->rot.y, 5.0f);
            temp_r31->unkD4 = sp110;
            if (fn_1_F00() >= 7) {
                temp_r31->unk18 = 10;
                temp_r31->unk68 = 0;
                break;
            }
            if (!(var_r25 & PAD_BUTTON_A)) {
                var_f25 = 15.000001f + 30.0f * temp_f29;
#if VERSION_PAL
                temp_r31->unk60 = var_f25 * 1.2f;
#else
                temp_r31->unk60 = var_f25;
#endif
                temp_r31->unk16 = 5;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_NONE);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f * (0.5f + 1.5f * temp_f29);
#else
                temp_r27->unk_88 = 0.5f + 1.5f * temp_f29;
#endif
                temp_r31->unk18 = 8;
                temp_r31->unk68 = 0;
            }
            break;
        case 8:
            if (fn_1_F00() >= 7) {
                temp_r31->unk18 = 10;
                temp_r31->unk68 = 0;
                break;
            }
            if (CharModelMotionTimeGet(temp_r31->unk02) >= 10.0f && CharModelMotionShiftIDGet(temp_r31->unk02) == -1) {
                temp_r26 = fn_1_AE64(temp_r31->unk5C);
                if (temp_r26 == -1 || temp_r31->unk5C == -1) {
                    temp_r31->unk18 = 3;
                }
                VECSubtract(&temp_r31->unkD4, &temp_r31->unkC8, &spF8);
                VECNormalize(&spF8, &spF8);
                temp_f27 = 15.0f;
                spF8.x *= temp_r31->unk60 * cosd(temp_f27);
                spF8.z *= temp_r31->unk60 * cosd(temp_f27);
                spF8.y = temp_r31->unk60 * sind(temp_f27);
                fn_1_AC80(temp_r31->unk5C, spF8);
                temp_r31->unk5C = -1;
                HuAudFXPlay(0x61F);
                sp104 = temp_r31->unkC8;
                sp104.y += 75.0f;
                spF8.x = 0.0f;
                spF8.y = 1.0f;
                spF8.z = 1.0f;
                sp104.y = 0.0f;
                fn_1_DC24(sp104, spF8, 50.0f, -0.5f, 1.0f, lbl_1_data_5F8);
                temp_f29 = (temp_r31->unk60 - 15.000001f) / 30.0f;
                if (temp_f29 > 0.66f) {
                    HuAudFXPlay(0x61B);
                }
                else if (temp_f29 > 0.33f) {
                    HuAudFXPlay(0x61C);
                }
                else {
                    HuAudFXPlay(0x61D);
                }
                temp_r31->unk18 = 9;
                temp_r31->unk68 = 0;
            }
            break;
        case 9:
            if (fn_1_F00() >= 7) {
                temp_r31->unk18 = 10;
                temp_r31->unk68 = 0;
                break;
            }
            if (++temp_r31->unk68 >= REFRESH_RATE_F / 5) {
                temp_r31->unk16 = 0;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_LOOP);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
                temp_r31->unk18 = 3;
                temp_r31->unk68 = 0;
            }
            break;
        case 10:
            arg0->rot.y = fn_1_122F4(0.0f, arg0->rot.y, 10.0f);
            if (CharModelMotionShiftIDGet(temp_r31->unk02) == -1 && temp_r31->unk16 != 0) {
                temp_r31->unk16 = 0;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_LOOP);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
            }
            break;
        case 11:
            if (CharModelMotionShiftIDGet(temp_r31->unk02) == -1 && temp_r31->unk16 != 6) {
                temp_r31->unk16 = 6;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_NONE);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_SHIFT_LOOP);
            }
            break;
        case 12:
            if (CharModelMotionShiftIDGet(temp_r31->unk02) == -1 && temp_r31->unk16 != 7) {
                temp_r31->unk16 = 7;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_NONE);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_SHIFT_LOOP);
            }
            break;
    }
}

GXColor lbl_1_data_630 = { 0xFF, 0xFF, 0xFF, 0x14 };

void fn_1_5D18(omObjData *arg0)
{
    Vec sp60;
    Vec sp54;
    Vec sp48;
    float var_f30;
    float var_f31;
    float var_f29;
    StructBssBCData *temp_r31;
    ModelData *temp_r27;
    s16 var_r26;
    s16 var_r25;
    s16 var_r28;
    s16 var_r24;
    s16 i;

    temp_r31 = arg0->data;
    temp_r27 = &Hu3DData[arg0->model[0]];
    temp_r31->unk0E = HuPadBtn[temp_r31->unk04];
    temp_r31->unk10 = HuPadBtnDown[temp_r31->unk04];
    temp_r31->unk12 = HuPadStkX[temp_r31->unk04];
    temp_r31->unk14 = HuPadStkY[temp_r31->unk04];
    if (fn_1_F00() == 6) {
        if (temp_r31->unk06 != 0) {
            temp_r31->unk0E &= ~PAD_BUTTON_A;
            temp_r31->unk10 &= ~PAD_BUTTON_A;
            temp_r31->unk12 = 0;
            temp_r31->unk14 = 0;
            fn_1_8CB4(arg0);
        }
        var_r28 = temp_r31->unk12;
        var_r24 = temp_r31->unk14;
    }
    if (fabs(var_r28) < 8.0) {
        var_r28 = 0;
    }
    if (fabs(var_r28) > 80.0) {
        var_r28 = 80;
    }
    if (fabs(var_r24) < 8.0) {
        var_r24 = 0;
    }
    if (fabs(var_r24) > 80.0) {
        var_r24 = 80;
    }
    switch (temp_r31->unk18) {
        case 0:
            if (fn_1_F00() >= 6) {
                temp_r31->unk18 = 1;
            }
            break;
        case 1:
            if (fabs(var_r28) > 8.0) {
                var_f30 = 0.125f * var_r28;
            }
            else {
                var_f30 = 0.0f;
            }
            temp_r31->unk1C[temp_r31->unk58] = var_f30;
            if (++temp_r31->unk58 >= 15) {
                temp_r31->unk58 = 0;
            }
            for (i = 0, var_f30 = 0.0f; i < 15; i++) {
                var_f30 += temp_r31->unk1C[i];
            }
            var_f30 *= 0.06666667f;
            if (var_f30 > 25.0f) {
                var_f30 = 25.0f;
            }
            else if (var_f30 < -25.0f) {
                var_f30 = -25.0f;
            }
            if (0.0f == var_f30) {
                var_r25 = 0;
            }
            else if (fabs(var_f30) < 10.0) {
                var_r25 = 1;
            }
            else {
                var_r25 = 2;
            }
            if (temp_r31->unk16 != var_r25 && CharModelMotionShiftIDGet(temp_r31->unk02) == -1) {
                temp_r31->unk16 = var_r25;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_LOOP);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
            }
            if (temp_r31->unk16 == 1 && CharModelMotionShiftIDGet(temp_r31->unk02) == -1) {
                var_f31 = fabs(0.1f * var_f30);
                if (var_f31 < 0.25f) {
                    var_f31 = 0.25f;
                }
#if VERSION_PAL
                CharModelMotionSpeedSet(temp_r31->unk02, var_f31 * 1.2f);
#else
                CharModelMotionSpeedSet(temp_r31->unk02, var_f31);
#endif
            }
            if (var_r28 == 0.0f) {
                var_f29 = 0.0f;
            }
            else if (var_r28 < 0.0f) {
                var_f29 = -90.0f;
            }
            else {
                var_f29 = 90.0f;
            }
            if (arg0->rot.y < var_f29 && (arg0->rot.y += 20.0f) > var_f29) {
                arg0->rot.y = var_f29;
            }
            if (arg0->rot.y > var_f29 && (arg0->rot.y -= 20.0f) < var_f29) {
                arg0->rot.y = var_f29;
            }
#if VERSION_PAL
            arg0->trans.x += var_f30 * 1.2f;
#else
            arg0->trans.x += var_f30;
#endif
            arg0->trans.y = 0.0f;
            arg0->trans.z = temp_r31->unkB8;
            if (arg0->trans.x < -225.0f) {
                arg0->trans.x = -225.0f;
            }
            if (arg0->trans.x > 225.0f) {
                arg0->trans.x = 225.0f;
            }
            if (fn_1_F00() >= 7) {
                temp_r31->unk18 = 9;
                temp_r31->unk68 = 0;
            }
            else if (temp_r31->unk10 & PAD_BUTTON_A) {
                if (var_r28 > 0) {
                    temp_r27->unk_0C = -1;
                    temp_r31->unk16 = 3;
                    CharModelMotionSet(temp_r31->unk02, arg0->motion[temp_r31->unk16]);
                    CharModelMotionSpeedSet(temp_r31->unk02, VERSION_PAL ? 1.2f : 1.0f);
                    Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_SHIFT_LOOP);
                    temp_r31->unk7C = 6.5f;
                    temp_r31->unk68 = 0;
                    arg0->rot.y = 90.0f;
                    i = 99;
                    if ((var_r26 = fn_1_B304(lbl_1_bss_40)) != 0) {
                        for (i = 0; i < var_r26; i++) {
                            if (lbl_1_bss_40[0]->unk1C < lbl_1_bss_40[0]->unk14 || lbl_1_bss_40[0]->unk1C - lbl_1_bss_40[0]->unk14 > REFRESH_RATE / 10.0f) {
                                continue;
                            }
                            if (lbl_1_bss_40[0]->unk1C < REFRESH_RATE * 0.6f) {
                                var_f31 = lbl_1_bss_40[0]->unk68.z - arg0->trans.z;
                            }
                            else {
                                var_f31 = lbl_1_bss_40[0]->unk38.z - arg0->trans.z;
                            }
                            if (var_f31 < -100.0f) {
                                continue;
                            }
                            var_f31 = fabs(var_f31);
                            if (var_f31 >= 300.0f) {
                                temp_r31->unk8C = 13.5f;
                            }
                            else if (var_f31 <= 100.0f) {
                                temp_r31->unk8C = 6.5f;
                            }
                            else {
                                temp_r31->unk8C = 10.0f;
                            }
                        }
                    }
                    if (i >= var_r26) {
                        temp_r31->unk8C = 10.0f;
                    }
                    temp_r31->unk18 = 2;
                }
                else if (var_r28 < 0) {
                    temp_r27->unk_0C = -1;
                    temp_r31->unk16 = 5;
                    CharModelMotionSet(temp_r31->unk02, arg0->motion[temp_r31->unk16]);
                    CharModelMotionSpeedSet(temp_r31->unk02, VERSION_PAL ? 1.2f : 1.0f);
                    Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_SHIFT_LOOP);
                    temp_r31->unk7C = 6.5f;
                    temp_r31->unk68 = 0;
                    arg0->rot.y = -90.0f;
                    i = 99;
                    if ((var_r26 = fn_1_B304(lbl_1_bss_40)) != 0) {
                        for (i = 0; i < var_r26; i++) {
                            if (lbl_1_bss_40[0]->unk1C < lbl_1_bss_40[0]->unk14 || lbl_1_bss_40[0]->unk1C - lbl_1_bss_40[0]->unk14 > REFRESH_RATE / 10.0f) {
                                continue;
                            }
                            if (lbl_1_bss_40[0]->unk1C < REFRESH_RATE * 0.6f) {
                                var_f31 = lbl_1_bss_40[0]->unk68.z - arg0->trans.z;
                            }
                            else {
                                var_f31 = lbl_1_bss_40[0]->unk38.z - arg0->trans.z;
                            }
                            if (var_f31 > 100.0f) {
                                continue;
                            }
                            var_f31 = fabs(var_f31);
                            if (var_f31 >= 300.0f) {
                                temp_r31->unk8C = 13.5f;
                            }
                            else if (var_f31 <= 100.0f) {
                                temp_r31->unk8C = 6.5f;
                            }
                            else {
                                temp_r31->unk8C = 10.0f;
                            }
                        }
                    }
                    if (i >= var_r26) {
                        temp_r31->unk8C = 10.0f;
                    }
                    temp_r31->unk18 = 4;
                }
                else {
                    temp_r27->unk_0C = -1;
                    temp_r31->unk16 = 7;
                    CharModelMotionSet(temp_r31->unk02, arg0->motion[temp_r31->unk16]);
                    CharModelMotionSpeedSet(temp_r31->unk02, VERSION_PAL ? 1.2f : 1.0f);
                    Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_SHIFT_LOOP);
                    temp_r31->unk7C = 10.5f;
                    temp_r31->unk68 = 0;
                    arg0->rot.y = 0.0f;
                    temp_r31->unk18 = 7;
                }
            }
            break;
        case 2:
#if VERSION_PAL
            arg0->trans.x += temp_r31->unk8C * 1.2f;
#else
            arg0->trans.x += temp_r31->unk8C;
#endif
            if (arg0->trans.x > 225.0f) {
                arg0->trans.x = 225.0f;
            }
            arg0->trans.y += temp_r31->unk7C;
            temp_r31->unk7C -= (VERSION_PAL) ? 29.4f / REFRESH_RATE_OFF_BY_1 : 29.4f * REFRESH_FREQ;
            temp_r31->unk68++;
            if (temp_r31->unk68 == temp_r31->unk80 - REFRESH_RATE_F / 5) {
                temp_r31->unk16 = 4;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_NONE);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_SHIFT_LOOP);
            }
            if (arg0->trans.y <= 0.0f) {
                for (i = 0; i < 6; i++) {
                    sp48.x = sind(-90.0f + 30.0f * i);
                    sp48.z = cosd(-90.0f + 30.0f * i);
                    sp48.y = 0.0f;
                    sp54.x = 100.0f * sp48.x * 0.01f;
                    sp54.z = 100.0f * sp48.z * 0.01f;
                    sp54.y = 1.0f;
                    sp60.x = arg0->trans.x + 100.0f * sp48.x * 0.2;
                    sp60.z = arg0->trans.z + 100.0f * sp48.z * 0.2;
                    sp60.y = 0.0f;
                    fn_1_DD70(sp60, sp54, 50.0f, -0.25f, 20.0f, 0.5f, lbl_1_data_630);
                }
                arg0->trans.y = 0.0f;
                temp_r31->unk18 = 3;
            }
            break;
        case 3:
            if (CharModelMotionEndCheck(temp_r31->unk02) && CharModelMotionShiftIDGet(temp_r31->unk02) == -1) {
                memset(&temp_r31->unk1C, 0, sizeof(temp_r31->unk1C));
                temp_r31->unk58 = 0;
                temp_r31->unk16 = 0;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_LOOP);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
                temp_r31->unk18 = 6;
                temp_r31->unkAC = 0;
            }
            break;
        case 4:
#if VERSION_PAL
            arg0->trans.x -= temp_r31->unk8C * 1.2f;
#else
            arg0->trans.x -= temp_r31->unk8C;
#endif
            if (arg0->trans.x < -225.0f) {
                arg0->trans.x = -225.0f;
            }
            arg0->trans.y += temp_r31->unk7C;
            temp_r31->unk7C -= (VERSION_PAL) ? 29.4f / REFRESH_RATE_OFF_BY_1 : 29.4f * REFRESH_FREQ;
            temp_r31->unk68++;
            if (temp_r31->unk68 == temp_r31->unk80 - REFRESH_RATE_F / 5) {
                temp_r31->unk16 = 6;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_NONE);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_SHIFT_LOOP);
            }
            if (arg0->trans.y <= 0.0f) {
                for (i = 0; i < 6; i++) {
                    sp48.x = sind(-90.0f + 30.0f * i);
                    sp48.z = cosd(-90.0f + 30.0f * i);
                    sp48.y = 0.0f;
                    sp54.x = 100.0f * sp48.x * 0.01f;
                    sp54.z = 100.0f * sp48.z * 0.01f;
                    sp54.y = 1.0f;
                    sp60.x = arg0->trans.x + 100.0f * sp48.x * 0.2;
                    sp60.z = arg0->trans.z + 100.0f * sp48.z * 0.2;
                    sp60.y = 0.0f;
                    fn_1_DD70(sp60, sp54, 50.0f, -0.25f, 20.0f, 0.5f, lbl_1_data_630);
                }
                arg0->trans.y = 0.0f;
                temp_r31->unk18 = 5;
            }
            break;
        case 5:
            if (CharModelMotionEndCheck(temp_r31->unk02) && CharModelMotionShiftIDGet(temp_r31->unk02) == -1) {
                memset(&temp_r31->unk1C, 0, sizeof(temp_r31->unk1C));
                temp_r31->unk58 = 0;
                temp_r31->unk16 = 0;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_LOOP);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
                temp_r31->unk18 = 6;
                temp_r31->unkAC = 0;
            }
            break;
        case 6:
            if (++temp_r31->unkAC > 0.0f) {
                temp_r31->unkAC = 0;
                temp_r31->unk18 = 1;
            }
            break;
        case 7:
            arg0->trans.y += temp_r31->unk7C;
            temp_r31->unk7C -= (VERSION_PAL) ? 39.2f / REFRESH_RATE_F : 0.65333337f;
            temp_r31->unk68++;
            if (arg0->trans.y <= 0.0f) {
                temp_r31->unk16 = 0;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_NONE);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_SHIFT_LOOP);
                arg0->trans.y = 0.0f;
                temp_r31->unk68 = 0;
                temp_r31->unk18 = 8;
            }
            break;
        case 8:
            if (++temp_r31->unk68 > REFRESH_RATE_F / 5) {
                memset(&temp_r31->unk1C, 0, sizeof(temp_r31->unk1C));
                temp_r31->unk58 = 0;
                temp_r31->unk16 = 0;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_LOOP);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
                temp_r31->unk18 = 1;
            }
            break;
        case 9:
            arg0->rot.y = fn_1_122F4(0.0f, arg0->rot.y, 10.0f);
            if (CharModelMotionShiftIDGet(temp_r31->unk02) == -1 && temp_r31->unk16 != 1) {
                temp_r31->unk16 = 1;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_LOOP);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
            }
            if (CharModelMotionShiftIDGet(temp_r31->unk02) == -1 && temp_r31->unk16 == 1) {
                arg0->trans.z += (VERSION_PAL) ? 6.0f : 5.0f;
            }
            if (arg0->trans.z > lbl_1_data_150->z + 100.0f) {
                temp_r31->unk18 = 10;
            }
            break;
        case 10:
            arg0->rot.y = fn_1_122F4(0.0f, arg0->rot.y, 10.0f);
            if (CharModelMotionShiftIDGet(temp_r31->unk02) == -1 && temp_r31->unk16 != 0) {
                temp_r31->unk16 = 0;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_LOOP);
#if VERSION_PAL
                temp_r27->unk_88 = 1.2f;
#endif
            }
            break;
        case 11:
            if (CharModelMotionShiftIDGet(temp_r31->unk02) == -1 && temp_r31->unk16 != 9) {
                temp_r31->unk16 = 9;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_NONE);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_SHIFT_LOOP);
            }
            break;
        case 12:
            if (CharModelMotionShiftIDGet(temp_r31->unk02) == -1 && temp_r31->unk16 != 10) {
                temp_r31->unk16 = 10;
                CharModelMotionShiftSet(temp_r31->unk02, arg0->motion[temp_r31->unk16], 0.0f, REFRESH_RATE_F / 7.5f, HU3D_MOTATTR_NONE);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_SHIFT_LOOP);
            }
            break;
    }
    lbl_1_bss_B8 = arg0;
    temp_r31->unkEC = arg0->trans.x - temp_r31->unkE0;
    temp_r31->unkF0 = arg0->trans.y - temp_r31->unkE4;
    temp_r31->unkF4 = arg0->trans.z - temp_r31->unkE8;
    temp_r31->unkE0 = arg0->trans.x;
    temp_r31->unkE4 = arg0->trans.y;
    temp_r31->unkE8 = arg0->trans.z;
}

void fn_1_77C4(omObjData *arg0)
{
    arg0->func = NULL;
}

void fn_1_77D0(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        fn_1_77C4(lbl_1_bss_BC[i]);
    }
}

s32 fn_1_781C(void)
{
    omObjData *temp_r29;
    StructBssBCData *temp_r31;
    s32 i;

    for (i = 0; i < 4; i++) {
        temp_r29 = lbl_1_bss_BC[i];
        temp_r31 = temp_r29->data;
        if (temp_r31->unk0A == 0) {
            if (temp_r31->unk18 != 0 || fabs(fn_1_121DC(temp_r29->rot.y, 0.0f)) > 1.0) {
                break;
            }
        }
        else {
            if (temp_r31->unk18 < 5) {
                break;
            }
        }
    }
    if (i >= 4) {
        return 1;
    }
    return 0;
}

s32 fn_1_791C(void)
{
    omObjData *temp_r30;
    StructBssBCData *temp_r31;
    s32 i;

    for (i = 0; i < 4; i++) {
        temp_r30 = lbl_1_bss_BC[i];
        temp_r31 = temp_r30->data;
        if (temp_r31->unk0A == 0) {
            if (temp_r31->unk18 != 10 || fabs(fn_1_121DC(temp_r30->rot.y, 0.0f)) > 1.0 || CharModelMotionShiftIDGet(temp_r31->unk02) != -1) {
                break;
            }
        }
        else {
            if (temp_r31->unk18 != 10 || fabs(fn_1_121DC(temp_r30->rot.y, 0.0f)) > 1.0 || CharModelMotionShiftIDGet(temp_r31->unk02) != -1) {
                break;
            }
        }
    }
    if (i >= 4) {
        return 1;
    }
    return 0;
}

void fn_1_7AA8(s32 arg0)
{
    omObjData *var_r29;
    StructBssBCData *temp_r31;
    s32 i;

    for (i = 0; i < 4; i++) {
        var_r29 = lbl_1_bss_BC[i];
        temp_r31 = var_r29->data;
        if (temp_r31->unk0A == 0) {
            if (temp_r31->unk0A == arg0) {
                temp_r31->unk18 = 11;
            }
            else {
                temp_r31->unk18 = 12;
            }
        }
        else {
            if (temp_r31->unk0A == arg0) {
                temp_r31->unk18 = 11;
            }
            else {
                temp_r31->unk18 = 12;
            }
        }
    }
}

s32 fn_1_7B48(Vec *arg0, Vec *arg1, Vec *arg2, float arg3)
{
    Vec spA8[4];
    Vec sp78[4];
    Vec sp48[4];
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f31;
    float var_f28;
    float var_f30;
    float var_f27;
    float var_f26;
    omObjData *temp_r31;
    StructBssBCData *temp_r28;
    ModelData *sp8;

    if (lbl_1_bss_B8 == NULL) {
        return 0;
    }
    temp_r31 = lbl_1_bss_B8;
    temp_r28 = temp_r31->data;
    sp8 = &Hu3DData[temp_r31->model[0]];
    *arg2 = *arg1;
    switch (temp_r28->unk18) {
        case 2:
        case 4:
            var_f31 = 150.0f;
            var_f28 = 130.0f;
            var_f30 = 60.000004f;
            var_f27 = 130.0f;
            break;
        default:
            var_f31 = 100.0f;
            var_f28 = 130.0f;
            var_f30 = 60.000004f;
            var_f27 = 0.0f;
            break;
    }
    sp78[0].x = temp_r31->trans.x - 0.5f * var_f31;
    sp78[0].y = temp_r31->trans.y + var_f28;
    sp78[0].z = temp_r31->trans.z + 0.5f * var_f30;
    sp78[1].x = temp_r31->trans.x + 0.5f * var_f31;
    sp78[1].y = temp_r31->trans.y + var_f28;
    sp78[1].z = temp_r31->trans.z + 0.5f * var_f30;
    sp78[2].x = temp_r31->trans.x + 0.5f * var_f31;
    sp78[2].y = temp_r31->trans.y - var_f27;
    sp78[2].z = temp_r31->trans.z + 0.5f * var_f30;
    sp78[3].x = temp_r31->trans.x - 0.5f * var_f31;
    sp78[3].y = temp_r31->trans.y - var_f27;
    sp78[3].z = temp_r31->trans.z + 0.5f * var_f30;
    spA8[0].x = temp_r31->trans.x + 0.5f * var_f31;
    spA8[0].y = temp_r31->trans.y + var_f28;
    spA8[0].z = temp_r31->trans.z - 0.5f * var_f30;
    spA8[1].x = temp_r31->trans.x - 0.5f * var_f31;
    spA8[1].y = temp_r31->trans.y + var_f28;
    spA8[1].z = temp_r31->trans.z - 0.5f * var_f30;
    spA8[2].x = temp_r31->trans.x - 0.5f * var_f31;
    spA8[2].y = temp_r31->trans.y - var_f27;
    spA8[2].z = temp_r31->trans.z - 0.5f * var_f30;
    spA8[3].x = temp_r31->trans.x + 0.5f * var_f31;
    spA8[3].y = temp_r31->trans.y - var_f27;
    spA8[3].z = temp_r31->trans.z - 0.5f * var_f30;
    VECNormalize(arg1, &spC);
    VECScale(&spC, &spC, arg3);
    VECAdd(arg0, arg1, &sp30);
    VECAdd(arg0, arg1, &sp24);
    VECAdd(arg0, &spC, &sp3C);
    VECAdd(&sp30, &spC, &sp30);
    sp48[0] = sp78[0];
    sp48[1] = sp78[1];
    sp48[2] = sp78[2];
    sp48[3] = sp78[3];
    if (fn_1_137C4(sp48, arg0, arg1, &sp18, arg3, 4) != 0) {
        arg2->x *= 0.5f;
        arg2->z *= -0.5f;
        fn_1_82C8(15, 1, 0);
        return 1;
    }
    if (sp24.x >= sp78[0].x - arg3 && sp24.x <= sp78[2].x + arg3 && sp24.y <= sp78[0].y + arg3 && sp24.y >= sp78[2].y - arg3
        && sp24.z <= sp78[0].z + arg3 && sp24.z >= spA8[3].z - arg3) {
        if (temp_r28->unkEC > 0.0f && sp24.x > temp_r31->trans.x) {
            spC = *arg1;
            spC.y = 0.0f;
            var_f26 = VECMag(&spC);
            arg2->x = 0.5f * var_f26 + temp_r28->unkEC;
            arg2->z = 0.0f;
        }
        else if (temp_r28->unkEC < 0.0f && sp24.x < temp_r31->trans.x) {
            spC = *arg1;
            spC.y = 0.0f;
            var_f26 = VECMag(&spC);
            arg2->x = -(0.5f * var_f26) + temp_r28->unkEC;
            arg2->z = 0.0f;
        }
        else {
            if (fabs(arg1->x) > fabs(arg1->z)) {
                arg2->x *= -1.0f;
            }
            else {
                arg2->z *= -1.0f;
            }
            arg2->x *= 0.5f;
            arg2->z *= 0.5f;
        }
        fn_1_82C8(15, 1, 0);
        return 1;
    }
    return 0;
}

void fn_1_82C8(s32 arg0, s32 arg1, s32 arg2)
{
    omObjData *var_r31;
    StructBssBCData *var_r30;

    if (lbl_1_bss_B8 != NULL) {
        var_r31 = lbl_1_bss_B8;
        var_r30 = var_r31->data;
        omVibrate(var_r30->unk00, 12, 6, 6);
        HuAudFXPlay(0x61A);
    }
}

s32 lbl_1_data_668[] = { 3, 4, 5, 6 };
float lbl_1_data_678[] = { 0.6f, 0.65f, 0.7f, 0.7f };

s32 lbl_1_data_688[][2] = {
    { REFRESH_RATE / 2, REFRESH_RATE },
    { REFRESH_RATE / 2.5, REFRESH_RATE / 1.25 },
    { REFRESH_RATE / 5, REFRESH_RATE / 2.5 },
    { 0, REFRESH_RATE / 5 }
};

s32 lbl_1_data_6A8[][2] = {
    { REFRESH_RATE * 0.6, REFRESH_RATE * 1.4 },
    { REFRESH_RATE * 0.6, REFRESH_RATE * 1.3 },
    { REFRESH_RATE * 0.55, REFRESH_RATE * 1.2 },
    { REFRESH_RATE * 0.55, REFRESH_RATE * 1.1 }
};

void fn_1_8338(omObjData *arg0)
{
    float var_f31;
    float temp_f30;
    StructBssBCData *temp_r31;
    ModelData *sp8;
    s32 var_r29;

    temp_r31 = arg0->data;
    sp8 = &Hu3DData[arg0->model[0]];
    var_r29 = temp_r31->unk18;
    if (temp_r31->unkA0 == 0) {
        temp_r31->unkA0 = 1;
        temp_r31->unk70 = 0;
        var_r29 = 5;
    }
    switch (var_r29) {
        case 5:
            if (temp_r31->unk70 != 0) {
                break;
            }
            if (temp_r31->unk9C > lbl_1_bss_108 && lbl_1_data_668[temp_r31->unk08] > temp_r31->unk98 && lbl_1_bss_B8 != NULL) {
                temp_r31->unkA4 = 1;
                temp_r31->unkA8 = (1.0f / 127) * frand7();
                if (lbl_1_bss_B8->trans.x >= 270.0f) {
                    temp_r31->unk88 = -(0.4f + 0.3f * temp_r31->unkA8);
                }
                else if (lbl_1_bss_B8->trans.x <= -270.0f) {
                    temp_r31->unk88 = 0.4f + 0.3f * temp_r31->unkA8;
                }
                else if (frand() & 1) {
                    temp_r31->unk88 = -(0.3f + 0.1f * temp_r31->unkA8);
                }
                else {
                    temp_r31->unk88 = 0.3f + 0.1f * temp_r31->unkA8;
                }
                var_f31 = lbl_1_data_6A8[3][0];
                temp_f30 = lbl_1_data_6A8[3][1];
                temp_r31->unk70 = var_f31 + (1.0f / 127) * frand7() * (temp_f30 - var_f31);
                var_f31 = lbl_1_data_688[temp_r31->unk08][0];
                temp_f30 = lbl_1_data_688[temp_r31->unk08][1];
                temp_r31->unk74 = var_f31 + (1.0f / 127) * frand7() * (temp_f30 - var_f31);
                temp_r31->unk98++;
            }
            else {
                if (frand() & 1) {
                    temp_r31->unk88 = (1.0f / 127) * frand7() * lbl_1_data_678[temp_r31->unk08];
                }
                else {
                    temp_r31->unk88 = -((1.0f / 127) * frand7()) * lbl_1_data_678[temp_r31->unk08];
                }
                var_f31 = lbl_1_data_6A8[temp_r31->unk08][0];
                temp_f30 = lbl_1_data_6A8[temp_r31->unk08][1];
                temp_r31->unk70 = var_f31 + (1.0f / 127) * frand7() * (temp_f30 - var_f31);
                var_f31 = lbl_1_data_688[temp_r31->unk08][0];
                temp_f30 = lbl_1_data_688[temp_r31->unk08][1];
                temp_r31->unk74 = var_f31 + (1.0f / 127) * frand7() * (temp_f30 - var_f31);
            }
            temp_r31->unk6C = 0;
            break;
        case 6:
            if (++temp_r31->unk6C >= temp_r31->unk74) {
                temp_r31->unk12 = 80.0f * temp_r31->unk88;
                temp_r31->unk10 |= PAD_BUTTON_A;
                temp_r31->unk0E |= PAD_BUTTON_A;
                temp_r31->unk6C = 0;
                return;
            }
            var_f31 = sind(180.0f * ((temp_r31->unk74 - temp_r31->unk6C) / REFRESH_RATE_F));
            if (temp_r31->unk74 & 1) {
                var_f31 *= -1.0f;
            }
            temp_r31->unk12 = 80.0f * (temp_r31->unk88 + var_f31);
            return;
        case 7:
            if (temp_r31->unkA4 != 0) {
                if (lbl_1_bss_B8->trans.x >= 148.5f) {
                    temp_r31->unk88 = -(0.4f + 0.3f * temp_r31->unkA8);
                }
                else if (lbl_1_bss_B8->trans.x <= -148.5f) {
                    temp_r31->unk88 = 0.4f + 0.3f * temp_r31->unkA8;
                }
                else if (lbl_1_bss_B8->trans.x > 0.0f) {
                    temp_r31->unk88 = -(0.5f + 0.2f * temp_r31->unkA8);
                }
                else {
                    temp_r31->unk88 = 0.5f + 0.2f * temp_r31->unkA8;
                }
            }
            temp_r31->unk12 = 80.0f * temp_r31->unk88;
            if (++temp_r31->unk6C > temp_r31->unk70) {
                temp_r31->unk88 = 0.0f;
                temp_r31->unk6C = 0;
                temp_r31->unk70 = 0;
                temp_r31->unk74 = 0;
                temp_r31->unkA4 = 0;
            }
            else {
                temp_r31->unk0E |= PAD_BUTTON_A;
            }
            break;
        default:
            temp_r31->unk6C = 0;
            break;
    }
}

s32 lbl_1_data_6C8[] = {
    REFRESH_RATE * 1,
    REFRESH_RATE * 0.75,
    REFRESH_RATE * 0.5,
    REFRESH_RATE * 0.25
};

float lbl_1_data_6D8[][2] = { { 200.0f, 150.0f }, { 125.0f, 100.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } };

s32 lbl_1_data_6F8[][2] = {
    { REFRESH_RATE * 0.8, REFRESH_RATE * 2.5 },
    { REFRESH_RATE * 0.65, REFRESH_RATE * 1.9 },
    { REFRESH_RATE * 0.55, REFRESH_RATE * 1.5 },
    { REFRESH_RATE * 0.35, REFRESH_RATE * 0.7 }
};

s32 lbl_1_data_718[][2] = {
    { REFRESH_RATE * 0.45, REFRESH_RATE * 0.65 },
    { REFRESH_RATE * 0.25, REFRESH_RATE * 0.45 },
    { REFRESH_RATE * 0.15, REFRESH_RATE * 0.25 },
    { 0, REFRESH_RATE * 0.05 }
};

void fn_1_8CB4(omObjData *arg0)
{
    Vec spC;
    float temp_f29;
    float temp_f28;
    float var_f30;
    float var_f31;
    float var_f26; // ! - uninitialized
    float temp_f27;
    StructBssBCData *temp_r31;
    ModelData *sp8;
    StructBssA8Data *temp_r30;
    s32 var_r28;
    s32 var_r24;
    s32 i, j;
    s32 var_r25;

    var_r25 = 0;
    temp_r31 = arg0->data;
    sp8 = &Hu3DData[arg0->model[0]];
    if (temp_r31->unk64 != -1) {
        temp_r30 = fn_1_B13C(temp_r31->unk64);
        if (temp_r30 != NULL) {
            if (temp_r30->unk0C != 3 || temp_r30->unk08 != 0 || temp_r30->unk38.z <= -900.0f) {
                var_r25 = 1;
            }
        }
        else {
            var_r25 = 1;
        }
    }
    else {
        var_r25 = 1;
    }
    if (var_r25 != 0) {
        temp_r31->unk64 = -1;
        temp_r31->unk6C = 0;
        temp_f29 = lbl_1_data_6F8[temp_r31->unk08][0];
        temp_f28 = lbl_1_data_6F8[temp_r31->unk08][1];
        temp_r31->unk90 = temp_f29 + (1.0f / 127) * frand7() * (temp_f28 - temp_f29);
        temp_f29 = lbl_1_data_718[temp_r31->unk08][0];
        temp_f28 = lbl_1_data_718[temp_r31->unk08][1];
        temp_r31->unk94 = temp_f29 + (1.0f / 127) * frand7() * (temp_f28 - temp_f29);
        temp_r31->unkD4.x = lbl_1_data_6D8[temp_r31->unk08][0] * (0.5f - (1.0f / 127) * frand7());
        temp_r31->unkD4.y = lbl_1_data_6D8[temp_r31->unk08][1] * (0.5f - (1.0f / 127) * frand7());
        if (lbl_1_bss_104 >= 5) {
            temp_r31->unkD4.x *= 1.5f;
        }
        var_r24 = fn_1_B304(lbl_1_bss_4);
        if (var_r24 != 0) {
            for (i = 0; i < var_r24; i++) {
                temp_r30 = lbl_1_bss_4[i];
                if (temp_r30 == NULL || temp_r30->unk06 == 0 || 0.0f == temp_r30->unk50.z || fabs(temp_r30->unk38.x) >= 325.0
                    || temp_r30->unk14 < temp_r31->unk94) {
                    continue;
                }
                var_r28 = (var_f26 - temp_r30->unk38.z) / temp_r30->unk50.z;
                if (var_r28 > REFRESH_RATE_F * 5) {
                    continue;
                }
                spC = temp_r30->unk50;
                var_f30 = temp_r30->unk38.x;
                var_f31 = temp_r30->unk38.y;
                for (j = 0; j < var_r28; j++) {
                    var_f30 += spC.x;
                    var_f31 += spC.y;
                    spC.x *= temp_r30->unk8C;
                    spC.z *= temp_r30->unk8C;
                    spC.y -= 19.6f / REFRESH_RATE_F;
                    if (var_f31 < 20.0) {
                        var_f31 = 19.6f / REFRESH_RATE_F;
                        spC.y *= temp_r30->unk90;
                    }
                }
                var_f30 += temp_r31->unkD4.x;
                var_f31 += temp_r31->unkD4.y;
                if (temp_r31->unk08 <= 2 || !(fabs(var_f30) >= 225.0 || var_f31 >= 200.0f)) {
                    temp_r31->unk64 = temp_r30->unk02;
                    break;
                }
            }
        }
    }
    if (temp_r31->unk64 != -1 && (temp_r30 = fn_1_B13C(temp_r31->unk64)) != NULL) {
        if (temp_r30->unk38.z > 60.000004f + arg0->trans.z) {
            var_f26 = 60.000004f + arg0->trans.z;
            var_r28 = (var_f26 - temp_r30->unk38.z) / temp_r30->unk50.z;
            if (var_r28 > REFRESH_RATE_F * 5) {
                temp_r31->unk64 = -1;
                return;
            }
            spC = temp_r30->unk50;
            var_f30 = temp_r30->unk38.x;
            var_f31 = temp_r30->unk38.y;
            for (j = 0; j < var_r28; j++) {
                var_f30 += spC.x;
                var_f31 += spC.y;
                spC.x *= temp_r30->unk8C;
                spC.z *= temp_r30->unk8C;
                spC.y -= 19.6f / REFRESH_RATE_F;
                if (var_f31 < 20.0) {
                    var_f31 = 19.6f / REFRESH_RATE_F;
                    spC.y *= temp_r30->unk90;
                }
            }
            var_r28 += temp_r31->unk90;
            var_f30 += temp_r31->unkD4.x;
            var_f31 += temp_r31->unkD4.y;
        }
        else {
            var_r28 = 0;
            var_f30 = temp_r30->unk38.x;
            var_f31 = temp_r30->unk38.y;
        }
        if (arg0->trans.x - 25.0f > var_f30) {
            temp_r31->unk12 = -64;
        }
        if (arg0->trans.x + 25.0f < var_f30) {
            temp_r31->unk12 = 64;
        }
        temp_f27 = fabs(var_f30 - arg0->trans.x);
        if (var_r28 < 10 && temp_f27 > 120.00001f) {
            temp_r31->unk10 |= 0x100;
        }
        else if (var_r28 < 5 && temp_f27 < 25.0f && var_f31 > 100.0f) {
            temp_r31->unk10 |= 0x100;
        }
        else if (var_r28 > 20 && temp_f27 < 50.0) {
            temp_r31->unk10 /= 2;
        }
        if (++temp_r31->unk6C > lbl_1_data_6C8[temp_r31->unk08]) {
            temp_r31->unk64 = -1;
        }
    }
}

void fn_1_95C4(void)
{
    lbl_1_bss_A8 = omAddObjEx(lbl_1_bss_120, 0x50, 0, 0, -1, fn_1_9614);
}

s32 lbl_1_data_738[]
    = { DATA_MAKE_NUM(DATADIR_M423, 4), DATA_MAKE_NUM(DATADIR_M423, 5), DATA_MAKE_NUM(DATADIR_M423, 6), DATA_MAKE_NUM(DATADIR_M423, 7),
          DATA_MAKE_NUM(DATADIR_M423, 8), DATA_MAKE_NUM(DATADIR_M423, 9), DATA_MAKE_NUM(DATADIR_M423, 10), DATA_MAKE_NUM(DATADIR_M423, 11) };

void fn_1_9614(omObjData *arg0)
{
    StructBssA8Data *var_r28;
    StructBssA8Data *var_r31;
    ModelData *var_r27;
    s32 i;

    if (lbl_1_bss_EC[0] == -1) {
        return;
    }
    var_r31 = var_r28 = arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 15 * sizeof(*var_r31), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 15 * sizeof(*var_r31));
    for (i = 0; i < 15; i++, var_r31++) {
        var_r31->unk04 = i % 3;
        var_r31->unk02 = i;
        var_r31->unk06 = 0;
        var_r31->unk0A = 0;
        var_r31->unk08 = 0;
        var_r31->unk0C = 0;
        var_r31->unk0E = 0;
        var_r31->unk10 = 0;
        var_r31->unk12 = 0;
        var_r31->unk14 = 0;
        var_r31->unk18 = 0;
        var_r31->unk1C = 0;
        var_r31->unk38.x = var_r31->unk38.y = var_r31->unk38.z = 0.0f;
        var_r31->unk44 = var_r31->unk48 = var_r31->unk4C = 0.0f;
        var_r31->unk50.x = var_r31->unk50.y = var_r31->unk50.z = 0.0f;
        var_r31->unk74 = var_r31->unk38;
        var_r31->unk80 = var_r31->unk50;
        var_r31->unk8C = 0.995f;
        var_r31->unk90 = -0.5f;
        var_r31->unk68.x = var_r31->unk68.y = var_r31->unk68.z = 0.0f;
        if (i < 3) {
            var_r31->unk00 = Hu3DModelCreateFile(lbl_1_data_738[lbl_1_bss_EC[var_r31->unk04]]);
        }
        else {
            var_r31->unk00 = Hu3DModelLink(var_r28[var_r31->unk04].unk00);
        }
        Hu3DModelScaleSet(var_r31->unk00, 0.8f, 0.8f, 0.8f);
        Hu3DModelAttrSet(var_r31->unk00, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(var_r31->unk00, 5);
        Hu3DModelShadowSet(var_r31->unk00);
        var_r27 = &Hu3DData[var_r31->unk00];
        MTXIdentity(var_r27->unk_F0);
    }
    fn_1_B430();
    arg0->func = fn_1_98A0;
}

void fn_1_98A0(omObjData *arg0)
{
    Mtx spC4;
    Vec spB8;
    Vec spAC;
    Vec spA0;
    Vec sp94;
    Vec sp88;
    float temp_f30;
    float var_f25;
    float var_f31;
    float var_f22;
    StructBssA8Data *var_r31;
    StructBssA8Data *var_r30;
    ModelData *temp_r27;
    s32 i, j;
    s32 var_r25;
    s32 var_r23;
    s32 var_r28;

    var_r31 = arg0->data;
    for (i = 0; i < 15; i++, var_r31++) {
        if (var_r31->unk06 == 0) {
            continue;
        }
        temp_r27 = &Hu3DData[var_r31->unk00];
        var_r25 = 0;
        switch (var_r31->unk0C) {
            case 0:
                break;
            case 1:
                temp_f30 = var_r31->unk14 / REFRESH_RATE_F;
                var_r31->unk14++;
                if (temp_f30 > 1.0f) {
                    var_f31 = 1.0f;
                }
                else {
                    var_f31 = temp_f30;
                }
                var_r31->unk38.x = var_r31->unk20.x + var_f31 * (var_r31->unk2C.x - var_r31->unk20.x);
                var_r31->unk38.z = var_r31->unk20.z + var_f31 * (var_r31->unk2C.z - var_r31->unk20.z);
                if (temp_f30 < 0.6f) {
                    var_f31 = temp_f30 / 0.6f;
                    var_f25 = 100.0f;
                }
                else if (temp_f30 < 1.0f) {
                    var_f31 = (temp_f30 - 0.6f) / 0.4f;
                    var_f25 = 50.0f;
                }
                else {
                    var_f31 = (temp_f30 - 1.0f) / 0.25f;
                    var_f25 = 10.0f;
                }
                var_r31->unk38.y = 20.0 + var_f25 * sind(180.0f * var_f31);
                if (var_r31->unk14 >= REFRESH_RATE_F * 1.25f) {
                    var_r31->unk0C = 2;
                    var_r31->unk14 = 0;
                    var_r31->unk38.y = 20.0f;
                    var_r31->unk50.y = 0.0f;
                }
                if (var_r31->unk14 < REFRESH_RATE_F * 1.22f) {
                    spAC.x = var_r31->unk50.z;
                    spAC.z = -var_r31->unk50.x;
                    spAC.y = 0.0f;
                    var_f31 = 0.05 * VECMag(&spAC);
                    if (var_f31 > 0.00001f) {
                        MTXRotAxisRad(spC4, &spAC, var_f31);
                        MTXConcat(spC4, temp_r27->unk_F0, temp_r27->unk_F0);
                    }
                }
                Hu3DModelPosSet(var_r31->unk00, var_r31->unk38.x, var_r31->unk38.y, var_r31->unk38.z);
                Hu3DModelRotSet(var_r31->unk00, var_r31->unk44, var_r31->unk48, var_r31->unk4C);
                break;
            case 2:
                Hu3DModelPosSet(var_r31->unk00, var_r31->unk38.x, var_r31->unk38.y, var_r31->unk38.z);
                Hu3DModelRotSet(var_r31->unk00, var_r31->unk44, var_r31->unk48, var_r31->unk4C);
                break;
            case 3:
                var_r31->unk74 = var_r31->unk38;
                var_r31->unk80 = var_r31->unk50;
                var_r23 = 0;
                if (var_r28 = fn_1_C498(&var_r31->unk38, &var_r31->unk50, &spB8, &sp88, 20.0f, 3)) {
                    if (var_r28 & 0x8000) {
                        var_r25 = 1;
                    }
                    if (var_r28 & 0x2000) { }
                    if ((var_r28 & 0x4000) && var_r31->unk12 == 0 && var_r31->unk08 == 0) {
                        var_f31 = VECMagXZ(&var_r31->unk50);
                        sp94.x = 0.0f;
                        sp94.y = 0.0f;
                        sp94.z = (1.0f / 127) * frand7() * 360.0f;
                        fn_1_E334(spB8, sp94, 0.5f);
                        HuAudFXPlay(0x620);
                        var_r31->unk12 = 1;
                    }
                    var_r31->unk38 = spB8;
                    var_r31->unk50 = sp88;
                    var_r31->unk8C = 0.975f;
                    var_r31->unk90 = -0.5f;
                }
                else {
                    if (fabs(var_r31->unk38.x) > 1000.0) {
                        Hu3DModelAttrSet(var_r31->unk00, HU3D_ATTR_DISPOFF);
                        var_r31->unk0C = 0;
                        var_r31->unk06 = 0;
                        var_r31->unk14 = 0;
                    }
                    else {
                        var_r31->unk38.x += var_r31->unk50.x;
                        var_r31->unk38.y += var_r31->unk50.y;
                        var_r31->unk38.z += var_r31->unk50.z;
                    }
                }
                if (var_r31->unk08 == 0) {
                    for (j = 0, var_r30 = arg0->data; j < 15; j++, var_r30++) {
                        if (i == j || var_r30->unk06 == 0 || var_r30->unk08 != 0 || var_r30->unk0C != 3) {
                            continue;
                        }
                        VECSubtract(&var_r31->unk38, &var_r30->unk38, &spAC);
                        var_f31 = VECMag(&spAC);
                        if (var_f31 < 40.0) {
                            spA0 = var_r31->unk38;
                            if (var_f31 != 0.0f) {
                                temp_f30 = 40.0 - var_f31;
                                VECNormalize(&spAC, &spAC);
                                VECScale(&spAC, &spAC, temp_f30);
                                VECAdd(&var_r31->unk38, &spAC, &var_r31->unk38);
                            }
                            else {
                                var_r31->unk38.x += 40.0;
                            }
                            temp_f30 = VECMag(&var_r31->unk50);
                            var_f22 = VECMag(&var_r30->unk50);
                            var_f31 = 0.5f * (temp_f30 + var_f22);
                            if (VECMag(&var_r31->unk50) == 0.0f) {
                                var_r31->unk50.x = 1.0f;
                            }
                            VECNormalize(&var_r31->unk50, &var_r31->unk50);
                            VECSubtract(&var_r31->unk38, &var_r30->unk38, &spAC);
                            if (VECMag(&spAC) == 0.0f) {
                                spAC.x = 1.0f;
                            }
                            VECNormalize(&spAC, &spAC);
                            VECAdd(&var_r31->unk50, &spAC, &var_r31->unk50);
                            if (VECMag(&var_r31->unk50) == 0.0f) {
                                var_r31->unk50.x = 1.0f;
                            }
                            VECNormalize(&var_r31->unk50, &var_r31->unk50);
                            VECScale(&var_r31->unk50, &var_r31->unk50, var_f31);
                            if (VECMag(&var_r30->unk50) == 0.0f) {
                                var_r30->unk50.x = -1.0f;
                            }
                            VECNormalize(&var_r30->unk50, &var_r30->unk50);
                            VECSubtract(&var_r30->unk38, &var_r31->unk38, &spAC);
                            if (VECMag(&spAC) == 0.0f) {
                                spAC.x = 1.0f;
                            }
                            VECNormalize(&spAC, &spAC);
                            VECAdd(&var_r30->unk50, &spAC, &var_r30->unk50);
                            if (VECMag(&var_r30->unk50) == 0.0f) {
                                var_r30->unk50.x = -1.0f;
                            }
                            VECNormalize(&var_r30->unk50, &var_r30->unk50);
                            VECScale(&var_r30->unk50, &var_r30->unk50, var_f31);
                            if (var_r28 = fn_1_C498(&spA0, &spAC, &spB8, &sp88, 20.0f, 1)) {
                                if (var_r28 & 0x8000) {
                                    var_r25 = 1;
                                }
                                var_r31->unk38 = spB8;
                                var_r31->unk50 = sp88;
                            }
                        }
                    }
                }
                if (var_r31->unk38.y < 20.0) {
                    var_r31->unk38.y = 20.0f;
                    var_r31->unk50.y *= var_r31->unk90;
                    var_r23 = 1;
                    if (var_r31->unk38.x >= -225.0f && var_r31->unk38.x <= 225.0f && var_r31->unk38.z >= -1100.0f && var_r31->unk38.z <= -900.0f) {
                        var_r25 = 1;
                    }
                    if (fabs(var_r31->unk50.y) < 0.05f) {
                        var_r31->unk50.y = 0.0f;
                    }
                }
                if (var_r31->unk08 == 0) {
                    VECSubtract(&var_r31->unk38, &var_r31->unk74, &spAC);
                    if (fn_1_7B48(&var_r31->unk38, &var_r31->unk50, &sp88, 20.0f) != 0) {
                        var_r31->unk50 = sp88;
                        var_r31->unk08 = 1;
                        var_r31->unk8C = 0.975f;
                        var_r31->unk90 = -0.5f;
                    }
                }
                if (var_r31->unk50.z > 0.0f) {
                    var_r31->unk08 = 1;
                }
                var_r31->unk50.y -= 19.6f / REFRESH_RATE_F;
                if (var_r23 == 0) {
                    var_r31->unk50.x *= var_r31->unk8C;
                    var_r31->unk50.z *= var_r31->unk8C;
                }
                else {
                    var_r31->unk50.x *= 0.995f * var_r31->unk8C;
                    var_r31->unk50.z *= 0.995f * var_r31->unk8C;
                }
                if (var_r25 != 0 && var_r31->unk0A == 0 && var_r31->unk08 == 0) {
                    fn_1_AEE8(i);
                }
                if (var_r31->unk08 != 0) {
                    var_r31->unk18++;
                    if (var_r31->unk18 & 1) {
                        Hu3DModelAttrReset(var_r31->unk00, HU3D_ATTR_DISPOFF);
                    }
                    else {
                        Hu3DModelAttrSet(var_r31->unk00, HU3D_ATTR_DISPOFF);
                    }
                    if (var_r31->unk18 >= REFRESH_RATE_F * 2) {
                        Hu3DModelAttrSet(var_r31->unk00, HU3D_ATTR_DISPOFF);
                        var_r31->unk0C = 0;
                        var_r31->unk06 = 0;
                        var_r31->unk14 = 0;
                        var_r31->unk18 = 0;
                    }
                }
                temp_f30 = VECMagXZ(&var_r31->unk50);
                if (fabs(temp_f30) < 0.1f && var_r31->unk38.y <= 20.0 && var_r31->unk08 == 0) {
                    var_r31->unk0C = 4;
                    var_r31->unk14 = 0;
                    var_r31->unk18 = 0;
                }
                if (fabs(var_r31->unk38.x) > 2000.0 || fabs(var_r31->unk38.y) > 2000.0 || fabs(var_r31->unk38.z) > 2000.0) {
                    var_r31->unk0C = 4;
                    var_r31->unk14 = 0;
                    var_r31->unk18 = REFRESH_RATE * 2;
                }
                var_r31->unk14++;
                spAC.x = var_r31->unk50.z;
                spAC.z = -var_r31->unk50.x;
                spAC.y = 0.0f;
                var_f31 = 0.05 * VECMag(&spAC);
                if (var_f31 > 0.00001f) {
                    MTXRotAxisRad(spC4, &spAC, var_f31);
                    MTXConcat(spC4, temp_r27->unk_F0, temp_r27->unk_F0);
                }
                Hu3DModelPosSet(var_r31->unk00, var_r31->unk38.x, var_r31->unk38.y, var_r31->unk38.z);
                break;
            case 4:
                var_r31->unk18++;
                if (var_r31->unk18 & 1) {
                    Hu3DModelAttrReset(var_r31->unk00, HU3D_ATTR_DISPOFF);
                }
                else {
                    Hu3DModelAttrSet(var_r31->unk00, HU3D_ATTR_DISPOFF);
                }
                if (var_r31->unk18 >= REFRESH_RATE_F * 2) {
                    Hu3DModelAttrSet(var_r31->unk00, HU3D_ATTR_DISPOFF);
                    var_r31->unk0C = 0;
                    var_r31->unk06 = 0;
                    var_r31->unk14 = 0;
                    var_r31->unk18 = 0;
                }
                break;
        }
    }
}

void fn_1_A9A0(omObjData *arg0)
{
    arg0->func = NULL;
}

void fn_1_A9AC(void)
{
    fn_1_A9A0(lbl_1_bss_A8);
}

s32 fn_1_A9D4(s32 arg0, Vec arg1, Vec arg2)
{
    StructBssA8Data *var_r31;
    ModelData *temp_r26;
    s32 var_r27;
    s32 i;

    if (lbl_1_bss_A8 == NULL) {
        return -1;
    }
    var_r31 = lbl_1_bss_A8->data;
    for (i = 0, var_r27 = -1; i < 3; i++) {
        if (arg0 == lbl_1_bss_EC[i]) {
            var_r27 = i;
        }
    }
    if (var_r27 == -1) {
        return -1;
    }
    for (i = 0; i < 15; i++, var_r31++) {
        if (var_r31->unk04 == var_r27 && var_r31->unk06 == 0) {
            break;
        }
    }
    if (i >= 15) {
        return -1;
    }
    temp_r26 = &Hu3DData[var_r31->unk00];
    var_r31->unk06 = 1;
    var_r31->unk0A = 0;
    var_r31->unk08 = 0;
    var_r31->unk10 = 0;
    var_r31->unk12 = 0;
    var_r31->unk0C = 1;
    var_r31->unk14 = 0;
    var_r31->unk18 = 0;
    var_r31->unk20 = arg1;
    var_r31->unk2C = arg2;
    var_r31->unk38 = arg1;
    var_r31->unk44 = var_r31->unk48 = var_r31->unk4C = 0.0f;
    var_r31->unk50.x = 0.016666668f * (arg2.x - arg1.x); //! not updated for PAL
    var_r31->unk50.z = 0.016666668f * (arg2.z - arg1.z);
    var_r31->unk50.y = 5.0f;
    Hu3DModelPosSet(var_r31->unk00, var_r31->unk38.x, var_r31->unk38.y, var_r31->unk38.z);
    Hu3DModelRotSet(var_r31->unk00, var_r31->unk44, var_r31->unk48, var_r31->unk4C);
    Hu3DModelAttrReset(var_r31->unk00, HU3D_ATTR_DISPOFF);
    MTXIdentity(temp_r26->unk_F0);
    return i;
}

void fn_1_AC0C(s32 arg0, Vec arg1)
{
    StructBssA8Data *var_r31;

    if (lbl_1_bss_A8 != NULL) {
        var_r31 = lbl_1_bss_A8->data;
        if (arg0 < 0 || arg0 >= 15) {
            return;
        }
        var_r31[arg0].unk38 = arg1;
    }
}

void fn_1_AC80(s32 arg0, Vec arg1)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    StructBssA8Data *var_r28;
    StructBssA8Data *temp_r31;

    if (lbl_1_bss_A8 == NULL) {
        return;
    }
    var_r28 = lbl_1_bss_A8->data;
    if (arg0 < 0 || arg0 >= 15) {
        return;
    }
    temp_r31 = &var_r28[arg0];
    temp_r31->unk0C = 3;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0;
    temp_r31->unk50 = arg1;
    temp_r31->unk74 = temp_r31->unk38;
    temp_r31->unk8C = 0.995f;
    temp_r31->unk90 = -0.5f;
    if (temp_r31->unk50.z < 0.0f) {
        sp14 = temp_r31->unk38;
        var_f31 = -800.0f - sp14.z;
        temp_r31->unk1C = fabs(var_f31 / temp_r31->unk50.z);
        VECScale(&arg1, &sp8, temp_r31->unk1C);
        VECAdd(&sp14, &sp8, &temp_r31->unk68);
    }
    else {
        temp_r31->unk1C = 1000;
    }
}

s32 fn_1_AE64(s32 arg0)
{
    StructBssA8Data *temp_r31;

    if (lbl_1_bss_A8 == NULL) {
        return -1;
    }
    temp_r31 = lbl_1_bss_A8->data;
    if (arg0 < 0 || arg0 >= 15) {
        return -1;
    }
    if (temp_r31[arg0].unk06 == 0) {
        return -1;
    }
    return temp_r31[arg0].unk0C;
}

void fn_1_AEE8(s32 arg0)
{
    StructBssA8Data *var_r26;
    StructBssA8Data *temp_r31;

    if (lbl_1_bss_A8 == NULL) {
        return;
    }
    var_r26 = lbl_1_bss_A8->data;
    if (arg0 < 0 || arg0 >= 15) {
        return;
    }
    temp_r31 = &var_r26[arg0];
    temp_r31->unk0A = 1;
    temp_r31->unk08 = 1;
    temp_r31->unk14 = 0;
    fn_1_F574(temp_r31->unk38, 0.75f, lbl_1_bss_EC[temp_r31->unk04]);
    HuAudFXPlay(9);
    fn_1_3A8C();
    lbl_1_bss_DC[temp_r31->unk04]++;
    lbl_1_bss_104--;
}

StructBssA8Data *fn_1_B13C(s32 arg0)
{
    StructBssA8Data *temp_r31;
    StructBssA8Data *sp8;

    if (lbl_1_bss_A8 == NULL) {
        return NULL;
    }
    temp_r31 = lbl_1_bss_A8->data;
    sp8 = temp_r31;
    if (arg0 < 0 || arg0 >= 15) {
        return NULL;
    }
    return &temp_r31[arg0];
}

GXColor lbl_1_data_758 = { 0xFF, 0xFF, 0xFF, 0xFF };

void fn_1_B1A4(void)
{
    Vec sp2C;
    StructBssA8Data *sp10;
    StructBssA8Data *var_r31;
    s32 spC;
    s32 i;

    if (lbl_1_bss_A8 == NULL) {
        return;
    }
    var_r31 = sp10 = lbl_1_bss_A8->data;
    for (i = 0, spC = 0; i < 15; i++, var_r31++) {
        if (var_r31->unk06 == 0) {
            continue;
        }
        sp2C.x = sp2C.y = sp2C.z = 0.0f;
        fn_1_DC24(var_r31->unk38, sp2C, 100.0f, 0.0f, 1.0f, lbl_1_data_758);
        Hu3DModelAttrSet(var_r31->unk00, HU3D_ATTR_DISPOFF);
        var_r31->unk0C = 0;
        var_r31->unk06 = 0;
        var_r31->unk14 = 0;
        var_r31->unk18 = 0;
    }
}

s32 fn_1_B304(StructBssA8Data **arg0)
{
    s32 var_r29;
    s32 i;
    StructBssA8Data *var_r30;
    StructBssA8Data *var_r28;
    StructBssA8Data *var_r27;

    if (lbl_1_bss_A8 == NULL) {
        return;
    }
    var_r30 = lbl_1_bss_A8->data;
    var_r28 = var_r30;
    for (i = 0, var_r29 = 0; i < 15; i++, var_r30++) {
        if (var_r30->unk06 == 0 || var_r30->unk0C != 3 || var_r30->unk08 != 0 || var_r30->unk38.z <= -900.0f) {
            continue;
        }
        arg0[var_r29] = var_r30;
        var_r29++;
    }
    var_r28 = var_r30;
    for (i = 0; i < var_r29 - 1; i++) {
        if (arg0[i]->unk38.z > arg0[i + 1]->unk38.z) {
            var_r27 = arg0[i];
            arg0[i] = arg0[i + 1];
            arg0[i + 1] = var_r27;
        }
    }
    return var_r29;
}

void fn_1_B430(void)
{
    Vec sp2C[8];
    Vec sp20;
    Vec sp14;
    Vec sp8;
    StructBss94Data *var_r31;
    s32 i;

    var_r31 = lbl_1_bss_94 = HuMemDirectMallocNum(HEAP_SYSTEM, 16 * sizeof(*lbl_1_bss_94), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, 16 * sizeof(*var_r31));
    for (i = 0; i < 16; i++, var_r31++) {
        var_r31->unk02 = 0;
    }
    sp20.x = sp20.y = 0.0f;
    sp20.z = -1400.0f;
    fn_1_BCD8(&sp20, NULL, NULL, 0.8f, 0, 0x2003);
    sp2C[0].x = 1000.0f;
    sp2C[0].y = 1000.0f;
    sp2C[0].z = -200.0f;
    sp2C[1].x = -1000.0f;
    sp2C[1].y = 1000.0f;
    sp2C[1].z = -200.0f;
    sp2C[2].x = -1000.0f;
    sp2C[2].y = 0.0f;
    sp2C[2].z = -200.0f;
    sp2C[3].x = 1000.0f;
    sp2C[3].y = 0.0f;
    sp2C[3].z = -200.0f;
    fn_1_BCD8(sp2C, NULL, NULL, 1.0f, 0, 6);
    sp20.x = -650.0f;
    sp20.y = 75.0f;
    sp20.z = -1300.0f;
    sp14.x = 370.0f;
    sp14.y = 1095.0f;
    sp14.z = 120.0f;
    fn_1_BCD8(&sp20, &sp14, NULL, 0.8f, 25, 0x2004);
    sp20.x = 650.0f;
    sp20.y = 75.0f;
    sp20.z = -1300.0f;
    sp14.x = 370.0f;
    sp14.y = 1095.0f;
    sp14.z = 120.0f;
    fn_1_BCD8(&sp20, &sp14, NULL, 0.8f, 21, 0x2004);
    sp20.x = 0.0f;
    sp20.y = 100.0f;
    sp20.z = -1070.0f;
    sp14.x = 245.0f;
    sp14.y = 130.0f;
    sp14.z = 170.0f;
    fn_1_BCD8(&sp20, &sp14, NULL, 1.0f, 45, 4);
    sp20.x = -235.0f;
    sp20.y = 0.0f;
    sp20.z = -900.0f;
    sp14.x = -235.0f;
    sp14.y = 200.0f;
    sp14.z = -900.0f;
    sp8.x = 30.000002f;
    sp8.y = sp8.z = 0.0f;
    fn_1_BCD8(&sp20, &sp14, &sp8, 0.5f, 0, 0x4007);
    sp20.x = 235.0f;
    sp20.y = 0.0f;
    sp20.z = -900.0f;
    sp14.x = 235.0f;
    sp14.y = 200.0f;
    sp14.z = -900.0f;
    sp8.x = 30.000002f;
    sp8.y = sp8.z = 0.0f;
    fn_1_BCD8(&sp20, &sp14, &sp8, 0.5f, 0, 0x4007);
    sp20.x = 0.0f;
    sp20.y = 200.0f;
    sp20.z = -900.0f;
    sp14.x = 245.0f;
    sp14.y = 30.0f;
    sp14.z = 30.0f;
    fn_1_BCD8(&sp20, &sp14, NULL, 0.5f, 29, 0x4004);
    sp2C[0].x = -225.0f;
    sp2C[0].y = 200.0f;
    sp2C[0].z = -900.0f;
    sp2C[1].x = -225.0f;
    sp2C[1].y = 200.0f;
    sp2C[1].z = -1150.0f;
    sp2C[2].x = -225.0f;
    sp2C[2].y = 0.0f;
    sp2C[2].z = -1150.0f;
    sp2C[3].x = -225.0f;
    sp2C[3].y = 0.0f;
    sp2C[3].z = -900.0f;
    fn_1_BCD8(sp2C, NULL, NULL, 0.5f, 0, 0x8006);
    sp2C[0].x = 225.0f;
    sp2C[0].y = 200.0f;
    sp2C[0].z = -1150.0f;
    sp2C[1].x = 225.0f;
    sp2C[1].y = 200.0f;
    sp2C[1].z = -900.0f;
    sp2C[2].x = 225.0f;
    sp2C[2].y = 0.0f;
    sp2C[2].z = -900.0f;
    sp2C[3].x = 225.0f;
    sp2C[3].y = 0.0f;
    sp2C[3].z = -1150.0f;
    fn_1_BCD8(sp2C, NULL, NULL, 0.5f, 0, 0x8006);
    sp2C[0].x = -225.0f;
    sp2C[0].y = 200.0f;
    sp2C[0].z = -1150.0f;
    sp2C[1].x = 225.0f;
    sp2C[1].y = 200.0f;
    sp2C[1].z = -1150.0f;
    sp2C[2].x = 225.0f;
    sp2C[2].y = 0.0f;
    sp2C[2].z = -1150.0f;
    sp2C[3].x = -225.0f;
    sp2C[3].y = 0.0f;
    sp2C[3].z = -1150.0f;
    fn_1_BCD8(sp2C, NULL, NULL, 0.1f, 0, 0x8006);
    sp2C[0].x = -225.0f;
    sp2C[0].y = 200.0f;
    sp2C[0].z = -900.0f;
    sp2C[1].x = 225.0f;
    sp2C[1].y = 200.0f;
    sp2C[1].z = -900.0f;
    sp2C[2].x = 225.0f;
    sp2C[2].y = 200.0f;
    sp2C[2].z = -1150.0f;
    sp2C[3].x = -225.0f;
    sp2C[3].y = 200.0f;
    sp2C[3].z = -1150.0f;
    fn_1_BCD8(sp2C, NULL, NULL, 0.1f, 0, 0x8006);
}

s16 lbl_1_data_75C[][3] = { { 0, 1, 2 }, { 1, 3, 2 }, { 6, 5, 4 }, { 5, 6, 7 }, { 0, 2, 4 }, { 2, 6, 4 }, { 3, 1, 7 }, { 7, 1, 5 }, { 2, 3, 6 },
    { 3, 7, 6 }, { 1, 0, 4 }, { 1, 4, 5 } };

void fn_1_BCD8(Vec *arg0, Vec *arg1, Vec *arg2, float arg3, s32 arg4, s32 arg5)
{
    Vec sp24[8];
    Vec sp18;
    float var_f29;
    StructBss94Data *var_r30;
    s32 i;
    s32 j;

    var_r30 = lbl_1_bss_94;
    for (i = 0; i < 16; i++, var_r30++) {
        if (var_r30->unk02 == 0) {
            break;
        }
    }
    if (i >= 16) {
        return;
    }
    var_r30->unk00 = i;
    var_r30->unk02 = arg5;
    var_r30->unk3C = arg3;
    switch (var_r30->unk02 & 0xFFF) {
        case 1:
            var_r30->unk34 = arg0[0].x;
            break;
        case 2:
            var_r30->unk34 = arg0[0].y;
            break;
        case 3:
            var_r30->unk34 = arg0[0].z;
            break;
        case 4:
            var_r30->unk04 = arg0[0];
            var_r30->unk10 = *arg1;
            sp24[0].x = arg0[0].x - arg1->x;
            sp24[0].y = arg0[0].y + arg1->y;
            sp24[0].z = arg0[0].z - arg1->z;
            sp24[1].x = arg0[0].x + arg1->x;
            sp24[1].y = arg0[0].y + arg1->y;
            sp24[1].z = arg0[0].z - arg1->z;
            sp24[2].x = arg0[0].x - arg1->x;
            sp24[2].y = arg0[0].y + arg1->y;
            sp24[2].z = arg0[0].z + arg1->z;
            sp24[3].x = arg0[0].x + arg1->x;
            sp24[3].y = arg0[0].y + arg1->y;
            sp24[3].z = arg0[0].z + arg1->z;
            sp24[4].x = arg0[0].x - arg1->x;
            sp24[4].y = arg0[0].y - arg1->y;
            sp24[4].z = arg0[0].z - arg1->z;
            sp24[5].x = arg0[0].x + arg1->x;
            sp24[5].y = arg0[0].y - arg1->y;
            sp24[5].z = arg0[0].z - arg1->z;
            sp24[6].x = arg0[0].x - arg1->x;
            sp24[6].y = arg0[0].y - arg1->y;
            sp24[6].z = arg0[0].z + arg1->z;
            sp24[7].x = arg0[0].x + arg1->x;
            sp24[7].y = arg0[0].y - arg1->y;
            sp24[7].z = arg0[0].z + arg1->z;
            for (j = 0; j < 12; j++) {
                fn_1_129F0(&sp24[lbl_1_data_75C[j][0]], &sp24[lbl_1_data_75C[j][1]], &sp24[lbl_1_data_75C[j][2]], var_r30->unk44[j]);
                var_r30->unk104[j][0] = sp24[lbl_1_data_75C[j][0]];
                var_r30->unk104[j][1] = sp24[lbl_1_data_75C[j][1]];
                var_r30->unk104[j][2] = sp24[lbl_1_data_75C[j][2]];
            }
            var_r30->unk40 = arg4;
            break;
        case 5:
            var_r30->unk104[0][0] = arg0[0];
            var_r30->unk104[1][0] = arg0[1];
            var_r30->unk104[2][0] = arg0[2];
            var_r30->unk104[3][0] = arg0[3];
            fn_1_129F0(&arg0[0], &arg0[1], &arg0[3], var_r30->unk44[0]);
            fn_1_129F0(&arg0[1], &arg0[2], &arg0[3], var_r30->unk44[1]);
            break;
        case 6:
            var_r30->unk104[0][0] = arg0[0];
            var_r30->unk104[1][0] = arg0[1];
            var_r30->unk104[2][0] = arg0[2];
            var_r30->unk104[3][0] = arg0[3];
            fn_1_129F0(&arg0[0], &arg0[1], &arg0[3], var_r30->unk44[0]);
            fn_1_129F0(&arg0[1], &arg0[2], &arg0[3], var_r30->unk44[1]);
            if (var_r30->unk44[0][1] < -0.5f) {
                var_r30->unk40 = 0;
            }
            if (var_r30->unk44[0][1] > 0.5f) {
                var_r30->unk40 = 1;
            }
            if (var_r30->unk44[0][0] > 0.5f) {
                var_r30->unk40 = 2;
            }
            if (var_r30->unk44[0][0] < -0.5f) {
                var_r30->unk40 = 3;
            }
            if (var_r30->unk44[0][2] < -0.5f) {
                var_r30->unk40 = 4;
            }
            if (var_r30->unk44[0][2] > 0.5f) {
                var_r30->unk40 = 5;
            }
            break;
        case 7:
            var_r30->unk04 = arg0[0];
            var_r30->unk10 = *arg1;
            var_r30->unk34 = arg2->x;
            sp18.x = arg1->x - arg0[0].x;
            sp18.y = arg1->y - arg0[0].y;
            sp18.z = arg1->z - arg0[0].z;
            var_f29 = VECMagXZ(&sp18);
            var_r30->unk28 = -atan2d(sp18.y, var_f29);
            var_r30->unk2C = atan2d(sp18.x, sp18.z);
            var_r30->unk30 = 0.0f;
            break;
    }
}

s32 lbl_1_data_7C4[] = { 1, 1, 0, 0, 2, 2 };

s32 fn_1_C498(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, float arg4, s32 arg5)
{
    StructBss94Data *var_r31;
    Vec sp140[6];
    Vec sp134;
    Vec sp128;
    Vec sp11C;
    Vec sp110;
    Vec sp104;
    Vec spF8;
    Vec spEC;
    Vec spE0;
    Vec spD4;
    Vec spC8;
    float var_f30;
    float var_f19;
    float sp34;
    float sp30;
    float sp2C;
    s32 var_r26;
    s32 var_r24;
    s32 var_r23;
    s32 i;
    s32 j;

    var_r31 = lbl_1_bss_94;
    var_r26 = -1;
    sp134.x = arg0->x + arg1->x;
    sp134.y = arg0->y + arg1->y;
    sp134.z = arg0->z + arg1->z;
    for (i = 0; i < 16; i++, var_r31++) {
        if (var_r31->unk02 == 0) {
            continue;
        }
        switch (var_r31->unk02 & 0xFFF) {
            case 1:
                if (arg1->x < 0.0f) {
                    if (arg0->x > var_r31->unk34 + arg4 && sp134.x <= var_r31->unk34 + arg4 + 1.0f) {
                        sp134.x = var_r31->unk34 + arg4;
                        *arg2 = sp134;
                        var_r26 = 0;
                    }
                }
                else {
                    if (arg0->x < var_r31->unk34 - arg4 && sp134.x >= var_r31->unk34 - arg4 - 1.0f) {
                        sp134.x = var_r31->unk34 - arg4;
                        *arg2 = sp134;
                        var_r26 = 0;
                    }
                }
                break;
            case 2:
                if (arg1->y < 0.0f) {
                    if (arg0->y > var_r31->unk34 + arg4 && sp134.y <= var_r31->unk34 + arg4 + 1.0f) {
                        sp134.y = var_r31->unk34 + arg4;
                        *arg2 = sp134;
                        var_r26 = 1;
                    }
                }
                else {
                    if (arg0->y < var_r31->unk34 - arg4 && sp134.y >= var_r31->unk34 - arg4 - 1.0f) {
                        sp134.y = var_r31->unk34 - arg4;
                        *arg2 = sp134;
                        var_r26 = 1;
                    }
                }
                break;
            case 3:
                if (arg1->z < 0.0f) {
                    if (arg0->z > var_r31->unk34 + arg4 && sp134.z <= var_r31->unk34 + arg4 + 1.0f) {
                        sp134.z = var_r31->unk34 + arg4;
                        *arg2 = sp134;
                        var_r26 = 2;
                    }
                }
                else {
                    if (arg0->z < var_r31->unk34 - arg4 && sp134.z >= var_r31->unk34 - arg4 - 1.0f) {
                        sp134.z = var_r31->unk34 - arg4;
                        *arg2 = sp134;
                        var_r26 = 2;
                    }
                }
                break;
            case 4:
                arg4 = 0.0f;
                VECSubtract(&sp134, &var_r31->unk04, &sp128);
                if (fabs(sp128.x) < var_r31->unk10.x + arg4 && fabs(sp128.y) < var_r31->unk10.y + arg4 && fabs(sp128.z) < var_r31->unk10.z + arg4) {
                    for (j = 0; j < 6; j++) {
                        if (var_r31->unk40 & (1 << j)) {
                            var_r24 = fn_1_12C6C(arg0, &sp134, var_r31->unk44[j * 2]);
                            if (var_r24 != 0) {
                                break;
                            }
                        }
                    }
                    switch (j) {
                        case 0:
                            sp134.y = var_r31->unk04.y + var_r31->unk10.y + arg4 + 1.0f;
                            break;
                        case 1:
                            sp134.y = var_r31->unk04.y - var_r31->unk10.y - arg4 - 1.0f;
                            break;
                        case 2:
                            sp134.x = var_r31->unk04.x - var_r31->unk10.x - arg4 - 1.0f;
                            break;
                        case 3:
                            sp134.x = var_r31->unk04.x + var_r31->unk10.x + arg4 + 1.0f;
                            break;
                        case 4:
                            sp134.z = var_r31->unk04.z + var_r31->unk10.z + arg4 + 1.0f;
                            break;
                        case 5:
                            sp134.z = var_r31->unk04.z - var_r31->unk10.z - arg4 - 1.0f;
                            break;
                    }
                    if (j < 6) {
                        *arg2 = sp134;
                        var_r26 = lbl_1_data_7C4[j];
                    }
                }
                break;
            case 5:
                if (fn_1_12C6C(arg0, &sp134, var_r31->unk44[0]) != 1) {
                    break;
                }
                fn_1_1334C(var_r31->unk44[0], arg0, arg1, var_r31->unk104[0], &sp104);
                sp110.x = fabs(var_r31->unk44[0][0]);
                sp110.y = fabs(var_r31->unk44[0][1]);
                sp110.z = fabs(var_r31->unk44[0][2]);
                if (sp110.x > sp110.y && sp110.x > sp110.z) {
                    var_r24 = 0;
                }
                else if (sp110.y > sp110.x && sp110.y > sp110.z) {
                    var_r24 = 1;
                }
                else {
                    var_r24 = 2;
                }
                sp140[0] = var_r31->unk104[0][0];
                sp140[1] = var_r31->unk104[1][0];
                sp140[2] = var_r31->unk104[3][0];
                sp140[3] = var_r31->unk104[1][0];
                sp140[4] = var_r31->unk104[2][0];
                sp140[5] = var_r31->unk104[3][0];
                sp34 = fn_1_12E68(&sp140[0], &sp104, var_r24);
                sp30 = fn_1_12E68(&sp140[3], &sp104, var_r24);
                if (sp34 != 0.0f || sp30 != 0.0f) {
                    arg2->x = sp104.x + var_r31->unk44[0][0] * (arg4 + 1.0f);
                    arg2->y = sp104.y + var_r31->unk44[0][1] * (arg4 + 1.0f);
                    arg2->z = sp104.z + var_r31->unk44[0][2] * (arg4 + 1.0f);
                    var_r26 = var_r24;
                }
                break;
            case 6:
                sp140[0] = var_r31->unk104[0][0];
                sp140[1] = var_r31->unk104[1][0];
                sp140[2] = var_r31->unk104[2][0];
                sp140[3] = var_r31->unk104[3][0];
                if (fn_1_137C4(&sp140[0], arg0, arg1, &sp104, arg4, var_r31->unk40) != 0) {
                    *arg2 = sp104;
                    var_r26 = lbl_1_data_7C4[var_r31->unk40];
                }
                break;
            case 7:
                spEC.x = arg0->x;
                spEC.y = arg0->z;
                spEC.z = 0.0f;
                spE0.x = sp134.x;
                spE0.y = sp134.z;
                spE0.z = 0.0f;
                spD4.x = var_r31->unk04.x;
                spD4.y = var_r31->unk04.z;
                spD4.z = 0.0f;
                var_f30 = fn_1_1367C(&spEC, &spE0, &spD4, &spC8, &sp2C);
                if (sp2C >= 0.0f && sp2C <= 1.0f && var_f30 < var_r31->unk34 + arg4) {
                    var_f19 = arg0->y + arg1->y * sp2C;
                    if (var_f19 >= var_r31->unk04.y && var_f19 <= var_r31->unk10.y) {
                        spC8.z = spC8.y;
                        spC8.y = 0.0f;
                        VECSubtract(&spC8, &var_r31->unk04, &sp128);
                        sp128.y = 0.0f;
                        if (VECMag(&sp128) == 0.0f) {
                            sp128.z = 1.0f;
                        }
                        else {
                            VECNormalize(&sp128, &sp128);
                        }
                        VECScale(&sp128, &sp128, var_r31->unk34 + arg4 + 1.0f);
                        arg2->x = sp128.x + var_r31->unk04.x;
                        arg2->z = sp128.z + var_r31->unk04.z;
                        arg2->y = var_f19;
                        sp2C = var_f30;
                        var_r26 = 99;
                    }
                }
                else {
                    sp2C = var_f30;
                    VECSubtract(&sp134, &var_r31->unk04, &sp128);
                    var_f30 = VECMagXZ(&sp128);
                    if (var_f30 < var_r31->unk34 + arg4 && sp134.y >= var_r31->unk04.y && sp134.y <= var_r31->unk10.y) {
                        VECSubtract(&sp134, &var_r31->unk04, &sp128);
                        sp128.y = 0.0f;
                        if (VECMag(&sp128) == 0.0f) {
                            sp128.z = 1.0f;
                        }
                        else {
                            VECNormalize(&sp128, &sp128);
                        }
                        VECScale(&sp128, &sp128, var_r31->unk34 + arg4 + 1.0f);
                        arg2->x = var_r31->unk04.x + sp128.x;
                        arg2->z = var_r31->unk04.z + sp128.z;
                        arg2->y = sp134.y;
                        var_r26 = 99;
                    }
                }
                if (var_r26 == -1) {
                    break;
                }
                sp128.x = spC8.x - var_r31->unk04.x;
                sp128.z = spC8.y - var_r31->unk04.z;
                var_f30 = VECMagXZ(&sp128);
                if (var_f30 == 0.0f) {
                    var_f30 = 1.0f;
                    sp128.x = 0.0f;
                    sp128.z = 1.0f;
                }
                else {
                    var_f30 = 1.0f / var_f30;
                }
                spC8.x = sp128.x * var_f30;
                spC8.z = sp128.z * var_f30;
                var_f30 = VECMagXZ(arg1);
                if (var_f30 != 0.0f) {
                    var_f30 = 1.0f / var_f30;
                }
                spD4.x = -(arg1->x * var_f30);
                spD4.z = -(arg1->z * var_f30);
                sp2C = var_f30 / (var_r31->unk34 + arg4);
                sp128.x = spD4.x + sp2C * (spC8.x - spD4.x);
                sp128.z = spD4.z + sp2C * (spC8.z - spD4.z);
                var_f30 = VECMagXZ(&sp128);
                if (var_f30 == 0.0f) {
                    var_f30 = 1.0f;
                    sp128.x = 0.0f;
                    sp128.z = 1.0f;
                }
                else {
                    var_f30 = 1.0f / var_f30;
                }
                sp128.x = sp128.x * var_f30 - spD4.x;
                sp128.z = sp128.z * var_f30 - spD4.z;
                sp128.y = 0.0f;
                if (VECMag(&sp128) == 0.0f) {
                    sp128.z = 1.0f;
                }
                else {
                    VECNormalize(&sp128, &sp128);
                }
                var_f30 = VECMagXZ(arg1);
                arg3->x = sp128.x * var_f30 * var_r31->unk3C;
                arg3->z = sp128.z * var_f30 * var_r31->unk3C;
                arg3->y = arg1->y;
                break;
        }
        if (var_r26 != -1) {
            break;
        }
    }
    if (i < 16) {
        switch (var_r26) {
            case 0:
                arg3->x = -arg1->x * var_r31->unk3C;
                arg3->y = arg1->y;
                arg3->z = arg1->z * var_r31->unk3C;
                var_r23 = var_r31->unk02;
                break;
            case 1:
                arg3->x = arg1->x * var_r31->unk3C;
                arg3->y = arg1->y * -0.5f;
                arg3->z = arg1->z * var_r31->unk3C;
                var_r23 = var_r31->unk02;
                break;
            case 2:
                arg3->x = arg1->x * var_r31->unk3C;
                arg3->y = arg1->y;
                arg3->z = -arg1->z * var_r31->unk3C;
                var_r23 = var_r31->unk02;
                break;
            default:
                var_r23 = var_r31->unk02;
                break;
        }
        arg5--;
        if (arg5 > 0) {
            sp11C = *arg0;
            sp110.x = arg2->x - arg0->x;
            sp110.y = arg2->y - arg0->y;
            sp110.z = arg2->z - arg0->z;
            var_r26 = fn_1_C498(&sp11C, &sp110, &sp104, &spF8, arg4, arg5);
            if (var_r26 != 0) {
                *arg2 = sp104;
                *arg3 = spF8;
                if (var_r23 & 0x4000) {
                    var_r26 |= 0x4000;
                }
                if (var_r23 & 0x8000) {
                    var_r26 |= 0x8000;
                }
                var_r23 = var_r26;
            }
        }
        return var_r23;
    }
    return 0;
}

void fn_1_D930(void)
{
    omObjData *var_r30;
    StructBssA4Data *var_r31;
    AnimData *var_r27;
    StructM423_05 *var_r29;
    ModelData *var_r28;
    s32 sp8;

    var_r30 = lbl_1_bss_A4 = omAddObjEx(lbl_1_bss_120, 0xBF, 0, 0, -1, fn_1_DA38);
    var_r31 = var_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*var_r31), MEMORY_DEFAULT_NUM);
    memset(var_r31, 0, sizeof(*var_r31));
    var_r31->unk08 = var_r27 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M423, 22), MEMORY_DEFAULT_NUM));
    var_r31->unk00 = sp8 = fn_1_11114(var_r27, 0x100);
    Hu3DModelCameraSet(var_r31->unk00, 4);
    Hu3DModelLayerSet(var_r31->unk00, 1);
    var_r31->unk04 = 0;
    var_r28 = &Hu3DData[var_r31->unk00];
    var_r29 = var_r28->unk_120;
    var_r29->unk20 = 0;
}

void fn_1_DA38(omObjData *arg0)
{
    StructBssA4Data *temp_r30;
    ModelData *var_r27;
    StructM423_05 *temp_r29;
    StructM423_04 *var_r31;
    s32 i;

    temp_r30 = arg0->data;
    if (temp_r30->unk04 <= 0) {
        Hu3DModelAttrSet(temp_r30->unk00, HU3D_ATTR_DISPOFF);
        return;
    }
    Hu3DModelAttrReset(temp_r30->unk00, HU3D_ATTR_DISPOFF);
    var_r27 = &Hu3DData[temp_r30->unk00];
    temp_r29 = var_r27->unk_120;
    var_r31 = temp_r29->unk3C;
    temp_r29->unk23 = 0;
    for (i = 0; i < temp_r29->unk26; i++, var_r31++) {
        if (var_r31->unk30 <= 0.0f) {
            continue;
        }
        var_r31->unk38.x += var_r31->unk04.x;
        var_r31->unk38.y += var_r31->unk04.y;
        var_r31->unk38.z += var_r31->unk04.z;
        var_r31->unk34 += var_r31->unk18;
        if (var_r31->unk34 >= 360.0f) {
            var_r31->unk34 -= 360.0f;
        }
        var_r31->unk48 = var_r31->unk28;
        var_r31->unk28 += var_r31->unk2C;
        if (var_r31->unk48 >= 16) {
            var_r31->unk48 = 0;
            var_r31->unk00 = 0;
            var_r31->unk30 = 0.0f;
            temp_r30->unk04--;
        }
    }
}

void fn_1_DBC8(void)
{
    omObjData *temp_r31;
    StructBssA4Data *temp_r30;

    temp_r31 = lbl_1_bss_A4;
    temp_r30 = temp_r31->data;
    Hu3DModelAttrSet(temp_r30->unk00, HU3D_ATTR_DISPOFF);
    HuSprAnimKill(temp_r30->unk08);
    temp_r31->func = NULL;
}

inline s32 fn_1_DC24(Vec arg0, Vec arg1, float arg2, float arg3, float arg4, GXColor arg5)
{
    omObjData *var_r27;
    StructBssA4Data *temp_r28;
    ModelData *var_r26;
    StructM423_05 *temp_r30;
    StructM423_04 *var_r31;
    s32 i;

    var_r27 = lbl_1_bss_A4;
    temp_r28 = var_r27->data;
    var_r26 = &Hu3DData[temp_r28->unk00];
    temp_r30 = var_r26->unk_120;
    var_r31 = temp_r30->unk3C;
    for (i = 0; i < temp_r30->unk26; i++, var_r31++) {
        if (var_r31->unk30 <= 0.0f) {
            break;
        }
    }
    if (i >= temp_r30->unk26) {
        return -1;
    }
    var_r31->unk00 = var_r31->unk02 = 0;
    var_r31->unk38.x = arg0.x;
    var_r31->unk38.y = arg0.y;
    var_r31->unk38.z = arg0.z;
    var_r31->unk04.x = arg1.x;
    var_r31->unk04.y = arg1.y;
    var_r31->unk04.z = arg1.z;
    var_r31->unk18 = arg3;
    var_r31->unk30 = arg2;
    var_r31->unk44.r = arg5.r;
    var_r31->unk44.g = arg5.g;
    var_r31->unk44.b = arg5.b;
    var_r31->unk44.a = arg5.a;
    var_r31->unk34 = 0.0f;
    var_r31->unk48 = 0;
    var_r31->unk00 = 0;
    var_r31->unk28 = 0.0f;
    var_r31->unk2C = arg4;
    temp_r28->unk04++;
    return i;
}

s32 fn_1_DD70(Vec arg0, Vec arg1, float arg2, float arg3, float arg4, float arg5, GXColor arg6)
{
    Vec sp60;
    Vec sp54;
    float temp_f31;
    s32 sp20;
    s32 sp1C;

    sp54.x = arg1.z;
    sp54.z = arg1.x;
    sp54.y = 0.0f;
    VECNormalize(&sp54, &sp54);
    temp_f31 = 0.5f * arg4;
    sp60.x = arg0.x + sp54.x * temp_f31;
    sp60.y = arg0.y + sp54.y * temp_f31;
    sp60.z = arg0.z + sp54.z * temp_f31;
    sp20 = fn_1_DC24(sp60, arg1, arg2, arg3, arg5, arg6);
    sp60.x = arg0.x - sp54.x * temp_f31;
    sp60.y = arg0.y - sp54.y * temp_f31;
    sp60.z = arg0.z - sp54.z * temp_f31;
    sp1C = fn_1_DC24(sp60, arg1, arg2, -arg3, arg5, arg6);
    return (sp20 << 16) | sp1C;
}

void fn_1_E1BC(void)
{
    omObjData *var_r31;
    s32 var_r29;
    s32 i;

    var_r31 = lbl_1_bss_A0 = omAddObjEx(lbl_1_bss_120, 0xBF, 16, 0, -1, fn_1_E290);
    for (i = 0; i < var_r31->mdlcnt; i++) {
        var_r29 = var_r31->model[i] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M423, 3));
        Hu3DModelAttrSet(var_r29, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(var_r29, 4);
    }
    var_r31->stat |= 0x100;
}

void fn_1_E290(omObjData *arg0)
{
    ModelData *var_r28;
    s32 temp_r30;
    s32 i;

    for (i = 0; i < arg0->mdlcnt; i++) {
        temp_r30 = arg0->model[i];
        var_r28 = &Hu3DData[temp_r30];
        if (!(var_r28->attr & 1) && Hu3DMotionEndCheck(temp_r30)) {
            Hu3DModelAttrSet(temp_r30, HU3D_ATTR_DISPOFF);
        }
    }
}

void fn_1_E330(void) { }

s32 fn_1_E334(Vec arg0, Vec arg1, float arg2)
{
    omObjData *var_r31;
    ModelData *var_r26;
    s32 temp_r29;
    s32 i;

    var_r31 = lbl_1_bss_A0;
    for (i = 0; i < var_r31->mdlcnt; i++) {
        var_r26 = &Hu3DData[var_r31->model[i]];
        if (var_r26->attr & 1) {
            break;
        }
    }
    if (i >= var_r31->mdlcnt) {
        return -1;
    }
    temp_r29 = var_r31->model[i];
    Hu3DModelPosSet(temp_r29, arg0.x, arg0.y, arg0.z);
    Hu3DModelRotSet(temp_r29, arg1.x, arg1.y, arg1.z);
    Hu3DModelScaleSet(temp_r29, arg2, arg2, arg2);
    Hu3DMotionTimeSet(temp_r29, 0.0f);
    Hu3DMotionSpeedSet(temp_r29, 2.0f);
    Hu3DModelAttrReset(temp_r29, HU3D_ATTR_DISPOFF);
    return i;
}

void fn_1_E460(void)
{
    omObjData *temp_r3;

    temp_r3 = lbl_1_bss_9C = omAddObjEx(lbl_1_bss_120, 0xBF, 1, 0, -1, fn_1_E4EC);
    temp_r3->model[0] = fn_1_E678();
    Hu3DModelCameraSet(temp_r3->model[0], 4);
    Hu3DModelLayerSet(temp_r3->model[0], 2);
}

void fn_1_E4EC(omObjData *arg0)
{
    ModelData *var_r29;
    StructM423_0B *var_r28;
    StructM423_0A *var_r31;
    s32 i;

    var_r29 = &Hu3DData[arg0->model[0]];
    var_r28 = var_r29->unk_120;
    var_r31 = var_r28->unk00;
    for (i = 0; i < 16; i++, var_r31++) {
        if (var_r31->unk00 == 0) {
            continue;
        }
        var_r31->unk00++;
        if (var_r31->unk00 < REFRESH_RATE_F / 5) {
            var_r31->unk04 += 3.5f / REFRESH_RATE_F;
        }
        else {
            var_r31->unk04 += 1.5f / REFRESH_RATE_F;
            var_r31->unk10 -= 3.0f / REFRESH_RATE_F;
        }
        if (var_r31->unk10 < 0.0f) {
            var_r31->unk00 = 0;
        }
    }
}

void fn_1_E60C(void)
{
    omObjData *temp_r31;
    ModelData *var_r30;
    StructM423_0B *var_r29;

    temp_r31 = lbl_1_bss_9C;
    var_r30 = &Hu3DData[temp_r31->model[0]];
    var_r29 = var_r30->unk_120;
    HuSprAnimKill(var_r29->unk200);
    temp_r31->func = NULL;
}

s32 fn_1_E678(void)
{
    float sp88[32][2];
    float sp8[32];
    float temp_f28;
    float temp_f30;
    float temp_f29;
    float var_f31;
    ModelData *temp_r27;
    StructM423_0B *var_r30;
    StructM423_09 *var_r29;
    StructM423_08 *var_r28;
    s32 var_r26;
    s32 i;

    var_r26 = Hu3DHookFuncCreate(fn_1_EF44);
    temp_r27 = &Hu3DData[var_r26];
    var_r30 = temp_r27->unk_120 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r30), temp_r27->unk_48);
    memset(var_r30, 0, sizeof(*var_r30));
    var_r30->unk20C = HuMemDirectMallocNum(HEAP_DATA, 32 * sizeof(*var_r30->unk20C), temp_r27->unk_48);
    memset(var_r30->unk20C, 0, 32 * sizeof(*var_r30->unk20C));
    var_r30->unk210 = HuMemDirectMallocNum(HEAP_DATA, 32 * sizeof(*var_r30->unk210), temp_r27->unk_48);
    memset(var_r30->unk210, 0, 32 * sizeof(*var_r30->unk210));
    var_r30->unk214 = HuMemDirectMallocNum(HEAP_DATA, 5 * sizeof(*var_r30->unk214), temp_r27->unk_48);
    memset(var_r30->unk214, 0, 5 * sizeof(*var_r30->unk214));
    var_r30->unk204 = GXGetTexBufferSize(640, 480, GX_TF_RGB5A3, GX_FALSE, 0);
    var_r30->unk208 = HuMemDirectMallocNum(HEAP_DATA, var_r30->unk204, temp_r27->unk_48);
    DCFlushRange(var_r30->unk208, var_r30->unk204);
    var_r30->unk200 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M423, 23), MEMORY_DEFAULT_NUM));
    var_f31 = 0.0f;
    for (i = 0; i < 32; i++) {
        temp_f28 = 1.0f + 0.001f * frandmod(1000);
        sp8[i] = temp_f28;
        var_f31 += temp_f28;
        sp88[i][1] = 80.0f * temp_f28;
        sp88[i][0] = 10.0f + 0.02f * frandmod(1000);
    }
    var_f31 = 360.0f / var_f31;
    for (i = 0; i < 32; i++) {
        sp8[i] *= var_f31;
    }
    var_f31 = frandmod(90);
    var_r28 = var_r30->unk20C;
    var_r29 = var_r30->unk210;
    for (i = 0; i < 32; var_r28++, var_r29++, i++) {
        temp_f29 = -cosd(var_f31);
        temp_f30 = sind(var_f31);
        var_r28->unk24 = temp_f29 * sp88[i][0];
        var_r28->unk28 = temp_f30 * sp88[i][0];
        var_r28->unk0C = temp_f29 * (sp88[i][0] + sp88[i][1]);
        var_r28->unk10 = temp_f30 * (sp88[i][0] + sp88[i][1]);
        var_r28->unk00 = temp_f29 * (sp88[i][0] + 0.85f * sp88[i][1]);
        var_r28->unk04 = temp_f30 * (sp88[i][0] + 0.85f * sp88[i][1]);
        var_r29->unk00 = -0.3f * -temp_f29;
        var_r29->unk04 = -0.3f * temp_f30;
        temp_f29 = -cosd(var_f31 - 0.4f * sp8[i]);
        temp_f30 = sind(var_f31 - 0.4f * sp8[i]);
        var_r28->unk30 = temp_f29 * (sp88[i][0] + 0.7f * sp88[i][1]);
        var_r28->unk34 = temp_f30 * (sp88[i][0] + 0.7f * sp88[i][1]);
        temp_f29 = -cosd(var_f31 + 0.4f * sp8[i]);
        temp_f30 = sind(var_f31 + 0.4f * sp8[i]);
        var_r28->unk18 = temp_f29 * (sp88[i][0] + 0.7f * sp88[i][1]);
        var_r28->unk1C = temp_f30 * (sp88[i][0] + 0.7f * sp88[i][1]);
        var_r29->unk08 = var_r29->unk0C = var_r29->unk10 = var_r29->unk14 = 0.0f;
        var_r29->unk18 = var_r29->unk1C = var_r29->unk20 = var_r29->unk24 = 0.0f;
        var_f31 += sp8[i];
    }
    for (i = 0; i < 5; i++) {
        var_r30->unk214[i].r = var_r30->unk214[i].g = var_r30->unk214[i].b = 0xFF;
        var_r30->unk214[i].a = 0xFF;
    }
    var_r30->unk218 = 32 * 54;
    var_r30->unk220 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r30->unk218, MEMORY_DEFAULT_NUM);
    GXBeginDisplayList(var_r30->unk220, var_r30->unk218);
    for (i = 0; i < 32; i++) {
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 6);

        GXPosition1x16(i * 5);
        GXColor1x16(0);
        GXTexCoord1x16(i * 5);

        GXPosition1x16(i * 5 + 1);
        GXColor1x16(1);
        GXTexCoord1x16(i * 5 + 1);

        GXPosition1x16(i * 5 + 2);
        GXColor1x16(2);
        GXTexCoord1x16(i * 5 + 2);

        GXPosition1x16(i * 5 + 3);
        GXColor1x16(3);
        GXTexCoord1x16(i * 5 + 3);

        GXPosition1x16(i * 5 + 4);
        GXColor1x16(4);
        GXTexCoord1x16(i * 5 + 4);

        GXPosition1x16(i * 5 + 1);
        GXColor1x16(1);
        GXTexCoord1x16(i * 5 + 1);

        GXEnd();
    }
    var_r30->unk21C = GXEndDisplayList();
    DCFlushRangeNoSync(var_r30->unk20C, 32 * sizeof(*var_r30->unk20C));
    DCFlushRangeNoSync(var_r30->unk210, 32 * sizeof(*var_r30->unk210));
    DCFlushRangeNoSync(var_r30->unk214, 5 * sizeof(*var_r30->unk214));
    DCFlushRangeNoSync(var_r30->unk220, var_r30->unk218);
    DCStoreRangeNoSync(var_r30, sizeof(*var_r30));
    PPCSync();
    return var_r26;
}

GXColor lbl_1_data_7FC[] = { { 0x66, 0x00, 0x00, 0xFF }, { 0x00, 0x00, 0x66, 0xFF }, { 0x66, 0x00, 0x5B, 0xFF }, { 0x00, 0x66, 0x00, 0xFF },
    { 0x42, 0x00, 0x4C, 0xFF }, { 0x47, 0x28, 0x00, 0xFF }, { 0x66, 0x66, 0x00, 0xFF }, { 0x00, 0x00, 0x00, 0xFF } };

void fn_1_EF44(ModelData *arg0, Mtx arg1)
{
    Mtx sp124;
    Mtx spF4;
    Mtx spC4;
    Mtx sp94;
    Mtx sp64;
    Mtx sp34;
    GXTexObj sp14;
    GXColor sp10 = { 0xCC, 0xCC, 0xCC, 0x7F };
    StructM423_0B *temp_r30;
    StructM423_0A *var_r31;
    s32 i;

    temp_r30 = arg0->unk_120;
    GXSetTexCopySrc(0, 0, 640, 480);
    GXSetTexCopyDst(640, 480, GX_TF_RGB5A3, GX_FALSE);
    GXCopyTex(temp_r30->unk208, GX_FALSE);
    GXPixModeSync();
    MTXTrans(spF4, -400.0f, 400.0f, -700.0f);
    MTXConcat(Hu3DCameraMtx, spF4, sp64);
    GXLoadPosMtxImm(sp64, GX_PNMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXInitTexObj(&sp14, temp_r30->unk208, 640, 480, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&sp14, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&sp14, GX_TEXMAP0);
    HuSprTexLoad(temp_r30->unk200, 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTexGens(2);
    C_MTXLightPerspective(sp94, 41.5f, 1.2f, 0.5555555f, -0.5f, 0.5555555f, 0.5f);
    MTXConcat(sp94, Hu3DCameraMtx, sp94);
    MTXInverse(Hu3DCameraMtx, sp34);
    MTXConcat(sp34, sp64, sp124);
    MTXConcat(sp94, sp124, spF4);
    GXLoadTexMtxImm(spF4, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEXCOORD0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    MTXScale(spF4, -0.5f, -0.5f, 0.5f);
    GXSetIndTexMtx(GX_ITM_0, (float(*)[3])spF4, -1);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG1, sp10);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_A0, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_POS, temp_r30->unk20C, 12);
    GXSetArray(GX_VA_CLR0, temp_r30->unk214, 4);
    GXSetArray(GX_VA_TEX0, temp_r30->unk210, 8);
    var_r31 = temp_r30->unk00;
    for (i = 0; i < 16; i++, var_r31++) {
        if (var_r31->unk00 == 0) {
            continue;
        }
        lbl_1_data_7FC[var_r31->unk02].a = 255.0f * var_r31->unk10;
        GXSetTevColor(GX_TEVREG0, lbl_1_data_7FC[var_r31->unk02]);
        MTXTrans(spF4, var_r31->unk14.x, var_r31->unk14.y, var_r31->unk14.z);
        MTXRotRad(sp124, 'Z', MTXDegToRad(var_r31->unk0C));
        MTXConcat(spF4, sp124, spF4);
        MTXScale(spC4, var_r31->unk04 * var_r31->unk08, var_r31->unk04 * var_r31->unk08, var_r31->unk04 * var_r31->unk08);
        MTXConcat(spF4, spC4, spF4);
        MTXConcat(Hu3DCameraMtx, spF4, sp64);
        GXLoadPosMtxImm(sp64, GX_PNMTX0);
        MTXConcat(sp34, sp64, sp124);
        MTXConcat(sp94, sp124, spF4);
        GXLoadTexMtxImm(spF4, GX_TEXMTX0, GX_MTX3x4);
        MTXRotRad(sp124, 'Z', MTXDegToRad(-var_r31->unk0C));
        GXLoadTexMtxImm(sp124, GX_TEXMTX1, GX_MTX2x4);
        GXCallDisplayList(temp_r30->unk220, temp_r30->unk21C);
    }
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
}

s32 fn_1_F574(Vec arg0, float arg1, s32 arg2)
{
    omObjData *var_r29;
    ModelData *var_r28;
    StructM423_0B *var_r26;
    StructM423_0A *var_r31;
    s32 var_r27;
    s32 i;

    var_r29 = lbl_1_bss_9C;
    var_r28 = &Hu3DData[var_r29->model[0]];
    var_r26 = var_r28->unk_120;
    var_r31 = var_r26->unk00;
    for (i = 0; i < 16; i++, var_r31++) {
        if (var_r31->unk00 == 0) {
            break;
        }
    }
    if (i < 16) {
        if (arg2 < 0) {
            arg2 = 0;
        }
        var_r31->unk00 = 1;
        var_r31->unk02 = arg2;
        var_r31->unk10 = 1.0f;
        var_r31->unk08 = arg1;
        var_r31->unk04 = 0.25f;
        var_r31->unk0C = frandmod(360);
        var_r31->unk14 = arg0;
    }
}

void fn_1_F690(void)
{
    lbl_1_bss_98 = omAddObjEx(lbl_1_bss_120, 0xFE, 0, 0, -1, fn_1_F6E0);
}

s32 lbl_1_data_81C[] = { DATA_MAKE_NUM(DATADIR_MGCONST, 12), DATA_MAKE_NUM(DATADIR_MGCONST, 13), DATA_MAKE_NUM(DATADIR_MGCONST, 14),
    DATA_MAKE_NUM(DATADIR_MGCONST, 15), DATA_MAKE_NUM(DATADIR_MGCONST, 16), DATA_MAKE_NUM(DATADIR_MGCONST, 17), DATA_MAKE_NUM(DATADIR_MGCONST, 18),
    DATA_MAKE_NUM(DATADIR_MGCONST, 19) };

s16 lbl_1_data_83C[] = { 0x7F, 0x7F, 0x7F, 0x100 };

s16 lbl_1_data_844[][2] = { { -75, 10 }, { -61, -14 }, { -47, 10 }, { 0, 0 }, { -12, -8 }, { -12, -8 }, { 6, -8 }, { 6, -8 }, { 24, -8 }, { 24, -8 },
    { 42, -8 }, { 42, -8 }, { 60, -8 }, { 60, -8 }, { -12, 10 }, { -12, 10 }, { 6, 10 }, { 6, 10 }, { 24, 10 }, { 24, 10 }, { 42, 10 }, { 42, 10 },
    { 60, 10 }, { 60, 10 } };

void fn_1_F6E0(omObjData *arg0)
{
    StructM423_0C *var_r31;
    s32 sp8;
    s32 var_r29;
    s32 i;

    if ((sp8 = lbl_1_bss_EC[3]) != -1) {
        var_r31 = arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(*var_r31), MEMORY_DEFAULT_NUM);
        memset(var_r31, 0, sizeof(*var_r31));
        var_r31->unk00 = 480;
        var_r31->unk04 = 70;
        var_r31->unk08 = 0;
        var_r31->unk0C = 0;
        for (i = 0; i < 24; i++) {
            switch (i) {
                case 0:
                case 1:
                case 2:
                    var_r29 = espEntry(lbl_1_data_81C[lbl_1_bss_EC[i]], lbl_1_data_83C[i], 0);
                    var_r31->unk10[i] = var_r29;
                    var_r31->unk70[i][0] = lbl_1_data_844[i][0];
                    var_r31->unk70[i][1] = lbl_1_data_844[i][1];
                    break;
                case 3:
                    var_r29 = espEntry(DATA_MAKE_NUM(DATADIR_MGCONST, 38), lbl_1_data_83C[i], 0);
                    var_r31->unk10[i] = var_r29;
                    var_r31->unk70[i][0] = lbl_1_data_844[i][0];
                    var_r31->unk70[i][1] = lbl_1_data_844[i][1];
                    break;
                default:
                    if (!(i & 1)) {
                        var_r29 = espEntry(DATA_MAKE_NUM(DATADIR_M423, 24), 0x40, 0);
                        var_r31->unk10[i] = var_r29;
                    }
                    else {
                        var_r29 = espEntry(DATA_MAKE_NUM(DATADIR_M423, 25), 0x20, 0);
                        var_r31->unk10[i] = var_r29;
                    }
                    var_r31->unk70[i][0] = lbl_1_data_844[i][0];
                    var_r31->unk70[i][1] = lbl_1_data_844[i][1];
                    break;
            }
            espDispOn(var_r29);
            espDrawNoSet(var_r29, 0);
            espAttrSet(var_r29, 1);
            espPosSet(var_r29, var_r31->unk00 + var_r31->unk70[i][0], var_r31->unk04 + var_r31->unk70[i][1]);
            espBankSet(var_r29, 0);
        }
        for (i = 0; i < 10; i++) {
            var_r31->unk190[i][0] = 0;
            var_r31->unk190[i][1] = 0;
        }
        fn_1_10028(0);
        arg0->func = fn_1_FA40;
    }
}

void fn_1_FA40(omObjData *arg0)
{
    float var_f31;
    float var_f28;
    float temp_f30;
    float temp_f29;
    StructM423_0C *temp_r31;
    s32 temp_r28;
    s32 temp_r29;
    s32 i;

    temp_r31 = arg0->data;
    if (lbl_1_bss_104 != temp_r31->unk08) {
        temp_r31->unk08 = lbl_1_bss_104;
        temp_r31->unk0C = 20;
    }
    if (temp_r31->unk0C != 0) {
        var_f31 = 1.0 + 0.8f * sind(180.0f * (temp_r31->unk0C / 20.0f));
        temp_r31->unk0C--;
    }
    else {
        var_f31 = 1.0f;
    }
    var_f31 = 1.0f;
    temp_r28 = 10 - lbl_1_bss_104;
    for (i = 0; i < 4; i++) {
        temp_f30 = temp_r31->unk00 + temp_r31->unk70[i][0];
        temp_f29 = temp_r31->unk04 + temp_r31->unk70[i][1];
        espPosSet(temp_r31->unk10[i], temp_f30, temp_f29);
        espScaleSet(temp_r31->unk10[i], 1.0f, 1.0f);
    }
    for (i = 4; i < 24; i++) {
        temp_f30 = temp_r31->unk00 + temp_r31->unk70[i][0];
        temp_f29 = temp_r31->unk04 + temp_r31->unk70[i][1];
        if (!(i & 1)) {
            espPosSet(temp_r31->unk10[i], temp_f30, temp_f29);
            espScaleSet(temp_r31->unk10[i], 1.0f, 1.0f);
        }
        else {
            temp_r29 = (i - 4) / 2;
            if (temp_r28 > temp_r29) {
                temp_r31->unk190[temp_r29][0] = 1;
            }
            else {
                temp_r31->unk190[temp_r29][0] = 0;
            }
            if (temp_r31->unk190[temp_r29][0] != 0) {
                if (temp_r31->unk190[temp_r29][1] < REFRESH_RATE / 4) {
                    temp_r31->unk190[temp_r29][1]++;
#if VERSION_PAL
                    var_f31 = 3.0f - 2.0f * (temp_r31->unk190[temp_r29][1] / 12.0f);
                    var_f28 = temp_r31->unk190[temp_r29][1] / 12.0f;
#else
                    var_f31 = 3.0f - 2.0f * (temp_r31->unk190[temp_r29][1] / 15.0f);
                    var_f28 = temp_r31->unk190[temp_r29][1] / 15.0f;
#endif
                }
                else {
                    var_f31 = 1.0f;
                    var_f28 = 1.0f;
                }
                espDispOn(temp_r31->unk10[i]);
                espPosSet(temp_r31->unk10[i], temp_f30, temp_f29);
                espTPLvlSet(temp_r31->unk10[i], var_f28);
                espScaleSet(temp_r31->unk10[i], var_f31, var_f31);
            }
            else {
                espDispOff(temp_r31->unk10[i]);
            }
        }
    }
}

void fn_1_FF10(omObjData *arg0)
{
    StructM423_0C *temp_r29;
    s32 i;

    if (arg0 && arg0->data) {
        temp_r29 = arg0->data;
        for (i = 0; i < 24; i++) {
            espKill(temp_r29->unk10[i]);
        }
        arg0->data = NULL;
        arg0->func = NULL;
    }
}

void fn_1_FF98(void)
{
    fn_1_FF10(lbl_1_bss_98);
}

void fn_1_10028(s32 arg0)
{
    StructM423_0C *temp_r30;
    s32 i;

    temp_r30 = lbl_1_bss_98->data;
    for (i = 0; i < 24; i++) {
        if (arg0 != 0) {
            espDispOn(temp_r30->unk10[i]);
        }
        else {
            espDispOff(temp_r30->unk10[i]);
        }
        if (i >= 4 && (i & 1)) {
            espDispOff(temp_r30->unk10[i]);
        }
    }
}

void fn_1_100DC(void)
{
    omObjData *temp_r3;
    s32 i;

    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 50.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 320, 240);
    Hu3DCameraCreate(2);
    Hu3DCameraPerspectiveSet(2, 45.0f, 50.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(2, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 0, 0, 640, 480);
    Hu3DCameraCreate(4);
    Hu3DCameraPerspectiveSet(4, 45.0f, 100.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(4, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(4, 0, 0, 640, 480);
    temp_r3 = lbl_1_bss_8C = omAddObjEx(lbl_1_bss_120, 0x7FDA, 0, 0, -1, omOutViewMulti);
    temp_r3->work[0] = 3;
    for (i = 0; i < temp_r3->work[0]; i++) {
        CRotM[i].x = lbl_1_data_0[0].unk00.x;
        CRotM[i].y = lbl_1_data_0[0].unk00.y;
        CRotM[i].z = lbl_1_data_0[0].unk00.z;
        CenterM[i].x = lbl_1_data_0[0].unk0C.x;
        CenterM[i].y = lbl_1_data_0[0].unk0C.y;
        CenterM[i].z = lbl_1_data_0[0].unk0C.z;
        CZoomM[i] = lbl_1_data_0[0].unk18;
    }
    lbl_1_bss_84 = 0;
    lbl_1_bss_88 = -1;
    omAddObjEx(lbl_1_bss_120, 0xFF, 0, 0, -1, fn_1_10480);
}

void fn_1_10480(omObjData *arg0)
{
    CRotM[1].x = CRotM[0].x;
    CRotM[1].y = CRotM[0].y;
    CRotM[1].z = CRotM[0].z;
    CenterM[1].x = CenterM[0].x;
    CenterM[1].y = CenterM[0].y;
    CenterM[1].z = CenterM[0].z;
    CZoomM[1] = CZoomM[0];
}

void fn_1_1052C(void) { }

s32 fn_1_10530(void)
{
    return lbl_1_bss_84;
}

void fn_1_10540(s32 arg0, s32 arg1, s32 arg2, f32 arg3)
{
    StructData0 *temp_r31;
    StructData0 *temp_r30;

    temp_r31 = &lbl_1_data_0[arg1];
    temp_r30 = &lbl_1_data_0[arg2];
    CRotM[arg0].x = fn_1_12544(arg3, temp_r31->unk00.x, temp_r30->unk00.x);
    CRotM[arg0].y = fn_1_12544(arg3, temp_r31->unk00.y, temp_r30->unk00.y);
    CRotM[arg0].z = fn_1_12544(arg3, temp_r31->unk00.z, temp_r30->unk00.z);
    CenterM[arg0].x = temp_r31->unk0C.x + arg3 * (temp_r30->unk0C.x - temp_r31->unk0C.x);
    CenterM[arg0].y = temp_r31->unk0C.y + arg3 * (temp_r30->unk0C.y - temp_r31->unk0C.y);
    CenterM[arg0].z = temp_r31->unk0C.z + arg3 * (temp_r30->unk0C.z - temp_r31->unk0C.z);
    CZoomM[arg0] = temp_r31->unk18 + arg3 * (temp_r30->unk18 - temp_r31->unk18);
}

float lbl_1_data_8A4[] = { 95.0f, 95.0f, 135.0f, 95.0f, 95.0f, 125.0f, 135.0f, 125.0f };

void fn_1_106D8(s32 arg0)
{
    float var_f31;
    StructBssBCData *var_r30;
    s32 var_r29;

    if (lbl_1_bss_90 != arg0) {
        CRotM->x = lbl_1_data_38[arg0].unk00.x;
        CRotM->y = lbl_1_data_38[arg0].unk00.y;
        CRotM->z = lbl_1_data_38[arg0].unk00.z;
        CenterM->x = lbl_1_data_38[arg0].unk0C.x;
        CenterM->y = lbl_1_data_38[arg0].unk0C.y;
        CenterM->z = lbl_1_data_38[arg0].unk0C.z;
        CZoomM[0] = lbl_1_data_38[arg0].unk18;
        lbl_1_bss_80 = 0;
        if (arg0 != 0) {
            lbl_1_bss_7C = frand();
        }
        else {
            lbl_1_bss_7C = 0;
        }
        lbl_1_bss_90 = arg0;
    }
    var_r29 = lbl_1_bss_90;
    switch (var_r29) {
        case 0:
        case 1:
        case 2:
            lbl_1_bss_80++;
            if (lbl_1_bss_7C & 1) {
                var_f31 = cosd((float)lbl_1_bss_80);
            }
            else {
                var_f31 = -cosd((float)lbl_1_bss_80);
            }
            CRotM->y = 23.0f * var_f31 + lbl_1_data_38[arg0].unk00.y;
            break;
        case 3:
        case 4:
        case 5:
            lbl_1_bss_80++;
            if (lbl_1_bss_7C & 1) {
                CRotM->y = lbl_1_data_38[arg0].unk00.y - 45.0f + 0.5f * lbl_1_bss_80;
            }
            else {
                CRotM->y = lbl_1_data_38[arg0].unk00.y + 45.0f - 0.5f * lbl_1_bss_80;
            }
            break;
        case 6:
        case 7:
        case 8:
            if (lbl_1_bss_AC[var_r29 - 6] != NULL) {
                var_r30 = lbl_1_bss_AC[var_r29 - 6]->data;
                CenterM->y = lbl_1_data_8A4[var_r30->unk02];
            }
            break;
        case 9:
            if (lbl_1_bss_B8 != NULL) {
                var_r30 = lbl_1_bss_B8->data;
                CenterM->x = lbl_1_bss_B8->trans.x;
                CenterM->z = lbl_1_bss_B8->trans.z;
                CenterM->y = lbl_1_data_8A4[var_r30->unk02];
            }
            break;
    }
}

void fn_1_10BC8(void)
{
    Mtx44 sp64;
    Mtx sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    GXColor spC;
    CameraData *var_r31;

    var_r31 = &Hu3DCamera[0];
    if (var_r31->fov <= 0.0f) {
        return;
    }
    C_MTXPerspective(sp64, var_r31->fov, var_r31->aspect, var_r31->near, var_r31->far);
    GXSetProjection(sp64, GX_PERSPECTIVE);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 640, 480);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    spC.r = spC.g = spC.b = 0;
    spC.a = 0xFF;
    GXSetTevColor(GX_TEVREG0, spC);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    sp28.x = sp28.y = sp28.z = 0.0f;
    sp1C.x = sp1C.y = 0.0f;
    sp1C.z = -100.0f;
    sp10.x = sp10.z = 0.0f;
    sp10.y = 1.0f;
    C_MTXLookAt(sp34, &sp28, &sp10, &sp1C);
    GXLoadPosMtxImm(sp34, GX_PNMTX0);
    sp28.x = 10000.0 * -sin(var_r31->fov / 2.0f) * 1.2f;
    sp28.y = 10000.0 * -sin(var_r31->fov / 2.0f) * 0.8333333f;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-sp28.x, -sp28.y, -10000.0f);
    GXPosition3f32(sp28.x, -sp28.y, -10000.0f);
    GXPosition3f32(sp28.x, sp28.y, -10000.0f);
    GXPosition3f32(-sp28.x, sp28.y, -10000.0f);
    GXEnd();
}

void fn_1_11008(StructBssD0Data *arg0, void *arg1, s16 arg2, GXTexWrapMode arg3, s32 arg4, s32 arg5)
{
    GXTexObj sp18;
    StructBssD0Data *var_r31;

    var_r31 = arg0;
    GXInitTexObj(&sp18, arg1, var_r31->unk00, var_r31->unk04, GX_TF_RGB5A3, arg3, arg3, GX_FALSE);
    if (arg5 != 0) {
        GXInitTexObjLOD(&sp18, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    else {
        GXInitTexObjLOD(&sp18, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    }
    GXLoadTexObj(&sp18, arg2);
}

s16 fn_1_11114(AnimData *arg0, s16 arg1)
{
    s16 var_r23;
    s16 i;
    ModelData *temp_r27;
    StructM423_05 *var_r31;
    StructM423_04 *var_r29;
    Vec *var_r25;
    float(*var_r28)[2];
    void *var_r24;
    void *var_r22;

    var_r23 = Hu3DHookFuncCreate(fn_1_11900);
    temp_r27 = &Hu3DData[var_r23];
    temp_r27->unk_120 = var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r31), temp_r27->unk_48);
    var_r31->unk38 = arg0;
    var_r31->unk26 = arg1;
    var_r31->unk20 = 0;
    var_r31->unk22 = 0;
    var_r31->unk4C = NULL;
    var_r31->unk50 = NULL;
    var_r31->unk28 = 0;
    var_r31->unk21 = 0;
    var_r31->unk23 = 0;
    var_r31->unk30 = 0;
    var_r31->unk00 = var_r31->unk02 = 0;
    var_r31->unk3C = var_r29 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(*var_r29), temp_r27->unk_48);
    memset(var_r29, 0, arg1 * sizeof(*var_r29));
    for (i = 0; i < arg1; i++, var_r29++) {
        var_r29->unk30 = 0.0f;
        var_r29->unk34 = 0.0f;
        var_r29->unk28 = 0.0f;
        var_r29->unk2C = 1.0f;
        var_r29->unk38.x = (frand7() - 64) * 20;
        var_r29->unk38.y = (frand7() - 64) * 30;
        var_r29->unk38.z = (frand7() - 64) * 20;
        var_r29->unk44.r = var_r29->unk44.g = var_r29->unk44.b = var_r29->unk44.a = 0xFF;
        var_r29->unk48 = 0;
    }
    var_r31->unk40 = var_r25 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(*var_r25) * 4, temp_r27->unk_48);
    for (i = 0; i < arg1 * 4; i++, var_r25++) {
        var_r25->x = var_r25->y = var_r25->z = 0.0f;
    }
    var_r31->unk44 = var_r28 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(*var_r28) * 4, temp_r27->unk_48);
    for (i = 0; i < arg1; i++) {
        (*var_r28)[0] = 0.0f;
        (*var_r28)[1] = 0.0f;
        var_r28++;
        (*var_r28)[0] = 1.0f;
        (*var_r28)[1] = 0.0f;
        var_r28++;
        (*var_r28)[0] = 1.0f;
        (*var_r28)[1] = 1.0f;
        var_r28++;
        (*var_r28)[0] = 0.0f;
        (*var_r28)[1] = 1.0f;
        var_r28++;
    }
    var_r22 = var_r24 = HuMemDirectMallocNum(HEAP_DATA, 0x10000, temp_r27->unk_48);
    DCFlushRange(var_r24, 0x10000);
    GXBeginDisplayList(var_r22, 0x10000);
    GXBegin(GX_QUADS, GX_VTXFMT0, arg1 * 4);
    for (i = 0; i < arg1; i++) {
        GXPosition1x16(i * 4);
        GXColor1x16(i);
        GXTexCoord1x16(i * 4);

        GXPosition1x16(i * 4 + 1);
        GXColor1x16(i);
        GXTexCoord1x16(i * 4 + 1);

        GXPosition1x16(i * 4 + 2);
        GXColor1x16(i);
        GXTexCoord1x16(i * 4 + 2);

        GXPosition1x16(i * 4 + 3);
        GXColor1x16(i);
        GXTexCoord1x16(i * 4 + 3);
    }
    GXEnd();
    var_r31->unk34 = GXEndDisplayList();
    var_r31->unk48 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk34, temp_r27->unk_48);
    memcpy(var_r31->unk48, var_r24, var_r31->unk34);
    DCFlushRange(var_r31->unk48, var_r31->unk34);
    HuMemDirectFree(var_r24);
    return var_r23;
}

s16 fn_1_115C4(s16 arg0)
{
    s32 temp_r24;
    s16 var_r22;
    s16 i;
    ModelData *temp_r23;
    ModelData *temp_r27;
    StructM423_05 *temp_r26;
    StructM423_05 *var_r31;
    StructM423_04 *var_r30;
    Vec *var_r25;
    float(*var_r29)[2];

    temp_r23 = &Hu3DData[arg0];
    temp_r26 = temp_r23->unk_120;
    var_r22 = Hu3DHookFuncCreate(temp_r23->hook);
    temp_r27 = &Hu3DData[var_r22];
    temp_r27->unk_120 = var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r31), temp_r27->unk_48);
    var_r31->unk38 = temp_r26->unk38;
    var_r31->unk26 = temp_r26->unk26;
    temp_r24 = var_r31->unk26;
    var_r31->unk20 = 0;
    var_r31->unk22 = temp_r26->unk22;
    var_r31->unk4C = NULL;
    var_r31->unk50 = NULL;
    var_r31->unk28 = 0;
    var_r31->unk21 = 0;
    var_r31->unk30 = 0;
    var_r31->unk00 = var_r31->unk02 = 0;
    var_r31->unk3C = var_r30 = HuMemDirectMallocNum(HEAP_DATA, temp_r24 * sizeof(*var_r30), temp_r27->unk_48);
    for (i = 0; i < temp_r24; i++, var_r30++) {
        var_r30->unk30 = 0.0f;
        var_r30->unk34 = 0.0f;
        var_r30->unk28 = 0.0f;
        var_r30->unk2C = 1.0f;
        var_r30->unk38.x = (frand7() - 64) * 20;
        var_r30->unk38.y = (frand7() - 64) * 30;
        var_r30->unk38.z = (frand7() - 64) * 20;
        var_r30->unk44.r = var_r30->unk44.g = var_r30->unk44.b = var_r30->unk44.a = 0xFF;
        var_r30->unk48 = 0;
    }
    var_r31->unk40 = var_r25 = HuMemDirectMallocNum(HEAP_DATA, temp_r24 * sizeof(*var_r25) * 4, temp_r27->unk_48);
    for (i = 0; i < (temp_r24 * 4); i++, var_r25++) {
        var_r25->x = var_r25->y = var_r25->z = 0.0f;
    }
    var_r31->unk44 = var_r29 = HuMemDirectMallocNum(HEAP_DATA, temp_r24 * sizeof(*var_r29) * 4, temp_r27->unk_48);
    for (i = 0; i < temp_r24; i++) {
        (*var_r29)[0] = 0.0f;
        (*var_r29)[1] = 0.0f;
        var_r29++;
        (*var_r29)[0] = 1.0f;
        (*var_r29)[1] = 0.0f;
        var_r29++;
        (*var_r29)[0] = 1.0f;
        (*var_r29)[1] = 1.0f;
        var_r29++;
        (*var_r29)[0] = 0.0f;
        (*var_r29)[1] = 1.0f;
        var_r29++;
    }
    var_r31->unk34 = temp_r26->unk34;
    var_r31->unk48 = temp_r26->unk48;
    return var_r22;
}

Vec lbl_1_data_8C4[] = { { -0.5f, 0.5f, 0.0f }, { 0.5f, 0.5f, 0.0f }, { 0.5f, -0.5f, 0.0f }, { -0.5f, -0.5f, 0.0f } };

float lbl_1_data_8F4[][2] = { { 0.0f, 0.0f }, { 0.25f, 0.0f }, { 0.25f, 0.25f }, { 0.0f, 0.25f } };

void fn_1_11900(ModelData *arg0, Mtx arg1)
{
    Mtx sp128;
    Mtx spF8;
    Mtx spC8;
    Vec sp98[4];
    Vec sp68[4];
    Vec sp38[4];
    ROMtx sp8;
    StructM423_05 *temp_r31;
    StructM423_04 *var_r29;
    Vec *var_r30;
    float(*var_r28)[2];
    Vec *temp_r27;
    Vec *temp_r24;
    s16 var_r21;
    s16 var_r20;
    s16 var_r19;
    void (*var_r18)(ModelData *, struct struct_m423_05 *, Mtx);
    s16 i;
    s16 j;

    temp_r31 = arg0->unk_120;
    if (temp_r31->unk2C == GlobalCounter && shadowModelDrawF == 0) {
        return;
    }
    if (temp_r31->unk50 && temp_r31->unk50 != arg0) {
        fn_1_11900(temp_r31->unk50, arg1);
    }
    GXLoadPosMtxImm(arg1, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    if (shadowModelDrawF != 0) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    }
    else {
        var_r21 = temp_r31->unk38->bmp->dataFmt & 0xF;
        if (var_r21 == 7 || var_r21 == 8) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
        }
        else {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
        }
        if (temp_r31->unk22 & 1) {
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
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    HuSprTexLoad(temp_r31->unk38, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    switch (temp_r31->unk20) {
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
    if (HmfInverseMtxF3X3(arg1, sp128) == 0) {
        MTXIdentity(sp128);
    }
    PSMTXReorder(sp128, sp8);
    if (temp_r31->unk4C) {
        var_r18 = temp_r31->unk4C;
        var_r18(arg0, temp_r31, arg1);
    }
    var_r29 = temp_r31->unk3C;
    var_r30 = temp_r31->unk40;
    var_r28 = temp_r31->unk44;
    PSMTXROMultVecArray(sp8, lbl_1_data_8C4, sp38, 4);
    for (i = 0; i < temp_r31->unk26; i++, var_r29++) {
        if (!var_r29->unk30) {
            var_r30->x = var_r30->y = var_r30->z = 0.0f;
            var_r30++;
            var_r30->x = var_r30->y = var_r30->z = 0.0f;
            var_r30++;
            var_r30->x = var_r30->y = var_r30->z = 0.0f;
            var_r30++;
            var_r30->x = var_r30->y = var_r30->z = 0.0f;
            var_r30++;
        }
        else if (!var_r29->unk34) {
            temp_r27 = sp98;
            temp_r24 = sp38;
            VECScale(temp_r24++, temp_r27, var_r29->unk30);
            VECAdd(temp_r27++, &var_r29->unk38, var_r30++);
            VECScale(temp_r24++, temp_r27, var_r29->unk30);
            VECAdd(temp_r27++, &var_r29->unk38, var_r30++);
            VECScale(temp_r24++, temp_r27, var_r29->unk30);
            VECAdd(temp_r27++, &var_r29->unk38, var_r30++);
            VECScale(temp_r24++, temp_r27, var_r29->unk30);
            VECAdd(temp_r27++, &var_r29->unk38, var_r30++);
        }
        else {
            VECScale(&lbl_1_data_8C4[0], &sp98[0], var_r29->unk30);
            VECScale(&lbl_1_data_8C4[1], &sp98[1], var_r29->unk30);
            VECScale(&lbl_1_data_8C4[2], &sp98[2], var_r29->unk30);
            VECScale(&lbl_1_data_8C4[3], &sp98[3], var_r29->unk30);
            MTXRotRad(spC8, 'Z', var_r29->unk34);
            MTXConcat(sp128, spC8, spF8);
            MTXMultVecArray(spF8, sp98, sp68, 4);
            VECAdd(&sp68[0], &var_r29->unk38, var_r30++);
            VECAdd(&sp68[1], &var_r29->unk38, var_r30++);
            VECAdd(&sp68[2], &var_r29->unk38, var_r30++);
            VECAdd(&sp68[3], &var_r29->unk38, var_r30++);
        }
    }
    var_r29 = temp_r31->unk3C;
    var_r28 = temp_r31->unk44;
    if (!(temp_r31->unk22 & 2)) {
        for (i = 0; i < temp_r31->unk26; i++, var_r29++) {
            var_r20 = var_r29->unk48 & 3;
            var_r19 = (var_r29->unk48 >> 2) & 3;
            for (j = 0; j < 4; j++, var_r28++) {
                (*var_r28)[0] = 0.25f * var_r20 + lbl_1_data_8F4[j][0];
                (*var_r28)[1] = 0.25f * var_r19 + lbl_1_data_8F4[j][1];
            }
        }
    }
    else {
        for (i = 0; i < temp_r31->unk26; i++, var_r29++) {
            for (j = 0; j < 4; j++, var_r28++) {
                (*var_r28)[0] = 4.0f * lbl_1_data_8F4[j][0];
                (*var_r28)[1] = 4.0f * lbl_1_data_8F4[j][1];
            }
        }
    }
    DCFlushRangeNoSync(temp_r31->unk40, temp_r31->unk26 * sizeof(*temp_r31->unk40) * 4);
    DCFlushRangeNoSync(temp_r31->unk44, temp_r31->unk26 * sizeof(*temp_r31->unk44) * 4);
    DCFlushRangeNoSync(temp_r31->unk3C, temp_r31->unk26 * sizeof(*temp_r31->unk3C));
    PPCSync();
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, temp_r31->unk40, 12);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, &temp_r31->unk3C->unk44, 76);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_TEX0, temp_r31->unk44, 8);
    GXCallDisplayList(temp_r31->unk48, temp_r31->unk34);
    if (shadowModelDrawF == 0) {
        if (!(temp_r31->unk21 & 2)) {
            temp_r31->unk28++;
        }
        if (temp_r31->unk30 != 0 && temp_r31->unk30 <= temp_r31->unk28) {
            if (temp_r31->unk21 & 1) {
                temp_r31->unk28 = 0;
            }
            temp_r31->unk28 = temp_r31->unk30;
        }
        temp_r31->unk2C = GlobalCounter;
    }
}

float fn_1_121DC(float arg0, float arg1)
{
    float var_f31;

    if (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    }
    else if (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    if (arg1 >= 360.0f) {
        arg1 -= 360.0f;
    }
    else if (arg1 < 0.0f) {
        arg1 += 360.0f;
    }
    var_f31 = arg0 - arg1;
    if (var_f31 <= -180.0f) {
        var_f31 += 360.0f;
    }
    else if (var_f31 >= 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}

float fn_1_122F4(float arg0, float arg1, float arg2)
{
    float var_f30;
    float var_f31;

    if (arg0 >= 360.0) {
        arg0 -= 360.0;
    }
    else if (arg0 < 0.0) {
        arg0 += 360.0;
    }
    if (arg1 >= 360.0) {
        arg1 -= 360.0;
    }
    else if (arg1 < 0.0) {
        arg1 += 360.0;
    }
    var_f30 = arg0 - arg1 + 360.0;
    if (fabs(var_f30) >= 360.0) {
        var_f30 = fmod(var_f30, 360.0);
    }
    if (var_f30 < 180.0) {
        if (var_f30 <= arg2) {
            var_f31 = var_f30;
        }
        else {
            var_f31 = arg2;
        }
    }
    else {
        if (360.0 - var_f30 <= arg2) {
            var_f31 = -(360.0 - var_f30);
        }
        else {
            var_f31 = -arg2;
        }
    }
    var_f31 += arg1;
    if (var_f31 >= 360.0) {
        var_f31 -= 360.0;
    }
    else if (var_f31 < 0.0) {
        var_f31 += 360.0;
    }
    return var_f31;
}

float fn_1_12544(float arg0, float arg1, float arg2)
{
    float var_f28;

    var_f28 = fn_1_121DC(arg2, arg1);
    return fn_1_122F4(arg2, arg1, fabs(var_f28 * arg0));
}

void fn_1_1293C(Mtx arg0, Vec *arg1)
{
    Vec sp8;

    sp8.x = arg0[0][0] * arg1->x + arg0[0][1] * arg1->y + arg0[0][2] * arg1->z;
    sp8.y = arg0[1][0] * arg1->x + arg0[1][1] * arg1->y + arg0[1][2] * arg1->z;
    sp8.z = arg0[2][0] * arg1->x + arg0[2][1] * arg1->y + arg0[2][2] * arg1->z;
    *arg1 = sp8;
}

void fn_1_129F0(Vec *arg0, Vec *arg1, Vec *arg2, float *arg3)
{
    Vec sp18;
    Vec spC;
    float var_f30;
    float var_f29;

    sp18.x = arg1->x - arg0->x;
    sp18.y = arg1->y - arg0->y;
    sp18.z = arg1->z - arg0->z;
    spC.x = arg2->x - arg1->x;
    spC.y = arg2->y - arg1->y;
    spC.z = arg2->z - arg1->z;
    arg3[0] = sp18.y * spC.z - sp18.z * spC.y;
    arg3[1] = sp18.z * spC.x - sp18.x * spC.z;
    arg3[2] = sp18.x * spC.y - sp18.y * spC.x;
    var_f29 = arg3[0] * arg3[0] + arg3[1] * arg3[1] + arg3[2] * arg3[2];
    var_f30 = sqrtf(var_f29);
    if (var_f30 != 0.0f) {
        var_f30 = 1.0f / var_f30;
    }
    else {
        var_f30 = 0.0f;
    }
    arg3[0] *= var_f30;
    arg3[1] *= var_f30;
    arg3[2] *= var_f30;
    arg3[3] = -(arg3[0] * arg0->x + arg3[1] * arg0->y + arg3[2] * arg0->z);
}

s32 fn_1_12C6C(Vec *arg0, Vec *arg1, float *arg2)
{
    float temp_f31;
    float temp_f30;

    temp_f31 = arg0->x * arg2[0] + arg0->y * arg2[1] + arg0->z * arg2[2] + arg2[3];
    temp_f30 = arg1->x * arg2[0] + arg1->y * arg2[1] + arg1->z * arg2[2] + arg2[3];
    if (temp_f31 <= 0.0f && temp_f30 > 0.0f) {
        return 1;
    }
    if (temp_f31 >= 0.0f && temp_f30 < 0.0f) {
        return -1;
    }
    return 0;
}

float fn_1_12D6C(Vec *arg0, Vec *arg1, s32 arg2, float arg3, float arg4)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;

    switch (arg2) {
        case 0:
            var_f31 = arg0->y - arg3;
            var_f30 = arg0->z - arg4;
            var_f29 = arg1->y - arg3;
            var_f28 = arg1->z - arg4;
            break;
        case 1:
            var_f31 = arg0->x - arg3;
            var_f30 = arg0->z - arg4;
            var_f29 = arg1->x - arg3;
            var_f28 = arg1->z - arg4;
            break;
        case 2:
            var_f31 = arg0->x - arg3;
            var_f30 = arg0->y - arg4;
            var_f29 = arg1->x - arg3;
            var_f28 = arg1->y - arg4;
            break;
    }
    var_f27 = -(var_f30 * var_f29 - var_f31 * var_f28);
    return var_f27;
}

u8 lbl_1_data_914[][2] = { { 0, 1 }, { 1, 2 }, { 2, 0 } };

float fn_1_12E68(Vec *arg0, Vec *arg1, s32 arg2)
{
    float var_f31;
    float var_f30;
    float var_f29;
    s32 i;

    switch (arg2) {
        case 0:
            var_f31 = arg1->y;
            var_f30 = arg1->z;
            break;
        case 1:
            var_f31 = arg1->x;
            var_f30 = arg1->z;
            break;
        case 2:
            var_f31 = arg1->x;
            var_f30 = arg1->y;
            break;
    }
    var_f29 = fn_1_12D6C(&arg0[lbl_1_data_914[0][0]], &arg0[lbl_1_data_914[0][1]], arg2, var_f31, var_f30);
    if (var_f29 > 0.0f) {
        for (i = 1; i < 3; i++) {
            var_f29 = fn_1_12D6C(&arg0[lbl_1_data_914[i][0]], &arg0[lbl_1_data_914[i][1]], arg2, var_f31, var_f30);
            if (var_f29 == 0.0f) {
                return 1.0f;
            }
            if (var_f29 < 0.0f) {
                return 0.0f;
            }
        }
        return 1.0f;
    }
    else {
        for (i = 1; i < 3; i++) {
            var_f29 = fn_1_12D6C(&arg0[lbl_1_data_914[i][0]], &arg0[lbl_1_data_914[i][1]], arg2, var_f31, var_f30);
            if (var_f29 == 0.0f) {
                return -1.0f;
            }
            if (var_f29 > 0.0f) {
                return 0.0f;
            }
        }
        return -1.0f;
    }
}

void fn_1_1334C(float *arg0, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4)
{
    float temp_f26;
    float temp_f25;
    float temp_f24;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float var_f22;
    float var_f21;
    float var_f20;
    float var_f19;
    float var_f18;
    float spC;
    float var_f28;

    temp_f26 = arg0[0];
    temp_f25 = arg0[1];
    temp_f24 = arg0[2];
    var_f19 = arg3->x;
    var_f18 = arg3->y;
    spC = arg3->z;
    temp_f31 = arg2->x;
    temp_f30 = arg2->y;
    temp_f29 = arg2->z;
    var_f22 = arg1->x;
    var_f21 = arg1->y;
    var_f20 = arg1->z;
    var_f28 = sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30 + temp_f29 * temp_f29);
    if (var_f28 != 0.0f) {
        var_f28 = 1.0f / var_f28;
    }
    temp_f31 *= var_f28;
    temp_f30 *= var_f28;
    temp_f29 *= var_f28;
    var_f28 = temp_f26 * temp_f31 + temp_f25 * temp_f30 + temp_f24 * temp_f29;
    if (var_f28 != 0.0f) {
        var_f28 = -(temp_f26 * (var_f22 - var_f19) + temp_f25 * (var_f21 - var_f18) + temp_f24 * (var_f20 - spC)) / var_f28;
    }
    else {
        var_f28 = 0.0f;
    }
    arg4->x = arg1->x + var_f28 * arg2->x;
    arg4->y = arg1->y + var_f28 * arg2->y;
    arg4->z = arg1->z + var_f28 * arg2->z;
}

float fn_1_1367C(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, f32 *arg4)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;

    arg0->z = 0.0f;
    arg1->z = 0.0f;
    arg2->z = 0.0f;
    VECSubtract(arg1, arg0, &sp2C);
    VECSubtract(arg2, arg0, &sp20);
    temp_f31 = (sp2C.x * sp20.x + sp2C.y * sp20.y) / (sp2C.x * sp2C.x + sp2C.y * sp2C.y);
    if (arg4 != NULL) {
        *arg4 = temp_f31;
    }
    VECScale(&sp2C, &sp14, temp_f31);
    VECAdd(&sp2C, &sp14, &sp38);
    if (arg3 != NULL) {
        *arg3 = sp38;
    }
    VECSubtract(arg2, &sp38, &sp8);
    return VECMag(&sp8);
}

s32 fn_1_137C4(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, float arg4, s32 arg5)
{
    Vec sp40;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f28;
    f32 var_f31;

    VECAdd(arg1, arg2, &sp28);
    *arg3 = sp28;
    VECNormalize(arg2, &sp1C);
    VECScale(&sp1C, &sp1C, arg4);
    VECAdd(arg1, &sp1C, &sp40);
    VECAdd(&sp28, &sp1C, &sp34);
    VECNormalize(arg2, &sp1C);
    VECScale(&sp1C, &sp10, -arg4);
    switch (arg5) {
        case 0:
            if (sp40.y >= arg0[0].y && sp34.y < arg0[0].y) {
                if (sp1C.y == 0.0f) {
                    var_f31 = 0.0f;
                }
                else {
                    var_f31 = (arg0[0].y - arg1->y) / sp1C.y;
                }
                temp_f30 = arg1->x + var_f31 * sp1C.x;
                temp_f28 = arg1->z + var_f31 * sp1C.z;
                if (temp_f30 >= arg0[0].x && temp_f30 <= arg0[2].x && temp_f28 >= arg0[0].z && temp_f28 <= arg0[2].z) {
                    arg3->x = temp_f30;
                    arg3->y = arg0[0].y + arg4 + 1.0f;
                    arg3->z = temp_f28;
                    VECAdd((Vec *)&arg3, &sp10, (Vec *)&arg3);
                    return 1;
                }
            }
            break;
        case 1:
            if (sp40.y <= arg0[0].y && sp34.y > arg0[0].y) {
                if (sp1C.y == 0.0f) {
                    var_f31 = 0.0f;
                }
                else {
                    var_f31 = (arg0[0].y - arg1->y) / sp1C.y;
                }
                temp_f30 = arg1->x + var_f31 * sp1C.x;
                temp_f28 = arg1->z + var_f31 * sp1C.z;
                if (temp_f30 >= arg0[0].x && temp_f30 <= arg0[2].x && temp_f28 <= arg0[0].z && temp_f28 >= arg0[2].z) {
                    arg3->x = temp_f30;
                    arg3->y = arg0[0].y - arg4 - 1.0f;
                    arg3->z = temp_f28;
                    VECAdd((Vec *)&arg3, &sp10, (Vec *)&arg3);
                    return 1;
                }
            }
            break;
        case 2:
            if (sp40.x <= arg0[0].x && sp34.x > arg0[0].x) {
                if (sp1C.x == 0.0f) {
                    var_f31 = 0.0f;
                }
                else {
                    var_f31 = (arg0[0].x - arg1->x) / sp1C.x;
                }
                temp_f29 = arg1->y + var_f31 * sp1C.y;
                temp_f28 = arg1->z + var_f31 * sp1C.z;
                if (temp_f29 <= arg0[0].y && temp_f29 >= arg0[2].y && temp_f28 >= arg0[0].z && temp_f28 <= arg0[2].z) {
                    arg3->x = arg0[0].x - arg4 - 1.0f;
                    arg3->y = temp_f29;
                    arg3->z = temp_f28;
                    VECAdd((Vec *)&arg3, &sp10, (Vec *)&arg3);
                    return 1;
                }
            }
            break;
        case 3:
            if (sp40.x >= arg0[0].x && sp34.x < arg0[0].x) {
                if (sp1C.x == 0.0f) {
                    var_f31 = 0.0f;
                }
                else {
                    var_f31 = (arg0[0].x - arg1->x) / sp1C.x;
                }
                temp_f29 = arg1->y + var_f31 * sp1C.y;
                temp_f28 = arg1->z + var_f31 * sp1C.z;
                if (temp_f29 <= arg0[0].y && temp_f29 >= arg0[2].y && temp_f28 <= arg0[0].z && temp_f28 >= arg0[2].z) {
                    arg3->x = arg0[0].x + arg4 + 1.0f;
                    arg3->y = temp_f29;
                    arg3->z = temp_f28;
                    VECAdd((Vec *)&arg3, &sp10, (Vec *)&arg3);
                    return 1;
                }
            }
            break;
        case 4:
            if (sp40.z >= arg0[0].z && sp34.z < arg0[0].z) {
                if (sp1C.z == 0.0f) {
                    var_f31 = 0.0f;
                }
                else {
                    var_f31 = (arg0[0].z - arg1->z) / sp1C.z;
                }
                temp_f30 = arg1->x + var_f31 * sp1C.x;
                temp_f29 = arg1->y + var_f31 * sp1C.y;
                if (temp_f30 >= arg0[0].x && temp_f30 <= arg0[2].x && temp_f29 <= arg0[0].y && temp_f29 >= arg0[2].y) {
                    arg3->x = temp_f30;
                    arg3->y = temp_f29;
                    arg3->z = arg0[0].z + arg4 + 1.0f;
                    VECAdd((Vec *)&arg3, &sp10, (Vec *)&arg3);
                    return 1;
                }
            }
            break;
        case 5:
            if (sp40.z <= arg0[0].z && sp34.z > arg0[0].z) {
                if (sp1C.z == 0.0f) {
                    var_f31 = 0.0f;
                }
                else {
                    var_f31 = (arg0[0].z - arg1->z) / sp1C.z;
                }
                temp_f30 = arg1->x + var_f31 * sp1C.x;
                temp_f29 = arg1->y + var_f31 * sp1C.y;
                if (temp_f30 <= arg0[0].x && temp_f30 >= arg0[2].x && temp_f29 <= arg0[0].y && temp_f29 >= arg0[2].y) {
                    arg3->x = temp_f30;
                    arg3->y = temp_f29;
                    arg3->z = arg0[0].z - arg4 - 1.0f;
                    VECAdd((Vec *)&arg3, &sp10, (Vec *)&arg3);
                    return 1;
                }
            }
            break;
    }
    return 0;
}
