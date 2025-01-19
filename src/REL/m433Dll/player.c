#include "datadir_enum.h"
#include "dolphin/mtx.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/flag.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "string.h"

#include "REL/m433Dll.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/frand.h"
#endif

typedef struct M433PlayerWork {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    s32 unk_20;
    float unk_24;
    float unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    char unk50[4];
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    s32 unk_70;
    u32 unk_74;
    u32 unk_78;
    u32 unk_7C;
    u32 unk_80;
    u32 unk_84;
    u32 unk_88;
    s32 unk_8C;
    u32 unk_90;
    char unk94[4];
    float unk_98;
    s16 unk_9C;
    char unk9E[6];
    float unk_A4;
    float unk_A8;
    float unk_AC;
    float unk_B0;
    float unk_B4;
    float unk_B8;
    float unk_BC;
    float unk_C0;
    char unkC4[8];
    u32 unk_CC;
    u32 unk_D0;
    u32 unk_D4;
    u32 unk_D8;
    float unk_DC;
    float unk_E0;
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    s32 unk_F0;
    s32 unk_F4;
    u32 unk_F8;
    Vec unk_FC;
    Vec unk_108;
    Vec unk_114;
    float unk_120;
    float unk_124;
    Vec unk_128;
    Vec unk_134;
    Vec unk_140;
    omObjData *unk_14C;
} M433PlayerWork; /* size = 0x150 */

typedef struct M433PlayerWork2Sub {
    float unk_00;
    float unk_04;
    float unk_08;
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    float unk_20;
    float unk_24;
    float unk_28;
    Vec unk_2C;
    Vec unk_38;
} M433PlayerWork2Sub; /* size = 0x44 */

typedef struct M433PlayerWork2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    char unk14[4];
    u16 unk_18;
    char unk1A[0x16];
    Vec unk_30;
    Vec unk_3C;
    float unk_48;
    Vec unk_4C;
    char unk58[0x14];
    u32 unk_6C;
    s32 unk_70;
    s32 unk_74;
    u32 unk_78;
    float unk_7C[2];
    float unk_84[2];
    s32 unk_8C;
    u32 unk_90;
    u32 unk_94;
    s32 unk_98;
    float unk_9C;
    float unk_A0;
    float unk_A4;
    float unk_A8;
    Vec unk_AC;
    float unk_B8;
    Vec unk_BC;
    Mtx unk_C8;
    M433PlayerWork2Sub unk_F8;
} M433PlayerWork2; /* size = 0x13C */

typedef struct M433PlayerWork3Sub {
    s16 unk_00;
    s16 unk_02[5];
} M433PlayerWork3Sub; /* size = 0xC */

typedef struct M433PlayerWork3Sub2Sub {
    s16 unk_00[2];
    float unk_04[2];
    float unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    float unk_1C;
    float unk_20;
    float unk_24;
    float unk_28;
} M433PlayerWork3Sub2Sub; /* size 0x2C */

typedef struct M433PlayerWork3Sub2Sub2 {
    s32 unk_00[2];
    char unk08[8];
} M433PlayerWork3Sub2Sub2; /* size 0x10 */

typedef struct M433PlayerWork3Sub2 {
    s32 unk_00;
    u32 unk_04;
    u32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14[2];
    u32 unk_1C;
    M433PlayerWork3Sub2Sub unk_20[4];
    M433PlayerWork3Sub2Sub2 unk_D0[3][0x14];
    M433PlayerWork3Sub2Sub2 unk_490;
} M433PlayerWork3Sub2; /* size = 0x4A0 */

typedef struct M433PlayerWork3 {
    u32 uGameEvent;
    s32 sWinGrp;
    u32 uServeGrp;
    u32 uPointGrp;
    u32 auServeCel[2];
    u32 auEvents[2];
    u32 unk_20[2];
    u32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    u32 uContactCnt;
    s32 sGroundGrp;
    u32 uContactGrp;
    u32 uContactCel;
    u32 uTargetGrp;
    u32 unk_48;
    M433PlayerWork3Sub unk_4C[2];
    M433PlayerWork3Sub2 unk_64;
} M433PlayerWork3; /* size = 0x504 */

typedef struct M433DllPlayerData24CStruct {
    /* 0x00 */ u16 unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ u32 unk_10;
} M433DllPlayerData24CStruct; /* size = 0x14 */

typedef struct M433DllPlayerData794Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} M433DllPlayerData794Struct; /* size = 0x0C */

void fn_1_10130(Vec *arg0, u32 arg1);
void fn_1_10260(float arg8, float arg9, u32 arg0, u32 arg1, Vec *arg2);
s32 fn_1_10614(Vec *arg0);
void fn_1_1070C(void);
u32 fn_1_10740(Vec *arg0);
u32 fn_1_107B0(Vec *arg0);
float fn_1_10848(void);
u32 fn_1_108C4(void);
u32 fn_1_10900(void);
float fn_1_10B20(float arg8, Vec *arg0);
s32 fn_1_10D24(Vec *arg0);
u32 fn_1_10EA4(void);
u32 fn_1_10ECC(u32 arg0);
s32 fn_1_10F00(u32 arg0);
u32 fn_1_10F38(u32 arg0);
s32 fn_1_10F6C(u32 arg0);
u32 fn_1_10FDC(void);
s32 fn_1_11004(u32 arg0, s32 arg1);
s32 fn_1_11060(u32 arg0);
float fn_1_11130(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3);
void fn_1_5B98(omObjData *object);
void fn_1_6070(omObjData *object);
void fn_1_60C0(omObjData *object);
void fn_1_682C(omObjData *object);
void fn_1_722C(omObjData *object);
void fn_1_74D4(omObjData *object);
void fn_1_8408(omObjData *object);
void fn_1_873C(omObjData *object);
s32 fn_1_8938(u32 arg0, Vec *arg1);
void fn_1_8BD0(omObjData *object);
void fn_1_8F80(omObjData *object);
void fn_1_9688(omObjData *object);
void fn_1_A618(omObjData *object);
void fn_1_AB88(omObjData *object);
void fn_1_B194(omObjData *object);
void fn_1_B4D4(omObjData *object, u32 arg1);
s32 fn_1_B6E0(omObjData *object);
s32 fn_1_B7AC(omObjData *object);
s32 fn_1_BAE0(omObjData *object, u32 arg1);
void fn_1_BD48(omObjData *object);
void fn_1_C240(omObjData *object);
void fn_1_C6AC(omObjData *object);
s32 fn_1_C6B0(omObjData *object);
void fn_1_CB98(omObjData *object);
void fn_1_CDB8(M433PlayerWork2Sub *arg0, Vec *arg1, Vec *arg2, u32 arg3, float arg8);
void fn_1_D180(M433PlayerWork2Sub *arg0);
void fn_1_D338(M433PlayerWork2Sub *arg0);
s32 fn_1_D4E0(M433PlayerWork2Sub *arg0, Vec *arg1, Vec *arg2, float arg8);
void fn_1_D6A8(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_D888(Vec *arg0, float arg8);
void fn_1_DD70(Vec *arg0);
void fn_1_DE28(ModelData *model, ParticleData *particle, Mtx matrix);
void fn_1_DF44(omObjData *object);
void fn_1_E11C(omObjData *object);
void fn_1_E5C0(M433PlayerWork3Sub *arg0, M433PlayerWork3Sub2 *arg1);
void fn_1_ECFC(M433PlayerWork3Sub *arg0, M433PlayerWork3Sub2 *arg1);
void fn_1_FE64(M433PlayerWork3Sub2 *arg0, s32 arg1, s32 arg2, u32 arg3);
void fn_1_FE8C(Vec *arg0, u32 arg1, u32 arg2, s32 arg3);

s32 lbl_1_data_C8[6] = { 0, 1, 2, 3, 4, 5 };
float lbl_1_data_E0[0xE] = {
    130.0f,
    130.0f,
    160.0f,
    130.0f,
    130.0f,
    160.0f,
    160.0f,
    180.0f,
    240.00002f,
    100.0f,
    130.0f,
    130.0f,
    120.00001f,
    130.0f,
};
float lbl_1_data_118[0xE] = {
    50.0f,
    50.0f,
    50.0f,
    50.0f,
    50.0f,
    70.0f,
    50.0f,
    70.0f,
    110.0f,
    50.0f,
    50.0f,
    50.0f,
    50.0f,
    50.0f,
};
s32 lbl_1_data_150[6][2] = {
    { 0x3A, 0x3B },
    { 0x36, 0x38 },
    { 0x40, 0x42 },
    { 0x4B, 0x4D },
    { 0x46, 0x48 },
    { 0x3E, 0x3F },
};
s32 lbl_1_data_180[0x11] = {
    DATA_MAKE_NUM(DATADIR_M433, 97),
    DATA_MAKE_NUM(DATADIR_M433, 98),
    DATA_MAKE_NUM(DATADIR_M433, 99),
    DATA_MAKE_NUM(DATADIR_M433, 100),
    DATA_MAKE_NUM(DATADIR_M433, 101),
    DATA_MAKE_NUM(DATADIR_M433, 102),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
u32 lbl_1_data_1C4[0x11] = {
    0,
    2,
    3,
    DATA_MAKE_NUM(DATADIR_M433, 0x11),
    DATA_MAKE_NUM(DATADIR_M433, 0x19),
    DATA_MAKE_NUM(DATADIR_M433, 0x21),
    DATA_MAKE_NUM(DATADIR_M433, 0x29),
    DATA_MAKE_NUM(DATADIR_M433, 0x31),
    DATA_MAKE_NUM(DATADIR_M433, 0x39),
    DATA_MAKE_NUM(DATADIR_M433, 0x41),
    DATA_MAKE_NUM(DATADIR_M433, 0x49),
    DATA_MAKE_NUM(DATADIR_M433, 0x51),
    DATA_MAKE_NUM(DATADIR_M433, 0x59),
    0x17,
    0x18,
    0x48,
    0x49,
};
s32 lbl_1_data_208[0x11] = {
    DATA_MAKE_NUM(DATADIR_M433, 0x67),
    DATA_MAKE_NUM(DATADIR_M433, 0x6D),
    DATA_MAKE_NUM(DATADIR_M433, 0x73),
    DATA_MAKE_NUM(DATADIR_M433, 0x79),
    DATA_MAKE_NUM(DATADIR_M433, 0x7F),
    DATA_MAKE_NUM(DATADIR_M433, 0x85),
    DATA_MAKE_NUM(DATADIR_M433, 0x8B),
    DATA_MAKE_NUM(DATADIR_M433, 0x91),
    DATA_MAKE_NUM(DATADIR_M433, 0x97),
    DATA_MAKE_NUM(DATADIR_M433, 0x9D),
    DATA_MAKE_NUM(DATADIR_M433, 0xA3),
    DATA_MAKE_NUM(DATADIR_M433, 0xA9),
    DATA_MAKE_NUM(DATADIR_M433, 0xAF),
    DATA_MAKE_NUM(DATADIR_M433, 0xB5),
    DATA_MAKE_NUM(DATADIR_M433, 0xC1),
    DATA_MAKE_NUM(DATADIR_M433, 0xBB),
    DATA_MAKE_NUM(DATADIR_M433, 0xC7),
};
M433DllPlayerData24CStruct lbl_1_data_24C[0x15] = {
    { 0, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 1, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 2, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 3, 0.15f, 0.0f, 0.0f, 0 },
    { 3, 0.02f, 0.0f, -1.0f, 0 },
    { 4, 0.02f, 0.2f, -1.0f, 0 },
    { 5, 0.05f, 0.25f, -1.0f, 0 },
    { 6, 0.1f, 0.0f, -1.0f, 0 },
    { 7, 0.02f, 0.0f, -1.0f, 0 },
    { 0xB, 0.02f, 0.4f, -1.0f, 0 },
    { 0xC, 0.02f, 0.36666667f, -1.0f, 0 },
    { 8, 0.01f, 0.2f, -1.0f, 0 },
    { 9, 0.02f, 0.0f, -1.0f, 0 },
    { 0xA, 0.02f, 0.0f, -1.0f, 0 },
    { 5, 0.08f, 0.0f, 0.25f, 0 },
    { 0xB, 0.2f, 0.0f, 0.4f, 0 },
    { 0xC, 0.08f, 0.0f, 0.3f, 0 },
    { 0xD, 0.2f, 0.0f, -1.0f, 0 },
    { 0xE, 0.2f, 0.0f, -1.0f, 0 },
    { 0xF, 0.2f, 0.0f, -1.0f, 0 },
    { 0x10, 0.2f, 0.0f, -1.0f, 0 },
};
u32 lbl_1_data_3F0[0xE] = {
    0x32,
    0x32,
    0x3C,
    0x32,
    0x32,
    0x5A,
    0x32,
    0x3C,
    0x64,
    0x1E,
    0x32,
    0x1E,
    0x28,
    0x32,
};

// M433PlayerWork
omObjData *lbl_1_bss_7D0[5];
// M433PlayerWork2
omObjData *lbl_1_bss_7CC;
// M433PlayerWork3
omObjData *lbl_1_bss_7C8;
u32 lbl_1_bss_7B8[4];

void fn_1_5904(Process *process)
{
    u32 sp18[4];
    s32 sp8[4];

    s16 var_r31;
    s16 var_r30;
    u32 var_r28;
    omObjData *var_r27;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp18[var_r31] = GWPlayerCfg[var_r31].group;
        sp8[var_r31] = var_r31;
    }
    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        for (var_r30 = var_r31 + 1; var_r30 < 4; var_r30++) {
            if (sp18[var_r31] > sp18[var_r30]) {
                var_r28 = sp18[var_r31];
                sp18[var_r31] = sp18[var_r30];
                sp18[var_r30] = var_r28;
                var_r28 = sp8[var_r31];
                sp8[var_r31] = sp8[var_r30];
                sp8[var_r30] = var_r28;
            }
        }
    }
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_7B8[sp8[var_r31]] = var_r31;
    }
    lbl_1_bss_7C8 = omAddObjEx(process, 0x14, 0, 0, 0, fn_1_DF44);
    lbl_1_bss_7CC = omAddObjEx(process, 0x15, 0x1F, 0, 0, fn_1_BD48);
    omMakeGroupEx(process, 0, 4);
    omGetGroupMemberListEx(process, 0);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r27 = lbl_1_bss_7D0[var_r31] = omAddObjEx(process, 0x28, 2, 0x11, 0, fn_1_5B98);
        var_r27->work[0] = var_r31;
    }
}

void fn_1_5B74(void)
{
    CharModelKill(-1);
}

void fn_1_5B98(omObjData *object)
{
    s32 sp8;
    M433PlayerWork *work;
    s16 var_r29;
    u32 var_r28;
    s32 var_r27;

    float spC[4] = { 0.25f, 0.5f, 0.75f, 1.0f };
    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M433PlayerWork), MEMORY_DEFAULT_NUM);
    work = object->data;
    memset(work, 0, sizeof(M433PlayerWork));
    var_r27 = object->work[0];
    var_r28 = GWPlayerCfg[var_r27].character;
    work->unk_00 = var_r28;
    work->unk_04 = -1;
    if (var_r28 >= 8) {
        work->unk_04 = var_r28 - 8;
    }
    sp8 = work->unk_08 = 0;
    work->unk_14 = (lbl_1_bss_7B8[object->work[0]] >> 1) & 1;
    work->unk_18 = lbl_1_bss_7B8[object->work[0]] & 1;
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if ((var_r29 != object->work[0]) && (work->unk_14 == ((lbl_1_bss_7B8[var_r29] >> 1) & 1))) {
            break;
        }
    }
    work->unk_14C = lbl_1_bss_7D0[var_r29];
    work->unk_C0 = spC[GWPlayerCfg[var_r27].diff & 3];
    work->unk_2C = GWPlayerCfg[object->work[0]].iscom;
    if (work->unk_04 < 0) {
        object->model[0] = CharModelCreate(var_r28, 4);
        CharModelStepTypeSet(var_r28, 2);
    }
    else {
        object->model[0] = Hu3DModelCreateFile(lbl_1_data_180[work->unk_04]);
    }
    Hu3DModelShadowSet(object->model[0]);
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 8));
    Hu3DModelLayerSet(object->model[1], 1);
    for (var_r29 = 0; var_r29 < 0x11; var_r29++) {
        if (work->unk_04 < 0) {
            if (lbl_1_data_1C4[var_r29] < 0x10000) {
                object->motion[var_r29] = CharModelMotionCreate(var_r28, lbl_1_data_1C4[var_r29]);
            }
            else {
                object->motion[var_r29] = Hu3DJointMotionFile(object->model[0], var_r28 + lbl_1_data_1C4[var_r29]);
            }
        }
        else {
            object->motion[var_r29] = Hu3DJointMotionFile(object->model[0], work->unk_04 + lbl_1_data_208[var_r29]);
        }
    }
    if (work->unk_04 < 0) {
        CharModelVoiceEnableSet(var_r28, object->motion[16], 0);
        CharModelMotionDataClose(var_r28);
    }
    else {
        CharModelEffectNpcInitSilent(object->model[0], object->motion[1], 0);
        CharModelEffectNpcInitSilent(object->model[0], object->motion[2], 1);
    }
    object->trans.x = work->unk_128.x = (0.4f * (700.0f * (object->work[0] + 1))) - 700.0f;
    object->trans.y = work->unk_128.y = 0.0f;
    object->trans.z = work->unk_128.z = 0.0f;
    work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
    work->unk_A4 = work->unk_A8 = 0.0f;
    work->unk_AC = 0.0f;
    work->unk_B0 = 0.02f;
    work->unk_120 = lbl_1_data_118[var_r28];
    work->unk_0C = -1;
    work->unk_70 = -1;
    fn_1_B4D4(object, 0);
    work->unk_74 = 0;
    object->func = fn_1_6070;
}

