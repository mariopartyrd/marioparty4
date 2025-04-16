#include "REL/m427Dll.h"

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXVert.h"
#include "dolphin/pad.h"
#include "ext_math.h"
#include "game/animdata.h"
#include "game/audio.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "string.h"

extern s32 rand8(void);
SHARED_SYM extern LightData Hu3DLocalLight[0x20];

#define FABS(value) ((value < 0) ? -(value) : (value))

typedef struct M427DllStruct2 {
    s32 unk0[3];
    s32 unkC;
    s32 unk10;
    s32 unk14[7];
    s32 unk30[7];
    HsfVector2f unk4C[7];
    f32 unk84;
    f32 unk88;
    s32 unk8C;
    f32 unk90;
    f32 unk94;
    f32 unk98;
    s32 unk9C;
    s32 unkA0;
} M427DllStruct2; // sizeof 0xA4

typedef struct M427DllStruct3 {
    Vec rot;
    Vec cen;
    f32 zoom;
} M427DllStruct3; // sizeof 0x1C

typedef struct M427DllMapStruct {
    u8 unk0;
    char unk_1;
    s16 unk2;
    s16 unk4;
    char unk_6[0x2];
    AnimData *unk8;
    Vec unkC;
    Vec unk18;
    Vec unk24;
    Vec unk30;
    Vec2f unk3C;
    Vec2f unk44;
    Vec2f unk4C;
    Vec2f unk54;
    Vec2f unk5C[4];
    GXColor unk7C;
    void *unk80;
    s32 unk84;
    float unk88;
    float unk8C;
    float unk90;
    float unk94;
} M427DllMapStruct; // sizeof 0x98

typedef struct M427DllMapStruct2 {
    s8 unk0;
    s16 unk2;
    s16 unk4;
} M427DllMapStruct2; // sizeof 0x6

typedef struct M427DllMapSubstruct {
    s16 unk0;
    Vec unk4;
} M427DllMapSubstruct; // sizeof 0x10

typedef struct M427DllMapSubstruct2 {
    s16 unk0;
    Vec unk4;
    s16 unk10[2];
    s16 unk14[4];
} M427DllMapSubstruct2; // sizeof 0x1C

typedef struct M427DllMapSubstruct7 {
    s16 unk0;
    s32 unk4;
    void *unk8;
} M427DllMapSubstruct7; // sizeof 0xC

typedef struct M427DllMapUNKB8 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 unk8;
    s16 unkA;
    float unkC;
    float unk_10;
    float unk_14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    float unk20;
    float unk24;
    float unk28;
    float unk2C;
} M427DllMapUNKB8; // sizeof 0x30

typedef struct M427DllMapUNK17E {
    s16 unk0;
    s16 unk2;
} M427DllMapUNK17E; // sizeof 0x4

typedef struct M427DllMapSubstruct3Sub {
    s16 unk0;
    void *unk4;
    u32 unk8;
} M427DllMapSubstruct3Sub; // sizeof 0xC

typedef struct M427DllMapSubstruct3 {
    s16 unk0;
    s16 unk2[11];
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    char unk_22[2];
    float unk24[4];
    s16 unk34[4];
    s16 unk3C[4];
    s16 unk44[0xB];
    s16 unk5A;
    s16 unk5C;
    char unk_5E[2];
    Vec unk_60;
    Vec unk_6C;
    Vec unk78;
    Vec unk84;
    f32 unk90;
    M427DllMapSubstruct3Sub unk94;
    char unk_A0[0xC];
    struct M427DllMapStruct6 *unkAC;
    s16 unkB0[1];
    char unk_B2[0x6];
    M427DllMapUNKB8 unkB8[2][2];
    s16 unk178[3];
    M427DllMapUNK17E unk17E[2][2];
    s16 unk18E[2];
    char unk194[4];
} M427DllMapSubstruct3; // sizeof 0x198

typedef struct M427DllMapStruct3Sub {
    AnimData *unk_00;
    AnimData *unk_04;
    float unk_08;
    float unk_0C;
    float unk_10;
    float unk_14;
} M427DllMapStruct3Sub; // sizeof 0x18

typedef struct M427DllMapStruct3 {
    u8 unk0;
    M427DllMapSubstruct3 unk4[2];
    M427DllMapStruct3Sub unk334;
    M427DllMapSubstruct2 unk34C[3];
    M427DllMapSubstruct unk3A0[5];
} M427DllMapStruct3; // sizeof 0x3F0

typedef struct M427DllMapSubstruct5 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    Vec unk8;
    char unk14[0x8];
} M427DllMapSubstruct5; // sizeof 0x1C

typedef struct M427DllMapStruct4 {
    s16 unk0;
    Vec *unk4;
    Vec2f *unk8;
    Vec *unkC;
    GXColor *unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    M427DllMapSubstruct5 *unk1C;
    void *unk20;
    u32 unk24;
    void *unk28;
    u32 unk2C;
    void *unk30;
    u32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    s16 unk48[1];
    s16 unk4A;
} M427DllMapStruct4; // sizeof 0x4C

typedef struct M427DllMapStruct5 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} M427DllMapStruct5; // sizeof 0x14

typedef struct M427DllMapStruct6 {
    s16 unk_00;
    Vec *unk_04;
    Vec *unk_08;
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    float unk_20;
    float unk_24;
    AnimData *unk_28;
    Vec *unk_2C;
    Vec2f *unk_30;
    Vec *unk_34;
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    char pad_3E[2];
    void *unk_40;
    u32 unk_44;
    M427DllMapSubstruct5 *unk_48;
    float unk_4C;
    float unk_50;
    float unk_54;
    float unk_58;
    float unk_5C;
    /* 0x60 */ float unk_60;
} M427DllMapStruct6; /* size = 0x64, stored in unk_120 */

typedef struct M427DllMapSubstruct6 {
    /* 0x00 */ float unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ char pad_0C[0xC]; /* maybe part of unk_08[4]? */
    /* 0x18 */ float unk_18;
    /* 0x1C */ float unk_1C;
    /* 0x20 */ float unk_20;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ float unk_2C;
    /* 0x30 */ float unk_30;
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ char pad_3A[2];
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ char pad_42[2];
    /* 0x44 */ float unk_44;
    /* 0x48 */ Vec unk_48;
    /* 0x54 */ Vec unk_54;
    /* 0x60 */ s16 unk_60;
    /* 0x62 */ s8 unk_62;
    /* 0x63 */ char pad_63[1];
} M427DllMapSubstruct6; // sizeof 0x64

typedef void (*M427DllHook)(ModelData *model, struct M427DllMapStruct7 *particle, Mtx matrix);

typedef struct M427DllMapStruct7 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char pad_02[2];
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ char pad_09[3]; /* maybe part of unk_08[4]? */
    /* 0x0C */ M427DllHook unk_0C;
    /* 0x10 */ AnimData *unk_10;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ char pad_16[2];
    /* 0x18 */ M427DllMapSubstruct6 *unk_18;
    /* 0x1C */ Vec *unk_1C;
    /* 0x20 */ Vec2f *unk_20;
    /* 0x24 */ GXColor *unk_24;
    /* 0x28 */ void *unk_28;
    /* 0x2C */ Vec unk_2C;
    /* 0x38 */ float unk_38;
    /* 0x3C */ float unk_3C;
    /* 0x40 */ float unk_40;
    /* 0x44 */ float unk_44;
    /* 0x48 */ float unk_48;
    /* 0x4C */ float unk_4C;
    /* 0x50 */ float unk_50;
    /* 0x54 */ float unk_54;
    /* 0x58 */ float unk_58;
    /* 0x5C */ Vec2f *unk_5C;
    /* 0x60 */ float unk_60;
    /* 0x64 */ float unk_64;
} M427DllMapStruct7; /* size = 0x68, stored in unk_120 */

GXColor lbl_1_data_E8 = { 0xFF, 0xFF, 0xFF, 0xFF };

omObjData *lbl_1_bss_548;
M427DllMapStruct3 lbl_1_bss_158;
M427DllMapStruct2 lbl_1_bss_F8[0x10];
AnimData *lbl_1_bss_F4;
M427DllMapStruct *lbl_1_bss_F0;
s16 lbl_1_bss_EC[2];
s16 lbl_1_bss_E8[2];
M427DllMapStruct5 *lbl_1_bss_E4;
M427DllMapStruct4 lbl_1_bss_98;
f32 lbl_1_bss_94;
s8 lbl_1_bss_91;
s8 lbl_1_bss_90;

void fn_1_372C(void);
void fn_1_4218(omObjData *object);
void fn_1_44F4(f32, f32, f32, f32, f32);
void fn_1_48EC(ModelData *model, Mtx matrix);
void fn_1_4D7C(ModelData *model, Mtx matrix);
void fn_1_50A0(ModelData *model, Mtx matrix);
void fn_1_510C(s32, s16, s16);
void fn_1_558C(M427DllMapStruct4 *);
void fn_1_618C(ModelData *model, Mtx matrix);
void fn_1_6760(omObjData *object);
void fn_1_C2C8(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3);
void fn_1_D22C(ModelData *model, struct M427DllMapStruct7 *arg1, Mtx matrix);
s16 fn_1_D63C(AnimData *arg0, s16 arg1, float arg8, s16 arg2, s16 arg3);
void fn_1_DB80(s16);
void fn_1_DC64(s16, M427DllHook);
void fn_1_DC9C(s16, u8);

void fn_1_72E4(omObjData *arg0);
void fn_1_73BC(void);
void fn_1_794C(M427DllMapSubstruct3 *arg0, s16 arg1);
void fn_1_7C34(void);
void fn_1_7E60(s16 arg0, M427DllMapSubstruct3 *arg1);
void fn_1_7F38(void);
void fn_1_85D4(s16 arg0, M427DllMapSubstruct3 *arg1);
void fn_1_8768(M427DllMapSubstruct3 *arg0, M427DllMapUNKB8 *arg1, s16 arg2, float arg8, float arg9);
void fn_1_8E1C(u8 arg0, M427DllMapSubstruct3 *arg1, M427DllMapUNKB8 *arg2);
void fn_1_8F90(omObjData *object);
void fn_1_9240(void);
void fn_1_9318(s16 *arg0, s16 arg1);
void fn_1_93EC(s32 arg0, s32 arg1, float arg8, float arg9, float argA, float argB);
s16 fn_1_95E8(s32 arg0, s16 arg1, s16 arg2, float arg8, float arg9, float argA, float argB, float argC);
void fn_1_9958(s16 arg0, u8 arg1);
void fn_1_999C(s16 arg0, u8 arg1);
void fn_1_99E4(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void fn_1_9A2C(s16 arg0, float arg8, float arg9, float argA);
void fn_1_9AA0(s16 arg0, float arg8, float arg9, float argA);
void fn_1_9B14(s16 arg0, float arg8, float arg9, float argA);
void fn_1_9B88(ModelData *model, Mtx matrix);
void fn_1_A148(ModelData *model, Mtx matrix);
s16 fn_1_A1F4(s32 arg0, s16 arg1, s16 arg2, s16 arg3, float arg8, Vec *arg4, Vec *arg5);
void fn_1_A7F8(M427DllMapStruct6 *arg0);
void fn_1_B194(M427DllMapStruct6 *arg0, float arg8, Vec *arg1);
void fn_1_B3CC(ModelData *model, Mtx matrix);
void fn_1_C154(ModelData *model, Mtx matrix);
void fn_1_C200(ModelData *model, Mtx matrix);
void fn_1_C2AC(Vec *arg0, float arg8, float arg9, float argA);
void fn_1_C2BC(Vec2f *arg0, float arg8, float arg9);
s16 fn_1_C41C(float arg8, float arg9, float argA, float argB, float argC, float argD, u8 arg0, u8 arg1, u8 arg2);
void fn_1_C528(s16 arg0, s16 arg1, float arg8, float arg9, float argA, float argB, float argC, float argD, u8 arg2, u8 arg3, u8 arg4);
void fn_1_C68C(LightData *arg0, Vec *arg1, Vec *arg2, GXColor *arg3);
void fn_1_C76C(u8 arg0, float arg8, float arg9, float argA, s16 arg1, float argB, float argC, s16 arg2);
s16 fn_1_D430(float arg8, float arg9, float argA, s16 arg0);
M427DllMapSubstruct6 *fn_1_D4FC(s16 arg0, Vec *arg1, Vec *arg2, float arg8, GXColor *arg3);
M427DllMapSubstruct6 *fn_1_DC0C(s16 arg0, s16 arg1);
void fn_1_DCD4(ModelData *model, Mtx matrix);
void fn_1_E2B0(Vec2f *arg0, s16 arg1, s16 arg2, float arg8, float arg9);
void fn_1_E37C(Vec2f *arg0, Vec2f *arg1, s16 arg2, float arg8, float arg9);
void fn_1_E420(Vec *arg0, Vec *arg1, Vec *arg2, s16 arg3);

void fn_1_32F4(Process *arg0)
{
    s16 var_r31;
    AnimData *temp_r30;
    s32 var_r29;
    s32 var_r28;

    lbl_1_bss_158.unk0 = 0;
    lbl_1_bss_548 = omAddObjEx(arg0, 0x7F, 0, 0, -1, fn_1_6760);
    lbl_1_bss_F0 = HuMemDirectMallocNum(HEAP_SYSTEM, 16 * sizeof(M427DllMapStruct), MEMORY_DEFAULT_NUM);

    for (var_r31 = 0; var_r31 < 16; var_r31++) {
        lbl_1_bss_F0[var_r31].unk2 = -1;
    }
    temp_r30 = HuSprAnimRead(HuDataReadNum(0x3A0017, MEMORY_DEFAULT_NUM));
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_EC[var_r31] = fn_1_D63C(temp_r30, 0x200, 80.0f, 0x40, 0x40);
        fn_1_DC64(lbl_1_bss_EC[var_r31], fn_1_D22C);
        fn_1_DC9C(lbl_1_bss_EC[var_r31], 1);
        Hu3DModelLayerSet(lbl_1_bss_EC[var_r31], 7);
        if (var_r31 == 0) {
            var_r29 = 1;
        }
        else {
            var_r29 = 2;
        }
        Hu3DModelCameraSet(lbl_1_bss_EC[var_r31], var_r29);
    }
    temp_r30 = HuSprAnimRead(HuDataReadNum(0x3A001A, MEMORY_DEFAULT_NUM));
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        lbl_1_bss_E8[var_r31] = fn_1_D63C(temp_r30, 4, 120.0f, 0, 0);
        fn_1_DC9C(lbl_1_bss_E8[var_r31], 1);
        Hu3DModelLayerSet(lbl_1_bss_E8[var_r31], 7);
        if (var_r31 == 0) {
            var_r28 = 1;
        }
        else {
            var_r28 = 2;
        }
        Hu3DModelCameraSet(lbl_1_bss_E8[var_r31], var_r28);
    }
    fn_1_372C();

    for (var_r31 = 0; var_r31 < 0x10; var_r31++) {
        lbl_1_bss_F8[var_r31].unk0 = -1;
        lbl_1_bss_F8[var_r31].unk2 = Hu3DModelCreateFile(0x3A0012);
        Hu3DModelAttrSet(lbl_1_bss_F8[var_r31].unk2, 1);
        Hu3DModelScaleSet(lbl_1_bss_F8[var_r31].unk2, 0.75f, 0.75f, 0.75f);
        Hu3DModelLayerSet(lbl_1_bss_F8[var_r31].unk2, 4);
        Hu3DMotionSpeedSet(lbl_1_bss_F8[var_r31].unk2, 2.0f);
        lbl_1_bss_F8[var_r31].unk4 = Hu3DAnimCreate(HuDataReadNum(0x3A001B, MEMORY_DEFAULT_NUM), lbl_1_bss_F8[var_r31].unk2, "db91");
        Hu3DAnimSpeedSet(lbl_1_bss_F8[var_r31].unk4, 2.0f);
    }
}

