#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/esprite.h"
#include "game/flag.h"
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
#include "game/window.h"
#include "game/wipe.h"
#include "string.h"

extern s32 rand8(void);

typedef struct UnkCameraStruct {
    /* 0x00 */ float unk_00;
    /* 0x04 */ float unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
} UnkCameraStruct; /* size = 0x18 */

typedef struct UnkBssCCStruct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ float unk_04[3];
} UnkBssCCStruct; /* size = 0x10 */

typedef struct UnkBss28CStruct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkBss28CStruct; /* size = 0x10 */

typedef struct UnkData114Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ float unk_0C;
    /* 0x10 */ float unk_10;
    /* 0x14 */ float unk_14;
} UnkData114Struct; /* size = 0x18 */

typedef struct M458DllWork {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    float unk_28;
    float unk_2C;
    char unk30[4];
    float unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
} M458DllWork; /* size = 0x44 */

s16 fn_1_4BE8();
void fn_1_6D9C(omObjData *arg0);

s32 lbl_1_data_0[2] = { 0x570025, 0x570026 };
s32 lbl_1_data_8[2] = { 0, 0 };
s32 lbl_1_data_10[0xA] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x03),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x06),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x36),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x2F),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x1A),
    0x570000,
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
};
u32 lbl_1_data_38[0xA] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
u32 lbl_1_data_60[0xA] = { 0x30008, 0, 0, 0x3000A, 0, 0, 0x57002A, 0x570028, 0x570029, 0x570027 };
u8 lbl_1_data_88[0xA] = { 0, 0, 0, 1, 1, 1, 1, 0, 1, 1 };
u8 lbl_1_data_92[0xA] = { 0, 0, 0, 1, 1, 1, 1, 0, 1, 1 };
s32 lbl_1_data_9C[0xA] = { 8, 8, 8, 0, 0, 0, 8, 8, 8, 8 };
s32 lbl_1_data_C4[0xA] = { 0, 0, 0, 0, 3, 0, 0, 0, 0, 0 };
s32 lbl_1_data_EC[0xA] = { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };
UnkData114Struct lbl_1_data_114 = { 0, 0, 0.0f, 0.0f, 0.0f, 0.0f };
s16 lbl_1_data_12C = -1;
s16 lbl_1_data_12E = -1;
s32 lbl_1_data_130 = -1;
s32 lbl_1_data_134 = -1;
s16 lbl_1_data_138[0x12] = {
    -1,
    0,
    -0x3D4C,
    0,
    0,
    0,
    0x4403,
    0x4000,
    0x4334,
    0,
    0x42B4,
    0,
    0,
    0,
    0x4403,
    0x4000,
    0x4334,
    0,
};
s32 lbl_1_data_15C = -1;

UnkBss28CStruct lbl_1_bss_28C[9];
UnkBssCCStruct lbl_1_bss_CC[0x1C];
omObjData *lbl_1_bss_C8;
omObjData *lbl_1_bss_C4;
omObjData *lbl_1_bss_BC[2];
omObjData *lbl_1_bss_B8;
s32 lbl_1_bss_B4;
s32 lbl_1_bss_B0;
s32 lbl_1_bss_AC;
s32 lbl_1_bss_A8;
s32 lbl_1_bss_A4;
Process *lbl_1_bss_A0;
s32 lbl_1_bss_9C;
s32 lbl_1_bss_98;
s32 lbl_1_bss_94;
s32 lbl_1_bss_90;
s32 lbl_1_bss_8C;
HsfanimStruct00 lbl_1_bss_3C;
float lbl_1_bss_38;
float lbl_1_bss_34;
float lbl_1_bss_30;
float lbl_1_bss_2C;
float lbl_1_bss_28;
s32 lbl_1_bss_24;
s32 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
s16 lbl_1_bss_C;
s32 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

void fn_1_A0(void)
{
    if ((HuPadBtnDown[0] & PAD_BUTTON_B) != 0) {
        Center.x = lbl_1_bss_BC[0]->trans.x;
        Center.y = lbl_1_bss_BC[0]->trans.y;
        Center.z = lbl_1_bss_BC[0]->trans.z;
    }
    Center.x += 10.0 * (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) - ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0));
    Center.z -= 10.0 * (((HuPadBtn[0] & PAD_BUTTON_UP) != 0) - ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0));
    Center.y += (30.0 * ((HuPadTrigL[0] - HuPadTrigR[0]) / 128.0));
    CZoom += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_X) != 0) - ((HuPadBtn[0] & PAD_BUTTON_Y) != 0));
    CRot.y += HuPadSubStkX[0] / 16.0;
    CRot.x += HuPadSubStkY[0] / -16.0;
    print8(0x40, 0x188, 1.0f, "%f,%f,%f", Center.x, Center.y, Center.z);
    print8(0x40, 0x198, 1.0f, "%f,%f,%f", CRot.x, CRot.y, CRot.z);
    print8(0x40, 0x1A8, 1.0f, "%f", CZoom);
}

s32 lbl_1_data_16C = -1;

