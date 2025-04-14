#include "dolphin.h"

#include "game/hsfman.h"
#include "game/object.h"

SHARED_SYM extern u8 texMtxTbl[];

#define FABS(x) ((x < 0.0f) ? -(x) : (x))

// types
typedef struct _unkType2 {
    char unk[0x10];
} unkType2;

typedef struct _unkType {
    unkType2 unk[0x10];
} unkType;

typedef struct _unkType3 {
    Vec unk[4];
} unkType3;

typedef struct _unkStruct {
    s16 unk0[3];
    s16 unk6;
    s16 unk8;
} unkStruct; // sizeof 0xC

typedef struct _unkStruct2 {
    char unk[0xE];
    s8 unkE;
} unkStruct2;

typedef struct _unkStruct3 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    char unk8[0x2];
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    float unk1C;
    float unk20;
    float unk24;
    float unk28;
    Vec unk2C;
    Vec unk38;
    Vec unk44;
    Vec unk50;
    u8 unk5C;
    u8 unk5D;
    union {
        s32 *unk60;
        struct {
            s16 unk60s;
            s16 unk62s;
        };
    };
    s16 unk64;
    s16 unk66;
    s16 unk68;
    Vec unk6C;
} unkStruct3;

typedef struct _unkStruct4 {
    u8 unk0;
    Vec unk4;
    Vec unk10;
    Vec unk1C;
    Vec unk28;
    Vec unk34;
    Vec unk40;
    Vec unk4C;
    Vec unk58;
    Vec unk64[3];
    Vec unk88[3];
    Vec unkAC[3];
    Vec unkD0[3];
    float unkF4[3];
    float unk100[3];
    float unk10C[3];
    float unk118[3];
    float unk124[3];
    float unk130;
    float unk134;
    float unk138;
    float unk13C;
    float unk140;
    float unk144;
    float unk148;
} unkStruct4;

typedef struct _unkSubStruct4 {
    s8 unk0;
    s8 unk1;
    char unk2[0x2];
    HsfVector2f unk4[4];
    u8 unk24;
    char unk25[0x3];
    float unk28;
    float unk2C;
} unkSubStruct4;

// taken from m438
typedef struct _unkSubStruct {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    char unk24[0xC];
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    u32 unk34;
    s16 unk38;
    void *unk3C;
    Vec *unk40;
    GXColor *unk44;
    Vec *unk48;
    GXColor unk4C;
    GXColor unk50;
    unkSubStruct4 *unk54;
    u8 unk58;
    char unk59[0x3];
    Vec unk5C;
    Vec unk68;
    s16 unk74[2];
    s16 *unk78;
    s16 *unk7C;
    char unk80[0x14];
} unkSubStruct; /* size = 0x94 */

typedef void (*unkSubStruct2Func)(struct _unkSubStruct2 *);

typedef struct _unkSubStruct2 {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u32 unk8;
    Vec unkC;
    Vec unk18;
    Vec unk24;
    void (*unk30)(struct _unkSubStruct2 *);
    s16 *unk34;
    s16 unk38;
    char unk3A[2];
    unkSubStruct *unk3C;
    char unk40[0x8];
    s16 unk48;
    char *unk4C;
    Vec *unk50;
    GXColor *unk54;
    Vec *unk58;
    unkSubStruct4 *unk5C;
    u8 unk60;
    char unk61[0x3];
    Vec unk64;
    Vec unk70;
    union {
        s16 unk7C[0x20];
        struct {
            s16 unk7Cs;
            s16 unk7Es;
            float unk80;
            float unk84;
            float unk88;
            float unk8C;
            float unk90;
            char unk94[0x28];
        };
    };
} unkSubStruct2; /* size = 0xBC */

typedef struct _unkSubStruct3 {
    AnimData *unk0;
    s16 unk4;
    s16 unk6;
    u32 unk8;
    Vec unkC;
    Mtx unk18;
    GXColor unk48;
    u8 unk4C;
    u8 unk4D;
    s16 unk4E;
    s16 unk50;
    char unk52[0x2];
    float unk54;
    float unk58;
    float unk5C;
    float unk60;
} unkSubStruct3; /* size = 0x64 */

typedef struct _unkStruct5 {
    Mtx unk0;
    s16 unk30;
    s16 unk32;
    s16 unk34;
    s16 unk36;
    s16 unk38;
    s16 unk3A;
    unkSubStruct3 *unk3C;
    unkSubStruct2 *unk40;
} unkStruct5; /* size =  */

typedef struct _unkStruct6 {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    Vec unk24;
} unkStruct6;

// bss
extern unkStruct5 lbl_1_bss_36C;

// prototypes
// main.c
void fn_1_43C(omObjData *object);
void fn_1_4B0(omObjData *object);
void fn_1_7D8(omObjData *object);
void fn_1_14C0(omObjData *object);
void fn_1_15D0(omObjData *object);
void fn_1_1960(omObjData *object);
void fn_1_2B18(omObjData *object);
void fn_1_2C14(omObjData *object);
void fn_1_2E88(float, Vec *, Vec *, float);
void fn_1_3208(omObjData *object);
void fn_1_3640(omObjData *object);
void fn_1_3764(omObjData *object);
void fn_1_3B44(omObjData *object);
void fn_1_4660(omObjData *object);
void fn_1_5B20(unkSubStruct2 *);
void fn_1_6304(omObjData *object);
void fn_1_6368(void);
void *fn_1_63A8(s32);
void fn_1_64DC(void);
AnimBmpData *fn_1_668C(s16);
s16 fn_1_66AC(void);
s32 fn_1_679C(void);
float fn_1_67F0(float, float, float);
void fn_1_6A78(Mtx, Vec *);
void fn_1_7268(float *, float *, float *, s32);
float fn_1_7520(float, float *, float *, float *, s32);
void fn_1_7674(float *, Vec *, Vec *, s32);
void fn_1_7A54(float, Vec *, float *, Vec *, Vec *, s32);
// map.c
void fn_1_95C0(ModelData *, Mtx);
AnimData **fn_1_9734(s16);
void fn_1_9DC8(unkSubStruct2 *);
s16 fn_1_A2D0(u8, u8);
void fn_1_A800(s16);
s16 fn_1_A94C(u32, s16, s16);
void fn_1_ACF4(s16, s16, s16, s16, s16, s16);
void fn_1_AF48(s16);
u8 fn_1_AFC8(s16, u8, s32, s16, s16);
s32 fn_1_B0B8(s16, u8, s16);
void fn_1_B864(s16, float, float, float);
void fn_1_BB4C(s16, float, float, float);
void fn_1_BC9C(s16, float, float, float);
void fn_1_BD08(s16, s16, float, float, float);
void fn_1_C264(s16, u8);
void fn_1_C2D0(s16, s16, u8);
void fn_1_C410(s16, s16, u8, u8);
void fn_1_C58C(s16, s16, u8, float);
void fn_1_C81C(s16, u8);