void fn_1_372C(void)
{
    M427DllMapSubstruct *var_r29 = &lbl_1_bss_158.unk3A0[0];
    M427DllMapSubstruct2 *var_r30 = &lbl_1_bss_158.unk34C[0];
    s16 sp1A[5] = { 0, 0, 1, 1, 0 };
    Vec sp60[5] = { { -700.0f, -150.0f, -7000.0f }, { 0.0f, -300.0f, -12000.0f }, { 800.0f, -350.0f, -12700.0f }, { 600.0f, -350.0f, -13700.0f },
        { 825.0f, -450.0f, -15000.0f } };
    s16 sp8[3] = { 1, 1, 0 };
    s16 spE[3][2] = { { 4, 5 }, { 8, -1 }, { 9, -1 } };
    s16 sp24[3][4] = { { 180, 120, 60, 60 }, { 90, 180, 60, 60 }, { 90, 180, 60, 60 } };
    Vec sp3C[3] = { -350.0f, -300.0f, -10000.0f, -700.0f, -600.0f, -17000.0f, 700.0f, -600.0f, -19000.0f };
    s16 var_r28;
    s16 var_r31;

    for (var_r31 = 0; var_r31 < 5; var_r31++, var_r29++) {
        var_r29->unk0 = sp1A[var_r31];
        var_r29->unk4.x = sp60[var_r31].x;
        var_r29->unk4.y = sp60[var_r31].y;
        var_r29->unk4.z = sp60[var_r31].z;
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++, var_r30++) {
        var_r30->unk0 = sp8[var_r31];
        var_r30->unk4.x = sp3C[var_r31].x;
        var_r30->unk4.y = sp3C[var_r31].y;
        var_r30->unk4.z = sp3C[var_r31].z;
        var_r30->unk10[0] = spE[var_r31][0];
        var_r30->unk10[1] = spE[var_r31][1];
        for (var_r28 = 0; var_r28 < 4; var_r28++) {
            var_r30->unk14[var_r28] = sp24[var_r31][var_r28];
        }
    }
}

void fn_1_3A88(void)
{
    M427DllMapStruct *sp8;
    s16 var_r30;
    M427DllMapSubstruct3 *var_r31;

    sp8 = lbl_1_bss_F0;
    HuSprAnimKill(lbl_1_bss_158.unk334.unk_00);
    HuSprAnimKill(lbl_1_bss_158.unk334.unk_04);

    for (var_r30 = 0, var_r31 = &lbl_1_bss_158.unk4[0]; var_r30 < 2; var_r30++, var_r31++) {
        if (var_r31->unk94.unk4) {
            HuMemDirectFree(var_r31->unk94.unk4);
        }
    }
}

void fn_1_3B20(s8 arg0, s16 arg1)
{
    M427DllMapStruct2 *var_r31 = &lbl_1_bss_F8[0];
    M427DllMapSubstruct3 *temp_r30 = &lbl_1_bss_158.unk4[arg1];
    Vec sp54[4] = { { 110.0f, -20.0f, 0.0f }, { -110.0f, -20.0f, 0.0f }, { 110.0f, -20.0f, 190.0f }, { -110.0f, -20.0f, 190.0f } };
    Mtx sp24;
    f32 sp14[4] = { 135.0f, 225.0f, 45.0f, 315.0f };
    Vec sp8;
    f32 temp_f31;
    s16 var_r29;
    s32 var_r27;

    for (var_r29 = 0; var_r29 < 0x10; var_r29++, var_r31++) {
        if (var_r31->unk0 == -1)
            break;
    }
    if (var_r29 != 0x10) {
        var_r31->unk0 = arg0;
        temp_f31 = temp_r30->unk90;
        MTXRotRad(sp24, 0x59, MTXDegToRad(temp_f31));
        MTXMultVec(sp24, &sp54[arg0], &sp8);
        sp8.x += temp_r30->unk84.x;
        sp8.y += temp_r30->unk84.y;
        sp8.z += temp_r30->unk84.z;
        Hu3DModelAttrReset(var_r31->unk2, 1);
        if (arg1 == 0) {
            var_r27 = 1;
        }
        else {
            var_r27 = 2;
        }
        Hu3DModelCameraSet(var_r31->unk2, var_r27);
        Hu3DModelPosSet(var_r31->unk2, sp8.x, sp8.y, sp8.z);
        Hu3DModelRotSet(var_r31->unk2, 0.0f, temp_f31 + sp14[arg0], 0.0f);
        Hu3DMotionTimeSet(var_r31->unk2, 0.0f);
        if (arg0 < 2) {
            Hu3DModelAmbSet(var_r31->unk2, 1.0f, 1.0f, 1.0f);
        }
        else {
            Hu3DModelAmbSet(var_r31->unk2, 0.5f, 0.5f, 0.5f);
        }
        Hu3DAnimBankSet(var_r31->unk4, 0);
    }
}

void fn_1_3DBC(void)
{
    M427DllMapStruct2 *var_r31;
    s16 var_r30;
    f32 temp_f31;

    var_r31 = &lbl_1_bss_F8[0];
    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (var_r31->unk0 != -1) {
            temp_f31 = Hu3DMotionMaxTimeGet(var_r31->unk2);
            if (Hu3DMotionTimeGet(var_r31->unk2) >= temp_f31) {
                var_r31->unk0 = -1;
                Hu3DModelAttrSet(var_r31->unk2, 1U);
            }
        }
    }
}

void fn_1_3E58(omObjData *arg0)
{
    s32 sp8[8];
    M427DllMapStruct *var_r26;
    M427DllMapSubstruct3 *var_r31;
    ModelData *temp_r25;
    s16 var_r30;
    M427DllMapStruct4 *var_r29;
    s16 var_r28;
    s16 var_r27;

    var_r29 = &lbl_1_bss_98;
    for (var_r28 = 0, var_r31 = lbl_1_bss_158.unk4; var_r28 < 2; var_r28++, var_r31++) {
        var_r27 = fn_1_10FE8(var_r31->unk0, &sp8[0]);

        for (var_r30 = 0; var_r30 < var_r27; var_r30++) {
            temp_r25 = &Hu3DData[sp8[var_r30]];
            temp_r25->unk_38[4] = temp_r25->unk_38[5] = temp_r25->unk_38[6] = temp_r25->unk_38[7] = -1;
        }

        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            for (var_r27 = 0; var_r27 < 2; var_r27++) {
                Hu3DModelKill(var_r31->unk17E[var_r30][var_r27].unk2);
            }
        }
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            for (var_r27 = 0; var_r27 < 2; var_r27++) {
                Hu3DModelKill(var_r31->unkB8[var_r30][var_r27].unk2);
            }
        }
        HuSprAnimKill(var_r31->unkAC->unk_28);
        Hu3DModelKill(var_r31->unk1A);
        Hu3DModelKill(var_r31->unk1C);
        HuMemDirectFree(var_r31->unk94.unk4);
        var_r31->unk94.unk4 = NULL;
        fn_1_DB80(lbl_1_bss_EC[var_r28]);
        fn_1_DB80(lbl_1_bss_E8[var_r28]);

        for (var_r30 = 0; var_r30 < 11; var_r30++) {
            Hu3DModelKill(var_r31->unk2[var_r30]);
        }
        Hu3DModelKill(var_r31->unk1E);
        Hu3DModelKill(var_r31->unk20);
    }
    for (var_r28 = 0, var_r26 = lbl_1_bss_F0; var_r28 < 0x10; var_r28++, var_r26++) {
        if (var_r26->unk2 != -1) {
            Hu3DModelKill(var_r26->unk4);
            HuSprAnimKill(var_r26->unk8);
            HuMemDirectFree(var_r26->unk80);
        }
    }
    HuMemDirectFree(lbl_1_bss_F0);
    Hu3DFogClear();
    var_r30 = Hu3DModelCreateFile(0x3A0011);
    Hu3DModelCameraSet(var_r30, 1);
    Hu3DModelLayerSet(var_r30, 1);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    var_r29->unk0 = Hu3DModelCreateFile(0x3A0010);
    Hu3DModelCameraSet(var_r29->unk0, 1);
    Hu3DModelLayerSet(var_r29->unk0, 3);
    Hu3DModelPosSet(var_r29->unk0, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_158.unk0 = 1;
    var_r29->unk48[0] = 0;
    var_r29->unk4A = 0;
    var_r29->unk4 = 0;
    lbl_1_bss_E4 = HuMemDirectMallocNum(HEAP_SYSTEM, 16 * sizeof(M427DllMapStruct5), MEMORY_DEFAULT_NUM);
    for (var_r28 = 0; var_r28 < 16; var_r28++) {
        lbl_1_bss_E4[var_r28].unk10 = -1.0f;
    }
    fn_1_510C(0, 0x32, 0x32);
    arg0->func = fn_1_4218;
}

void fn_1_4218(omObjData *arg0)
{
    f32 var_f31;
    f32 temp_f30;
    f32 var_f29;
    M427DllMapStruct5 *var_r31;
    s16 var_r30;
    M427DllMapStruct4 *var_r29;

    var_r29 = &lbl_1_bss_98;
    var_r31 = &lbl_1_bss_E4[0];
    for (var_r30 = 0; var_r30 < 1; var_r30++) {
        if (--var_r29->unk48[var_r30] < 0.0f) {
            var_r29->unk48[var_r30] = (f32)((((rand8() << 8) | rand8()) % 241) + 0x78);
            var_f31 = ((((rand8() << 8) | rand8()) % 4001) - 0x7D0);
            temp_f30 = -3000.0f;
            var_f29 = ((((rand8() << 8) | rand8()) % 21) + 0xA);
            fn_1_44F4(var_f31, 0.0f, temp_f30, var_f29, 0.0f);
        }
    }

    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (-1.0f != var_r31->unk10) {
            var_r31->unkC += 20.0f;
            var_r31->unk10 -= 0.2f;
            if (var_r31->unk10 < 0.0f) {
                var_r31->unk10 = -1.0f;
            }
        }
    }
}

void fn_1_44F4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4)
{
    M427DllMapStruct5 *var_r31;
    s16 var_r30;

    var_r31 = &lbl_1_bss_E4[0];

    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (-1.0f == var_r31->unk10)
            break;
    }
    if (var_r30 != 0x10) {
        var_r31->unk0 = arg0;
        var_r31->unk4 = arg1;
        var_r31->unk8 = arg2;
        var_r31->unkC = arg4;
        var_r31->unk10 = arg3;
    }
}

f32 lbl_1_data_F4 = 450.0f;

f32 fn_1_4570(Vec *arg0)
{
    f32 temp_f31;
    f32 temp_f30;
    f32 var_f28;
    f32 var_f27;
    f32 var_f23;
    M427DllMapStruct5 *var_r31;
    s16 var_r30;

    var_r31 = &lbl_1_bss_E4[0];
    var_f27 = 0.0f;

    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (-1.0f != var_r31->unk10) {
            temp_f31 = arg0->x - var_r31->unk0;
            temp_f30 = arg0->z - var_r31->unk8;
            if (FABS(temp_f31) > (var_r31->unkC + lbl_1_data_F4)) {
                if (FABS(temp_f30) > (var_r31->unkC + lbl_1_data_F4)) {
                    continue;
                }
            }
            var_f28 = sqrtf((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
            var_f23 = FABS(var_f28 - var_r31->unkC);
            var_f28 = 1.0f - (var_f23 / lbl_1_data_F4);
            if (var_f28 < 0.0f) {
                var_f28 = 0.0f;
            }
            var_f27 += var_r31->unk10 * sind(90.0f * var_f28);
        }
    }
    return var_f27;
}

void fn_1_48EC(ModelData *arg0, Mtx arg1)
{
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    f32 sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;

    sp3C.x = CenterM->x;
    sp3C.y = CenterM->y;
    sp3C.z = CenterM->z;
    sp30.x = CRotM->x;
    sp30.y = CRotM->y;
    sp30.z = CRotM->z;
    temp_f29 = *CZoomM;
    CenterM->x = -CenterM->x;
    CenterM->y = -CenterM->y;
    CenterM->z = CenterM->z;
    CRotM->x = 180.0f + CRotM->x;
    CRotM->y = 180.0f + -CRotM->y;
    CRotM->z = CRotM->z;
    *CZoomM = *CZoomM;
    temp_f31 = CRotM->x;
    temp_f30 = CRotM->y;
    sp8 = CRotM->z;
    sp24.x = (CenterM->x + (*CZoomM * (sind(temp_f30) * cosd(temp_f31))));
    sp24.y = (CenterM->y + (*CZoomM * -sind(temp_f31)));
    sp24.z = (CenterM->z + (*CZoomM * (cosd(temp_f30) * cosd(temp_f31))));
    spC.x = CenterM->x;
    spC.y = CenterM->y;
    spC.z = CenterM->z;
    sp18.x = (sind(temp_f30) * sind(temp_f31));
    sp18.y = cosd(temp_f31);
    sp18.z = (cosd(temp_f30) * sind(temp_f31));
    Hu3DCameraPosSetV(1, &sp24, &sp18, &spC);
    CenterM->x = sp3C.x;
    CenterM->y = sp3C.y;
    CenterM->z = sp3C.z;
    CRotM->x = sp30.x;
    CRotM->y = sp30.y;
    CRotM->z = sp30.z;
    *CZoomM = temp_f29;
}

void fn_1_4D7C(ModelData *arg0, Mtx arg1)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    f32 sp8;
    f32 temp_f30;
    f32 temp_f31;

    temp_f31 = CRotM->x;
    temp_f30 = CRotM->y;
    sp8 = CRotM->z;
    sp24.x = CenterM->x + sind(temp_f30) * cosd(temp_f31) * *CZoomM;
    sp24.y = CenterM->y + *CZoomM * -sind(temp_f31);
    sp24.z = CenterM->z + cosd(temp_f30) * cosd(temp_f31) * *CZoomM;
    sp18.x = CenterM->x;
    sp18.y = CenterM->y;
    sp18.z = CenterM->z;
    spC.x = sind(temp_f30) * sind(temp_f31);
    spC.y = cosd(temp_f31);
    spC.z = cosd(temp_f30) * sind(temp_f31);
    Hu3DCameraPosSetV(1, &sp24, &spC, &sp18);
    if (lbl_1_bss_98.unk30) {
        GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
        GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGB5A3, 0);
        GXCopyTex(lbl_1_bss_98.unk30, 1);
    }
}

void fn_1_50A0(ModelData *arg0, Mtx arg1)
{
    if (lbl_1_bss_98.unk28) {
        GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
        GXSetTexCopyDst(0x280, 0x1E0, GX_TF_RGB5A3, 0);
        GXCopyTex(lbl_1_bss_98.unk28, 0);
    }
}

void fn_1_510C(s32 arg0, s16 arg1, s16 arg2)
{
    M427DllMapStruct4 *var_r31;
    M427DllMapSubstruct5 *var_r30;
    s16 var_r29;
    ModelData *temp_r28;
    s16 var_r27;
    M427DllMapSubstruct5 *var_r26;
    M427DllMapSubstruct5 *var_r23;

    var_r31 = &lbl_1_bss_98;
    var_r29 = Hu3DHookFuncCreate(fn_1_618C);
    Hu3DModelCameraSet(var_r29, 1);
    Hu3DModelLayerSet(var_r29, 5);
    temp_r28 = &Hu3DData[var_r29];
    var_r29 = Hu3DHookFuncCreate(fn_1_48EC);
    Hu3DModelCameraSet(var_r29, 1);
    Hu3DModelLayerSet(var_r29, 0);
    var_r29 = Hu3DHookFuncCreate(fn_1_4D7C);
    Hu3DModelCameraSet(var_r29, 1);
    Hu3DModelLayerSet(var_r29, 2);
    var_r29 = Hu3DHookFuncCreate(fn_1_50A0);
    Hu3DModelCameraSet(var_r29, 1);
    Hu3DModelLayerSet(var_r29, 4);
    var_r31->unk38 = var_r31->unk3C = 0.0f;
    var_r31->unk34 = GXGetTexBufferSize(0x280, 0x1E0, 5, 0, 0);
    var_r31->unk30 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk34, temp_r28->unk_48);
    var_r31->unk2C = GXGetTexBufferSize(0x280, 0x1E0, 5, 0, 0);
    var_r31->unk28 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk2C, temp_r28->unk_48);
    var_r31->unk16 = arg1 + 1;
    var_r31->unk18 = arg2 + 1;
    var_r31->unk14 = var_r31->unk16 * var_r31->unk18;
    var_r31->unk4 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk14 * sizeof(Vec), temp_r28->unk_48);
    var_r31->unk8 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk14 * sizeof(Vec2f), temp_r28->unk_48);
    var_r31->unkC = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk14 * sizeof(Vec), temp_r28->unk_48);
    var_r31->unk10 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk14 * (3 * sizeof(GXColor)), temp_r28->unk_48);
    var_r31->unk1C = HuMemDirectMallocNum(HEAP_DATA, arg2 * (arg1 * sizeof(M427DllMapSubstruct5)), temp_r28->unk_48);
    var_r30 = var_r31->unk1C;
    var_r23 = var_r26 = HuMemDirectMallocNum(HEAP_DATA, 0x20000, temp_r28->unk_48);
    DCFlushRange(var_r26, 0x20000);
    GXBeginDisplayList(var_r23, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, (arg1 * arg2 * 4));

    for (var_r29 = 0; var_r29 < arg2; var_r29++) {
        for (var_r27 = 0; var_r27 < arg1; var_r30++, var_r27++) {
            var_r30->unk0 = var_r27 + var_r29 * var_r31->unk16;
            var_r30->unk2 = (var_r29 * var_r31->unk16) + var_r27 + 1;
            var_r30->unk4 = ((var_r29 + 1) * var_r31->unk16) + var_r27 + 1;
            var_r30->unk6 = var_r27 + ((var_r29 + 1) * var_r31->unk16);
            GXPosition1x16(var_r30->unk0);
            GXPosition1x16(var_r30->unk0);
            GXPosition1x16(var_r30->unk0);
            GXPosition1x16(var_r30->unk2);
            GXPosition1x16(var_r30->unk2);
            GXPosition1x16(var_r30->unk2);
            GXPosition1x16(var_r30->unk4);
            GXPosition1x16(var_r30->unk4);
            GXPosition1x16(var_r30->unk4);
            GXPosition1x16(var_r30->unk6);
            GXPosition1x16(var_r30->unk6);
            GXPosition1x16(var_r30->unk6);
            fn_1_C2C8(&var_r31->unk4[var_r30->unk0], &var_r31->unk4[var_r30->unk2], &var_r31->unk4[var_r30->unk4], &var_r30->unk8);
        }
    }
    var_r31->unk24 = GXEndDisplayList();
    var_r31->unk20 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk24, temp_r28->unk_48);
    memcpy(var_r31->unk20, var_r26, var_r31->unk24);
    DCFlushRange(var_r31->unk20, var_r31->unk24);
    HuMemDirectFree(var_r26);
    fn_1_558C(var_r31);
}

