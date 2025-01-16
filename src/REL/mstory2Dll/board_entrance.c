#include "REL/mstory2Dll.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/board/main.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"

typedef struct {
    /* 0x000 */ s32 unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ char unk18[0x18];
    /* 0x030 */ StructFn357C unk30[4];
    /* 0x100 */ float unk100;
} StructBss194; // Size 0x104

StructBss194 lbl_1_bss_194;
StructBss16C lbl_1_bss_16C;
StructBss16C lbl_1_bss_144;
StructBss16C lbl_1_bss_11C;
StructBss16C lbl_1_bss_F4;
StructBss16C lbl_1_bss_CC;
Process *lbl_1_bss_C8;
s32 lbl_1_bss_88[16];
s32 lbl_1_bss_78[4];

u32 lbl_1_data_3A0[11]
    = { 0x00250000, 0x00250000, 0x00250000, 0x00250000, 0x00250000, 0x00250000, 0x00250000, 0x00250000, 0x00250000, 0x00250000, 0x00250000 };

s32 lbl_1_data_3CC[2][2] = { 20, 70, 1, 1 };

s32 lbl_1_data_3DC = -1;
s32 lbl_1_data_3E0[2] = { -1, -1 };

void fn_1_9768(void);
void fn_1_9A10(void);
void fn_1_9BD4(s32 arg0);
void fn_1_9ECC(omObjData *arg0, StructBss16C *arg1);
void fn_1_9FDC(void);
void fn_1_A4A8(omObjData *arg0, StructBss16C *arg1);
void fn_1_A58C(void);
void fn_1_AB10(omObjData *arg0, StructBss16C *arg1);

void fn_1_AE5C(void);
void fn_1_B1C0(void);
void fn_1_B24C(void);

void fn_1_7DB0(void)
{
    int i;
    while (1) {
        do {
            HuPrcVSleep();
        } while (lbl_1_data_3DC == -1 || lbl_1_data_3E0[0] == -1 || lbl_1_data_3E0[1] == -1 || lbl_1_data_3E0[0] != Hu3DMotionIDGet(lbl_1_data_3DC));
        for (i = 0; i < 2; i++) {
            if (lbl_1_data_3CC[1][i] != -1) {
                if (Hu3DMotionTimeGet(lbl_1_data_3DC) >= lbl_1_data_3CC[0][i]) {
                    OSReport("KE-System  TIME:%d\n", lbl_1_data_3CC[0][i]);
                    HuAudFXPlay(81);
                    lbl_1_data_3CC[1][i] = -1;
                }
            }
        }
        if (Hu3DMotionTimeGet(lbl_1_data_3DC) <= 10) {
            for (i = 0; i < 2; i++) {
                lbl_1_data_3CC[1][i] = 1;
            }
        }
    }
}

void fn_1_7F54(Process *arg0, s32 arg1)
{
    lbl_1_bss_C8 = arg0;
    lbl_1_bss_194.unk0C = arg1;
    fn_1_C30();
    fn_1_3668(255);
    fn_1_2828(lbl_1_bss_C8, fn_1_B1C0);
    fn_1_3754();
    fn_1_9BD4(arg1);
    HuPrcChildCreate(fn_1_9FDC, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_9A10, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_A58C, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_AE5C, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_9768, 100, 8192, 0, HuPrcCurrentGet());
}

void fn_1_806C(omObjData *object)
{
    if (object->work[2]) {
        object->work[2]--;
        return;
    }
    if (object->work[2] == 0 && Hu3DMotionEndCheck(object->model[1])) {
        fn_1_1DFC(object, 1, object->work[1], 15, 1);
        object->work[0] = object->work[1] = object->work[2] = 0;
    }
}

