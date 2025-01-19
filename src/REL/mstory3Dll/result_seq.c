#include "REL/mstory3Dll.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "msm/msmse.h"

#include "ext_math.h"

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ char unk08[0xC];
} StructUnk24Bss1580; // Size 0x14

typedef struct {
    /* 0x00 */ StructFn352C unk00;
    /* 0x34 */ char unk34[0x60];
} StructUnkC4Bss1580; // Size 0x94

typedef struct {
    /* 0x000 */ s32 unk00;
    /* 0x004 */ s32 unk04;
    /* 0x008 */ s32 unk08;
    /* 0x00C */ s32 unk0C;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ s32 unk18;
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ s32 unk20;
    /* 0x024 */ StructUnk24Bss1580 unk24[4];
    /* 0x074 */ char unk74[0x50];
    /* 0x0C4 */ StructUnkC4Bss1580 unkC4[4];
    /* 0x314 */ s32 unk314;
    /* 0x318 */ char unk318[0xC];
    /* 0x324 */ s32 unk324;
    /* 0x328 */ char unk328[0xC];
    /* 0x334 */ s32 unk334[1]; // array length unknown
    /* 0x338 */ char unk338[0xC];
    /* 0x344 */ s32 unk344;
    /* 0x348 */ s32 unk348;
    /* 0x34C */ char unk34C[4];
} StructBss1580; // Size 0x350

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ char unk0C[4];
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ char unk1C[4];
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
} StructBssC8; // Size 0x38

void fn_1_7E88(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_1_82E0(void);
s32 fn_1_B670(void);
void fn_1_D48C(void);
void fn_1_D718(omObjData* arg0);
void fn_1_D7D8(omObjData* arg0);
void fn_1_FE80(void);
void fn_1_FF7C(s32 arg0);
void fn_1_1036C(omObjData* arg0);
void fn_1_10D74(omObjData* arg0);
void fn_1_11794(omObjData* arg0);
void fn_1_11834(omObjData* arg0);
void fn_1_123D8(omObjData* arg0);
void fn_1_1241C(omObjData* arg0);
void fn_1_12420(omObjData* arg0);
void fn_1_12A98(s32 arg0);
void fn_1_12C08(s32 arg0);
void fn_1_12DAC(void);
void fn_1_13908(void);
void fn_1_130A8(void);
void fn_1_1317C(void);
void fn_1_13A38(omObjData* arg0);
void fn_1_13A3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_13C78(s32 arg0, s32 arg1, s32 arg2);
void fn_1_13D38(s32 arg0, s32 arg1, s32 arg2);
void fn_1_140A0(void);
void fn_1_15450(s32 arg0);

StructBss1580 lbl_1_bss_1580;
StructBss1530 lbl_1_bss_1558;
StructBss1530 lbl_1_bss_1530;
StructBss1530 lbl_1_bss_1490[4];
StructBss1530 lbl_1_bss_1468;
s32 lbl_1_bss_1458[4];
s32 lbl_1_bss_1448[4];
s32 lbl_1_bss_1438[4];
s32 lbl_1_bss_1428[4];
float lbl_1_bss_1424;
s32 lbl_1_bss_1420;
float lbl_1_bss_1408[3][2];
StructBssC8 lbl_1_bss_C8[88];
float lbl_1_bss_C4;
float lbl_1_bss_C0;
float lbl_1_bss_BC;
s32 lbl_1_bss_B8;
s32 lbl_1_bss_B4;
float lbl_1_bss_B0;
float lbl_1_bss_AC;
Process* lbl_1_bss_A8;
s32 lbl_1_bss_68[16];
u8 lbl_1_bss_5C[0xC]; // unused
s32 lbl_1_bss_58;

Vec lbl_1_data_130[] = {
    { -300.0f, 0.0f, 460.0f },
    { -100.0f, 0.0f, 460.0f },
    {  100.0f, 0.0f, 460.0f },
    {  300.0f, 0.0f, 460.0f }
};

HsfanimStruct00 lbl_1_data_160 = {
    60, { 0, 0 },
    1000.0f, 0.0f, 180.0f,
    { 0.0f, -0.009f, 0.0f },
    30.0f, 0.9f, 20.0f, 0.99f, 4,
    {
        { 0xFF, 0xFF, 0x00, 0xFF },
        { 0xFF, 0xFF, 0x20, 0xFF },
        { 0xFF, 0xFF, 0x80, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF }
    },
    {
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 }
    }
};

HsfanimStruct00 lbl_1_data_1B0 = {
    60, { 0, 0 },
    1000.0f, 0.0f, 180.0f,
    { 0.0f, -0.009f, 0.0f },
    30.0f, 0.9f, 20.0f, 0.99f, 4,
    {
        { 0xFF, 0xFF, 0x00, 0xFF },
        { 0xFF, 0xFF, 0x20, 0xFF },
        { 0xFF, 0xFF, 0x80, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF }
    },
    {
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 }
    }
};

HsfanimStruct00 lbl_1_data_200 = {
    500, { 0, 0 },
    0.25f, 0.0f, 30.0f,
    { 0.0f, -0.009f, 0.001f },
    30.0f, 0.9f, 20.0f, 0.999f, 4,
    {
        { 0xFF, 0xFF, 0x00, 0xFF },
        { 0xFF, 0xFF, 0x20, 0xFF },
        { 0xFF, 0xFF, 0x80, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF }
    },
    {
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 }
    }
};

void fn_1_6E34(Process* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_r31;

    lbl_1_bss_A8 = arg0;
    lbl_1_bss_1580.unk00 = arg1;
    lbl_1_bss_1580.unk04 = arg2;
    if (arg3 == 1) {
        lbl_1_bss_1580.unk08 = 0;
    } else {
        lbl_1_bss_1580.unk08 = 1;
        lbl_1_bss_1580.unk04 = 1;
    }
    lbl_1_bss_1580.unk14 = fn_1_36E4();
    lbl_1_bss_1580.unk344 = GWSystem.team;
    _ClearFlag(FLAG_ID_MAKE(1, 29));
    lbl_1_bss_1580.unk348 = -1;
    fn_1_9A0();
    fn_1_290C(lbl_1_bss_A8, fn_1_82E0);
    lbl_1_bss_1580.unk1C = fn_1_37C8(lbl_1_bss_1580.unk20 = 0xFF);
    fn_1_FF7C(arg4);
    fn_1_38B4();
    fn_1_12DAC();
    HuPrcChildCreate(fn_1_FE80, 100, 0x2000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_140A0, 100, 0x2000, 0, HuPrcCurrentGet());
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuPrcChildCreate(fn_1_13908, 200, 0x2000, 0, HuPrcCurrentGet());
    }
    HuPrcChildCreate(fn_1_D48C, 100, 0x2000, 0, HuPrcCurrentGet());
}

void fn_1_7004(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp1C[4];
    s32 spC[4];
    s32 temp_r27;
    s32 var_r26;
    s32 var_r30;
    s32 var_r31;

    temp_r27 = lbl_1_bss_1580.unk20;
    var_r26 = arg0;
    lbl_1_bss_1530.unk04 = (void*) fn_1_D718;
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        lbl_1_bss_1490[var_r30].unk04 = (void*) fn_1_1241C;
    }
    lbl_1_bss_1468.unk04 = (void*) fn_1_13A38;
    if (arg2 != 0) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            sp1C[var_r31] = lbl_1_bss_1490[var_r31].unk00->work[0];
            spC[var_r31] = 0xFF;
        }
    }
    for (var_r30 = 0; var_r30 < arg1; var_r30++) {
        fn_1_938();
        lbl_1_bss_1580.unk20 = fn_1_5D4(temp_r27, var_r26, var_r30, arg1);
        Hu3DGLightColorSet(lbl_1_bss_1580.unk1C, lbl_1_bss_1580.unk20, lbl_1_bss_1580.unk20, lbl_1_bss_1580.unk20, 0xFF);
        if (arg2 != 0) {
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                fn_1_7E88(sp1C[var_r31], spC[var_r31], var_r30, arg1, var_r31);
            }
        }
    }
    if (arg2 != 0) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            lbl_1_bss_1490[var_r31].unk00->work[0] = 0;
            lbl_1_bss_1490[var_r31].unk00->work[1] = 0;
            Hu3DModelAttrSet(lbl_1_bss_1490[var_r31].unk00->model[6], 1);
            Hu3DLLightColorSet(lbl_1_bss_1490[var_r31].unk00->model[1], lbl_1_bss_1580.unk24[var_r31].unk00, 0, 0, 0, 0xFF);
            Hu3DLLightColorSet(lbl_1_bss_1490[var_r31].unk00->model[2], lbl_1_bss_1580.unk24[var_r31].unk04, 0, 0, 0, 0xFF);
        }
    }
    lbl_1_bss_1530.unk04 = NULL;
    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        lbl_1_bss_1490[var_r30].unk04 = NULL;
    }
    lbl_1_bss_1468.unk04 = NULL;
}

void fn_1_7398(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    float temp_f31;
    float temp_f30;
    s32 sp10;
    s32 spC;
    s32 temp_r29;
    s32 var_r28;

    sp10 = lbl_1_bss_1490[arg2].unk00->work[0];
    spC = arg0;
    Hu3DModelPosSet(lbl_1_bss_1490[arg2].unk00->model[6], lbl_1_data_130[arg2].x, 500.0f + lbl_1_data_130[arg2].y + lbl_1_bss_AC, lbl_1_data_130[arg2].z + 0.1f * lbl_1_bss_AC);
    Hu3DModelScaleSet(lbl_1_bss_1490[arg2].unk00->model[6], 0.0f, 1.25f, 0.0f);
    Hu3DModelTPLvlSet(lbl_1_bss_1490[arg2].unk00->model[6], 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_1490[arg2].unk00->model[6], 1);
    Hu3DModelPosSet(lbl_1_bss_1490[arg3].unk00->model[6], lbl_1_data_130[arg3].x, 500.0f + lbl_1_data_130[arg3].y + lbl_1_bss_AC, lbl_1_data_130[arg3].z + 0.1f * lbl_1_bss_AC);
    Hu3DModelScaleSet(lbl_1_bss_1490[arg3].unk00->model[6], 0.0f, 1.25f, 0.0f);
    Hu3DModelTPLvlSet(lbl_1_bss_1490[arg3].unk00->model[6], 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_1490[arg3].unk00->model[6], 1);
    for (var_r28 = 0; var_r28 <= arg1; var_r28++) {
        fn_1_938();
        temp_f31 = fn_1_6F4(0.0f, 1.5f, var_r28, arg1);
        temp_f30 = fn_1_6F4(0.0f, 0.5f, var_r28, arg1);
        temp_r29 = fn_1_6F4(0.0f, 128.0f, var_r28, arg1);
        Hu3DModelScaleSet(lbl_1_bss_1490[arg2].unk00->model[6], temp_f31, 1.25f, temp_f31);
        Hu3DModelTPLvlSet(lbl_1_bss_1490[arg2].unk00->model[6], temp_f30);
        Hu3DModelScaleSet(lbl_1_bss_1490[arg3].unk00->model[6], temp_f31, 1.25f, temp_f31);
        Hu3DModelTPLvlSet(lbl_1_bss_1490[arg3].unk00->model[6], temp_f30);
        Hu3DLLightColorSet(lbl_1_bss_1490[arg2].unk00->model[1], lbl_1_bss_1580.unk24[arg2].unk00, temp_r29, temp_r29, temp_r29, 0xFF);
        Hu3DLLightColorSet(lbl_1_bss_1490[arg2].unk00->model[2], lbl_1_bss_1580.unk24[arg2].unk04, temp_r29, temp_r29, temp_r29, 0xFF);
        Hu3DLLightColorSet(lbl_1_bss_1490[arg3].unk00->model[1], lbl_1_bss_1580.unk24[arg3].unk00, temp_r29, temp_r29, temp_r29, 0xFF);
        Hu3DLLightColorSet(lbl_1_bss_1490[arg3].unk00->model[2], lbl_1_bss_1580.unk24[arg3].unk04, temp_r29, temp_r29, temp_r29, 0xFF);
    }
    lbl_1_bss_1490[arg2].unk00->work[1] = 1;
    lbl_1_bss_1490[arg3].unk00->work[1] = 1;
}

void fn_1_79D8(s32 arg0, s32 arg1, s32 arg2) {
    float temp_f31;
    float temp_f30;
    s32 temp_r27;
    s32 var_r26;
    s32 temp_r29;
    s32 var_r30;

    temp_r27 = lbl_1_bss_1490[arg2].unk00->work[0];
    var_r26 = arg0;
    Hu3DModelPosSet(lbl_1_bss_1490[arg2].unk00->model[6], lbl_1_data_130[arg2].x, 500.0f + lbl_1_data_130[arg2].y + lbl_1_bss_AC, lbl_1_data_130[arg2].z + 0.1f * lbl_1_bss_AC);
    Hu3DModelScaleSet(lbl_1_bss_1490[arg2].unk00->model[6], 0.0f, 1.25f, 0.0f);
    Hu3DModelTPLvlSet(lbl_1_bss_1490[arg2].unk00->model[6], 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_1490[arg2].unk00->model[6], 1);
    for (var_r30 = 0; var_r30 <= arg1; var_r30++) {
        fn_1_938();
        lbl_1_bss_1490[arg2].unk00->work[0] = fn_1_6F4(temp_r27, var_r26, var_r30, arg1);
        temp_f31 = fn_1_6F4(0.0f, 1.5f, var_r30, arg1);
        temp_f30 = fn_1_6F4(0.0f, 0.5f, var_r30, arg1);
        temp_r29 = fn_1_6F4(0.0f, 128.0f, var_r30, arg1);
        Hu3DModelScaleSet(lbl_1_bss_1490[arg2].unk00->model[6], temp_f31, 1.25f, temp_f31);
        Hu3DModelTPLvlSet(lbl_1_bss_1490[arg2].unk00->model[6], temp_f30);
        Hu3DLLightColorSet(lbl_1_bss_1490[arg2].unk00->model[1], lbl_1_bss_1580.unk24[arg2].unk00, temp_r29, temp_r29, temp_r29, 0xFF);
        Hu3DLLightColorSet(lbl_1_bss_1490[arg2].unk00->model[2], lbl_1_bss_1580.unk24[arg2].unk04, temp_r29, temp_r29, temp_r29, 0xFF);
    }
    lbl_1_bss_1490[arg2].unk00->work[1] = 1;
}

void fn_1_7E88(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    float var_f31;
    s32 temp_r31;

    if (lbl_1_bss_1490[arg4].unk00->work[1] != 0) {
        lbl_1_bss_1490[arg4].unk00->work[0] = fn_1_5D4(arg0, arg1, arg2, arg3);
        var_f31 = fn_1_5D4(0.5f, 0.0f, arg2, arg3);
        Hu3DModelTPLvlSet(lbl_1_bss_1490[arg4].unk00->model[6], var_f31);
        temp_r31 = fn_1_5D4(128.0f, 0.0f, arg2, arg3);
        Hu3DLLightColorSet(lbl_1_bss_1490[arg4].unk00->model[1], lbl_1_bss_1580.unk24[arg4].unk00, temp_r31, temp_r31, temp_r31, 0xFF);
        Hu3DLLightColorSet(lbl_1_bss_1490[arg4].unk00->model[2], lbl_1_bss_1580.unk24[arg4].unk04, temp_r31, temp_r31, temp_r31, 0xFF);
    }
}

s32 fn_1_814C(s32 arg0) {
    s32 var_r31;

    if (arg0 == 0) {
        var_r31 = Hu3DParManCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 1)), 100, &lbl_1_data_160);
    } else if (arg0 == 1) {
        var_r31 = Hu3DParManCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 1)), 500, &lbl_1_data_1B0);
    } else if (arg0 == 2) {
        var_r31 = Hu3DParManCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 1)), 250, &lbl_1_data_200);
    }
    if (arg0 != 2) {
        Hu3DParManTimeLimitSet(var_r31, 60);
        Hu3DParManAttrSet(var_r31, 4 | 0x40);
        Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(var_r31), 1);
    } else {
        Hu3DParManAttrSet(var_r31, 4 | 0x40);
    }
    return var_r31;
}

s32 fn_1_8264(void) {
    return fn_1_814C(0);
}

void fn_1_82E0(void) {
    StructBss4* var_r31;

    var_r31 = &lbl_1_bss_4;
    var_r31->unk08.x = 0.0f;
    var_r31->unk08.y = 125.0f;
    var_r31->unk08.z = 0.0f;
    var_r31->unk20.x = -5.0f;
    var_r31->unk20.y = 0.0f;
    var_r31->unk20.z = 0.0f;
    var_r31->unk38 = 1750.0f;
}

void fn_1_836C(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    sp8.unk08.x = 0.0f;
    sp8.unk08.y = 170.0f;
    sp8.unk08.z = 0.0f;
    sp8.unk20.x = -5.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 1700.0f;
    fn_1_514C(var_r31, &sp8, var_r31->unk40++, 60.0f, 30.0f);
}

