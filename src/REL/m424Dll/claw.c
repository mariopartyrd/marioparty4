#include "REL/m424Dll.h"

#include "math.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/pad.h"

// STRUCT
typedef struct _M424DllClawStruct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    Vec unk30;
    Vec unk3C[12];
    Vec unkCC[12];
    s32 unk15C;
    s32 unk160;
    s32 unk164;
    s32 unk168;
    s32 unk16C;
    s32 unk170;
    Vec unk174;
    f32 unk180;
    s32 unk184;
    s32 unk188;
    s32 unk18C;
    s32 unk190;
    s32 unk194;
    s32 unk198;
    s32 unk19C;
    s32 unk1A0;
    s32 unk1A4;
    f32 unk1A8;
    s32 unk1AC;
} M424DllClawStruct; // sizeof 0x1B0

typedef struct _M424DllClawStruct2 {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} M424DllClawStruct2; // sizeof 0x10

typedef struct _M424DllClawStruct3 {
    s32 unk0;
    s32 unk4;
} M424DllClawStruct3; // sizeof 0x8

// BSS
Process* lbl_1_bss_6DC;
omObjData* lbl_1_bss_6D8;
s32 lbl_1_bss_6D0[2];
s32 lbl_1_bss_6CC;
s32 lbl_1_bss_6C8;
s32 lbl_1_bss_6C4;
s32 lbl_1_bss_6C0;
M424DllClawStruct3 lbl_1_bss_640[0x10];

// DATA
Vec lbl_1_data_1E0[4] = {
    { 950.0f, 275.0f, 0.0f },
    { 900.0f, 360.0f, 320.0f },
    { 494.99996f, 220.0f, 494.99996f },
    { 0.0f, 225.0f, 0.0f },
};
f32 lbl_1_data_210[3] = { 12.0f, 11.0f, 17.5f };
char lbl_1_data_21C[12][0x10] = {
    "tsume10",
    "tsume11",
    "tsume12",
    "tsume20",
    "tsume21",
    "tsume22",
    "tsume30",
    "tsume31",
    "tsume32",
    "tsume40",
    "tsume41",
    "tsume42",
};
u8 lbl_1_data_2DC[12] = { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 };
s32 lbl_1_data_2E8[9] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x06), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x42),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x08), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17), DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x18) };
Vec lbl_1_data_30C = { 0.0f, 0.0f, 0.0f };

// PROTO
void fn_1_88E8(u8, f32, f32, f32);
void fn_1_8924(u8, s32);
u8 fn_1_8950(u8);
u8 fn_1_897C(u8);
u8 fn_1_89A8(u8);
Vec *fn_1_89D4(u8);
void fn_1_94D0(omObjData *);
void fn_1_9A64(omObjData *);
void fn_1_AE58(omObjData *);
void fn_1_AE64(omObjData *);
u16 fn_1_B79C(f32, f32, f32);
s32 fn_1_B9E0(Vec *arg0, Vec *arg1, f32 arg8, Vec *arg2, s32 arg3);
void fn_1_C604(s32, s32);
s32 fn_1_C878(s16, const char *, Mtx, s32);
void fn_1_C99C(HsfObject *, Mtx, const char *, Mtx);
void fn_1_CE74(s32);
void fn_1_CF00(Process *);
void fn_1_CF80(omObjData *);
s32 fn_1_D010(s32, s32);

omObjData *fn_1_93F0(Process *arg0)
{
    lbl_1_bss_6DC = arg0;
    lbl_1_bss_6D8 = omAddObjEx(arg0, 0x40, 5, 9, -1, fn_1_94D0);
    lbl_1_bss_6CC = 0;
    lbl_1_bss_6C8 = 0;
    lbl_1_bss_6C4 = 0;
    lbl_1_bss_6C0 = 0;
    fn_1_CF00(arg0);
    return lbl_1_bss_6D8;
}

void fn_1_94A4(void)
{
    fn_1_AE58(lbl_1_bss_6D8);
}

void fn_1_94D0(omObjData *arg0)
{
    s32 var_r29;
    M424DllClawStruct *var_r31;

    var_r31 = arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x1B0, 0x10000000);
    memset(var_r31, 0, 0x1B0);
    var_r31->unk0 = lbl_1_bss_24[3];
    var_r31->unk2 = GWPlayerCfg[var_r31->unk0].character;
    var_r31->unk4 = GWPlayerCfg[var_r31->unk0].pad_idx;
    var_r31->unk6 = GWPlayerCfg[var_r31->unk0].iscom;
    var_r31->unk8 = GWPlayerCfg[var_r31->unk0].diff;
    var_r31->unkA = var_r31->unkC = 0;
    var_r31->unk10 = 0;
    var_r31->unk12 = 0;
    var_r31->unk14 = 0;
    var_r31->unk16 = 0;
    var_r31->unk18 = 0;
    var_r31->unk1C = 0.0f;
    var_r31->unk20 = 1.0f;
    var_r31->unk24 = 0.0f;
    var_r31->unk28 = 0.0f;
    var_r31->unk2C = 1.0f;
    var_r31->unk15C = 0;
    var_r31->unk160 = 0;
    var_r31->unk164 = 0;
    var_r31->unk168 = -1;
    var_r31->unk16C = -1;
    var_r31->unk170 = -1;
    var_r31->unk174 = lbl_1_data_30C;
    // @todo how did this happen
    var_r31->unk180 = atan2d(-102.864990234375, 424.559997558593750);
    if (var_r31->unk180 < 0.0f) {
        var_r31->unk180 += 360.0f;
    }
    var_r31->unk184 = -1;
    var_r31->unk30 = lbl_1_data_30C;
  
    for (var_r29 = 0; var_r29 < 0xC; var_r29++) {
        var_r31->unk3C[var_r29] = lbl_1_data_30C;
        var_r31->unkCC[var_r29] = lbl_1_data_30C;
    }
    var_r31->unk188 = 0;
    var_r31->unk18C = -1;
    var_r31->unk190 = 0;
    var_r31->unk194 = 0;
    var_r31->unk198 = 0;
    var_r31->unk19C = 0;
    var_r31->unk1A0 = 0;
    var_r31->unk1A4 = 0;
    var_r31->unk1A8 = 0.0f;
    var_r31->unk1AC = 0;
    arg0->model[0] = CharModelCreate(var_r31->unk2, 1);
    Hu3DModelShadowSet(arg0->model[0]);
    CharModelStepTypeSet(var_r31->unk2, 1);
    for (var_r29 = 0; var_r29 < 9; var_r29++) {
        arg0->motion[var_r29] = CharModelMotionCreate(var_r31->unk2, lbl_1_data_2E8[var_r29]);
    }
    var_r31->unkE = 5;
    CharModelMotionSet(var_r31->unk2, arg0->motion[var_r31->unkE]);
    arg0->model[1] = Hu3DModelCreateFile(0x37001D);
    Hu3DModelShadowSet(arg0->model[1]);
    arg0->model[2] = Hu3DModelCreateFile(0x37001E);
    Hu3DModelShadowSet(arg0->model[2]);
    arg0->model[3] = Hu3DModelCreateFile(0x37001F);
    Hu3DModelShadowSet(arg0->model[3]);
    arg0->model[4] = Hu3DModelCreateFile(0x370020);
    Hu3DModelShadowSet(arg0->model[4]);
    Hu3DModelScaleSet(arg0->model[4], 0.9f, 0.9f, 0.9f);
    Hu3DModelHookSet(arg0->model[1], "hook1", arg0->model[2]);
    Hu3DModelHookSet(arg0->model[2], "hook2", arg0->model[3]);
    Hu3DModelHookSet(arg0->model[3], "hook3", arg0->model[4]);
    Hu3DModelPosSet(arg0->model[1], 950.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[2], 0x40000002);
    Hu3DModelAttrSet(arg0->model[4], 0x40000002);
    arg0->trans.x = 950.0f;
    arg0->trans.y = 275.0f;
    arg0->trans.z = 0.0f;
    arg0->rot.y = 270.0f;
    var_r31->unk10 = 3;
    var_r31->unk24 = 0.45f;
    var_r31->unk12 = 0;
    arg0->func = fn_1_9A64;
}

