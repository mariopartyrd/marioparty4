#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/sprite.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"
#include "string.h"

#include "ext_math.h"

s32 rand8(void);

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
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ s32 unk4C;
} StructBss68Data; // Size 0x50

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ float unk04[3];
} StructBss78; // Size 0x10

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
} StructData28C; // Size 0x18

void fn_1_7AE4(omObjData* arg0);

StructBss78 lbl_1_bss_78[5];
omObjData* lbl_1_bss_74;
omObjData* lbl_1_bss_70;
omObjData* lbl_1_bss_68[2];
omObjData* lbl_1_bss_64;
s32 lbl_1_bss_60;
s32 lbl_1_bss_5C;
char lbl_1_bss_58[4]; // unused
s32 lbl_1_bss_54;
s32 lbl_1_bss_50;
Process* lbl_1_bss_4C;
s32 lbl_1_bss_48;
s32 lbl_1_bss_44;
s32 lbl_1_bss_40;
s32 lbl_1_bss_3C;
char lbl_1_bss_38[4]; // unused
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
char lbl_1_bss_8[8]; // unused
s32 lbl_1_bss_4;
char lbl_1_bss_0[4]; // unused

s32 lbl_1_data_0[] = {
    DATA_MAKE_NUM(DATADIR_M457, 23),
    DATA_MAKE_NUM(DATADIR_M457, 22),
    DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0),
    DATA_MAKE_NUM(DATADIR_M457, 23),
    DATA_MAKE_NUM(DATADIR_M457, 22),
    DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0),
    DATA_MAKE_NUM(DATADIR_M457, 27),
    DATA_MAKE_NUM(DATADIR_M457, 28),
    DATA_MAKE_NUM(DATADIR_M457, 25),
    DATA_MAKE_NUM(DATADIR_M457, 25),
    DATA_MAKE_NUM(DATADIR_M457, 25),
    DATA_MAKE_NUM(DATADIR_M457, 25),
    DATA_MAKE_NUM(DATADIR_M457, 25)
};

s32 lbl_1_data_5C[23] = { 0 };

s32 lbl_1_data_B8[] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 5),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 6),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 112),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 111),
    DATA_MAKE_NUM(DATADIR_M457, 8),
    DATA_MAKE_NUM(DATADIR_M457, 0),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 12),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 13),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 21),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 23),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 24)
};

u32 lbl_1_data_E8[] = { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 };

u32 lbl_1_data_118[] = {
    DATA_MAKE_NUM(DATADIR_BKOOPA, 8),
    DATA_MAKE_NUM(DATADIR_BKOOPA, 10),
    0,
    DATA_MAKE_NUM(DATADIR_M457, 31),
    DATA_MAKE_NUM(DATADIR_M457, 32),
    DATA_MAKE_NUM(DATADIR_M457, 33),
    DATA_MAKE_NUM(DATADIR_M457, 34),
    DATA_MAKE_NUM(DATADIR_M457, 35),
    DATA_MAKE_NUM(DATADIR_M457, 36),
    DATA_MAKE_NUM(DATADIR_M457, 37),
    DATA_MAKE_NUM(DATADIR_M457, 29),
    DATA_MAKE_NUM(DATADIR_M457, 30)
};

u8 lbl_1_data_148[12] = { 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1 };
s32 lbl_1_data_154[12] = { 8, 0, 0, 8, 5, 8, 4, 2, 2, 8, 8, 8 };
s32 lbl_1_data_184[12] = { 0 };

float lbl_1_data_1B4[][3] = {
    {   0.0f,   0.0f,   0.0f },
    {   0.0f,   0.0f,   0.0f },
    {  20.0f,  60.0f,  20.0f },
    {  20.0f,  70.0f,  20.0f },
    {  20.0f,  20.0f,  20.0f },
    {  50.0f, -70.0f,   0.0f },
    {  20.0f,  60.0f,  20.0f },
    { 100.0f,   0.0f,  50.0f },
    { -70.0f, -70.0f, -70.0f }
};

float lbl_1_data_220[][3] = {
    {  1.5f,  45.0f, 270.0f },
    {  1.7f,  45.0f, 270.0f },
    {  1.8f,  45.0f, 270.0f },
    {  1.6f,  45.0f, 270.0f },
    {  1.7f,   5.0f, 270.0f },
    {  2.0f, -85.0f, 295.0f },
    {  1.8f,  45.0f, 270.0f },
    {  2.0f,  40.0f, 330.0f },
    { 2.25f, -30.0f, 300.0f }
};

StructData28C lbl_1_data_28C = { 0 };

s16 lbl_1_data_2A4 = -1;
s16 lbl_1_data_2A6 = -1;
s32 lbl_1_data_2A8 = -1;
s32 lbl_1_data_2AC = -1;
s16 lbl_1_data_2B0 = -1;
s32 lbl_1_data_2B4 = -1;
s32 lbl_1_data_2B8 = 600;

void fn_1_A0(void) {
    Center.x += 10.0 * (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) - ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0));
    Center.z -= 10.0 * (((HuPadBtn[0] & PAD_BUTTON_UP) != 0) - ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0));
    Center.y += 10.0 * (((HuPadBtn[0] & PAD_BUTTON_Y) != 0) - ((HuPadBtn[0] & PAD_BUTTON_X) != 0));
    CZoom += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_X) != 0) - ((HuPadBtn[0] & PAD_BUTTON_Y) != 0));
    CRot.y += HuPadSubStkX[0] / 16.0;
    CRot.x += HuPadSubStkY[0] / -16.0;
    print8(64, 392, 1.0f, "%f,%f,%f", Center.x, Center.y, Center.z);
    print8(64, 408, 1.0f, "%f,%f,%f", CRot.x, CRot.y, CRot.z);
    print8(64, 424, 1.0f, "%f", CZoom);
}

