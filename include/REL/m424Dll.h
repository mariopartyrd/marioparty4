#include "dolphin.h"

#include "game/object.h"

typedef struct _M424DllMainStruct {
    Vec rot;
    Vec center;
    float zoom;
} M424DllMainStruct; // sizeof 1C

typedef struct _M424DllBallStruct2 {
    omObjData *unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u16 unk8;
    u16 unkA;
    Mtx unkC;
    Vec unk3C;
    Vec unk48;
    Vec unk54;
    Vec unk60;
    Vec unk6C;
    Vec unk78;
    Vec unk84;
    u8 unk90;
    u8 unk91;
} M424DllBallStruct2; // sizeof 0x94

extern M424DllBallStruct2 lbl_1_bss_60[9];
extern u8 lbl_1_bss_58;
extern s16 lbl_1_bss_24[4];

float fn_1_1358(float, float);
float fn_1_1470(float, float, float);
omObjData *fn_1_1AB8(Process *);
void fn_1_1B8C(void);
float fn_1_213C(void);
void fn_1_252C(float, s32);
void fn_1_2670(s32, s32);
void fn_1_2720(Process *);
void fn_1_2880(void);
Vec *fn_1_8A00(u8);
s32 fn_1_8A2C(void);
omObjData *fn_1_93F0(Process *);
void fn_1_94A4(void);
s32 fn_1_B804(void);
s32 fn_1_B888(void);
s32 fn_1_B8AC(void);
s32 fn_1_B924(void);
