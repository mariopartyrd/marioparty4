#ifndef M431DLL_H
#define M431DLL_H

#include "game/object.h"

#define rand16() ((rand8() << 8) | (rand8()))

typedef struct bss_12C_inner {
    Vec unk0;
    float unkC;
    s8 unk10;
} Bss12CInner;

typedef struct bss_12c_struct {
    s16 unk0[2];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    Vec unkC;
    float unk18;
    Bss12CInner unk1C[10];
    float unkE4[10][2];
    s16 unk134[2];
    s16 unk138[2];
} Bss12CStruct;

typedef struct bss_61C_work {
    u32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    float unk10;
    struct bss_61C_work *unk14;
    Vec unk18;
    Vec unk24;
    float unk30;
    omObjFunc unk34;
    s16 unk38;
    s16 unk3A;
#if VERSION_PAL
	s16 unk3C_pal;
	s16 unk3E_pal;
#endif
    u32 unk3C;
    s16 unk40;
    s16 unk42;
    Vec unk44;
    s16 unk50;
    s8 unk52;
    u32 unk54;
    s16 unk58;
    s16 unk5A;
    s16 unk5C;
    s16 unk5E[8];
    s16 unk6E;
    s16 unk70;
    s16 unk72;
    u32 unk74;
    s16 unk78;
    s16 unk7A;
    s16 unk7C;
    s16 unk7E;
    s16 unk80;
    s16 unk82;
    s16 unk84;
    s16 unk86;
    float unk88;
    Vec unk8C;
    float unk98;
    Vec unk9C;
    float unkA8;
    s32 unkAC;
    s16 unkB0;
    s16 unkB2;
    s8 unkB4;
    s8 unkB5;
} Bss61CWork;

struct unk_72B4_data_18;
struct work_72B4;

typedef void (*unkHook72B4Data18)(struct unk_72B4_data_18 *);
typedef void (*unkHook72B4)(ModelData *, struct work_72B4 *, Mtx);

typedef struct unk_72B4_data_18 {
    Vec unk0;
    Vec unkC;
    char unk18[16];
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    unkHook72B4Data18 unk30;
    s16 unk34;
    float unk38;
    Vec unk3C;
    Vec unk48;
    s16 unk54;
    s8 unk56;
} Unk72B4Data18;

typedef struct work_72B4 {
    s16 unk0;
    u32 unk4;
    u8 unk8;
    unkHook72B4 unkC;
    AnimData *unk10;
    s16 unk14;
    Unk72B4Data18 *unk18;
    Vec *unk1C;
    HsfVector2f *unk20;
    GXColor *unk24;
    void *unk28;
    Vec unk2C[4];
    HsfVector2f *unk5C;
    float unk60;
    float unk64;
} Work72B4;

extern s32 lbl_1_bss_4;
extern Bss12CStruct lbl_1_bss_12C[4];
extern omObjData *lbl_1_bss_61C[4];
extern float lbl_1_data_1D0;

void fn_1_2000(s16 arg0);
void fn_1_2050(u16 arg0, u16 arg1);
u16 fn_1_2090(u16 arg0);
s16 fn_1_4724(void);
u32 fn_1_4738(s16 arg0, s16 arg1);
s16 fn_1_4B14(s16 arg0, s16 arg1, s16 *arg2);
s16 fn_1_4CDC(s16 arg0, s16 arg1);

void fn_1_5B70(float arg0, float arg1, float arg2, s16 arg3, unkHook72B4Data18 arg4, s16 arg5);

void fn_1_6184(Vec *arg0, Bss12CInner *arg1);
float fn_1_6504(float arg0, float arg1, float arg2);

void fn_1_7ABC(Process *objman);
s32 fn_1_7FB8(s16 arg0);
void fn_1_A7D0(s16 arg0);
void fn_1_A904(s16 arg0);

s32 fn_1_8474(s16 arg0);

#endif
