#include "game/audio.h"
#include "game/chrman.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "math.h"

#include "REL/m407dll.h"

typedef struct unkDominationData {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    // padding unk_03
    s32 unk_04;
    s32 unk_08;
    u8 unk_0C;
    // padding unk_0D
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    s32 unk_34;
    s32 unk_38;
} unkDominationData;

// function signatures
void fn_1_628(omObjData *, s32);
void fn_1_64C(omObjData *);
void fn_1_99C(omObjData *);
void fn_1_A1C(omObjData *arg0);
void fn_1_26CC(u8);
void fn_1_4544(s32, s32, f32, f32, f32);
s16 fn_1_28B8(u8);
s16 fn_1_28E4(u8);
void fn_1_A88(omObjData *arg0);
void fn_1_A8C(omObjData *arg0);
void fn_1_C58(omObjData *arg0);
void fn_1_CF4(omObjData *arg0);
void fn_1_DB4(omObjData *arg0);
void fn_1_F8C(omObjData *arg0);
void fn_1_1074(omObjData *arg0);
void fn_1_11CC(omObjData *arg0);
void fn_1_13E4(omObjData *arg0);
void fn_1_1460(omObjData *arg0);

// bss
Process *lbl_1_bss_18;
omObjData *lbl_1_bss_8[4];
Process *lbl_1_bss_0[2];

// data
u32 lbl_1_data_0[8][8] = {
    {
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x24),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x29),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x4A),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x4B),
        DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18),
    },
    {
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x24),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x29),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x4A),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x4B),
        DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x18),
    },
    {
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x24),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x29),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x4A),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x4B),
        DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x18),
    },
    {
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x24),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x29),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x4A),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x4B),
        DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x18),
    },
    {
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x24),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x29),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x4A),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x4B),
        DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x18),
    },
    {
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x24),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x29),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x4A),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x4B),
        DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x18),
    },
    {
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x24),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x29),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x4A),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x4B),
        DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x18),
    },
    {
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x24),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x29),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x05),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x06),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x4A),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x4B),
        DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x18),
    },
};

s32 lbl_1_data_100[] = {
    DATA_MAKE_NUM(DATADIR_M407, 0x0D),
    DATA_MAKE_NUM(DATADIR_M407, 0x0E),
    DATA_MAKE_NUM(DATADIR_M407, 0x0F),
    DATA_MAKE_NUM(DATADIR_M407, 0x10),
    DATA_MAKE_NUM(DATADIR_M407, 0x11),
    DATA_MAKE_NUM(DATADIR_M407, 0x12),
    DATA_MAKE_NUM(DATADIR_M407, 0x13),
    DATA_MAKE_NUM(DATADIR_M407, 0x14),
};

char lbl_1_data_120[] = "test11_tex_we-itemhook-r";
char *lbl_1_data_13C[]
    = { lbl_1_data_120, lbl_1_data_120, lbl_1_data_120, lbl_1_data_120, lbl_1_data_120, lbl_1_data_120, lbl_1_data_120, lbl_1_data_120 };

ObjFuncs lbl_1_data_15C[] = { fn_1_A88, fn_1_A8C, fn_1_C58, fn_1_CF4, fn_1_DB4, fn_1_F8C, fn_1_1074, fn_1_11CC, fn_1_13E4, fn_1_1460 };

u8 lbl_1_data_184[4][2] = { { 0x3C, 0x0F }, { 0x50, 0x0F }, { 0x64, 0x14 }, { 0x78, 0x14 } };

inline void SetDominationDataStuff(omObjData *arg0, s32 val0, s32 val1)
{
    unkDominationData *temp_r29 = arg0->data;
    temp_r29->unk_1C = val0;
    temp_r29->unk_20 = val1;
}

void ObjectSetup(void)
{
    lbl_1_bss_0[0] = omInitObjMan(0x2F8, 0x2000);
    omGameSysInit(lbl_1_bss_0[0]);
    fn_1_4980(lbl_1_bss_0[0]);
}

void fn_1_F4(Process *arg0)
{
    u32 i;
    lbl_1_bss_18 = arg0;

    for (i = 0; i < 4; i++) {
        lbl_1_bss_8[i] = omAddObjEx(lbl_1_bss_18, 0x100, 2, 8, 0, fn_1_64C);
        lbl_1_bss_8[i]->work[0] = i;
    }
}