void fn_1_6070(omObjData *object)
{
    M433PlayerWork *work = object->data;
    fn_1_722C(object);
    work->unk_74 = 0;
    object->func = fn_1_60C0;
}

void fn_1_60C0(omObjData *object)
{
    Vec spC;
    float var_f31;
    float var_f30;

    M433PlayerWork *work = object->data;
    s32 var_r29 = 0;
    M433PlayerWork *var_r28 = work->unk_14C->data;
    work->unk_1C = 0;
    work->unk_20 = 0;
    work->unk_28 = 0.0f;
    work->unk_24 = 0.0f;
    if ((work->unk_30 == 0) && (work->unk_70 != fn_1_10ECC(work->unk_14))) {
        work->unk_70 = fn_1_10ECC(work->unk_14);
        switch (fn_1_10ECC(work->unk_14)) {
            case 0:
                work->unk_6C = 0;
                work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
                work->unk_74 = 0;
                work->unk_38 = 0;
                work->unk_3C = work->unk_40 = 0;
                work->unk_128.y = 0.0f;
                if (work->unk_18 == fn_1_10F38(work->unk_14)) {
                    if (fn_1_10F00(work->unk_14) != 0) {
                        work->unk_128.z = 0.0f;
                        work->unk_128.x = 840.00006f;
                        work->unk_74 = 1;
                        work->unk_38 = 1;
                    }
                    else {
                        work->unk_128.z = 140.0f;
                        work->unk_128.x = 540.2f;
                    }
                }
                else {
                    work->unk_128.z = -140.0f;
                    work->unk_128.x = 385.1f;
                }
                work->unk_A4 = work->unk_A8 = -90.0f;
                work->unk_AC = 1.0f;
                work->unk_B0 = 1.0f;
                if (work->unk_14 == 0) {
                    work->unk_128.x *= -1.0f;
                    work->unk_A4 = work->unk_A8 = 90.0f;
                }
                work->unk_0C = -1;
                work->unk_34 = 1;
                work->unk_88 = work->unk_8C = 0;
                work->unk_7C = work->unk_78 = work->unk_80 = 0;
                break;
            case 1:
            case 2:
                if (work->unk_74 == 1) {
                    work->unk_34 = 0;
                };
                break;
            case 3:
                work->unk_74 = 2;
                work->unk_7C = work->unk_78 = work->unk_80 = 0;
                work->unk_34 = 0;
                break;
            case 4:
            case 5:
                work->unk_74 = 3;
                break;
            case 6:
            case 7:
                if (fn_1_10F6C(work->unk_14) != 0) {
                    fn_1_B4D4(object, 0x13);
                    if (work->unk_04 >= 0) {
                        HuAudFXPlay(lbl_1_data_150[work->unk_04][0]);
                    }
                    VECSubtract(&var_r28->unk_128, &work->unk_128, &spC);
                    work->unk_A8 = atan2d(spC.x, spC.z);
                    work->unk_AC = 0.15f;
                    work->unk_B0 = 0.0f;
                }
                else {
                    fn_1_B4D4(object, 0x14);
                }
                work->unk_74 = 4;
                break;
            default:
                break;
        }
    }
    if (fn_1_216C() == 2) {
        if (work->unk_2C != 0) {
            fn_1_74D4(object);
        }
        else {
            work->unk_20 = HuPadBtn[GWPlayerCfg[object->work[0]].pad_idx];
            work->unk_1C = HuPadBtnDown[GWPlayerCfg[object->work[0]].pad_idx];
            var_f31 = HuPadStkX[GWPlayerCfg[object->work[0]].pad_idx];
            var_f30 = -HuPadStkY[GWPlayerCfg[object->work[0]].pad_idx];
            work->unk_28 = atan2d(var_f31, var_f30);
            work->unk_24 = 0.013888889f * sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
            if (work->unk_24 > 1.0f) {
                work->unk_24 = 1.0f;
            }
        }
    }
    switch (work->unk_74) {
        case 0:
            fn_1_B4D4(object, 0);
            var_r29 = 1;
            break;
        case 1:
            fn_1_8F80(object);
            break;
        case 2:
            fn_1_8BD0(object);
            fn_1_AB88(object);
            fn_1_9688(object);
            break;
        case 3:
            fn_1_8BD0(object);
            fn_1_A618(object);
            fn_1_9688(object);
            break;
        case 4:
            work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
            work->unk_30 = 0;
            if (fn_1_B6E0(object) != 0) {
                work->unk_30 = 0;
                work->unk_74 = 0;
            }
            break;
    }
    VECAdd(&work->unk_128, &work->unk_134, &work->unk_128);
    if (fn_1_10ECC(work->unk_14) >= 2) {
        fn_1_B194(object);
    }
    fn_1_722C(object);
    if ((fn_1_216C() == 3) && (var_r29 != 0)) {
        work->unk_74 = 0;
        object->func = fn_1_682C;
    }
}

void fn_1_682C(omObjData *object)
{
    Vec sp1C;
    Vec sp10;
    float sp8[2];
    float var_f31;
    M433PlayerWork *var_r30;
    M433PlayerWork *var_r29;
    M433PlayerWork *var_r27;
    Vec *var_r26;
    s32 var_r25;
    M433PlayerWork *var_r24;
    s32 var_r23;

    M433PlayerWork *work = object->data;
    {
        Vec sp40[2] = { { 130.0f, 0.0f, -50.0f }, { 250.0f, 0.0f, 50.0f } };
        Vec sp28[2] = { { 150.0f, 0.0f, 100.0f }, { 300.0f, 0.0f, -100.0f } };
        var_r27 = work->unk_14C->data;
        VECAdd(&work->unk_128, &work->unk_134, &work->unk_128);
        fn_1_B194(object);
        fn_1_722C(object);
        switch (work->unk_74) {
            case 0:
                fn_1_B4D4(object, 0);
                if (fn_1_2244() != 0) {
                    if (work->unk_18 == 0) {
                        var_r23 = 1;
                        if (work->unk_14 == 0) {
                            sp40[0].x *= -1.0f;
                            sp40[1].x *= -1.0f;
                            sp28[0].x *= -1.0f;
                            sp28[1].x *= -1.0f;
                        }
                        var_r30 = work;
                        var_r29 = var_r27;
                        var_r26 = sp40;
                        work->unk_84 = var_r27->unk_84 = 0;
                        if (lbl_1_data_3F0[var_r30->unk_00] != lbl_1_data_3F0[var_r29->unk_00]) {
                            if (lbl_1_data_3F0[var_r30->unk_00] < lbl_1_data_3F0[var_r29->unk_00]) {
                                var_r24 = var_r30;
                                var_r30 = var_r29;
                                var_r29 = var_r24;
                            }
                            var_f31 = fn_1_11130(&var_r30->unk_128, &sp40[0], &var_r29->unk_128, &sp40[1]);
                            sp8[0] = 0.8f * (var_r30->unk_120 + var_r29->unk_120);
                            if (var_f31 < sp8[0]) {
                                var_r26 = sp28;
                                work->unk_84 = var_r27->unk_84 = 1;
                                OSReport("Escape!\n");
                            }
                            else {
                                var_r23 = 0;
                                OSReport("Direct!\n");
                            }
                        }
                        if (var_r23 != 0) {
                            var_r30 = work;
                            var_r29 = var_r27;
                            for (var_r25 = 0; var_r25 < 2; var_r25++) {
                                sp8[var_r25] = fn_1_11130(&var_r30->unk_128, &var_r26[var_r25 & 1], &var_r29->unk_128, &var_r26[(var_r25 + 1) & 1]);
                            }
                            if (sp8[0] < sp8[1]) {
                                var_r24 = var_r30;
                                var_r30 = var_r29;
                                var_r29 = var_r24;
                            }
                        }
                        var_r30->unk_140 = var_r26[0];
                        var_r30->unk_140.z -= var_r30->unk_120;
                        var_r29->unk_140 = var_r26[1];
                    }
                    work->unk_30 = work->unk_60 = work->unk_34 = 0;
                    if (work->unk_84 != 0) {
                        work->unk_74++;
                    }
                    else {
                        work->unk_74 += 2;
                    }
                    work->unk_88 = 0;
                    break;
                }
                break;
            case 1:
                if (work->unk_84 == 1) {
                    VECSubtract(&work->unk_140, &work->unk_128, &sp10);
                    sp10.y = 0.0f;
                    var_f31 = VECMag(&sp10);
                    if (var_f31 < 20.0f) {
                        var_f31 = 0.01f;
                        work->unk_84++;
                    }
                    else {
                        if (VECMag(&sp10) >= 100.0f) {
                            var_f31 = 100.0f;
                        }
                        var_f31 = 0.2f + (0.008f * var_f31);
                    }
                    work->unk_28 = 180.0 * (atan2(sp10.x, sp10.z) / 3.141592653589793);
                    work->unk_24 = var_f31;
                    fn_1_8BD0(object);
                }
                else if (work->unk_84 == 2) {
                    fn_1_BAE0(object, 0);
                    if ((work->unk_18 == 0) && (var_r27->unk_84 != 0)) {
                        if (work->unk_14 == 0) {
                            sp40[0].x *= -1.0f;
                            sp40[1].x *= -1.0f;
                        }
                        var_r30 = work;
                        var_r29 = var_r27;
                        if (lbl_1_data_3F0[var_r30->unk_00] < lbl_1_data_3F0[var_r29->unk_00]) {
                            var_r24 = var_r30;
                            var_r30 = var_r29;
                            var_r29 = var_r24;
                        }
                        var_r30->unk_140 = sp40[0];
                        var_r30->unk_140.z -= var_r30->unk_120;
                        var_r29->unk_140 = sp40[1];
                        work->unk_84 = var_r27->unk_84 = 3;
                    }
                }
                if (work->unk_84 == 3) {
                    work->unk_74++;
                    work->unk_88 = 0;
                    return;
                }
                break;
            case 2:
                VECSubtract(&work->unk_140, &work->unk_128, &sp10);
                sp10.y = 0.0f;
                var_f31 = VECMag(&sp10);
                if (var_f31 < 10.0f) {
                    var_f31 = 0.01f;
                }
                else {
                    if (VECMag(&sp10) >= 100.0f) {
                        var_f31 = 100.0f;
                    }
                    var_f31 = 0.2f + (0.008f * var_f31);
                }
                work->unk_28 = atan2d(sp10.x, sp10.z);
                work->unk_24 = var_f31;
                fn_1_8BD0(object);
                if ((work->unk_24 < 0.02f) || (work->unk_88 > 300.0f)) {
                    work->unk_A8 = 0.0f;
                    work->unk_AC = 0.15f;
                    work->unk_B0 = 0.0f;
                    work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
                    fn_1_21E4(object->work[0]);
                    work->unk_74++;
                    return;
                }
                break;
            case 3:
                if (fn_1_2184() == 1) {
                    if (fn_1_10FA4(work->unk_14) != 0) {
                        fn_1_B4D4(object, 0x11);
                        if (work->unk_04 >= 0) {
                            HuAudFXPlay(lbl_1_data_150[work->unk_04][0]);
                        }
                    }
                    else {
                        fn_1_B4D4(object, 0x12);
                        if (work->unk_04 >= 0) {
                            HuAudFXPlay(lbl_1_data_150[work->unk_04][1]);
                        }
                    }
                    work->unk_74++;
                    return;
                }
                fn_1_BAE0(object, 0);
                return;
            case 4:
                if (fn_1_10FA4(work->unk_14) != 0) {
                    sp1C.x = Center.x + (CZoom * (sind(CRot.y) * cosd(CRot.x)));
                    sp1C.y = Center.y + (CZoom * -sind(CRot.x));
                    sp1C.z = Center.z + (CZoom * (cosd(CRot.y) * cosd(CRot.x)));
                    VECSubtract(&sp1C, &work->unk_128, &sp10);
                    work->unk_A8 = atan2d(sp10.x, sp10.z);
                }
                if (fn_1_B6E0(object) != 0) {
                    fn_1_2214(object->work[0]);
                    work->unk_74++;
                }
                break;
        }
    }
}

char *lbl_1_data_450[6] = {
    "itemhook_R",
    "itemhook_r",
    "itemhook_R",
    "itemhook_R",
    "itemhook_r",
    "itemhook_r",
};
s32 lbl_1_data_468[9] = { 0, 0, 1, 1, 1, 1, 1, 0, 1 };
float lbl_1_data_48C[0x12] = {
    0.0f,
    0.6666667f,
    2.1666667f,
    2.0f,
    1.0f,
    7.0000005f,
    1.5000001f,
    1.5000001f,
    3.0000002f,
    0.0f,
    0.0f,
    1e-45f,
    0.0f,
    0.0f,
    1e-45f,
    0.0f,
    0.0f,
    1e-45f,
};
Vec lbl_1_data_4D4[9] = {
    { 0.0f, 0.0f, 1.0f },
    { 0.0f, 1.5f, 1.0f },
    { 236.5f, 0.0f, 1300.0f },
    { 0.0f, 1.5f, 1.0f },
    { 0.0f, 1.8f, 1.0f },
    { 231.0f, 0.0f, 1500.0f },
    { 231.0f, 0.0f, 1000.0f },
    { 0.0f, 1.2f, 1.0f },
    { 0.0f, 0.8f, 1.0f },
};
float lbl_1_data_540[9] = { 1.0f, 1.0f, 3.0f, 1.0f, 1.0f, 4.0f, 2.0f, 1.0f, 1.0f };

void fn_1_722C(omObjData *object)
{
    Vec sp8;

    M433PlayerWork *work = object->data;
    work->unk_9C++;
    work->unk_88++;
    object->trans.x = work->unk_128.x;
    object->trans.y = work->unk_128.y;
    object->trans.z = work->unk_128.z;
    work->unk_AC = work->unk_AC + work->unk_B0;
    if (work->unk_AC > 0.45f) {
        work->unk_AC = 0.45f;
    }
    work->unk_A4 = fn_1_26C4(work->unk_A4, work->unk_A8, work->unk_AC);
    object->rot.y = work->unk_A4;
    Hu3DModelPosSet(object->model[1], work->unk_128.x, 11.0f, work->unk_128.z);
    work->unk_BC += 3.0000002f;
    if (work->unk_BC >= 360.0f) {
        work->unk_BC -= 360.0f;
    }
    Hu3DModelRotSet(object->model[1], 0.0f, work->unk_BC, 0.0f);
    work->unk_B8 = 0.0f;
    if (fn_1_216C() == 2) {
        if (((fn_1_10EA4() == 4) || (fn_1_10EA4() == 3)) && (work->unk_14 == fn_1_10740(&sp8)) && (fn_1_10FDC() != 0) && (fn_1_10FDC() < 3)
            && (work->unk_60 == 0) && (fn_1_11004(work->unk_14, work->unk_18) != 0)) {
            work->unk_B8 = 1.0f;
        }
        if (work->unk_74 == 1) {
            work->unk_B8 = 1.0f;
        }
    }
    work->unk_B4 += 0.1f * (work->unk_B8 - work->unk_B4);
    Hu3DModelScaleSet(object->model[1], work->unk_B4, 1.0f, work->unk_B4);
    if ((work->unk_B8 <= 0.0f) && (work->unk_B4 < 0.1f)) {
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
        work->unk_B4 = 0.0f;
        return;
    }
    Hu3DModelAttrReset(object->model[1], HU3D_ATTR_DISPOFF);
}