void fn_1_4C8(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f20;

    M458DllWork *var_r31;
    ModelData *var_r29;
    s16 var_r28;
    M458DllWork *var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    ModelData *var_r23;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;
    s32 var_r18;
    s32 var_r17;

    Mtx sp1E0;
    float sp1A8[2];
    float sp1A0[2];
    s32 spD0;
    s32 spCC;
    s32 spC8;
    s32 spC4;
    s32 spC0;
    float spBC;
    s32 spB8;
    ModelData *spB4;
    float spB0;
    float spAC;
    s32 spA8;
    s32 spA4;

    var_r31 = object->data;
    var_r27 = lbl_1_bss_BC[1 - object->work[0]]->data;
    var_f23 = 0.0f;
    var_f22 = 0.0f;
    var_f28 = 0.0f;
    var_r22 = 0;
    var_r28 = -1;
    var_r31->unk_2C = var_r31->unk_34 = 0.0f;
    if ((lbl_1_bss_B0 == (var_r31->unk_00 == 0 ? 0x3F1 : 0x3F2)) && (var_r31->unk_18 == 3) && (var_r31->unk_1C >= 0x168)) {
        if (var_r31->unk_1C == 0x168) {
            var_r31->unk_14 = rand8() % 15;
        }
        if (var_r31->unk_0C != -1) {
            var_r22 = (HuPadBtnDown[var_r31->unk_0C] & 0x100) != 0 ? 1 : 0;
        }
        else {
            var_r31->unk_14 += var_r31->unk_14 < 0x10000;
            if (var_r31->unk_14 == 0x1E) {
                var_r22 = 1;
            }
        }
    }
    if (lbl_1_bss_B0 == (var_r31->unk_00 == 0 ? 0x3ED : 0x3EF)) {
        var_r25 = 0;
        var_r24 = 0;
        if (var_r31->unk_0C != -1) {
            var_r25 = HuPadStkX[var_r31->unk_0C] < -0x14 ? -1 : (HuPadStkX[var_r31->unk_0C] > 0x14 ? 1 : 0);
            var_r24 = -HuPadStkY[var_r31->unk_0C] < -0x14 ? -1 : (-HuPadStkY[var_r31->unk_0C] > 0x14 ? 1 : 0);
            var_r22 = (HuPadBtnDown[var_r31->unk_0C] & 0x100) != 0 ? 1 : 0;
        }
        else {
            var_r31->unk_14 += var_r31->unk_14 < 0x10000;
            if (var_r31->unk_14 == 0x1E) {
                lbl_1_bss_94 = rand8() % (var_r31->unk_00 + 2);
                lbl_1_bss_90 = rand8() % (var_r31->unk_00 + 2);
            }
            if (fabs((500.0 * var_r31->unk_3C) - object->trans.x) < 10.0) {
                var_r25 = lbl_1_bss_94 > 0 ? (var_r31->unk_00 == 0 ? (((rand8() % 2) * 2) - 1) : -1) : 0;
                lbl_1_bss_94 -= lbl_1_bss_94 > 0;
            }
            if (fabs((500.0 * var_r31->unk_40) - object->trans.z) < 10.0) {
                var_r24 = lbl_1_bss_90 > 0 ? (var_r31->unk_00 == 0 ? (((rand8() % 2) * 2) - 1) : -1) : 0;
                lbl_1_bss_90 -= lbl_1_bss_90 > 0;
            }
            if ((var_r31->unk_14 >= 0x2D) && ((var_r31->unk_14 % 30) == 0xF) && (lbl_1_bss_94 == 0) && (lbl_1_bss_90 == 0)) {
                var_r22 = 1;
            }
        }
        if (lbl_1_bss_B4 >= 0x32) {
            var_r25 = var_r24 = 0;
        }
        if (var_r31->unk_00 == 1) {
            spC4 = 0;
            spC0 = 0;
            if (fabs((500.0 * var_r31->unk_3C) - object->trans.x) < 10.0) {
                var_r17 = spD0 = object->trans.x < -250.0 ? -1 : (object->trans.x > 250.0 ? 1 : 0);
            }
            else {
                var_r17 = (object->trans.x < 0.0f ? -1 : 0);
                spD0 = var_r17 + 1;
            }
            if (fabs((500.0 * var_r31->unk_40) - object->trans.z) < 10.0) {
                spCC = spC8 = object->trans.z < -250.0 ? -1 : (object->trans.z > 250.0 ? 1 : 0);
            }
            else {
                spCC = object->trans.z < 0.0f ? -1 : 0;
                spC8 = spCC + 1;
            }
            for (var_r21 = var_r17; var_r21 <= spD0; var_r21++) {
                for (var_r20 = spCC; var_r20 <= spC8; var_r20++) {
                    if (var_r27->unk_38 == 1 + var_r21 + var_r25 + (1 + var_r20 + var_r24) * 3) {
                        var_r25 = var_r24 = 0;
                    }
                    if (var_r27->unk_38 == 1 + var_r21 + var_r25 + (var_r20 + 1) * 3) {
                        var_r25 = 0;
                    }
                    if (var_r27->unk_38 == 1 + var_r21 + (1 + var_r20 + var_r24) * 3) {
                        var_r24 = 0;
                    }
                }
            }
        }
        if ((var_r25 * ((500.0 * var_r31->unk_3C) - object->trans.x)) < 0.0) {
            var_r31->unk_3C = var_r31->unk_3C + var_r25;
        }
        if ((fabs((500.0 * var_r31->unk_3C) - object->trans.x) < 10.0) && (var_r25 != 0) && ((var_r31->unk_3C + var_r25) >= -1)
            && ((var_r31->unk_3C + var_r25) <= 1)) {
            var_r31->unk_3C = var_r31->unk_3C + var_r25;
        }
        var_f23 = (((500.0 * var_r31->unk_3C) - object->trans.x) / 0.25) / 1.75;
        if ((var_r24 * ((500.0 * var_r31->unk_40) - object->trans.z)) < 0.0) {
            var_r31->unk_40 = var_r31->unk_40 + var_r24;
        }
        if ((fabs((500.0 * var_r31->unk_40) - object->trans.z) < 10.0) && (var_r24 != 0) && ((var_r31->unk_40 + var_r24) >= -1)
            && ((var_r31->unk_40 + var_r24) <= 1)) {
            var_r31->unk_40 = var_r31->unk_40 + var_r24;
        }
        var_f22 = (((500.0 * var_r31->unk_40) - object->trans.z) / -0.25) / 1.75;
    }
    if (((var_r31->unk_00 != 1) || (var_r31->unk_08 != -1)) && (var_r31->unk_18 == 0)) {
        if ((lbl_1_bss_B0 > (var_r31->unk_00 == 0 ? 0x3E9 : 0x3EE)) && (lbl_1_bss_B0 < 0x3F3)) {
            var_f31 = 0.25 * var_f23;
            var_f30 = 0.25 * -var_f22;
            {
                Vec sp1B0 = { 0.0f, 0.0f, 0.0f };
                sp1B0.x = var_f31;
                sp1B0.z = var_f30;
                MTXRotRad(sp1E0, 0x79, 0.017453292f * CRot.y);
                MTXMultVec(sp1E0, &sp1B0, &sp1B0);
                var_f31 = sp1B0.x;
                var_f30 = sp1B0.z;
            }
            var_f28 = sqrtf((var_f31 * var_f31) + (var_f30 * var_f30));
            if (var_f28 >= 0.5f) {
                if (var_f28 < 10.0f) {
                    var_r31->unk_2C = var_f31;
                    var_r31->unk_34 += var_f30;
                }
                else {
                    var_f31 = var_f31 / var_f28;
                    var_f30 = var_f30 / var_f28;
                    var_f28 = 10.0f;
                    var_r31->unk_2C = var_f31 * var_f28;
                    var_r31->unk_34 = var_f30 * var_f28;
                }
                var_r31->unk_28 = var_f28;
                object->rot.y = atan2d(var_r31->unk_2C, var_r31->unk_34);
                if (var_r31->unk_28 >= 8.0f) {
                    var_r28 = 2;
                }
                else {
                    var_r28 = 2;
                }
            }
            else {
                var_r28 = 0;
            }
        }
    }
    object->trans.x += 1.75f * var_r31->unk_2C;
    object->trans.z += 1.75f * var_r31->unk_34;
    switch (lbl_1_bss_B0) {
        case 0x3E9:
        case 0x3EE:
            if (lbl_1_bss_B0 == (var_r31->unk_00 == 0 ? 0x3E9 : 0x3EE)) {
                if (lbl_1_bss_B4 == 0) {
                    Hu3DModelAttrReset(object->model[0], HU3D_ATTR_DISPOFF);
                    if (var_r31->unk_00 == 0) {
                        object->trans.x = 0.0f;
                        object->trans.z = 0.0f;
                    }
                    else if (var_r31->unk_08 != -1) {
                        var_r31->unk_3C = -2;
                        for (var_r18 = 2; var_r18 >= 0; var_r18--) {
                            for (var_r19 = 2; var_r19 >= 0; var_r19--) {
                                if (var_r27->unk_38 != (var_r18 + (var_r19 * 3))) {
                                    var_r31->unk_3C = var_r19 - 1;
                                    var_r31->unk_40 = var_r18 - 1;
                                    object->trans.x = 500.0 * var_r31->unk_3C;
                                    object->trans.z = 500.0 * var_r31->unk_40;
                                    break;
                                }
                            }
                            if (var_r31->unk_3C != -2) {
                                break;
                            }
                        }
                    }
                    else {
                        do {
                            var_r31->unk_38 = rand8() % 9;
                        } while (var_r27->unk_38 == var_r31->unk_38);
                        var_r31->unk_3C = (var_r31->unk_38 % 3) - 1;
                        var_r31->unk_40 = (var_r31->unk_38 / 3) - 1;
                        object->trans.x = 500.0 * var_r31->unk_3C;
                        object->trans.z = 500.0 * var_r31->unk_40;
                    }
                }
                if (lbl_1_bss_B4 <= 0x1E) {
                    if (var_r31->unk_08 == -1) {
                        Hu3DMotionTimeSet(object->model[0], 138.0f);
                    }
                    object->trans.y = 2400.0 * (1.0 - (lbl_1_bss_B4 / 30.0));
                }
                if ((var_r31->unk_08 != -1) && (lbl_1_bss_B4 == 0x1E)) {
                    var_r28 = 4;
                }
                if (lbl_1_bss_B4 == ((var_r31->unk_08 != -1 ? 0xA : 0x3C) + 0x1E)) {
                    var_r28 = 0;
                }
                if (lbl_1_bss_B4 == 0x1E) {
                    lbl_1_data_114.unk_04 += 0x32;
                }
                if (lbl_1_bss_B4 == 0x1E) {
                    HuAudFXPlay(0x33D);
                }
            }
            break;
        case 0x3EB:
            if ((lbl_1_bss_B4 == 0) && (var_r31->unk_00 == 0)) {
                var_r31->unk_18 = 1;
                var_r31->unk_1C = 0;
            }
            break;
        case 0x3ED:
        case 0x3EF:
            if (lbl_1_bss_B0 == (var_r31->unk_00 == 0 ? 0x3ED : 0x3EF)) {
                if (lbl_1_bss_B4 == 0) {
                    lbl_1_bss_0 = 0x12C;
                    lbl_1_data_12E = MGSeqCreate(1, 0xA, -1, -1);
                    HuWinMesMaxSizeGet(1, sp1A8, MAKE_MESSID(0x28, 0x19));
                    lbl_1_bss_C = HuWinCreate(-10000.0f, 400.0f, sp1A8[0], sp1A8[1], 1);
                    HuWinBGTPLvlSet(lbl_1_bss_C, 0.0f);
                    HuWinMesSpeedSet(lbl_1_bss_C, 0);
                    HuWinMesSet(lbl_1_bss_C, MAKE_MESSID(0x28, 0x19));
                }
                if (lbl_1_data_12E != -1) {
                    MGSeqParamSet(lbl_1_data_12E, 1, (lbl_1_bss_0 + 0x3A) / 60);
                }
                lbl_1_bss_0--;
                if ((var_r22 != 0) || (lbl_1_bss_0 == 0)) {
                    lbl_1_bss_B4 = 0x32;
                    MGSeqKill(lbl_1_data_12E);
                    lbl_1_data_12E = -1;
                    HuWinExCleanup(lbl_1_bss_C);
                }
                if (lbl_1_bss_B4 == 0x32) {
                    if (fabs((500.0 * var_r31->unk_3C) - object->trans.x) < 1.0) {
                        if (fabs((500.0 * var_r31->unk_40) - object->trans.z) < 1.0) {
                            lbl_1_bss_B4 = 0x3C;
                            object->rot.y = 0.0f;
                            var_r31->unk_38 = 1 + var_r31->unk_3C + ((var_r31->unk_40 + 1) * 3);
                        }
                    }
                }
            }
            break;
        case 0x3F1:
        case 0x3F2:
            if ((lbl_1_bss_B0 == (var_r31->unk_00 == 0 ? 0x3F1 : 0x3F2)) && (lbl_1_bss_B4 == 0) && (var_r31->unk_08 != -1)) {
                HuWinMesMaxSizeGet(1, sp1A0, MAKE_MESSID(0x30, 0x25));
                lbl_1_bss_C = HuWinCreate(-10000.0f, 400.0f, sp1A0[0], sp1A0[1], 1);
                HuWinBGTPLvlSet(lbl_1_bss_C, 0.0f);
                HuWinMesSpeedSet(lbl_1_bss_C, 0);
                HuWinMesSet(lbl_1_bss_C, MAKE_MESSID(0x30, 0x25));
            }
            break;
        case 0x3F3:
            if (lbl_1_bss_98 != var_r31->unk_00) {
                if (lbl_1_bss_B4 == 1) {
                    var_r28 = 7;
                }
                if (lbl_1_bss_B4 == 0x78) {
                    Hu3DModelAttrReset(lbl_1_bss_B8->model[var_r31->unk_38 + 4], HU3D_MOTATTR_PAUSE);
                    if (lbl_1_bss_CC[0].unk_00 < 3) {
                        lbl_1_bss_CC[0].unk_04[lbl_1_bss_CC[0].unk_00] = 0.0f;
                        lbl_1_bss_CC[0].unk_00++;
                    }
                }
                if (lbl_1_bss_B4 == 0x99) {
                    Hu3DModelAttrSet(lbl_1_bss_B8->model[var_r31->unk_38 + 4], HU3D_MOTATTR_PAUSE);
                }
                if (lbl_1_bss_B4 == 0xB7) {
                    Hu3DModelAttrReset(lbl_1_bss_B8->model[var_r31->unk_38 + 4], HU3D_MOTATTR_PAUSE);
                }
                if ((lbl_1_bss_B4 == 0xBC) && (lbl_1_bss_CC[1].unk_00 < 3)) {
                    lbl_1_bss_CC[1].unk_04[lbl_1_bss_CC[1].unk_00] = 0.0f;
                    lbl_1_bss_CC[1].unk_00++;
                }
                if (lbl_1_bss_B4 == 0xD2) {
                    var_r28 = 8;
                    espAttrReset(lbl_1_data_8[1], HUSPR_ATTR_DISPOFF);
                    if (lbl_1_bss_CC[(var_r31->unk_08 != -1 ? var_r31->unk_08 : 8) + 2].unk_00 < 3) {
                        lbl_1_bss_CC[(var_r31->unk_08 != -1 ? var_r31->unk_08 : 8) + 2]
                            .unk_04[lbl_1_bss_CC[(var_r31->unk_08 != -1 ? var_r31->unk_08 : 8) + 2].unk_00]
                            = 0.0f;
                        lbl_1_bss_CC[(var_r31->unk_08 != -1 ? var_r31->unk_08 : 8) + 2].unk_00++;
                    }
                    if (lbl_1_data_130 != -1) {
                        HuAudSeqFadeOut(lbl_1_data_130, 0x64);
                        lbl_1_data_130 = -1;
                    }
                }
                if ((lbl_1_bss_B4 >= 0xD2) && (lbl_1_bss_B4 <= 0xD6)) {
                    s32 sp1BC[9] = { 0, -12, -36, 0, 0, -12, -36, -48, 0 };
                    spBC = (lbl_1_bss_B4 - 0xD2) / 4.0;
                    var_f26 = (lbl_1_bss_B4 - 0xD2) / 4.0;
                    var_f26 = var_f26 > 1.0f ? 1.0f : var_f26;
                    espPosSet(lbl_1_data_8[1], 290.0f, (64.0f * (1.0f - spBC)) + (sp1BC[(var_r31->unk_08 != -1 ? var_r31->unk_08 : 8)] + 0x8C));
                    espScaleSet(lbl_1_data_8[1], var_f26, var_f26);
                }
                if (lbl_1_bss_B4 == 0x10E) {
                    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
                    espAttrSet(lbl_1_data_8[1], HUSPR_ATTR_DISPOFF);
                }
                if (lbl_1_bss_B4 == 0x122) {
                    spB8 = HuAudFXPlay((var_r31->unk_08 != -1 ? var_r31->unk_08 : 8) + 0x800);
                    HuAudFXFadeOut(spB8, 0x9C4);
                }
                if (lbl_1_bss_B4 >= 0x13B) {
                    object->trans.y -= 77.0f;
                }
            }
            else if ((lbl_1_bss_B4 == 0x3C) && (lbl_1_data_138[0] != -1)) {
                Hu3DParManKill(lbl_1_data_138[0]);
                lbl_1_data_138[0] = -1;
            }
            break;
        case 0x3F4:
            if (var_r31->unk_00 == lbl_1_bss_98) {
                if ((lbl_1_bss_B4 == 1) && (var_r31->unk_08 == -1)) {
                    HuAudFXPlay(0x3A);
                }
                var_r28 = 9;
            }
            break;
    }
    switch (var_r31->unk_18) {
        case 0:
            var_r31->unk_1C++;
            break;
        case 1:
            var_r31->unk_1C++;
            if (var_r31->unk_1C <= 0x3C) {
                var_r28 = 5;
                object->rot.y = -180.0 * (var_r31->unk_1C / 60.0);
            }
            else {
                Hu3DMotionTimeSet(object->model[0], 120.0f);
                var_r28 = 0;
                var_r31->unk_18 = 0;
                var_r31->unk_1C = 0;
            }
            break;
        case 2:
            var_r31->unk_1C++;
            break;
        case 3:
            if (var_r31->unk_1C == 0) {
                lbl_1_data_15C = 6;
            }
            if (var_r31->unk_1C < 0x168) {
                var_r23 = &Hu3DData[lbl_1_bss_B8->model[3]];
                if (var_r31->unk_1C == 0) {
                    Hu3DModelAttrReset(lbl_1_bss_B8->model[3], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(lbl_1_bss_B8->model[3], object->trans.x, 625.0f + object->trans.y, object->trans.z);
                    Hu3DModelScaleSet(lbl_1_bss_B8->model[3], 0.1f, 0.1f, 0.1f);
                    Hu3DModelTPLvlSet(lbl_1_bss_B8->model[3], 1.0f);
                    lbl_1_bss_1C = 0;
                    HuAudFXPlay(0x7F4);
                    lbl_1_data_16C = HuAudFXPlay(0x7F3);
                }
                var_r23->rot.y = lbl_1_bss_1C % 360;
                lbl_1_bss_1C += 0x19;
                if (var_r31->unk_1C < 0xB4) {
                    var_f20 = 0.0f;
                    var_f21 = 1.0f;
                }
                else {
                    var_f20 = 1.0f;
                    var_f21 = 0.5f;
                }
                var_r23->scale.x = var_f20 + (var_f21 * sind((float)(var_r31->unk_1C % 180)));
                var_r23->scale.y = var_r23->scale.z = var_r23->scale.x;
                if (var_r31->unk_1C < 0xB4) {
                    var_r31->unk_1C += 6;
                }
                else {
                    var_r31->unk_1C = var_r31->unk_1C + 0x12;
                }
                if (var_r31->unk_1C >= 0x168) {
                    var_r31->unk_1C = 0x168;
                    Hu3DModelRotSet(lbl_1_bss_B8->model[3], 0.0f, 0.0f, 0.0f);
                }
            }
            else {
                spB4 = &Hu3DData[lbl_1_bss_B8->model[3]];
                var_r31->unk_1C = var_r31->unk_1C + 4;
                if (var_r31->unk_1C > 0x2D0) {
                    var_r31->unk_1C -= 0x168;
                }
                spB4->pos.y += (0.20000000298023224 * sind((var_r31->unk_1C - 0x168)));
                if (var_r22 != 0) {
                    lbl_1_bss_B4 = 0x32;
                    var_r31->unk_18 = 4;
                    var_r31->unk_1C = 0;
                    var_r28 = 6;
                }
            }
            break;
        case 4:
            var_r31->unk_1C++;
            if (var_r31->unk_1C >= 0x1B) {
                var_r29 = &Hu3DData[lbl_1_bss_B8->model[3]];
                var_r26 = var_r31->unk_1C - 0x1B;
                if (var_r26 == 0) {
                    if (var_r31->unk_04 != -1) {
                        omVibrate(var_r31->unk_04, 0xC, 4, 2);
                    }
                    HuWinExCleanup(lbl_1_bss_C);
                    lbl_1_data_15C = -1;
                    if (lbl_1_data_16C != -1) {
                        HuAudFXStop(lbl_1_data_16C);
                        lbl_1_data_16C = -1;
                    }
                    HuAudFXPlay(0x7F5);
                }
                if (var_r26 == 8) {
                    if (lbl_1_data_138[0] == -1) {
                        lbl_1_data_138[0] = fn_1_4BE8();
                        Hu3DParManPosSet(lbl_1_data_138[0], var_r29->pos.x, var_r29->pos.y, var_r29->pos.z);
                    }
                    Hu3DModelAttrSet(lbl_1_bss_B8->model[3], HU3D_ATTR_DISPOFF);
                }
                else if (var_r26 > 8) {
                    if (var_r31->unk_20 == 6) {
                        if (Hu3DMotionTimeGet(object->model[0]) >= Hu3DMotionMaxTimeGet(object->model[0])) {
                            var_r28 = 0;
                        }
                    }
                    if (var_r26 <= 0x1C) {
                        var_f27 = (var_r26 - 8) / 10.0;
                        spB0 = ((var_r26 - 8) * 0x12);
                        var_f27 = var_f27 > 1.0f ? 2.5 : 2.5 * var_f27;
                        Hu3DModelAttrReset(lbl_1_bss_B8->model[lbl_1_bss_18 + 0xD], HU3D_ATTR_DISPOFF);
                        Hu3DModelPosSet(lbl_1_bss_B8->model[lbl_1_bss_18 + 0xD], var_r29->pos.x, var_r29->pos.y, var_r29->pos.z);
                        Hu3DModelScaleSet(lbl_1_bss_B8->model[lbl_1_bss_18 + 0xD], var_f27, var_f27, var_f27);
                    }
                    if ((var_r26 >= 0x2D) && (var_r26 <= 0x41)) {
                        var_f25 = (var_r26 - 0x2D) / 5.0;
                        spAC = (var_r26 - 0x2D) * 0x12;
                        var_f25 = var_f25 > 1.0f ? 1.0f : var_f25;
                        var_f25 = 0.0;
                        Hu3DModelAttrReset(lbl_1_bss_B8->model[lbl_1_bss_18 + 0xD], HU3D_ATTR_DISPOFF);
                        Hu3DModelPosSet(lbl_1_bss_B8->model[lbl_1_bss_18 + 0xD], var_r29->pos.x, var_r29->pos.y - (30.0f * var_f25), var_r29->pos.z);
                        var_r31->unk_1C += 5;
                    }
                    if (var_r26 == 0x62) {
                        Hu3DModelAttrSet(lbl_1_bss_B8->model[lbl_1_bss_18 + 0xD], HU3D_ATTR_DISPOFF);
                        lbl_1_bss_18 = lbl_1_bss_18 >= 9 ? var_r27->unk_38 : lbl_1_bss_18;
                        if (lbl_1_bss_18 == var_r27->unk_38) {
                            lbl_1_bss_98 = var_r31->unk_00;
                        }
                        else if (lbl_1_bss_18 == var_r31->unk_38) {
                            lbl_1_bss_98 = var_r27->unk_00;
                        }
                        var_r31->unk_18 = lbl_1_bss_98 == -1 ? 5 : 0;
                        var_r31->unk_1C = 0;
                    }
                }
                else {
                    if (var_r26 < 4) {
                        var_r29->pos.y += 10.0f + (0.5f * var_r26);
                        var_r29->scale.x += 0.10000000149011612 * sind((4.0f * var_r26));
                        var_r29->scale.y = var_r29->scale.z = var_r29->scale.x;
                    }
                    else {
                        var_f24 = (0xFF - (var_r26 << 5));
                        var_f24 = var_f24 * 0.003921569f; // 1 / 255
                        Hu3DModelTPLvlSet(lbl_1_bss_B8->model[3], var_f24);
                    }
                    var_r29->pos.y += -0.49f * var_r26 * var_r26;
                }
            }
            break;
        case 5:
            if (var_r31->unk_1C == 0) {
                Hu3DModelAttrReset(lbl_1_bss_B8->model[lbl_1_bss_18 + 4], HU3D_MOTATTR_PAUSE);
                lbl_1_bss_28C[lbl_1_bss_18].unk_0C = 0;
                if (lbl_1_bss_CC[0].unk_00 < 3) {
                    lbl_1_bss_CC[0].unk_04[lbl_1_bss_CC->unk_00] = 0.0f;
                    lbl_1_bss_CC[0].unk_00++;
                }
            }
            var_r31->unk_1C++;
            if ((var_r31->unk_1C == 0x3C) && (*lbl_1_data_138 != -1)) {
                Hu3DParManKill(*lbl_1_data_138);
                lbl_1_data_138[0] = -1;
            }
            if (var_r31->unk_1C == 0x21) {
                Hu3DModelAttrSet(lbl_1_bss_B8->model[lbl_1_bss_18 + 4], HU3D_MOTATTR_PAUSE);
            }
            if (var_r31->unk_1C == 0x3F) {
                Hu3DModelAttrReset(lbl_1_bss_B8->model[lbl_1_bss_18 + 4], HU3D_MOTATTR_PAUSE);
            }
            if ((var_r31->unk_1C == 0x44) && (lbl_1_bss_CC[1].unk_00 < 3)) {
                lbl_1_bss_CC[1].unk_04[lbl_1_bss_CC[1].unk_00] = 0.0f;
                lbl_1_bss_CC[1].unk_00++;
            }
            if (var_r31->unk_1C == 0x82) {
                var_r31->unk_18 = 0;
                var_r31->unk_1C = 0;
            }
            break;
    }
    if (((var_r31->unk_18 == 3) || (var_r31->unk_18 == 4)) && (lbl_1_data_15C >= 0)) {
        lbl_1_data_15C++;
        if (lbl_1_data_15C >= 6) {
            spA4 = lbl_1_bss_18;
            for (spA8 = 0; spA8 < 0x32; spA8++) {
                do {
                    lbl_1_bss_18 = rand8() % 11;
                } while ((lbl_1_bss_18 >= 9 && lbl_1_bss_18 == var_r31->unk_00 + 9) || (lbl_1_bss_18 < 9 && lbl_1_bss_28C[lbl_1_bss_18].unk_0C == 0));
                if (spA4 != lbl_1_bss_18) {
                    break;
                }
            }
            spA4 = lbl_1_bss_18 >= 9 ? (var_r27->unk_08 == -1 ? 0x11 : (var_r27->unk_08 + 9)) : lbl_1_bss_18;
            lbl_1_data_15C = 0;
            Hu3DMotionTimeSet(lbl_1_bss_B8->model[3], 0.5 + spA4);
        }
    }
    if (var_r31->unk_24 >= 0) {
        var_r28 = var_r31->unk_24;
    }
    if ((var_r28 >= 0) && (var_r28 != var_r31->unk_20)) {
        Hu3DMotionShiftSet(object->model[0], object->motion[var_r28], lbl_1_data_C4[var_r28],
            (var_r31->unk_08 != -1 ? lbl_1_data_9C[var_r28] : lbl_1_data_EC[var_r28]),
            (var_r28 == 8                                                                            ? 0x40000002
                    : (var_r31->unk_08 != -1 ? lbl_1_data_88[var_r28] : lbl_1_data_92[var_r28]) != 0 ? 0
                                                                                                     : 0x40000001));
        var_r31->unk_20 = var_r28;
    }
}

s32 lbl_1_data_1A0 = -1;
float lbl_1_data_1A4 = 3500.0f;
float lbl_1_data_1A8 = 100.0f;
float lbl_1_data_1AC = -59.0f;

void fn_1_350C(omObjData *var_r27)
{
    M458DllWork *spC[2];
    float var_f31;
    float var_f29;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f19;

    s32 var_r31;
    s32 var_r30;
    ModelData *var_r29;
    ModelData *var_r28;
    ModelData *var_r26;
    s32 var_r25;

    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        spC[var_r31] = lbl_1_bss_BC[var_r31]->data;
    }
    lbl_1_bss_4++;
    switch (lbl_1_bss_B0) {
        case 0x3EA:
            if (lbl_1_bss_B4 <= 0x77) {
                var_f27 = lbl_1_bss_B4 / 119.0;
                var_f27 = var_f27 > 1.0f ? 1.0f : var_f27;
                Hu3DModelPosSet(lbl_1_bss_B8->model[2], 0.0f, 100.0f + (-1500.0f * (1.0f - var_f27)), -950.0f);
                Hu3DModelAttrReset(lbl_1_bss_B8->model[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_B8->model[2], HU3D_ATTR_DISPOFF);
            }
            break;
        case 0x3EB:
            if (lbl_1_bss_B4 == 0) {
                lbl_1_bss_8C = 0;
            }
            if (lbl_1_bss_B4 == 0x14) {
                espAttrReset(lbl_1_data_8[0], HUSPR_ATTR_DISPOFF);
            }
            if (((lbl_1_bss_B4 >= 0x14) && (lbl_1_bss_B4 <= 0x32)) || ((lbl_1_bss_B4 >= 0xB4) && (lbl_1_bss_B4 <= 0xD2))) {
                var_f19 = lbl_1_bss_B4 <= 0x78 ? ((lbl_1_bss_B4 - 0x14) / 30.0) : (1.0 - ((lbl_1_bss_B4 - 0xB4) / 30.0));
                espTPLvlSet(lbl_1_data_8[0], var_f19);
            }
            if (lbl_1_bss_B4 == 0xD2) {
                espAttrSet(lbl_1_data_8[0], HUSPR_ATTR_DISPOFF);
            }
        case 0x3EC:
        case 0x3ED:
            lbl_1_bss_8C++;
            lbl_1_bss_8C %= 0x168;
            if (lbl_1_bss_14 != 0) {
                Hu3DModelPosSet(lbl_1_bss_B8->model[2], 0.0f, 100.0 + (25.0 * sind((360.0 * ((lbl_1_bss_8C % 360) / 360.0)))), -950.0f);
            }
            break;
        case 0x3EE:
            if (lbl_1_bss_14 != 0) {
                var_r26 = &Hu3DData[lbl_1_bss_B8->model[2]];
                if (lbl_1_bss_B4 >= 7) {
                    var_r26->pos.y += 12.5;
                }
                if (lbl_1_bss_B4 == 0) {
                    Hu3DMotionShiftSet(var_r27->model[1], var_r27->motion[1], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
            }
            else {
                var_r29 = &Hu3DData[lbl_1_bss_B8->model[spC[0]->unk_38 + 4]];
                if (lbl_1_bss_20 == 0) {
                    lbl_1_bss_20 = 1;
                    HuAudFXPlay(0x7F6);
                }
                if (lbl_1_bss_B4 == 1) {
                    lbl_1_bss_28C[spC[0]->unk_38].unk_08 = 83.333336f;
                }
                var_r29->pos.y = (0.9 * var_r29->pos.y) + (0.1 * lbl_1_bss_28C[spC[0]->unk_38].unk_08);
                lbl_1_bss_BC[0]->trans.y = var_r29->pos.y - -16.666666666666668;
            }
            break;
        case 0x3F0:
            Hu3DModelAttrSet(lbl_1_bss_B8->model[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_B8->model[2], HU3D_ATTR_DISPOFF);
            if (lbl_1_bss_B4 <= 0x3C) {
                var_f29 = lbl_1_bss_B4 / 60.0;
                var_f29 = var_f29;
                var_f29 = 1.0f - ((1.0f - var_f29) * (1.0f - var_f29));
                if (lbl_1_bss_B4 == 0) {
                    lbl_1_bss_28C[spC[0]->unk_38].unk_08 = -16.666666f;
                }
                for (var_r31 = 0; var_r31 < 9; var_r31++) {
                    var_r28 = &Hu3DData[lbl_1_bss_B8->model[var_r31 + 4]];
                    Hu3DModelPosSet(lbl_1_bss_B8->model[var_r31 + 4], (500.0 + (200.0f * var_f29)) * (lbl_1_bss_28C[var_r31].unk_00 - 1),
                        (0.9 * var_r28->pos.y) + (0.1 * lbl_1_bss_28C[spC[0]->unk_38].unk_08),
                        (500.0 + (200.0f * var_f29)) * (lbl_1_bss_28C[var_r31].unk_04 - 1));
                    for (var_r30 = 0; var_r30 < 2; var_r30++) {
                        if (var_r31 == spC[var_r30]->unk_38) {
                            lbl_1_bss_BC[var_r30]->trans.x = (500.0 + (200.0f * var_f29)) * (lbl_1_bss_28C[var_r31].unk_00 - 1);
                            lbl_1_bss_BC[var_r30]->trans.y = var_r28->pos.y - -16.666666666666668;
                            lbl_1_bss_BC[var_r30]->trans.z = (500.0 + (200.0f * var_f29)) * (lbl_1_bss_28C[var_r31].unk_04 - 1);
                        }
                    }
                }
            }
            break;
    }
    var_r25 = lbl_1_data_1A0;
    {
        UnkCameraStruct sp14[6] = {
            { 3500.0f, 0.0f, 100.0f, 0.0f, -59.0f, 0.0f },
            { 3200.0f, 0.0f, 100.0f, 0.0f, -30.0f, 0.0f },
            { 3800.0f, 0.0f, 100.0f, 0.0f, -30.0f, 0.0f },
            { 2000.0f, 0.0f, 200.0f, 0.0f, -30.0f, 0.0f },
            { 800.0f, 0.0f, 200.0f, 0.0f, -89.0f, 0.0f },
            { 1800.0f, 0.0f, 200.0f, 0.0f, -30.0f, 0.0f },
        };

        if (lbl_1_bss_98 != -1) {
            sp14[3].unk_04 = lbl_1_bss_BC[1 - lbl_1_bss_98]->trans.x;
            sp14[3].unk_0C = lbl_1_bss_BC[1 - lbl_1_bss_98]->trans.z;
            sp14[4].unk_04 = lbl_1_bss_BC[1 - lbl_1_bss_98]->trans.x;
            sp14[4].unk_0C = lbl_1_bss_BC[1 - lbl_1_bss_98]->trans.z;
            sp14[5].unk_04 = lbl_1_bss_BC[lbl_1_bss_98]->trans.x;
            sp14[5].unk_0C = lbl_1_bss_BC[lbl_1_bss_98]->trans.z;
        }
        if (lbl_1_data_1A0 == -1) {
            lbl_1_data_1A0 = 0;
            lbl_1_bss_24 = 1;
            lbl_1_bss_28 = 1.0f;
        }
        if (lbl_1_data_1A0 == 0) {
            lbl_1_data_1A0 = 1;
            lbl_1_bss_24 = 1;
            lbl_1_bss_28 = 0.5f;
        }
        if ((lbl_1_bss_B0 == 0x3F0) && (lbl_1_bss_B4 >= 1) && (lbl_1_data_1A0 == 1)) {
            lbl_1_data_1A0 = 2;
            lbl_1_bss_24 = 0;
            lbl_1_bss_28 = 0.0f;
        }
        if ((lbl_1_bss_B0 == 0x3F3) && (lbl_1_data_1A0 == 2)) {
            lbl_1_data_1A0 = 3;
            lbl_1_bss_24 = 0;
            lbl_1_bss_28 = 0.0f;
        }
        if ((lbl_1_bss_B0 == 0x3F3) && (lbl_1_bss_B4 >= 0x12C) && (lbl_1_data_1A0 == 3)) {
            lbl_1_data_1A0 = 4;
            lbl_1_bss_24 = 1;
            lbl_1_bss_28 = 1.0f;
        }
        if ((lbl_1_bss_B0 == 0x3F4) && (lbl_1_data_1A0 == 4)) {
            lbl_1_data_1A0 = 5;
            lbl_1_bss_24 = 0;
            lbl_1_bss_28 = 0.0f;
        }
        if ((var_r25 != lbl_1_data_1A0) && (var_r25 != -1)) {
            lbl_1_data_1A4 = CZoom;
            lbl_1_data_1A8 = Center.y;
            lbl_1_bss_30 = Center.z;
            lbl_1_data_1AC = CRot.x;
            lbl_1_bss_34 = CRot.y;
        }
        if (lbl_1_bss_28 <= 1.0f) {
            if (lbl_1_bss_24 == 0) {
                lbl_1_bss_28 = 1.0 - (0.95 * (1.0f - lbl_1_bss_28));
                var_f31 = lbl_1_bss_28;
            }
            else {
                lbl_1_bss_28 += 0.008333333333333333;
                lbl_1_bss_28 = lbl_1_bss_28 > 1.0f ? 1.0f : lbl_1_bss_28;
                var_f31 = 0.5 + (-0.5 * cosd((180.0f * lbl_1_bss_28)));
                var_f31 = var_f31;
            }
            lbl_1_bss_28 = lbl_1_bss_28 > 1.0f ? 1.0f : lbl_1_bss_28;
            CZoom = (var_f31 * sp14[lbl_1_data_1A0].unk_00) + (lbl_1_data_1A4 * (1.0f - var_f31));
            Center.x = (var_f31 * sp14[lbl_1_data_1A0].unk_04) + (lbl_1_bss_2C * (1.0f - var_f31));
            Center.y = (var_f31 * sp14[lbl_1_data_1A0].unk_08) + (lbl_1_data_1A8 * (1.0f - var_f31));
            Center.z = (var_f31 * sp14[lbl_1_data_1A0].unk_0C) + (lbl_1_bss_30 * (1.0f - var_f31));
            CRot.x = (var_f31 * sp14[lbl_1_data_1A0].unk_10) + (lbl_1_data_1AC * (1.0f - var_f31));
            CRot.y = (var_f31 * sp14[lbl_1_data_1A0].unk_14) + (lbl_1_bss_34 * (1.0f - var_f31));
        }
    }
    if ((lbl_1_bss_B0 == 0x3E9) || (lbl_1_bss_B0 == 0x3EE)) {
        var_f25 = 0.0f;
        var_f26 = 0.0f;
        if ((lbl_1_data_114.unk_00 % 2) >= 0) {
            lbl_1_data_114.unk_08 = lbl_1_data_114.unk_10;
            lbl_1_data_114.unk_0C = lbl_1_data_114.unk_14;
            do {
                lbl_1_data_114.unk_10 = 2.0 * (rand8() / 255.0) - 1.0;
                lbl_1_data_114.unk_14 = (2.0 * (rand8() / 255.0)) - 1.0;
                lbl_1_data_114.unk_10 = 0.0f;
            } while (sqrtf(((lbl_1_data_114.unk_10 - lbl_1_data_114.unk_08) * (lbl_1_data_114.unk_10 - lbl_1_data_114.unk_08))
                         + ((lbl_1_data_114.unk_14 - lbl_1_data_114.unk_0C) * (lbl_1_data_114.unk_14 - lbl_1_data_114.unk_0C)))
                < 0.75);
        }
        var_f25 = lbl_1_data_114.unk_08;
        var_f26 = lbl_1_data_114.unk_0C;
        var_f25 *= lbl_1_data_114.unk_04 * 2;
        var_f26 *= lbl_1_data_114.unk_04 * 2;
        lbl_1_data_114.unk_00 = !lbl_1_data_114.unk_00;
        lbl_1_data_114.unk_04 = (lbl_1_data_114.unk_04 > 24) ? 23 : (lbl_1_data_114.unk_04 - 1 > 0) ? (lbl_1_data_114.unk_04 - 1) : 0;
        Center.x = 0.0f;
        Center.y = 100.0f + var_f26;
    }
}

const HsfanimStruct00 lbl_1_rodata_2A0 = {
    0x0096,
    { 0x00, 0x00 },
    50.0f,
    0.0f,
    65.0f,
    { 0.0f, -0.195f, 0.0f },
    100.0f,
    0.99f,
    40.0f,
    0.999f,
    4,
    {
        { 0xFF, 0xFF, 0x20, 0xFF },
        { 0xFF, 0xFF, 0x00, 0xFF },
        { 0xFF, 0xFF, 0x80, 0xFF },
        { 0xFF, 0xFF, 0xFF, 0xFF },
    },
    {
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0xFF, 0x00 },
    },
};

s16 fn_1_4BE8(void)
{
    s16 var_r31;
    s16 var_r30;
    AnimData *var_r29;
    void *var_r28;

    HsfanimStruct00 sp8 = lbl_1_rodata_2A0;
    lbl_1_bss_3C = sp8;
    var_r28 = HuDataSelHeapReadNum(0x7006B, MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29 = HuSprAnimRead(var_r28);
    var_r31 = Hu3DParManCreate(var_r29, 0x64, &lbl_1_bss_3C);
    Hu3DParManAttrSet(var_r31, 0x108);
    Hu3DParManRotSet(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DParManVecSet(var_r31, 0.0f, 0.4f, 0.2f);
    var_r30 = Hu3DParManModelIDGet(var_r31);
    Hu3DModelLayerSet(var_r30, 2);
    Hu3DParticleBlendModeSet(var_r30, 0);
    return var_r31;
}

void fn_1_4D44(void)
{
    M458DllWork *spC[2];
    s16 sp8;
    s16 var_r31;
    s32 var_r30;
    WindowData *var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;

    sp8 = 0;
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        spC[var_r30] = lbl_1_bss_BC[var_r30]->data;
    }
    HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 0x3C);
    HuWinComKeyReset();
    var_r31 = HuWinExCreateStyled(36.0f, 344.0f, 0x1F8, 0x60, 6, 0);
    var_r29 = &winData[var_r31];
    if (spC[1]->unk_0C != -1) {
        var_r28 = 1 << spC[1]->unk_0C;
    }
    else {
        if (spC[1]->unk_08 != -1) {
            var_r27 = 1 << GWPlayerCfg[spC[1]->unk_04].pad_idx;
        }
        else {
            var_r27 = 0;
        }
        var_r28 = var_r27;
    }
    if (spC[0]->unk_0C != -1) {
        var_r26 = 1 << spC[0]->unk_0C;
    }
    else {
        if (spC[0]->unk_08 != -1) {
            var_r25 = 1 << GWPlayerCfg[spC[0]->unk_04].pad_idx;
        }
        else {
            var_r25 = 0;
        }
        var_r26 = var_r25;
    }
    var_r29->active_pad = var_r26 | var_r28;
    OSReport("%d\n", var_r29->active_pad);
    HuWinBGTPLvlSet(var_r31, 0.8f);
    HuWinMesSpeedSet(var_r31, 1);
    HuWinExAnimIn(var_r31);
    HuWinMesSet(var_r31, MAKE_MESSID(0x30, 0x24));
    if (((spC[0]->unk_0C == -1) || (spC[0]->unk_08 == -1)) && ((spC[1]->unk_0C == -1) || (spC[1]->unk_08 == -1))) {
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 0x3C);
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 0x3C);
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 0x3C);
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 0x3C);
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 0x3C);
    }
    HuWinMesWait(var_r31);
    HuWinExAnimOut(var_r31);
    HuWinExCleanup(var_r31);
    lbl_1_bss_10 = 0;
    HuPrcEnd();
}

