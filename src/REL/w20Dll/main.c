#include "game/board/model.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "math.h"

#include "REL/w20Dll.h"

s16 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
UnkW20BoardData *lbl_1_bss_0;

s16 lbl_1_data_0 = 0xFFFF;
s16 lbl_1_data_2 = 0xFFFF;
s16 lbl_1_data_4 = 0xFFFF;
s16 lbl_1_data_6 = 0xFFFF;
s16 lbl_1_data_8 = 0xFFFF;
s16 lbl_1_data_A = 0xFFFF;
s32 lbl_1_data_C[] = {
	DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
	DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
	DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
	DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
	DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
	DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
	DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
	DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
};

s32 unkMotTbl[] = { DATA_MAKE_NUM(DATADIR_BGUEST, 42), -1 };

void fn_1_44C(void);
void fn_1_490(void);
void fn_1_494(void);
s32 fn_1_498(void);
void fn_1_4A0(void);
void fn_1_4A4(void);
void fn_1_4A8(void);
s32 fn_1_4AC(s16 arg0, float arg8, float arg9);

void BoardCreate(void)
{
    s32 sp8;
    s32 var_r31;

    var_r31 = GWSystem.board;
    sp8 = var_r31;
    lbl_1_bss_0 = (UnkW20BoardData *)GWSystem.board_data;
    lbl_1_bss_0->unk_00 = 0;
    lbl_1_bss_0->unk_04 = 0;
    lbl_1_bss_0->unk_06 = 0;
    BoardSpaceInit(DATA_MAKE_NUM(DATADIR_W20, 0));
    lbl_1_data_0 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W20, 0x01), NULL, 0);
    fn_8006DDE8(lbl_1_data_0, -1.0f);
    BoardModelPosSet(lbl_1_data_0, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_0, 0, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_data_0, 1.0f);
    lbl_1_data_2 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W20, 0x02), NULL, 0);
    fn_8006DDE8(lbl_1_data_2, -1.0f);
    BoardModelPosSet(lbl_1_data_2, 0.0f, 0.0f, 0.0f);
    BoardModelMotionStart(lbl_1_data_2, 0, 0x40000001);
    lbl_1_data_6 = BoardModelCreate(0x20029, unkMotTbl, 0);
    BoardModelMotionStart(lbl_1_data_6, 1, 0x40000001);
    lbl_1_data_8 = BoardModelCreate(0x20029, unkMotTbl, 0);
    BoardModelMotionStart(lbl_1_data_8, 1, 0x40000001);
    BoardLightHookSet(fn_1_44C, fn_1_490);
    BoardSpaceWalkEventFuncSet(fn_1_498);
    BoardSpaceWalkMiniEventFuncSet(fn_1_4A8);
    BoardSpaceLandEventFuncSet(fn_1_494);
    BoardShopHostSet(lbl_1_data_6);
    BoardLotteryHostSet(lbl_1_data_8);
    BoardStarHostSet(lbl_1_data_6);
}

void BoardDestroy(void)
{
    if (lbl_1_data_6 != -1) {
        BoardModelKill(lbl_1_data_6);
        lbl_1_data_6 = -1;
    }
    if (lbl_1_data_0 != -1) {
        BoardModelKill(lbl_1_data_0);
        lbl_1_data_0 = -1;
    }
    if (lbl_1_data_2 != -1) {
        BoardModelKill(lbl_1_data_2);
        lbl_1_data_2 = -1;
    }
    BoardSpaceDestroy();
}

void fn_1_44C(void)
{
    s16 var_r31;

    var_r31 = BoardModelIDGet(lbl_1_data_0);
    Hu3DModelLightInfoSet(var_r31, 1);
}

void fn_1_490(void) { }

void fn_1_494(void) { }

s32 fn_1_498(void) { return 0; }

void fn_1_4A0(void) { }

void fn_1_4A4(void) { }

void fn_1_4A8(void) { }

s32 fn_1_4AC(s16 arg0, float arg8, float arg9)
{
    float var_f29;
    float var_f31;
    s32 var_r31;

    var_r31 = 0;
    var_f31 = BoardModelRotYGet(arg0);
    arg8 = fmod(arg8, 360.0f);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (arg8 < 0.0f) {
        arg8 += 360.0f;
    }
    if (var_f31 != arg8) {
        var_f29 = arg8 - var_f31;
        if (var_f29 < 0.0f) {
            var_f29 += 360.0f;
        }
        if (var_f29 < 180.0f) {
            if (var_f29 > arg9) {
                var_f31 += arg9;
            } else {
                var_f31 = arg8;
            }
        } else if ((360.0f - var_f29) > arg9) {
            var_f31 -= arg9;
        } else {
            var_f31 = arg8;
        }
        if (var_f31 < 0.0f) {
            var_f31 += 360.0f;
        }
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        BoardModelRotYSet(arg0, var_f31);
    } else {
        var_r31 = 1;
    }
    return var_r31;
}
