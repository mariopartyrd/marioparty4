#include "game/audio.h"
#include "game/frand.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "ext_math.h"
#include "math.h"

#include "game/gamework.h"
#include "game/objsub.h"

#include "game/gamework_data.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#endif

typedef struct bss_348_data {
    s16 unk0[5];
    s16 unkA;
    s16 unkC[20];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    float unk48[9];
    HsfObject *unk6C[40];
    HsfObject *unk10C[40];
    HsfObject *unk1AC[40];
    HsfTransform unk24C[40];
    u32 unk7EC[2];
    s8 unk7F4;
    s8 unk7F5;
    s8 unk7F6;
    s8 unk7F7;
    u16 unk7F8;
    s16 unk7FA[5];
    s32 unk804;
    s32 unk808;
} Bss348Data;

typedef struct camera_view_params {
    Vec rot;
    Vec pos;
    float zoom;
} CameraViewParams;

s16 lbl_1_bss_CB4;
s16 lbl_1_bss_CB0[2];
s16 lbl_1_bss_CAE;
s16 lbl_1_bss_CAC;
s32 lbl_1_bss_CA8;
s32 lbl_1_bss_CA4;
s32 lbl_1_bss_C04[40];
s32 lbl_1_bss_B64[40];
s32 lbl_1_bss_B60;
s32 lbl_1_bss_B5C;
s32 lbl_1_bss_B58;
s32 lbl_1_bss_B54;
Bss348Data lbl_1_bss_348[1];
s32 lbl_1_bss_C[207];
omObjData *lbl_1_bss_8;
Process *lbl_1_bss_4[1];
s32 lbl_1_bss_0;

CameraViewParams lbl_1_data_0[3]
    = { { { -64, 0, 0 }, { 0, 0, 0 }, 5000 }, { { -9.5, 0, 0 }, { 0, 0, -510 }, 1860 }, { { -5, 0, 0 }, { 0, 0, -2870 }, 5060 } };

s32 lbl_1_data_54[3] = { DATA_MAKE_NUM(DATADIR_M451, 0x01), DATA_MAKE_NUM(DATADIR_M451, 0x02), DATA_MAKE_NUM(DATADIR_M451, 0x03) };

s32 lbl_1_data_60[3] = { DATA_MAKE_NUM(DATADIR_M451, 0x05), DATA_MAKE_NUM(DATADIR_M451, 0x06), DATA_MAKE_NUM(DATADIR_M451, 0x07) };

char *lbl_1_data_78[3] = { "puzzle00", "puzzle00", "puzzle00" };

char *lbl_1_data_464[3][40] = {
    {
        "puzzle2001",
        "puzzle2002",
        "puzzle2003",
        "puzzle2004",
        "puzzle2005",
        "puzzle2006",
        "puzzle2007",
        "puzzle2008",
        "puzzle2009",
        "puzzle2010",
        "puzzle2011",
        "puzzle2012",
        "puzzle2013",
        "puzzle2014",
        "puzzle2015",
        "puzzle2016",
        "puzzle2017",
        "puzzle2018",
        "puzzle2019",
        "puzzle2020",
    },
    {
        "puzzle3001",
        "puzzle3002",
        "puzzle3003",
        "puzzle3004",
        "puzzle3005",
        "puzzle3006",
        "puzzle3007",
        "puzzle3008",
        "puzzle3009",
        "puzzle3010",
        "puzzle3011",
        "puzzle3012",
        "puzzle3013",
        "puzzle3014",
        "puzzle3015",
        "puzzle3016",
        "puzzle3017",
        "puzzle3018",
        "puzzle3019",
        "puzzle3020",
        "puzzle3021",
        "puzzle3022",
        "puzzle3023",
        "puzzle3024",
        "puzzle3025",
        "puzzle3026",
        "puzzle3027",
        "puzzle3028",
        "puzzle3029",
        "puzzle3030",
    },
    {
        "puzzle4001",
        "puzzle4002",
        "puzzle4003",
        "puzzle4004",
        "puzzle4005",
        "puzzle4006",
        "puzzle4007",
        "puzzle4008",
        "puzzle4009",
        "puzzle4010",
        "puzzle4011",
        "puzzle4012",
        "puzzle4013",
        "puzzle4014",
        "puzzle4015",
        "puzzle4016",
        "puzzle4017",
        "puzzle4018",
        "puzzle4019",
        "puzzle4020",
        "puzzle4021",
        "puzzle4022",
        "puzzle4023",
        "puzzle4024",
        "puzzle4025",
        "puzzle4026",
        "puzzle4027",
        "puzzle4028",
        "puzzle4029",
        "puzzle4030",
        "puzzle4031",
        "puzzle4032",
        "puzzle4033",
        "puzzle4034",
        "puzzle4035",
        "puzzle4036",
        "puzzle4037",
        "puzzle4038",
        "puzzle4039",
        "puzzle4040",
    },
};

s32 lbl_1_data_644[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    DATA_MAKE_NUM(DATADIR_MARIOMDL1, 0x00),
    DATA_MAKE_NUM(DATADIR_LUIGIMDL1, 0x00),
    DATA_MAKE_NUM(DATADIR_PEACHMDL1, 0x00),
    DATA_MAKE_NUM(DATADIR_YOSHIMDL1, 0x00),
    DATA_MAKE_NUM(DATADIR_WARIOMDL1, 0x00),
    DATA_MAKE_NUM(DATADIR_DONKEYMDL1, 0x00),
    DATA_MAKE_NUM(DATADIR_DAISYMDL1, 0x00),
    DATA_MAKE_NUM(DATADIR_WALUIGIMDL1, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x01),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x06),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1B),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x20),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x21),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
};

s32 lbl_1_data_6C8[] = { 6, 7, 8 };

float lbl_1_data_6D4[][2] = { -52, -9, 53, -8, 35, -8, 23, -8, 9, -8, -9, -8, -17, -8, -31, -8, 53, 8, 35, 8, 23, 8, 9, 8, -9, 8, -17, 8, -31, 8 };

s32 lbl_1_data_74C[] = { 3600, 7200, 10800 };

s32 lbl_1_data_758[] = { 58, 54, 48 };

void fn_1_7BC(void);
void fn_1_B2C(void);
void fn_1_48C4(void);