f32 lbl_1_data_F8 = -1.0f;

void fn_1_558C(M427DllMapStruct4 *arg0)
{
    Mtx spAC;
    Mtx sp7C;
    Mtx sp4C;
    Vec2f sp44;
    Vec2f sp3C;
    Vec2f sp34;
    Vec2f sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 var_f26;
    f32 var_f25;
    f32 var_f20;
    M427DllMapSubstruct5 *var_r30;
    Vec *var_r29;
    Vec *var_r28;
    s16 var_r27;
    Vec2f *var_r25;
    s16 var_r24;
    CameraData *var_r23;

    var_r23 = &Hu3DCamera[0];
    if (lbl_1_data_F8 == -1.0f) {
        lbl_1_bss_94 = 720.0f / arg0->unk16;
        lbl_1_data_F8 = 1440.0f / arg0->unk18;
    }
    if (omPauseChk() == 0) {
        arg0->unk40 += 1.0f;
        arg0->unk44 += 1.5f;
    }
    if (arg0->unk40 >= 360.0f) {
        arg0->unk40 -= 360.0f;
    }
    if (arg0->unk44 >= 360.0f) {
        arg0->unk44 -= 360.0f;
    }
    var_r28 = arg0->unk4;
    var_r29 = arg0->unkC;
    sp3C.x = 2000.0f;
    sp3C.y = -2000.0f;
    sp44.x = 1000.0f;
    sp44.y = -2500.0f;
    sp2C.x = sp44.x;
    sp2C.y = (sp44.y - sp44.x) / (arg0->unk18 - 1);
    var_f25 = arg0->unk44;

    for (var_r27 = 0; var_r27 < arg0->unk18; var_r27++) {
        sp34.x = sp3C.x;
        sp34.y = (sp3C.y - sp3C.x) / (arg0->unk16 - 1);
        var_f26 = arg0->unk40;

        for (var_r24 = 0; var_r24 < arg0->unk16; var_r28++, var_r29++, var_r24++) {
            var_r28->x = sp34.x;
            var_r28->z = sp2C.x;
            sp24 = 5.0 * sind(var_f26) + 10.0 * sind(var_f25);
            sp34.x += sp34.y;
            var_f26 += lbl_1_bss_94;
            if (var_f26 >= 360.0f) {
                var_f26 -= 360.0f;
            }
            var_r28->y = sp24 + fn_1_4570(var_r28);
            var_r29->x = var_r29->y = var_r29->z = 0.0f;
        }
        sp2C.x += sp2C.y;
        var_f25 += lbl_1_data_F8;
        if (var_f25 >= 360.0f) {
            var_f25 -= 360.0f;
        }
    }
    var_r30 = arg0->unk1C;
    var_r24 = (arg0->unk16 - 1) * (arg0->unk18 - 1);

    for (var_r27 = 0; var_r27 < var_r24; var_r27++, var_r30++) {
        fn_1_C2C8(&arg0->unk4[var_r30->unk0], &arg0->unk4[var_r30->unk2], &arg0->unk4[var_r30->unk4], &var_r30->unk8);
        arg0->unkC[var_r30->unk0].x += var_r30->unk8.x;
        arg0->unkC[var_r30->unk0].y += var_r30->unk8.y;
        arg0->unkC[var_r30->unk0].z += var_r30->unk8.z;
        arg0->unkC[var_r30->unk2].x += var_r30->unk8.x;
        arg0->unkC[var_r30->unk2].y += var_r30->unk8.y;
        arg0->unkC[var_r30->unk2].z += var_r30->unk8.z;
        arg0->unkC[var_r30->unk4].x += var_r30->unk8.x;
        arg0->unkC[var_r30->unk4].y += var_r30->unk8.y;
        arg0->unkC[var_r30->unk4].z += var_r30->unk8.z;
        arg0->unkC[var_r30->unk6].x += var_r30->unk8.x;
        arg0->unkC[var_r30->unk6].y += var_r30->unk8.y;
        arg0->unkC[var_r30->unk6].z += var_r30->unk8.z;
    }

    var_r29 = arg0->unkC;
    for (var_r27 = 0; var_r27 < arg0->unk14; var_r27++, var_r29++) {
        var_f20 = sqrtf((var_r29->x * var_r29->x) + (var_r29->y * var_r29->y) + (var_r29->z * var_r29->z));
        var_r29->x /= var_f20;
        var_r29->y /= var_f20;
        var_r29->z /= var_f20;
    }
    var_r28 = arg0->unk4;
    var_r25 = arg0->unk8;
    C_MTXLookAt(spAC, &var_r23->pos, &var_r23->up, &var_r23->target);
    GXGetProjectionv(&sp7C[0][0]);
    GXGetViewportv(&sp4C[0][0]);

    for (var_r27 = 0; var_r27 < arg0->unk14; var_r27++, var_r28++, var_r25++) {
        GXProject(var_r28->x, var_r28->y, var_r28->z, spAC, &sp7C[0][0], &sp4C[0][0], &sp28, &sp24, &sp20);
        var_r25->x = 0.0015625f * sp28;
        var_r25->y = 0.0020833f * sp24;
        var_r25->x += 0.05f * arg0->unkC[var_r27].x;
        var_r25->y += 0.05f * arg0->unkC[var_r27].z;
        arg0->unk10[var_r27].r = 0xFF;
        arg0->unk10[var_r27].g = 0xFF;
        arg0->unk10[var_r27].b = 0xFF;
        arg0->unk10[var_r27].a = 0xFF;
    }
    DCFlushRangeNoSync(arg0->unk4, arg0->unk14 * 0xC);
    DCFlushRangeNoSync(arg0->unkC, arg0->unk14 * 0xC);
    DCFlushRangeNoSync(arg0->unk8, arg0->unk14 * 8);
    DCFlushRangeNoSync(arg0->unk10, arg0->unk14 * 4);
    PPCSync();
}

void fn_1_618C(ModelData *arg0, Mtx arg1)
{
    Mtx sp64;
    Mtx sp34;
    GXTexObj sp14;
    GXColor spC;
    M427DllMapStruct4 *var_r31 = &lbl_1_bss_98;
    M427DllMapStruct3Sub *var_r30 = &lbl_1_bss_158.unk334;

    fn_1_558C(var_r31);
    GXLoadPosMtxImm(arg1, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    GXSETARRAY(GX_VA_POS, var_r31->unk4, var_r31->unk14 * sizeof(Vec), sizeof(Vec));
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSETARRAY(GX_VA_TEX0, var_r31->unk8, var_r31->unk14 * sizeof(Vec2f), sizeof(Vec2f));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0);
    GXSETARRAY(GX_VA_CLR0, var_r31->unk10, var_r31->unk14 * 3 * sizeof(GXColor), sizeof(GXColor));
    GXInitTexObj(&sp14, var_r31->unk30, 0x280, 0x1E0, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&sp14, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&sp14, GX_TEXMAP0);
    GXInitTexObj(&sp14, var_r31->unk28, 0x280, 0x1E0, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&sp14, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&sp14, GX_TEXMAP1);
    HuSprTexLoad(var_r30->unk_00, 0, 2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTevStages(3);
    spC.r = 0;
    spC.g = 0x10;
    spC.b = 0x1E;
    spC.a = 0x4C;
    GXSetTevColor(GX_TEVREG2, spC);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_C0, GX_CC_A2, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C2);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, 1, 0, GX_ITM_0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    MTXScale(sp64, -0.1f, 0.0f, 1.0f);
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3])(sp64), 0);
    GXSetNumTexGens(2);
    if (omPauseChk() == 0) {
        var_r31->unk38 += 0.001f;
        var_r31->unk3C += 0.0005f;
    }
    MTXRotRad(sp64, 0x58, 1.5707964f);
    MTXScale(sp34, 0.001f, 0.001f, 0.001f);
    MTXConcat(sp64, sp34, sp64);
    mtxTransCat(sp64, var_r31->unk38, var_r31->unk3C, 0.0f);
    GXLoadTexMtxImm(sp64, 0x1E, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_POS, 0x1E, GX_FALSE, 0x7D);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXCallDisplayList(var_r31->unk20, var_r31->unk24);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
#ifdef TARGET_PC
    GXDestroyTexObj(&sp14);
#endif
}

s32 lbl_1_data_FC[0xC] = {
    0x3A0000,
    0x3A0001,
    0x3A0002,
    0x3A0003,
    0x3A0004,
    0x3A0005,
    0x3A0006,
    0x3A0007,
    0x3A0008,
    0x3A0009,
    0x3A000A,
    0x3A000B,
};
s32 lbl_1_data_12C[2] = { 0x3A000C, 0x3A000D };
s32 lbl_1_data_134[4] = { 0x3A000E, 0x3A000F, 0x3F800000, 0x01000000 };

void fn_1_6760(omObjData *object)
{
    s16 sp14[2][0x20];
    s16 sp10[2];
    s16 spC[2];
    s16 sp8[2];
    M427DllMapSubstruct3 *var_r31;
    s16 var_r30;
    M427DllMapUNKB8 *var_r29;
    s16 var_r28;
    M427DllMapUNK17E *var_r27;
    s16 var_r26;
    M427DllMapSubstruct3Sub *var_r25;
    M427DllMapStruct3 *var_r24;

    var_r24 = &lbl_1_bss_158;
    Hu3DFogSet(3500.0f, 20000.0f, 0, 0, 0);
    for (var_r28 = 0, var_r31 = &var_r24->unk4[0]; var_r28 < 2; var_r28++, var_r31++) {
        var_r31->unk0 = var_r28;
        sp10[var_r28] = 0;
        for (var_r30 = 0; var_r30 < 3; var_r30++) {
            var_r31->unk178[var_r30] = 0;
        }
        for (var_r30 = 0; var_r30 < 0xB; var_r30++) {
            var_r31->unk2[var_r30] = Hu3DModelCreateFile(lbl_1_data_FC[var_r30]);
            var_r31->unk44[var_r30] = -1;
            if (var_r30 < 0xA) {
                Hu3DModelLayerSet(var_r31->unk2[var_r30], 2);
            }
            else {
                Hu3DModelLayerSet(var_r31->unk2[var_r30], 5);
            }
            Hu3DModelAmbSet(var_r31->unk2[var_r30], 0.1f, 0.1f, 0.1f);
            if (var_r28 == 0) {
                Hu3DModelCameraSet(var_r31->unk2[var_r30], 1);
            }
            else {
                Hu3DModelCameraSet(var_r31->unk2[var_r30], 2);
            }
            sp14[var_r28][sp10[var_r28]++] = var_r31->unk2[var_r30];
        }
        var_r30 = Hu3DHookFuncCreate(fn_1_C154);
        var_r31->unk1E = var_r30;
        Hu3DModelLayerSet(var_r30, 4);
        if (var_r28 == 0) {
            Hu3DModelCameraSet(var_r30, 1);
        }
        else {
            Hu3DModelCameraSet(var_r30, 2);
        }
        var_r30 = Hu3DHookFuncCreate(fn_1_C200);
        var_r31->unk20 = var_r30;
        Hu3DModelLayerSet(var_r30, 6);
        if (var_r28 == 0) {
            Hu3DModelCameraSet(var_r30, 1);
        }
        else {
            Hu3DModelCameraSet(var_r30, 2);
        }
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            var_r29 = var_r31->unkB8[var_r30];
            for (var_r26 = 0; var_r26 < 2; var_r26++, var_r29++) {
                if ((var_r28 == 0) && (var_r26 == 0)) {
                    var_r29->unk2 = spC[var_r30] = Hu3DModelCreateFile(lbl_1_data_134[var_r30]);
                }
                else {
                    var_r29->unk2 = Hu3DModelLink(spC[var_r30]);
                }
                Hu3DModelAttrSet(var_r29->unk2, HU3D_ATTR_DISPOFF);
                Hu3DModelLayerSet(var_r29->unk2, 2);
                Hu3DModelAmbSet(var_r29->unk2, 0.0f, 0.0f, 0.0f);
                if (var_r28 == 0) {
                    Hu3DModelCameraSet(var_r29->unk2, 1);
                }
                else {
                    Hu3DModelCameraSet(var_r29->unk2, 2);
                }
                sp14[var_r28][sp10[var_r28]++] = var_r29->unk2;
                var_r29->unk6 = fn_1_95E8(0x3A0018, var_r28, 0, 0.0f, -400.0f, 700.0f, 800.0f, -5.0f);
                fn_1_9958(var_r29->unk6, 1);
                fn_1_99E4(var_r29->unk6, 0xFF, 0xFF, 0xFF, 0);
                var_r29->unk4 = 2 * var_r30 + 4 + var_r26;
                fn_1_C528(var_r29->unk2, var_r29->unk4, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0xFF, 0xA0, 0x60);
                Hu3DLLightStaticSet(var_r29->unk2, var_r29->unk4, 1);
                Hu3DLLightPointSet(var_r29->unk2, var_r29->unk4, 1.0f, 0.6f, 3);
            }
        }
        for (var_r30 = 0; var_r30 < 2; var_r30++) {
            var_r27 = var_r31->unk17E[var_r30];
            for (var_r26 = 0; var_r26 < 2; var_r26++, var_r27++) {
                if ((var_r28 == 0) && (var_r26 == 0)) {
                    var_r27->unk2 = sp8[var_r30] = Hu3DModelCreateFile(lbl_1_data_12C[var_r30]);
                }
                else {
                    var_r27->unk2 = Hu3DModelLink(sp8[var_r30]);
                }
                Hu3DModelAttrSet(var_r27->unk2, HU3D_ATTR_DISPOFF);
                Hu3DModelLayerSet(var_r27->unk2, 2);
                Hu3DModelAmbSet(var_r27->unk2, 0.0f, 0.0f, 0.0f);
                if (var_r28 == 0) {
                    Hu3DModelCameraSet(var_r27->unk2, 1);
                }
                else {
                    Hu3DModelCameraSet(var_r27->unk2, 2);
                }
                sp14[var_r28][sp10[var_r28]++] = var_r27->unk2;
            }
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            var_r31->unk34[var_r30] = fn_1_C41C(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF);
            var_r31->unk24[var_r30] = -1.0f;
        }
    }
    for (var_r28 = 0, var_r31 = var_r24->unk4; var_r28 < 2; var_r28++, var_r31++) {
        var_r31->unk5C = Hu3DLLightCreate(var_r31->unk2[0], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0xFA, 0xF0, 0xD2);
        Hu3DLLightSpotSet(var_r31->unk2[0], var_r31->unk5C, 37.5f, 4);
        Hu3DLLightStaticSet(var_r31->unk2[0], var_r31->unk5C, 1);
        var_r31->unk78.x = 0.0f;
        var_r31->unk78.y = 0.0f;
        var_r31->unk78.z = 0.0f;
        var_r31->unk84.x = 0.0f;
        var_r31->unk84.y = 0.0f;
        var_r31->unk84.z = 0.0f;
        var_r31->unk90 = 0.0f;
    }
    fn_1_93EC(0x3A0016, 0x3A0014, 2000.0f, 6000.0f, 4.0f, 9.0f);
    for (var_r28 = 0, var_r31 = var_r24->unk4; var_r28 < 2; var_r28++, var_r31++) {
        var_r31->unkB0[0] = fn_1_95E8(0x3A0015, var_r28, 0.0f, 0.0f, -900.0f, 500.0f, 700.0f, -10.0f);
        var_r25 = &var_r31->unk94;
        var_r25->unk0 = var_r28;
        var_r25->unk8 = GXGetTexBufferSize(0x140, 0x1E0, 5, 0, 0);
        var_r25->unk4 = HuMemDirectMalloc(HEAP_DATA, var_r25->unk8);
        var_r30 = Hu3DHookFuncCreate(fn_1_A148);
        var_r31->unk1C = var_r30;
        Hu3DModelCameraSet(var_r30, var_r28 ? 2 : 1);
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DData[var_r30].unk_120 = var_r25;
        var_r31->unk1A = fn_1_A1F4(0x3A0013, 0xA, 0x1E, var_r28, 6000.0f, lbl_1_bss_554, lbl_1_bss_558);
        fn_1_C528(var_r31->unk1A, 1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0xC8, 0xF0, 0xA0);
        Hu3DLLightStaticSet(var_r31->unk1A, 1, 1);
        Hu3DLLightPointSet(var_r31->unk1A, 1, 125.0f, 0.5f, 3);
        fn_1_C528(var_r31->unk1A, 2, 0.0f, -500.0f, -23500.0f, 0.0f, 0.0f, 0.0f, 0xFA, 0xF0, 0xD2);
        Hu3DLLightStaticSet(var_r31->unk1A, 2, 1);
        Hu3DLLightPointSet(var_r31->unk1A, 2, 800.0f, 0.5f, 3);
        sp14[var_r28][sp10[var_r28]++] = var_r31->unk1A;
        fn_1_9318(sp14[var_r28], sp10[var_r28]);
    }
    object->func = fn_1_72E4;
}

