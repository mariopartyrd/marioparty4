#include "game/data.h"
#include "game/process.h"
#include "game/printfunc.h"
#include "game/pad.h"
#include "game/object.h"
#include "game/armem.h"
#include "game/wipe.h"
#include "game/gamework_data.h"
#include "game/flag.h"
#include "game/chrman.h"
#include "math.h"
#include "REL/executor.h"
#include "game/board/main.h"

typedef struct struct_data0 {
	s32 unk0;
	s32 unk4;
	s32 unk8;
	s32 unkC;
	s32 unk10;
} StructData0;

StructData0 lbl_1_data_0[] = {
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x00), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x01), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x02), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x03), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x04), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x05), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x06), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x07), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x08), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x09), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0A), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0B), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0C), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0D), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0E), 1, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x0F), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x10), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x11), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x12), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x13), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x14), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x15), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x16), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x17), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x18), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x19), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1A), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1B), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1C), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1D), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1E), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x1F), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x20), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x21), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x22), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x23), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x24), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x25), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x26), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x27), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x28), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x29), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2A), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2B), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2C), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2D), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2E), 0, 0, 0, 1 },
	{ DATA_MAKE_NUM(DATADIR_MSTORY4, 0x2F), 0, 0, 0, 1 },
};

char *lbl_1_data_430[] = {
	"Map1:Fun Party",
	"Map2:Exciting Party",
	"Map3:Adventure Party",
	"Map4:Scary Party",
	"Map5:Resort Party",
	"Map6:Bowser Party"
};

char *lbl_1_data_538[] = {
	"(Map1-Map6) Board Game",
	"(Map1-Map6) Story:Board Clear Event",
	"(Map1-Map6) Story:Board Miss Event",
	"(Map1-Map6) Story:MiniGame Clear Event", 
	"(Map1-Map6) Story:MiniGame Miss Event",
	"(Map6)      Story:BowserParty Inst Event",
	"(Map6)      Story:Ending"
};

s32 lbl_1_data_554[] = {
	0, 0, 0, 0, 0, 0
};

s32 lbl_1_data_56C[] = {
	DATADIR_W01,
	DATADIR_W02,
	DATADIR_W03,
	DATADIR_W04,
	DATADIR_W05,
	DATADIR_W06,
	DATADIR_W10
};

void fn_1_EC(void);
void fn_1_12E8(void);
void fn_1_13A0(void);

s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
Process *lbl_1_bss_0;

void fn_1_0(void)
{
	s32 status = HuDataDirReadAsync(DATADIR_BOARD);
	if(status != -1) {
		while(!HuDataGetAsyncStat(status)) {
			HuPrcVSleep();
		}
	}
	HuAR_MRAMtoARAM(DATADIR_BOARD);
	while(HuARDMACheck()) {
		HuPrcVSleep();
	}
	HuDataDirClose(DATADIR_BOARD);
	if(_CheckFlag(0x1000B)) {
		status = HuDataDirReadAsync(DATADIR_W10);
	} else {
		status = HuDataDirReadAsync(lbl_1_data_56C[GWSystem.board]);
	}
	if(status != -1) {
		while(!HuDataGetAsyncStat(status)) {
			HuPrcVSleep();
		}
	}
	lbl_1_bss_14 = 1;
	HuPrcEnd();
	while(1) {
		HuPrcVSleep();
	}
}

