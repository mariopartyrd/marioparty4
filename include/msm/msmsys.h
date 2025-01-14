#ifndef MSMSYS_H
#define MSMSYS_H

#include "musyx/musyx.h"

#include "dolphin.h"

typedef struct {
    u32 tempDisableFX;
    f32 coloration;
    f32 mix;
    f32 time;
    f32 damping;
    f32 preDelay;
    f32 crosstalk;
} SubStructRev;

typedef struct {
    u32 baseDelay;
    u32 variation;
    u32 period;
} SubStructCh;

typedef struct {
    u32 delay[3];
    u32 feedback[3];
    u32 output[3];
} SubDelay;

typedef struct _unkSubStruct {
    s8 unk0;
    union {
        SubStructRev rev;
        SubStructCh ch;
        SubDelay delay;
    };
} unkSubStruct;

typedef union {
    SND_AUX_REVERBHI revHi;
    SND_AUX_REVERBSTD revStd;
    SND_AUX_CHORUS ch;
    SND_AUX_DELAY delay;
} UnkSndAuxUnion; // Size 0x1E0

typedef struct _unkSubStruct3 {
    char unk[0x4];
    s32 unk4;
    char unk8[0x8];
    s32 unk10; // offset
    u32 unk14; // length
    s32 unk18; // offset
    u32 unk1C; // length
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    char unk3C[4];
    s32 unk40;
    char unk44[4];
    s32 unk48;
    char unk4C[4];
    s32 unk50;
    s32 unk54;
    char unk58[8];
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
    s8 unk3;
    s16 unk4;
    s16 unk6;
    s8 unk8;
    s8 unk9;
    s8 unkA;
    s8 unkB;
    char unkC[2];
    s8 unkE;
    s8 unkF;
    u32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    char unk24[4];
    s8 unk28;
    s8 unk29[10]; // size unknown
} sndInitData;

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ u32 unk04;
    /* 0x08 */ void *unk08;
} UnkStructSys43C; // Size 0xC

typedef struct _unkStruct4 {
    SND_GROUPID unk0;
    s8 unk2;
    s8 unk3;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    char unk14[0xC];
} unkStruct4; // Size 0x20

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02[1]; // unknown array length
} UnkSys3F0Struct; // Size unknown

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
    s8 unk18[2];
    s8 unk1A;
    s8 unk1B;
    UnkSndAuxUnion unk1C[2]; // 0: userA, 1: userB
    s8 unk3DC;
    char unk3DD[3];
    s32 unk3E0;
    u32 unk3E4;
    u32 unk3E8;
    unkStruct4 *unk3EC;
    UnkSys3F0Struct *unk3F0;
    s8 unk3F4;
    unkStruct3 *unk3F8[1]; // unknown array length
    char unk3FC[0x38];
    s8 unk434;
    u8 unk435;
    s8 unk436;
    char unk437[1];
    void *unk438;
    UnkStructSys43C unk43C[1]; // unknown array length
    char unk448[0x24];
    s8 unk46C;
    u8 unk46D;
    s8 unk46E;
    char unk46F[1];
    void *unk470;
    UnkStructSys43C unk474[1]; // unknown array length
    char unk480[0x6C];
    s32 unk4EC;
    BOOL unk4F0;
    AIDCallback unk4F4;
    s32 unk4F8;
} sysData;

#endif
