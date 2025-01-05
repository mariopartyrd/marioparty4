#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
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

#include "ext_math.h"

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ s32 unk0C;
} StructBss51C; // Size 0x10

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ float unk04[3];
} StructBss35C; // Size 0x10

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x00 */ s32 unk04;
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
    /* 0x30 */ char unk30[4];
    /* 0x34 */ float unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x48 */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ char unk56[2];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
} StructBss330Data; // Size 0x60

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
} StructData134; // Size 0x18

s16 fn_1_4474(void);
void fn_1_659C(omObjData* arg0);

StructBss51C lbl_1_bss_51C[9];
StructBss35C lbl_1_bss_35C[28];
omObjData* lbl_1_bss_358;
omObjData* lbl_1_bss_354;
omObjData* lbl_1_bss_330[9];
omObjData* lbl_1_bss_32C;
HsfanimStruct00 lbl_1_bss_5C[9];
s32 lbl_1_bss_58;
s32 lbl_1_bss_54;
s32 lbl_1_bss_50;
char lbl_1_bss_4C[4]; // unused
s32 lbl_1_bss_48;
s32 lbl_1_bss_44;
Process* lbl_1_bss_40;
s32 lbl_1_bss_3C;
s32 lbl_1_bss_38;
s32 lbl_1_bss_34;
char lbl_1_bss_30[4]; // unused
float lbl_1_bss_2C;
float lbl_1_bss_28;
float lbl_1_bss_24;
float lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
s32 lbl_1_bss_14;
char lbl_1_bss_E[6]; // unused
s16 lbl_1_bss_C;
char lbl_1_bss_8[4]; // unused
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

s32 lbl_1_data_0[9] = {
    DATA_MAKE_NUM(DATADIR_M458, 38),
    DATA_MAKE_NUM(DATADIR_M458, 38),
    DATA_MAKE_NUM(DATADIR_M458, 38),
    DATA_MAKE_NUM(DATADIR_M458, 38),
    DATA_MAKE_NUM(DATADIR_M458, 38),
    DATA_MAKE_NUM(DATADIR_M458, 38),
    DATA_MAKE_NUM(DATADIR_M458, 38),
    DATA_MAKE_NUM(DATADIR_M458, 38),
    DATA_MAKE_NUM(DATADIR_M458, 38)
};

s32 lbl_1_data_24[9] = { 0 };

s32 lbl_1_data_48[9] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 2),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 3),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 5),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 6),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 47),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 26),
    DATA_MAKE_NUM(DATADIR_M458, 0),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 23),
};

u32 lbl_1_data_6C[9] = { 0, 0, 0, 0, 0, 0, 0, 1, 0 };

u32 lbl_1_data_90[] = {
    DATA_MAKE_NUM(DATADIR_BKOOPA, 8),
    0,
    0,
    DATA_MAKE_NUM(DATADIR_BKOOPA, 10),
    0,
    DATA_MAKE_NUM(DATADIR_M458, 42),
    DATA_MAKE_NUM(DATADIR_M458, 40),
    DATA_MAKE_NUM(DATADIR_M458, 41),
    DATA_MAKE_NUM(DATADIR_M458, 39)
};

u8 lbl_1_data_B4[9] = { 0, 0, 0, 1, 1, 1, 0, 1, 1 };
u8 lbl_1_data_BD[9] = { 0, 0, 0, 1, 1, 1, 0, 1, 1 };
s32 lbl_1_data_C8[9] = { 8, 8, 8, 0, 0, 8, 8, 8, 8 };
s32 lbl_1_data_EC[9] = { 0, 0, 0, 0, 3, 0, 0, 0, 0 };
s32 lbl_1_data_110[9] = { 8, 8, 8, 8, 8, 8, 8, 8, 8 };

StructData134 lbl_1_data_134 = { 0 };

s16 lbl_1_data_14C = -1;
s16 lbl_1_data_14E = -1;
s32 lbl_1_data_150 = -1;
s32 lbl_1_data_154 = -1;

// unused
float lbl_1_data_158[] = { -90.0f, 0.0f, 525.0f, 180.0f, 90.0f, 0.0f, 525.0f, 180.0f };

void fn_1_A0(void) {
    if (HuPadBtnDown[0] & PAD_BUTTON_B) {
        Center.x = lbl_1_bss_330[0]->trans.x;
        Center.y = lbl_1_bss_330[0]->trans.y;
        Center.z = lbl_1_bss_330[0]->trans.z;
    }
    Center.x += 10.0 * (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) - ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0));
    Center.z -= 10.0 * (((HuPadBtn[0] & PAD_BUTTON_UP) != 0) - ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0));
    Center.y += 30.0 * ((HuPadTrigL[0] - HuPadTrigR[0]) / 128.0);
    CZoom += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_X) != 0) - ((HuPadBtn[0] & PAD_BUTTON_Y) != 0));
    CRot.y += HuPadSubStkX[0] / 16.0;
    CRot.x += HuPadSubStkY[0] / -16.0;
    print8(64, 392, 1.0f, "%f,%f,%f", Center.x, Center.y, Center.z);
    print8(64, 408, 1.0f, "%f,%f,%f", CRot.x, CRot.y, CRot.z);
    print8(64, 424, 1.0f, "%f", CZoom);
}

s32 lbl_1_data_184 = -1;

