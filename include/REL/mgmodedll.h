#ifndef MGMODEDLL_H
#define MGMODEDLL_H

#include "game/data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"

#include "game/pad.h"
#include "game/sprite.h"
#include "game/window.h"

typedef struct datalist_model {
    s32 datanum;
    u32 attr;
    s16 type;
    s16 link;
    s16 mot_link;
    Vec pos;
    Vec rot;
    Vec scale;
} DataListModel; // Size 0x34

typedef struct datalist_sprite {
    u32 datanum;
    s16 attr;
    s16 prio;
    float x;
    float y;
    GXColor color;
} DataListSprite; // Size 0x14

typedef struct struct_bss8_24 {
    omObjData *unk0;
    void (*unk4)(omObjData *, ...);
    u8 unk8[0x50];
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    s32 unk70[4];
    s32 unk80[4];
} StructBss8_24; // Size 0x90

typedef struct struct_bss8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    StructBss8_24 unk24[4];
} StructBss8; // Size 0x264

extern s16 lbl_1_bss_2C80[13];
extern s16 lbl_1_bss_2C66[13];
extern s16 lbl_1_bss_2C2C[29];
extern s16 lbl_1_bss_2C24[4];
extern s16 lbl_1_bss_2C1C[4];
extern s16 lbl_1_bss_2C14[4];
extern s16 lbl_1_bss_2BC4[4][10];

extern s16 lbl_1_bss_264C[10][70];
extern s16 lbl_1_bss_2638[10];
extern s16 lbl_1_bss_20C0[10][70];
extern s16 lbl_1_bss_20AC[10];
extern s16 lbl_1_bss_20AA;

extern Process *objman;

extern s16 lbl_1_bss_2E4;

extern s16 lbl_1_bss_2A6;
extern s16 lbl_1_bss_2A4;

extern StructBss8 lbl_1_bss_8;
extern s16 mgModeEvtNo;

extern s16 lbl_1_data_A2[];
extern DataListModel lbl_1_data_490[];
extern DataListSprite lbl_1_data_768[];

s32 fn_1_6D28(void);
s32 fn_1_C0C8(s32 arg0);
void fn_1_D8D0(void);
s32 fn_1_E72C(void);
s32 fn_1_13418(void);

void fn_1_18DF8(Process *arg0, StructBss8 *arg1);

void fn_1_19018(void);
s32 fn_1_194C8(s32 arg0);

s32 fn_1_2530C(s32 arg0, s32 arg1, s32 arg2);
void fn_1_25584(s32 arg0);
void fn_1_25838(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 fn_1_2592C(s32 arg0, s32 arg1, s32 arg2);
s32 fn_1_25CA8(s32 arg0);
void fn_1_25E74(s32 arg0);

void fn_1_267E8(DataListModel *model_list);
void fn_1_26A78(DataListSprite *sprite_list);
void fn_1_26C28(void);
void fn_1_27080(void);
s16 fn_1_271B4(s16 mgNo, s16 x, s16 y);
void fn_1_27418(void);
void fn_1_279FC(s32 coinSkipF);

#endif
