#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "ext_math.h"

#ifndef __MWERKS__
s32 rand8(void);
#endif

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u32 unk04;
} StructBss104; // Size 4

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ float unk04[3];
} StructBss54; // Size 0x10

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ s32 unk40;
} StructBss3CData; // Size 0x44

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ char unk28[4];
    /* 0x2C */ s32 unk2C;
} StructDataF0; // Size 0x30

void fn_1_B480(omObjData *arg0);

StructBss104 lbl_1_bss_104[3][8];
StructBss54 lbl_1_bss_54[11];
omObjData *lbl_1_bss_50;
omObjData *lbl_1_bss_4C;
omObjData *lbl_1_bss_3C[4];
omObjData *lbl_1_bss_38;
s32 lbl_1_bss_34;
Process *lbl_1_bss_30;
s16 lbl_1_bss_2E;
s16 lbl_1_bss_2C;
s32 lbl_1_bss_28;
s32 lbl_1_bss_24;
s32 lbl_1_bss_20;
s32 lbl_1_bss_1C; // unused
s32 lbl_1_bss_18;
s32 lbl_1_bss_14;
s32 lbl_1_bss_10; // unused
s32 lbl_1_bss_C;
float lbl_1_bss_8;
float lbl_1_bss_4;
float lbl_1_bss_0;

const float lbl_1_rodata_10[12] = { 25.0f, 95.0f, 25.0f, 75.0f, 75.0f, 75.0f, 35.0f, 35.0f, 35.0f, 25.0f, 50.0f, 50.0f };

const float lbl_1_rodata_40[12] = { 75.0f, 0.0f, 75.0f, 0.0f, 0.0f, 0.0f, 20.0f, 20.0f, 20.0f, 50.0f, 0.0f, 0.0f };

const float lbl_1_rodata_70[12] = { 75.0f, 0.0f, 37.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 70.0f, 0.0f, 0.0f };

const float lbl_1_rodata_A0[12] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 75.0f, 50.0f, 0.0f };

const float lbl_1_rodata_D0[12] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

const float lbl_1_rodata_100[12] = { 30.0f, 30.0f, 30.0f, 30.0f, 30.0f, 30.0f, 40.0f, 40.0f, 40.0f, 0.0f, 0.0f, 0.0f };

const float lbl_1_rodata_130[12] = { 290.0f, 290.0f, 290.0f, 370.0f, 370.0f, 370.0f, 450.0f, 450.0f, 450.0f, 0.0f, 0.0f, 0.0f };

s32 lbl_1_data_0[] = { DATA_MAKE_NUM(DATADIR_MGCONST, 41), DATA_MAKE_NUM(DATADIR_MGCONST, 40), DATA_MAKE_NUM(DATADIR_MGCONST, 51),
    DATA_MAKE_NUM(DATADIR_MGCONST, 51), DATA_MAKE_NUM(DATADIR_MGCONST, 8), DATA_MAKE_NUM(DATADIR_M422, 51), DATA_MAKE_NUM(DATADIR_MGCONST, 0),
    DATA_MAKE_NUM(DATADIR_MGCONST, 37), DATA_MAKE_NUM(DATADIR_MGCONST, 36), DATA_MAKE_NUM(DATADIR_MGCONST, 51), DATA_MAKE_NUM(DATADIR_MGCONST, 51),
    DATA_MAKE_NUM(DATADIR_MGCONST, 8), DATA_MAKE_NUM(DATADIR_M422, 51), DATA_MAKE_NUM(DATADIR_MGCONST, 12), DATA_MAKE_NUM(DATADIR_MGCONST, 12),
    DATA_MAKE_NUM(DATADIR_MGCONST, 12) };

s32 lbl_1_data_40[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x005E0000, 0x00190000, 0x006C0000, 0x00890000, 0x00840000, 0x00100000,
    0x000C0000, 0x00800000 };

s32 lbl_1_data_A0[] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MARIOMOT, 2), DATA_MAKE_NUM(DATADIR_MARIOMOT, 3),
    DATA_MAKE_NUM(DATADIR_M422, 0), DATA_MAKE_NUM(DATADIR_M422, 8), DATA_MAKE_NUM(DATADIR_MARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MARIOMOT, 23),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 24) };

u32 lbl_1_data_C0[] = { 0, 0, 0, 1, 1, 0, 0, 0 };
u8 lbl_1_data_E0[] = { 0, 0, 0, 1, 0, 1, 1 };
u8 lbl_1_data_E7[] = { 8, 8, 8, 0, 12, 0, 8, 8, 0 };
StructDataF0 lbl_1_data_F0[12][10] = { 0 };

char *lbl_1_data_1828[]
    = { "m422al01-cube8", "m422al02-cyl143", "m422al03-cube11", "m422am01-cyl76", "m422am02-cube13", "m422am03-cube12", "m422as01-cube9",
          "m422test11-cube9", "m422test12-cube9", "m422m09m-m422m09m", "coin", "m422a04-sphere2", "m422m09m-m422m09m", "m422m09m-m422m09m",
          "m422m09m-m422m09m", "m422m09m-m422m09m", "m422m09m-m422m09m", "m422m09m-m422m09m", "m422m09m-m422m09m", "m422m09m-m422m09m" };

s32 lbl_1_data_1878[11] = { 0 };
s32 lbl_1_data_18A4[2] = { 0 };
s32 lbl_1_data_18AC = -1;
s32 lbl_1_data_18B0 = -1;

float lbl_1_data_18B4[][4]
    = { { 0.0f, 300.0f, 450.0f, 180.0f }, { -200.0f, 0.0f, 1050.0f, 180.0f }, { 0.0f, 0.0f, 1050.0f, 180.0f }, { 200.0f, 0.0f, 1050.0f, 180.0f } };

s32 lbl_1_data_18F4[] = { 0, 0 };

float lbl_1_data_18FC = 1.0f; // unused
s32 lbl_1_data_1900 = -1;

void fn_1_A0(void)
{
    Center.x += 10.0 * (((HuPadBtn[0] & 2) != 0) - ((HuPadBtn[0] & 1) != 0));
    Center.z -= 10.0 * (((HuPadBtn[0] & 8) != 0) - ((HuPadBtn[0] & 4) != 0));
    Center.y += ((HuPadTrigL[0] - HuPadTrigR[0]) / 128.0) * 30.0;
    CRot.y += HuPadSubStkX[0] / 16.0;
    CRot.x += HuPadSubStkY[0] / -16.0;
}

