#include "game/chrman.h"
#include "game/esprite.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "REL/m401Dll.h"
#include "ext_math.h"
#include "math.h"

#ifndef __MWERKS__
#include "game/audio.h"
#endif

float lbl_2_data_0 = -7.1875f;

s16 lbl_2_data_4[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

Vec lbl_2_data_14 = { 1500, 2500, 1500 };

Vec lbl_2_data_20 = { 0, -1, 0 };

GXColor lbl_2_data_2C = { 255, 255, 255, 255 };

Vec lbl_2_data_30 = { 0, 2500, 0 };

Vec lbl_2_data_3C = { 0, 1, -1 };

Vec lbl_2_data_48 = { 0, 0, 0 };

s32 lbl_2_bss_11C;
omObjData **lbl_2_bss_118;
omObjData *lbl_2_bss_114;
omObjData *lbl_2_bss_110;
omObjData *lbl_2_bss_10C;
omObjData *lbl_2_bss_108;
omObjData *lbl_2_bss_100[2];
omObjData *lbl_2_bss_FC;
omObjData *lbl_2_bss_F8;
omObjData *lbl_2_bss_F4;
omObjData *lbl_2_bss_E4[4];
omObjData *lbl_2_bss_E0;
omObjData *lbl_2_bss_DC;
omObjData *lbl_2_bss_D8;
omObjData *lbl_2_bss_D4;
omObjData *lbl_2_bss_D0;
omObjData *lbl_2_bss_CC;
omObjData *lbl_2_bss_C8;
omObjData *lbl_2_bss_C4;
s16 lbl_2_bss_C0;
s16 lbl_2_bss_BE;
s16 lbl_2_bss_BC;
s16 lbl_2_bss_BA;
s16 lbl_2_bss_B2[4];
s16 lbl_2_bss_AA[4];
s16 lbl_2_bss_A8;
s32 lbl_2_bss_A4;
s32 lbl_2_bss_90[5];
s32 lbl_2_bss_8C;
float lbl_2_bss_88;
float lbl_2_bss_84;
Vec lbl_2_bss_78;
Vec lbl_2_bss_6C;
Vec lbl_2_bss_60;
Vec lbl_2_bss_54;
float lbl_2_bss_50;
Vec lbl_2_bss_44;
Vec lbl_2_bss_38;
Vec lbl_2_bss_2C;
Vec lbl_2_bss_20;
Process *lbl_2_bss_1C;
s16 lbl_2_bss_1A;
s16 lbl_2_bss_18;
s32 lbl_2_bss_14;
float lbl_2_bss_10;
s16 lbl_2_bss_E;
s16 lbl_2_bss_C;
omObjData *lbl_2_bss_8;
omObjData *lbl_2_bss_4;
omObjData *lbl_2_bss_0;

void fn_2_70C(omObjData *object);
void fn_2_A10(omObjData *object);
void fn_2_C1C(omObjData *object);
void fn_2_11D0(omObjData *object);

void fn_2_2FA4(omObjData *object);
void fn_2_3B24(omObjData *object);
void fn_2_48A0(omObjData *object);
void fn_2_7CB4(omObjData *object);
void fn_2_8E74(omObjData *object);
void fn_2_95E4(omObjData *object);
void fn_2_9D00(Process *objman);
void fn_2_BD90(omObjData *object);
void fn_2_C130(omObjData *object);
void fn_2_C6DC(omObjData *object);
void fn_2_D088(omObjData *object);

void fn_2_DBCC(s16 arg0);

void ObjectSetup(void)
{
    s32 i;
    omObjData *object;
    CameraData *camera;
    LightData *light;
    OSReport("**** M401ObjectSetup ****\n");
    HuMemHeapDump(HuMemHeapPtrGet(HEAP_SYSTEM), -1);
    HuMemHeapDump(HuMemHeapPtrGet(HEAP_DATA), -1);
    HuMemHeapDump(HuMemHeapPtrGet(HEAP_DVD), -1);
    lbl_2_bss_1C = omInitObjMan(60, 8192);
    omGameSysInit(lbl_2_bss_1C);
    lbl_2_bss_A8 = Hu3DGLightCreateV(&lbl_2_data_14, &lbl_2_data_20, &lbl_2_data_2C);
    Hu3DGLightInfinitytSet(lbl_2_bss_A8);
    light = &Hu3DGlobalLight[lbl_2_bss_A8];
    light->unk_00 |= 0x8000;
    Hu3DCameraCreate(1);
    camera = &Hu3DCamera[0];
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    lbl_2_bss_114 = omAddObjEx(lbl_2_bss_1C, 1000, 3, 0, -1, fn_2_BD90);
    lbl_2_bss_114->work[0] = 0;
    lbl_2_bss_110 = omAddObjEx(lbl_2_bss_1C, 10, 0, 0, -1, fn_2_70C);
    omMakeGroupEx(lbl_2_bss_1C, 0, 4);
    lbl_2_bss_118 = omGetGroupMemberListEx(lbl_2_bss_1C, 0);
    omMakeGroupEx(lbl_2_bss_1C, 1, 28);
    for (i = 0; i < 4; i++) {
        object = omAddObjEx(lbl_2_bss_1C, 1200, 4, 10, 0, fn_2_3B24);
        object->work[0] = i;
    }
    lbl_2_bss_12C = 60;
    lbl_2_bss_128 = 50;
    lbl_2_bss_124 = 25000;
    Hu3DShadowCreate(30, 20, 5000);
    Hu3DShadowTPLvlSet(0.35f);
    lbl_2_data_30.y = lbl_2_bss_60.y + 1500.0f;
    lbl_2_data_30.z = lbl_2_bss_60.z + 500.0f;
    lbl_2_data_48.y = lbl_2_bss_60.y;
    lbl_2_data_48.z = lbl_2_bss_60.z + 500.0f;
    Hu3DShadowPosSet(&lbl_2_data_30, &lbl_2_data_3C, &lbl_2_data_48);
    lbl_2_bss_10C = omAddObjEx(lbl_2_bss_1C, 500, 12, 3, -1, fn_2_2FA4);
    lbl_2_bss_108 = omAddObjEx(lbl_2_bss_1C, 1100, 1, 1, -1, fn_2_7CB4);
    lbl_2_bss_100[0] = omAddObjEx(lbl_2_bss_1C, 1110, 1, 1, -1, fn_2_8E74);
    lbl_2_bss_100[1] = omAddObjEx(lbl_2_bss_1C, 1110, 1, 1, -1, fn_2_8E74);
    lbl_2_bss_FC = omAddObjEx(lbl_2_bss_1C, 1120, 1, 2, -1, fn_2_95E4);
    lbl_2_bss_C8 = omAddObjEx(lbl_2_bss_1C, 100, 0, 0, -1, fn_2_D088);
    lbl_2_bss_E0 = omAddObjEx(lbl_2_bss_1C, 1500, 0, 0, -1, fn_2_C1C);
    fn_2_DBCC(90);
    lbl_2_bss_F8 = omAddObjEx(lbl_2_bss_1C, 500, 9, 0, -1, fn_2_C6DC);
    fn_2_9D00(lbl_2_bss_1C);
    fn_2_1041C();
    fn_2_1079C();
    lbl_2_bss_F4 = fn_2_14640(lbl_2_bss_1C);
    lbl_2_bss_50 = 0;
    lbl_2_bss_54 = camera->pos;
    Hu3DReflectNoSet(0);
    lbl_2_bss_120 = 0;
    lbl_2_bss_BE = 0;
    lbl_2_bss_BA = 0;
    Hu3DFogSet(3000, 10000, 10, 60, 160);
    Hu3DBGColorSet(10, 60, 160);
    lbl_2_bss_88 = 3000;
    lbl_2_bss_84 = 142000;
    lbl_2_bss_11C = HuAudFXPlay(1290);
}

void fn_2_70C(omObjData *object)
{
    s32 temp_r31;
    M401WorkPlayer *temp_r30;
    s16 temp_r29;
    switch (lbl_2_bss_120) {
        case 0:
            break;

        case 1:
            if (lbl_2_bss_BE == 1) {
                lbl_2_bss_120 = 2;
                lbl_2_bss_C0 = MGSeqFinishCreate();
                HuAudSeqFadeOut(lbl_2_bss_A4, 100);
            }
            break;

        case 2:
            if (lbl_2_bss_114 == NULL) {
                lbl_2_bss_114 = omAddObjEx(HuPrcCurrentGet(), 1000, 0, 0, -1, fn_2_C130);
                lbl_2_bss_114->work[0] = 0;
                temp_r29 = 0;
                lbl_2_bss_BA = 0;
                for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                    temp_r30 = lbl_2_bss_118[temp_r31]->data;
                    lbl_2_bss_118[temp_r31]->func = fn_2_48A0;
                    temp_r30->unk0 = 5;
                    temp_r30->unk68 = 0;
                    if (temp_r30->unk72 > temp_r29) {
                        temp_r29 = temp_r30->unk72;
                    }
                    lbl_2_bss_B2[temp_r31] = -1;
                    lbl_2_bss_AA[temp_r31] = -1;
                }
                if (temp_r29 > 0) {
                    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                        temp_r30 = lbl_2_bss_118[temp_r31]->data;
                        if (temp_r30->unk72 == temp_r29) {
                            lbl_2_bss_AA[lbl_2_bss_BA] = GWPlayerCfg[temp_r31].character;
                            lbl_2_bss_B2[lbl_2_bss_BA++] = temp_r31;
                            temp_r30->unk68 = 1;
                        }
                    }
                }
                OSReport("winnercnt:%d\n", lbl_2_bss_BA);
            }
            break;
    }
    if (omSysExitReq) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        HuAudSeqFadeOut(lbl_2_bss_A4, 100);
        HuAudFXStop(lbl_2_bss_11C);
        object->func = fn_2_A10;
    }
}

void fn_2_A10(omObjData *object)
{
    s32 i;
    if (!WipeStatGet()) {
        fn_2_10710();
        for (i = 0; i < 4; i++) {
            CharModelKill(lbl_2_data_4[GWPlayerCfg[i].character]);
        }
        HuAudFXListnerKill();
        omOvlReturnEx(1, 1);
    }
}

void fn_2_A98(void)
{
    Hu3DFogSet(3000, 10000, 10, 60, 160);
    Hu3DBGColorSet(10, 60, 160);
}

typedef struct m401_work_2d {
    s16 unk0[4];
    s16 unk8[4][3];
    u8 unk20[0x30];
    s16 unk50[4][3];
    s16 unk68[4][3];
    s16 unk80[4];
    s16 unk88[4];
    float unk90[4];
    float unkA0[4];
    float unkB0[4];
    float unkC0[4];
    float unkD0[4];
    float unkE0[4];
    float unkF0[4];
    float unk100[4];
    float unk110[4];
    float unk120[4];
    s16 unk130[4];
    s16 unk138[4];
    s16 unk140[4];
} M401Work2D;

void fn_2_AEC(s16 arg0)
{
    M401Work2D *temp_r31;
    s32 i;
    s32 j;
    temp_r31 = lbl_2_bss_E0->data;
    if (arg0) {
        for (i = 0; i < 4; i++) {
            espDispOn(temp_r31->unk0[i]);
            espDispOn(temp_r31->unk80[i]);
            espDispOn(temp_r31->unk88[i]);
            for (j = 0; j < 2; j++) {
                espDispOn(temp_r31->unk8[i][j]);
            }
        }
    }
    else {
        for (i = 0; i < 4; i++) {
            espDispOff(temp_r31->unk0[i]);
            espDispOff(temp_r31->unk80[i]);
            espDispOff(temp_r31->unk88[i]);
            for (j = 0; j < 2; j++) {
                espDispOff(temp_r31->unk8[i][j]);
            }
        }
    }
}

s32 lbl_2_data_80[] = {
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x00),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x01),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x02),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x03),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x04),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x05),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x06),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x07),
};

#define PLAYER_POS_X(index, left, width) ((((index)&1) * width) + left)
#define PLAYER_POS_Y(index, top, height) ((((index) > 1) * height) + top)

void fn_2_C1C(omObjData *object)
{
    M401Work2D *temp_r31;
    s32 i;
    s32 j;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M401Work2D), MEMORY_DEFAULT_NUM);
    temp_r31 = object->data;
    for (i = 0; i < 4; i++) {
        temp_r31->unk0[i] = espEntry(lbl_2_data_80[GWPlayerCfg[i].character], 2, 0);
        espDispOff(temp_r31->unk0[i]);
        espDrawNoSet(temp_r31->unk0[i], 0);
        espPosSet(temp_r31->unk0[i], PLAYER_POS_X(i, 37, 438), PLAYER_POS_Y(i, 59, 358));
        temp_r31->unk80[i] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2F), 3, 0);
        espDispOff(temp_r31->unk80[i]);
        espDrawNoSet(temp_r31->unk80[i], 0);
        espPosSet(temp_r31->unk80[i], PLAYER_POS_X(i, 73, 438), PLAYER_POS_Y(i, 61, 358));
        temp_r31->unk88[i] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x30), 4, 0);
        espDispOff(temp_r31->unk88[i]);
        espDrawNoSet(temp_r31->unk88[i], 0);
        espPosSet(temp_r31->unk88[i], PLAYER_POS_X(i, 73, 438), PLAYER_POS_Y(i, 61, 358));
        espColorSet(temp_r31->unk88[i], 0, 0, 0);
        espTPLvlSet(temp_r31->unk88[i], 0.5f);
        for (j = 0; j < 2; j++) {
            temp_r31->unk8[i][j] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2E), 1, 0);
            espDispOff(temp_r31->unk8[i][j]);
            espDrawNoSet(temp_r31->unk8[i][j], 0);
            espPosSet(temp_r31->unk8[i][j], PLAYER_POS_X(i, 69 + (j * 20), 438), PLAYER_POS_Y(i, 63, 358));
            espAttrSet(temp_r31->unk8[i][j], HUSPR_ATTR_NOANIM);
        }
        for (j = 0; j < 3; j++) {
            temp_r31->unk50[i][j] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2D), 0, 0);
            espDispOff(temp_r31->unk50[i][j]);
            espDrawNoSet(temp_r31->unk50[i][j], 0);
            espAttrSet(temp_r31->unk50[i][j], HUSPR_ATTR_NOANIM);
            temp_r31->unk68[i][j] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2D), 0, 0);
            espDispOff(temp_r31->unk68[i][j]);
            espDrawNoSet(temp_r31->unk68[i][j], 0);
            espAttrSet(temp_r31->unk68[i][j], HUSPR_ATTR_NOANIM);
        }
        espBankSet(temp_r31->unk50[i][0], 10);
        espBankSet(temp_r31->unk68[i][0], 11);
        temp_r31->unk90[i] = 1.0f;
        temp_r31->unkA0[i] = 1.0f;
        temp_r31->unk130[i] = 0;
        temp_r31->unk138[i] = 0;
    }
    object->func = fn_2_11D0;
}

void fn_2_15C4(s16 arg0);

void fn_2_11D0(omObjData *object)
{
    M401Work2D *temp_r31;
    s32 i;
    s32 j;
    omObjData *temp_r28;
    Vec sp18;
    Vec spC;
    M401WorkPlayer *sp8;
    temp_r31 = object->data;
    for (i = 0; i < 4; i++) {
        sp8 = lbl_2_bss_118[i]->data;
        if (temp_r31->unk130[i]) {
            temp_r28 = lbl_2_bss_118[i];
            sp18.x = temp_r28->trans.x;
            sp18.y = temp_r28->trans.y;
            sp18.z = temp_r28->trans.z;
            fn_2_10240(&sp18, &spC);
            for (j = 0; j < 3; j++) {
                espPosSet(temp_r31->unk50[i][j], (-20.0f + spC.x + temp_r31->unkF0[i]) + (j * 16), 20.0f + spC.y + temp_r31->unk100[i]);
                espTPLvlSet(temp_r31->unk50[i][j], temp_r31->unk90[i]);
            }
            temp_r31->unkC0[i] -= 0.5f;
            temp_r31->unk100[i] -= 1.0f;
            if (temp_r31->unk130[i] < 15) {
                temp_r31->unk90[i] -= 1.0f / 15.0f;
            }
            if (--temp_r31->unk130[i] == 0) {
                espDispOff(temp_r31->unk50[i][0]);
                espDispOff(temp_r31->unk50[i][1]);
            }
        }
        if (temp_r31->unk138[i]) {
            temp_r28 = lbl_2_bss_118[i];
            sp18.x = temp_r28->trans.x;
            sp18.y = temp_r28->trans.y;
            sp18.z = temp_r28->trans.z;
            fn_2_10240(&sp18, &spC);
            for (j = 0; j < 2; j++) {
                espPosSet(temp_r31->unk68[i][j], (-20.0f + spC.x + temp_r31->unk110[i]) + (j * 16), -20.0f + spC.y + temp_r31->unk120[i]);
                espTPLvlSet(temp_r31->unk68[i][j], temp_r31->unkA0[i]);
            }
            temp_r31->unkE0[i] += 0.5f;
            temp_r31->unk120[i] += 1.0f;
            if (temp_r31->unk138[i] < 15) {
                temp_r31->unkA0[i] -= 1.0f / 15.0f;
            }
            if (--temp_r31->unk138[i] == 0) {
                espDispOff(temp_r31->unk68[i][0]);
                espDispOff(temp_r31->unk68[i][1]);
            }
        }
        fn_2_15C4(i);
    }
}

void fn_2_15C4(s16 arg0)
{
    M401Work2D *temp_r31;
    s32 temp_r30;
    M401WorkPlayer *temp_r29;
    temp_r31 = lbl_2_bss_E0->data;
    temp_r29 = lbl_2_bss_118[arg0]->data;
    temp_r30 = temp_r29->unk72;
    espBankSet(temp_r31->unk8[arg0][0], temp_r30 / 10);
    espBankSet(temp_r31->unk8[arg0][1], temp_r30 % 10);
}