void ObjectSetup(void)
{
    Vec pos;
    Vec up;
    Vec target;
    s32 i;
    Process *objman;
    s32 type;
    type = GWSystem.mg_type;
    lbl_1_bss_B60 = type;
    if (type == -1) {
        lbl_1_bss_B60 = frandmod(3);
    }
    lbl_1_bss_B5C = lbl_1_bss_B60;
    switch (lbl_1_bss_B5C) {
        case 0:
            lbl_1_bss_B58 = 20;
            break;

        case 1:
            lbl_1_bss_B58 = 30;
            break;

        default:
            lbl_1_bss_B58 = 40;
            break;
    }
    objman = omInitObjMan(50, 8192);
    omGameSysInit(objman);
    Hu3DCameraCreate(3);
    Hu3DCameraPerspectiveSet(1, 15, 20, 25000, 1.2);
    Hu3DCameraPerspectiveSet(2, 15, 20, 25000, 1.2);
    Hu3DCameraViewportSet(1, 0, 0, 320, 240, 0, 1);
    Hu3DCameraViewportSet(2, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(1, 0, 0, 320, 240);
    Hu3DCameraScissorSet(2, 0, 0, 640, 480);
    lbl_1_bss_8 = omAddObjEx(objman, 32730, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_8->work[0] = 2;
    for (i = 0; i < 1; i++) {
        CRotM[i].x = lbl_1_data_0[lbl_1_bss_B60].rot.x;
        CRotM[i].y = lbl_1_data_0[lbl_1_bss_B60].rot.y;
        CRotM[i].z = lbl_1_data_0[lbl_1_bss_B60].rot.z;
        CenterM[i].x = lbl_1_data_0[lbl_1_bss_B60].pos.x;
        CenterM[i].y = lbl_1_data_0[lbl_1_bss_B60].pos.y;
        CenterM[i].z = lbl_1_data_0[lbl_1_bss_B60].pos.z;
        CZoomM[i] = lbl_1_data_0[lbl_1_bss_B60].zoom;
    }
    for (i = 1; i < lbl_1_bss_8->work[0]; i++) {
        CRotM[i].x = 0;
        CRotM[i].y = 0;
        CRotM[i].z = 0;
        CenterM[i].x = 0;
        CenterM[i].y = 10;
        CenterM[i].z = 0;
        CZoomM[i] = 1900;
    }
    Hu3DLighInit();
    lbl_1_bss_CB4 = Hu3DGLightCreate(10000, 0, 10000, -1, 0, -1, 255, 255, 255);
    Hu3DGLightPosAimSet(lbl_1_bss_CB4, 0, 6796.88f, 9706.95f, 0, 0, 0);
    Hu3DGLightInfinitytSet(lbl_1_bss_CB4);
    pos.x = -1800;
    pos.y = 3600;
    pos.z = 0;
    up.x = up.z = 0;
    up.y = 1;
    target.x = -100;
    target.y = 0;
    target.z = 0;
    Hu3DShadowCreate(30, 20, 10000);
    Hu3DShadowTPLvlSet(0.4f);
    Hu3DShadowPosSet(&pos, &up, &target);
    Hu3DBGColorSet(0, 0, 0);
    fn_1_B2C();
    HuPrcSetStat(HuPrcChildCreate(fn_1_7BC, 4096, 4096, 0, HuPrcCurrentGet()), 12);
    HuPrcChildCreate(fn_1_48C4, 4096, 8192, 0, HuPrcCurrentGet());
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
}

void fn_1_7BC(void)
{
    Bss348Data *data = &lbl_1_bss_348[0];
    while (1) {
        if (omPauseChk()) {
            Hu3DModelAttrSet(data->unk0[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(data->unk0[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(data->unk0[2], HU3D_ATTR_DISPOFF);
            HuSprAttrSet(data->unkA, 0, HUSPR_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(data->unk0[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(data->unk0[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(data->unk0[2], HU3D_ATTR_DISPOFF);
            HuSprAttrReset(data->unkA, 0, HUSPR_ATTR_DISPOFF);
        }
        HuPrcVSleep();
    }
}

void fn_1_858(void)
{
    s32 i;
    float angle = 0;
    while (1) {
        float scale;
        angle += 16.0f;
        scale = (0.2f * sind(angle)) + 1.0;
        for (i = 0; i < 8; i++) {
            HuSprScaleSet(lbl_1_bss_CAE, i + 1, scale, scale);
        }
        HuPrcVSleep();
    }
}

void fn_1_918(s16 group, s16 base_member, u32 value, s32 state)
{
    s32 member;
    u32 time[3];
    if (state != 2) {
        time[0] = (value % 60);
        value = (value - time[0]) / 60;
        time[0] = 100.0f * (time[0] / 60.0f);
        time[1] = value % 60;
        value = (value - time[1]) / 60;
        time[2] = value;
    }
    else {
        time[0] = 99;
        time[1] = 59;
        time[2] = 9;
    }
    member = base_member;
    if (state != 0) {
        member += 7;
    }
    HuSprBankSet(group, member, time[0] % 10);
    HuSprBankSet(group, member + 1, time[0] / 10);
    HuSprBankSet(group, member + 3, time[1] % 10);
    HuSprBankSet(group, member + 4, time[1] / 10);
    HuSprBankSet(group, member + 6, time[2] % 10);
}

void fn_1_1B64(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_37C4(void);
void fn_1_4864(void);

void fn_1_B2C(void)
{
    Bss348Data *temp_r31;
    s32 temp_r30;
    void *temp_r29;
    s32 temp_r28;
    HsfTransform *temp_r27;
    s16 temp_r26;
    HsfTransform *temp_r25;
    Process *temp_r18;
    s32 temp_r17;
    AnimData *sp2C[4];
    s32 sp10;
    AnimData *spC;
    AnimData *sp8;
    HuAudSndGrpSet(36);
    for (temp_r30 = 0; temp_r30 < 1; temp_r30++) {
        temp_r31 = &lbl_1_bss_348[temp_r30];
        temp_r31->unk34 = temp_r30;
        temp_r31->unk3C = GWPlayerCfg[temp_r30].pad_idx;
        temp_r31->unk38 = temp_r30 + 1;
        temp_r31->unk44 = 0;
        temp_r31->unk804 = -1;
        temp_r29 = HuDataSelHeapReadNum(lbl_1_data_54[lbl_1_bss_B5C], MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk0[0] = Hu3DModelCreate(temp_r29);
        temp_r29 = HuDataSelHeapReadNum(lbl_1_data_60[lbl_1_bss_B60], MEMORY_DEFAULT_NUM, HEAP_DATA);
        Hu3DAnimCreate(temp_r29, temp_r31->unk0[0], lbl_1_data_78[lbl_1_bss_B5C]);
        Hu3DModelCameraSet(temp_r31->unk0[0], 1 << temp_r31->unk38);
        Hu3DModelPosSet(temp_r31->unk0[0], 0, 0, 0);
        Hu3DModelRotSet(temp_r31->unk0[0], 0, 0, 0);
        Hu3DModelAttrSet(temp_r31->unk0[0], HU3D_ATTR_NOCULL);
        temp_r29 = HuDataSelHeapReadNum(lbl_1_data_54[lbl_1_bss_B5C], MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk0[1] = Hu3DModelCreate(temp_r29);
        temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M451, 0x0D), MEMORY_DEFAULT_NUM, HEAP_DATA);
        Hu3DAnimCreate(temp_r29, temp_r31->unk0[1], lbl_1_data_78[lbl_1_bss_B5C]);
        Hu3DModelCameraSet(temp_r31->unk0[1], 1 << temp_r31->unk38);
        Hu3DModelPosSet(temp_r31->unk0[1], 0, 0, 0);
        Hu3DModelRotSet(temp_r31->unk0[1], 0, 0, 0);
        temp_r29 = HuDataSelHeapReadNum(lbl_1_data_54[lbl_1_bss_B5C], MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk0[2] = Hu3DModelCreate(temp_r29);
        Hu3DModelCameraSet(temp_r31->unk0[2], 1 << temp_r31->unk38);
        Hu3DModelPosSet(temp_r31->unk0[2], 0, 0, 0);
        Hu3DModelRotSet(temp_r31->unk0[2], 0, 0, 0);
        Hu3DModelTPLvlSet(temp_r31->unk0[2], 128);
        Hu3DModelAttrSet(temp_r31->unk0[2], HU3D_ATTR_NOCULL);
        for (temp_r28 = 0; temp_r28 < lbl_1_bss_B58; temp_r28++) {
            temp_r31->unk6C[temp_r28] = Hu3DModelObjPtrGet(temp_r31->unk0[0], lbl_1_data_464[lbl_1_bss_B5C][temp_r28]);
            if (!temp_r31->unk6C[temp_r28]) {
                OSReport("PeaceNo %d\n", lbl_1_bss_B5C);
                OSReport("objname %s\n", lbl_1_data_464[lbl_1_bss_B5C][temp_r28]);
                OSPanic("m451.c", 543, "ObjPtr1");
            }
            temp_r25 = &temp_r31->unk24C[temp_r28];
            temp_r27 = &temp_r31->unk6C[temp_r28]->data.base;
            temp_r27->pos.z += -10;
            temp_r25->pos.x = temp_r27->pos.x;
            temp_r25->pos.y = temp_r27->pos.y;
            temp_r25->pos.z = temp_r27->pos.z;
            temp_r25->rot.x = temp_r27->rot.x;
            temp_r25->rot.y = temp_r27->rot.y;
            temp_r25->rot.z = temp_r27->rot.z;
            temp_r25->scale.x = temp_r27->scale.x;
            temp_r25->scale.y = temp_r27->scale.y;
            temp_r25->scale.z = temp_r27->scale.z;
            temp_r31->unk10C[temp_r28] = Hu3DModelObjPtrGet(temp_r31->unk0[2], lbl_1_data_464[lbl_1_bss_B5C][temp_r28]);
            if (!temp_r31->unk10C[temp_r28]) {
                OSReport("objname %s\n", lbl_1_data_464[lbl_1_bss_B5C][temp_r28]);
                OSPanic("m451.c", 555, "ObjPtr2");
            }
            temp_r31->unk1AC[temp_r28] = Hu3DModelObjPtrGet(temp_r31->unk0[1], lbl_1_data_464[lbl_1_bss_B5C][temp_r28]);
            if (!temp_r31->unk1AC[temp_r28]) {
                OSReport("objname %s\n", lbl_1_data_464[lbl_1_bss_B5C][temp_r28]);
                OSPanic("m451.c", 561, "ObjPtr3");
            }
        }
        temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M451, 0x00), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r26 = Hu3DModelCreate(temp_r29);
        Hu3DModelCameraSet(temp_r26, 1 << temp_r31->unk38);
        Hu3DModelPosSet(temp_r26, 0, 0, 0);
        Hu3DModelRotSet(temp_r26, 0, 0, 0);
        temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M451, 0x04), MEMORY_DEFAULT_NUM, HEAP_DATA);
        temp_r31->unk0[4] = Hu3DModelCreate(temp_r29);
        Hu3DModelCameraSet(temp_r31->unk0[4], 1 << temp_r31->unk38);
        Hu3DModelPosSet(temp_r31->unk0[4], 0, 0, 0);
        Hu3DModelRotSet(temp_r31->unk0[4], 0, 0, 0);
        temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M451, 0x08) + lbl_1_bss_B5C, MEMORY_DEFAULT_NUM, HEAP_DATA);
        Hu3DAnimCreate(temp_r29, temp_r31->unk0[4], "s3puzzle00");
        temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 0x38) + GWPlayerCfg[temp_r30].character, MEMORY_DEFAULT_NUM, HEAP_DATA);
        spC = HuSprAnimRead(temp_r29);
        temp_r26 = HuSprCreate(spC, 16384, 0);
        temp_r31->unkA = HuSprGrpCreate(1);
        HuSprGrpMemberSet(temp_r31->unkA, 0, temp_r26);
        HuSprAttrSet(temp_r31->unkA, 0, 7);
        sp8 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_M451, 0x0C), MEMORY_DEFAULT_NUM));
        temp_r26 = Hu3DParticleCreate(sp8, 100);
        Hu3DModelPosSet(temp_r26, 0, 0, 0);
        Hu3DModelScaleSet(temp_r26, 1, 1, 1);
        Hu3DModelLayerSet(temp_r26, 1);
        Hu3DParticleHookSet(temp_r26, fn_1_1B64);
        Hu3DModelCameraSet(temp_r26, 1 << temp_r31->unk38);
        temp_r18 = HuPrcChildCreate(fn_1_37C4, 8192, 12288, 0, HuPrcCurrentGet());
        temp_r18->user_data = temp_r31;
        lbl_1_bss_4[temp_r30] = temp_r18;
    }
    temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 0x30), MEMORY_DEFAULT_NUM, HEAP_DATA);
    sp2C[0] = HuSprAnimRead(temp_r29);
    temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 0x31), MEMORY_DEFAULT_NUM, HEAP_DATA);
    sp2C[1] = HuSprAnimRead(temp_r29);
    temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MGCONST, 0x37), MEMORY_DEFAULT_NUM, HEAP_DATA);
    sp2C[2] = HuSprAnimRead(temp_r29);
    temp_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M451, 0x0B), MEMORY_DEFAULT_NUM, HEAP_DATA);
    sp2C[3] = HuSprAnimRead(temp_r29);
    lbl_1_bss_CAE = HuSprGrpCreate(16);
    temp_r26 = HuSprCreate(sp2C[3], 16385, 0);
    HuSprGrpMemberSet(lbl_1_bss_CAE, 0, temp_r26);
    HuSprPosSet(lbl_1_bss_CAE, 0, 0, 0);
    HuSprTPLvlSet(lbl_1_bss_CAE, 0, 0.5f);
    HuSprColorSet(lbl_1_bss_CAE, 0, 0, 0, 0);
    for (temp_r30 = 0; temp_r30 < 14; temp_r30++) {
        if (temp_r30 >= 7) {
            temp_r26 = HuSprCreate(sp2C[1], 16384, 0);
        }
        else {
            temp_r26 = HuSprCreate(sp2C[0], 16384, 0);
        }
        HuSprGrpMemberSet(lbl_1_bss_CAE, temp_r30 + 2, temp_r26);
        HuSprPosSet(lbl_1_bss_CAE, temp_r30 + 2, lbl_1_data_6D4[temp_r30 + 1][0], lbl_1_data_6D4[temp_r30 + 1][1]);
        temp_r28 = 0;
        if (temp_r30 == 2 || temp_r30 == 9) {
            temp_r28 = 11;
        }
        if (temp_r30 == 5 || temp_r30 == 12) {
            temp_r28 = 10;
        }
        HuSprBankSet(lbl_1_bss_CAE, temp_r30 + 2, temp_r28);
    }
    temp_r26 = HuSprCreate(sp2C[2], 16384, 0);
    HuSprGrpMemberSet(lbl_1_bss_CAE, 1, temp_r26);
    HuSprPosSet(lbl_1_bss_CAE, 1, lbl_1_data_6D4[0][0], lbl_1_data_6D4[0][1]);
    HuSprGrpPosSet(lbl_1_bss_CAE, 280, 61);
    fn_1_918(lbl_1_bss_CAE, 2, GWMGRecordGet(lbl_1_data_6C8[lbl_1_bss_B5C]), 0);
    fn_1_918(lbl_1_bss_CAE, 2, 0, 1);
    for (temp_r30 = 0; temp_r30 < lbl_1_bss_B58; temp_r30++) {
        lbl_1_bss_C04[temp_r30] = temp_r30;
        lbl_1_bss_B64[temp_r30] = frandmod(4);
    }
    for (temp_r30 = 0; temp_r30 < 50; temp_r30++) {
        temp_r28 = frandmod(lbl_1_bss_B58);
        temp_r17 = frandmod(lbl_1_bss_B58);
        sp10 = lbl_1_bss_C04[temp_r28];
        lbl_1_bss_C04[temp_r28] = lbl_1_bss_C04[temp_r17];
        lbl_1_bss_C04[temp_r17] = sp10;
    }
    HuPrcChildCreate(fn_1_4864, 4096, 4096, 0, HuPrcCurrentGet());
}