void fn_1_80F8(void)
{
    int posX = 16;
    int posY = 40;
    GXColor winColor = { 0, 0, 128, 128 };
    int i;
    while (1) {
        fn_1_BC8();
        fontcolor = FONT_COLOR_WHITE;
        printWin(posX, posY, 220, 130, &winColor);
        if (lbl_1_bss_16C.unk04 == NULL) {
            print8(posX, posY, 1, "PROC_MAIN   -> FALSE");
        }
        else {
            print8(posX, posY, 1, "PROC_MAIN   -> TRUE");
        }
        if (lbl_1_bss_144.unk04 == NULL) {
            print8(posX, posY + 10, 1, "PROC_MAP    -> FALSE");
        }
        else {
            print8(posX, posY + 10, 1, "PROC_MAP    -> TRUE");
        }
        if (lbl_1_bss_11C.unk04 == NULL) {
            print8(posX, posY + 20, 1, "PROC_PLAYER -> FALSE");
        }
        else {
            print8(posX, posY + 20, 1, "PROC_PLAYER -> TRUE");
        }
        if (lbl_1_bss_F4.unk04 == NULL) {
            print8(posX, posY + 30, 1, "PROC_SUB    -> FALSE");
        }
        else {
            print8(posX, posY + 30, 1, "PROC_SUB    -> TRUE");
        }
        if (lbl_1_bss_CC.unk04 == NULL) {
            print8(posX, posY + 40, 1, "PROC_KOOPA  -> FALSE");
        }
        else {
            print8(posX, posY + 40, 1, "PROC_KOOPA  -> TRUE");
        }

        print8(posX, posY + 60, 1, "P:%d W:%d", lbl_1_bss_194.unk00, lbl_1_bss_194.unk0C);
        print8(posX, posY + 80, 1, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (i = 0; i < 4; i++) {
            print8(posX, posY + 90 + (i * 10), 1, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i, lbl_1_bss_194.unk30[i].unk00, lbl_1_bss_194.unk30[i].unk04,
                lbl_1_bss_194.unk30[i].unk08, lbl_1_bss_194.unk30[i].unk0C, lbl_1_bss_194.unk30[i].unk14, lbl_1_bss_194.unk30[i].unk10);
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_X) {
            fn_1_7384(lbl_1_bss_11C.unk00->model[1], lbl_1_bss_194.unk30[lbl_1_bss_194.unk00].unk10, 30, 120, TRUE);
        }
        else if (HuPadBtnDown[0] & PAD_BUTTON_Y) {
            fn_1_7384(lbl_1_bss_11C.unk00->model[1], lbl_1_bss_194.unk30[lbl_1_bss_194.unk00].unk10, 30, 120, FALSE);
        }
    }
}

void fn_1_8580(void)
{
    lbl_1_bss_78[0] = HuAudSeqPlay(51);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet());
    fn_1_BE8(60);
}

void fn_1_85DC(void)
{
    fn_1_1DFC(lbl_1_bss_144.unk00, 2, 3, 0, 0);
    fn_1_2264(lbl_1_bss_144.unk00, 2, 3, 0);
    lbl_1_bss_11C.unk04 = (void *)fn_1_9ECC;
    lbl_1_bss_F4.unk04 = (void *)fn_1_A4A8;
    fn_1_3854(&lbl_1_bss_24);
    fn_1_2750(fn_1_B24C);
    fn_1_BE8(30);
    fn_1_1DFC(lbl_1_bss_144.unk00, 2, 2, 0, 0);
    do {
        fn_1_BC8();
    } while (lbl_1_bss_11C.unk04 != NULL);
    do {
        fn_1_BC8();
    } while (lbl_1_bss_F4.unk04 != NULL);
    lbl_1_bss_194.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_194.unk0C);
    HuAudFXPlay(lbl_1_data_0[0][2]);
    fn_1_1DFC(lbl_1_bss_F4.unk00, 1, 3, 5, 1);
    fn_1_1D18(lbl_1_bss_194.unk04, 0x1F0000);
    fn_1_1AFC(lbl_1_bss_194.unk04, -1);
    fn_1_1D18(lbl_1_bss_194.unk04, 0x1F0001);
    fn_1_1AFC(lbl_1_bss_194.unk04, -1);
    fn_1_1D18(lbl_1_bss_194.unk04, 0x250004);
    fn_1_1DFC(lbl_1_bss_F4.unk00, 1, 1, 5, 1);
    fn_1_1A94(lbl_1_bss_194.unk04);
    fn_1_BE8(15);
}