void fn_1_194(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        fn_1_99C(lbl_1_bss_8[i]);
    }
}

void fn_1_1E4(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        fn_1_628(lbl_1_bss_8[i], 1);
    }
}

void fn_1_238(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        fn_1_628(lbl_1_bss_8[i], 2);
    }
}

void fn_1_28C(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        fn_1_628(lbl_1_bss_8[i], 3);
    }
}

void fn_1_2E0(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        fn_1_628(lbl_1_bss_8[i], 4);
    }
}

void fn_1_334(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        fn_1_628(lbl_1_bss_8[i], 5);
    }
}

void fn_1_388(u8 arg0, s32 arg1)
{
    omObjData *obj = lbl_1_bss_8[arg0];
    unkDominationData *unkData = obj->data;
    unkData->unk_38 = arg1;
}

void fn_1_3C4(u8 arg0)
{
    fn_1_628(lbl_1_bss_8[arg0], 8);
}

void fn_1_404(void)
{
    omObjData *temp_r31;
    unkDominationData *unkData;
    s32 temp_r0;
    u8 i;

    for (i = 0; i < 4; i++) {
        temp_r31 = lbl_1_bss_8[i];
        unkData = temp_r31->data;
        switch (unkData->unk_38) {
            case 0:
                fn_1_628(temp_r31, 9);
                break;
            case 1:
                fn_1_628(temp_r31, 6);
                break;
            case 2:
                fn_1_628(temp_r31, 9);
                break;
        }
    }
}

s32 fn_1_4C0(u8 arg0)
{
    unkDominationData *unkData;

    if (arg0 >= 4) {
        return -1;
    }

    unkData = lbl_1_bss_8[arg0]->data;
    return unkData->unk_01;
}

s32 fn_1_508(u8 arg0)
{
    unkDominationData *unkData = lbl_1_bss_8[arg0]->data;
    return unkData->unk_04;
}

s32 fn_1_53C(u8 arg0)
{
    return ((unkDominationData *)(lbl_1_bss_8[arg0]->data))->unk_1C == 0;
}

void fn_1_568(s16 arg0, s16 arg1, s16 arg2)
{
    unkDominationData *unkData;

    unkData = lbl_1_bss_8[arg0]->data;
    switch (arg1) {
        case 0:
            omVibrate(unkData->unk_00, arg2, 6, 6);
            break;
        case 1:
            omVibrate(unkData->unk_00, arg2, 4, 2);
            break;
        case 2:
            omVibrate(unkData->unk_00, arg2, 0xC, 0);
            break;
    }
}

void fn_1_628(omObjData *arg0, s32 arg1)
{
    unkDominationData *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk_1C = arg1;
    temp_r31->unk_20 = 0;
}

void fn_1_64C(omObjData *arg0)
{
    u32 temp_r29;
    unkDominationData *temp_r27;
    unkDominationData *temp_r31;
    u32 i;

    arg0->func = fn_1_A1C;
    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(unkDominationData), MEMORY_DEFAULT_NUM);
    temp_r31 = arg0->data;
    temp_r29 = arg0->work[0];
    temp_r31->unk_00 = temp_r29;
    temp_r31->unk_01 = GWPlayerCfg[temp_r29].character;
    temp_r31->unk_0C = GWPlayerCfg[temp_r29].pad_idx;
    temp_r31->unk_04 = GWPlayerCfg[temp_r29].iscom;
    temp_r31->unk_02 = GWPlayerCfg[temp_r29].diff;
    temp_r31->unk_08 = 0;
    temp_r31->unk_34 = 0;
    temp_r31->unk_38 = 0;
    temp_r31->unk_28 = 0.0f;
    temp_r31->unk_30 = (600.0f / (lbl_1_data_184[temp_r31->unk_02][0] - frandmod31(lbl_1_data_184[temp_r31->unk_02][1])));
    temp_r31->unk_2C = temp_r31->unk_30;
    arg0->model[0] = CharModelCreate(temp_r31->unk_01, 8);
    arg0->model[1] = Hu3DModelCreateFile(lbl_1_data_100[temp_r31->unk_01]);
    Hu3DModelAmbSet(arg0->model[0], 1.0f, 1.0f, 1.0f);
    Hu3DModelAmbSet(arg0->model[1], 1.0f, 1.0f, 1.0f);

    for (i = 0; i < 8; i++) {
        arg0->motion[i] = CharModelMotionCreate(temp_r31->unk_01, lbl_1_data_0[temp_r31->unk_01][i]);
    }

    Hu3DModelShadowSet(arg0->model[0]);
    Hu3DModelShadowSet(arg0->model[1]);
    CharModelMotionDataClose(temp_r31->unk_01);
    CharModelMotionSet(temp_r31->unk_01, arg0->motion[1]);
    Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelHookSet(arg0->model[0], lbl_1_data_13C[temp_r31->unk_01], arg0->model[1]);
    temp_r31->unk_10 = (600.0f - (400.0f * temp_r29));
    temp_r31->unk_14 = 0.0f;
    temp_r31->unk_18 = -500.0f;
    SetDominationDataStuff(arg0, 0, 0);
}