void fn_1_72E4(omObjData *object)
{
    float var_f31;
    M427DllMapStruct2 *var_r31;
    s16 var_r30;

    if (fn_1_1788() == 7) {
        object->func = fn_1_3E58;
    }
    fn_1_73BC();
    fn_1_7C34();
    fn_1_7F38();
    fn_1_8F90(object);
    fn_1_9240();
    for (var_r31 = lbl_1_bss_F8, var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (var_r31->unk0 != -1) {
            var_f31 = Hu3DMotionMaxTimeGet(var_r31->unk2);
            if (Hu3DMotionTimeGet(var_r31->unk2) >= var_f31) {
                var_r31->unk0 = -1;
                Hu3DModelAttrSet(var_r31->unk2, HU3D_ATTR_DISPOFF);
            }
        }
    }
}

void fn_1_73BC(void)
{
    float var_f31;
    M427DllMapSubstruct3 *var_r31;
    M427DllMapSubstruct6 *var_r30;
    s16 var_r29;
    ModelData *var_r28;
    s16 var_r27;

    for (var_r27 = 0, var_r31 = lbl_1_bss_158.unk4; var_r27 < 2; var_r27++, var_r31++) {
        for (var_r29 = 0; var_r29 < 0xA; var_r29++) {
            var_r28 = &Hu3DData[var_r31->unk2[var_r29]];
            var_r30 = fn_1_DC0C(lbl_1_bss_E8[var_r31->unk0], var_r31->unk3C[var_r31->unk44[var_r29]]);
            var_f31 = -2000.0f * var_r29;
            if (((var_r31->unk84.z - 25000.0f) < var_f31) && ((3000.0f + var_r31->unk84.z) > var_f31)) {
                if (var_r31->unk44[var_r29] == -1) {
                    fn_1_794C(var_r31, var_r29);
                    var_r28->attr &= 0xFFFFFFFE;
                }
                else {
                    if (var_r30) {
                        var_r30->unk_24 += 5.0f;
                        if (var_r30->unk_24 >= 360.0f) {
                            var_r30->unk_24 -= 360.0f;
                        }
                        var_r30->unk_48.x = var_r30->unk_48.y = var_r30->unk_48.z = 1.0 + (0.05000000074505806 * sind(var_r30->unk_24));
                    }
                    var_r31->unk24[var_r31->unk44[var_r29]] += 5.0f;
                    if (var_r31->unk24[var_r31->unk44[var_r29]] >= 360.0f) {
                        var_r31->unk24[var_r31->unk44[var_r29]] -= 360.0f;
                    }
                    var_f31 = 50.0 * sind(var_r31->unk24[var_r31->unk44[var_r29]]);
                    var_f31 = var_f31;
                    Hu3DLLightPointSet(var_r31->unk2[var_r29], 1, 400.0f + var_f31, 0.5f, 3);
                    if (var_r29 == 0) {
                        var_r30 = fn_1_DC0C(lbl_1_bss_E8[var_r31->unk0], var_r31->unk5A);
                        if (var_r30->unk_24 >= 360.0f) {
                            var_r30->unk_24 -= 360.0f;
                        }
                        var_r30->unk_48.x = var_r30->unk_48.y = var_r30->unk_48.z = 1.0 + (0.05000000074505806 * sind(var_r30->unk_24));
                        var_r31->unk24[1] += 5.0f;
                        if (var_r31->unk24[1] >= 360.0f) {
                            var_r31->unk24[1] -= 360.0f;
                        }
                        var_f31 = 50.0 * sind(var_r31->unk24[1]);
                        var_f31 = var_f31;
                        Hu3DLLightPointSet(var_r31->unk2[var_r29], 2, 400.0f + var_f31, 0.5f, 3);
                    }
                }
            }
            else {
                if (var_r31->unk44[var_r29] != -1) {
                    if (var_r30) {
                        var_r30->unk_62 = 0;
                    }
                    var_r28->unk_38[1] = -1;
                    var_r31->unk24[var_r31->unk44[var_r29]] = -1.0f;
                    var_r31->unk44[var_r29] = -1;
                    if (var_r29 == 0) {
                        var_r30 = fn_1_DC0C(lbl_1_bss_E8[var_r31->unk0], var_r31->unk5A);
                        var_r30->unk_62 = 0;
                        var_r28->unk_38[2] = -1;
                        var_r31->unk24[1] = -1.0f;
                    }
                }
                var_r28->attr |= 1;
            }
        }
    }
}

Vec lbl_1_data_144[0xC] = {
    { -670.0f, 400.0f, 1750.0f },
    { 930.0f, 400.0f, -1000.0f },
    { -930.0f, 400.0f, -3000.0f },
    { 230.0f, 400.0f, -5000.0f },
    { -1630.0f, 300.0f, -7000.0f },
    { 530.0f, 100.0f, -9000.0f },
    { -530.0f, 100.0f, -11000.0f },
    { 1630.0f, 100.0f, -13000.0f },
    { -230.0f, 0.0f, -15000.0f },
    { 930.0f, -200.0f, -17000.0f },
    { -930.0f, -200.0f, -19000.0f },
    { 930.0f, -200.0f, -21000.0f },
};

void fn_1_794C(M427DllMapSubstruct3 *arg0, s16 arg1)
{
    Vec sp14;
    s16 var_r30;
    ModelData *var_r28;

    var_r28 = &Hu3DData[arg0->unk2[arg1]];
    {
        Vec sp8 = { 0.0f, 0.0f, 0.0f };
        if (arg1 != 0xA) {
            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                if (arg0->unk24[var_r30] == -1.0f) {
                    break;
                }
            }
            if (var_r30 != 4) {
                var_r28->unk_38[1] = arg0->unk34[var_r30];
                arg0->unk24[var_r30] = 0.0f;
                arg0->unk44[arg1] = var_r30;
                if (var_r28->unk_38[1] != -1) {
                    sp14.x = lbl_1_data_144[arg1 + 1].x;
                    sp14.y = lbl_1_data_144[arg1 + 1].y;
                    sp14.z = lbl_1_data_144[arg1 + 1].z;
                    Hu3DLLightPointSet(arg0->unk2[arg1], 1, 400.0f, 0.5f, 3);
                    Hu3DLLightPosSetV(arg0->unk2[arg1], 1, &sp14, &sp8);
                }
                arg0->unk3C[var_r30] = fn_1_D430(sp14.x, sp14.y, sp14.z, lbl_1_bss_E8[arg0->unk0]);
                if (arg1 == 0) {
                    var_r30 = 1;
                    var_r28->unk_38[2] = arg0->unk34[var_r30];
                    arg0->unk24[var_r30] = 0.0f;
                    sp14.x = lbl_1_data_144[0].x;
                    sp14.y = lbl_1_data_144[0].y;
                    sp14.z = lbl_1_data_144[0].z;
                    Hu3DLLightPointSet(arg0->unk2[0], 2, 400.0f, 0.5f, 3);
                    Hu3DLLightPosSetV(arg0->unk2[0], 2, &sp14, &sp8);
                    arg0->unk5A = fn_1_D430(sp14.x, sp14.y, sp14.z, lbl_1_bss_E8[arg0->unk0]);
                }
            }
        }
    }
}

float lbl_1_data_1D4[2] = { 50.0f, 80.0f };

void fn_1_7C34(void)
{
    Vec sp14;
    M427DllMapSubstruct3 *var_r31;
    ModelData *var_r30;
    s16 var_r29;
    s16 var_r28;
    M427DllMapUNK17E *var_r27;
    M427DllMapSubstruct *var_r26;
    s16 var_r25;

    for (var_r26 = lbl_1_bss_158.unk3A0, var_r29 = 0; var_r29 < 5; var_r29++, var_r26++) {
        for (var_r28 = 0, var_r31 = lbl_1_bss_158.unk4; var_r28 < 2; var_r28++, var_r31++) {
            if ((var_r31->unk18E[var_r29] == 0) && ((var_r31->unk84.z - 7000.0f) < var_r26->unk4.z)
                && ((1000.0f + var_r31->unk84.z) > var_r26->unk4.z)) {
                fn_1_7E60(var_r29, var_r31);
            }
        }
    }
    for (var_r29 = 0, var_r31 = lbl_1_bss_158.unk4; var_r29 < 2; var_r29++, var_r31++) {
        for (var_r28 = 0; var_r28 < 2; var_r28++) {
            var_r27 = var_r31->unk17E[var_r28];
            for (var_r25 = 0; var_r25 < 2; var_r25++, var_r27++) {
                var_r30 = &Hu3DData[var_r27->unk2];
                if ((var_r30->attr & 1) == 0) {
                    if (((var_r31->unk84.z - 7000.0f) > var_r30->pos.z) || ((1000.0f + var_r31->unk84.z) < var_r30->pos.z)) {
                        var_r30->attr |= 1;
                        var_r31->unk18E[var_r27->unk0] = 0;
                    }
                    else {
                        sp14.x = var_r30->pos.x;
                        sp14.z = var_r30->pos.z;
                        fn_1_15FD0(sp14, lbl_1_data_1D4[var_r28], 0, 1, var_r31->unk0);
                    }
                }
            }
        }
    }
}