void fn_1_87D4(void)
{
    int i;
    float speed;
    HuAudSeqFadeOut(lbl_1_bss_78[0], 500);
    HuAudFXPlay(153);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 2, 0, 0);
    fn_1_BC8();
    Hu3DMotionTimeSet(lbl_1_bss_CC.unk00->model[1], 100);
    Hu3DModelAttrReset(lbl_1_bss_CC.unk00->model[1], 1);
    while (1) {
        fn_1_BC8();
        if (Hu3DMotionTimeGet(lbl_1_bss_CC.unk00->model[1]) >= 132) {
            break;
        }
    }
    fn_1_1DFC(lbl_1_bss_F4.unk00, 1, 4, 0, 0);
    fn_1_BC8();
    while (1) {
        fn_1_BC8();
        if (Hu3DMotionTimeGet(lbl_1_bss_F4.unk00->model[1]) >= 5) {
            break;
        }
    }
    Hu3DMotionSpeedSet(lbl_1_bss_F4.unk00->model[1], 0);
    Hu3DData[lbl_1_bss_F4.unk00->model[1]].rot.y = 0;
    fn_1_67D8(lbl_1_bss_11C.unk00, 3, 1, 5, 0);
    HuAudFXPlay(156);
    omVibrate(lbl_1_bss_194.unk0C, 45, 12, 0);
    speed = 50;
    for (i = 0; i < 60; i++) {
        float weight = fn_1_B08(0, speed, i % 15, 15);
        speed = fn_1_88C(speed, 0, 30);
        lbl_1_bss_194.unk100 = fn_1_88C(lbl_1_bss_194.unk100, weight, 5);
        fn_1_BC8();
    }
    lbl_1_bss_194.unk100 = 0;
}

void fn_1_8ABC(void)
{
    fn_1_7384(lbl_1_bss_11C.unk00->model[1], lbl_1_bss_194.unk30[lbl_1_bss_194.unk00].unk10, 1, 20, 1);
    lbl_1_bss_78[1] = HuAudSeqPlay(6);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 3, 10, 0);
    fn_1_BE8(30);
    lbl_1_bss_194.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_194.unk0C);
    HuAudFXPlay(lbl_1_data_0[6][0]);
    HuWinAttrSet(lbl_1_bss_194.unk04, 0x400);
    HuWinMesSet(lbl_1_bss_194.unk04, 0x1F0002);
    fn_1_2264(lbl_1_bss_CC.unk00, 1, 3, 10);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 3, 10, 0);
    fn_1_BE8(45);
    HuAudFXPlay(lbl_1_data_0[6][0]);
    fn_1_2264(lbl_1_bss_CC.unk00, 1, 3, 10);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 1, 10, 1);
    HuWinAttrReset(lbl_1_bss_194.unk04, 0x400);
    HuWinKeyWaitEntry(lbl_1_bss_194.unk04);
    fn_1_BC8();
    fn_1_1AFC(lbl_1_bss_194.unk04, -1);
    HuAudFXPlay(lbl_1_data_0[6][2]);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 4, 10, 1);
    fn_1_1D18(lbl_1_bss_194.unk04, 0x1F0003);
    fn_1_1AFC(lbl_1_bss_194.unk04, -1);
    fn_1_1D18(lbl_1_bss_194.unk04, 0x250004);
    fn_1_1A94(lbl_1_bss_194.unk04);
    fn_1_BE8(30);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 1, 30, 1);
    fn_1_BE8(60);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 5, 10, 0);
    fn_1_BE8(25);
    HuAudFXPlay(81);
    fn_1_BE8(20);
    lbl_1_bss_194.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_194.unk0C);
    HuAudFXPlay(lbl_1_data_0[6][2]);
    fn_1_1D4C(lbl_1_bss_194.unk04, lbl_1_bss_194.unk30[lbl_1_bss_194.unk00].unk10, 0);
    fn_1_1D18(lbl_1_bss_194.unk04, 0x1F0004);
    fn_1_1AFC(lbl_1_bss_194.unk04, -1);
    fn_1_1D18(lbl_1_bss_194.unk04, 0x1F0005);
    fn_1_1AFC(lbl_1_bss_194.unk04, -1);
    fn_1_1D18(lbl_1_bss_194.unk04, 0x250004);
    fn_1_1A94(lbl_1_bss_194.unk04);
    fn_1_67D8(lbl_1_bss_11C.unk00, 7, 8, 10, 0);
    fn_1_7384(lbl_1_bss_11C.unk00->model[1], lbl_1_bss_194.unk30[lbl_1_bss_194.unk00].unk10, 3, 5, 0);
    fn_1_BE8(90);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 3, 30, 0);
    fn_1_BE8(30);
    lbl_1_bss_194.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_194.unk0C);
    HuAudFXPlay(lbl_1_data_0[6][0]);
    HuWinAttrSet(lbl_1_bss_194.unk04, 0x400);
    HuWinMesSet(lbl_1_bss_194.unk04, 0x1F0002);
    fn_1_2264(lbl_1_bss_CC.unk00, 1, 3, 10);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 1, 10, 1);
    HuWinAttrReset(lbl_1_bss_194.unk04, 0x400);
    HuWinKeyWaitEntry(lbl_1_bss_194.unk04);
    fn_1_BC8();
    fn_1_1AFC(lbl_1_bss_194.unk04, -1);
    fn_1_1D18(lbl_1_bss_194.unk04, 0x250004);
    fn_1_1A94(lbl_1_bss_194.unk04);
}