void fn_1_46C(omObjData* arg0) {
    s16 var_r29;
    s16 var_r26;
    s16 var_r22;
    s32 var_r20;
    s32 var_r25;
    s32 var_r24;
    Vec sp104;
    float spFC[2];
    float spE8;
    float spE4;
    float spE0;
    float temp_f31;
    s32 spDC;
    s32 spD8;
    s32 sp20;
    s32 temp_r19;
    s32 temp_r21;
    char* var_r18;
    StructBss68Data* temp_r31;
    StructBss68Data* temp_r28;
    ModelData* spD4;
    s32 i;

    temp_r31 = arg0->data;
    temp_r28 = lbl_1_bss_68[1 - arg0->work[0]]->data;
    spE8 = 0.0f;
    spE4 = 0.0f;
    spE0 = 0.0f;
    spDC = 0;
    var_r29 = -1;
    var_r26 = -1;
    var_r22 = -1;
    var_r20 = (temp_r31->unk0C == -1) ? 0
        : ((HuPadBtnDown[temp_r31->unk0C] & 0x100) > 0);
    var_r25 = (temp_r31->unk0C == -1) ? 0
        : ((HuPadBtnDown[temp_r31->unk0C] & 0x20) > 0);
    var_r24 = (temp_r31->unk0C == -1) ? 0
        : ((HuPadBtnDown[temp_r31->unk0C] & 0x40) > 0);
    if (temp_r31->unk0C == -1) {
        temp_r31->unk3C--;
        if (temp_r31->unk3C <= 0) {
            if (temp_r31->unk14 == 1) {
                var_r20 = 1;
            } else {
                var_r25 = var_r24 = 1;
            }
            if (temp_r31->unk14 >= 8 || (temp_r31->unk14 >= 3 && temp_r31->unk18 >= 10)) {
                switch (temp_r31->unk10) {
                    case 0:
                        temp_r31->unk3C = rand8() % 14 + 4
                            + (temp_r31->unk14 != 8 ? 28 - temp_r31->unk18 : 0);
                        break;
                    case 1:
                        temp_r31->unk3C = rand8() % 9 + 4
                            + (temp_r31->unk14 != 8 ? 28 - temp_r31->unk18 : 0);
                        break;
                    case 2:
                        temp_r31->unk3C = rand8() % 10 + 12
                            + ((temp_r31->unk14 != 8 && temp_r31->unk18 >= 9 && temp_r31->unk18 <= 13) ? 13 - temp_r31->unk18 : 0);
                        break;
                    case 3:
                        temp_r31->unk3C = rand8() % 5 + 4
                            + ((temp_r31->unk14 != 8 && temp_r31->unk18 >= 2 && temp_r31->unk18 <= 17) ? 17 - temp_r31->unk18 : 0);
                        if (temp_r28->unk1C > 0 || temp_r31->unk14 == 7) {
                            var_r24 = var_r25 = 0;
                        }
                        break;
                }
            }
        }
    }
    if (temp_r31->unk38 == 0) {
        var_r24 = 0;
    }
    if (temp_r31->unk38 == 1) {
        var_r25 = 0;
    }
    if (temp_r31->unk20 > 0) {
        var_r20 = 0;
        temp_r31->unk20--;
    } else if (var_r20 != 0) {
        temp_r31->unk20 = 20;
    }
    if (temp_r31->unk24 > 0) {
        var_r24 = 0;
        temp_r31->unk24--;
    } else if (var_r24 != 0) {
        temp_r31->unk24 = 6;
    }
    if (temp_r31->unk28 > 0) {
        var_r25 = 0;
        temp_r31->unk28--;
    } else if (var_r25 != 0) {
        temp_r31->unk28 = 6;
    }
    if (lbl_1_bss_5C == 1008 && temp_r31->unk14 >= 8 && temp_r31->unk14 <= 14) {
        spD8 = temp_r31->unk30;
        if (var_r24 != 0) {
            temp_r31->unk30 -= 7;
        }
        if (var_r25 != 0) {
            temp_r31->unk30 -= 7;
        }
        if (spD8 > 0 && temp_r31->unk30 <= 0) {
            temp_r31->unk30 = -1;
            temp_r31->unk4C = 1;
        }
    }
    if (lbl_1_bss_20 == 0 && lbl_1_bss_5C == 1008 && temp_r31->unk14 >= 7 && temp_r31->unk14 <= 14 && (var_r24 != 0 || var_r25 != 0)) {
        temp_r31->unk38 = (var_r24 != 0) ? 0
            : (var_r25 != 0) ? 1 : 0;
    }
    if (temp_r31->unk00 == 0) {
        lbl_1_bss_68[0]->trans.x -= temp_r31->unk48;
        lbl_1_bss_68[1]->trans.x -= temp_r28->unk48;
    }
    switch (lbl_1_bss_5C) {
        case 1001:
            if (lbl_1_bss_60 == 0) {
                Hu3DModelAttrReset(arg0->model[0], HU3D_ATTR_DISPOFF);
            }
            if (lbl_1_bss_60 <= 30) {
                if (temp_r31->unk08 == -1) {
                    Hu3DMotionTimeSet(arg0->model[0], 138.0f);
                }
                arg0->trans.y = 2400.0 * (1.0 - lbl_1_bss_60 / 30.0);
            }
            if (temp_r31->unk08 != -1 && lbl_1_bss_60 == 30) {
                var_r29 = 2;
            }
            if (lbl_1_bss_60 == 40 && temp_r31->unk08 != -1) {
                var_r29 = 0;
            }
            if (lbl_1_bss_60 == 45 && temp_r31->unk08 == -1) {
                var_r29 = 0;
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[var_r29], lbl_1_data_184[var_r29], 35.0f, HU3D_MOTATTR_LOOP);
                temp_r31->unk40 = var_r29;
            }
            if (lbl_1_bss_60 == 30) {
                lbl_1_data_28C.unk04 += 50;
            }
            if (lbl_1_bss_60 == 30) {
                HuAudFXPlay(0x33D);
            }
            break;
        case 1005:
            if (lbl_1_bss_60 == 0) {
                var_r29 = 3;
            }
            if (lbl_1_bss_60 == 70) {
                var_r29 = 4;
            }
            break;
        case 1006:
            if (lbl_1_bss_60 == 5) {
                var_r29 = 5;
            }
            break;
        case 1010:
            if (lbl_1_bss_44 == temp_r31->unk00 && lbl_1_bss_60 >= 15) {
                if (lbl_1_bss_60 == 15) {
                    temp_r31->unk14 = 0;
                    temp_r31->unk18 = 0;
                    if (temp_r31->unk08 == -1) {
                        HuAudFXPlay(0x3A);
                    }
                }
                var_r29 = 10;
                if (arg0->rot.y > 180.0f) {
                    arg0->rot.y -= 360.0f;
                }
                arg0->rot.y *= 0.9;
            }
            if (lbl_1_bss_44 == 2 && lbl_1_bss_60 >= 15) {
                if (lbl_1_bss_60 == 15) {
                    temp_r31->unk14 = 0;
                    temp_r31->unk18 = 0;
                }
                var_r29 = 11;
                if (arg0->rot.y > 180.0f) {
                    arg0->rot.y -= 360.0f;
                }
                arg0->rot.y *= 0.9;
            }
            break;
    }
    temp_r31->unk18 += (temp_r31->unk18 < 0x10000);
    if (temp_r31->unk14 == 3 || temp_r31->unk14 == 5) {
        if (temp_r31->unk18 == 1 && lbl_1_data_2B0 != -1) {
            HuWinExCleanup(lbl_1_data_2B0);
            lbl_1_data_2B0 = -1;
        }
        if ((temp_r31->unk14 == 3 && temp_r31->unk18 == 23) || (temp_r31->unk14 == 5 && temp_r31->unk18 == 15)) {
            HuWinMesMaxSizeGet(1, spFC, MAKE_MESSID(48, 35));
            if (lbl_1_data_2B0 == -1) {
                lbl_1_data_2B0 = HuWinCreate(-10000.0f, 400.0f, spFC[0], spFC[1], 1);
            }
            HuWinBGTPLvlSet(lbl_1_data_2B0, 0.0f);
            HuWinMesSpeedSet(lbl_1_data_2B0, 0);
            HuWinMesSet(lbl_1_data_2B0, MAKE_MESSID(48, 35));
        }
    }
    switch (temp_r31->unk14) {
        case 0:
            if (lbl_1_bss_5C == 1008) {
                temp_r31->unk14 = 1;
                temp_r31->unk18 = 0;
            }
            break;
        case 1:
            if (temp_r31->unk18 == 1 && temp_r31->unk0C == -1) {
                switch (temp_r31->unk10) {
                    case 0:
                        temp_r31->unk3C = rand8() % 5 + 15;
                        break;
                    case 1:
                        temp_r31->unk3C = rand8() % 5 + 12;
                        break;
                    case 2:
                        temp_r31->unk3C = rand8() % 5 + 10;
                        break;
                    case 3:
                        temp_r31->unk3C = rand8() % 4 + 9;
                        break;
                }
            }
            if (var_r20 != 0) {
                temp_r31->unk14 = 2;
                temp_r31->unk18 = 0;
                var_r29 = 6;
                arg0->trans.x += (temp_r31->unk00 == 0) ? ((rand8() % 2) * 2 - 1) : 0;
            }
            break;
        case 2:
            arg0->trans.x += 8.695652f * (temp_r31->unk00 == 0 ? 1 : -1);
            break;
        case 3:
            arg0->trans.x += 4.347826f * (temp_r31->unk00 == 0 ? 1 : -1);
            if (temp_r31->unk18 >= 23) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 4:
            if (temp_r31->unk18 == 1) {
                var_r29 = 7;
            }
            arg0->trans.x += -4.347826f * (temp_r31->unk00 == 0 ? 1 : -1);
            if (temp_r31->unk18 >= 23) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 5:
            arg0->trans.x += 8.695652f * (temp_r31->unk00 == 0 ? 1 : -1);
            if (temp_r31->unk18 >= 15) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 6:
            if (temp_r31->unk18 == 1) {
                var_r29 = 8;
            }
            arg0->trans.x += -8.695652f * (temp_r31->unk00 == 0 ? 1 : -1);
            if (temp_r31->unk18 >= 7) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
                var_r26 = 7;
                var_r29 = 4;
            }
            if (temp_r31->unk18 >= 15) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
            }
            break;
        case 8:
            if (temp_r31->unk30 == 0) {
                var_r26 = 0;
                temp_r31->unk14 = 7;
                temp_r31->unk18 = 1;
                temp_r31->unk34 = 0;
            } else {
                if (var_r24 == 0 && var_r25 == 0) {
                    break;
                }
                temp_r31->unk14 = 9;
                temp_r31->unk18 = 0;
                var_r26 = 3;
                var_r22 = (temp_r31->unk38 == 0 ? 0 : 11) + 5;
                var_r29 = 6;
                if (lbl_1_bss_20 == 1) {
                    temp_r31->unk38 = (var_r24 != 0) ? 0
                        : (var_r25 != 0) ? 1 : 0;
                }
                break;
            }
            /* fallthrough */
        case 7:
            if (temp_r31->unk18 == 1) {
                s32 sp1B4[] = {
                    0x12A, 0x16A, 0x1AA,
                    0x1EA, 0x22A, 0x26A,
                    0x2AA, 0x2EA, 0x03B
                };
                HuAudFXPlay(sp1B4[temp_r31->unk08 == -1 ? 8 : temp_r31->unk08]);
                var_r29 = 9;
                temp_r31->unk4C = 0;
            }
            if (temp_r31->unk30 > 0) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 9:
            arg0->trans.x += 8.695652f * (temp_r31->unk00 == 0 ? 1 : -1);
            if (temp_r31->unk18 >= 23) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 12:
            if (temp_r31->unk18 == 7) {
                var_r26 = 0;
                var_r22 = 7;
                var_r29 = 7;
            }
            if (temp_r31->unk18 == 15) {
                var_r26 = 5;
                var_r29 = 4;
            }
            if (temp_r31->unk18 >= 20) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 10:
            arg0->trans.x += 4.347826f * (temp_r31->unk00 == 0 ? 1 : -1);
            if (temp_r31->unk18 >= 23) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 11:
            arg0->trans.x += -4.347826f * (temp_r31->unk00 == 0 ? 1 : -1);
            if (temp_r31->unk18 == 1) {
                var_r29 = 7;
            }
            if (temp_r31->unk18 >= 23) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 13:
            arg0->trans.x += 8.695652f * (temp_r31->unk00 == 0 ? 1 : -1);
            if (temp_r31->unk18 >= 23) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 14:
            arg0->trans.x += -8.695652f * (temp_r31->unk00 == 0 ? 1 : -1);
            if (temp_r31->unk18 == 1) {
                var_r29 = 8;
            }
            if (temp_r31->unk18 == 11) {
                var_r26 = 11;
                var_r29 = 4;
            }
            if (temp_r31->unk18 >= 23) {
                temp_r31->unk14 = 8;
                temp_r31->unk18 = 0;
            }
            if (temp_r31->unk34 < 8) {
                temp_r31->unk34 = 8;
            }
            break;
        case 15:
            if (temp_r31->unk18 == 1 && temp_r31->unk1C > 4) {
                temp_r31->unk1C = 4;
            }
            if (temp_r31->unk18 == 1 && lbl_1_data_2B0 != -1) {
                HuWinExCleanup(lbl_1_data_2B0);
                lbl_1_data_2B0 = -1;
            }
            if (temp_r31->unk18 == 7) {
                var_r29 = 4;
                var_r26 = 20;
            }
            if (temp_r31->unk18 == 60) {
                lbl_1_bss_44 = temp_r31->unk00;
                temp_r31->unk1C = 0;
            }
            break;
        case 16:
            arg0->trans.x += -39.130432f * (temp_r31->unk00 == 0 ? 1 : -1);
            arg0->trans.y += 39.130432f;
            if (temp_r31->unk18 == 1) {
                s32 sp190[] = {
                    0x123, 0x163, 0x1A3,
                    0x1E3, 0x223, 0x263,
                    0x2A3, 0x2E3, 0x03C
                };

                HuAudFXPlay(sp190[temp_r31->unk08 == -1 ? 8 : temp_r31->unk08]);
                var_r29 = 8;
                var_r26 = 0;
                var_r22 = 6;
            }
            arg0->rot.z = (temp_r31->unk00 == 0) ? -20 : 20;
            break;
        case 17:
            if (temp_r31->unk18 == 1 && temp_r31->unk1C > 4) {
                temp_r31->unk1C = 4;
            }
            if (temp_r31->unk18 == 1 && lbl_1_data_2B0 != -1) {
                HuWinExCleanup(lbl_1_data_2B0);
                lbl_1_data_2B0 = -1;
            }
            if (temp_r31->unk18 == 7) {
                var_r29 = 0;
                var_r26 = 10;
            }
            if (temp_r31->unk18 >= 7 && temp_r31->unk18 < 17) {
                arg0->trans.x += (temp_r31->unk00 == 0 ? -1 : 1) * 2;
            }
            if (temp_r31->unk18 == 60) {
                lbl_1_bss_44 = 2;
                temp_r31->unk1C = 0;
            }
            break;
    }
    switch (temp_r31->unk14) {
        case 12:
            if (temp_r31->unk00 == 0) {
                break;
            }
            /* fallthrough */
        case 3:
        case 5:
        case 10:
        case 13:
            temp_r19 = Hu3DMotionTimeGet(arg0->model[0]);
            if ((temp_r28->unk14 != 4 && temp_r28->unk14 != 6) || temp_r28->unk18 != 1) {
                if ((temp_r19 + 1) % 11 != 0 || (temp_r31->unk14 == 12 && temp_r19 + 1 > 11)) {
                    break;
                }
            }
            temp_r21 = ((temp_r19 + 1) / 11 - 1) % 2;
            {
                char sp1D8[][50] = {
                    "g000mN-itemhook_R",
                    "g000mN-itemhook_L"
                };

                if (temp_r31->unk08 != -1) {
                    var_r18 = CharModelHookNameGet(temp_r31->unk08, 1, (temp_r21 % 2 == 0) ? 0 : 1);
                } else {
                    var_r18 = (temp_r21 % 2 == 0) ? sp1D8[0] : sp1D8[1];
                }
            }
            Hu3DModelObjPosGet(arg0->model[0], var_r18, &sp104);
            Hu3DModelPosSet(lbl_1_bss_64->model[temp_r21 + 7], sp104.x + (temp_r31->unk00 == 0 ? 1 : -1) * 50, sp104.y, 75.0f + sp104.z);
            Hu3DMotionTimeSet(lbl_1_bss_64->model[temp_r21 + 7], 2.0f);
            Hu3DModelAttrReset(lbl_1_bss_64->model[temp_r21 + 7], 1);
            if (lbl_1_bss_78[temp_r31->unk08 == -1 ? 1 : 0].unk00 < 3) {
                lbl_1_bss_78[temp_r31->unk08 == -1 ? 1 : 0].unk04[lbl_1_bss_78[temp_r31->unk08 == -1 ? 1 : 0].unk00] = 0.0f;
                lbl_1_bss_78[temp_r31->unk08 == -1 ? 1 : 0].unk00++;
            }
            if (fabs(lbl_1_bss_68[1 - temp_r31->unk00]->trans.x) >= 800.0 && (temp_r28->unk14 == 11 || temp_r28->unk14 == 14)) {
                temp_r31->unk14 = 15;
                temp_r28->unk14 = 16;
                temp_r31->unk18 = temp_r28->unk18 = 0;
                if (lbl_1_bss_78[4].unk00 < 3) {
                    lbl_1_bss_78[4].unk04[lbl_1_bss_78[4].unk00] = 0.0f;
                    lbl_1_bss_78[4].unk00++;
                }
                if (lbl_1_data_2A8 != -1) {
                    HuAudSeqFadeOut(lbl_1_data_2A8, 100);
                    lbl_1_data_2A8 = -1;
                }
            }
        break;
    }
    temp_r31->unk34++;
    if (temp_r31->unk14 != 16 && temp_r31->unk14 != 15 && temp_r31->unk14 != 17 && lbl_1_bss_5C == 1008 && temp_r31->unk34 >= 30 && (temp_r31->unk34 - 30) % 30 == 0) {
        temp_r31->unk30 += (temp_r31->unk4C == 0 || temp_r31->unk14 == 7) ? 10 : 0;
    }
    temp_r31->unk30 = (temp_r31->unk1C > 0 || temp_r31->unk30 >= 100) ? 100
        : (temp_r31->unk30 < 0) ? 0
        : temp_r31->unk30;
    for (i = 0; i < 5; i++) {
        temp_f31 = (temp_r31->unk30 >= i * 20 + 20) ? 1.0
            : (temp_r31->unk30 <= i * 20) ? 0.0
            : (temp_r31->unk30 - i * 20) / 20.0;
        espScaleSet(lbl_1_data_5C[i + (temp_r31->unk00 == 0 ? 2 : 10)], temp_f31, temp_f31);
        if (temp_r31->unk1C > 0) {
            s32 spF4[] = { 106, 469 };
            s32 spEC[] = { 78, 78 };
            s32 sp150[] = {
                0, 0, -33, -9, 15, 39, 63, -68,
                0, 0, -33, -9, 15, 39, 63, -68
            };
            s32 sp110[] = {
                0, 0, -1, -1, -1, -1, -1, -2,
                0, 0, -1, -1, -1, -1, -1, -2
            };

            espPosSet(lbl_1_data_5C[i + 18], spF4[temp_r31->unk00] + sp150[i + 2], spEC[temp_r31->unk00] + sp110[i + 2]);
            espScaleSet(lbl_1_data_5C[i + 18],
                (temp_r31->unk1C % 4 == 0) ? 1.1 : 1.0,
                (temp_r31->unk1C % 4 == 0) ? 1.1 : 1.0);
            espTPLvlSet(lbl_1_data_5C[i + 18],
                (temp_r31->unk1C % 4 < 2) ? 1.0
                    : (var_r22 % 4 == 2) ? 0.5 : 0.0);
            espDispOn(lbl_1_data_5C[i + 18]);
        } else if (temp_r28->unk1C == 0) {
            espDispOff(lbl_1_data_5C[i + 18]);
        }
    }
    if (temp_r31->unk1C > 0) {
        sp20 = (temp_r31->unk08 != -1) ? temp_r31->unk08 : 8;
        Hu3DModelPosSet(lbl_1_bss_64->model[3],
            arg0->trans.x + lbl_1_data_220[sp20][1] * (temp_r31->unk00 == 0 ? 1 : -1),
            arg0->trans.y + lbl_1_data_220[sp20][2],
            150.0f + arg0->trans.z);
        Hu3DModelScaleSet(lbl_1_bss_64->model[3],
            0.75 * lbl_1_data_220[sp20][0],
            0.75 * lbl_1_data_220[sp20][0],
            0.75 * lbl_1_data_220[sp20][0]);
        Hu3DModelAttrReset(lbl_1_bss_64->model[3], 1);
        Hu3DModelAttrSet(lbl_1_bss_64->model[3], HU3D_ATTR_ZCMP_OFF);
        Hu3DModelPosSet(lbl_1_bss_64->model[4],
            arg0->trans.x + lbl_1_data_220[sp20][1] * (temp_r31->unk00 == 0 ? 1 : -1),
            arg0->trans.y + lbl_1_data_220[sp20][2],
            150.0f + arg0->trans.z);
        Hu3DModelScaleSet(lbl_1_bss_64->model[4],
            0.75 * lbl_1_data_220[sp20][0],
            0.75 * lbl_1_data_220[sp20][0],
            0.75 * lbl_1_data_220[sp20][0]);
        Hu3DModelAttrReset(lbl_1_bss_64->model[4], 1);
        Hu3DModelAttrSet(lbl_1_bss_64->model[4], HU3D_ATTR_ZCMP_OFF);
        temp_r31->unk1C--;
        if (temp_r31->unk1C == 0) {
            HuAudFXStop(lbl_1_data_2B4);
        }
    } else if (temp_r28->unk1C == 0) {
        Hu3DModelAttrSet(lbl_1_bss_64->model[3], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_64->model[4], HU3D_ATTR_DISPOFF);
    }
    if (temp_r31->unk44 >= 0) {
        var_r29 = temp_r31->unk44;
    }
    if (var_r29 >= 0 && var_r29 != temp_r31->unk40) {
        if (var_r26 == 0) {
            Hu3DMotionSet(arg0->model[0], arg0->motion[var_r29]);
            Hu3DMotionTimeSet(arg0->model[0], (var_r22 == -1) ? 0 : var_r22);
        } else {
            Hu3DMotionShiftSet(arg0->model[0], arg0->motion[var_r29],
                (var_r22 != -1) ? var_r22 : lbl_1_data_184[var_r29],
                (var_r26 != -1) ? var_r26 : lbl_1_data_154[var_r29],
                lbl_1_data_148[var_r29] ? HU3D_MOTATTR_NONE : HU3D_MOTATTR_LOOP);
        }
        temp_r31->unk40 = var_r29;
    }
    if (temp_r31->unk00 == 1) {
        spD4 = &Hu3DData[arg0->model[0]];
    }
}