void fn_2_169C(s16 arg0)
{
    M401Work2D *temp_r31;
    s32 i;
    M401WorkPlayer *temp_r28;
    temp_r31 = lbl_2_bss_E0->data;
    temp_r28 = lbl_2_bss_118[arg0]->data;
    for (i = 0; i < 2; i++) {
        espDispOn(temp_r31->unk50[arg0][i]);
    }
    temp_r31->unk90[arg0] = 1;
    temp_r31->unkC0[arg0] = PLAYER_POS_Y(arg0, 52, 398);
    temp_r31->unkB0[arg0] = PLAYER_POS_X(arg0, 41, 442);
    temp_r31->unk100[arg0] = 0;
    temp_r31->unkF0[arg0] = 0;
    espBankSet(temp_r31->unk50[arg0][1], temp_r28->unk74);
    temp_r31->unk130[arg0] = 45;
}

void fn_2_1858(s16 arg0, s16 arg1)
{
    M401Work2D *temp_r31;
    M401WorkPlayer *temp_r29;
    s32 i;
    temp_r31 = lbl_2_bss_E0->data;
    temp_r29 = lbl_2_bss_118[arg0]->data;
    for (i = 0; i < 2; i++) {
        espDispOn(temp_r31->unk68[arg0][i]);
    }
    temp_r31->unkA0[arg0] = 1;
    temp_r31->unkE0[arg0] = PLAYER_POS_Y(arg0, 20, 398);
    temp_r31->unkD0[arg0] = PLAYER_POS_X(arg0, 41, 442);
    temp_r31->unk120[arg0] = 0;
    temp_r31->unk110[arg0] = 0;
    espBankSet(temp_r31->unk68[arg0][1], arg1);
    temp_r31->unk138[arg0] = 45;
    temp_r31->unk140[arg0] = arg1;
    temp_r29->unk72 -= arg1;
    if (temp_r29->unk72 < 0) {
        temp_r29->unk72 = 0;
    }
}

float lbl_2_data_A0[] = { -500, -8500, -17500, -26500, -99000 };

float lbl_2_data_B4[] = { -9100, -18100, -27100, -36100, -45100, -100000 };

void fn_2_1A38(omObjData *object);
void fn_2_1B80(omObjData *object);
void fn_2_1CF0(omObjData *object);
void fn_2_1DE8(omObjData *object);
void fn_2_20B0(omObjData *object);
void fn_2_2CBC(omObjData *object);
void fn_2_2D64(omObjData *object);
void fn_2_2DCC(omObjData *object);
void fn_2_2E20(omObjData *object);
void fn_2_2ED0(omObjData *object);

omObjFunc lbl_2_data_CC[][2] = { fn_2_1A38, fn_2_2CBC, fn_2_1B80, fn_2_2D64, fn_2_1CF0, fn_2_2DCC, fn_2_1DE8, fn_2_2E20, fn_2_20B0, fn_2_2ED0 };

char *lbl_2_data_124[] = { "kaitei01", "kaitei02", "kaitei03", "kaitei04", "kaitei05" };

s32 lbl_2_data_138[] = {
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
};

omObjData *fn_2_FC40(s16 arg0, Vec *arg1, Vec *arg2, Vec *arg3);
void fn_2_E6BC(omObjData *object, float arg2, float arg3, float arg4, float arg5, float arg6);

void fn_2_1A38(omObjData *object)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    HsfObject *temp_r31 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[0]);
    omObjData *temp_r30;
    temp_r31->type = 2;
    sp20.x = -2500;
    sp20.y = 150;
    sp20.z = -6800;
    sp14.x = 50;
    sp14.y = 50;
    sp14.z = 50;
    sp8.x = 1500;
    sp8.y = 150;
    sp8.z = -4800;
    temp_r30 = fn_2_FC40(18, &sp20, &sp14, &sp8);
    fn_2_E6BC((omObjData *)temp_r30->work[0], 5, 1.5, 0.2, 0.8, 3);
}

void fn_2_1B80(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    omObjData *temp_r31;
    HsfObject *temp_r30 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[1]);
    temp_r30->type = 2;
    sp14.x = -1000;
    sp14.y = 0;
    sp14.z = -9100;
    sp8.x = 150;
    sp8.y = 100;
    sp8.z = 100;
    temp_r31 = fn_2_FC40(14, &sp14, &sp8, &sp14);
    omSetRot(temp_r31, 3, 0, 0);
    omSetSca(temp_r31, 0, 0, 50);
    fn_2_E6BC((omObjData *)temp_r31->work[0], 4.5, 2.5, 0.08, 0.9, 1);
}

void fn_2_1CF0(omObjData *object)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    HsfObject *temp_r31 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[2]);
    temp_r31->type = 2;
    sp20.x = 500;
    sp20.y = 0;
    sp20.z = -24300;
    sp14.x = 200;
    sp14.y = 100;
    sp14.z = 100;
    sp8.x = 1000;
    sp8.y = 0;
    sp8.z = -16300;
    fn_2_FC40(40, &sp20, &sp14, &sp8);
}

void fn_2_91AC(omObjData *object, Vec *pos);

void fn_2_1DE8(omObjData *object)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    omObjData *temp_r31;
    HsfObject *temp_r30 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[3]);
    temp_r30->type = 2;
    sp2C.x = 0;
    sp2C.y = -150.0f + ((1.0f / 255.0f) * (300.0f * frandu8()));
    sp2C.z = -23000;
    fn_2_91AC(lbl_2_bss_100[0], &sp2C);
    sp2C.x = 0;
    sp2C.y = -150.0f + ((1.0f / 255.0f) * (300.0f * frandu8()));
    sp2C.z = -25000;
    fn_2_91AC(lbl_2_bss_100[1], &sp2C);
    sp2C.x = 5500;
    sp2C.y = 0;
    sp2C.z = -29800;
    sp20.x = 100;
    sp20.y = 100;
    sp20.z = 100;
    sp14.x = -1500;
    sp14.y = 0;
    sp14.z = -24900;
    temp_r31 = fn_2_FC40(20, &sp2C, &sp20, &sp14);
    fn_2_E6BC((omObjData *)temp_r31->work[0], 6, 1.5f, 0.2f, 0.8f, 3.5f);
    sp8.x = -650;
    sp8.y = -360;
    sp8.z = -26300;
    lbl_2_bss_D0 = fn_2_10A88(&sp8, 3);
    lbl_2_bss_90[0] = HuAudFXEmiterPlay(1291, &sp8);
}

void fn_2_20B0(omObjData *object)
{
    Vec sp8;
    HsfObject *temp_r30 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[4]);
    temp_r30->type = 2;
    Hu3DModelAttrReset(object->model[7], HU3D_ATTR_DISPOFF);
    sp8.x = 0;
    sp8.y = -370;
    sp8.z = -43000;
    lbl_2_bss_8 = fn_2_10A88(&sp8, 3);
    lbl_2_bss_90[1] = HuAudFXEmiterPlay(1291, &sp8);
    sp8.x = 380;
    sp8.y = -440;
    sp8.z = -32000;
    lbl_2_bss_CC = fn_2_10A88(&sp8, 3);
    lbl_2_bss_90[2] = HuAudFXEmiterPlay(1291, &sp8);
    Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_CLUSTER_ATTR_LOOP);
}

void fn_2_21F8(omObjData *object)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s32 temp_r30;
    HsfObject *temp_r29 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[0]);
    s32 temp_r28;
    temp_r29->type = 2;
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(object->model[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->model[1], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(object->model[3], HU3D_ATTR_DISPOFF);
    lbl_2_bss_44.x = 0;
    lbl_2_bss_44.y = 100;
    lbl_2_bss_44.z = 0;
    lbl_2_bss_38.x = 0;
    lbl_2_bss_38.y = 1000;
    lbl_2_bss_38.z = -1500;
    lbl_2_bss_2C.x = 0;
    lbl_2_bss_2C.y = 1;
    lbl_2_bss_2C.z = 0;
    Hu3DCameraPosSetV(1, &lbl_2_bss_44, &lbl_2_bss_2C, &lbl_2_bss_38);
    Hu3DCameraPerspectiveSet(1, lbl_2_bss_12C, lbl_2_bss_128, lbl_2_bss_124, 1.2f);
    lbl_2_bss_54 = lbl_2_bss_44;
    fn_2_D088(NULL);
    sp20 = lbl_2_bss_44;
    VECSubtract(&lbl_2_bss_38, &lbl_2_bss_44, &sp2C);
    VECNormalize(&sp2C, &sp2C);
    HuAudFXListnerSetEX(&sp20, &sp2C, lbl_2_bss_88, lbl_2_bss_84, 300, 300, 300);
    sp14.x = 300;
    sp14.y = -450;
    sp14.z = -3100;
    lbl_2_bss_D8 = fn_2_10A88(&sp14, 3);
    lbl_2_bss_90[0] = HuAudFXEmiterPlay(1291, &sp14);
    sp14.x = -300;
    sp14.y = -340;
    sp14.z = -4720;
    lbl_2_bss_D4 = fn_2_10A88(&sp14, 3);
    lbl_2_bss_90[1] = HuAudFXEmiterPlay(1291, &sp14);
    Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_CLUSTER_ATTR_LOOP);
    temp_r28 = 4;
    for (temp_r30 = 0; temp_r30 < temp_r28; temp_r30++) {
        sp8.x = -340.0f + ((1.0f / 255.0f) * (680.0f * frandu8()));
        sp8.y = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
        sp8.z = ((-1550.0f - (temp_r30 * 260)) - 40.0f) + ((1.0f / 255.0f) * (80.0f * frandu8()));
        fn_2_10A88(&sp8, 0);
    }
}

typedef struct work_2FA4 {
    s32 unk0;
    float unk4;
    Vec unk8;
    Vec unk14[2];
    s16 unk2C;
} Work2FA4;

void fn_2_26E0(omObjData *object)
{
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    Work2FA4 *temp_r30;
    s32 temp_r29;
    Hu3DModelAttrReset(object->model[4], HU3D_ATTR_DISPOFF);
    Hu3DModelClusterAttrSet(object->model[4], 0, 0xC0000001);
    Hu3DModelAttrReset(object->model[8], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[8], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->model[4], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowMapSet(object->model[4]);
    Hu3DModelAttrReset(object->model[5], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(object->model[4], 0, 0, 0);
    Hu3DModelAmbSet(object->model[4], 1, 1, 1);
    Hu3DModelPosSet(object->model[5], 0, 0, 0);
    Hu3DModelPosSet(object->model[6], 0, 0, 0);
    temp_r30 = lbl_2_bss_10C->data;
    if (lbl_2_bss_BA) {
        temp_r30->unk14[0].x = 210;
        temp_r30->unk14[0].y = 1018;
        temp_r30->unk14[0].z = 0;
        temp_r30->unk14[1].x = -160;
        temp_r30->unk14[1].y = 1020;
        temp_r30->unk14[1].z = -50;
        for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
            Hu3DModelPosSet(object->model[temp_r29 + 9], temp_r30->unk14[temp_r29].x, temp_r30->unk14[temp_r29].y, temp_r30->unk14[temp_r29].z);
            Hu3DModelAttrReset(object->model[temp_r29 + 9], HU3D_ATTR_DISPOFF);
        }
        Hu3DMotionSet(object->model[10], object->motion[0]);
        Hu3DMotionSet(object->model[9], object->motion[2]);
    }
    else {
        temp_r30->unk14[0].x = 210;
        temp_r30->unk14[0].y = 1018;
        temp_r30->unk14[0].z = 0;
        temp_r30->unk14[1].x = -160;
        temp_r30->unk14[1].y = 1020;
        temp_r30->unk14[1].z = -50;
        for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
            Hu3DModelPosSet(object->model[temp_r29 + 9], temp_r30->unk14[temp_r29].x, temp_r30->unk14[temp_r29].y, temp_r30->unk14[temp_r29].z);
            Hu3DModelAttrReset(object->model[temp_r29 + 9], HU3D_ATTR_DISPOFF);
        }
        Hu3DMotionSet(object->model[10], object->motion[1]);
        Hu3DMotionSet(object->model[9], object->motion[2]);
    }
    Hu3DModelAttrSet(object->model[9], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->model[10], HU3D_MOTATTR_LOOP);
    Hu3DModelRotSet(object->model[9], 0, 90, 0);
    Hu3DModelPosSet(object->model[11], 210, 1018, 0);
    Hu3DModelRotSet(object->model[11], 0, 90, 0);
    Hu3DModelAttrReset(object->model[11], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[11], HU3D_MOTATTR_LOOP);
    sp2C.x = 0;
    sp2C.y = 1300;
    sp2C.z = 1300;
    sp20.x = 0;
    sp20.y = 920;
    sp20.z = -100;
    sp14.x = 0;
    sp14.y = 1;
    sp14.z = 0;
    Hu3DCameraPosSetV(1, &sp2C, &sp14, &sp20);
    lbl_2_bss_12C = 45;
    Hu3DShadowData.unk_08.x = lbl_2_bss_12C;
    MTXLightPerspective(Hu3DShadowData.unk_68, lbl_2_bss_12C, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    Hu3DCameraPerspectiveSet(1, lbl_2_bss_12C, lbl_2_bss_128, lbl_2_bss_124, 1.2f);
    VECSubtract(&sp20, &sp2C, &sp8);
    VECNormalize(&sp8, &sp8);
    HuAudFXListnerUpdate(&sp2C, &sp8);
}

void fn_2_2CBC(omObjData *object)
{
    HsfObject *temp_r30 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[0]);
    temp_r30->type = -1;
    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
    lbl_2_bss_D8->work[0] = 1;
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
    HuAudFXStop(lbl_2_bss_90[0]);
    HuAudFXStop(lbl_2_bss_90[1]);
}

void fn_2_2D64(omObjData *object)
{
    HsfObject *temp_r31 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[1]);
    temp_r31->type = -1;
    lbl_2_bss_D4->work[0] = 1;
}

void fn_2_2DCC(omObjData *object)
{
    HsfObject *temp_r31 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[2]);
    temp_r31->type = -1;
}

void fn_2_2E20(omObjData *object)
{
    HsfObject *temp_r30 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[3]);
    temp_r30->type = -1;
    Hu3DModelAttrSet(lbl_2_bss_100[0]->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_2_bss_100[1]->model[0], HU3D_ATTR_DISPOFF);
    lbl_2_bss_D0->work[0] = 1;
    HuAudFXStop(lbl_2_bss_90[0]);
}

void fn_2_2ED0(omObjData *object)
{
    HsfObject *temp_r30 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[4]);
    temp_r30->type = -1;
    Hu3DModelAttrSet(object->model[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    lbl_2_bss_8->work[0] = 1;
    lbl_2_bss_CC->work[0] = 1;
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
    HuAudFXStop(lbl_2_bss_90[1]);
    HuAudFXStop(lbl_2_bss_90[2]);
}

void fn_2_2F9C(omObjData *object) { }

void fn_2_2FA0(omObjData *object) { }

void fn_2_33B4(omObjData *object);

void fn_2_2FA4(omObjData *object)
{
    Work2FA4 *temp_r30;
    s32 temp_r29;
    HsfObject *temp_r28;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work2FA4), MEMORY_DEFAULT_NUM);
    temp_r30 = object->data;
    fn_2_D088(NULL);
    temp_r30->unk0 = 0;
    temp_r30->unk8.x = 0;
    temp_r30->unk8.y = 0;
    temp_r30->unk8.z = 0;
    temp_r30->unk2C = 0;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x00));
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x01));
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x07));
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_MOTATTR_LOOP);
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x1F));
    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x20));
    Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF);
    object->model[11] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x2C));
    Hu3DModelAttrSet(object->model[11], HU3D_ATTR_DISPOFF);
    object->model[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x03));
    Hu3DModelAttrSet(object->model[7], HU3D_ATTR_DISPOFF);
    object->model[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x23));
    Hu3DModelAttrSet(object->model[8], HU3D_ATTR_DISPOFF);
    object->model[9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x28));
    Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF);
    object->model[10] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x28));
    Hu3DModelAttrSet(object->model[10], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(object->model[10]);
    object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x21));
    Hu3DModelAttrSet(object->model[5], HU3D_ATTR_DISPOFF);
    object->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x22));
    Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF);
    object->motion[0] = Hu3DJointMotionFile(object->model[10], DATA_MAKE_NUM(DATADIR_M401, 0x29));
    object->motion[1] = Hu3DJointMotionFile(object->model[10], DATA_MAKE_NUM(DATADIR_M401, 0x2A));
    object->motion[2] = Hu3DJointMotionFile(object->model[9], DATA_MAKE_NUM(DATADIR_M401, 0x2B));
    Hu3DModelPosSet(object->model[1], 0, 0, -1500);
    Hu3DModelShadowMapSet(object->model[0]);
    for (temp_r29 = 0; temp_r29 < 5; temp_r29++) {
        temp_r28 = Hu3DModelObjPtrGet(object->model[0], lbl_2_data_124[temp_r29]);
        temp_r28->type = -1;
    }
    fn_2_21F8(object);
    object->func = fn_2_33B4;
}

void fn_2_33B4(omObjData *object)
{
    Hu3DModelPosSet(object->model[3], 110, 5.0 * sind(lbl_2_bss_10), -1500);
    lbl_2_bss_10 += 2.0f;
    if (lbl_2_bss_10 >= 360.0f) {
        lbl_2_bss_10 -= 360.0f;
    }
}

void fn_2_9E28(float arg1, float arg2);