void fn_1_9A64(omObjData *arg0)
{
    Mtx sp74;
    Mtx sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 var_f31;
    f32 temp_f30;
    M424DllClawStruct *temp_r31;
    s32 var_r29;
    s32 temp_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;

    temp_r31 = arg0->data;
    if (fn_1_FE0() == 4) {
        temp_r31->unkC = HuPadBtn[temp_r31->unk4];
        temp_r31->unkA = HuPadBtnDown[temp_r31->unk4];
        if (temp_r31->unk6 != 0) {
            fn_1_AE64(arg0);
        }
    }
    else {
        temp_r31->unkC = 0;
        temp_r31->unkA = 0;
    }
    if (fn_1_FE0() <= 1) {
        var_r25 = -1;
    }
    else {
        var_r25 = temp_r31->unk10;
    }
    switch (var_r25) {
        case 0:
            if (fn_1_FE0() >= 4) {
                temp_r31->unk10 = 1;
                temp_r31->unk12 = 0;
            }
            break;
        case 1:
            if (fn_1_FE0() > 4) {
                temp_r31->unk10 = 10;
                temp_r31->unk12 = 0;
            }
            else if ((temp_r31->unkA & 0x100) != 0) {
                HuAudFXPlay(0x62A);
                temp_r31->unk184 = HuAudFXPlay(0x621);
                temp_r31->unk10 = 2;
                temp_r31->unk12 = 0;
            }
            break;
        case 2:
            temp_r31->unk12++;
            temp_r31->unk24 += ((1.0f / 60.0f) * temp_r31->unk20);
            if (temp_r31->unk24 >= 1.0f) {
                temp_r31->unk24 = 1.0f;
                temp_r31->unk20 = -1.0f;
            }
            else {
                if (temp_r31->unk24 <= 0.0f) {
                    temp_r31->unk24 = 0.0f;
                    temp_r31->unk20 = 1.0f;
                }
            }
            if (fn_1_FE0() > 4) {
                if (temp_r31->unk184 != -1) {
                    HuAudFXStop(temp_r31->unk184);
                    temp_r31->unk184 = -1;
                }
                HuAudFXPlay(0x622);
                temp_r31->unk10 = 10;
                temp_r31->unk12 = 0;
            }
            else if (((temp_r31->unkC & 0x100) == 0) || (temp_r31->unk12 >= 360.0f)) {
                if (temp_r31->unk184 != -1) {
                    HuAudFXStop(temp_r31->unk184);
                    temp_r31->unk184 = -1;
                }
                HuAudFXPlay(0x622);
                temp_r31->unk184 = HuAudFXPlay(0x62C);
                temp_r31->unk168 = -1;
                temp_r31->unk16C = -1;
                temp_r31->unk10 = 3;
                temp_r31->unk12 = 0;
            }
            break;
        case 3:
            temp_r31->unk12++;
            if (temp_r31->unk15C == 0) {
                temp_r31->unk28 += (1.0f / 60.0f);
            }
            if (temp_r31->unk28 > 1.0f) {
                temp_r31->unk28 = 1.0f;
            }
            if (temp_r31->unk12 >= 0x3C) {
                if (temp_r31->unk184 != -1) {
                    HuAudFXStop(temp_r31->unk184);
                    temp_r31->unk184 = -1;
                }
                HuAudFXPlay(0x62D);
                HuAudFXPlay(0x625);
                temp_r31->unk10 = 4;
                temp_r31->unk12 = 0;
            }
            temp_r31->unk15C = 0;
            break;
        case 4:
            temp_r31->unk12++;
            if (temp_r31->unk160 == 0) {
                temp_r31->unk2C -= (1.0f / 60.0f);
            }
            if (temp_r31->unk2C < 0.0f) {
                temp_r31->unk2C = 0.0f;
            }
            if (temp_r31->unk12 >= 0x3C) {
                temp_r31->unk10 = 5;
                temp_r31->unk12 = 0;
            }
            temp_r31->unk160 = 0;
            break;
        case 5:
            temp_r31->unk12++;
            if (temp_r31->unk12 >= 6.0f) {
                temp_r31->unk184 = HuAudFXPlay(0x62C);
                if ((temp_r31->unk168 != -1)) {
                    var_r27 = fn_1_897C(temp_r31->unk168);
                    if (var_r27 != 0) {
                        var_r26 = fn_1_89A8(temp_r31->unk168);
                        HuAudCharVoicePlay(var_r26, 0x128);
                    }
                }
                temp_r31->unk10 = 6;
                temp_r31->unk12 = 0;
            }
            break;
        case 6:
            temp_r31->unk12++;
            temp_r31->unk28 -= (1.0f / 45.0f);
            if (temp_r31->unk28 <= 0.0f) {
                if (temp_r31->unk184 != -1) {
                    HuAudFXStop(temp_r31->unk184);
                    temp_r31->unk184 = -1;
                }
                HuAudFXPlay(0x62D);
                temp_r31->unk28 = 0.0f;
                if (temp_r31->unk168 != -1) {
                    var_r27 = fn_1_897C(temp_r31->unk168);
                }
                else {
                    var_r27 = -1;
                }
                if (temp_r31->unk168 == -1) {
                    if (fn_1_FE0() > 4) {
                        temp_r31->unk10 = 10;
                        temp_r31->unk12 = 0;
                    }
                    else {
                        temp_r31->unk10 = 8;
                        temp_r31->unk12 = 0;
                        HuAudFXPlay(0x625);
                    }
                }
                else if (var_r27 == 0) {
                    temp_r31->unk10 = 8;
                    temp_r31->unk12 = 0;
                    HuAudFXPlay(0x625);
                }
                else {
                    if (temp_r31->unk168 != -1) {
                        fn_1_252C(-0.01f, 0x3C);
                        fn_1_2670(0x75, 0);
                    }
                    HuAudFXPlay(0x62B);
                    temp_r31->unk184 = HuAudFXPlay(0x623);
                    temp_r31->unk10 = 7;
                    temp_r31->unk12 = 0;
                }
            }
            break;
        case 7:
            if (arg0->rot.y < temp_r31->unk180) {
                arg0->rot.y += 1.25f;
            }
            else if (arg0->rot.y > temp_r31->unk180) {
                arg0->rot.y = temp_r31->unk180;
            }
            var_f31 = 0.35f - temp_r31->unk24;
            if (var_f31 > 0.0125f) {
                temp_r31->unk24 += 0.0125f;
            }
            else if (var_f31 < -0.0125f) {
                temp_r31->unk24 -= 0.0125f;
            }
            else {
                temp_r31->unk24 = 0.35f;
            }
            if ((arg0->rot.y == temp_r31->unk180) && (0.35f == temp_r31->unk24)) {
                if (temp_r31->unk184 != -1) {
                    HuAudFXStop(temp_r31->unk184);
                    temp_r31->unk184 = -1;
                }
                HuAudFXPlay(0x624);
                HuAudFXPlay(0x625);
                temp_r31->unk10 = 8;
                temp_r31->unk12 = 0;
            }
            break;
        case 8:
            if ((temp_r31->unk12 == 0) && (temp_r31->unk168 != -1)) {
                if (fn_1_897C(temp_r31->unk168) != 0) {
                    fn_1_8924(temp_r31->unk168, 4);
                    var_r26 = fn_1_89A8(temp_r31->unk168);
                    HuAudCharVoicePlay(var_r26, 0x123);
                    fn_1_D010(0x628, 30);
                }
                else {
                    fn_1_8924(temp_r31->unk168, 2);
                }
                temp_r31->unk16C = temp_r31->unk168;
                temp_r31->unk168 = -1;
            }
            temp_r31->unk12++;
            temp_r31->unk2C += 0.033333335f;
            if (temp_r31->unk2C > 1.0f) {
                temp_r31->unk2C = 1.0f;
            }
            if (temp_r31->unk2C >= 1.0f) {
                if (arg0->rot.y == temp_r31->unk180) {
                    temp_r31->unk184 = HuAudFXPlay(0x623);
                }
                if (temp_r31->unk16C != -1) {
                    if (fn_1_897C(temp_r31->unk16C) != 0) {
                        lbl_1_bss_6CC++;
                    }
                }
                temp_r31->unk10 = 9;
                temp_r31->unk12 = 0;
            }
            break;
        case 9:
            temp_r31->unk12++;
            if (arg0->rot.y > 270.0f) {
                arg0->rot.y -= 1.25f;
            }
            else if (arg0->rot.y < 270.0f) {
                arg0->rot.y = 270.0f;
            }
            if (temp_r31->unk24 > 0.025f) {
                temp_r31->unk24 -= 0.025f;
            }
            else if (temp_r31->unk24 < 0.05f) {
                temp_r31->unk24 = 0.0f;
            }
            if ((270.0f == arg0->rot.y) && (0.0f == temp_r31->unk24)) {
                if (temp_r31->unk184 != -1) {
                    HuAudFXStop(temp_r31->unk184);
                    temp_r31->unk184 = -1;
                    HuAudFXPlay(0x624);
                }
                temp_r31->unk20 = 1.0f;
                temp_r31->unk10 = 1;
                temp_r31->unk12 = 0;
            }
            break;
        case 10:
            if (fn_1_B888() != 0) {
                temp_r31->unkE = 5;
                CharModelMotionSet(temp_r31->unk2, arg0->motion[temp_r31->unkE]);
                temp_r31->unkE = 3;
                CharModelMotionShiftSet(temp_r31->unk2, arg0->motion[temp_r31->unkE], 0.0f, 8.0f, 0U);
                temp_r31->unk16 = 0;
                temp_r31->unk14 = 0;
                temp_r31->unk1C = lbl_1_data_210[0];
                temp_r31->unk18 = fn_1_B79C(lbl_1_data_1E0[0].y, lbl_1_data_1E0[1].y, temp_r31->unk1C);
                temp_r31->unk10 = 11;
                temp_r31->unk12 = 0;
            }
            else {
                temp_r31->unk10 = 13;
                temp_r31->unk12 = 0;
            }
            break;
        case 11:
            var_r29 = temp_r31->unk14;
            if (var_r29 > 2) {
                var_r29 = 2;
            }
            if (temp_r31->unk16 == 0) {
                temp_r31->unk12++;
                sp14 = lbl_1_data_1E0[var_r29];
                sp8 = lbl_1_data_1E0[var_r29 + 1];
                arg0->rot.y = fn_1_1470(atan2d((sp8.x - arg0->trans.x), (sp8.z - arg0->trans.z)), arg0->rot.y, 10.0f);
                var_f31 = (f32)temp_r31->unk12 / temp_r31->unk18;
                arg0->trans.x = sp14.x + (var_f31 * (sp8.x - sp14.x));
                arg0->trans.z = sp14.z + (var_f31 * (sp8.z - sp14.z));
                arg0->trans.y += temp_r31->unk1C;
                temp_r31->unk1C -= 0.65333337f;
                if (temp_r31->unk14 == 2) {
                    if ((temp_r31->unk12 >= (0.4f * temp_r31->unk18)) && (temp_r31->unkE != 6) && (CharModelMotionShiftIDGet(temp_r31->unk2) == -1)) {
                        temp_r31->unkE = 6;
                        CharModelMotionShiftSet(temp_r31->unk2, arg0->motion[temp_r31->unkE], 0.0f, 8.0f, 0);
                    }
                }
                if (temp_r31->unk12 >= temp_r31->unk18) {
                    arg0->trans.x = sp8.x;
                    arg0->trans.y = sp8.y;
                    arg0->trans.z = sp8.z;
                    temp_r31->unkE = 4;
                    CharModelMotionShiftSet(temp_r31->unk2, arg0->motion[temp_r31->unkE], 0.0f, 8.0f, 0U);
                    temp_r31->unk12 = 0;
                    temp_r31->unk16 ^= 1;
                    if (++temp_r31->unk14 >= 3) {
                        temp_r31->unk10 = 0xC;
                    }
                }
            }
            else {
                sp14 = lbl_1_data_1E0[var_r29];
                sp8 = lbl_1_data_1E0[var_r29 + 1];
                var_f31 = atan2d((sp8.x - arg0->trans.x), (sp8.z - arg0->trans.z));
                arg0->rot.y = fn_1_1470(var_f31, arg0->rot.y, 10.0f);
                if ((fn_1_1358(var_f31, arg0->rot.y) < 1.0f) && (CharModelMotionShiftIDGet(temp_r31->unk2) == -1)) {
                    temp_r31->unkE = 3;
                    CharModelMotionShiftSet(temp_r31->unk2, arg0->motion[temp_r31->unkE], 0.0f, 8.0f, 0);
                    temp_r31->unk1C = lbl_1_data_210[var_r29];
                    temp_r31->unk18 = fn_1_B79C(sp14.y, sp8.y, temp_r31->unk1C);
                    temp_r31->unk12 = 0;
                    temp_r31->unk16 ^= 1;
                }
            }
            break;
        case 12:
            if ((temp_r31->unkE != 0) && (CharModelMotionShiftIDGet(temp_r31->unk2) == -1)) {
                temp_r31->unkE = 0;
                CharModelMotionShiftSet(temp_r31->unk2, arg0->motion[temp_r31->unkE], 0.0f, 8.0f, 0x40000008);
            }
            arg0->rot.y = fn_1_1470(0.0f, arg0->rot.y, 10.0f);
            if ((fn_1_1358(0.0f, arg0->rot.y) < 1.0f) && (temp_r31->unkE == 0)) {
                temp_r31->unk10 = 0xD;
                temp_r31->unk12 = 0;
            }
            break;
        case 13:
            if (fn_1_FE0() >= 7) {
                if (fn_1_B888() != 0) {
                    temp_r31->unk10 = 14;
                    temp_r31->unk12 = 0;
                }
                else {
                    temp_r31->unk10 = 15;
                    temp_r31->unk12 = 0;
                }
            }
            break;
        case 14:
            if ((temp_r31->unkE != 7) && (CharModelMotionShiftIDGet(temp_r31->unk2) == -1)) {
                temp_r31->unkE = 7;
                CharModelMotionShiftSet(temp_r31->unk2, arg0->motion[temp_r31->unkE], 0.0f, 8.0f, 0);
            }
            break;
        case 15:
            break;
    }
    if (temp_r31->unk10 <= 9) {
        Hu3DModelRotSet(arg0->model[1], 0.0f, 90.0f + arg0->rot.y, 0.0f);
    }
    temp_r28 = arg0->model[2];
    Hu3DMotionTimeSet(temp_r28, temp_r31->unk24 * Hu3DMotionMaxTimeGet(temp_r28));
    fn_1_CE74(temp_r28);
    temp_f30 = 0.2f + (0.8f * temp_r31->unk28);
    Hu3DModelScaleSet(arg0->model[3], 1.0f, temp_f30, 1.0f);
    Hu3DModelScaleSet(arg0->model[4], 1.0f, 1.0f / temp_f30, 1.0f);
    temp_r28 = arg0->model[4];
    Hu3DMotionTimeSet(temp_r28, temp_r31->unk2C * Hu3DMotionMaxTimeGet(temp_r28));
    fn_1_CE74(temp_r28);
    fn_1_C878(arg0->model[1], "hook1", sp74, 0);
    fn_1_C878(arg0->model[2], "hook2", sp74, 1);
    fn_1_C878(arg0->model[3], "hook3", sp74, 1);
    PSMTXCopy(sp74, sp44);
    temp_r31->unk30.x = sp74[0][3];
    temp_r31->unk30.y = sp74[1][3];
    temp_r31->unk30.z = sp74[2][3];

    for (var_r29 = 0; var_r29 < 0xC; var_r29++) {
        PSMTXCopy(sp44, sp74);
        fn_1_C878(arg0->model[4], lbl_1_data_21C[var_r29], sp74, 1);
        temp_r31->unkCC[var_r29] = temp_r31->unk3C[var_r29];
        temp_r31->unk3C[var_r29].x = sp74[0][3];
        temp_r31->unk3C[var_r29].y = sp74[1][3];
        temp_r31->unk3C[var_r29].z = sp74[2][3];
    }
    if ((temp_r31->unk168 != -1) && (temp_r31->unk10 >= 6)) {
        sp2C.x = 0.0f;
        sp2C.y = temp_r31->unk174.y;
        sp2C.z = 0.0f;
        PSVECSubtract(&temp_r31->unk174, &sp2C, &sp20);
        var_f31 = PSVECMag(&sp20);
        if (var_f31 != 0.0f) {
            PSVECNormalize(&sp20, &sp20);
            PSVECScale(&sp20, &sp20, 0.9f * var_f31);
            PSVECAdd(&sp2C, &sp20, &temp_r31->unk174);
        }
        PSVECAdd(&temp_r31->unk30, &temp_r31->unk174, &sp38);
        fn_1_88E8(temp_r31->unk168, sp38.x, sp38.y, sp38.z);
    }
    temp_r31->unk164 = 1;
}

