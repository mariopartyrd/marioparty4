#include "REL/mstory2Dll.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/board/main.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework.h"
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
} StructBss3DC; // Size 0x104

StructBss3DC lbl_1_bss_3DC;
StructBss16C lbl_1_bss_3B4;
StructBss16C lbl_1_bss_38C;
StructBss16C lbl_1_bss_364;
StructBss16C lbl_1_bss_33C;
StructBss16C lbl_1_bss_29C[4];
Process *lbl_1_bss_298;

void fn_1_C4C0(void);
void fn_1_C858(void);
void fn_1_CCCC(int arg0, int arg1, int arg2, int arg3, int arg4);
void fn_1_CD78(void);
void fn_1_D224(int arg0, int arg1, int arg2, int arg3, int arg4);
void fn_1_D2D0(omObjData *arg0, StructBss16C *arg1);
void fn_1_D478(void);
void fn_1_D764(int arg0);
void fn_1_DB58(int arg0, int arg1, int arg2, int arg3, int arg4);
void fn_1_DC54(omObjData *arg0, StructBss16C *arg1);
void fn_1_DDC4(void);
void fn_1_E1B8(void);
void fn_1_E244(void);
void fn_1_E334(void);

void fn_1_B37C(omObjData *arg0, StructBss16C *arg1)
{
    fn_1_BE8(30);
    fn_1_DB58(4, -1, 15, 1, 0);
    fn_1_D224(4, -1, 15, 1, 0);
    arg1->unk04 = NULL;
}

void fn_1_B3E4(Process *arg0, s32 arg1)
{
    int i;
    lbl_1_bss_298 = arg0;
    lbl_1_bss_3DC.unk0C = arg1;
    fn_1_C30();
    fn_1_3668(255);
    fn_1_2828(lbl_1_bss_298, fn_1_E1B8);
    fn_1_3754();
    fn_1_D764(arg1);
    HuPrcChildCreate(fn_1_C858, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_CD78, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_D478, 100, 8192, 0, HuPrcCurrentGet());
    for (i = 0; i < 4; i++) {
        HuPrcChildCreate(fn_1_DDC4, 100, 8192, 0, HuPrcCurrentGet());
    }
    HuPrcChildCreate(fn_1_C4C0, 100, 8192, 0, HuPrcCurrentGet());
}

void fn_1_B518(omObjData *object)
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

void fn_1_B5A4(void)
{
    int posX = 16;
    int posY = 40;
    GXColor winColor = { 0, 0, 128, 128 };
    int i;
    while (1) {
        fn_1_BC8();
        printWin(posX, posY, 220, 160, &winColor);
        if (lbl_1_bss_3B4.unk04 == NULL) {
            print8(posX, posY, 1, "PROC_MAIN    -> FALSE");
        }
        else {
            print8(posX, posY, 1, "PROC_MAIN    -> TRUE");
        }
        if (lbl_1_bss_38C.unk04 == NULL) {
            print8(posX, posY + 10, 1, "PROC_MAP     -> FALSE");
        }
        else {
            print8(posX, posY + 10, 1, "PROC_MAP     -> TRUE");
        }
        if (lbl_1_bss_364.unk04 == NULL) {
            print8(posX, posY + 20, 1, "PROC_KOOPA   -> FALSE");
        }
        else {
            print8(posX, posY + 20, 1, "PROC_KOOPA   -> TRUE");
        }
        if (lbl_1_bss_33C.unk04 == NULL) {
            print8(posX, posY + 30, 1, "PROC_MKOOPA  -> FALSE");
        }
        else {
            print8(posX, posY + 30, 1, "PROC_MKOOPA  -> TRUE");
        }
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_29C[i].unk04 == NULL) {
                print8(posX, posY + 40 + (i * 10), 1, "PROC_PLAYER%d -> FALSE", i);
            }
            else {
                print8(posX, posY + 40 + (i * 10), 1, "PROC_PLAYER%d -> TRUE", i);
            }
        }
        print8(posX, posY + 90, 1, "P:%d W:%d", lbl_1_bss_3DC.unk00, lbl_1_bss_3DC.unk0C);
        print8(posX, posY + 110, 1, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (i = 0; i < 4; i++) {
            print8(posX, posY + 120 + (i * 10), 1, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i, lbl_1_bss_3DC.unk30[i].unk00, lbl_1_bss_3DC.unk30[i].unk04,
                lbl_1_bss_3DC.unk30[i].unk08, lbl_1_bss_3DC.unk30[i].unk0C, lbl_1_bss_3DC.unk30[i].unk14, lbl_1_bss_3DC.unk30[i].unk10);
        }
    }
}