s32 lbl_1_data_33C = -1;
float lbl_1_data_340 = 3500.0f;
float lbl_1_data_344 = 100.0f;
float lbl_1_data_348 = -59.0f;

void fn_1_2CC4(omObjData* arg0) {
    StructBss68Data* sp158[2];
    omObjData* sp150[2];
    StructBss68Data* sp148[2];
    s32 sp140[2];
    omObjData* sp138[2];
    StructBss68Data* sp130[2];
    ModelData* temp_r24;
    ModelData* temp_r27;
    ModelData* temp_r28;
    ModelData* temp_r29;
    float spAC;
    float spA8;
    float spA4;
    float temp_f20;
    float var_f19;
    float temp_f24;
    float temp_f23;
    float temp_f22;
    float var_f21;
    float temp_f27;
    float temp_f26;
    float temp_f25;
    float temp_f28;
    float temp_f29;
    float var_f31;
    s32 var_r23;
    s32 var_r26;
    s32 var_r25;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;
    s32 i;

    for (i = 0; i < 2; i++) {
        sp158[i] = lbl_1_bss_68[i]->data;
    }
    lbl_1_bss_4++;
    switch (lbl_1_bss_5C) {
        case 1003:
            temp_f27 = 1800.0 * (1.0 - lbl_1_bss_60 / 30.0);
            temp_f27 = (temp_f27 < 0.0f) ? 0.0f : temp_f27;
            Hu3DModelPosSet(lbl_1_bss_64->model[5], 0.0f, temp_f27, 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_64->model[5], HU3D_ATTR_DISPOFF);
            if (lbl_1_bss_60 == 31) {
                HuAudFXPlay(0x5B);
            }
            if (lbl_1_bss_60 >= 31 && lbl_1_bss_60 <= 38) {
                temp_f24 = 1.0 - (lbl_1_bss_60 - 31) / 7.0;
                Hu3DModelRotSet(arg0->model[5], 25.0 * (temp_f24 * 0.5 + temp_f24 * temp_f24 * 0.5), 0.0f, 0.0f);
            }
            break;
        case 1002:
            if (lbl_1_bss_60 == 0) {
                lbl_1_bss_3C = 0;
            }
            if (lbl_1_bss_60 == 20) {
                espAttrReset(lbl_1_data_5C[16], HU3D_ATTR_SHADOW);
            }
            if ((lbl_1_bss_60 >= 20 && lbl_1_bss_60 <= 50) || (lbl_1_bss_60 >= 180 && lbl_1_bss_60 <= 210)) {
                spAC = (lbl_1_bss_60 <= 120)
                    ? (lbl_1_bss_60 - 20) / 30.0
                    : (1.0 - (lbl_1_bss_60 - 180) / 30.0);
                espTPLvlSet(lbl_1_data_5C[16], spAC);
            }
            if (lbl_1_bss_60 == 210) {
                espAttrSet(lbl_1_data_5C[16], HU3D_ATTR_SHADOW);
            }
            break;
        case 1006:
            if (lbl_1_bss_60 == 0) {
                Hu3DMotionSet(arg0->model[5], arg0->motion[2]);
                Hu3DModelAttrReset(arg0->model[5], HU3D_MOTATTR_LOOP);
            }
            if (lbl_1_bss_60 == 15) {
                Hu3DModelAttrSet(arg0->model[5], HU3D_MOTATTR_PAUSE);
            }
            break;
        case 1008:
            if (lbl_1_bss_60 == 1) {
                Hu3DModelAttrReset(arg0->model[5], HU3D_MOTATTR_PAUSE);
                for (i = 0; i < 16; i++) {
                    espDispOn(lbl_1_data_5C[i]);
                }
            }
            if (lbl_1_bss_60 <= 25) {
                temp_f28 = lbl_1_bss_60 / 25.0;
                temp_f26 = 1.0f - (1.0f - temp_f28) * (1.0f - temp_f28) * (1.0f - temp_f28);
                temp_f26 = 0.25 + 1.375 * temp_f26;
                temp_f23 = 1.0f - (1.0f - temp_f28) * (1.0f - temp_f28);
                temp_f23 = 2.0f * (1.0f - temp_f28);
                espAttrReset(lbl_1_data_5C[17], HU3D_ATTR_SHADOW);
                espScaleSet(lbl_1_data_5C[17], 0.85 * temp_f26, 0.85 * temp_f26);
                espTPLvlSet(lbl_1_data_5C[17], (temp_f23 > 1.0f) ? 1.0f : temp_f23);
            } else {
                espAttrSet(lbl_1_data_5C[17], HU3D_ATTR_SHADOW);
            }
            for (i = 0; i < 2; i++) {
                sp150[i] = lbl_1_bss_68[i];
                sp148[i] = lbl_1_bss_68[i]->data;
            }
            for (i = 0; i < 2; i++) {
                sp140[i] = (sp148[1 - i]->unk1C > 0) ? 2
                    : (sp148[i]->unk14 == 8) ? 2
                    : (sp148[i]->unk14 == 1) ? 1
                    : (sp148[i]->unk14 == 9) ? (sp148[i]->unk18 >= 0 ? 3 : 2)
                    : (sp148[i]->unk14 == 2) ? 4
                    : (sp148[i]->unk14 == 7) ? 0 : -1;
            }
            if (sp140[0] >= 0 && sp140[1] >= 0 && fabs(sp150[0]->trans.x - sp150[1]->trans.x) < 300.0) {
                sp150[0]->trans.x = (sp148[0]->unk1C > 0) ? sp150[0]->trans.x
                    : (sp148[1]->unk1C > 0) ? (sp150[1]->trans.x - 300.0f)
                    : ((sp150[0]->trans.x + sp150[1]->trans.x) / 2.0 - 150.0);
                sp150[0]->trans.x = (sp150[0]->trans.x >= 650.0) ? 650.0
                    : (sp150[0]->trans.x <= -950.0) ? -950.0
                    : sp150[0]->trans.x;
                sp150[1]->trans.x = sp150[0]->trans.x + 300.0f;
                if (sp140[0] >= 3 || sp140[1] >= 3) {
                    var_r26 = (sp140[0] >= 3) ? 0 : 1;
                    var_r25 = 1 - var_r26;
                    switch (sp140[var_r25]) {
                        case 4:
                            if (sp150[var_r26]->trans.x * (var_r26 == 0 ? 1 : -1) < sp150[var_r25]->trans.x * (var_r25 == 0 ? 1 : -1)) {
                                var_r26 = 1 - var_r26;
                                var_r25 = 1 - var_r25;
                            }
                            sp148[var_r26]->unk14 = 3;
                            sp148[var_r25]->unk14 = 4;
                            break;
                        case 1:
                            sp148[var_r26]->unk14 = 5;
                            sp148[var_r25]->unk14 = 6;
                            break;
                        case 3:
                            sp148[var_r26]->unk14 = 12;
                            sp148[var_r25]->unk14 = 12;
                            break;
                        case 2:
                            sp148[var_r26]->unk14 = 10;
                            sp148[var_r25]->unk14 = 11;
                            break;
                        case 0:
                            sp148[var_r26]->unk14 = 13;
                            sp148[var_r25]->unk14 = 14;
                            break;
                    }
                    sp148[0]->unk18 = sp148[1]->unk18 = 0;
                }
            }
            /* fallthrough */
        case 1009:
            if (lbl_1_bss_5C != 1008 && lbl_1_bss_40 == 0) {
                break;
            }
            for (i = 0; i < 2; i++) {
                sp138[i] = lbl_1_bss_68[i];
                sp130[i] = lbl_1_bss_68[i]->data;
            }
            switch (lbl_1_bss_18) {
                case 0:
                    if (lbl_1_bss_40 == 0 && lbl_1_bss_18 == 0 && (sp138[0]->trans.x > -150.0f || sp138[1]->trans.x < 150.0f)) {
                        lbl_1_bss_18 = (-sp138[0]->trans.x < sp138[1]->trans.x ? 1 : 2);
                        Hu3DModelPosSet(lbl_1_bss_64->model[9], 0.0f, 100.0f, 0.0f);
                        Hu3DMotionTimeSet(lbl_1_bss_64->model[9], 0.0f);
                        Hu3DModelAttrReset(lbl_1_bss_64->model[9], HU3D_ATTR_DISPOFF);
                        if (lbl_1_bss_78[4].unk00 < 3) {
                            lbl_1_bss_78[4].unk04[lbl_1_bss_78[4].unk00] = 0.0f;
                            lbl_1_bss_78[4].unk00++;
                        }
                    }
                    if (lbl_1_bss_18 == 0) {
                        break;
                    }
                    /* fallthrough */
                case 1:
                case 2:
                    temp_r27 = &Hu3DData[arg0->model[5]];
                    temp_r27->rot.y += (lbl_1_bss_18 == 1 ? 18 : -18);
                    temp_r27->rot.z = (lbl_1_bss_18 == 1 ? -20 : 20);
                    temp_r27->pos.x += 5.130000000000001 * (lbl_1_bss_18 == 1 ? 1 : -1);
                    temp_r27->pos.y += 47.0;
                    temp_r27->pos.z += -20.0f;
                    if (temp_r27->pos.y > 1800.0f) {
                        lbl_1_bss_18 += 2;
                    }
                    break;
            }
            switch (lbl_1_bss_1C) {
                case 0:
                case 2:
                    lbl_1_data_2B8 -= (lbl_1_bss_18 >= 3 && sp130[0]->unk14 < 16 && sp130[1]->unk14 < 16);
                    if (lbl_1_data_2B8 != 0) {
                        break;
                    }
                    Hu3DModelAttrReset(arg0->model[2], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(arg0->model[2],
                        (lbl_1_bss_1C == 0) ? 0.0 : (2.0 * ((rand8() % 256) / 255.0 - 0.5) * 400.0),
                        1500.0f, 0.0f);
                    lbl_1_bss_1C = 1;
                    /* fallthrough */
                case 1:
                    temp_r28 = &Hu3DData[arg0->model[2]];
                    temp_r28->pos.y -= 10.0f;
                    if (temp_r28->pos.y <= 225.0f) {
                        float sp128[] = { 100000000.0f, 100000000.0f };

                        temp_r28->pos.y = (temp_r28->pos.y < 100.0f) ? 100.0f : temp_r28->pos.y;
                        for (i = 0; i < 2; i++) {
                            if (fabs(sp138[i]->trans.x + (i == 0 ? 40 : -40) - temp_r28->pos.x) < 180.0) {
                                sp128[i] = fabs(sp138[i]->trans.x + (i == 0 ? 40 : -40) - temp_r28->pos.x);
                            }
                        }
                        if (sp128[0] != sp128[1]) {
                            var_r23 = (sp128[0] < sp128[1]) ? 0 : 1;
                            Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
                            lbl_1_bss_1C = 2;
                            lbl_1_data_2B8 = 600;
                            sp130[var_r23]->unk1C = 300;
                            sp130[var_r23]->unk4C = 0;
                            if (lbl_1_bss_78[3].unk00 < 3) {
                                lbl_1_bss_78[3].unk04[lbl_1_bss_78[3].unk00] = 0.0f;
                                lbl_1_bss_78[3].unk00++;
                            }
                            lbl_1_data_2B4 = HuAudFXPlay(0x7E6);
                        }
                    }
                    if (sp130[0]->unk14 >= 16 || sp130[1]->unk14 >= 16 || lbl_1_bss_40 != 0) {
                        lbl_1_bss_1C = 3;
                        lbl_1_data_2B8 = 0;
                    }
                    if (lbl_1_bss_1C == 1) {
                        break;
                    }
                    /* fallthrough */
                case 3:
                    lbl_1_data_2B8++;
                    if (lbl_1_data_2B8 < 60 && lbl_1_data_2B8 % 2 == 0) {
                        Hu3DModelAttrReset(arg0->model[2], HU3D_ATTR_DISPOFF);
                    } else {
                        Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
                    }
                    break;
            }
            break;
    }
    switch (lbl_1_bss_5C) {
        case 1009:
            if (lbl_1_bss_40 == 0) {
                if (lbl_1_bss_60 <= 30) {
                    Hu3DModelPosSet(lbl_1_bss_64->model[5], 0.0f, (30 - lbl_1_bss_60) * 50 * 0.94, 0.0f);
                    Hu3DModelRotSet(lbl_1_bss_64->model[5], 0.0f, 0.0f, lbl_1_bss_18 == 3 ? -20 : 20);
                    Hu3DModelAttrReset(lbl_1_bss_64->model[5], HU3D_ATTR_DISPOFF);
                }
                if (lbl_1_bss_60 == 30) {
                    Hu3DMotionSet(arg0->model[5], arg0->motion[0]);
                    Hu3DModelAttrReset(arg0->model[5], HU3D_MOTATTR_LOOP);
                }
                if (lbl_1_bss_60 == 30) {
                    HuAudFXPlay(0x5B);
                }
                if (lbl_1_bss_60 >= 30 && lbl_1_bss_60 <= 37) {
                    temp_f22 = 1.0 - (lbl_1_bss_60 - 30) / 7.0;
                    Hu3DModelRotSet(arg0->model[5], 25.0 * (temp_f22 * 0.5 + temp_f22 * temp_f22 * 0.5), 0.0f, 0.0f);
                }
            } else if (lbl_1_bss_18 == 0) {
                Hu3DMotionSet(lbl_1_bss_64->model[5], arg0->motion[0]);
                Hu3DModelAttrReset(lbl_1_bss_64->model[5], HU3D_MOTATTR_LOOP);
            }
            break;
        case 1010:
            if (lbl_1_bss_40 == 0) {
                if (lbl_1_bss_60 == 1) {
                    Hu3DMotionSet(arg0->model[5], arg0->motion[3]);
                    Hu3DModelAttrReset(arg0->model[5], HU3D_MOTATTR_LOOP);
                }
                temp_r24 = &Hu3DData[arg0->model[5]];
                temp_f20 = (lbl_1_bss_68[lbl_1_bss_44]->trans.x < 0.0f) ? -90 : 90;
                temp_r24->rot.y = temp_f20 + 0.8 * (temp_r24->rot.y - temp_f20);
            }
            break;
    }
    var_r22 = lbl_1_data_33C;
    {
        float sp160[][6] = {
            { 3500.0f, 0.0f, 100.0f, 0.0f, -59.0f, 0.0f },
            { 3200.0f, 0.0f, 100.0f, 0.0f, -30.0f, 0.0f },
            { 2100.0f, 0.0f, 200.0f, 0.0f, -30.0f, 0.0f },
            { 2000.0f, 0.0f, 200.0f, 0.0f, -30.0f, 0.0f },
            {  800.0f, 0.0f, 200.0f, 0.0f, -89.0f, 0.0f },
            { 1800.0f, 0.0f, 200.0f, 0.0f, -30.0f, 0.0f }
        };

        if (lbl_1_bss_44 != -1 && lbl_1_bss_40 == 0) {
            sp160[2][1] = lbl_1_bss_68[lbl_1_bss_44]->trans.x;
        }
        if (lbl_1_data_33C == -1) {
            lbl_1_data_33C = 0;
            lbl_1_bss_24 = 1;
            lbl_1_bss_28 = 1.0f;
        }
        if (lbl_1_data_33C == 0) {
            lbl_1_data_33C = 1;
            lbl_1_bss_24 = 1;
            lbl_1_bss_28 = 0.5f;
        }
        if (lbl_1_bss_5C == 1010 && lbl_1_bss_44 != 2 && lbl_1_bss_60 >= 15 && lbl_1_data_33C == 1) {
            lbl_1_data_33C = 2;
            lbl_1_bss_24 = 0;
            lbl_1_bss_28 = 0.0f;
        }
        if (var_r22 != lbl_1_data_33C && var_r22 != -1) {
            lbl_1_data_340 = CZoom;
            lbl_1_data_344 = Center.y;
            lbl_1_bss_30 = Center.z;
            lbl_1_data_348 = CRot.x;
            lbl_1_bss_34 = CRot.y;
        }
        if (lbl_1_bss_28 <= 1.0f) {
            if (lbl_1_bss_24 == 0) {
                lbl_1_bss_28 = 1.0 - 0.95 * (1.0f - lbl_1_bss_28);
                var_f31 = lbl_1_bss_28;
            } else {
                lbl_1_bss_28 += 0.008333333333333333;
                lbl_1_bss_28 = (lbl_1_bss_28 > 1.0f) ? 1.0f : lbl_1_bss_28;
                var_f31 = 0.5 + -0.5 * cosd(180.0f * lbl_1_bss_28);
            }
            lbl_1_bss_28 = (lbl_1_bss_28 > 1.0f) ? 1.0f : lbl_1_bss_28;
            CZoom = var_f31 * sp160[lbl_1_data_33C][0] + lbl_1_data_340 * (1.0f - var_f31);
            Center.x = var_f31 * sp160[lbl_1_data_33C][1] + lbl_1_bss_2C * (1.0f - var_f31);
            Center.y = var_f31 * sp160[lbl_1_data_33C][2] + lbl_1_data_344 * (1.0f - var_f31);
            Center.z = var_f31 * sp160[lbl_1_data_33C][3] + lbl_1_bss_30 * (1.0f - var_f31);
            CRot.x = var_f31 * sp160[lbl_1_data_33C][4] + lbl_1_data_348 * (1.0f - var_f31);
            CRot.y = var_f31 * sp160[lbl_1_data_33C][5] + lbl_1_bss_34 * (1.0f - var_f31);
        }
    }
    if (lbl_1_bss_5C == 1001) {
        var_f21 = 0.0f;
        temp_f25 = 0.0f;
        if (lbl_1_data_28C.unk00 % 2 >= 0) {
            lbl_1_data_28C.unk08 = lbl_1_data_28C.unk10;
            lbl_1_data_28C.unk0C = lbl_1_data_28C.unk14;
            do {
                lbl_1_data_28C.unk10 = 2.0 * (rand8() / 255.0) - 1.0;
                lbl_1_data_28C.unk14 = 2.0 * (rand8() / 255.0) - 1.0;
                lbl_1_data_28C.unk10 = 0.0f;
                temp_f29 = (lbl_1_data_28C.unk10 - lbl_1_data_28C.unk08) * (lbl_1_data_28C.unk10 - lbl_1_data_28C.unk08) + (lbl_1_data_28C.unk14 - lbl_1_data_28C.unk0C) * (lbl_1_data_28C.unk14 - lbl_1_data_28C.unk0C);
            } while (sqrtf(temp_f29) < 0.75);
        }
        var_f21 = lbl_1_data_28C.unk08;
        temp_f25 = lbl_1_data_28C.unk0C;
        var_f21 *= lbl_1_data_28C.unk04 * 2;
        temp_f25 *= lbl_1_data_28C.unk04 * 2;
        lbl_1_data_28C.unk00 = !lbl_1_data_28C.unk00;
        lbl_1_data_28C.unk04 = (lbl_1_data_28C.unk04 > 24) ? 23
            : (lbl_1_data_28C.unk04 - 1 > 0) ? (lbl_1_data_28C.unk04 - 1) : 0;
        Center.x = 0.0f;
        Center.y = 100.0f + temp_f25;
    }
    if (lbl_1_bss_5C >= 1008) {
        for (i = 0; i < 2; i++) {
            temp_r29 = &Hu3DData[lbl_1_bss_68[i]->model[0]];
            var_r21 = (sp158[i]->unk08 != -1) ? sp158[i]->unk08 : 8;
            var_r20 = (temp_r29->unk_08 == lbl_1_bss_68[i]->motion[4]) ? 0
                : (temp_r29->unk_08 == lbl_1_bss_68[i]->motion[6]) ? 1
                : (temp_r29->unk_08 == lbl_1_bss_68[i]->motion[7]) ? 2 : -1;
            var_r19 = (temp_r29->unk_0C == lbl_1_bss_68[i]->motion[4]) ? 0
                : (temp_r29->unk_0C == lbl_1_bss_68[i]->motion[6]) ? 1
                : (temp_r29->unk_0C == lbl_1_bss_68[i]->motion[7]) ? 2 : -1;
            spA8 = (var_r20 == -1) ? 0.0f : lbl_1_data_1B4[var_r21][var_r20];
            spA4 = (var_r19 == -1) ? 0.0f : lbl_1_data_1B4[var_r21][var_r19];
            var_f19 = (temp_r29->unk_0C == -1) ? 0.0f
                : (temp_r29->unk_80 == 0.0f) ? 1.0f
                : (temp_r29->unk_7C / temp_r29->unk_80);
            sp158[i]->unk48 = (i == 0 ? 1 : -1) * (spA8 * (1.0f - var_f19) + spA4 * var_f19);
            lbl_1_bss_68[i]->trans.x += sp158[i]->unk48;
            Hu3DModelPosSet(lbl_1_bss_68[i]->model[0], lbl_1_bss_68[i]->trans.x, lbl_1_bss_68[i]->trans.y, lbl_1_bss_68[i]->trans.z);
        }
    }
}

void fn_1_5500(void) {
    StructBss68Data* spC[2];
    s16 sp8;
    s16 temp_r31;
    s32 i;

    sp8 = 0;
    for (i = 0; i < 2; i++) {
        spC[i] = lbl_1_bss_68[i]->data;
    }
    HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
    HuWinComKeyReset();
    temp_r31 = HuWinExCreateStyled(36.0f, 344.0f, 504, 96, 6, 0);
    HuWinBGTPLvlSet(temp_r31, 0.8f);
    HuWinMesSpeedSet(temp_r31, 1);
    HuWinExAnimIn(temp_r31);
    HuWinDisablePlayerSet(temp_r31, 0xF
        & ((spC[0]->unk0C != -1) ? ~(1 << spC[0]->unk0C) : 0xF)
        & ((spC[1]->unk0C != -1) ? ~(1 << spC[1]->unk0C) : 0xF));
    HuWinMesSet(temp_r31, MAKE_MESSID(48, 31));
    if ((spC[0]->unk0C == -1 || spC[0]->unk08 == -1) && (spC[1]->unk0C == -1 || spC[1]->unk08 == -1)) {
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
    }
    HuWinMesWait(temp_r31);
    HuWinExAnimOut(temp_r31);
    HuWinExCleanup(temp_r31);
    lbl_1_bss_10 = 0;
    HuPrcEnd();
}

void fn_1_5720(void) {
    float var_f31;
    StructBss68Data* spC[2];
    WindowData* temp_r30;
    s16 sp8;
    s16 temp_r31;
    s32 var_r28;
    s32 i;

    sp8 = 0;
    for (i = 0; i < 2; i++) {
        spC[i] = lbl_1_bss_68[i]->data;
    }
    HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, 60);
    HuWinComKeyReset();
    temp_r31 = HuWinCreate(215.0f, 100.0f, 130, 37, 1);
    HuSprColorSet(winData[temp_r31].group, 0, 0xFF, 0xFF, 0xCC);
    HuWinBGTPLvlSet(temp_r31, 0.9f);
    temp_r30 = &winData[temp_r31];
    temp_r30->mess_color = 0;
    temp_r30->mess_shadow_color = 9;
    temp_r30->attr |= 0x80;
    for (var_r28 = 15, var_f31 = 0.0f; var_r28 != 0; var_r28--, var_f31 += 0.06666667f) {
        HuWinScaleSet(temp_r31, 1.0f, 1.0 * (1.0f - (1.0f - var_f31) * (1.0f - var_f31)));
        HuWinPosSet(temp_r31, 215.0f, 100.0 + 37.0 * (1.0f - (1.0f - var_f31) * (1.0f - var_f31)) / -4.0);
        HuPrcVSleep();
    }
    HuWinScaleSet(temp_r31, 1.0f, 1.0f);
    HuWinMesSet(temp_r31, MAKE_MESSID(48, 32));
    HuPrcSleep(60);
    HuWinExAnimOut(temp_r31);
    HuWinExCleanup(temp_r31);
    lbl_1_bss_10 = 0;
    HuPrcEnd();
}

