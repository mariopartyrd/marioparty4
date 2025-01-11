#include "REL/mstory2Dll.h"
#include "game/armem.h"
#include "game/board/main.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/objsub.h"

typedef struct struct_data850 {
	s32 unk0;
	s32 unk4;
	s32 unk8;
	s32 unkC;
	s32 unk10;
} StructData850;

StructData850 lbl_1_data_850[] = {
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

s32 lbl_1_data_C10[2][2] = { 20, 70, 1, 1 };
s32 lbl_1_data_C20 = -1;
s32 lbl_1_data_C24[2] = { -1, -1 };

typedef struct {
    /* 0x000 */ s32 unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ char unk18[0x18];
    /* 0x030 */ StructFn357C unk30[4];
    /* 0x100 */ s32 unk100;
} StructBss860; // Size 0x104

StructBss860 lbl_1_bss_860;
StructBss16C lbl_1_bss_838;
StructBss16C lbl_1_bss_810;
StructBss16C lbl_1_bss_7E8;
StructBss16C lbl_1_bss_7C0;
StructBss16C lbl_1_bss_798;
BOOL lbl_1_bss_794;
Process *lbl_1_bss_790;

void fn_1_13BB8(void);
void fn_1_13FB4(omObjData* arg0, StructBss16C* arg1);
void fn_1_140A0(omObjData* arg0, StructBss16C* arg1);
void fn_1_1449C(void);
void fn_1_14A9C(int arg0, int arg1, int arg2, int arg3, int arg4);
void fn_1_14B48(omObjData* arg0, StructBss16C* arg1);
void fn_1_14C40(void);
void fn_1_15134(int arg0, int arg1, int arg2, int arg3, int arg4);
void fn_1_151E0(omObjData* arg0, StructBss16C* arg1);
void fn_1_152C4(omObjData* arg0, StructBss16C* arg1);
void fn_1_153A8(void);
void fn_1_15668(int arg0);
void fn_1_159F0(void);
void fn_1_15CDC(void);
void fn_1_15D68(void);
void fn_1_15E58(void);
void fn_1_15F70(void);

void fn_1_123C8(void)
{
    int i;
    while(1) {
        do {
            HuPrcVSleep();
        } while(lbl_1_data_C20 == -1 || lbl_1_data_C24[0] == -1 || lbl_1_data_C24[1] == -1 || lbl_1_data_C24[0] != Hu3DMotionIDGet(lbl_1_data_C20));
        for(i=0; i<2; i++) {
            if(lbl_1_data_C10[1][i] != -1) {
                if(Hu3DMotionTimeGet(lbl_1_data_C20) >= lbl_1_data_C10[0][i]) {
                    OSReport("KE-System  TIME:%d\n", lbl_1_data_C10[0][i]);
                    HuAudFXPlay(81);
                    lbl_1_data_C10[1][i] = -1;
                }
            }
        }
        if(Hu3DMotionTimeGet(lbl_1_data_C20) <= 10) {
            for(i=0; i<2; i++) {
                lbl_1_data_C10[1][i] = 1;
            }
        }
    }
}

void fn_1_1256C(Process* arg0, s32 arg1)
{
    lbl_1_bss_790 = arg0;
    lbl_1_bss_860.unk0C = arg1;
    fn_1_C30();
    lbl_1_bss_860.unk100 = fn_1_3668(255);
    fn_1_2828(lbl_1_bss_790, fn_1_15CDC);
    fn_1_3754();
    fn_1_15668(arg1);
    HuPrcChildCreate(fn_1_1449C, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_14C40, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_153A8, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_159F0, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_13BB8, 100, 8192, 0, HuPrcCurrentGet());
}

void fn_1_12690(omObjData *object)
{
    if(object->work[2]) {
        object->work[2]--;
        return;
    }
    if(object->work[2] == 0 && Hu3DMotionEndCheck(object->model[1])) {
        fn_1_1DFC(object, 1, object->work[1], 15, 1);
        object->work[0] = object->work[1] = object->work[2] = 0;
    }
}

void fn_1_1271C(void)
{
    int posX = 16;
    int posY = 40;
    GXColor winColor = { 0, 0, 128, 128 };
    int i;
    while(1) {
        fn_1_BC8();
        printWin(posX, posY, 220, 130, &winColor);
        if(lbl_1_bss_838.unk04 == NULL) {
            print8(posX, posY, 1, "PROC_MAIN   -> FALSE");
        } else {
            print8(posX, posY, 1, "PROC_MAIN   -> TRUE");
        }
        if(lbl_1_bss_810.unk04 == NULL) {
            print8(posX, posY+10, 1, "PROC_MAP    -> FALSE");
        } else {
            print8(posX, posY+10, 1, "PROC_MAP    -> TRUE");
        }
        if(lbl_1_bss_7E8.unk04 == NULL) {
            print8(posX, posY+20, 1, "PROC_KOOPA  -> FALSE");
        } else {
            print8(posX, posY+20, 1, "PROC_KOOPA  -> TRUE");
        }
        if(lbl_1_bss_7C0.unk04 == NULL) {
            print8(posX, posY+30, 1, "PROC_MKOOPA -> FALSE");
        } else {
            print8(posX, posY+30, 1, "PROC_MKOOPA -> TRUE");
        }
        if(lbl_1_bss_798.unk04 == NULL) {
            print8(posX, posY+40, 1, "PROC_PLAYER -> FALSE");
        } else {
            print8(posX, posY+40, 1, "PROC_PLAYER -> TRUE");
        }
        print8(posX, posY+60, 1, "P:%d W:%d", lbl_1_bss_860.unk00, lbl_1_bss_860.unk0C);
        print8(posX, posY+80, 1, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for(i=0; i<4; i++) {
            print8(posX, posY+90+(i*10), 1, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i, lbl_1_bss_860.unk30[i].unk00, lbl_1_bss_860.unk30[i].unk04, lbl_1_bss_860.unk30[i].unk08, lbl_1_bss_860.unk30[i].unk0C, lbl_1_bss_860.unk30[i].unk14, lbl_1_bss_860.unk30[i].unk10);
        }
    }
}

void fn_1_12AC8(void)
{
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet());
    fn_1_BE8(30);
}

void fn_1_12B10(void)
{
    lbl_1_bss_860.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_860.unk0C);
    HuAudFXPlay(lbl_1_data_0[6][1]);
    fn_1_14A9C(4, 1, 15, 0, 1);
    fn_1_1D4C(lbl_1_bss_860.unk04, lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10, 0);
    fn_1_6D78(lbl_1_bss_860.unk04, 0x1F0014, 0, lbl_1_bss_7E8.unk00->model[1]);
    HuAudFXPlay(lbl_1_data_0[6][2]);
    fn_1_1DFC(lbl_1_bss_7E8.unk00, 1, 5, 10, 1);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x1F0015);
    fn_1_1AFC(lbl_1_bss_860.unk04, -1);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x250004);
    fn_1_15134(1, -1, 15, 1, 0);
    fn_1_1A94(lbl_1_bss_860.unk04);
    lbl_1_bss_7E8.unk04 = (void *)fn_1_14B48;
    fn_1_BE8(60);
    fn_1_1DFC(lbl_1_bss_798.unk00, 1, 4, 15, 0);
    fn_1_BE8(16);
    while(1) {
        fn_1_BC8();
        if(Hu3DMotionTimeGet(lbl_1_bss_798.unk00->model[1]) >= 20) {
            break;
        }
    }
    Hu3DMotionSpeedSet(lbl_1_bss_798.unk00->model[1], 0);
    while(1) {
        fn_1_BC8();
        if(lbl_1_bss_7E8.unk04 == NULL) {
            break;
        }
    }
    fn_1_BE8(30);
    fn_1_3854(&lbl_1_bss_24);
    fn_1_2750(fn_1_15D68);
    lbl_1_bss_7C0.unk04 = (void *)fn_1_152C4;
    fn_1_BE8(80);
    Hu3DMotionSpeedSet(lbl_1_bss_798.unk00->model[1], 1);
    fn_1_1DFC(lbl_1_bss_798.unk00, 1, 1, 15, 1);
    while(1) {
        fn_1_BC8();
        if(lbl_1_bss_7C0.unk04 == NULL) {
            break;
        }
    }
}

