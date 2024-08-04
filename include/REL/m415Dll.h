#include "dolphin.h"

#include "game/animdata.h"
#include "game/object.h"

// types
typedef struct _unkStruct {
    s16 unk0[3];
    s16 unk6;
    s16 unk8;
} unkStruct; // sizeof 0xC

typedef struct _unkStruct2 {
    char unk[0xE];
    s8 unkE;
} unkStruct2;

// prototypes
void ObjectSetup(void);
void fn_1_43C(omObjData* object);
void fn_1_4B0(omObjData* object);
void fn_1_7D8(omObjData* object);
void fn_1_14C0(omObjData* object);
void fn_1_1524(s16, char*, f32, Mtx);
void fn_1_15D0(omObjData* object);
void fn_1_1960(omObjData* object);
// ...
void fn_1_2B18(omObjData* object); // *
void fn_1_2E88(f32, Vec*, Vec*, f32); // *
void fn_1_3208(omObjData* object); // *
void fn_1_6304(omObjData* object); // *
void fn_1_6368(void); // *
void fn_1_64DC(void);
s16 fn_1_66AC(void);
s32 fn_1_679C(void);
void fn_1_6A78(Mtx, Vec*);
void fn_1_8780(s32, s32);
AnimData** fn_1_9734(s16);
s16 fn_1_A2D0(s32, s32);
void fn_1_A94C(s32, s32, s32);
void fn_1_AFC8(s16, s32, s32, s32, s32);
void fn_1_B0B8(s16, s32, s16);
void fn_1_B634(void);
void fn_1_B864(s16, f32, f32, f32);
void fn_1_BB4C(s16, f32, f32, f32);
void fn_1_BC9C(s16, f32, f32, f32);
void fn_1_C2D0(s16, s32, s32);
void fn_1_C81C(s16, s32);