void fn_1_59BC(omObjData* arg0) {
    StructBss68Data* sp14[2];
    float spC[2];
    s32 sp8;
    s32 i;

    for (i = 0; i < 5; i++) {
        s32 sp1C[] = { 0x7E1, 0x7E2, 0x7E3, 0x7E4, 0x7E5 };

        if (lbl_1_bss_78[i].unk00 > 3) {
            lbl_1_bss_78[i].unk00 = 3;
        }
        if (lbl_1_bss_78[i].unk00 > 0) {
            sp8 = HuAudFXPlay(sp1C[i]);
            lbl_1_bss_78[i].unk00--;
        }
    }
    for (i = 0; i < 2; i++) {
        sp14[i] = lbl_1_bss_68[i]->data;
    }
    if (omSysExitReq != 0 && WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        arg0->func = fn_1_7AE4;
    }
    switch (lbl_1_bss_5C) {
        case 1000:
            if (WipeStatGet() == 0) {
                lbl_1_bss_5C++;
                lbl_1_bss_60 = 0;
            }
            break;
        case 1001:
            lbl_1_bss_60++;
            if (lbl_1_bss_60 == 60) {
                lbl_1_bss_5C = (lbl_1_bss_14 != 0 ? 1002 : 1003);
                lbl_1_bss_60 = 0;
            }
            break;
        case 1002:
            lbl_1_bss_60++;
            if (lbl_1_bss_60 > 210) {
                lbl_1_bss_5C++;
                lbl_1_bss_60 = 0;
            }
            break;
        case 1003:
            lbl_1_bss_60++;
            if (lbl_1_bss_60 == 60) {
                lbl_1_bss_5C = (lbl_1_bss_14 != 0 ? 1004 : 1005);
                lbl_1_bss_60 = 0;
            }
            break;
        case 1004:
            if (lbl_1_bss_60 == 0) {
                HuPrcChildCreate(fn_1_5500, 100, 0x2000, 0, HuPrcCurrentGet());
                lbl_1_bss_10 = 1;
                lbl_1_bss_60++;
            } else if (lbl_1_bss_10 == 0) {
                lbl_1_bss_60++;
                if (sp14[0]->unk14 == 0) {
                    lbl_1_bss_5C++;
                    lbl_1_bss_60 = 0;
                }
            }
            break;
        case 1005:
            lbl_1_bss_60++;
            if (lbl_1_bss_60 == 180) {
                lbl_1_bss_5C++;
                lbl_1_bss_60 = 0;
            }
            break;
        case 1006:
            if (lbl_1_bss_60 == 0) {
                HuWinMesMaxSizeGet(1, spC, MAKE_MESSID(48, 34));
                lbl_1_data_2B0 = HuWinCreate(-10000.0f, 400.0f, spC[0], spC[1], 1);
                HuWinBGTPLvlSet(lbl_1_data_2B0, 0.0f);
                HuWinMesSpeedSet(lbl_1_data_2B0, 0);
                HuWinMesSet(lbl_1_data_2B0, MAKE_MESSID(48, 34));
                HuPrcChildCreate(fn_1_5720, 100, 0x2000, 0, HuPrcCurrentGet());
                lbl_1_bss_10 = 1;
                lbl_1_bss_60++;
            } else if (lbl_1_bss_10 == 0) {
                lbl_1_bss_60++;
                if (sp14[0]->unk14 == 0) {
                    lbl_1_bss_5C++;
                    lbl_1_bss_60 = rand8() * 30 % 5 + 60;
                }
            } else {
                lbl_1_bss_60++;
            }
            break;
        case 1007:
            lbl_1_bss_60 -= 1;
            if (lbl_1_bss_60 <= 0) {
                lbl_1_bss_5C++;
                lbl_1_bss_60 = 0;
                HuAudFXPlay(0x3E);
            }
            break;
        case 1008:
            lbl_1_bss_60++;
            if (lbl_1_bss_44 != -1) {
                lbl_1_bss_5C = 1009;
                lbl_1_bss_60 = 0;
                break;
            }
            if (lbl_1_data_2A6 == -1 && lbl_1_bss_60 >= 16200 && sp14[0]->unk14 < 16 && sp14[1]->unk14 < 16) {
                lbl_1_data_2A6 = MGSeqTimerCreate(30);
            }
            if (lbl_1_data_2A6 == -1) {
                break;
            }
            if (sp14[0]->unk14 < 16 && sp14[1]->unk14 < 16) {
                MGSeqParamSet(lbl_1_data_2A6, 1, (18059 - lbl_1_bss_60) / 60);
                if (lbl_1_bss_60 > 18000) {
                    MGSeqParamSet(lbl_1_data_2A6, 2, -1);
                    lbl_1_data_2A6 = -1;
                }
            }
            if (lbl_1_bss_60 > 18000 && sp14[0]->unk14 < 16 && sp14[1]->unk14 < 16) {
                lbl_1_bss_5C = 1009;
                lbl_1_bss_60 = 0;
                lbl_1_bss_40 = 1;
                sp14[0]->unk14 = sp14[1]->unk14 = 17;
                sp14[0]->unk18 = sp14[1]->unk18 = 0;
                MGSeqFinishCreate();
                if (lbl_1_data_2A8 != -1) {
                    HuAudSeqFadeOut(lbl_1_data_2A8, 100);
                    lbl_1_data_2A8 = -1;
                }
            }
            break;
        case 1009:
            if (lbl_1_bss_60 == 1 && lbl_1_data_2A6 != -1) {
                MGSeqParamSet(lbl_1_data_2A6, 2, -1);
                lbl_1_data_2A6 = -1;
            }
            lbl_1_bss_60++;
            if (lbl_1_bss_60 >= 120) {
                lbl_1_bss_5C++;
                lbl_1_bss_60 = 0;
            }
            break;
        case 1010:
            lbl_1_bss_60++;
            if (lbl_1_bss_60 == 15) {
                if (lbl_1_bss_44 != 2) {
                    if (sp14[lbl_1_bss_44]->unk08 != -1) {
                        HuAudSStreamPlay(1);
                    } else {
                        HuAudSStreamPlay(3);
                    }
                    if (lbl_1_bss_14 != 0) {
                        if (lbl_1_bss_44 == 0) {
                            _SetFlag(FLAG_ID_MAKE(1, 7));
                        }
                    } else {
                        GWPlayerCoinWinSet(sp14[lbl_1_bss_44]->unk04, 10);
                    }
                } else if (lbl_1_bss_44 == 2) {
                    HuAudSStreamPlay(4);
                }
            }
            if (225.0f < lbl_1_bss_60) {
                if (lbl_1_data_2AC != -1) {
                    HuAudFXStop(lbl_1_data_2AC);
                    lbl_1_data_2AC = -1;
                }
                lbl_1_data_2A4 = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                arg0->func = fn_1_7AE4;
            }
            break;
    }
}