void fn_2_34B8(omObjData *object)
{
    Vec sp8;
    Work2FA4 *temp_r31;
    s32 temp_r30;
    s32 temp_r28;
    temp_r31 = object->data;
    if (lbl_2_bss_60.z < -5000.0f && temp_r31->unk0 == 0) {
        temp_r31->unk0 = 1;
        fn_2_9E28(-15500, -20000);
    }
    if (lbl_2_bss_6C.z <= lbl_2_data_A0[lbl_2_bss_C]) {
        lbl_2_bss_C++;
        lbl_2_data_CC[lbl_2_bss_C][0](object);
    }
    if (lbl_2_bss_6C.z <= lbl_2_data_B4[lbl_2_bss_E]) {
        lbl_2_data_CC[lbl_2_bss_E][1](object);
        lbl_2_bss_E++;
    }
    if (lbl_2_bss_6C.z <= -40000.0f) {
        lbl_2_bss_BE = 1;
    }
    if (temp_r31->unk2C) {
        temp_r31->unk2C--;
    }
    else {
        temp_r31->unk2C = 274;
        if (lbl_2_bss_60.z > -31260.0f) {
            temp_r28 = 4;
            for (temp_r30 = 0; temp_r30 < temp_r28; temp_r30++) {
                sp8.x = -340.0f + ((1.0f / 255.0f) * (680.0f * frandu8()));
                sp8.y = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
                sp8.z = ((-4000.0f - (temp_r30 * 240)) - 40.0f) + ((1.0f / 255.0f) * (80.0f * frandu8()));
                fn_2_10A88(&sp8, 0);
            }
        }
    }
}

void fn_2_3838(omObjData *object)
{
    Work2FA4 *temp_r31;
    s32 temp_r29;
    float temp_f31;
    temp_r31 = object->data;
    temp_r31->unk4 = 5.0 * sind(temp_r31->unk8.x);
    temp_r31->unk8.y += temp_r31->unk8.z;
    Hu3DModelPosSet(object->model[4], temp_r31->unk8.y, temp_r31->unk4, 0);
    Hu3DModelPosSet(object->model[5], temp_r31->unk8.y, 0, 0);
    Hu3DModelScaleSet(object->model[5], 1.0f - (0.09f * (temp_r31->unk4 / 5.0f)), 1.0f, 1.0f - (0.09f * (temp_r31->unk4 / 5.0f)));
    for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
        temp_f31 = temp_r31->unk14[temp_r29].y + (5.0 * sind(temp_r31->unk8.x));
        temp_r31->unk14[temp_r29].x += temp_r31->unk8.z;
        Hu3DModelPosSet(object->model[temp_r29 + 9], temp_r31->unk14[temp_r29].x, temp_f31, temp_r31->unk14[temp_r29].z);
    }
    Hu3DModelPosSet(object->model[11], temp_r31->unk14[0].x, temp_f31, temp_r31->unk14[0].z);
    temp_r31->unk8.z *= 1.04f;
    if (temp_r31->unk8.z > 12.0f) {
        temp_r31->unk8.z = 12.0f;
    }
    temp_r31->unk8.x += 2.0f;
    if (temp_r31->unk8.x >= 360.0f) {
        temp_r31->unk8.x -= 360.0f;
    }
    lbl_2_data_30.x = temp_r31->unk8.y;
    lbl_2_data_48.x = temp_r31->unk8.y;
    Hu3DShadowPosSet(&lbl_2_data_30, &lbl_2_data_3C, &lbl_2_data_48);
}

void fn_2_3F28(omObjData *object);

s32 lbl_2_data_158[][10] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x31),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x39),
    DATA_MAKE_NUM(DATADIR_M401, 0x41),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x49),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x32),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3A),
    DATA_MAKE_NUM(DATADIR_M401, 0x42),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4A),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x33),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3B),
    DATA_MAKE_NUM(DATADIR_M401, 0x43),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4B),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x34),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3C),
    DATA_MAKE_NUM(DATADIR_M401, 0x44),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4C),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x35),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3D),
    DATA_MAKE_NUM(DATADIR_M401, 0x45),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4D),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x36),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3E),
    DATA_MAKE_NUM(DATADIR_M401, 0x46),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4E),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x37),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3F),
    DATA_MAKE_NUM(DATADIR_M401, 0x47),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4F),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x38),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x40),
    DATA_MAKE_NUM(DATADIR_M401, 0x48),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x50),
};

Vec lbl_2_data_298[] = {
    -150,
    1250,
    -1400,
    -50,
    1250,
    -1400,
    50,
    1250,
    -1400,
    150,
    1250,
    -1400,
};

Vec lbl_2_data_2C8[] = {
    -300,
    0,
    -1500,
    -100,
    0,
    -1500,
    100,
    0,
    -1500,
    300,
    0,
    -1500,
};

void fn_2_3F28(omObjData *object);

void fn_2_3B24(omObjData *object)
{
    M401WorkPlayer *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M401WorkPlayer), MEMORY_DEFAULT_NUM);
    temp_r31 = object->data;
    temp_r29 = object->work[0];
    temp_r31->unk4 = temp_r29;
    temp_r31->unk8 = GWPlayerCfg[temp_r29].pad_idx;
    temp_r27 = GWPlayerCfg[temp_r29].character;
    temp_r31->unk86 = lbl_2_data_4[temp_r27];
    object->model[0] = CharModelCreate(temp_r31->unk86, 4);
    if (temp_r29 == 0) {
        object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x25));
        object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x27));
    }
    else {
        object->model[2] = Hu3DModelLink(lbl_2_bss_118[0]->model[2]);
        object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x27));
    }
    Hu3DModelAttrSet(object->model[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelClusterAttrSet(object->model[3], 0, 0xC0000002);
    Hu3DModelLayerSet(object->model[3], 7);
    for (temp_r28 = 0; temp_r28 < 10; temp_r28++) {
        object->motion[temp_r28] = CharModelMotionCreate(lbl_2_data_4[temp_r27], lbl_2_data_158[temp_r27][temp_r28]);
    }
    CharModelMotionSet(temp_r31->unk86, object->motion[2]);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->model[2], 2);
    Hu3DModelAmbSet(object->model[0], 1, 1, 1);
    Hu3DModelShadowSet(object->model[0]);
    CharModelVoiceEnableSet(lbl_2_data_4[temp_r27], object->motion[4], 0);
    temp_r31->unkC = lbl_2_data_2C8[temp_r29];
    temp_r31->unk58.z = 0;
    omSetTra(object, lbl_2_data_298[temp_r29].x, lbl_2_data_298[temp_r29].y, lbl_2_data_298[temp_r29].z);
    temp_r31->unk0 = 0;
    temp_r31->unk6E = 70;
    temp_r31->unk24.x = lbl_2_data_2C8[temp_r29].x;
    temp_r31->unk24.y = lbl_2_data_2C8[temp_r29].y;
    temp_r31->unk24.z = 800 + lbl_2_data_2C8[temp_r29].z;
    temp_r31->unk6A = 0;
    temp_r31->unk72 = 0;
    temp_r31->unk74 = 0;
    temp_r31->unk78 = 0;
    temp_r31->unk7A = 0;
    temp_r31->unk7C = 0;
    temp_r31->unk76 = 0;
    temp_r31->unk88 = 0;
    temp_r31->unk84 = 0;
    temp_r31->unk8C = 0;
    temp_r31->unk8E = 0;
    temp_r31->unk94.x = temp_r31->unk94.y = temp_r31->unk94.z = 0;
    temp_r31->unk90 = 0;
    temp_r31->unkA0 = temp_r31->unkA1 = 0;
    CharModelMotionDataClose(temp_r31->unk86);
    object->func = fn_2_3F28;
}

void fn_2_6B44(omObjData *object);
void fn_2_D3E8(omObjData *object);

