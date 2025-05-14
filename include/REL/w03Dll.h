#ifndef REL_W03_H
#define REL_W03_H

#include "game/gamework_data.h"
#include "dolphin.h"
#include "REL/executor.h"
#include "game/process.h"
#include "game/window.h"
#include "game/object.h"

enum {
    MAPOBJ_MAX = 12
};

typedef struct w03UnkStruct2{
    u8 unk0 : 1;
} w03UnkStruct2;

typedef struct w03State {
           s8 unk0;
           u8 unk1;
           u8 unk2;
           s8 unk3;
           u16 unk4;
           u16 unk6;
           s16 unk8;
} w03State;

extern w03State* lbl_1_bss_0;
extern s16 lbl_1_bss_C[MAPOBJ_MAX];

#endif