void fn_1_7E60(s16 arg0, M427DllMapSubstruct3 *arg1)
{
    M427DllMapUNK17E *var_r31;
    M427DllMapSubstruct *var_r30;
    s16 var_r29;
    ModelData *var_r28;

    var_r30 = &lbl_1_bss_158.unk3A0[arg0];
    var_r31 = arg1->unk17E[var_r30->unk0];
    for (var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        var_r28 = &Hu3DData[var_r31->unk2];
        if ((var_r28->attr & 1) != 0) {
            Hu3DModelAttrReset(var_r31->unk2, HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(var_r31->unk2, var_r30->unk4.x, var_r30->unk4.y, var_r30->unk4.z);
            var_r31->unk0 = arg0;
            arg1->unk18E[arg0] = 1;
            return;
        }
    }
}

void fn_1_7F38(void)
{
    Vec sp14;
    float var_f31;
    M427DllMapUNKB8 *var_r31;
    M427DllMapSubstruct3 *var_r30;
    ModelData *var_r29;
    s16 var_r28;
    s16 var_r27;
    M427DllMapSubstruct2 *var_r26;
    s16 var_r25;
    s32 var_r24;
    s32 var_r23;

    for (var_r26 = lbl_1_bss_158.unk34C, var_r27 = 0; var_r27 < 3; var_r27++, var_r26++) {
        for (var_r28 = 0, var_r30 = lbl_1_bss_158.unk4; var_r28 < 2; var_r28++, var_r30++) {
            if ((var_r30->unk178[var_r27] == 0) && ((var_r30->unk84.z - 7000.0f) < var_r26->unk4.z)
                && ((1000.0f + var_r30->unk84.z) > var_r26->unk4.z)) {
                fn_1_85D4(var_r27, var_r30);
            }
        }
    }
    for (var_r27 = 0, var_r30 = lbl_1_bss_158.unk4; var_r27 < 2; var_r27++, var_r30++) {
        for (var_r28 = 0; var_r28 < 2; var_r28++) {
            var_r31 = var_r30->unkB8[var_r28];
            for (var_r25 = 0; var_r25 < 2; var_r25++, var_r31++) {
                var_r29 = &Hu3DData[var_r31->unk2];
                if ((var_r29->attr & 1) == 0) {
                    if (((var_r30->unk84.z - 7000.0f) > var_r29->pos.z) || ((1000.0f + var_r30->unk84.z) < var_r29->pos.z)) {
                        if (var_r31->unk8 == 0) {
                            fn_1_8E1C(1, var_r30, var_r31);
                            fn_1_9958(var_r31->unk6, 1);
                            var_r29->attr |= 1;
                            var_r31->unk8 = 0x63;
                            var_r30->unk178[var_r31->unk0] = 0;
                        }
                        else if (var_r31->unk8 != 2) {
                            var_r31->unkA = 0;
                            var_r31->unk8 = 2;
                        }
                    }
                    switch (var_r31->unk8) {
                        case 0:
                            if (++var_r31->unkA > var_r31->unk18) {
                                var_r31->unkA = 0;
                                var_r31->unkC = 0.0f;
                                var_r31->unk20 = ((rand8() << 8) | rand8()) % 361;
                                var_r31->unk24 = ((rand8() << 8) | rand8()) % 361;
                                var_r31->unk28 = 1.0f;
                                var_r31->unk2C = 0.0f;
                                var_r31->unk8++;
                            }
                            break;
                        case 1:
                            if (++var_r31->unkA > var_r31->unk1E) {
                                var_r31->unkA = 0;
                                var_r31->unk8++;
                                if (fn_1_1788() <= 4) {
                                    if (var_r27 == 0) {
                                        var_r24 = HuAudFXPlay(0x65A);
                                    }
                                    else {
                                        var_r24 = HuAudFXPlay(0x65B);
                                    }
                                    var_r23 = var_r27 * 4 + var_r28 * 2 + var_r25;
                                    lbl_1_bss_0[var_r23].unk0 = var_r24;
                                    lbl_1_bss_0[var_r23].unk4 = 0x78;
                                }
                            }
                            var_r31->unk_14 = 0.1f;
                            fn_1_8768(var_r30, var_r31, var_r28, 0.2f, var_r31->unk_14);
                            break;
                        case 2:
                            if (++var_r31->unkA > var_r31->unk1A) {
                                var_r31->unkA = 0;
                                var_r31->unk8++;
                            }
                            if (var_r31->unk_14 < 1.0f) {
                                var_r31->unk_14 += 0.05f;
                            }
                            if (var_r31->unk_14 > 1.0f) {
                                var_r31->unk_14 = 1.0f;
                            }
                            var_r31->unk_10 += 40.0f;
                            var_r31->unkC += 0.05f;
                            fn_1_8768(var_r30, var_r31, var_r28, 1.0f, var_r31->unk_14);
                            break;
                        case 3:
                            var_r31->unkA++;
                            var_f31 = 1.0f - ((float)var_r31->unkA / var_r31->unk1C);
                            if (var_r31->unkA > var_r31->unk1C) {
                                var_r31->unkA = 0;
                                var_f31 = 0.0f;
                                var_r31->unk8 = 0;
                            }
                            var_r31->unk_10 = 400.0 * sind((90.0f * var_f31));
                            var_r31->unkC = 1.2f * var_f31;
                            var_r31->unk_14 = var_f31;
                            fn_1_8768(var_r30, var_r31, var_r28, var_f31, var_r31->unk_14);
                            break;
                    }
                    sp14.x = var_r29->pos.x;
                    sp14.z = var_r29->pos.z;
                    fn_1_15FD0(sp14, 50.0f, 0, 1, var_r30->unk0);
                }
            }
        }
    }
}

void fn_1_85D4(s16 arg0, M427DllMapSubstruct3 *arg1)
{
    float var_f31;
    M427DllMapUNKB8 *var_r31;
    M427DllMapSubstruct2 *var_r30;
    s16 var_r29;
    ModelData *var_r27;

    var_r30 = &lbl_1_bss_158.unk34C[arg0];
    var_r31 = arg1->unkB8[var_r30->unk0];
    for (var_r29 = 0; var_r29 < 2; var_r29++, var_r31++) {
        var_r27 = &Hu3DData[var_r31->unk2];
        if ((var_r27->attr & 1) != 0) {
            Hu3DModelAttrReset(var_r31->unk2, HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(var_r31->unk2, var_r30->unk4.x, var_r30->unk4.y, var_r30->unk4.z);
            var_r31->unk8 = 0;
            var_r31->unkA = 0;
            var_r31->unk18 = var_r30->unk14[0];
            var_r31->unk1A = var_r30->unk14[1];
            var_r31->unk1C = var_r30->unk14[2];
            var_r31->unk1E = var_r30->unk14[3];
            var_r31->unk0 = arg0;
            arg1->unk178[arg0] = 1;
            fn_1_9A2C(var_r31->unk6, var_r30->unk4.x, var_r30->unk4.y, var_r30->unk4.z);
            if (var_r30->unk0 == 0) {
                var_f31 = 90.0f;
            }
            else {
                var_f31 = 270.0f;
            }
            fn_1_9B14(var_r31->unk6, 0.0f, var_f31, 0.0f);
            fn_1_999C(var_r31->unk6, 1);
            fn_1_8E1C(0, arg1, var_r31);
            return;
        }
    }
}

float lbl_1_data_1DC[2] = { -1.0f, 1.0f };
float lbl_1_data_1E4[2] = { 270.0f, 90.0f };

void fn_1_8768(M427DllMapSubstruct3 *var_r28, M427DllMapUNKB8 *var_r31, s16 var_r27, float var_f28, float var_f29)
{
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    float var_f31;
    float var_f30;
    ModelData *var_r30;
    M427DllMapStruct *var_r29;

    var_r30 = &Hu3DData[var_r31->unk2];
    var_f31 = var_f28 * var_r31->unk28;
    sp50.x = var_r30->pos.x + (60.0f * lbl_1_data_1DC[var_r27]);
    sp50.y = 80.0f + var_r30->pos.y;
    sp50.z = var_r30->pos.z;
    if (var_r31->unk8 == 1) {
        fn_1_C76C(0, sp50.x, sp50.y, sp50.z, 1, lbl_1_data_1E4[var_r27], var_f31, lbl_1_bss_EC[var_r28->unk0]);
        return;
    }
    fn_1_C76C(1, sp50.x, sp50.y, sp50.z, 1, lbl_1_data_1E4[var_r27], var_f31, lbl_1_bss_EC[var_r28->unk0]);
    if (var_r31->unk_10 > (400.0f * var_r31->unk28)) {
        var_r31->unk_10 = 400.0f * var_r31->unk28;
    }
    else if (var_r31->unk_10 < 1.0f) {
        var_r31->unk_10 = 1.0f;
    }
    var_r31->unk2C += 30.0f;
    if (var_r31->unk2C >= 360.0f) {
        var_r31->unk2C -= 360.0f;
    }
    sp50.x = var_r30->pos.x + (240.0f * lbl_1_data_1DC[var_r27]);
    sp50.y = 100.0f + var_r30->pos.y;
    sp50.z = var_r30->pos.z;
    sp44.x = sp44.y = sp44.z = 0.0f;
    var_f30 = var_r31->unk_10 + (var_f28 * (50.0 * sind(var_r31->unk2C)));
    Hu3DLLightPointSet(var_r31->unk2, var_r31->unk4, var_f30, 0.5f, 3);
    Hu3DLLightPosSetV(var_r31->unk2, var_r31->unk4, &sp50, &sp44);
    var_r29 = &lbl_1_bss_F0[var_r31->unk6];
    var_r29->unk90 -= 0.0005f;
    var_r29->unk8C += 0.005f;
    var_r29->unk94 += 0.001f;
    if (var_r31->unkC > 1.0f) {
        var_r31->unkC = 1.0f;
    }
    else if (var_r31->unkC < 0.0f) {
        var_r31->unkC = 0.0f;
    }
    fn_1_99E4(var_r31->unk6, 0xFF, 0xA0, 0x60, 255.0f * var_r31->unkC);
    var_r31->unk20 += 2.0f;
    var_r31->unk24 += (((rand8() << 8) | rand8()) % 5) + 4;
    if (var_r31->unk20 >= 360.0f) {
        var_r31->unk20 -= 360.0f;
    }
    if (var_r31->unk24 >= 360.0f) {
        var_r31->unk24 -= 360.0f;
    }
    sp38.x = 1.0 + (0.009999999776482582 * sind(var_r31->unk24));
    sp38.z = var_r31->unk28 + (0.009999999776482582 * sind(var_r31->unk20));
    fn_1_9AA0(var_r31->unk6, sp38.x, 1.0f, sp38.z);
    if (var_r27 == 0) {
        sp2C.x = var_r30->pos.x - (700.0f * var_f31 * var_f29);
        sp20.x = var_r30->pos.x - 50.0f;
    }
    else {
        sp2C.x = 50.0f + var_r30->pos.x;
        sp20.x = var_r30->pos.x + (700.0f * var_f31 * var_f29);
    }
    sp2C.z = var_r30->pos.z - 30.0f;
    sp20.z = 30.0f + var_r30->pos.z;
    fn_1_15F10(sp2C, sp20, 1, 1, var_r28->unk0);
}

void fn_1_8E1C(u8 arg0, M427DllMapSubstruct3 *arg1, M427DllMapUNKB8 *arg2)
{
    s32 spC[8];
    s16 var_r30;
    ModelData *var_r29;
    M427DllMapSubstruct2 *var_r27;
    s16 var_r26;
    ModelData *var_r25;
    s16 var_r24;

    var_r27 = &lbl_1_bss_158.unk34C[arg2->unk0];
    var_r25 = &Hu3DData[arg2->unk2];
    if (arg0 == 0) {
        var_r26 = var_r25->unk_38[arg2->unk4];
    }
    else {
        var_r26 = -1;
    }
    var_r24 = fn_1_10FE8(arg1->unk0, spC);
    for (var_r30 = 0; var_r30 < var_r24; var_r30++) {
        var_r29 = &Hu3DData[spC[var_r30]];
        var_r29->unk_38[arg2->unk4] = var_r26;
    }
    var_r29 = &Hu3DData[arg1->unk1A];
    var_r29->unk_38[arg2->unk4] = var_r26;
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        if (var_r27->unk10[var_r30] != -1) {
            var_r29 = &Hu3DData[arg1->unk2[var_r27->unk10[var_r30]]];
            var_r29->unk_38[arg2->unk4] = var_r26;
        }
    }
}

void fn_1_8F90(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    M427DllMapSubstruct3 *var_r31;
    s16 var_r30;
    M427DllMapStruct3 *var_r29;

    var_r29 = &lbl_1_bss_158;
    for (var_r30 = 0, var_r31 = var_r29->unk4; var_r30 < 2; var_r30++, var_r31++) {
        var_f31 = sind(var_r31->unk90);
        var_f30 = cosd(var_r31->unk90);
        var_r31->unk_60.x = var_r31->unk84.x - (25.0f * var_f31);
        var_r31->unk_60.y = 100.0f + var_r31->unk84.y;
        var_r31->unk_60.z = var_r31->unk84.z - (25.0f * var_f30);
        var_r31->unk_6C.x = var_r31->unk_60.x - (50.0f * var_f31);
        var_r31->unk_6C.y = var_r31->unk_60.y;
        var_r31->unk_6C.z = var_r31->unk_60.z - (50.0f * var_f30);
        Hu3DLLightPosSet(var_r31->unk2[0], var_r31->unk5C, var_r31->unk_60.x, var_r31->unk_60.y, var_r31->unk_60.z, 0.0f, 0.0f, 0.0f);
        Hu3DLLightPosAimSetV(var_r31->unk2[0], var_r31->unk5C, &var_r31->unk_60, &var_r31->unk_6C);
        fn_1_9A2C(var_r31->unkB0[0], var_r31->unk84.x, var_r31->unk84.y, var_r31->unk84.z);
        fn_1_9B14(var_r31->unkB0[0], 0.0f, var_r31->unk90, 0.0f);
        sp14.x = var_r31->unk84.x;
        sp14.y = 100.0f + var_r31->unk84.y;
        sp14.z = 50.0f + var_r31->unk84.z;
        sp8.x = sp8.y = sp8.z = 0.0f;
        Hu3DLLightPosSetV(var_r31->unk1A, 1, &sp14, &sp8);
    }
}

void fn_1_91E0(s16 arg0, float arg8, float arg9, float argA, float argB)
{
    M427DllMapSubstruct3 *var_r31;

    var_r31 = &lbl_1_bss_158.unk4[arg0];
    var_r31->unk84.x = arg8;
    var_r31->unk84.y = arg9;
    var_r31->unk84.z = argA;
    var_r31->unk90 = argB;
    if (var_r31->unkAC) {
        var_r31->unkAC->unk_0C = 1500.0f + argA;
    }
}

void fn_1_9240(void)
{
    M427DllMapStruct *var_r31;
    M427DllMapSubstruct3 *var_r30;
    s16 var_r29;
    s16 var_r28;

    for (var_r30 = lbl_1_bss_158.unk4, var_r28 = 0; var_r28 < 2; var_r28++, var_r30++) {
        for (var_r29 = 0; var_r29 < 1; var_r29++) {
            var_r31 = &lbl_1_bss_F0[var_r30->unkB0[var_r29]];
            var_r31->unk90 -= 0.0005f;
            var_r31->unk8C += 0.0005f;
            var_r31->unk94 += 0.0005f;
        }
    }
}

void fn_1_9318(s16 *arg0, s16 arg1)
{
    s16 var_r31;
    ModelData *var_r30;
    ModelData *var_r29;
    s16 var_r28;

    var_r30 = &Hu3DData[*arg0];
    for (var_r28 = 1; var_r28 < arg1; var_r28++) {
        var_r29 = &Hu3DData[arg0[var_r28]];
        for (var_r31 = 0; var_r31 < 8; var_r31++) {
            if (var_r30->unk_38[var_r31] != -1) {
                var_r29->unk_38[var_r31] = var_r30->unk_38[var_r31];
            }
        }
        var_r29->attr |= 0x1000;
    }
}

void fn_1_93EC(s32 sp8, s32 spC, float var_f30, float var_f31, float sp10, float sp14)
{
    M427DllMapStruct3Sub *var_r31;

    var_r31 = &lbl_1_bss_158.unk334;
    var_r31->unk_00 = HuSprAnimRead(HuDataReadNum(sp8, MEMORY_DEFAULT_NUM));
    var_r31->unk_04 = HuSprAnimRead(HuDataReadNum(spC, MEMORY_DEFAULT_NUM));
    var_r31->unk_08 = 0.5f * var_f30;
    var_r31->unk_0C = 0.5f * var_f31;
    var_r31->unk_10 = sp10 / var_f30;
    var_r31->unk_14 = sp14 / var_f31;
}

void fn_1_94BC(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3, float arg8, Vec2f *arg4, s16 arg5)
{
    Mtx sp58;
    Mtx sp28;
    Vec sp1C;
    Vec sp10;
    M427DllMapStruct3Sub *var_r31;
    s16 var_r28;

    var_r31 = &lbl_1_bss_158.unk334;
    for (var_r28 = 0; var_r28 < arg5; var_r28++, arg2++, arg4++) {
        MTXScale(sp58, arg3->x, arg3->y, arg3->z);
        MTXRotRad(sp28, 0x59, MTXDegToRad(arg8));
        MTXConcat(sp58, sp28, sp58);
        MTXMultVec(sp58, arg2, &sp1C);
        sp10.x = var_r31->unk_08 + ((sp1C.x + arg1->x) - arg0->x);
        sp10.z = var_r31->unk_0C + ((sp1C.z + arg1->z) - arg0->z);
        arg4->x = sp10.x * var_r31->unk_10;
        arg4->y = sp10.z * var_r31->unk_14;
    }
}

s16 fn_1_95E8(s32 arg0, s16 arg1, s16 arg2, float arg8, float arg9, float argA, float argB, float argC)
{
    M427DllMapStruct *var_r31;
    s16 var_r30;
    s16 var_r29;
    void *var_r28;
    void *var_r26;

    for (var_r31 = lbl_1_bss_F0, var_r29 = 0; var_r29 < 0x10; var_r29++, var_r31++) {
        if (var_r31->unk2 == -1) {
            break;
        }
    }
    if (var_r29 == 0x10) {
        return -1;
    }
    var_r31->unk4 = Hu3DHookFuncCreate(fn_1_9B88);
    Hu3DModelCameraSet(var_r31->unk4, arg1 ? 2 : 1);
    Hu3DModelLayerSet(var_r31->unk4, arg2);
    Hu3DData[var_r31->unk4].unk_120 = var_r31;
    Hu3DModelPosSet(var_r31->unk4, 0.0f, 0.0f, -2000.0f);
    var_r31->unk0 = 0;
    var_r31->unk2 = arg1;
    var_r31->unk7C.r = var_r31->unk7C.g = var_r31->unk7C.b = var_r31->unk7C.a = 0xFF;
    var_r31->unk88 = var_r31->unk8C = 0.0f;
    var_r31->unk90 = var_r31->unk94 = 0.0f;
    var_r31->unk8 = HuSprAnimRead(HuDataReadNum(arg0, MEMORY_DEFAULT_NUM));
    fn_1_C2AC(&var_r31->unkC, arg8 - argA, argC, arg9 - argB);
    fn_1_C2BC(&var_r31->unk3C, 0.0f, 0.0f);
    fn_1_C2AC(&var_r31->unk18, arg8 + argA, argC, arg9 - argB);
    fn_1_C2BC(&var_r31->unk44, 1.0f, 0.0f);
    fn_1_C2AC(&var_r31->unk24, arg8 + argA, argC, arg9 + argB);
    fn_1_C2BC(&var_r31->unk4C, 1.0f, 1.0f);
    fn_1_C2AC(&var_r31->unk30, arg8 - argA, argC, arg9 + argB);
    fn_1_C2BC(&var_r31->unk54, 0.0f, 1.0f);
    DCFlushRangeNoSync(&var_r31->unkC, 0x30);
    DCFlushRangeNoSync(&var_r31->unk3C, 0x20);
    PPCSync();
    var_r28 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x1000, MEMORY_DEFAULT_NUM);
    var_r26 = var_r28;
    DCFlushRange(var_r28, 0x1000);
    GXBeginDisplayList(var_r26, 0x1000);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        GXPosition1x16(var_r30);
        GXPosition1x16(var_r30);
        GXPosition1x16(var_r30);
    }
    var_r31->unk84 = GXEndDisplayList();
    var_r31->unk80 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r31->unk84, MEMORY_DEFAULT_NUM);
    memcpy(var_r31->unk80, var_r28, var_r31->unk84);
    DCFlushRange(var_r31->unk80, var_r31->unk84);
    HuMemDirectFree(var_r28);
    return var_r29;
}

void fn_1_9958(s16 arg0, u8 arg1)
{
    M427DllMapStruct *var_r31;

    if (arg0 != -1) {
        var_r31 = &lbl_1_bss_F0[arg0];
        var_r31->unk0 |= arg1;
    }
}

void fn_1_999C(s16 arg0, u8 arg1)
{
    M427DllMapStruct *var_r31;

    if (arg0 != -1) {
        var_r31 = &lbl_1_bss_F0[arg0];
        var_r31->unk0 &= ~arg1;
    }
}

void fn_1_99E4(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4)
{
    M427DllMapStruct *var_r31;

    if (arg0 != -1) {
        var_r31 = &lbl_1_bss_F0[arg0];
        var_r31->unk7C.r = arg1;
        var_r31->unk7C.g = arg2;
        var_r31->unk7C.b = arg3;
        var_r31->unk7C.a = arg4;
    }
}

void fn_1_9A2C(s16 arg0, float arg8, float arg9, float argA)
{
    M427DllMapStruct *var_r31;

    if (arg0 != -1) {
        var_r31 = &lbl_1_bss_F0[arg0];
        Hu3DModelPosSet(var_r31->unk4, arg8, arg9, argA);
    }
}