void fn_1_EC(void)
{
	s32 i;
	s32 x = 16;
	s32 y = 40;
	s32 row_h = 10;
	s32 delay = 0;
	float scale = 1.0f;
	GXColor hilite = { 0, 0, 255, 128 };
	OverlayID boardOvlTbl[] = {
		OVL_W01,
		OVL_W02,
		OVL_W03,
		OVL_W04,
		OVL_W05,
		OVL_W06,
		OVL_W10
	};
	WipeColorSet(255, 255, 255);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
	while(1) {
		if(!WipeStatGet()) {
			break;
		}
		HuPrcVSleep();
	}
	while(1) {
		HuPrcVSleep();
		fontcolor = FONT_COLOR_WHITE;
		if(!lbl_1_bss_4) {
			printWin(x,y+(row_h*(lbl_1_bss_8+2))-2, 400, 10*scale, &hilite);
		}
		print8(x, y, scale, "MAP NO");
		print8(x, y+row_h, scale, "--------------------------------------------------");
		for(i=0; i<6; i++) {
			if(!lbl_1_bss_4) {
				print8(x, y+(row_h*(i+2)), scale, "%s", lbl_1_data_430[i]);
			} else if(lbl_1_bss_8 == i) {
				print8(x, y+(row_h*(i+2)), scale, "%s", lbl_1_data_430[i]);
			}
		}
		if(lbl_1_bss_4 == 1) {
			printWin(x, y+(row_h*(lbl_1_bss_C+12))-2, 400, 10*scale, &hilite);
		}
		print8(x, y+(row_h*10), scale, "EVENT NO");
		print8(x, y+(row_h*11), scale, "--------------------------------------------------");
		if(lbl_1_bss_8 == 5) {
			for(i=0; i<7; i++) {
				if(lbl_1_bss_4 <= 1) {
					print8(x, y+(row_h*(i+12)), scale, "%s", lbl_1_data_538[i]);
				} else if(lbl_1_bss_C == i) {
					print8(x, y+(row_h*(i+12)), scale, "%s", lbl_1_data_538[i]);
				}
			}
		} else {
			for(i=0; i<5; i++) {
				if(lbl_1_bss_4 <= 1) {
					print8(x, y+(row_h*(i+12)), scale, "%s", lbl_1_data_538[i]);
				} else if(lbl_1_bss_C == i) {
					print8(x, y+(row_h*(i+12)), scale, "%s", lbl_1_data_538[i]);
				}
			}
		}
		if(lbl_1_bss_4 == 2) {
			printWin(x, y+(row_h*(lbl_1_bss_10+23))-2, 400, 10*scale, &hilite);
		}
		print8(x, y+(row_h*21), scale, "CLEAR FLAG");
		print8(x, y+(row_h*22), scale, "--------------------------------------------------");
		for(i=0; i<6; i++) {
			if(!lbl_1_data_554[i]) {
				print8(x, y+(row_h*(i+23)), scale, "FALSE - %s", lbl_1_data_430[i]);
			} else {
				print8(x, y+(row_h*(i+23)), scale, "TRUE  - %s", lbl_1_data_430[i]);
			}
		}
		if(delay <= 0) {
			switch(lbl_1_bss_4) {
				case 0:
					if(HuPadStkY[0] <= -30) {
						lbl_1_bss_8++;
						if(lbl_1_bss_8 > 5) {
							lbl_1_bss_8 = 0;
						}
						delay = 10;
					} else if(HuPadStkY[0] >= 30) {
						lbl_1_bss_8--;
						if(lbl_1_bss_8 < 0) {
							lbl_1_bss_8 = 5;
						}
						delay = 10;
					}
					break;
					
				case 1:
					if(lbl_1_bss_8 == 5) {
						if(HuPadStkY[0] >= 30) {
							lbl_1_bss_C--;
							if(lbl_1_bss_C < 0) {
								lbl_1_bss_C = 6;
							}
							delay = 10;
						} else if(HuPadStkY[0] <= -30) {
							lbl_1_bss_C++;
							if(lbl_1_bss_C > 6) {
								lbl_1_bss_C = 0;
							}
							delay = 10;
						}
					} else {
						if(HuPadStkY[0] >= 30) {
							lbl_1_bss_C--;
							if(lbl_1_bss_C < 0) {
								lbl_1_bss_C = 4;
							}
							delay = 10;
						} else if(HuPadStkY[0] <= -30) {
							lbl_1_bss_C++;
							if(lbl_1_bss_C > 4) {
								lbl_1_bss_C = 0;
							}
							delay = 10;
						}
					}
					break;
					
				case 2:
					if(HuPadStkY[0] >= 30) {
						lbl_1_bss_10--;
						if(lbl_1_bss_10 < 0) {
							lbl_1_bss_10 = 5;
						}
						delay = 10;
					} else if(HuPadStkY[0] <= -30) {
						lbl_1_bss_10++;
						if(lbl_1_bss_10 > 5) {
							lbl_1_bss_10 = 0;
						}
						delay = 10;
					} else if(HuPadStkX[0] <= -30) {
						lbl_1_data_554[lbl_1_bss_10]++;
						if(lbl_1_data_554[lbl_1_bss_10] > 1) {
							lbl_1_data_554[lbl_1_bss_10] = 0;
						}
						delay = 10;
					} else if(HuPadStkX[0] >= 30) {
						lbl_1_data_554[lbl_1_bss_10]--;
						if(lbl_1_data_554[lbl_1_bss_10] < 0) {
							lbl_1_data_554[lbl_1_bss_10] = 1;
						}
						delay = 10;
					}
					break;
					
				default:
					break;
			}
			if(lbl_1_bss_8 != 5 && lbl_1_bss_C > 4) {
				lbl_1_bss_C = 4;
			}
			if(HuPadBtnDown[0] & PAD_BUTTON_A) {
				lbl_1_bss_4++;
				if(lbl_1_bss_4 == 3) {
					break;
				}
			} else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
				lbl_1_bss_4--;
				if(lbl_1_bss_4 < 0) {
					lbl_1_bss_4 = 0;
				}
			}
			
		} else {
			delay--;
			continue;
		}
	}
	WipeColorSet(255, 255, 255);
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
	while(1) {
		if(!WipeStatGet()) {
			break;
		}
		HuPrcVSleep();
	}
	GWSystem.board = lbl_1_bss_8;
	if(lbl_1_data_554[0] == 1 || lbl_1_bss_8 == 0 && lbl_1_bss_C == 1) {
		_SetFlag(FLAG_ID_MAKE(0, 2));
	} else {
		_ClearFlag(FLAG_ID_MAKE(0, 2));
	}
	if(lbl_1_data_554[1] == 1 || lbl_1_bss_8 == 1 && lbl_1_bss_C == 1) {
		_SetFlag(FLAG_ID_MAKE(0, 3));
	} else {
		_ClearFlag(FLAG_ID_MAKE(0, 3));
	}
	if(lbl_1_data_554[2] == 1 || lbl_1_bss_8 == 2 && lbl_1_bss_C == 1) {
		_SetFlag(FLAG_ID_MAKE(0, 4));
	} else {
		_ClearFlag(FLAG_ID_MAKE(0, 4));
	}
	if(lbl_1_data_554[3] == 1 || lbl_1_bss_8 == 3 && lbl_1_bss_C == 1) {
		_SetFlag(FLAG_ID_MAKE(0, 5));
	} else {
		_ClearFlag(FLAG_ID_MAKE(0, 5));
	}
	if(lbl_1_data_554[4] == 1 || lbl_1_bss_8 == 4 && lbl_1_bss_C == 1) {
		_SetFlag(FLAG_ID_MAKE(0, 6));
	} else {
		_ClearFlag(FLAG_ID_MAKE(0, 6));
	}
	if(lbl_1_data_554[5] == 1 || lbl_1_bss_8 == 5 && lbl_1_bss_C == 1) {
		_SetFlag(FLAG_ID_MAKE(0, 7));
	} else {
		_ClearFlag(FLAG_ID_MAKE(0, 7));
	}
	if(GWSystem.board == BOARD_ID_MAIN6) {
		_SetFlag(FLAG_ID_MAKE(0, 2));
		_SetFlag(FLAG_ID_MAKE(0, 3));
		_SetFlag(FLAG_ID_MAKE(0, 4));
		_SetFlag(FLAG_ID_MAKE(0, 5));
		_SetFlag(FLAG_ID_MAKE(0, 6));
		switch(lbl_1_bss_C) {
			case 0:
				HuPrcChildCreate(fn_1_0, 100, 12288, 0, lbl_1_bss_0);
				do {
					HuPrcVSleep();
				} while(lbl_1_bss_14 != 1);
				CharKill(-1);
				CharARAMOpen(GWPlayerCfg[0].character);
				CharARAMOpen(GWPlayerCfg[1].character);
				CharARAMOpen(GWPlayerCfg[2].character);
				CharARAMOpen(GWPlayerCfg[3].character);
				{
					omOvlHisData *his = omOvlHisGet(0);
					omOvlHisChg(0, OVL_MSTORY3, 0, 0);
					omOvlCallEx(boardOvlTbl[GWSystem.board], 1, 0, 0);
				}
				break;
				
			case 1:
				omOvlGotoEx(OVL_MSTORY2, 1, 1, 0);
				break;
				
			case 2:
				omOvlGotoEx(OVL_MSTORY2, 1, 2, 0);
				break;
				
			case 3:
				GWPlayerCoinWinSet(0, 10);
				omOvlGotoEx(OVL_MSTORY2, 1, 3, 0);
				break;
				
			case 4:
				GWPlayerCoinWinSet(0, 0);
				omOvlGotoEx(OVL_MSTORY2, 1, 3, 0);
				break;
				
			case 5:
				omOvlGotoEx(OVL_MSTORY2, 1, 0, 0);
				break;
				
			case 6:
				omOvlGotoEx(OVL_MSTORY2, 1, 4, 0);
				break;
		}
	} else {
		switch(lbl_1_bss_C) {
			case 0:
				HuPrcChildCreate(fn_1_0, 100, 12288, 0, lbl_1_bss_0);
				do {
					HuPrcVSleep();
				} while(lbl_1_bss_14 != 1);
				CharKill(-1);
				CharARAMOpen(GWPlayerCfg[0].character);
				CharARAMOpen(GWPlayerCfg[1].character);
				CharARAMOpen(GWPlayerCfg[2].character);
				CharARAMOpen(GWPlayerCfg[3].character);
				{
					omOvlHisData *his = omOvlHisGet(0);
					omOvlHisChg(0, OVL_MSTORY3, 0, 0);
					omOvlCallEx(boardOvlTbl[GWSystem.board], 1, 0, 0);
				}
				break;
				
			case 1:
				omOvlGotoEx(OVL_MSTORY, 1, 0, 0);
				break;
				
			case 2:
				omOvlGotoEx(OVL_MSTORY, 1, 1, 0);
				break;
			
			case 3:
				GWPlayerCoinWinSet(0, 10);
				omOvlGotoEx(OVL_MSTORY, 1, 2, 0);
				break;
				
			case 4:
				GWPlayerCoinWinSet(0, 0);
				omOvlGotoEx(OVL_MSTORY, 1, 2, 0);
				break;
		}
	}
	HuPrcEnd();
	while(1) {
		HuPrcVSleep();
	}
}