void fn_1_1B64(ModelData *model, ParticleData *particle, Mtx matrix)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;

    HsfanimStruct01 *temp_r31;
    s16 temp_r29;
    Bss348Data *temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s32 temp_r25;

    if (particle->unk_34 == 0) {
        temp_r31 = particle->unk_48;
        for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
            temp_r31->unk14.x = temp_r31->unk2C = 0;
            temp_r31->unk40.r = 255;
            temp_r31->unk40.g = 255;
            temp_r31->unk40.b = 0;
        }
    }
    temp_r31 = particle->unk_48;
    temp_r28 = &lbl_1_bss_348[0];
    if (temp_r28->unk44 == 1) {
        for (temp_r27 = 0; temp_r27 < 4; temp_r27++) {
            temp_f28 = 1.0f;
            for (temp_r26 = 0, temp_f30 = 0; temp_r26 < 24; temp_r26++, temp_f30 += 15.0f) {
                for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
                    if (0.0f == temp_r31->unk14.x) {
                        break;
                    }
                }
                if (temp_r29 == particle->unk_30) {
                    break;
                }
                temp_f31 = temp_f30;
                temp_f29 = temp_f28 + (5.0f * frandf());
                temp_r31->unk34.x = temp_r28->unk48[7] + ((temp_r27 * 10.0f) * sind(temp_f31));
                temp_r31->unk34.y = temp_r28->unk48[8] + ((temp_r27 * 10.0f) * cosd(temp_f31));
                temp_r31->unk34.z = 50;
                temp_r31->unk08.x = temp_f29 * sind(temp_f31);
                temp_r31->unk08.y = temp_f29 * cosd(temp_f31);
                temp_r31->unk08.z = 0;
                temp_r31->unk14.x = 30.0f;
                temp_r31->unk14.y = 360.0f * frandf();
                temp_r31->unk14.z = 225;
                temp_r31->unk2C = (5.0f * frandf()) + 25.0f;
                temp_r31->unk40.r = 255;
                temp_r31->unk40.g = 255;
                temp_r31->unk40.b = 0;
                temp_r31->unk40.a = 255;
            }
        }
        temp_r28->unk44++;
        DCStoreRangeNoSync(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
    }
    temp_r31 = particle->unk_48;
    for (temp_r29 = 0; temp_r29 < particle->unk_30; temp_r29++, temp_r31++) {
        if (0.0f == temp_r31->unk14.x) {
            continue;
        }
        VECAdd(&temp_r31->unk08, &temp_r31->unk34, &temp_r31->unk34);
        temp_r31->unk08.x *= 0.95f;
        temp_r31->unk08.y *= 0.95f;
        temp_r31->unk14.y += 20.0f;
        if (temp_r31->unk14.y >= 180.0f && temp_r31->unk14.y < 200.0f) {
            temp_r31->unk14.z *= 0.4f;
        }
        if (temp_r31->unk14.y >= 360.0f && temp_r31->unk14.y < 380.0f) {
            temp_r31->unk14.z *= 0.4f;
        }
        if (temp_r31->unk14.y >= 360.0f) {
            temp_r31->unk14.y -= 360.0f;
        }
        temp_r25 = (30.0 * sind(temp_r31->unk14.y)) + temp_r31->unk14.z;
        if (temp_r25 < 0) {
            temp_r25 = 0;
            temp_r31->unk14.x = 0;
        }
        temp_r31->unk40.a = temp_r25;
        if (0.0f == temp_r31->unk14.x) {
            temp_r31->unk2C = 0;
        }
    }
    PPCSync();
}