void fn_1_845C(void) {
    StructBss4* var_r31 = &lbl_1_bss_4;
    StructBss4 sp28;
    float sp8[] = {
        530.0f, 530.0f, 540.0f, 530.0f,
        530.0f, 580.0f, 540.0f, 630.0f
    };

    if (lbl_1_bss_1580.unk344 == 1) {
        if (lbl_1_bss_1580.unk348 == 0) {
            sp28.unk08.x = 100.0f + Hu3DData[lbl_1_bss_1490[0].unk00->model[1]].pos.x;
        } else {
            sp28.unk08.x = 100.0f + Hu3DData[lbl_1_bss_1490[2].unk00->model[1]].pos.x;
        }
    } else {
        sp28.unk08.x = Hu3DData[lbl_1_bss_1490[lbl_1_bss_1458[1]].unk00->model[1]].pos.x;
        lbl_1_bss_B4 = lbl_1_bss_1580.unkC4[lbl_1_bss_1458[1]].unk00.unk10;
    }
    if (lbl_1_bss_1580.unk344 == 1) {
        sp28.unk08.y = 570.0f;
        sp28.unk08.z = -700.0f;
        sp28.unk20.x = 15.0f;
        sp28.unk20.y = 0.0f;
        sp28.unk20.z = 0.0f;
        sp28.unk38 = 1750.0f;
        fn_1_4CC0(var_r31, &sp28, var_r31->unk40++, 120.0f);
    } else {
        sp28.unk08.y = sp8[lbl_1_bss_B4];
        sp28.unk08.z = -700.0f;
        sp28.unk20.x = 15.0f;
        sp28.unk20.y = 0.0f;
        sp28.unk20.z = 0.0f;
        sp28.unk38 = 1600.0f;
        fn_1_4CC0(var_r31, &sp28, var_r31->unk40++, 120.0f);
    }
}

void fn_1_8758(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    sp8.unk08.x = lbl_1_bss_1424;
    sp8.unk08.y = 125.0f;
    sp8.unk08.z = 0.0f;
    sp8.unk20.x = -5.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 1250.0f;
    sp8.unk38 = 1350.0f;
    fn_1_514C(var_r31, &sp8, var_r31->unk40++, 10.0f, 5.0f);
}

void fn_1_8858(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    sp8.unk08.x = 0.0f;
    sp8.unk08.y = 170.0f;
    sp8.unk08.z = 0.0f;
    sp8.unk20.x = -5.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 1700.0f;
    fn_1_514C(var_r31, &sp8, var_r31->unk40++, 30.0f, 10.0f);
}

void fn_1_8948(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    sp8.unk08.x = 300.0f;
    sp8.unk08.y = 100.0f;
    sp8.unk08.z = 0.0f;
    sp8.unk20.x = -5.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 1000.0f;
    fn_1_4400(var_r31, &sp8, var_r31->unk40++, 60.0f, 10.0f);
}

void fn_1_8A38(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    sp8.unk08.x = -300.0f;
    sp8.unk08.y = 100.0f;
    sp8.unk08.z = 0.0f;
    sp8.unk20.x = -5.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 1000.0f;
    fn_1_4400(var_r31, &sp8, var_r31->unk40++, 180.0f, 10.0f);
}

void fn_1_8B28(void) {
    StructBss4* var_r31;
    StructBss4 sp8;

    var_r31 = &lbl_1_bss_4;
    sp8.unk08.x = 0.0f;
    sp8.unk08.y = 170.0f;
    sp8.unk08.z = 0.0f;
    sp8.unk20.x = -5.0f;
    sp8.unk20.y = 0.0f;
    sp8.unk20.z = 0.0f;
    sp8.unk38 = 1700.0f;
    fn_1_4400(var_r31, &sp8, var_r31->unk40++, 120.0f, 10.0f);
}

void fn_1_8C18(void) {
    fn_1_39B4(&lbl_1_bss_4);
    fn_1_2834(fn_1_8948);
    fn_1_958(120);
    fn_1_39B4(&lbl_1_bss_4);
    fn_1_2834(fn_1_8A38);
    fn_1_958(210);
    fn_1_39B4(&lbl_1_bss_4);
    fn_1_2834(fn_1_8B28);
    fn_1_958(120);
}

void fn_1_8C94(void) {
    s32 var_r30 = 16;
    s32 var_r29 = 40;
    s32 var_r28 = 0;
    GXColor sp10 = { 0x00, 0x00, 0x80, 0x80 };
    s32 var_r31;

    while (TRUE) {
        fn_1_938();
        if (HuPadBtnDown[0] & PAD_TRIGGER_R) {
            var_r28++;
            var_r28 %= 2;
        }
        if (var_r28 == 0) {
            continue;
        }
        printWin(var_r30, var_r29, 220, 200, &sp10);
        if (lbl_1_bss_1558.unk04 == NULL) {
            print8(var_r30, var_r29, 1.0f, "PROC_MAIN    -> FALSE");
        } else {
            print8(var_r30, var_r29, 1.0f, "PROC_MAIN    -> TRUE");
        }
        if (lbl_1_bss_1530.unk04 == NULL) {
            print8(var_r30, var_r29 + 10, 1.0f, "PROC_MAP     -> FALSE");
        } else {
            print8(var_r30, var_r29 + 10, 1.0f, "PROC_MAP     -> TRUE");
        }
        if (lbl_1_bss_1468.unk04 == NULL) {
            print8(var_r30, var_r29 + 20, 1.0f, "PROC_SUB     -> FALSE");
        } else {
            print8(var_r30, var_r29 + 20, 1.0f, "PROC_SUB     -> TRUE");
        }
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_1490[var_r31].unk04 == NULL) {
                print8(var_r30, var_r29 + 30 + var_r31 * 10, 1.0f, "PROC_PLAYER%d -> FALSE", var_r31);
            } else {
                print8(var_r30, var_r29 + 30 + var_r31 * 10, 1.0f, "PROC_PLAYER%d -> TRUE", var_r31);
            }
        }
        print8(var_r30, var_r29 + 80, 1.0f, "M:%d P:%d W:%d", lbl_1_bss_1580.unk00, lbl_1_bss_1580.unk0C, lbl_1_bss_1580.unk14);
        print8(var_r30, var_r29 + 100, 1.0f, "NO) IDX:GRP:COM:DIF:PAD:CHR");
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            print8(var_r30, var_r29 + 110 + var_r31 * 10, 1.0f, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", var_r31,
                lbl_1_bss_1580.unkC4[var_r31].unk00.unk00, lbl_1_bss_1580.unkC4[var_r31].unk00.unk04, lbl_1_bss_1580.unkC4[var_r31].unk00.unk08,
                lbl_1_bss_1580.unkC4[var_r31].unk00.unk0C, lbl_1_bss_1580.unkC4[var_r31].unk00.unk14, lbl_1_bss_1580.unkC4[var_r31].unk00.unk10);
        }
        print8(var_r30, var_r29 + 150, 1.0f, "NO) RNK:STA:COI:MGS:COS:HAS");
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            print8(var_r30, var_r29 + 160 + var_r31 * 10, 1.0f, "%2d) %3d:%3d:%3d:%3d:%3d:%3d", var_r31,
                lbl_1_bss_1580.unkC4[var_r31].unk00.unk18, lbl_1_bss_1580.unkC4[var_r31].unk00.unk20, lbl_1_bss_1580.unkC4[var_r31].unk00.unk1C,
                lbl_1_bss_1580.unkC4[var_r31].unk00.unk24, lbl_1_bss_1580.unkC4[var_r31].unk00.unk28, lbl_1_bss_1580.unkC4[var_r31].unk00.unk2C);
        }
    }
}

void fn_1_9140(void) {
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (TRUE) {
        if (WipeStatGet() == 0) {
            break;
        }
        fn_1_938();
    }
    fn_1_9C4();
    CharModelKill(-1);
    MGSeqKillAll();
    HuAudSStreamAllStop();
    msmSeStopAll(0, 1000);
    omOvlGotoEx(OVL_MSTORY3, 1, 1, 0);
}

void fn_1_91C8(void) {
    lbl_1_bss_58 = HuAudSeqPlay(0x31);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    while (TRUE) {
        if (WipeStatGet() == 0) {
            break;
        }
        fn_1_938();
    }
}

void fn_1_9220(void) {
    Vec sp14 = { -320.0f, 0.0f, 910.0f };

    fn_1_958(60);
    lbl_1_bss_1580.unk10 = fn_1_1624(1, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][0]);
    fn_1_13C78(lbl_1_bss_1580.unk10, 0, 3);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    fn_1_39B4(&lbl_1_bss_4);
    fn_1_2834(fn_1_836C);
    fn_1_1E28(lbl_1_bss_1530.unk00, 2, 2, 0, 0);
    fn_1_1E28(lbl_1_bss_1468.unk00, 1, 2, 15, 1);
    fn_1_2DD4(lbl_1_bss_1468.unk00, 1, sp14, 30.0f, 60.0f, 10.0f);
    fn_1_1E28(lbl_1_bss_1468.unk00, 1, 1, 15, 1);
    fn_1_2280(lbl_1_bss_1530.unk00, 2, 2, 0);
}

void fn_1_93D0(omObjData* arg0) {
    StructBss1530* temp_r31;

    temp_r31 = arg0->data;
    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][2]);
    fn_1_13A3C(lbl_1_bss_1580.unk10, 1, -1, 3);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    temp_r31->unk04 = 0;
}

void fn_1_9488(void) {
    s32 var_r31;

    lbl_1_bss_1530.unk04 = (void*) fn_1_93D0;
    do {
        fn_1_938();
    } while (lbl_1_bss_1580.unk18 != 99);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1490[var_r31].unk04 = (void*) fn_1_1036C;
        lbl_1_bss_1490[var_r31].unk18 = lbl_1_bss_1490[var_r31].unk1C = 0;
    }
    fn_1_12A98(0);
    for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
        if (lbl_1_bss_1580.unkC4[lbl_1_bss_1448[var_r31]].unk00.unk20 != 0) {
            lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk1C = 1;
        }
    }
    HuAudFXPlay(0xB9);
    do {
        fn_1_938();
    } while (lbl_1_bss_1530.unk04 != NULL);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1490[var_r31].unk18 = 1;
    }
    do {
        fn_1_938();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_1490[var_r31].unk18 != 2) {
                break;
            }
        }
    } while (var_r31 < 4);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1490[var_r31].unk18 = 3;
    }
    do {
        fn_1_938();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_1490[var_r31].unk04 != NULL) {
                break;
            }
        }
    } while (var_r31 < 4);
}

void fn_1_96B0(omObjData* arg0) {
    StructBss1530* temp_r31;

    temp_r31 = arg0->data;
    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][2]);
    fn_1_13A3C(lbl_1_bss_1580.unk10, 2, -1, 3);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    temp_r31->unk04 = 0;
}

void fn_1_9768(void) {
    s32 var_r31;

    lbl_1_bss_1530.unk04 = (void*) fn_1_96B0;
    do {
        fn_1_938();
    } while (lbl_1_bss_1580.unk18 != 99);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1490[var_r31].unk04 = (void*) fn_1_10D74;
        lbl_1_bss_1490[var_r31].unk18 = lbl_1_bss_1490[var_r31].unk1C = 0;
    }
    fn_1_12A98(1);
    for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
        if (lbl_1_bss_1580.unkC4[lbl_1_bss_1448[var_r31]].unk00.unk1C != 0) {
            lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk1C = 1;
        }
    }
    HuAudFXPlay(0xB8);
    do {
        fn_1_938();
    } while (lbl_1_bss_1530.unk04 != NULL);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1490[var_r31].unk18 = 1;
    }
    do {
        fn_1_938();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_1490[var_r31].unk18 != 2) {
                break;
            }
        }
    } while (var_r31 < 4);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1490[var_r31].unk18 = 3;
    }
    do {
        fn_1_938();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_1490[var_r31].unk04 != NULL) {
                break;
            }
        }
    } while (var_r31 < 4);
}

void fn_1_9990(omObjData* arg0) {
    StructBss1530* temp_r31;

    temp_r31 = arg0->data;
    HuAudFXPlay(0x9A);
    fn_1_13A3C(lbl_1_bss_1580.unk10, lbl_1_bss_1420, -1, 4);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    temp_r31->unk04 = 0;
}

void fn_1_9A08(omObjData* arg0) {
    StructBss1530* temp_r31;

    temp_r31 = arg0->data;
    fn_1_958(60);
    HuAudSeqPause(lbl_1_bss_58, 0, 1000);
    temp_r31->unk04 = 0;
}

void fn_1_9A64(s32 arg0) {
    s32 var_r28;
    s32 var_r27;
    s32 var_r30;
    s32 var_r31;

    var_r28 = 9999;
    var_r27 = -1;
    lbl_1_bss_1420 = arg0;
    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][2]);
    fn_1_13C78(lbl_1_bss_1580.unk10, arg0 * 3 + 3, 3);
    fn_1_12C08(arg0);
    lbl_1_bss_1424 = 0.0f;
    switch (lbl_1_bss_1458[0]) {
        case 1:
            lbl_1_bss_1424 = lbl_1_data_130[lbl_1_bss_1448[0]].x;
            break;
        case 2:
            lbl_1_bss_1424 = (lbl_1_data_130[lbl_1_bss_1448[0]].x + lbl_1_data_130[lbl_1_bss_1448[1]].x) / 2;
            fn_1_13C78(lbl_1_bss_1580.unk10, arg0 * 3 + 4, 3);
            break;
        case 3:
            for (var_r31 = 0; var_r31 < 3; var_r31++) {
                if (var_r28 >= lbl_1_bss_1448[var_r31]) {
                    var_r28 = lbl_1_bss_1448[var_r31];
                }
                if (var_r27 <= lbl_1_bss_1448[var_r31]) {
                    var_r27 = lbl_1_bss_1448[var_r31];
                }
            }
            lbl_1_bss_1424 = (lbl_1_data_130[var_r27].x + lbl_1_data_130[var_r28].x) / 2;
            fn_1_13C78(lbl_1_bss_1580.unk10, arg0 * 3 + 5, 3);
            break;
        case 4:
            break;
    }
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    HuAudSeqPause(lbl_1_bss_58, 1, 1000);
    lbl_1_bss_68[0] = HuAudFXPlay(0x9E);
    fn_1_7004(0x40, 30, 0);
    fn_1_958(60);
    if (lbl_1_bss_1458[0] < 4) {
        fn_1_39B4(&lbl_1_bss_4);
        fn_1_2834(fn_1_8758);
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                if (var_r31 == lbl_1_bss_1448[var_r30]) {
                    lbl_1_bss_1490[var_r31].unk04 = (void*) fn_1_11834;
                    lbl_1_bss_1490[var_r31].unk18 = 0;
                    break;
                }
            }
            if (var_r30 == 4) {
                lbl_1_bss_1490[var_r31].unk04 = (void*) fn_1_11794;
                lbl_1_bss_1490[var_r31].unk18 = 0;
            }
        }
    } else {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            lbl_1_bss_1490[var_r31].unk04 = (void*) fn_1_11794;
            lbl_1_bss_1490[var_r31].unk18 = 0;
        }
    }
    if (lbl_1_bss_1458[0] != 4) {
        lbl_1_bss_1580.unk10 = fn_1_1624(1, 0, 21, 2, lbl_1_bss_1580.unk14);
    } else {
        lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    }
    if (lbl_1_bss_1458[0] <= 3) {
        HuAudFXPlay(0x9F);
    }
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][2]);
    switch (lbl_1_bss_1458[0]) {
        case 1:
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[0], 0);
            lbl_1_bss_1420 = 12;
            lbl_1_bss_1530.unk04 = (void*) fn_1_9990;
            lbl_1_bss_1468.unk04 = (void*) fn_1_9A08;
            break;
        case 2:
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[0], 0);
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[1], 1);
            lbl_1_bss_1420 = 13;
            lbl_1_bss_1530.unk04 = (void*) fn_1_9990;
            lbl_1_bss_1468.unk04 = (void*) fn_1_9A08;
            break;
        case 3:
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[0], 0);
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[1], 1);
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[2], 2);
            lbl_1_bss_1420 = 14;
            lbl_1_bss_1530.unk04 = (void*) fn_1_9990;
            lbl_1_bss_1468.unk04 = (void*) fn_1_9A08;
            break;
        case 4:
            HuAudFXFadeOut(lbl_1_bss_68[0], 500);
            lbl_1_bss_1468.unk04 = (void*) fn_1_9A08;
            if (lbl_1_bss_1580.unkC4[lbl_1_bss_1448[0]].unk00.unk2C == 0 && arg0 == 2) {
                fn_1_13C78(lbl_1_bss_1580.unk10, 26, 3);
            } else {
                fn_1_13C78(lbl_1_bss_1580.unk10, 15, 3);
            }
            fn_1_1AB0(lbl_1_bss_1580.unk10);
            break;
    }
    for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
        lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk18 = 1;
    }
    do {
        fn_1_938();
        for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
            if (lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk04 != NULL) {
                break;
            }
        }
    } while (var_r31 < lbl_1_bss_1458[0]);
    lbl_1_bss_1580.unk18 = 1;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        Hu3DModelAttrReset(lbl_1_bss_1490[var_r31].unk00->model[1], HU3D_MOTATTR_PAUSE);
    }
    fn_1_958(10);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        fn_1_1E28(lbl_1_bss_1490[var_r31].unk00, 1, 1, 15, 1);
    }
    do {
        fn_1_938();
    } while (lbl_1_bss_1530.unk04 != NULL);
    fn_1_12DAC();
    HuAudSeqPause(lbl_1_bss_58, 0, 1000);
    fn_1_39B4(&lbl_1_bss_4);
    fn_1_2834(fn_1_8858);
    fn_1_7004(0xFF, 30, 1);
    fn_1_958(60);
}