void fn_1_74D4(omObjData *object)
{
    Vec sp1C;
    Vec sp10;
    M433PlayerWork *spC;
    float var_f31;

    M433PlayerWork *work = object->data;
    s32 var_r29 = 1;
    s32 sp8 = 0;
    spC = work->unk_14C->data;
    switch (work->unk_74) {
        case 0:
            work->unk_6C = 0;
            fn_1_873C(object);
            break;
        case 1:
            if (work->unk_3C != 0) {
                work->unk_1C = work->unk_1C | 0x100;
                work->unk_DC = frandmod(0x168);
                work->unk_E0 = 0.3f + (0.00040000002f * (work->unk_C0 * frandmod(0x3E8)));
                work->unk_E4 = 0;
                if (frandmod(0x3E8) > (300.0f + (500.0f * work->unk_C0))) {
                    work->unk_E4 = 1;
                }
            }
            if (fn_1_10614(&sp1C) != 0) {
                if (work->unk_E4 != 0) {
                    if ((fabs(sp1C.z) > 1.100000023841858) || (sp1C.x > 1.1f)) {
                        work->unk_E0 = 0.0f;
                    }
                }
                else {
                    if ((fabs(sp1C.z) > 0.949999988079071) || (sp1C.x > 0.95f)) {
                        work->unk_E0 = 0.0f;
                    }
                }
            }
            work->unk_28 = work->unk_DC;
            work->unk_24 = work->unk_E0;
            if (work->unk_40 != 0) {
                if (work->unk_D0++ >= work->unk_CC) {
                    work->unk_1C = work->unk_1C | 0x100;
                }
            }
            else if (work->unk_60 != 0) {
                work->unk_CC = ((60.0f * (0.35f * work->unk_C0)) / 1000.0f) * frandmod(0x3E8);
                work->unk_D0 = 0;
            }
            fn_1_873C(object);
            break;
        case 2:
            work->unk_F0 = 0;
            if (frandmod(0x3E8) < (300.0f * work->unk_C0)) {
                work->unk_F0 = 1;
            }
            fn_1_8408(object);
            if (work->unk_F4 != 0) {
                if (fn_1_10EA4() == 2) {
                    work->unk_F4 = 0;
                    work->unk_F8 = 0;
                }
                if (work->unk_14 == fn_1_107B0(&sp1C)) {
                    work->unk_D8++;
                }
                if ((work->unk_14 == fn_1_107B0(&sp1C)) && (work->unk_F8 == 0)) {
                    fn_1_10B20(0.9f, &work->unk_108);
                    work->unk_108.x = 115.0f;
                    if (work->unk_14 == 0) {
                        work->unk_108.x *= -1.0f;
                    }
                    work->unk_F8++;
                }
                if (work->unk_F8 == 1) {
                    if ((work->unk_D8 >= (0.5f * work->unk_D4)) && (fn_1_10D24(&work->unk_108) != 0)) {
                        work->unk_108.x = 115.0f;
                        if (work->unk_14 == 0) {
                            work->unk_108.x *= -1.0f;
                        }
                        work->unk_F8++;
                    }
                }
                else if ((work->unk_F8 == 2) && ((work->unk_D8 >= work->unk_D4) || (work->unk_14 == fn_1_10740(&sp1C)))) {
                    work->unk_1C = work->unk_1C | 0x200;
                    work->unk_F4 = 0;
                    work->unk_F8 = 0;
                }
            }
            if ((work->unk_14 == fn_1_107B0(&sp1C)) && (fn_1_10900() >= (60.0f * (0.8f - (0.4f * work->unk_C0)))) && (work->unk_6C != 0)) {
                VECSubtract(&sp1C, &work->unk_128, &sp10);
                sp10.y = 0.0f;
                var_f31 = VECMag(&sp10);
                if (VECMag(&sp10) >= 20.0f) {
                    if (var_f31 >= 50.0f) {
                        var_f31 = 50.0f;
                    }
                    work->unk_28 = atan2d(sp10.x, sp10.z);
                    work->unk_24 = var_f31 / 50.0f;
                }
                if ((fn_1_10848() < (0.8f - (0.6f * work->unk_C0))) && ((work->unk_44 != 0) || ((work->unk_48 != 0) && (work->unk_EC != 0)))) {
                    work->unk_1C = work->unk_1C | 0x100;
                }
                var_r29 = 0;
            }
            if (work->unk_F8 != 0) {
                VECSubtract(&work->unk_108, &work->unk_128, &sp10);
                sp10.y = 0.0f;
                var_f31 = VECMag(&sp10);
                if (var_f31 >= 10.0f) {
                    if (var_f31 >= 50.0f) {
                        var_f31 = 50.0f;
                    }
                    work->unk_28 = atan2d(sp10.x, sp10.z);
                    work->unk_24 = var_f31 / 50.0f;
                }
                else {
                    work->unk_28 = 90.0f;
                    if (work->unk_14 != 0) {
                        work->unk_28 *= -1.0f;
                    }
                    work->unk_24 = 0.01f;
                }
                var_r29 = 0;
            }
            if (var_r29 != 0) {
                VECSubtract(&work->unk_FC, &work->unk_128, &sp10);
                sp10.y = 0.0f;
                var_f31 = VECMag(&sp10);
                var_f31 -= 100.0f * (1.25f * (2.0f - work->unk_C0));
                if (var_f31 >= 10.0f) {
                    if (var_f31 >= 70.0f) {
                        var_f31 = 70.0f;
                    }
                    work->unk_28 = atan2d(sp10.x, sp10.z);
                    work->unk_24 = var_f31 / 70.0f;
                    break;
                }
                work->unk_28 = 90.0f;
                if (work->unk_14 != 0) {
                    work->unk_28 *= -1.0f;
                    break;
                }
            }
            break;
        case 3:
            fn_1_8408(object);
            fn_1_873C(object);
            if (work->unk_14 == fn_1_10740(&sp1C)) {
                if (work->unk_68 == 0) {
                    if (fn_1_11004(work->unk_14, work->unk_18) != 0) {
                        VECSubtract(&sp1C, &work->unk_128, &sp10);
                        sp10.y = 0.0f;
                        var_f31 = VECMag(&sp10);
                        if (var_f31 >= 30.000002f) {
                            if (var_f31 >= 70.0f) {
                                var_f31 = 70.0f;
                            }
                            work->unk_24 = var_f31 / 70.0f;
                            work->unk_28 = atan2d(sp10.x, sp10.z);
                        }
                    }
                    if ((((work->unk_6C == 0) && (fn_1_10EA4() == 3) && (work->unk_F0 != 0)) || ((work->unk_6C != 0) && (fn_1_10EA4() == 4)))
                        && (work->unk_5C != 0)) {
                        work->unk_1C = work->unk_1C | 0x200;
                        work->unk_E8 = 0;
                        if (frandmod(0x3E8) < (s32)(300.0f * (work->unk_C0 - 0.4f))) {
                            work->unk_E8 = fn_1_8938(work->unk_14, &work->unk_114);
                            work->unk_DC = 0.0f;
                            work->unk_E0 = 0.0f;
                            work->unk_E4 = 0;
                        }
                        if (work->unk_E8 == 0) {
                            work->unk_DC = frandmod(0x168);
                            work->unk_E0 = 0.3f + (0.00040000002f * (work->unk_C0 * frandmod(0x3E8)));
                            work->unk_E4 = 0;
                            if (frandmod(0x3E8) > (300.0f + (500.0f * work->unk_C0))) {
                                work->unk_E4 = 1;
                            }
                        }
                    }
                    if ((work->unk_4C != 0) || (work->unk_44 != 0) || (work->unk_48 != 0)) {
                        work->unk_1C = work->unk_1C | 0x100;
                        break;
                    }
                }
                else {
                    if (fn_1_10614(&sp1C) != 0) {
                        if (work->unk_E8 != 0) {
                            VECSubtract(&work->unk_114, &sp1C, &sp10);
                            sp10.y = 0.0f;
                            var_f31 = VECMag(&sp10);
                            if (var_f31 < 0.05f) {
                                work->unk_DC = 0.0f;
                                work->unk_E0 = 0.0f;
                            }
                            else {
                                if (work->unk_14 != 0) {
                                    sp10.x *= -1.0f;
                                }
                                work->unk_DC = atan2d(sp10.x, sp10.z);
                                work->unk_E0 = 1.0f;
                            }
                        }
                        if (work->unk_E4 != 0) {
                            if ((fabs(sp1C.z) > 1.100000023841858) || (sp1C.x > 1.1f)) {
                                work->unk_E0 = 0.0f;
                            }
                        }
                        else {
                            if ((fabs(sp1C.z) > 0.949999988079071) || (sp1C.x > 0.95f)) {
                                work->unk_E0 = 0.0f;
                            }
                        }
                    }
                    work->unk_28 = work->unk_DC;
                    work->unk_24 = work->unk_E0;
                    if (work->unk_54 != 0) {
                        if (work->unk_D0++ >= work->unk_CC) {
                            work->unk_1C |= 0x100;
                            break;
                        }
                    }
                    else {
                        work->unk_CC = ((60.0f * (0.35f * work->unk_C0)) / 1000.0f) * frandmod(0x3E8);
                        work->unk_D0 = 0;
                    }
                }
            }
            break;
    }
}

void fn_1_8408(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;

    M433PlayerWork *work = object->data;
    M433PlayerWork *var_r30 = work->unk_14C->data;

    if (var_r30->unk_2C == 0) {
        var_r30->unk_C0 = work->unk_C0 - 0.1f;
    }
    if ((work->unk_14 == fn_1_107B0(&sp14)) && (fn_1_108C4() >= 12.0f)) {
        if (((var_r30->unk_6C == 0) && (work->unk_6C == 0)) || (fn_1_108C4() < 0x3E8)) {
            if ((work->unk_30 == 0) || (var_r30->unk_30 == 0)) {
                VECSubtract(&sp14, &work->unk_128, &sp8);
                sp8.y = 0.0f;
                var_f31 = VECMag(&sp8) - (100.0f * (2.0f * work->unk_C0));
                VECSubtract(&sp14, &var_r30->unk_128, &sp8);
                sp8.y = 0.0f;
                var_f30 = VECMag(&sp8) - (100.0f * (2.0f * var_r30->unk_C0));
                if ((work->unk_30 != 0) || (work->unk_60 != 0)) {
                    var_f31 = 2000.0f;
                }
                if ((var_r30->unk_30 != 0) || (var_r30->unk_60 != 0)) {
                    var_f30 = 2000.0f;
                }
                if (var_f31 >= 300.0f) {
                    var_r30->unk_F4 = 0;
                }
                if (var_f30 >= 300.0f) {
                    work->unk_F4 = 0;
                }
                if (work->unk_F4 != 0) {
                    var_f31 += 300.0f;
                }
                if (var_r30->unk_F4 != 0) {
                    var_f30 += 300.0f;
                }
                var_r30->unk_6C = work->unk_6C = 0;
                if (var_f31 <= var_f30) {
                    work->unk_6C = 1;
                    work->unk_F4 = 0;
                }
                else {
                    var_r30->unk_6C = 1;
                    var_r30->unk_F4 = 0;
                }
                if (work->unk_F4 == 0) {
                    work->unk_F8 = 0;
                }
                if (var_r30->unk_F4 == 0) {
                    var_r30->unk_F8 = 0;
                }
            }
        }
        else if (fn_1_10FDC() == 1) {
            work->unk_6C = fn_1_11004(work->unk_14, work->unk_18) == 0;
            var_r30->unk_6C = work->unk_6C == 0;
        }
    }
    else if (work->unk_14 != fn_1_10740(&sp14)) {
        var_r30->unk_6C = work->unk_6C = 0;
    }
}

void fn_1_873C(omObjData *object)
{
    M433PlayerWork *work = object->data;
    work->unk_EC = 0;
    if (frandmod(0x3E8) < (600.0f * work->unk_C0)) {
        work->unk_EC = 1;
    }
    work->unk_F4 = 0;
    work->unk_F8 = 0;
    if ((work->unk_18 != fn_1_10F38(work->unk_14)) && (work->unk_74 != 0) && (frandmod(0x3E8) < (500.0f * work->unk_C0))) {
        work->unk_F4 = 1;
        work->unk_D4 = ((60.0f * (0.5f * work->unk_C0)) / 1000.0f) * frandmod(0x3E8);
        work->unk_D8 = 0;
    }
    if (work->unk_18 == fn_1_10F38(work->unk_14)) {
        work->unk_FC.z = 140.0f;
        work->unk_FC.x = 540.2f;
    }
    else {
        work->unk_FC.z = -140.0f;
        work->unk_FC.x = 300.5f;
    }
    if (work->unk_14 == 0) {
        work->unk_FC.x *= -1.0f;
    }
}

s32 fn_1_8938(u32 var_r27, Vec *var_r29)
{
    Vec sp2C[2];
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    u32 var_r31;
    u32 var_r30;

    for (var_r31 = 0, var_r30 = 0; (var_r30 < 4) && (var_r31 < 2); var_r30++) {
        M433PlayerWork *work = lbl_1_bss_7D0[var_r30]->data;
        if (work->unk_14 != var_r27) {
            sp2C[var_r31] = work->unk_128;
            sp2C[var_r31].y = 0.0f;
            var_r31++;
        }
    }
    if (var_r31 < 2) {
        return 0;
    }
    if (var_r27 == 1) {
        sp2C[0].x *= -1.0f;
        sp2C[1].x *= -1.0f;
    }
    var_f29 = 47.0f;
    var_f28 = 70.0f;
    var_f30 = -1.0f;
    sp14.z = -350.0f;
    sp14.y = 0.0f;
    for (var_r30 = 0; var_r30 <= 0xA; var_r30++) {
        sp14.x = 230.0f;
        for (var_r31 = 0; var_r31 <= 0xA; var_r31++) {
            VECSubtract(&sp14, &sp2C[0], &sp20);
            var_f31 = VECMag(&sp20);
            VECSubtract(&sp14, &sp2C[1], &sp20);
            var_f31 *= VECMag(&sp20);
            if (var_f31 > var_f30) {
                var_f30 = var_f31;
                sp8 = sp14;
            }
            sp14.x += var_f29;
        }
        sp14.z += var_f28;
    }
    *var_r29 = sp8;
    var_r29->x -= 465.0f;
    var_r29->x *= 0.004255319f;
    var_r29->z *= 0.0028571428f;
    return 1;
}

void fn_1_8BD0(omObjData *object)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;

    M433PlayerWork *work = object->data;
    s32 var_r29 = 1;
    if ((work->unk_30 == 0) && (work->unk_60 == 0)) {
        if ((work->unk_24 > 0.0f) && (work->unk_34 == 0)) {
            work->unk_A8 = work->unk_28;
        }
        if ((work->unk_24 > 0.05f) && (work->unk_34 == 0)) {
            work->unk_134.x = 0.01666666753590107 * (550.0 * (work->unk_24 * sind(work->unk_28)));
            work->unk_134.z = 0.01666666753590107 * (550.0 * (work->unk_24 * cosd(work->unk_28)));
            if (work->unk_2C != 0) {
                work->unk_AC = 0.1f;
            }
            else {
                work->unk_AC = 0.2f;
            }
            work->unk_B0 = 0.0f;
            if (fn_1_B7AC(object) != 0) {
                var_f30 = 0.5f;
                if (work->unk_0C == 2) {
                    var_f30 = 0.45f;
                }
                if (work->unk_24 > var_f30) {
                    fn_1_B4D4(object, 2);
                    var_f31 = work->unk_24;
                }
                else {
                    fn_1_B4D4(object, 1);
                    var_f31 = work->unk_24 / var_f30;
                }
                if (work->unk_04 < 0) {
                    CharModelMotionSpeedSet(work->unk_00, var_f31);
                }
                else {
                    Hu3DMotionSpeedSet(object->model[0], var_f31);
                }
            }
            if ((work->unk_24 > 0.5f) && (((work->unk_88 + 0xF) & 0xF) == 0)) {
                fn_1_D888(&work->unk_128, 0.2f);
            }
        }
        else {
            work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
            if ((work->unk_5C != 0) && (fn_1_10FDC() >= 2)) {
                fn_1_B4D4(object, 0x10);
            }
            else if (work->unk_4C != 0) {
                fn_1_B4D4(object, 0xF);
            }
            else if (work->unk_44 != 0) {
                fn_1_B4D4(object, 0xE);
            }
            else {
                fn_1_BAE0(object, 0);
            }
            if ((var_r29 != 0) && (work->unk_24 == 0.0f)) {
                fn_1_10B20(0.0f, &sp14);
                VECSubtract(&sp14, &work->unk_128, &sp8);
                work->unk_A8 = atan2d(sp8.x, sp8.z);
                work->unk_AC = 0.1f;
                work->unk_B0 = 0.0f;
            }
        }
    }
}