void fn_1_9034(void)
{
    fn_1_BE8(60);
    lbl_1_bss_CC.unk04 = (void *)fn_1_AB10;
    lbl_1_bss_194.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_194.unk0C);
    HuAudFXPlay(lbl_1_data_0[6][1]);
    fn_1_1D18(lbl_1_bss_194.unk04, 0x1F0007);
    fn_1_1AFC(lbl_1_bss_194.unk04, -1);
    fn_1_1A94(lbl_1_bss_194.unk04);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_CC.unk04 == NULL) {
            break;
        }
    }
    HuAudFXPlay(149);
    Hu3DMotionSpeedSet(lbl_1_bss_F4.unk00->model[1], 1);
    fn_1_BC8();
    fn_1_2264(lbl_1_bss_F4.unk00, 1, 4, 0);
    lbl_1_bss_88[0] = HuAudFXPlay(98);
    HuAudFXPlay(lbl_1_data_0[0][1]);
    fn_1_1DFC(lbl_1_bss_F4.unk00, 1, 5, 15, 1);
    fn_1_BE8(60);
}

void fn_1_9198(void)
{
    fn_1_BE8(60);
    HuAudSeqFadeOut(lbl_1_bss_78[0], 1000);
    HuAudFXFadeOut(lbl_1_bss_88[0], 1000);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (1) {
        fn_1_BC8();
        if (!WipeStatGet()) {
            break;
        }
    }
    CharModelKill(-1);
    HuAudFadeOut(1);
    GWPlayerCfg[0].group = 0;
    GWPlayerCfg[0].character = lbl_1_bss_194.unk30[lbl_1_bss_194.unk00].unk10;
    GWPlayerCfg[0].pad_idx = lbl_1_bss_194.unk30[lbl_1_bss_194.unk00].unk14;
    GWPlayerCfg[0].iscom = FALSE;
    omOvlGotoEx(OVL_MENT, 1, 11, 0);
}

void fn_1_92BC(omObjData *arg0, StructBss16C *arg1)
{
    int temp = 0;
    fn_1_8580();
    fn_1_85DC();
    fn_1_87D4();
    fn_1_8ABC();
    fn_1_9034();
    fn_1_9198();
    arg1->unk04 = NULL;
}

void fn_1_9768(void)
{
    omObjData *obj;
    lbl_1_bss_16C.unk00 = obj = omAddObjEx(lbl_1_bss_C8, 256, 16, 16, -1, NULL);
    lbl_1_bss_16C.unk04 = (void *)fn_1_92BC;
    lbl_1_bss_16C.unk00->data = &lbl_1_bss_16C;
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_16C.unk04 != NULL) {
            lbl_1_bss_16C.unk04(obj, &lbl_1_bss_16C);
        }
    }
}

