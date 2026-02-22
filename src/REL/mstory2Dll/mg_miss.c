#include "REL/mstory2Dll.h"
#include "game/armem.h"
#include "game/board/main.h"

#ifndef __MWERKS__
#include "game/audio.h"
#endif

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
    /* 0x100 */ s32 unk100;
} StructBssA34; // Size 0x104

StructBssA34 lbl_1_bss_A34;
StructBss16C lbl_1_bss_A0C;
StructBss16C lbl_1_bss_9E4;
StructBss16C lbl_1_bss_9BC;
StructBss16C lbl_1_bss_994;
StructBss16C lbl_1_bss_96C;
Process *lbl_1_bss_968;

void fn_1_16FC0(void);
void fn_1_17338(void);
void fn_1_1774C(int arg0, int arg1, int arg2, int arg3, int arg4);
void fn_1_177F8(void);
void fn_1_17C44(void);
void fn_1_17E64(s32 arg0);
void fn_1_180D8(int arg0, int arg1, int arg2, int arg3, int arg4);
void fn_1_18184(void);
void fn_1_18408(void);
void fn_1_18494(void);

void fn_1_16060(Process *arg0, s32 arg1)
{
    lbl_1_bss_968 = arg0;
    lbl_1_bss_A34.unk0C = arg1;
    fn_1_C30();
    fn_1_3668(255);
    fn_1_2828(lbl_1_bss_968, fn_1_18408);
    fn_1_3754();
    fn_1_17E64(arg1);
    HuPrcChildCreate(fn_1_17338, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_177F8, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_17C44, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_18184, 100, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_16FC0, 100, 8192, 0, HuPrcCurrentGet());
}

void fn_1_16178(omObjData *object)
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

void fn_1_16204(void)
{
    int posX = 16;
    int posY = 40;
    GXColor winColor = { 0, 0, 128, 128 };
    int i;
    while (1) {
        fn_1_BC8();
        printWin(posX, posY, 220, 130, &winColor);
        if (lbl_1_bss_A0C.unk04 == NULL) {
            print8(posX, posY, 1, "PROC_MAIN   -> FALSE");
        }
        else {
            print8(posX, posY, 1, "PROC_MAIN   -> TRUE");
        }
        if (lbl_1_bss_9E4.unk04 == NULL) {
            print8(posX, posY + 10, 1, "PROC_MAP    -> FALSE");
        }
        else {
            print8(posX, posY + 10, 1, "PROC_MAP    -> TRUE");
        }
        if (lbl_1_bss_9BC.unk04 == NULL) {
            print8(posX, posY + 20, 1, "PROC_KOOPA  -> FALSE");
        }
        else {
            print8(posX, posY + 20, 1, "PROC_KOOPA  -> TRUE");
        }
        if (lbl_1_bss_994.unk04 == NULL) {
            print8(posX, posY + 30, 1, "PROC_MKOOPA -> FALSE");
        }
        else {
            print8(posX, posY + 30, 1, "PROC_MKOOPA -> TRUE");
        }
        if (lbl_1_bss_96C.unk04 == NULL) {
            print8(posX, posY + 40, 1, "PROC_PLAYER -> FALSE");
        }
        else {
            print8(posX, posY + 40, 1, "PROC_PLAYER -> TRUE");
        }
        print8(posX, posY + 60, 1, "P:%d W:%d", lbl_1_bss_A34.unk00, lbl_1_bss_A34.unk0C);
        print8(posX, posY + 80, 1, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (i = 0; i < 4; i++) {
            print8(posX, posY + 90 + (i * 10), 1, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", i, lbl_1_bss_A34.unk30[i].unk00, lbl_1_bss_A34.unk30[i].unk04,
                lbl_1_bss_A34.unk30[i].unk08, lbl_1_bss_A34.unk30[i].unk0C, lbl_1_bss_A34.unk30[i].unk14, lbl_1_bss_A34.unk30[i].unk10);
        }
    }
}

void fn_1_165B0(void)
{
    lbl_1_bss_78[0] = HuAudSeqPlay(52);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet());
    fn_1_BE8(60);
}

void fn_1_1661C(void)
{
    lbl_1_bss_A34.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_A34.unk0C);
    fn_1_1774C(2, 1, 15, 0, 1);
    fn_1_180D8(2, 3, 15, 0, 1);
    HuAudCharVoicePlay(lbl_1_bss_A34.unk30[lbl_1_bss_A34.unk00].unk10, 302);
    fn_1_6D78(lbl_1_bss_A34.unk04, 0x1F0010, -1, lbl_1_bss_9BC.unk00->model[1]);
    fn_1_1D18(lbl_1_bss_A34.unk04, 0x250004);
    fn_1_1774C(1, -1, 15, 1, 0);
    fn_1_1A94(lbl_1_bss_A34.unk04);
}