void fn_1_4C8(omObjData* arg0) {
    ModelData* temp_r24;
    ModelData* temp_r29;
    float temp_f31;
    float temp_f30;
    float var_f28;
    float temp_f27;
    float temp_f26;
    float temp_f25;
    float var_f24;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f20;
    StructBss330Data* temp_r31;
    s16 var_r28;
    s32 temp_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r23;
    s32 var_r22;
    StructBss330Data* temp_r21;
    s32 var_r20;
    s32 var_r19;
    StructBss330Data* temp_r18;
    s32 var_r17;
    float sp180[2];
    s32 spE0;
    s32 spDC;
    s32 spD8;
    s32 spD4;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    StructBss330Data* spC4;
    s32 spC0;
    s32 spBC;
    StructBss330Data* spB8;
    s32 spB4;
    u32 spB0;
    float spAC;
    s32 spA8;
    s32 spA4;
    s32 spA0;
    StructBss330Data* sp9C;
    ModelData* sp98;
    float sp94;
    float sp90;
    s32 sp8C;
    s32 sp88;

    temp_r31 = arg0->data;
    var_f23 = 0.0f;
    var_f22 = 0.0f;
    var_f28 = 0.0f;
    var_r22 = 0;
    var_r28 = -1;
    temp_r31->unk2C = temp_r31->unk34 = 0.0f;
    if (lbl_1_bss_50 == 1005 && temp_r31->unk18 == 3 && temp_r31->unk1C >= 360) {
        if (temp_r31->unk1C == 360) {
            temp_r31->unk14 = rand8() % 15;
        }
        if (temp_r31->unk0C != -1) {
            var_r22 = (HuPadBtnDown[temp_r31->unk0C] & PAD_BUTTON_A) ? 1 : 0;
        } else {
            temp_r31->unk14 += (temp_r31->unk14 < 0x10000);
            if (temp_r31->unk14 == 30) {
                var_r22 = 1;
            }
        }
    }
    if (temp_r31->unk00 < 4 && lbl_1_bss_50 == 1002) {
        var_r26 = 0;
        var_r25 = 0;
        if (temp_r31->unk0C != -1) {
            var_r26 = (HuPadStkX[temp_r31->unk0C] < -20) ? -1
                : (HuPadStkX[temp_r31->unk0C] > 20) ? 1 : 0;
            var_r25 = (-HuPadStkY[temp_r31->unk0C] < -20) ? -1
                : (-HuPadStkY[temp_r31->unk0C] > 20) ? 1 : 0;
            var_r22 = (HuPadBtnDown[temp_r31->unk0C] & PAD_BUTTON_A) ? 1 : 0;
        } else {
            if (lbl_1_bss_54 == 1) {
                temp_r31->unk14 = rand8() % 64 + 30;
            }
            temp_r31->unk14 -= (temp_r31->unk14 > 0);
            if (temp_r31->unk14 == 1) {
                var_r26 = (temp_r31->unk3C > 0 ? -1 : 1) * (rand8() % 2);
                var_r25 = (temp_r31->unk40 > 0 ? -1 : 1) * (rand8() % 2);
            }
            if (temp_r31->unk14 == 0) {
                var_r22 = (rand8() % 64 == 1) ? 1 : 0;
            }
        }
        if (lbl_1_bss_54 >= 50 || temp_r31->unk50 != 0) {
            var_r26 = var_r25 = 0;
        }
        for (var_r17 = 0; var_r17 < 4; var_r17++) {
            temp_r21 = lbl_1_bss_330[var_r17]->data;
            spD0 = 0;
            spCC = 0;
            if (var_r17 != temp_r31->unk00) {
                if (fabs(500.0 * temp_r31->unk3C - arg0->trans.x) < 10.0) {
                    spE0 = spDC = (arg0->trans.x < -250.0) ? -1
                        : (arg0->trans.x > 250.0) ? 1 : 0;
                } else {
                    spE0 = (arg0->trans.x < 0.0f) ? -1 : 0;
                    spDC = spE0 + 1;
                }
                if (fabs(500.0 * temp_r31->unk40 - arg0->trans.z) < 10.0) {
                    spD8 = spD4 = (arg0->trans.z < -250.0) ? -1
                        : (arg0->trans.z > 250.0) ? 1 : 0;
                } else {
                    spD8 = (arg0->trans.z < 0.0f) ? -1 : 0;
                    spD4 = spD8 + 1;
                }
                for (var_r20 = spE0; var_r20 <= spDC; var_r20++) {
                    for (var_r19 = spD8; var_r19 <= spD4; var_r19++) {
                        if (temp_r21->unk38 == (1 + var_r20 + var_r26) + (1 + var_r19 + var_r25) * 3) {
                            var_r26 = var_r25 = 0;
                        }
                        if (temp_r21->unk38 == (1 + var_r20 + var_r26) + (1 + var_r19) * 3) {
                            var_r26 = 0;
                        }
                        if (temp_r21->unk38 == (1 + var_r20) + (1 + var_r19 + var_r25) * 3) {
                            var_r25 = 0;
                        }
                    }
                }
            }
        }
        if (var_r26 * (500.0 * temp_r31->unk3C - arg0->trans.x) < 0.0) {
            temp_r31->unk3C += var_r26;
        }
        if (fabs(500.0 * temp_r31->unk3C - arg0->trans.x) < 10.0 && var_r26 != 0 && temp_r31->unk3C + var_r26 >= -1 && temp_r31->unk3C + var_r26 <= 1) {
            temp_r31->unk3C += var_r26;
        }
        var_f23 = ((500.0 * temp_r31->unk3C - arg0->trans.x) / 0.25) / 1.75;
        if (var_r25 * (500.0 * temp_r31->unk40 - arg0->trans.z) < 0.0) {
            temp_r31->unk40 += var_r25;
        }
        if (fabs(500.0 * temp_r31->unk40 - arg0->trans.z) < 10.0 && var_r25 != 0 && temp_r31->unk40 + var_r25 >= -1 && temp_r31->unk40 + var_r25 <= 1) {
            temp_r31->unk40 += var_r25;
        }
        var_f22 = ((500.0 * temp_r31->unk40 - arg0->trans.z) / -0.25) / 1.75;
        temp_r31->unk38 = (temp_r31->unk3C + 1) + (temp_r31->unk40 + 1) * 3;
    }
    if (temp_r31->unk18 == 0) {
        if (lbl_1_bss_50 > (temp_r31->unk00 < 4 ? 1001 : 1003) && lbl_1_bss_50 < 1006) {
            temp_f31 = 0.25 * var_f23;
            temp_f30 = 0.25 * -var_f22;
            {
                Vec sp1A0 = { 0.0f, 0.0f, 0.0f };
                Mtx sp1D0;

                sp1A0.x = temp_f31;
                sp1A0.z = temp_f30;
                PSMTXRotRad(sp1D0, 'y', MTXDegToRad(CRot.y));
                PSMTXMultVec(sp1D0, &sp1A0, &sp1A0);
                temp_f31 = sp1A0.x;
                temp_f30 = sp1A0.z;
                var_f28 = sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30);
                if (var_f28 >= 0.5f) {
                    if (var_f28 < 10.0f) {
                        temp_r31->unk2C = temp_f31;
                        temp_r31->unk34 += temp_f30;
                    } else {
                        temp_f31 /= var_f28;
                        temp_f30 /= var_f28;
                        var_f28 = 10.0f;
                        temp_r31->unk2C = temp_f31 * var_f28;
                        temp_r31->unk34 = temp_f30 * var_f28;
                    }
                    temp_r31->unk28 = var_f28;
                    arg0->rot.y = atan2d(temp_r31->unk2C, temp_r31->unk34);
                    if (temp_r31->unk28 >= 8.0f) {
                        var_r28 = 2;
                    } else {
                        var_r28 = 2;
                    }
                } else {
                    var_r28 = 0;
                }
            }
        }
    }
    arg0->trans.x += 1.75f * temp_r31->unk2C;
    arg0->trans.z += 1.75f * temp_r31->unk34;
    switch (lbl_1_bss_50) {
        case 1001:
        case 1003:
            if (lbl_1_bss_50 != (temp_r31->unk00 < 4 ? 1001 : 1003)) {
                break;
            }
            if (lbl_1_bss_54 == 0) {
                Hu3DModelAttrReset(arg0->model[0], HU3D_ATTR_DISPOFF);
                if (temp_r31->unk00 < 4) {
                    temp_r31->unk38 = (temp_r31->unk00 == 0) ? 0
                        : (temp_r31->unk00 == 1) ? 2
                        : (temp_r31->unk00 == 2) ? 6 : 8;
                    temp_r31->unk3C = temp_r31->unk38 % 3 - 1;
                    temp_r31->unk40 = temp_r31->unk38 / 3 - 1;
                    arg0->trans.x = 500.0 * temp_r31->unk3C;
                    arg0->trans.z = 500.0 * temp_r31->unk40;
                } else {
                    do {
                        temp_r31->unk38 = rand8() % 9;
                        for (spC8 = 0; spC8 < temp_r31->unk00; spC8++) {
                            spC4 = lbl_1_bss_330[spC8]->data;
                            if (temp_r31->unk38 == spC4->unk38) {
                                break;
                            }
                        }
                    } while (spC8 != temp_r31->unk00);
                    temp_r31->unk3C = temp_r31->unk38 % 3 - 1;
                    temp_r31->unk40 = temp_r31->unk38 / 3 - 1;
                    arg0->trans.x = 500.0 * temp_r31->unk3C;
                    arg0->trans.z = 500.0 * temp_r31->unk40;
                }
            }
            if (lbl_1_bss_54 <= 30) {
                if (temp_r31->unk08 == -1) {
                    Hu3DMotionTimeSet(arg0->model[0], 138.0f);
                }
                arg0->trans.y = 2400.0 * (1.0 - lbl_1_bss_54 / 30.0);
            }
            if (temp_r31->unk08 != -1 && lbl_1_bss_54 == 30) {
                var_r28 = 4;
            }
            if (lbl_1_bss_54 == (temp_r31->unk08 != -1 ? 10 : 60) + 30) {
                var_r28 = 0;
            }
            if (lbl_1_bss_54 == 30) {
                lbl_1_data_134.unk04 += 50;
            }
            if (lbl_1_bss_54 == 30 && (temp_r31->unk00 == 0 || temp_r31->unk00 == 4)) {
                HuAudFXPlay(0x33D);
            }
            break;
        case 1002:
            if (lbl_1_bss_54 != 0 && temp_r31->unk00 < 4 && (var_r22 != 0 || lbl_1_bss_0 == 0) && temp_r31->unk50 == 0) {
                temp_r31->unk50 = 1;
                lbl_1_bss_14++;
                lbl_1_bss_51C[temp_r31->unk38].unk08 = 83.333336f;
            }
            if (temp_r31->unk00 != 0) {
                break;
            }
            if (lbl_1_bss_54 == 0) {
                lbl_1_bss_0 = 300;
                lbl_1_data_14E = MGSeqTimerCreate(10);
                HuWinMesMaxSizeGet(1, sp180, MAKE_MESSID(40, 25));
                lbl_1_bss_C = HuWinCreate(-10000.0f, 400.0f, sp180[0], sp180[1], 1);
                HuWinBGTPLvlSet(lbl_1_bss_C, 0.0f);
                HuWinMesSpeedSet(lbl_1_bss_C, 0);
                HuWinMesSet(lbl_1_bss_C, MAKE_MESSID(40, 25));
            }
            lbl_1_bss_0--;
            if (lbl_1_data_14E != -1) {
                MGSeqParamSet(lbl_1_data_14E, 1, (lbl_1_bss_0 + 59) / 60);
            }
            if (lbl_1_bss_14 >= 4) {
                lbl_1_bss_54 = 50;
                MGSeqParamSet(lbl_1_data_14E, 2, -1);
                lbl_1_data_14E = -1;
                HuWinExCleanup(lbl_1_bss_C);
            }
            if (lbl_1_bss_54 == 50) {
                for (var_r23 = 0; var_r23 < 4; var_r23++) {
                    temp_r18 = lbl_1_bss_330[var_r23]->data;
                    if (!(fabs(500.0 * temp_r18->unk3C - lbl_1_bss_330[var_r23]->trans.x) < 1.0)
                        || !(fabs(500.0 * temp_r18->unk40 - lbl_1_bss_330[var_r23]->trans.z) < 1.0)
                        || temp_r18->unk20 != 0)
                    {
                        break;
                    }
                }
                if (var_r23 == 4) {
                    lbl_1_bss_54 = 60;
                }
            }
            break;
        case 1005:
            if (temp_r31->unk5C != 0) {
                if (arg0->trans.y < -15000.0f) {
                    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
                } else {
                    arg0->trans.y -= 77.0f;
                }
            }
            break;
        case 1006:
            if (lbl_1_bss_54 <= 1) {
                Hu3DModelAttrSet(arg0->model[temp_r31->unk44 + 2], HU3D_ATTR_DISPOFF);
                lbl_1_bss_51C[temp_r31->unk44].unk0C = 0;
            }
            if (lbl_1_bss_51C[temp_r31->unk38].unk0C != 0 || temp_r31->unk5C != 0) {
                break;
            }
            if (lbl_1_bss_54 == 120) {
                Hu3DModelAttrReset(lbl_1_bss_32C->model[temp_r31->unk38 + 1], HU3D_MOTATTR_PAUSE);
            }
            if (lbl_1_bss_54 == 153) {
                Hu3DModelAttrSet(lbl_1_bss_32C->model[temp_r31->unk38 + 1], HU3D_MOTATTR_PAUSE);
            }
            if (lbl_1_bss_54 == 183) {
                Hu3DModelAttrReset(lbl_1_bss_32C->model[temp_r31->unk38 + 1], HU3D_MOTATTR_PAUSE);
            }
            if (lbl_1_bss_54 == 210) {
                spBC = 0;
                for (spC0 = 0; spC0 < 9; spC0++) {
                    spB8 = lbl_1_bss_330[spC0]->data;
                    spBC += (lbl_1_bss_51C[spB8->unk38].unk0C == 0 && spB8->unk5C == 0);
                }
                var_r28 = 7;
                HuAudFXPlayVol(0x7F7 + (temp_r31->unk08 != -1 ? temp_r31->unk08 : 8), 1651 / (spBC + 12));
            }
            if (lbl_1_bss_54 >= 210 && lbl_1_bss_54 <= 214) {
                s32 sp1AC[] = { 0, -12, -36, 0, 0, -12, -36, -48, 0 };
                float sp194[] = { 150.0f, 175.0f, 205.0f };
                float sp188[] = { 100.0f, 170.0f, 260.0f };

                spB4 = temp_r31->unk38 % 3 - 1;
                spB0 = temp_r31->unk38 / 3;
                spAC = (lbl_1_bss_54 - 210) / 4.0;
                temp_f26 = (lbl_1_bss_54 - 210) / 4.0;
                temp_f26 = (temp_f26 > 1.0f) ? 1.0f : temp_f26;
                espAttrReset(lbl_1_data_24[temp_r31->unk38], HUSPR_ATTR_DISPOFF);
                espPosSet(lbl_1_data_24[temp_r31->unk38],
                    290.0f + spB4 * sp194[spB0],
                    sp188[spB0] + 0.5 * (64.0f * (1.0f - spAC) * 0.5 + sp1AC[temp_r31->unk08 != -1 ? temp_r31->unk08 : 8]));
                espScaleSet(lbl_1_data_24[temp_r31->unk38], 0.5 * temp_f26, 0.5 * temp_f26);
            }
            if (lbl_1_bss_54 == 270) {
                Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_PAUSE);
                espAttrSet(lbl_1_data_24[temp_r31->unk38], HUSPR_ATTR_DISPOFF);
            }
            if (lbl_1_bss_54 == 290) {
                spA0 = 0;
                for (spA4 = 0; spA4 < 9; spA4++) {
                    sp9C = lbl_1_bss_330[spA4]->data;
                    spA0 += (lbl_1_bss_51C[sp9C->unk38].unk0C == 0 && sp9C->unk5C == 0);
                }
                spA8 = HuAudFXPlayVol(0x800 + (temp_r31->unk08 != -1 ? temp_r31->unk08 : 8), 1651 / (spA0 + 12));
                HuAudFXFadeOut(spA8, 0x9C4);
            }
            if (lbl_1_bss_54 >= 315) {
                arg0->trans.y -= 77.0f;
            }
            break;
        case 1007:
            if (temp_r31->unk00 == lbl_1_bss_38) {
                var_r28 = 8;
                if (temp_r31->unk00 >= 4 && temp_r31->unk08 != -1 && lbl_1_bss_54 == 1) {
                    HuAudFXPlay(0x809 + temp_r31->unk08);
                }
                if (temp_r31->unk08 == -1 && lbl_1_bss_54 == 1) {
                    HuAudFXPlay(0x3A);
                }
            } else if (arg0->trans.y < -40000.0f) {
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
            } else {
                arg0->trans.y -= 77.0f;
            }
            break;
    }
    switch (temp_r31->unk18) {
        case 0:
            temp_r31->unk1C++;
            break;
        case 1:
            temp_r31->unk1C++;
            if (temp_r31->unk1C <= 60) {
                arg0->rot.y = -180.0 * (temp_r31->unk1C / 60.0);
            } else {
                Hu3DMotionTimeSet(arg0->model[0], 120.0f);
                var_r28 = 0;
                temp_r31->unk18 = 0;
                temp_r31->unk1C = 0;
            }
            break;
        case 2:
            temp_r31->unk1C++;
            break;
        case 3:
            if (temp_r31->unk1C == 0) {
                temp_r31->unk48 = 6;
                temp_r31->unk4C = 0;
            }
            if (temp_r31->unk1C < 360) {
                temp_r24 = &Hu3DData[arg0->model[1]];
                if (temp_r31->unk1C == 0) {
                    Hu3DModelAttrReset(arg0->model[1], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y + 625.0f, arg0->trans.z);
                    Hu3DModelScaleSet(arg0->model[1], 0.1f, 0.1f, 0.1f);
                    Hu3DModelTPLvlSet(arg0->model[1], 1.0f);
                    temp_r31->unk4C = 0;
                    if (lbl_1_bss_18 == 0) {
                        HuAudFXPlay(0x7F4);
                        lbl_1_data_184 = HuAudFXPlay(0x7F3);
                    }
                    lbl_1_bss_18++;
                }
                temp_r24->rot.y = temp_r31->unk4C % 360;
                temp_r31->unk4C += 25;
                if (temp_r31->unk1C < 180) {
                    var_f20 = 0.0f;
                    var_f21 = 1.0f;
                } else {
                    var_f20 = 1.0f;
                    var_f21 = 0.5f;
                }
                temp_r24->scale.x = var_f20 + var_f21 * sind((float) (temp_r31->unk1C % 180));
                temp_r24->scale.y = temp_r24->scale.z = temp_r24->scale.x;
                if (temp_r31->unk1C < 180) {
                    temp_r31->unk1C += 6;
                } else {
                    temp_r31->unk1C += 18;
                }
                if (temp_r31->unk1C >= 360) {
                    temp_r31->unk1C = 360;
                    Hu3DModelRotSet(arg0->model[1], 0.0f, 0.0f, 0.0f);
                }
            } else {
                sp98 = &Hu3DData[arg0->model[1]];
                temp_r31->unk1C += 4;
                if (temp_r31->unk1C > 720) {
                    temp_r31->unk1C -= 360;
                }
                sp98->pos.y += 0.2f * sind(temp_r31->unk1C - 360);
                if (var_r22 != 0 || lbl_1_bss_0 == 0) {
                    lbl_1_bss_54 = 50;
                    temp_r31->unk18 = 4;
                    temp_r31->unk1C = 0;
                    var_r28 = 5;
                }
            }
            break;
        case 4:
            temp_r31->unk1C++;
            if (temp_r31->unk1C < 27) {
                break;
            }
            temp_r29 = &Hu3DData[arg0->model[1]];
            temp_r27 = temp_r31->unk1C - 27;
            if (temp_r27 == 0) {
                if (temp_r31->unk04 != -1) {
                    omVibrate(temp_r31->unk04, 12, 4, 2);
                }
                temp_r31->unk48 = -1;
                lbl_1_bss_18--;
                if (lbl_1_bss_18 == 0 && lbl_1_data_184 != -1) {
                    HuAudFXStop(lbl_1_data_184);
                    lbl_1_data_184 = -1;
                }
                HuAudFXPlay(0x7F5);
            }
            if (temp_r27 == 8) {
                if (temp_r31->unk54 == -1) {
                    lbl_1_bss_58 = temp_r31->unk00;
                    temp_r31->unk54 = fn_1_4474();
                    Hu3DParManPosSet(temp_r31->unk54, temp_r29->pos.x, temp_r29->pos.y, temp_r29->pos.z);
                    temp_r31->unk58 = 150;
                }
                Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF);
            } else if (temp_r27 > 8) {
                if (temp_r31->unk20 == 5) {
                    if (Hu3DMotionTimeGet(arg0->model[0]) >= Hu3DMotionMaxTimeGet(arg0->model[0])) {
                        var_r28 = 0;
                    }
                }
                if (temp_r27 <= 28) {
                    temp_f27 = (temp_r27 - 8) / 10.0;
                    sp94 = (temp_r27 - 8) * 18;
                    temp_f27 = (temp_f27 > 1.0f) ? 2.5 : (2.5 * temp_f27);
                    Hu3DModelAttrReset(arg0->model[temp_r31->unk44 + 2], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(arg0->model[temp_r31->unk44 + 2], temp_r29->pos.x, temp_r29->pos.y, temp_r29->pos.z);
                    Hu3DModelScaleSet(arg0->model[temp_r31->unk44 + 2], temp_f27, temp_f27, temp_f27);
                }
                if (temp_r27 >= 45 && temp_r27 <= 65) {
                    temp_f25 = (temp_r27 - 45) / 5.0;
                    sp90 = (temp_r27 - 45) * 18;
                    temp_f25 = (temp_f25 > 1.0f) ? 1.0f : temp_f25;
                    temp_f25 = 0.0f;
                    Hu3DModelAttrReset(arg0->model[temp_r31->unk44 + 2], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(arg0->model[temp_r31->unk44 + 2], temp_r29->pos.x, temp_r29->pos.y - 30.0f * temp_f25, temp_r29->pos.z);
                    temp_r31->unk1C += 5;
                }
                if (temp_r27 == 158) {
                    temp_r31->unk18 = 0;
                    temp_r31->unk1C = 0;
                }
            } else {
                if (temp_r27 < 4) {
                    temp_r29->pos.y += 10.0f + 0.5f * temp_r27;
                    temp_r29->scale.x += 0.1f * sind(4.0f * temp_r27);
                    temp_r29->scale.y = temp_r29->scale.z = temp_r29->scale.x;
                } else {
                    var_f24 = 255 - (temp_r27 << 5);
                    var_f24 = var_f24 * (1.0f / 255);
                    Hu3DModelTPLvlSet(arg0->model[1], var_f24);
                }
                temp_r29->pos.y += -0.49f * temp_r27 * temp_r27;
            }
            break;
        case 5:
            if (temp_r31->unk1C == 0) {
                Hu3DModelAttrReset(lbl_1_bss_32C->model[temp_r31->unk44 + 1], HU3D_MOTATTR_PAUSE);
                lbl_1_bss_51C[temp_r31->unk44].unk0C = 0;
                if (lbl_1_bss_35C->unk00 < 3) {
                    lbl_1_bss_35C->unk04[lbl_1_bss_35C->unk00] = 0.0f;
                    lbl_1_bss_35C->unk00++;
                }
            }
            temp_r31->unk1C++;
            if (temp_r31->unk1C == 60 && temp_r31->unk54 != -1) {
                Hu3DParManKill(temp_r31->unk54);
                temp_r31->unk54 = -1;
            }
            if (temp_r31->unk1C == 33) {
                Hu3DModelAttrSet(lbl_1_bss_32C->model[temp_r31->unk44 + 1], HU3D_MOTATTR_PAUSE);
            }
            if (temp_r31->unk1C == 63) {
                Hu3DModelAttrReset(lbl_1_bss_32C->model[temp_r31->unk44 + 1], HU3D_MOTATTR_PAUSE);
            }
            if (temp_r31->unk1C == 68 && lbl_1_bss_35C[1].unk00 < 3) {
                lbl_1_bss_35C[1].unk04[lbl_1_bss_35C[1].unk00] = 0.0f;
                lbl_1_bss_35C[1].unk00++;
            }
            if (temp_r31->unk1C == 130) {
                temp_r31->unk18 = 0;
                temp_r31->unk1C = 0;
            }
            break;
    }
    if ((temp_r31->unk18 == 3 || temp_r31->unk18 == 4) && temp_r31->unk48 >= 0) {
        temp_r31->unk48++;
        if (temp_r31->unk48 >= 6) {
            sp88 = temp_r31->unk44;
            for (sp8C = 0; sp8C < 50; sp8C++) {
                do {
                    temp_r31->unk44 = rand8() % 9;
                    if (temp_r31->unk44 >= 9) {
                        break;
                    }
                } while (lbl_1_bss_51C[temp_r31->unk44].unk0C == 0);
                if (sp88 != temp_r31->unk44) {
                    break;
                }
            }
            sp88 = temp_r31->unk44;
            temp_r31->unk48 = 0;
            Hu3DMotionTimeSet(arg0->model[1], 0.5 + sp88);
        }
    }
    if (temp_r31->unk24 >= 0) {
        var_r28 = temp_r31->unk24;
    }
    if (var_r28 >= 0 && var_r28 != temp_r31->unk20) {
        Hu3DMotionShiftSet(arg0->model[0],
            arg0->motion[var_r28],
            lbl_1_data_EC[var_r28],
            (temp_r31->unk08 != -1) ? lbl_1_data_C8[var_r28] : lbl_1_data_110[var_r28],
            (var_r28 == 7) ? HU3D_MOTATTR_PAUSE
                : (temp_r31->unk08 != -1 ? lbl_1_data_B4[var_r28] : lbl_1_data_BD[var_r28]) ? 0
                : HU3D_MOTATTR_LOOP);
        temp_r31->unk20 = var_r28;
    }
    temp_r31->unk58 -= (temp_r31->unk58 > -1);
    if (temp_r31->unk58 == 0) {
        if (temp_r31->unk54 != -1) {
            Hu3DParManKill(temp_r31->unk54);
            temp_r31->unk54 = -1;
        }
        temp_r31->unk58 = -1;
    }
}