s32 fn_1_A314(void) {
    s32 var_r31 = 0;

    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][2]);
    fn_1_13C78(lbl_1_bss_1580.unk10, 0x10, 3);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    fn_1_12DAC();
    fn_1_130A8();
    if (lbl_1_bss_1580.unk344 == 1) {
        var_r31 = fn_1_B670();
    }
    if (var_r31 != -1 && lbl_1_bss_1458[0] <= 1) {
        HuAudSeqFadeOut(lbl_1_bss_58, 1000);
    } else {
        HuAudSeqPause(lbl_1_bss_58, 1, 1000);
    }
    lbl_1_bss_68[0] = HuAudFXPlay(0x9E);
    lbl_1_bss_B0 = 1.0f;
    lbl_1_bss_1530.unk04 = (void*) fn_1_D7D8;
    fn_1_7004(0x40, 30, 0);
    fn_1_8C18();
    lbl_1_bss_AC = 125.0f;
    return var_r31;
}

void fn_1_A4F0(void) {
    s32 var_r31;

    HuAudSeqPause(lbl_1_bss_58, 0, 1000);
    HuAudFXFadeOut(lbl_1_bss_68[0], 1000);
    lbl_1_bss_B0 = 0.0f;
    fn_1_7004(0xFF, 30, 1);
    fn_1_958(60);
    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][1]);
    fn_1_13C78(lbl_1_bss_1580.unk10, 0x11, 3);
    switch (lbl_1_bss_1458[0]) {
        case 1:
            break;
        case 2:
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[0], 0);
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[1], 1);
            fn_1_13C78(lbl_1_bss_1580.unk10, 13, 3);
            break;
        case 3:
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[0], 0);
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[1], 1);
            fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1448[2], 2);
            fn_1_13C78(lbl_1_bss_1580.unk10, 14, 3);
            break;
        case 4:
            fn_1_13C78(lbl_1_bss_1580.unk10, 0x12, 3);
            break;
    }
    fn_1_13C78(lbl_1_bss_1580.unk10, 0x13, 3);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1438[var_r31] = lbl_1_bss_1428[var_r31] = -1;
    }
    for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
        lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk04 = (void*) fn_1_123D8;
        lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk18 = 0;
    }
    do {
        fn_1_938();
        for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
            if (lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk18 != 1) {
                break;
            }
        }
    } while (var_r31 < lbl_1_bss_1458[0]);
    for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
        lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk18 = 2;
    }
    fn_1_958(0x96);
    fn_1_1317C();
    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][2]);
    fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1458[1], 0);
    fn_1_13C78(lbl_1_bss_1580.unk10, 0x14, 3);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
        if (lbl_1_bss_1458[1] == lbl_1_bss_1448[var_r31]) {
            fn_1_1E28(lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk00, 1, 14, 15, 0);
        } else {
            fn_1_1E28(lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk00, 1, 15, 15, 0);
        }
    }
    fn_1_958(0x23);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        fn_1_1E28(lbl_1_bss_1490[var_r31].unk00, 1, 1, 15, 1);
    }
    fn_1_958(0x55);
    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][3]);
    fn_1_13C78(lbl_1_bss_1580.unk10, 0x15, 3);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        fn_1_1E28(lbl_1_bss_1490[var_r31].unk00, 1, 1, 15, 1);
    }
    HuAudSeqFadeOut(lbl_1_bss_58, 1000);
    lbl_1_bss_68[0] = HuAudFXPlay(0x9E);
    lbl_1_bss_B0 = 1.0f;
    fn_1_7004(0x40, 30, 0);
    fn_1_8C18();
}

void fn_1_ABAC(void) {
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1490[var_r31].unk04 = (void*) fn_1_12420;
    }
    do {
        fn_1_938();
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (lbl_1_bss_1490[var_r31].unk04 != NULL) {
                break;
            }
        }
    } while (var_r31 < 4);
    lbl_1_bss_B0 = 0.0f;
    fn_1_958(15);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_1580.unkC4[var_r31].unk00.unk18 == 1) {
            break;
        }
    }
    if (lbl_1_bss_1580.unk344 == 1) {
        if (lbl_1_bss_1580.unk348 == 0) {
            fn_1_7398(0xFF, 5, 0, 1);
        } else {
            fn_1_7398(0xFF, 5, 2, 3);
        }
    } else {
        fn_1_79D8(0xFF, 5.0f, var_r31);
    }
    HuAudFXPlay(0x9F);
    HuAudSeqPlay(0x32);
    fn_1_958(30);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (lbl_1_bss_1580.unk344 == 1) {
            if (lbl_1_bss_1580.unk348 == 0) {
                CharModelVoiceEnableSet(lbl_1_bss_1580.unkC4[0].unk00.unk10, lbl_1_bss_1490[0].unk00->motion[3], 0);
                CharModelVoiceEnableSet(lbl_1_bss_1580.unkC4[1].unk00.unk10, lbl_1_bss_1490[1].unk00->motion[3], 0);
                CharModelVoiceEnableSet(lbl_1_bss_1580.unkC4[2].unk00.unk10, lbl_1_bss_1490[2].unk00->motion[4], 0);
                CharModelVoiceEnableSet(lbl_1_bss_1580.unkC4[3].unk00.unk10, lbl_1_bss_1490[3].unk00->motion[4], 0);
                fn_1_1E28(lbl_1_bss_1490[0].unk00, 1, 3, 15, 0);
                fn_1_1E28(lbl_1_bss_1490[1].unk00, 1, 3, 15, 0);
                fn_1_1E28(lbl_1_bss_1490[2].unk00, 1, 4, 15, 0);
                fn_1_1E28(lbl_1_bss_1490[3].unk00, 1, 4, 15, 0);
                lbl_1_bss_1580.unk0C = 0;
            } else {
                CharModelVoiceEnableSet(lbl_1_bss_1580.unkC4[0].unk00.unk10, lbl_1_bss_1490[0].unk00->motion[4], 0);
                CharModelVoiceEnableSet(lbl_1_bss_1580.unkC4[1].unk00.unk10, lbl_1_bss_1490[1].unk00->motion[4], 0);
                CharModelVoiceEnableSet(lbl_1_bss_1580.unkC4[2].unk00.unk10, lbl_1_bss_1490[2].unk00->motion[3], 0);
                CharModelVoiceEnableSet(lbl_1_bss_1580.unkC4[3].unk00.unk10, lbl_1_bss_1490[3].unk00->motion[3], 0);
                fn_1_1E28(lbl_1_bss_1490[0].unk00, 1, 4, 15, 0);
                fn_1_1E28(lbl_1_bss_1490[1].unk00, 1, 4, 15, 0);
                fn_1_1E28(lbl_1_bss_1490[2].unk00, 1, 3, 15, 0);
                fn_1_1E28(lbl_1_bss_1490[3].unk00, 1, 3, 15, 0);
                lbl_1_bss_1580.unk0C = 2;
            }
        } else if (lbl_1_bss_1580.unkC4[var_r31].unk00.unk18 == 1) {
            CharModelVoiceEnableSet(lbl_1_bss_1580.unkC4[var_r31].unk00.unk10, lbl_1_bss_1490[var_r31].unk00->motion[3], 0);
            fn_1_1E28(lbl_1_bss_1490[var_r31].unk00, 1, 3, 15, 0);
            lbl_1_bss_1580.unk0C = var_r31;
        } else {
            CharModelVoiceEnableSet(lbl_1_bss_1580.unkC4[var_r31].unk00.unk10, lbl_1_bss_1490[var_r31].unk00->motion[4], 0);
            fn_1_1E28(lbl_1_bss_1490[var_r31].unk00, 1, 4, 15, 0);
        }
        GWPlayer[lbl_1_bss_1580.unkC4[var_r31].unk00.unk00].rank = lbl_1_bss_1580.unkC4[var_r31].unk00.unk18 - 1;
    }
    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][2]);
    if (lbl_1_bss_1580.unk344 == 1) {
        if (lbl_1_bss_1580.unk348 == 0) {
            fn_1_13D38(lbl_1_bss_1580.unk10, 0, 0);
            fn_1_13D38(lbl_1_bss_1580.unk10, 1, 1);
            _SetFlag(FLAG_ID_MAKE(1, 29));
        } else {
            fn_1_13D38(lbl_1_bss_1580.unk10, 2, 0);
            fn_1_13D38(lbl_1_bss_1580.unk10, 3, 1);
        }
        fn_1_13C78(lbl_1_bss_1580.unk10, 0x19, 5);
    } else {
        fn_1_13D38(lbl_1_bss_1580.unk10, lbl_1_bss_1458[1], 0);
        fn_1_13C78(lbl_1_bss_1580.unk10, 0x16, 5);
    }
    fn_1_1AB0(lbl_1_bss_1580.unk10);
}

s32 fn_1_B670(void) {
    s32 var_r31;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27;

    var_r31 = 1;
    temp_r30 = lbl_1_bss_1580.unkC4[0].unk00.unk20 + lbl_1_bss_1580.unkC4[1].unk00.unk20;
    temp_r29 = lbl_1_bss_1580.unkC4[2].unk00.unk20 + lbl_1_bss_1580.unkC4[3].unk00.unk20;
    temp_r28 = lbl_1_bss_1580.unkC4[0].unk00.unk1C + lbl_1_bss_1580.unkC4[1].unk00.unk1C;
    temp_r27 = lbl_1_bss_1580.unkC4[2].unk00.unk1C + lbl_1_bss_1580.unkC4[3].unk00.unk1C;
    if (temp_r30 > temp_r29) {
        lbl_1_bss_1580.unk348 = 0;
    } else if (temp_r30 < temp_r29) {
        lbl_1_bss_1580.unk348 = 1;
    } else if (temp_r28 > temp_r27) {
        lbl_1_bss_1580.unk348 = 0;
    } else if (temp_r28 < temp_r27) {
        lbl_1_bss_1580.unk348 = 1;
    } else {
        var_r31 = -1;
    }
    return var_r31;
}

void fn_1_B788(void) {
    s32 var_r31;

    HuAudSeqPause(lbl_1_bss_58, 0, 1000);
    HuAudFXFadeOut(lbl_1_bss_68[0], 1000);
    lbl_1_bss_B0 = 0.0f;
    fn_1_7004(0xFF, 30, 1);
    fn_1_958(60);
    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][1]);
    fn_1_13C78(lbl_1_bss_1580.unk10, 0x17, 3);
    fn_1_13C78(lbl_1_bss_1580.unk10, 0x13, 3);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_1438[var_r31] = lbl_1_bss_1428[var_r31] = -1;
    }
    lbl_1_bss_1458[0] = 2;
    lbl_1_bss_1448[0] = 0;
    lbl_1_bss_1448[1] = 2;
    for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
        lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk04 = (void*) fn_1_123D8;
        lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk18 = 0;
    }
    do {
        fn_1_938();
        for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
            if (lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk18 != 1) {
                break;
            }
        }
    } while (var_r31 < lbl_1_bss_1458[0]);
    for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
        lbl_1_bss_1490[lbl_1_bss_1448[var_r31]].unk18 = 2;
    }
    fn_1_958(150);
    if (lbl_1_bss_1428[0] > lbl_1_bss_1428[2]) {
        lbl_1_bss_1580.unk348 = 0;
    } else {
        lbl_1_bss_1580.unk348 = 1;
    }
    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][2]);
    if (lbl_1_bss_1580.unk348 == 0) {
        fn_1_13D38(lbl_1_bss_1580.unk10, 0, 0);
        fn_1_13D38(lbl_1_bss_1580.unk10, 1, 1);
    } else {
        fn_1_13D38(lbl_1_bss_1580.unk10, 2, 0);
        fn_1_13D38(lbl_1_bss_1580.unk10, 3, 1);
    }
    fn_1_13C78(lbl_1_bss_1580.unk10, 0x18, 3);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    for (var_r31 = 0; var_r31 < lbl_1_bss_1458[0]; var_r31++) {
        if (lbl_1_bss_1580.unk348 == 0) {
            fn_1_1E28(lbl_1_bss_1490[0].unk00, 1, 14, 15, 0);
            fn_1_1E28(lbl_1_bss_1490[1].unk00, 1, 14, 15, 0);
            fn_1_1E28(lbl_1_bss_1490[2].unk00, 1, 15, 15, 0);
            fn_1_1E28(lbl_1_bss_1490[3].unk00, 1, 15, 15, 0);
        } else {
            fn_1_1E28(lbl_1_bss_1490[0].unk00, 1, 15, 15, 0);
            fn_1_1E28(lbl_1_bss_1490[1].unk00, 1, 15, 15, 0);
            fn_1_1E28(lbl_1_bss_1490[2].unk00, 1, 14, 15, 0);
            fn_1_1E28(lbl_1_bss_1490[3].unk00, 1, 14, 15, 0);
        }
    }
    fn_1_958(35);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        fn_1_1E28(lbl_1_bss_1490[var_r31].unk00, 1, 1, 15, 1);
    }
    fn_1_958(85);
    lbl_1_bss_1580.unk10 = fn_1_1624(0, 0, 21, 2, lbl_1_bss_1580.unk14);
    HuAudFXPlay(lbl_1_data_0[lbl_1_bss_1580.unk00][3]);
    fn_1_13C78(lbl_1_bss_1580.unk10, 0x15, 3);
    fn_1_1AB0(lbl_1_bss_1580.unk10);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        fn_1_1E28(lbl_1_bss_1490[var_r31].unk00, 1, 1, 15, 1);
    }
    HuAudSeqFadeOut(lbl_1_bss_58, 1000);
    lbl_1_bss_68[0] = HuAudFXPlay(0x9E);
    lbl_1_bss_B0 = 1.0f;
    fn_1_7004(0x40, 30, 0);
    fn_1_8C18();
}

void fn_1_BE5C(void) {
    float var_f31;

    var_f31 = fn_1_878(0.0f, 0.1f, lbl_1_bss_B8, 180.0f);
    Hu3DData[lbl_1_bss_1530.unk00->model[20]].pos.y += var_f31;
    lbl_1_bss_B8++;
    if (lbl_1_bss_B8 >= 180) {
        lbl_1_bss_B8 -= 180;
    }
}

void fn_1_BF60(void) {
    float temp_f1;

    temp_f1 = fn_1_878(1.0f, 1.1f, lbl_1_bss_B8, 60.0f);
    Hu3DModelScaleSet(lbl_1_bss_1530.unk00->model[23], temp_f1, temp_f1, 1.0f);
    lbl_1_bss_B8++;
    if (lbl_1_bss_B8 >= 60) {
        lbl_1_bss_B8 -= 60;
    }
}

s32 lbl_1_data_364 = -1;
s32 lbl_1_data_368 = -1; // unused