int fn_1_1670C(void)
{
    int result = 0;
    HuWinInsertMesSet(lbl_1_bss_A34.unk04, 0x1E003C, 3);
    fn_1_1D18(lbl_1_bss_A34.unk04, 0x1E002D);
    fn_1_1AFC(lbl_1_bss_A34.unk04, 5);
    lbl_1_bss_A34.unk08 = fn_1_7064(0x1E0035, lbl_1_bss_A34.unk0C);
    fn_1_1D18(lbl_1_bss_A34.unk08, 0x1E0035);
    result = fn_1_1C64(lbl_1_bss_A34.unk08);
    fn_1_1D18(lbl_1_bss_A34.unk08, 0x250004);
    fn_1_71DC(lbl_1_bss_A34.unk08);
    if (result) {
        HuAudFXPlay(lbl_1_data_0[6][2]);
        fn_1_1774C(3, 1, 15, 1, 0);
        fn_1_1D18(lbl_1_bss_A34.unk04, 0x1F0012);
        fn_1_1AFC(lbl_1_bss_A34.unk04, -1);
        fn_1_1D18(lbl_1_bss_A34.unk04, 0x250004);
        fn_1_1774C(1, -1, 15, 1, 0);
        fn_1_180D8(4, 1, 15, 0, 1);
    }
    return result;
}

int fn_1_168B0(void)
{
    int result = 0;
    fn_1_1D18(lbl_1_bss_A34.unk04, 0x1E0005);
    fn_1_1AFC(lbl_1_bss_A34.unk04, 5);
    lbl_1_bss_A34.unk08 = fn_1_7064(0x1E0035, lbl_1_bss_A34.unk0C);
    fn_1_1D18(lbl_1_bss_A34.unk08, 0x1E0035);
    result = fn_1_1BA8(lbl_1_bss_A34.unk08, 1);
    fn_1_1D18(lbl_1_bss_A34.unk08, 0x250004);
    fn_1_71DC(lbl_1_bss_A34.unk08);
    return result;
}

void fn_1_16984(void)
{
    HuAudSeqFadeOut(lbl_1_bss_78[0], 3000);
    fn_1_3854(&lbl_1_bss_24);
    fn_1_2750(fn_1_18494);
    fn_1_BE8(150);
}

void fn_1_169D4(void) { }

void fn_1_169D8(int arg0)
{
    omOvlHisData *his;

    if (arg0 != 0) {
        HuAudSeqFadeOut(lbl_1_bss_78[0], 1000);
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    do {
        fn_1_BC8();
    } while (WipeStatGet() != 0);
    CharModelKill(-1);
    his = omOvlHisGet(0);
    omOvlHisChg(0, OVL_MSTORY2, 3, his->stat);
    if (arg0 == 0) {
        HuAudSeqAllFadeOut(1000);
        HuAudSStreamAllFadeOut(1000);
        GWMGAvailSet(450);
        GWSystem.mg_next = 450 - 401;
        omOvlCallEx(OVL_M450, 1, 0, 0);
    }
    else {
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_16ACC(omObjData *arg0, StructBss16C *arg1)
{
    int mode = 0;
    fn_1_165B0();
    fn_1_1661C();
    lbl_1_bss_A34.unk04 = fn_1_185C(1, 0, 21, 2, lbl_1_bss_A34.unk0C);
    while (1) {
        fn_1_BC8();
        if (fn_1_1670C()) {
            mode = 0;
            break;
        }
        else if (fn_1_168B0()) {
            mode = 1;
            break;
        }
    }
    fn_1_1A94(lbl_1_bss_A34.unk04);
    switch (mode) {
        case 0:
            fn_1_16984();
            break;
        case 1:
            break;
    }
    fn_1_169D8(mode);
    arg1->unk04 = NULL;
}

void fn_1_16FC0(void)
{
    omObjData *obj;
    lbl_1_bss_A0C.unk00 = obj = omAddObjEx(lbl_1_bss_968, 256, 16, 16, -1, NULL);
    lbl_1_bss_A0C.unk04 = (void *)fn_1_16ACC;
    lbl_1_bss_A0C.unk00->data = &lbl_1_bss_A0C;
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_A0C.unk04 != NULL) {
            lbl_1_bss_A0C.unk04(obj, &lbl_1_bss_A0C);
        }
    }
}

void fn_1_17074(omObjData *object)
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
    Hu3DModelShadowSet(object->model[5]);
    fn_1_1DFC(object, 5, 5, 0, 2);
    object->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, 0x5A));
    object->motion[6] = Hu3DMotionIDGet(object->model[6]);
    Hu3DModelHookSet(object->model[5], "koopasgbox_fix-effect_fook2", object->model[6]);
    fn_1_1DFC(object, 6, 6, 0, 2);
}

void fn_1_1727C(omObjData *arg0, StructBss16C *arg1)
{
    Hu3DData[arg0->model[5]].pos.y = fn_1_B08(80, 90, arg1->unk08++, 360);
    if (arg1->unk08 >= 360) {
        arg1->unk08 = 0;
    }
}

void fn_1_17338(void)
{
    omObjData *obj;
    lbl_1_bss_9E4.unk00 = obj = omAddObjEx(lbl_1_bss_968, 256, 16, 16, -1, NULL);
    lbl_1_bss_9E4.unk04 = (void *)fn_1_1727C;
    lbl_1_bss_9E4.unk00->data = &lbl_1_bss_9E4;
    fn_1_17074(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_9E4.unk04 != NULL) {
            lbl_1_bss_9E4.unk04(obj, &lbl_1_bss_9E4);
        }
    }
}

