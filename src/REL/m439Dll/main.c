#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"

#include "game/init.h"

#include "game/esprite.h"

#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/minigame_seq.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "ext_math.h"

#include "rel_sqrt_consts.h"

#include "REL/m439data.h"

typedef struct camera_params {
    float zoom;
    Vec pos;
    Vec rot;
} CameraViewParams;

CameraViewParams lbl_1_data_741C[] = { {
                                           4775,
                                           -2800,
                                           0,
                                           -7700,
                                           343,
                                           20,
                                           0,
                                       },
    {
        5000,
        0,
        0,
        0,
        290,
        0,
        0,
    },
    {
        2800,
        0,
        0,
        -7600,
        347,
        0,
        0,
    },
    { 2800, 0, 0, -7600, 290, 0, 0 } };

typedef struct struct_data_748C {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC[2];
} StructData748C;

StructData748C lbl_1_data_748C[16] = { { 0, -1, 1, { 1, 0 } }, { 1, 0, 2, { 2, 3 } }, { 2, 1, 1, { 4, 0 } }, { 2, 1, 1, { 5, 0 } },
    { 3, 2, 2, { 6, 7 } }, { 3, 3, 2, { 8, 9 } }, { 4, 4, 1, { 10, 0 } }, { 4, 4, 1, { 11, 0 } }, { 4, 5, 1, { 12, 0 } }, { 4, 5, 1, { 13, 0 } },
    { 5, 6, 0, { 0, 0 } }, { 5, 7, 0, { 0, 0 } }, { 5, 8, 0, { 0, 0 } }, { 5, 9, 0, { 0, 0 } } };

float lbl_1_data_75CC[5] = { -700, -2200, -3600, -5200, -6600 };
s32 lbl_1_data_75E0[4] = { 1, 2, 4, 8 };
Vec lbl_1_data_75F0 = { 700, 2500, -700 };
Vec lbl_1_data_75FC = { 0, 0, 0 };
GXColor lbl_1_data_7608 = { 255, 255, 255, 255 };
Vec lbl_1_data_760C = { 700, 2500, -700 };
Vec lbl_1_data_7618 = { 0, 1, 0 };

omObjData *lbl_1_bss_170;
omObjData *lbl_1_bss_16C;
omObjData *lbl_1_bss_168;
u32 lbl_1_bss_164;
u32 lbl_1_bss_160;
s32 lbl_1_bss_150[4];
s32 lbl_1_bss_14C;
s32 lbl_1_bss_148;
s32 lbl_1_bss_144;
s32 lbl_1_bss_140;
s16 lbl_1_bss_13C;
s16 lbl_1_bss_13A;
s16 lbl_1_bss_132[4];
s16 lbl_1_bss_130;
s16 lbl_1_bss_12E;
s16 lbl_1_bss_12C;
Process *lbl_1_bss_128;
void *lbl_1_bss_11C[3];
Vec lbl_1_bss_F8[3];
Vec lbl_1_bss_D4[3];
Mtx lbl_1_bss_44[3];
AnimData *lbl_1_bss_40;
Vec lbl_1_bss_34;
s16 lbl_1_bss_32;
s16 lbl_1_bss_30;
s16 lbl_1_bss_10[16];
StructData748C *lbl_1_bss_C;
StructData748C *lbl_1_bss_8;
s16 pad_05_00000000_bss[4];

void fn_1_384(omObjData *object);
void fn_1_A18(Process *objman);
void fn_1_49C8(Process *objman);
void fn_1_5BA0(Process *objman);
void fn_1_73F4(Process *objman);

void fn_1_6C08(omObjData *object);

void ObjectSetup(void)
{
    Process *objman;
    s16 light;

    CameraData *camera = &Hu3DCamera[0];
    OSReport("******* M439ObjectSetup *********\n");
    objman = omInitObjMan(50, 8192);
    omGameSysInit(objman);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 10, 100, 15000, 1.2);
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    lbl_1_bss_168 = omAddObjEx(objman, 32730, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_168->work[0] = 1;
    lbl_1_bss_34.x = lbl_1_data_75FC.x - lbl_1_data_75F0.x;
    lbl_1_bss_34.y = lbl_1_data_75FC.y - lbl_1_data_75F0.y;
    lbl_1_bss_34.z = lbl_1_data_75FC.z - lbl_1_data_75F0.z;
    VECNormalize(&lbl_1_bss_34, &lbl_1_bss_34);
    light = Hu3DGLightCreateV(&lbl_1_data_75F0, &lbl_1_bss_34, &lbl_1_data_7608);
    Hu3DGLightInfinitytSet(light);
    Hu3DGLightStaticSet(light, 1);
    Hu3DShadowCreate(20, 200, 10000);
    Hu3DShadowTPLvlSet(0.625f);
    Hu3DShadowPosSet(&lbl_1_data_760C, &lbl_1_data_7618, &lbl_1_data_75FC);
    HuAudSndGrpSet(65);
    lbl_1_bss_170 = omAddObjEx(objman, 0, 0, 0, -1, fn_1_384);
    lbl_1_bss_16C = omAddObjEx(objman, 10, 0, 0, -1, fn_1_6C08);
    fn_1_A18(objman);
    fn_1_49C8(objman);
    fn_1_5BA0(objman);
    fn_1_73F4(objman);
}

void fn_1_364(s32 arg0)
{
    lbl_1_bss_160 = arg0;
}

s32 fn_1_374(void)
{
    return lbl_1_bss_160;
}

void fn_1_408(omObjData *object);

void fn_1_384(omObjData *object)
{
    fn_1_364(0);
    lbl_1_bss_14C = 60;
    lbl_1_bss_12E = 60;
    lbl_1_bss_12C = 60;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    object->func = fn_1_408;
}

s32 lbl_1_data_7648 = -1;
s32 lbl_1_data_764C = -1;

void fn_1_9BC(omObjData *object);

s32 fn_1_B7C(void);
void fn_1_C00(void);

void fn_1_408(omObjData *object)
{
    switch (fn_1_374()) {
        case 0:
            if (lbl_1_bss_14C == 60) {
                HuAudFXPlay(1797);
            }
            if (--lbl_1_bss_14C == 0) {
                fn_1_364(1);
                lbl_1_bss_14C = 120;
            }
            break;

        case 1:
            if (--lbl_1_bss_14C == 0) {
                WipeColorSet(0, 0, 0);
                fn_1_364(2);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
            }
            break;

        case 2:
            if (!WipeStatGet()) {
                fn_1_364(3);
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
                lbl_1_data_764C = HuAudFXPlay(1798);
            }
            break;

        case 3:
            if (!WipeStatGet()) {
                fn_1_364(4);
                lbl_1_bss_32 = MGSeqStartCreate();
            }
            break;

        case 4:
            if (!MGSeqStatGet(lbl_1_bss_32)) {
                fn_1_364(5);
                lbl_1_bss_30 = MGSeqTimerCreate(60);
            }
            if (lbl_1_data_7648 < 0 && (MGSeqStatGet(lbl_1_bss_32) & 0x10)) {
                lbl_1_data_7648 = HuAudSeqPlay(75);
            }
            break;

        case 5:
            if (--lbl_1_bss_12C == 0) {
                lbl_1_bss_12E--;
                MGSeqParamSet(lbl_1_bss_30, 1, lbl_1_bss_12E);
                lbl_1_bss_12C = 60;
            }
            if (lbl_1_bss_130 >= 3 || lbl_1_bss_12E == 0) {
                fn_1_364(6);
                lbl_1_bss_32 = MGSeqFinishCreate();
                HuAudSeqFadeOut(lbl_1_data_7648, 100);
            }
            break;

        case 6:
            if (lbl_1_bss_30 >= 0) {
                MGSeqParamSet(lbl_1_bss_30, 2, -1);
                lbl_1_bss_30 = -1;
            }
            if (!MGSeqStatGet(lbl_1_bss_32)) {
                fn_1_364(7);
                lbl_1_bss_14C = 60;
            }
            break;

        case 7:
            if (fn_1_B7C() && --lbl_1_bss_14C == 0) {
                fn_1_C00();
                fn_1_364(9);
                if (lbl_1_bss_130) {
                    HuAudSStreamPlay(1);
                }
                else {
                    HuAudSStreamPlay(4);
                }
                lbl_1_bss_14C = 210;
            }
            break;

        case 9:
            if (--lbl_1_bss_14C == 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                WipeColorSet(255, 255, 255);
                HuAudFXStop(lbl_1_data_764C);
                object->func = fn_1_9BC;
            }
            break;
    }
    if (lbl_1_bss_13A) {
        s32 i;
        for (i = 0; i < lbl_1_bss_13A; i++) {
            GWPlayerCoinWinSet(lbl_1_bss_132[i], lbl_1_bss_13C);
        }
        lbl_1_bss_13C += lbl_1_bss_13A;
        lbl_1_bss_130 += lbl_1_bss_13A;
        lbl_1_bss_13A = 0;
    }
    if (omSysExitReq && !WipeStatGet()) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        WipeColorSet(255, 255, 255);
        object->func = fn_1_9BC;
    }
}

void fn_1_B20(void);
void fn_1_5CAC(void);

void fn_1_9BC(omObjData *object)
{
    if (!WipeStatGet()) {
        fn_1_B20();
        fn_1_5CAC();
        MGSeqKillAll();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
        OSReport("******* M439Exit *********\n");
    }
}

void fn_1_D0C(omObjData *object);

void fn_1_A18(Process *objman)
{
    s32 i;
    lbl_1_bss_150[0] = lbl_1_bss_150[1] = lbl_1_bss_150[2] = lbl_1_bss_150[3] = -1;
    lbl_1_bss_148 = 0;
    lbl_1_bss_13C = 0;
    lbl_1_bss_13A = 0;
    lbl_1_bss_130 = 0;
    omMakeGroupEx(objman, 0, 4);
    for (i = 0; i < 4; i++) {
        omAddObjEx(objman, 5, 3, 50, 0, fn_1_D0C);
    }
    lbl_1_bss_40 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M439, 0x16), MEMORY_DEFAULT_NUM));
}

