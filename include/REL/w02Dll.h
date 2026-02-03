#ifndef W02DLL
#define W02DLL

#include "dolphin.h"
#include "game/board/main.h"
#include "game/board/map_object.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/window.h"
#include "game/gamework_data.h"
#include "game/process.h"
#include "math.h"

/* STRUCTS*/
typedef struct m02_dice {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 *unk08;          // ? Holds the objects for the dice faces
    /* 0x0C */ Vec unk0C;           // ? Position of the dice
    /* 0x18 */ s16 unk18;           // ? Holds the minimum value
    /* 0x1A */ s16 unk1A;           // ? Holds the maximum value
    /* 0x1C */ u16 unk1C[3];        // ? Holds the values of up to 3 dice
    /* 0x22 */ s16 unk22;
    /* 0x24 */ float unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 unk2A[0x2];
    /* 0x2C */ Process *unk2C;
    /* 0x30 */ s16 unk30[3];
    /* 0x36 */ s16 unk36[3];
    /* 0x3C */ omObjData *unk3C[3];
    /* 0x48 */ s16 unk48[3];
    /* 0x4E */ u8 unk4E[0x2];
    /* 0x50 */ omObjData *unk50[3];
    /* 0x5C */ u8 unk5C[0x08];
    /* 0x64 */ Vec unk64[2];
    /* 0x7C */ Vec unk7C;
    /* 0x88 */ s32 unk88[3];
    /* 0x94 */ s16 unk94;
    /* 0x96 */ s16 unk96;
    /* 0x98 */ float unk98;
    /* 0x9C */ s16 unk9C;
} m02GenDice;

extern s16 lbl_1_bss_2E;
extern s16 lbl_1_bss_2C;
extern Vec lbl_1_bss_20;
extern Vec lbl_1_bss_14;
extern s16 lbl_1_bss_30[0x10]; // Model List
extern s16 lbl_1_data_286;

// main.c
extern void fn_1_770();
extern void fn_1_72C();
extern s32 fn_1_774();
extern s32 fn_1_800();
extern void fn_1_92C();
extern s32 fn_1_1128();
extern void CreateBoardTextWindow(u32);

void fn_1_1254(m02GenDice *arg0);
void fn_1_1518(m02GenDice *arg0);
s32 fn_1_17F4(m02GenDice *arg0);

// roulette.c
extern void fn_1_D3AC();
extern s32 fn_1_D8C4();
extern void fn_1_DF48();
// unorganized
extern void BootstrapGamble(s32);
extern void fn_1_3BF4();
extern void fn_1_39F4();
extern void fn_1_5CF8();
extern void fn_1_5D28();
extern void fn_1_5F90();
extern void fn_1_79BC(s16 *arg0);
extern void fn_1_8244(u16 arg0);
extern s32 fn_1_9250();
extern void fn_1_93C8(u32 arg0);
extern void fn_1_BC1C();
extern s32 fn_1_BE88();
extern s32 fn_1_C108(s32);
extern void fn_1_CD04(s32);
void fn_1_E41C(void);

#endif // W02DLL
