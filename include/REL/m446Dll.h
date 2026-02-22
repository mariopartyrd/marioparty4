#ifndef M446DLL_H
#define M446DLL_H

#include "dolphin/types.h"

#include "game/object.h"
#include "game/process.h"


////// TYPES //////
typedef struct _unkStruct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    char unk8[0x4];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    struct _unkStruct6 *unk20;
    struct _unkStruct9 *unk24;
    struct _unkStruct5 *unk28;
    struct _unkStruct8 *unk2C[2];
    struct _unkStruct4 *unk34;
    struct _unkStruct4 *unk38[23];
    s32 unk94;
    Process *unk98;
} unkStruct;

typedef struct _unkStruct2 {
    void **unk0;
    s32 unk4;
    s32 unk8;
} unkStruct2;

typedef struct _unkStruct3 {
    void *unk0;
    struct _unkStruct3 *unk4;
    struct _unkStruct3 *unk8;
} unkStruct3;

typedef struct _unkStruct4 {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 unk9;
    s16 unkA[2];
    s16 unkE;
    Vec unk10;
    Vec unk1C;
    Vec unk28;
    Vec unk34;
    Vec unk40;
    Vec unk4C;
    float unk58;
    float unk5C;
    float unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    float unk80;
    float unk84;
    float unk88;
    float unk8C;
    float unk90;
    float unk94;
} unkStruct4;

typedef struct _unkStruct5 {
    unkStruct2 *unk0;
    Vec unk4;
} unkStruct5;

typedef struct _unkStruct6 {
    struct _unkStruct7 *unk0;
    s16 unk4;
    s16 unk6;
    unkStruct4 *unk8[21];
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
} unkStruct6;

typedef struct _unkStruct7 {
    struct {
        s8 field00_bit0 : 1;
        s8 field00_bit1 : 1;
        s8 field00_bit2 : 1;
        s8 field00_bit3 : 1;
    };
    s32 unk4;
    s32 unk8;
    s16 unkC[9];
    Vec unk20;
    Vec unk2C;
    Vec unk38;
    float unk44;
    u8 unk48;
    float unk4C;
    float unk50;
} unkStruct7;

typedef struct _unkStruct8 {
    s32 unk0;
    unkStruct6 *unk4;
    unkStruct7 *unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    unkStruct4 *unk2C[3];
    s32 unk38;
    s16 unk3C[2];
    s16 unk40[4];
    Vec unk48;
    Vec unk54;
    float unk60;
    u8 unk64;
    u8 unk65;
    u8 unk66;
    u8 unk67;
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    char unk78[0x4];
    s32 unk7C;
    Vec unk80;
    Vec unk8C;
    s32 unk98;
    Vec unk9C;
    Vec unkA8;
    s32 unkB4;
    float unkB8;
    float unkBC;
    float unkC0;
    float unkC4;
    s32 unkC8;
} unkStruct8;

typedef struct _unkStruct9 {
    s16 unk0[5];
    s16 unkA[2];
    s16 unkE;
    float unk10;
    float unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
} unkStruct9;

typedef struct _unkStruct10 {
    Vec unk0;
    Vec unkC;
    GXColor unk18;
} unkStruct10;

typedef void (*m446Func)(s32);
typedef void (*m446Func1)(unkStruct *);
typedef void (*m446Func4)(unkStruct4 *);
typedef void (*m446Func8)(unkStruct8 *);

