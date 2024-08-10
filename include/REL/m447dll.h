#ifndef M447DLL_H
#define M447DLL_H

#include "game/animdata.h"
#include "game/process.h"

typedef struct {
    /* 0x00 */ Process* unk00;
    /* 0x04 */ Process* unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34[25];
    /* 0x66 */ char unk66[0xA];
    /* 0x70 */ s32 unk70;
} UnkM447Struct_00; // Size 0x74

typedef struct {
    /* 0x00 */ s16 unk00[22];
    /* 0x2C */ s16 unk2C[6];
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ AnimData* unk50;
    /* 0x54 */ s32 unk54[5];
    /* 0x68 */ s32 unk68[5];
    /* 0x7C */ Process* unk7C;
} UnkM447Struct_06; // Size 0x80

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ Vec unk28;
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ float unk40;
    /* 0x44 */ float unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ float unk50;
    /* 0x54 */ float unk54;
    /* 0x58 */ s16 unk58[23];
    /* 0x86 */ char unk86[2];
    /* 0x88 */ float unk88;
    /* 0x8C */ float unk8C;
    /* 0x90 */ float unk90;
    /* 0x94 */ float unk94;
    /* 0x98 */ float unk98;
    /* 0x9C */ float unk9C;
    /* 0xA0 */ AnimData* unkA0;
    /* 0xA4 */ Process* unkA4;
    /* 0xA8 */ Vec unkA8;
    /* 0xB4 */ float unkB4;
    /* 0xB8 */ float unkB8;
    /* 0xBC */ float unkBC;
    /* 0xC0 */ float unkC0;
    /* 0xC4 */ float unkC4;
    /* 0xC8 */ float unkC8;
} UnkM447Struct_01; // Size 0xCC

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[2];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ Vec unk28;
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ float unk40;
    /* 0x44 */ float unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ float unk4C;
    /* 0x50 */ float unk50;
    /* 0x54 */ char unk54[0xC];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ s16 unk6A[9];
    /* 0x7C */ s16 unk7C[2];
    /* 0x80 */ char unk80[0x24];
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ UnkM447Struct_01* unkA8;
    /* 0xAC */ Process* unkAC;
    /* 0xB0 */ Process* unkB0;
    /* 0xB4 */ Process* unkB4;
} UnkM447Struct_04; // Size 0xB8

UnkM447Struct_06* fn_1_1D90(void);
void fn_1_1E70(UnkM447Struct_06* arg0);
void fn_1_1EB0(UnkM447Struct_06* arg0, s32 arg1);
BOOL fn_1_1EC0(UnkM447Struct_06* arg0);
void fn_1_1ED4(s32 arg0, Vec* arg1);
void fn_1_1F00(UnkM447Struct_06* arg0, s32 arg1);
s32 fn_1_1F9C(UnkM447Struct_06* arg0);
void fn_1_1FEC(UnkM447Struct_06* arg0, s32 arg1);

s32 fn_1_3130(void);
void fn_1_32E0(void);
void fn_1_330C(const Vec* arg0, s32 arg1);
void fn_1_33C8(const Vec* arg0, s32 arg1);
void fn_1_3484(float arg0, s32 arg1);
void fn_1_351C(Vec* arg0);
void fn_1_3540(Vec* arg0);

void fn_1_3F84(void);
UnkM447Struct_04* fn_1_3FC4(s32 arg0);
void fn_1_43CC(UnkM447Struct_04* arg0, s32 arg1);
void fn_1_7A6C(UnkM447Struct_04* arg0);
void fn_1_7AA4(UnkM447Struct_04* arg0, s32 arg1, s32 arg2);

void fn_1_7B54(Vec* arg0, Vec* arg1, s32 arg2, float arg3);
s32 fn_1_80BC(float* arg0, float* arg1, float* arg2);
s32 fn_1_879C(float* arg0, float* arg1, s32 arg2, s32 arg3);

UnkM447Struct_01* fn_1_8DF8(void);
void fn_1_8FF4(UnkM447Struct_01* arg0, s32 arg1);
void fn_1_9004(UnkM447Struct_01* arg0, s32 arg1, s32 arg2);
void fn_1_90FC(s32 arg0);
void fn_1_A230(s32 arg0);
s32 fn_1_A240(void);

extern UnkM447Struct_06* lbl_1_bss_10;
extern UnkM447Struct_00* lbl_1_bss_8;
extern Process* lbl_1_bss_4;
extern UnkM447Struct_04* lbl_1_bss_98[2];
extern const float lbl_1_rodata_648[20];
extern UnkM447Struct_01* lbl_1_bss_A4[5];

#endif