void fn_1_C060(float arg8) {
    float sp20[] = {
        50.0f, 50.0f, 60.0f,  50.0f,
        50.0f, 80.0f, 60.0f, 120.0f
    };
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float temp_f29;
    float var_f28;
    float temp_f27;
    float var_f26;
    s32 var_r31;

    lbl_1_bss_BC = arg8;
    fn_1_938();
    var_f31 = arg8;
    var_f30 = 0.0f;
    temp_f29 = 3600.0f;
    Hu3DModelPosSet(lbl_1_bss_1530.unk00->model[20], var_f31, 1000.0f, 460.0f);
    Hu3DModelScaleSet(lbl_1_bss_1530.unk00->model[20], 0.5f, 0.5f, 0.5f);
    Hu3DModelAttrReset(lbl_1_bss_1530.unk00->model[20], HU3D_ATTR_DISPOFF);
    fn_1_1E28(lbl_1_bss_1530.unk00, 20, 20, 0, 2);
    Hu3DModelPosSet(lbl_1_bss_1530.unk00->model[21], var_f31, 1000.0f, 460.0f);
    Hu3DModelScaleSet(lbl_1_bss_1530.unk00->model[21], 0.5f, 0.5f, 0.5f);
    fn_1_1E28(lbl_1_bss_1530.unk00, 21, 21, 0, 2);
    Hu3DModelPosSet(lbl_1_bss_1530.unk00->model[22], var_f31, 1000.0f, 460.0f);
    Hu3DModelScaleSet(lbl_1_bss_1530.unk00->model[22], 0.5f, 0.5f, 0.5f);
    Hu3DMotionShapeSpeedSet(lbl_1_bss_1530.unk00->model[22], 2.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_1530.unk00->model[22], 2.0f);
    Hu3DMotionShiftSpeedSet(lbl_1_bss_1530.unk00->model[22], 2.0f);
    fn_1_1E28(lbl_1_bss_1530.unk00, 22, 22, 0, 2);
    Hu3DModelScaleSet(lbl_1_bss_1530.unk00->model[23], 0.0f, 0.0f, 1.0f);
    Hu3DModelAttrSet(lbl_1_bss_1530.unk00->model[23], HU3D_ATTR_DISPOFF);
    fn_1_958(60);
    fn_1_39B4(&lbl_1_bss_4);
    fn_1_2834(fn_1_845C);
    for (var_r31 = 0; var_r31 <= 120; var_r31++) {
        fn_1_938();
        if (lbl_1_bss_1580.unk344 == 0) {
            var_f30 = fn_1_6F4(1000.0f, 250.0f + sp20[lbl_1_bss_1580.unkC4[lbl_1_bss_1458[1]].unk00.unk10], var_r31, 120.0f);
        } else {
            var_f30 = fn_1_6F4(1000.0f, 350.0f, var_r31, 120.0f);
        }
        temp_f29 = fn_1_6F4(1800.0f, 0.0f, var_r31, 120.0f);
        var_f28 = fn_1_6F4(1.0f, 0.0f, var_r31, 120.0f);
        Hu3DModelPosSet(lbl_1_bss_1530.unk00->model[20], var_f31, var_f30, 460.0f);
        Hu3DModelRotSet(lbl_1_bss_1530.unk00->model[20], 0.0f, temp_f29, 0.0f);
    }
    lbl_1_bss_1530.unk04 = (void*) fn_1_BE5C;
    fn_1_958(30);
    fn_1_1E28(lbl_1_bss_1530.unk00, 20, 20, 0, 0);
    fn_1_958(30);
    HuAudFXPlay(0x33B);
    fn_1_958(30);
    Hu3DModelPosSet(lbl_1_bss_1530.unk00->model[22], var_f31, Hu3DData[lbl_1_bss_1530.unk00->model[20]].pos.y - 10.0f, 460.0f);
    Hu3DModelAttrReset(lbl_1_bss_1530.unk00->model[22], HU3D_ATTR_DISPOFF);
    fn_1_1E28(lbl_1_bss_1530.unk00, 22, 22, 0, 0);
    sp14.x = var_f31;
    sp14.y = Hu3DData[lbl_1_bss_1530.unk00->model[20]].pos.y;
    sp14.z = 460.0f;
    sp8.x = 288.0f;
    sp8.y = 100.0f;
    sp8.z = 500.0f;
    fn_1_1DED8(DATA_MAKE_NUM(DATADIR_MSTORY3, 0), &sp14, &sp8, 100);
    fn_1_1E0F4();
    fn_1_958(15);
    if (lbl_1_bss_1580.unk344 == 1) {
        if (lbl_1_bss_1580.unk348 == 0) {
            HuAudCharVoicePlay(lbl_1_bss_1580.unkC4[0].unk00.unk10, 0x12B);
            HuAudCharVoicePlay(lbl_1_bss_1580.unkC4[1].unk00.unk10, 0x12B);
        } else {
            HuAudCharVoicePlay(lbl_1_bss_1580.unkC4[2].unk00.unk10, 0x12B);
            HuAudCharVoicePlay(lbl_1_bss_1580.unkC4[3].unk00.unk10, 0x12B);
        }
    } else {
        HuAudCharVoicePlay(lbl_1_bss_1580.unkC4[lbl_1_bss_1458[1]].unk00.unk10, 0x12B);
    }
    HuAudFXPlay(0xBA);
    HuAudFXPlay(0x9A);
    Hu3DModelPosSet(lbl_1_bss_1530.unk00->model[21], var_f31, Hu3DData[lbl_1_bss_1530.unk00->model[20]].pos.y, 510.0f);
    Hu3DModelAttrReset(lbl_1_bss_1530.unk00->model[21], HU3D_ATTR_DISPOFF);
    fn_1_1E28(lbl_1_bss_1530.unk00, 21, 21, 0, 0);
    fn_1_958(5);
    lbl_1_data_364 = fn_1_814C(1);
    Hu3DParManPosSet(lbl_1_data_364, var_f31, Hu3DData[lbl_1_bss_1530.unk00->model[21]].pos.y, 510.0f);
    Hu3DModelAttrSet(lbl_1_bss_1530.unk00->model[20], HU3D_ATTR_DISPOFF);
    lbl_1_bss_C0 = 1.0f;
    for (var_r31 = 0; var_r31 <= 30; var_r31++) {
        fn_1_938();
        temp_f27 = fn_1_5D4(0.0f, 1.0f, var_r31, 30.0f);
        var_f30 = fn_1_5D4(0.0f, 75.0f, var_r31, 30.0f);
        var_f26 = fn_1_5D4(550.0f, 640.0f, var_r31, 30.0f);
        Hu3DModelPosSet(lbl_1_bss_1530.unk00->model[23], var_f31, Hu3DData[lbl_1_bss_1530.unk00->model[20]].pos.y - var_f30, var_f26);
        Hu3DModelScaleSet(lbl_1_bss_1530.unk00->model[23], temp_f27, temp_f27, 1.0f);
        var_f28 = fn_1_5D4(1.0f, 0.0f, var_r31, 30.0f);
        Hu3DModelTPLvlSet(lbl_1_bss_1530.unk00->model[22], var_f28);
    }
    lbl_1_bss_B8 = 0;
    lbl_1_bss_1530.unk04 = (void*) fn_1_BF60;
    fn_1_958(30);
    Hu3DParManKill(lbl_1_data_364);
    lbl_1_data_364 = -1;
    fn_1_958(240);
    fn_1_1834(MAKE_MESSID(36, 7), 0);
    if (lbl_1_bss_1580.unk344 == 1) {
        if (lbl_1_bss_1580.unk348 == 0) {
            if (lbl_1_bss_1580.unkC4[0].unk00.unk08 == 1 && lbl_1_bss_1580.unkC4[1].unk00.unk08 == 1) {
                fn_1_958(30);
            } else {
                while (TRUE) {
                    fn_1_938();
                    if (lbl_1_bss_1580.unkC4[0].unk00.unk08 == 0 && (HuPadBtnDown[lbl_1_bss_1580.unkC4[0].unk00.unk14] & PAD_BUTTON_A)) {
                        break;
                    }
                    if (lbl_1_bss_1580.unkC4[1].unk00.unk08 == 0 && (HuPadBtnDown[lbl_1_bss_1580.unkC4[1].unk00.unk14] & PAD_BUTTON_A)) {
                        break;
                    }
                }
            }
        } else {
            if (lbl_1_bss_1580.unkC4[2].unk00.unk08 == 1 && lbl_1_bss_1580.unkC4[3].unk00.unk08 == 1) {
                fn_1_958(30);
            } else {
                while (TRUE) {
                    fn_1_938();
                    if (lbl_1_bss_1580.unkC4[0].unk00.unk08 == 0 && (HuPadBtnDown[lbl_1_bss_1580.unkC4[0].unk00.unk14] & PAD_BUTTON_A)) {
                        break;
                    }
                    if (lbl_1_bss_1580.unkC4[1].unk00.unk08 == 0 && (HuPadBtnDown[lbl_1_bss_1580.unkC4[1].unk00.unk14] & PAD_BUTTON_A)) {
                        break;
                    }
                }
            }
        }
    } else if (lbl_1_bss_1580.unk08 == 0) {
        if (lbl_1_bss_1580.unkC4[lbl_1_bss_1580.unk0C].unk00.unk08 != 1) {
            fn_1_2420(lbl_1_bss_1580.unkC4[lbl_1_bss_1580.unk0C].unk00.unk14, PAD_BUTTON_A);
        } else {
            fn_1_958(30);
        }
    } else {
        fn_1_2420(0, PAD_BUTTON_A);
    }
    HuAudFXPlay(0x1C);
}

void fn_1_CE6C(omObjData* arg0) {
    StructBss1530* sp8 = arg0->data;
    s32 var_r31;

    fn_1_91C8();
    fn_1_9220();
    fn_1_9488();
    fn_1_9768();
    if (lbl_1_bss_1580.unk04 != 0) {
        fn_1_9A64(0);
        fn_1_9A64(1);
        fn_1_9A64(2);
    }
    var_r31 = fn_1_A314();
    if (lbl_1_bss_1580.unk344 == 1) {
        if (var_r31 == -1) {
            fn_1_B788();
        }
    } else if (lbl_1_bss_1458[0] > 1) {
        fn_1_A4F0();
    }
    fn_1_ABAC();
    if (lbl_1_bss_1580.unk344 == 1) {
        if (lbl_1_bss_1580.unk348 == 0) {
            fn_1_C060(lbl_1_data_130[0].x + 100.0f);
        } else {
            fn_1_C060(lbl_1_data_130[2].x + 100.0f);
        }
    } else {
        fn_1_C060(lbl_1_data_130[lbl_1_bss_1458[1]].x);
    }
    fn_1_958(60);
    fn_1_9140();
}

void fn_1_D48C(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_A8, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_1558.unk00 = temp_r3;
    lbl_1_bss_1558.unk04 = (void*) fn_1_CE6C;
    lbl_1_bss_1558.unk00->data = &lbl_1_bss_1558;
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_1558.unk04 != NULL) {
            lbl_1_bss_1558.unk04(temp_r3);
        }
    }
}

void fn_1_D538(omObjData* arg0) {
    float sp8;
    float var_f30;
    float var_f31;
    StructBss1530* temp_r31;
    s32 var_r30;
    s32 var_r29;

    temp_r31 = arg0->data;
    var_f31 = 1.75f;
    sp8 = 0.5f;
    var_r29 = 0;
    HuAudFXPlay(0xBA);
    HuAudFXPlay(0x9A);
    lbl_1_bss_1580.unk324 = 1;
    espDispOn(temp_r31->unk14);
    espScaleSet(temp_r31->unk14, 0.0f, 0.0f);
    for (var_r30 = 0; var_r30 < 120; var_r30++) {
        fn_1_938();
        if (var_r30 < 60) {
            var_f30 = fn_1_6F4(0.0f, 1.75f, var_r30, 60.0f);
        } else {
            var_f30 = fn_1_7BC(var_f31, 1.0f, var_r29, 15.0f);
            var_r29++;
            if (var_r29 == 15) {
                if (var_f31 > 1.25f) {
                    var_f31 -= 0.1f;
                }
                var_r29 = 0;
            }
        }
        espScaleSet(temp_r31->unk14, var_f30, var_f30);
    }
    temp_r31->unk04 = 0;
}

void fn_1_D718(omObjData* arg0) {
    float temp_f31;

    temp_f31 = lbl_1_bss_1580.unk20 / 255.0f;
    Hu3DModelAmbSet(arg0->model[1], temp_f31, temp_f31, temp_f31);
    Hu3DModelAmbSet(arg0->model[2], temp_f31, temp_f31, temp_f31);
    Hu3DModelAmbSet(arg0->model[3], temp_f31, temp_f31, temp_f31);
}

float lbl_1_data_36C[] = { 0.0f, 120.0f, 240.0f };

void fn_1_D7D8(omObjData* arg0) {
    s32 var_r30;

    if (lbl_1_bss_B0 == 1.0f) {
        Hu3DModelAttrReset(arg0->model[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(arg0->model[5], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(arg0->model[6], HU3D_ATTR_DISPOFF);
        lbl_1_bss_C4 += 0.033333335f;
        if (lbl_1_bss_C4 >= 0.5f) {
            lbl_1_bss_C4 = 0.5f;
        }
    } else {
        if (lbl_1_bss_B0 == 0.0f) {
            lbl_1_bss_C4 -= 0.033333335f;
            if (lbl_1_bss_C4 <= 0.0f) {
                lbl_1_bss_C4 = 0.0f;
                Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(arg0->model[6], HU3D_ATTR_DISPOFF);
                return;
            }
        } else {
            Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(arg0->model[6], HU3D_ATTR_DISPOFF);
            return;
        }
    }
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        Hu3DModelTPLvlSet(arg0->model[var_r30 + 4], lbl_1_bss_C4);
        Hu3DModelRotSet(arg0->model[var_r30 + 4], 0.0f, 0.0f, lbl_1_bss_1408[var_r30][1]);
        lbl_1_bss_1408[var_r30][0] = 10.0 * cosd(11.0f * lbl_1_data_36C[var_r30]);
        lbl_1_bss_1408[var_r30][1] = 30.0 * sind(8.0f * lbl_1_data_36C[var_r30]);
        if ((lbl_1_data_36C[var_r30] += 0.4f) >= 360.0f) {
            lbl_1_data_36C[var_r30] -= 360.0f;
        }
    }
}

void fn_1_DB68(omObjData* arg0, s32 arg1, s32 arg2) {
    s32 sp8[] = { DATA_MAKE_NUM(DATADIR_MSTORY3, 6), DATA_MAKE_NUM(DATADIR_MSTORY3, 5) };
    s32 var_r30;

    if (arg2 < 5) {
        arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 4));
        arg0->motion[0] = Hu3DMotionIDGet(arg0->model[1]);
        fn_1_1E28(arg0, 1, 0, 0, 2);
        arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 8));
        arg0->model[3] = Hu3DModelCreateFile(sp8[arg1]);
        arg0->motion[3] = Hu3DMotionIDGet(arg0->model[3]);
        fn_1_1E28(arg0, 3, 3, 0, 1);
        Hu3DModelShadowMapObjSet(arg0->model[1], "base_fix9-base");
    } else {
        arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 7));
        arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 8));
        arg0->model[3] = Hu3DModelCreateFile(sp8[arg1]);
        Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF);
        arg0->motion[3] = Hu3DMotionIDGet(arg0->model[1]);
        fn_1_1E28(arg0, 1, 3, 0, 1);
        Hu3DModelShadowMapObjSet(arg0->model[1], "base_story-base");
    }
    for (var_r30 = 4; var_r30 < 7; var_r30++) {
        arg0->model[var_r30] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 11));
        Hu3DModelTPLvlSet(arg0->model[var_r30], 0.0f);
        Hu3DModelPosSet(arg0->model[var_r30], -200.0f + 200.0f * (var_r30 - 4), 750.0f, 500.0f);
        Hu3DModelScaleSet(arg0->model[var_r30], 1.25f, 2.0f, 1.25f);
        Hu3DModelAttrSet(arg0->model[var_r30], HU3D_ATTR_DISPOFF);
    }
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[2], DATA_MAKE_NUM(DATADIR_MSTORY3, 9));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[2], DATA_MAKE_NUM(DATADIR_MSTORY3, 10));
    lbl_1_bss_1530.unk14 = espEntry(DATA_MAKE_NUM(DATADIR_MSTORY3, 30), 0, 0);
    espPosSet(lbl_1_bss_1530.unk14, 288.0f, 110.0f);
    espDispOff(lbl_1_bss_1530.unk14);
    fn_1_1E28(arg0, 2, 2, 0, 2);
    fn_1_35C8(arg0->model[1]);
    fn_1_35C8(arg0->model[2]);
    fn_1_35C8(arg0->model[3]);
    arg0->model[20] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 31) + arg2);
    arg0->motion[20] = Hu3DMotionIDGet(arg0->model[20]);
    Hu3DModelPosSet(arg0->model[20], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[20], HU3D_ATTR_DISPOFF);
    fn_1_1E28(arg0, 20, 20, 0, 2);
    arg0->model[21] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 37));
    arg0->motion[21] = Hu3DMotionIDGet(arg0->model[21]);
    Hu3DModelPosSet(arg0->model[21], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[21], HU3D_ATTR_DISPOFF);
    fn_1_1E28(arg0, 21, 21, 0, 2);
    arg0->model[22] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 38));
    arg0->motion[22] = Hu3DMotionIDGet(arg0->model[22]);
    Hu3DModelPosSet(arg0->model[22], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[22], HU3D_ATTR_DISPOFF);
    fn_1_1E28(arg0, 22, 22, 0, 2);
    arg0->model[23] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 39));
    Hu3DModelPosSet(arg0->model[23], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[23], HU3D_ATTR_DISPOFF);
}