void fn_1_981C(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x50));
    object->motion[0] = Hu3DMotionIDGet(object->model[1]);
    fn_1_1DFC(object, 1, 0, 0, 2);
    Hu3DModelShadowMapObjSet(object->model[1], "base_fix9-base");
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x53));
    object->motion[2] = Hu3DJointMotionFile(object->model[2], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x54));
    object->motion[3] = Hu3DJointMotionFile(object->model[2], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x55));
    fn_1_1DFC(object, 2, 3, 0, 2);
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x51));
}

void fn_1_9954(omObjData *arg0, StructBss16C *arg1)
{
    Hu3DData[arg0->model[5]].pos.y = fn_1_B08(125, 130, arg1->unk08++, 360);
    if (arg1->unk08 >= 360) {
        arg1->unk08 = 0;
    }
}

void fn_1_9A10(void)
{
    omObjData *obj;
    lbl_1_bss_144.unk00 = obj = omAddObjEx(lbl_1_bss_C8, 256, 16, 16, -1, NULL);
    lbl_1_bss_144.unk04 = (void *)fn_1_9954;
    lbl_1_bss_144.unk00->data = &lbl_1_bss_144;
    fn_1_981C(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_144.unk04 != NULL) {
            lbl_1_bss_144.unk04(obj, &lbl_1_bss_144);
        }
    }
}

void fn_1_9BD4(s32 arg0)
{
    int i;
    int order[4];
    order[0] = 0;
    for (i = 1; i < 4; i++) {
        order[i] = order[i - 1] + 1;
        if (order[i] >= 4) {
            order[i] = 0;
        }
        if (arg0 == order[i]) {
            lbl_1_bss_194.unk00 = i;
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_357C(&lbl_1_bss_194.unk30[i], order[i]);
    }
}

void fn_1_9CB8(omObjData *object)
{
    int charNo = lbl_1_bss_194.unk30[lbl_1_bss_194.unk00].unk10;
    object->model[1] = CharModelCreate(charNo, 1);
    object->motion[1] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
    object->motion[2] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x35));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x18) + charNo);
    object->motion[7] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x48) + charNo);
    object->motion[8] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x40) + charNo);
    object->motion[9] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x20) + charNo);
    object->motion[10] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x12));
    CharModelMotionDataClose(charNo);
    Hu3DModelPosSet(object->model[1], 120, 0, 800);
    Hu3DModelRotSet(object->model[1], 0, -135, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
}

void fn_1_9ECC(omObjData *arg0, StructBss16C *arg1)
{
    int i;
    fn_1_1DFC(arg0, 1, 2, 0, 0);
    fn_1_BC8();
    Hu3DMotionTimeSet(arg0->model[1], 60);
    for (i = 0; i < 60; i++) {
        fn_1_BC8();
        Hu3DData[arg0->model[1]].rot.y = fn_1_864(-135, -90, i, 60);
    }
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_9FDC(void)
{
    omObjData *obj;
    lbl_1_bss_11C.unk00 = obj = omAddObjEx(lbl_1_bss_C8, 256, 16, 16, -1, NULL);
    lbl_1_bss_11C.unk04 = NULL;
    lbl_1_bss_11C.unk00->data = &lbl_1_bss_11C;
    fn_1_9CB8(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_11C.unk04 != NULL) {
            lbl_1_bss_11C.unk04(obj, &lbl_1_bss_11C);
        }
        if (obj->work[0]) {
            fn_1_6704(obj);
        }
    }
}

void fn_1_A288(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x72 : 0x73));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x73 : 0x74));
    object->motion[2] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x75));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x76));
    object->motion[4] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x7A : 0x78));
    object->motion[5] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x7B : 0x79));
    object->motion[6] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x79 : 0x77));
    Hu3DModelPosSet(object->model[1], 0, 0, 460);
    Hu3DModelRotSet(object->model[1], 0, 0, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 6, 0, 1);
    CharModelEffectNpcInit(object->model[1], object->motion[2], 1, 9);
}