void fn_2_3F28(omObjData *object)
{
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    M401WorkPlayer *temp_r31;
    CameraData *temp_r29;
    omObjData *temp_r28;
    UnkWork10A88 *temp_r27;
    float temp_f27;
    temp_r31 = object->data;
    switch (temp_r31->unk0) {
        case 0:
            if (--temp_r31->unk6E == 0) {
                temp_r31->unk0 = 1;
                CharModelMotionShiftSet(temp_r31->unk86, object->motion[4], 0, 20, HU3D_MOTATTR_NONE);
                temp_r31->unk58.x = 16;
                temp_r31->unk58.y = 0;
            }
            break;

        case 1:
            if (object->trans.y < 1100) {
                temp_r31->unk0 = 2;
                temp_f27 = VECMagPoint(object->trans.x - temp_r31->unk24.x, object->trans.y - temp_r31->unk24.y, object->trans.z - temp_r31->unk24.z);
                temp_r31->unk58.z = temp_f27;
                temp_r31->unk58.y = 0;
                temp_r31->unk6E = 110;
                temp_r28 = fn_2_10A88(&lbl_2_data_298[temp_r31->unk4], 2);
                temp_r31->unk50 = temp_r28;
                temp_r27 = temp_r28->data;
                temp_r27->unkC = object;
                fn_2_6B44(object);
                temp_r28 = fn_2_10A88(&lbl_2_data_298[temp_r31->unk4], 4);
                temp_r27 = temp_r28->data;
                temp_r27->unkC = object;
                temp_r31->unk4C = temp_r28;
                temp_r28 = fn_2_10A88(&lbl_2_data_298[temp_r31->unk4], 5);
                temp_r27 = temp_r28->data;
                temp_r27->unkC = object;
                temp_r31->unk48 = temp_r28;
                CharModelMotionShiftSet(temp_r31->unk86, object->motion[1], 0, 80, HU3D_MOTATTR_LOOP);
                temp_r31->unk30.x = object->trans.x;
                temp_r31->unk30.y = object->trans.y;
                temp_r31->unk30.z = object->trans.z;
                Hu3DModelAttrReset(object->model[3], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(object->model[3], HU3D_MOTATTR_PAUSE);
                Hu3DModelClusterAttrReset(object->model[3], 0, 0xC0000002);
                Hu3DModelPosSet(object->model[3], object->trans.x, 100, 100 + object->trans.z);
                Hu3DMotionTimeSet(object->model[3], 0);
                if (temp_r31->unk4 == 0) {
                    HuAudFXPlay(1281);
                }
                omVibrate(temp_r31->unk4, 12, 4, 2);
            }
            else {
                object->trans.y += temp_r31->unk58.x - (0.07f * temp_r31->unk58.y * temp_r31->unk58.y);
                object->trans.z += 2.0f;
                temp_r31->unk58.y += 1.0f;
            }
            break;

        case 2:
            temp_r29 = &Hu3DCamera[0];
            sp1C = temp_r31->unk24;
            sp10 = temp_r31->unk30;
            VECSubtract(&sp1C, &sp10, &sp28);
            VECNormalize(&sp28, &sp28);
            object->trans.x = temp_r31->unk30.x + (temp_r31->unk58.z * (sp28.x * sind(temp_r31->unk58.y)));
            object->trans.y = temp_r31->unk30.y + (temp_r31->unk58.z * (sp28.y * sind(temp_r31->unk58.y)));
            object->trans.z = temp_r31->unk30.z + (temp_r31->unk58.z * (sp28.z * sind(temp_r31->unk58.y)));
            temp_r31->unk58.y += 9.0f / 11.0f;
            omSetRot(object, atan2d(sp28.y, sp28.z) + 90.0, 0, 0);
            temp_f27 = VECMagPoint(object->trans.x - sp1C.x, object->trans.y - sp1C.y, object->trans.z - sp1C.z);
            if (--temp_r31->unk6E == 60 && temp_r31->unk4 == 0 && lbl_2_bss_4 == NULL) {
                temp_r29 = &Hu3DCamera[0];
                lbl_2_bss_4 = omAddObjEx(HuPrcCurrentGet(), 1400, 0, 0, -1, fn_2_D3E8);
                lbl_2_bss_4->trans.x = temp_r29->pos.x;
                lbl_2_bss_4->trans.y = temp_r29->pos.y;
                lbl_2_bss_4->trans.z = temp_r29->pos.z;
                lbl_2_bss_4->rot.x = temp_r29->target.x;
                lbl_2_bss_4->rot.y = temp_r29->target.y;
                lbl_2_bss_4->rot.z = temp_r29->target.z;
                lbl_2_bss_4->scale.x = 0;
            }
            if (temp_r31->unk6E == 0) {
                temp_r31->unk0 = 3;
                temp_r31->unk4C->work[0] = 1;
                temp_r31->unk48->work[0] = 1;
            }
            fn_2_6B44(object);
            break;

        case 3:
            sp1C.x = lbl_2_bss_108->trans.x;
            sp1C.y = lbl_2_data_298[temp_r31->unk4].y;
            sp1C.z = lbl_2_bss_108->trans.z;
            sp10.x = object->trans.x;
            sp10.y = object->trans.y;
            sp10.z = object->trans.z;
            VECSubtract(&sp1C, &sp10, &sp28);
            VECNormalize(&sp28, &sp28);
            object->rot.x *= 0.95f;
            if (object->rot.x < 1.0f) {
                object->rot.x = 0.0f;
            }
            omSetRot(object, object->rot.x, atan2d(sp28.x, sp28.z), 0);
            fn_2_6B44(object);
            break;
    }
}

void fn_2_6B44(omObjData *object);

void fn_2_48A0(omObjData *object)
{
    M401WorkPlayer *temp_r31;
    Work2FA4 *temp_r29;
    float temp_f29;
    Vec sp4C;
    Vec sp40;
    s32 sp30[] = { -10, -50, -80, -130 };
    Vec sp24;
    Vec sp18;
    Vec spC;
    temp_r31 = object->data;
    temp_r29 = lbl_2_bss_10C->data;
    if (temp_r31->unk4 == 0) {
        lbl_2_bss_1A--;
    }
    switch (temp_r31->unk0) {
        case 5:
            if (temp_r31->unk6A == 1) {
                CharModelMotionShiftSet(temp_r31->unk86, object->motion[1], 0, 8, HU3D_MOTATTR_LOOP);
                temp_r31->unk6A = 0;
            }
            omSetRot(object, 0, 180, 0);
            object->trans.z -= 5.0f;
            fn_2_6B44(object);
            break;

        case 6:
            object->trans.y += temp_r31->unk58.x;
            if (object->trans.y >= 910.0f) {
                if (temp_r31->unk6C == 0) {
                    temp_r31->unk6C = 1;
                    Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(object->model[2], HU3D_MOTATTR_LOOP);
                    Hu3DModelPosSet(object->model[2], object->trans.x, 950, 30 + object->trans.z);
                    Hu3DModelScaleSet(object->model[2], 1, 1, 1);
                    Hu3DMotionTimeSet(object->model[2], 0);
                    sp4C.x = object->trans.x;
                    sp4C.y = 950;
                    sp4C.z = 30 + object->trans.z;
                    fn_2_10A88(&sp4C, 7);
                    HuAudFXEmiterPlay(1289, &sp4C);
                }
                temp_r31->unk58.x *= 0.7f;
                if (temp_r31->unk58.x <= 0.5f) {
                    temp_r31->unk0 = 7;
                    temp_r31->unk58.x = -0.5f;
                    CharModelMotionShiftSet(temp_r31->unk86, object->motion[0], 0, 30, HU3D_MOTATTR_LOOP);
                    temp_r31->unk80 = 0;
                    temp_r31->unk6C = 0;
                }
            }

            break;

        case 7:
            object->trans.y += temp_r31->unk58.x;
            if (object->trans.y <= 890) {
                object->trans.y = 890;
                if (lbl_2_bss_BA) {
                    if (temp_r31->unk68) {
                        temp_r31->unk0 = 16;
                    }
                    else {
                        temp_r31->unk0 = 9;
                    }
                }
                else {
                    temp_r31->unk0 = 8;
                    temp_r29->unk8.z = 0.5f;
                    temp_r31->unk6E = 0;
                    HuAudSStreamPlay(4);
                    lbl_2_bss_C0 = MGSeqDrawCreate();
                    lbl_2_bss_1A = 210;
                }
            }
            temp_r31->unk58.x *= 1.17f;
            object->trans.y -= 0.35f * sind(temp_r31->unk80);
            temp_r31->unk80 += 3.0f;
            if (temp_r31->unk80 >= 360.0f) {
                temp_r31->unk80 -= 360.0f;
            }
            break;

        case 8:
            object->trans.y -= 0.35f * sind(temp_r31->unk80);
            temp_r31->unk80 += 3.0f;
            if (temp_r31->unk80 >= 360.0f) {
                temp_r31->unk80 -= 360.0f;
            }
            if (temp_r31->unk6E == 13) {
                Hu3DModelAttrReset(lbl_2_bss_10C->model[6], HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(lbl_2_bss_10C->model[6], 0);
            }
            else if (temp_r31->unk6E == 50) {
                Hu3DMotionOverlaySet(object->model[0], object->motion[8]);
                Hu3DMotionOverlayTimeSet(object->model[0], 31.0f);
                Hu3DData[object->model[0]].unk_78 = 1;
            }
            if (temp_r31->unk6E >= 70) {
                if (object->rot.y < 90.0f) {
                    object->rot.y += 2.25f;
                }
                else {
                    object->rot.y = 90.0f;
                }
            }
            temp_r31->unk6E++;
            if (temp_r29->unk8.y >= 1500.0f) {
                temp_r29->unk8.z = 0;
                if (temp_r31->unk4 == 0) {
                    temp_r31->unk0 = 14;
                }
            }
            break;

        case 16:
            if (!temp_r31->unk6C) {
                temp_r31->unk6C = 1;
                HuAudPlayerVoicePlay(temp_r31->unk4, 292);
                Hu3DMotionOverlaySet(object->model[0], object->motion[9]);
                if (temp_r31->unk4 == lbl_2_bss_B2[0]) {
                    HuAudSStreamPlay(1);
                    lbl_2_bss_C0 = MGSeqWinCreate(lbl_2_bss_AA[0], lbl_2_bss_AA[1], lbl_2_bss_AA[2], lbl_2_bss_AA[3]);
                    lbl_2_bss_1A = 210;
                    temp_r31->unk6E = 160;
                    temp_r31->unk0 = 13;
                }
            }
            temp_r31->unk58.x *= 1.17f;
            object->trans.y -= 0.35f * sind(temp_r31->unk80);
            temp_r31->unk80 += 3.0f;
            if (temp_r31->unk80 >= 360.0f) {
                temp_r31->unk80 -= 360.0f;
            }
            if (73.0f <= Hu3DMotionOverlayTimeGet(object->model[0])) {
                Hu3DMotionOverlayTimeSet(object->model[0], 35.0f);
            }
            break;

        case 10:
            object->trans.y += temp_r31->unk58.x;
            if (object->trans.y >= 910.0f) {
                if (temp_r31->unk6C == 0) {
                    temp_r31->unk6C = 1;
                    omVibrate(temp_r31->unk4, 12, 4, 2);
                    Hu3DModelAttrReset(object->model[2], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(object->model[2], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(object->model[2], HU3D_MOTATTR_LOOP);
                    Hu3DModelPosSet(object->model[2], object->trans.x, 950, 30 + object->trans.z);
                    Hu3DModelScaleSet(object->model[2], 1, 1, 1);
                    Hu3DMotionTimeSet(object->model[2], 0);
                    Hu3DModelAttrReset(object->model[3], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(object->model[3], HU3D_ATTR_DISPOFF);
                    Hu3DModelClusterAttrReset(object->model[3], 0, 0xC0000002);
                    Hu3DModelPosSet(object->model[3], object->trans.x, 0, 30 + object->trans.z);
                    Hu3DMotionTimeSet(object->model[3], 0);
                    sp4C.x = object->trans.x;
                    sp4C.y = 950;
                    sp4C.z = 30 + object->trans.z;
                    fn_2_10A88(&sp4C, 7);
                    HuAudFXEmiterPlay(1289, &sp4C);
                }
                temp_r31->unk0 = 11;
                temp_r31->unk24.x = sp30[temp_r31->unk4];
                temp_r31->unk24.y = 1030;
                temp_r31->unk24.z = 40;
                sp4C.x = object->trans.x;
                sp4C.y = object->trans.y;
                sp4C.z = object->trans.z;
                VECSubtract(&temp_r31->unk24, &sp4C, &sp40);
                VECNormalize(&sp40, &sp40);
                temp_f29 = VECDistanceXZ(&temp_r31->unk24, &object->trans);
                temp_r31->unk30.x = (sp40.x * temp_f29) / 60.0f;
                temp_r31->unk30.z = (sp40.z * temp_f29) / 60.0f;
                temp_r31->unk30.y = 18.75f;
                temp_r31->unk58.y = 0;
            }
            break;

        case 11:
            temp_f29 = temp_r31->unk30.y - (0.020833334f * temp_r31->unk58.y * temp_r31->unk58.y);
            object->trans.x += temp_r31->unk30.x;
            object->trans.z += temp_r31->unk30.z;
            object->trans.y += temp_f29;
            temp_r31->unk58.y += 1.0f;
            if (object->trans.y <= 1030.0f && temp_f29 < 0) {
                temp_r31->unk0 = 12;
                object->trans.y = 1030 + temp_r29->unk4;
                CharModelMotionShiftSet(temp_r31->unk86, object->motion[2], 0, 15, HU3D_MOTATTR_LOOP);
                temp_r31->unk58.x = 0;
            }
            break;

        case 12:
            object->trans.y = 1030 + temp_r29->unk4;
            sp24.x = (sind(temp_r31->unk58.x), 0.0);
            sp24.y = -100 * sind(temp_r31->unk58.x) + 1300;
            sp24.z = -500 * sind(temp_r31->unk58.x) + 1300;
            sp18.x = (sind(temp_r31->unk58.x), 0.0);
            sp18.y = 330 * sind(temp_r31->unk58.x) + 920;
            sp18.z = (sind(temp_r31->unk58.x), 0.0) + -100.0;
            spC.x = 0;
            spC.y = 1;
            spC.z = 0;
            Hu3DCameraPosSetV(1, &sp24, &spC, &sp18);
            temp_r31->unk58.x += 3.0f;
            if (temp_r31->unk58.x > 90.0f) {
                temp_r31->unk0 = 13;
                CharModelMotionShiftSet(temp_r31->unk86, object->motion[5], 0, 20, HU3D_MOTATTR_NONE);
                HuAudSStreamPlay(1);
                lbl_2_bss_C0 = MGSeqWinCreate(lbl_2_bss_AA[0], -1, -1, -1);
                lbl_2_bss_1A = 210;
            }
            temp_r31->unk6E = 160;
            break;

        case 13:
            if (lbl_2_bss_BA == 1) {
                object->trans.y = 1030 + temp_r29->unk4;
            }
            else {
                temp_r31->unk58.x *= 1.17f;
                object->trans.y -= 0.35f * sind(temp_r31->unk80);
                temp_r31->unk80 += 3.0f;
                if (temp_r31->unk80 >= 360.0f) {
                    temp_r31->unk80 -= 360.0f;
                }
                if (73.0f <= Hu3DMotionOverlayTimeGet(object->model[0])) {
                    Hu3DMotionOverlayTimeSet(object->model[0], 35.0f);
                }
            }
            if (--temp_r31->unk6E == 0) {
                temp_r31->unk0 = 14;
            }

            break;

        case 14:
            if (temp_r31->unk68) {
                if (lbl_2_bss_BA == 1) {
                    object->trans.y = 1030 + temp_r29->unk4;
                }
                else {
                    temp_r31->unk58.x *= 1.17f;
                    object->trans.y -= 0.35f * sind(temp_r31->unk80);
                    temp_r31->unk80 += 3.0f;
                    if (temp_r31->unk80 >= 360.0f) {
                        temp_r31->unk80 -= 360.0f;
                    }
                    if (73.0f <= Hu3DMotionOverlayTimeGet(object->model[0])) {
                        Hu3DMotionOverlayTimeSet(object->model[0], 35.0f);
                    }
                }
            }
            if (lbl_2_bss_1A <= 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                HuAudSeqFadeOut(lbl_2_bss_A4, 100);
                HuAudFXStop(lbl_2_bss_11C);
                temp_r31->unk0 = 15;
            }
            break;

        case 15:
            if (temp_r31->unk68) {
                if (lbl_2_bss_BA == 1) {
                    object->trans.y = 1030 + temp_r29->unk4;
                }
                else {
                    temp_r31->unk58.x *= 1.17f;
                    object->trans.y -= 0.35f * sind(temp_r31->unk80);
                    temp_r31->unk80 += 3.0f;
                    if (temp_r31->unk80 >= 360.0f) {
                        temp_r31->unk80 -= 360.0f;
                    }
                    if (73.0f <= Hu3DMotionOverlayTimeGet(object->model[0])) {
                        Hu3DMotionOverlayTimeSet(object->model[0], 35.0f);
                    }
                }
            }
            if (!WipeStatGet()) {
                lbl_2_bss_110->func = fn_2_A10;
            }
            break;
    }
}

void fn_2_65FC(omObjData *object);
void fn_2_6AF4(omObjData *object);
void fn_2_A940(omObjData *object);

void fn_2_6C94(omObjData *object, s8 *x, s8 *y, u16 *btn);

void fn_2_5CC0(omObjData *object)
{
    M401WorkPlayer *temp_r31;
    float temp_f29;
    Vec sp20;
    Vec sp14;
    s32 sp10;
    u16 spA;
    s8 sp9;
    s8 sp8;
    temp_f29 = 0;
    temp_r31 = object->data;
    sp9 = sp8 = spA = 0;
    if (temp_r31->unk78 == 0) {
        if (GWPlayerCfg[temp_r31->unk4].iscom) {
            fn_2_6C94(object, &sp9, &sp8, &spA);
        }
        else {
            sp9 = HuPadStkX[temp_r31->unk8];
            sp8 = HuPadStkY[temp_r31->unk8];
            spA = HuPadBtnDown[temp_r31->unk8];
        }
        if (sp9 != 0 || sp8 != 0) {
            temp_r31->unk58.z = sqrtf((sp9 * sp9) + (sp8 * sp8)) / 9.0f;
        }
        temp_r31->unk64 = atan2d(sp9, sp8);
        if (spA & PAD_BUTTON_A) {
            temp_r31->unk88 += 1.51f * lbl_2_data_0;
            if (temp_r31->unk88 < 1.51f * lbl_2_data_0) {
                temp_r31->unk88 = 1.51f * lbl_2_data_0;
            }
        }
        if (temp_r31->unk88 >= 0.0f) {
            temp_f29 = 0;
        }
        else {
            temp_f29 = fabs(temp_r31->unk88 / (1.51f * lbl_2_data_0));
        }
        if (temp_r31->unk84) {
            if (--temp_r31->unk84 == 0) {
                CharModelMotionShiftSet(temp_r31->unk86, object->motion[1], 0, 8, HU3D_MOTATTR_LOOP);
                temp_r31->unk6A = 0;
            }
        }
    }
    else {
        temp_r31->unk84 = 0;
        if (--temp_r31->unk7A == 0) {
            sp10 = GWPlayerCfg[temp_r31->unk4].character;
            CharModelMotionShiftSet(temp_r31->unk86, object->motion[1], 0, 8, HU3D_MOTATTR_LOOP);
            temp_r31->unk78 = 0;
            temp_r31->unk6A = 0;
        }
        if (temp_r31->unk7A & 0x1) {
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
        }
    }
    if (temp_f29 != 0) {
        if (++temp_r31->unk8C > 15) {
            temp_r31->unk8C = 15;
        }
        temp_r31->unk8E = 0;
    }
    else {
        if (++temp_r31->unk8E > 5) {
            temp_r31->unk8E = 5;
            temp_r31->unk8C = 0;
        }
    }
    if (temp_r31->unk78 == 0 && temp_r31->unk84 == 0) {
        if (temp_r31->unk58.z > 0 || temp_r31->unk8C >= 5) {
            if (temp_r31->unk6A == 0) {
                temp_r31->unk6A = 1;
                CharModelMotionShiftSet(temp_r31->unk86, object->motion[3], 0, 8, HU3D_MOTATTR_LOOP);
            }
        }
        else {
            if (temp_r31->unk6A == 1) {
                CharModelMotionShiftSet(temp_r31->unk86, object->motion[1], 0, 8, HU3D_MOTATTR_LOOP);
                temp_r31->unk6A = 0;
            }
        }
    }
    CharModelMotionSpeedSet(temp_r31->unk86, 1.0f + temp_f29);
    fn_2_65FC(object);
    if (temp_r31->unk58.z > 0.1f) {
        temp_r31->unk58.z *= 0.9f;
    }
    else {
        temp_r31->unk58.z = 0.0f;
    }
    temp_r31->unk88 -= 0.15f * lbl_2_data_0;
    if (temp_r31->unk88 > -lbl_2_data_0) {
        temp_r31->unk88 = -lbl_2_data_0;
    }
    sp20.x = object->trans.x;
    sp20.y = object->trans.y;
    sp20.z = object->trans.z;
    omSetTra(object, temp_r31->unkC.x, temp_r31->unkC.y, lbl_2_bss_60.z + temp_r31->unkC.z);
    sp14.x = object->trans.x;
    sp14.y = object->trans.y;
    sp14.z = object->trans.z;
    if (sp8 != 0) {
        object->rot.x -= 0.05f * sp8;
    }
    else {
        object->rot.x *= 0.8f;
        if (object->rot.x < 0.01f) {
            object->rot.x = 0;
        }
    }
    if (sp9 != 0) {
        object->rot.z -= 0.05f * sp9;
    }
    else {
        object->rot.z *= 0.8f;
        if (object->rot.z < 0.01f) {
            object->rot.z = 0;
        }
    }
    if (object->rot.x < -30.0f) {
        object->rot.x = -30.0f;
    }
    if (object->rot.x > 30.0f) {
        object->rot.x = 30.0f;
    }
    if (object->rot.z < -30.0f) {
        object->rot.z = -30.0f;
    }
    if (object->rot.z > 30.0f) {
        object->rot.z = 30.0f;
    }
    object->rot.y = 180;
    fn_2_6AF4(object);
    fn_2_A940(object);
    temp_r31->unk70 = 0;
}

void fn_2_65FC(omObjData *object)
{
    M401WorkPlayer *temp_r31;
    M401WorkPlayer *temp_r30;
    s32 temp_r29;
    omObjData *temp_r28;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f26;
    float temp_f24;

    Vec sp24;
    Vec sp18;
    Vec spC;
    temp_r30 = object->data;
    temp_f26 = temp_r30->unk58.z;
    sp24.x = sind(temp_r30->unk64);
    sp24.y = cosd(temp_r30->unk64);
    sp24.z = temp_r30->unk88 + lbl_2_data_0;
    VECNormalize(&sp24, &sp18);
    sp24.x *= temp_f26;
    sp24.y *= temp_f26;
    sp24.z -= lbl_2_data_0;
    temp_f31 = temp_r30->unkC.x + sp24.x;
    temp_f30 = temp_r30->unkC.y + sp24.y;
    temp_f29 = temp_r30->unkC.z + sp24.z;
    if (temp_f31 < -400) {
        temp_f31 = -400;
    }
    if (temp_f31 > 400) {
        temp_f31 = 400;
    }
    if (temp_f30 < -300) {
        temp_f30 = -300;
    }
    if (temp_f30 > 300) {
        temp_f30 = 300;
    }
    if (temp_f29 < 400) {
        temp_f29 = 400;
    }
    if (temp_f29 > 800) {
        temp_f29 = 800;
    }
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        if (lbl_2_bss_118[temp_r29] != object) {
            temp_r28 = lbl_2_bss_118[temp_r29];
            temp_r31 = temp_r28->data;
            temp_f24 = VECMagPoint(temp_f31 - temp_r31->unkC.x, temp_f30 - temp_r31->unkC.y, temp_f29 - temp_r31->unkC.z);
            if (temp_f24 < 127.0f) {
                spC.x = temp_f31 - temp_r31->unkC.x;
                spC.y = temp_f30 - temp_r31->unkC.y;
                spC.z = temp_f29 - temp_r31->unkC.z;
                VECNormalize(&spC, &spC);
                temp_f31 = temp_r31->unkC.x + 127.0f * spC.x;
                temp_f30 = temp_r31->unkC.y + 127.0f * spC.y;
                temp_f29 = temp_r31->unkC.z + 127.0f * spC.z;
            }
        }
    }
    if (temp_f31 < -400) {
        temp_f31 = -400;
    }
    if (temp_f31 > 400) {
        temp_f31 = 400;
    }
    if (temp_f30 < -300) {
        temp_f30 = -300;
    }
    if (temp_f30 > 300) {
        temp_f30 = 300;
    }
    if (temp_f29 < 400) {
        temp_f29 = 400;
    }
    if (temp_f29 > 800) {
        temp_f29 = 800;
    }
    temp_r30->unkC.x = temp_f31;
    temp_r30->unkC.y = temp_f30;
    temp_r30->unkC.z = temp_f29;
}

void fn_2_6AF4(omObjData *object)
{
    M401WorkPlayer *temp_r31 = object->data;
    temp_r31->unk18.x = temp_r31->unkC.x + lbl_2_bss_60.x;
    temp_r31->unk18.y = object->trans.y;
    temp_r31->unk18.z = 80 + object->trans.z;
}

void fn_2_6B44(omObjData *object)
{
    M401WorkPlayer *temp_r30;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    temp_r30 = object->data;
    temp_f31 = 80.0 * sind(object->rot.y + 180.0f);
    temp_f29 = 80.0 * -cosd(object->rot.y);
    temp_f30 = 80.0 * sind(object->rot.x);
    temp_r30->unk18.x = object->trans.x + temp_f31;
    temp_r30->unk18.y = object->trans.y + temp_f30;
    temp_r30->unk18.z = object->trans.z + temp_f29;
}

omObjData *fn_2_792C(omObjData *object);

void fn_2_6C94(omObjData *object, s8 *x, s8 *y, u16 *btn)
{
    M401WorkPlayer *temp_r31;
    s32 temp_r30;
    omObjData *temp_r28;
    s32 temp_r27;
    u16 temp_r26 = 0;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    s16 sp50[][8] = {
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        0,
        0,
        2,
        0,
        0,
        0,
        2,
        0,
        0,
        0,
        2,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    s16 sp18[] = { 50, 125, 200, 245 };
    s16 sp10[] = { 75, 150, 200, 250 };
    s16 sp8[] = { 9, 6, 4, 2 };
    temp_r31 = object->data;
    *x = *y = 0;
    *btn = 0;
    if (temp_r31->unk7C == 0) {
        temp_r31->unk7E = sp50[GWPlayerCfg[temp_r31->unk4].diff][frand() & 0x7];
        temp_r31->unk7C = (frand() % 60) + 30;
        temp_r31->unk92 = 0;
        if (frandu8() < sp18[GWPlayerCfg[temp_r31->unk4].diff]) {
            temp_r31->unk92 |= 1;
        }
        if (frandu8() < sp10[GWPlayerCfg[temp_r31->unk4].diff]) {
            temp_r31->unk92 |= 2;
        }
    }
    else {
        temp_r31->unk7C--;
    }
    temp_r26 = temp_r31->unk92;
    sp44.x = sp44.y = sp44.z = 0;
    switch (temp_r31->unk7E) {
        case 0:
            temp_r28 = fn_2_792C(object);
            if (temp_r28) {
                sp44.x = temp_r28->trans.x - object->trans.x;
                sp44.y = temp_r28->trans.y - object->trans.y;
                sp44.z = temp_r28->trans.z - object->trans.z;
            }
            break;

        case 2:
            break;
    }
    if (temp_r26 & 0x1) {
        sp38.x = object->trans.x;
        sp38.y = object->trans.y;
        sp38.z = object->trans.z;
        for (temp_r27 = 0; temp_r27 < 4; temp_r27++) {
            if (lbl_2_bss_118[temp_r27] != object) {
                sp20.x = lbl_2_bss_118[temp_r27]->trans.x;
                sp20.y = lbl_2_bss_118[temp_r27]->trans.y;
                sp20.z = lbl_2_bss_118[temp_r27]->trans.z;
                VECSubtract(&sp38, &sp20, &sp2C);
                temp_f31 = VECMag(&sp2C) - 110.0f;
                if (temp_f31 < 110.0f) {
                    temp_f31 -= 60.0f;
                    if (temp_f31 < 0.01f) {
                        temp_f31 = 0.01;
                    }
                    VECScale(&sp2C, &sp2C, 1.0f / temp_f31);
                    VECAdd(&sp44, &sp2C, &sp44);
                }
            }
        }
    }
    if (temp_r26 & 0x2) {
        for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
            if (lbl_2_bss_E4[temp_r30]->func != NULL) {
                sp20.x = lbl_2_bss_E4[temp_r30]->trans.x;
                sp20.y = lbl_2_bss_E4[temp_r30]->trans.y;
                sp20.z = lbl_2_bss_E4[temp_r30]->trans.z;
                VECSubtract(&sp38, &sp20, &sp2C);
                temp_f31 = VECMag(&sp2C) - 110.0f;
                if (temp_f31 < 110.0f) {
                    temp_f31 -= 60.0f;
                    if (temp_f31 < 0.01f) {
                        temp_f31 = 0.01;
                    }
                    VECScale(&sp2C, &sp2C, 1.0f / temp_f31);
                    VECAdd(&sp44, &sp2C, &sp44);
                }
            }
        }
        for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
            if (lbl_2_bss_100[temp_r30]->func != NULL) {
                sp20.x = lbl_2_bss_100[temp_r30]->trans.x;
                sp20.y = lbl_2_bss_100[temp_r30]->trans.y;
                sp20.z = lbl_2_bss_100[temp_r30]->trans.z;
                VECSubtract(&sp38, &sp20, &sp2C);
                temp_f31 = VECMag(&sp2C) - 110.0f;
                if (temp_f31 < 110.0f) {
                    temp_f31 -= 60.0f;
                    if (temp_f31 < 0.01f) {
                        temp_f31 = 0.01;
                    }
                    VECScale(&sp2C, &sp2C, 1.0f / temp_f31);
                    VECAdd(&sp44, &sp2C, &sp44);
                }
            }
        }
        sp20.x = lbl_2_bss_FC->trans.x;
        sp20.y = lbl_2_bss_FC->trans.y;
        sp20.z = lbl_2_bss_FC->trans.z;
        VECSubtract(&sp38, &sp20, &sp2C);
        sp2C.x = 0;
        temp_f31 = VECMag(&sp2C) - 220.0f;
        if (temp_f31 < 220.0f) {
            temp_f31 -= 160.0f;
            if (temp_f31 < 0.01f) {
                temp_f31 = 0.01;
            }
            VECScale(&sp2C, &sp2C, 1.0f / temp_f31);
            VECAdd(&sp44, &sp2C, &sp44);
        }
    }

    if (sp44.z < 0.0f) {
        if (temp_r31->unk90 == 0) {
            *btn |= 0x100;
            temp_r31->unk90 = (frand() % sp8[GWPlayerCfg[temp_r31->unk4].diff]) + 3;
        }
        else {
            temp_r31->unk90--;
        }
    }
    sp44.z = 0;
    temp_f30 = VECMag(&sp44);
    temp_f30 *= 0.2f;
    temp_f29 = atan2d(sp44.y, sp44.x);
    if (temp_f30 > 72.0f) {
        temp_f30 = 72.0f;
    }
    if (temp_f30 < 10.0f) {
        temp_f30 = 0.0f;
    }
    *x = temp_f30 * cosd(temp_f29);
    *y = temp_f30 * sind(temp_f29);
}

s32 fn_2_AC2C(Vec *pos, float dist, omObjData **newobj);

s32 fn_2_7640(omObjData *object, omObjData **newobj)
{
    Vec spC;
    spC.x = object->trans.x;
    spC.y = object->trans.y;
    spC.z = object->trans.z - 100.0f;
    return fn_2_AC2C(&spC, 270.0f, newobj);
}

void fn_2_76AC(omObjData *object, s32 arg1)
{
    M401WorkPlayer *temp_r31;
    if (arg1) {
        temp_r31 = object->data;
        temp_r31->unk7E = 1;
        temp_r31->unk7C = 5;
        switch (arg1) {
            case 1:
                temp_r31->unk80 = 180.0 + atan2d(temp_r31->unk54->trans.x - object->trans.x, temp_r31->unk54->trans.y - object->trans.y);
                break;

            case 2:
                if (temp_r31->unkC.y > temp_r31->unk54->trans.y) {
                    temp_r31->unk80 = 80.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                else {
                    temp_r31->unk80 = 260.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                break;

            case 3:
                if (temp_r31->unkC.y > temp_r31->unk54->trans.y) {
                    temp_r31->unk80 = 80.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                else {
                    temp_r31->unk80 = 260.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                break;
        }
    }
}

omObjData *fn_2_792C(omObjData *object)
{
    omObjData **temp_r31;
    s32 temp_r30;
    omObjData *temp_r28;
    float temp_f31, temp_f30, temp_f29;
    float temp_f27, temp_f26;
    temp_r31 = omGetGroupMemberListEx(HuPrcCurrentGet(), 1);
    temp_f26 = 100000;
    temp_r28 = NULL;
    for (temp_r30 = 0; temp_r30 < 28; temp_r30++) {
        if (temp_r31[temp_r30] == NULL || temp_r31[temp_r30]->trans.z - lbl_2_bss_60.z > 850.0f
            || temp_r31[temp_r30]->trans.z - lbl_2_bss_60.z < -2500.0f) {
            continue;
        }
        temp_f30 = temp_r31[temp_r30]->trans.x - object->trans.x;
        temp_f29 = temp_r31[temp_r30]->trans.y - object->trans.y;
        temp_f31 = temp_r31[temp_r30]->trans.z - object->trans.z;
        temp_f31 *= 0.15f;
        temp_f27 = VECMagPoint(temp_f30, temp_f29, temp_f31);
        if (temp_f27 < temp_f26 && temp_f27 < 2000.0f) {
            temp_f26 = temp_f27;
            temp_r28 = temp_r31[temp_r30];
        }
    }
    return temp_r28;
}

void fn_2_A914(s32 player);

void fn_2_7C3C(omObjData *object)
{
    M401WorkPlayer *temp_r31 = object->data;
    temp_r31->unk78 = 1;
    temp_r31->unk7A = 120;
    CharModelMotionShiftSet(temp_r31->unk86, object->motion[7], 0, 10, HU3D_MOTATTR_NONE);
    fn_2_A914(temp_r31->unk4);
}

typedef struct work_7CB4 {
    s16 unk0;
    Vec unk4;
    Vec unk10;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    float unk28;
    s16 unk2C;
    s16 unk2E;
    float unk30;
} Work7CB4;

void fn_2_7E6C(omObjData *object);

void fn_2_7CB4(omObjData *object)
{
    Work7CB4 *temp_r31;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work7CB4), MEMORY_DEFAULT_NUM);
    temp_r31 = object->data;
    temp_r31->unk10.x = 0;
    temp_r31->unk10.y = 200;
    temp_r31->unk10.z = 0;
    temp_r31->unk1E = 0;
    temp_r31->unk22 = 100;
    temp_r31->unk4.x = 0;
    temp_r31->unk4.y = 200;
    temp_r31->unk24 = 0;
    temp_r31->unk28 = 0;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x0B));
    Hu3DModelClusterAttrSet(object->model[0], 0, 0xC0000001);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAmbSet(object->model[0], 0.6f, 0.6f, 0.6f);
    Hu3DModelShadowSet(object->model[0]);
    temp_r31->unk0 = 0;
    temp_r31->unk22 = 180;
    omSetTra(object, 0, 200, 200);
    omSetRot(object, 0, 180, 0);
    object->func = fn_2_7E6C;
}

void fn_2_7E6C(omObjData *object)
{
    Work7CB4 *temp_r31;
    temp_r31 = object->data;
    switch (temp_r31->unk0) {
        case 0:
            if (--temp_r31->unk22 == 0) {
                temp_r31->unk0 = 1;
            }
            break;

        case 1:
            object->trans.z += -11.333333f;
            break;
    }
}

s32 gap_04_00000328_data = DATA_MAKE_NUM(DATADIR_M401, 0x0C);
s32 lbl_2_data_32C[] = { 4, 6 };
Vec lbl_2_data_334[][10] = { {
                                 { 1400, -600, -21500 },
                                 { -100, 100, -22000 },
                                 { -1000, -200, -23000 },
                                 { -2000, -200, -23500 },
                                 { -2200, -200, -23500 },
                                 { -2300, -200, -23500 },
                             },
    {
        { -1000, 500, -29500 },
        { -300, 300, -31500 },
        { 300, -150, -32500 },
        { -200, 250, -34000 },
        { -300, 300, -35000 },
        { -600, 300, -36000 },
        { 1000, -180, -40000 },
        { 1000, -180, -40000 },
    }

};

void fn_2_7EDC(s32 arg0, s32 arg1, float arg2, Vec *arg3)
{
    Vec *temp_r31;
    Vec *temp_r30;
    Vec *temp_r29;
    Vec *temp_r28;
    float temp_f31 = arg2 * arg2;
    if (arg1 == 0) {
        temp_r31 = &lbl_2_data_334[arg0][arg1];
        temp_r30 = &lbl_2_data_334[arg0][arg1 + 1];
        temp_r29 = &lbl_2_data_334[arg0][arg1 + 2];
        temp_r28 = &lbl_2_data_334[arg0][arg1 + 3];
        arg3->x = (0.5f
            * ((2.0f * temp_r31->x)
                + ((temp_f31 * (temp_r29->x + (temp_r31->x - (2.0f * temp_r30->x))))
                    + (arg2 * (((-3.0f * temp_r31->x) + (4.0f * temp_r30->x)) - temp_r29->x)))));
        arg3->y = (0.5f
            * ((2.0f * temp_r31->y)
                + ((temp_f31 * (temp_r29->y + (temp_r31->y - (2.0f * temp_r30->y))))
                    + (arg2 * (((-3.0f * temp_r31->y) + (4.0f * temp_r30->y)) - temp_r29->y)))));
        arg3->z = (0.5f
            * ((2.0f * temp_r31->z)
                + ((temp_f31 * (temp_r29->z + (temp_r31->z - (2.0f * temp_r30->z))))
                    + (arg2 * (((-3.0f * temp_r31->z) + (4.0f * temp_r30->z)) - temp_r29->z)))));
    }
    else {
        temp_r31 = &lbl_2_data_334[arg0][arg1 - 1];
        temp_r30 = &lbl_2_data_334[arg0][arg1];
        temp_r29 = &lbl_2_data_334[arg0][arg1 + 1];
        temp_r28 = &lbl_2_data_334[arg0][arg1 + 2];
        arg3->x = (0.5f
            * ((2.0f * temp_r30->x)
                + ((arg2 * (-temp_r31->x + temp_r29->x))
                    + ((arg2 * (temp_f31 * (temp_r28->x + ((-temp_r31->x + (3.0f * temp_r30->x)) - (3.0f * temp_r29->x)))))
                        + (temp_f31 * (((4.0f * temp_r29->x) + ((2.0f * temp_r31->x) - (5.0f * temp_r30->x))) - temp_r28->x))))));
        arg3->y = (0.5f
            * ((2.0f * temp_r30->y)
                + ((arg2 * (-temp_r31->y + temp_r29->y))
                    + ((arg2 * (temp_f31 * (temp_r28->y + ((-temp_r31->y + (3.0f * temp_r30->y)) - (3.0f * temp_r29->y)))))
                        + (temp_f31 * (((4.0f * temp_r29->y) + ((2.0f * temp_r31->y) - (5.0f * temp_r30->y))) - temp_r28->y))))));
        arg3->z = (0.5f
            * ((2.0f * temp_r30->z)
                + ((arg2 * (-temp_r31->z + temp_r29->z))
                    + ((arg2 * (temp_f31 * (temp_r28->z + ((-temp_r31->z + (3.0f * temp_r30->z)) - (3.0f * temp_r29->z)))))
                        + (temp_f31 * (((4.0f * temp_r29->z) + ((2.0f * temp_r31->z) - (5.0f * temp_r30->z))) - temp_r28->z))))));
    }
}

s32 fn_2_8450(omObjData *object)
{
    Work7CB4 *temp_r31;
    Vec *temp_r29;
    Vec *temp_r28;
    float temp_f29;
    Vec sp18;
    Vec spC;
    temp_r31 = object->data;
    while (1) {
        if (temp_r31->unk2E == lbl_2_data_32C[temp_r31->unk2C]) {
            return 1;
        }
        temp_r28 = &lbl_2_data_334[temp_r31->unk2C][temp_r31->unk2E + 1];
        temp_r29 = &lbl_2_data_334[temp_r31->unk2C][temp_r31->unk2E];
        sp18.x = temp_r28->x - temp_r29->x;
        sp18.y = temp_r28->y - temp_r29->y;
        sp18.z = temp_r28->z - temp_r29->z;
        temp_f29 = VECMagPoint(sp18.x, sp18.y, sp18.z);
        if (temp_r31->unk30 > temp_f29) {
            temp_r31->unk30 -= temp_f29;
            temp_r31->unk2E++;
            continue;
        }
        break;
    }
    fn_2_7EDC(temp_r31->unk2C, temp_r31->unk2E, temp_r31->unk30 / temp_f29, &spC);
    sp18.x = spC.x - object->trans.x;
    sp18.y = spC.y - object->trans.y;
    sp18.z = spC.z - object->trans.z;
    VECNormalize(&sp18, &sp18);
    object->trans.x = spC.x;
    object->trans.y = spC.y;
    object->trans.z = spC.z;
    object->rot.y = atan2d(sp18.x, sp18.z);
    object->rot.x = -90.0f * sp18.y;
    return 0;
}

s32 fn_2_873C(omObjData *object)
{
    Work7CB4 *temp_r30;
    Vec sp8;
    temp_r30 = object->data;
    if (object->trans.x > -400.0f && object->trans.x < 400.0f && object->trans.z - lbl_2_bss_60.z < 300.0f && object->trans.y > -300.0f
        && object->trans.y < 300.0f) {
        if (temp_r30->unk1E == 0) {
            if (temp_r30->unk20 != 0) {
                temp_r30->unk20--;
                sp8.x = object->trans.x;
                sp8.y = object->trans.y;
                sp8.z = object->trans.z - lbl_2_bss_60.z;
                fn_2_10A88(&sp8, 1);
                return 1;
            }
        }
        else {
            temp_r30->unk1E--;
        }
    }
    return 0;
}

void fn_2_8968(omObjData *object);

void fn_2_8868(omObjData *object)
{
    Work7CB4 *temp_r31;
    temp_r31 = object->data;
    if (lbl_2_bss_60.z < -20800.0f) {
        Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
        temp_r31->unk2C = 0;
        temp_r31->unk2E = 0;
        temp_r31->unk30 = 0;
        temp_r31->unk1E = ((frand() % 10) + 13) * 0.43478262f;
        temp_r31->unk20 = 2;
        fn_2_8450(object);
        object->func = fn_2_8968;
    }
}

void fn_2_8B58(omObjData *object);

void fn_2_8968(omObjData *object)
{
    Work7CB4 *temp_r29;
    temp_r29 = object->data;
    temp_r29->unk30 += 25.875;
    if (fn_2_873C(object)) {
        temp_r29->unk1E = ((frand() % 15) + 22) * 0.43478262f;
    }
    if (fn_2_8450(object)) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        object->func = fn_2_8B58;
    }
}

void fn_2_8C58(omObjData *object);

void fn_2_8B58(omObjData *object)
{
    Work7CB4 *temp_r31;
    temp_r31 = object->data;
    if (lbl_2_bss_60.z < -30500.0f) {
        Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
        temp_r31->unk2C = 1;
        temp_r31->unk2E = 0;
        temp_r31->unk30 = 0;
        temp_r31->unk1E = ((frand() % 60) + 50) * 0.43478262f;
        temp_r31->unk20 = 3;
        fn_2_8450(object);
        object->func = fn_2_8C58;
    }
}

s32 lbl_2_data_424[] = { 50, 95 };

void fn_2_8C58(omObjData *object)
{
    Work7CB4 *temp_r29;
    temp_r29 = object->data;
    temp_r29->unk30 += 25.875;
    if (fn_2_873C(object)) {
        temp_r29->unk1E = ((frand() % 15) + lbl_2_data_424[lbl_2_bss_14++]) * 0.43478262f;
    }
    if (fn_2_8450(object)) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        object->func = NULL;
    }
}

typedef struct work_8E74 {
    Vec unk0;
    Vec unkC;
    Vec unk18;
    Vec unk24;
    float unk30;
    Vec unk34;
} Work8E74;

void fn_2_9298(omObjData *object);

void fn_2_8E74(omObjData *object)
{
    Work8E74 *temp_r31;
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work8E74), MEMORY_DEFAULT_NUM);
    temp_r31 = object->data;
    temp_r31->unk24.x = 6;
    temp_r31->unk24.z = 90;
    temp_r31->unk24.y = 100;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x0D));
    object->motion[0] = Hu3DJointMotionFile(object->model[0], DATA_MAKE_NUM(DATADIR_M401, 0x10));
    Hu3DMotionSet(object->model[0], object->motion[0]);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    omSetTra(object, -1000, 0, -23000);
    omSetRot(object, 0, 90, 0);
    temp_r31->unkC.x = 1000.0f - object->trans.x;
    temp_r31->unkC.y = temp_r31->unk24.y - object->trans.y;
    temp_r31->unkC.z = 0;
    temp_r31->unk34.x = 1000;
    temp_r31->unk34.y = 30;
    temp_r31->unk34.z = 360.0f + ((1.0f / 255.0f) * frandu8());
    temp_r31->unk30 = VECMagPoint(temp_r31->unkC.x, temp_r31->unkC.y, temp_r31->unkC.z);
    VECNormalize(&temp_r31->unkC, &temp_r31->unk0);
    Hu3DModelShadowSet(object->model[0]);
    object->work[3] = 2;
    object->func = fn_2_9298;
}