void fn_1_AE58(omObjData *arg0)
{
    arg0->func = NULL;
}

f32 lbl_1_data_36C[4][2] = { 30.0f, 24.0f, 24.0f, 18.0f, 12.0f, 6.0f, 6.0f, 0.0f };

f32 lbl_1_data_38C[4][2] = { 0.2f, 0.15f, 0.15f, 0.1f, 0.1f, 0.05f, 0.05f, 0.0f };

void fn_1_AE64(omObjData *arg0)
{
    M424DllClawStruct2 sp20[8];
    M424DllClawStruct2 sp10;
    s32 spC;
    f32 var_f31;
    f32 var_f29;
    f32 temp_f28;
    f32 temp_f27;
    f32 temp_f26;
    f32 var_f25;
    f32 var_f24;
    s32 temp_r24;
    s32 temp_r23;
    M424DllClawStruct *temp_r31;
    Vec *var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    M424DllBallStruct2 *var_r26;
    s32 var_r25;

    spC = 0;
    temp_r31 = arg0->data;
    var_r26 = &lbl_1_bss_60[0];
    if (var_r26) {
        temp_r31->unkC = 0;
        temp_r31->unkA = 0;
        switch (temp_r31->unk10) {
            case 1:
                if (temp_r31->unk188 == 0) {
                    temp_r31->unk188 = 1;
                    temp_r31->unk18C = -1;
                    temp_r31->unk190 = 0;
                    temp_r31->unk194 = 0;
                    temp_r31->unk198 = 0;
                    temp_r31->unk19C = 0;
                    temp_r31->unk1A0 = 0;
                    temp_r31->unk1A4 = 0;
                    temp_r31->unk1A8 = 0.0f;
                }
                if (temp_r31->unk18C == -1) {
                    for (var_r29 = 0, var_r28 = 0; var_r29 < lbl_1_bss_58; var_r29++, var_r26++) {
                        if ((fn_1_897C(var_r29) != 0) && (fn_1_8950(var_r29) <= 2)) {
                            var_r30 = fn_1_89D4(var_r29);
                            var_f31 = atan2d(var_r30->x, var_r30->z);
                            if (var_f31 > 180.0f) {
                                var_f31 -= 360.0f;
                            }
                            if (var_r28 < 8) {
                                if (var_f31 >= -90.0f) {
                                    if (var_f31 <= 45.0f) {
                                        sp20[var_r28].unk0 = var_r29;
                                        sp20[var_r28].unkC = var_f31;
                                        sp20[var_r28].unk4 = var_r30->x;
                                        sp20[var_r28].unk8 = var_r30->z;
                                        var_r28++;
                                    }
                                }
                            }
                        }
                    }
                    if (var_r28 != 0) {
                        for (var_r29 = 0; var_r29 < (var_r28 - 1); var_r29++) {
                            var_r27 = var_r29 + 1;
                            for (; var_r27 < var_r28; var_r27++) {
                                if (sp20[var_r29].unkC < sp20[var_r27].unkC) {
                                    sp10 = sp20[var_r29];
                                    sp20[var_r29] = sp20[var_r27];
                                    sp20[var_r27] = sp10;
                                }
                            }
                        }
                        temp_r31->unk18C = sp20[0].unk0;
                        temp_r31->unk1A8 = sp20[0].unkC;
                        temp_r31->unk19C = 0;
                        temp_r31->unk1A0 = 0;
                        temp_r31->unk1A4 = 0;
                        temp_r31->unk1AC = 0;
                    }
                }
                if (temp_r31->unk18C != -1) {
                    var_r30 = fn_1_89D4(temp_r31->unk18C);
                    var_f31 = atan2d(var_r30->x, var_r30->z);
                    if (var_f31 > 180.0f) {
                        var_f31 -= 360.0f;
                    }
                    if (var_f31 >= 30.0f) {
                        if (temp_r31->unk19C != 0) {
                            temp_f27 = lbl_1_data_36C[temp_r31->unk8][0];
                            temp_f26 = lbl_1_data_36C[temp_r31->unk8][1];
                            temp_r24 = ((temp_f26 - temp_f27) * (temp_f27 * (0.007874016f * (frand() & 0x7F))));
                            temp_f27 = lbl_1_data_38C[temp_r31->unk8][0];
                            temp_f26 = lbl_1_data_38C[temp_r31->unk8][1];
                            temp_r23 = ((temp_f26 - temp_f27) * (temp_f27 * (0.007874016f * (frand() & 0x7F))));
                            temp_r31->unk190 = ((3.0f * temp_r31->unk1A4) + temp_r24);
                            temp_f28 = (var_r30->x * var_r30->x) + (var_r30->z * var_r30->z);
                            var_f29 = sqrtf(temp_f28);
                            var_f29 = (var_f29 - 350.0f) / 250.0f + temp_r23;
                            if (var_f29 < 0.0f) {
                                var_f29 = 0.0f;
                            }
                            else if (var_f29 > 1.0f) {
                                var_f29 = 1.0f;
                            }
                            temp_r31->unk194 = (60.0f * (1.0f - var_f29));
                            var_f25 = (1.5f + (-1.5f * var_f29));
                            temp_r31->unk190 -= (s32)(60.0f * var_f25);
                            var_f25 = (1.0f + (-1.1f * var_f29));
                            temp_r31->unk198 = (60.0f * var_f25);
                            temp_r31->unk19C = 0;
                            temp_r31->unk1A0 = 0;
                            temp_r31->unk1AC = 0;
                            temp_r31->unk1AC = (temp_r31->unk1AC + (60.0f * (1.0f - var_f29)));
                        }
                        if (++temp_r31->unk1AC >= (temp_r31->unk190 - temp_r31->unk198)) {
                            temp_r31->unkA |= 0x100;
                            temp_r31->unkC |= 0x100;
                            temp_r31->unk1AC = 0;
                            return;
                        }
                    }
                    else {
                        if (var_f31 >= (15.0f + temp_r31->unk1A8)) {
                            temp_r31->unk1A0++;
                            temp_r31->unk1A8 = var_f31;
                            temp_r31->unk1A4 = (temp_r31->unk19C / temp_r31->unk1A0);
                            return;
                        }
                        temp_r31->unk19C++;
                        return;
                    }
                }
                break;
            case 2:
                if (temp_r31->unk18C != -1) {
                    var_r25 = 1;
                    if (++temp_r31->unk1AC >= temp_r31->unk194) {
                        var_r25 = 0;
                    }
                }
                else {
                    var_r25 = 0;
                }
                if (var_r25 != 0) {
                    temp_r31->unkC |= 0x100;
                }
                temp_r31->unk188 = 0;
                break;
        }
    }
}