void fn_1_4978(omObjData *object);

void fn_1_B20(void)
{
    omObjData **objList = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    s32 i;
    for (i = 0; i < 4; i++) {
        fn_1_4978(objList[i]);
    }
}

typedef struct work_d0c {
    u16 unk0_field0 : 1;
    u16 unk0_field1 : 1;
    u16 unk0_field2 : 1;
    u16 unk0_field3 : 1;
    u16 unk0_field4 : 1;
    u16 unk0_field5 : 1;
    u16 unk0_field6 : 1;
    u16 unk0_field7 : 1;
    u16 unk0_field8 : 1;
    s16 unk2;
    s16 unk4;
    s8 unk6;
    s8 unk7;
    u16 unk8;
    u16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    Vec unk14;
    Vec unk20;
    s32 unk2C;
    u32 unk30;
    float unk34;
    float unk38;
    s16 unk3C;
    s16 unk3E;
    float unk40;
    s16 unk44;
    s16 unk46;
    float unk48;
    float unk4C;
    Vec unk50;
    Vec unk5C;
    Vec unk68;
    Vec unk74;
    u16 unk80;
    Vec unk84;
    float unk90;
    float unk94;
    Vec unk98;
    float unkA4;
    float unkA8;
} WorkD0C;

s32 fn_1_B7C(void)
{
    omObjData **objList = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    s32 i;
    for (i = 0; i < 4; i++) {
        WorkD0C *work = objList[i]->data;
        if (!work->unk0_field7) {
            return 0;
        }
    }
    return 1;
}

void fn_1_C00(void)
{
    omObjData **objList = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    s32 i;
    if (lbl_1_bss_13C == 0) {
        for (i = 0; i < 4; i++) {
            GWPlayerCoinWinSet(i, 3);
        }
    }
    else {
        for (i = 0; i < 4; i++) {
            WorkD0C *work = objList[i]->data;
            if (!work->unk0_field0) {
                GWPlayerCoinWinSet(i, lbl_1_bss_13C);
            }
        }
    }
}

s32 lbl_1_data_7694[7] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x14), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x50), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x72) };

void fn_1_4528(ModelData *model, ParticleData *particle, Mtx matrix);

void fn_1_2BB4(omObjData *object);

void fn_1_D0C(omObjData *object)
{
    WorkD0C *work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WorkD0C), MEMORY_DEFAULT_NUM);
    u32 i;
    s32 charNo;
    object->data = work;
    memset(work, 0, sizeof(WorkD0C));
    work->unk2 = lbl_1_bss_148++;
    work->unk4 = GWPlayerCfg[work->unk2].pad_idx;
    charNo = GWPlayerCfg[work->unk2].character;
    work->unkC = charNo;
    work->unkE = GWPlayerCfg[work->unk2].diff;
    work->unk10 = GWPlayerCfg[work->unk2].group;
    object->model[0] = CharModelCreate(charNo, 8);
    if (work->unk2 == 0) {
        Hu3DModelShadowSet(object->model[0]);
    }
    Hu3DModelCameraSet(object->model[0], lbl_1_data_75E0[work->unk2]);
    work->unk2C = 0;
    work->unk30 = 0x40000001;
    for (i = 0; i < 7; i++) {
        object->motion[i] = CharModelMotionCreate(work->unkC, lbl_1_data_7694[i]);
    }
    Hu3DMotionSet(object->model[0], object->motion[0]);
    Hu3DModelAttrSet(object->model[0], 0x40000001);
    CharModelVoiceEnableSet(work->unkC, object->motion[4], 0);
    CharModelDataClose(work->unkC);
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M439, 0x12));
    Hu3DModelAttrSet(object->model[1], 1);
    Hu3DModelCameraSet(object->model[1], lbl_1_data_75E0[work->unk2]);
    work->unk0_field3 = 1;
    work->unk44 = 0;
    work->unk46 = 0;
    work->unk40 = 1000;
    work->unk14.x = 0;
    work->unk94 = work->unkA4 = 0.5f;
    object->rot.y = 180;
    object->model[2] = Hu3DParticleCreate(lbl_1_bss_40, 10);
    Hu3DParticleHookSet(object->model[2], fn_1_4528);
    Hu3DModelAttrSet(object->model[2], 1);
    Hu3DModelCameraSet(object->model[2], lbl_1_data_75E0[work->unk2]);
    object->func = fn_1_2BB4;
}

float fn_1_1024(float arg0, float arg1, float arg2)
{
    float temp_f31 = fmod(arg1 - arg0, 360);
    float temp_f30;
    if (temp_f31 < 0.0f) {
        temp_f31 += 360.0f;
    }
    if (temp_f31 > 180.0f) {
        temp_f31 -= 360.0f;
    }
    temp_f30 = fmod(arg0 + (arg2 * temp_f31), 360.0);
    if (temp_f30 < 0.0f) {
        temp_f30 += 360.0f;
    }
    return temp_f30;
}

float lbl_1_data_76B0[11][2] = {
    { -180.0f, -230.0f },
    { -260.0f, -150.0f },
    { -300.0f, 0.0f },
    { -260.0f, 150.0f },
    { -150.0f, 260.0f },
    { -0.0f, 300.0f },
    { 150.0f, 260.0f },
    { 260.0f, 150.0f },
    { 300.0f, -0.0f },
    { 260.0f, -150.0f },
    { 180.0f, -230.0f },
};

s32 fn_1_1128(Vec *arg0)
{
    float sp20[2];
    float sp18[2];
    float sp10[2];
    float temp_f29;

    u32 i;
    for (i = 0; i < 10; i++) {
        s32 temp_r30 = i + 1;

        float temp_f26;
        sp20[0] = lbl_1_data_76B0[temp_r30][0] - lbl_1_data_76B0[i][0];
        sp20[1] = lbl_1_data_76B0[temp_r30][1] - lbl_1_data_76B0[i][1];
        temp_f26 = (((arg0->z * sp20[1]) + ((arg0->x * sp20[0]) - (sp20[0] * lbl_1_data_76B0[i][0]))) - (sp20[1] * lbl_1_data_76B0[i][1]))
            / ((sp20[0] * sp20[0]) + (sp20[1] * sp20[1]));
        if (temp_f26 >= 0.0f && temp_f26 < 1.0f) {
            sp10[0] = lbl_1_data_76B0[i][0] + (sp20[0] * temp_f26);
            sp10[1] = lbl_1_data_76B0[i][1] + (sp20[1] * temp_f26);
            sp18[0] = arg0->x - sp10[0];
            sp18[1] = arg0->z - sp10[1];
            temp_f29 = sqrtf((sp18[0] * sp18[0]) + (sp18[1] * sp18[1]));
            if (temp_f29 < 130.0f) {
                if (temp_f29 != 0.0f) {
                    sp18[0] /= temp_f29;
                    sp18[1] /= temp_f29;
                }
                else {
                    sp18[0] = 0;
                    sp18[1] = 1;
                }
                arg0->x = sp10[0] + (130.0f * sp18[0]);
                arg0->z = sp10[1] + (130.0f * sp18[1]);
            }
        }
    }
    for (i = 0; i < 11; i++) {
        sp20[0] = arg0->x - lbl_1_data_76B0[i][0];
        sp20[1] = arg0->z - lbl_1_data_76B0[i][1];
        temp_f29 = sqrtf((sp20[0] * sp20[0]) + (sp20[1] * sp20[1]));
        if (temp_f29 < 130.0f) {
            if (temp_f29 != 0.0f) {
                sp20[0] /= temp_f29;
                sp20[1] /= temp_f29;
            }
            else {
                sp20[0] = 0;
                sp20[1] = 1;
            }
            arg0->x = lbl_1_data_76B0[i][0] + (130.0f * sp20[0]);
            arg0->z = lbl_1_data_76B0[i][1] + (130.0f * sp20[1]);
        }
    }
}

float lbl_1_data_7708[3][2][2] = { -99.8, -1431.8, 77.2, -1437.8, -1499.8, -4571.8, -1322.8, -4577.8, 1300.2, -4571.8, 1477.2, -4577.8 };

s32 fn_1_16B0(Vec *arg0)
{
    s32 i;
    for (i = 0; i < 3; i++) {
        float sp20[2];
        float sp18[2];
        float sp10[2];
        float temp_f29;
        float temp_f26;
        s32 j;
        sp20[0] = lbl_1_data_7708[i][1][0] - lbl_1_data_7708[i][0][0];
        sp20[1] = lbl_1_data_7708[i][1][1] - lbl_1_data_7708[i][0][1];
        temp_f26 = (((arg0->z * sp20[1]) + ((arg0->x * sp20[0]) - (sp20[0] * lbl_1_data_7708[i][0][0]))) - (sp20[1] * lbl_1_data_7708[i][0][1]))
            / ((sp20[0] * sp20[0]) + (sp20[1] * sp20[1]));
        if (temp_f26 >= 0.0f && temp_f26 < 1.0f) {
            sp10[0] = lbl_1_data_7708[i][0][0] + (sp20[0] * temp_f26);
            sp10[1] = lbl_1_data_7708[i][0][1] + (sp20[1] * temp_f26);
            sp18[0] = arg0->x - sp10[0];
            sp18[1] = arg0->z - sp10[1];
            temp_f29 = sqrtf((sp18[0] * sp18[0]) + (sp18[1] * sp18[1]));
            if (temp_f29 < 50.0f) {
                if (temp_f29 != 0.0f) {
                    sp18[0] /= temp_f29;
                    sp18[1] /= temp_f29;
                }
                else {
                    sp18[0] = 0;
                    sp18[1] = 1;
                }
                arg0->x = sp10[0] + (50.0f * sp18[0]);
                arg0->z = sp10[1] + (50.0f * sp18[1]);
            }
        }
        for (j = 0; j < 2; j++) {
            sp20[0] = arg0->x - lbl_1_data_7708[i][j][0];
            sp20[1] = arg0->z - lbl_1_data_7708[i][j][1];
            temp_f29 = sqrtf((sp20[0] * sp20[0]) + (sp20[1] * sp20[1]));
            if (temp_f29 < 50.0f) {
                if (temp_f29 != 0.0f) {
                    sp20[0] /= temp_f29;
                    sp20[1] /= temp_f29;
                }
                else {
                    sp20[0] = 0;
                    sp20[1] = 1;
                }
                arg0->x = lbl_1_data_7708[i][j][0] + (50.0f * sp20[0]);
                arg0->z = lbl_1_data_7708[i][j][1] + (50.0f * sp20[1]);
            }
        }
    }
}