s32 _prolog(void) {
    const VoidFunc* ctors = _ctors;
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
    fn_1_12E8();
    return 0;
}

void _epilog(void) {
    const VoidFunc* dtors = _dtors;
    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}

void fn_1_12E8(void)
{
	lbl_1_bss_0 = omInitObjMan(62, 8192);
	omGameSysInit(lbl_1_bss_0);
	if((HuPadBtn[0] & PAD_TRIGGER_L) && (HuPadBtn[0] & PAD_TRIGGER_R)) {
		HuPrcChildCreate(fn_1_13A0, 2000, 12288, 0, HuPrcCurrentGet());
	} else {
		HuPrcChildCreate(fn_1_EC, 2000, 12288, 0, HuPrcCurrentGet());
	}
}

char *charNameTbl[] = {
	"Mario",
	"Luigi",
	"Peach",
	"Yoshi",
	"Wario",
	"Donkey",
	"Daisy",
	"Waluigi"
};

void fn_1_13A0(void)
{
	s32 itemno = 0;
	s32 x = 16;
	s32 y = 40;
	s32 row_h = 15;
	float scale = 1.5f;
	float delay = 0;
	GXColor hilite = { 0, 0, 255, 128 };
	CharKill(-1);
	WipeColorSet(255, 255, 255);
	WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
	while(1) {
		if(!WipeStatGet()) {
			break;
		}
		HuPrcVSleep();
	}
	while(1) {
		HuPrcVSleep();
		printWin(x, y+(row_h*3)-2, 400, 10*scale, &hilite);
		print8(x, y, scale, "MpgcStory - ItemDebug");
		print8(x, y+row_h, scale, "--------------------------------------------------");
		if(itemno < 9) {
			print8(x, y+(row_h*3), scale, "Item No    : 0%d", itemno+1);
		} else {
			print8(x, y+(row_h*3), scale, "Item No    : %d", itemno+1);
		}
		print8(x, y+(row_h*5), scale, "Chara Name :");
		fontcolor = 13;
		print8(x, y+(row_h*5), scale, "             %s", charNameTbl[itemno/6]);
		fontcolor = 15;
		print8(x, y+(row_h*6), scale, "Item  Name :");
		if(lbl_1_data_0[itemno].unk10 == 1) {
			fontcolor = 13;
		}
		if(itemno < 9) {
			print8(x, y+(row_h*6), scale, "             ys029a0%d.hsf", itemno+1);
			fontcolor = 15;
		} else {
			print8(x, y+(row_h*6), scale, "             ys029a%d.hsf", itemno+1);
			fontcolor = 15;
		}
		if(delay  == 0.0f) {
			if(HuPadStkX[0] > 30) {
				itemno++;
				delay = 5;
			} else if(HuPadStkX[0] < -30) {
				itemno--;
				delay = 5;
			} else if(HuPadBtnDown[0] & PAD_TRIGGER_R) {
				itemno += 6;
				delay = 5;
			} else if(HuPadBtnDown[0] & PAD_TRIGGER_L) {
				itemno -= 6;
				delay = 5;
			}
			if(HuPadBtnDown[0] & PAD_BUTTON_A) {
				break;
			}
			if(itemno >= 48) {
				itemno -= 48;
			}
			if(itemno <= -1) {
				itemno += 48;
			}
		} else {
			delay--;
		}
	}
	WipeColorSet(255, 255, 255);
	WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
	while(1) {
		if(!WipeStatGet()) {
			break;
		}
		HuPrcVSleep();
	}
	GWPlayerCfg[0].character = itemno/6;
	{
		s32 i;
		for(i=1; i<4; i++) {
			GWPlayerCfg[i].character = GWPlayerCfg[i-1].character+1;
			if(GWPlayerCfg[i].character > CHARNO_MAX ) {
				GWPlayerCfg[i].character = 0;
			}				
		}
		GWStoryCharSet(GWPlayerCfg[0].character);
		GWPlayer[0].character = GWPlayerCfg[0].character;
		GWPlayer[1].character = GWPlayerCfg[1].character;
		GWPlayer[2].character = GWPlayerCfg[2].character;
		GWPlayer[3].character = GWPlayerCfg[3].character;
		CharARAMOpen(GWPlayerCfg[0].character);
		CharARAMOpen(GWPlayerCfg[1].character);
		CharARAMOpen(GWPlayerCfg[2].character);
		CharARAMOpen(GWPlayerCfg[3].character);
		GWSystem.board = itemno%6;
		if(GWSystem.board != BOARD_ID_MAIN6) {
			GWPlayerCoinWinSet(0, 10);
			omOvlGotoEx(OVL_MSTORY, 1, 2, 9999);
		} else {
			GWPlayerCoinWinSet(0, 10);
			omOvlGotoEx(OVL_MSTORY2, 1, 3, 9999);
		}
	}
	HuPrcEnd();
	while(1) {
		HuPrcVSleep();
	}
}