void fn_1_B984(void)
{
    lbl_1_bss_78[0] = HuAudSeqPlay(51);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet());
    fn_1_BE8(60);
}

void fn_1_B9E0(void)
{
    lbl_1_bss_29C[lbl_1_bss_3DC.unk00].unk04 = (void *)fn_1_DC54;
    fn_1_3854(&lbl_1_bss_24);
    fn_1_2750(fn_1_E244);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_29C[lbl_1_bss_3DC.unk00].unk04 == NULL) {
            break;
        }
    }
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_33C.unk04 == NULL) {
            break;
        }
    }
    fn_1_BE8(30);
}

void fn_1_BA90(void)
{
    int i;
    lbl_1_bss_3DC.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_3DC.unk0C);
    HuAudFXPlay(lbl_1_data_0[5][0]);
    fn_1_D224(3, -1, 15, 1, 0);
    fn_1_1D4C(lbl_1_bss_3DC.unk04, lbl_1_bss_3DC.unk30[lbl_1_bss_3DC.unk00].unk10, 0);
    fn_1_1D18(lbl_1_bss_3DC.unk04, 0x1F000C);
    fn_1_1AFC(lbl_1_bss_3DC.unk04, -1);
    fn_1_1D18(lbl_1_bss_3DC.unk04, 0x250004);
    fn_1_D224(1, -1, 15, 1, 0);
    fn_1_1A94(lbl_1_bss_3DC.unk04);
    HuAudSeqFadeOut(lbl_1_bss_78[0], 1000);
    fn_1_BE8(60);
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_3DC.unk30[i].unk00 != lbl_1_bss_3DC.unk30[lbl_1_bss_3DC.unk00].unk00) {
            Hu3DModelAttrSet(lbl_1_bss_29C[i].unk00->model[1], 1);
        }
        Hu3DModelAttrSet(lbl_1_bss_29C[i].unk00->model[2], 1);
    }
    Hu3DModelAttrReset(lbl_1_bss_364.unk00->model[1], 1);
    Hu3DModelAttrReset(lbl_1_bss_38C.unk00->model[5], 1);
    Hu3DModelAttrReset(lbl_1_bss_38C.unk00->model[6], 1);
    lbl_1_bss_3DC.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_3DC.unk0C);
    HuAudFXPlay(lbl_1_data_0[6][0]);
    lbl_1_bss_78[1] = HuAudSeqPlay(55);
    lbl_1_bss_33C.unk04 = (void *)fn_1_B37C;
    fn_1_1D18(lbl_1_bss_3DC.unk04, 0x1F000D);
    fn_1_1AFC(lbl_1_bss_3DC.unk04, -1);
    fn_1_1D18(lbl_1_bss_3DC.unk04, 0x250004);
    fn_1_1A94(lbl_1_bss_3DC.unk04);
    fn_1_1DFC(lbl_1_bss_38C.unk00, 2, 3, 0, 0);
    fn_1_BE8(60);
    lbl_1_bss_33C.unk04 = (void *)fn_1_D2D0;
    fn_1_DB58(5, -1, 15, 0, 0);
    fn_1_D224(5, 1, 0, 0, 1);
    fn_1_2264(lbl_1_bss_38C.unk00, 2, 3, 0);
}