float fn_1_1C54(s32 arg0, Vec *arg1, Vec *arg2)
{
    Vec *temp_r31;
    Vec *temp_r30;
    s32 i;
    Vec sp24;
    Vec sp18;
    s32 sp14 = -1;
    float sp10 = 1000;
    float *temp_r28 = lbl_1_data_108C[arg0];
    VECSubtract(arg2, arg1, &sp18);
    temp_r31 = lbl_1_data_1014[arg0][0];
    temp_r30 = lbl_1_data_1014[arg0][1];
    for (i = 0; i < lbl_1_data_1074[arg0] - 1; i++, temp_r31++, temp_r30++) {
        float temp_f31;
        float temp_f30;
        float temp_f29;
        float temp_f28;
        VECSubtract(&temp_r31[1], &temp_r31[0], &sp24);
        temp_f31 = VECMag2Point(&sp24);
        if (temp_f31 == 0.0f) {
            continue;
        }
        temp_f29
            = ((sp18.x * sp24.x) - (temp_r31->x * sp24.x) + (sp18.y * sp24.y) - (temp_r31->y * sp24.y) + (sp18.z * sp24.z) - (temp_r31->z * sp24.z))
            / temp_f31;
        VECSubtract(&temp_r30[1], &temp_r30[0], &sp24);
        temp_f31 = VECMag2Point(&sp24);
        if (temp_f31 == 0.0f) {
            continue;
        }
        temp_f28
            = ((sp18.x * sp24.x) - (temp_r30->x * sp24.x) + (sp18.y * sp24.y) - (temp_r30->y * sp24.y) + (sp18.z * sp24.z) - (temp_r30->z * sp24.z))
            / temp_f31;
        temp_f30 = 0.5f * (temp_f29 + temp_f28);
        if (temp_f30 < 0.0f || temp_f30 >= 1.0f) {
            continue;
        }
        else {
            return temp_r28[i] + (temp_f30 * (temp_r28[i + 1] - temp_r28[i]));
        }
    }
    return -1;
}

void fn_1_1F3C(s32 arg0, Vec *arg1, float arg2, float arg3, Vec *arg4)
{
    float *temp_r30 = lbl_1_data_108C[arg0];
    s32 i;
    for (i = 0; i < lbl_1_data_1074[arg0] - 1; i++) {
        if (arg2 < temp_r30[i + 1]) {
            break;
        }
    }
    if (i < lbl_1_data_1074[arg0] - 1) {
        float temp_f31 = (arg2 - temp_r30[i]) / (temp_r30[i + 1] - temp_r30[i]);
        Vec *temp_r29 = &lbl_1_data_1014[arg0][0][i];
        Vec *temp_r28 = &lbl_1_data_1014[arg0][1][i];
        Vec sp20;
        Vec sp14;
        Vec sp8;
        VECSubtract(&temp_r29[1], &temp_r29[0], &sp8);
        sp20.x = temp_r29->x + (temp_f31 * sp8.x);
        sp20.y = temp_r29->y + (temp_f31 * sp8.y);
        sp20.z = temp_r29->z + (temp_f31 * sp8.z);
        VECSubtract(&temp_r28[1], &temp_r28[0], &sp8);
        sp14.x = temp_r28->x + (temp_f31 * sp8.x);
        sp14.y = temp_r28->y + (temp_f31 * sp8.y);
        sp14.z = temp_r28->z + (temp_f31 * sp8.z);
        arg4->x = (arg1->x + sp20.x) + (arg3 * (sp14.x - sp20.x));
        arg4->y = (arg1->y + sp20.y) + (arg3 * (sp14.y - sp20.y));
        arg4->z = (arg1->z + sp20.z) + (arg3 * (sp14.z - sp20.z));
    }
}

float fn_1_2184(s32 arg0, float arg1)
{
    float *temp_r30 = lbl_1_data_108C[arg0];
    s32 i;
    for (i = 0; i < lbl_1_data_1074[arg0] - 1; i++) {
        if (arg1 < temp_r30[i + 1]) {
            break;
        }
    }
    if (i >= lbl_1_data_1074[arg0] - 1) {
        return -1;
    }
    else {
        return temp_r30[i + 1] - temp_r30[i];
    }
}

s16 lbl_1_data_7738[10][3] = { 1, 0, 0, 2, 1, 2, 2, 3, 4, 1, 5, 0, 1, 6, 0, 1, 7, 0, 1, 8, 0, 1, 9, 0, 1, 10, 0, 1, 11, 0 };

s32 lbl_1_data_7774[8] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x01),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x14),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x50),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18),
};

typedef struct work_5cb0 {
    s16 unk0;
    Vec unk4;
    StructData748C unk10;
} Work5CB0;

void fn_1_223C(omObjData *object)
{
    float temp_f29;
    WorkD0C *temp_r31;
    Work5CB0 *temp_r18;
    Vec sp58;
    s32 sp18;
    omObjData **sp14;
    temp_r31 = object->data;
    if (temp_r31->unk0_field4) {
        temp_r31->unk0_field4 = 0;
        sp14 = omGetGroupMemberListEx(HuPrcCurrentGet(), 1);
        temp_r18 = sp14[temp_r31->unk2]->data;
        sp18 = temp_r18[temp_r31->unk44].unk0;
        temp_r31->unk80 = lbl_1_data_7738[sp18][((lbl_1_data_7738[sp18][0] * frand8()) >> 8) + 1];
        temp_r31->unk84 = temp_r18[temp_r31->unk44].unk4;
        temp_r31->unk90 = fn_1_1C54(temp_r31->unk80, &temp_r31->unk84, &object->trans);
        if (temp_r31->unk90 < 0.0f) {
            temp_r31->unk90 = 105.0f;
        }
        temp_r31->unk90 += 20.0f;
    }
    else {
        if (temp_r31->unk0_field5) {
            temp_r31->unk94 = temp_r31->unkA4 = 0.5f;
            temp_r31->unk0_field5 = 0;
            temp_r31->unk0_field6 = 1;
        }
        else {
            VECSubtract(&temp_r31->unk98, &object->trans, &sp58);
            if (VECMag(&sp58) < 20.0f) {
                temp_r31->unk90 += 20.0f;
                temp_r31->unk0_field6 = 0;
            }
        }
    }
    if (object->trans.z < -500.0f && !temp_r31->unk0_field6 && frand8() == 0) {
        temp_r31->unkA4 = (0.55f * ((((s32)frand() & 0x1FF) - 256.0f) / 256.0f)) + 0.5f;
    }
    temp_r31->unk94 += 0.05f * (temp_r31->unkA4 - temp_r31->unk94);
    fn_1_1F3C(temp_r31->unk80, &temp_r31->unk84, temp_r31->unk90, temp_r31->unk94, &temp_r31->unk98);
    if (temp_r31->unk98.z > temp_r31->unk40) {
        temp_r31->unk98.z = temp_r31->unk40;
    }
    VECSubtract(&temp_r31->unk98, &object->trans, &sp58);
    VECNormalize(&sp58, &sp58);
    temp_f29 = 10.0 + (((18.0 + (6.0f * temp_r31->unkE)) * fn_1_2184(temp_r31->unk80, temp_r31->unk90)) / 200.0);
    if (temp_f29 > 72) {
        temp_f29 = 72;
    }
    temp_r31->unk6 = sp58.x * temp_f29;
    temp_r31->unk7 = -sp58.z * temp_f29;
}

void fn_1_2C84(omObjData *object);

s32 fn_1_62E0(float arg0);

void fn_1_2BB4(omObjData *object)
{
    WorkD0C *work = object->data;
    Hu3DModelAttrReset(object->model[1], 1);
    Hu3DModelPosSet(object->model[1], CenterM[work->unk2].x, CenterM[work->unk2].y, CenterM[work->unk2].z);
    if (fn_1_374() == 3) {
        Hu3DModelAttrSet(object->model[1], 1);
        object->func = fn_1_2C84;
    }
}

typedef struct work_4aa8 {
    u8 unk0 : 1;
    s16 unk2;
    s16 unk4;
    float unk8[2];
    float unk10;
    float unk14[4];
    s16 unk24;
    s16 unk26;
    Vec unk28;
    Vec unk34;
    Vec unk40;
} Work4AA8;

void fn_1_3C1C(omObjData *object);
s32 fn_1_6328(omObjData *object);
s32 fn_1_67B4(Vec *arg0, s32 arg1, s32 arg2, Vec *arg3, Vec *arg4);