void fn_2_91AC(omObjData *object, Vec *pos)
{
    Work8E74 *temp_r30;
    temp_r30 = object->data;
    temp_r30->unk18 = *pos;
    temp_r30->unk34.z = (1.0f / 255.0f) * (360.0f * frandu8());
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    omSetTra(object, pos->x, pos->y, pos->z);
#ifdef NON_MATCHING
    object->work[2] = HuAudFXEmiterPlay(1284, pos);
#else
    object->work[2] = HuAudFXEmiterPlay(1284, &pos);
#endif
    object->func = fn_2_9298;
}

void fn_2_9298(omObjData *object)
{
    Work8E74 *temp_r31;
    float temp_f29;
    Vec spC;
    temp_r31 = object->data;
    object->trans.x = temp_r31->unk18.x + 1000.0f * sind(temp_r31->unk34.z);
    temp_f29 = (temp_r31->unk34.y / temp_r31->unk34.x) * sqrtf((temp_r31->unk34.x * temp_r31->unk34.x) - (object->trans.x * object->trans.x));
    if (temp_r31->unk34.z >= 90.0f && temp_r31->unk34.z <= 270.0f) {
        temp_f29 = -temp_f29;
    }
    object->trans.z = temp_r31->unk18.z + temp_f29;
    temp_r31->unk34.z += 0.6f + (0.6f * fabs(cosd(temp_r31->unk34.z)));
    if (temp_r31->unk34.z >= 360.0f) {
        temp_r31->unk34.z -= 360.0f;
    }
    omSetRot(object, 0, 90.0f + temp_r31->unk34.z, 0);
    spC.x = object->trans.x;
    spC.y = object->trans.y;
    spC.z = object->trans.z;
    HuAudFXEmiterUpDate(object->work[2], &spC);
    if (object->trans.z > lbl_2_bss_6C.z - 220.0f) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        HuAudFXStop(object->work[2]);
        object->func = NULL;
    }
}