void fn_1_5014(omObjData *var_r30)
{
    M458DllWork *spC[2];
    s32 sp8;
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 0x1C; var_r31++) {
        s32 sp14[] = {
            0x7F1,
            0x7F2,
            0x7F7,
            0x7F8,
            0x7F9,
            0x7FA,
            0x7FB,
            0x7FC,
            0x7FD,
            0x7FE,
            0x7FF,
            0x800,
            0x801,
            0x802,
            0x803,
            0x804,
            0x7FB,
            0x7FC,
            0x7FD,
            0x7FE,
            0x7FF,
            0x800,
            0x801,
            0x802,
            0x803,
            0x804,
            0x7FB,
            0x7FC,
        };
        if (lbl_1_bss_CC[var_r31].unk_00 > 3) {
            lbl_1_bss_CC[var_r31].unk_00 = 3;
        }
        if (lbl_1_bss_CC[var_r31].unk_00 > 0) {
            sp8 = HuAudFXPlay(sp14[var_r31]);
            lbl_1_bss_CC[var_r31].unk_00--;
        }
    }
    for (var_r31 = 0; var_r31 < 2; var_r31++) {
        spC[var_r31] = lbl_1_bss_BC[var_r31]->data;
    }
    if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        var_r30->func = fn_1_6D9C;
    }
    switch (lbl_1_bss_B0) {
        case 0x3E8:
            if (WipeStatGet() == 0) {
                lbl_1_bss_B0++;
                lbl_1_bss_B4 = 0.0f;
                if (lbl_1_data_138[0] != -1) {
                    Hu3DParManKill(*lbl_1_data_138);
                    lbl_1_data_138[0] = -1;
                }
            }
        default:
            break;
        case 0x3E9:
            lbl_1_bss_B4++;
            if (lbl_1_bss_B4 == ((lbl_1_bss_14 == 0 ? 0x1E : 0) + 0x3C)) {
                lbl_1_bss_B0 = lbl_1_bss_14 != 0 ? 0x3EA : 0x3ED;
                lbl_1_bss_B4 = 0.0f;
            }
            break;
        case 0x3EA:
            lbl_1_bss_B4++;
            if (lbl_1_bss_B4 == 0x78) {
                lbl_1_bss_B0++;
                lbl_1_bss_B4 = 0.0f;
            }
            break;
        case 0x3EB:
            lbl_1_bss_B4++;
            if (lbl_1_bss_B4 > 0xD2) {
                lbl_1_bss_B0++;
                lbl_1_bss_B4 = 0.0f;
            }
            break;
        case 0x3EC:
            if (lbl_1_bss_B4 == 0) {
                HuPrcChildCreate(fn_1_4D44, 0x64, 0x2000, 0, HuPrcCurrentGet());
                lbl_1_bss_10 = 1;
                lbl_1_bss_B4++;
                break;
            }
            if (lbl_1_bss_10 == 0) {
                lbl_1_bss_B4++;
                if (spC[0]->unk_18 == 0) {
                    lbl_1_bss_B0++;
                    lbl_1_bss_B4 = 0.0f;
                }
            }
            break;
        case 0x3ED:
            lbl_1_bss_B4 += lbl_1_bss_B4 < 0x1E;
            if (lbl_1_bss_B4 >= 0x3C) {
                lbl_1_bss_B0++;
                lbl_1_bss_B4 = 0.0f;
            }
            break;
        case 0x3EE:
            lbl_1_bss_B4++;
            if (lbl_1_bss_B4 == ((spC[1]->unk_08 == -1 ? 0x78 : 0x3C) + (lbl_1_bss_14 == 0 ? 0x1E : 0))) {
                lbl_1_bss_B0++;
                if (spC[1]->unk_08 == -1) {
                    lbl_1_bss_B0++;
                }
                lbl_1_bss_B4 = 0.0f;
            }
            break;
        case 0x3EF:
            lbl_1_bss_B4 += lbl_1_bss_B4 < 0x1E;
            if (lbl_1_bss_B4 >= 0x3C) {
                lbl_1_bss_B0++;
                lbl_1_bss_B4 = 0.0f;
            }
            break;
        case 0x3F0:
            lbl_1_bss_B4++;
            if (lbl_1_bss_B4 == 0x5A) {
                lbl_1_bss_B0++;
                lbl_1_bss_B4 = 0.0f;
            }
            break;
        case 0x3F1:
        case 0x3F2:
            if (lbl_1_bss_B4 == 0) {
                spC[lbl_1_bss_B0 == 0x3F1 ? 0 : 1]->unk_18 = 3;
                spC[lbl_1_bss_B0 == 0x3F1 ? 0 : 1]->unk_1C = 0;
            }
            lbl_1_bss_B4++;
            if (spC[lbl_1_bss_B0 == 0x3F1 ? 0 : 1]->unk_18 == 0) {
                if (lbl_1_bss_98 != -1) {
                    lbl_1_bss_B0 = 0x3F3;
                }
                else {
                    lbl_1_bss_B0 = lbl_1_bss_B0 == 0x3F1 ? 0x3F2 : 0x3F1;
                }
                lbl_1_bss_B4 = 0.0f;
            }
            break;
        case 0x3F3:
            lbl_1_bss_B4++;
            if (lbl_1_bss_B4 >= 0x1E0) {
                lbl_1_bss_B0++;
                lbl_1_bss_B4 = 0.0f;
            }
            break;
        case 0x3F4:
            lbl_1_bss_B4++;
            if (lbl_1_bss_B4 == 1) {
                if (lbl_1_bss_98 != 4) {
                    if (spC[lbl_1_bss_98]->unk_08 != -1) {
                        HuAudSStreamPlay(1);
                    }
                    else {
                        HuAudSStreamPlay(3);
                    }
                    if (lbl_1_bss_14 != 0) {
                        if (lbl_1_bss_98 == 0) {
                            _SetFlag(0x10007);
                        }
                    }
                    else {
                        GWPlayerCoinWinSet(spC[lbl_1_bss_98]->unk_04, 10);
                    }
                }
                else {
                    lbl_1_bss_98 == 4;
                }
            }
            if (210.0f < lbl_1_bss_B4) {
                if (lbl_1_data_134 != -1) {
                    HuAudFXStop(lbl_1_data_134);
                    lbl_1_data_134 = -1;
                }
                lbl_1_data_12C = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 0x3C);
                var_r30->func = fn_1_6D9C;
            }
            break;
    }
}