void fn_1_2C84(omObjData *object)
{
    WorkD0C *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    omObjData *temp_r27;
    u32 temp_r26;
    omObjData **temp_r25;
    Work4AA8 *temp_r24;
    ParticleData *temp_r23;
    float temp_f31;
    float temp_f30;
    float temp_f28;
    float temp_f26;
    float temp_f25;
    float temp_f23;

    Vec spC;
    temp_r31 = object->data;
    temp_r28 = temp_r31->unk2C;
    temp_f25 = temp_r31->unk34;
    temp_r26 = temp_r31->unk30;
    if (fn_1_374() >= 6 && !temp_r31->unk0_field2) {
        temp_r31->unk0_field7 = 1;
        temp_r31->unk12 = 2;
        temp_r31->unk3E = 120;
        object->func = fn_1_3C1C;
        return;
    }
    if (fn_1_374() < 5) {
        return;
    }
    switch (temp_r31->unk12) {
        case 0:
            if (GWPlayerCfg[temp_r31->unk2].iscom == 0) {
                temp_r31->unk6 = HuPadStkX[temp_r31->unk4];
                temp_r31->unk7 = HuPadStkY[temp_r31->unk4];
                temp_r31->unk8 = HuPadBtn[temp_r31->unk4];
                temp_r31->unkA = HuPadBtnDown[temp_r31->unk4];
            }
            else {
                temp_r31->unk8 = temp_r31->unkA = 0;
                temp_r31->unk6 = temp_r31->unk7 = 0;
                fn_1_223C(object);
            }
            temp_f31 = temp_r31->unk6;
            temp_f30 = -(float)temp_r31->unk7;
            temp_f26 = VECMagPoint(temp_f31, temp_f30, 0);
            if (temp_f26 > 0.0f) {
                temp_f31 /= temp_f26;
                temp_f30 /= temp_f26;
                if (temp_f26 > 72) {
                    temp_f26 = 72;
                }
                temp_f23 = (10.0f * temp_f26) / 72.0f;
                temp_r31->unk20.x = temp_f31 * temp_f23;
                temp_r31->unk20.z = temp_f30 * temp_f23;
                temp_r31->unk14.y = temp_f23;
                object->rot.y = fn_1_1024(object->rot.y, atan2d(temp_r31->unk20.x, temp_r31->unk20.z), 0.2f);
                if (temp_r31->unk14.y < 7.5f) {
                    temp_r28 = 1;
                    temp_f25 = temp_r31->unk14.y / 7.5f;
                }
                else {
                    temp_r28 = 2;
                    temp_f25 = temp_r31->unk14.y / 10.0f;
                }
            }
            else {
                temp_r31->unk20.x = temp_r31->unk20.z = 0;
                temp_r28 = 0;
                temp_f25 = 1;
            }
            VECAdd(&object->trans, &temp_r31->unk20, &object->trans);
            fn_1_1128(&object->trans);
            fn_1_16B0(&object->trans);
            if (object->trans.z > temp_r31->unk40) {
                object->trans.z = temp_r31->unk40;
            }
            else {
                if (object->trans.z < -7300) {
                    temp_r31->unk0_field0 = 1;
                    temp_r31->unk0_field7 = 1;
                    temp_r31->unk12 = 0;
                    if (lbl_1_bss_130 == 0) {
                        temp_r31->unk0_field8 = 1;
                    }
                    lbl_1_bss_132[lbl_1_bss_13A++] = temp_r31->unk2;
                    object->func = fn_1_3C1C;
                    return;
                }
            }
            if (fn_1_67B4(&object->trans, temp_r31->unk2, temp_r31->unk44, &temp_r31->unk5C, &temp_r31->unk74) && !temp_r31->unk0_field6) {
                temp_r31->unk0_field2 = 1;
                temp_r31->unk0_field1 = 1;
                temp_r31->unk0_field5 = 1;
                temp_r31->unk0_field3 = 0;
                temp_r31->unk50.x = object->trans.x;
                temp_r31->unk50.y = object->trans.y;
                temp_r31->unk50.z = object->trans.z;
                temp_r31->unk68.y = -2000;
                temp_r31->unk12 = 2;
                temp_r31->unk3E = 12;
                temp_r23 = Hu3DData[object->model[2]].unk_120;
                temp_r23->unk_00 = 0;
                VECSubtract(&temp_r31->unk5C, &object->trans, &temp_r23->unk_04);
                Hu3DModelAttrReset(object->model[2], 1);
                Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
                temp_r25 = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
                temp_r25[temp_r31->unk2]->work[3] = 1;
            }
            else {
                spC.x = CenterM[temp_r31->unk2].x;
                spC.z = CenterM[temp_r31->unk2].z;
                spC.x += 0.1f * (object->trans.x - spC.x);
                spC.z += 0.1f * (object->trans.z - spC.z);
                temp_r29 = fn_1_62E0(spC.z - 350.0f);
                if (temp_r29 != temp_r31->unk46 && temp_r29 > 1 && temp_r29 < 6) {
                    spC.z = lbl_1_data_75CC[temp_r29 - 1] + 350.0f;
                }
                else {
                    temp_r29 = fn_1_62E0(spC.z + 350.0f);
                    if (temp_r29 != temp_r31->unk46 && temp_r31->unk46 > 1 && temp_r31->unk46 < 6) {
                        spC.z = lbl_1_data_75CC[temp_r31->unk46 - 1] - 350.0f;
                    }
                }
                CenterM[temp_r31->unk2].x = spC.x;
                CenterM[temp_r31->unk2].z = spC.z;
                temp_r29 = fn_1_62E0(object->trans.z);
                if (temp_r29 != temp_r31->unk46) {
                    temp_r31->unk46 = temp_r29;
                    temp_r31->unk44 = fn_1_6328(object);
                    temp_r31->unk0_field4 = 01;
                    if (temp_r29 > 1 && temp_r29 < 6) {
                        temp_r31->unk12++;
                        temp_r31->unk3E = 30;
                        temp_r31->unk48 = CenterM[temp_r31->unk2].z;
                        temp_r31->unk4C = object->trans.z - 350.0f;
                        temp_r31->unk40 = lbl_1_data_75CC[temp_r31->unk46 - 1];
                    }
                }
            }
            break;

        case 1:
            if (--temp_r31->unk3E == 0) {
                temp_r31->unk12 = 0;
            }
            CenterM[temp_r31->unk2].z = temp_r31->unk48 + ((temp_r31->unk4C - temp_r31->unk48) * cosd((temp_r31->unk3E * 90.0f) / 30.0f));
            temp_r28 = 0;
            temp_f25 = 1;
            break;

        case 2:
            temp_r25 = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
            temp_r27 = temp_r25[temp_r31->unk2];
            temp_r24 = temp_r27->data;
            switch (temp_r24->unk4) {
                case 1:
                    temp_f28 = 1.0f - (temp_r24->unk24 / 90.0f);
                    object->trans.x = temp_r31->unk50.x + (temp_f28 * (temp_r31->unk5C.x - temp_r31->unk50.x));
                    object->trans.y = 100 + (-2000.0f * (temp_f28 - 0.1f)) * (temp_f28 - 0.1f);
                    object->trans.z = temp_r31->unk50.z + (temp_f28 * (temp_r31->unk5C.z - temp_r31->unk50.z));
                    temp_r28 = 3;
                    temp_r26 = 0;
                    break;

                case 2:
                case 3:
                    if (temp_r24->unk0) {
                        object->trans.x = temp_r27->trans.x;
                        object->trans.y = temp_r27->trans.y - 150;
                        object->trans.z = temp_r27->trans.z;
                        temp_r28 = 4;
                        temp_r26 = 0;
                    }
                    else {
                        if (temp_r31->unk3E) {
                            temp_r31->unk3E--;
                        }
                        temp_f28 = sind((temp_r31->unk3E / 30.0f) * 90.0f);
                        object->trans.x = temp_r31->unk74.x - (temp_f28 * (temp_r31->unk74.x - temp_r31->unk68.x));
                        object->trans.y = temp_r31->unk74.y - (temp_f28 * (temp_r31->unk74.y - temp_r31->unk68.y));
                        object->trans.z = temp_r31->unk74.z - (temp_f28 * (temp_r31->unk74.z - temp_r31->unk68.z));
                        temp_r28 = 0;
                        temp_r26 = 0x40000001;
                    }
                    break;
            }
            if (!temp_r31->unk0_field1) {
                temp_r31->unk0_field2 = 0;
                temp_r31->unk12 = 0;
                temp_r31->unk20.y = 0;
            }
            break;
    }
    if ((temp_r28 >= 0 && temp_r28 != temp_r31->unk2C) || temp_r26 != temp_r31->unk30) {
        temp_r31->unk2C = temp_r28;
        temp_r31->unk30 = temp_r26;
        CharModelMotionShiftSet(temp_r31->unkC, object->motion[temp_r31->unk2C], 0, 8, temp_r26);
    }
    CharModelMotionSpeedSet(temp_r31->unkC, temp_f25);
    temp_r31->unk34 = temp_f25;
    if (temp_r31->unk2 == 0) {
        Hu3DShadowData.unk_20.x = object->trans.x;
        Hu3DShadowData.unk_20.y = object->trans.y;
        Hu3DShadowData.unk_20.z = object->trans.z;
        Hu3DShadowData.unk_14.x = 700 + Hu3DShadowData.unk_20.x;
        Hu3DShadowData.unk_14.y = 2500 + Hu3DShadowData.unk_20.y;
        Hu3DShadowData.unk_14.z = Hu3DShadowData.unk_20.z - 700;
    }
    else {
        lbl_1_bss_D4[temp_r31->unk2 - 1].x = object->trans.x;
        lbl_1_bss_D4[temp_r31->unk2 - 1].y = object->trans.y;
        lbl_1_bss_D4[temp_r31->unk2 - 1].z = object->trans.z;
        lbl_1_bss_F8[temp_r31->unk2 - 1].x = 700 + lbl_1_bss_D4[temp_r31->unk2 - 1].x;
        lbl_1_bss_F8[temp_r31->unk2 - 1].y = 2500 + lbl_1_bss_D4[temp_r31->unk2 - 1].y;
        lbl_1_bss_F8[temp_r31->unk2 - 1].z = lbl_1_bss_D4[temp_r31->unk2 - 1].z - 700;
    }
}