void fn_1_12DD4(void)
{
    lbl_1_bss_860.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_860.unk0C);
    lbl_1_bss_78[0] = HuAudSeqPlay(56);
    HuAudFXPlay(lbl_1_data_0[5][0]);
    fn_1_1DFC(lbl_1_bss_7C0.unk00, 1, 4, 15, 0);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x1F0016);
    fn_1_1AFC(lbl_1_bss_860.unk04, -1);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x250004);
    HuAudFXPlay(lbl_1_data_0[5][0]);
    fn_1_1DFC(lbl_1_bss_7C0.unk00, 1, 3, 15, 1);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x1F0017);
    fn_1_1AFC(lbl_1_bss_860.unk04, -1);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x250004);
    HuAudFXPlay(lbl_1_data_0[5][0]);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x1F0018);
    fn_1_1AFC(lbl_1_bss_860.unk04, -1);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x250004);
    fn_1_1DFC(lbl_1_bss_7C0.unk00, 1, 1, 15, 1);
    fn_1_1A94(lbl_1_bss_860.unk04);
    fn_1_BE8(60);
    lbl_1_bss_860.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_860.unk0C);
    HuAudFXPlay(lbl_1_data_0[5][0]);
    fn_1_1DFC(lbl_1_bss_7C0.unk00, 1, 3, 15, 1);
    fn_1_1D4C(lbl_1_bss_860.unk04, lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10, 0);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x1F0019);
    fn_1_1AFC(lbl_1_bss_860.unk04, -1);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x250004);
    HuAudFXPlay(lbl_1_data_0[5][1]);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x1F001A);
    fn_1_1AFC(lbl_1_bss_860.unk04, -1);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x250004);
    lbl_1_bss_7C0.unk04 = (void *)fn_1_151E0;
    fn_1_1D18(lbl_1_bss_860.unk04, 0x1F001B);
    fn_1_1AFC(lbl_1_bss_860.unk04, -1);
    fn_1_1D18(lbl_1_bss_860.unk04, 0x250004);
    fn_1_1A94(lbl_1_bss_860.unk04);
    while(1) {
        fn_1_BC8();
        if(lbl_1_bss_7C0.unk04 == NULL) {
            break;
        }
    }
}