void fn_1_99C(omObjData *arg0)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        Hu3DMotionKill(arg0->motion[i]);
    }

    for (i = 0; i < 2; i++) {
        Hu3DModelKill(arg0->model[i]);
    }

    HuMemDirectFree(arg0->data);
}

void fn_1_A1C(omObjData *arg0)
{
    unkDominationData *temp_r31;

    temp_r31 = arg0->data;
    lbl_1_data_15C[temp_r31->unk_1C](arg0);
    omSetTra(arg0, temp_r31->unk_10, temp_r31->unk_14, temp_r31->unk_18);
}

void fn_1_A88(omObjData *arg0) { }

void fn_1_A8C(omObjData *arg0)
{
    s32 var_r29;
    unkDominationData *temp_r31;

    var_r29 = 0;
    temp_r31 = arg0->data;
    temp_r31->unk_28 += 1.0f;

    if (temp_r31->unk_04 == 0) {
        var_r29 = (HuPadBtnDown[temp_r31->unk_0C] & 0x100) ? 1 : 0;
    }
    else if ((u32)temp_r31->unk_28 >= (u32)temp_r31->unk_2C) {
        var_r29 = 1;
        temp_r31->unk_2C += temp_r31->unk_30;
    }

    if (var_r29 != 0) {
        CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[2], 0.0f, 0.0f, HU3D_MOTATTR_NONE);
        fn_1_4544(4, 0x10, 600.0f - (400.0f * temp_r31->unk_00), -20.0f, -450.0f);
        fn_1_26CC(temp_r31->unk_00);
        temp_r31->unk_34 = 1;
        return;
    }

    if ((temp_r31->unk_34 != 0) && (Hu3DMotionEndCheck(arg0->model[0]) != 0)) {
        CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[1], 0.0f, 0.0f, HU3D_MOTATTR_LOOP);
        temp_r31->unk_34 = 0;
    }
}