void fn_1_64F8(omObjData* arg0) {
    StructBss68Data* sp18[2];
    StructBss68Data* temp_r29;
    s32 i;

    for (i = 0; i < 2; i++) {
        sp18[i] = lbl_1_bss_68[i]->data;
    }
    arg0->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_BKOOPA, 14));
    Hu3DModelAttrSet(arg0->model[5], HU3D_MOTATTR_LOOP);
    arg0->model[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 38));
    Hu3DModelAttrSet(arg0->model[6], HU3D_MOTATTR_LOOP);
    Hu3DModelHookSet(arg0->model[5], "g007m0-itemhook_r", arg0->model[6]);
    Hu3DModelPosSet(arg0->model[5], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(arg0->model[5], 15.0f, 0.0f, 0.0f);
    arg0->motion[0] = Hu3DJointMotionFile(arg0->model[5], DATA_MAKE_NUM(DATADIR_M457, 39));
    arg0->motion[1] = Hu3DJointMotionFile(arg0->model[5], DATA_MAKE_NUM(DATADIR_M457, 40));
    arg0->motion[2] = Hu3DJointMotionFile(arg0->model[5], DATA_MAKE_NUM(DATADIR_M457, 41));
    arg0->motion[3] = Hu3DJointMotionFile(arg0->model[5], DATA_MAKE_NUM(DATADIR_M457, 42));
    Hu3DMotionSet(arg0->model[5], arg0->motion[0]);
    Hu3DModelLayerSet(arg0->model[6], 2);
    Hu3DModelLayerSet(arg0->model[5], 2);
    Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(arg0->model[6]);
    Hu3DModelShadowSet(arg0->model[5]);
    arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 16));
    Hu3DModelAttrSet(arg0->model[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(arg0->model[0], 0.1f);
    Hu3DModelLayerSet(arg0->model[0], 1);
    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 17));
    Hu3DModelAttrSet(arg0->model[1], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowMapSet(arg0->model[1]);
    Hu3DModelLayerSet(arg0->model[1], 1);
    Hu3DModelScaleSet(arg0->model[1], 1.0f, 1.0f, 1.0f);
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 21));
    Hu3DModelAttrSet(arg0->model[2], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(arg0->model[2], 2);
    arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 19));
    Hu3DModelAttrSet(arg0->model[3], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(arg0->model[3], 2);
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 20));
    Hu3DModelAttrSet(arg0->model[4], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(arg0->model[4], 4);
    for (i = 0; i < 3; i++) {
        arg0->model[i + 7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 18));
        Hu3DModelLayerSet(arg0->model[i + 7], 4);
        Hu3DModelAttrSet(arg0->model[i + 7], HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 16; i++) {
        s32 sp10[] = { 106, 469 };
        s32 sp8[] = { 78, 78 };
        s32 sp60[] = {
            0, 0, -33, -9, 15, 39, 63, -68,
            0, 0, -33, -9, 15, 39, 63, -68
        };
        s32 sp20[] = {
            0, 0, -1, -1, -1, -1, -1, -2,
            0, 0, -1, -1, -1, -1, -1, -2
        };

        if (lbl_1_data_0[i] == DATA_MAKE_NUM(DATADIR_MGCONST, 0)) {
            temp_r29 = lbl_1_bss_68[i == 7 ? 0 : 1]->data;
            lbl_1_data_5C[i] = espEntry((temp_r29->unk08 == -1) ? DATA_MAKE_NUM(DATADIR_M457, 26) : (lbl_1_data_0[i] + temp_r29->unk08), 0, 0);
        } else {
            lbl_1_data_5C[i] = espEntry(lbl_1_data_0[i], 0, 0);
        }
        espDrawNoSet(lbl_1_data_5C[i], 0);
        espDispOff(lbl_1_data_5C[i]);
        espAttrSet(lbl_1_data_5C[i], HU3D_ATTR_DISPOFF);
        espBankSet(lbl_1_data_5C[i], 0);
        espPriSet(lbl_1_data_5C[i], 128 - i);
        espPosSet(lbl_1_data_5C[i], sp60[i] + sp10[i < 8 ? 0 : 1], sp20[i] + sp8[i < 8 ? 0 : 1]);
        if ((i >= 8 ? i - 8 : i) != 0) {
            (void) 1; // Required to match.
        } else {
            espTPLvlSet(lbl_1_data_5C[i], 0.5f);
            espColorSet(lbl_1_data_5C[i], 0, 0, 0);
        }
    }
    for (i = 16; i < 23; i++) {
        s32 temp_r28 = i - 16;
        s32 spFC[23] = { 288, 288 };
        s32 spA0[23] = { 240, 240 };

        lbl_1_data_5C[i] = espEntry(lbl_1_data_0[i], 0, 0);
        espDrawNoSet(lbl_1_data_5C[i], 0);
        espAttrSet(lbl_1_data_5C[i], HU3D_ATTR_DISPOFF | HU3D_ATTR_SHADOW);
        espBankSet(lbl_1_data_5C[i], 0);
        espPriSet(lbl_1_data_5C[i], 128 - i);
        espPosSet(lbl_1_data_5C[i], spFC[temp_r28], spA0[temp_r28]);
        espTPLvlSet(lbl_1_data_5C[i], 1.0f);
    }
    arg0->func = fn_1_2CC4;
}

