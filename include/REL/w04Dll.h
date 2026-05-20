#ifndef REL_W04DLL_H
#define REL_W04DLL_H

#include "game/board/map_object.h"

#include "dolphin/types.h"

enum {
    MAPOBJ_MAX = 16
};

typedef struct {
    s8 unk00;
    u8 unk01;
} UnkW04BoardData;

extern s32 fn_1_1130(s16 arg0, float arg1, float arg2);

extern void fn_1_12FC(void);
extern void fn_1_15C8(void);
extern void fn_1_1618(void);
extern void fn_1_2058(void);

extern void fn_1_55B4(void);

extern void fn_1_6024(void);
extern void fn_1_9EBC(void);

extern void fn_1_A0F8(void);
extern void fn_1_A1F0(void);
extern void fn_1_BA7C(void);
extern void fn_1_BB00(s16 *arg0);
extern void fn_1_C2BC(void);

extern void fn_1_C7A0(void);
extern void fn_1_C7D4(void);

extern s16 lbl_1_bss_14[MAPOBJ_MAX];
extern BoardMapObject lbl_1_data_0[MAPOBJ_MAX];
extern UnkW04BoardData *lbl_1_bss_0;

#endif