s8 fn_1_20FC(s32 arg0, s32 arg1)
{
    Bss348Data *temp_r31 = &lbl_1_bss_348[arg0];
    s8 temp_r30;
    s8 temp_r29;
    s8 temp_r28;
    if (!GWPlayerCfg[arg0].iscom) {
        if (arg1) {
            temp_r29 = temp_r30 = HuPadStkY[temp_r31->unk3C];
        }
        else {
            temp_r29 = temp_r30 = HuPadStkX[temp_r31->unk3C];
        }
        (void)temp_r29;
    }
    else {
        if (arg1) {
            temp_r28 = temp_r30 = temp_r31->unk7F5;
        }
        else {
            temp_r28 = temp_r30 = temp_r31->unk7F4;
        }
    }
    return temp_r30;
}

u8 fn_1_21B4(s32 arg0, s32 arg1)
{
    Bss348Data *temp_r31 = &lbl_1_bss_348[arg0];
    s8 temp_r30;
    s8 temp_r29;
    s8 temp_r28;
    if (!GWPlayerCfg[arg0].iscom) {
        if (arg1) {
            temp_r29 = temp_r30 = HuPadTrigR[temp_r31->unk3C];
        }
        else {
            temp_r29 = temp_r30 = HuPadTrigL[temp_r31->unk3C];
        }
        (void)temp_r29;
    }
    else {
        if (arg1) {
            temp_r28 = temp_r30 = temp_r31->unk7F6;
        }
        else {
            temp_r28 = temp_r30 = temp_r31->unk7F7;
        }
    }
    return temp_r30;
}

static inline s8 fn_1_20FC_inline(s32 arg0, s32 arg1)
{
    Bss348Data *temp_r31 = &lbl_1_bss_348[arg0];
    s8 temp_r30;
    if (!GWPlayerCfg[arg0].iscom) {
        if (arg1) {
            temp_r30 = HuPadStkY[temp_r31->unk3C];
        }
        else {
            temp_r30 = HuPadStkX[temp_r31->unk3C];
        }
    }
    else {
        if (arg1) {
            temp_r30 = temp_r31->unk7F5;
        }
        else {
            temp_r30 = temp_r31->unk7F4;
        }
    }
    return temp_r30;
}