u16 fn_1_B79C(f32 arg0, f32 arg1, f32 arg2)
{
    f32 var_f31;
    f32 var_f3;
    u16 var_r31;

    var_r31 = 0;
    for (var_f31 = arg0; arg2 > 0.0f || var_f31 > arg1; var_r31++) {
        var_f31 += arg2;
        arg2 -= 0.65333337f;
    }
    return var_r31;
}

s32 fn_1_B804(void)
{
    M424DllClawStruct *temp_r31;

    if (!lbl_1_bss_6D8) {
        return 0;
    }
    if (!lbl_1_bss_6D8->data) {
        return 0;
    }
    temp_r31 = lbl_1_bss_6D8->data;
    if ((temp_r31->unk10 >= 1) && (temp_r31->unk10 < 6)) {
        return 1;
    }
    return 0;
}

s32 fn_1_B888(void)
{
    if (lbl_1_bss_6CC >= 3) {
        return 1;
    }
    else {
        return 0;
    }
}

s32 fn_1_B8AC(void)
{
    M424DllClawStruct *temp_r31;

    if (!lbl_1_bss_6D8) {
        return 0;
    }
    if (!lbl_1_bss_6D8->data) {
        return 0;
    }

    temp_r31 = lbl_1_bss_6D8->data;
    if (temp_r31->unk10 >= 10) {
        return 1;
    }
    return 0;
}