void fn_1_9AA0(s16 arg0, float arg8, float arg9, float argA)
{
    M427DllMapStruct *var_r31;

    if (arg0 != -1) {
        var_r31 = &lbl_1_bss_F0[arg0];
        Hu3DModelScaleSet(var_r31->unk4, arg8, arg9, argA);
    }
}

void fn_1_9B14(s16 arg0, float arg8, float arg9, float argA)
{
    M427DllMapStruct *var_r31;

    if (arg0 != -1) {
        var_r31 = &lbl_1_bss_F0[arg0];
        Hu3DModelRotSet(var_r31->unk4, arg8, arg9, argA);
    }
}

void fn_1_9B88(ModelData *model, Mtx matrix)
{
    Mtx sp88;
    M427DllMapStruct *var_r31;
    M427DllMapSubstruct3 *var_r27;
    M427DllMapStruct3Sub *var_r26;

    var_r31 = model->unk_120;
    var_r27 = &lbl_1_bss_158.unk4[var_r31->unk2];
    var_r26 = &lbl_1_bss_158.unk334;
    if ((var_r31->unk0 & 1) == 0) {
        fn_1_94BC(&var_r27->unk78, &model->pos, &var_r31->unkC, &model->scale, model->rot.y, var_r31->unk5C, 4);
        DCFlushRangeNoSync(var_r31->unk5C, 4 * sizeof(Vec2f));
        PPCSync();
        GXLoadPosMtxImm(matrix, 0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
        GXSETARRAY(GX_VA_POS, &var_r31->unkC, sizeof(var_r31->unkC), sizeof(Vec));
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
        GXSETARRAY(GX_VA_TEX0, &var_r31->unk3C, sizeof(var_r31->unk3C), sizeof(Vec2f));
        GXSetVtxDesc(GX_VA_TEX1, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_RGBA6, 0);
        GXSETARRAY(GX_VA_TEX1, var_r31->unk5C, sizeof(var_r31->unk5C), sizeof(Vec2f));
        HuSprTexLoad(var_r31->unk8, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        HuSprTexLoad(var_r26->unk_04, 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        HuSprTexLoad(var_r26->unk_00, 0, 2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        GXSetNumTexGens(3);
        MTXScale(sp88, 1.0f, 1.0f, 1.0f);
        mtxTransCat(sp88, var_r31->unk88, var_r31->unk90, 0.0f);
        GXLoadTexMtxImm(sp88, 0x1E, GX_MTX2x4);
        MTXScale(sp88, 1.0f, 1.0f, 1.0f);
        mtxTransCat(sp88, var_r31->unk8C, var_r31->unk94, 0.0f);
        GXLoadTexMtxImm(sp88, 0x21, GX_MTX2x4);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0, 0x7D);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, 0x1E, 0, 0x7D);
        GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, 0x21, 0, 0x7D);
        GXSetNumTevStages(2);
        GXSetTevColor(GX_TEVREG1, var_r31->unk7C);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C1, GX_CC_TEXA, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXA, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_A1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumIndStages(1);
        GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD2, GX_TEXMAP2);
        GXSetTevIndWarp(0, 0, 1, 0, 1);
        MTXScale(sp88, 0.1f, 0.10000000149011612 * -sind(model->rot.y), 1.0f);
        GXSetIndTexMtx(GX_ITM_0, (float(*)[3])sp88, 0);
        GXSetNumChans(0);
        GXSetZMode(0, GX_LEQUAL, 0);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(0);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
        GXCallDisplayList(var_r31->unk80, var_r31->unk84);
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTevDirect(GX_TEVSTAGE1);
    }
}

void fn_1_A148(ModelData *model, Mtx matrix)
{
    M427DllMapSubstruct3Sub *var_r31;

    var_r31 = model->unk_120;
    if (var_r31->unk0 == 0) {
        GXSetTexCopySrc(0, 0, 0x140, 0x1E0);
        GXSetTexCopyDst(0x140, 0x1E0, GX_TF_RGB5A3, 0);
    }
    else {
        GXSetTexCopySrc(0x140, 0, 0x140, 0x1E0);
        GXSetTexCopyDst(0x140, 0x1E0, GX_TF_RGB5A3, 0);
    }
    GXCopyTex(var_r31->unk4, 1);
    DCFlushRange(var_r31->unk4, var_r31->unk8);
}

s16 fn_1_A1F4(s32 arg0, s16 arg1, s16 arg2, s16 arg3, float arg8, Vec *arg4, Vec *arg5)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    M427DllMapStruct6 *var_r31;
    M427DllMapSubstruct5 *var_r30;
    ModelData *var_r29;
    s16 var_r28;
    s16 var_r27;
    Vec2f *var_r26;
    void *var_r25;
    M427DllMapStruct3 *var_r22;
    s16 var_r19;
    void *var_r18;

    var_r22 = &lbl_1_bss_158;
    var_r28 = Hu3DHookFuncCreate(fn_1_B3CC);
    var_r19 = var_r28;
    Hu3DModelCameraSet(var_r28, arg3 ? 2 : 1);
    Hu3DModelLayerSet(var_r28, 5);
    var_r29 = &Hu3DData[var_r28];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(M427DllMapStruct6), var_r29->unk_48);
    var_r29->unk_120 = var_r31;
    var_r22->unk4[arg3].unkAC = var_r31;
    var_r31->unk_00 = arg3;
    var_r31->unk_0C = 0.0f;
    var_r31->unk_10 = arg8;
    var_r31->unk_04 = arg4;
    var_r31->unk_08 = arg5;
    var_r31->unk_14 = var_r31->unk_18 = 0.0f;
    var_r31->unk_1C = var_r31->unk_20 = 0.0f;
    var_r31->unk_4C = var_r31->unk_50 = 0.0f;
    var_r31->unk_54 = 120.0f;
    var_r31->unk_58 = 72.0f;
    var_r31->unk_5C = 10.0f;
    var_r31->unk_60 = 10.0f;
    var_r31->unk_28 = HuSprAnimRead(HuDataReadNum(arg0, MEMORY_DEFAULT_NUM));
    var_r31->unk_3A = arg1 + 1;
    var_r31->unk_3C = arg2 + 1;
    var_r31->unk_38 = var_r31->unk_3A * var_r31->unk_3C;
    var_r31->unk_2C = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_38 * sizeof(Vec), var_r29->unk_48);
    var_r26 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_38 * sizeof(Vec2f), var_r29->unk_48);
    var_r31->unk_30 = var_r26;
    var_r31->unk_34 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_38 * sizeof(Vec), var_r29->unk_48);
    var_r30 = HuMemDirectMallocNum(HEAP_DATA, arg2 * (arg1 * sizeof(M427DllMapSubstruct5)), var_r29->unk_48);
    var_r31->unk_48 = var_r30;
    var_r25 = HuMemDirectMallocNum(HEAP_DATA, 0x20000, var_r29->unk_48);
    var_r18 = var_r25;
    DCFlushRange(var_r25, 0x20000);
    GXBeginDisplayList(var_r18, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, arg1 * arg2 * 4);
    for (var_r28 = 0; var_r28 < arg2; var_r28++) {
        for (var_r27 = 0; var_r27 < arg1; var_r27++) {
            var_r30->unk0 = var_r27 + (var_r28 * var_r31->unk_3A);
            var_r30->unk2 = var_r27 + var_r28 * var_r31->unk_3A + 1;
            var_r30->unk4 = var_r27 + ((var_r28 + 1) * var_r31->unk_3A) + 1;
            var_r30->unk6 = var_r27 + ((var_r28 + 1) * var_r31->unk_3A);
            GXPosition1x16(var_r30->unk0);
            GXPosition1x16(var_r30->unk0);
            GXPosition1x16(var_r30->unk0);
            GXPosition1x16(var_r30->unk2);
            GXPosition1x16(var_r30->unk2);
            GXPosition1x16(var_r30->unk2);
            GXPosition1x16(var_r30->unk4);
            GXPosition1x16(var_r30->unk4);
            GXPosition1x16(var_r30->unk4);
            GXPosition1x16(var_r30->unk6);
            GXPosition1x16(var_r30->unk6);
            GXPosition1x16(var_r30->unk6);
            fn_1_C2C8(&var_r31->unk_2C[var_r30->unk0], &var_r31->unk_2C[var_r30->unk2], &var_r31->unk_2C[var_r30->unk4], &var_r30->unk8);
            var_r30++;
        }
    }
    var_r31->unk_44 = GXEndDisplayList();
    var_r31->unk_40 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_44, var_r29->unk_48);
    memcpy(var_r31->unk_40, var_r25, var_r31->unk_44);
    DCFlushRange(var_r31->unk_40, var_r31->unk_44);
    HuMemDirectFree(var_r25);
    fn_1_A7F8(var_r31);
    var_f29 = 3.0f / (var_r31->unk_3A - 1);
    var_f28 = 5.0f / (var_r31->unk_3C - 1);
    var_f30 = 0.0f;
    for (var_r28 = 0; var_r28 < var_r31->unk_3C; var_r28++) {
        var_f31 = 0.0f;
        for (var_r27 = 0; var_r27 < var_r31->unk_3A; var_r27++) {
            var_r26->x = var_f31;
            var_r26->y = var_f30;
            var_f31 += var_f29;
            var_r26++;
        }
        var_f30 += var_f28;
    }
    DCFlushRangeNoSync(var_r31->unk_30, var_r31->unk_38 * 8);
    PPCSync();
    return var_r19;
}

void fn_1_A7F8(M427DllMapStruct6 *var_r31)
{
    Vec sp1C;
    float sp14[2];
    float spC[2];
    float var_f29;
    float var_f28;
    float var_f27;
    M427DllMapSubstruct5 *var_r30;
    Vec *var_r29;
    s16 var_r28;
    Vec *var_r27;
    s16 var_r26;
    s16 var_r25;

    if (omPauseChk() == 0) {
        var_r31->unk_4C += 1.0f;
        var_r31->unk_50 += 1.5f;
    }
    if (var_r31->unk_4C >= 360.0f) {
        var_r31->unk_4C -= 360.0f;
    }
    if (var_r31->unk_50 >= 360.0f) {
        var_r31->unk_50 -= 360.0f;
    }
    var_r27 = var_r31->unk_2C;
    var_r29 = var_r31->unk_34;
    spC[0] = var_r31->unk_0C - var_r31->unk_10;
    spC[1] = var_r31->unk_10 / (var_r31->unk_3C - 1);
    var_f28 = var_r31->unk_50;
    for (var_r28 = 0; var_r28 < var_r31->unk_3C; var_r28++) {
        fn_1_B194(var_r31, spC[0], &sp1C);
        sp14[0] = sp1C.x;
        sp14[1] = (sp1C.y - sp1C.x) / (var_r31->unk_3A - 1);
        var_f29 = var_r31->unk_4C;
        for (var_r26 = 0; var_r26 < var_r31->unk_3A; var_r26++) {
            var_r27->x = sp14[0];
            var_r27->y = sp1C.z + (var_r31->unk_5C * sind(var_f29)) + var_r31->unk_60 * sind(var_f28);
            var_r27->z = spC[0];
            sp14[0] += sp14[1];
            var_r27++;
            var_r29->x = var_r29->y = var_r29->z = 0.0f;
            var_r29++;
            var_f29 += var_r31->unk_54;
            if (var_f29 >= 360.0f) {
                var_f29 -= 360.0f;
            }
        }
        spC[0] += spC[1];
        var_f28 += var_r31->unk_58;
        if (var_f28 >= 360.0f) {
            var_f28 -= 360.0f;
        }
    }
    var_r30 = var_r31->unk_48;
    var_r25 = (var_r31->unk_3A - 1) * (var_r31->unk_3C - 1);
    for (var_r28 = 0; var_r28 < var_r25; var_r28++) {
        fn_1_C2C8(&var_r31->unk_2C[var_r30->unk0], &var_r31->unk_2C[var_r30->unk2], &var_r31->unk_2C[var_r30->unk4], &var_r30->unk8);
        var_r31->unk_34[var_r30->unk0].x += var_r30->unk8.x;
        var_r31->unk_34[var_r30->unk0].y += var_r30->unk8.y;
        var_r31->unk_34[var_r30->unk0].z += var_r30->unk8.z;

        var_r31->unk_34[var_r30->unk2].x += var_r30->unk8.x;
        var_r31->unk_34[var_r30->unk2].y += var_r30->unk8.y;
        var_r31->unk_34[var_r30->unk2].z += var_r30->unk8.z;

        var_r31->unk_34[var_r30->unk4].x += var_r30->unk8.x;
        var_r31->unk_34[var_r30->unk4].y += var_r30->unk8.y;
        var_r31->unk_34[var_r30->unk4].z += var_r30->unk8.z;

        var_r31->unk_34[var_r30->unk6].x += var_r30->unk8.x;
        var_r31->unk_34[var_r30->unk6].y += var_r30->unk8.y;
        var_r31->unk_34[var_r30->unk6].z += var_r30->unk8.z;
        var_r30++;
    }
    var_r29 = var_r31->unk_34;
    for (var_r28 = 0; var_r28 < var_r31->unk_38; var_r28++) {
        var_f27 = sqrtf((var_r29->z * var_r29->z) + ((var_r29->x * var_r29->x) + (var_r29->y * var_r29->y)));
        var_r29->x /= var_f27;
        var_r29->y /= var_f27;
        var_r29->z /= var_f27;
        var_r29++;
    }
    DCFlushRangeNoSync(var_r31->unk_2C, var_r31->unk_38 * sizeof(Vec));
    DCFlushRangeNoSync(var_r31->unk_34, var_r31->unk_38 * sizeof(Vec));
    PPCSync();
}

s16 lbl_1_data_1EC[2] = { 0, 0 };

float fn_1_AE78(s16 arg0, float arg8, float arg9)
{
    float sp8[2];
    float var_f31;
    float var_f30;
    Vec *var_r31;
    s16 var_r30;
    M427DllMapSubstruct3 *var_r29;
    Vec *var_r28;
    s16 var_r27;
    s16 var_r26;

    var_r29 = &lbl_1_bss_158.unk4[arg0];
    if (lbl_1_bss_158.unk0 != 0) {
        if (lbl_1_bss_158.unk0 == 1) {
            lbl_1_data_1EC[arg0] = 0;
            lbl_1_bss_158.unk0 = 2;
        }
        if (!lbl_1_bss_98.unk4) {
            return 0.0f;
        }
        var_r28 = lbl_1_bss_98.unk4;
        var_r31 = &lbl_1_bss_98.unk4[lbl_1_data_1EC[arg0]];
        var_r27 = lbl_1_bss_98.unk14;
        var_r26 = lbl_1_bss_98.unk16;
        for (var_r30 = lbl_1_data_1EC[arg0]; var_r30 < var_r27; var_r30++, var_r31++) {
            if (arg9 >= var_r31->z && arg8 >= var_r31->x) {
                break;
            }
        }
        if (var_r30 == var_r27) {
            return 0.0f;
        }
    }
    else {
        if (!var_r29->unkAC) {
            return 0.0f;
        }
        var_r28 = var_r29->unkAC->unk_2C;
        var_r31 = &var_r29->unkAC->unk_2C[lbl_1_data_1EC[arg0]];
        var_r27 = var_r29->unkAC->unk_38;
        var_r26 = var_r29->unkAC->unk_3A;
        for (var_r30 = lbl_1_data_1EC[arg0]; var_r30 < var_r27; var_r30++, var_r31++) {
            if (arg9 <= var_r31->z && arg8 <= var_r31->x) {
                break;
            }
        }
        if (var_r30 == var_r27) {
            return 0.0f;
        }
    }
    sp8[0] = var_r31->x - var_r28[var_r30 - 1].x;
    sp8[1] = arg8 - var_r28[var_r30 - 1].x;
    var_f30 = sp8[1] / sp8[0];
    var_f31 = var_r31->y - var_r28[var_r30 - 1].y;
    var_f31 = var_r28[var_r30 - 1].y + (var_f31 * var_f30);
    lbl_1_data_1EC[arg0] = var_r30 - (var_r26 * 2);
    return 20.0f + var_f31;
}