void fn_1_175CC(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x62 : 0x66));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x63 : 0x67));
    object->motion[2] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x66 : 0x6A));
    object->motion[3] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x69 : 0x6C));
    Hu3DModelPosSet(object->model[1], 0, 0, 200);
    Hu3DModelRotSet(object->model[1], 0, 0, 0);
    Hu3DModelScaleSet(object->model[1], 1.6f, 1.6f, 1.6f);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
}

void fn_1_1774C(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_9BC.unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_9BC.unk00->work[0] = arg4;
    lbl_1_bss_9BC.unk00->work[1] = arg1;
    lbl_1_bss_9BC.unk00->work[2] = arg2 + 1;
}

void fn_1_177F8(void)
{
    omObjData *obj;
    lbl_1_bss_9BC.unk00 = obj = omAddObjEx(lbl_1_bss_968, 256, 16, 16, -1, NULL);
    lbl_1_bss_9BC.unk04 = NULL;
    lbl_1_bss_9BC.unk00->data = &lbl_1_bss_9E4;
    fn_1_175CC(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_9BC.unk04 != NULL) {
            lbl_1_bss_9BC.unk04(obj, &lbl_1_bss_9BC);
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

void fn_1_17A70(omObjData *object)
{
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x7D : 0x7B));
    object->motion[1] = Hu3DJointMotionFile(object->model[1], DATA_MAKE_NUM(DATADIR_MSTORY2, VERSION_NTSC ? 0x7E : 0x7C));
    Hu3DModelPosSet(object->model[1], -120, 0, 800);
    Hu3DModelRotSet(object->model[1], 0, 135, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
}

void fn_1_17B98(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_994.unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_994.unk00->work[0] = arg4;
    lbl_1_bss_994.unk00->work[1] = arg1;
    lbl_1_bss_994.unk00->work[2] = arg2 + 1;
}

void fn_1_17C44(void)
{
    omObjData *obj;
    lbl_1_bss_994.unk00 = obj = omAddObjEx(lbl_1_bss_968, 256, 16, 16, -1, NULL);
    lbl_1_bss_994.unk04 = NULL;
    lbl_1_bss_994.unk00->data = &lbl_1_bss_994;
    fn_1_17A70(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_994.unk04 != NULL) {
            lbl_1_bss_994.unk04(obj, &lbl_1_bss_994);
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

void fn_1_17E64(s32 arg0)
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
            lbl_1_bss_A34.unk00 = i;
        }
    }
    for (i = 0; i < 4; i++) {
        fn_1_357C(&lbl_1_bss_A34.unk30[i], order[i]);
    }
}

void fn_1_17F48(omObjData *object)
{
    int charNo = lbl_1_bss_A34.unk30[lbl_1_bss_A34.unk00].unk10;
    object->model[1] = CharModelCreate(charNo, 1);
    object->motion[1] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00));
    object->motion[2] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18));
    object->motion[3] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x34));
    object->motion[4] = CharModelMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x48));
    CharModelVoiceEnableSet(charNo, object->motion[2], FALSE);
    CharModelMotionDataClose(charNo);
    Hu3DModelPosSet(object->model[1], 120, 0, 800);
    Hu3DModelRotSet(object->model[1], 0, -135, 0);
    Hu3DModelScaleSet(object->model[1], 1, 1, 1);
    Hu3DModelShadowSet(object->model[1]);
    fn_1_1DFC(object, 1, 1, 0, 1);
}

void fn_1_180D8(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    fn_1_1DFC(lbl_1_bss_96C.unk00, 1, arg0, arg2, arg3);
    if (arg3 == 1) {
        arg4 = 0;
    }
    lbl_1_bss_96C.unk00->work[0] = arg4;
    lbl_1_bss_96C.unk00->work[1] = arg1;
    lbl_1_bss_96C.unk00->work[2] = arg2 + 1;
}

void fn_1_18184(void)
{
    omObjData *obj;
    lbl_1_bss_96C.unk00 = obj = omAddObjEx(lbl_1_bss_968, 256, 16, 16, -1, NULL);
    lbl_1_bss_96C.unk04 = NULL;
    lbl_1_bss_96C.unk00->data = &lbl_1_bss_96C;
    fn_1_17F48(obj);
    while (1) {
        fn_1_BC8();
        if (lbl_1_bss_96C.unk04 != NULL) {
            lbl_1_bss_96C.unk04(obj, &lbl_1_bss_96C);
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

void fn_1_18408(void)
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

void fn_1_18494(void)
{
    StructBss24 *work = &lbl_1_bss_24;
    StructBss24 temp;
    if (work->unk40 == 50) {
        fn_1_1DFC(lbl_1_bss_9E4.unk00, 5, 5, 0, 0);
        fn_1_1DFC(lbl_1_bss_9E4.unk00, 6, 6, 0, 0);
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
        Hu3DData[lbl_1_bss_9E4.unk00->model[5]].rot.x = fn_1_864(0, 45, work->unk40 - 90, 90);
    }
}
