#ifndef MSMSYS_H
#define MSMSYS_H

#include "dolphin.h"

typedef struct _unkSubStruct {
    s8 unk0;
    union {
        f32 unk4f[9];
        s32 unk4s[9];
    };
} unkSubStruct;

typedef struct _unkSubStruct2 {
    char unk[0x3C];
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    char unk60[0x30];
    s32 unk90;
    s32 unk94;
    s32 unk98;
    char unk9C[0xA0];
    u8 unk13C;
    f32 unk140;
    f32 unk144;
    f32 unk148;
    f32 unk14C;
    f32 unk150;
    char unk154[0x70];
    u8 unk1C4;
    f32 unk1C8;
    f32 unk1CC;
    f32 unk1D0;
    f32 unk1D4;
    f32 unk1D8;
    f32 unk1DC;
} unkSubStruct2; // sizeof unk1E0

typedef struct _unkSubStruct3 {
    char unk[0x4];
    s32 unk4;
    char unk8[0x8];
    s32 unk10; // offset
    u32 unk14; // length
    s32 unk18; // offset
    u32 unk1C; // length
    char unk20[8];
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    char unk3C[4];
    s32 unk40;
    char unk44[4];
    s32 unk48;
    char unk4C[0x14];
} unkSubStruct3; // sizeof 0x60

typedef struct _unkStruct3 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} unkStruct3;

typedef struct _sndInitData {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    char unk3[1];
    s16 unk4;
    s16 unk6;
    s8 unk8;
    char unk9[5];
    s8 unkE;
    s8 unkF;
    u32 unk10;
    s32 unk14;
    char unk18[8];
    s32 unk20;
    char unk24[5];
    s8 unk29[10]; // size unknown
} sndInitData;

typedef struct _sysData {
    s32 unk0;
    s8 unk4;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    s32 unk8;
    unkSubStruct3 *unkC;
    sndInitData *unk10;
    unkSubStruct *unk14;
    s8 unk18;
    s8 unk19;
    s8 unk1A;
    s8 unk1B;
    unkSubStruct2 unk1C; // userA
    unkSubStruct2 unk1FC; // userB
    char unk3DC[0x8];
    s32 unk3E4;
    s32 unk3E8;
    s32 unk3EC;
    s32 unk3F0;
    s8 unk3F4;
    unkStruct3 *unk3F8;
    char unk3FC[0xF0];
    s32 unk4EC;
    BOOL unk4F0;
    AIDCallback unk4F4;
    s32 unk4F8;
} sysData;

#endif