void fn_1_13150(omObjData* arg0, StructBss16C* arg1)
{
    int streamNo = HuAudSStreamPlay(7);
    while(1) {
        fn_1_BC8();
        if(HuAudSStreamStatGet(streamNo) == 0) {
            break;
        }
    }
    HuAudSeqPause(lbl_1_bss_78[0], 0, 1000);
    arg1->unk04 = NULL;
}

void fn_1_131C0(omObjData* arg0, StructBss16C* arg1)
{
    int presentSe = (lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10*6)+5;
    fn_1_BE8(150);
    OSReport("########## PRESENT_SE : %d\n", presentSe);
    HuAudFXPlay(presentSe+2260);
    fn_1_1DFC(lbl_1_bss_810.unk00, 7, 7, 1, 0);
    arg1->unk04 = NULL;
}

void fn_1_13264(void)
{
    int i;
    fn_1_1DFC(lbl_1_bss_798.unk00, 1, 2, 15, 1);
    for(i=0; i<30; i++) {
        fn_1_BC8();
        if(lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10 != 5) {
            Hu3DData[lbl_1_bss_798.unk00->model[1]].pos.x = fn_1_864(120, 80, i, 30);
        }
        Hu3DData[lbl_1_bss_798.unk00->model[1]].rot.y = fn_1_864(-60, -90, i, 30);
    }
    fn_1_1DFC(lbl_1_bss_798.unk00, 1, 5, 5, 0);
    fn_1_BE8(10);
    while(1) {
        fn_1_BC8();
        if(Hu3DMotionTimeGet(lbl_1_bss_798.unk00->model[1]) >= 30) {
            break;
        }
    }
    Hu3DModelPosSet(lbl_1_bss_810.unk00->model[5], 0, 0, 0);
    Hu3DModelHookSet(lbl_1_bss_798.unk00->model[1], CharModelHookNameGet(lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10, 1, 1), lbl_1_bss_810.unk00->model[5]);
    fn_1_BE8(60);
    lbl_1_bss_810.unk04 = (void *)fn_1_13FB4;
    HuAudFXPlay(163);
    HuAudCharVoicePlay(lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10, 296);
    fn_1_1DFC(lbl_1_bss_810.unk00, 6, 6, 0, 0);
    Hu3DModelAttrReset(lbl_1_bss_810.unk00->model[6], 1);
    Hu3DModelAttrSet(lbl_1_bss_810.unk00->model[5], 1);
    fn_1_1DFC(lbl_1_bss_798.unk00, 1, 6, 5, 0);
    HuAudSeqPause(lbl_1_bss_78[0], 1, 1000);
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    while(1) {
        fn_1_BC8();
        if(!WipeStatGet()) {
            break;
        }
    }
    Hu3DMotionSpeedSet(lbl_1_bss_798.unk00->model[1], 0);
    Hu3DMotionTimeSet(lbl_1_bss_798.unk00->model[1], 50);
    Hu3DModelAttrReset(lbl_1_bss_810.unk00->model[7], 1);
    Hu3DModelAttrReset(lbl_1_bss_810.unk00->model[8], 1);
    fn_1_1DFC(lbl_1_bss_810.unk00, 8, 8, 0, 1);
    fn_1_BE8(30);
    HuAudFXPlay(169);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    while(1) {
        fn_1_BC8();
        if(!WipeStatGet()) {
            break;
        }
    }
    fn_1_3854(&lbl_1_bss_24);
    fn_1_2750(fn_1_15F70);
    fn_1_BE8(60);
    lbl_1_bss_798.unk04 = (void *)fn_1_131C0;
    lbl_1_bss_860.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_860.unk0C);
    lbl_1_bss_7C0.unk04 = (void *)fn_1_13150;
    fn_1_1D4C(lbl_1_bss_860.unk04, (lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10*6)+0x32000B, 0);
    fn_1_6DBC(lbl_1_bss_860.unk04, 0x320086, 0, 300);
    fn_1_1D18(lbl_1_bss_860.unk04,0x250004);
    fn_1_1A94(lbl_1_bss_860.unk04);
    fn_1_3854(&lbl_1_bss_24);
    fn_1_2750(fn_1_15E58);
    lbl_1_bss_810.unk04 = (void *)fn_1_140A0;
    fn_1_BE8(30);
    Hu3DMotionSpeedSet(lbl_1_bss_798.unk00->model[1], 0.1f);
    fn_1_BE8(180);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
}