void fn_2_979C(omObjData *object);

void fn_2_95E4(omObjData *object)
{
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x18));
    object->motion[0] = Hu3DJointMotionFile(object->model[0], DATA_MAKE_NUM(DATADIR_M401, 0x19));
    object->motion[1] = Hu3DJointMotionFile(object->model[0], DATA_MAKE_NUM(DATADIR_M401, 0x1A));
    omSetTra(object, 3000, 0, -37000);
    omSetRot(object, 0, 270, 0);
    Hu3DMotionSet(object->model[0], object->motion[0]);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    object->work[3] = 3;
    Hu3DModelShadowSet(object->model[0]);
    object->func = fn_2_979C;
}

void fn_2_9734(s32 flag)
{
    if (flag) {
        Hu3DModelAttrReset(lbl_2_bss_FC->model[0], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(lbl_2_bss_FC->model[0], HU3D_ATTR_DISPOFF);
    }
}

void fn_2_988C(omObjData *object);

void fn_2_979C(omObjData *object)
{
    if (lbl_2_bss_60.z < -19000.0f) {
        fn_2_9734(1);
        omSetTra(object, -2500, -800, -21000);
        omSetRot(object, 0, 125, 0);
        Hu3DMotionSet(object->model[0], object->motion[0]);
        Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
        object->func = fn_2_988C;
    }
}

void fn_2_99A4(omObjData *object);

void fn_2_988C(omObjData *object)
{
    object->trans.x += 2.3f * (26.0 * sind(object->rot.y));
    object->trans.z += 2.3f * (26.0 * cosd(object->rot.y));
    if (object->trans.x > 6000.0f) {
        fn_2_9734(0);
        object->func = fn_2_99A4;
    }
}

void fn_2_9B90(omObjData *object);

void fn_2_99A4(omObjData *object)
{
    float temp_f31;
    if (lbl_2_bss_60.z <= -36200.0f + ((1.0f / 255.0f) * (200.0f * frandu8()))) {
        temp_f31 = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
        fn_2_9734(1);
        omSetTra(object, 3000, temp_f31, -37000);
        omSetRot(object, 0, 270, 0);
        Hu3DMotionSet(object->model[0], object->motion[0]);
        Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
        object->func = fn_2_9B90;
        lbl_2_bss_78.x = object->trans.x;
        lbl_2_bss_78.y = object->trans.y;
        lbl_2_bss_78.z = object->trans.z;
        lbl_2_bss_8C = HuAudFXEmiterPlay(1286, &lbl_2_bss_78);
    }
}

void fn_2_9B90(omObjData *object)
{
    object->trans.x += 2.3f * (17.0 * sind(object->rot.y));
    object->trans.z += 2.3f * (17.0 * cosd(object->rot.y));
    lbl_2_bss_78.x = object->trans.x;
    lbl_2_bss_78.y = object->trans.y;
    lbl_2_bss_78.z = object->trans.z;
    HuAudFXEmiterUpDate(lbl_2_bss_8C, &lbl_2_bss_78);
    if (object->trans.x <= -3000.0f) {
        fn_2_9734(0);
        object->func = NULL;
        HuAudFXStop(lbl_2_bss_8C);
    }
}

typedef struct work_a318 {
    Vec unk0;
    s16 unkC;
} WorkA318;

s32 lbl_2_data_42C[] = { DATA_MAKE_NUM(DATADIR_M401, 0x1C), DATA_MAKE_NUM(DATADIR_M401, 0x1D) };

void fn_2_9D00(Process *objman)
{
    omObjData *temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        temp_r31 = omAddObjEx(objman, 1130, 1, 2, -1, NULL);
        lbl_2_bss_E4[temp_r29] = temp_r31;
        temp_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x1B));
        for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
            temp_r31->motion[temp_r30] = Hu3DJointMotionFile(temp_r31->model[0], lbl_2_data_42C[temp_r30]);
        }
        Hu3DModelAttrSet(temp_r31->model[0], HU3D_ATTR_DISPOFF);
        temp_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkA318), MEMORY_DEFAULT_NUM);
        Hu3DModelShadowSet(temp_r31->model[0]);
        temp_r31->work[3] = 1;
    }
}

void fn_2_A318(omObjData *object);

void fn_2_9E28(float arg1, float arg2)
{
    s32 temp_r31;
    WorkA318 *temp_r30;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    temp_f30 = (arg2 - arg1) / 4;
    temp_f31 = arg1;
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        temp_r30 = lbl_2_bss_E4[temp_r31]->data;
        Hu3DModelAttrReset(lbl_2_bss_E4[temp_r31]->model[0], HU3D_ATTR_DISPOFF);
        temp_f29 = -400.0f + ((1.0f / 255.0f) * (800.0f * frandu8()));
        temp_r30->unk0.x = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
        omSetTra(lbl_2_bss_E4[temp_r31], temp_f29, temp_r30->unk0.x + lbl_2_bss_60.y, temp_f31);
        Hu3DMotionSet(lbl_2_bss_E4[temp_r31]->model[0], lbl_2_bss_E4[temp_r31]->motion[0]);
        Hu3DModelAttrSet(lbl_2_bss_E4[temp_r31]->model[0], HU3D_MOTATTR_LOOP);
        temp_f31 += temp_f30;
        temp_r30->unkC = (frand() % 30) + 30;
        temp_r30->unk0.z = 0;
        lbl_2_bss_E4[temp_r31]->func = fn_2_A318;
    }
}

omObjData *fn_2_A0B0(omObjData *object)
{
    omObjData *temp_r31;
    s32 temp_r30;
    omObjData *temp_r29;
    M401WorkPlayer *spC;

    float temp_f27;
    float temp_f26;
    temp_f26 = 999999;
    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
        float temp_f31;
        float temp_f30;
        float temp_f29;
        temp_r31 = lbl_2_bss_118[temp_r30];
        spC = temp_r31->data;
        temp_f31 = temp_r31->trans.x - object->trans.x;
        temp_f30 = temp_r31->trans.y - object->trans.y;
        temp_f29 = 0.4f * (temp_r31->trans.z - object->trans.z);
        temp_f27 = VECMagPoint(temp_f31, temp_f30, temp_f29);
        if (temp_f27 < temp_f26) {
            temp_r29 = lbl_2_bss_118[temp_r30];
            temp_f26 = temp_f27;
        }
    }
    return temp_r29;
}

void fn_2_A318(omObjData *object)
{
    WorkA318 *temp_r30;
    omObjData *temp_r28;
    M401WorkPlayer *sp10;
    temp_r30 = object->data;
    if (0.0f == temp_r30->unk0.z) {
        if (temp_r30->unkC == 0) {
            temp_r28 = fn_2_A0B0(object);
            sp10 = temp_r28->data;
            temp_r30->unk0.y = atan2d(temp_r28->trans.y - object->trans.y, temp_r28->trans.x - object->trans.x);
            temp_r30->unk0.z = 8.0f + ((1.0f / 255.0f) * ((9.0f * frandu8())));
            Hu3DMotionSet(object->model[0], object->motion[1]);
            Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
            lbl_2_bss_78.x = object->trans.x;
            lbl_2_bss_78.y = object->trans.y;
            lbl_2_bss_78.z = object->trans.z;
            HuAudFXEmiterPlay(1282, &lbl_2_bss_78);
        }
        else {
            temp_r30->unkC--;
            temp_r30->unk0.x -= 2.5f;
        }
    }
    else {
        temp_r30->unk0.x = temp_r30->unk0.x + (temp_r30->unk0.z * sind(temp_r30->unk0.y));
        object->trans.x += temp_r30->unk0.z * cosd(temp_r30->unk0.y);
        temp_r30->unk0.z *= 0.94f;
        if (temp_r30->unk0.z < 0.1f) {
            temp_r30->unk0.z = 0;
            temp_r30->unkC = (frand() % 30) + 25;
            Hu3DMotionSet(object->model[0], object->motion[0]);
            Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
        }
    }
    if (temp_r30->unk0.x < -300.0f) {
        temp_r30->unk0.x = -300.0f;
    }
    if (temp_r30->unk0.x > 300.0f) {
        temp_r30->unk0.x = 300.0f;
    }
    if (object->trans.x < -400.0f) {
        object->trans.x = -400.0f;
    }
    if (object->trans.x > 400.0f) {
        object->trans.x = 400.0f;
    }
    omSetTra(object, object->trans.x, temp_r30->unk0.x + lbl_2_bss_60.y, object->trans.z);
    if (object->trans.z > lbl_2_bss_6C.z - 160.0f) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        object->func = NULL;
    }
}

void fn_2_A8A4(omObjData *object, float x, float y, float z)
{
    omSetTra(object, lbl_2_bss_60.x + x, lbl_2_bss_60.y + y, lbl_2_bss_60.z + z);
}

s32 lbl_2_data_434[] = { 0x12D, 0x16D, 0x1AD, 0x1ED, 0x22D, 0x26D, 0x2AD, 0x2ED };

void fn_2_A914(s32 player)
{
    HuAudPlayerVoicePlay(player, 301);
}

void fn_2_A940(omObjData *object)
{
    Vec spC;
    omObjData *sp8;
    M401WorkPlayer *temp_r28;
    s32 temp_r23;
    temp_r28 = object->data;
    if (temp_r28->unk78 != 0) {
        return;
    }
    spC.x = object->trans.x;
    spC.y = object->trans.y;
    spC.z = object->trans.z;
    if ((temp_r23 = fn_2_AC2C(&spC, 90, &sp8)) != 0) {
        if (temp_r23 == 1) {
            omVibrate(temp_r28->unk4, 12, 4, 2);
        }
        else if (temp_r23 == 3) {
            omVibrate(temp_r28->unk4, 12, 4, 2);
        }
        else {
            omVibrate(temp_r28->unk4, 12, 12, 0);
        }
        fn_2_7C3C(object);
        fn_2_1858(temp_r28->unk4, sp8->work[3]);
    }
}

s32 fn_2_AC2C(Vec *pos, float dist, omObjData **newobj)
{
    omObjData *temp_r30;
    s32 temp_r29;
    float temp_f20;
    float temp_f19;
    float temp_f18;
    WorkA318 *sp70;
    float sp6C;

    *newobj = NULL;
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        temp_r30 = lbl_2_bss_E4[temp_r29];
        if (temp_r30->func != NULL) {
            sp70 = temp_r30->data;
            temp_f20 = VECMagPoint(pos->x - temp_r30->trans.x, pos->y - temp_r30->trans.y, pos->z - temp_r30->trans.z);
            if (temp_f20 < sqrtf(1024.0f + (dist * dist))) {
                *newobj = temp_r30;
                return 1;
            }
        }
    }
    temp_r30 = lbl_2_bss_FC;
    temp_f20 = VECDistanceZY(pos, &temp_r30->trans);
    if (temp_f20 < sqrtf(6400.0f + (dist * dist)) && temp_r30->trans.x < pos->x - (dist / 2.0f)
        && 1500.0f + temp_r30->trans.x > pos->x + (dist / 2.0f)) {
        *newobj = temp_r30;
        return 2;
    }
    for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
        if (lbl_2_bss_100[temp_r29]->func != NULL) {
            temp_f19 = lbl_2_bss_100[temp_r29]->trans.x + (70.0 * sind(lbl_2_bss_100[temp_r29]->rot.y));
            temp_f18 = lbl_2_bss_100[temp_r29]->trans.z + (70.0 * cosd(lbl_2_bss_100[temp_r29]->rot.y));
            sp6C = lbl_2_bss_100[temp_r29]->trans.y - 10.0f;
            temp_f20 = VECMagPoint(pos->x - temp_f19, pos->y - sp6C, pos->z - temp_f18);
            if (temp_f20 < sqrtf(4900.0f + (dist * dist))) {
                *newobj = lbl_2_bss_100[temp_r29];
                return 3;
            }
            temp_f19 = lbl_2_bss_100[temp_r29]->trans.x;
            temp_f18 = lbl_2_bss_100[temp_r29]->trans.z;
            sp6C = lbl_2_bss_100[temp_r29]->trans.y - 10.0f;
            temp_f20 = VECMagPoint(pos->x - temp_f19, pos->y - sp6C, pos->z - temp_f18);
            if (temp_f20 < sqrtf(4900.0f + (dist * dist))) {
                *newobj = lbl_2_bss_100[temp_r29];
                return 3;
            }
            temp_f19 = lbl_2_bss_100[temp_r29]->trans.x + (70.0 * sind(lbl_2_bss_100[temp_r29]->rot.y + 180.0f));
            temp_f18 = lbl_2_bss_100[temp_r29]->trans.z + (70.0 * cosd(lbl_2_bss_100[temp_r29]->rot.y + 180.0f));
            sp6C = lbl_2_bss_100[temp_r29]->trans.y - 10.0f;
            temp_f20 = VECMagPoint(pos->x - temp_f19, pos->y - sp6C, pos->z - temp_f18);
            if (temp_f20 < sqrtf(4410.0f + (dist * dist))) {
                *newobj = lbl_2_bss_100[temp_r29];
                return 3;
            }
        }
    }
    return 0;
}

void fn_2_D8CC(omObjData *object);

void fn_2_BD90(omObjData *object)
{
    s32 temp_r27;
    M401WorkPlayer *temp_r26;
    switch (object->work[0]) {
        case 0:
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            ;
            object->work[0] = 1;
            break;

        case 1:
            if (!WipeStatGet()) {
                object->work[0] = 2;
                object->work[1] = 180;
            }
            break;

        case 2:
            if (object->work[1] == 0) {
                lbl_2_bss_C0 = MGSeqStartCreate();
                object->work[0] = 3;
                lbl_2_bss_A4 = HuAudSeqPlay(68);
            }
            else {
                object->work[1]--;
            }
            break;

        case 3:
            if (!MGSeqStatGet(lbl_2_bss_C0)) {
                fn_2_AEC(1);
                lbl_2_bss_120 = 1;
                fn_2_1A38(lbl_2_bss_10C);

                lbl_2_bss_10C->func = fn_2_34B8;
                for (temp_r27 = 0; temp_r27 < 4; temp_r27++) {
                    temp_r26 = lbl_2_bss_118[temp_r27]->data;
                    temp_r26->unk58.z = 0;
                    temp_r26->unkC.z = 800;
                    lbl_2_bss_118[temp_r27]->func = fn_2_5CC0;
                    object->trans.x = object->trans.y = object->trans.z = 0;
                }
                lbl_2_bss_108->func = fn_2_8868;
                omDelObjEx(HuPrcCurrentGet(), object);
                lbl_2_bss_114 = NULL;
                lbl_2_bss_4->func = fn_2_D8CC;
            }

            break;
    }
}