void fn_1_3C1C(omObjData *object)
{
    WorkD0C *temp_r31;
    s32 temp_r29;
    u32 temp_r28;
    float temp_f29;
    temp_r31 = object->data;
    temp_r29 = temp_r31->unk2C;
    temp_f29 = temp_r31->unk34;
    temp_r28 = temp_r31->unk30;
    switch (temp_r31->unk12) {
        case 0:
            if (object->trans.z > -7600.0f) {
                object->trans.z -= 3.75f;
            }
            else {
                temp_r31->unk12++;
            }
            object->rot.y = fn_1_1024(object->rot.y, 180.0f, 0.2f);
            temp_r29 = 1;
            temp_f29 = 1.0f;
            temp_r28 = 0x40000001;
            break;

        case 1:
            if (fn_1_374() >= 9) {
                temp_r29 = (temp_r31->unk0_field8) ? 5 : 6;
                temp_f29 = 1.0f;
                temp_r28 = 0;
            }
            else {
                object->rot.y = fn_1_1024(object->rot.y, 0.0f, 0.2f);
                temp_r29 = 0;
                temp_f29 = 1.0f;
                temp_r28 = 0x40000001;
            }
            break;

        case 2:
            if (--temp_r31->unk3E == 0 || fn_1_374() == 7) {
                temp_r31->unk12 = 1;
            }
            temp_r29 = 0;
            temp_f29 = 1.0f;
            temp_r28 = 0x40000001;
            break;
    }
    if (temp_r31->unk0_field0) {
        CZoomM[temp_r31->unk2] += (lbl_1_data_741C[2].zoom - CZoomM[temp_r31->unk2]) * 0.1f;
        CenterM[temp_r31->unk2].x += (object->trans.x - CenterM[temp_r31->unk2].x) * 0.1f;
        CenterM[temp_r31->unk2].y += ((object->trans.y + 100) - CenterM[temp_r31->unk2].y) * 0.1f;
        CenterM[temp_r31->unk2].z += (object->trans.z - CenterM[temp_r31->unk2].z) * 0.1f;
        CRotM[temp_r31->unk2].x += (lbl_1_data_741C[2].rot.x - CRotM[temp_r31->unk2].x) * 0.1f;
        CRotM[temp_r31->unk2].y += (lbl_1_data_741C[2].rot.y - CRotM[temp_r31->unk2].y) * 0.1f;
        CRotM[temp_r31->unk2].z += (lbl_1_data_741C[2].rot.z - CRotM[temp_r31->unk2].z) * 0.1f;
        Hu3DModelAttrReset(object->model[1], 1);
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + 200, object->trans.z);
    }
    else {
        CZoomM[temp_r31->unk2] += (lbl_1_data_741C[3].zoom - CZoomM[temp_r31->unk2]) * 0.1f;
        CenterM[temp_r31->unk2].x += (object->trans.x - CenterM[temp_r31->unk2].x) * 0.1f;
        CenterM[temp_r31->unk2].y += ((object->trans.y + 100) - CenterM[temp_r31->unk2].y) * 0.1f;
        CenterM[temp_r31->unk2].z += (object->trans.z - CenterM[temp_r31->unk2].z) * 0.1f;
        CRotM[temp_r31->unk2].x += (lbl_1_data_741C[3].rot.x - CRotM[temp_r31->unk2].x) * 0.1f;
        CRotM[temp_r31->unk2].y += (lbl_1_data_741C[3].rot.y - CRotM[temp_r31->unk2].y) * 0.1f;
        CRotM[temp_r31->unk2].z += (lbl_1_data_741C[3].rot.z - CRotM[temp_r31->unk2].z) * 0.1f;
    }
    if ((temp_r29 >= 0 && temp_r29 != temp_r31->unk2C) || temp_r28 != temp_r31->unk30) {
        temp_r31->unk2C = temp_r29;
        temp_r31->unk30 = temp_r28;
        CharModelMotionShiftSet(temp_r31->unkC, object->motion[temp_r31->unk2C], 0, 8, temp_r28);
    }
    CharModelMotionSpeedSet(temp_r31->unkC, temp_f29);
    temp_r31->unk34 = temp_f29;
}

void fn_1_4528(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    HsfanimStruct01 *temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    if (particle->unk_00 == 0) {
        particle->unk_00 = 1;
        temp_r31 = particle->unk_48;
        temp_f29 = atan2d(particle->unk_04.x, particle->unk_04.z);
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r31++, temp_r29++) {
            temp_r31->unk2C = ((20.0f * frand8()) + 50.0f) / 256.0f;
            temp_f31 = (frand8() * 360.0f) / 256.0f;
            temp_r31->unk34.x = 100.0f * (0.2f * sind(temp_f31));
            temp_r31->unk34.y = 0;
            temp_r31->unk34.z = 100.0f * (0.2f * cosd(temp_f31));
            temp_f30 = ((frand8() * 2.5f) / 256.0f) + (5.0f / 3.0f);
            temp_f31 = temp_f29 + (30.0f * (((s32)frand() & 0x1FF) - 256.0f) / 256.0f);
            temp_r31->unk08.x = temp_f30 * sind(temp_f31);
            temp_r31->unk08.z = temp_f30 * cosd(temp_f31);
            temp_r31->unk08.y = (frand8() * (50.0f / 3.0f)) / 256.0f;
            temp_r31->unk40.r = temp_r31->unk40.g = temp_r31->unk40.b = temp_r31->unk40.a = 255;
        }
    }
    temp_r28 = 0;
    temp_r31 = particle->unk_48;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (temp_r31->unk34.y < -2000.0f) {
            temp_r28++;
        }
        else {
            temp_r31->unk08.y += -0.50000006f;
            temp_r31->unk34.x += temp_r31->unk08.x;
            temp_r31->unk34.y += temp_r31->unk08.y;
            temp_r31->unk34.z += temp_r31->unk08.z;
        }
    }
    if (temp_r28 == particle->unk_30) {
        model->attr |= 0x1;
    }
    DCStoreRangeNoSync(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_4978(omObjData *object)
{
    WorkD0C *work = object->data;
    if (object->data != NULL) {
        HuMemDirectFree(object->data);
        object->data = NULL;
    }
}

void fn_1_4AA8(omObjData *object);

void fn_1_49C8(Process *objman)
{
    s32 i;
    lbl_1_bss_140 = 0;
    omMakeGroupEx(objman, 2, 4);
    for (i = 0; i < 4; i++) {
        omAddObjEx(objman, 6, 4, 50, 2, fn_1_4AA8);
    }
}

void fn_1_5B9C(omObjData *object);

void fn_1_4A4C(void)
{
    omObjData **objList = omGetGroupMemberListEx(HuPrcCurrentGet(), 2);
    s32 i;
    for (i = 0; i < 4; i++) {
        fn_1_5B9C(objList[i]);
    }
}

s32 lbl_1_data_7794[1] = { 0x460014 };

void fn_1_4CC0(omObjData *object);
void fn_1_4F54(omObjData *object);

void fn_1_4AA8(omObjData *object)
{
    Work4AA8 *work;
    u32 i;
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work4AA8), MEMORY_DEFAULT_NUM);
    object->data = work;
    memset(work, 0, sizeof(Work4AA8));
    work->unk2 = lbl_1_bss_140;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M439, 0x13));
    Hu3DModelCameraSet(object->model[0], lbl_1_data_75E0[lbl_1_bss_140]);
    Hu3DModelAttrSet(object->model[0], 1);
    for (i = 0; i < 1; i++) {
        object->motion[i] = Hu3DJointMotionFile(object->model[0], lbl_1_data_7794[i]);
    }
    Hu3DMotionSet(object->model[0], object->motion[0]);
    Hu3DModelAttrSet(object->model[0], 0x40000001);
    object->trans.y = 500;
    object->scale.x = object->scale.y = object->scale.z = 0.25f;
    if (work->unk2 == 0) {
        object->trans.x = -1800;
        object->trans.y = 50;
        object->trans.z = -8500;
        object->rot.y = -90;
        object->func = fn_1_4CC0;
        Hu3DMotionSpeedSet(object->model[0], 2.0f);
        work->unk24 = 60;
    }
    else {
        object->func = fn_1_4F54;
    }
    lbl_1_bss_140++;
}

s32 lbl_1_data_7798 = 2;
s32 lbl_1_data_779C = -1;

void fn_1_4CC0(omObjData *object)
{
    Work4AA8 *work = object->data;
    float pan;
    Vec pos2D;
    if (42.0f == work->unk24) {
        HuAudFXPlay(1795);
    }
    if (work->unk24 == 0) {
        object->trans.x -= 25.0f;
    }
    else {
        if (--work->unk24 == 0) {
            lbl_1_data_779C = HuAudFXPlay(1796);
            lbl_1_data_7798--;
        }
    }
    if (lbl_1_data_779C >= 0) {
        if (HuAudFXStatusGet(lbl_1_data_779C) == 0) {
            if (lbl_1_data_7798 > 0) {
                lbl_1_data_779C = HuAudFXPlay(1796);
                lbl_1_data_7798--;
            }
            else {
                lbl_1_data_779C = -1;
            }
        }
        if (lbl_1_data_779C >= 0) {
            Hu3D3Dto2D(&object->trans, 1, &pos2D);
            pan = 64.0f + ((32.0f * pos2D.x) / 576.0f);
            if (pan < 32.0f) {
                pan = 32.0f;
            }
            else if (pan > 96.0f) {
                pan = 96.0f;
            }
            HuAudFXPanning(lbl_1_data_779C, pan);
        }
    }
    Hu3DModelAttrReset(object->model[0], 1);
    if (fn_1_374() == 3) {
        Hu3DMotionSpeedSet(object->model[0], 1.0f);
        Hu3DModelAttrSet(object->model[0], 1);
        object->func = fn_1_4F54;
    }
}