void fn_1_A4A8(omObjData *arg0, StructBss16C *arg1)
{
    Vec pos = { -120, 0, 800 };
    fn_1_1DFC(arg0, 1, 2, 15, 1);
    fn_1_2D00(arg0, 1, pos, 90, 45, 10);
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_A58C(void)
{
    omObjData *obj;
    lbl_1_bss_F4.unk00 = obj = omAddObjEx(lbl_1_bss_C8, 256, 16, 16, -1, NULL);
    lbl_1_bss_F4.unk04 = NULL;
    lbl_1_bss_F4.unk00->data = &lbl_1_bss_F4;
    fn_1_A288(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_F4.unk04 != NULL) {
            lbl_1_bss_F4.unk04(obj, &lbl_1_bss_F4);
        }
        if (obj->work[0]) {
            fn_1_6704(obj);
        }
    }
}

void fn_1_A848(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x62 : 0x66));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x63 : 0x67));
    object->motion[2] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x65 : 0x69));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x66 : 0x6A));
    object->motion[4] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x69 : 0x6C));
    object->motion[5] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x68 : 0x6B));
    object->motion[6] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x6C : 0x6D));
    object->motion[7] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x6D : 0x6E));
    object->motion[8] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x64 : 0x68));
    Hu3DModelPosSet(object->model[1], -120, 0, 800);
    Hu3DModelRotSet(object->model[1], 0, 90, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelAttrSet(object->model[1], 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
    lbl_1_data_3DC = object->model[1];
    lbl_1_data_3E0[0] = object->motion[7];
    lbl_1_data_3E0[1] = object->motion[8];
    HuPrcChildCreate(fn_1_7DB0, 100, 8192, 0, HuPrcCurrentGet());
}

void fn_1_AB10(omObjData *arg0, StructBss16C *arg1)
{
    int i;
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 8, 15, 1);
    for (i = 0; i < 30; i++) {
        fn_1_BC8();
        Hu3DData[lbl_1_bss_CC.unk00->model[1]].pos.x = fn_1_864(-120, -60, i, 30);
    }
    fn_1_1DFC(lbl_1_bss_11C.unk00, 1, 9, 15, 0);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 6, 15, 0);
    fn_1_2264(lbl_1_bss_CC.unk00, 1, 6, 15);
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 7, 15, 1);
    fn_1_1DFC(lbl_1_bss_11C.unk00, 1, 10, 15, 1);
    for (i = 0; i < 240; i++) {
        fn_1_BC8();
        Hu3DData[lbl_1_bss_CC.unk00->model[1]].pos.x = fn_1_864(-60, 540, i, 180);
        Hu3DData[lbl_1_bss_11C.unk00->model[1]].pos.x = fn_1_864(120, 840, i, 180);
    }
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_ADB0(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_CC.unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_CC.unk00->work[0] = arg4;
    lbl_1_bss_CC.unk00->work[1] = arg1;
    lbl_1_bss_CC.unk00->work[2] = arg2 + 1;
}

void fn_1_AE5C(void)
{
    omObjData *obj;
    lbl_1_bss_CC.unk00 = obj = omAddObjEx(lbl_1_bss_C8, 256, 16, 16, -1, NULL);
    lbl_1_bss_CC.unk04 = NULL;
    lbl_1_bss_CC.unk00->data = &lbl_1_bss_CC;
    fn_1_A848(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_CC.unk04 != NULL) {
            lbl_1_bss_CC.unk04(obj, &lbl_1_bss_CC);
        }
        if (obj->work[0]) {
            fn_1_6704(obj);
        }
    }
}

void fn_1_B1C0(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    work->unk08.x = 0;
    work->unk08.y = 125;
    work->unk08.z = 0;
    work->unk20.x = -4.9f;
    work->unk20.y = 0;
    work->unk20.z = 0;
    work->unk38 = 1750;
}

void fn_1_B24C(void)
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
    fn_1_42A0(work, &temp, work->unk40++, 60, 10);
    if (0.0f != lbl_1_bss_194.unk100) {
        work->unk08.y = 100 + lbl_1_bss_194.unk100;
    }
}