s32 lbl_1_data_1A4[4] = { 0 };
s32 lbl_1_data_1B4 = -1;
float lbl_1_data_1B8 = 3500.0f;
float lbl_1_data_1BC = 100.0f;
float lbl_1_data_1C0 = -59.0f;

void fn_1_3264(omObjData* arg0) {
    float temp_f29;
    float var_f31;
    float temp_f26;
    float temp_f27;
    float temp_f28;
    StructBss330Data* spC[9];
    ModelData* temp_r29;
    ModelData* temp_r28;
    s32 var_r27;
    s32 i;
    s32 j;

    for (i = 0; i < 9; i++) {
        spC[i] = lbl_1_bss_330[i]->data;
    }
    lbl_1_bss_4++;
    switch (lbl_1_bss_50) {
        case 1002:
            lbl_1_bss_34++;
            lbl_1_bss_34 %= 360;
            /* fallthrough */
        case 1003:
            var_r27 = 0;
            for (i = 0; i < 4; i++) {
                if (spC[i]->unk50 == 0 || spC[i]->unk20 != 0) {
                    continue;
                }
                temp_r29 = &Hu3DData[lbl_1_bss_32C->model[spC[i]->unk38 + 1]];
                if (var_r27 == 0 && lbl_1_data_1A4[i] == 0) {
                    lbl_1_data_1A4[i] = 1;
                    var_r27 = 1;
                    HuAudFXPlay(0x7F6);
                }
                temp_r29->pos.y = 0.9 * temp_r29->pos.y + 0.1 * lbl_1_bss_51C[spC[i]->unk38].unk08;
                lbl_1_bss_330[i]->trans.y = temp_r29->pos.y - -16.666666666666668;
                lbl_1_bss_330[i]->rot.y = 0.0f;
            }
            break;
        case 1004:
            if (lbl_1_bss_54 <= 60) {
                temp_f29 = lbl_1_bss_54 / 60.0;
                temp_f29 = 1.0f - (1.0f - temp_f29) * (1.0f - temp_f29);
                if (lbl_1_bss_54 == 0) {
                    lbl_1_bss_51C[spC[0]->unk38].unk08 = -16.666666f;
                }
                for (i = 0; i < 9; i++) {
                    temp_r28 = &Hu3DData[lbl_1_bss_32C->model[i + 1]];
                    Hu3DModelPosSet(lbl_1_bss_32C->model[i + 1],
                        (500.0 + 200.0f * temp_f29) * (lbl_1_bss_51C[i].unk00 - 1),
                        0.9 * temp_r28->pos.y + 0.1 * lbl_1_bss_51C[spC[0]->unk38].unk08,
                        (500.0 + 200.0f * temp_f29) * (lbl_1_bss_51C[i].unk04 - 1));
                    for (j = 0; j < 9; j++) {
                        if (i == spC[j]->unk38) {
                            lbl_1_bss_330[j]->trans.x = (500.0 + 200.0f * temp_f29) * (lbl_1_bss_51C[i].unk00 - 1);
                            lbl_1_bss_330[j]->trans.y = temp_r28->pos.y - -16.666666666666668;
                            lbl_1_bss_330[j]->trans.z = (500.0 + 200.0f * temp_f29) * (lbl_1_bss_51C[i].unk04 - 1);
                        }
                    }
                }
            }
            break;
    }
    {
        s32 var_r26 = lbl_1_data_1B4;
        float sp30[][6] = {
            { 3500.0f, 0.0f, 100.0f, 0.0f, -59.0f, 0.0f },
            { 3200.0f, 0.0f, 100.0f, 0.0f, -30.0f, 0.0f },
            { 3800.0f, 0.0f, 100.0f, 0.0f, -30.0f, 0.0f },
            { 2000.0f, 0.0f, 200.0f, 0.0f, -30.0f, 0.0f },
            { 4000.0f, 0.0f, 200.0f, 0.0f, -89.0f, 0.0f },
            { 2700.0f, 0.0f, 200.0f, 0.0f, -30.0f, 0.0f }
        };

        if (lbl_1_bss_38 != -1 && lbl_1_bss_38 != 9) {
            sp30[5][1] = lbl_1_bss_330[lbl_1_bss_38]->trans.x;
            sp30[5][3] = lbl_1_bss_330[lbl_1_bss_38]->trans.z;
        }
        if (lbl_1_data_1B4 == -1) {
            lbl_1_data_1B4 = 0;
            lbl_1_bss_1C = 1;
            lbl_1_bss_20 = 1.0f;
        }
        if (lbl_1_data_1B4 == 0) {
            lbl_1_data_1B4 = 1;
            lbl_1_bss_1C = 1;
            lbl_1_bss_20 = 0.5f;
        }
        if (lbl_1_bss_50 == 1004 && lbl_1_bss_54 >= 1 && lbl_1_data_1B4 == 1) {
            lbl_1_data_1B4 = 2;
            lbl_1_bss_1C = 0;
            lbl_1_bss_20 = 0.0f;
        }
        if (lbl_1_bss_50 == 1006 && lbl_1_bss_54 >= 270 && lbl_1_data_1B4 == 2) {
            lbl_1_data_1B4 = 4;
            lbl_1_bss_1C = 1;
            lbl_1_bss_20 = 1.0f;
        }
        if (lbl_1_bss_50 == 1005 && lbl_1_data_1B4 == 4) {
            lbl_1_data_1B4 = 2;
            lbl_1_bss_1C = 0;
            lbl_1_bss_20 = 0.0f;
        }
        if (lbl_1_bss_50 == 1007 && lbl_1_bss_38 != 9 && lbl_1_data_1B4 == 4) {
            lbl_1_data_1B4 = 5;
            lbl_1_bss_1C = 0;
            lbl_1_bss_20 = 0.0f;
        }
        if (var_r26 != lbl_1_data_1B4 && var_r26 != -1) {
            lbl_1_data_1B8 = CZoom;
            lbl_1_data_1BC = Center.y;
            lbl_1_bss_28 = Center.z;
            lbl_1_data_1C0 = CRot.x;
            lbl_1_bss_2C = CRot.y;
        }
        if (lbl_1_bss_20 <= 1.0f) {
            if (lbl_1_bss_1C == 0) {
                lbl_1_bss_20 = 1.0 - 0.95 * (1.0f - lbl_1_bss_20);
                var_f31 = lbl_1_bss_20;
            } else {
                lbl_1_bss_20 += 0.008333333333333333;
                lbl_1_bss_20 = (lbl_1_bss_20 > 1.0f) ? 1.0f : lbl_1_bss_20;
                var_f31 = 0.5 + -0.5 * cosd(180.0f * lbl_1_bss_20);
            }
            lbl_1_bss_20 = (lbl_1_bss_20 > 1.0f) ? 1.0f : lbl_1_bss_20;
            CZoom = var_f31 * sp30[lbl_1_data_1B4][0] + lbl_1_data_1B8 * (1.0f - var_f31);
            Center.x = var_f31 * sp30[lbl_1_data_1B4][1] + lbl_1_bss_24 * (1.0f - var_f31);
            Center.y = var_f31 * sp30[lbl_1_data_1B4][2] + lbl_1_data_1BC * (1.0f - var_f31);
            Center.z = var_f31 * sp30[lbl_1_data_1B4][3] + lbl_1_bss_28 * (1.0f - var_f31);
            CRot.x = var_f31 * sp30[lbl_1_data_1B4][4] + lbl_1_data_1C0 * (1.0f - var_f31);
            CRot.y = var_f31 * sp30[lbl_1_data_1B4][5] + lbl_1_bss_2C * (1.0f - var_f31);
        }
    }
    if (lbl_1_bss_50 == 1001 || lbl_1_bss_50 == 1003) {
        temp_f26 = 0.0f;
        temp_f27 = 0.0f;
        if (lbl_1_data_134.unk00 % 2 >= 0) {
            lbl_1_data_134.unk08 = lbl_1_data_134.unk10;
            lbl_1_data_134.unk0C = lbl_1_data_134.unk14;
            do {
                lbl_1_data_134.unk10 = 2.0 * (rand8() / 255.0) - 1.0;
                lbl_1_data_134.unk14 = 2.0 * (rand8() / 255.0) - 1.0;
                lbl_1_data_134.unk10 = 0.0f;
                temp_f28 = (lbl_1_data_134.unk10 - lbl_1_data_134.unk08) * (lbl_1_data_134.unk10 - lbl_1_data_134.unk08) + (lbl_1_data_134.unk14 - lbl_1_data_134.unk0C) * (lbl_1_data_134.unk14 - lbl_1_data_134.unk0C);
            } while (sqrtf(temp_f28) < 0.75);
        }
        lbl_1_data_134.unk04 = (lbl_1_data_134.unk04 > 24) ? 24
            : (lbl_1_data_134.unk04 > 0) ? lbl_1_data_134.unk04 : 0;
        temp_f26 = lbl_1_data_134.unk08;
        temp_f27 = lbl_1_data_134.unk0C;
        temp_f26 *= lbl_1_data_134.unk04 * 2;
        temp_f27 *= lbl_1_data_134.unk04 * 2;
        lbl_1_data_134.unk00 = !lbl_1_data_134.unk00;
        lbl_1_data_134.unk04 = (lbl_1_data_134.unk04 > 24) ? 23
            : (lbl_1_data_134.unk04 - 1 > 0) ? (lbl_1_data_134.unk04 - 1) : 0;
        Center.x = 0.0f;
        Center.y = 100.0f + temp_f27;
    }
}