void fn_1_13828(void)
{
    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_BE8(60);
    SLCommonSet();
    SLSaveBoardStory();
    if (SLSaveFlagGet() == 1) {
        SLSave();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_794 = TRUE;
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_138CC(void)
{
    omOvlHisData* var_r31;

    msmSeStopAll(FALSE, 1000);
    do {
        fn_1_BC8();
    } while (WipeStatGet() != 0);
    CharModelKill(-1);
    HuAudFXAllStop();
    HuAudSStreamAllStop();
    GWMGAvailSet(omMgIndexGet(58)+401);
    GWGameStat.present[lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10 * 6 + 5] = 1;
    OSReport("########## PRESENTFLG CHR:%d, MAP:5, PRESENT:%d\n", lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10, lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10 * 6 + 5);
    var_r31 = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MSTORY2, 20, var_r31->stat);
    omOvlCallEx(OVL_PRESENT, 1, lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10 * 6 + 5 + 1, 0);
}

void fn_1_13A18(omObjData* arg0, StructBss16C* arg1)
{
    int temp = 0;
    fn_1_12AC8();
    fn_1_12B10();
    fn_1_12DD4();
    fn_1_13264();
    fn_1_138CC();
    arg1->unk04 = 0;
}

void fn_1_13BB8(void)
{
    omObjData *obj;
    lbl_1_bss_838.unk00 = obj = omAddObjEx(lbl_1_bss_790, 256, 16, 16, -1, NULL);
    lbl_1_bss_838.unk04 = (void *)fn_1_13A18;
    lbl_1_bss_838.unk00->data = &lbl_1_bss_838;
    while(1) {
        fn_1_BC8();
        if(lbl_1_bss_838.unk04 != NULL) {
            lbl_1_bss_838.unk04(obj, &lbl_1_bss_838);
        }
    }
}

void fn_1_13C6C(omObjData* object)
{
    s32 charNo;
    charNo = lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10;
    object->model[7] = Hu3DModelCreateFile(lbl_1_data_850[charNo * 6 + 5].unk0);
    object->motion[7] = Hu3DMotionIDGet(object->model[7]);
    Hu3DModelPosSet(object->model[7], 0, 180, 825);
    Hu3DModelAttrSet(object->model[7], 1);
    Hu3DModelShadowSet(object->model[7]);
    fn_1_1DFC(object, 7, 7, 0, 2);
    HuDataDirClose(DATADIR_MSTORY4);
    object->model[1] = Hu3DModelCreateFile(0x660052);
    object->motion[1] = Hu3DMotionIDGet(object->model[1]);
    Hu3DModelShadowMapObjSet(object->model[1], "base_story-base");
    fn_1_1DFC(object, 1, 1, 0, 1);
    object->model[2] = Hu3DModelCreateFile(0x660053);
    object->motion[2] = Hu3DJointMotionFile(object->model[2], 0x660054);
    object->motion[3] = Hu3DJointMotionFile(object->model[2], 0x660055);
    fn_1_1DFC(object, 2, 3, 0, 2);
    object->model[5] = Hu3DModelCreateFile(0x66005B);
    Hu3DModelPosSet(object->model[5], 0, 125, 800);
    Hu3DModelAttrSet(object->model[5], 1);
    Hu3DModelShadowSet(object->model[5]);
    object->model[6] = Hu3DModelCreateFile(0x66005D);
    object->motion[6] = Hu3DMotionIDGet(object->model[6]);
    Hu3DModelPosSet(object->model[6], 25, 125, 900);
    Hu3DModelAttrSet(object->model[6], 1);
    fn_1_1DFC(object, 6, 6, 0, 2);
    object->model[8] = Hu3DModelCreateFile(0x66005F);
    object->motion[8] = Hu3DMotionIDGet(object->model[8]);
    Hu3DModelAttrSet(object->model[8], 1);
    fn_1_1DFC(object, 8, 8, 0, 1);
}


void fn_1_13FB4(omObjData* arg0, StructBss16C* arg1)
{
    Mtx matrix;
    Hu3DData[arg0->model[7]].pos.y = fn_1_B08(180, 185, arg1->unk08++, 360);
    Hu3DModelObjMtxGet(arg0->model[7], "effect", matrix);
    Hu3DModelPosSet(arg0->model[8], matrix[0][3], matrix[1][3], matrix[2][3]);
    if(arg1->unk08 >= 360) {
        arg1->unk08 = 0;
    }
}

void fn_1_140A0(omObjData* arg0, StructBss16C* arg1)
{
    Mtx matrix;
    Hu3DData[arg0->model[7]].pos.y += arg1->unk0C/100.0f;
    Hu3DModelObjMtxGet(arg0->model[7], "effect", matrix);
    Hu3DModelPosSet(arg0->model[8], matrix[0][3], matrix[1][3], matrix[2][3]);
    arg1->unk0C += 2;
}

void fn_1_1416C(omObjData* arg0, StructBss16C* arg1)
{
    int i;
    Vec pos;
    float rotY;
    Hu3DModelPosSet(arg0->model[5], -180, 100, 800);
    Hu3DModelRotSet(arg0->model[5], 0, 0, 0);
    Hu3DModelAttrReset(arg0->model[5], 1);
    for(i=0; i<60; i++) {
        fn_1_BC8();
        if(i == 30) {
            HuAudFXPlay(151);
        }
        if(i <= 30) {
            pos.y = fn_1_A4C(0, 100, i+30, 60);
            pos.x = fn_1_864(-180, -45, i, 30);
            rotY = fn_1_984(0, -90, i, 30);
        } else {
            pos.x = fn_1_864(-45, 0, i-30, 30);
            pos.y = fn_1_A4C(0, 25, i-30, 30);
            rotY = fn_1_984(-90, -360, i-30, 30);
        }
        Hu3DModelPosSet(arg0->model[5], pos.x, pos.y, 800);
        Hu3DModelRotSet(arg0->model[5], 0, rotY, 0);
    }
    arg1->unk04 = NULL;
}

void fn_1_1449C(void)
{
    omObjData *obj;
    lbl_1_bss_810.unk00 = obj = omAddObjEx(lbl_1_bss_790, 256, 16, 16, -1, NULL);
    lbl_1_bss_810.unk04 = NULL;
    lbl_1_bss_810.unk00->data = &lbl_1_bss_810;
    fn_1_13C6C(obj);
    while(1) {
        fn_1_BC8();
        if(lbl_1_bss_810.unk04 != NULL) {
            lbl_1_bss_810.unk04(obj, &lbl_1_bss_810);
        }
    }
}

void fn_1_14868(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(0x660062);
    object->motion[1] = Hu3DJointMotionFile(object->model[1], 0x660063);
    object->motion[2] = Hu3DJointMotionFile(object->model[1], 0x660064);
    object->motion[3] = Hu3DJointMotionFile(object->model[1], 0x66006E);
    object->motion[4] = Hu3DJointMotionFile(object->model[1], 0x66006F);
    object->motion[5] = Hu3DJointMotionFile(object->model[1], 0x660069);
    Hu3DModelPosSet(object->model[1], -180, 0, 800);
    Hu3DModelRotSet(object->model[1], 0, 60, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 3, 0, 1);
    lbl_1_data_C20 = object->model[1];
    lbl_1_data_C24[0] = object->motion[2];
    lbl_1_data_C24[1] = object->motion[2];
    HuPrcChildCreate(fn_1_123C8, 100, 8192, 0, HuPrcCurrentGet());
}

void fn_1_14A9C(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_7E8.unk00, 1, arg0, arg2, arg3);
    if(arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_7E8.unk00->work[0] = arg4;
    lbl_1_bss_7E8.unk00->work[1] = arg1;
    lbl_1_bss_7E8.unk00->work[2] = arg2+1;
}

void fn_1_14B48(omObjData* arg0, StructBss16C* arg1)
{
    Vec pos = { -1000, 0, 810 };
    lbl_1_bss_810.unk04 = (void *)fn_1_1416C;
    fn_1_1DFC(arg0, 1, 2, 15, 1);
    fn_1_2D00(arg0, 1, pos, -1, 45, 10);
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_14C40(void)
{
    omObjData *obj;
    lbl_1_bss_7E8.unk00 = obj = omAddObjEx(lbl_1_bss_790, 256, 16, 16, -1, NULL);
    lbl_1_bss_7E8.unk04 = NULL;
    lbl_1_bss_7E8.unk00->data = &lbl_1_bss_810;
    fn_1_14868(obj);
    while(1) {
        fn_1_BC8();
        if(lbl_1_bss_7E8.unk04 != NULL) {
            lbl_1_bss_7E8.unk04(obj, &lbl_1_bss_7E8);
        }
        if(obj->work[0]) {
            if(obj->work[2]) {
                obj->work[2]--;
            } else if(obj->work[2] == 0 && Hu3DMotionEndCheck(obj->model[1])) {
                fn_1_1DFC(obj, 1, obj->work[1], 15, 1);
                obj->work[0] = obj->work[1] = obj->work[2] = 0;
            }
        }
    }
}

void fn_1_14F6C(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(0x66007D);
    object->motion[1] = Hu3DJointMotionFile(object->model[1], 0x66007E);
    object->motion[2] = Hu3DJointMotionFile(object->model[1], 0x660080);
    object->motion[3] = Hu3DJointMotionFile(object->model[1], 0x660081);
    object->motion[4] = Hu3DJointMotionFile(object->model[1], 0x660086);
    Hu3DModelPosSet(object->model[1], -600, 0, 800);
    Hu3DModelRotSet(object->model[1], 0, 60, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
    CharModelEffectNpcInit(object->model[1], object->motion[2], 1, 13);
}

void fn_1_15134(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_7C0.unk00, 1, arg0, arg2, arg3);
    if(arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_7C0.unk00->work[0] = arg4;
    lbl_1_bss_7C0.unk00->work[1] = arg1;
    lbl_1_bss_7C0.unk00->work[2] = arg2+1;
}

void fn_1_151E0(omObjData* arg0, StructBss16C* arg1)
{
    Vec pos = { -800, 0, 800 };
    fn_1_1DFC(arg0, 1, 2, 15, 1);
    fn_1_2D00(arg0, 1, pos, 60, 60, 10);
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_152C4(omObjData* arg0, StructBss16C* arg1)
{
    Vec pos = { -120, 0, 800 };
    fn_1_1DFC(arg0, 1, 2, 15, 1);
    fn_1_2D00(arg0, 1, pos, 60, 60, 10);
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_153A8(void)
{
    omObjData *obj;
    lbl_1_bss_7C0.unk00 = obj = omAddObjEx(lbl_1_bss_790, 256, 16, 16, -1, NULL);
    lbl_1_bss_7C0.unk04 = NULL;
    lbl_1_bss_7C0.unk00->data = &lbl_1_bss_7C0;
    fn_1_14F6C(obj);
    while(1) {
        fn_1_BC8();
        if(lbl_1_bss_7C0.unk04 != NULL) {
            lbl_1_bss_7C0.unk04(obj, &lbl_1_bss_7C0);
        }
        if(obj->work[0]) {
            if(obj->work[2]) {
                obj->work[2]--;
            } else if(obj->work[2] == 0 && Hu3DMotionEndCheck(obj->model[1])) {
                fn_1_1DFC(obj, 1, obj->work[1], 15, 1);
                obj->work[0] = obj->work[1] = obj->work[2] = 0;
            }
        }
    }
}

void fn_1_15668(int arg0)
{
    int i;
    int order[4];
    order[0] = 0;
    for(i=1; i<4; i++) {
        order[i] = order[i-1]+1;
        if(order[i] >= 4) {
            order[i] = 0;
        }
        if(arg0 == order[i]) {
            lbl_1_bss_860.unk00 = i;
        }
    }
    for(i=0; i<4; i++) {
        fn_1_357C(&lbl_1_bss_860.unk30[i], order[i]);
    }
}

void fn_1_1574C(omObjData *object)
{
    int charNo = lbl_1_bss_860.unk30[lbl_1_bss_860.unk00].unk10;
    object->model[1] = CharModelCreate(charNo, 1);
    object->motion[1] = CharModelMotionCreate(charNo, 0x5F0000);
    object->motion[2] = CharModelMotionCreate(charNo, 0x5F0002);
    object->motion[3] = Hu3DJointMotionFile(object->model[1], 0x660028+charNo);
    object->motion[4] = Hu3DJointMotionFile(object->model[1], 0x660030+charNo);
    object->motion[5] = Hu3DJointMotionFile(object->model[1], 0x660038+charNo);
    object->motion[6] = Hu3DJointMotionFile(object->model[1], 0x660000+charNo);
    CharModelMotionDataClose(charNo);
    Hu3DModelPosSet(object->model[1], 120, 0, 800);
    Hu3DModelRotSet(object->model[1], 0, -60, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 3, 0, 1);
}

void fn_1_15944(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_798.unk00, 1, arg0, arg2, arg3);
    if(arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_798.unk00->work[0] = arg4;
    lbl_1_bss_798.unk00->work[1] = arg1;
    lbl_1_bss_798.unk00->work[2] = arg2+1;
}

void fn_1_159F0(void)
{
    omObjData *obj;
    lbl_1_bss_798.unk00 = obj = omAddObjEx(lbl_1_bss_790, 256, 16, 16, -1, NULL);
    lbl_1_bss_798.unk04 = NULL;
    lbl_1_bss_798.unk00->data = &lbl_1_bss_798;
    fn_1_1574C(obj);
    while(1) {
        fn_1_BC8();
        if(lbl_1_bss_798.unk04 != NULL) {
            lbl_1_bss_798.unk04(obj, &lbl_1_bss_798);
        }
        if(obj->work[0]) {
            if(obj->work[2]) {
                obj->work[2]--;
            } else if(obj->work[2] == 0 && Hu3DMotionEndCheck(obj->model[1])) {
                fn_1_1DFC(obj, 1, obj->work[1], 15, 1);
                obj->work[0] = obj->work[1] = obj->work[2] = 0;
            }
        }
    }
}

void fn_1_15CDC(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    work->unk08.x = 0;
    work->unk08.y = 125;
    work->unk08.z = 0;
    work->unk20.x = -5;
    work->unk20.y = 0;
    work->unk20.z = 0;
    work->unk38 = 1750;
}

void fn_1_15D68(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    StructBss24 temp;
    temp.unk08.x = 0;
    temp.unk08.y = 100;
    temp.unk08.z = 0;
    temp.unk20.x = 0;
    temp.unk20.y = 0;
    temp.unk20.z = 0;
    temp.unk38 = 1400;
    fn_1_4FEC(work, &temp, work->unk40++, 120, 10);

}

void fn_1_15E58(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    work->unk14 = 0;
    work->unk18 = Hu3DData[lbl_1_bss_810.unk00->model[7]].pos.y;
    work->unk1C = 0;
    work->unk2C = 0;
    work->unk30 = 0;
    work->unk34 = 0;
    work->unk3C = fn_1_864(1200, 1400, work->unk40++, 240);
    fn_1_3B04(work, 30);
}

void fn_1_15F70(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    StructBss24 temp;
    temp.unk08.x = 0;
    temp.unk08.y = 160;
    temp.unk08.z = 0;
    temp.unk20.x = 0;
    temp.unk20.y = 0;
    temp.unk20.z = 0;
    temp.unk38 = 1200;
    fn_1_6004(work, &temp, work->unk40++, 10, 5);
}