s32 fn_1_B924(void)
{
    M424DllClawStruct *temp_r31;

    if (!lbl_1_bss_6D8) {
        return 0;
    }
    if (!lbl_1_bss_6D8->data) {
        return 0;
    }

    temp_r31 = lbl_1_bss_6D8->data;
    if (temp_r31->unk10 >= 13) {
        return 1;
    }
    return 0;
}

void fn_1_B99C(Vec *arg0, Vec *arg1, f32 arg8, Vec *arg2)
{
    fn_1_B9E0(arg0, arg1, arg8, arg2, 0x10);
}

s32 fn_1_B9E0(Vec *arg0, Vec *arg1, f32 arg8, Vec *arg2, s32 arg3)
{
    Vec sp60;
    Vec sp54;
    Vec sp48;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    f32 temp_f30;
    f32 var_f29;
    f32 temp_f28;
    f32 temp_f27;
    f32 temp_f26;
    f32 var_f25;
    f32 var_f24;
    f32 var_f23;
    M424DllClawStruct *temp_r31;
    s32 var_r29;
    s32 var_r28;
    s32 var_r26;
    omObjData *var_r24;
    s32 var_r23;

    var_r23 = 1;
    var_r28 = 0;
    var_r24 = lbl_1_bss_6D8;
    temp_r31 = var_r24->data;
    PSVECAdd(arg0, arg1, &sp24);
    spC = *arg1;
    *arg2 = *arg0;
    temp_f30 = 5.0f + arg8;
    if (temp_r31->unk164 == 0) {
        return 0;
    }
    switch (temp_r31->unk10) {
        case 3:
            for (var_r29 = 0; var_r29 < 0xC; var_r29++) {
                if (var_r28 != 0) {
                    sp24 = *arg2;
                    PSVECSubtract(&sp24, arg0, &spC);
                }
                PSVECSubtract(&sp24, &temp_r31->unk3C[var_r29], &sp18);
                var_f29 = PSVECMag(&sp18);
                if (var_f29 < temp_f30) {
                    if (0.0f == var_f29) {
                        var_f29 = temp_f30;
                        sp18.x = 0.0f;
                        sp18.y = 0.0f;
                        sp18.z = 1.0f;
                    }
                    var_f23 = sqrtf((sp18.x * sp18.x) + (sp18.z * sp18.z));
                    if ((temp_r31->unk3C[var_r29].y > sp24.y) && (var_f23 < 17.599999999999998)) {
                        temp_r31->unk15C = 1;
                    }
                    else {
                        PSVECNormalize(&sp18, &sp18);
                        PSVECScale(&sp18, &sp18, temp_f30);
                        PSVECAdd(&temp_r31->unk3C[var_r29], &sp18, arg2);
                    }
                    var_r28 = 1;
                }
            }
            break;
        default:
            for (var_r29 = 0; var_r29 < 0xC; var_r29++) {
                if (var_r28 != 0) {
                    sp24 = *arg2;
                    PSVECSubtract(&sp24, arg0, &spC);
                }
                var_r26 = 0;
                sp60 = temp_r31->unk3C[var_r29];
                PSVECAdd(&temp_r31->unkCC[var_r29], &spC, &sp54);
                PSVECSubtract(&sp60, &sp54, &sp18);
                PSVECSubtract(&sp24, &sp54, &sp48);
                temp_f26 = (sp18.z * sp18.z) + ((sp18.x * sp18.x) + (sp18.y * sp18.y));
                if (temp_f26 != 0.0f) {
                    var_f24 = (sp18.x * sp48.x) + (sp18.y * sp48.y) + (sp18.z * sp48.z);
                    temp_f27 = var_f24 / temp_f26;
                    if (temp_f27 >= 0.0f) {
                        if (temp_f27 <= 1.0f) {
                            PSVECScale(&sp18, &sp18, temp_f27);
                            PSVECAdd(&sp54, &sp18, &sp3C);
                            PSVECSubtract(&sp24, &sp3C, &sp30);
                            var_f29 = PSVECMag(&sp30);
                            if (var_f29 == 0.0f) {
                                if (PSVECMag(&sp18) <= 0.0f) {
                                    sp18.x = sp18.y = 0.0f;
                                    sp18.z = 1.0f;
                                }
                                PSVECNormalize(&sp18, &sp30);
                                PSVECScale(&sp30, &sp30, temp_f30);
                                PSVECAdd(&sp60, &sp30, arg2);
                                var_r28 = 1;
                                var_r26 = 1;
                            }
                            else if (var_f29 < temp_f30) {
                                if (PSVECMag(&sp30) <= 0.0f) {

                                    sp30.x = sp30.y = 0.0f;
                                    sp30.z = 1.0f;
                                }
                                PSVECNormalize(&sp30, &sp30);
                                PSVECScale(&sp30, &sp30, temp_f30);
                                PSVECAdd(&sp3C, &sp30, arg2);
                                var_r28 = 1;
                                var_r26 = 1;
                            }
                        }
                    }
                }
                if (var_r26 == 0) {
                    PSVECSubtract(&sp24, &sp60, &sp18);
                    var_f29 = PSVECMag(&sp18);
                    if (var_f29 < temp_f30) {
                        if (var_f29 <= 0.0f) {
                            sp18.x = sp18.y = 0.0f;
                            sp18.z = 1.0f;
                        }
                        PSVECNormalize(&sp18, &sp18);
                        PSVECScale(&sp18, &sp18, temp_f30);
                        PSVECAdd(&temp_r31->unk3C[var_r29], &sp18, arg2);
                        var_r28 = 1;
                        var_r26 = 1;
                    }
                }
                if (var_r26 == 0) {
                    PSVECSubtract(&sp24, &sp54, &sp18);
                    var_f29 = PSVECMag(&sp18);
                    if (var_f29 < temp_f30) {
                        if (var_f29 <= 0.0f) {
                            sp18.x = sp18.y = 0.0f;
                            sp18.z = 1.0f;
                        }
                        PSVECNormalize(&sp18, &sp18);
                        PSVECScale(&sp18, &sp18, temp_f30);
                        PSVECAdd(&temp_r31->unk3C[var_r29], &sp18, arg2);
                        var_r28 = 1;
                        var_r26 = 1;
                    }
                }
                if ((lbl_1_data_2DC[var_r29] != 0) && (var_r26 == 0)) {
                    var_r23 = 0;
                }
            }
            if ((temp_r31->unk10 == 4) && (var_r23 != 0)) {
                arg2->x = temp_r31->unk30.x;
                arg2->y = arg0->y;
                arg2->z = temp_r31->unk30.z;
                arg3 = 0;
                temp_r31->unk160 = 1;
            }
            break;
        case 0:
        case 1:
        case 2:
        case 9:
            break;
    }
    if (var_r28 != 0) {
        if (--arg3 > 0) {
            sp24 = *arg2;
            PSVECSubtract(&sp24, arg0, &spC);
            if (fn_1_B9E0(arg0, &spC, arg8, &sp24, arg3) != 0) {
                *arg2 = sp24;
            }
        }
    }

    (void)temp_f30; // @todo fix
    (void)temp_f30;
    return var_r28;
}