void fn_1_71EC(Vec *arg0, Vec *arg1, float arg2);

void fn_1_4F54(omObjData *object)
{
    Work4AA8 *work = object->data;
    omObjData **temp_r29;
    WorkD0C *temp_r28;
    Vec sp4C;
    Vec sp40;
    switch (work->unk4) {
        case 0:
            if (object->work[3]) {
                work->unk4++;
                work->unk24 = work->unk26 = 90;
                temp_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
                object->trans.x = work->unk28.x = temp_r29[work->unk2]->trans.x;
                object->trans.y = work->unk28.y = 2000;
                object->trans.z = work->unk28.z = temp_r29[work->unk2]->trans.z - 100;
                object->rot.y = 180;
                Hu3DModelAttrReset(object->model[0], 1);
            }
            break;

        case 1:
            temp_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
            work->unk34.x = temp_r29[work->unk2]->trans.x;
            work->unk34.y = 1500;
            work->unk34.z = temp_r29[work->unk2]->trans.z;
            work->unk40.x = temp_r29[work->unk2]->trans.x;
            work->unk40.y = temp_r29[work->unk2]->trans.y;
            work->unk40.z = temp_r29[work->unk2]->trans.z;
            fn_1_71EC(&work->unk28, &sp40, 1.0f - ((float)work->unk24 / (float)work->unk26));
            VECSubtract(&sp40, &object->trans, &sp4C);
            object->rot.x = fn_1_1024(object->rot.x, atan2d(-sp4C.y, VECMagXZ(&sp4C)), 0.2f);
            object->rot.y = fn_1_1024(object->rot.y, atan2d(sp4C.x, sp4C.z), 0.2f);
            object->trans.x = sp40.x;
            object->trans.y = sp40.y;
            object->trans.z = sp40.z;
            if (--work->unk24 == 0) {
                work->unk0 = 1;
                work->unk4++;
                work->unk24 = 90;
                work->unk10 = (200.0f - object->trans.y) / work->unk24;
                object->rot.x = 0;
            }
            if (60.0f == work->unk24) {
                HuAudFXPlay(1796);
            }
            break;

        case 2:
            object->trans.y += work->unk10;
            if (--work->unk24 == 0) {
                work->unk4++;
                work->unk24 = work->unk26 = 48;
                work->unk28.x = object->trans.x;
                work->unk28.y = object->trans.y;
                work->unk28.z = object->trans.z;
                temp_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
                temp_r28 = temp_r29[work->unk2]->data;
                work->unk34.x = temp_r28->unk50.x;
                work->unk34.y = 250;
                work->unk34.z = temp_r28->unk50.z;
                temp_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
                temp_r28 = temp_r29[work->unk2]->data;
                temp_r28->unk0_field3 = 1;
                VECSubtract(&work->unk34, &work->unk28, &sp4C);
                VECNormalize(&sp4C, &sp4C);
                VECScale(&sp4C, &work->unk40, 2000.0f);
                work->unk40.y = 300;
                VECAdd(&work->unk28, &work->unk40, &work->unk40);
            }
            break;

        case 3:
            fn_1_71EC(&work->unk28, &sp40, 1.0f - ((float)work->unk24 / (float)work->unk26));
            VECSubtract(&sp40, &object->trans, &sp4C);
            object->rot.x = fn_1_1024(object->rot.x, atan2d(-sp4C.y, VECMagXZ(&sp4C)), 0.2f);
            object->rot.y = fn_1_1024(object->rot.y, atan2d(sp4C.x, sp4C.z), 0.2f);
            object->trans.x = sp40.x;
            object->trans.y = sp40.y;
            object->trans.z = sp40.z;
            if (--work->unk24 == 0) {
                temp_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
                temp_r28 = temp_r29[work->unk2]->data;
                temp_r28->unk0_field1 = 0;
                work->unk4 = 0;
                object->work[3] = 0;
                Hu3DModelAttrSet(object->model[0], 1);
            }
            if (work->unk24 == (int)(work->unk26 - 12.0f)) {
                work->unk0 = 0;
                temp_r29 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
                temp_r28 = temp_r29[work->unk2]->data;
                temp_r28->unk68.x = object->trans.x;
                temp_r28->unk68.y = object->trans.y;
                temp_r28->unk68.z = object->trans.z;
            }
            break;
    }
}

void fn_1_5B9C(omObjData *object) { }

s32 lbl_1_data_77A0[10] = { 0x00460000, 0x00460001, 0x00460002, 0x00460003, 0x00460004, 0x00460005, 0x00460006, 0x00460007, 0x00460008, 0x00460009 };

void fn_1_5CB0(omObjData *object);
void fn_1_6520(omObjData *object);

void fn_1_5BA0(Process *objman)
{
    s32 i;
    lbl_1_bss_144 = 0;
    omMakeGroupEx(objman, 1, 4);
    for (i = 0; i < 4; i++) {
        omAddObjEx(objman, 10, 28, 0, 1, fn_1_5CB0);
    }
    for (i = 0; i < 10; i++) {
        lbl_1_bss_10[i] = Hu3DModelCreateFile(lbl_1_data_77A0[i]);
        Hu3DModelAttrSet(lbl_1_bss_10[i], 1);
    }
    omAddObjEx(objman, 10, 4, 0, 1, fn_1_6520);
}

void fn_1_5CAC(void) { }

float lbl_1_data_77C8[][2] = { 0, 0, 0, -700, -1400, -2200, 1400, -2200, -1400, -3600, 1400, -3600, -2800, -5200, 0, -5200, 0, -5200, 2800, -5200,
    -2800, -6600, 0, -6600, 0, -6600, 2800, -6600 };

s16 lbl_1_data_7838[] = { 0, 1, -1, -1, 2, 2, -1, -1, -1, -1, 3, 3, 3, 3 };

void fn_1_6068(omObjData *object);

void fn_1_5CB0(omObjData *object)
{
    u16 sp8[6] = { 4, 7, 5, 8, 6, 9 };
    char *sp14[10][2] = { "road0", NULL, "road1", "bridge1", "road2", "bridge2", "road3", NULL, "road4", NULL, "road5", NULL, "road6", NULL, "road7",
        NULL, "road8", NULL, "road9", NULL };
    Work5CB0 *work;
    s32 i;
    s32 temp;
    s32 temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    s32 temp_r24;
    omSetStatBit(object, 0x100);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work5CB0) * 14, MEMORY_DEFAULT_NUM);
    object->data = work;
    memset(work, 0, sizeof(Work5CB0) * 14);
    for (i = 0; i < 100; i++) {
        temp_r27 = ((frand8() * 3) >> 8) * 2;
        temp_r25 = ((frand8() * 3) >> 8) * 2;
        temp = sp8[temp_r27];
        sp8[temp_r27] = sp8[temp_r25];
        sp8[temp_r25] = temp;
        temp_r27 = (((frand8() * 3) >> 8) * 2) + 1;
        temp_r25 = (((frand8() * 3) >> 8) * 2) + 1;
        temp = sp8[temp_r27];
        sp8[temp_r27] = sp8[temp_r25];
        sp8[temp_r25] = temp;
    }
    for (i = 0; i < 100; i++) {
        temp_r27 = ((frand8() * 3) >> 8) * 2;
        temp = sp8[temp_r27 + 1];
        sp8[temp_r27 + 1] = sp8[temp_r27];
        sp8[temp_r27] = temp;
    }
    temp_r24 = 0;
    for (i = 0; i < 14; i++, work++) {
        temp_r26 = lbl_1_data_7838[i];
        if (temp_r26 < 0) {
            temp_r26 = sp8[temp_r24++];
        }
        object->model[i] = Hu3DModelLink(lbl_1_bss_10[temp_r26]);
        Hu3DModelPosSet(object->model[i], lbl_1_data_77C8[i][0], 0, lbl_1_data_77C8[i][1]);
        Hu3DModelAttrReset(object->model[i], 1);
        for (temp = 0; temp < 2; temp++) {
            if (sp14[temp_r26][temp]) {
                Hu3DModelShadowMapObjSet(object->model[i], sp14[temp_r26][temp]);
            }
        }
        work->unk0 = temp_r26;
        work->unk4.x = lbl_1_data_77C8[i][0];
        work->unk4.y = 0;
        work->unk4.z = lbl_1_data_77C8[i][1];
        memcpy(&work->unk10, &lbl_1_data_748C[i], sizeof(StructData748C));
    }
    object->work[0] = lbl_1_bss_144;
    lbl_1_bss_144++;
    object->func = fn_1_6068;
}

void fn_1_6120(omObjData *object);

void fn_1_6068(omObjData *object)
{
    s32 i;
    for (i = 0; i < 14; i++) {
        if (object->work[0] == 0 && i == 10) {
            Hu3DModelCameraSet(object->model[i], lbl_1_data_75E0[0]);
        }
        else {
            Hu3DModelCameraSet(object->model[i], 0);
        }
    }
    if (fn_1_374() == 3) {
        object->func = fn_1_6120;
    }
}