void fn_1_E160(omObjData* arg0) {
    s32 var_r28;
    s32 var_r29;
    s32 var_r31;

    if (lbl_1_bss_C0 == 0.0f) {
        return;
    }
    Hu3DGLightColorSet(lbl_1_bss_1580.unk1C, lbl_1_bss_1580.unk20, lbl_1_bss_1580.unk20, lbl_1_bss_1580.unk20, 0xFF);
    lbl_1_bss_1580.unk20++;
    if (lbl_1_bss_1580.unk20 >= 128) {
        lbl_1_bss_1580.unk20 = 128;
    }
    for (var_r31 = 1; var_r31 < 80; var_r31++) {
        switch (lbl_1_bss_C8[var_r31].unk00) {
            case 0:
                lbl_1_bss_C8[var_r31].unk30 = Hu3DData[arg0->model[var_r31]].pos.y = 450.0f + rand8() % 150;
                lbl_1_bss_C8[var_r31].unk00 = 1;
                break;
            case 3:
                lbl_1_bss_C8[var_r31].unk30 = Hu3DData[arg0->model[var_r31]].pos.y = 500.0f;
                /* fallthrough */
            case 1:
                if (var_r31 % 3 != 0) {
                    var_r28 = rand8() % 4;
                } else {
                    var_r28 = 5;
                }
                switch (var_r28) {
                    case 0:
                        Hu3DModelAmbSet(arg0->model[var_r31], 1.0f, 1.0f, 1.0f);
                        break;
                    case 1:
                        Hu3DModelAmbSet(arg0->model[var_r31], 1.0f, 0.0f, 0.0f);
                        break;
                    case 2:
                        Hu3DModelAmbSet(arg0->model[var_r31], 0.0f, 1.0f, 0.0f);
                        break;
                    case 3:
                        Hu3DModelAmbSet(arg0->model[var_r31], 0.0f, 0.0f, 1.0f);
                        break;
                    case 5:
                        break;
                }
                Hu3DModelAttrReset(arg0->model[var_r31], HU3D_ATTR_DISPOFF);
                if (lbl_1_bss_1580.unk344 == 0) {
                    lbl_1_bss_C8[var_r31].unk2C = Hu3DData[arg0->model[var_r31]].pos.x = -50.0f + lbl_1_bss_BC + rand8() % 100;
                } else {
                    lbl_1_bss_C8[var_r31].unk2C = Hu3DData[arg0->model[var_r31]].pos.x = -100.0f + lbl_1_bss_BC + rand8() % 200;
                }
                lbl_1_bss_C8[var_r31].unk34 = Hu3DData[arg0->model[var_r31]].pos.z = 460.0f;
                Hu3DData[arg0->model[var_r31]].rot.x = rand8();
                Hu3DData[arg0->model[var_r31]].rot.y = rand8();
                Hu3DData[arg0->model[var_r31]].rot.z = rand8();
                lbl_1_bss_C8[var_r31].unk20 = (rand8() % 50 + -1.0f) / 100.0f;
                if (var_r31 % 2 == 0) {
                    lbl_1_bss_C8[var_r31].unk20 *= -1.0f;
                }
                lbl_1_bss_C8[var_r31].unk24 = ((rand8() % 100 + 100) / 100.0f) * -1.0f;
                lbl_1_bss_C8[var_r31].unk28 = (rand8() % 100 - 1) / 100;
                lbl_1_bss_C8[var_r31].unk10 = (rand8() % 100 - 50) / 5;
                lbl_1_bss_C8[var_r31].unk14 = (rand8() % 100 - 50) / 5;
                lbl_1_bss_C8[var_r31].unk18 = (rand8() % 100 - 50) / 5;
                lbl_1_bss_C8[var_r31].unk00 = 2;
                break;
            case 2:
                if (lbl_1_bss_C8[var_r31].unk04-- <= 0) {
                    lbl_1_bss_C8[var_r31].unk04 = rand8() % 30 + 30;
                    lbl_1_bss_C8[var_r31].unk20 = (rand8() % 50 + -1.0f) / 100.0f;
                    if (var_r31 % 2 == 0) {
                        lbl_1_bss_C8[var_r31].unk20 *= -1.0f;
                    }
                    lbl_1_bss_C8[var_r31].unk24 = ((rand8() % 100 + 100) / 100.0f) *-1.0f;
                    lbl_1_bss_C8[var_r31].unk28 = (rand8() % 100 - 1) / 100;
                    lbl_1_bss_C8[var_r31].unk10 = (rand8() % 100 - 50) / 5;
                    lbl_1_bss_C8[var_r31].unk14 = (rand8() % 100 - 50) / 5;
                    lbl_1_bss_C8[var_r31].unk18 = (rand8() % 100 - 50) / 5;
                }
                lbl_1_bss_C8[var_r31].unk2C += lbl_1_bss_C8[var_r31].unk20;
                lbl_1_bss_C8[var_r31].unk30 += lbl_1_bss_C8[var_r31].unk24;
                lbl_1_bss_C8[var_r31].unk34 += lbl_1_bss_C8[var_r31].unk28;
                Hu3DData[arg0->model[var_r31]].rot.x += lbl_1_bss_C8[var_r31].unk10;
                Hu3DData[arg0->model[var_r31]].rot.y += lbl_1_bss_C8[var_r31].unk14;
                Hu3DData[arg0->model[var_r31]].rot.z += lbl_1_bss_C8[var_r31].unk18;
                if (Hu3DData[arg0->model[var_r31]].pos.y <= 0.0f) {
                    lbl_1_bss_C8[var_r31].unk00 = 3;
                }
                break;
            case 10:
                Hu3DModelAttrReset(arg0->model[var_r31], HU3D_ATTR_DISPOFF);
                if (var_r31 % 3 != 0) {
                    var_r28 = rand8() % 4;
                } else {
                    var_r28 = 5;
                }
                switch (var_r28) {
                    case 0:
                        Hu3DModelAmbSet(arg0->model[var_r31], 1.0f, 1.0f, 1.0f);
                        break;
                    case 1:
                        Hu3DModelAmbSet(arg0->model[var_r31], 1.0f, 0.0f, 0.0f);
                        break;
                    case 2:
                        Hu3DModelAmbSet(arg0->model[var_r31], 0.0f, 1.0f, 0.0f);
                        break;
                    case 3:
                        Hu3DModelAmbSet(arg0->model[var_r31], 0.0f, 0.0f, 1.0f);
                        break;
                    case 5:
                        break;
                }
                lbl_1_bss_C8[var_r31].unk2C = Hu3DData[arg0->model[var_r31]].pos.x = lbl_1_bss_BC;
                lbl_1_bss_C8[var_r31].unk30 = Hu3DData[arg0->model[var_r31]].pos.y = 375.0f;
                lbl_1_bss_C8[var_r31].unk34 = Hu3DData[arg0->model[var_r31]].pos.z = 460.0f;
                var_r29 = rand8();
                if (rand8() % 2 == 0) {
                    var_r29 *= -1;
                }
                lbl_1_bss_C8[var_r31].unk2C += var_r29;
                var_r29 = rand8();
                if (rand8() % 2 == 0) {
                    var_r29 *= -1;
                }
                lbl_1_bss_C8[var_r31].unk30 += var_r29;
                var_r29 = rand8() % 50;
                if (rand8() % 2 == 0) {
                    var_r29 *= -1;
                }
                lbl_1_bss_C8[var_r31].unk34 += var_r29;
                lbl_1_bss_C8[var_r31].unk20 = (rand8() % 50 + -1.0f) / 100.0f;
                if (var_r31 % 2 == 0) {
                    lbl_1_bss_C8[var_r31].unk20 *= -1.0f;
                }
                lbl_1_bss_C8[var_r31].unk24 = ((rand8() % 100 + 100) / 100.0f) * -1.0f;
                lbl_1_bss_C8[var_r31].unk28 = (rand8() % 100 - 1) / 100;
                lbl_1_bss_C8[var_r31].unk10 = (rand8() % 100 - 50) / 5;
                lbl_1_bss_C8[var_r31].unk14 = (rand8() % 100 - 50) / 5;
                lbl_1_bss_C8[var_r31].unk18 = (rand8() % 100 - 50) / 5;
                lbl_1_bss_C8[var_r31].unk08 = 0;
                lbl_1_bss_C8[var_r31].unk04 = rand8() % 30 + 30;
                lbl_1_bss_C8[var_r31].unk00 = 11;
                break;
            case 11:
                if (lbl_1_bss_C8[var_r31].unk04-- <= 0) {
                    lbl_1_bss_C8[var_r31].unk04 = rand8() % 30 + 30;
                    lbl_1_bss_C8[var_r31].unk20 = (rand8() % 50 + -1.0f) / 100.0f;
                    if (var_r31 % 2 == 0) {
                        lbl_1_bss_C8[var_r31].unk20 *= -1.0f;
                    }
                    lbl_1_bss_C8[var_r31].unk24 = ((rand8() % 100 + 100) / 100.0f) * -1.0f;
                    lbl_1_bss_C8[var_r31].unk28 = (rand8() % 100 - 1) / 100;
                    lbl_1_bss_C8[var_r31].unk10 = (rand8() % 100 - 50) / 5;
                    lbl_1_bss_C8[var_r31].unk14 = (rand8() % 100 - 50) / 5;
                    lbl_1_bss_C8[var_r31].unk18 = (rand8() % 100 - 50) / 5;
                }
                lbl_1_bss_C8[var_r31].unk2C += lbl_1_bss_C8[var_r31].unk20;
                lbl_1_bss_C8[var_r31].unk30 += lbl_1_bss_C8[var_r31].unk24 / 2;
                lbl_1_bss_C8[var_r31].unk34 += lbl_1_bss_C8[var_r31].unk28;
                Hu3DData[arg0->model[var_r31]].rot.x += lbl_1_bss_C8[var_r31].unk10;
                Hu3DData[arg0->model[var_r31]].rot.y += lbl_1_bss_C8[var_r31].unk14;
                Hu3DData[arg0->model[var_r31]].rot.z += lbl_1_bss_C8[var_r31].unk18;
                if (lbl_1_bss_C8[var_r31].unk08++ >= 50) {
                    lbl_1_bss_C8[var_r31].unk00 = 2;
                }
                break;
        }
        Hu3DData[arg0->model[var_r31]].pos.x = fn_1_5FC(Hu3DData[arg0->model[var_r31]].pos.x, lbl_1_bss_C8[var_r31].unk2C, 30.0f);
        Hu3DData[arg0->model[var_r31]].pos.y = fn_1_5FC(Hu3DData[arg0->model[var_r31]].pos.y, lbl_1_bss_C8[var_r31].unk30, 30.0f);
        Hu3DData[arg0->model[var_r31]].pos.z = fn_1_5FC(Hu3DData[arg0->model[var_r31]].pos.z, lbl_1_bss_C8[var_r31].unk34, 30.0f);
    }
}

void fn_1_FD30(omObjData* arg0) {
    s32 var_r30;

    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 17));
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 18));
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
    for (var_r30 = 2; var_r30 < 80; var_r30++) {
        if (var_r30 % 3 == 0) {
            arg0->model[var_r30] = Hu3DModelLink(arg0->model[1]);
        } else {
            arg0->model[var_r30] = Hu3DModelLink(arg0->model[0]);
        }
        Hu3DModelAttrSet(arg0->model[var_r30], HU3D_ATTR_DISPOFF);
        lbl_1_bss_C8[var_r30].unk04 = lbl_1_bss_C8[var_r30].unk08 = 0;
        lbl_1_bss_C8[var_r30].unk00 = 10;
    }
    arg0->func = fn_1_E160;
}

void fn_1_FE80(void) {
    omObjData* temp_r31;
    omObjData* sp8;

    temp_r31 = omAddObjEx(lbl_1_bss_A8, 0x100, 0x20, 0x20, -1, NULL);
    sp8 = omAddObjEx(lbl_1_bss_A8, 0x100, 0x80, 0, -1, fn_1_FD30);
    lbl_1_bss_1530.unk00 = temp_r31;
    lbl_1_bss_1530.unk04 = NULL;
    lbl_1_bss_1530.unk00->data = &lbl_1_bss_1530;
    fn_1_DB68(temp_r31, lbl_1_bss_1580.unk08, lbl_1_bss_1580.unk00);
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_1530.unk04 != NULL) {
            lbl_1_bss_1530.unk04(temp_r31);
        }
        fn_1_D7D8(temp_r31);
    }
}

void fn_1_FF7C(s32 arg0) {
    s32 sp30[4];
    s32 sp20[4];
    s32 sp10[4];
    s32 i, j;
    s32 var_r29;

    sp30[0] = 0;
    for (i = 1; i < 4; i++) {
        sp30[i] = sp30[i - 1] + 1;
        if (sp30[i] >= 4) {
            sp30[i] = 0;
        }
        if (arg0 == sp30[i]) {
            lbl_1_bss_1580.unk0C = i;
        }
    }
    if (lbl_1_bss_1580.unk08 != 0) {
        lbl_1_bss_1580.unk14 = arg0;
    }
    if (lbl_1_bss_1580.unk344 == 1) {
        var_r29 = 0;
        for (i = 0; i < 4; i++) {
            sp10[0] = GWPlayer[sp30[0]].team;
            sp10[1] = GWPlayer[sp30[1]].team;
            sp10[2] = GWPlayer[sp30[2]].team;
            sp10[3] = GWPlayer[sp30[3]].team;
            sp20[i] = sp30[i];
        }
        OSReport("########## Sort Start WIN:%d  IDX (%d,%d), (%d,%d), (%d,%d), (%d,%d)\n",
            var_r29, sp10[0], sp30[0], sp10[1], sp30[1], sp10[2], sp30[2], sp10[3], sp30[3]);
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (sp10[j] != -1 && var_r29 == sp10[j]) {
                    sp10[j] = -1;
                    sp30[i] = sp20[j];
                    break;
                }
            }
            if (i == 1) {
                var_r29++;
                var_r29 %= 2;
            }
        }
        OSReport("########## Sort End WIN:%d  IDX %d, %d, %d, %d\n", var_r29, sp30[0], sp30[1], sp30[2], sp30[3]);
    }
    for (i = 0; i < 4; i++) {
        fn_1_3650(&lbl_1_bss_1580.unkC4[i].unk00, sp30[i]);
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_1580.unkC4[i].unk00.unk1C = GWPlayer[sp30[i]].coins;
        lbl_1_bss_1580.unkC4[i].unk00.unk20 = GWPlayer[sp30[i]].stars;
        lbl_1_bss_1580.unkC4[i].unk00.unk24 = GWPlayer[sp30[i]].coins_mg;
        lbl_1_bss_1580.unkC4[i].unk00.unk28 = GWPlayer[sp30[i]].coins_max;
        lbl_1_bss_1580.unkC4[i].unk00.unk2C = GWPlayer[sp30[i]].question_count;
    }
}

void fn_1_1036C(omObjData* arg0) {
    float var_f29;
    float var_f30;
    float temp_f31;
    s32 temp_r25;
    s32 var_r26;
    s32 var_r27 = 3;
    StructBss1530* temp_r30 = arg0->data;
    char* sp98[][3] = {
        { "submit07-star_null3", "submit07-star_null1", "submit07-star_null1" },
        { "submit07-star_null4", "submit07-star_null2", "submit07-star_null1" },
        { "submit07-star_null5", "submit07-star_null3", "submit07-star_null1" }
    };
    Mtx sp68;
    Mtx sp38;
    Mtx sp8;
    s32 var_r28;
    s32 var_r29;

    Hu3DModelPosSet(arg0->model[3], lbl_1_data_130[temp_r30->unk08].x, 100.0f, lbl_1_data_130[temp_r30->unk08].z - 20.0f);
    Hu3DModelRotSet(arg0->model[3], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[3], 0.0f, 0.0f, 0.0f);
    if ((temp_r25 = lbl_1_bss_1580.unkC4[temp_r30->unk08].unk00.unk20 / 100) == 0) {
        var_r27 = 2;
    } else {
        Hu3DMotionTimeSet(arg0->model[9], (temp_r25 + 1) % 10);
    }
    if ((temp_r25 = (lbl_1_bss_1580.unkC4[temp_r30->unk08].unk00.unk20 % 100) / 10) == 0 && var_r27 == 2) {
        var_r27 = 1;
    } else {
        Hu3DMotionTimeSet(arg0->model[8], (temp_r25 + 1) % 10);
    }
    temp_r25 = lbl_1_bss_1580.unkC4[temp_r30->unk08].unk00.unk20 % 10;
    Hu3DMotionTimeSet(arg0->model[7], (temp_r25 + 1) % 10);
    Hu3DModelAttrReset(arg0->model[3], HU3D_ATTR_DISPOFF);
    for (var_r28 = 0; var_r28 < 90; var_r28++) {
        fn_1_938();
        var_f29 = fn_1_6F4(100.0f, 300.0f, var_r28, 90.0f);
        var_f30 = fn_1_6F4(0.0f, 1080.0f, var_r28, 90.0f);
        temp_f31 = fn_1_6F4(0.0f, 0.75f, var_r28, 90.0f);
        Hu3DModelPosSet(arg0->model[3], lbl_1_data_130[temp_r30->unk08].x, var_f29, lbl_1_data_130[temp_r30->unk08].z - 20.0f);
        Hu3DModelRotSet(arg0->model[3], 0.0f, var_f30, 0.0f);
        Hu3DModelScaleSet(arg0->model[3], temp_f31, temp_f31, temp_f31);
        for (var_r29 = 0; var_r29 < var_r27; var_r29++) {
            if (var_f30 >= 900.0f) {
                Hu3DModelAttrReset(arg0->model[var_r29 + 7], HU3D_ATTR_DISPOFF);
            }
            Hu3DModelObjMtxGet(arg0->model[3], sp98[var_r27 - 1][var_r29], sp68);
            Hu3DModelPosSet(arg0->model[var_r29 + 7], sp68[0][3], sp68[1][3], sp68[2][3]);
            Hu3DModelRotSet(arg0->model[var_r29 + 7], 0.0f, var_f30, 0.0f);
            Hu3DModelScaleSet(arg0->model[var_r29 + 7], temp_f31, temp_f31, temp_f31);
        }
    }
    var_r28 = var_r29 = var_r26 = 0;
    if (temp_r30->unk1C == 1) {
        fn_1_1E28(arg0, 1, 14, 5, 0);
    } else {
        fn_1_1E28(arg0, 1, 15, 5, 0);
    }
    do {
        fn_1_938();
        if (temp_r30->unk1C == 1) {
            temp_f31 = fn_1_878(0.75f, 1.0f, var_r26, 30.0f);
            if (var_r26++ >= 29) {
                var_r26 = 0;
            }
            Hu3DModelScaleSet(arg0->model[3], temp_f31, temp_f31, temp_f31);
            for (var_r29 = 0; var_r29 < var_r27; var_r29++) {
                Hu3DModelObjMtxGet(arg0->model[3], sp98[var_r27 - 1][var_r29], sp38);
                Hu3DModelPosSet(arg0->model[var_r29 + 7], sp38[0][3], sp38[1][3], sp38[2][3]);
                Hu3DModelRotSet(arg0->model[var_r29 + 7], 0.0f, var_f30, 0.0f);
                Hu3DModelScaleSet(arg0->model[var_r29 + 7], temp_f31, temp_f31, temp_f31);
            }
        }
        if (var_r28 == 60) {
            fn_1_1E28(arg0, 1, 1, 15, 1);
        }
        if (var_r28 == 120) {
            lbl_1_bss_1580.unk18 = 1;
        }
        if (var_r28++ >= 120 && (var_r26 == 0 || var_r26 == 15) && temp_r30->unk18 == 1) {
            temp_r30->unk18 = 2;
        }
    } while (temp_r30->unk18 != 3);
    HuAudFXPlay(0xBB);
    for (var_r28 = 0; var_r28 < 60; var_r28++) {
        fn_1_938();
        if (var_r28 > 30) {
            var_f29 = fn_1_61C(300.0f, 600.0f, var_r28 - 30, 30.0f);
        }
        var_f30 = fn_1_61C(0.0f, 360.0f, var_r28, 60.0f);
        Hu3DModelPosSet(arg0->model[3], lbl_1_data_130[temp_r30->unk08].x, var_f29, lbl_1_data_130[temp_r30->unk08].z - 20.0f);
        Hu3DModelRotSet(arg0->model[3], 0.0f, var_f30, 0.0f);
        for (var_r29 = 0; var_r29 < var_r27; var_r29++) {
            if (var_f30 >= 180.0f) {
                Hu3DModelAttrSet(arg0->model[var_r29 + 7], HU3D_ATTR_DISPOFF);
            }
            Hu3DModelObjMtxGet(arg0->model[3], sp98[var_r27 - 1][var_r29], sp8);
            Hu3DModelPosSet(arg0->model[var_r29 + 7], sp8[0][3], sp8[1][3], sp8[2][3]);
            Hu3DModelRotSet(arg0->model[var_r29 + 7], 0.0f, var_f30, 0.0f);
        }
    }
    Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF);
    for (var_r28 = 0; var_r28 < 3; var_r28++) {
        Hu3DModelAttrSet(arg0->model[var_r28 + 7], HU3D_ATTR_DISPOFF);
    }
    temp_r30->unk04 = 0;
}