s32 fn_1_C210(Vec *arg0)
{
    Vec sp1C;
    Vec sp10;
    f32 spC;
    M424DllClawStruct *temp_r31;
    omObjData *var_r30;
    s32 var_r29;

    var_r29 = 0;
    var_r30 = lbl_1_bss_6D8;
    temp_r31 = var_r30->data;
    if (temp_r31->unk164 == 0) {
        return 0;
    }
    switch (temp_r31->unk10) {
        case 5:
            sp1C.x = temp_r31->unk30.x;
            sp1C.y = -120.00001f + temp_r31->unk30.y;
            sp1C.z = temp_r31->unk30.z;
            PSVECSubtract(arg0, &sp1C, &sp10);
            if ((spC = PSVECMag(&sp10)) < 50.0f) {
                var_r29 = 1;
            }
    }
    return var_r29;
}

void fn_1_C2E0(s32 arg0)
{
    Vec sp4C;
    Vec sp40;
    Vec sp34;
    Vec sp28;
    Vec *spC;
    M424DllBallStruct2 *temp_r27;
    Vec *temp_r28;
    M424DllClawStruct *temp_r31;
    s32 var_r30;
    s32 var_r26;
    omObjData *var_r25;

    if ((u8)omPauseChk() != 0U)
        return;

    var_r25 = lbl_1_bss_6D8;
    if (lbl_1_bss_6D8) {
        temp_r31 = var_r25->data;
        if (temp_r31 && (temp_r31->unk164 != 0)) {
            temp_r27 = &lbl_1_bss_60[0];
            if (temp_r27) {
                var_r26 = 0x10;

                for (var_r30 = 0; var_r30 < lbl_1_bss_58; var_r30++) {
                    temp_r27 = &lbl_1_bss_60[var_r30];
                    if ((fn_1_8950(var_r30) == 3) || (fn_1_8950(var_r30) == 4))
                        continue;
                    temp_r28 = fn_1_89D4(var_r30);
                    spC = fn_1_8A00(var_r30);
                    sp28 = *temp_r28;
                    sp4C = temp_r27->unk60;
                    PSVECSubtract(temp_r28, &sp4C, &sp40);
                    if (fn_1_B9E0(&sp4C, &sp40, 100.0f, &sp34, 0x10) != 0) {
                        *temp_r28 = sp34;
                        sp4C = sp34;
                        if ((temp_r27->unk4 < 3) && (fn_1_907C(&sp4C, &sp34) != 0)) {
                            *temp_r28 = sp34;
                            sp4C = sp34;
                        }
                        fn_1_C604(var_r30, 0x20);
                        if ((sp28.y != sp4C.y) && (var_r30 != temp_r31->unk168) && (var_r30 != temp_r31->unk16C)) {
                            temp_r28->y = sp28.y;
                            sp4C.y = sp28.y;
                            if (var_r26 > 0) {
                                var_r30--;
                                var_r26--;
                                continue;
                            }
                        }
                    }
                    if (temp_r31->unk168 == -1) {
                        if (fn_1_C210(&sp4C) != 0) {
                            temp_r31->unk168 = var_r30;
                            temp_r31->unk170 = fn_1_897C(var_r30);
                            PSVECSubtract(&sp4C, &temp_r31->unk30, &temp_r31->unk174);
                            fn_1_88E8(temp_r31->unk168, sp4C.x, sp4C.y, sp4C.z);
                        }
                    }
                    var_r26 = 0x10;
                }
            }
        }
    }
}