void fn_1_BDF0(void)
{
    lbl_1_bss_3DC.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_3DC.unk0C);
    HuAudFXPlay(lbl_1_data_0[6][1]);
    fn_1_CCCC(3, -1, 15, 1, 0);
    fn_1_1D18(lbl_1_bss_3DC.unk04, 0x1F000E);
    fn_1_1AFC(lbl_1_bss_3DC.unk04, -1);
    fn_1_1D18(lbl_1_bss_3DC.unk04, 0x250004);
    fn_1_CCCC(1, -1, 15, 1, 0);
    fn_1_1A94(lbl_1_bss_3DC.unk04);
    fn_1_CCCC(2, -1, 15, 0, 0);
    fn_1_BE8(45);
    HuAudFXPlay(lbl_1_data_0[6][0]);
    fn_1_BE8(15);
    HuAudSeqFadeOut(lbl_1_bss_78[1], 3000);
    fn_1_3854(&lbl_1_bss_24);
    fn_1_2750(fn_1_E334);
    fn_1_BE8(30);
    fn_1_BE8(45);
    fn_1_BE8(75);
}

void fn_1_BF48(void)
{
    int i;
    omOvlHisData *his;
    int charNo;
    int padNo;
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (1) {
        fn_1_BC8();
        if (!WipeStatGet()) {
            break;
        }
    }
    CharModelKill(-1);
    charNo = lbl_1_bss_3DC.unk30[lbl_1_bss_3DC.unk00].unk10;
    padNo = lbl_1_bss_3DC.unk30[lbl_1_bss_3DC.unk00].unk14;
    GWPlayerCfg[lbl_1_bss_3DC.unk00].character = GWPlayerCfg[0].character;
    GWPlayerCfg[lbl_1_bss_3DC.unk00].pad_idx = GWPlayerCfg[0].pad_idx;
    GWPlayerCfg[lbl_1_bss_3DC.unk00].group = GWPlayerCfg[0].group;
    GWPlayerCfg[lbl_1_bss_3DC.unk00].iscom = GWPlayerCfg[0].iscom;
    GWPlayerCfg[0].character = charNo;
    GWPlayerCfg[0].pad_idx = padNo;
    GWPlayerCfg[0].group = 0;
    GWPlayerCfg[0].iscom = FALSE;
    for (i = 0; i < 4; i++) {
        GWPlayer[i].character = GWPlayerCfg[i].character;
        GWPlayer[i].port = GWPlayerCfg[i].pad_idx;
        GWPlayer[i].com = GWPlayerCfg[i].iscom;
        GWPlayer[i].team = GWPlayerCfg[i].group;
    }
    GWPlayerCfg[1].character = 8;
    for (i = 1; i < 4; i++) {
        GWPlayerCfg[i].iscom = GWPlayerCfg[i].group = 1;
    }
    his = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MSTORY2, 3, his->stat);
    HuAudSeqAllFadeOut(1000);
    HuAudSStreamAllFadeOut(1000);
    GWSystem.mg_type = -1;
    GWMGAvailSet(450);
    GWSystem.mg_next = 450 - 401;
    omOvlCallEx(OVL_M450, 1, 0, 0);
    while (1) {
        fn_1_BC8();
    }
}

void fn_1_C270(omObjData *arg0, StructBss16C *arg1)
{
    int temp = 0;
    fn_1_B984();
    fn_1_B9E0();
    fn_1_BA90();
    fn_1_BDF0();
    fn_1_BF48();
    arg1->unk04 = NULL;
}

void fn_1_C4C0(void)
{
    omObjData *obj;
    lbl_1_bss_3B4.unk00 = obj = omAddObjEx(lbl_1_bss_298, 256, 16, 16, -1, NULL);
    lbl_1_bss_3B4.unk04 = (void *)fn_1_C270;
    lbl_1_bss_3B4.unk00->data = &lbl_1_bss_3B4;
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_3B4.unk04 != NULL) {
            lbl_1_bss_3B4.unk04(obj, &lbl_1_bss_3B4);
        }
    }
}