void fn_1_C58(omObjData *arg0)
{
    unkDominationData *temp_r30;

    temp_r30 = arg0->data;
    if (Hu3DMotionEndCheck(arg0->model[0]) != 0) {
        CharModelMotionShiftSet(temp_r30->unk_01, arg0->motion[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
        temp_r30->unk_34 = 0;
        SetDominationDataStuff(arg0, 0, 0);
    }
}

void fn_1_CF4(omObjData *arg0)
{
    unkDominationData *temp_r31;

    temp_r31 = arg0->data;
    if (temp_r31->unk_20 == 0) {
        CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
        CharModelItemHookCreate(temp_r31->unk_01, lbl_1_data_13C[temp_r31->unk_01]);
    }
    if (temp_r31->unk_20++ >= 30) {
        SetDominationDataStuff(arg0, 0, 0);
    }
}

void fn_1_DB4(omObjData *arg0)
{
    f32 temp_f31;
    f32 temp_f30;
    unkDominationData *temp_r31;

    temp_r31 = arg0->data;

    if (temp_r31->unk_20 == 0) {
        CharModelVoiceEnableSet(temp_r31->unk_01, arg0->motion[3], 0);
        CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[3], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        temp_r31->unk_24 = 0.0f;
        temp_r31->unk_20++;
    }

    temp_f31 = 32.0f * sin(M_PI / 3) - 9.8f * temp_r31->unk_24;
    temp_f30 = 22.0f * cos(M_PI / 3);
    temp_r31->unk_18 = temp_r31->unk_18 + temp_f30;
    temp_r31->unk_14 = temp_r31->unk_14 + temp_f31;
    temp_r31->unk_24 += 0.3f;

    if (!(temp_f31 < 0.0f) || !(temp_r31->unk_14 <= 30.0f)) {
        return;
    }

    temp_r31->unk_14 = 30.0f;
    CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    SetDominationDataStuff(arg0, 0, 0);
}

// can also be placed into fn_1_F8C as static const
const s32 lbl_1_rodata_70[] = { 0x00000122, 0x00000162, 0x000001A2, 0x000001E2, 0x00000222, 0x00000262, 0x000002A2, 0x000002E2 };

void fn_1_F8C(omObjData *arg0)
{
    unkDominationData *temp_r31;

    temp_r31 = arg0->data;

    if (temp_r31->unk_20 == 0) {
        CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[5], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        HuAudFXPlay(lbl_1_rodata_70[temp_r31->unk_01]);
    }

    if (temp_r31->unk_20++ >= 120) {
        CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
        SetDominationDataStuff(arg0, 0, 0);
    }
}

void fn_1_1074(omObjData *arg0)
{
    unkDominationData *temp_r31;

    temp_r31 = arg0->data;
    if (temp_r31->unk_20 == 0) {
        CharModelVoiceEnableSet(temp_r31->unk_01, arg0->motion[3], 0);
        CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[3], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        temp_r31->unk_24 = 0.0f;
        temp_r31->unk_20 = 1;
    }

    temp_r31->unk_14 += 80.0 * sin(M_PI / 2) - 9.8 * temp_r31->unk_24;
    temp_r31->unk_24 += 0.3f;

    if (!(temp_r31->unk_14 < 1000.0f)) {
        CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        SetDominationDataStuff(arg0, 7, 0);
    }
}

void fn_1_11CC(omObjData *arg0)
{
    unkDominationData *temp_r31;
    s16 temp;

    temp_r31 = arg0->data;
    if (temp_r31->unk_20 == 0) {
        CharModelVoiceEnableSet(temp_r31->unk_01, arg0->motion[3], 0);
        CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[3], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        temp_r31->unk_14 = 1000.0f;
        temp_r31->unk_18 = 200.0f * (fn_1_28B8(temp_r31->unk_00) + 2);
        temp_r31->unk_24 = 0.0f;
        temp_r31->unk_20 = 1;
    }

    temp_r31->unk_14 = (temp_r31->unk_14 - (2.0f + (9.8f * temp_r31->unk_24)));
    temp_r31->unk_24 += 0.3f;

    if (!(temp_r31->unk_14 > 300.0f)) {
        temp_r31->unk_14 = 300.0f;
        CharModelVoiceEnableSet(temp_r31->unk_01, arg0->motion[4], 0);
        CharModelMotionShiftSet(temp_r31->unk_01, arg0->motion[4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        temp = fn_1_28E4(temp_r31->unk_00);
        Hu3DModelHookSet(temp, "itemhook_c", arg0->model[0]);
        temp_r31->unk_10 = 0.0f;
        temp_r31->unk_14 = 0.0f;
        temp_r31->unk_18 = 0.0f;
        SetDominationDataStuff(arg0, 0, 0);
    }
}

void fn_1_13E4(omObjData *arg0)
{
    unkDominationData *temp_r30;

    temp_r30 = arg0->data;
    CharModelMotionShiftSet(temp_r30->unk_01, arg0->motion[6], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    SetDominationDataStuff(arg0, 0, 0);
}

void fn_1_1460(omObjData *arg0)
{
    unkDominationData *temp_r30;

    temp_r30 = arg0->data;
    CharModelVoiceEnableSet(temp_r30->unk_01, arg0->motion[7], 0);
    CharModelMotionShiftSet(temp_r30->unk_01, arg0->motion[7], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    SetDominationDataStuff(arg0, 0, 0);
}