////// PROTOTYPES //////
// main.c
void ObjectSetup(void);
void fn_1_13C(omObjData *);
unkStruct *m446FlowCreate(void);
void fn_1_3FC(unkStruct *);
void fn_1_4B4(unkStruct *);
void fn_1_53C(unkStruct *);
void fn_1_958(unkStruct *);
void fn_1_B78(unkStruct *);
void fn_1_C0C(unkStruct *);
void fn_1_CA0(unkStruct *);
s32 fn_1_17FC(unkStruct *);
void fn_1_183C(unkStruct *);
void fn_1_1874(unkStruct *);
void fn_1_18B0(unkStruct *);
void fn_1_19D4(void);
// card.c
unkStruct2 *fn_1_1C64(s32);
void fn_1_1CF8(unkStruct2 *);
s32 fn_1_1D30(unkStruct2 *, void *);
s32 fn_1_1D6C(unkStruct2 *, unkStruct4 **);
s32 fn_1_1DA8(unkStruct2 *, void **);
BOOL fn_1_1DDC(unkStruct2 *);
s32 fn_1_1DEC(unkStruct2 *);
unkStruct3 *fn_1_1DF4(void *);
void fn_1_1E5C(unkStruct3 *);
void fn_1_1E84(unkStruct3 **);
void fn_1_1EC8(unkStruct3 *, unkStruct3 *);
void fn_1_1F04(unkStruct3 *);
void fn_1_1F38(u8 *, u8 *, s32);
void fn_1_1F84(u8 *, s8, s32);
void fn_1_1FC0(u8 *, s32);
s32 fn_1_1FFC(s8 *, s8 *, s32);
s32 fn_1_2064(void);
void fn_1_207C(void);
void fn_1_20D4(void);
unkStruct4 *m446CardCreate(s32);
void fn_1_2688(unkStruct4 *);
void fn_1_272C(unkStruct4 *);
void fn_1_2794(unkStruct4 *);
void fn_1_27FC(unkStruct4 *, Vec *, s32);
void fn_1_2890(unkStruct4 *, Vec *, s32, s32);
void fn_1_2928(unkStruct4 *, Vec *, s32);
void fn_1_29B4(unkStruct4 *, float, s32);
void fn_1_2A1C(unkStruct4 *);
void fn_1_2A58(unkStruct4 *);
void fn_1_2A94(unkStruct4 *);
void fn_1_2AA8(unkStruct4 *);
void fn_1_2D94(unkStruct4 *);
void fn_1_2DA8(unkStruct4 *);
void fn_1_2EC0(unkStruct4 *, s32);
void fn_1_2F64(unkStruct4 *);
// deck.c
unkStruct5 *fn_1_3064(void);
void fn_1_3180(unkStruct2 **);
void fn_1_31D8(unkStruct2 **, unkStruct4 **, s32 *, s32);
void fn_1_34A0(unkStruct5 *, unkStruct4 **, s32, s32);
s32 m446DeckPushCard(unkStruct5 *, unkStruct4 *, s32);
s32 m446DeckPopCard(unkStruct2 **, unkStruct4 **);
void fn_1_38B0(unkStruct2 **);
void fn_1_38E0(u32 arg0);
s32 fn_1_38F0(void);
// table.c
s32 fn_1_3924(void);
void fn_1_393C(void);
void fn_1_3994(void);
unkStruct6 *fn_1_39D0(void);
void fn_1_3B4C(unkStruct6 *);
s32 fn_1_3BF0(unkStruct6 *, unkStruct4 *, s32);
s32 fn_1_3EB4(unkStruct6 *, unkStruct4 *, s32);
s32 fn_1_3FD0(unkStruct6 *, s32, unkStruct4 **);
void fn_1_4000(unkStruct6 *, s32);
s32 fn_1_4088(unkStruct6 *, u8, u8, s32, unkStruct4 **, s32);
void fn_1_46AC(unkStruct6 *);
void fn_1_46D0(unkStruct6 *);
s32 fn_1_4720(unkStruct6 *, s32);
void fn_1_4798(unkStruct6 *);
// player.c
s32 fn_1_480C(void);
void fn_1_4824(void);
void fn_1_487C(void);
unkStruct8 *m446PlayerCreate(s32, unkStruct6 *);
void fn_1_509C(unkStruct8 *);
s32 m446PlayerAppendCard(unkStruct8 *, unkStruct4 *, s32);
s32 m446PlayerRemoveCard(unkStruct8 *, unkStruct4 *, s32);
s32 fn_1_5648(unkStruct8 *, s32, unkStruct4 **);
s32 fn_1_5678(unkStruct8 *, unkStruct4 **, s32);
void fn_1_5B34(unkStruct8 *);
void fn_1_5B48(unkStruct8 *);
void fn_1_5C10(unkStruct8 *);
void fn_1_5C24(unkStruct8 *);
void fn_1_5CEC(unkStruct8 *);
void fn_1_5D00(unkStruct8 *);
void fn_1_5E54(unkStruct8 *, s32);
void fn_1_6074(unkStruct8 *);
void fn_1_6264(unkStruct8 *, Vec *, s32);
void fn_1_62F0(unkStruct8 *, Vec *, s32);
void fn_1_637C(unkStruct8 *, s32);
void fn_1_64BC(unkStruct8 *, s32, s32);
void fn_1_6578(unkStruct8 *);
void fn_1_6620(unkStruct8 *);
// camera.c
s32 fn_1_6778(void);
void fn_1_68D8(void);
void fn_1_68DC(void);
void fn_1_6EA0(Vec *);
void fn_1_6EC4(Vec *);
void fn_1_6EE8(float);
void fn_1_6EF8(Vec *, Vec *, float *, s32);
s32 fn_1_708C(void);
void fn_1_709C(void);
// cursor.c
s32 fn_1_72E0(void);
void fn_1_72F8(void);
void fn_1_7350(void);
unkStruct7 *m446CursorCreate(s32);
void fn_1_76E8(unkStruct7 *);
void fn_1_77C8(unkStruct7 *, u8);
void fn_1_7884(unkStruct7 *);
void fn_1_7908(unkStruct7 *, Vec *, s32);
void fn_1_799C(unkStruct7 *);
void fn_1_7A38(unkStruct7 *);
void fn_1_7AB4(unkStruct7 *);
// stage.c
s32 fn_1_7BF0(void);
void fn_1_7C08(void);
void fn_1_7C60(void);
unkStruct9 *m446StageCreate(void);
void fn_1_83F0(unkStruct9 *);
void fn_1_84AC(unkStruct9 *);
void fn_1_852C(unkStruct9 *);
void fn_1_860C(unkStruct9 *);

#endif