s32 lbl_1_data_1E8[0xB] = {
    0x570013,
    0x570014,
    0x570015,
    0x570016,
    0x570017,
    0x570018,
    0x570019,
    0x57001A,
    0x57001B,
    0x57001C,
    0x57001D,
};

void fn_1_59DC(omObjData *object)
{
    M458DllWork *sp18[2];

    s32 var_r30;
    s16 var_r29;
    s16 var_r28;
    s32 var_r27;
    void *var_r26;
    AnimData *var_r25;
    s16 var_r24;
    s16 var_r23;

    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        sp18[var_r30] = lbl_1_bss_BC[var_r30]->data;
    }
    object->model[1] = Hu3DModelCreateFile(0x3000E);
    Hu3DModelAttrSet(object->model[1], HU3D_MOTATTR_LOOP);
    object->model[2] = Hu3DModelCreateFile(0x30000);
    Hu3DModelAttrSet(object->model[2], HU3D_MOTATTR_LOOP);
    Hu3DModelHookSet(object->model[2], "minik01", object->model[1]);
    Hu3DModelPosSet(object->model[2], 0.0f, -750.0f, -700.0f);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF);
    object->motion[0] = Hu3DJointMotionFile(object->model[1], 0x3000F);
    object->motion[1] = Hu3DJointMotionFile(object->model[1], 0x30012);
    Hu3DMotionSet(object->model[1], object->motion[0]);
    Hu3DModelLayerSet(object->model[2], 1);
    Hu3DModelLayerSet(object->model[1], 1);
    object->model[0] = Hu3DModelCreateFile(0x570008);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(object->model[0], 0.1f);
    object->model[3] = Hu3DModelCreateFile(0x570009);
    Hu3DModelAttrSet(object->model[3], HU3D_MOTATTR_LOOP);
    Hu3DModelPosSet(object->model[3], 0.0f, 400.0f, 0.0f);
    Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(object->model[3], 1);
    Hu3DMotionSpeedSet(object->model[3], 0.0f);
    for (var_r30 = 0; var_r30 < 9; var_r30++) {
        object->model[var_r30 + 4] = Hu3DModelCreateFile(var_r30 + 0x57000A);
        lbl_1_bss_28C[var_r30].unk_00 = var_r30 % 3;
        lbl_1_bss_28C[var_r30].unk_04 = var_r30 / 3;
        lbl_1_bss_28C[var_r30].unk_08 = 0.0f;
        lbl_1_bss_28C[var_r30].unk_0C = 1;
        Hu3DModelPosSet(
            lbl_1_bss_B8->model[var_r30 + 4], 500.0 * (lbl_1_bss_28C[var_r30].unk_00 - 1), -16.666666f, 500.0 * (lbl_1_bss_28C[var_r30].unk_04 - 1));
        Hu3DModelScaleSet(lbl_1_bss_B8->model[var_r30 + 4], 1.6666666f, 1.6666666f, 1.6666666f);
        Hu3DModelAttrSet(object->model[var_r30 + 4], HU3D_MOTATTR_PAUSE);
        Hu3DModelShadowMapSet(object->model[var_r30 + 4]);
        Hu3DModelLayerSet(object->model[var_r30 + 4], 1);
    }
    for (var_r30 = 0; var_r30 < 0xB; var_r30++) {
        if ((var_r30 == 9) || (var_r30 == 0xA)) {
            if (sp18[var_r30 - 9]->unk_08 != -1) {
                var_r27 = sp18[var_r30 - 9]->unk_08 + 0x57001C;
            }
            else {
                var_r27 = 0x570024;
            }
            lbl_1_data_1E8[var_r30] = var_r27;
        }
        object->model[var_r30 + 0xD] = Hu3DModelCreateFile(lbl_1_data_1E8[var_r30]);
        Hu3DMotionTimeSet(object->model[var_r30 + 0xD], 10.0f);
        Hu3DMotionSpeedSet(object->model[var_r30 + 0xD], 0.0f);
        Hu3DModelAttrSet(object->model[var_r30 + 0xD], HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(object->model[var_r30 + 0xD], 1);
    }
    for (var_r30 = 0; var_r30 < 2; var_r30++) {
        s32 sp10[2] = { 0x120, 0x122 };
        s32 sp8[2] = { 0xF0, 0x8C };
        lbl_1_data_8[var_r30] = espEntry(lbl_1_data_0[var_r30], 0, 0);
        espDrawNoSet(lbl_1_data_8[var_r30], 0);
        espAttrSet(lbl_1_data_8[var_r30], HUSPR_ATTR_NOANIM | HUSPR_ATTR_DISPOFF);
        espBankSet(lbl_1_data_8[var_r30], 0);
        espPriSet(lbl_1_data_8[var_r30], 0x80 - var_r30);
        espPosSet(lbl_1_data_8[var_r30], sp10[var_r30], sp8[var_r30]);
        espTPLvlSet(lbl_1_data_8[var_r30], 1.0f);
    }
    {
        HsfanimStruct00 sp20 = lbl_1_rodata_2A0;
        lbl_1_bss_3C = sp20;
    }
    var_r26 = HuDataSelHeapReadNum(0x7006B, MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r25 = HuSprAnimRead(var_r26);
    var_r29 = Hu3DParManCreate(var_r25, 0x64, &lbl_1_bss_3C);
    Hu3DParManAttrSet(var_r29, 0x108);
    Hu3DParManRotSet(var_r29, 0.0f, 0.0f, 0.0f);
    Hu3DParManVecSet(var_r29, 0.0f, 0.4f, 0.2f);
    var_r28 = Hu3DParManModelIDGet(var_r29);
    Hu3DModelLayerSet(var_r28, 2);
    Hu3DParticleBlendModeSet(var_r28, 0);
    var_r24 = var_r29;
    var_r23 = var_r24;
    lbl_1_data_138[0] = var_r23;
    Hu3DParManPosSet(lbl_1_data_138[0], 10000.0f, -10000.0f, 10000.0f);
    object->func = fn_1_350C;
}

void fn_1_6314(omObjData *object)
{
    s32 sp10;
    void *spC;
    M458DllWork *work;
    s32 var_r29;

    work = object->data;
    spC = lbl_1_bss_BC[1 - object->work[0]]->data;
    memset(work, 0, sizeof(M458DllWork));
    work->unk_00 = object->work[0];
    work->unk_04 = GWPlayerCfg->group == work->unk_00
        ? 0
        : (GWPlayerCfg[1].group == work->unk_00 ? 1 : (GWPlayerCfg[2].group == work->unk_00 ? 2 : (GWPlayerCfg[3].group == work->unk_00 ? 3 : 4)));
    sp10 = GWPlayerCfg->group == (1 - work->unk_00)
        ? 0
        : (GWPlayerCfg[1].group == (1 - work->unk_00)
                ? 1
                : (GWPlayerCfg[2].group == (1 - work->unk_00) ? 2 : (GWPlayerCfg[3].group == (1 - work->unk_00) ? 3 : 4)));
    if (work->unk_04 == 4) {
        OSReport("m458:wrong player group\n");
        work->unk_04 = work->unk_00;
    }
    if ((work->unk_00 == 1) && (lbl_1_bss_14 != 0)) {
        work->unk_08 = -1;
        work->unk_0C = -1;
        work->unk_04 = -1;
        work->unk_10 = 0;
    }
    else {
        work->unk_08 = GWPlayerCfg[work->unk_04].character;
        work->unk_0C = ((work->unk_08 == -1) || (GWPlayerCfg[work->unk_04].iscom != 0)) ? -1 : GWPlayerCfg[work->unk_04].pad_idx;
        work->unk_10 = work->unk_0C != -1 ? 0 : GWPlayerCfg[work->unk_04].diff;
    }
    work->unk_18 = 0;
    work->unk_20 = 3;
    work->unk_24 = -1;
    if (work->unk_08 != -1) {
        object->model[0] = CharModelCreate(work->unk_08, 1);
    }
    else {
        object->model[0] = Hu3DModelCreateFile(0x30007);
    }
    omSetTra(object, 0.0f, work->unk_00 == 0 ? 0 : 0x12C, 0.0f);
    if (work->unk_08 != -1) {
        omSetSca(object, 2.5f, 2.5f, 2.5f);
    }
    else {
        omSetSca(object, 2.0f, 2.0f, 2.0f);
    }
    for (var_r29 = 0; var_r29 < 0xA; var_r29++) {
        if (work->unk_08 != -1) {
            object->motion[var_r29] = CharModelMotionCreate(work->unk_08, lbl_1_data_10[var_r29] + (lbl_1_data_38[var_r29] != 0 ? work->unk_08 : 0));
        }
        else if (lbl_1_data_60[var_r29] != 0) {
            object->motion[var_r29] = Hu3DJointMotionFile(object->model[0], lbl_1_data_60[var_r29]);
        }
    }
    Hu3DMotionSet(object->model[0], object->motion[work->unk_20]);
    Hu3DMotionTimeSet(object->model[0], 10.0f);
    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(object->model[0]);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(object->model[0], 1);
    CharModelLayerSetAll2(1);
    object->func = fn_1_4C8;
}

void fn_1_685C(omObjData *object)
{
    lbl_1_bss_B0 = 0x3E8;
    lbl_1_bss_B4 = 0.0f;
    lbl_1_bss_A8 = 0;
    lbl_1_bss_A4 = 0;
    if (lbl_1_data_130 == -1) {
        lbl_1_data_130 = HuAudSeqPlay(0x4D);
    }
    lbl_1_data_134 = HuAudFXPlay(0x6D7);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    object->func = fn_1_5014;
}

void ObjectSetup(void)
{
    s32 i;
    omObjData *object;

    OSReport("******* M458 ObjectSetup *********\n");
    lbl_1_bss_A0 = omInitObjMan(0x258, 0x2000);
    omGameSysInit(lbl_1_bss_A0);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    CZoom = 3200.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = -100.0f;
    CRot.x = -30.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    {
        Vec sp3C = { 0.0f, 0.0f, 0.0f };
        Vec sp30 = { 0.25f, -0.75f, -0.45f };
        GXColor sp8 = { 255, 255, 255, 255 };
        lbl_1_bss_9C = Hu3DGLightCreateV(&sp3C, &sp30, &sp8);
        Hu3DGLightStaticSet(lbl_1_bss_9C, 1);
        Hu3DGLightInfinitytSet(lbl_1_bss_9C);
    }
    {
        Vec sp24;
        Vec sp18;
        Vec spC;

        sp24.x = 0.0f;
        sp24.y = 10000.0f;
        sp24.z = 0.0f;
        sp18.x = 0.0f;
        sp18.y = 1.0f;
        sp18.z = 0.0f;
        spC.x = 0.0f;
        spC.y = 0.0f;
        spC.z = 0.5f;
        Hu3DShadowCreate(12.0f, 9000.0f, 10010.0f);
        Hu3DShadowTPLvlSet(0.625f);
        Hu3DShadowPosSet(&sp24, &sp18, &spC);
    }
    Hu3DShadowSizeSet(0xE0);
    lbl_1_data_12C = -1;
    lbl_1_bss_98 = -1;
    lbl_1_bss_14 = _CheckFlag(0x10000) != 0;
    HuWinInit(1);
    lbl_1_bss_B8 = omAddObjEx(lbl_1_bss_A0, 0x65, 0x18, 2, 1, fn_1_59DC);
    for (i = 0; i < 2; i++) {
        object = lbl_1_bss_BC[i] = omAddObjEx(lbl_1_bss_A0, 0x64, 0xB, 0xA, 0, fn_1_6314);
        object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M458DllWork), MEMORY_DEFAULT_NUM);
        object->work[0] = i;
    }
    lbl_1_bss_C4 = omAddObjEx(lbl_1_bss_A0, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_C8 = omAddObjEx(lbl_1_bss_A0, 0x67, 0, 0, -1, fn_1_685C);
}

void fn_1_6D9C(omObjData *object)
{
    if (lbl_1_data_138[0] != -1) {
        Hu3DParManKill(lbl_1_data_138[0]);
        lbl_1_data_138[0] = -1;
    }
    if (WipeStatGet() == 0) {
        s32 i;
        for (i = 0; i < 2; i++) {
            void *sp8 = lbl_1_bss_BC[i]->data;
        }
        if (lbl_1_data_12C >= 0) {
            MGSeqKill(lbl_1_data_12C);
        }
        MGSeqKillAll();
        HuAudAllStop();
        omOvlReturnEx(1, 1);
    }
}