void fn_1_8F80(omObjData *object)
{
    Vec sp1C;
    Vec sp10;
    float var_f31;
    float var_f30;

    M433PlayerWork *work = object->data;
    s32 var_r29 = work->unk_40;
    {
        s32 sp8[2] = { 0x6A4, 0x6A5 };
        work->unk_3C = 0;
        work->unk_40 = 0;
        if (work->unk_04 < 0) {
            char *var_r28 = CharModelHookNameGet(work->unk_00, 4, 0);
            Hu3DModelObjPosGet(object->model[0], var_r28, &sp10);
        }
        else {
            Hu3DModelObjPosGet(object->model[0], lbl_1_data_450[work->unk_04], &sp10);
        }
        switch (work->unk_8C) {
            case 0:
                work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
                work->unk_8C++;
                work->unk_88 = 0;

            case 1:
                work->unk_30 = 0;
                work->unk_38 = 1;
                fn_1_B4D4(object, 3);
                fn_1_FE8C(&sp10, 0, work->unk_14, work->unk_18);
                if (fn_1_10ECC(work->unk_14) != 1) {
                    work->unk_88 = 0;
                    break;
                }
                if (work->unk_34 == 0) {
                    work->unk_3C = 1;
                    if ((work->unk_1C & 0x100) || (work->unk_88 > 300.0f)) {
                        fn_1_B4D4(object, 4);
                        work->unk_30 = 1;
                        work->unk_8C++;
                        work->unk_88 = 0;
                    }
                }
                break;
            case 2:
                if (work->unk_60 == 0) {
                    work->unk_134.x = 1.6666667461395264 * (2.0 * sind((10.0f + (4.285714f * work->unk_88))));
                    if (work->unk_14 != 0) {
                        work->unk_134.x *= -1.0f;
                    }
                }
                if ((work->unk_88 >= 9.0f) && (work->unk_38 != 0)) {
                    if (work->unk_14 != 0) {
                        var_f30 = -1.0f;
                    }
                    else {
                        var_f30 = 1.0f;
                    }
                    sp1C.x = object->trans.x + (250.0f * var_f30);
                    sp1C.y = 80.0f + object->trans.y;
                    sp1C.z = sp10.z;
                    fn_1_FE8C(&sp1C, 1, work->unk_14, work->unk_18);
                    work->unk_38 = 0;
                }
                else if (work->unk_88 >= 28.0f) {
                    var_f31 = 0.5f;
                    work->unk_124 = (2.0f * -(350.0f - lbl_1_data_E0[work->unk_00])) / (var_f31 * var_f31);
                    work->unk_134.y = 0.016666668f * (-work->unk_124 * var_f31);
                    work->unk_60 = 1;
                    work->unk_8C++;
                    work->unk_88 = 0;
                    fn_1_D888(&work->unk_128, 0.5f);
                }
                if (work->unk_38 == 0) {
                    fn_1_10260(work->unk_28, work->unk_24, work->unk_14, 0, &sp1C);
                    break;
                }
                fn_1_FE8C(&sp10, 0, work->unk_14, work->unk_18);
                break;
            case 3:
                work->unk_134.y += 0.016666668f * (0.016666668f * work->unk_124);
                if ((work->unk_88 > 27.0f) && (work->unk_88 < 51.0f)) {
                    work->unk_40 = 1;
                }
                fn_1_10260(work->unk_28, work->unk_24, work->unk_14, work->unk_40, &sp1C);
                if (((work->unk_40 != 0) && ((work->unk_1C & 0x100) != 0)) || ((work->unk_40 == 0) && (var_r29 != 0))) {
                    fn_1_B4D4(object, 5);
                    if (work->unk_40 == 0) {
                        fn_1_1070C();
                    }
                    fn_1_FE8C(&sp1C, 2, work->unk_14, work->unk_18);
                    work->unk_40 = 0;
                    work->unk_8C = 5;
                    work->unk_88 = 0;
                    HuAudFXPlay(sp8[work->unk_14]);
                }
                break;
            case 4:
                if (work->unk_88 >= 12.0f) {
                    work->unk_60 = 0;
                    work->unk_8C = 1;
                    work->unk_88 = 0;
                }
                break;
            case 5:
                work->unk_134.y += 0.016666668f * (0.016666668f * work->unk_124);
                if (work->unk_128.y <= 0.0f) {
                    work->unk_60 = 0;
                    fn_1_D888(&work->unk_128, 0.5f);
                    work->unk_30 = 0;
                    work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
                }
                break;
        }
    }
}

void fn_1_9688(omObjData *object)
{
    Vec sp2C;
    Vec sp20;
    float var_f31;
    float var_f30;
    float var_f29;

    M433PlayerWork *work = object->data;
    s32 sp38[3][3] = { { 3, 4, 6 }, { 3, 4, 6 }, { 3, 4, 7 } };
    s32 sp18[2] = { 0x6AD, 0x6AE };
    s32 sp10[2] = { 0x6A6, 0x6A7 };
    s32 sp8[2] = { 0x6AA, 0x6AB };
    M433PlayerWork *var_r29 = work->unk_14C->data;

    work->unk_4C = 0;
    work->unk_44 = 0;
    work->unk_48 = 0;
    if (work->unk_60 == 0) {
        switch (work->unk_7C) {
            case 0:
                if ((work->unk_7C == 0) && (work->unk_78 == 0) && (work->unk_80 == 0)
                    && (work->unk_30 = 0, work->unk_64 = 0, ((work->unk_34 == 0) != 0)) && (work->unk_14 == fn_1_10740(&sp2C))
                    && (fn_1_11004(work->unk_14, work->unk_18) != 0) && (fn_1_10FDC() < 3)) {
                    work->unk_140 = sp2C;
                    var_f31 = fn_1_10848();
                    if ((var_f31 <= 0.8f) && (var_f31 >= 0.02f) && (var_r29->unk_64 == 0)) {
                        VECSubtract(&sp2C, &work->unk_128, &sp20);
                        sp20.y = 0.0f;
                        var_f30 = VECMag(&sp20);
                        work->unk_98 = var_f30;
                        if (var_f30 <= 200.0f) {
                            if ((var_f31 >= 0.2f) && (var_f30 <= 70.0f) && (var_f31 >= (0.2f + (0.001f * var_f30))) && (fn_1_10FDC() >= 1)) {
                                work->unk_4C = 1;
                            }
                            if ((var_f31 >= 0.02f) && (var_f30 <= 100.0f) && (var_f31 >= (0.02f + (0.001f * var_f30)))) {
                                work->unk_44 = 1;
                            }
                            if ((var_f31 >= 0.1f) && (var_f31 <= 0.3f) && (var_f30 > 100.0f) && (var_f30 <= 200.0f)
                                && (var_f31 >= (0.1f + (0.0002f * (var_f30 - 100.0f))))) {
                                work->unk_48 = 1;
                            }
                        }
                    }
                    if ((work->unk_1C & 0x100) != 0) {
                        work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
                        if (work->unk_4C != 0) {
                            work->unk_7C = 1;
                            var_f31 -= 0.12f;
                            work->unk_98 *= 0.014285714f;
                            fn_1_B4D4(object, 0xF);
                            fn_1_10B20(0.0f, &sp2C);
                        }
                        else if (work->unk_44 != 0) {
                            work->unk_7C = 2;
                            var_f31 -= 0.03f;
                            work->unk_98 *= 0.01f;
                            fn_1_B4D4(object, 0xE);
                            fn_1_10B20(0.0f, &sp2C);
                        }
                        else if (work->unk_48 != 0) {
                            work->unk_7C = 3;
                            var_f31 -= 0.03f;
                            work->unk_98 *= 0.005f;
                            fn_1_B4D4(object, 7);
                            fn_1_D888(&work->unk_128, 0.75f);
                            HuAudFXPlay(sp8[work->unk_14]);
                        }
                        else {
                            if (fn_1_10FDC() >= 1) {
                                fn_1_B4D4(object, 9);
                            }
                            else {
                                fn_1_B4D4(object, 6);
                            }
                            work->unk_7C = 4;
                        }
                        if (work->unk_7C < 4) {
                            work->unk_64 = 1;
                            if (var_f31 < 0.0f) {
                                var_f31 = 0.0f;
                            }
                            work->unk_90 = 60.0f * var_f31;
                        }
                        VECSubtract(&sp2C, &work->unk_128, &sp20);
                        work->unk_A8 = atan2d(sp20.x, sp20.z);
                        work->unk_AC = 0.2f;
                        work->unk_B0 = 0.0f;
                        work->unk_30 = 1;
                        work->unk_88 = 0;
                    }
                }
                break;
            case 1:
                if (work->unk_88 >= work->unk_90) {
                    if (work->unk_64 != 0) {
                        if (fn_1_10FDC() >= 2) {
                            sp2C.x = 350.0f;
                            sp2C.y = 11.0f;
                            sp2C.z = 0.0f;
                            if (work->unk_14 != 0) {
                                sp2C.x *= -1.0f;
                            }
                        }
                        else {
                            sp2C = var_r29->unk_128;
                            sp2C.y = 11.0f;
                            sp2C.x *= 0.5f;
                        }
                        var_f29 = frandmod(0x168);
                        var_f30 = 200.0f * work->unk_98;
                        sp2C.x += var_f30 * sind(var_f29);
                        sp2C.z += var_f30 * cosd(var_f29);
                        if (fn_1_10FDC() < 2) {
                            fn_1_10130(&sp2C, work->unk_14);
                        }
                        fn_1_FE8C(&sp2C, sp38[0][fn_1_10FDC()], work->unk_14, work->unk_18);
                        fn_1_D888(&work->unk_128, 0.0f);
                        HuAudFXPlay(sp10[work->unk_14]);
                    }
                    work->unk_64 = 0;
                    fn_1_B4D4(object, 9);
                    VECSubtract(&sp2C, &work->unk_128, &sp20);
                    work->unk_A8 = atan2d(sp20.x, sp20.z);
                    work->unk_AC = 0.1f;
                    work->unk_90 = 0x186A0;
                    work->unk_88 = 0;
                    break;
                }
                if (work->unk_90 < 0x2710) {
                    work->unk_134.x = 0.07f * (work->unk_140.x - work->unk_128.x);
                    work->unk_134.z = 0.07f * (work->unk_140.z - work->unk_128.z);
                    if (work->unk_64 == 0) {
                        work->unk_90 = 0;
                    }
                }
                else {
                    work->unk_134.x *= 0.7f;
                    work->unk_134.z *= 0.7f;
                    if (fn_1_B6E0(object) != 0) {
                        work->unk_7C = 0;
                    }
                }
                break;
            case 2:
                if (work->unk_88 >= work->unk_90) {
                    if (work->unk_64 != 0) {
                        switch (fn_1_10FDC()) {
                            case 0:
                                sp2C = var_r29->unk_128;
                                sp2C.y = 11.0f;
                                break;
                            case 1:
                                sp2C = var_r29->unk_128;
                                sp2C.y = 11.0f;
                                sp2C.x *= 0.5f;
                                break;
                            case 2:
                            default:
                                sp2C.x = 350.0f;
                                sp2C.y = 11.0f;
                                sp2C.z = 0.0f;
                                if (work->unk_14 != 0) {
                                    sp2C.x *= -1.0f;
                                }
                                break;
                        }
                        var_f29 = frandmod(0x168);
                        var_f30 = 200.0f * work->unk_98;
                        sp2C.x += var_f30 * sind(var_f29);
                        sp2C.z += var_f30 * cosd(var_f29);
                        if (fn_1_10FDC() < 2) {
                            fn_1_10130(&sp2C, work->unk_14);
                        }
                        fn_1_FE8C(&sp2C, sp38[1][fn_1_10FDC()], work->unk_14, work->unk_18);
                        fn_1_D888(&work->unk_128, 0.0f);
                        if (fn_1_10FDC() < 1) {
                            HuAudFXPlay(sp18[work->unk_14]);
                        }
                        else {
                            HuAudFXPlay(sp10[work->unk_14]);
                        }
                    }
                    work->unk_64 = 0;
                    fn_1_B4D4(object, 6);
                    VECSubtract(&sp2C, &work->unk_128, &sp20);
                    work->unk_A8 = atan2d(sp20.x, sp20.z);
                    work->unk_AC = 0.1f;
                    work->unk_90 = 0x186A0;
                    work->unk_88 = 0;
                    break;
                }
                if (work->unk_90 < 0x2710) {
                    work->unk_134.x = 0.07f * (work->unk_140.x - work->unk_128.x);
                    work->unk_134.z = 0.07f * (work->unk_140.z - work->unk_128.z);
                    if (work->unk_64 == 0) {
                        work->unk_90 = 0;
                        break;
                    }
                }
                else {
                    work->unk_134.x *= 0.7f;
                    work->unk_134.z *= 0.7f;
                    if (fn_1_B6E0(object) != 0) {
                        work->unk_7C = 0;
                        break;
                    }
                }
                break;
            case 3:
                if (work->unk_88 >= work->unk_90) {
                    if (work->unk_64 != 0) {
                        sp2C = work->unk_128;
                        sp2C.y = 11.0f;
                        VECSubtract(&var_r29->unk_128, &work->unk_128, &sp20);
                        var_f29 = 180.0 + (atan2d(sp20.x, sp20.z));
                        var_f29 += frandmod(0xB4) - 90.0f;
                        var_f30 = 200.0f * work->unk_98;
                        sp2C.x += var_f30 * sind(var_f29);
                        sp2C.z += var_f30 * cosd(var_f29);
                        fn_1_10130(&sp2C, work->unk_14);
                        fn_1_FE8C(&sp2C, sp38[2][fn_1_10FDC()], work->unk_14, work->unk_18);
                        if (fn_1_10FDC() < 1) {
                            HuAudFXPlay(sp18[work->unk_14]);
                        }
                        else {
                            HuAudFXPlay(sp10[work->unk_14]);
                        }
                    }
                    work->unk_64 = 0;
                    work->unk_90 = 0x186A0;
                    work->unk_88 = 0;
                    fn_1_D888(&work->unk_128, 1.3f);
                    break;
                }
                if (work->unk_90 < 0x2710) {
                    work->unk_134.x = 0.15f * (work->unk_140.x - work->unk_128.x);
                    work->unk_134.z = 0.15f * (work->unk_140.z - work->unk_128.z);
                    break;
                }
                work->unk_134.x *= 0.95f;
                work->unk_134.z *= 0.95f;
                if (fn_1_B6E0(object) != 0) {
                    fn_1_B4D4(object, 8);
                    work->unk_7C = 4;
                }
                break;
            case 4:
                work->unk_134.x *= 0.95f;
                work->unk_134.z *= 0.95f;
                if (fn_1_B6E0(object) != 0) {
                    work->unk_7C = 0;
                }
                break;
        }
    }
}

void fn_1_A618(omObjData *object)
{
    Vec sp20;
    Vec sp14;
    M433PlayerWork *sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    M433PlayerWork *work = object->data;
    s32 spC[2] = { 0x6A8, 0x6A9 };
    sp8 = work->unk_14C->data;
    work->unk_54 = 0;
    work->unk_5C = 0;
    switch (work->unk_80) {
        case 0:
            if ((work->unk_7C == 0) && (work->unk_78 == 0) && (work->unk_80 == 0) && (work->unk_30 = 0, work->unk_68 = 0, ((work->unk_34 == 0) != 0))
                && (fn_1_11004(work->unk_14, work->unk_18) != 0) && (fn_1_10FDC() < 3) && (work->unk_14 == fn_1_10740(&sp20))) {
                VECSubtract(&sp20, &work->unk_128, &sp14);
                sp14.y = 0.0f;
                if (!(VECMag(&sp14) > 500.0f)) {
                    fn_1_10B20(0.5f, &sp20);
                    sp20.y -= lbl_1_data_E0[work->unk_00];
                    VECSubtract(&sp20, &work->unk_128, &sp14);
                    sp14.y = 0.0f;
                    if ((VECMag(&sp14) < 200.0f) && (sp20.y >= 50.0f)) {
                        work->unk_5C = 1;
                    }
                    if (((work->unk_1C & 0x200) != 0) && (work->unk_5C != 0)) {
                        work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
                        fn_1_B4D4(object, 0xA);
                        work->unk_80 = 1;
                        work->unk_88 = 0;
                        work->unk_30 = 1;
                        if (work->unk_5C != 0) {
                            var_f30 = 0.5f;
                            work->unk_124 = (2.0f * -sp20.y) / (var_f30 * var_f30);
                            work->unk_134.y = 0.016666668f * (-work->unk_124 * var_f30);
                            VECSubtract(&sp20, &work->unk_128, &sp14);
                            sp14.y = 0.0f;
                            work->unk_134.x = 0.016666668f * (sp14.x / 0.5f);
                            work->unk_134.z = 0.016666668f * (sp14.z / 0.5f);
                            if (work->unk_14 != 0) {
                                var_f29 = -90.0f;
                            }
                            else {
                                var_f29 = 90.0f;
                            }
                            work->unk_A8 = var_f29;
                            work->unk_AC = 0.2f;
                            work->unk_B0 = 0.0f;
                            work->unk_68 = 1;
                        }
                        else {
                            work->unk_134.y = 14.833334f;
                        }
                        work->unk_60 = 1;
                        fn_1_D888(&work->unk_128, 0.75f);
                    }
                }
            }
            break;
        case 1:
            work->unk_134.y += 0.016666668f * (0.016666668f * work->unk_124);
            if (work->unk_68 != 0) {
                var_f31 = (0.016666668f * work->unk_88) - 0.35f;
                if ((var_f31 >= 0.0f) && (var_f31 < 0.4)) {
                    work->unk_54 = 1;
                    if ((work->unk_1C & 0x100) != 0) {
                        fn_1_B4D4(object, 0xB);
                        fn_1_10260(work->unk_28, work->unk_24, work->unk_14, work->unk_54, &sp20);
                        fn_1_FE8C(&sp20, 5, work->unk_14, work->unk_18);
                        work->unk_68 = 0;
                        work->unk_54 = 0;
                        HuAudFXPlay(spC[work->unk_14]);
                    }
                }
                else if (var_f31 > 0.0f) {
                    work->unk_68 = 0;
                    work->unk_54 = 0;
                }
                fn_1_10260(work->unk_28, work->unk_24, work->unk_14, work->unk_54, &sp20);
            }
            if (work->unk_128.y <= 0.0f) {
                fn_1_D888(&work->unk_128, 0.75f);
                work->unk_30 = 0;
                work->unk_80 = 0;
                work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
                work->unk_60 = 0;
                work->unk_68 = 0;
            }
            break;
    }
}