void fn_1_6120(omObjData *object)
{
    s32 i;
    WorkD0C *temp_r29;
    omObjData **temp_r28;
    Work5CB0 *work = object->data;
    s16 sp8[14];
    for (i = 0; i < 14; i++) {
        sp8[i] = 0;
    }
    temp_r28 = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    temp_r29 = temp_r28[object->work[0]]->data;
    lbl_1_bss_C = &work[temp_r29->unk44].unk10;
    sp8[temp_r29->unk44] |= lbl_1_data_75E0[object->work[0]];
    if (lbl_1_bss_C->unk4 >= 0) {
        sp8[lbl_1_bss_C->unk4] |= lbl_1_data_75E0[object->work[0]];
    }
    for (i = 0; i < lbl_1_bss_C->unk8; i++) {
        sp8[lbl_1_bss_C->unkC[i]] |= lbl_1_data_75E0[object->work[0]];
    }
    for (i = 0; i < 14; i++) {
        Hu3DModelCameraSet(object->model[i], sp8[i]);
    }
}

s32 fn_1_62E0(float arg0)
{
    s32 i;
    for (i = 0; i < 5; i++) {
        if (arg0 > lbl_1_data_75CC[i]) {
            break;
        }
    }
    return i;
}

s32 fn_1_6328(omObjData *object)
{
    WorkD0C *work = object->data;
    omObjData **temp_r28 = omGetGroupMemberListEx(HuPrcCurrentGet(), 1);
    Work5CB0 *temp_r29 = temp_r28[work->unk2]->data;
    s32 i;
    ModelData *temp_r26;
    s32 temp_r25;
    float temp_f31;
    float temp_f30;
    lbl_1_bss_8 = &temp_r29[work->unk44].unk10;
    if (lbl_1_bss_8->unk8 > 0 && work->unk46 == temp_r29[lbl_1_bss_8->unkC[0]].unk10.unk0) {
        temp_r25 = -1;
        temp_f30 = 9999;
        for (i = 0; i < lbl_1_bss_8->unk8; i++) {
            temp_r26 = &Hu3DData[temp_r28[work->unk2]->model[lbl_1_bss_8->unkC[i]]];
            temp_f31 = fabs(object->trans.x - temp_r26->pos.x);
            if (temp_f31 < temp_f30) {
                temp_f30 = temp_f31;
                temp_r25 = lbl_1_bss_8->unkC[i];
            }
        }
        (void)i;
        return temp_r25;
    }
    else {
        if (work->unk46 == temp_r29[lbl_1_bss_8->unk4].unk10.unk0) {
            return lbl_1_bss_8->unk4;
        }
        else {
            return -1;
        }
    }
}

s32 lbl_1_data_78A0[8] = { 0x0046000A, 0x0046000B, 0x0046000C, 0x0046000D, 0x0046000E, 0x0046000F, 0x00460010, 0x00460011 };

Vec lbl_1_data_78C0[4] = { { -2800, 0, -7700 }, { 0, 0, -7700 }, { 0, 0, -7700 }, { 2800, 0, -7700 } };

void fn_1_661C(omObjData *object);

void fn_1_6520(omObjData *object)
{
    s32 i;
    omSetStatBit(object, 0x100);
    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = Hu3DModelCreateFile(lbl_1_data_78A0[GWPlayerCfg[i].character]);
        Hu3DModelCameraSet(object->model[i], lbl_1_data_75E0[i]);
        Hu3DModelClusterAttrSet(object->model[i], 0, 0xC0000001);
        Hu3DModelAttrSet(object->model[i], 1);
    }
    object->func = fn_1_661C;
}

void fn_1_66BC(omObjData *object);

void fn_1_661C(omObjData *object)
{
    Hu3DModelAttrReset(object->model[0], 1);
    Hu3DModelPosSet(object->model[0], -2800, 0, -7700);
    if (fn_1_374() == 3) {
        Hu3DModelAttrSet(object->model[0], 1);
        object->func = fn_1_66BC;
    }
}

void fn_1_66BC(omObjData *object)
{
    omObjData **objList = omGetGroupMemberListEx(HuPrcCurrentGet(), 0);
    s32 i;
    for (i = 0; i < 4; i++) {
        WorkD0C *work = objList[i]->data;
        if (work->unk44 >= 10 && work->unk44 <= 13) {
            s32 goalNo = work->unk44 - 10;
            Hu3DModelPosSet(object->model[i], lbl_1_data_78C0[goalNo].x, lbl_1_data_78C0[goalNo].y, lbl_1_data_78C0[goalNo].z);
            Hu3DModelAttrReset(object->model[i], 1);
        }
        else {
            Hu3DModelAttrSet(object->model[i], 1);
        }
    }
}

s32 fn_1_67B4(Vec *arg0, s32 arg1, s32 arg2, Vec *arg3, Vec *arg4)
{
    omObjData **temp_r21 = omGetGroupMemberListEx(HuPrcCurrentGet(), 1);
    Work5CB0 *temp_r28 = temp_r21[arg1]->data;
    s32 i;
    s32 temp_r25;

    Vec sp34;
    VECSubtract(arg0, &temp_r28[arg2].unk4, &sp34);
    temp_r25 = temp_r28[arg2].unk0;
    for (i = 0; i < lbl_1_data_73B8[temp_r25]; i++) {
        Vec *temp_r29 = (lbl_1_data_73CC[temp_r25])[i * 3];
        Vec *temp_r31 = *((&lbl_1_data_73CC[temp_r25][i * 3]) + 1);
        Vec *temp_r30 = *((&lbl_1_data_73CC[temp_r25][i * 3]) + 2);
        s32 j;
        for (j = 0; j < lbl_1_data_73F4[temp_r25][i] - 1; j++, temp_r29++, temp_r31++, temp_r30++) {
            Vec sp28;
            Vec sp1C;
            Vec sp10;
            float temp_f31;
            float temp_f30;
            VECSubtract(&temp_r29[1], &temp_r29[0], &sp28);
            VECSubtract(&sp34, &temp_r29[1], &sp1C);
            VECCrossProduct(&sp28, &sp1C, &sp10);
            if (sp10.y < 0.0f) {
                continue;
            }
            VECSubtract(&temp_r31[1], &temp_r29[1], &sp28);
            VECSubtract(&sp34, &temp_r31[1], &sp1C);
            VECCrossProduct(&sp28, &sp1C, &sp10);
            if (sp10.y < 0.0f) {
                continue;
            }
            VECSubtract(&temp_r31[0], &temp_r31[1], &sp28);
            VECSubtract(&sp34, &temp_r31[0], &sp1C);
            VECCrossProduct(&sp28, &sp1C, &sp10);
            if (sp10.y < 0.0f) {
                continue;
            }
            VECSubtract(&temp_r29[0], &temp_r31[0], &sp28);
            VECSubtract(&sp34, &temp_r29[0], &sp1C);
            VECCrossProduct(&sp28, &sp1C, &sp10);
            if (sp10.y < 0.0f) {
                continue;
            }
            VECSubtract(&temp_r29[1], &temp_r29[0], &sp28);
            temp_f30 = VECMag2Point(&sp28);
            if (0.0f == temp_f30) {
                continue;
            }
            temp_f31 = ((sp34.x * sp28.x) - (temp_r29->x * sp28.x) + (sp34.y * sp28.y) - (temp_r29->y * sp28.y) + (sp34.z * sp28.z)
                           - (temp_r29->z * sp28.z))
                / temp_f30;
            arg3->x = (temp_r31[0].x + temp_r28[arg2].unk4.x) + (temp_f31 * (temp_r31[1].x - temp_r31[0].x));
            arg3->y = (temp_r31[0].y + temp_r28[arg2].unk4.y) + (temp_f31 * (temp_r31[1].y - temp_r31[0].y));
            arg3->z = (temp_r31[0].z + temp_r28[arg2].unk4.z) + (temp_f31 * (temp_r31[1].z - temp_r31[0].z));
            arg4->x = (temp_r30[0].x + temp_r28[arg2].unk4.x) + (temp_f31 * (temp_r30[1].x - temp_r30[0].x));
            arg4->y = (temp_r30[0].y + temp_r28[arg2].unk4.y) + (temp_f31 * (temp_r30[1].y - temp_r30[0].y));
            arg4->z = (temp_r30[0].z + temp_r28[arg2].unk4.z) + (temp_f31 * (temp_r30[1].z - temp_r30[0].z));
            return 1;
        }
    }
    return 0;
}

void fn_1_6CD0(s32 arg0, s32 arg1);
void fn_1_6DEC(omObjData *object);

void fn_1_6C08(omObjData *object)
{
    fn_1_6CD0(0, 0);
    object->work[3] = espEntry(0x460015, 32768, 0);
    espPosSet(object->work[3], 288, 240);
    espDispOff(object->work[3]);
    espScaleSet(object->work[3], 2.0f, 2.0f);
    espColorSet(object->work[3], 0, 0, 0);
    object->func = fn_1_6DEC;
}

void fn_1_6CD0(s32 arg0, s32 arg1)
{
    CZoomM[arg0] = lbl_1_data_741C[arg1].zoom;
    CenterM[arg0].x = lbl_1_data_741C[arg1].pos.x;
    CenterM[arg0].y = lbl_1_data_741C[arg1].pos.y;
    CenterM[arg0].z = lbl_1_data_741C[arg1].pos.z;
    CRotM[arg0].x = lbl_1_data_741C[arg1].rot.x;
    CRotM[arg0].y = lbl_1_data_741C[arg1].rot.y;
    CRotM[arg0].z = lbl_1_data_741C[arg1].rot.z;
}