void fn_1_C574(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x52));
    object->motion[1] = Hu3DMotionIDGet(object->model[1]);
    Hu3DModelShadowMapObjSet(object->model[1], "base_story-base");
    fn_1_1DFC(object, 1, 1, 0, 1);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x53));
    object->motion[2] = Hu3DJointMotionFile(object->model[2], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x54));
    object->motion[3] = Hu3DJointMotionFile(object->model[2], DATA_MAKE_NUM(DATADIR_MSTORY2, 0x55));
    fn_1_1DFC(object, 2, 2, 0, 2);
    object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x59));
    object->motion[5] = Hu3DMotionIDGet(object->model[5]);
    Hu3DModelPosSet(object->model[5], 0, 80, 460);
    Hu3DModelAttrSet(object->model[5], 1);
    Hu3DModelShadowSet(object->model[5]);
    fn_1_1DFC(object, 5, 5, 0, 2);
    object->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x5A));
    object->motion[6] = Hu3DMotionIDGet(object->model[6]);
    Hu3DModelHookSet(object->model[5], "koopasgbox_fix-effect_fook2", object->model[6]);
    Hu3DModelAttrSet(object->model[6], 1);
    fn_1_1DFC(object, 6, 6, 0, 2);
}

void fn_1_C79C(omObjData *arg0, StructBss16C *arg1)
{
    Hu3DData[arg0->model[5]].pos.y = fn_1_B08(80, 90, arg1->unk08++, 360);
    if (arg1->unk08 >= 360) {
        arg1->unk08 = 0;
    }
}

void fn_1_C858(void)
{
    omObjData *obj;
    lbl_1_bss_38C.unk00 = obj = omAddObjEx(lbl_1_bss_298, 256, 16, 16, -1, NULL);
    lbl_1_bss_38C.unk04 = (void *)fn_1_C79C;
    lbl_1_bss_38C.unk00->data = &lbl_1_bss_38C;
    fn_1_C574(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_38C.unk04 != NULL) {
            lbl_1_bss_38C.unk04(obj, &lbl_1_bss_38C);
        }
    }
}

void fn_1_CB0C(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x62 : 0x66));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x63 : 0x67));
    object->motion[2] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x66 : 0x6A));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x69 : 0x6C));
    Hu3DModelPosSet(object->model[1], 0, 0, 150);
    Hu3DModelRotSet(object->model[1], 0, 0, 0);
    Hu3DModelScaleSet(object->model[1], 1.25f, 1.25f, 1.25f);
    Hu3DModelScaleSet(object->model[1], 1.6f, 1.6f, 1.6f);
    Hu3DModelAttrSet(object->model[1], 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
}

void fn_1_CCCC(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_364.unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_364.unk00->work[0] = arg4;
    lbl_1_bss_364.unk00->work[1] = arg1;
    lbl_1_bss_364.unk00->work[2] = arg2 + 1;
}

void fn_1_CD78(void)
{
    omObjData *obj;
    lbl_1_bss_364.unk00 = obj = omAddObjEx(lbl_1_bss_298, 256, 16, 16, -1, NULL);
    lbl_1_bss_364.unk04 = NULL;
    lbl_1_bss_364.unk00->data = &lbl_1_bss_38C;
    fn_1_CB0C(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_364.unk04 != NULL) {
            lbl_1_bss_364.unk04(obj, &lbl_1_bss_364);
        }
        if (obj->work[0]) {
            if (obj->work[2]) {
                obj->work[2]--;
            }
            else if (obj->work[2] == 0 && Hu3DMotionEndCheck(obj->model[1])) {
                fn_1_1DFC(obj, 1, obj->work[1], 15, 1);
                obj->work[0] = obj->work[1] = obj->work[2] = 0;
            }
        }
    }
}