void fn_1_AB88(omObjData *object)
{
    Vec sp1C;
    Vec sp10;
    float var_f29;
    float var_f28;

    M433PlayerWork *work = object->data;
    s32 var_r30 = 0;
    s32 sp8[2] = { 0x6A8, 0x6A9 };
    M433PlayerWork *var_r28 = work->unk_14C->data;

    work->unk_58 = 0;
    switch (work->unk_78) {
        case 0:
            if ((work->unk_7C == 0) && (work->unk_78 == 0) && (work->unk_80 == 0) && (work->unk_30 = 0, work->unk_68 = 0, ((work->unk_34 == 0) != 0))
                && (work->unk_14 == fn_1_107B0(&sp1C)) && (fn_1_11060(work->unk_14) == 0)) {
                float var_f31 = work->unk_128.x;
                float var_f30;
                if (work->unk_14 == 0) {
                    var_f31 *= -1.0f;
                }
                if (!(var_f31 > 230.0f) && (fn_1_10EA4() != 2)) {
                    if (fn_1_10D24(&sp1C) != 0) {
                        var_r30 = 1;
                    }
                    if (var_r30 != 0) {
                        var_f31 = sp1C.z - work->unk_128.z;
                        if (var_f31 > 100.0f) {
                            var_f31 = 100.0f;
                        }
                        else if (var_f31 < -100.0f) {
                            var_f31 = -100.0f;
                        }
                        else {
                            work->unk_58 = 1;
                        }
                    }
                    if ((work->unk_1C & 0x200) != 0) {
                        work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
                        fn_1_B4D4(object, 0xA);
                        work->unk_78 = 1;
                        work->unk_88 = 0;
                        work->unk_30 = 1;
                        if (work->unk_14 != 0) {
                            var_f28 = -90.0f;
                        }
                        else {
                            var_f28 = 90.0f;
                        }
                        work->unk_A8 = var_f28;
                        work->unk_AC = 0.2f;
                        work->unk_B0 = 0.0f;
                        fn_1_D888(&work->unk_128, 0.75f);
                        var_f30 = 0.5f;
                        work->unk_124 = (2.0f * -(350.0f - lbl_1_data_E0[work->unk_00])) / (var_f30 * var_f30);
                        work->unk_134.y = 0.016666668f * (-work->unk_124 * var_f30);
                        work->unk_134.x = 0.016666668f * (-work->unk_128.x / 0.75f);
                        if (var_r30 != 0) {
                            work->unk_134.z = 0.016666668f * (var_f31 / 0.5f);
                        }
                        work->unk_60 = 1;
                        work->unk_58 = 0;
                    }
                }
            }
            break;
        case 1:
            work->unk_134.y += 0.016666668f * (0.016666668f * work->unk_124);
            if ((work->unk_14 == fn_1_10740(&sp1C)) && (fn_1_10FDC() == 0)) {
                fn_1_10B20(0.0f, &sp1C);
                if ((sp1C.x * work->unk_128.x) > 0.0f) {
                    sp1C.y = work->unk_128.y;
                    VECSubtract(&sp1C, &work->unk_128, &sp10);
                    if (VECMag(&sp10) < 60.000004f) {
                        if (frandmod(0x64) < 0x1E) {
                            fn_1_10740(&sp1C);
                            sp1C.x *= -0.5f;
                            fn_1_FE8C(&sp1C, 5, work->unk_14, work->unk_18);
                            HuAudFXPlay(sp8[work->unk_14]);
                        }
                        else {
                            fn_1_10740(&sp1C);
                            var_f29 = frandmod(0x168);
                            sp1C.x += 100.0 * (2.0 * sind(var_f29));
                            sp1C.z += 100.0 * (2.0 * cosd(var_f29));
                            fn_1_10130(&sp1C, work->unk_14);
                            fn_1_FE8C(&sp1C, 8, work->unk_14, work->unk_18);
                            HuAudFXPlay(sp8[work->unk_14]);
                        }
                        fn_1_B4D4(object, 0xD);
                        var_r28->unk_64 = 0;
                    }
                }
            }
            if (work->unk_128.y <= 0.0f) {
                fn_1_D888(&work->unk_128, 0.75f);
                work->unk_30 = 0;
                work->unk_78 = 0;
                work->unk_134.x = work->unk_134.y = work->unk_134.z = 0.0f;
                work->unk_60 = 0;
            }
            break;
    }
}

void fn_1_B194(omObjData *object)
{
    Vec sp8;
    float var_f31;
    M433PlayerWork *var_r31;
    M433PlayerWork *var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;

    for (var_r27 = 0; var_r27 < 2; var_r27++) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            var_r31 = lbl_1_bss_7D0[var_r29]->data;
            for (var_r28 = 0; var_r28 < 4; var_r28++) {
                if (var_r29 != var_r28) {
                    var_r30 = lbl_1_bss_7D0[var_r28]->data;
                    VECSubtract(&var_r31->unk_128, &var_r30->unk_128, &sp8);
                    sp8.y = 0.0f;
                    var_f31 = VECMag(&sp8);
                    if (var_f31 < (var_r31->unk_120 + var_r30->unk_120)) {
                        if (var_f31 > 0.0f) {
                            var_f31 = 0.5f * ((var_r31->unk_120 + var_r30->unk_120) - var_f31);
                        }
                        else {
                            var_f31 = 0.5f * (var_r31->unk_120 + var_r30->unk_120);
                            sp8.x = frandmod(0x3E8) - 0x1F4;
                            sp8.z = frandmod(0x3E8) - 0x1F4;
                        }
                        VECNormalize(&sp8, &sp8);
                        VECScale(&sp8, &sp8, var_f31);
                        VECAdd(&var_r31->unk_128, &sp8, &var_r31->unk_128);
                        VECSubtract(&var_r30->unk_128, &sp8, &var_r30->unk_128);
                    }
                }
            }
            if (var_r31->unk_128.y < 0.0f) {
                var_r31->unk_128.y = 0.0f;
            }
            if ((var_r31->unk_128.z - var_r31->unk_120) < -500.0f) {
                var_r31->unk_128.z = -500.0f + var_r31->unk_120;
            }
            else if ((var_r31->unk_128.z + var_r31->unk_120) > 500.0f) {
                var_r31->unk_128.z = 500.0f - var_r31->unk_120;
            }
            if (var_r31->unk_14 == 0) {
                var_r31->unk_128.x *= -1.0f;
            }
            if ((var_r31->unk_128.x - var_r31->unk_120) < 20.0f) {
                var_r31->unk_128.x = 20.0f + var_r31->unk_120;
            }
            else if ((60.000004f + var_r31->unk_128.x) > 800.0f) {
                var_r31->unk_128.x = 740.0f;
            }
            if (var_r31->unk_14 == 0) {
                var_r31->unk_128.x *= -1.0f;
            }
        }
    }
}

void fn_1_B4D4(omObjData *object, u32 arg1)
{
    M433PlayerWork *work = object->data;
    if ((work->unk_0C != arg1) && (arg1 < 0x15)) {
        float var_f31 = 60.0f * lbl_1_data_24C[arg1].unk_04;
        if (work->unk_0C < 0) {
            var_f31 = 0.0f;
        }
        work->unk_0C = arg1;
        if (work->unk_04 < 0) {
            CharModelMotionShiftSet(
                work->unk_00, object->motion[lbl_1_data_24C[arg1].unk_00], 60.0f * lbl_1_data_24C[arg1].unk_08, var_f31, lbl_1_data_24C[arg1].unk_10);
        }
        else {
            Hu3DMotionShiftSet(object->model[0], object->motion[lbl_1_data_24C[arg1].unk_00], 60.0f * lbl_1_data_24C[arg1].unk_08, var_f31,
                lbl_1_data_24C[arg1].unk_10);
        }
        if (lbl_1_data_24C[arg1].unk_0C >= 0.0f) {
            Hu3DMotionShiftStartEndSet(object->model[0], 60.0f * lbl_1_data_24C[arg1].unk_08, 60.0f * lbl_1_data_24C[arg1].unk_0C);
        }
        work->unk_10 = 0;
    }
}

s32 fn_1_B6E0(omObjData *object)
{
    M433PlayerWork *work = object->data;
    s32 var_r29 = 0;
    if (work->unk_04 < 0) {
        if (((CharModelMotionEndCheck(work->unk_00) != 0) || (work->unk_10 != 0)) && (CharModelMotionShiftIDGet(work->unk_00) < 0)) {
            var_r29 = 1;
        }
    }
    else if (((Hu3DMotionEndCheck(object->model[0]) != 0) || (work->unk_10 != 0)) && (Hu3DMotionShiftIDGet(object->model[0]) < 0)) {
        var_r29 = 1;
    }
    return var_r29;
}

s32 fn_1_B7AC(omObjData *object)
{
    M433PlayerWork *work = object->data;
    s32 var_r30 = 0;
    if (work->unk_04 < 0) {
        if (CharModelMotionShiftIDGet(work->unk_00) < 0) {
            var_r30 = 1;
        }
    }
    else if (Hu3DMotionShiftIDGet(object->model[0]) < 0) {
        var_r30 = 1;
    }
    return var_r30;
}

s32 fn_1_B838(omObjData *object, u32 arg1)
{
    s32 var_r26 = 0;
    if (fn_1_B6E0(object)) {
        fn_1_B4D4(object, arg1);
        var_r26 = 1;
    }
    return var_r26;
}

s32 fn_1_BAE0(omObjData *object, u32 arg1)
{
    s32 var_r26 = 0;
    if (fn_1_B7AC(object)) {
        fn_1_B4D4(object, arg1);
        var_r26 = 1;
    }
    return var_r26;
}

void fn_1_BD48(omObjData *object)
{
    M433PlayerWork2 *work;
    s32 var_r29;
    s32 var_r28;
    HsfanimStruct01 *var_r27;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M433PlayerWork2), MEMORY_DEFAULT_NUM);
    work = object->data;
    memset(work, 0, sizeof(M433PlayerWork2));
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 0));
    Hu3DModelShadowSet(object->model[0]);
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 4));
    Hu3DModelAttrSet(object->model[1], HU3D_MOTATTR_LOOP);
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 4));
    Hu3DModelAttrSet(object->model[2], HU3D_MOTATTR_LOOP);
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 3));
    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 7));
    Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF);
    object->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 5));
    Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(object->model[6], 0.75f, 0.75f, 0.75f);
    Hu3DModelLayerSet(object->model[6], 2);
    object->model[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 6));
    Hu3DModelAttrSet(object->model[7], HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(object->model[7], 0.75f, 0.75f, 0.75f);
    Hu3DModelLayerSet(object->model[7], 2);
    var_r28 = Hu3DParticleCreate(HuSprAnimRead(HuDataReadNum(0x120002, MEMORY_DEFAULT_NUM)), 1);
    object->model[8] = var_r28;
    Hu3DModelLayerSet(var_r28, 2);
    Hu3DParticleHookSet(var_r28, fn_1_DE28);
    Hu3DModelAttrSet(var_r28, HU3D_ATTR_DISPOFF);
    var_r28 = Hu3DParticleCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_M433, 9)), 0xC8);
    object->model[5] = var_r28;
    Hu3DModelLayerSet(var_r28, 2);
    Hu3DParticleHookSet(var_r28, fn_1_D6A8);
    for (var_r27 = ((ParticleData *)Hu3DData[var_r28].unk_120)->unk_48, var_r29 = 0; var_r29 < 0xC8; var_r29++, var_r27++) {
        var_r27->unk2C = 0.0f;
        var_r27->unk40.a = 0;
        var_r27->unk00_s16 = 0;
    }
    object->model[9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 2));
    Hu3DModelScaleSet(object->model[9], 1.05f, 1.05f, 1.05f);
    Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(object->model[9], 1);
    Hu3DModelShadowSet(object->model[9]);
    for (var_r29 = 1; var_r29 < 0x15; var_r29++) {
        if (var_r29 == 0xA) {
            object->model[var_r29 + 9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M433, 1));
        }
        else {
            object->model[var_r29 + 9] = Hu3DModelLink(object->model[9]);
            Hu3DModelLayerSet(object->model[var_r29 + 9], 1);
        }
        Hu3DModelShadowSet(object->model[var_r29 + 9]);
        Hu3DModelScaleSet(object->model[var_r29 + 9], 1.05f, 1.05f, 1.05f);
        Hu3DModelAttrSet(object->model[var_r29 + 9], HU3D_ATTR_DISPOFF);
    }
    object->trans.x = work->unk_30.x = 0.0f;
    object->trans.y = work->unk_30.y = 0.0f;
    object->trans.z = work->unk_30.z = 0.0f;
    work->unk_B8 = 0.0f;
    work->unk_BC.x = work->unk_BC.y = 0.0f;
    work->unk_BC.z = 1.0f;
    MTXIdentity(work->unk_C8);
    work->unk_18 = 0;
    object->func = fn_1_C240;
}

