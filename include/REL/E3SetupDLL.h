#ifndef REL_E3SETUPDLL_H
#define REL_E3SETUPDLL_H

#include "game/animdata.h"
#include "game/object.h"
#include "game/pad.h"

typedef struct e3pad {
	u16 btn;
	u16 btnDown;
	u16 enable;
	u16 unk6;
} E3Pad;

typedef struct mgInterface {
	/* 0x00 */ AnimData *unk_00[2];
	/* 0x08 */ s32 unk08[5];
	/* 0x1C */ s16 group;
	/* 0x1E */ s16 group2;
	/* 0x20 */ s32 unk20[3];
	/* 0x2C */ s16 unk_2C;
	/* 0x30 */ s32 unk30;
} mgInterface;

typedef struct mgPic {
	/* 0x00 */ AnimData *unk_00[2];
	/* 0x08 */ s32 unk08[9];
	/* 0x2C */ s16 unk_2C;
	/* 0x2E */ s32 unk2E[4];
	/* 0x40 */ s16 unk_40;
	/* 0x44 */ s32 unk44[2];
	/* 0x4C */ s32 unk_4C;
	/* 0x50 */ s32 unk50;
} mgPic;

typedef struct mgSelect {
	/* 0x00 */ AnimData *unk_00[4];
	/* 0x10 */ s32 unk10[3];
	/* 0x1C */ s16 unk_1C;
	/* 0x1E */ s16 unk_1E;
	/* 0x20 */ s16 unk_20;
	/* 0x22 */ s16 unk22;
	/* 0x24 */ s32 unk24[2];
	/* 0x2C */ s16 unk_2C;
	/* 0x2E */ s16 unk_2E[4];
	/* 0x36 */ s16 unk36;
	/* 0x38 */ s16 unk_38[4];
	/* 0x40 */ s16 unk40;
	/* 0x42 */ s16 unk_42;
	/* 0x44 */ s16 unk_44;
	/* 0x46 */ s16 unk_46;
} mgSelect;

extern E3Pad e3PadData[4];
extern s16 e3PadCtrl;
extern s16 e3ConfigPlayerCnt;
extern s16 e3ConfigPlayerF;
extern s32 e3ExitEnableF;
extern OMOVL e3NextOvl;
extern s32 e3NextEvent;
extern u32 e3ExitMode;
extern float e3CameraFov;
extern omObjData *e3MenuMainObj;
extern omObjData *e3ViewObj;
extern omObjData *e3OvlWatchObj;
extern omObjData *e3BGObj;

void E3MainInit(void);
void E3MGSelectInit(void);
s16 E3PadRead(void);
u16 E3PadUpdate(s16 player, E3Pad *pad);
void E3OvlWatchInit(omObjData *object);
void E3BGCreate(omObjData *object);
void E3LightInit(void);

#endif