void fn_1_10D74(omObjData* arg0) {
    float var_f29;
    float var_f30;
    float temp_f31;
    s32 temp_r25;
    s32 var_r26;
    s32 var_r27 = 3;
    StructBss1530* temp_r30 = arg0->data;
    char* sp98[][3] = {
        { "coin-coin-null3", "coin-coin_null1", "coin-coin-null1" },
        { "coin-coin-null4", "coin-coin-null2", "coin-coin-null1" },
        { "coin-coin-null5", "coin-coin-null3", "coin-coin-null1" }
    };
    Mtx sp68;
    Mtx sp38;
    Mtx sp8;
    s32 var_r28;
    s32 var_r29;

    Hu3DModelPosSet(arg0->model[4], lbl_1_data_130[temp_r30->unk08].x, 100.0f, lbl_1_data_130[temp_r30->unk08].z - 20.0f);
    Hu3DModelRotSet(arg0->model[4], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[4], 0.0f, 0.0f, 0.0f);
    if ((temp_r25 = lbl_1_bss_1580.unkC4[temp_r30->unk08].unk00.unk1C / 100) == 0) {
        var_r27 = 2;
    } else {
        Hu3DMotionTimeSet(arg0->model[9], (temp_r25 + 1) % 10);
    }
    if ((temp_r25 = (lbl_1_bss_1580.unkC4[temp_r30->unk08].unk00.unk1C % 100) / 10) == 0 && var_r27 == 2) {
        var_r27 = 1;
    } else {
        Hu3DMotionTimeSet(arg0->model[8], (temp_r25 + 1) % 10);
    }
    temp_r25 = lbl_1_bss_1580.unkC4[temp_r30->unk08].unk00.unk1C % 10;
    Hu3DMotionTimeSet(arg0->model[7], (temp_r25 + 1) % 10);
    Hu3DModelAttrReset(arg0->model[4], HU3D_ATTR_DISPOFF);
    for (var_r28 = 0; var_r28 < 90; var_r28++) {
        fn_1_938();
        var_f29 = fn_1_6F4(100.0f, 300.0f, var_r28, 90.0f);
        var_f30 = fn_1_6F4(0.0f, 1080.0f, var_r28, 90.0f);
        temp_f31 = fn_1_6F4(0.0f, 0.75f, var_r28, 90.0f);
        Hu3DModelPosSet(arg0->model[4], lbl_1_data_130[temp_r30->unk08].x, var_f29, lbl_1_data_130[temp_r30->unk08].z - 20.0f);
        Hu3DModelRotSet(arg0->model[4], 0.0f, var_f30, 0.0f);
        Hu3DModelScaleSet(arg0->model[4], temp_f31, temp_f31, temp_f31);
        for (var_r29 = 0; var_r29 < var_r27; var_r29++) {
            if (var_f30 >= 900.0f) {
                Hu3DModelAttrReset(arg0->model[var_r29 + 7], HU3D_ATTR_DISPOFF);
            }
            Hu3DModelObjMtxGet(arg0->model[4], sp98[var_r27 - 1][var_r29], sp68);
            Hu3DModelPosSet(arg0->model[var_r29 + 7], sp68[0][3], sp68[1][3], sp68[2][3]);
            Hu3DModelRotSet(arg0->model[var_r29 + 7], 0.0f, var_f30, 0.0f);
            Hu3DModelScaleSet(arg0->model[var_r29 + 7], temp_f31, temp_f31, temp_f31);
        }
    }
    var_r28 = var_r29 = var_r26 = 0;
    if (temp_r30->unk1C == 1) {
        fn_1_1E28(arg0, 1, 14, 5, 0);
    } else {
        fn_1_1E28(arg0, 1, 15, 5, 0);
    }
    do {
        fn_1_938();
        if (temp_r30->unk1C == 1) {
            temp_f31 = fn_1_878(0.75f, 1.0f, var_r26, 30.0f);
            if (var_r26++ >= 29) {
                var_r26 = 0;
            }
            Hu3DModelScaleSet(arg0->model[4], temp_f31, temp_f31, temp_f31);
            for (var_r29 = 0; var_r29 < var_r27; var_r29++) {
                Hu3DModelObjMtxGet(arg0->model[4], sp98[var_r27 - 1][var_r29], sp38);
                Hu3DModelPosSet(arg0->model[var_r29 + 7], sp38[0][3], sp38[1][3], sp38[2][3]);
                Hu3DModelRotSet(arg0->model[var_r29 + 7], 0.0f, var_f30, 0.0f);
                Hu3DModelScaleSet(arg0->model[var_r29 + 7], temp_f31, temp_f31, temp_f31);
            }
        }
        if (var_r28 == 60) {
            fn_1_1E28(arg0, 1, 1, 15, 1);
        }
        if (var_r28 == 120) {
            lbl_1_bss_1580.unk18 = 1;
        }
        if (var_r28++ >= 120 && (var_r26 == 0 || var_r26 == 15) && temp_r30->unk18 == 1) {
            temp_r30->unk18 = 2;
        }
    } while (temp_r30->unk18 != 3);
    fn_1_1E28(arg0, 1, 1, 15, 1);
    HuAudFXPlay(0xBC);
    for (var_r28 = 0; var_r28 < 60; var_r28++) {
        fn_1_938();
        if (var_r28 > 30) {
            var_f29 = fn_1_61C(300.0f, 600.0f, var_r28 - 30, 30.0f);
        }
        var_f30 = fn_1_61C(0.0f, 360.0f, var_r28, 60.0f);
        Hu3DModelPosSet(arg0->model[4], lbl_1_data_130[temp_r30->unk08].x, var_f29, lbl_1_data_130[temp_r30->unk08].z - 20.0f);
        Hu3DModelRotSet(arg0->model[4], 0.0f, var_f30, 0.0f);
        for (var_r29 = 0; var_r29 < var_r27; var_r29++) {
            if (var_f30 >= 180.0f) {
                Hu3DModelAttrSet(arg0->model[var_r29 + 7], HU3D_ATTR_DISPOFF);
            }
            Hu3DModelObjMtxGet(arg0->model[4], sp98[var_r27 - 1][var_r29], sp8);
            Hu3DModelPosSet(arg0->model[var_r29 + 7], sp8[0][3], sp8[1][3], sp8[2][3]);
            Hu3DModelRotSet(arg0->model[var_r29 + 7], 0.0f, var_f30, 0.0f);
        }
    }
    Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF);
    for (var_r28 = 0; var_r28 < 3; var_r28++) {
        Hu3DModelAttrSet(arg0->model[var_r28 + 7], HU3D_ATTR_DISPOFF);
    }
    temp_r30->unk04 = 0;
}

void fn_1_11794(omObjData* arg0) {
    StructBss1530* temp_r30;

    temp_r30 = arg0->data;
    fn_1_958(25);
    fn_1_1E28(arg0, 1, 15, 5, 0);
    fn_1_958(10);
    while (TRUE) {
        fn_1_938();
        if (Hu3DMotionTimeGet(arg0->model[1]) >= 40.0f) {
            break;
        }
    }
    Hu3DModelAttrSet(arg0->model[1], HU3D_MOTATTR_PAUSE);
    temp_r30->unk04 = 0;
}

void fn_1_11834(omObjData* arg0) {
    float var_f31;
    float var_f30;
    float temp_f26;
    float temp_f27;
    float temp_f25;
    float temp_f29;
    float temp_f28;
    StructBss1530* temp_r31;
    s32 temp_r29;
    s32 var_r24;
    s32 temp_r23;
    s32 var_r27;
    s32 temp_r25;
    s32 var_r28;

    var_f30 = 0.0f;
    temp_r31 = arg0->data;
    temp_r29 = temp_r31->unk08;
    temp_r23 = lbl_1_bss_1490[temp_r29].unk00->work[0];
    var_r24 = 0xFF;
    Hu3DModelPosSet(lbl_1_bss_1490[temp_r29].unk00->model[6], lbl_1_data_130[temp_r29].x, 500.0f + lbl_1_data_130[temp_r29].y + lbl_1_bss_AC, lbl_1_data_130[temp_r29].z + 0.1f * lbl_1_bss_AC);
    Hu3DModelScaleSet(lbl_1_bss_1490[temp_r29].unk00->model[6], 0.0f, 1.25f, 0.0f);
    Hu3DModelTPLvlSet(lbl_1_bss_1490[temp_r29].unk00->model[6], 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_1490[temp_r29].unk00->model[6], HU3D_ATTR_DISPOFF);
    for (var_r27 = 0; var_r27 <= 5; var_r27++) {
        fn_1_938();
        lbl_1_bss_1490[temp_r29].unk00->work[0] = fn_1_6F4(temp_r23, var_r24, var_r27, 5.0f);
        temp_f27 = fn_1_6F4(0.0f, 1.5f, var_r27, 5.0f);
        temp_f25 = fn_1_6F4(0.0f, 0.5f, var_r27, 5.0f);
        temp_r25 = fn_1_6F4(0.0f, 128.0f, var_r27, 5.0f);
        Hu3DModelScaleSet(lbl_1_bss_1490[temp_r29].unk00->model[6], temp_f27, 1.25f, temp_f27);
        Hu3DModelTPLvlSet(lbl_1_bss_1490[temp_r29].unk00->model[6], temp_f25);
        Hu3DLLightColorSet(lbl_1_bss_1490[temp_r29].unk00->model[1], lbl_1_bss_1580.unk24[temp_r29].unk00, temp_r25, temp_r25, temp_r25, 0xFF);
        Hu3DLLightColorSet(lbl_1_bss_1490[temp_r29].unk00->model[2], lbl_1_bss_1580.unk24[temp_r29].unk04, temp_r25, temp_r25, temp_r25, 0xFF);
    }
    lbl_1_bss_1490[temp_r29].unk00->work[1] = 1;
    fn_1_958(20);
    fn_1_1E28(arg0, 1, 3, 15, 0);
    fn_1_2310(arg0, 1, 3, 15);
    do {
        fn_1_938();
    } while (temp_r31->unk18 == 0);
    Hu3DModelPosSet(arg0->model[5], lbl_1_data_130[temp_r31->unk08].x, 300.0f, lbl_1_data_130[temp_r31->unk08].z - 50.0f);
    Hu3DModelRotSet(arg0->model[5], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[5], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(arg0->model[5], HU3D_ATTR_DISPOFF);
    HuAudFXPlay(0x338);
    for (var_r28 = 0; var_r28 < 60; var_r28++) {
        fn_1_938();
        temp_f29 = 10.0 + 10.0 * sind(var_f30);
        temp_f28 = 10.0 * sind(2.0f * var_f30);
        if (var_r28 < 10) {
            var_f31 = fn_1_61C(0.0f, 1.0f, var_r28, 10.0f);
        } else {
            var_f31 = fn_1_61C(1.0f, 0.5f, var_r28 - 10, 5.0f);
        }
        if (var_r28 == 10) {
            lbl_1_bss_1580.unk334[temp_r31->unk08] = fn_1_8264();
            Hu3DParManPosSet(lbl_1_bss_1580.unk334[temp_r31->unk08], lbl_1_data_130[temp_r31->unk08].x, 300.0f + temp_f29, lbl_1_data_130[temp_r31->unk08].z);
        }
        if ((var_f30 += 2.0f) >= 360.0f) {
            var_f30 -= 360.0f;
        }
        Hu3DModelPosSet(arg0->model[5], lbl_1_data_130[temp_r31->unk08].x, 300.0f + temp_f29, lbl_1_data_130[temp_r31->unk08].z - 50.0f);
        Hu3DModelRotSet(arg0->model[5], 0.0f, temp_f28, 0.0f);
        Hu3DModelScaleSet(arg0->model[5], var_f31, var_f31, var_f31);
    }
    Hu3DParManKill(lbl_1_bss_1580.unk334[temp_r31->unk08]);
    lbl_1_bss_1580.unk334[temp_r31->unk08] = -1;
    temp_f29 = Hu3DData[arg0->model[5]].pos.y;
    temp_f26 = temp_f29;
    temp_f28 = Hu3DData[arg0->model[5]].rot.y;
    var_f31 = 0.5f;
    var_f30 = 0.0f;
    for (var_r28 = 0; var_r28 < 90; var_r28++) {
        fn_1_938();
        if (var_r28 == 45) {
            HuAudFXPlay(0x339);
        }
        if (var_r28 > 45) {
            temp_f29 = fn_1_61C(temp_f26, 100.0f, var_r28 - 45, 45.0f);
            var_f31 = fn_1_61C(0.5f, 0.0f, var_r28 - 45, 45.0f);
        }
        temp_f28 += var_f30 += 0.25f;
        Hu3DModelPosSet(arg0->model[5], lbl_1_data_130[temp_r31->unk08].x, temp_f29, lbl_1_data_130[temp_r31->unk08].z - 50.0f);
        Hu3DModelRotSet(arg0->model[5], 0.0f, temp_f28, 0.0f);
        Hu3DModelScaleSet(arg0->model[5], var_f31, var_f31, var_f31);
    }
    Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF);
    HuAudFXPlay(8);
    lbl_1_bss_1580.unkC4[temp_r31->unk08].unk00.unk20++;
    GWPlayer[lbl_1_bss_1580.unkC4[temp_r31->unk08].unk00.unk00].stars++;
    if (GWPlayer[lbl_1_bss_1580.unkC4[temp_r31->unk08].unk00.unk00].stars >= 999) {
        GWPlayer[lbl_1_bss_1580.unkC4[temp_r31->unk08].unk00.unk00].stars = 999;
    }
    temp_r31->unk04 = 0;
}

void fn_1_123D8(omObjData* arg0) {
    StructBss1530* temp_r31;

    temp_r31 = arg0->data;
    fn_1_15450(temp_r31->unk08);
    temp_r31->unk04 = 0;
}

void fn_1_1241C(omObjData* arg0) {
}