void fn_1_6FB0(omObjData* arg0) {
    s32 sp14;
    StructBss68Data* temp_r31;
    StructBss68Data* sp10;
    s32 i;

    temp_r31 = arg0->data;
    sp10 = lbl_1_bss_68[1 - arg0->work[0]]->data;
    memset(temp_r31, 0, sizeof(*temp_r31));
    temp_r31->unk00 = arg0->work[0];
    temp_r31->unk04 = (GWPlayerCfg[0].group == temp_r31->unk00) ? 0
        : (GWPlayerCfg[1].group == temp_r31->unk00) ? 1
        : (GWPlayerCfg[2].group == temp_r31->unk00) ? 2
        : (GWPlayerCfg[3].group == temp_r31->unk00) ? 3 : 4;
    sp14 = (GWPlayerCfg[0].group == 1 - temp_r31->unk00) ? 0
        : (GWPlayerCfg[1].group == 1 - temp_r31->unk00) ? 1
        : (GWPlayerCfg[2].group == 1 - temp_r31->unk00) ? 2
        : (GWPlayerCfg[3].group == 1 - temp_r31->unk00) ? 3 : 4;
    if (temp_r31->unk04 == 4) {
        OSReport("m457:wrong player group\n");
        temp_r31->unk04 = temp_r31->unk00;
    }
    if (temp_r31->unk00 == 1 && lbl_1_bss_14 != 0) {
        temp_r31->unk08 = -1;
        temp_r31->unk0C = -1;
        temp_r31->unk04 = -1;
        temp_r31->unk10 = 1;
    } else {
        temp_r31->unk08 = GWPlayerCfg[temp_r31->unk04].character;
        temp_r31->unk0C = (temp_r31->unk08 == -1 || GWPlayerCfg[temp_r31->unk04].iscom) ? -1 : GWPlayerCfg[temp_r31->unk04].pad_idx;
        temp_r31->unk10 = (temp_r31->unk0C != -1) ? 0 : GWPlayerCfg[temp_r31->unk04].diff;
    }
    temp_r31->unk14 = 0;
    temp_r31->unk30 = 100;
    temp_r31->unk34 = 0;
    temp_r31->unk38 = -1;
    temp_r31->unk2C = -1;
    temp_r31->unk3C = 10000;
    temp_r31->unk40 = 1;
    temp_r31->unk44 = -1;
    if (temp_r31->unk08 != -1) {
        arg0->model[0] = CharModelCreate(temp_r31->unk08, 1);
    } else {
        arg0->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_BKOOPA, 7));
    }
    omSetTra(arg0, 0.0f, temp_r31->unk00 == 0 ? 0 : 300, 0.0f);
    if (temp_r31->unk08 != -1) {
        omSetSca(arg0, 2.5f, 2.5f, 2.5f);
    } else {
        omSetSca(arg0, 2.0f, 2.0f, 2.0f);
    }
    for (i = 0; i < 12; i++) {
        if (temp_r31->unk08 != -1) {
            arg0->motion[i] = CharModelMotionCreate(temp_r31->unk08, lbl_1_data_B8[i] + (lbl_1_data_E8[i] != 0 ? temp_r31->unk08 : 0));
        } else if (lbl_1_data_118[i] != 0) {
            arg0->motion[i] = Hu3DJointMotionFile(arg0->model[0], lbl_1_data_118[i]);
        }
    }
    Hu3DMotionSet(arg0->model[0], arg0->motion[temp_r31->unk40]);
    Hu3DMotionTimeSet(arg0->model[0], 10.0f);
    Hu3DModelAttrReset(arg0->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(arg0->model[0]);
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(arg0->model[0], 3);
    CharModelLayerSetAll2(4);
    arg0->rot.y = temp_r31->unk00 * 180 + 90;
    arg0->trans.x = (temp_r31->unk00 == 0 ? -1 : 1) * 300;
    arg0->func = fn_1_46C;
}