void fn_1_C240(omObjData *object)
{
    s32 var_r29;

    M433PlayerWork2 *work = object->data;
    s32 sp8 = 0;
    work->unk_00 = 0;
    switch (work->unk_18) {
        case 0:
            work->unk_04 = 1;
            break;
        case 1:
            work->unk_B8 = 0.0f;
            work->unk_BC.x = work->unk_BC.y = 0.0f;
            work->unk_BC.z = 1.0f;
            MTXIdentity(work->unk_C8);
            work->unk_00 = 1;
            break;
        case 10:
            work->unk_00 = 1;
            break;
    }
    work->unk_8C++;
    if (work->unk_90 != 0) {
        work->unk_A0 = 1.0f;
        if (work->unk_94 == 2) {
            work->unk_A4 += 12.000001f;
            if (work->unk_A4 >= 360.0f) {
                work->unk_A4 -= 360.0f;
            }
            work->unk_A0 = 1.5f;
            work->unk_A8 += 0.015000001f;
            Hu3DMotionSpeedSet(object->model[3], 2.5f);
        }
        else {
            Hu3DMotionTimeSet(object->model[3], 0.0f);
            Hu3DMotionSpeedSet(object->model[3], 0.0f);
        }
        Hu3DModelRotSet(object->model[3], 0.0f, work->unk_A4, 0.0f);
        Hu3DModelAttrReset(object->model[3], HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(object->model[3], work->unk_AC.x, 3.0f + work->unk_AC.y, work->unk_AC.z);
        work->unk_98++;
        work->unk_90 = 0;
    }
    else if (work->unk_94 != 0) {
        work->unk_94 = 0;
        work->unk_A0 = 0.0f;
    }
    work->unk_9C = work->unk_9C + (0.2f * (work->unk_A0 - work->unk_9C));
    Hu3DModelScaleSet(object->model[3], work->unk_9C, 1.0f, work->unk_9C);
    if ((work->unk_A0 <= 0.0f) && (work->unk_9C < 0.1f)) {
        Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
        work->unk_9C = 0.0f;
    }
    for (var_r29 = 0; var_r29 < 2; var_r29++) {
        work->unk_7C[var_r29] += (0.3f * (work->unk_84[var_r29] - work->unk_7C[var_r29]));
        if (work->unk_84[var_r29] > 0.0f) {
            Hu3DModelAttrReset(object->model[var_r29 + 1], HU3D_ATTR_DISPOFF);
        }
        else if (work->unk_7C[var_r29] < 0.1f) {
            Hu3DModelAttrSet(object->model[var_r29 + 1], HU3D_ATTR_DISPOFF);
        }
        Hu3DModelScaleSet(object->model[var_r29 + 1], work->unk_7C[var_r29], 1.0f, work->unk_7C[var_r29]);
    }
    fn_1_C6B0(object);
    fn_1_CB98(object);
    object->trans.x = work->unk_30.x;
    object->trans.y = work->unk_30.y;
    object->trans.z = work->unk_30.z;
    if ((fn_1_216C() >= 3) && (work->unk_04 != 0) && (fn_1_2244() != 0)) {
        fn_1_DD70(&work->unk_30);
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        object->func = fn_1_C6AC;
    }
}

void fn_1_C6AC(omObjData *object) { }

s32 fn_1_C6B0(omObjData *object)
{
    Mtx sp14;
    Vec sp8;
    M433PlayerWork3 *var_r29;
    s32 var_r28;

    M433PlayerWork2 *work = object->data;
    if ((work->unk_00 == 0) && (work->unk_04 == 0) && (work->unk_08 == 0)) {
        if (work->unk_10 == 0) {
            fn_1_CDB8(&work->unk_F8, &work->unk_30, &work->unk_3C, work->unk_6C, work->unk_A8);
            fn_1_D338(&work->unk_F8);
            fn_1_D180(&work->unk_F8);
            work->unk_B8 = work->unk_A8 * (8.0f * lbl_1_data_48C[work->unk_6C]);
            VECSubtract(&work->unk_3C, &work->unk_30, &sp8);
            sp8.y = 0.0f;
            if (VECMag(&sp8) <= 0.0f) {
                work->unk_BC.x = work->unk_BC.y = 0.0f;
                work->unk_BC.z = 1.0f;
            }
            else {
                VECNormalize(&sp8, &sp8);
                work->unk_BC.x = -sp8.z;
                work->unk_BC.y = 0.0f;
                work->unk_BC.z = sp8.x;
            }
            work->unk_48 = 0.0f;
            var_r28 = 0;
            if (work->unk_84[0] > 0.0f) {
                var_r28++;
            }
            Hu3DModelPosSet(object->model[var_r28 + 1], work->unk_F8.unk_38.x, 3.0f + work->unk_F8.unk_38.y, work->unk_F8.unk_38.z);
            if (work->unk_9C <= 0.0f) {
                work->unk_8C = 9;
            }
            if (lbl_1_data_468[work->unk_6C] != 0) {
                work->unk_84[var_r28] = 1.0f;
            }
            work->unk_84[1 - var_r28] = 0.0f;
        }
        work->unk_10 = 1;
        if (work->unk_B8 != 0.0f) {
            MTXRotAxisRad(sp14, &work->unk_BC, 0.017453292f * work->unk_B8);
            MTXConcat(sp14, work->unk_C8, work->unk_C8);
            MTXCopy(work->unk_C8, Hu3DData[object->model[0]].unk_F0);
        }
        work->unk_48 += 0.016666668f;
        work->unk_08 = fn_1_D4E0(&work->unk_F8, &work->unk_30, &work->unk_4C, work->unk_48);
        if (work->unk_08 != 0) {
            work->unk_84[0] = work->unk_84[1] = 0.0f;
            if (work->unk_30.y <= 12.0f) {
                var_r29 = lbl_1_bss_7C8->data;
                work->unk_78 = 0;
                Hu3DModelPosSetV(object->model[4], &work->unk_30);
                Hu3DMotionTimeSet(object->model[4], 0.0f);
                if ((work->unk_6C == 5) || (work->unk_6C == 2)) {
                    Hu3DMotionSpeedSet(object->model[4], 1.5f);
                    fn_1_D888(&work->unk_30, 1.0f);
                }
                else {
                    Hu3DMotionSpeedSet(object->model[4], 1.0f);
                    fn_1_D888(&work->unk_30, 0.5f);
                    work->unk_30.y += 11.0f;
                }
                work->unk_6C = 0;
                work->unk_04 = 1;
                var_r29->unk_2C = 1;
                var_r29->sGroundGrp = -1;
                if (fabs(work->unk_30.z) < 350.0) {
                    if (fabs(work->unk_30.x) < 700.0) {
                        var_r29->sGroundGrp = 0;
                        if (work->unk_30.x >= 0.0f) {
                            var_r29->sGroundGrp = 1;
                        }
                    }
                }
            }
        }
    }
    else {
        work->unk_10 = 0;
    }
    return work->unk_08;
}

void fn_1_CB98(omObjData *object)
{
    Mtx sp50;
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    s32 var_r29;

    M433PlayerWork2 *work = object->data;
    if (work->unk_78 != 0) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
        var_f30 = work->unk_F8.unk_04;
        var_f29 = var_f30;
        var_f31 = var_f29 - (0.020000001f * work->unk_A8);
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
        }
        var_f31 = (var_f30 - var_f31) / 21.0f;
        MTXCopy(work->unk_C8, sp20);
        var_f28 = (work->unk_B8 * (1.2f * work->unk_A8)) / 21.0f;
        MTXRotAxisRad(sp50, &work->unk_BC, MTXDegToRad(-var_f28));
        for (var_r29 = 0; var_r29 < 0x15; var_r29++) {
            Hu3DModelAttrReset(object->model[var_r29 + 9], HU3D_ATTR_DISPOFF);
            fn_1_D4E0(&work->unk_F8, &sp14, &sp8, var_f30);
            Hu3DModelPosSetV(object->model[var_r29 + 9], &sp14);
            MTXCopy(sp20, Hu3DData[object->model[var_r29 + 9]].unk_F0);
            MTXConcat(sp50, sp20, sp20);
            var_f30 -= var_f31;
        }
        work->unk_F8.unk_04 = var_f29;
        return;
    }
    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
    for (var_r29 = 0; var_r29 < 0x15; var_r29++) {
        Hu3DModelAttrSet(object->model[var_r29 + 9], HU3D_ATTR_DISPOFF);
    }
}

void fn_1_CDB8(M433PlayerWork2Sub *arg0, Vec *arg1, Vec *arg2, u32 arg3, float arg8)
{
    Vec sp18;
    Vec spC;
    float var_f31;
    float var_f30;
    float var_f29;

    arg0->unk_0C = 0.0f;
    arg0->unk_08 = 0.0f;
    var_f31 = lbl_1_data_4D4[arg3].y;
    arg0->unk_00 = var_f31;
    if (arg0->unk_00 <= 0.0f) {
        if (((arg2->x * arg1->x) < 0.0f) && (arg1->x != 0.0f) && (lbl_1_data_4D4[arg3].x > 0.0f)) {
            arg0->unk_0C = lbl_1_data_4D4[arg3].x;
            arg0->unk_08 = fabs(arg1->x / (arg2->x - arg1->x));
            var_f29 = arg1->y + (arg0->unk_08 * (arg2->y - arg1->y));
            if (var_f29 < arg0->unk_0C) {
                spC.x = arg1->x + (arg0->unk_08 * (arg2->x - arg1->x));
                spC.y = arg0->unk_0C;
                spC.z = arg1->z + (arg0->unk_08 * (arg2->z - arg1->z));
                VECSubtract(arg2, &spC, &sp18);
                var_f30 = VECMag(&sp18);
                VECSubtract(&spC, arg1, &sp18);
                var_f30 += VECMag(&sp18);
            }
            else {
                VECSubtract(arg2, arg1, &sp18);
                var_f30 = VECMag(&sp18);
            }
        }
        else {
            VECSubtract(arg2, arg1, &sp18);
            var_f30 = VECMag(&sp18);
        }
        var_f31 = var_f30 / (arg8 * lbl_1_data_4D4[arg3].z);
        arg0->unk_00 = var_f31;
    }
    arg0->unk_04 = 0.0f;
    arg0->unk_2C = *arg1;
    arg0->unk_38 = *arg2;
    arg0->unk_1C = arg2->y - arg1->y;
    arg0->unk_24 = -980.0f;
    VECSubtract(arg2, arg1, &sp18);
    sp18.y = 0.0f;
    arg0->unk_10 = VECMag(&sp18);
    arg0->unk_18 = 0.0f;
    if (var_f31 > 0.0f) {
        arg0->unk_20 = (arg0->unk_1C - (0.5f * (-980.0f * (var_f31 * var_f31)))) / var_f31;
        arg0->unk_14 = arg0->unk_10 / var_f31;
    }
    else {
        arg0->unk_20 = arg0->unk_1C;
        arg0->unk_14 = arg0->unk_10;
    }
    arg0->unk_28 = lbl_1_data_540[arg3];
}

void fn_1_D180(M433PlayerWork2Sub *arg0)
{
    float sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    s32 var_r31;

    if (!(arg0->unk_0C <= 0.0f)) {
        var_f31 = arg0->unk_00;
        var_f28 = arg0->unk_00;
        var_f27 = 10.0f * arg0->unk_00;
        for (var_r31 = 0; var_r31 < 0x10; var_r31++) {
            var_f30 = 1.0f / var_f31;
            sp8 = arg0->unk_10 * var_f30;
            var_f26 = (arg0->unk_1C * var_f30) - (0.5f * arg0->unk_24 * var_f31);
            var_f29 = arg0->unk_08 * var_f31;
            var_f25 = arg0->unk_2C.y + ((var_f29 * (0.5f * arg0->unk_24 * var_f29)) + (var_f26 * var_f29));
            if (arg0->unk_0C > var_f25) {
                var_f28 = var_f31;
            }
            else {
                var_f27 = var_f31;
            }
            var_f31 = 0.5f * (var_f28 + var_f27);
        }
        var_f30 = 1.0f / var_f31;
        arg0->unk_00 = var_f31;
        arg0->unk_14 = arg0->unk_10 * var_f30;
        arg0->unk_20 = (arg0->unk_1C * var_f30) - (0.5f * arg0->unk_24 * var_f31);
    }
}

void fn_1_D338(M433PlayerWork2Sub *arg0)
{
    float sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    s32 var_r31;

    if (!(arg0->unk_0C <= 0.0f)) {
        var_f29 = arg0->unk_08 * arg0->unk_00;
        var_f30 = 1.0f / arg0->unk_00;
        var_f31 = arg0->unk_24;
        var_f28 = arg0->unk_24;
        var_f27 = arg0->unk_24 * arg0->unk_28;
        for (var_r31 = 0; var_r31 < 0x10; var_r31++) {
            sp8 = arg0->unk_10 * var_f30;
            var_f26 = (arg0->unk_1C * var_f30) - (0.5f * var_f31 * arg0->unk_00);
            var_f25 = arg0->unk_2C.y + ((var_f29 * (0.5f * var_f31 * var_f29)) + (var_f26 * var_f29));
            if (arg0->unk_0C > var_f25) {
                var_f28 = var_f31;
            }
            else {
                var_f27 = var_f31;
            }
            var_f31 = 0.5f * (var_f28 + var_f27);
        }
        arg0->unk_24 = var_f31;
        arg0->unk_14 = arg0->unk_10 * var_f30;
        arg0->unk_20 = (arg0->unk_1C * var_f30) - (0.5f * arg0->unk_24 * arg0->unk_00);
    }
}

s32 fn_1_D4E0(M433PlayerWork2Sub *arg0, Vec *arg1, Vec *arg2, float arg8)
{
    Vec sp18;
    Vec spC;
    float var_f30;
    float var_f29;

    if (arg8 < 0.0f) {
        arg8 = 0.0f;
    }
    if (arg8 > arg0->unk_00) {
        arg8 = arg0->unk_00;
    }
    arg0->unk_04 = arg8;
    if (arg0->unk_10 > 0.0f) {
        VECSubtract(&arg0->unk_38, &arg0->unk_2C, &spC);
        spC.y = 0.0f;
        VECNormalize(&spC, &spC);
    }
    else {
        spC.x = spC.y = spC.z = 0.0f;
    }
    sp18 = *arg1;
    var_f30 = (arg8 * (0.5f * arg0->unk_18 * arg8)) + (arg0->unk_14 * arg8);
    var_f29 = (arg8 * (0.5f * arg0->unk_24 * arg8)) + (arg0->unk_20 * arg8);
    arg1->x = arg0->unk_2C.x + (spC.x * var_f30);
    arg1->y = arg0->unk_2C.y + var_f29;
    arg1->z = arg0->unk_2C.z + (spC.z * var_f30);
    VECSubtract(arg1, &sp18, arg2);
    if (arg8 >= arg0->unk_00) {
        return 1;
    }
    return 0;
}

void fn_1_D6A8(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    s32 var_r29;

    for (var_r31 = particle->unk_48, var_r29 = 0; var_r29 < particle->unk_30; var_r29++, var_r31++) {
        if (var_r31->unk00_s16 != 0) {
            VECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            var_r31->unk08.x *= 0.92f;
            var_r31->unk08.z *= 0.92f;
            var_r31->unk08.y += -0.27222225f;
            var_r31->unk2C += 2.0f;
            var_r31->unk40.a *= 0.99f;
            if (var_r31->unk00_s16 < 24.0f) {
                var_r31->unk40.a = 0.9f * var_r31->unk40.a;
            }
            if (--var_r31->unk00_s16 == 0) {
                var_r31->unk00_s16 = 0;
                var_r31->unk2C = 0.0f;
                var_r31->unk40.a = 0;
            }
        }
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * 0x44);
}

void fn_1_D888(Vec *arg0, float arg8)
{
    Vec sp8;
    float var_f31;
    float var_f30;
    HsfanimStruct01 *var_r31;
    s32 var_r29;
    u32 var_r28;

    var_r31 = ((ParticleData *)Hu3DData[lbl_1_bss_7CC->model[5]].unk_120)->unk_48;
    var_r28 = 3.0f + (12.0f * arg8);
    for (var_r29 = 0; var_r29 < 0xC8; var_r29++, var_r31++) {
        if (var_r31->unk00_s16 == 0) {
            var_r31->unk00_s16 = 60.0f * (0.6f + (0.0006f * frandmod(0x3E8)));
            var_f30 = frandmod(0x168);
            sp8.x = sind(var_f30);
            sp8.y = 0.0f;
            sp8.z = cosd(var_f30);
            var_f31 = 0.030000001f * frandmod(0x3E8);
            var_r31->unk34.x = arg0->x + (sp8.x * var_f31);
            var_r31->unk34.y = 10.0f + (arg0->y + (0.030000001f * frandmod(0x3E8)));
            var_r31->unk34.z = arg0->z + (sp8.z * var_f31);
            var_f31 = 0.8333334f + (0.0016666667f * frandmod(0x3E8));
            var_f31 *= 1.0f + arg8;
            var_r31->unk08.x = sp8.x * var_f31;
            var_r31->unk08.z = sp8.z * var_f31;
            var_r31->unk08.y = 0.50000006f + (0.0011666667f * frandmod(0x3E8));
            var_r31->unk08.y *= (1.0f + arg8);
            var_r31->unk30 = frandmod(0x168);
            var_r31->unk2C = 60.0f + frandmod(0x1E);
            var_r31->unk40.a = frandmod(0x64) + 0x78;
            var_f31 = 0.001f * frandmod(0x3E8);
            var_r31->unk40.r = 235.0f + (20.0f * var_f31);
            var_r31->unk40.g = 180.0f + (75.0f * var_f31);
            var_r31->unk40.b = 155.0f + (100.0f * var_f31);
            if (--var_r28 < 1) {
                break;
            }
        }
    }
}

void fn_1_DD70(Vec *arg0)
{
    HsfanimStruct01 *var_r30;

    ParticleData *var_r31 = Hu3DData[lbl_1_bss_7CC->model[8]].unk_120;
    Hu3DModelAttrReset(lbl_1_bss_7CC->model[8], HU3D_ATTR_DISPOFF);
    var_r30 = var_r31->unk_48;
    var_r31->unk_00 = 0;
    var_r31->unk_02 = 0x3C;
    var_r30->unk2C = 100.0f;
    var_r30->unk34 = *arg0;
}

void fn_1_DE28(ModelData *var_r27, ParticleData *var_r31, Mtx matrix)
{
    HsfanimStruct01 *var_r30;
    s32 var_r29;
    s8 var_r28;

    if (var_r31->unk_00 == 0) {
        var_r31->unk_00 = 1;
        for (var_r30 = (HsfanimStruct01 *)&var_r31->unk_48, var_r29 = 0; var_r29 < var_r31->unk_30; var_r29++, var_r30++) {
            var_r30->unk2C = 0.0f;
        }
    }
    var_r28 = 0.016666668f * (var_r31->unk_02 * 0xFF);
    for (var_r30 = var_r31->unk_48, var_r29 = 0; var_r29 < var_r31->unk_30; var_r29++, var_r30++) {
        var_r30->unk40.a = var_r28;
    }
    if (--var_r31->unk_02 == 0) {
        var_r27->attr |= 1;
    }
    DCStoreRange(var_r31->unk_48, var_r31->unk_30 * sizeof(HsfanimStruct01));
}

void fn_1_DF44(omObjData *object)
{
    M433PlayerWork3 *work;

    object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M433PlayerWork3), MEMORY_DEFAULT_NUM);
    work = object->data;
    memset(work, 0, sizeof(M433PlayerWork3));
    work->uGameEvent = 0;
    work->sWinGrp = -1;
    work->uServeGrp = 0;
    work->auEvents[0] = work->auEvents[1] = 0;
    work->unk_2C = work->unk_30 = 0;
    fn_1_E5C0(work->unk_4C, &work->unk_64);
    object->func = fn_1_E11C;
}

void fn_1_DFE4(omObjData *var_r30)
{
    M433PlayerWork3 *work = var_r30->data;
    OSReport("\n");
    OSReport("uGameEvent       %d\n", work->uGameEvent);
    OSReport("sWinGrp          %d\n", work->sWinGrp);
    OSReport("uServeGrp        %d\n", work->uServeGrp);
    OSReport("uPointGrp        %d\n", work->uPointGrp);
    OSReport("auServeCel[2]    %d,%d\n", work->auServeCel[0], work->auServeCel[1]);
    OSReport("auEvents[2]      %d,%d\n", work->auEvents[0], work->auEvents[1]);
    OSReport("uContactCnt      %d\n", work->uContactCnt);
    OSReport("sGroundGrp       %d\n", work->sGroundGrp);
    OSReport("uContactGrp      %d\n", work->uContactGrp);
    OSReport("sContactCel      %d\n", work->uContactCel);
    OSReport("uTargetGrp       %d\n", work->uTargetGrp);
    OSReport("\n");
}