void fn_1_12420(omObjData* arg0) {
    float sp8[] = { 0.0f, -30.0f, -60.0f, -90.0f };
    float temp_f31;
    StructBss1530* temp_r31;
    s32 var_r27;
    s32 var_r29;
    s32 var_r28;

    temp_r31 = arg0->data;
    if (lbl_1_bss_1580.unk344 == 1) {
        var_r27 = 0;
        if (lbl_1_bss_1580.unk348 == 1) {
            var_r27 = 2;
        }
        if ((lbl_1_bss_1580.unk348 == 0 && temp_r31->unk08 <= 1) || (lbl_1_bss_1580.unk348 == 1 && temp_r31->unk08 >= 2)) {
            Hu3DModelPosSet(arg0->model[2], 100.0f + lbl_1_data_130[temp_r31->unk08].x, -90.0f, lbl_1_data_130[temp_r31->unk08].z);
            fn_1_958(90);
            if (temp_r31->unk08 == var_r27) {
                Hu3DModelAttrReset(arg0->model[2], HU3D_ATTR_DISPOFF);
            }
            if (arg0->work[0] == 0) {
                HuAudFXPlay(0xA8);
            }
            for (var_r28 = 0; var_r28 <= 30; var_r28++) {
                fn_1_938();
                temp_f31 = fn_1_6F4(-90.0f, 0.0f, var_r28, 30.0f);
                Hu3DModelPosSet(arg0->model[1], lbl_1_data_130[temp_r31->unk08].x, 90.0f + temp_f31, lbl_1_data_130[temp_r31->unk08].z - 20.0f);
                Hu3DModelPosSet(arg0->model[2], 100.0f + lbl_1_data_130[temp_r31->unk08].x, temp_f31, lbl_1_data_130[temp_r31->unk08].z - 20.0f);
            }
        }
    } else {
        Hu3DModelPosSet(arg0->model[2], lbl_1_data_130[temp_r31->unk08].x, -90.0f, lbl_1_data_130[temp_r31->unk08].z);
        if (lbl_1_bss_1580.unkC4[temp_r31->unk08].unk00.unk18 != 4) {
        }
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if (arg0->work[0] == 0 && var_r29 >= 1) {
                HuAudFXPlay(0xA5 + var_r29);
            }
            if (var_r29 != 3) {
                for (var_r28 = 0; var_r28 < 30; var_r28++) {
                    fn_1_938();
                    if (sp8[lbl_1_bss_1580.unkC4[temp_r31->unk08].unk00.unk18 - 1] >= sp8[3 - var_r29] && 4 - var_r29 < 4) {
                        temp_f31 = fn_1_6F4(sp8[4 - var_r29], sp8[3 - var_r29], var_r28, 30.0f);
                        if (var_r29 == 1) {
                            Hu3DModelAttrReset(arg0->model[2], HU3D_ATTR_DISPOFF);
                        }
                        Hu3DModelPosSet(arg0->model[1], lbl_1_data_130[temp_r31->unk08].x, 90.0f + temp_f31, lbl_1_data_130[temp_r31->unk08].z - 20.0f);
                        Hu3DModelPosSet(arg0->model[2], lbl_1_data_130[temp_r31->unk08].x, temp_f31, lbl_1_data_130[temp_r31->unk08].z - 20.0f);
                    }
                }
            } else {
                for (var_r28 = 0; var_r28 < 10; var_r28++) {
                    fn_1_938();
                    if ((sp8[lbl_1_bss_1580.unkC4[temp_r31->unk08].unk00.unk18 - 1] >= sp8[3 - var_r29]) && ((4 - var_r29) < 4)) {
                        temp_f31 = fn_1_6F4(sp8[4 - var_r29], sp8[3 - var_r29], var_r28, 10.0f);
                        if (var_r29 == 1) {
                            Hu3DModelAttrReset(arg0->model[2], HU3D_ATTR_DISPOFF);
                        }
                        Hu3DModelPosSet(arg0->model[1], lbl_1_data_130[temp_r31->unk08].x, 90.0f + temp_f31, lbl_1_data_130[temp_r31->unk08].z - 20.0f);
                        Hu3DModelPosSet(arg0->model[2], lbl_1_data_130[temp_r31->unk08].x, temp_f31, lbl_1_data_130[temp_r31->unk08].z - 20.0f);
                    }
                }
            }
            if (var_r29 == 2) {
                fn_1_958(120);
            } else if (var_r29 != 3) {
                fn_1_958(60);
            }
        }
    }
    temp_r31->unk04 = 0;
}

void fn_1_12A98(s32 arg0) {
    s32 sp8[4];
    s32 var_r29;
    s32 var_r30;
    s32 i;

    var_r29 = 0;
    var_r30 = -1;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_1458[i] = lbl_1_bss_1448[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        switch (arg0) {
            case 0:
                sp8[i] = lbl_1_bss_1580.unkC4[i].unk00.unk20;
                break;
            case 1:
                sp8[i] = lbl_1_bss_1580.unkC4[i].unk00.unk1C;
                break;
        }
    }
    for (i = 0; i < 4; i++) {
        if (var_r30 <= sp8[i]) {
            var_r30 = sp8[i];
        }
    }
    for (i = 0; i < 4; i++) {
        if (var_r30 == sp8[i]) {
            lbl_1_bss_1458[0]++;
            lbl_1_bss_1448[var_r29++] = i;
        }
    }
}

void fn_1_12C08(s32 arg0) {
    s32 sp8[4];
    s32 var_r29;
    s32 var_r30;
    s32 i;

    var_r29 = 0;
    var_r30 = -1;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_1458[i] = 0;
        lbl_1_bss_1448[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        switch (arg0) {
            case 0:
                sp8[i] = lbl_1_bss_1580.unkC4[i].unk00.unk24;
                break;
            case 1:
                sp8[i] = lbl_1_bss_1580.unkC4[i].unk00.unk28;
                break;
            case 2:
                sp8[i] = lbl_1_bss_1580.unkC4[i].unk00.unk2C;
                break;
        }
    }
    for (i = 0; i < 4; i++) {
        if (var_r30 <= sp8[i]) {
            var_r30 = sp8[i];
        }
    }
    for (i = 0; i < 4; i++) {
        if (var_r30 == sp8[i]) {
            lbl_1_bss_1458[0]++;
            lbl_1_bss_1448[var_r29++] = i;
        }
    }
}

void fn_1_12DAC(void) {
    s32 sp8[4];
    s32 var_r29;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        sp8[i] = i;
    }
    for (i = 0; i < 4; i++) {
        for (j = i; j < 4; j++) {
            if (lbl_1_bss_1580.unkC4[sp8[j]].unk00.unk20 >= lbl_1_bss_1580.unkC4[sp8[i]].unk00.unk20) {
                var_r29 = sp8[i];
                sp8[i] = sp8[j];
                sp8[j] = var_r29;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = i; j < 4; j++) {
            if ((lbl_1_bss_1580.unkC4[sp8[j]].unk00.unk20 == lbl_1_bss_1580.unkC4[sp8[i]].unk00.unk20) && (lbl_1_bss_1580.unkC4[sp8[j]].unk00.unk1C >= lbl_1_bss_1580.unkC4[sp8[i]].unk00.unk1C)) {
                var_r29 = sp8[i];
                sp8[i] = sp8[j];
                sp8[j] = var_r29;
            }
        }
    }
    lbl_1_bss_1580.unkC4[sp8[0]].unk00.unk18 = j = 1;
    for (i = 1; i < 4; i++) {
        j++;
        lbl_1_bss_1580.unkC4[sp8[i]].unk00.unk18 = j;
        if ((lbl_1_bss_1580.unkC4[sp8[i]].unk00.unk20 == lbl_1_bss_1580.unkC4[sp8[i - 1]].unk00.unk20) && (lbl_1_bss_1580.unkC4[sp8[i]].unk00.unk1C == lbl_1_bss_1580.unkC4[sp8[i - 1]].unk00.unk1C)) {
            lbl_1_bss_1580.unkC4[sp8[i]].unk00.unk18 = lbl_1_bss_1580.unkC4[sp8[i - 1]].unk00.unk18;
        }
    }
}

void fn_1_130A8(void) {
    s32 var_r30;
    s32 i;

    var_r30 = 0;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_1458[i] = lbl_1_bss_1448[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_1580.unkC4[i].unk00.unk18 == 1) {
            lbl_1_bss_1458[0]++;
            lbl_1_bss_1448[var_r30++] = i;
            lbl_1_bss_1458[1] = i;
        }
    }
}

void fn_1_1317C(void) {
    s32 sp8[4];
    s32 var_r30;
    s32 i;

    var_r30 = -1;
    for (i = 0; i < 4; i++) {
        sp8[i] = lbl_1_bss_1428[i];
    }
    for (i = 0; i < 4; i++) {
        if (var_r30 <= sp8[i]) {
            var_r30 = sp8[i];
        }
    }
    for (i = 0; i < 4; i++) {
        if (var_r30 == sp8[i]) {
            lbl_1_bss_1458[1] = i;
        }
    }
    for (i = 0; i < lbl_1_bss_1458[0]; i++) {
        if (lbl_1_bss_1458[1] != lbl_1_bss_1448[i]) {
            lbl_1_bss_1580.unkC4[lbl_1_bss_1448[i]].unk00.unk18 = 2;
        }
    }
}

void fn_1_132AC(omObjData* arg0, s32 arg1) {
    StructFn352C* temp_r30;
    s32 var_r28;

    temp_r30 = &lbl_1_bss_1580.unkC4[arg1].unk00;
    arg0->model[1] = CharModelCreate(temp_r30->unk10, 4);
    arg0->motion[1] = CharModelMotionCreate(temp_r30->unk10, DATA_MAKE_NUM(DATADIR_MARIOMOT, 0));
    arg0->motion[2] = CharModelMotionCreate(temp_r30->unk10, DATA_MAKE_NUM(DATADIR_MARIOMOT, 72));
    arg0->motion[5] = CharModelMotionCreate(temp_r30->unk10, DATA_MAKE_NUM(DATADIR_MARIOMOT, 47));
    arg0->motion[3] = CharModelMotionCreate(temp_r30->unk10, DATA_MAKE_NUM(DATADIR_MARIOMOT, 23));
    arg0->motion[4] = CharModelMotionCreate(temp_r30->unk10, DATA_MAKE_NUM(DATADIR_MARIOMOT, 24));
    arg0->motion[14] = CharModelMotionCreate(temp_r30->unk10, DATA_MAKE_NUM(DATADIR_MARIOMOT, 72));
    arg0->motion[15] = CharModelMotionCreate(temp_r30->unk10, DATA_MAKE_NUM(DATADIR_MARIOMOT, 73));
    CharModelMotionDataClose(temp_r30->unk10);
    Hu3DModelPosSet(arg0->model[1], lbl_1_data_130[arg1].x, lbl_1_data_130[arg1].y, lbl_1_data_130[arg1].z - 20.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
    Hu3DModelShadowSet(arg0->model[1]);
    fn_1_1E28(arg0, 1, 1, 0, 1);
    if (lbl_1_bss_1580.unk344 == 1) {
        var_r28 = 0;
        if (arg1 > 1) {
            var_r28 = 1;
        }
        arg0->model[2] = Hu3DModelCreateFile(var_r28 + DATA_MAKE_NUM(DATADIR_MSTORY3, 144));
        Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
        Hu3DModelScaleSet(arg0->model[2], 1.25f, 1.0f, 1.5f);
        Hu3DModelShadowMapSet(arg0->model[2]);
    } else {
        arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 12));
        Hu3DModelScaleSet(arg0->model[2], 1.5f, 1.0f, 1.5f);
        Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
        Hu3DModelShadowMapSet(arg0->model[2]);
    }
    arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 14));
    Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF);
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 15));
    Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF);
    arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 13));
    Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF);
    arg0->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 11));
    Hu3DModelAttrSet(arg0->model[6], HU3D_ATTR_DISPOFF);
    for (arg1 = 0; arg1 < 3; arg1++) {
        arg0->model[arg1 + 7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 16));
        Hu3DModelAttrSet(arg0->model[arg1 + 7], HU3D_ATTR_DISPOFF);
        Hu3DMotionSpeedSet(arg0->model[arg1 + 7], 0.0f);
    }
    lbl_1_bss_1580.unk24[arg1].unk00 = Hu3DLLightCreate(arg0->model[1], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DLLightInfinitytSet(arg0->model[1], lbl_1_bss_1580.unk24[arg1].unk00);
    Hu3DLLightPosAimSet(arg0->model[1], lbl_1_bss_1580.unk24[arg1].unk00, 0.0f, 700.0f, 1200.0f, 0.0f, 0.0f, 640.0f);
    lbl_1_bss_1580.unk24[arg1].unk04 = Hu3DLLightCreate(arg0->model[2], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DLLightInfinitytSet(arg0->model[2], lbl_1_bss_1580.unk24[arg1].unk04);
    Hu3DLLightPosAimSet(arg0->model[2], lbl_1_bss_1580.unk24[arg1].unk04, 0.0f, 700.0f, 1200.0f, 0.0f, 0.0f, 640.0f);
}

void fn_1_13908(void) {
    omObjData* var_r30;
    s32 temp_r31;

    temp_r31 = lbl_1_bss_1580.unk314++;
    var_r30 = omAddObjEx(lbl_1_bss_A8, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_1490[temp_r31].unk00 = var_r30;
    lbl_1_bss_1490[temp_r31].unk04 = NULL;
    lbl_1_bss_1490[temp_r31].unk08 = temp_r31;
    lbl_1_bss_1490[temp_r31].unk00->data = &lbl_1_bss_1490[temp_r31];
    fn_1_132AC(lbl_1_bss_1490[temp_r31].unk00, temp_r31);
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_1490[temp_r31].unk04 != NULL) {
            lbl_1_bss_1490[temp_r31].unk04(lbl_1_bss_1490[temp_r31].unk00);
        }
    }
}

void fn_1_13A38(omObjData* arg0) {
}

s32 lbl_1_data_504[][27] = {
    {
        MAKE_MESSID(37, 0x00), MAKE_MESSID(37, 0x01), MAKE_MESSID(37, 0x02),
        MAKE_MESSID(37, 0x03), MAKE_MESSID(37, 0x05), MAKE_MESSID(37, 0x06),
        MAKE_MESSID(37, 0x0B), MAKE_MESSID(37, 0x0C), MAKE_MESSID(37, 0x0D),
        MAKE_MESSID(37, 0x0E), MAKE_MESSID(37, 0x0F), MAKE_MESSID(37, 0x10),
        MAKE_MESSID(37, 0x07), MAKE_MESSID(37, 0x08), MAKE_MESSID(37, 0x09),
        MAKE_MESSID(37, 0x0A), MAKE_MESSID(37, 0x11), MAKE_MESSID(37, 0x12),
        MAKE_MESSID(37, 0x13), MAKE_MESSID(37, 0x14), MAKE_MESSID(37, 0x15),
        MAKE_MESSID(37, 0x16), MAKE_MESSID(37, 0x17), MAKE_MESSID(37, 0x8C),
        MAKE_MESSID(37, 0x8D), MAKE_MESSID(37, 0x8E), MAKE_MESSID(37, 0x9E)
    },
    {
        MAKE_MESSID(37, 0x19), MAKE_MESSID(37, 0x1A), MAKE_MESSID(37, 0x1B),
        MAKE_MESSID(37, 0x1C), MAKE_MESSID(37, 0x1D), MAKE_MESSID(37, 0x1E),
        MAKE_MESSID(37, 0x23), MAKE_MESSID(37, 0x24), MAKE_MESSID(37, 0x25),
        MAKE_MESSID(37, 0x26), MAKE_MESSID(37, 0x27), MAKE_MESSID(37, 0x28),
        MAKE_MESSID(37, 0x1F), MAKE_MESSID(37, 0x20), MAKE_MESSID(37, 0x21),
        MAKE_MESSID(37, 0x22), MAKE_MESSID(37, 0x29), MAKE_MESSID(37, 0x2A),
        MAKE_MESSID(37, 0x2B), MAKE_MESSID(37, 0x2C), MAKE_MESSID(37, 0x2D),
        MAKE_MESSID(37, 0x2E), MAKE_MESSID(37, 0x2F), MAKE_MESSID(37, 0x8F),
        MAKE_MESSID(37, 0x90), MAKE_MESSID(37, 0x91), MAKE_MESSID(37, 0x9F)
    },
    {
        MAKE_MESSID(37, 0x30), MAKE_MESSID(37, 0x31), MAKE_MESSID(37, 0x32),
        MAKE_MESSID(37, 0x33), MAKE_MESSID(37, 0x34), MAKE_MESSID(37, 0x35),
        MAKE_MESSID(37, 0x3A), MAKE_MESSID(37, 0x3B), MAKE_MESSID(37, 0x3C),
        MAKE_MESSID(37, 0x3D), MAKE_MESSID(37, 0x3E), MAKE_MESSID(37, 0x3F),
        MAKE_MESSID(37, 0x36), MAKE_MESSID(37, 0x37), MAKE_MESSID(37, 0x38),
        MAKE_MESSID(37, 0x39), MAKE_MESSID(37, 0x40), MAKE_MESSID(37, 0x41),
        MAKE_MESSID(37, 0x42), MAKE_MESSID(37, 0x43), MAKE_MESSID(37, 0x44),
        MAKE_MESSID(37, 0x45), MAKE_MESSID(37, 0x46), MAKE_MESSID(37, 0x92),
        MAKE_MESSID(37, 0x93), MAKE_MESSID(37, 0x94), MAKE_MESSID(37, 0xA0)
    },
    {
        MAKE_MESSID(37, 0x47), MAKE_MESSID(37, 0x48), MAKE_MESSID(37, 0x49),
        MAKE_MESSID(37, 0x4A), MAKE_MESSID(37, 0x4B), MAKE_MESSID(37, 0x4C),
        MAKE_MESSID(37, 0x51), MAKE_MESSID(37, 0x52), MAKE_MESSID(37, 0x53),
        MAKE_MESSID(37, 0x54), MAKE_MESSID(37, 0x55), MAKE_MESSID(37, 0x56),
        MAKE_MESSID(37, 0x4D), MAKE_MESSID(37, 0x4E), MAKE_MESSID(37, 0x4F),
        MAKE_MESSID(37, 0x50), MAKE_MESSID(37, 0x57), MAKE_MESSID(37, 0x58),
        MAKE_MESSID(37, 0x59), MAKE_MESSID(37, 0x5A), MAKE_MESSID(37, 0x5B),
        MAKE_MESSID(37, 0x5C), MAKE_MESSID(37, 0x5D), MAKE_MESSID(37, 0x95),
        MAKE_MESSID(37, 0x96), MAKE_MESSID(37, 0x97), MAKE_MESSID(37, 0xA1)
    },
    {
        MAKE_MESSID(37, 0x5E), MAKE_MESSID(37, 0x5F), MAKE_MESSID(37, 0x60),
        MAKE_MESSID(37, 0x61), MAKE_MESSID(37, 0x62), MAKE_MESSID(37, 0x63),
        MAKE_MESSID(37, 0x68), MAKE_MESSID(37, 0x69), MAKE_MESSID(37, 0x6A),
        MAKE_MESSID(37, 0x6B), MAKE_MESSID(37, 0x6C), MAKE_MESSID(37, 0x6D),
        MAKE_MESSID(37, 0x64), MAKE_MESSID(37, 0x65), MAKE_MESSID(37, 0x66),
        MAKE_MESSID(37, 0x67), MAKE_MESSID(37, 0x6E), MAKE_MESSID(37, 0x6F),
        MAKE_MESSID(37, 0x70), MAKE_MESSID(37, 0x71), MAKE_MESSID(37, 0x72),
        MAKE_MESSID(37, 0x73), MAKE_MESSID(37, 0x74), MAKE_MESSID(37, 0x98),
        MAKE_MESSID(37, 0x99), MAKE_MESSID(37, 0x9A), MAKE_MESSID(37, 0xA2)
    },
    {
        MAKE_MESSID(37, 0x75), MAKE_MESSID(37, 0x76), MAKE_MESSID(37, 0x77),
        MAKE_MESSID(37, 0x78), MAKE_MESSID(37, 0x79), MAKE_MESSID(37, 0x7A),
        MAKE_MESSID(37, 0x7F), MAKE_MESSID(37, 0x80), MAKE_MESSID(37, 0x81),
        MAKE_MESSID(37, 0x82), MAKE_MESSID(37, 0x83), MAKE_MESSID(37, 0x84),
        MAKE_MESSID(37, 0x7B), MAKE_MESSID(37, 0x7C), MAKE_MESSID(37, 0x7D),
        MAKE_MESSID(37, 0x7E), MAKE_MESSID(37, 0x85), MAKE_MESSID(37, 0x86),
        MAKE_MESSID(37, 0x87), MAKE_MESSID(37, 0x88), MAKE_MESSID(37, 0x89),
        MAKE_MESSID(37, 0x8A), MAKE_MESSID(37, 0x8B), MAKE_MESSID(37, 0x9B),
        MAKE_MESSID(37, 0x9C), MAKE_MESSID(37, 0x9D), MAKE_MESSID(37, 0xA3)
    }
};