void fn_1_75A4(omObjData* arg0) {
    lbl_1_bss_5C = 1000;
    lbl_1_bss_60 = 0;
    lbl_1_bss_54 = 0;
    lbl_1_bss_50 = 0;
    if (lbl_1_data_2A8 == -1) {
        lbl_1_data_2A8 = HuAudSeqPlay(0x4D);
    }
    lbl_1_data_2AC = HuAudFXPlay(0x6D7);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    arg0->func = fn_1_59BC;
}

void ObjectSetup(void) {
    omObjData* var_r30;
    s32 i;

    OSReport("******* M457 ObjectSetup *********\n");
    lbl_1_bss_4C = omInitObjMan(600, 0x2000);
    omGameSysInit(lbl_1_bss_4C);
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

        lbl_1_bss_48 = Hu3DGLightCreateV(&sp3C, &sp30, &sp8);
    }
    Hu3DGLightStaticSet(lbl_1_bss_48, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_48);
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
    Hu3DShadowSizeSet(224);
    lbl_1_data_2A4 = -1;
    lbl_1_bss_44 = -1;
    lbl_1_bss_14 = (_CheckFlag(FLAG_ID_MAKE(1, 0)) != 0);
    HuWinInit(1);
    lbl_1_bss_64 = omAddObjEx(lbl_1_bss_4C, 101, 10, 4, 1, fn_1_64F8);
    for (i = 0; i < 2; i++) {
        var_r30 = lbl_1_bss_68[i] = omAddObjEx(lbl_1_bss_4C, 100, 1, 12, 0, fn_1_6FB0);
        var_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(StructBss68Data), MEMORY_DEFAULT_NUM);
        var_r30->work[0] = i;
    }
    lbl_1_bss_70 = omAddObjEx(lbl_1_bss_4C, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_74 = omAddObjEx(lbl_1_bss_4C, 103, 0, 0, -1, fn_1_75A4);
}

void fn_1_7AE4(omObjData* arg0) {
    StructBss68Data* sp8;
    s32 i;

    if (WipeStatGet() == 0) {
        for (i = 0; i < 2; i++) {
            sp8 = lbl_1_bss_68[i]->data;
        }
        if (lbl_1_data_2A4 >= 0) {
            MGSeqKill(lbl_1_data_2A4);
        }
        MGSeqKillAll();
        HuAudAllStop();
        omOvlReturnEx(1, 1);
    }
}