s16 fn_1_4474(void) {
    AnimData* var_r29;
    void* var_r28;
    s16 var_r31;
    s16 var_r30;
    HsfanimStruct00 sp8 = {
        0x96,
        { 0x00, 0x00 },
        50.0f,
        0.0f,
        65.0f,
        { 0.0f, -0.195f, 0.0f },
        80.0f,
        0.99f,
        40.0f,
        0.999f,
        4,
        {
            { 0xFF, 0xFF, 0x20, 0xFF },
            { 0xFF, 0xFF, 0x00, 0xFF },
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

    lbl_1_bss_5C[lbl_1_bss_58] = sp8;
    var_r28 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_BOARD, 107), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r29 = HuSprAnimRead(var_r28);
    var_r31 = Hu3DParManCreate(var_r29, 40, &lbl_1_bss_5C[lbl_1_bss_58]);
    Hu3DParManAttrSet(var_r31, 8 | 0x100);
    Hu3DParManRotSet(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DParManVecSet(var_r31, 0.0f, 0.4f, 0.2f);
    var_r30 = Hu3DParManModelIDGet(var_r31);
    Hu3DModelLayerSet(var_r30, 2);
    Hu3DParticleBlendModeSet(var_r30, 0);
    return var_r31;
}

void fn_1_45F8(omObjData* arg0) {
    StructBss330Data* sp14[9];
    float spC[2];
    s32 sp8;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r30;
    s32 i;

    for (i = 0; i < 28; i++) {
        s32 sp38[] = {
            0x7F1, 0x7F2, 0x7F7, 0x7F8,
            0x7F9, 0x7FA, 0x7FB, 0x7FC,
            0x7FD, 0x7FE, 0x7FF, 0x800,
            0x801, 0x802, 0x803, 0x804,
            0x7FB, 0x7FC, 0x7FD, 0x7FE,
            0x7FF, 0x800, 0x801, 0x802,
            0x803, 0x804, 0x7FB, 0x7FC
        };

        if (lbl_1_bss_35C[i].unk00 > 3) {
            lbl_1_bss_35C[i].unk00 = 3;
        }
        if (lbl_1_bss_35C[i].unk00 > 0) {
            sp8 = HuAudFXPlay(sp38[i]);
            lbl_1_bss_35C[i].unk00--;
        }
    }
    for (i = 0; i < 9; i++) {
        sp14[i] = lbl_1_bss_330[i]->data;
    }
    if (omSysExitReq != 0 && WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        arg0->func = fn_1_659C;
    }
    switch (lbl_1_bss_50) {
        case 1000:
            if (WipeStatGet() != 0) {
                break;
            }
            lbl_1_bss_50++;
            lbl_1_bss_54 = 0;
            for (i = 0; i < 9; i++) {
                if (sp14[i]->unk54 != -1) {
                    Hu3DParManKill(sp14[i]->unk54);
                    sp14[i]->unk54 = -1;
                }
            }
            break;
        case 1001:
            lbl_1_bss_54++;
            if (lbl_1_bss_54 == 90 && lbl_1_data_14C < 0) {
                lbl_1_data_14C = MGSeqStartCreate();
            }
            if (lbl_1_bss_54 >= 90 && lbl_1_data_150 == -1 && (MGSeqStatGet(lbl_1_data_14C) & 0x10)) {
                lbl_1_data_150 = HuAudSeqPlay(0x49);
            }
            if (lbl_1_bss_54 >= 90 && MGSeqStatGet(lbl_1_data_14C) == 0 && lbl_1_data_14C >= 0) {
                lbl_1_bss_50 = 1002;
                lbl_1_bss_54 = 0;
            }
            break;
        case 1002:
            lbl_1_bss_54 += (lbl_1_bss_54 < 30);
            if (lbl_1_bss_54 >= 60) {
                lbl_1_bss_50++;
                lbl_1_bss_54 = 0;
            }
            break;
        case 1003:
            lbl_1_bss_54++;
            if (lbl_1_bss_54 == (sp14[1]->unk08 == -1 ? 120 : 60) + 30) {
                lbl_1_bss_50++;
                if (sp14[1]->unk08 == -1) {
                    lbl_1_bss_50++;
                }
                lbl_1_bss_54 = 0;
            }
            break;
        case 1004:
            lbl_1_bss_54++;
            if (lbl_1_bss_54 == 90) {
                lbl_1_bss_50++;
                lbl_1_bss_54 = 0;
            }
            break;
        case 1005:
            if (lbl_1_bss_54 == 0) {
                for (i = 0; i < 9; i++) {
                    if (lbl_1_bss_51C[sp14[i]->unk38].unk0C != 0) {
                        sp14[i]->unk18 = 3;
                        sp14[i]->unk1C = 0;
                    } else {
                        sp14[i]->unk5C = 1;
                    }
                }
                HuWinMesMaxSizeGet(1, spC, MAKE_MESSID(48, 37));
                lbl_1_bss_C = HuWinCreate(-10000.0f, 400.0f, spC[0], spC[1], 1);
                HuWinBGTPLvlSet(lbl_1_bss_C, 0.0f);
                HuWinMesSpeedSet(lbl_1_bss_C, 0);
                HuWinMesSet(lbl_1_bss_C, MAKE_MESSID(48, 37));
                lbl_1_bss_0 = 180;
            }
            lbl_1_bss_54++;
            if (lbl_1_bss_54 == 30) {
                lbl_1_data_14E = MGSeqTimerCreate(10);
                MGSeqPosSet(lbl_1_data_14E, 489.6f, 64.0f);
            }
            if (lbl_1_bss_54 >= 30 && lbl_1_data_14E != -1) {
                var_r29 = 0;
                for (i = 0; i < 9; i++) {
                    if (lbl_1_bss_51C[sp14[i]->unk38].unk0C == 0 || sp14[i]->unk18 == 4 || sp14[i]->unk18 == 0) {
                        var_r29++;
                    }
                }
                if (var_r29 >= 9 || lbl_1_bss_0 == 0) {
                    MGSeqParamSet(lbl_1_data_14E, 2, -1);
                    lbl_1_data_14E = -1;
                } else {
                    lbl_1_bss_0 -= (lbl_1_bss_0 > 0);
                    MGSeqParamSet(lbl_1_data_14E, 1, (lbl_1_bss_0 + 59) / 60);
                }
            }
            var_r28 = 0;
            for (i = 0; i < 9; i++) {
                if (lbl_1_bss_51C[sp14[i]->unk38].unk0C == 0 || sp14[i]->unk18 == 0) {
                    var_r28++;
                }
            }
            if (var_r28 >= 9) {
                lbl_1_bss_50++;
                lbl_1_bss_54 = 0;
            }
            break;
        case 1006:
            if (lbl_1_bss_54 == 1) {
                HuWinExCleanup(lbl_1_bss_C);
            }
            lbl_1_bss_54++;
            if (lbl_1_bss_54 == 3) {
                lbl_1_bss_54 = 118;
            }
            if (lbl_1_bss_54 == 223) {
                lbl_1_bss_54 = 233;
            }
            if (lbl_1_bss_54 == 120 && lbl_1_bss_35C->unk00 < 3) {
                lbl_1_bss_35C->unk04[lbl_1_bss_35C->unk00] = 0.0f;
                lbl_1_bss_35C->unk00++;
            }
            if (lbl_1_bss_54 == 188 && lbl_1_bss_35C[1].unk00 < 3) {
                lbl_1_bss_35C[1].unk04[lbl_1_bss_35C[1].unk00] = 0.0f;
                lbl_1_bss_35C[1].unk00++;
            }
            if (lbl_1_bss_54 == 360) {
                var_r30 = 0;
                var_r27 = -1;
                for (i = 0; i < 9; i++) {
                    var_r30 += lbl_1_bss_51C[i].unk0C;
                    var_r27 = (lbl_1_bss_51C[sp14[i]->unk38].unk0C != 0) ? i : var_r27;
                }
                if (var_r30 <= 1) {
                    lbl_1_bss_38 = (var_r30 == 0) ? 9 : var_r27;
                }
                if (lbl_1_bss_38 != -1) {
                    lbl_1_data_14C = MGSeqFinishCreate();
                    if (lbl_1_data_150 != -1) {
                        HuAudSeqFadeOut(lbl_1_data_150, 100);
                    }
                }
            }
            if (lbl_1_bss_54 >= 480) {
                if (lbl_1_bss_38 != -1) {
                    if (MGSeqStatGet(lbl_1_data_14C) == 0 && lbl_1_bss_54 >= 510) {
                        lbl_1_bss_50 = 1007;
                        lbl_1_bss_54 = 0;
                    }
                } else {
                    lbl_1_bss_50 = 1005;
                    lbl_1_bss_54 = 0;
                }
            }
            break;
        case 1007:
            lbl_1_bss_54++;
            if (lbl_1_bss_54 == 1) {
                if (lbl_1_bss_38 != 9) {
                    if (lbl_1_bss_38 < 9) {
                        HuAudSStreamPlay(1);
                    } else {
                        HuAudSStreamPlay(1);
                    }
                    if (lbl_1_bss_38 < 4 && sp14[lbl_1_bss_38]->unk04 != -1) {
                        GWPlayerCoinWinSet(sp14[lbl_1_bss_38]->unk04, 10);
                    }
                } else if (lbl_1_bss_38 == 9) {
                    HuAudSStreamPlay(4);
                }
            }
            if (210.0f + (lbl_1_bss_38 == 9 ? 60 : 0) < lbl_1_bss_54) {
                if (lbl_1_data_154 != -1) {
                    HuAudFXStop(lbl_1_data_154);
                    lbl_1_data_154 = -1;
                }
                lbl_1_data_14C = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                arg0->func = fn_1_659C;
            }
            break;
    }
}

void fn_1_53A0(omObjData* arg0) {
    StructBss330Data* sp50[9];
    s32 i;

    for (i = 0; i < 9; i++) {
        sp50[i] = lbl_1_bss_330[i]->data;
    }
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M458, 8));
    Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(arg0->model[0], 0.1f);
    for (i = 0; i < 9; i++) {
        arg0->model[i + 1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M458, 10 + i));
        lbl_1_bss_51C[i].unk00 = i % 3;
        lbl_1_bss_51C[i].unk04 = i / 3;
        lbl_1_bss_51C[i].unk08 = 0.0f;
        lbl_1_bss_51C[i].unk0C = 1;
        Hu3DModelPosSet(lbl_1_bss_32C->model[i + 1],
            500.0 * (lbl_1_bss_51C[i].unk00 - 1),
            -16.666666f,
            500.0 * (lbl_1_bss_51C[i].unk04 - 1));
        Hu3DModelScaleSet(lbl_1_bss_32C->model[i + 1], 1.6666666f, 1.6666666f, 1.6666666f);
        Hu3DModelAttrSet(arg0->model[i + 1], HU3D_MOTATTR_PAUSE);
        Hu3DModelShadowMapSet(arg0->model[i + 1]);
        Hu3DModelLayerSet(arg0->model[i + 1], 1);
    }
    for (i = 0; i < 9; i++) {
        s32 sp2C[9] = { 288, 290 };
        s32 sp8[9] = { 240, 140 };

        lbl_1_data_24[i] = espEntry(lbl_1_data_0[i], 0, 0);
        espDrawNoSet(lbl_1_data_24[i], 0);
        espAttrSet(lbl_1_data_24[i], HUSPR_ATTR_NOANIM | HUSPR_ATTR_DISPOFF);
        espBankSet(lbl_1_data_24[i], 0);
        espPriSet(lbl_1_data_24[i], 0x80 - i);
        espPosSet(lbl_1_data_24[i], 290.0f, 140.0f);
        espTPLvlSet(lbl_1_data_24[i], 1.0f);
    }
    arg0->func = fn_1_3264;
}