void fn_2_C130(omObjData *object)
{
    M401WorkPlayer *temp_r31;
    s32 temp_r30;
    LightData *temp_r28;
    Vec sp14;
    Vec sp8;
    switch (object->work[0]) {
        case 0:
            if (!MGSeqStatGet(lbl_2_bss_C0)) {
                object->work[0] = 1;
                #if VERSION_NTSC
                HuAudFXStop(lbl_2_bss_11C);
                #else
                HuAudFXFadeOut(lbl_2_bss_11C, 500);
                #endif
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                WipeColorSet(255, 255, 255);
            }
            break;

        case 1:
            if (WipeStatGet()) {
                return;
            }
            Hu3DFogClear();
            temp_r28 = &Hu3DGlobalLight[0];
            temp_r28->color.r = 255;
            temp_r28->color.g = 255;
            temp_r28->color.b = 255;
            sp14.x = 0;
            sp14.y = 2500;
            sp14.z = 1000;
            sp8.x = 0;
            sp8.y = 1030;
            sp8.z = 0;
            Hu3DGLightPosAimSetV(lbl_2_bss_A8, &sp14, &sp8);
            lbl_2_data_30.x = 0;
            lbl_2_data_30.y = 2500;
            lbl_2_data_30.z = 1000;
            lbl_2_data_48.x = 0;
            lbl_2_data_48.y = 1030;
            lbl_2_data_48.z = 0;
            Hu3DShadowPosSet(&lbl_2_data_30, &lbl_2_data_3C, &lbl_2_data_48);
            HuAudAUXVolSet(-1, -1);
            fn_2_2ED0(lbl_2_bss_10C);
            for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                temp_r31 = lbl_2_bss_118[temp_r30]->data;
                temp_r31->unk50->work[0] = 1;
                temp_r31->unk6C = 0;
                CharModelMotionSet(((M401WorkPlayer *)(lbl_2_bss_118[temp_r30]->data))->unk86, lbl_2_bss_118[temp_r30]->motion[4]);
                Hu3DModelAttrReset(lbl_2_bss_118[temp_r30]->model[0], HU3D_MOTATTR_LOOP);
                lbl_2_bss_118[temp_r30]->func = fn_2_48A0;
                Hu3DModelAmbSet(lbl_2_bss_118[temp_r30]->model[0], 0.7f, 0.7f, 0.7f);
                omSetTra(lbl_2_bss_118[temp_r30], -225.0f + (temp_r30 * 150), 740, 400);
                omSetRot(lbl_2_bss_118[temp_r30], 0, 0, 0);
                if (temp_r31->unk68) {
                    if (lbl_2_bss_BA == 1) {
                        temp_r31->unk0 = 10;
                        temp_r31->unk58.x = 13;
                    }
                    else {
                        temp_r31->unk58.x = 10;
                        temp_r31->unk0 = 6;
                    }
                    OSReport("GetCoin:%d\n", temp_r30);
                    GWPlayerCoinWinSet(temp_r30, 10);
                }
                else {
                    temp_r31->unk58.x = 10;
                    temp_r31->unk0 = 6;
                }
            }
            fn_2_26E0(lbl_2_bss_10C);
            object->work[0] = 2;
            lbl_2_bss_F4->work[0] = 1;
            fn_2_141B0();
            lbl_2_bss_10C->func = fn_2_3838;
            lbl_2_bss_11C = HuAudFXPlay(1280);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            omDelObjEx(HuPrcCurrentGet(), lbl_2_bss_C8);
            break;

        case 2:
            WipeStatGet() == 0;
            break;
    }
}

typedef struct work_c840 {
    Vec unk0[9];
    float unk6C[9];
} WorkC840;

void fn_2_C840(s16 arg0);

void fn_2_CAB0(omObjData *object);

void fn_2_C6DC(omObjData *object)
{
    s32 temp_r30;
    float temp_f31;
    WorkC840 *sp8;
    sp8 = object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkC840), MEMORY_DEFAULT_NUM);
    for (temp_r30 = 0; temp_r30 < 9; temp_r30++) {
        if (temp_r30 == 0) {
            object->model[temp_r30] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x02));
        }
        else {
            object->model[temp_r30] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x02));
        }
        Hu3DModelLayerSet(object->model[temp_r30], 1);
        fn_2_C840(temp_r30);
        temp_f31 = (1.0f / 255.0f) * (Hu3DMotionMaxTimeGet(object->model[temp_r30]) * frandu8());
        Hu3DMotionTimeSet(object->model[temp_r30], temp_f31);
    }
    omSetStatBit(object, 0x100);
    object->func = fn_2_CAB0;
}

void fn_2_C840(s16 arg0)
{
    WorkC840 *temp_r31;
    float temp_f31, temp_f30;
    temp_r31 = lbl_2_bss_F8->data;
    temp_f30 = (1.0f / 255.0f) * (360.0f * frandu8());
    temp_f31 = (1.0f / 255.0f) * (200.0f * frandu8());
    temp_r31->unk0[arg0].x = temp_f31 * cosd(temp_f30);
    temp_r31->unk0[arg0].z = temp_f31 * sind(temp_f30);
    temp_r31->unk0[arg0].y = 1000;
    temp_r31->unk6C[arg0] = 1.0f;
    temp_f31 *= 0.25f;
    Hu3DModelRotSet(lbl_2_bss_F8->model[arg0], temp_f31 * sind(temp_f30), 0, temp_f31 * cosd(temp_f30));
    Hu3DMotionTimeSet(lbl_2_bss_F8->model[arg0], 0);
}

void fn_2_CAB0(omObjData *object)
{
    s32 temp_r31;
    WorkC840 *temp_r29;
    u8 temp_r28;
    float temp_f29;
    temp_r29 = object->data;
    for (temp_r31 = 0; temp_r31 < 9; temp_r31++) {
        Hu3DModelPosSet(
            object->model[temp_r31], temp_r29->unk0[temp_r31].x, temp_r29->unk0[temp_r31].y, lbl_2_bss_38.z + temp_r29->unk0[temp_r31].z - 500);
        Hu3DModelTPLvlSet(object->model[temp_r31], temp_r29->unk6C[temp_r31]);
        temp_f29 = Hu3DMotionTimeGet(object->model[temp_r31]) / Hu3DMotionMaxTimeGet(object->model[temp_r31]);
        temp_r29->unk6C[temp_r31] = 1.0f - temp_f29;
        if (Hu3DMotionTimeGet(object->model[temp_r31]) >= Hu3DMotionMaxTimeGet(object->model[temp_r31])) {
            fn_2_C840(temp_r31);
        }
    }
    if (lbl_2_bss_60.z <= -26800.0f && lbl_2_bss_60.z >= -27400.0f) {
        temp_r28 = 255.0f - (223.0f * (-(lbl_2_bss_60.z + 26800.0f) / 600.0f));
        if (temp_r28 < 32) {
            temp_r28 = 32;
        }
    }
    else if (lbl_2_bss_60.z <= -27700.0f && lbl_2_bss_60.z >= -28300.0f) {
        temp_r28 = 32.0f + (223.0f * (-(lbl_2_bss_60.z + 27700.0f) / 600.0f));
    }
    else if (lbl_2_bss_60.z < -27400.0f && lbl_2_bss_60.z > -28300.0f) {
        temp_r28 = 32;
    }
    else {
        temp_r28 = 255;
    }
    Hu3DGLightColorSet(lbl_2_bss_A8, temp_r28, temp_r28, temp_r28, 255);
    if (lbl_2_bss_60.z < -26600.0f && lbl_2_bss_60.z > -27500.0f) {
        for (temp_r31 = 0; temp_r31 < 9; temp_r31++) {
            Hu3DModelAttrSet(object->model[temp_r31], HU3D_ATTR_DISPOFF);
        }
    }
    else {
        for (temp_r31 = 0; temp_r31 < 9; temp_r31++) {
            Hu3DModelAttrReset(object->model[temp_r31], HU3D_ATTR_DISPOFF);
        }
    }
}

void fn_2_D088(omObjData *object)
{
    CameraData *temp_r31 = &Hu3DCamera[0];
    Vec sp8;

    lbl_2_bss_6C = temp_r31->pos;
    lbl_2_bss_60 = temp_r31->target;
    VECSubtract(&lbl_2_bss_6C, &lbl_2_bss_54, &sp8);
    lbl_2_bss_50 = VECMag(&sp8);
    lbl_2_bss_54 = lbl_2_bss_6C;

    fn_2_A98();
}

void fn_2_D180(float arg0)
{
    Vec sp14;
    Vec sp8;
    lbl_2_bss_44.x = 0;
    lbl_2_bss_44.y = 0;
    lbl_2_bss_44.z = arg0;
    lbl_2_bss_38.x = 0;
    lbl_2_bss_38.y = 0;
    lbl_2_bss_38.z = -1500 + arg0;
    lbl_2_bss_2C.x = 0;
    lbl_2_bss_2C.y = 1;
    lbl_2_bss_2C.z = 0;
    Hu3DCameraPosSetV(1, &lbl_2_bss_44, &lbl_2_bss_2C, &lbl_2_bss_38);
    Hu3DModelPosSet(lbl_2_bss_10C->model[1], 0, 0, -1500 + arg0);
    lbl_2_data_30.y = 3500 + lbl_2_bss_38.y;
    lbl_2_data_30.z = 1500 + lbl_2_bss_38.z;
    lbl_2_data_48.y = lbl_2_bss_38.y - 200;
    lbl_2_data_48.z = 500 + lbl_2_bss_38.z;
    Hu3DShadowPosSet(&lbl_2_data_30, &lbl_2_data_3C, &lbl_2_data_48);
    sp14 = lbl_2_bss_44;
    VECSubtract(&lbl_2_bss_38, &sp14, &sp8);
    VECNormalize(&sp8, &sp8);
    HuAudFXListnerUpdate(&sp14, &sp8);
}

void fn_2_D3E8(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    float temp_f31 = 1.5f * object->scale.x;
    lbl_2_bss_44.x = object->trans.x + (-object->trans.x * sind(temp_f31));
    lbl_2_bss_44.y = object->trans.y + (-object->trans.y * sind(temp_f31));
    lbl_2_bss_44.z = object->trans.z + (-object->trans.z * sind(temp_f31));
    lbl_2_bss_38.x = object->rot.x + (-object->rot.x * sind(temp_f31));
    lbl_2_bss_38.y = object->rot.y + (-object->rot.y * sind(temp_f31));
    lbl_2_bss_38.z = object->rot.z + ((-1500.0f - object->rot.z) * sind(temp_f31));
    lbl_2_bss_2C.x = 0;
    lbl_2_bss_2C.y = 1;
    lbl_2_bss_2C.z = 0;
    object->scale.x += 1.0f;
    if (object->scale.x > 60.0f) {
        lbl_2_bss_44.x = 0;
        lbl_2_bss_44.y = 0;
        lbl_2_bss_44.z = 0;
        lbl_2_bss_38.x = 0;
        lbl_2_bss_38.y = 0;
        lbl_2_bss_38.z = -1500;
    }
    Hu3DCameraPosSetV(1, &lbl_2_bss_44, &lbl_2_bss_2C, &lbl_2_bss_38);
    lbl_2_bss_54 = lbl_2_bss_44;
    lbl_2_data_30.y = 3500 + lbl_2_bss_38.y;
    lbl_2_data_30.z = 1500 + lbl_2_bss_38.z;
    lbl_2_data_48.y = lbl_2_bss_38.y - 200;
    lbl_2_data_48.z = 500 + lbl_2_bss_38.z;
    Hu3DShadowPosSet(&lbl_2_data_30, &lbl_2_data_3C, &lbl_2_data_48);
    sp14 = lbl_2_bss_44;
    VECSubtract(&lbl_2_bss_38, &lbl_2_bss_44, &sp8);
    VECNormalize(&sp8, &sp8);
    HuAudFXListnerUpdate(&sp14, &sp8);
    if (object->scale.x > 60.0f) {
        lbl_2_bss_128 = 100;
        Hu3DCameraPerspectiveSet(1, lbl_2_bss_12C, lbl_2_bss_128, lbl_2_bss_124, 1.2f);
        object->scale.x = 0;
        object->func = NULL;
    }
}

void fn_2_D8CC(omObjData *object)
{
    if (lbl_2_bss_BE != 0) {
        return;
    }
    lbl_2_data_0 *= 1.05f;
    if (lbl_2_data_0 < -14.375f) {
        lbl_2_data_0 = -14.375f;
    }
    object->scale.x += lbl_2_data_0;
    fn_2_D180(object->scale.x);
}

s32 lbl_2_data_460[] = { DATA_MAKE_NUM(DATADIR_M401, 0x04), DATA_MAKE_NUM(DATADIR_M401, 0x05), DATA_MAKE_NUM(DATADIR_M401, 0x06) };

typedef struct work_e6e8 {
    s16 unk0;
    Vec unk4;
    float unk10;
    float unk14;
    float unk18;
    float unk1C;
    float unk20;
    float unk24;
    float unk28;
    float unk2C;
    s8 *unk30;
    Vec *unk34;
    Vec *unk38;
    Vec *unk3C;
    Vec *unk40;
    Vec *unk44;
    Vec *unk48;
    Vec *unk4C;
    s16 *unk50;
    s16 *unk54;
    float *unk58;
    float *unk5C;
    float *unk60;
    float *unk64;
    float *unk68;
} WorkE6E8;

void fn_2_DBCC(s16 arg0)
{
    omObjData *temp_r31;
    s32 temp_r30;
    s8 *temp_r28;
    float temp_f31;
    temp_r31 = lbl_2_bss_C4 = omAddObjEx(lbl_2_bss_1C, 1145, arg0, 0, -1, NULL);
    omSetStatBit(temp_r31, 0x100);
    temp_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(s8), MEMORY_DEFAULT_NUM);
    temp_r28 = temp_r31->data;
    temp_r31->work[0] = arg0;
    for (temp_r30 = 0; temp_r30 < arg0; temp_r30++) {
        if (temp_r30 < 3) {
            temp_r31->model[temp_r30] = Hu3DModelCreateFile(lbl_2_data_460[temp_r30]);
        }
        else {
            temp_r31->model[temp_r30] = Hu3DModelLink(temp_r31->model[temp_r30 % 3]);
        }
        temp_f31 = 0.5f + ((1.0f / 255.0f) * (0.5f * frandu8()));
        Hu3DModelScaleSet(temp_r31->model[temp_r30], temp_f31, temp_f31, temp_f31);
        Hu3DModelAttrSet(temp_r31->model[temp_r30], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(temp_r31->model[temp_r30], HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(temp_r31->model[temp_r30], (1.0f / 255.0f) * (Hu3DMotionMaxTimeGet(temp_r31->model[temp_r30]) * frandu8()));
        temp_r28[temp_r30] = 0;
    }
}

void fn_2_DE1C(WorkE6E8 *arg0)
{
    HuMemDirectFree(arg0->unk34);
    HuMemDirectFree(arg0->unk38);
    HuMemDirectFree(arg0->unk40);
    HuMemDirectFree(arg0->unk44);
    HuMemDirectFree(arg0->unk48);
    HuMemDirectFree(arg0->unk4C);
    HuMemDirectFree(arg0->unk3C);
    HuMemDirectFree(arg0->unk50);
    HuMemDirectFree(arg0->unk54);
    HuMemDirectFree(arg0->unk58);
    HuMemDirectFree(arg0->unk5C);
    HuMemDirectFree(arg0->unk60);
    HuMemDirectFree(arg0->unk64);
    HuMemDirectFree(arg0->unk68);
    HuMemDirectFree(arg0->unk30);
}

omObjData *fn_2_DEBC(s16 arg0)
{
    WorkE6E8 *temp_r31;
    s32 temp_r29;
    omObjData *temp_r28;
    s32 temp_r27;
    s8 *temp_r26;
    if (arg0 <= 0) {
        return NULL;
    }
    temp_r28 = omAddObjEx(lbl_2_bss_1C, 1145, arg0, 0, -1, NULL);
    omSetStatBit(temp_r28, 0x100);
    temp_r28->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkE6E8), MEMORY_DEFAULT_NUM);
    temp_r31 = temp_r28->data;
    temp_r31->unk34 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    temp_r31->unk38 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    temp_r31->unk40 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    temp_r31->unk44 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    temp_r31->unk48 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    temp_r31->unk4C = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    temp_r31->unk3C = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(Vec), MEMORY_DEFAULT_NUM);
    temp_r31->unk50 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(s16), MEMORY_DEFAULT_NUM);
    temp_r31->unk54 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(s16), MEMORY_DEFAULT_NUM);
    temp_r31->unk58 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(float), MEMORY_DEFAULT_NUM);
    temp_r31->unk5C = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(float), MEMORY_DEFAULT_NUM);
    temp_r31->unk60 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(float), MEMORY_DEFAULT_NUM);
    temp_r31->unk64 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(float), MEMORY_DEFAULT_NUM);
    temp_r31->unk68 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(float), MEMORY_DEFAULT_NUM);
    temp_r31->unk30 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * sizeof(s8), MEMORY_DEFAULT_NUM);
    for (temp_r27 = 0; temp_r27 < arg0; temp_r27++) {
        temp_r26 = lbl_2_bss_C4->data;
        for (temp_r29 = 0; temp_r29 < lbl_2_bss_C4->work[0]; temp_r29++) {
            if (temp_r26[temp_r29] == 0) {
                temp_r26[temp_r29] = 1;
                temp_r28->model[temp_r27] = lbl_2_bss_C4->model[temp_r29];
                temp_r31->unk54[temp_r27] = temp_r29 % 3;
                temp_r31->unk30[temp_r27] = temp_r29;
                break;
            }
        }
        if (temp_r29 == lbl_2_bss_C4->work[0]) {
            arg0 -= (s32)arg0 - temp_r27;
            break;
        }
    }
    if (arg0 == 0) {
        fn_2_DE1C(temp_r31);
        omDelObjEx(HuPrcCurrentGet(), temp_r28);
        temp_r28 = NULL;
    }
    else {
        temp_r31->unk0 = arg0;
        temp_r31->unk10 = 0;
    }
    return temp_r28;
}

void fn_2_E24C(omObjData *object)
{
    WorkE6E8 *temp_r31;
    s32 temp_r30;
    s8 *temp_r28;
    temp_r31 = object->data;
    temp_r28 = lbl_2_bss_C4->data;
    for (temp_r30 = 0; temp_r30 < temp_r31->unk0; temp_r30++) {
        temp_r28[temp_r31->unk30[temp_r30]] = 0;
        Hu3DModelAttrSet(object->model[temp_r30], HU3D_ATTR_DISPOFF);
    }
    fn_2_DE1C(temp_r31);
    omDelObjEx(HuPrcCurrentGet(), object);
}

void fn_2_E6E8(omObjData *object);

void fn_2_E364(omObjData *object, s16 arg1)
{
    s32 temp_r31;
    WorkE6E8 *temp_r29 = object->data;
    if (arg1 == 1) {
        for (temp_r31 = 0; temp_r31 < temp_r29->unk0; temp_r31++) {
            Hu3DModelAttrReset(object->model[temp_r31], HU3D_ATTR_DISPOFF);
        }
        object->func = fn_2_E6E8;
    }
    else {
        for (temp_r31 = 0; temp_r31 < temp_r29->unk0; temp_r31++) {
            Hu3DModelAttrSet(object->model[temp_r31], HU3D_ATTR_DISPOFF);
        }
        object->func = NULL;
    }
}