void fn_1_C604(s32 arg0, s32 arg1)
{
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    M424DllBallStruct2 *sp8;
    Vec *var_r31;
    f32 temp_f31;
    f32 var_f30;
    s32 var_r30;
    M424DllBallStruct2 *var_r28;
    Vec *var_r27;

    sp8 = &lbl_1_bss_60[var_r30];
    var_r27 = fn_1_89D4(arg0);
    sp30 = *var_r27;
    for (var_r30 = 0; var_r30 < lbl_1_bss_58; var_r30++) {
        if ((var_r30 != arg0) && (fn_1_8950(var_r30) < 3)) {
            var_r28 = &lbl_1_bss_60[var_r30];
            var_r31 = fn_1_89D4(var_r30);
            sp24 = *var_r31;
            PSVECSubtract(&sp24, &sp30, &sp18);
            var_f30 = PSVECMag(&sp18);
            if (var_f30 < 200.0f) {
                if (var_f30 > 0.0f) {
                    temp_f31 = 1.0f / var_f30;
                    sp18.x *= temp_f31;
                    sp18.y *= temp_f31;
                    sp18.z *= temp_f31;
                }
                else {
                    sp18.x = 0.0f;
                    sp18.y = 0.0f;
                    sp18.z = 1.0f;
                }
                temp_f31 = 1.0f + (200.0f - var_f30);
                sp24.x += (sp18.x * temp_f31);
                sp24.z += (sp18.z * temp_f31);
                var_r31->x = sp24.x;
                var_r31->z = sp24.z;
                if ((var_r28->unk4 < 3) && (fn_1_907C(&sp24, &spC) != 0)) {
                    var_r31->x = sp24.x = spC.x;
                    var_r31->z = sp24.z = spC.z;
                }
                if (arg1 > 0) {
                    arg1--;
                    fn_1_C604(var_r30, arg1);
                }
            }
        }
    }
}

void fn_1_C854(void)
{
    fn_1_C2E0(0);
}