void fn_1_2FC(omObjData *arg0)
{
    Mtx sp254;
    s32 sp1CC;
    s32 sp1C8;
    s32 sp1A4;
    float sp1A0;
    float sp158;
    float sp154;
    float sp150;
    float sp14C;
    float sp148;
    s32 sp144;
    float sp140;
    float sp13C;
    float sp138;
    float sp134;
    float sp130;
    float sp12C;
    float sp128;
    s32 sp124;
    float sp120;
    float sp11C;
    float sp118;
    s32 var_r17;
    s32 sp114;
    float temp_f23;
    float temp_f22;
    float temp_f25;
    float temp_f24;
    float temp_f27;
    float temp_f26;
    float phi_f29;
    float phi_f28;
    StructDataF0 *temp_r28;
    StructDataF0 *temp_r29;
    StructBss3CData *temp_r31;
    s32 var_r19;
    s32 phi_r23;
    s32 phi_r26;
    s32 phi_r22;
    s32 phi_r21;
    s16 phi_r25;
    s32 phi_r24;
    s32 phi_r20;
    s32 var_r18;
    s32 i;

    temp_r31 = arg0->data;
    sp158 = 0.0f;
    sp154 = 0.0f;
    sp150 = 0.0f;
    phi_r25 = -1;
    if (temp_r31->unk20 == 0 || temp_r31->unk20 == 1) {
        arg0->trans.z += lbl_1_bss_0;
    }
    temp_r31->unk2C = temp_r31->unk34 = 0.0f;
    if (lbl_1_bss_34 != 1004 || !(lbl_1_bss_8 < 45.0f)) {
        if (lbl_1_bss_34 >= 1004 && temp_r31->unk20 != 0) {
            temp_f25 = lbl_1_data_18B4[temp_r31->unk00][0] - arg0->trans.x;
            temp_f24 = lbl_1_data_18B4[temp_r31->unk00][2] - arg0->trans.z;
            sp14C = 270.0 + atan2d(temp_f25, temp_f24) - CRot.y;
            sp148 = sqrtf(temp_f25 * temp_f25 + temp_f24 * temp_f24);
            sp148 = (sp148 > 100.0f) ? 72.0f : (sp148 < 12.0f) ? 0.0f : (72.0f * (sp148 / 100.0f));
            sp154 = sp148 * cosd(sp14C);
            sp150 = sp148 * sind(sp14C);
            if (sp148 == 0.0f) {
                temp_r31->unk20 = 0;
            }
        }
        else if (temp_r31->unk20 == 1) {
            if (temp_r31->unk0C != -1) {
                sp154 = HuPadStkX[temp_r31->unk0C];
                sp150 = HuPadStkY[temp_r31->unk0C];
            }
            else {
                float sp238[7] = { 0 };
                float sp21C[7] = { 0 };
                float sp1EC[] = { -400.0f, -550.0f, -700.0f, -800.0f };
                float sp1DC[] = { -800.0f, -900.0f, -1100.0f, -2100.0f };
                Vec sp1D0;

                sp154 = sp150 = 0.0f;
                for (i = 0; i < 7; i++) {
                    sp238[i] = (temp_r31->unk00 == 0 ? 600.0f : 1400.0f) + sp1EC[temp_r31->unk10];
                    sp21C[i] = (temp_r31->unk00 == 0 ? 600.0f : 1400.0f) + sp1EC[temp_r31->unk10];
                }
                for (i = 0; i < 12; i++) {
                    for (phi_r23 = 0; phi_r23 < (i < 10 ? 4 : 10); phi_r23++) {
                        temp_r28 = &lbl_1_data_F0[i][phi_r23];
                        sp144 = (i < 10) ? (i * 4 + 43 + phi_r23) : ((i - 10) * 10 + 83 + phi_r23);
                        if (temp_r28->unk04 != 0 && !(temp_r28->unk14 < 0.0f)) {
                            Hu3DModelObjPosGet(lbl_1_bss_38->model[sp144], lbl_1_data_1828[temp_r28->unk00], &sp1D0);
                            phi_r26 = (s32)(300.0f + sp1D0.x + 2000.0f) / 100 - 20;
                            phi_r26--;
                            for (phi_r22 = 0; phi_r22 < 3; phi_r26++, phi_r22++) {
                                if (phi_r26 >= 0 && phi_r26 < 7
                                    && arg0->trans.z + 50.0f >= sp1D0.z - lbl_1_rodata_10[temp_r28->unk00] - lbl_1_rodata_70[temp_r28->unk00]
                                    && sp1D0.x - lbl_1_rodata_10[temp_r28->unk00] - lbl_1_rodata_70[temp_r28->unk00] - 50.0f < (phi_r26 - 3) * 100
                                    && sp1D0.x + lbl_1_rodata_10[temp_r28->unk00] + lbl_1_rodata_70[temp_r28->unk00] + 50.0f > (phi_r26 - 3) * 100) {
                                    if (temp_r28->unk00 < 10) {
                                        if (sp238[phi_r26] < sp1D0.z + lbl_1_rodata_10[temp_r28->unk00] + lbl_1_rodata_70[temp_r28->unk00]) {
                                            sp238[phi_r26] = sp1D0.z + lbl_1_rodata_10[temp_r28->unk00] + lbl_1_rodata_70[temp_r28->unk00];
                                        }
                                    }
                                    else {
                                        if (sp21C[phi_r26] < sp1D0.z + lbl_1_rodata_10[temp_r28->unk00] + lbl_1_rodata_70[temp_r28->unk00]) {
                                            sp21C[phi_r26] = sp1D0.z + lbl_1_rodata_10[temp_r28->unk00] + lbl_1_rodata_70[temp_r28->unk00]
                                                + (temp_r28->unk00 < 11);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                phi_r26 = (s32)(300.0f + arg0->trans.x + 2000.0f) / 100 - 20;
                phi_r26 = (phi_r26 < 0) ? 0 : (phi_r26 >= 7) ? 6 : phi_r26;
                for (i = 0, phi_r22 = phi_r26; i < 7; i++) {
                    var_r19 = ((temp_r31->unk00 / 2) % 2 == 0) ? i : (6 - i);
                    if (sp21C[phi_r22] - 60.0 * fabs(phi_r22 - phi_r26) < sp21C[var_r19] - 60.0 * fabs(var_r19 - phi_r26)
                        && sp238[var_r19] < sp21C[var_r19]) {
                        phi_r22 = var_r19;
                    }
                }
                sp238[phi_r22] -= 1.0f;
                for (i = 0, phi_r23 = phi_r26; i < 7; i++) {
                    var_r17 = ((temp_r31->unk00 / 2) % 2 == 0) ? i : (6 - i);
                    if (sp238[phi_r23] > sp238[var_r17]) {
                        phi_r23 = var_r17;
                    }
                }
                sp140 = arg0->trans.z - (temp_r31->unk00 == 0 ? -100.0f : 700.0f);
                sp13C = (((sp238[phi_r22] > sp140 - 400.0f || sp140 > 550.0f) ? phi_r23
                                 : (sp140 > 500.0f) ? ((sp140 - 500.0f) / 50.0f) * phi_r23 + (1.0f - (sp140 - 500.0f) / 50.0f) * phi_r22
                                                    : phi_r22)
                            - 3.0f)
                        * 100.0f
                    - arg0->trans.x;
                {
                    float sp1C4[] = { -21.0f, 0.0f, 15.0f };
                    float sp1B8[] = { 60.0f, 65.0f, 53.0f };
                    float sp1AC[] = { 54.0f, 72.0f, 59.0f };
                    float sp1A0[] = { -15.0f, 7.0f, 22.0f };

                    var_r18 = (temp_r31->unk14 / 5) % 3;
                    var_r18 = (temp_r31->unk00 == 0) ? (arg0->trans.z < 200.0f ? 0 : 1) : 2;
                    sp13C /= 20.0f;
                    sp13C = (sp13C < -1.0f) ? sp13C : (sp13C > 1.0f) ? 1.0f : sp13C;
                    sp138 = (sp13C < 0.0f) ? -sp13C : sp13C;
                    sp134 = 1.0f - sp138;
                    sp154 = (sp13C < 0.0f) ? (36.0f * sp134 + sp138 * sp1C4[var_r18]) : (36.0f * sp134 + sp138 * sp1B8[var_r18]);
                    sp150 = (sp13C < 0.0f) ? (42.0f * sp134 + sp138 * sp1AC[var_r18]) : (42.0f * sp134 + sp138 * sp1A0[var_r18]);
                }
                temp_f23 = temp_r31->unk38 - sp154;
                temp_f22 = temp_r31->unk3C - sp150;
                if (sqrtf(temp_f23 * temp_f23 + temp_f22 * temp_f22) > 50.0f) {
                    temp_r31->unk40++;
                }
                else {
                    temp_r31->unk40 = 0;
                }
                if (temp_r31->unk40 >= 2) {
                    sp154 = temp_r31->unk38;
                    sp150 = temp_r31->unk3C;
                    temp_r31->unk40 = 0;
                }
                temp_r31->unk38 = sp154;
                temp_r31->unk3C = sp150;
            }
        }
    }
    if (temp_r31->unk20 == 2) {
        sp130 = arg0->trans.y;
        sp12C = arg0->trans.z;
        phi_r25 = 4;
        arg0->trans.z += 9.375;
        if (temp_r31->unk00 == 0 && lbl_1_data_1900 != -1 && arg0->trans.z > (arg0->trans.y > 0.0f ? 620.0f : 1400.0f) + 50.0f
            && sp12C <= (arg0->trans.y > 0.0f ? 620.0f : 1400.0f) + 50.0f) {
            HuAudFXStop(lbl_1_data_1900);
            lbl_1_data_1900 = -1;
        }
        temp_r31->unk30 -= 1.0f;
        arg0->trans.y += (arg0->trans.z > (arg0->trans.y > 0.0f ? 620.0f : 1400.0f) - 50.0f) ? temp_r31->unk30 : 0.0f;
        if (temp_r31->unk00 == 0 && lbl_1_data_1900 == -1 && arg0->trans.z > 670.0f && arg0->trans.z < 1450.0f && arg0->trans.y == 0.0f
            && sp130 > 0.0f) {
            lbl_1_data_1900 = HuAudFXPlay(0x612);
        }
        if (arg0->trans.z < 1400.0f && arg0->trans.y <= 0.0f) {
            arg0->trans.y = 0.0f;
            temp_r31->unk30 = 0.0f;
        }
        arg0->rot.y += (arg0->rot.y < 0.0f) ? 360 : (arg0->rot.y > 360.0f) ? -360 : 0;
        arg0->rot.y = (arg0->rot.y > 140.0f && arg0->rot.y < 220.0f) ? 180.0f
            : (arg0->rot.y < 180.0f)                                 ? (40.0f + arg0->rot.y)
            : (arg0->rot.y > 180.0f)                                 ? (arg0->rot.y - 40.0f)
                                                                     : arg0->trans.y;
        ;
        if (lbl_1_bss_C % 4 < 3) {
            Hu3DModelAttrReset(arg0->model[0], 1);
        }
        else {
            Hu3DModelAttrSet(arg0->model[0], 1);
        }
        if (arg0->trans.y < -500.0f) {
            temp_r31->unk20 = 3;
            Hu3DModelAttrSet(arg0->model[0], 1);
        }
    }
    else if (temp_r31->unk20 != 3 && temp_r31->unk20 != 4) {
        if (temp_r31->unk20 == 5) {
            if (temp_r31->unk24 == 0) {
                phi_r25 = 3;
                Hu3DMotionSpeedSet(arg0->model[0], 1.0f);
                Hu3DModelAttrReset(arg0->model[0], 1);
            }
            temp_r31->unk24++;
            if (temp_r31->unk24 == 30) {
                temp_r31->unk1C = -1;
                temp_r31->unk18 = phi_r25 = 0;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
            if (temp_r31->unk24 >= 31 && temp_r31->unk24 <= 38) {
                arg0->trans.x -= 150.0 * -sind(arg0->rot.y) / 7.0;
                arg0->trans.z -= 150.0 * -cosd(arg0->rot.y) / 7.0;
            }
            else {
                arg0->trans.x = lbl_1_data_F0[9][temp_r31->unk00].unk0C;
                arg0->trans.y = (temp_r31->unk00 == 0) ? 300 : 0;
                arg0->trans.z = lbl_1_data_F0[9][temp_r31->unk00].unk14;
            }
            if (temp_r31->unk24 == 34 && temp_r31->unk00 == 0) {
                Hu3DMotionTimeSet(lbl_1_bss_38->model[temp_r31->unk00 + 79], 15.0f + Hu3DMotionTimeGet(lbl_1_bss_38->model[temp_r31->unk00 + 79]));
            }
            if (temp_r31->unk24 == 38) {
                temp_r31->unk20 = 1;
            }
        }
        else {
            float temp_f31 = 0.25 * sp154;
            float temp_f30 = 0.25 * -sp150;
            Vec sp194 = { 0.0f, 0.0f, 0.0f };

            sp194.x = temp_f31;
            sp194.z = temp_f30;
            MTXRotRad(sp254, 'y', MTXDegToRad(CRot.y));
            MTXMultVec(sp254, &sp194, &sp194);
            temp_f31 = sp194.x;
            temp_f30 = sp194.z;
            sp158 = sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30);
            if (sp158 >= 0.5f) {
                if (sp158 < 10.0f) {
                    temp_r31->unk2C = temp_f31;
                    temp_r31->unk34 += temp_f30;
                }
                else {
                    temp_f31 /= sp158;
                    temp_f30 /= sp158;
                    sp158 = 10.0f;
                    temp_r31->unk2C = temp_f31 * sp158;
                    temp_r31->unk34 = temp_f30 * sp158;
                }
                temp_r31->unk28 = sp158;
                arg0->rot.y = atan2d(temp_r31->unk2C, temp_r31->unk34);
                if (temp_r31->unk20 == 1) {
                    if (temp_r31->unk28 >= 8.0f) {
                        phi_r25 = 2;
                    }
                    else {
                        phi_r25 = 1;
                    }
                }
            }
            else if (temp_r31->unk20 == 1) {
                phi_r25 = 0;
            }
            if (lbl_1_bss_34 == 1005 && (temp_r31->unk20 == 1 || temp_r31->unk20 == 0)) {
                temp_r31->unk1C = (lbl_1_data_18F4[temp_r31->unk00 == 0 ? 0 : 1] > 0) ? 6 : 7;
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
                temp_r31->unk20 = 0;
                if (lbl_1_bss_8 == 1.0f && lbl_1_data_18F4[temp_r31->unk00 == 0 ? 0 : 1] > 0) {
                    s32 sp1FC[] = { 0x122, 0x162, 0x1A2, 0x1E2, 0x222, 0x262, 0x2A2, 0x2E2 };

                    HuAudFXPlay(sp1FC[temp_r31->unk08]);
                }
            }
            if (lbl_1_bss_34 >= 1004 && temp_r31->unk20 == 0) {
                arg0->rot.y = 2.4f + 0.8f * arg0->rot.y;
                if (temp_r31->unk18 != 6 && temp_r31->unk18 != 7) {
                    phi_r25 = 0;
                }
            }
            arg0->trans.x += temp_r31->unk2C;
            arg0->trans.z += temp_r31->unk34;
            if (temp_r31->unk00 != 0) {
                for (phi_r21 = 1; phi_r21 < 4; phi_r21++) {
                    temp_f27 = lbl_1_bss_3C[phi_r21]->trans.x - arg0->trans.x;
                    phi_f29 = lbl_1_bss_3C[phi_r21]->trans.z - arg0->trans.z;
                    if (phi_r21 != temp_r31->unk00) {
                        if (temp_f27 == 0.0f && phi_f29 == 0.0f) {
                            phi_f29 = -1.0f;
                        }
                        sp128 = sqrtf(temp_f27 * temp_f27 + phi_f29 * phi_f29);
                        if (sp128 < 100.0f) {
                            temp_f27 *= (100.0f / sp128);
                            phi_f29 *= (100.0f / sp128);
                            arg0->trans.x = lbl_1_bss_3C[phi_r21]->trans.x - temp_f27;
                            arg0->trans.z = lbl_1_bss_3C[phi_r21]->trans.z - phi_f29;
                        }
                    }
                }
            }
            if (lbl_1_bss_34 > 1001) {
                for (phi_r24 = 0; phi_r24 < 12; phi_r24++) {
                    if (phi_r24 == 9 && lbl_1_bss_34 <= 1001) { }
                    for (phi_r20 = 0; phi_r20 < (phi_r24 < 10 ? 4 : 10); phi_r20++) {
                        temp_r29 = &lbl_1_data_F0[phi_r24][phi_r20];
                        sp124 = (phi_r24 < 10) ? (phi_r24 * 4 + 43 + phi_r20) : ((phi_r24 - 10) * 10 + 83 + phi_r20);
                        if (temp_r29->unk04 != 0 && temp_r29->unk2C <= 0) {
                            Vec sp188;

                            Hu3DModelObjPosGet(lbl_1_bss_38->model[sp124], lbl_1_data_1828[temp_r29->unk00], &sp188);
                            if (((temp_r29->unk04 == 3 || (temp_r29->unk04 == 4 && sp188.y >= 250.0f)) && temp_r31->unk00 == 0)
                                || (((temp_r29->unk04 == 4 && sp188.y < 250.0f) || temp_r29->unk04 == 5 || temp_r29->unk04 == 6)
                                    && temp_r31->unk00 != 0)) {
                                sp11C = sp188.x;
                                sp118 = sp188.z;
                                if (lbl_1_rodata_40[temp_r29->unk00] > 0.0f || lbl_1_rodata_70[temp_r29->unk00] > 0.0f) {
                                    sp11C = (arg0->trans.x < sp11C - lbl_1_rodata_40[temp_r29->unk00]) ? (sp11C - lbl_1_rodata_40[temp_r29->unk00])
                                        : (arg0->trans.x > sp11C + lbl_1_rodata_40[temp_r29->unk00])   ? (sp11C + lbl_1_rodata_40[temp_r29->unk00])
                                                                                                       : arg0->trans.x;
                                    sp118 = (arg0->trans.z < sp118 - lbl_1_rodata_70[temp_r29->unk00]) ? (sp118 - lbl_1_rodata_70[temp_r29->unk00])
                                        : (arg0->trans.z > sp118 + lbl_1_rodata_70[temp_r29->unk00])   ? (sp118 + lbl_1_rodata_70[temp_r29->unk00])
                                                                                                       : arg0->trans.z;
                                }
                                temp_f26 = sp11C - arg0->trans.x;
                                phi_f28 = sp118 - arg0->trans.z;
                                if (phi_r24 < 10 && temp_f26 == 0.0f && phi_f28 == 0.0f) {
                                    phi_f28 = -1.0f;
                                }
                                sp120 = sqrtf(temp_f26 * temp_f26 + phi_f28 * phi_f28);
                                if (sp120 < 50.0f + lbl_1_rodata_10[temp_r29->unk00]) {
                                    if (phi_r24 < 10) {
                                        temp_f26 *= (50.0f + lbl_1_rodata_10[temp_r29->unk00]) / sp120;
                                        phi_f28 *= (50.0f + lbl_1_rodata_10[temp_r29->unk00]) / sp120;
                                        arg0->trans.x = sp11C - temp_f26;
                                        arg0->trans.z = sp118 - phi_f28;
                                    }
                                    else {
                                        temp_r29->unk04 = 0;
                                        lbl_1_data_18F4[temp_r31->unk00 == 0 ? 0 : 1] += (phi_r24 == 10 ? 1 : 5);
                                        CharModelCoinEffectCreate(-1, &sp188);
                                        if (lbl_1_bss_54[phi_r24 == 10 ? 8 : 9].unk00 < 3) {
                                            lbl_1_bss_54[phi_r24 == 10 ? 8 : 9].unk04[lbl_1_bss_54[phi_r24 == 10 ? 8 : 9].unk00] = 0.0f;
                                            lbl_1_bss_54[phi_r24 == 10 ? 8 : 9].unk00++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (arg0->trans.z > (temp_r31->unk00 == 0 ? 620.0f : 1400.0f) - 50.0f) {
                temp_r31->unk20 = 2;
                temp_r31->unk30 = 0.0f;
                HuAudCharVoicePlay(temp_r31->unk08, 0x123);
            }
            if (temp_r31->unk20 != 2) {
                if (arg0->trans.x > (temp_r31->unk00 == 0 ? 400 : 400) - 50.0f) {
                    arg0->trans.x = (temp_r31->unk00 == 0 ? 400 : 400) - 50.0f;
                }
                if (arg0->trans.x < -(temp_r31->unk00 == 0 ? 400 : 400) + 50.0f) {
                    arg0->trans.x = -(temp_r31->unk00 == 0 ? 400 : 400) + 50.0f;
                }
                if (arg0->trans.z < (temp_r31->unk00 == 0 ? 0.0f : 600.0f) + 50.0f) {
                    arg0->trans.z = (temp_r31->unk00 == 0 ? 0.0f : 600.0f) + 50.0f;
                }
                if (arg0->trans.z > (temp_r31->unk00 == 0 ? 620.0f : 1400.0f) - 50.0f) {
                    arg0->trans.z = (temp_r31->unk00 == 0 ? 620.0f : 1400.0f) - 50.0f;
                }
            }
        }
    }
    if (lbl_1_bss_34 == 1001) {
        sp114 = temp_r31->unk00;
        if (lbl_1_bss_8 == 23.0f) {
            Hu3DMotionSet(lbl_1_bss_38->model[temp_r31->unk00 + 79], lbl_1_bss_38->motion[temp_r31->unk00 + 22]);
            Hu3DModelAttrReset(lbl_1_bss_38->model[temp_r31->unk00 + 79], HU3D_MOTATTR_PAUSE);
            if (lbl_1_bss_54[4].unk00 < 3) {
                lbl_1_bss_54[4].unk04[lbl_1_bss_54[4].unk00] = 0.0f;
                lbl_1_bss_54[4].unk00++;
            }
        }
        if (lbl_1_bss_8 == 43.0f) {
            Hu3DModelAttrSet(lbl_1_bss_38->model[temp_r31->unk00 + 79], HU3D_MOTATTR_PAUSE);
        }
        if (lbl_1_bss_8 == 80.0f) {
            Hu3DMotionTimeSet(lbl_1_bss_38->model[temp_r31->unk00 + 79], 20.0f);
            Hu3DModelAttrReset(lbl_1_bss_38->model[temp_r31->unk00 + 79], HU3D_MOTATTR_PAUSE);
        }
        if (lbl_1_bss_8 == 100.0f && lbl_1_bss_54[0].unk00 < 3) {
            lbl_1_bss_54[0].unk04[lbl_1_bss_54[0].unk00] = 0.0f;
            lbl_1_bss_54[0].unk00++;
        }
        if (lbl_1_bss_8 == 106.0f) {
            Hu3DModelAttrReset(lbl_1_bss_38->model[temp_r31->unk00 + 39], 1);
            Hu3DParticleCntSet(lbl_1_bss_38->model[temp_r31->unk00 + 39], 0);
            lbl_1_bss_18 = 1;
        }
        if (lbl_1_bss_8 == 60.0f) {
            Hu3DModelAttrReset(arg0->model[0], 1);
            Hu3DMotionSet(arg0->model[0], arg0->motion[3]);
            Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_PAUSE);
        }
        if (lbl_1_bss_8 == 61.0f) {
            Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_PAUSE);
        }
        if (lbl_1_bss_8 == 120.0f) {
            phi_r25 = 3;
            Hu3DModelAttrReset(arg0->model[0], 1);
        }
        if (lbl_1_bss_8 == 155.0f) {
            phi_r25 = 0;
        }
        arg0->trans.x = lbl_1_data_F0[9][sp114].unk0C;
        arg0->trans.z = (lbl_1_bss_8 > 163.0f) ? arg0->trans.z : (lbl_1_bss_8 > 155.0f) ? (arg0->trans.z - 18.75) : lbl_1_data_F0[9][sp114].unk14;
    }
    if (temp_r31->unk1C >= 0) {
        phi_r25 = temp_r31->unk1C;
    }
    if (phi_r25 >= 0 && phi_r25 != temp_r31->unk18) {
        Hu3DMotionShiftSet(arg0->model[0], arg0->motion[phi_r25], 0.0f, lbl_1_data_E7[phi_r25],
            (lbl_1_data_E0[phi_r25] != 0) ? HU3D_MOTATTR_NONE : HU3D_MOTATTR_LOOP);
        temp_r31->unk18 = phi_r25;
    }
}

s32 fn_1_34BC(float arg0, float arg1, float arg2, s32 arg3, s32 arg4)
{
    Vec sp1C;
    float var_f27;
    float var_f28;
    float var_f25;
    float var_f26;
    float temp_f30;
    float var_f31;
    float sp18;
    StructDataF0 *temp_r31;
    s32 var_r24;
    s32 i;
    s32 j;

    for (i = 0; i < 12; i++) {
        for (j = 0; j < (i < 10 ? 4 : 10); j++) {
            temp_r31 = &lbl_1_data_F0[i][j];
            var_r24 = (i < 10) ? (i * 4 + 43 + j) : ((i - 10) * 10 + 83 + j);
            if (temp_r31->unk04 != 0 && temp_r31->unk2C <= 0) {
                Hu3DModelObjPosGet(lbl_1_bss_38->model[var_r24], lbl_1_data_1828[temp_r31->unk00], &sp1C);
                if (temp_r31->unk04 == 3 || temp_r31->unk04 == 5) {
                    var_f27 = (temp_r31->unk08 == 0) ? temp_r31->unk0C : sp1C.x;
                    var_f28 = (temp_r31->unk08 == 0) ? temp_r31->unk14 : sp1C.z;
                    var_f25 = 50.0f + lbl_1_rodata_70[temp_r31->unk00];
                    var_f26 = 50.0f + lbl_1_rodata_70[temp_r31->unk00];
                    if (temp_r31->unk04 == 3) {
                        float sp28[][12] = { { -25.0f, -25.0f, -25.0f, -6.6875f, -6.6875f, -6.6875f, 62.765625f, 62.765625f, 62.765625f, 51.99469f,
                                                 76.875f, 45.0f },
                            { -27.647583f, -27.647583f, -27.647583f, -9.64325f, -9.64325f, -9.64325f, 60.49022f, 60.49022f, 60.49022f, 51.99469f,
                                76.875f, 45.0f } };

                        var_f28 += sp28[temp_r31->unk08 == 0 ? 0 : 1][temp_r31->unk00];
                        var_f25 += 50.0f;
                        var_f26 += 50.0f;
                    }
                    else if (temp_r31->unk04 == 5 && temp_r31->unk08 == 0) {
                        var_f28 += lbl_1_rodata_130[temp_r31->unk00];
                    }
                    else if (temp_r31->unk04 == 1) {
                        var_f27 = (temp_r31->unk0C < 0.0f ? -1 : 1) * 321;
                        var_f28 = 880.0f - lbl_1_bss_0 * (100 - temp_r31->unk08);
                    }
                    if (temp_r31->unk00 == 9) {
                        var_f26 += 300.0f;
                    }
                    if (lbl_1_rodata_40[temp_r31->unk00] > 0.0f || var_f25 > 0.0f || var_f26 > 0.0f) {
                        var_f27 = (arg0 < var_f27 - lbl_1_rodata_40[temp_r31->unk00]) ? (var_f27 - lbl_1_rodata_40[temp_r31->unk00])
                            : (arg0 > var_f27 + lbl_1_rodata_40[temp_r31->unk00])     ? (var_f27 + lbl_1_rodata_40[temp_r31->unk00])
                                                                                      : arg0;
                        var_f28 = (arg1 < var_f28 - var_f25) ? (var_f28 - var_f25) : (arg1 > var_f28 + var_f26) ? (var_f28 + var_f26) : arg1;
                    }
                    temp_f30 = var_f27 - arg0;
                    var_f31 = var_f28 - arg1;
                    if (i < 10 && temp_f30 == 0.0f && var_f31 == 0.0f) {
                        var_f31 = -1.0f;
                    }
                    sp18 = sqrtf(temp_f30 * temp_f30 + var_f31 * var_f31);
                    if (sp18 < arg2 + lbl_1_rodata_10[temp_r31->unk00]) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void fn_1_3B74(omObjData *arg0)
{
    StructBss3CData *sp354[4];
    Vec sp348;
    s32 var_r20;
    s32 var_r19;
    s32 var_r18;
    s32 var_r17;
    s32 sp230;
    s32 sp22C;
    s32 sp228;
    s32 sp224;
    s32 sp220;
    s32 sp21C;
    s32 sp218;
    float sp214;
    float sp210;
    float sp20C;
    s32 sp208;
    float var_f25;
    float var_f24;
    float temp_f21;
    float temp_f20;
    float temp_f23;
    float temp_f22;
    float temp_f26;
    float temp_f28;
    float temp_f27;
    float temp_f29;
    float temp_f30;
    float temp_f31;
    StructDataF0 *temp_r31;
    s32 var_r21;
    s32 var_r28;
    s32 var_r27;
    s32 var_r25;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        sp354[i] = lbl_1_bss_3C[i]->data;
    }
    lbl_1_bss_C++;
    lbl_1_bss_0 = (lbl_1_bss_34 <= 1002) ? 1.5
        : (lbl_1_bss_34 == 1003)         ? (7.5 * (lbl_1_bss_8 > 120.0f ? 1.0 : (0.2 + 0.8 * (lbl_1_bss_8 / 120.0))))
                                         : 0.0;
    lbl_1_bss_4 = (lbl_1_bss_34 < 1005 && sp354[0]->unk20 >= 2 && sp354[0]->unk20 <= 5 && !(lbl_1_bss_34 == 1003 && lbl_1_bss_8 <= 120.0f))
        ? 7.5
        : lbl_1_bss_0;
    Hu3DMotionSpeedSet(arg0->model[1], 1.5 * lbl_1_bss_4 / 7.5);
    Hu3DMotionSpeedSet(arg0->model[3], 1.5 * lbl_1_bss_0 / 7.5);
    if (lbl_1_data_18B0 != -1) {
        temp_f21 = 1.5 * lbl_1_bss_4 / 7.5;
        HuAudFXPitchSet(lbl_1_data_18B0, 8190.0f * temp_f21 - 8190.0f);
        HuAudFXVolSet(lbl_1_data_18B0, temp_f21 <= 0.001 ? 0 : 127);
    }
    if (lbl_1_bss_34 <= 1001) {
        temp_f31 = (lbl_1_bss_34 == 1000 || lbl_1_bss_8 < 60.0f) ? 0.0 : (lbl_1_bss_8 < 120.0f) ? (lbl_1_bss_8 - 60.0f) / 60.0 : 1.0;
        temp_f31 = 1.0f - temp_f31;
        temp_f31 *= temp_f31;
        temp_f31 = 1.0f - temp_f31;
        temp_f28 = 1.0f - temp_f31;
        Center.x = 690.0f * temp_f31;
        Center.y = 400.0f * temp_f28 + 1340.0f * temp_f31;
        Center.z = 500.0f * temp_f28 + 1380.0f * temp_f31;
        CRot.x = -10.0f * temp_f28 + -50.8125f * temp_f31;
        CRot.y = 40.0f * temp_f31;
        CZoom = 2126.6f * temp_f28 + 2126.6f * temp_f31;
        Center.x = 700.0f * temp_f31;
        Center.y = 400.0f * temp_f28 + 870.0f * temp_f31;
        Center.z = 500.0f * temp_f28 + 1320.0f * temp_f31;
        CRot.x = -10.0f * temp_f28 + -37.25f * temp_f31;
        CRot.y = 40.0f * temp_f31;
    }
    if (lbl_1_bss_34 == 1005 && lbl_1_bss_8 < 100.0f) {
        temp_f30 = (lbl_1_bss_8 < 90.0f) ? (lbl_1_bss_8 / 90.0) : 1.0;
        temp_f30 = 1.0f - temp_f30;
        temp_f30 *= temp_f30;
        temp_f30 = 1.0f - temp_f30;
        temp_f26 = 1.0f - temp_f30;
        Center.x = 120.0f * temp_f30 + 700.0f * temp_f26;
        Center.y = 292.5f * temp_f30 + 870.0f * temp_f26;
        Center.z = 1200.0f * temp_f30 + 1320.0f * temp_f26;
        CRot.x = -19.5f * temp_f30 + -37.25f * temp_f26;
        CRot.y = 13.5f * temp_f30 + 40.0 * temp_f26;
        CZoom = 2126.6f * temp_f30 + 2126.6f * temp_f26;
    }
    var_r20 = (sp354[0]->unk20 == 3 && (lbl_1_data_F0[9][0].unk04 == 0 || lbl_1_bss_34 != 1003));
    sp22C = (sp354[1]->unk20 == 3 && (lbl_1_data_F0[9][1].unk04 == 0 || lbl_1_bss_34 != 1003))
        + (sp354[2]->unk20 == 3 && (lbl_1_data_F0[9][2].unk04 == 0 || lbl_1_bss_34 != 1003))
        + (sp354[3]->unk20 == 3 && (lbl_1_data_F0[9][3].unk04 == 0 || lbl_1_bss_34 != 1003));
    var_r19 = (lbl_1_bss_34 == 1003 && lbl_1_bss_C % 60 == 0) ? (rand8() % 2 + 1 + var_r20) : var_r20;
    var_r18 = (lbl_1_bss_34 == 1003 && lbl_1_bss_C % 120 == 0) ? (rand8() % 2 + 1) : 0;
    var_r17 = sp22C + (lbl_1_bss_34 == 1003 && lbl_1_bss_C % 60 == 0 && lbl_1_bss_28 > 120);
    sp228 = (lbl_1_bss_34 == 1003 && lbl_1_bss_C % 60 == 0) ? (rand8() % 2 + 2) : 0;
    sp224 = 0;
    var_r19 = (lbl_1_bss_34 == 1003 && lbl_1_bss_C % 60 == 0) ? ((rand8() % 4 < 3) + 1 + var_r20) : var_r20;
    var_r18 = (lbl_1_bss_34 == 1003 && lbl_1_bss_C % 120 == 1) ? (rand8() % 2 + 1) : 0;
    var_r17 = sp22C + (lbl_1_bss_34 == 1003 && lbl_1_bss_C % 60 == 38 && lbl_1_bss_28 > 120);
    sp228 = (lbl_1_bss_34 == 1003 && lbl_1_bss_C % 60 == 0) ? (rand8() % 2 + 2) : 0;
    while (var_r19 > 0 || var_r18 > 0 || var_r17 > 0 || sp228 > 0) {
        var_r27 = (rand8() % 2 == 0) ? ((var_r17 != 0) ? 3
                          : (sp228 != 0)               ? 4
                          : (var_r19 != 0)             ? 1
                          : (var_r18 != 0)             ? 2
                                                       : 0)
                                     : ((var_r17 != 0)        ? 3
                                             : (var_r19 != 0) ? 1
                                             : (sp228 != 0)   ? 4
                                             : (var_r18 != 0) ? 2
                                                              : 0);
        sp224++;
        if (sp224 > 8) {
            var_r19 -= (var_r27 == 1);
            var_r18 -= (var_r27 == 2);
            var_r17 -= (var_r27 == 3);
            sp228 -= (var_r27 == 4);
            sp224 = 0;
        }
        else if (var_r27 == 1 || var_r27 == 2 || var_r27 == 3 || var_r27 == 4) {
            var_r28 = (var_r27 != 4) ? (rand8() % 9) : 10;
            if (var_r27 == 1 && var_r20 != 0) {
                var_r28 = 9;
                i = 0;
            }
            else if (var_r27 == 3 && sp22C != 0) {
                var_r28 = 9;
                i = (sp354[(lbl_1_bss_C % 3) + 1]->unk20 == 3 && (lbl_1_data_F0[9][lbl_1_bss_C % 3 + 1].unk04 == 0 || lbl_1_bss_34 != 1003))
                    ? (lbl_1_bss_C % 3 + 1)
                    : (sp354[(lbl_1_bss_C + 1) % 3 + 1]->unk20 == 3
                          && (lbl_1_data_F0[9][(lbl_1_bss_C + 1) % 3 + 1].unk04 == 0 || lbl_1_bss_34 != 1003))
                    ? ((lbl_1_bss_C + 1) % 3 + 1)
                    : (sp354[(lbl_1_bss_C + 2) % 3 + 1]->unk20 == 3
                          && (lbl_1_data_F0[9][(lbl_1_bss_C + 2) % 3 + 1].unk04 == 0 || lbl_1_bss_34 != 1003))
                    ? ((lbl_1_bss_C + 2) % 3 + 1)
                    : 0;
            }
            else {
                if (var_r28 == 10 && (lbl_1_bss_28 / 60) / 15 + 1 <= 2 - lbl_1_bss_14
                    && rand8() % (((lbl_1_bss_28 / 60 - (1 - lbl_1_bss_14) * 15) * 3) + 1) == 0) {
                    var_r28 = 11;
                }
                for (i = 0; i < (var_r27 != 4 ? 4 : 10); i++) {
                    if (lbl_1_data_F0[var_r28][i].unk04 == 0) {
                        break;
                    }
                }
                if (i >= (var_r27 != 4 ? 4 : 10)) {
                    continue;
                }
            }
            lbl_1_data_F0[var_r28][i].unk0C = (var_r27 != 3) ? (rand8() % 7 - 3) * 100 : ((rand8() % 2) * 2 - 1) * 1595;
            if (i == 0 && lbl_1_bss_34 >= 1004 && var_r28 == 9) {
                lbl_1_data_F0[var_r28][i].unk0C = 0.0f;
            }
            lbl_1_data_F0[var_r28][i].unk10 = (var_r27 == 1) ? 300 : (var_r27 == 2) ? 0 : (var_r27 == 3) ? 500 : (var_r27 == 4) ? 300 : 0;
            lbl_1_data_F0[var_r28][i].unk14 = (var_r27 == 1) ? -450 : (var_r27 == 2) ? -450 : (var_r27 == 3) ? 105 : (var_r27 == 4) ? -150 : 0;
            lbl_1_data_F0[var_r28][i].unk14 += (var_r27 == 1) ? -(var_r28 <= 8 ? 0 : 0)
                : (var_r27 == 2)                              ? -(var_r28 <= 8 ? (var_r28 / 3) * 80 : 0)
                : (var_r27 == 4)                              ? -50
                                                              : 0;
            lbl_1_data_F0[var_r28][i].unk14 += (var_r27 == 1) ? ((var_r28 <= 2) ? 315.0
                                                       : (var_r28 <= 5)         ? 296.6875
                                                       : (var_r28 <= 8)         ? 227.234375
                                                       : (var_r28 == 9)         ? 200
                                                                                : 0)
                                                              : 0.0;
            if (var_r27 == 1 || var_r27 == 4) {
                float sp3C4[] = { -25.0f, -25.0f, -25.0f, -6.6875f, -6.6875f, -6.6875f, 62.765625f, 62.765625f, 62.765625f, 51.99469f, 76.875f, 45.0f,
                    -27.647583f, -27.647583f, -27.647583f, -9.64325f, -9.64325f, -9.64325f, 60.49022f, 60.49022f, 60.49022f, 51.99469f, 76.875f,
                    45.0f };

                var_f25 = lbl_1_data_F0[var_r28][i].unk0C;
                var_f24 = sp3C4[var_r28] + lbl_1_data_F0[var_r28][i].unk14;
            }
            else if (var_r27 == 2) {
                var_f25 = lbl_1_data_F0[var_r28][i].unk0C;
                var_f24 = lbl_1_rodata_130[var_r28] + lbl_1_data_F0[var_r28][i].unk14;
            }
            else if (var_r27 == 3) {
                var_f25 = (lbl_1_data_F0[var_r28][i].unk0C < 0.0f) ? -335 : 335;
                var_f24 = 830.0f - 94.0f * lbl_1_bss_0;
            }
            else {
                var_f25 = lbl_1_data_F0[var_r28][i].unk0C;
                var_f24 = lbl_1_data_F0[var_r28][i].unk14;
            }
            if (fn_1_34BC(
                    var_f25, var_f24, lbl_1_rodata_10[lbl_1_data_F0[var_r28][i].unk00] + lbl_1_rodata_40[lbl_1_data_F0[var_r28][i].unk00], var_r28, 0)
                != 0) {
                continue;
            }
            if (var_r27 == 3 && lbl_1_data_18A4[(lbl_1_data_F0[var_r28][i].unk0C < 0.0f) ? 0 : 1] > 0) {
                continue;
            }
            if (var_r27 == 4) {
                for (var_r21 = 0; var_r21 < 10; var_r21++) {
                    if (lbl_1_data_F0[10][var_r21].unk04 != 0 && fabs(lbl_1_data_F0[var_r28][i].unk14 - lbl_1_data_F0[10][var_r21].unk14) <= 100.0
                        && fabs(lbl_1_data_F0[var_r28][i].unk0C - lbl_1_data_F0[10][var_r21].unk0C) <= 200.0) {
                        break;
                    }
                    if (lbl_1_data_F0[11][var_r21].unk04 != 0 && fabs(lbl_1_data_F0[var_r28][i].unk14 - lbl_1_data_F0[11][var_r21].unk14) <= 100.0
                        && fabs(lbl_1_data_F0[var_r28][i].unk0C - lbl_1_data_F0[11][var_r21].unk0C) <= 200.0) {
                        break;
                    }
                }
                if (var_r21 < 10 || (lbl_1_data_F0[var_r28][i].unk0C >= -100.0f && lbl_1_data_F0[var_r28][i].unk0C <= 100.0f)) {
                    continue;
                }
            }
            if (var_r28 == 11) {
                lbl_1_bss_14++;
            }
            if ((lbl_1_bss_28 / 60) / 15 == 0 && lbl_1_bss_14 == 0) {
                lbl_1_bss_14++;
            }
            lbl_1_data_F0[var_r28][i].unk00 = var_r28;
            lbl_1_data_F0[var_r28][i].unk04 = (var_r27 == 1) ? 3 : (var_r27 == 2) ? 5 : (var_r27 == 3) ? 1 : (var_r27 == 4) ? 3 : 0;
            lbl_1_data_F0[var_r28][i].unk08 = 0;
            lbl_1_data_F0[var_r28][i].unk2C = 0;
            lbl_1_data_F0[var_r28][i].unk18 = lbl_1_data_F0[var_r28][i].unk1C = lbl_1_data_F0[var_r28][i].unk20 = 0.0f;
            if (var_r27 != 4) {
                sp220 = var_r28 * 4 + 43 + i;
                Hu3DMotionTimeSet(arg0->model[sp220], (var_r27 == 1 || var_r27 == 3) ? 1.0f : Hu3DMotionMaxTimeGet(arg0->model[sp220]));
                Hu3DModelAttrSet(arg0->model[sp220], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(arg0->model[sp220], 1);
                Hu3DModelRotSet(arg0->model[sp220], 0.0f, 0.0f, 0.0f);
            }
            else {
                Hu3DModelAttrReset(arg0->model[i + (var_r28 == 10 ? 83 : 93)], 1);
            }
            if (var_r27 == 1 && var_r20 != 0) {
                var_r20--;
                sp354[0]->unk20 = 4;
            }
            else if (var_r27 == 3 && sp22C != 0) {
                sp22C--;
                sp354[i]->unk20 = 4;
            }
            if (var_r27 == 3) {
                lbl_1_data_18A4[(lbl_1_data_F0[var_r28][i].unk0C < 0.0f) ? 0 : 1] = 85;
                Hu3DMotionTimeSet(arg0->model[(lbl_1_data_F0[var_r28][i].unk0C < 0.0f) ? 6 : 5], 9.0f);
                if (var_r28 == 9 && lbl_1_bss_54[(lbl_1_data_F0[var_r28][i].unk0C < 0.0f) ? 7 : 6].unk00 < 3) {
                    lbl_1_bss_54[(lbl_1_data_F0[var_r28][i].unk0C < 0.0f) ? 7 : 6]
                        .unk04[lbl_1_bss_54[(lbl_1_data_F0[var_r28][i].unk0C < 0.0f) ? 7 : 6].unk00]
                        = 0.0f;
                    lbl_1_bss_54[(lbl_1_data_F0[var_r28][i].unk0C < 0.0f) ? 7 : 6].unk00++;
                }
            }
            if (var_r28 == 9) {
                sp21C = var_r28 * 4 + 43 + i;
                Hu3DMotionSet(arg0->model[sp21C], arg0->motion[i + 22]);
                Hu3DMotionTimeSet(arg0->model[sp21C], 0.0f);
                Hu3DMotionSpeedSet(arg0->model[sp21C], 2.0f);
            }
            var_r19 -= (var_r27 == 1);
            var_r18 -= (var_r27 == 2);
            var_r17 -= (var_r27 == 3);
            sp228 -= (var_r27 == 4);
            sp224 = 0;
        }
    }
    for (i = 0; i < 12; i++) {
        for (j = 0; j < (i < 10 ? 4 : 10); j++) {
            temp_r31 = &lbl_1_data_F0[i][j];
            var_r25 = (i < 10) ? (i * 4 + 43 + j) : ((i - 10) * 10 + 83 + j);
            sp348.x = sp348.y = sp348.z = 0.0f;
            if (temp_r31->unk04 == 0) {
                Hu3DModelAttrSet(arg0->model[var_r25], 1);
            }
            else {
                temp_r31->unk08++;
                temp_r31->unk24 += (temp_r31->unk00 == 10) ? 0 : 0;
                temp_r31->unk24 += (temp_r31->unk24 < 0.0f) ? 360 : (temp_r31->unk24 > 360.0f) ? -360 : 0;
                Hu3DModelObjPosGet(arg0->model[var_r25], lbl_1_data_1828[temp_r31->unk00], &sp348);
                switch (temp_r31->unk04) {
                    case 3:
                    case 5:
                    case 6:
                        if (temp_r31->unk00 >= 3 && temp_r31->unk00 >= 9 && temp_r31->unk04 == 3 && temp_r31->unk14 < -120.0f
                            && temp_r31->unk14 + lbl_1_bss_4 >= -120.0f) {
                            sp218 = (500.0f + temp_r31->unk0C) / 100.0f;
                            sp218 = (sp218 < 0) ? 0 : (sp218 >= 11) ? 10 : sp218;
                            lbl_1_data_1878[sp218] = 15;
                            Hu3DMotionShiftSet(arg0->model[sp218 + 8], arg0->motion[11], 20.0f, 15.0f, HU3D_MOTATTR_NONE);
                            if (temp_r31->unk00 == 9 && lbl_1_bss_54[5].unk00 < 3) {
                                lbl_1_bss_54[5].unk04[lbl_1_bss_54[5].unk00] = 0.0f;
                                lbl_1_bss_54[5].unk00++;
                            }
                        }
                        temp_r31->unk14 += (temp_r31->unk04 == 3 ? lbl_1_bss_4 : lbl_1_bss_0);
                        if (lbl_1_bss_34 >= 1003 && lbl_1_bss_34 < 1005) {
                            if ((temp_r31->unk04 == 3 && temp_r31->unk00 == 9 && temp_r31->unk14 >= 150.0f && temp_r31->unk14 - lbl_1_bss_4 < 150.0f)
                                || (temp_r31->unk04 == 6 && temp_r31->unk00 == 9 && temp_r31->unk08 == 1)) {
                                sp354[j]->unk20 = 5;
                                sp354[j]->unk24 = 0;
                                lbl_1_bss_3C[j]->trans.x = temp_r31->unk0C;
                                lbl_1_bss_3C[j]->trans.y = (j == 0 ? 300 : 0);
                                lbl_1_bss_3C[j]->trans.z = temp_r31->unk14;
                                lbl_1_bss_3C[j]->rot.y
                                    = 180 + ((lbl_1_bss_20 == 4 && temp_r31->unk04 == 6) ? (temp_r31->unk0C < 0.0f ? -45 : 45) : 0);
                                Hu3DMotionSpeedSet(arg0->model[j + 79], 1.0f);
                                Hu3DMotionShiftSet(arg0->model[j + 79], arg0->motion[j + 22], 44.0f, 2.0f, HU3D_MOTATTR_NONE);
                                Hu3DParticleCntSet(arg0->model[j + 39], j == 0 ? 15 : 0);
                                if (lbl_1_bss_54->unk00 < 3) {
                                    lbl_1_bss_54->unk04[lbl_1_bss_54->unk00] = 0.0f;
                                    lbl_1_bss_54->unk00++;
                                }
                            }
                        }
                        if (temp_r31->unk04 == 3 && temp_r31->unk14 > 510.0f) {
                            temp_r31->unk04 = 4;
                            temp_r31->unk08 = 0;
                            if (temp_r31->unk00 != 10) {
                                if (temp_r31->unk00 != 9) {
                                    Hu3DMotionTimeSet(arg0->model[var_r25], 1.0f);
                                }
                                else {
                                    Hu3DMotionSet(arg0->model[var_r25], arg0->motion[j + 26]);
                                    Hu3DMotionTimeSet(arg0->model[var_r25], 1.0f);
                                    Hu3DMotionSpeedSet(arg0->model[var_r25], 1.0f);
                                }
                                Hu3DModelAttrReset(arg0->model[var_r25], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                            }
                        }
                        if ((temp_r31->unk04 == 5 || temp_r31->unk04 == 6) && sp348.z > 1400.0f && temp_r31->unk14 > 700.0f) {
                            temp_r31->unk08 = 0;
                            temp_r31->unk10 = sp348.y;
                            temp_r31->unk14 = sp348.z;
                            temp_r31->unk1C = 0.0f;
                            if (temp_r31->unk00 == 10) {
                                Hu3DModelAttrSet(arg0->model[var_r25], HU3D_MOTATTR_LOOP);
                            }
                            else if (temp_r31->unk00 != 9) {
                                Hu3DMotionTimeSet(arg0->model[var_r25], 2.0f);
                                Hu3DModelAttrReset(arg0->model[var_r25], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                            }
                            else {
                                Hu3DMotionSet(arg0->model[var_r25], arg0->motion[(temp_r31->unk04 == 6) ? (j + 26) : (j + 30)]);
                                Hu3DMotionTimeSet(arg0->model[var_r25], 1.0f);
                                Hu3DMotionSpeedSet(arg0->model[var_r25], 1.0f);
                            }
                            temp_r31->unk04 = 7;
                            Hu3DModelPosSet(arg0->model[var_r25], temp_r31->unk0C, temp_r31->unk10, temp_r31->unk14);
                        }
                        else {
                            Hu3DModelPosSet(arg0->model[var_r25], temp_r31->unk0C,
                                ((temp_r31->unk00 >= 0 && temp_r31->unk00 < 10)
                                        ? ((temp_r31->unk04 != 6 ? 300 : 0) + lbl_1_rodata_100[temp_r31->unk00])
                                        : temp_r31->unk10)
                                    + lbl_1_rodata_A0[temp_r31->unk00],
                                temp_r31->unk14 + lbl_1_rodata_D0[temp_r31->unk00]);
                        }
                        if (temp_r31->unk00 >= 10) {
                            Hu3DModelRotSet(arg0->model[var_r25], 0.0f, temp_r31->unk24, 0.0f);
                        }
                        break;
                    case 4:
                        if (temp_r31->unk00 >= 0 && temp_r31->unk00 < 10) {
                            float sp394[] = { 0.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, 1.75f, 1.75f, 1.75f, 0.0f, 0.0f, 0.0f };
                            s32 sp364[] = { 42, 42, 42, 41, 41, 41, 48, 48, 48, 27, 27, 27 };

                            if (temp_r31->unk00 >= 6 && temp_r31->unk00 <= 8) {
                                temp_f29 = temp_r31->unk08;
                                temp_f27 = (temp_f29 <= 1.0f)                 ? 0.0
                                    : (temp_f29 >= 30.0f && temp_f29 < 40.0f) ? -1.0 * (1.0 - (temp_f29 - 30.0f) / 9.0)
                                    : (temp_f29 >= 40.0f)                     ? 1.0 - (temp_f29 - 40.0f) / 8.0
                                                                              : 1.0;
                                temp_f27 = (temp_f29 >= 40.0f) ? -1.0 + (temp_f27 * 0.5 + temp_f27 * temp_f27 * 0.5) : temp_f27;
                                temp_f27 = (temp_f29 <= 1.0f) ? 0.0
                                    : (temp_f29 < 23.0f)      ? 1.0
                                    : (temp_f29 < 32.0f)      ? 0.5
                                    : (temp_f29 < 40.0f)      ? -0.8
                                                              : (-1.0 - 0.4 * (1.0 - (temp_f29 - 40.0f) / 8.0));
                                temp_r31->unk14 -= (lbl_1_bss_4 * sp394[temp_r31->unk00] / 4.0) * temp_f27;
                            }
                            else {
                                temp_r31->unk14 -= lbl_1_bss_4 * sp394[temp_r31->unk00] / 4.0;
                            }
                            if (temp_r31->unk08 >= sp364[temp_r31->unk00]) {
                                temp_r31->unk10 = 0.0f;
                                temp_r31->unk04 = 5;
                                temp_r31->unk08 = 0;
                            }
                        }
                        else {
                            temp_r31->unk1C -= 1.0f;
                            temp_r31->unk10 += temp_r31->unk1C;
                            temp_r31->unk14 += 1.25 * lbl_1_bss_4;
                            if (temp_r31->unk10 <= 0.0f) {
                                if (temp_r31->unk1C < -10.0f && temp_r31->unk00 == 10) {
                                    temp_r31->unk1C = 9.0f;
                                }
                                else {
                                    temp_r31->unk1C = 0.0f;
                                    temp_r31->unk10 = 0.0f;
                                    temp_r31->unk04 = 5;
                                    temp_r31->unk08 = 0;
                                }
                            }
                        }
                        Hu3DModelPosSet(arg0->model[var_r25], temp_r31->unk0C,
                            lbl_1_rodata_A0[temp_r31->unk00]
                                + ((temp_r31->unk00 >= 0 && temp_r31->unk00 < 10) ? (300.0f + lbl_1_rodata_100[temp_r31->unk00]) : temp_r31->unk10),
                            temp_r31->unk14 + lbl_1_rodata_D0[temp_r31->unk00]);
                        if (temp_r31->unk00 >= 10) {
                            Hu3DModelRotSet(arg0->model[var_r25], 0.0f, temp_r31->unk24, 0.0f);
                        }
                        break;
                    case 1:
                        temp_f20 = temp_r31->unk08 / 90.0;
                        temp_f23 = 1.0f - temp_f20;
                        sp214 = temp_r31->unk0C;
                        sp210 = temp_r31->unk10;
                        sp20C = temp_r31->unk14;
                        temp_r31->unk0C = (460.0f + 1135.0f * temp_f23) * (temp_r31->unk0C < 0.0f ? -1 : 1);
                        temp_r31->unk10 = 100.0f * temp_f20 + 500.0f * temp_f23;
                        temp_r31->unk14 = 800.0f - 695.0f * temp_f23;
                        temp_r31->unk18 = temp_r31->unk0C - sp214;
                        temp_r31->unk1C = temp_r31->unk10 - sp210;
                        temp_r31->unk20 = temp_r31->unk14 - sp20C;
                        if (temp_r31->unk08 >= 90) {
                            temp_r31->unk04 = 2;
                            temp_r31->unk08 = 0;
                        }
                        Hu3DModelPosSet(arg0->model[var_r25], temp_r31->unk0C, temp_r31->unk10 + lbl_1_rodata_A0[temp_r31->unk00],
                            temp_r31->unk14 + lbl_1_rodata_D0[temp_r31->unk00]);
                        Hu3DModelRotSet(arg0->model[var_r25], 9.0f, (temp_r31->unk0C < 0.0f) ? -31 : 31, (temp_r31->unk0C < 0.0f) ? -18 : 18);
                        break;
                    case 2:
                        temp_r31->unk1C -= (temp_r31->unk00 != 9) ? 0.625 : 0.9;
                        temp_r31->unk0C += temp_r31->unk18;
                        temp_r31->unk10 += temp_r31->unk1C;
                        temp_r31->unk14 += temp_r31->unk20;
                        if (temp_r31->unk10 <= lbl_1_rodata_100[temp_r31->unk00]) {
                            temp_r31->unk10 = -lbl_1_rodata_100[temp_r31->unk00];
                            temp_r31->unk1C = 0.0f;
                            temp_r31->unk04 = 6;
                            temp_r31->unk08 = 0;
                            Hu3DModelPosSet(arg0->model[var_r25], temp_r31->unk0C,
                                temp_r31->unk10 + lbl_1_rodata_A0[temp_r31->unk00] + lbl_1_rodata_100[temp_r31->unk00]
                                    + lbl_1_rodata_100[temp_r31->unk00],
                                temp_r31->unk14 + lbl_1_rodata_D0[temp_r31->unk00]);
                            Hu3DModelRotSet(arg0->model[var_r25], 0.0f, (temp_r31->unk0C < 0.0f) ? -31 : 31, 0.0f);
                        }
                        else {
                            Hu3DModelPosSet(arg0->model[var_r25], temp_r31->unk0C, temp_r31->unk10 + lbl_1_rodata_A0[temp_r31->unk00],
                                temp_r31->unk14 + lbl_1_rodata_D0[temp_r31->unk00]);
                        }
                        break;
                    case 7:
                        temp_r31->unk1C -= 1.0f;
                        temp_r31->unk10 += temp_r31->unk1C;
                        temp_r31->unk14 += (temp_r31->unk00 >= 10) ? lbl_1_bss_0 : 0.0f;
                        if (temp_r31->unk10 <= -800.0f) {
                            Hu3DModelAttrSet(arg0->model[var_r25], 1);
                            if (temp_r31->unk00 == 9) {
                                Hu3DMotionSet(arg0->model[var_r25], arg0->motion[j + 22]);
                                Hu3DMotionTimeSet(arg0->model[var_r25], 0.0f);
                                Hu3DMotionSpeedSet(arg0->model[var_r25], 2.0f);
                            }
                            temp_r31->unk04 = 0;
                        }
                        Hu3DModelPosSet(arg0->model[var_r25], temp_r31->unk0C,
                            (temp_r31->unk00 >= 0 && temp_r31->unk00 < 9) ? (300.0f + lbl_1_rodata_100[temp_r31->unk00]) : temp_r31->unk10,
                            temp_r31->unk14 + lbl_1_rodata_D0[temp_r31->unk00]);
                        Hu3DModelPosSet(arg0->model[var_r25], temp_r31->unk0C, temp_r31->unk10, temp_r31->unk14);
                        if (temp_r31->unk00 >= 10) {
                            Hu3DModelRotSet(arg0->model[var_r25], 0.0f, temp_r31->unk24, 0.0f);
                        }
                        break;
                }
                if (temp_r31->unk00 >= 0 && temp_r31->unk00 <= 8 && (temp_r31->unk04 == 4 || temp_r31->unk04 == 5)) {
                    sp208 = Hu3DMotionTimeGet(arg0->model[var_r25]);
                    if (temp_r31->unk00 >= 0 && temp_r31->unk00 <= 2 && (sp208 == 26 || sp208 == -41) && lbl_1_bss_54[3].unk00 < 3) {
                        lbl_1_bss_54[3].unk04[lbl_1_bss_54[3].unk00] = 0.0f;
                        lbl_1_bss_54[3].unk00++;
                    }
                    if (temp_r31->unk00 >= 3 && temp_r31->unk00 <= 5 && (sp208 == 23 || sp208 == -39) && lbl_1_bss_54[2].unk00 < 3) {
                        lbl_1_bss_54[2].unk04[lbl_1_bss_54[2].unk00] = 0.0f;
                        lbl_1_bss_54[2].unk00++;
                    }
                    if (temp_r31->unk00 >= 6 && temp_r31->unk00 <= 8 && (sp208 == 20 || sp208 == -29) && lbl_1_bss_54[1].unk00 < 3) {
                        lbl_1_bss_54[1].unk04[lbl_1_bss_54[1].unk00] = 0.0f;
                        lbl_1_bss_54[1].unk00++;
                    }
                }
                if (i == 9 && lbl_1_bss_18 != 0) {
                    ModelData *sp204 = &Hu3DData[arg0->model[j + 39]];
                    ParticleData *sp200 = sp204->unk_120;

                    if (sp200->unk_34 == 63) {
                        ModelData *temp_r23 = &Hu3DData[arg0->model[var_r25]];
                        ModelData *temp_r22 = &Hu3DData[arg0->model[j + 39]];

                        temp_r22->pos.x = temp_r23->pos.x;
                        temp_r22->pos.y = temp_r23->pos.y;
                        temp_r22->pos.z = temp_r23->pos.z;
                        temp_r22->rot.x = temp_r23->rot.x;
                        temp_r22->rot.y = temp_r23->rot.y;
                        temp_r22->rot.z = temp_r23->rot.z;
                    }
                }
                if (temp_r31->unk2C == 0 && (lbl_1_bss_34 == 1004 || lbl_1_bss_34 == 1005)) {
                    if (temp_r31->unk00 != 9
                        || (temp_r31->unk04 != 1 && temp_r31->unk04 != 2
                            && ((temp_r31->unk04 != 3 && temp_r31->unk04 != 6) || sp354[j]->unk20 > 5 || sp354[j]->unk20 < 3))) {
                        temp_r31->unk2C = 1;
                    }
                }
                temp_r31->unk2C += (temp_r31->unk2C > 0);
                if (temp_r31->unk2C != 0 && (temp_r31->unk2C % 2 == 0 || temp_r31->unk2C > 25)) {
                    Hu3DModelAttrSet(arg0->model[var_r25], 1);
                }
                else {
                    Hu3DModelAttrReset(arg0->model[var_r25], 1);
                }
            }
        }
    }
    for (i = 0; i < 11; i++) {
        if (lbl_1_data_1878[i] == 1) {
            Hu3DMotionShiftSet(arg0->model[i + 8], arg0->motion[0], 0.0f, 60.0f, HU3D_MOTATTR_LOOP);
        }
        lbl_1_data_1878[i] -= (lbl_1_data_1878[i] > 0);
    }
    lbl_1_data_18A4[0] -= (lbl_1_data_18A4[0] > 0);
    lbl_1_data_18A4[1] -= (lbl_1_data_18A4[1] > 0);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 8; j++) {
            s32 sp1FC = lbl_1_bss_104[i][j].unk00 + 21;

            lbl_1_bss_104[i][j].unk04++;
            if (lbl_1_bss_104[i][j].unk04 >= 520) {
                if (lbl_1_bss_104[i][j].unk00 != -1) {
                    Hu3DModelAttrReset(arg0->model[lbl_1_bss_104[i][j].unk00 + 21], 1);
                }
                lbl_1_bss_104[i][j].unk04 = 0;
                lbl_1_bss_104[i][j].unk00 = -1;
                for (sp230 = 0; sp230 < 14; sp230++) {
                    s32 sp1F8;
                    s32 sp1F4 = rand8() % 18;

                    for (sp1F8 = 0; sp1F8 < 24; sp1F8++) {
                        if (sp1F4 == lbl_1_bss_104[sp1F8 / 8][sp1F8 % 8].unk00) {
                            break;
                        }
                    }
                    if (sp1F8 == 24) {
                        lbl_1_bss_104[i][j].unk00 = sp1F4;
                        break;
                    }
                }
                if (lbl_1_bss_104[i][j].unk00 != -1) {
                    Hu3DModelAttrReset(arg0->model[lbl_1_bss_104[i][j].unk00 + 21], 1);
                }
            }
            sp1FC = lbl_1_bss_104[i][j].unk00 + 21;
            temp_f22 = lbl_1_bss_104[i][j].unk04 / 520.0f;
            if (lbl_1_bss_104[i][j].unk00 != -1) {
                switch (i) {
                    case 0:
                        Hu3DModelPosSet(arg0->model[sp1FC], 2000.0f - 4000.0f * temp_f22, -490.0f, 1000.0f);
                        break;
                    case 1:
                        Hu3DModelPosSet(arg0->model[sp1FC], -1200.0f, -290.0f, 2000.0f - 4000.0f * temp_f22);
                        break;
                    case 2:
                        Hu3DModelPosSet(arg0->model[sp1FC], 1200.0f, -290.0f, 2000.0f - 4000.0f * temp_f22);
                        break;
                }
            }
        }
    }
    for (i = 0; i < 2; i++) {
        espBankSet(lbl_1_data_40[i * 7 + 2], lbl_1_data_18F4[i] % 10);
        espBankSet(lbl_1_data_40[i * 7 + 3], (lbl_1_data_18F4[i] / 10) % 10);
    }
    for (i = 0; i < 4; i++) {
        ModelData *temp_r24 = &Hu3DData[lbl_1_bss_3C[i]->model[0]];
        float temp_f19 = 0.0f;
        float sp1F0 = (temp_r24->unk_08 == lbl_1_bss_3C[i]->motion[3]) ? 0 : -1;
        float sp1EC = (temp_r24->unk_0C == lbl_1_bss_3C[i]->motion[3]) ? 0 : -1;
        float sp1E8 = (sp1F0 == -1.0f)   ? 0.0f
            : (temp_r24->unk_64 < 4.0f)  ? 0.0f
            : (temp_r24->unk_64 > 28.0f) ? 1.0f
                                         : (temp_r24->unk_64 - 4.0f) / 24.0f;
        float sp1E4 = (sp1EC == -1.0f)   ? 0.0f
            : (temp_r24->unk_84 < 4.0f)  ? 0.0f
            : (temp_r24->unk_84 > 28.0f) ? 1.0f
                                         : (temp_r24->unk_84 - 4.0f) / 24.0f;
        float temp_f18 = (temp_r24->unk_0C == -1) ? 0.0f : (temp_r24->unk_80 == 0.0f) ? 1.0f : (temp_r24->unk_7C / temp_r24->unk_80);

        temp_f19 = sp1E8 * (1.0f - temp_f18) + sp1E4 * temp_f18;
        if (!(temp_r24->attr & 1) && sp354[i]->unk20 != 3 && sp354[i]->unk20 != 4 && lbl_1_bss_3C[i]->trans.z < 1400.0f) {
            Hu3DModelAttrReset(lbl_1_bss_3C[i]->model[1], 1);
            Hu3DModelPosSet(lbl_1_bss_3C[i]->model[1], lbl_1_bss_3C[i]->trans.x, (lbl_1_bss_3C[i]->trans.z < 620.0f) ? 5 : -295,
                lbl_1_bss_3C[i]->trans.z - 165.0f * temp_f19);
            Hu3DModelScaleSet(
                lbl_1_bss_3C[i]->model[1], 0.75 * (sp354[i]->unk08 == 5 ? 1.25 : 1.0), 1.0f, 1.25 * (sp354[i]->unk08 == 5 ? 1.25 : 1.0));
        }
        else {
            Hu3DModelAttrSet(lbl_1_bss_3C[i]->model[1], 1);
        }
    }
}

void fn_1_89E0(omObjData *arg0)
{
    StructBss3CData *spC[4];
    s32 sp8;
    s32 var_r29;
    s32 var_r30;
    s32 i;

    for (i = 0; i < 4; i++) {
        spC[i] = lbl_1_bss_3C[i]->data;
    }
    for (i = 0; i < 11; i++) {
        s32 sp1C[] = { 0x60A, 0x60B, 0x60C, 0x60D, 0x60E, 0x60F, 0x611, 0x610, 0x007, 0x013, 0x612 };

        if (lbl_1_bss_54[i].unk00 > 3) {
            lbl_1_bss_54[i].unk00 = 3;
        }
        if (lbl_1_bss_54[i].unk00 > 0) {
            sp8 = HuAudFXPlay(sp1C[i]);
            lbl_1_bss_54[i].unk00--;
        }
    }
    if (omSysExitReq != 0 && WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        arg0->func = fn_1_B480;
    }
    switch (lbl_1_bss_34) {
        case 1000:
            lbl_1_bss_8 += 1.0f;
            if (lbl_1_bss_8 == 5.0f) {
                lbl_1_data_18B0 = HuAudFXPlay(0x609);
            }
            if (WipeStatGet() == 0) {
                lbl_1_bss_34++;
                lbl_1_bss_8 = 0.0f;
            }
            break;
        case 1001:
            lbl_1_bss_8 += 1.0f;
            if (180.0f < lbl_1_bss_8) {
                lbl_1_bss_34++;
                lbl_1_bss_8 = 0.0f;
            }
            break;
        case 1002:
            lbl_1_bss_8 += 1.0f;
            if (lbl_1_bss_8 == 5.0f && lbl_1_bss_2E < 0) {
                lbl_1_bss_2E = MGSeqStartCreate();
            }
            if (lbl_1_bss_8 >= 5.0f && lbl_1_data_18AC == -1 && (MGSeqStatGet(lbl_1_bss_2E) & 0x10)) {
                lbl_1_data_18AC = HuAudSeqPlay(0x47);
            }
            if (lbl_1_bss_8 >= 5.0f && MGSeqStatGet(lbl_1_bss_2E) == 0 && lbl_1_bss_2E >= 0) {
                lbl_1_bss_34++;
                lbl_1_bss_28 = 1800;
                lbl_1_bss_2C = MGSeqTimerCreate(lbl_1_bss_28 / 60);
                lbl_1_bss_2E = -1;
                lbl_1_bss_8 = 0.0f;
                for (i = 0; i < 16; i++) {
                    espDispOn(lbl_1_data_40[i]);
                }
                for (i = 0; i < 4; i++) {
                    spC[i]->unk20 = 1;
                }
            }
            break;
        case 1003:
            lbl_1_bss_8 += 1.0f;
            MGSeqParamSet(lbl_1_bss_2C, 1, (lbl_1_bss_28 + 58) / 60);
            lbl_1_bss_28--;
            if (lbl_1_bss_28 <= 0) {
                lbl_1_bss_34 = 1004;
                lbl_1_bss_8 = 0.0f;
                lbl_1_bss_20 = 4;
            }
            break;
        case 1004:
            if (lbl_1_bss_2E < 0 && lbl_1_bss_8 == 0.0f) {
                MGSeqParamSet(lbl_1_bss_2C, 2, -1);
                lbl_1_bss_2E = MGSeqFinishCreate();
                if (lbl_1_data_18AC != -1) {
                    HuAudSeqFadeOut(lbl_1_data_18AC, 100);
                }
            }
            else {
                var_r29 = 0;
                var_r30 = 0;
                for (i = 0; i < 4; i++) {
                    if (spC[i]->unk20 == 1 || (spC[i]->unk20 >= 2 && spC[i]->unk20 <= 5)) {
                        var_r29++;
                    }
                    if (i == 0 && ((spC[0]->unk20 >= 2 && spC[0]->unk20 <= 4) || (spC[0]->unk20 == 4 && lbl_1_data_F0[9][0].unk14 < 70.0f))) {
                        var_r30++;
                    }
                    else if (i != 0 && spC[i]->unk20 >= 2 && spC[i]->unk20 <= 4) {
                        var_r30++;
                    }
                }
                if (MGSeqStatGet(lbl_1_bss_2E) == 0
                    && ((lbl_1_bss_8 >= 150.0f && var_r29 == 0 && var_r30 == 0) || (lbl_1_bss_8 >= 240.0f && var_r30 == 0)
                        || lbl_1_bss_8 >= 360.0f)) {
                    lbl_1_bss_34++;
                    lbl_1_bss_8 = 0.0f;
                    GWPlayerCoinCollectSet(spC[0]->unk04, lbl_1_data_18F4[0]);
                    GWPlayerCoinCollectSet(spC[1]->unk04, lbl_1_data_18F4[1]);
                    GWPlayerCoinCollectSet(spC[2]->unk04, lbl_1_data_18F4[1]);
                    GWPlayerCoinCollectSet(spC[3]->unk04, lbl_1_data_18F4[1]);
                    if (lbl_1_data_18F4[0] == 0 && lbl_1_data_18F4[1] == 0) {
                        HuAudSStreamPlay(4);
                    }
                    else {
                        HuAudSStreamPlay(1);
                    }
                }
            }
            lbl_1_bss_8 += 1.0f;
            break;
        case 1005:
            lbl_1_bss_8 += 1.0f;
            if (210.0f < lbl_1_bss_8) {
                HuAudFXStop(lbl_1_data_18B0);
                lbl_1_bss_2E = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                arg0->func = fn_1_B480;
            }
            break;
        default:
            OSReport("*** main mode error(%d)!!\n", lbl_1_bss_34);
            break;
    }
}

void fn_1_9410(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r31;
    float temp_f31;
    float temp_f30;
    s16 i;

    if (particle->unk_34 < 50) {
        var_r31 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk00 = particle->unk_34 + 41;
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
    }
    if (particle->unk_34 >= 255) {
        var_r31 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r31++) {
            var_r31->unk00 = 255;
            var_r31->unk40.a = 0;
            var_r31->unk2C = 0.0f;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, var_r31++) {
        if (!var_r31->unk2C) {
            break;
        }
    }
    var_r31 = particle->unk_48;
    for (i = 0; i < particle->unk_30; i++, var_r31++) {
        if (var_r31->unk00 == 104) {
            var_r31->unk34.x = var_r31->unk34.z = 0.0f;
            var_r31->unk34.y = 72.0f;
            temp_f31 = frandu8() * 360 / 256;
            temp_f30 = 0.5 + (rand8() / 256.0) * 1.5;
            var_r31->unk34.x = 75.0 * sind(temp_f31);
            var_r31->unk34.z = 75.0 * cosd(temp_f31);
            var_r31->unk08.x = temp_f30 * sind(temp_f31) * 2.0;
            var_r31->unk08.y = 3.0 + (rand8() / 256.0) * 1.5;
            var_r31->unk08.z = temp_f30 * cosd(temp_f31) * 2.0;
            var_r31->unk40.r = 0xFF;
            var_r31->unk40.g = 0xFF;
            var_r31->unk40.b = 0xFF;
            var_r31->unk40.a = 0x60;
            var_r31->unk2C = 50.0f;
            VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
        }
        if (var_r31->unk00 < 240) {
            VECAdd(&var_r31->unk08, &var_r31->unk34, &var_r31->unk34);
            var_r31->unk08.x *= 0.9f;
            var_r31->unk08.z *= 0.9f;
            var_r31->unk08.y *= 0.9f;
            var_r31->unk40.a = var_r31->unk40.a * 16 / 17;
            var_r31->unk08.z *= 0.99f;
            var_r31->unk2C += 2.0f;
            if (var_r31->unk2C <= 0.0f) {
                var_r31->unk2C = 0.0f;
            }
            if (var_r31->unk40.a <= 3) {
                var_r31->unk40.a = 0;
                var_r31->unk2C = 0.0f;
            }
        }
        var_r31->unk00 += (var_r31->unk00 < 0x8000);
    }
}

void fn_1_9900(omObjData *arg0)
{
    s32 temp_r28;
    s32 i;
    s32 j;
    s32 k;

    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 18));
    omSetTra(arg0, 0.0f, 0.0f, 0.0f);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 17));
    Hu3DModelPosSet(arg0->model[1], 0.0f, 300.0f, -100.0f);
    Hu3DModelAttrSet(arg0->model[1], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(arg0->model[1], 0);
    Hu3DMotionSpeedSet(arg0->model[1], 1.5f);
    arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 16));
    Hu3DModelPosSet(arg0->model[3], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[3], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(arg0->model[3], 0);
    Hu3DMotionSpeedSet(arg0->model[3], 1.5f);
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 19));
    Hu3DModelAttrSet(arg0->model[4], HU3D_MOTATTR_LOOP);
    arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 20));
    Hu3DModelPosSet(arg0->model[5], 460.0f, 0.0f, 800.0f);
    Hu3DModelAttrReset(arg0->model[5], HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(arg0->model[5], Hu3DMotionMaxTimeGet(arg0->model[5]));
    arg0->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 21));
    Hu3DModelPosSet(arg0->model[6], -460.0f, 0.0f, 800.0f);
    Hu3DModelAttrReset(arg0->model[6], HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(arg0->model[6], Hu3DMotionMaxTimeGet(arg0->model[6]));
    arg0->model[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 22));
    Hu3DModelAttrSet(arg0->model[7], HU3D_MOTATTR_LOOP);
    arg0->model[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 23));
    arg0->motion[0] = Hu3DJointMotionFile(arg0->model[8], DATA_MAKE_NUM(DATADIR_M422, 24));
    arg0->motion[11] = Hu3DJointMotionFile(arg0->model[8], DATA_MAKE_NUM(DATADIR_M422, 25));
    for (i = 0; i < 11; i++) {
        if (i != 0) {
            arg0->model[i + 8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 23));
            arg0->motion[i] = Hu3DJointMotionFile(arg0->model[i + 8], DATA_MAKE_NUM(DATADIR_M422, 24));
            arg0->motion[i + 11] = Hu3DJointMotionFile(arg0->model[i + 8], DATA_MAKE_NUM(DATADIR_M422, 25));
        }
        Hu3DModelPosSet(arg0->model[i + 8], i * 100 - 500, 550.0f, 0.0f);
        Hu3DMotionSet(arg0->model[i + 8], arg0->motion[0]);
        Hu3DModelAttrSet(arg0->model[i + 8], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(arg0->model[i + 8], HU3D_MOTATTR_PAUSE);
        Hu3DMotionTimeSet(arg0->model[i + 8], rand8() % (s32)Hu3DMotionMaxTimeGet(arg0->model[i + 8]));
    }
    arg0->model[19] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 26));
    Hu3DModelPosSet(arg0->model[19], 1800.0f, 0.0f, -22.0f);
    Hu3DModelAttrSet(arg0->model[19], HU3D_MOTATTR_LOOP);
    arg0->model[20] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 27));
    Hu3DModelPosSet(arg0->model[20], -1800.0f, 0.0f, -22.0f);
    Hu3DModelAttrSet(arg0->model[20], HU3D_MOTATTR_LOOP);
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 4; j++) {
            s32 spD0[] = { DATA_MAKE_NUM(DATADIR_M422, 41), DATA_MAKE_NUM(DATADIR_M422, 42), DATA_MAKE_NUM(DATADIR_M422, 43),
                DATA_MAKE_NUM(DATADIR_M422, 44), DATA_MAKE_NUM(DATADIR_M422, 45), DATA_MAKE_NUM(DATADIR_M422, 46), DATA_MAKE_NUM(DATADIR_M422, 47),
                DATA_MAKE_NUM(DATADIR_M422, 48), DATA_MAKE_NUM(DATADIR_M422, 49), DATA_MAKE_NUM(DATADIR_M422, 30) };
            s32 sp30[] = { DATA_MAKE_NUM(DATADIR_M422, 30), DATA_MAKE_NUM(DATADIR_M422, 31), DATA_MAKE_NUM(DATADIR_M422, 32),
                DATA_MAKE_NUM(DATADIR_M422, 33), DATA_MAKE_NUM(DATADIR_M422, 34), DATA_MAKE_NUM(DATADIR_M422, 35), DATA_MAKE_NUM(DATADIR_M422, 37),
                DATA_MAKE_NUM(DATADIR_M422, 36) };

            temp_r28 = i * 4 + 43 + j;
            if (i == 9) {
                StructBss3CData *var_r23 = lbl_1_bss_3C[j]->data;

                arg0->model[temp_r28] = Hu3DModelCreateFile(sp30[var_r23->unk08]);
            }
            else if (j == 0) {
                arg0->model[temp_r28] = Hu3DModelCreateFile(spD0[i]);
            }
            else {
                arg0->model[temp_r28] = Hu3DModelLink(arg0->model[temp_r28 - j]);
            }
            Hu3DModelAttrSet(arg0->model[temp_r28], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(arg0->model[temp_r28], HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(arg0->model[temp_r28], 0.0f);
            Hu3DMotionSpeedSet(arg0->model[temp_r28], (i != 9) ? 0.9375 : 1.0);
            if (i == 9) {
                arg0->motion[j + 22] = Hu3DJointMotionFile(arg0->model[temp_r28], DATA_MAKE_NUM(DATADIR_M422, 38));
                arg0->motion[j + 26] = Hu3DJointMotionFile(arg0->model[temp_r28], DATA_MAKE_NUM(DATADIR_M422, 39));
                arg0->motion[j + 30] = Hu3DJointMotionFile(arg0->model[temp_r28], DATA_MAKE_NUM(DATADIR_M422, 40));
                Hu3DMotionSet(arg0->model[temp_r28], arg0->motion[j + 22]);
                Hu3DModelAttrSet(arg0->model[temp_r28], HU3D_MOTATTR_PAUSE);
            }
        }
        if (i <= 8) {
            for (k = 0; k < 2; k++) {
                arg0->model[i * 2 + 21 + k] = Hu3DModelLink(arg0->model[i * 4 + 43]);
                Hu3DModelAttrSet(arg0->model[i * 2 + 21 + k], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
            }
        }
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 10; j++) {
            s32 sp28[] = { DATA_MAKE_NUM(DATADIR_M422, 28), DATA_MAKE_NUM(DATADIR_M422, 29) };

            temp_r28 = i * 10 + 83 + j;
            if (j == 0) {
                arg0->model[temp_r28] = Hu3DModelCreateFile(sp28[i]);
            }
            else {
                arg0->model[temp_r28] = Hu3DModelLink(arg0->model[temp_r28 - j]);
            }
            Hu3DModelAttrSet(arg0->model[temp_r28], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrSet(arg0->model[temp_r28], 1);
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 8; j++) {
            lbl_1_bss_104[i][j].unk04 = j * 520 / 8;
            lbl_1_bss_104[i][j].unk00 = -1;
        }
    }
    for (i = 0; i < 16; i++) {
        s32 sp20[] = { 88, 473 };
        s32 sp18[] = { 78, 70 };
        s32 sp90[] = { 0, 0, 42, 22, -20, 2, -54, 0, 0, 55, 35, -7, 15, -51, -65, -37 };
        s32 sp50[] = { 0, 0, 1, 1, 1, 1, -2, 0, 0, 9, 9, 9, 9, -14, 10, 10 };

        if (lbl_1_data_0[i] == DATA_MAKE_NUM(DATADIR_MGCONST, 12) || lbl_1_data_0[i] == DATA_MAKE_NUM(DATADIR_MGCONST, 0)) {
            StructBss3CData *var_r22 = lbl_1_bss_3C[(i == 6) ? 0 : (i == 13) ? 1 : (i == 14) ? 2 : 3]->data;

            lbl_1_data_40[i] = espEntry(lbl_1_data_0[i] + var_r22->unk08, 0, 0);
        }
        else {
            lbl_1_data_40[i] = espEntry(lbl_1_data_0[i], 0, 0);
        }
        espDrawNoSet(lbl_1_data_40[i], 0);
        espDispOff(lbl_1_data_40[i]);
        espAttrSet(lbl_1_data_40[i], 1);
        espBankSet(lbl_1_data_40[i], 0);
        espPriSet(lbl_1_data_40[i], 128 - i);
        espPosSet(lbl_1_data_40[i], sp90[i] + sp20[i < 7 ? 0 : 1], sp50[i] + sp18[i < 7 ? 0 : 1]);
        switch (i >= 7 ? i - 7 : i) {
            case 0:
                espTPLvlSet(lbl_1_data_40[i], 0.5f);
                espColorSet(lbl_1_data_40[i], 0, 0, 0);
                break;
            case 5:
                espBankSet(lbl_1_data_40[i], 10);
                break;
        }
    }
    for (i = 0; i < 4; i++) {
        s32 temp_r26 = i + 39;

        arg0->model[temp_r26] = Hu3DParticleCreate(HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 3), MEMORY_DEFAULT_NUM)), 40);
        Hu3DModelPosSet(arg0->model[temp_r26], 2000.0f, -2000.0f, -2000.0f);
        Hu3DModelScaleSet(arg0->model[temp_r26], 1.0f, 1.0f, 1.0f);
        Hu3DModelLayerSet(arg0->model[temp_r26], 3);
        Hu3DModelAttrReset(arg0->model[temp_r26], 1);
        Hu3DParticleColSet(arg0->model[temp_r26], 0xFF, 0xFF, 0xFF);
        Hu3DParticleScaleSet(arg0->model[temp_r26], 5.0f);
        Hu3DParticleHookSet(arg0->model[temp_r26], fn_1_9410);
        Hu3DParticleCntSet(arg0->model[temp_r26], 45);
    }
    for (i = 0; i < 4; i++) {
        s32 var_r27 = 9;
        s32 temp_r24 = 43 + var_r27 * 4 + i;

        lbl_1_data_F0[var_r27][i].unk0C = lbl_1_data_18B4[i][0];
        lbl_1_data_F0[var_r27][i].unk10 = (i == 0 ? 300 : 0);
        lbl_1_data_F0[var_r27][i].unk14 = (i == 0 ? 50 : 800);
        lbl_1_data_F0[var_r27][i].unk00 = 9;
        lbl_1_data_F0[var_r27][i].unk04 = (i == 0 ? 3 : 6);
        lbl_1_data_F0[var_r27][i].unk08 = 0;
        lbl_1_data_F0[var_r27][i].unk18 = lbl_1_data_F0[var_r27][i].unk1C = lbl_1_data_F0[var_r27][i].unk20 = 0.0f;
        Hu3DMotionTimeSet(arg0->model[temp_r24], 0.0f);
        Hu3DModelAttrSet(arg0->model[temp_r24], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(arg0->model[temp_r24], 1);
        Hu3DModelRotSet(arg0->model[temp_r24], 0.0f, 0.0f, 0.0f);
    }
    arg0->func = fn_1_3B74;
}

void fn_1_AC4C(omObjData *arg0)
{
    s32 sp8[] = { 0, 1, 2, 3 };
    StructBss3CData *temp_r31;
    s32 var_r27;
    s32 j;
    s32 i;

    var_r27 = 0;
    temp_r31 = arg0->data;
    memset(temp_r31, 0, sizeof(*temp_r31));
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GWPlayerCfg[j].group) {
                sp8[var_r27] = j;
                var_r27++;
            }
        }
    }
    temp_r31->unk00 = arg0->work[0];
    temp_r31->unk04 = sp8[temp_r31->unk00];
    if (temp_r31->unk04 == 4) {
        OSReport("m422:wrong player group\n");
        temp_r31->unk04 = temp_r31->unk00;
    }
    temp_r31->unk08 = GWPlayerCfg[temp_r31->unk04].character;
    temp_r31->unk0C = (GWPlayerCfg[temp_r31->unk04].iscom ? -1 : GWPlayerCfg[temp_r31->unk04].pad_idx);
    temp_r31->unk10 = (temp_r31->unk0C != -1) ? 0 : GWPlayerCfg[temp_r31->unk04].diff;
    temp_r31->unk14 = rand8();
    temp_r31->unk20 = 0;
    arg0->model[0] = CharModelCreate(temp_r31->unk08, temp_r31->unk00 == 0 ? 2 : 2);
    Hu3DModelLayerSet(arg0->model[0], 1);
    Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(arg0->model[0], 1);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M422, 50));
    Hu3DModelPosSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelLayerSet(arg0->model[1], 0);
    temp_r31->unk18 = 0;
    temp_r31->unk1C = -1;
    for (i = 0; i < 8; i++) {
        arg0->motion[i] = CharModelMotionCreate(temp_r31->unk08, lbl_1_data_A0[i] + (lbl_1_data_C0[i] != 0 ? temp_r31->unk08 : 0));
    }
    CharModelVoiceEnableSet(temp_r31->unk08, arg0->motion[6], 0);
    Hu3DMotionSet(arg0->model[0], arg0->motion[3]);
    arg0->trans.x = lbl_1_data_18B4[temp_r31->unk00][0];
    arg0->trans.y = lbl_1_data_18B4[temp_r31->unk00][1];
    arg0->trans.z = lbl_1_data_18B4[temp_r31->unk00][2];
    arg0->rot.y = lbl_1_data_18B4[temp_r31->unk00][3];
    arg0->scale.x = arg0->scale.y = arg0->scale.z = 1.0f;
    arg0->rot.x = arg0->rot.z = 0.0f;
    arg0->func = fn_1_2FC;
}