void fn_1_E11C(omObjData *object)
{
    s32 spC[4];
    u32 var_r30;
    s32 var_r29;
    s32 var_r27;
    s16 var_r26;
    s16 var_r25;

    M433PlayerWork3 *work = object->data;
    s32 sp8 = 0;
    s32 var_r28 = 0;
    work->unk_28++;
    work->unk_4C[0].unk_00 = work->unk_20[0];
    work->unk_4C[1].unk_00 = work->unk_20[1];
    if (fn_1_216C() >= 2) {
        fn_1_ECFC(work->unk_4C, &work->unk_64);
    }
    switch (work->uGameEvent) {
        case 0:
            work->uContactCnt = 0;
            work->uContactCel = -1;
            if (work->unk_28 == 0xC) {
                fn_1_58D8(1);
            }
            if ((work->unk_28 >= 30.0f) && (fn_1_216C() >= 2)) {
                work->uGameEvent = 1;
                work->unk_28 = 0;
                work->auEvents[0] = work->auEvents[1] = 1;
            }
            break;
        case 1:
            if (work->unk_30 != 0) {
                work->unk_48 = 0;
                work->uContactCel = -1;
                work->uContactCnt = 0;
                work->uGameEvent = 2;
                work->unk_28 = 0;
                work->auEvents[0] = work->auEvents[1] = 3;
                if (work->uTargetGrp != 0) {
                    var_r26 = 5;
                }
                else {
                    var_r26 = 6;
                }
                fn_1_58D8(var_r26);
            }
            break;
        case 2:
        case 5:
            if (work->unk_30 != 0) {
                if (work->uContactCnt != 0) {
                    work->unk_48++;
                    work->uGameEvent = 3;
                    work->auEvents[work->uContactGrp] = 4;
                    if ((work->unk_48 >= 6) && ((work->unk_48 % 3) == 0)) {
                        fn_1_58D8(3);
                    }
                }
                work->unk_28 = 0;
            }
            var_r28 = 1;
            break;
        case 3:
        case 4:
            if (work->unk_30 != 0) {
                if (work->uContactGrp == work->uTargetGrp) {
                    work->uGameEvent = 4;
                    work->auEvents[work->uContactGrp] = 5;
                }
                else {
                    work->uContactCel = -1;
                    work->uContactCnt = 0;
                    work->uGameEvent = 5;
                    work->auEvents[work->uContactGrp] = 3;
                    if (work->uTargetGrp != 0) {
                        var_r25 = 5;
                    }
                    else {
                        var_r25 = 6;
                    }
                    fn_1_58D8(var_r25);
                }
                work->unk_28 = 0;
            }
            var_r28 = 1;
            break;
        case 6:
            if (work->unk_28 >= 120.0f) {
                work->uGameEvent = 0;
                work->unk_28 = 0;
                work->auEvents[0] = work->auEvents[1] = 0;
            }
            break;
        case 7:
            break;
    }
    if ((work->unk_2C != 0) && (var_r28 != 0)) {
        if (work->sGroundGrp >= 0) {
            var_r30 = 1 - work->sGroundGrp;
            fn_1_58D8(1);
        }
        else {
            var_r30 = 1 - work->uContactGrp;
            fn_1_58D8(2);
        }
        work->uPointGrp = var_r30;
        work->unk_20[var_r30]++;
        if (work->uServeGrp != var_r30) {
            work->uServeGrp = var_r30;
            work->auServeCel[work->uServeGrp] = 1 - work->auServeCel[work->uServeGrp];
        }
        if (work->unk_20[var_r30] >= 5) {
            work->sWinGrp = var_r30;
            work->uGameEvent = 7;
            work->auEvents[0] = work->auEvents[1] = 7;
            var_r27 = 0;
            for (var_r29 = 0; var_r29 < 4; var_r29++) {
                spC[var_r29] = -1;
                if (work->sWinGrp == OM_GET_DATA_PTR(lbl_1_bss_7D0[var_r29], M433PlayerWork)->unk_14) {
                    spC[var_r27++] = lbl_1_bss_7D0[var_r29]->work[0];
                }
            }
            fn_1_219C(1, spC[0], spC[1]);
            fn_1_21E4(4);
        }
        else {
            work->uGameEvent = 6;
            work->auEvents[0] = work->auEvents[1] = 6;
            fn_1_FE64(&work->unk_64, work->unk_20[0], work->unk_20[1], var_r30);
            HuAudFXPlay(0x16);
        }
        work->unk_28 = 0;
    }
    work->unk_2C = 0;
    work->unk_30 = 0;
}

u16 lbl_1_data_674[6] = { 0, 1, 2, 3, 3, 0 };
s32 lbl_1_data_680[2] = { 0x61001E, 0x61001F };
Vec2f lbl_1_data_688[5] = {
    { 0.0f, 0.0f },
    { 0.0f, 0.0f },
    { -23.0f, 0.0f },
    { 1.0f, 0.0f },
    { 21.0f, 0.0f },
};
Vec2f lbl_1_data_6B0[2] = { { 72.0f, 56.0f }, { 504.0f, 56.0f } };
s32 lbl_1_data_6C0[0xB][4] = {
    { 0x13000B, 0, 0, 0 },
    { 0x13000C, 0, 0, 0 },
    { 0x13000D, 0, 0, 0 },
    { 0x13000E, 0, 0, 0 },
    { 0x13000F, 0, 0, 0 },
    { 0x130010, 0, 0, 0 },
    { 0x130011, 0, 0, 0 },
    { 0x130012, 0, 0, 0 },
    { 0x130013, 0, 0, 0 },
    { 0x130014, 0, 0, 0 },
    { 0x130099, 0, 0, 0 },
};
s32 lbl_1_data_770[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
M433DllPlayerData794Struct lbl_1_data_794[9] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 1, 1, 0 },
    { 1, 0, 1 },
    { 1, 0, 1 },
    { 1, 1, 0 },
    { 1, 1, 0 },
    { 1, 0, 1 },
    { 1, 0, 1 },
};
u32 lbl_1_data_800[9] = { 0, 1, 2, 1, 1, 2, 1, 1, 1 };

void fn_1_E5C0(M433PlayerWork3Sub *arg0, M433PlayerWork3Sub2 *arg1)
{
    s32 var_r31;
    s32 var_r28;
    s32 var_r27;

    for (var_r28 = 0; var_r28 < 2; var_r28++, arg0++) {
        for (var_r31 = 0; (u32)var_r31 < 5; var_r31++) {
            switch (lbl_1_data_674[var_r31]) {
                case 0:
                    arg0->unk_02[var_r31] = espEntry(lbl_1_data_680[var_r28], 1, 0);
                    espPriSet(arg0->unk_02[var_r31], 0x100);
                    break;
                case 1:
                    arg0->unk_02[var_r31] = espEntry(0x610020, 1, 0);
                    espPriSet(arg0->unk_02[var_r31], 0x101);
                    espColorSet(arg0->unk_02[var_r31], 0, 0, 0);
                    espTPLvlSet(arg0->unk_02[var_r31], 0.5);
                    break;
                case 2:
                    arg0->unk_02[var_r31] = espEntry(DATA_MAKE_NUM(DATADIR_M433, 10), 1, 0);
                    espPriSet(arg0->unk_02[var_r31], 0xFF);
                    break;
                case 3:
                    arg0->unk_02[var_r31] = espEntry(0x610033, 1, 0);
                    espPriSet(arg0->unk_02[var_r31], 0xFF);
                    break;
            }
            espDispOff(arg0->unk_02[var_r31]);
            espDrawNoSet(arg0->unk_02[var_r31], 0);
            espAttrSet(arg0->unk_02[var_r31], HUSPR_ATTR_NOANIM);
            espAttrSet(arg0->unk_02[var_r31], HUSPR_ATTR_LINEAR);
            espPosSet(
                arg0->unk_02[var_r31], lbl_1_data_6B0[var_r28].x + lbl_1_data_688[var_r31].x, lbl_1_data_6B0[var_r28].y + lbl_1_data_688[var_r31].y);
        }
    }
    HuDataDirClose(0x610000);
    for (var_r28 = 0; var_r28 < 3; var_r28++) {
        for (var_r31 = 0; var_r31 < 0x14; var_r31++) {
            for (var_r27 = 0; var_r27 < 2; var_r27++) {
                if (lbl_1_data_6C0[var_r31 % 10][var_r27] != 0) {
                    arg1->unk_D0[var_r28][var_r31].unk_00[var_r27] = espEntry(lbl_1_data_6C0[var_r31 % 10][var_r27], 2, 0);
                    espAttrSet(arg1->unk_D0[var_r28][var_r31].unk_00[var_r27], HUSPR_ATTR_LINEAR);
                    espDispOff(arg1->unk_D0[var_r28][var_r31].unk_00[var_r27]);
                }
                else {
                    arg1->unk_D0[var_r28][var_r31].unk_00[var_r27] = -1;
                }
            }
        }
    }
    for (var_r27 = 0; var_r27 < 2; var_r27++) {
        if (lbl_1_data_6C0[10][var_r27] != 0) {
            arg1->unk_490.unk_00[var_r27] = espEntry(lbl_1_data_6C0[10][var_r27], 2, 0);
            espAttrSet(arg1->unk_490.unk_00[var_r27], HUSPR_ATTR_LINEAR);
            espDispOff(arg1->unk_490.unk_00[var_r27]);
        }
        else {
            arg1->unk_490.unk_00[var_r27] = -1;
        }
    }
    for (var_r28 = 0; var_r28 < 2; var_r28++) {
        arg1->unk_20[var_r28].unk_00[0] = -1;
        arg1->unk_20[var_r28].unk_00[1] = -1;
    }
    arg1->unk_20[2].unk_00[0] = -1;
    arg1->unk_20[2].unk_00[1] = -1;
    arg1->unk_20[3].unk_00[0] = -1;
    arg1->unk_20[3].unk_00[1] = -1;
    HuDataDirClose(lbl_1_data_6C0[0][0]);
}

void fn_1_EA8C(M433PlayerWork3Sub2Sub *var_r31)
{
    float var_f31;
    float var_f30;
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        if (var_r31->unk_00[var_r30] >= 0) {
            espDispOn(var_r31->unk_00[var_r30]);
            var_f31 = (var_r31->unk_04[var_r30] * var_r31->unk_1C) * cosd(var_r31->unk_28);
            var_f30 = (var_r31->unk_04[var_r30] * var_r31->unk_1C) * sind(var_r31->unk_28);
            espPosSet(var_r31->unk_00[var_r30], var_r31->unk_0C + var_f31, var_r31->unk_10 + var_f30);
            espZRotSet(var_r31->unk_00[var_r30], var_r31->unk_28);
            espScaleSet(var_r31->unk_00[var_r30], var_r31->unk_1C, var_r31->unk_20);
            espTPLvlSet(var_r31->unk_00[var_r30], var_r31->unk_24);
        }
    }
}

void fn_1_EBE4(M433PlayerWork3Sub2Sub2 *arg0, M433PlayerWork3Sub2Sub *arg1, u32 arg2)
{
    u32 var_r31;
    u32 var_r30;

    var_r31 = arg2 % 10;
    var_r30 = arg2 / 10;
    if (var_r30 == 0) {
        arg1->unk_00[0] = arg0[var_r31].unk_00[0];
        arg1->unk_00[1] = -1;
        arg1->unk_04[0] = 0.0f;
    }
    else {
        arg1->unk_00[0] = arg0[var_r30 + 0xA].unk_00[0];
        arg1->unk_00[1] = arg0[var_r31].unk_00[0];
        arg1->unk_04[0] = -23.039999f;
        arg1->unk_04[1] = 23.039999f;
    }
    arg1->unk_0C = arg1->unk_10 = 0.0f;
    arg1->unk_14 = arg1->unk_18 = 0.0f;
    arg1->unk_1C = arg1->unk_20 = 1.5f;
    arg1->unk_24 = 1.0f;
    arg1->unk_28 = 0.0f;
}

void fn_1_ECFC(M433PlayerWork3Sub *arg0, M433PlayerWork3Sub2 *arg1)
{
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    M433PlayerWork3Sub2Sub *var_r30;
    M433PlayerWork3Sub2Sub2 *var_r29;
    s32 var_r28;
    s32 var_r22;

    for (var_r28 = 0; var_r28 < 2; var_r28++, arg0++) {
        for (var_r22 = 0; var_r22 < 5; var_r22++) {
            espDispOn(arg0->unk_02[var_r22]);
        }
        espBankSet(arg0->unk_02[3], arg0->unk_00 / 10);
        espBankSet(arg0->unk_02[4], arg0->unk_00 % 10);
    }
    var_f28 = 2.88f;
    if (arg1->unk_1C == 0) {
        var_r30 = arg1->unk_20;
    }
    else {
        var_r30 = &arg1->unk_20[1];
        var_f28 *= -1.0f;
    }
    switch (arg1->unk_00) {
        case 0:
            break;
        case 1:
            fn_1_EBE4(&arg1->unk_D0[0][0], &arg1->unk_20[0], arg1->unk_0C);
            fn_1_EBE4(&arg1->unk_D0[1][0], &arg1->unk_20[1], arg1->unk_10);
            fn_1_EBE4(&arg1->unk_490, &arg1->unk_20[2], 0);
            fn_1_EBE4(&arg1->unk_D0[2][0], &arg1->unk_20[3], arg1->unk_14[arg1->unk_1C]);

            var_f30 = -48.0f;
            arg1->unk_20[0].unk_0C = 172.8f;
            arg1->unk_20[0].unk_10 = 360.0f - var_f30;
            arg1->unk_20[1].unk_0C = 403.19998f;
            arg1->unk_20[1].unk_10 = 360.0f - var_f30;
            arg1->unk_20[2].unk_0C = 288.0f;
            arg1->unk_20[2].unk_10 = 360.0f - var_f30;
            arg1->unk_20[0].unk_24 = arg1->unk_20[1].unk_24 = arg1->unk_20[2].unk_24 = 0.0f;
            var_f30 = var_f30 / 19.199999f;
            arg1->unk_20[0].unk_18 = var_f30;
            arg1->unk_20[1].unk_18 = var_f30;
            arg1->unk_20[2].unk_18 = var_f30;
            arg1->unk_20[3].unk_0C = 806.39996f;
            arg1->unk_20[3].unk_10 = 144.0f;
            arg1->unk_20[3].unk_1C += 0.5f;
            arg1->unk_20[3].unk_20 -= 0.5f;
            arg1->unk_20[3].unk_14 = (403.19998f - arg1->unk_20[3].unk_0C) / 24.0f;
            arg1->unk_20[3].unk_18 = (360.0f - arg1->unk_20[3].unk_10) / 24.0f;
            if (arg1->unk_1C == 0) {
                arg1->unk_20[3].unk_0C = -230.40001f;
                arg1->unk_20[3].unk_14 *= -1.0f;
            }
            arg1->unk_00++;
            arg1->unk_04 = 0;
            break;
        case 2:
            var_f31 = arg1->unk_20[0].unk_24;
            var_f31 += 0.055555556f;
            if (var_f31 > 0.95f) {
                var_f31 = 1.0f;
            }
            arg1->unk_20[2].unk_24 = var_f31;
            arg1->unk_20[1].unk_24 = var_f31;
            arg1->unk_20[0].unk_24 = var_f31;
            arg1->unk_20[0].unk_10 += arg1->unk_20[0].unk_18;
            arg1->unk_20[1].unk_10 += arg1->unk_20[1].unk_18;
            arg1->unk_20[2].unk_10 += arg1->unk_20[2].unk_18;
            arg1->unk_20[3].unk_0C += arg1->unk_20[3].unk_14;
            arg1->unk_20[3].unk_10 += arg1->unk_20[3].unk_18;
            if (arg1->unk_04 >= 19.199999f) {
                var_r30->unk_14 = var_f28;
                var_r30->unk_18 = -16.0f;
                arg1->unk_00++;
                arg1->unk_08 = 0;
            }
            break;
        case 3:
            if (arg1->unk_04 <= 24.0f) {
                arg1->unk_20[3].unk_0C += arg1->unk_20[3].unk_14;
                arg1->unk_20[3].unk_10 += arg1->unk_20[3].unk_18;
            }
            if (arg1->unk_08 < 24.0f) {
                arg1->unk_08++;
                var_f31 = 33.75f * arg1->unk_08;
                var_f29 = 0.041666668f * arg1->unk_08;
                var_f29 = 0.5f * (1.0f - (var_f29 * var_f29));
                if (arg1->unk_08 == 24.0f) {
                    var_f29 = 0.0f;
                }
                arg1->unk_20[3].unk_1C = 1.5 + (var_f29 * cosd(var_f31));
                arg1->unk_20[3].unk_20 = 1.5 + (var_f29 * sind((var_f31 - 90.0f)));
            }
            var_r30->unk_1C = arg1->unk_20[3].unk_20;
            var_r30->unk_20 = arg1->unk_20[3].unk_1C;
            var_r30->unk_0C += var_r30->unk_14;
            var_r30->unk_10 += var_r30->unk_18;
            var_r30->unk_18 += 0.80000013f;
            var_r30->unk_28 += 8.333334f;
            var_r30->unk_24 -= 0.017833335f;
            if (var_r30->unk_24 < 0.0f) {
                var_r30->unk_24 = 0.0f;
            }
            if (fn_1_10EA4() == 0) {
                arg1->unk_00++;
                arg1->unk_04 = 0;
            }
            break;
        case 4:
            var_f31 = arg1->unk_20[3].unk_24;
            var_f31 -= 0.055555556f;
            if (var_f31 < 0.05f) {
                var_f31 = 0.0f;
                arg1->unk_00++;
                arg1->unk_04 = 0;
            }
            arg1->unk_20[3].unk_24 = var_f31;
            arg1->unk_20[2].unk_24 = var_f31;
            arg1->unk_20[1].unk_24 = var_f31;
            arg1->unk_20[0].unk_24 = var_f31;
            break;
        default:
            for (var_r28 = 0; var_r28 < 2; var_r28++) {
                arg1->unk_20[var_r28].unk_00[0] = -1;
                arg1->unk_20[var_r28].unk_00[1] = -1;
            }
            arg1->unk_20[2].unk_00[0] = -1;
            arg1->unk_20[2].unk_00[1] = -1;
            arg1->unk_20[3].unk_00[0] = -1;
            arg1->unk_20[3].unk_00[1] = -1;
            arg1->unk_00 = 0;
            break;
    }
    for (var_r28 = 0; var_r28 < 3; var_r28++) {
        var_r29 = &arg1->unk_D0[var_r28][0];
        for (var_r22 = 0; var_r22 < 0x14; var_r22++, var_r29++) {
            if (var_r29->unk_00[0] >= 0) {
                espDispOff(var_r29->unk_00[0]);
            }
            if (var_r29->unk_00[1] >= 0) {
                espDispOff(var_r29->unk_00[1]);
            }
        }
    }
    var_r29 = &arg1->unk_490;
    if (var_r29->unk_00[0] >= 0) {
        espDispOff(var_r29->unk_00[0]);
    }
    if (var_r29->unk_00[1] >= 0) {
        espDispOff(var_r29->unk_00[1]);
    }
    fn_1_EA8C(&arg1->unk_20[0]);
    fn_1_EA8C(&arg1->unk_20[1]);
    fn_1_EA8C(&arg1->unk_20[2]);
    fn_1_EA8C(&arg1->unk_20[3]);
    arg1->unk_04++;
}