s32 fn_1_C878(s16 arg0, const char *arg1, Mtx arg2, s32 arg3)
{
    Mtx sp44;
    Mtx sp14;
    HsfData *temp_r30;
    ModelData *temp_r31;

    temp_r31 = &Hu3DData[arg0];
    temp_r30 = temp_r31->hsfData;
    lbl_1_bss_6C8 = 0;
    if (temp_r31->unk_08 != -1) {
        lbl_1_bss_6C4 = 1;
    }
    else {
        lbl_1_bss_6C4 = 0;
    }
    mtxRot(sp14, temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
    PSMTXScale(sp44, temp_r31->scale.x, temp_r31->scale.y, temp_r31->scale.z);
    PSMTXConcat(sp14, sp44, sp44);
    mtxTransCat(sp44, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
    if (arg3 != 0) {
        PSMTXConcat(arg2, sp44, sp44);
    }
    fn_1_C99C(temp_r30->root, sp44, arg1, arg2);
    return lbl_1_bss_6C8;
}

void fn_1_C99C(HsfObject *arg0, Mtx arg1, const char *arg2, Mtx arg3)
{
    Mtx spF8;
    Mtx spC8;
    Mtx sp98;
    Mtx sp68;
    Mtx sp38;
    Mtx sp8;
    HsfTransform *var_r31;
    HsfTransform *var_r30;
    HsfTransform *var_r29;
    HsfObject *temp_r28;
    HsfObject *temp_r27;
    u32 var_r25;
    u32 var_r24;
    u32 var_r23;

    if (lbl_1_bss_6C8 == 0) {
        if (lbl_1_bss_6C4 != 0) {
            var_r31 = &arg0->data.curr;
        }
        else {
            var_r31 = &arg0->data.base;
        }
        if ((var_r31->scale.x <= 0.0f) && (var_r31->scale.y <= 0.0f) && (var_r31->scale.z <= 0.0f)) {
            PSMTXCopy(arg1, spF8);
            OSReport("OBJ MTX CHECK ERROR %s \n", arg0->name);
        }
        else {
            mtxRot(spC8, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
            PSMTXScale(spF8, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
            PSMTXConcat(spC8, spF8, spF8);
            mtxTransCat(spF8, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
            PSMTXConcat(arg1, spF8, spF8);
        }
        if (lbl_1_bss_6C0 != 0) {
            OSReport("%s \n", arg0->name);
        }
        if (strcmp(arg2, arg0->name) == 0) {
            PSMTXCopy(spF8, arg3);
            lbl_1_bss_6C8 = 1;
        }
        for (var_r25 = 0; var_r25 < arg0->data.childrenCount; var_r25++) {
            temp_r28 = arg0->data.children[var_r25];
            if (lbl_1_bss_6C8 == 0) {
                if (lbl_1_bss_6C4 != 0) {
                    var_r30 = &temp_r28->data.curr;
                }
                else {
                    var_r30 = &temp_r28->data.base;
                }
                if ((var_r30->scale.x <= 0.0f) && (var_r30->scale.y <= 0.0f) && (var_r30->scale.z <= 0.0f)) {
                    PSMTXCopy(spF8, sp68);
                    OSReport("OBJ MTX CHECK ERROR %s \n", temp_r28->name);
                }
                else {
                    mtxRot(sp98, var_r30->rot.x, var_r30->rot.y, var_r30->rot.z);
                    PSMTXScale(sp68, var_r30->scale.x, var_r30->scale.y, var_r30->scale.z);
                    PSMTXConcat(sp98, sp68, sp68);
                    mtxTransCat(sp68, var_r30->pos.x, var_r30->pos.y, var_r30->pos.z);
                    PSMTXConcat(spF8, sp68, sp68);
                }
                if (lbl_1_bss_6C0 != 0) {
                    OSReport("%s \n", temp_r28->name);
                }
                if (strcmp(arg2, temp_r28->name) == 0) {
                    PSMTXCopy(sp68, arg3);
                    lbl_1_bss_6C8 = 1;
                }
                for (var_r24 = 0; var_r24 < temp_r28->data.childrenCount; var_r24++) {
                    temp_r27 = temp_r28->data.children[var_r24];
                    if (lbl_1_bss_6C8 == 0) {
                        if (lbl_1_bss_6C4 != 0) {
                            var_r29 = &temp_r27->data.curr;
                        }
                        else {
                            var_r29 = &temp_r27->data.base;
                        }
                        if ((var_r29->scale.x <= 0.0f) && (var_r29->scale.y <= 0.0f) && (var_r29->scale.z <= 0.0f)) {
                            PSMTXCopy(sp68, sp8);
                            OSReport("OBJ MTX CHECK ERROR %s \n", temp_r27->name
                        }
                        else {
                            mtxRot(sp38, var_r29->rot.x, var_r29->rot.y, var_r29->rot.z);
                            PSMTXScale(sp8, var_r29->scale.x, var_r29->scale.y, var_r29->scale.z);
                            PSMTXConcat(sp38, sp8, sp8);
                            mtxTransCat(sp8, var_r29->pos.x, var_r29->pos.y, var_r29->pos.z);
                            PSMTXConcat(sp68, sp8, sp8);
                        }
                        if (lbl_1_bss_6C0 != 0) {
                            OSReport("%s \n", temp_r27->name);
                        }
                        if (strcmp(arg2, temp_r27->name) == 0) {
                            PSMTXCopy(sp8, arg3);
                            lbl_1_bss_6C8 = 1;
                        }
                        for (var_r23 = 0; var_r23 < temp_r27->data.childrenCount; var_r23++) {
                            fn_1_C99C(temp_r27->data.children[var_r23], sp8, arg2, arg3);
                        }
                    }
                }
            }
        }
    }
}

void fn_1_CE74(s32 arg0)
{
    ModelData *temp_r31;

    temp_r31 = &Hu3DData[arg0];
    if (temp_r31->unk_08 != -1) {
        Hu3DMotionExec(arg0, temp_r31->unk_08, temp_r31->unk_64, 0);
    }
    if (temp_r31->unk_0C != -1) {
        Hu3DSubMotionExec(arg0);
    }
    if (temp_r31->hsfData->cenvCnt != 0) {
        EnvelopeProc(temp_r31->hsfData);
    }
}

void fn_1_CF00(Process *arg0)
{
    M424DllClawStruct3 *var_r31;
    s32 var_r30;

    omAddObjEx(arg0, 0x40, 0, 0, -1, fn_1_CF80);
    var_r31 = &lbl_1_bss_640[0];

    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        var_r31->unk0 = -1;
        var_r31->unk4 = -1;
    }
}

void fn_1_CF80(omObjData *arg0)
{
    M424DllClawStruct3 *var_r31;
    s32 var_r30;

    var_r31 = &lbl_1_bss_640[0];
    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if ((var_r31->unk0 >= 0) && (var_r31->unk4 > 0)) {
            if (--var_r31->unk4 <= 0) {
                HuAudFXPlay(var_r31->unk0);
                var_r31->unk0 = -1;
                var_r31->unk4 = -1;
            }
        }
    }
}

s32 fn_1_D010(s32 arg0, s32 arg1)
{
    M424DllClawStruct3 *var_r31;
    s32 var_r30;

    var_r31 = &lbl_1_bss_640[0];
    for (var_r30 = 0; var_r30 < 0x10; var_r30++, var_r31++) {
        if (var_r31->unk0 == -1)
            break;
    }
    if (var_r30 >= 0x10) {
        return -1;
    }
    var_r31->unk0 = arg0;
    var_r31->unk4 = arg1;
    return var_r30;
}