void fn_1_B004(omObjData *arg0)
{
    lbl_1_bss_34 = 1000;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    arg0->func = fn_1_89E0;
}

void ObjectSetup(void)
{
    omObjData *var_r30;
    s32 i;

    OSReport("******* M422 ObjectSetup *********\n");
    HuAudSndGrpSet(47);
    lbl_1_bss_30 = omInitObjMan(600, 0x2000);
    omGameSysInit(lbl_1_bss_30);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    CZoom = 1676.6f;
    Center.x = 690.0f;
    Center.y = 1340.0f;
    Center.z = 1380.0f;
    CRot.x = -50.8125f;
    CRot.y = 40.0f;
    CRot.z = 0.0f;
    CZoom = 2126.6f;
    Center.x = 700.0f;
    Center.y = 870.0f;
    Center.z = 1320.0f;
    CRot.x = -37.25f;
    CRot.y = 40.0f;
    CRot.z = 0.0f;
    {
        Vec sp18 = { -822.5f, 6743.0f, 4625.5f };
        Vec spC = { 0.1545085f, -0.788462f, -0.5850064f };
        GXColor sp8 = { 0xFF, 0xFF, 0xFF, 0xFF };

        lbl_1_bss_24 = Hu3DGLightCreateV(&sp18, &spC, &sp8);
    }
    Hu3DGLightStaticSet(lbl_1_bss_24, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_24);
    lbl_1_bss_2E = -1;
    lbl_1_bss_20 = -1;
    lbl_1_bss_38 = omAddObjEx(lbl_1_bss_30, 101, 103, 34, 1, fn_1_9900);
    for (i = 0; i < 4; i++) {
        var_r30 = lbl_1_bss_3C[i] = omAddObjEx(lbl_1_bss_30, 100, 2, 8, 0, fn_1_AC4C);
        var_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(StructBss3CData), MEMORY_DEFAULT_NUM);
        var_r30->work[0] = i;
    }
    lbl_1_bss_4C = omAddObjEx(lbl_1_bss_30, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_50 = omAddObjEx(lbl_1_bss_30, 102, 0, 0, -1, fn_1_B004);
}

void fn_1_B480(omObjData *arg0)
{
    StructBss3CData *var_r30;
    s32 i;

    if (WipeStatGet() == 0) {
        for (i = 0; i < 4; i++) {
            var_r30 = lbl_1_bss_3C[i]->data;
            CharModelKill(var_r30->unk08);
        }
        if (lbl_1_bss_2E >= 0) {
            MGSeqKill(lbl_1_bss_2E);
        }
        MGSeqKillAll();
        HuAudAllStop();
        omOvlReturnEx(1, 1);
    }
}