void fn_1_6DEC(omObjData *object)
{
    CameraData *camera = &Hu3DCamera[0];
    s32 i;
    switch (object->work[0]) {
        case 0:
            if (fn_1_374() <= 3) {
                CRotM[0].y -= 10.0f / 60.0f;
            }
            if (fn_1_374() == 3) {
                Hu3DCameraCreate(15);
                Hu3DCameraPerspectiveSet(15, 10, 20, 25000, 1.2);
                Hu3DCameraViewportSet(1, 0, 0, 320, 240, 0, 1);
                Hu3DCameraViewportSet(2, 320, 0, 320, 240, 0, 1);
                Hu3DCameraViewportSet(4, 0, 240, 320, 240, 0, 1);
                Hu3DCameraViewportSet(8, 320, 240, 320, 240, 0, 1);
                Hu3DCameraScissorSet(1, 0, 0, 320, 240);
                Hu3DCameraScissorSet(2, 320, 0, 640, 240);
                Hu3DCameraScissorSet(4, 0, 240, 320, 480);
                Hu3DCameraScissorSet(8, 320, 240, 640, 480);
                for (i = 0; i < 4; i++) {
                    fn_1_6CD0(i, 1);
                }
                lbl_1_bss_168->work[0] = 4;
                object->work[0]++;
                espDispOn(object->work[3]);
            }
            break;
    }
}

float fn_1_7190(float arg0, float arg1, float arg2, float arg3)
{
    float temp_f31 = 1.0f - arg3;
    return (arg0 * (temp_f31 * temp_f31)) + ((2.0f * temp_f31) * arg3 * arg1) + (arg2 * (arg3 * arg3));
}

void fn_1_71EC(Vec *arg0, Vec *arg1, float arg2)
{
    arg1->x = fn_1_7190(arg0[0].x, arg0[1].x, arg0[2].x, arg2);
    arg1->y = fn_1_7190(arg0[0].y, arg0[1].y, arg0[2].y, arg2);
    arg1->z = fn_1_7190(arg0[0].z, arg0[1].z, arg0[2].z, arg2);
}

void fn_1_7578(s16 layer);

void fn_1_73F4(Process *objman)
{
    s32 i;
    s32 dataSize = Hu3DShadowData.unk_02 * Hu3DShadowData.unk_02;
    lbl_1_bss_128 = objman;
    for (i = 0; i < 3; i++) {
        lbl_1_bss_11C[i] = HuMemDirectMallocNum(HEAP_SYSTEM, dataSize, MEMORY_DEFAULT_NUM);
        memset(lbl_1_bss_11C[i], 0, dataSize);
        lbl_1_bss_D4[i].x = Hu3DShadowData.unk_20.x;
        lbl_1_bss_D4[i].y = Hu3DShadowData.unk_20.y;
        lbl_1_bss_D4[i].z = Hu3DShadowData.unk_20.z;
        lbl_1_bss_F8[i].x = Hu3DShadowData.unk_14.x;
        lbl_1_bss_F8[i].y = Hu3DShadowData.unk_14.y;
        lbl_1_bss_F8[i].z = Hu3DShadowData.unk_14.z;
    }
    Hu3DLayerHookSet(0, fn_1_7578);
}

void fn_1_77E4(s32 shadowNo);

void fn_1_7578(s16 layer)
{
    omObjData **playerList;
    s32 i;
    s32 dataSize = Hu3DShadowData.unk_02 * Hu3DShadowData.unk_02;
    if (fn_1_374() < 3) {
        return;
    }
    if (Hu3DCameraNo == 0) {
        WorkD0C *playerWork;
        GXDrawDone();
        playerList = omGetGroupMemberListEx(lbl_1_bss_128, 0);
        if (Hu3DData[playerList[0]->model[0]].attr & 0x4) {
            Hu3DModelShadowReset(playerList[0]->model[0]);
        }
        for (i = 0; i < 3; i++) {
            playerWork = playerList[i + 1]->data;
            if (playerWork->unk0_field3) {
                Hu3DModelShadowSet(playerList[i + 1]->model[0]);
            }
            fn_1_77E4(i);
            GXDrawDone();
            DCFlushRangeNoSync(lbl_1_bss_11C[i], dataSize);
            if (playerWork->unk0_field3) {
                Hu3DModelShadowReset(playerList[i + 1]->model[0]);
            }
        }
        playerWork = playerList[0]->data;
        if (playerWork->unk0_field3) {
            Hu3DModelShadowSet(playerList[0]->model[0]);
        }
        else {
            memset(Hu3DShadowData.unk_04, 0, dataSize);
            DCFlushRangeNoSync(Hu3DShadowData.unk_04, dataSize);
        }
        if (Hu3DShadowCamBit < 1) {
            Hu3DShadowCamBit = 1;
        }
    }
    else {
        MTXCopy(lbl_1_bss_44[Hu3DCameraNo - 1], Hu3DShadowData.unk_38);
        memcpy(Hu3DShadowData.unk_04, lbl_1_bss_11C[Hu3DCameraNo - 1], dataSize);
        DCFlushRangeNoSync(Hu3DShadowData.unk_04, dataSize);
    }
}

void fn_1_77E4(s32 shadowNo)
{
    ModelData *model;
    s32 dataSize;
    s16 i;
    Mtx transform[3];
    Mtx44 proj;
    GXColor clearColor = { 0, 0, 0, 0 };

    Hu3DDrawPreInit();
    GXSetCopyClear(clearColor, 0xFFFFFF);
    MTXPerspective(proj, Hu3DShadowData.unk_08.x, 1.2f, Hu3DShadowData.unk_08.y, Hu3DShadowData.unk_08.z);
    GXSetProjection(proj, GX_PERSPECTIVE);
    if (Hu3DShadowData.unk_02 <= 240) {
        GXSetScissor(2, 2, (Hu3DShadowData.unk_02 * 2) - 4, (Hu3DShadowData.unk_02 * 2) - 4);
        GXSetViewport(0, 0, Hu3DShadowData.unk_02 * 2, Hu3DShadowData.unk_02 * 2, 0, 1);
        dataSize = (Hu3DShadowData.unk_02 / 2) * (Hu3DShadowData.unk_02 / 2);
    }
    else {
        GXSetScissor(1, 1, Hu3DShadowData.unk_02 - 2, Hu3DShadowData.unk_02 - 2);
        GXSetViewport(0, 0, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, 0, 1);
        dataSize = Hu3DShadowData.unk_02 * Hu3DShadowData.unk_02;
    }
    MTXLookAt(Hu3DCameraMtx, &lbl_1_bss_F8[shadowNo], &Hu3DShadowData.unk_2C, &lbl_1_bss_D4[shadowNo]);
    MTXCopy(Hu3DCameraMtx, lbl_1_bss_44[shadowNo]);
    model = &Hu3DData[0];
    shadowModelDrawF = 1;
    GXInvalidateTexAll();
    GXSetFog(0, 0, 0, 0, 0, BGColor);
    for (i = 0; i < 512; i++, model++) {
        s32 clusterF;
        if (model->hsfData && (model->attr & 0x4) && (model->attr & 0x1) == 0 && (model->attr & 0x8000) == 0) {
            if (model->attr & 0x8) {
                clusterF = 0;
                if (model->unk_08 != -1) {
                    Hu3DMotionExec(i, model->unk_08, model->unk_64, 0);
                }
                if (model->unk_0C != -1) {
                    Hu3DSubMotionExec(i);
                }
                if (model->unk_0A != -1) {
                    Hu3DMotionExec(i, model->unk_0A, model->unk_74, 1);
                }
                if (model->attr & 0x400) {
                    ClusterMotionExec(model);
                    clusterF = 1;
                }
                if (model->unk_0E != -1) {
                    if (model->unk_08 == -1) {
                        Hu3DMotionExec(i, model->unk_0E, model->unk_94, 0);
                    }
                    else {
                        Hu3DMotionExec(i, model->unk_0E, model->unk_94, 1);
                    }
                }
                if ((model->attr & 0x90) == 0 || (model->motion_attr & 0x40000002) == 0) {
                    clusterF = 1;
                    InitVtxParm(model->hsfData);
                    if (model->unk_0E != -1) {
                        ShapeProc(model->hsfData);
                    }
                    if (model->attr & 0x400) {
                        ClusterProc(model);
                    }
                    if (model->hsfData->cenvCnt) {
                        EnvelopeProc(model->hsfData);
                    }
                    PPCSync();
                }
                model->attr |= 0x800;
            }
            mtxRot(transform[0], model->rot.x, model->rot.y, model->rot.z);
            MTXScale(transform[2], model->scale.x, model->scale.y, model->scale.z);
            MTXConcat(transform[0], transform[2], transform[2]);
            mtxTransCat(transform[2], model->pos.x, model->pos.y, model->pos.z);
            MTXConcat(Hu3DCameraMtx, transform[2], transform[1]);
            MTXConcat(transform[1], model->unk_F0, transform[1]);
            Hu3DDraw(model, transform[1], &model->scale);
        }
    }
    Hu3DDrawPost();
    shadowModelDrawF = 0;
    if (Hu3DShadowData.unk_02 <= 240) {
        GXSetTexCopySrc(0, 0, Hu3DShadowData.unk_02 * 2, Hu3DShadowData.unk_02 * 2);
        GXSetTexCopyDst(Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, GX_CTF_R8, GX_TRUE);
    }
    else {
        GXSetTexCopySrc(0, 0, Hu3DShadowData.unk_02, Hu3DShadowData.unk_02);
        GXSetTexCopyDst(Hu3DShadowData.unk_02, Hu3DShadowData.unk_02, GX_CTF_R8, GX_FALSE);
    }
    GXCopyTex(lbl_1_bss_11C[shadowNo], GX_TRUE);
    GXSetViewport(0, 0, RenderMode->fbWidth, RenderMode->xfbHeight, 0, 1);
    GXSetScissor(0, 0, RenderMode->fbWidth, RenderMode->efbHeight);
    MTXOrtho(proj, 0, 1, 0, 1, 0, 1);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_U8, 0);
    GXSetTevColor(GX_TEVREG0, BGColor);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(0);
    MTXIdentity(transform[1]);
    GXLoadPosMtxImm(transform[1], GX_PNMTX0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_TRUE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3u8(0, 0, 0);
    GXPosition3u8(1, 0, 0);
    GXPosition3u8(1, 1, 0);
    GXPosition3u8(0, 1, 0);
}