void fn_1_FE64(M433PlayerWork3Sub2 *arg0, s32 arg1, s32 arg2, u32 arg3)
{
    arg0->unk_00 = 1;
    arg0->unk_0C = arg0->unk_14[0];
    arg0->unk_10 = arg0->unk_14[1];
    arg0->unk_14[0] = arg1;
    arg0->unk_14[1] = arg2;
    arg0->unk_1C = arg3;
}

void fn_1_FE8C(Vec *arg0, u32 arg1, u32 arg2, s32 arg3)
{
    M433PlayerWork2 *var_r31 = lbl_1_bss_7CC->data;
    var_r31->unk_18 = 0;
    if (arg1 < 9) {
        var_r31->unk_18 = lbl_1_data_770[arg1];
        if (lbl_1_data_794[arg1].unk_00 != 0) {
            M433PlayerWork3 *var_r30 = lbl_1_bss_7C8->data;
            var_r30->unk_30 = 1;
            var_r30->uContactGrp = arg2;
            var_r30->uContactCel = arg3;
            var_r30->uTargetGrp = arg2;
            if (lbl_1_data_794[arg1].unk_04 != 0) {
                var_r30->uTargetGrp = 1 - var_r30->uTargetGrp;
            }
            if (lbl_1_data_794[arg1].unk_08 != 0) {
                var_r30->uContactCnt++;
            }
        }
    }
    if (arg1 == 5) {
        s32 var_r28 = 6;
        if (var_r31->unk_6C == 5) {
            var_r28++;
        }
        Hu3DModelPosSetV(lbl_1_bss_7CC->model[var_r28], &var_r31->unk_30);
        Hu3DModelAttrReset(lbl_1_bss_7CC->model[var_r28], HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(lbl_1_bss_7CC->model[var_r28], 0.0f);
        Hu3DMotionShapeTimeSet(lbl_1_bss_7CC->model[var_r28], 0.0f);
    }
    else if (arg1 != 2) {
        var_r31->unk_A8 = 1.0f;
    }
    var_r31->unk_0C = 1;
    var_r31->unk_10 = 0;
    var_r31->unk_04 = 0;
    var_r31->unk_08 = 0;
    var_r31->unk_6C = arg1;
    var_r31->unk_70 = arg2;
    var_r31->unk_74 = arg3;
    if (lbl_1_data_800[arg1] != 0) {
        var_r31->unk_78 = lbl_1_data_800[arg1];
    }
    else if (var_r31->unk_78 != 0) {
        var_r31->unk_78--;
    }
    var_r31->unk_3C = *arg0;
    if (arg1 == 0) {
        var_r31->unk_30 = var_r31->unk_3C;
    }
    var_r31->unk_F8.unk_00 = 1.0f;
    var_r31->unk_F8.unk_00 = 0.0f;
}

void fn_1_10130(Vec *arg0, u32 arg1)
{
    float var_f31 = 44.0f;
    if ((arg0->z - var_f31) < -500.0f) {
        arg0->z = -500.0f + var_f31;
    }
    else if ((arg0->z + var_f31) > 500.0f) {
        arg0->z = 500.0f - var_f31;
    }
    if (arg1 == 0) {
        arg0->x *= -1.0f;
    }
    if ((arg0->x - var_f31) < 20.0f) {
        arg0->x = 20.0f + var_f31;
    }
    else if ((arg0->x + var_f31) > 800.0f) {
        arg0->x = 800.0f - var_f31;
    }
    if (arg1 == 0) {
        arg0->x *= -1.0f;
    }
}

void fn_1_10260(float var_f29, float var_f30, u32 var_r30, u32 sp8, Vec *var_r29)
{
    M433PlayerWork2 *var_r31 = lbl_1_bss_7CC->data;
    if (var_f30 > 1.0f) {
        var_f30 = 1.0f;
    }
    if (var_r31->unk_94 == 0) {
        var_r31->unk_AC.x = 465.0f;
        var_r31->unk_AC.y = 11.0f;
        var_r31->unk_AC.z = 0.0f;
        if (var_r30 != 0) {
            var_r31->unk_AC.x *= -1.0f;
        }
        var_r31->unk_94 = 1;
        var_r31->unk_98 = 0;
        var_r31->unk_A4 = 0.0f;
        var_r31->unk_8C = 0;
        var_r31->unk_A8 = 1.0f;
    }
    if (sp8 != 0) {
        var_r31->unk_94 = 2;
        var_f30 *= 1.5f;
    }
    var_r31->unk_90 = 1;
    var_r31->unk_AC.x += 0.01666666753590107 * (800.0 * (var_f30 * sind(var_f29)));
    var_r31->unk_AC.z += 0.01666666753590107 * (800.0 * (var_f30 * cosd(var_f29)));
    if (var_r30 != 0) {
        var_r31->unk_AC.x *= -1.0f;
    }
    if (var_r31->unk_AC.x < 230.0f) {
        var_r31->unk_AC.x = 230.0f;
    }
    if (var_r30 != 0) {
        var_r31->unk_AC.x *= -1.0f;
    }
    fn_1_10130(&var_r31->unk_AC, 1 - var_r30);
    *var_r29 = var_r31->unk_AC;
}

s32 fn_1_10614(Vec *arg0)
{
    M433PlayerWork2 *work = lbl_1_bss_7CC->data;

    arg0->x = arg0->y = arg0->z = 0.0f;
    if (work->unk_94 == 0) {
        return 0;
    }
    *arg0 = work->unk_AC;
    arg0->x = fabs(arg0->x);
    arg0->x -= 465.0f;
    arg0->x *= 0.004255319f;
    arg0->z *= 0.0028571428f;
    return 1;
}

void fn_1_1070C(void)
{
    M433PlayerWork2 *work = lbl_1_bss_7CC->data;
    work->unk_A8 = 1.0f;
}

u32 fn_1_10740(Vec *arg0)
{
    u32 var_r30;
    M433PlayerWork2 *work = lbl_1_bss_7CC->data;
    *arg0 = work->unk_3C;
    if (work->unk_3C.x >= 0.0f) {
        var_r30 = 1;
    }
    else {
        var_r30 = 0;
    }
    return var_r30;
}

u32 fn_1_107B0(Vec *arg0)
{
    u32 var_r30;
    M433PlayerWork2 *var_r31 = lbl_1_bss_7CC->data;
    if (var_r31->unk_94 != 0) {
        *arg0 = var_r31->unk_AC;
    }
    else {
        *arg0 = var_r31->unk_3C;
    }
    if (arg0->x >= 0.0f) {
        var_r30 = 1;
    }
    else {
        var_r30 = 0;
    }
    return var_r30;
}

float fn_1_10848(void)
{
    M433PlayerWork2 *var_r31 = lbl_1_bss_7CC->data;
    return var_r31->unk_F8.unk_00 - var_r31->unk_F8.unk_04;
}

float fn_1_10878(void)
{
    M433PlayerWork2 *var_r31 = lbl_1_bss_7CC->data;
    if (var_r31->unk_94 != 0) {
        return 1.5f;
    }
    return var_r31->unk_F8.unk_00 - var_r31->unk_F8.unk_04;
}

u32 fn_1_108C4(void)
{
    M433PlayerWork2 *var_r31 = lbl_1_bss_7CC->data;
    if (var_r31->unk_94 != 0) {
        return var_r31->unk_98;
    }
    return 0x2710;
}

u32 fn_1_10900(void)
{
    M433PlayerWork2 *var_r31 = lbl_1_bss_7CC->data;
    return var_r31->unk_8C;
}

float fn_1_10928(float arg8)
{
    float var_f30;
    float var_f28;
    float var_f26;
    M433PlayerWork2Sub *var_r31;
    M433PlayerWork2 *var_r30;

    var_r30 = lbl_1_bss_7CC->data;
    var_r31 = &var_r30->unk_F8;
    var_f28 = 1.0f / var_r31->unk_24;
    var_f30 = -var_r31->unk_20 * var_f28;
    var_f26 = var_r31->unk_2C.y + ((var_f30 * (0.5f * var_r31->unk_24 * var_f30)) + (var_r31->unk_20 * var_f30));
    if (arg8 > (var_f26)) {
        return -1.0f;
    }
    var_f30 = var_f28 * (-var_r31->unk_20 - sqrtf((var_r31->unk_20 * var_r31->unk_20) - (2.0f * var_r31->unk_24 * (var_r31->unk_2C.y - arg8))));
    var_f30 -= var_r31->unk_04;
    return var_f30;
}

float fn_1_10B20(float arg8, Vec *arg0)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    M433PlayerWork2Sub *var_r31;
    M433PlayerWork2 *var_r29;

    var_r29 = lbl_1_bss_7CC->data;
    var_r31 = &var_r29->unk_F8;
    var_f30 = var_r31->unk_04;
    var_f31 = var_f30 + arg8;
    if (var_f31 < 0.0f) {
        var_f31 = 0.0f;
    }
    if (var_f31 > var_r31->unk_00) {
        var_f31 = var_r31->unk_00;
    }
    var_r31->unk_04 = var_f31;
    if (var_r31->unk_10 > 0.0f) {
        VECSubtract(&var_r31->unk_38, &var_r31->unk_2C, &sp14);
        sp14.y = 0.0f;
        VECNormalize(&sp14, &sp14);
    }
    else {
        sp14.x = sp14.y = sp14.z = 0.0f;
    }
    sp8 = *arg0;
    var_f29 = (var_f31 * (0.5f * var_r31->unk_18 * var_f31)) + (var_r31->unk_14 * var_f31);
    var_f28 = (var_f31 * (0.5f * var_r31->unk_24 * var_f31)) + (var_r31->unk_20 * var_f31);
    arg0->x = var_r31->unk_2C.x + (sp14.x * var_f29);
    arg0->y = var_r31->unk_2C.y + var_f28;
    arg0->z = var_r31->unk_2C.z + (sp14.z * var_f29);
    VECSubtract(arg0, &sp8, &sp20);
    var_f31 >= var_r31->unk_00;
    var_r31->unk_04 = var_f30;
    return var_f30 + arg8;
}

static inline float fn_1_10D24_inline(Vec *arg0)
{
    M433PlayerWork2 *var_r31 = lbl_1_bss_7CC->data;
    if (var_r31->unk_94 != 0) {
        *arg0 = var_r31->unk_AC;
    }
    else {
        *arg0 = var_r31->unk_3C;
    }
}

s32 fn_1_10D24(Vec *sp8)
{
    Vec sp18;
    Vec spC;
    float var_f31;
    float var_f30;
    M433PlayerWork2 *var_r31;
    M433PlayerWork2 *var_r30;

    var_r31 = lbl_1_bss_7CC->data;
    fn_1_10D24_inline(&spC);
    VECSubtract(&spC, &var_r31->unk_30, &sp18);
    if ((spC.x * var_r31->unk_30.x) >= 0.0f) {
        return 0;
    }
    if ((var_r31->unk_30.x == 0.0f) || (sp18.x == 0.0f)) {
        return 0;
    }
    var_f31 = fabs(var_r31->unk_30.x / sp18.x);
    VECScale(&sp18, &sp18, var_f31);
    VECAdd(&var_r31->unk_30, &sp18, sp8);
    return 1;
}

u32 fn_1_10EA4(void)
{
    M433PlayerWork3 *var_r31 = lbl_1_bss_7C8->data;
    return var_r31->uGameEvent;
}

u32 fn_1_10ECC(u32 arg0)
{
    M433PlayerWork3 *work = lbl_1_bss_7C8->data;
    return work->auEvents[arg0 & 1];
}

s32 fn_1_10F00(u32 arg0)
{
    M433PlayerWork3 *var_r31 = lbl_1_bss_7C8->data;
    return var_r31->uServeGrp == (arg0 & 1);
}

u32 fn_1_10F38(u32 arg0)
{
    M433PlayerWork3 *var_r31 = lbl_1_bss_7C8->data;
    return var_r31->auServeCel[arg0 & 1];
}

s32 fn_1_10F6C(u32 arg0)
{
    M433PlayerWork3 *work = lbl_1_bss_7C8->data;
    return work->uPointGrp == (arg0 & 1);
}

s32 fn_1_10FA4(s32 arg0)
{
    M433PlayerWork3 *work = lbl_1_bss_7C8->data;
    return work->sWinGrp == (arg0 & 1);
}

u32 fn_1_10FDC(void)
{
    M433PlayerWork3 *var_r31 = lbl_1_bss_7C8->data;
    return var_r31->uContactCnt;
}

s32 fn_1_11004(u32 arg0, s32 arg1)
{
    M433PlayerWork3 *work = lbl_1_bss_7C8->data;
    return !((work->uContactGrp == (arg0 & 1)) && (work->uContactCel == (arg1 & 1)));
}

s32 fn_1_11060(u32 arg0)
{
    M433PlayerWork3 *work = lbl_1_bss_7C8->data;
    return work->uContactGrp == (arg0 & 1);
}

float fn_1_11098(Vec *arg0, Vec *arg1, Vec *arg2)
{
    Vec sp10;
    float var_f31;
    float var_f30;

    VECSubtract(arg1, arg0, &sp10);
    var_f31 = VECDotProduct(&sp10, arg2);
    var_f30 = -VECSquareMag(arg2);
    if (var_f30 != 0.0f) {
        var_f31 /= var_f30;
    }
    return var_f31;
}

float fn_1_11130(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3)
{
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    VECSubtract(arg1, arg0, &sp28);
    VECSubtract(arg3, arg2, &sp1C);
    VECSubtract(&sp28, &sp1C, &sp28);
    if (VECMag(&sp28) <= 0.0f) {
        sp34 = *arg0;
    }
    else {
        VECSubtract(arg0, arg2, &sp10);
        var_f30 = VECDotProduct(&sp10, &sp28);
        var_f29 = -VECSquareMag(&sp28);
        if (var_f29 != 0.0f) {
            var_f30 /= var_f29;
        }
        var_f28 = var_f30;
        var_f31 = var_f28;
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
        }
        else if (var_f31 > 1.0f) {
            var_f31 = 1.0f;
        }
        VECScale(&sp28, &sp1C, var_f31);
        VECAdd(arg0, &sp1C, &sp34);
    }
    VECSubtract(arg2, &sp34, &sp28);
    return VECMag(&sp28);
}