static inline u8 fn_1_21B4_inline(s32 arg0, s32 arg1)
{
    Bss348Data *temp_r31 = &lbl_1_bss_348[arg0];
    s8 temp_r30;
    if (!GWPlayerCfg[arg0].iscom) {
        if (arg1) {
            temp_r30 = HuPadTrigR[temp_r31->unk3C];
        }
        else {
            temp_r30 = HuPadTrigL[temp_r31->unk3C];
        }
    }
    else {
        if (arg1) {
            temp_r30 = temp_r31->unk7F6;
        }
        else {
            temp_r30 = temp_r31->unk7F7;
        }
    }
    return temp_r30;
}

u16 fn_1_2274(s32 arg0)
{
    Bss348Data *temp_r31 = &lbl_1_bss_348[arg0];
    u16 temp_r30;

    // Hacks to stop spilling in fn_1_37C4
    (void)temp_r31;
    (void)temp_r31;
    (void)temp_r31;
    (void)temp_r31;

    if (!GWPlayerCfg[arg0].iscom) {
        temp_r30 = HuPadBtnDown[temp_r31->unk3C];
    }
    else {
        temp_r30 = temp_r31->unk7F8;
    }
    return temp_r30;
}

void fn_1_22E0(Bss348Data *arg0, s32 arg1)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;

    Vec *temp_r31;
    Vec *temp_r29;
    Vec *temp_r28;
    s32 temp_r27;
    Vec *temp_r26;
    s32 temp_r25;

    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    temp_r31 = &arg0->unk6C[arg1]->data.base.pos;
    temp_r26 = &arg0->unk10C[arg1]->data.base.pos;
    temp_r28 = &arg0->unk1AC[arg1]->data.base.pos;
    temp_r29 = &arg0->unk24C[arg1].pos;
    temp_f29 = (temp_r29->x - temp_r31->x) / 15.0f;
    temp_f27 = (temp_r29->z - temp_r31->z) / 30.0f;
    temp_f28 = (temp_r29->y - temp_r31->y) / 15.0f;
    temp_f31 = 20;
    temp_f30 = -20;
    HuSprAttrSet(arg0->unkA, 0, 64);
    omVibrate(arg0->unk34, 12, 6, 6);
    temp_r25 = 0;
    for (temp_r27 = 0; temp_r27 < 30; temp_r27++) {
        temp_r31->z += temp_f27;
        temp_r28->z = temp_r26->z = temp_r31->z - 5.0f;
        if (temp_r27 < 15) {
            temp_r31->x += temp_f29;
            temp_r31->y += temp_f28;
            temp_r28->x = temp_r31->x;
            temp_r28->y = temp_r31->y;
            sp2C.x = 30.0f + temp_r31->x;
            sp2C.z = 50.0f;
            sp2C.y = -30.0f + temp_r31->y;
            Hu3D3Dto2D(&sp2C, (1 << arg0->unk38), &sp20);
            HuSprGrpPosSet(arg0->unkA, sp20.x, sp20.y);
        }
        temp_r26->x = temp_r31->x + temp_f31;
        temp_r26->y = temp_r31->y + temp_f30;
        temp_f31 -= (4.0f / 7.0f);
        temp_f30 -= (-4.0f / 7.0f);
        temp_r28->z += 10.0f;
        if (temp_r27 < 14) {
            temp_r25 += 17;
        }
        else if (temp_r27 < 28) {
            temp_r25 -= 17;
        }
        Hu3DModelTPLvlSet(arg0->unk0[1], 255 - temp_r25);
        HuPrcVSleep();
    }
    temp_r31->x = temp_r29->x;
    temp_r31->y = temp_r29->y;
    temp_r31->z = temp_r29->z;
    sp14.x = 30.0f + temp_r31->x;
    sp14.z = 50;
    sp14.y = -30.0f + temp_r31->y;
    Hu3D3Dto2D(&sp14, (1 << arg0->unk38), &sp8);
    HuSprGrpPosSet(arg0->unkA, sp8.x, sp8.y);
    temp_r28->x = 5000;
}

void fn_1_263C(Bss348Data *arg0, s32 arg1)
{
    HsfTransform *temp_r31;
    HsfTransform *temp_r30;
    HsfTransform *temp_r29;
    float temp_f31;
    temp_r31 = &arg0->unk6C[arg1]->data.base;
    temp_r29 = &arg0->unk10C[arg1]->data.base;
    temp_r30 = &arg0->unk24C[arg1];
    for (temp_f31 = 0; temp_f31 < 180; temp_f31 += 10) {
        temp_r31->scale.x = (temp_r30->scale.x * 0.8f) + (0.2f * (temp_r30->scale.x * (1.0 - sind(temp_f31))));
        temp_r31->scale.y = (temp_r30->scale.y * 0.8f) + (0.2f * (temp_r30->scale.y * (1.0 - sind(temp_f31))));
        temp_r31->scale.z = (temp_r30->scale.z * 0.8f) + (0.2f * (temp_r30->scale.z * (1.0 - sind(temp_f31))));
        temp_r29->scale.x = temp_r31->scale.x;
        temp_r29->scale.y = temp_r31->scale.y;
        temp_r29->scale.z = 0.8f * temp_r31->scale.z;
        HuPrcVSleep();
    }
    for (temp_f31 = 180; temp_f31 < 360; temp_f31 += 20) {
        temp_r31->scale.x = (temp_r30->scale.x * 0.9f) + (0.1f * (temp_r30->scale.x * (1.0 - sind(temp_f31))));
        temp_r31->scale.y = (temp_r30->scale.y * 0.9f) + (0.1f * (temp_r30->scale.y * (1.0 - sind(temp_f31))));
        temp_r31->scale.z = (temp_r30->scale.z * 0.9f) + (0.1f * (temp_r30->scale.z * (1.0 - sind(temp_f31))));
        temp_r29->scale.x = temp_r31->scale.x;
        temp_r29->scale.y = temp_r31->scale.y;
        temp_r29->scale.z = 0.8f * temp_r31->scale.z;
        HuPrcVSleep();
    }
    temp_r31->scale.x = temp_r30->scale.x;
    temp_r31->scale.y = temp_r30->scale.y;
    temp_r31->scale.z = temp_r30->scale.z;
    temp_r29->scale.x = temp_r31->scale.x;
    temp_r29->scale.y = temp_r31->scale.y;
    temp_r29->scale.z = 0.8f * temp_r31->scale.z;
}