void fn_2_E420(omObjData *object, Vec *arg1, Vec *arg2)
{
    WorkE6E8 *temp_r31 = object->data;
    s32 temp_r30;
    for (temp_r30 = 0; temp_r30 < temp_r31->unk0; temp_r30++) {
        temp_r31->unk34[temp_r30].x = (arg1->x - arg2->x) + ((1.0f / 255.0f) * (2.0f * arg2->x * frandu8()));
        temp_r31->unk34[temp_r30].y = (arg1->y - arg2->y) + ((1.0f / 255.0f) * (2.0f * arg2->y * frandu8()));
        temp_r31->unk34[temp_r30].z = (arg1->z - arg2->z) + ((1.0f / 255.0f) * (2.0f * arg2->z * frandu8()));
        VECNormalize(&temp_r31->unk34[temp_r30], &temp_r31->unk38[temp_r30]);
        temp_r31->unk5C[temp_r30] = temp_r31->unk64[temp_r30] = temp_r31->unk60[temp_r30] = temp_r31->unk68[temp_r30] = 0;
        temp_r31->unk58[temp_r30] = 0.1f;
        Hu3DModelPosSet(object->model[temp_r30], temp_r31->unk34[temp_r30].x, temp_r31->unk34[temp_r30].y, temp_r31->unk34[temp_r30].z);
    }
}

void fn_2_E66C(omObjData *object, Vec *pos)
{
    WorkE6E8 *temp_r31 = object->data;
    temp_r31->unk4 = *pos;
}

void fn_2_E69C(omObjData *object, float arg2, float arg3)
{
    WorkE6E8 *temp_r31 = object->data;
    temp_r31->unk14 = arg2;
    temp_r31->unk18 = arg3;
}

void fn_2_E6BC(omObjData *object, float arg2, float arg3, float arg4, float arg5, float arg6)
{
    WorkE6E8 *temp_r31 = object->data;
    temp_r31->unk1C = arg2;
    temp_r31->unk20 = arg3;
    temp_r31->unk24 = arg4;
    temp_r31->unk28 = arg5;
    temp_r31->unk2C = arg6;
}

void fn_2_E6E8(omObjData *object)
{
    WorkE6E8 *temp_r31 = object->data;
    s32 temp_r30;
    s32 temp_r29;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    Mtx sp158, sp128, spF8, spC8, sp98, sp68;
    Vec sp5C, sp50, sp44, sp38, sp2C, sp20, sp14, sp8;
    for (temp_r30 = 0; temp_r30 < temp_r31->unk0; temp_r30++) {
        temp_r31->unk3C[temp_r30].x = 0;
        temp_r31->unk3C[temp_r30].y = 0;
        temp_r31->unk3C[temp_r30].z = 0;
        temp_r31->unk40[temp_r30].x = 0;
        temp_r31->unk40[temp_r30].y = 0;
        temp_r31->unk40[temp_r30].z = 0;
        temp_r31->unk44[temp_r30].x = 0;
        temp_r31->unk44[temp_r30].y = 0;
        temp_r31->unk44[temp_r30].z = 0;
        temp_r31->unk48[temp_r30].x = 0;
        temp_r31->unk48[temp_r30].y = 0;
        temp_r31->unk48[temp_r30].z = 0;
        temp_r31->unk4C[temp_r30].x = 0;
        temp_r31->unk4C[temp_r30].y = 0;
        temp_r31->unk4C[temp_r30].z = 0;
        temp_r31->unk50[temp_r30] = 0;
    }
    for (temp_r30 = 0; temp_r30 < temp_r31->unk0; temp_r30++) {
        for (temp_r29 = temp_r30 + 1; temp_r29 < temp_r31->unk0; temp_r29++) {
            VECSubtract(&temp_r31->unk34[temp_r30], &temp_r31->unk34[temp_r29], &sp5C);
            temp_f28 = VECMag(&sp5C);
            if (temp_f28 < temp_r31->unk14) {
                VECScale(&sp5C, &sp50, 1.0f / (temp_f28 * temp_f28));
                VECAdd(&temp_r31->unk3C[temp_r30], &sp50, &temp_r31->unk3C[temp_r30]);
                VECSubtract(&temp_r31->unk3C[temp_r29], &sp50, &temp_r31->unk3C[temp_r29]);
                if (temp_r31->unk54[temp_r30] == temp_r31->unk54[temp_r29]) {
                    VECScale(&temp_r31->unk38[temp_r29], &sp50, 1.0f / temp_f28);
                    VECAdd(&temp_r31->unk40[temp_r30], &sp50, &temp_r31->unk40[temp_r30]);
                    VECScale(&temp_r31->unk38[temp_r30], &sp50, 1.0f / temp_f28);
                    VECAdd(&temp_r31->unk40[temp_r29], &sp50, &temp_r31->unk40[temp_r29]);
                    VECAdd(&temp_r31->unk44[temp_r30], &temp_r31->unk34[temp_r29], &temp_r31->unk44[temp_r30]);
                    VECAdd(&temp_r31->unk44[temp_r29], &temp_r31->unk34[temp_r30], &temp_r31->unk44[temp_r29]);
                }
                temp_r31->unk50[temp_r30]++;
                temp_r31->unk50[temp_r29]++;
            }
        }
        for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
            sp44.x = lbl_2_bss_118[temp_r29]->trans.x;
            sp44.y = lbl_2_bss_118[temp_r29]->trans.y;
            sp44.z = lbl_2_bss_118[temp_r29]->trans.z;
            VECSubtract(&temp_r31->unk34[temp_r30], &sp44, &sp38);
            if (!(VECDotProduct(&sp38, &temp_r31->unk38[temp_r30]) > 0)) {
                temp_f30 = VECMag(&sp38) - 200;
                if (temp_f30 < temp_r31->unk14) {
                    temp_f30 -= 100;
                    if (temp_f30 < 0.01f) {
                        temp_f30 = 0.01f;
                    }
                    VECScale(&sp38, &sp38, 1.0f / temp_f30);
                    VECAdd(&temp_r31->unk4C[temp_r30], &sp38, &temp_r31->unk4C[temp_r30]);
                }
            }
        }
        if (temp_r31->unk50[temp_r30] != 0) {
            VECScale(&temp_r31->unk44[temp_r30], &temp_r31->unk44[temp_r30], 1.0f / temp_r31->unk50[temp_r30]);
            VECSubtract(&temp_r31->unk44[temp_r30], &temp_r31->unk34[temp_r30], &sp2C);
            temp_f29 = VECMag(&sp2C);
            if (temp_f29 > 0.0f) {
                VECScale(&sp2C, &temp_r31->unk44[temp_r30], 1.0f / temp_f29);
            }
            else {
                temp_r31->unk44[temp_r30].x = 0;
                temp_r31->unk44[temp_r30].y = 0;
                temp_r31->unk44[temp_r30].z = 0;
            }
            VECScale(&temp_r31->unk40[temp_r30], &temp_r31->unk40[temp_r30], 1.0f / temp_r31->unk50[temp_r30]);
            temp_f29 = VECMag(&temp_r31->unk40[temp_r30]);
            if (temp_f29 > 0) {
                VECScale(&temp_r31->unk40[temp_r30], &temp_r31->unk40[temp_r30], 1.0f / temp_f29);
                VECSubtract(&temp_r31->unk40[temp_r30], &temp_r31->unk38[temp_r30], &sp2C);
                VECScale(&sp2C, &temp_r31->unk40[temp_r30], 1.0f / temp_f29);
            }
        }
        VECSubtract(&temp_r31->unk4, &temp_r31->unk34[temp_r30], &temp_r31->unk48[temp_r30]);
        VECNormalize(&temp_r31->unk48[temp_r30], &temp_r31->unk48[temp_r30]);
    }
    for (temp_r30 = 0; temp_r30 < temp_r31->unk0; temp_r30++) {
        sp20.x = 0;
        sp20.y = 0;
        sp20.z = 0;
        VECScale(&temp_r31->unk3C[temp_r30], &sp8, temp_r31->unk1C);
        VECAdd(&sp8, &sp20, &sp20);
        VECScale(&temp_r31->unk4C[temp_r30], &sp8, temp_r31->unk20);
        VECAdd(&sp8, &sp20, &sp20);
        VECScale(&temp_r31->unk40[temp_r30], &sp8, temp_r31->unk24);
        VECAdd(&sp8, &sp20, &sp20);
        VECScale(&temp_r31->unk44[temp_r30], &sp8, temp_r31->unk28);
        VECAdd(&sp8, &sp20, &sp20);
        VECScale(&temp_r31->unk48[temp_r30], &sp8, temp_r31->unk2C);
        VECAdd(&sp8, &sp20, &sp20);
        temp_f27 = VECMag(&sp20);
        if (temp_f27 > 1.0f) {
            VECScale(&sp20, &sp20, 1.0f / temp_f27);
        }
        if (sp20.y > 0.01f) {
            temp_r31->unk60[temp_r30] += 0.02f;
            if (temp_r31->unk60[temp_r30] > 0.8f) {
                temp_r31->unk60[temp_r30] = 0.8f;
            }
        }
        else {
            if (sp20.y < -0.01f) {
                temp_r31->unk60[temp_r30] -= 0.02f;
                if (temp_r31->unk60[temp_r30] < -0.8f) {
                    temp_r31->unk60[temp_r30] = -0.8f;
                }
            }
            else {
                temp_r31->unk60[temp_r30] *= 0.98f;
            }
        }
        temp_r31->unk58[temp_r30] -= 0.002 * temp_r31->unk60[temp_r30];
        temp_r31->unk58[temp_r30] = temp_r31->unk18 + (0.99f * (temp_r31->unk58[temp_r30] - temp_r31->unk18));
        if (temp_r31->unk58[temp_r30] < 0.4f * temp_r31->unk18) {
            temp_r31->unk58[temp_r30] = 0.4f * temp_r31->unk18;
        }
        if (temp_r31->unk58[temp_r30] > 5.0f * temp_r31->unk18) {
            temp_r31->unk58[temp_r30] = 5.0f * temp_r31->unk18;
        }
        sp14 = sp20;
        sp14.y = 0;
        sp8 = temp_r31->unk38[temp_r30];
        if (VECMag(&sp14) > 0) {
            VECNormalize(&sp14, &sp14);
        }
        temp_f31 = VECDotProduct(&sp14, &sp8);
        if (temp_f31 > 0.7f) {
            temp_f31 -= 0.7f;
            temp_r31->unk58[temp_r30] += 0.005f * temp_f31;
        }
        VECCrossProduct(&sp14, &sp8, &sp14);
        temp_f31 = 0.07f * ((1.0f - temp_f31) / 2);
        if (sp14.y > 0.05f) {
            temp_r31->unk68[temp_r30] = 0.05f * (temp_f31 + (19.0f * temp_r31->unk68[temp_r30]));
        }
        else if (sp14.y < -0.05f) {
            temp_r31->unk68[temp_r30] = 0.05f * ((19.0f * temp_r31->unk68[temp_r30]) - temp_f31);
        }
        else {
            temp_r31->unk68[temp_r30] *= 0.98f;
        }
        temp_r31->unk5C[temp_r30] += temp_r31->unk68[temp_r30];
        temp_r31->unk64[temp_r30] = 20.0f * -temp_r31->unk68[temp_r30];
        MTXTrans(sp158, temp_r31->unk34[temp_r30].x, temp_r31->unk34[temp_r30].y, temp_r31->unk34[temp_r30].z);
        MTXRotDeg(sp128, 'x', (temp_r31->unk60[temp_r30] / M_PI) * 180.0);
        MTXRotDeg(spF8, 'y', (temp_r31->unk5C[temp_r30] / M_PI) * 180.0);
        MTXRotDeg(spC8, 'z', (temp_r31->unk64[temp_r30] / M_PI) * 180.0);
        MTXConcat(sp128, spF8, sp98);
        MTXConcat(spC8, sp98, sp68);
        MTXConcat(sp68, sp158, sp98);
        temp_r31->unk38[temp_r30].x = MTXRowCol(sp98, 2, 0);
        temp_r31->unk38[temp_r30].y = MTXRowCol(sp98, 2, 1);
        temp_r31->unk38[temp_r30].z = MTXRowCol(sp98, 2, 2);
        temp_r31->unk34[temp_r30].x += 100.0f * (temp_r31->unk38[temp_r30].x * temp_r31->unk58[temp_r30]);
        temp_r31->unk34[temp_r30].y += 100.0f * (temp_r31->unk38[temp_r30].y * temp_r31->unk58[temp_r30]);
        temp_r31->unk34[temp_r30].z += 100.0f * (temp_r31->unk38[temp_r30].z * temp_r31->unk58[temp_r30]);
        if (temp_r31->unk34[temp_r30].y < -350.0f) {
            temp_r31->unk34[temp_r30].y = -350.0f;
        }
        Hu3DModelPosSet(object->model[temp_r30], temp_r31->unk34[temp_r30].x, temp_r31->unk34[temp_r30].y, temp_r31->unk34[temp_r30].z);
        Hu3DModelRotSet(object->model[temp_r30], (-temp_r31->unk60[temp_r30] / M_PI) * 180.0, (-temp_r31->unk5C[temp_r30] / M_PI) * 180.0, 0);
    }
}

void fn_2_F778()
{
    CameraData *temp_r31;
    s32 temp_r30;
    float sp8[7];
    temp_r31 = lbl_2_bss_DC->data;
    sp8[0] = temp_r31->pos.x;
    sp8[1] = temp_r31->pos.y;
    sp8[2] = temp_r31->pos.z;
    sp8[3] = temp_r31->up.x;
    sp8[4] = temp_r31->up.y;
    sp8[5] = temp_r31->up.z;
    sp8[6] = temp_r31->target.x;
    fontcolor = FONT_COLOR_WHITE;
    for (temp_r30 = 0; temp_r30 < 7; temp_r30++) {
        if (temp_r30 == lbl_2_bss_18) {
            print8(24.0 + (1.5 * ((temp_r30 * 8) * 7)), 384, 1.5f, "____");
        }
        print8(24.0 + (1.5 * ((temp_r30 * 8) * 7)), 400, 1.5f, "%.2f", sp8[temp_r30]);
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_LEFT) {
        if (--lbl_2_bss_18 < 0) {
            lbl_2_bss_18 = 6;
        }
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_RIGHT) {
        if (++lbl_2_bss_18 > 6) {
            lbl_2_bss_18 = 0;
        }
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_UP) {
        if (HuPadBtn[0] & PAD_TRIGGER_R) {
            sp8[lbl_2_bss_18] += 1.0f;
        }
        else if (HuPadBtn[0] & PAD_TRIGGER_L) {
            sp8[lbl_2_bss_18] += 0.1f;
        }
        else {
            sp8[lbl_2_bss_18] += 0.01f;
        }
        if (sp8[lbl_2_bss_18] > 999.99f) {
            sp8[lbl_2_bss_18] = 999.99f;
        }
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_DOWN) {
        if (HuPadBtn[0] & PAD_TRIGGER_R) {
            sp8[lbl_2_bss_18] -= 1.0f;
        }
        else if (HuPadBtn[0] & PAD_TRIGGER_L) {
            sp8[lbl_2_bss_18] -= 0.1f;
        }
        else {
            sp8[lbl_2_bss_18] -= 0.01f;
        }
        if (sp8[lbl_2_bss_18] < 0) {
            sp8[lbl_2_bss_18] = 0;
        }
    }
    temp_r31->pos.x = sp8[0];
    temp_r31->pos.y = sp8[1];
    temp_r31->pos.z = sp8[2];
    temp_r31->up.x = sp8[3];
    temp_r31->up.y = sp8[4];
    temp_r31->up.z = sp8[5];
    temp_r31->target.x = sp8[6];
}

void fn_2_FF98(omObjData *object);

omObjData *fn_2_FC40(s16 arg0, Vec *arg1, Vec *arg2, Vec *arg3)
{
    omObjData *temp_r30;
    omObjData *temp_r22;
    temp_r22 = omAddObjEx(HuPrcCurrentGet(), 1140, 0, 0, -1, fn_2_FF98);
    temp_r30 = fn_2_DEBC(arg0);
    temp_r22->work[0] = (u32)temp_r30;
    fn_2_E420(temp_r30, arg1, arg2);
    fn_2_E66C(temp_r30, arg3);
    fn_2_E69C(temp_r30, 90.0f, 0.045999996f);
    fn_2_E6BC(temp_r30, 5.0f, 1.5f, 0.08f, 0.8f, 0.8f);
    fn_2_E364(temp_r30, 1);
    return temp_r22;
}

void fn_2_FF98(omObjData *object)
{
    WorkE6E8 *temp_r29;
    omObjData *temp_r28;
    s32 temp_r25;
    s32 temp_r24;
    temp_r24 = 0;
    temp_r28 = (omObjData *)(object->work[0]);
    temp_r29 = temp_r28->data;
    temp_r29->unk4.x += object->scale.x * sind(object->trans.x);
    temp_r29->unk4.y += object->scale.y * sind(object->trans.x);
    temp_r29->unk4.z += object->scale.z * sind(object->trans.x);
    object->trans.x += object->rot.x;
    if (object->trans.x >= 360.0f) {
        object->trans.x -= 360.0f;
    }
    if (object->trans.x < 0.0f) {
        object->trans.x += 360.0f;
    }
    for (temp_r25 = 0; temp_r25 < temp_r29->unk0; temp_r25++) {
        if (temp_r29->unk34[temp_r25].z >= lbl_2_bss_6C.z) {
            temp_r24++;
        }
    }
    if (temp_r24 == temp_r29->unk0) {
        fn_2_E24C(temp_r28);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}