s32 lbl_1_data_1E4[] = {
    DATA_MAKE_NUM(DATADIR_M458, 19),
    DATA_MAKE_NUM(DATADIR_M458, 20),
    DATA_MAKE_NUM(DATADIR_M458, 21),
    DATA_MAKE_NUM(DATADIR_M458, 22),
    DATA_MAKE_NUM(DATADIR_M458, 23),
    DATA_MAKE_NUM(DATADIR_M458, 24),
    DATA_MAKE_NUM(DATADIR_M458, 25),
    DATA_MAKE_NUM(DATADIR_M458, 26),
    DATA_MAKE_NUM(DATADIR_M458, 27),
    DATA_MAKE_NUM(DATADIR_M458, 28),
    DATA_MAKE_NUM(DATADIR_M458, 29)
};

void fn_1_5850(omObjData* arg0) {
    StructBss330Data* temp_r31;
    s32 sp10[] = { 0, 1, 2, 3 };
    s32 var_r25;
    s32 var_r28;
    s32 i;
    s32 j;

    var_r25 = 0;
    temp_r31 = arg0->data;
    memset(temp_r31, 0, sizeof(*temp_r31));
    temp_r31->unk00 = arg0->work[0];
    if (temp_r31->unk00 >= 4) {
        var_r28 = -1;
        for (i = 0; i <= temp_r31->unk00 - 4; i++) {
            do {
                var_r28++;
            } while (GWPlayerCfg[0].character == var_r28 || GWPlayerCfg[1].character == var_r28 || GWPlayerCfg[2].character == var_r28 || GWPlayerCfg[3].character == var_r28);
        }
        temp_r31->unk08 = (var_r28 == 8) ? -1 : var_r28;
        temp_r31->unk0C = -1;
        temp_r31->unk04 = -1;
        temp_r31->unk10 = 0;
    } else {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (i == GWPlayerCfg[j].group) {
                    sp10[var_r25] = j;
                    var_r25++;
                }
            }
        }
        temp_r31->unk00 = arg0->work[0];
        temp_r31->unk04 = sp10[temp_r31->unk00];
        if (temp_r31->unk04 == 4) {
            OSReport("m463:wrong player group\n");
            temp_r31->unk04 = temp_r31->unk00;
        }
        temp_r31->unk08 = GWPlayerCfg[temp_r31->unk04].character;
        temp_r31->unk0C = (temp_r31->unk08 == -1 || GWPlayerCfg[temp_r31->unk04].iscom) ? -1 : GWPlayerCfg[temp_r31->unk04].pad_idx;
        temp_r31->unk10 = (temp_r31->unk0C != -1) ? 0 : GWPlayerCfg[temp_r31->unk04].diff;
    }
    temp_r31->unk18 = 0;
    temp_r31->unk20 = 3;
    temp_r31->unk24 = -1;
    temp_r31->unk48 = -1;
    if (temp_r31->unk08 != -1) {
        arg0->model[0] = CharModelCreate(temp_r31->unk08, 4);
    } else {
        arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_BKOOPA, 7));
    }
    omSetTra(arg0, 0.0f, temp_r31->unk00 == 0 ? 0 : 300, 0.0f);
    if (temp_r31->unk08 != -1) {
        omSetSca(arg0, 2.5f, 2.5f, 2.5f);
    } else {
        omSetSca(arg0, 2.0f, 2.0f, 2.0f);
    }
    for (i = 0; i < 9; i++) {
        if (temp_r31->unk08 != -1) {
            if (temp_r31->unk00 < 4 || (i != 1 && i != 2)) {
                arg0->motion[i] = CharModelMotionCreate(temp_r31->unk08, lbl_1_data_48[i] + (lbl_1_data_6C[i] ? temp_r31->unk08 : 0));
            }
        } else if (lbl_1_data_90[i] != 0) {
            arg0->motion[i] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_90[i]);
        }
    }
    Hu3DMotionSet(arg0->model[0], arg0->motion[temp_r31->unk20]);
    Hu3DMotionTimeSet(arg0->model[0], 10.0f);
    Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(arg0->model[0]);
    Hu3DModelAttrSet(arg0->model[0], 1U);
    Hu3DModelLayerSet(arg0->model[0], 1);
    CharModelLayerSetAll2(1);
    if (temp_r31->unk08 != -1) {
        CharModelDataClose(temp_r31->unk08);
    }
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M458, 9));
    Hu3DModelAttrSet(arg0->model[1], HU3D_MOTATTR_LOOP);
    Hu3DModelPosSet(arg0->model[1], 0.0f, 400.0f, 0.0f);
    Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(arg0->model[1], 1);
    Hu3DMotionSpeedSet(arg0->model[1], 0.0f);
    for (i = 0; i < 9; i++) {
        if (temp_r31->unk00 == 0) {
            arg0->model[i + 2] = Hu3DModelCreateFile(lbl_1_data_1E4[i]);
        } else {
            arg0->model[i + 2] = Hu3DModelLink(lbl_1_bss_330[0]->model[i + 2]);
        }
        Hu3DMotionTimeSet(arg0->model[i + 2], 10.0f);
        Hu3DMotionSpeedSet(arg0->model[i + 2], 0.0f);
        Hu3DModelAttrSet(arg0->model[i + 2], HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(arg0->model[i + 2], 1);
    }
    lbl_1_bss_58 = temp_r31->unk00;
    temp_r31->unk54 = fn_1_4474();
    Hu3DParManPosSet(temp_r31->unk54, 10000.0f, -10000.0f, 10000.0f);
    arg0->func = fn_1_4C8;
}