void fn_1_2A34(Bss348Data *arg0, s32 arg1, s32 arg2)
{
    HsfTransform *temp_r31;
    HsfTransform *temp_r30;
    s32 temp_r28;

    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;

    temp_r31 = &arg0->unk6C[arg1]->data.base;
    temp_r30 = &arg0->unk10C[arg1]->data.base;
    temp_f30 = temp_r31->scale.x;
    temp_f29 = temp_r31->scale.y;
    temp_f28 = temp_r31->scale.z;
    temp_r31->scale.x = temp_r31->scale.y = temp_r31->scale.z = 0;
    temp_r30->scale.x = temp_r30->scale.y = temp_r30->scale.z = 0;
    for (temp_r28 = 0, temp_f31 = 0; temp_r28 < 30; temp_r28++, temp_f31 += (1.0f / 30.0f)) {
        temp_r31->scale.x += temp_f30 / 30.0f;
        temp_r31->scale.y += temp_f29 / 30.0f;
        temp_r31->scale.z += temp_f28 / 30.0f;
        temp_r30->scale.x = temp_r31->scale.x;
        temp_r30->scale.y = temp_r31->scale.y;
        temp_r30->scale.z = 0.8f * temp_r31->scale.z;
        if (arg2 == 0) {
            HuSprGrpScaleSet(arg0->unkA, temp_f31, temp_f31);
        }
        HuPrcVSleep();
    }
    temp_r31->scale.x = temp_f30;
    temp_r31->scale.y = temp_f29;
    temp_r31->scale.z = temp_f28;
    temp_r30->scale.x = temp_r31->scale.x;
    temp_r30->scale.y = temp_r31->scale.y;
    temp_r30->scale.z = 0.8f * temp_r31->scale.z;
    if (arg2 == 0) {
        HuSprAttrReset(arg0->unkA, 0, HUSPR_ATTR_NOANIM);
        HuSprGrpScaleSet(arg0->unkA, 1, 1);
    }
    else {
        HuSprAttrReset(arg0->unkA, 0, HUSPR_ATTR_REVERSE);
    }
}

typedef struct work_2C50 {
    Bss348Data *unk0;
    s32 unk4;
    s32 unk8;
    s32 *unkC;
} Work2C50;