void fn_1_D030(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x7D : 0x7B));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x7E : 0x7C));
    object->motion[2] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x80 : 0x7D));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x81 : 0x7E));
    object->motion[4] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x84 : 0x7F));
    object->motion[5] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x85 : 0x80));
    Hu3DModelPosSet(object->model[1], -300, 0, 890);
    Hu3DModelRotSet(object->model[1], 0, 30, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
    CharModelEffectNpcInit(object->model[1], object->motion[2], 1, 13);
}

void fn_1_D224(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_33C.unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_33C.unk00->work[0] = arg4;
    lbl_1_bss_33C.unk00->work[1] = arg1;
    lbl_1_bss_33C.unk00->work[2] = arg2 + 1;
}

void fn_1_D2D0(omObjData *arg0, StructBss16C *arg1)
{
    int i;
    for (i = 0; i < 15; i++) {
        fn_1_BC8();
        Hu3DData[arg0->model[1]].rot.y = fn_1_864(0, 135, i, 15);
    }
    arg1->unk04 = NULL;
}

void fn_1_D394(omObjData *arg0, StructBss16C *arg1)
{
    Vec pos = { -120, 0, 800 };
    fn_1_1DFC(arg0, 1, 2, 15, 1);
    fn_1_2D00(arg0, 1, pos, 60, 60, 10);
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_D478(void)
{
    omObjData *obj;
    lbl_1_bss_33C.unk00 = obj = omAddObjEx(lbl_1_bss_298, 256, 16, 16, -1, NULL);
    lbl_1_bss_33C.unk04 = NULL;
    lbl_1_bss_33C.unk00->data = &lbl_1_bss_33C;
    fn_1_D030(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_33C.unk04 != NULL) {
            lbl_1_bss_33C.unk04(obj, &lbl_1_bss_33C);
        }
        if (obj->work[0]) {
            if (obj->work[2]) {
                obj->work[2]--;
            }
            else if (obj->work[2] == 0 && Hu3DMotionEndCheck(obj->model[1])) {
                fn_1_1DFC(obj, 1, obj->work[1], 15, 1);
                obj->work[0] = obj->work[1] = obj->work[2] = 0;
            }
        }
    }
}

void fn_1_D764(int arg0)
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
            lbl_1_bss_3DC.unk00 = i;
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_357C(&lbl_1_bss_3DC.unk30[i], order[i]);
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_3DC.unk30[i].unk18 = GWPlayer[order[i]].rank + 1;
    }
}

Vec lbl_1_data_668[4] = {
    { -300, 0, 460 },
    { -100, -30, 460 },
    { 100, -60, 460 },
    { 300, -90, 460 },
};

void fn_1_D898(omObjData *object, int player)
{
    int playerNo = player;
    int charNo = lbl_1_bss_3DC.unk30[playerNo].unk10;
    object->model[1] = CharModelCreate(charNo, 4);
    object->motion[1] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
    object->motion[2] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03));
    object->motion[3] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05));
    object->motion[4] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1A));
    object->motion[5] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x6D));
    CharModelMotionDataClose(charNo);
    Hu3DModelPosSet(
        object->model[1], lbl_1_data_668[playerNo].x, lbl_1_data_668[lbl_1_bss_3DC.unk30[playerNo].unk18 - 1].y + 90, lbl_1_data_668[playerNo].z);
    Hu3DModelRotSet(object->model[1], 0, 0, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x56));
    Hu3DModelPosSet(
        object->model[2], lbl_1_data_668[playerNo].x, lbl_1_data_668[lbl_1_bss_3DC.unk30[playerNo].unk18 - 1].y, lbl_1_data_668[playerNo].z);
    if (lbl_1_bss_3DC.unk30[playerNo].unk18 == 4) {
        Hu3DModelAttrSet(object->model[2], 1);
    }
    Hu3DModelScaleSet(object->model[2], 1.5, 1, 1.5);
    Hu3DModelShadowMapSet(object->model[2]);
}