void fn_1_60A4(omObjData* arg0) {
    lbl_1_bss_50 = 1000;
    lbl_1_bss_54 = 0;
    lbl_1_bss_48 = 0;
    lbl_1_bss_44 = 0;
    lbl_1_data_154 = HuAudFXPlay(0x6D7);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    arg0->func = fn_1_45F8;
}

void ObjectSetup(void) {
    omObjData* var_r30;
    s32 i;

    OSReport("******* M463 ObjectSetup *********\n");
    lbl_1_bss_40 = omInitObjMan(600, 0x2000);
    omGameSysInit(lbl_1_bss_40);
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
        GXColor sp8 = { 0xFF, 0xFF, 0xFF, 0xFF };

        lbl_1_bss_3C = Hu3DGLightCreateV(&sp3C, &sp30, &sp8);
    }
    Hu3DGLightStaticSet(lbl_1_bss_3C, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_3C);
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
    lbl_1_data_14C = -1;
    lbl_1_bss_38 = -1;
    HuWinInit(1);
    lbl_1_bss_32C = omAddObjEx(lbl_1_bss_40, 0x65, 10, 0, 1, fn_1_53A0);
    for (i = 0; i < 9; i++) {
        var_r30 = lbl_1_bss_330[i] = omAddObjEx(lbl_1_bss_40, 100, 11, 9, 0, fn_1_5850);
        var_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(StructBss330Data), MEMORY_DEFAULT_NUM);
        var_r30->work[0] = i;
    }
    lbl_1_bss_354 = omAddObjEx(lbl_1_bss_40, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_358 = omAddObjEx(lbl_1_bss_40, 103, 0, 0, -1, fn_1_60A4);
}

void fn_1_659C(omObjData* arg0) {
    StructBss330Data* spC[9];
    void* sp8;
    s32 var_r31;
    s32 var_r30;

    for (var_r31 = 0; var_r31 < 9; var_r31++) {
        spC[var_r31] = lbl_1_bss_330[var_r31]->data;
        if (spC[var_r31]->unk54 != -1) {
            Hu3DParManKill(spC[var_r31]->unk54);
            spC[var_r31]->unk54 = -1;
        }
    }
    if (WipeStatGet() == 0) {
        for (var_r30 = 0; var_r30 < 9; var_r30++) {
            sp8 = lbl_1_bss_330[var_r30]->data;
        }
        if (lbl_1_data_14C >= 0) {
            MGSeqKill(lbl_1_data_14C);
        }
        MGSeqKillAll();
        HuAudAllStop();
        omOvlReturnEx(1, 1);
    }
}