void fn_1_B194(M427DllMapStruct6 *arg0, float arg8, Vec *arg1)
{
    float sp10[2];
    float sp8[2];
    float var_f31;
    s16 var_r31;

    for (var_r31 = lbl_1_bss_580; var_r31 != 0;) {
        var_r31--;
        if (arg0->unk_04[var_r31].z >= arg8) {
            if (var_r31 == (lbl_1_bss_580 - 1)) {
                arg1->x = arg0->unk_08[var_r31].x;
                arg1->y = arg0->unk_04[var_r31].x;
                arg1->z = arg0->unk_04[var_r31].y;
            }
            else {
                var_f31 = (arg0->unk_04[var_r31].z - arg8) / (arg0->unk_04[var_r31].z - arg0->unk_04[var_r31 + 1].z);
                sp10[0] = arg0->unk_08[var_r31].x - 100.0f;
                sp10[1] = arg0->unk_08[var_r31 + 1].x - 100.0f;
                sp8[0] = 100.0f + arg0->unk_04[var_r31].x;
                sp8[1] = 100.0f + arg0->unk_04[var_r31 + 1].x;
                arg1->x = sp10[0] + (var_f31 * (sp10[1] - sp10[0]));
                arg1->y = sp8[0] + (var_f31 * (sp8[1] - sp8[0]));
                arg1->z = arg0->unk_04[var_r31].y + (var_f31 * (arg0->unk_04[var_r31 + 1].y - arg0->unk_04[var_r31].y));
            }
            return;
        }
    }
}

void fn_1_B3CC(ModelData *model, Mtx matrix)
{
    Mtx sp154;
    Mtx sp124;
    Mtx spF4;
    Mtx spC4;
    GXTexObj sp44;
    Vec2f sp18;
    GXColor sp14;
    float var_f31;
    M427DllMapStruct6 *var_r31;
    M427DllMapSubstruct3 *var_r30;
    M427DllMapSubstruct3Sub *var_r27;
    M427DllMapStruct3Sub *var_r24;
    s16 var_r21;

    var_r31 = model->unk_120;
    var_r30 = &lbl_1_bss_158.unk4[var_r31->unk_00];
    var_r27 = &var_r30->unk94;
    var_r24 = &lbl_1_bss_158.unk334;
    fn_1_A7F8(var_r31);
    GXLoadPosMtxImm(matrix, 0);
    MTXInvXpose(matrix, spF4);
    GXLoadNrmMtxImm(spF4, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSETARRAY(GX_VA_POS, var_r31->unk_2C, var_r31->unk_38 * sizeof(Vec), sizeof(Vec));
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSETARRAY(GX_VA_NRM, var_r31->unk_34, var_r31->unk_38 * sizeof(Vec), sizeof(Vec));
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSETARRAY(GX_VA_TEX0, var_r31->unk_30, var_r31->unk_38 * sizeof(Vec2f), sizeof(Vec2f));
    if (var_r31->unk_00 == 0) {
        GXInitTexObj(&sp44, var_r27->unk4, 0x140, 0x1E0, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, 0);
    }
    else {
        GXInitTexObj(&sp44, var_r27->unk4, 0x140, 0x1E0, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, 0);
    }
    GXInitTexObjLOD(&sp44, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&sp44, GX_TEXMAP0);
    HuSprTexLoad(var_r31->unk_28, 0, 1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(var_r24->unk_00, 0, 2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTevStages(3);
    sp14.r = 0;
    sp14.g = 0xB6;
    sp14.b = 0xCC;
    sp14.a = 0x40;
    GXSetTevColor(GX_TEVREG2, sp14);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, GX_TRUE, GX_TEVREG0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXA, GX_CC_C2, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C1, GX_CC_RASC, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD2, GX_TEXMAP2);
    GXSetTevIndWarp(1, 0, 1, 0, 1);
    MTXScale(spF4, -0.1f, 0.1f, 1.0f);
    GXSetIndTexMtx(GX_ITM_0, (float(*)[3])spF4, 0);
    GXSetNumTexGens(3);
    C_MTXLightPerspective(sp154, 45.0f, 0.6f, 0.5f, -0.5f, 0.5f, 0.5f);
    MTXCopy(matrix, sp124);
    MTXInverse(Hu3DCameraMtx, spF4);
    MTXConcat(spF4, sp124, spF4);
    MTXConcat(sp154, Hu3DCameraMtx, spC4);
    MTXConcat(spC4, spF4, spF4);
    GXLoadTexMtxImm(spF4, 0x1E, GX_MTX3x4);
    {
        Vec sp38 = { 1.0f, 1.0f, 1.0f };
        var_f31 = 0.0f;
        fn_1_94BC(&var_r30->unk78, &var_r30->unk84, var_r31->unk_2C, &sp38, var_f31, &sp18, 1);
    }
    if (omPauseChk() == 0) {
        var_r31->unk_20 = var_r31->unk_20 - 0.001f;
    }
    MTXScale(spF4, 1.0f, 1.0f, 1.0f);
    mtxTransCat(spF4, 0.0f, var_r31->unk_20 + (0.3f * sp18.y), 0.0f);
    GXLoadTexMtxImm(spF4, 0x21, GX_MTX2x4);
    if (omPauseChk() == 0) {
        var_r31->unk_24 += 0.05f;
    }
    if (var_r31->unk_24 >= 360.0f) {
        var_r31->unk_24 -= 360.0f;
    }
    var_r31->unk_14 = sind(var_r31->unk_24);
    if (omPauseChk() == 0) {
        var_r31->unk_1C += 0.0005f;
    }
    MTXScale(spF4, 0.5f, 0.5f, 0.5f);
    mtxTransCat(spF4, var_r31->unk_14, var_r31->unk_1C, 0.0f);
    GXLoadTexMtxImm(spF4, 0x24, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, 0x1E, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, 0x21, GX_FALSE, 0x7D);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, 0x24, GX_FALSE, 0x7D);
    GXSetNumChans(1);
    var_r21 = Hu3DLightSet(model, &Hu3DCameraMtx, &Hu3DCameraMtxXPose, 0.0f);
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, var_r21, GX_DF_CLAMP, GX_AF_SPOT);
    sp14.r = sp14.g = sp14.b = 0x10;
    sp14.a = 0xFF;
    GXSetChanAmbColor(GX_COLOR0A0, sp14);
    sp14.r = sp14.g = sp14.b = 0xFF;
    sp14.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, sp14);
    GXSetZMode(1, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    GXCallDisplayList(var_r31->unk_40, var_r31->unk_44);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
#ifdef TARGET_PC
    GXDestroyTexObj(&sp44);
#endif
}

void fn_1_BD2C(ModelData *model, Mtx matrix)
{
    GXColor sp14 = { 0, 0, 0, 0xFF };
    GXSetFog(GX_FOG_EXP, 10000.0f, 20000.0f, 300.0f, 50000.0f, sp14);
    GXLoadPosMtxImm(matrix, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    HuSprTexLoad(lbl_1_bss_F4, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetNumChans(0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-1000.0f, 1000.0f, -24000.0f);
    GXTexCoord2f32(0.0f, 0.0f);

    GXPosition3f32(1000.0f, 1000.0f, -24000.0f);
    GXTexCoord2f32(1.0f, 0.0f);

    GXPosition3f32(1000.0f, -1000.0f, -24000.0f);
    GXTexCoord2f32(1.0f, 1.0f);

    GXPosition3f32(-1000.0f, -1000.0f, -24000.0f);
    GXTexCoord2f32(0.0f, 1.0f);

    GXSetFog(GX_FOG_EXP, 3500.0f, 20000.0f, 300.0f, 50000.0f, sp14);
}

void fn_1_C154(ModelData *model, Mtx matrix)
{
    GXColor spC = { 0, 0, 0, 255 };
    GXSetFog(GX_FOG_EXP, 10000.0f, 20000.0f, 300.0f, 50000.0f, spC);
}

void fn_1_C200(ModelData *model, Mtx matrix)
{
    GXColor spC = { 0, 0, 0, 255 };
    GXSetFog(GX_FOG_EXP, 3500.0f, 20000.0f, 300.0f, 50000.0f, spC);
}

void fn_1_C2AC(Vec *arg0, float arg8, float arg9, float argA)
{
    arg0->x = arg8;
    arg0->y = arg9;
    arg0->z = argA;
}

void fn_1_C2BC(Vec2f *arg0, float arg8, float arg9)
{
    arg0->x = arg8;
    arg0->y = arg9;
}

void fn_1_C2C8(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3)
{
    Vec sp14;
    Vec sp8;

    sp14.x = arg1->x - arg0->x;
    sp14.y = arg1->y - arg0->y;
    sp14.z = arg1->z - arg0->z;
    sp8.x = arg2->x - arg1->x;
    sp8.y = arg2->y - arg1->y;
    sp8.z = arg2->z - arg1->z;
    arg3->x = -((sp14.y * sp8.z) - (sp14.z * sp8.y));
    arg3->y = -((sp14.z * sp8.x) - (sp14.x * sp8.z));
    arg3->z = -((sp14.x * sp8.y) - (sp14.y * sp8.x));
}

// is this one of the structs?
void fn_1_C3A0(float *arg0, float *arg1)
{
    arg1[0] = arg0[0];
    arg1[4] = arg0[1];
    arg1[8] = arg0[2];
    arg1[1] = arg0[4];
    arg1[5] = arg0[5];
    arg1[9] = arg0[6];
    arg1[2] = arg0[8];
    arg1[6] = arg0[9];
    arg1[10] = arg0[10];
    arg1[3] = 0.0f;
    arg1[7] = 0.0f;
    arg1[11] = 0.0f;
}

s16 fn_1_C41C(float x1, float y1, float z1, float x2, float y2, float z2, u8 r, u8 g, u8 b)
{
    Vec sp34;
    Vec sp28;
    GXColor sp23;
    LightData *var_r31;
    s16 var_r30;

    sp34.x = x1;
    sp34.y = y1;
    sp34.z = z1;
    sp28.x = x2;
    sp28.y = y2;
    sp28.z = z2;
    sp23.r = r;
    sp23.g = g;
    sp23.b = b;
    sp23.a = 0xFF;
    for (var_r31 = Hu3DLocalLight, var_r30 = 0; var_r30 < 0x20; var_r30++, var_r31++) {
        if (var_r31->unk_00 == -1) {
            break;
        }
    }
    if (var_r30 == 0x20) {
        return -1;
    }
    fn_1_C68C(var_r31, &sp34, &sp28, &sp23);
    var_r31->unk_00 |= 0x8000;
    return var_r30;
}

void fn_1_C528(s16 sp8, s16 var_r28, float x1, float y1, float z1, float x2, float y2, float z2, u8 r, u8 g, u8 b)
{
    Vec sp38;
    Vec sp2C;
    GXColor sp27;
    ModelData *var_r31;
    LightData *var_r30;
    s16 var_r29;

    var_r31 = &Hu3DData[sp8];
    sp38.x = x1;
    sp38.y = y1;
    sp38.z = z1;
    sp2C.x = x2;
    sp2C.y = y2;
    sp2C.z = z2;
    sp27.r = r;
    sp27.g = g;
    sp27.b = b;
    sp27.a = 0xFF;
    for (var_r30 = Hu3DLocalLight, var_r29 = 0; var_r29 < 0x20; var_r29++, var_r30++) {
        if (var_r30->unk_00 == -1) {
            break;
        }
    }
    if (var_r29 == 0x20) {
        OSReport("Light Entry Over!\n");
        return;
    }
    fn_1_C68C(var_r30, &sp38, &sp2C, &sp27);
    if (var_r31->unk_38[var_r28] == -1) {
        var_r31->unk_38[var_r28] = var_r29;
        var_r31->attr |= 0x1000;
    }
}

void fn_1_C68C(LightData *arg0, Vec *arg1, Vec *arg2, GXColor *arg3)
{
    arg0->unk_00 = 0;
    arg0->unk_1C = *arg1;
    arg0->unk_28 = *arg2;
    arg0->unk_34.x = arg0->unk_34.y = arg0->unk_34.z = 0.0f;
    arg0->unk_04 = 30.0f;
    arg0->unk_02 = 2;
    VECNormalize(&arg0->unk_28, &arg0->unk_28);
    arg0->color.r = arg3->r;
    arg0->color.g = arg3->g;
    arg0->color.b = arg3->b;
    arg0->color.a = arg3->a;
}

void fn_1_C76C(u8 arg0, float arg8, float arg9, float argA, s16 arg1, float argB, float argC, s16 arg2)
{
    Vec sp24;
    Vec sp18;
    float sp10[2];
    GXColor spC;
    M427DllMapSubstruct6 *var_r31;
    s16 var_r30;

    if (arg0 != 0) {
        argB += (((rand8() << 8) | rand8()) % 21) - 0xA;
    }
    else {
        argB += (((rand8() << 8) | rand8()) % 61) - 0x1E;
    }
    sp10[0] = sind(argB);
    sp10[1] = cosd(argB);
    for (var_r30 = 0; var_r30 < arg1; var_r30++) {
        if (arg0 != 0) {
            sp24.x = arg8 + ((((rand8() << 8) | rand8()) % 21) - 0xA);
            sp24.y = arg9 + ((((rand8() << 8) | rand8()) % 21) - 0xA);
            sp24.z = argA + ((((rand8() << 8) | rand8()) % 21) - 0xA);
        }
        else {
            sp24.x = arg8 + ((((rand8() << 8) | rand8()) % 41) - 0x14);
            sp24.y = arg9 + ((((rand8() << 8) | rand8()) % 41) - 0x14);
            sp24.z = argA + ((((rand8() << 8) | rand8()) % 41) - 0x14);
        }
        sp18.x = sp18.y = sp18.z = 0.0f;
        spC.r = spC.g = spC.b = spC.a = 0xFF;
        var_r31 = fn_1_D4FC(arg2, &sp24, &sp18, 0.0f, &spC);
        if (!var_r31) {
            break;
        }
        var_r31->unk_38 = arg0;
        if (arg0 != 0) {
            var_r31->unk_34 = 0;
            var_r31->unk_36 = 3;
            var_r31->unk_00 = argC * (sp10[0] * (0.1f * ((((rand8() << 8) | rand8()) % 151) + 0x96)));
            var_r31->unk_04 = 0.1f * ((((rand8() << 8) | rand8()) % 31) - 0x14);
            var_r31->unk_08 = argC * (sp10[1] * (0.1f * ((((rand8() << 8) | rand8()) % 151) + 0x96)));
            var_r31->unk_18 = 0.01f * var_r31->unk_00;
            var_r31->unk_1C = 0.1f;
            var_r31->unk_20 = 0.01f * var_r31->unk_08;
            var_r31->unk_24 = argC * (0.1f * ((((rand8() << 8) | rand8()) % 11) + 0xA));
            var_r31->unk_28 = argC * (0.01f * ((((rand8() << 8) | rand8()) % 101) + 0x32) / (var_r31->unk_36 * 0xE));
        }
        else {
            var_r31->unk_34 = 0;
            var_r31->unk_36 = 2;
            var_r31->unk_00 = sp10[0] * (0.1f * ((((rand8() << 8) | rand8()) % 31) + 0x32));
            var_r31->unk_04 = 0.1f * ((((rand8() << 8) | rand8()) % 31) - 0x14);
            var_r31->unk_08 = sp10[1] * (0.1f * (((((rand8() << 8) | rand8()) % 31)) + 0x32));
            var_r31->unk_18 = 0.0f;
            var_r31->unk_1C = 0.1f;
            var_r31->unk_20 = 0.0f;
            var_r31->unk_24 = 0.3f * (0.1f * ((((rand8() << 8) | rand8()) % 11) + 0xA));
            var_r31->unk_28 = 0.4f * ((0.01f * ((((rand8() << 8) | rand8()) % 51) + 0x32)) / (var_r31->unk_36 * 0xE));
        }
        var_r31->unk_2C = 1024.0f * argC;
        var_r31->unk_30 = var_r31->unk_2C / (var_r31->unk_36 * 0xE);
    }
}

void fn_1_D22C(ModelData *model, M427DllMapStruct7 *arg1, Mtx matrix)
{
    M427DllMapSubstruct6 *var_r31;
    GXColor *var_r30;
    s16 var_r29;
    u8 var_r28;

    var_r31 = arg1->unk_18;
    var_r30 = arg1->unk_24;
    for (var_r29 = 0; var_r29 < arg1->unk_00; var_r29++, var_r31++, var_r30++) {
        if (var_r31->unk_62 != 0) {
            var_r31->unk_54.x += var_r31->unk_00;
            var_r31->unk_54.y += var_r31->unk_04;
            var_r31->unk_54.z += var_r31->unk_08;
            if (var_r31->unk_38 != 0) {
                var_r31->unk_00 -= var_r31->unk_18;
                var_r31->unk_04 += var_r31->unk_1C;
                var_r31->unk_08 -= var_r31->unk_20;
                var_r31->unk_18 = 0.01f * var_r31->unk_00;
                var_r31->unk_1C *= 1.04f;
                var_r31->unk_20 = 0.01f * var_r31->unk_08;
            }
            else {
                var_r31->unk_04 += var_r31->unk_1C;
                var_r31->unk_1C *= 1.1f;
            }
            var_r31->unk_24 += var_r31->unk_28;
            var_r31->unk_48.x = var_r31->unk_48.y = var_r31->unk_48.z = var_r31->unk_24;
            var_r31->unk_2C -= var_r31->unk_30;
            if (var_r31->unk_2C > 255.0f) {
                var_r28 = 0xFF;
            }
            else {
                var_r28 = (s32)var_r31->unk_2C;
            }
            var_r30->a = (s32)var_r28;
            var_r31->unk_34++;
            if (var_r31->unk_34 >= var_r31->unk_36) {
                var_r31->unk_34 = 0;
                var_r31->unk_60++;
            }
            if (var_r31->unk_60 >= arg1->unk_14) {
                var_r31->unk_62 = 0;
            }
        }
    }
}

s16 fn_1_D430(float arg8, float arg9, float argA, s16 arg0)
{
    Vec sp28;
    Vec sp1C;
    GXColor sp16;
    M427DllMapSubstruct6 *var_r31;

    sp28.x = arg8;
    sp28.y = arg9;
    sp28.z = argA;
    sp1C.x = sp1C.y = sp1C.z = 1.0f;
    sp16.r = 0xFF;
    sp16.g = 0xA0;
    sp16.b = 0x60;
    sp16.a = 0xFF;
    var_r31 = fn_1_D4FC(arg0, &sp28, &sp1C, 0.0f, &sp16);
    if (!var_r31) {
        return -1;
    }
    var_r31->unk_24 = 0.0f;
    return var_r31->unk_40;
}

M427DllMapSubstruct6 *fn_1_D4FC(s16 arg0, Vec *arg1, Vec *arg2, float arg8, GXColor *arg3)
{
    M427DllMapSubstruct6 *var_r31;
    M427DllMapStruct7 *var_r30;
    s16 var_r29;
    ModelData *var_r28;

    var_r28 = &Hu3DData[arg0];
    var_r30 = var_r28->unk_120;
    for (var_r29 = 0, var_r31 = var_r30->unk_18; var_r29 < var_r30->unk_00; var_r29++, var_r31++) {
        if (var_r31->unk_62 == 0) {
            break;
        }
    }
    if (var_r29 == var_r30->unk_00) {
        return NULL;
    }
    var_r30->unk_24[var_r29].r = arg3->r;
    var_r30->unk_24[var_r29].g = arg3->g;
    var_r30->unk_24[var_r29].b = arg3->b;
    var_r30->unk_24[var_r29].a = arg3->a;
    var_r31->unk_40 = var_r29;
    var_r31->unk_44 = arg8;
    var_r31->unk_48 = *arg2;
    var_r31->unk_54 = *arg1;
    var_r31->unk_60 = 0;
    var_r31->unk_3C = 0;
    var_r31->unk_62 = 1;
    return var_r31;
}

s16 fn_1_D63C(AnimData *arg0, s16 arg1, float arg8, s16 arg2, s16 arg3)
{
    M427DllMapStruct7 *var_r31;
    s16 var_r30;
    Vec2f *var_r29;
    ModelData *var_r28;
    GXColor *var_r27;
    Vec *var_r25;
    M427DllMapSubstruct6 *var_r24;
    s16 var_r22;
    void *var_r21;
    s16 var_r20;
    s16 var_r19;
    void *var_r18;

    var_r20 = Hu3DHookFuncCreate(fn_1_DCD4);
    var_r28 = &Hu3DData[var_r20];
    var_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(M427DllMapStruct7), var_r28->unk_48);
    var_r28->unk_120 = var_r31;
    arg0->useNum++;
    var_r31->unk_10 = arg0;
    var_r31->unk_00 = arg1;
    var_r31->unk_08 = 0;
    var_r31->unk_0C = 0;
    var_r24 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(M427DllMapSubstruct6), var_r28->unk_48);
    var_r31->unk_18 = var_r24;
    for (var_r30 = 0; var_r30 < arg1; var_r30++, var_r24++) {
        var_r24->unk_60 = -1;
        var_r24->unk_62 = 0;
    }
    var_r25 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Vec) * 4, var_r28->unk_48);
    var_r31->unk_1C = var_r25;
    for (var_r30 = 0; var_r30 < (arg1 * 4); var_r30++, var_r25++) {
        var_r25->x = var_r25->y = var_r25->z = 0.0f;
    }
    var_r27 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(GXColor), var_r28->unk_48);
    var_r31->unk_24 = var_r27;
    for (var_r30 = 0; var_r30 < arg1; var_r30++, var_r27++) {
        var_r27->r = var_r27->g = var_r27->b = var_r27->a = 0xFF;
    }
    var_r29 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Vec2f) * 4, var_r28->unk_48);
    var_r31->unk_20 = var_r29;
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
    if ((arg2 != 0) || (arg3 != 0)) {
        var_r22 = arg0->bmp->sizeX / arg2;
        var_r19 = arg0->bmp->sizeY / arg3;
        var_r31->unk_14 = var_r22 * var_r19;
        var_r31->unk_60 = 1.0f / var_r22;
        var_r31->unk_64 = 1.0f / var_r19;
    }
    else {
        var_r22 = 1;
        var_r31->unk_14 = 1;
        var_r31->unk_60 = 1.0f;
        var_r31->unk_64 = 1.0f;
    }
    var_r31->unk_5C = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_14 * sizeof(Vec2f), var_r28->unk_48);
    fn_1_E2B0(var_r31->unk_5C, var_r31->unk_14, var_r22, var_r31->unk_60, var_r31->unk_64);
    var_r31->unk_2C.x = var_r31->unk_50 = var_r31->unk_48 = var_r31->unk_54 = -arg8;
    var_r31->unk_38 = var_r31->unk_44 = var_r31->unk_2C.y = var_r31->unk_3C = arg8;
    var_r31->unk_2C.z = var_r31->unk_40 = var_r31->unk_4C = var_r31->unk_58 = 0.0f;
    var_r21 = HuMemDirectMallocNum(HEAP_DATA, 0x20000, var_r28->unk_48);
    var_r18 = var_r21;
    DCFlushRange(var_r21, 0x20000);
    GXBeginDisplayList(var_r18, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, arg1 * 4);
    for (var_r30 = 0; var_r30 < arg1; var_r30++) {
        GXPosition1x16(var_r30 * 4);
        GXPosition1x16(var_r30);
        GXPosition1x16(var_r30 * 4);
        GXPosition1x16(var_r30 * 4 + 1);
        GXPosition1x16(var_r30);
        GXPosition1x16(var_r30 * 4 + 1);
        GXPosition1x16(var_r30 * 4 + 2);
        GXPosition1x16(var_r30);
        GXPosition1x16(var_r30 * 4 + 2);
        GXPosition1x16(var_r30 * 4 + 3);
        GXPosition1x16(var_r30);
        GXPosition1x16(var_r30 * 4 + 3);
    }
    var_r31->unk_04 = GXEndDisplayList();
    var_r31->unk_28 = HuMemDirectMallocNum(HEAP_DATA, var_r31->unk_04, var_r28->unk_48);
    memcpy(var_r31->unk_28, var_r21, var_r31->unk_04);
    DCFlushRange(var_r31->unk_28, var_r31->unk_04);
    HuMemDirectFree(var_r21);
    return var_r20;
}