void fn_1_2C50(void)
{
    HsfTransform *temp_r31;
    Work2C50 *temp_r30;
    s32 temp_r29;
    HsfTransform *temp_r28;
    s32 temp_r27;

    float temp_f31;
    float temp_f30;
    float temp_f29;
    temp_r30 = HuPrcCurrentGet()->user_data;
    temp_r31 = &temp_r30->unk0->unk6C[temp_r30->unk4]->data.base;
    temp_r28 = &temp_r30->unk0->unk10C[temp_r30->unk4]->data.base;
    HuAudFXPlay(1401);
    if (temp_r30->unk8) {
        temp_f30 = temp_r31->rot.z + 90.0f;
    }
    else {
        temp_f30 = temp_r31->rot.z - 90.0f;
    }
    if (temp_f30 >= 360.0f) {
        temp_f30 -= 360.0f;
    }
    if (temp_f30 < 0.0f) {
        temp_f30 += 360.0f;
    }
    temp_f29 = temp_r31->rot.z;
    temp_f31 = 0;
    for (temp_r29 = 0, temp_r27 = 15; temp_r29 < temp_r27; temp_r29++) {
        if (temp_r30->unk8) {
            temp_r31->rot.z = temp_f29 + (100.0 * sind(temp_f31));
        }
        else {
            temp_r31->rot.z = temp_f29 - (100.0 * sind(temp_f31));
        }
        temp_r28->rot.z = temp_r31->rot.z;
        temp_f31 += 6.0f;
        HuPrcVSleep();
    }
    temp_f31 = 90.0f;
    for (temp_r29 = 0, temp_r27 = 3; temp_r29 < temp_r27; temp_r29++) {
        temp_f31 -= (25.0f / 3.0f);
        if (temp_r30->unk8) {
            temp_r31->rot.z = temp_f29 + (100.0 * sind(temp_f31));
        }
        else {
            temp_r31->rot.z = temp_f29 - (100.0 * sind(temp_f31));
        }
        temp_r28->rot.z = temp_r31->rot.z;
        HuPrcVSleep();
    }
    temp_r31->rot.z = temp_r28->rot.z = temp_f30;
    *temp_r30->unkC = 0;
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_2F08(void)
{
    Vec *temp_r31 = HuPrcCurrentGet()->user_data;
    float temp_f31;
    float temp_f30;
    HuPrcSleep(frandmod(24));
    temp_f30 = temp_r31->x / 100.0f;
    temp_f31 = -7.0f;
    while (1) {
        temp_r31->y -= temp_f31;
        if (temp_r31->y < -500.0f) {
            break;
        }
        temp_f31 += 0.5f;
        if (temp_f31 > 20.0f) {
            temp_f31 = 20.0f;
        }
        temp_r31->x += temp_f30;
        temp_r31->z += 10.0f;
        HuPrcVSleep();
    }
    HuPrcKill(HuPrcCurrentGet());
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_2FEC(Bss348Data *arg0, s32 arg1)
{
    Vec *temp_r31 = &arg0->unk6C[arg1]->data.base.pos;
    if (temp_r31->x > 230.0f) {
        temp_r31->x = 230.0f;
    }
    if (temp_r31->x < -230.0f) {
        temp_r31->x = -230.0f;
    }
    if (temp_r31->y > 170.0f) {
        temp_r31->y = 170.0f;
    }
    if (temp_r31->y < -170.0f) {
        temp_r31->y = -170.0f;
    }
}

void fn_1_30B0(s32 arg0, s32 arg1)
{
    switch (GWPlayerCfg[arg0].diff) {
        case 0:
            arg1 *= 8;
            break;

        case 1:
            arg1 *= 4;
            break;

        case 2:
            arg1 *= 2;
            break;
    }
    if (arg1 <= 1) {
        HuPrcVSleep();
    }
    else {
        HuPrcSleep(frandmod(arg1 / 2) + arg1);
    }
}

void fn_1_3154(Bss348Data *arg0, s32 arg1, s32 arg2)
{
    HsfTransform *temp_r30;
    s32 temp_r29;
    HsfTransform *temp_r25;
    s32 temp_r23;
    float temp_f29;
    Vec sp24;
    Vec sp18;
    Vec spC;
    arg1 = lbl_1_bss_C04[arg2];
    temp_r30 = &arg0->unk6C[arg1]->data.base;
    arg0->unk7F4 = arg0->unk7F5 = 0;
    arg0->unk7F7 = arg0->unk7F6 = 0;
    arg0->unk7F8 = 0;
    switch (GWPlayerCfg[arg0->unk34].diff) {
        case 0:
            temp_r29 = (arg2 * 2) + 60;
            break;

        case 1:
            temp_r29 = arg2 + 80;
            break;

        case 2:
            temp_r29 = arg2 + 90;
            break;

        default:
            temp_r29 = arg2 + 95;
            break;
    }
    if (temp_r29 > 100) {
        temp_r29 = 100;
    }
    if (arg0->unk804 == -1) {
        if (frandmod(100) < temp_r29 || lbl_1_bss_B58 == arg2 + 1) {
            arg0->unk804 = arg1;
        }
        else {
            temp_r23 = frandmod(lbl_1_bss_B58 - arg2);
            arg0->unk804 = lbl_1_bss_C04[arg2 + temp_r23];
        }
        arg0->unk808 = -1;
        if (GWPlayerCfg[arg0->unk34].diff == 2 || GWPlayerCfg[arg0->unk34].diff == 3) {
            if (frandmod(100) < temp_r29 || lbl_1_bss_B58 == arg2 + 1) {
                arg0->unk808 = 10;
            }
        }
        fn_1_30B0(arg0->unk34, 10);
    }
    temp_r25 = &arg0->unk24C[arg0->unk804];
    HuSetVecF(&sp24, temp_r25->pos.x, temp_r25->pos.y, 0.0);
    HuSetVecF(&sp18, temp_r30->pos.x, temp_r30->pos.y, 0.0);
    HuSubVecF(&spC, &sp24, &sp18);
    if (VECMagXY(&spC) >= 40.0f) {
        temp_f29 = atan2d(spC.x, spC.y);
        arg0->unk7F4 = 50 * sind(temp_f29);
        arg0->unk7F5 = 50 * cosd(temp_f29);
        if (arg0->unk808 >= 0 && arg0->unk808-- == 0 && temp_r30->rot.z != 0.0f) {
            arg0->unk808 = 10;
            if (0.0f == (temp_r30->rot.z - 90.0f)) {
                arg0->unk7F6 = 50;
            }
            else {
                arg0->unk7F7 = 50;
            }
        }
    }
    else {
        fn_1_30B0(arg0->unk34, 1);
        if (frandmod(100) < temp_r29 || lbl_1_bss_B58 == arg2 + 1) {
            if (0.0f != temp_r30->rot.z) {
                if (0.0f == (temp_r30->rot.z - 90.0f)) {
                    arg0->unk7F6 = 50;
                }
                else {
                    arg0->unk7F7 = 50;
                }
            }
            else {
                arg0->unk7F8 = PAD_BUTTON_A;
                arg0->unk804 = -1;
            }
        }
        else {
            switch (frandmod(3)) {
                case 0:
                    arg0->unk7F6 = 50;
                    break;

                case 1:
                    arg0->unk7F6 = 50;
                    break;

                default:
                    arg0->unk7F8 = PAD_BUTTON_A;
                    arg0->unk804 = -1;
                    break;
            }
            if (frandmod(100) < temp_r29) {
                arg0->unk804 = -1;
            }
        }
    }
}

void fn_1_37C4(void)
{
    Bss348Data *temp_r31;
    HsfTransform *temp_r30;
    s32 temp_r29;
    HsfTransform *temp_r28;
    s32 temp_r26;
    HsfTransform *temp_r25;
    Process *temp_r24;
    s32 temp_r23;
    Vec spCC;
    Vec spC0;
    Vec spB4;
    Work2C50 spA4;
    Vec sp98;
    Vec sp8C;
    Vec sp80;
    Vec sp74;
    s32 sp70;
    s32 sp58;
    s32 sp48;
    float temp_f27;
    float temp_f26;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk40 = 0;
    for (temp_r29 = 0; temp_r29 < lbl_1_bss_B58; temp_r29++) {
        temp_r30 = &temp_r31->unk10C[temp_r29]->data.base;
        temp_r30->pos.x = 5000;
        temp_r30 = &temp_r31->unk1AC[temp_r29]->data.base;
        temp_r30->pos.x = 5000;
    }
    while (lbl_1_bss_CA8 == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(180);
    HuAudFXPlay(1391);
    for (temp_r29 = 0; temp_r29 < lbl_1_bss_B58; temp_r29++) {
        temp_r30 = &temp_r31->unk6C[temp_r29]->data.base;
        temp_f26 = atan2d(temp_r30->pos.x, temp_r30->pos.y);
        temp_f27 = VECMagXY(&temp_r30->pos);
        temp_f27 *= 1.05f;
        temp_r30->pos.x = temp_f27 * sind(temp_f26);
        temp_r30->pos.y = temp_f27 * cosd(temp_f26);
    }
    omVibrate(temp_r31->unk34, 12, 6, 6);
    HuPrcSleep(30);
    HuAudFXPlay(1387);
    for (temp_r29 = 0; temp_r29 < lbl_1_bss_B58; temp_r29++) {
        temp_r24 = HuPrcChildCreate(fn_1_2F08, 8192, 4096, 0, HuPrcCurrentGet());
        temp_r30 = &temp_r31->unk6C[temp_r29]->data.base;
        temp_r24->user_data = temp_r30;
    }
    HuPrcSleep(120);
    lbl_1_bss_CA8 = 2;
    for (temp_r29 = 0; temp_r29 < lbl_1_bss_B58; temp_r29++) {
        sp70 = 0;
        temp_r31->unk44 = 0;
        temp_r31->unk804 = -1;
        temp_r26 = lbl_1_bss_C04[temp_r29];
        temp_r30 = &temp_r31->unk6C[temp_r26]->data.base;
        temp_r28 = &temp_r31->unk10C[temp_r26]->data.base;
        if (temp_r29 != 0) {
            temp_r25 = &temp_r31->unk24C[lbl_1_bss_C04[temp_r29 - 1]];
            temp_r30->pos.x = temp_r25->pos.x;
            temp_r30->pos.y = temp_r25->pos.y;
            temp_r28->pos.x = 20 + temp_r30->pos.x;
            temp_r28->pos.y = -20 + temp_r30->pos.y;
        }
        else {
            temp_r30->pos.x = temp_r30->pos.y = 0;
            temp_r28->pos.x = 20 + temp_r30->pos.x;
            temp_r28->pos.y = -20 + temp_r30->pos.y;
            sp98.x = temp_r30->pos.x + 30;
            sp98.z = 50;
            sp98.y = -30 + temp_r30->pos.y;
            Hu3D3Dto2D(&sp98, (1 << temp_r31->unk38), &sp8C);
            HuSprGrpPosSet(temp_r31->unkA, sp8C.x, sp8C.y);
            HuSprAttrReset(temp_r31->unkA, 0, HUSPR_ATTR_DISPOFF);
        }
        temp_r30->pos.z = 50;
        temp_r28->pos.z = temp_r30->pos.z - 5;
        temp_r30->rot.z = temp_r28->rot.z = 90.0f * lbl_1_bss_B64[temp_r29];
        fn_1_2A34(temp_r31, temp_r26, temp_r29);
        if (temp_r29 == 0) {
            while (lbl_1_bss_CA8 != 3) {
                HuPrcVSleep();
            }
        }
        while (1) {
            if (GWPlayerCfg[temp_r31->unk34].iscom == 1) {
                fn_1_3154(temp_r31, temp_r26, temp_r29);
            }
            if (!sp70) {
                temp_r23 = -1;
                if (fn_1_21B4_inline(temp_r31->unk34, 0) > 20) {
                    temp_r23 = 1;
                }
                if (fn_1_21B4_inline(temp_r31->unk34, 1) > 20) {
                    temp_r23 = 0;
                }
                if (temp_r23 != -1) {
                    sp70 = 1;
                    temp_r24 = HuPrcChildCreate(fn_1_2C50, 8192, 8192, 0, HuPrcCurrentGet());
                    temp_r24->user_data = &spA4;
                    spA4.unk0 = temp_r31;
                    spA4.unk4 = temp_r26;
                    spA4.unk8 = temp_r23;
                    spA4.unkC = &sp70;
                }
            }
            if ((fn_1_2274(temp_r31->unk34) & PAD_BUTTON_A) && !sp70) {
                if (0.0f == temp_r30->rot.z) {
                    temp_r25 = &temp_r31->unk24C[temp_r26];
                    HuSetVecF(&spCC, temp_r25->pos.x, temp_r25->pos.y, 0.0f);
                    HuSetVecF(&spC0, temp_r30->pos.x, temp_r30->pos.y, 0.0f);
                    HuSubVecF(&spB4, &spCC, &spC0);
                    if (VECMagXY(&spB4) < 40.0f) {
                        HuAudFXPlay(1402);
                        temp_r31->unk44 = 1;
                        temp_r31->unk48[7] = temp_r30->pos.x;
                        temp_r31->unk48[8] = temp_r30->pos.y;
                        fn_1_22E0(temp_r31, temp_r26);
                        goto end;
                    }
                }
                fn_1_263C(temp_r31, temp_r26);
            }
            temp_r31->unk48[6] = -1.0f;
            if (ABS_INV(fn_1_20FC_inline(temp_r31->unk34, 0)) > 20 || ABS_INV(fn_1_20FC_inline(temp_r31->unk34, 1)) > 20) {
                temp_r31->unk48[6] = atan2d(fn_1_20FC_inline(temp_r31->unk34, 0), fn_1_20FC_inline(temp_r31->unk34, 1));
            }
            if (-1.0f != temp_r31->unk48[6]) {
                temp_r30->pos.x += 5.0f * sind(temp_r31->unk48[6]);
                temp_r30->pos.y += 5.0f * cosd(temp_r31->unk48[6]);
                fn_1_2FEC(temp_r31, temp_r26);
                temp_r28->pos.x = 20.0f + temp_r30->pos.x;
                temp_r28->pos.y = -20.0f + temp_r30->pos.y;
                sp80.x = 30.0f + temp_r30->pos.x;
                sp80.z = 50;
                sp80.y = -30.0f + temp_r30->pos.y;
                Hu3D3Dto2D(&sp80, (1 << temp_r31->unk38), &sp74);
                HuSprGrpPosSet(temp_r31->unkA, sp74.x, sp74.y);
            }
            HuPrcVSleep();
        }

    end:
        (void)temp_r31;
    }
    temp_r31->unk40 = 4;
    // Hacks to Stop Spilling
    (void)temp_r26;
    (void)temp_r26;
    (void)temp_r24;
    (void)temp_r24;
    (void)temp_r24;
    (void)temp_r23;
    (void)temp_r23;
    (void)temp_r23;
    (void)temp_r23;
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_4768(s32 arg0)
{
    float temp_f31;
    s32 temp_r31;
    s32 temp_r30;
    Bss348Data *spC = &lbl_1_bss_348[arg0];
    Bss348Data *temp_r29;

    for (temp_r31 = 0, temp_f31 = 1; temp_r31 < 15; temp_r31++) {
        temp_f31 -= (1.0f / 15.0f);
        for (temp_r30 = 0; temp_r30 < 1; temp_r30++) {
            temp_r29 = &lbl_1_bss_348[temp_r30];
            HuSprGrpScaleSet(temp_r29->unkA, temp_f31, temp_f31);
        }
        HuPrcVSleep();
    }
    for (temp_r31 = 0; temp_r31 < 1; temp_r31++) {
        HuSprAttrSet(lbl_1_bss_348[temp_r31].unkA, 0, HUSPR_ATTR_DISPOFF);
    }
}

void fn_1_4864(void)
{
    while (1) {
        if (omSysExitReq == 1) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(1000);
            HuPrcSleep(60);
            MGSeqKillAll();
            omOvlReturnEx(1, 1);
            while (1) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}

void fn_1_48C4(void)
{
    u32 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    s16 temp_r21;
    s32 sp14;
    s32 sp10;

    lbl_1_bss_CA8 = 0;
    temp_r31 = 0;
    lbl_1_bss_CA8 = 1;
    while (lbl_1_bss_CA8 == 1) {
        HuPrcVSleep();
    }
    sp10 = HuAudSeqPlay(69);
    temp_r21 = MGSeqStartCreate();
    while (MGSeqStatGet(temp_r21)) {
        HuPrcVSleep();
    }
    lbl_1_bss_CA8 = 3;
    while (1) {
        for (temp_r30 = 0, sp14 = 0; temp_r30 < 1; temp_r30++) {
            if (lbl_1_bss_348[temp_r30].unk40 == 4) {
                temp_r29 = temp_r30;
                sp14++;
            }
        }
        if (sp14 != 0) {
            break;
        }
        temp_r31++;
        fn_1_918(lbl_1_bss_CAE, 2, temp_r31, 1);
        if (temp_r31 >= 35999) {
            temp_r29 = -1;
            break;
        }
        HuPrcVSleep();
    }
    if (temp_r29 == -1) {
        fn_1_918(lbl_1_bss_CAE, 2, 0, 2);
    }
    HuAudSeqFadeOut(sp10, 100);
    for (temp_r30 = 0; temp_r30 < 1; temp_r30++) {
        HuPrcKill(lbl_1_bss_4[temp_r30]);
    }
    temp_r21 = MGSeqFinishCreate();
    while (MGSeqStatGet(temp_r21)) {
        HuPrcVSleep();
    }
    if (temp_r29 == -1 || temp_r31 >= GWMGRecordGet(lbl_1_data_6C8[lbl_1_bss_B5C])) {
        if (temp_r29 != -1) {
            HuAudSStreamPlay(1);
        }
        else {
            HuAudSStreamPlay(4);
        }
    }
    if (temp_r29 != -1) {
        lbl_1_bss_CA8 = 4;
        lbl_1_bss_CA4 = temp_r29;
        fn_1_4768(temp_r29);
    }
    mgRecordExtra = temp_r31;
    if (temp_r29 != -1) {
        if (lbl_1_data_74C[lbl_1_bss_B5C] >= temp_r31) {
            GWGameStat.present[lbl_1_data_758[lbl_1_bss_B5C]] = 1;
            OSReport("time %d no %d\n", lbl_1_data_74C[lbl_1_bss_B5C], lbl_1_data_758[lbl_1_bss_B5C]);
        }
        if (temp_r31 < GWMGRecordGet(lbl_1_data_6C8[lbl_1_bss_B5C])) {
            GWMGRecordSet(lbl_1_data_6C8[lbl_1_bss_B5C], temp_r31);
            temp_r21 = MGSeqRecordCreate(temp_r31);
            HuPrcChildCreate(fn_1_858, 4096, 4096, 0, HuPrcCurrentGet());
            fn_1_918(lbl_1_bss_CAE, 2, temp_r31, 0);
            while (MGSeqStatGet(temp_r21)) {
                HuPrcVSleep();
            }
            HuAudSStreamPlay(1);
        }
        HuPrcSleep(180);
    }
    else {
        mgRecordExtra = 36000;
        HuPrcSleep(210);
    }
    HuPrcSleep(30);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuPrcSleep(60);
    HuAudFadeOut(1);
    MGSeqKillAll();
    omOvlReturnEx(1, 1);
    while (1) {
        HuPrcVSleep();
    }
}