void fn_1_13A3C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r29 = 0;
    s32 temp_r28 = 0;
    s32 i;

    lbl_1_bss_1580.unk18 = 0;
    fn_1_1E28(lbl_1_bss_1468.unk00, 1, arg3, 15, 1);
    temp_r28 = (s16) HuWinKeyWaitNumGet(lbl_1_data_504[lbl_1_bss_1580.unk00][arg1]);
    if (arg2 == -1) {
        arg2 = temp_r28 - 1;
    }
    HuWinComKeyReset();
    if (lbl_1_bss_1580.unk14 == -1) {
        for (i = 0; i < 10; i++) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, GWMessDelayGet());
        }
    }
    HuWinMesSet(arg0, lbl_1_data_504[lbl_1_bss_1580.unk00][arg1]);
    for (i = 0; i < temp_r28; i++) {
        var_r29 = 0;
        do {
            HuPrcVSleep();
        } while (HuWinStatGet(arg0) != 1);
        if (i == arg2) {
            HuWinAttrSet(arg0, 0x400);
            var_r29 = 1;
            lbl_1_bss_1580.unk18 = 99;
        }
        while (TRUE) {
            HuPrcVSleep();
            if (var_r29 != 0) {
                if (var_r29 == 1) {
                    if (HuWinStatGet(arg0) != 1) {
                        var_r29 = 2;
                        continue;
                    }
                }
                if (var_r29 == 2) {
                    do {
                        fn_1_938();
                    } while (lbl_1_bss_1580.unk18 != 1);
                    HuWinAttrReset(arg0, 0x400);
                    HuWinKeyWaitEntry(arg0);
                    break;
                }
            } else if (HuWinStatGet(arg0) != 1) {
                break;
            }
        }
    }
    fn_1_1B18(arg0, -1);
    fn_1_1D44(arg0, MAKE_MESSID(37, 4));
    HuWinComKeyReset();
    fn_1_1E28(lbl_1_bss_1468.unk00, 1, 1, 15, 1);
}

void fn_1_13C78(s32 arg0, s32 arg1, s32 arg2) {
    fn_1_1E28(lbl_1_bss_1468.unk00, 1, arg2, 15, 1);
    fn_1_1D44(arg0, lbl_1_data_504[lbl_1_bss_1580.unk00][arg1]);
    fn_1_1B18(arg0, -1);
    fn_1_1D44(arg0, MAKE_MESSID(37, 4));
    fn_1_1E28(lbl_1_bss_1468.unk00, 1, 1, 15, 1);
}

void fn_1_13D38(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r31;

    var_r31 = lbl_1_bss_1580.unkC4[arg1].unk00.unk10;
    HuWinInsertMesSet(arg0, var_r31, arg2);
}

void fn_1_13D98(omObjData* arg0, s32 arg1) {
    s32 sp20[] = {
        DATA_MAKE_NUM(DATADIR_MSTORY3, 40),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 46),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 52),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 58),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 64),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 70)
    };
    s32 sp38[][5] = {
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 0x29), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x2A), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x2B), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x2C), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x2D) },
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 0x2F), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x30), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x31), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x32), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x33) },
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 0x35), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x36), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x37), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x38), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x39) },
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 0x3B), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x3C), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x3D), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x3E), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x3F) },
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 0x41), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x42), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x43), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x44), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x45) },
        { DATA_MAKE_NUM(DATADIR_MSTORY3, 0x47), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x48), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x49), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x4A), DATA_MAKE_NUM(DATADIR_MSTORY3, 0x4A) }
    };

    arg0->model[1] = Hu3DModelCreateFile(sp20[arg1]);
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[1], sp38[arg1][0]);
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[1], sp38[arg1][1]);
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[1], sp38[arg1][2]);
    arg0->motion[4] = Hu3DJointMotionFile(arg0->model[1], sp38[arg1][3]);
    arg0->motion[5] = Hu3DJointMotionFile(arg0->model[1], sp38[arg1][4]);
    Hu3DModelPosSet(arg0->model[1], 0.0f, 0.0f, 670.0f);
    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
    if (arg1 == 3) {
        Hu3DData[arg0->model[1]].pos.y = 50.0f;
    }
    Hu3DModelShadowSet(arg0->model[1]);
    fn_1_1E28(arg0, 1, 1, 0, 1);
    {
        s32 sp8[] = { 9, 14, 10, 11, 12, 13 };

        if (arg1 != 3) {
            CharModelEffectNpcInit(arg0->model[1], arg0->motion[2], 1, sp8[arg1]);
        }
    }
}

void fn_1_140A0(void) {
    omObjData* temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_A8, 0x100, 0x10, 0x10, -1, NULL);
    lbl_1_bss_1468.unk00 = temp_r3;
    lbl_1_bss_1468.unk04 = NULL;
    lbl_1_bss_1468.unk00->data = &lbl_1_bss_1468;
    fn_1_13D98(temp_r3, lbl_1_bss_1580.unk00);
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_1468.unk04 != NULL) {
            lbl_1_bss_1468.unk04(temp_r3);
        }
    }
}

void fn_1_1442C(s32 arg0) {
    s32 var_r31;

    var_r31 = -1;
    if (GWPlayerCfg[lbl_1_bss_1580.unkC4[arg0].unk00.unk00].iscom) {
        var_r31 = rand8() % 120 + 60;
    }
    do {
        fn_1_938();
        if (!GWPlayerCfg[lbl_1_bss_1580.unkC4[arg0].unk00.unk00].iscom && (HuPadBtnDown[GWPlayerCfg[lbl_1_bss_1580.unkC4[arg0].unk00.unk00].pad_idx] & PAD_BUTTON_A)) {
            break;
        }
    } while (var_r31-- != 0);
    fn_1_1E28(lbl_1_bss_1490[arg0].unk00, 1, 5, 15, 0);
}

void fn_1_1456C(s32 arg0) {
    while (TRUE) {
        fn_1_938();
        if (lbl_1_bss_1490[arg0].unk00->motion[5] != Hu3DMotionShiftIDGet(lbl_1_bss_1490[arg0].unk00->model[1])
            && lbl_1_bss_1490[arg0].unk00->motion[5] == Hu3DMotionIDGet(lbl_1_bss_1490[arg0].unk00->model[1])
            && Hu3DMotionTimeGet(lbl_1_bss_1490[arg0].unk00->model[1]) >= 27.0f)
        {
            break;
        }
    }
    HuAudFXStop(lbl_1_bss_68[arg0 + 1]);
    HuAudFXPlay(0x303);
}

HsfanimStruct00 lbl_1_data_78C = {
    60, { 0, 0 },
    1000.0f, 0.0f, 180.0f,
    { 0.0f, 0.0f, 0.0f },
    50.0f, 0.9f, 20.0f, 0.99f, 4,
    {
        { 0xFF, 0xFF, 0x00, 0xFF },
        { 0xFF, 0xFF, 0x20, 0xFF },
        { 0xFF, 0xFF, 0x80, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF }
    },
    {
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 }
    }
};

s32 fn_1_14684(void) {
    s32 temp_r3;

    temp_r3 = Hu3DParManCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_EFFECT, 1)), 250, &lbl_1_data_78C);
    Hu3DParManTimeLimitSet(temp_r3, 60);
    Hu3DParManAttrSet(temp_r3, 4 | 0x40);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(temp_r3), 1);
    return temp_r3;
}

void fn_1_14700(omObjData* arg0) {
    Hu3DModelKill(arg0->model[0]);
    omDelObjEx(lbl_1_bss_A8, arg0);
}

void fn_1_14748(omObjData* arg0) {
    float temp_f31;
    s32 sp8[3];
    s32 temp_r27;
    s32 var_r26;
    s32 var_r30;
    s32 temp_r25;
    s32 var_r29;

    switch (arg0->work[1]) {
        case 0:
            if (arg0->work[2] >= 1080) {
                arg0->work[1] = 1;
                arg0->rot.y = 0.0f;
                arg0->scale.x = arg0->scale.y = arg0->scale.z = 1.0f;
                arg0->work[2] = arg0->work[3] = 0;
                lbl_1_bss_68[arg0->work[0] + 1] = HuAudFXPlay(0x300);
            } else {
                arg0->rot.y = arg0->work[2] % 360;
                arg0->work[2] += 25;
                if (arg0->work[3] < 180) {
                    arg0->scale.x = sind(arg0->work[3] % 180);
                    arg0->work[3] += 6;
                } else {
                    arg0->scale.x = 1.0 + 0.5 * sind(arg0->work[3] % 180);
                    arg0->work[3] += 18;
                }
                arg0->scale.y = arg0->scale.z = arg0->scale.x;
                if (arg0->work[3] > 360) {
                    arg0->work[3] = 360;
                }
            }
            break;
        case 1:
            if (arg0->work[2] >= 40) {
                arg0->work[1] = 2;
            }
            /* fallthrough */
        case 2:
            arg0->trans.y += 0.2f * sind(arg0->work[2]);
            if ((arg0->work[2] += 4) > 360) {
                arg0->work[2] -= 360;
            }
            break;
        case 3:
            if (arg0->work[3]++ >= 8) {
                arg0->work[1] = 4;
                arg0->work[3] = 0;
                Hu3DModelAttrSet(arg0->model[0], 1);
            } else {
                temp_f31 = fn_1_5D4(1.0f, 0.0f, arg0->work[3], 8.0f);
                if (arg0->work[3] == 1) {
                    arg0->work[2] = fn_1_14684();
                    Hu3DParManPosSet(arg0->work[2], arg0->trans.x, 275.0f, arg0->trans.z);
                }
                arg0->trans.y = 250.0f + fn_1_5D4(0.0f, 25.0f, arg0->work[3], 4.0f);
                arg0->scale.x = 1.0f + 0.5f * (1.0f - temp_f31);
                arg0->scale.y = arg0->scale.z = arg0->scale.x;
                Hu3DModelTPLvlSet(arg0->model[0], temp_f31);
            }
            break;
        case 4:
            if (arg0->work[3]++ >= 60) {
                Hu3DParManKill(arg0->work[2]);
                arg0->work[2] = -1;
                arg0->func = NULL;
            }
            break;
    }
    if (arg0->work[1] >= 3) {
        var_r26 = 0;
        if (lbl_1_bss_1428[arg0->work[0]] == -1) {
            var_r30 = lbl_1_bss_1438[arg0->work[0]];
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                if (var_r29 != arg0->work[0]) {
                    sp8[var_r26++] = lbl_1_bss_1428[var_r29];
                }
            }
            while (TRUE) {
                if (var_r30 != sp8[0] && var_r30 != sp8[1] && var_r30 != sp8[2]) {
                    lbl_1_bss_1428[arg0->work[0]] = var_r30;
                    break;
                }
                var_r30 = rand8() % 10 + 1;
            }
            Hu3DMotionTimeSet(arg0->model[0], lbl_1_bss_1428[arg0->work[0]] - 1 + 0.5f);
        }
    } else {
        temp_r25 = lbl_1_bss_1438[arg0->work[0]] - 1;
        do {
            temp_r27 = rand8() % 10;
        } while (temp_r25 == temp_r27);
        lbl_1_bss_1438[arg0->work[0]] = temp_r27 + 1;
        Hu3DMotionTimeSet(arg0->model[0], temp_r27 + 0.5f);
    }
}

void fn_1_14E6C(omObjData* arg0) {
    s32 temp_r30;

    temp_r30 = arg0->work[0];
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MSTORY3, 19));
    omSetTra(arg0, lbl_1_data_130[temp_r30].x, 250.0f, lbl_1_data_130[temp_r30].z);
    omSetRot(arg0, 0.0f, 0.0f, 0.0f);
    omSetSca(arg0, 0.0f, 0.0f, 0.0f);
    Hu3DMotionSpeedSet(arg0->model[0], 0.0f);
    HuAudFXPlay(0x302);
    arg0->func = fn_1_14748;
}

void fn_1_14F80(omObjData* arg0) {
    Hu3DModelKill(arg0->model[1]);
    Hu3DModelKill(arg0->model[2]);
    omDelObjEx(lbl_1_bss_A8, arg0);
}

void fn_1_14FD4(omObjData* arg0) {
    s32 temp_r29;
    s32 var_r30;

    temp_r29 = arg0->work[0];
    for (var_r30 = 1; var_r30 < 3; var_r30++) {
        if (arg0->work[3] <= 40) {
            Hu3DData[arg0->model[var_r30]].rot.y = fn_1_6F4(0.0f, 360.0f, arg0->work[3], 40.0f);
        } else {
            Hu3DData[arg0->model[var_r30]].rot.y = fn_1_61C(360.0f, 0.0f, arg0->work[3] - 40, 20.0f);
        }
        if (arg0->work[1] / 10 == 0) {
            Hu3DData[arg0->model[var_r30]].pos.x = lbl_1_data_130[temp_r29].x;
        } else {
            Hu3DData[arg0->model[var_r30]].pos.x = lbl_1_data_130[temp_r29].x + fn_1_5D4(0.0f, 40.0f + -80.0f * (var_r30 - 1), arg0->work[3], 20.0f);
        }
        Hu3DData[arg0->model[var_r30]].pos.y = 275.0f + fn_1_5D4(0.0f, 50.0f, arg0->work[3], 20.0f);
        Hu3DData[arg0->model[var_r30]].pos.z = lbl_1_data_130[temp_r29].z;
    }
    if (arg0->work[3]++ >= 60) {
        arg0->func = NULL;
    }
}

void fn_1_152F0(omObjData* arg0) {
    s32 sp8[] = {
        DATA_MAKE_NUM(DATADIR_MSTORY3, 20),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 21),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 22),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 23),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 24),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 25),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 26),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 27),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 28),
        DATA_MAKE_NUM(DATADIR_MSTORY3, 29)
    };

    arg0->model[1] = Hu3DModelCreateFile(sp8[arg0->work[1] % 10]);
    arg0->model[2] = Hu3DModelCreateFile(sp8[arg0->work[1] / 10]);
    Hu3DMotionSpeedSet(arg0->model[1], 0.0f);
    Hu3DMotionSpeedSet(arg0->model[2], 0.0f);
    if (arg0->work[1] / 10 == 0) {
        Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
    }
    arg0->func = fn_1_14FD4;
}

void fn_1_15450(s32 arg0) {
    omObjData* temp_r3;
    omObjData* temp_r3_2;

    temp_r3 = omAddObjEx(lbl_1_bss_A8, 0x2000, 0x10, 0x10, -1, fn_1_14E6C);
    temp_r3->work[0] = arg0;
    do {
        fn_1_938();
    } while (temp_r3->work[1] != 2);
    fn_1_1442C(arg0);
    fn_1_1456C(arg0);
    temp_r3->work[1] = 3;
    fn_1_938();
    temp_r3_2 = omAddObjEx(lbl_1_bss_A8, 0x2000, 0x10, 0x10, -1, fn_1_152F0);
    temp_r3_2->work[0] = arg0;
    temp_r3_2->work[1] = lbl_1_bss_1428[arg0];
    fn_1_958(10);
    fn_1_1E28(lbl_1_bss_1490[arg0].unk00, 1, 1, 15, 1);
    do {
        fn_1_938();
    } while (temp_r3_2->func);
    lbl_1_bss_1490[arg0].unk18 = 1;
    do {
        fn_1_938();
    } while (lbl_1_bss_1490[arg0].unk18 != 2);
    fn_1_958(150);
    fn_1_14700(temp_r3);
    fn_1_14F80(temp_r3_2);
}