void fn_1_DB58(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_29C[lbl_1_bss_3DC.unk00].unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_29C[lbl_1_bss_3DC.unk00].unk00->work[0] = arg4;
    lbl_1_bss_29C[lbl_1_bss_3DC.unk00].unk00->work[1] = arg1;
    lbl_1_bss_29C[lbl_1_bss_3DC.unk00].unk00->work[2] = arg2 + 1;
}

void fn_1_DC54(omObjData *arg0, StructBss16C *arg1)
{
    Vec pos = { 120, 0, 800 };
    fn_1_2948(arg0, 1, pos, -1, 30, 10);
    lbl_1_bss_33C.unk04 = (void *)fn_1_D394;
    fn_1_1DFC(lbl_1_bss_38C.unk00, 2, 2, 0, 0);
    fn_1_1DFC(arg0, 1, 2, 15, 1);
    fn_1_2D00(arg0, 1, pos, -60, 30, 10);
    fn_1_1DFC(arg0, 1, 1, 15, 1);
    arg1->unk04 = NULL;
}

void fn_1_DDC4(void)
{
    omObjData *obj;
    int playerNo = lbl_1_bss_3DC.unk10++;
    lbl_1_bss_29C[playerNo].unk00 = obj = omAddObjEx(lbl_1_bss_298, 256, 16, 16, -1, NULL);
    lbl_1_bss_29C[playerNo].unk04 = NULL;
    lbl_1_bss_29C[playerNo].unk00->data = &lbl_1_bss_29C[0];
    fn_1_D898(obj, playerNo);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_29C[playerNo].unk04 != NULL) {
            lbl_1_bss_29C[playerNo].unk04(obj, &lbl_1_bss_29C[playerNo]);
        }
        if (obj->work[0]) {
            if (obj->work[2]) {
                obj->work[2]--;
            }
            else if (obj->work[2] == 0 && Hu3DMotionEndCheck(obj->model[1])) {
                fn_1_1DFC(obj, 1, obj->work[1], 15, 1);
                obj->work[0] = obj->work[1] = obj->work[2] = 0;
            }
        }
    }
}

void fn_1_E1B8(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    work->unk08.x = 0;
    work->unk08.y = 170;
    work->unk08.z = -20;
    work->unk20.x = -5;
    work->unk20.y = 0;
    work->unk20.z = 0;
    work->unk38 = 1700;
}

void fn_1_E244(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    StructBss24 temp;
    temp.unk08.x = 0;
    temp.unk08.y = 125;
    temp.unk08.z = -20;
    temp.unk20.x = -5;
    temp.unk20.y = 0;
    temp.unk20.z = 0;
    temp.unk38 = 1750;
    fn_1_4FEC(work, &temp, work->unk40++, 60, 30);
}

void fn_1_E334(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    StructBss24 temp;
    if (work->unk40 == 50) {
        fn_1_1DFC(lbl_1_bss_38C.unk00, 5, 5, 0, 0);
        fn_1_1DFC(lbl_1_bss_38C.unk00, 6, 6, 0, 0);
        HuAudFXPlay(161);
    }
    temp.unk08.x = 0;
    temp.unk08.y = 130;
    temp.unk08.z = 460;
    temp.unk20.x = 0;
    temp.unk20.y = 0;
    temp.unk20.z = 0;
    temp.unk38 = 150;
    fn_1_4FEC(work, &temp, work->unk40, 180, 10);
    if (work->unk40++ >= 90) {
        if (work->unk40 == 91) {
            lbl_1_bss_88[0] = HuAudFXPlay(32);
        }
        work->unk20.x = fn_1_864(work->unk20.x, -45, work->unk40 - 90, 90);
        Hu3DData[lbl_1_bss_38C.unk00->model[5]].rot.x = fn_1_864(0, 45, work->unk40 - 90, 90);
    }
}