void fn_1_DB80(s16 arg0)
{
    ModelData *var_r31;
    M427DllMapStruct7 *var_r30;

    var_r31 = &Hu3DData[arg0];
    var_r30 = var_r31->unk_120;
    HuSprAnimKill(var_r30->unk_10);
    Hu3DModelKill(arg0);
}

void *fn_1_DBE0(s16 arg0)
{
    ModelData *var_r31;

    var_r31 = &Hu3DData[arg0];
    return var_r31->unk_120;
}

M427DllMapSubstruct6 *fn_1_DC0C(s16 arg0, s16 arg1)
{
    ModelData *var_r31;
    M427DllMapStruct7 *var_r30;

    var_r31 = &Hu3DData[arg0];
    var_r30 = var_r31->unk_120;
    if (arg1 == -1) {
        return NULL;
    }
    return &var_r30->unk_18[arg1];
}

void fn_1_DC64(s16 arg0, M427DllHook arg1)
{
    ModelData *var_r31;
    M427DllMapStruct7 *var_r30;

    var_r31 = &Hu3DData[arg0];
    var_r30 = var_r31->unk_120;
    var_r30->unk_0C = arg1;
}

void fn_1_DC9C(s16 arg0, u8 arg1)
{
    ModelData *var_r31;
    M427DllMapStruct7 *var_r30;

    var_r31 = &Hu3DData[arg0];
    var_r30 = var_r31->unk_120;
    var_r30->unk_08 = arg1;
}

void fn_1_DCD4(ModelData *model, Mtx matrix)
{
    Mtx sp128;
    ROMtx spF8;
    Mtx spC8;
    Mtx sp98;
    Vec sp68[4];
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    Vec *var_r31;
    M427DllMapStruct7 *var_r30;
    M427DllMapSubstruct6 *var_r29;
    Vec2f *var_r26;
    s16 var_r25;
    s16 var_r24;
    M427DllHook var_r23;

    var_r30 = model->unk_120;
    GXLoadPosMtxImm(matrix, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    var_r24 = var_r30->unk_10->bmp->dataFmt & 0xF;
    if ((var_r24 == 7) || (var_r24 == 8)) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXA, GX_CC_RASC, GX_CC_ZERO);
    }
    else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    }
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    if ((model->attr & 2) != 0) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
    else {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    }
    HuSprTexLoad(var_r30->unk_10, 0, 0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(0);
    switch (var_r30->unk_08) {
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
    GXSETARRAY(GX_VA_POS, var_r30->unk_1C, var_r30->unk_00 * sizeof(Vec) * 4, sizeof(Vec));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSETARRAY(GX_VA_CLR0, var_r30->unk_24, var_r30->unk_00 * sizeof(GXColor), sizeof(GXColor));
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSETARRAY(GX_VA_TEX0, var_r30->unk_20, var_r30->unk_00 * sizeof(Vec2f) * 4, sizeof(Vec2f));
    sp128[0][0] = matrix[0][0];
    sp128[1][0] = matrix[0][1];
    sp128[2][0] = matrix[0][2];
    sp128[0][1] = matrix[1][0];
    sp128[1][1] = matrix[1][1];
    sp128[2][1] = matrix[1][2];
    sp128[0][2] = matrix[2][0];
    sp128[1][2] = matrix[2][1];
    sp128[2][2] = matrix[2][2];
    sp128[0][3] = 0.0f;
    sp128[1][3] = 0.0f;
    sp128[2][3] = 0.0f;
    MTXReorder(sp128, spF8);
    if ((omPauseChk() == 0) && (var_r30->unk_0C)) {
        var_r23 = var_r30->unk_0C;
        var_r23(model, var_r30, matrix);
    }
    var_r29 = var_r30->unk_18;
    var_r31 = var_r30->unk_1C;
    var_r26 = var_r30->unk_20;
    MTXROMultVecArray(spF8, &var_r30->unk_2C, sp68, 4);
    for (var_r25 = 0; var_r25 < var_r30->unk_00; var_r25++, var_r29++, var_r26 += 4) {
        if (var_r29->unk_62 == 0) {
            var_r31->x = var_r31->y = var_r31->z = 0.0f;
            var_r31++;
            var_r31->x = var_r31->y = var_r31->z = 0.0f;
            var_r31++;
            var_r31->x = var_r31->y = var_r31->z = 0.0f;
            var_r31++;
            var_r31->x = var_r31->y = var_r31->z = 0.0f;
            var_r31++;
        }
        else {
            if (var_r29->unk_44 == 0.0f) {
                fn_1_E420(sp68, &sp38, &var_r29->unk_48, 4);
                VECAdd(&sp38, &var_r29->unk_54, var_r31++);
                VECAdd(&sp44, &var_r29->unk_54, var_r31++);
                VECAdd(&sp50, &var_r29->unk_54, var_r31++);
                VECAdd(&sp5C, &var_r29->unk_54, var_r31++);
            }
            else {
                fn_1_E420(&var_r30->unk_2C, &sp38, &var_r29->unk_48, 4);
                MTXRotRad(spC8, 0x5A, MTXDegToRad(var_r29->unk_44));
                MTXConcat(sp128, spC8, sp98);
                MTXMultVecArray(sp98, &sp38, &sp8, 4);
                VECAdd(&sp8, &var_r29->unk_54, var_r31++);
                VECAdd(&sp14, &var_r29->unk_54, var_r31++);
                VECAdd(&sp20, &var_r29->unk_54, var_r31++);
                VECAdd(&sp2C, &var_r29->unk_54, var_r31++);
            }
            if (var_r29->unk_60 != -1) {
                fn_1_E37C(var_r26, var_r30->unk_5C, var_r29->unk_60, var_r30->unk_60, var_r30->unk_64);
            }
        }
    }
    DCFlushRangeNoSync(var_r30->unk_1C, var_r30->unk_00 * sizeof(Vec) * 4);
    DCFlushRangeNoSync(var_r30->unk_20, var_r30->unk_00 * sizeof(Vec2f) * 4);
    PPCSync();
    GXCallDisplayList(var_r30->unk_28, var_r30->unk_04);
}

void fn_1_E2B0(Vec2f *arg0, s16 arg1, s16 arg2, float arg8, float arg9)
{
    s16 var_r31;
    s16 var_r30;
    s16 var_r29;

    for (var_r31 = 0; var_r31 < arg1; var_r31++, arg0++) {
        var_r30 = var_r31 % arg2;
        var_r29 = var_r31 / arg2;
        arg0->x = var_r30 * arg8;
        arg0->y = var_r29 * arg9;
    }
}

void fn_1_E37C(Vec2f *arg0, Vec2f *arg1, s16 arg2, float arg8, float arg9)
{
    arg0[0].x = arg1[arg2].x;
    arg0[0].y = arg1[arg2].y;
    arg0[1].x = arg8 + arg1[arg2].x;
    arg0[1].y = arg1[arg2].y;
    arg0[2].x = arg8 + arg1[arg2].x;
    arg0[2].y = arg9 + arg1[arg2].y;
    arg0[3].x = arg1[arg2].x;
    arg0[3].y = arg9 + arg1[arg2].y;
}

void fn_1_E420(Vec *arg0, Vec *arg1, Vec *arg2, s16 arg3)
{
    s16 var_r31;

    for (var_r31 = 0; var_r31 < arg3; var_r31++, arg0++, arg1++) {
        arg1->x = arg0->x * arg2->x;
        arg1->y = arg0->y * arg2->y;
        arg1->z = arg0->z * arg2->z;
    }
}

void fn_1_E488(void)
{
    if ((HuPadBtnDown[0] & PAD_TRIGGER_L) != 0) {
        lbl_1_bss_91 ^= 1;
    }
    if (lbl_1_bss_91 != 0) {
        if ((HuPadBtnDown[0] & PAD_TRIGGER_Z) != 0) {
            lbl_1_bss_90 = lbl_1_bss_90 ^ 1;
        }
        if ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0) {
            CRotM[lbl_1_bss_90].y += 1.0f;
        }
        if ((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) {
            CRotM[lbl_1_bss_90].y -= 1.0f;
        }
        if ((HuPadBtn[0] & PAD_BUTTON_UP) != 0) {
            CRotM[lbl_1_bss_90].x -= 1.0f;
        }
        if ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0) {
            CRotM[lbl_1_bss_90].x += 1.0f;
        }
        CenterM[lbl_1_bss_90].x += HuPadSubStkX[0];
        if ((HuPadBtn[0] & PAD_TRIGGER_R) != 0) {
            CenterM[lbl_1_bss_90].y += HuPadSubStkY[0];
        }
        else {
            CenterM[lbl_1_bss_90].z += HuPadSubStkY[0];
        }
        if ((HuPadBtn[0] & PAD_BUTTON_X) != 0) {
            CZoomM[lbl_1_bss_90] += 10.0f;
        }
        if ((HuPadBtn[0] & PAD_BUTTON_Y) != 0) {
            CZoomM[lbl_1_bss_90] -= 10.0f;
        }
        if ((HuPadBtnDown[0] & PAD_BUTTON_A) != 0) {
            OSReport("\nCZoom = %.2f \n", CZoomM[lbl_1_bss_90]);
            OSReport("Center x = %.2f: y = %.2f: z = %.2f \n", CenterM[lbl_1_bss_90].x, CenterM[lbl_1_bss_90].y, CenterM[lbl_1_bss_90].z);
            OSReport("CRot x = %.2f: y = %.2f: z = %.2f \n", CRotM[lbl_1_bss_90].x, CRotM[lbl_1_bss_90].y, CRotM[lbl_1_bss_90].z);
        }
    }
}
