#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/wipe.h"

#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/pad.h"
#include "game/sprite.h"

#include "game/hsfmotion.h"

#include "ext_math.h"

#ifndef __MWERKS__
#include "string.h"
#include "game/hsfex.h"
#endif

extern s32 rand8(void);

typedef struct struct_bss_2A6C StructBss2A6C;

typedef struct struct_sp_14C8 StructSp14C8;

typedef struct struct_sp_14C8 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    s32 unk4[4];
    StructBss2A6C *unk14;
    StructBss2A6C *unk18;
    StructSp14C8 *unk1C;
} StructSp14C8;

typedef struct work_19C8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 unk30[0x10];
    float unk40;
    s32 unk44;
    StructBss2A6C *unk48[2];
    u8 unk50[8][2];
    u8 unk60;
    u8 unk61;
    u8 unk62;
    u8 unk63[2];
    u8 unk65[2];
    s32 unk68;
    s32 unk6C;
    u8 unk70;
    u8 unk71;
    u8 unk72;
    s32 unk74;
    u8 unk78;
    u8 unk79;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    s32 unk90;
    s32 unk94;
    float unk98;
    float unk9C;
    float unkA0;
    s16 unkA4;
} Work19C8;

typedef struct struct_bss_2A6C {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    s32 unk8[4];
    union {
        s8 unk18;
        u8 unk18_u;
    };

    Vec unk1C;
    u32 unk28;
    StructSp14C8 *unk2C;
    StructBss2A6C *unk30;
    StructBss2A6C *unk34;
    StructBss2A6C *unk38;
    StructBss2A6C *unk3C;
    StructBss2A6C *unk40;
    StructBss2A6C *unk44;
    StructBss2A6C *unk48;
    StructBss2A6C *unk4C;
    Work19C8 *unk50;
} StructBss2A6C;

typedef struct struct_bss_2684 {
    float unk0;
    float unk4;
    s32 unk8;
    s32 unkC;
    u8 unk10;
} StructBss2684;

typedef struct struct_bss_100 {
    u8 unk0;
    Vec unk4;
    Vec unk10;
    u8 unk1C;
    u8 unk1D;
} StructBss100;

typedef struct struct_bss_b8 {
    s32 unk0;
    s32 unk4;
    float unk8;
    Vec unkC;
} StructBssB8;

typedef struct struct_bss_48 {
    s32 unk0;
    float unk4[3];
} StructBss48;

StructBss2A6C *lbl_1_bss_7884[12];
StructBss2A6C lbl_1_bss_2A6C[238];
StructBss2684 lbl_1_bss_2684[50];
s32 lbl_1_bss_2680;
StructBss100 lbl_1_bss_100[300];
s32 lbl_1_bss_FC;
s32 lbl_1_bss_D4[5][2];
s32 lbl_1_bss_D0;
StructBssB8 lbl_1_bss_B8;
StructBss48 lbl_1_bss_48[7];
omObjData *lbl_1_bss_44;
omObjData *lbl_1_bss_34[4];
omObjData *lbl_1_bss_30;
float lbl_1_bss_2C;
s32 lbl_1_bss_28;
Process *lbl_1_bss_24;
s16 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
s16 lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_8[2];
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

s32 lbl_1_data_0 = -1;
s32 lbl_1_data_4[2] = { -1, -1 };
s32 lbl_1_data_C[4] = { 0, 1, 2, 3 };
float lbl_1_data_1C[7] = { 1000, 1000, 1000, 0, 0, 0, 30 };

const Vec lbl_1_rodata_10[2] = { 0, 7955, 3436, 0, -0.898794f, -0.43837115f };

const GXColor lbl_1_rodata_28 = { 0, 0, 0, 255 };

const Vec lbl_1_rodata_2C[2] = { 0, 5966.25f, 3436, 0, -0.6740955f, -0.43837115f };

const GXColor lbl_1_rodata_44 = { 0, 0, 0, 255 };

void fn_1_A0(s32 arg0)
{
    Mtx44 sp10C;
    Mtx44 spCC;
    Mtx44 sp8C;
    Mtx44 sp4C;
    Mtx44 spC;
    CameraData *temp_r31;
    s16 temp_r30;
    s16 temp_r29;
    s16 temp_r28;
    s16 temp_r27;
    s16 temp_r26;
    s16 temp_r25;

    MTXRotDeg(sp8C, 'y', HuPadSubStkX[0] / 16.0);
    MTXRotDeg(spCC, 'x', HuPadSubStkY[0] / -16.0);
    MTXTrans(spC, (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) - ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0)) * 10.0,
        (((HuPadBtn[0] & PAD_BUTTON_UP) != 0) - ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0)) * 10.0, ((HuPadTrigL[0] - HuPadTrigR[0]) / 128.0) * 30.0);
    MTXConcat(spCC, sp8C, sp4C);
    MTXConcat(spC, sp4C, sp10C);
    for (temp_r30 = 0, temp_r29 = 1; temp_r30 < 16; temp_r30++, temp_r29 <<= 1) {
        if (arg0 & temp_r29) {
            temp_r31 = &Hu3DCamera[temp_r30];
            MTXMultVec(sp10C, &temp_r31->pos, &temp_r31->pos);
            MTXMultVec(sp4C, &temp_r31->up, &temp_r31->up);
            MTXMultVec(sp10C, &temp_r31->target, &temp_r31->target);
        }
    }
    (void)temp_r28;
    (void)temp_r27;
    (void)temp_r26;
    (void)temp_r25;
    (void)temp_r28;
    (void)temp_r27;
    (void)temp_r26;
    (void)temp_r25;
}

s32 fn_1_38C(u8 *arg0, s32 *arg1)
{
    s32 temp_r28;
    s32 temp_r27 = rand8() % 4;

    if (!arg0 || *arg0 == 0) {
        return 0;
    }
    for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {
        s32 temp_r31 = (temp_r28 + temp_r27) % 4;
        if (*arg0 & (1 << temp_r31)) {
            *arg0 = 1 << temp_r31;
            if (arg1) {
                arg1[(temp_r31 + 1) % 4] = arg1[(temp_r31 + 2) % 4] = arg1[(temp_r31 + 3) % 4] = 0;
            }
            return temp_r31;
        }
    }
    return 0;
}

s32 fn_1_4C0(u8 *arg0, s32 *arg1)
{
    s32 temp_r31;

    s32 temp_r28 = rand8() % 4;
    if (!arg0 || *arg0 == 0) {
        return 0;
    }
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        s32 temp_r29 = (temp_r31 + temp_r28) % 4;
        if (*arg0 & (1 << temp_r29)) {
            return arg1[temp_r29];
        }
    }
    return 0;
}

#pragma dont_inline on
s32 fn_1_57C(s8 arg0, float arg1, StructBss2A6C *arg2, StructBss2A6C **arg3)
{
    StructBss2A6C *temp_r31;
    if (arg3) {
        *arg3 = NULL;
    }
    if (arg0 < 0 || arg0 >= 12 || arg1 < 0 || arg1 > 16) {
        return 1;
    }
    for (temp_r31 = lbl_1_bss_7884[arg0]; temp_r31;) {
        if (arg2 == NULL || (temp_r31 != arg2 && (!(arg2->unk1 & 0x2) || !(temp_r31->unk1 & 0x2) || (arg2->unk2 != temp_r31->unk2)))) {
            if (temp_r31->unk1C.y > arg1 - 1.0f && temp_r31->unk1C.y < arg1 + 1.0f) {
                if (arg3) {
                    *arg3 = temp_r31;
                }
                return 1;
            }
        }
        temp_r31 = temp_r31->unk48;
        if (!temp_r31) {
            continue;
        }
        if (temp_r31->unk1C.y >= arg1 + 1.0f) {
            break;
        }
    }
    return 0;
}
#pragma dont_inline off

static inline s32 fn_1_57C_inline(s8 arg0, float arg1, StructBss2A6C *arg2, StructBss2A6C **arg3)
{
    StructBss2A6C *temp_r31;
    if (arg3) {
        *arg3 = NULL;
    }
    if (arg0 < 0 || arg0 >= 12 || arg1 < 0 || arg1 > 16) {
        return 1;
    }
    for (temp_r31 = lbl_1_bss_7884[arg0]; temp_r31;) {
        if (arg2 == NULL || (temp_r31 != arg2 && (!(arg2->unk1 & 0x2) || !(temp_r31->unk1 & 0x2) || (arg2->unk2 != temp_r31->unk2)))) {
            if (temp_r31->unk1C.y > arg1 - 1.0f && temp_r31->unk1C.y < arg1 + 1.0f) {
                if (arg3) {
                    *arg3 = temp_r31;
                }
                return 1;
            }
        }
        temp_r31 = temp_r31->unk48;
        if (!temp_r31) {
            continue;
        }
        if (temp_r31->unk1C.y >= arg1 + 1.0f) {
            break;
        }
    }
    return 0;
}

void fn_1_6D0(s8 arg0, float arg1, StructBss2A6C *arg2)
{
    StructBss2A6C *temp_r31;
    StructBss2A6C *temp_r30;
    if (arg2->unk4C == NULL) {
        lbl_1_bss_7884[arg2->unk18] = arg2->unk48;
    }
    else {
        arg2->unk4C->unk48 = arg2->unk48;
    }
    if (arg2->unk48 != NULL) {
        arg2->unk48->unk4C = arg2->unk4C;
    }
    for (temp_r31 = lbl_1_bss_7884[arg0], temp_r30 = NULL; temp_r31; temp_r31 = temp_r31->unk48) {
        if (temp_r31->unk1C.y > arg1) {
            break;
        }
        temp_r30 = temp_r31;
    }
    arg2->unk18 = arg0;
    arg2->unk1C.y = arg1;
    arg2->unk48 = temp_r31;
    if (arg2->unk48) {
        arg2->unk48->unk4C = arg2;
    }
    arg2->unk4C = temp_r30;
    if (arg2->unk4C) {
        arg2->unk4C->unk48 = arg2;
    }
    if (lbl_1_bss_7884[arg0] == arg2->unk48) {
        lbl_1_bss_7884[arg0] = arg2;
    }
}

s32 fn_1_7F8(StructBss2A6C *arg0, StructSp14C8 *arg1)
{
    s32 temp_r29;
    Work19C8 *temp_r28;
    Work19C8 *temp_r27;
    Work19C8 *temp_r26;
    Work19C8 *temp_r25;
    s32 temp_r23;
    temp_r29 = 0;
    if (!arg0) {
        return temp_r29;
    }
    if (arg0->unk0 == 0) {
        return temp_r29;
    }
    if (lbl_1_bss_7884[arg0->unk18] == arg0) {
        lbl_1_bss_7884[arg0->unk18] = arg0->unk48;
    }
    if (arg0->unk4C) {
        arg0->unk4C->unk48 = arg0->unk48;
    }
    if (arg0->unk48) {
        arg0->unk48->unk4C = arg0->unk4C;
    }
    if (arg0->unk38) {
        arg0->unk38->unk3C = NULL;
    }
    if (arg0->unk3C) {
        arg0->unk3C->unk38 = NULL;
    }
    if (arg0->unk44) {
        arg0->unk44->unk40 = NULL;
    }
    if (arg0->unk40) {
        arg0->unk40->unk44 = NULL;
    }

    if (arg0->unk0 >= 1 && arg0->unk0 <= 4) {
        temp_r28 = lbl_1_bss_34[0]->data;
        temp_r27 = lbl_1_bss_34[1]->data;
        temp_r26 = lbl_1_bss_34[2]->data;
        temp_r25 = lbl_1_bss_34[3]->data;
        temp_r29 = (fn_1_4C0(&arg1->unk2, arg1->unk4) > 0) ? 2 : 1;
        if (lbl_1_bss_18 == -1) {
            if (arg1->unk2 & 0x1) {
                temp_r28->unk24 += temp_r29;
                temp_r28->unk68 += (arg0->unk1 & 0x10) ? 1 : 0;
            }
            if (arg1->unk2 & 0x2) {
                temp_r27->unk24 += temp_r29;
                temp_r27->unk68 += (arg0->unk1 & 0x10) ? 1 : 0;
            }
            if (arg1->unk2 & 0x4) {
                temp_r26->unk24 += temp_r29;
                temp_r26->unk68 += (arg0->unk1 & 0x10) ? 1 : 0;
            }
            if (arg1->unk2 & 0x8) {
                temp_r25->unk24 += temp_r29;
                temp_r25->unk68 += (arg0->unk1 & 0x10) ? 1 : 0;
            }
        }
        for (temp_r23 = 0; temp_r23 < 2; temp_r23++) {
            lbl_1_bss_100[lbl_1_bss_FC].unk0 = arg0->unk0;
            lbl_1_bss_100[lbl_1_bss_FC].unk4.x = ((arg0->unk18 * 100) - 500.0) - 50.0;
            lbl_1_bss_100[lbl_1_bss_FC].unk4.y = ((100.0f * arg0->unk1C.y) - 500.0f) + 50.0f;
            lbl_1_bss_100[lbl_1_bss_FC].unk4.z = 120;
            lbl_1_bss_100[lbl_1_bss_FC].unk10.x = ((rand8() / 255.0) * 24.0) - 12;
            lbl_1_bss_100[lbl_1_bss_FC].unk10.y = (rand8() / 255.0) * 16.0;
            lbl_1_bss_100[lbl_1_bss_FC].unk10.z = ((rand8() / 255.0) * 10.0) + 6;
            lbl_1_bss_100[lbl_1_bss_FC].unk1C = rand8();
            lbl_1_bss_100[lbl_1_bss_FC].unk1D = rand8();
            lbl_1_bss_FC++;
            lbl_1_bss_FC = (lbl_1_bss_FC >= 300) ? 0 : lbl_1_bss_FC;
        }
    }
    arg0->unk0 = arg0->unk1 = arg0->unk2 = arg0->unk3 = 0;
    arg0->unk48 = arg0->unk4C = NULL;
    return temp_r29;
}

void fn_1_EC0(Work19C8 *arg0)
{
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r26;
    s32 temp_r27;
    s32 temp_r25;
    u8 temp_r24;

    for (temp_r30 = 0; temp_r30 < 8; temp_r30++) {
        for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
            arg0->unk50[temp_r30][temp_r29] = 1;
        }
    }
    for (temp_r30 = 1; temp_r30 < 4; temp_r30++) {
        for (temp_r29 = 0; temp_r29 < 4;) {
            temp_r26 = rand8() % 8;
            temp_r28 = rand8() % 2;
            if (arg0->unk50[temp_r26][temp_r28] == 1) {
                arg0->unk50[temp_r26][temp_r28] = temp_r30 + 1;
                temp_r29++;
            }
        }
    }
    for (temp_r30 = 0; temp_r30 < 8; temp_r30++) {
        if (arg0->unk50[temp_r30][0] == arg0->unk50[temp_r30][1]) {
            do {
                temp_r29 = rand8() % 8;
            } while (
                temp_r30 == temp_r29 || arg0->unk50[temp_r30][0] == arg0->unk50[temp_r29][0] || arg0->unk50[temp_r30][0] == arg0->unk50[temp_r29][1]);

            temp_r27 = rand8() % 2;
            temp_r25 = arg0->unk50[temp_r30][0];
            temp_r24 = arg0->unk50[temp_r29][temp_r27];
            arg0->unk50[temp_r30][rand8() % 2] = temp_r24;
            arg0->unk50[temp_r29][temp_r27] = temp_r25;
        }
    }
}

void fn_1_10B8(Work19C8 *arg0)
{
    s32 temp_r31;
    s32 temp_r30;
    u8 sp16C[12][17] = {};
    u8 sp6C[12] = {};
    s32 temp_r22 = (arg0->unk48[0]->unk18 - 4 < 0) ? 0 : (arg0->unk48[0]->unk18 - 4);
    s32 temp_r21 = (arg0->unk48[0]->unk18 + 4 > 11) ? 11 : (arg0->unk48[0]->unk18 + 4);
    s32 sp44[2] = {};
    s32 sp3C[2] = {};
    s32 sp34[2] = { 9, 9 };
    s32 temp_r20 = 0;
    s32 temp_r19 = 0;
    s32 temp_r18 = 0;
    u8 sp8[2];
    sp44[0] = sp44[1] = temp_r22;
    sp3C[0] = sp3C[1] = temp_r21;
    sp34[0] = arg0->unk48[0]->unk1C.y - 0.5;
    sp34[1] = arg0->unk48[0]->unk1C.y - 1.5;
    sp34[1] = (sp34[1] < 0) ? 0 : sp34[1];
    sp8[0] = arg0->unk48[0]->unk0;
    sp8[1] = arg0->unk48[1]->unk0;
    for (temp_r31 = temp_r22; temp_r31 <= temp_r21; temp_r31++) {
        StructBss2A6C *temp_r27;
        s32 temp_r26;
        for (temp_r27 = lbl_1_bss_7884[temp_r31], temp_r26 = 0; temp_r27; temp_r27 = temp_r27->unk48) {
            if (temp_r27->unk1 & 0x2) {
                continue;
            }
            sp16C[temp_r31][temp_r26] = temp_r27->unk0;
            temp_r26++;
        }
        sp6C[temp_r31] = temp_r26;
        for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
            if (temp_r26 > sp34[temp_r30]) {
                if (temp_r31 <= arg0->unk48[0]->unk18) {
                    sp44[temp_r30] = temp_r31 + 1;
                }
                else {
                    sp3C[temp_r30] = temp_r31 - 1;
                }
            }
        }
    }
    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
        for (temp_r31 = sp44[temp_r30 == 2]; temp_r31 <= sp3C[temp_r30 == 2]; temp_r31++) {
            if (temp_r31 != sp44[temp_r30 == 2] || temp_r30 != 3) {
                if (temp_r31 != sp3C[temp_r30 == 2] - 1 || temp_r30 != 1) {
                    s32 temp_r25;
                    s32 spAC[4][12];
                    for (temp_r25 = 0; temp_r25 < 2; temp_r25++) {
                        s32 sp5C[4] = { 0, 1, 0, -1 };
                        s32 sp4C[4] = { 1, 0, -1, 0 };
                        s32 temp_r29;
                        s32 temp_r28;
                        s32 temp_r24;
                        s32 temp_r23;

                        spAC[temp_r30][temp_r31] = arg0->unk48[0]->unk18 - temp_r31;
                        spAC[temp_r30][temp_r31] = (spAC[temp_r30][temp_r31] < 0) ? (-spAC[temp_r30][temp_r31]) : spAC[temp_r30][temp_r31];
                        spAC[temp_r30][temp_r31]
                            = (spAC[temp_r30][temp_r31] < 3) ? ((3 - spAC[temp_r30][temp_r31]) * (3 - spAC[temp_r30][temp_r31])) : 0;
                        spAC[temp_r30][temp_r31] *= (arg0->unk20 == 0) ? 4 : ((arg0->unk20 == 1) ? 2 : 1);
                        temp_r24 = temp_r31 + ((temp_r25 == 1) ? sp5C[temp_r30] : 0);
                        for (temp_r28 = temp_r24 - 2; temp_r28 <= temp_r24 + 2; temp_r28++) {
                            temp_r23 = sp6C[temp_r24] + ((temp_r25 == 1) ? sp4C[temp_r30] : 0);
                            for (temp_r29 = temp_r23 - 2; temp_r29 <= temp_r23 + 2; temp_r29++) {
                                if (temp_r28 < 0 || temp_r28 >= 12 || temp_r29 < 0 || temp_r29 >= 9) {
                                    continue;
                                }
                                if (sp16C[temp_r28][temp_r29] != 5 && arg0->unk48[temp_r25]->unk0 == sp16C[temp_r28][temp_r29]) {
                                    u8 sp91[5][5] = { 0, 3, 0, 3, 0, 2, 10, 24, 10, 2, 10, 24, 0, 24, 10, 2, 10, 24, 10, 2, 0, 2, 10, 2, 0 };
                                    spAC[temp_r30][temp_r31] += sp91[temp_r28 - (temp_r24 - 2)][temp_r29 - (temp_r23 - 2)];
                                }
                                if (sp16C[temp_r28][temp_r29] == 5) {
                                    u8 sp78[5][5] = { 0, 0, 0, 0, 0, 0, 40, 40, 40, 0, 0, 40, 0, 40, 0, 0, 40, 40, 40, 0, 0, 0, 0, 0, 0 };
                                    spAC[temp_r30][temp_r31]
                                        += sp78[temp_r28 - (temp_r24 - 2)][temp_r29 - (temp_r23 - 2)] / ((arg0->unk20 == 0) ? 4 : 1);
                                }
                            }
                        }
                    }
                    if (spAC[temp_r30][temp_r31] > temp_r20) {
                        temp_r20 = spAC[temp_r30][temp_r31];
                        temp_r18 = temp_r30;
                        temp_r19 = temp_r31;
                    }
                }
            }
        }
    }
    arg0->unk7C = temp_r19;
    arg0->unk80 = temp_r18;
}

void fn_1_19C4(omObjData *object) { }

void fn_1_19C8(omObjData *object)
{
    Work19C8 *temp_r31;
    s32 sp19C;
    s32 spC4;
    s32 spC0;

    temp_r31 = object->data;
    temp_r31->unk28 = temp_r31->unk24;

    temp_r31->unk65[0] = (temp_r31->unk65[0] == 0 || temp_r31->unk65[0] >= 15) ? 0 : temp_r31->unk65[0] + 1;
    if (temp_r31->unk1C != -1) {
        sp19C = (HuPadStkX[temp_r31->unk1C] > 26) - (HuPadStkX[temp_r31->unk1C] < -26);
    }
    else {
        sp19C = (temp_r31->unk72 == 1 && temp_r31->unk7C != -1) ? ((temp_r31->unk48[0]) ? ((temp_r31->unk7C < temp_r31->unk48[0]->unk18) ? -1
                                                                           : (temp_r31->unk7C > temp_r31->unk48[0]->unk18)               ? 1
                                                                                                                                         : 0)
                                                                                        : 0)
                                                                : 0;
    }
    temp_r31->unk88 = ((temp_r31->unk72 == 1 && temp_r31->unk48[0]) && temp_r31->unk7C == temp_r31->unk48[0]->unk18) ? (temp_r31->unk88 + 1) : 0;
    if (sp19C != temp_r31->unk0) {
        temp_r31->unkC = (sp19C == 0) ? 0 : 1;
    }
    else {
        temp_r31->unkC = (temp_r31->unk0 != 0) ? temp_r31->unkC + 1 : 0;
    }
    temp_r31->unkC = (temp_r31->unkC >= 17) ? 14 : temp_r31->unkC;
    temp_r31->unk0 = sp19C;
    if (temp_r31->unk72 == 2) {
        float temp_f30;
        float temp_f24;
        s32 temp_r25;
        s32 temp_r23;
        s32 temp_r22;
        StructBss2A6C *sp198;

        for (temp_r23 = 0; temp_r23 < 3; temp_r23++) {
            s32 sp24C[3] = { 1, 2, 0 };
            temp_r22 = (temp_r31->unk10 * 3) + ((temp_r31->unk10 < 2) ? sp24C[temp_r23] : (2 - sp24C[temp_r23]));
            if (fn_1_57C_inline(temp_r22, 9.5f, NULL, NULL) == 0) {
                if (fn_1_57C_inline(temp_r22, 8.5f, NULL, NULL) == 0) {
                    break;
                }
            }
        }
        temp_r22 = (temp_r23 == 3) ? ((temp_r31->unk10 * 3) + 1) : temp_r22;
        temp_f30 = (temp_r22 * 100) - 490;
        temp_r31->unkA0 = (temp_r31->unk74 == 0)
            ? temp_f30
            : ((temp_r31->unkA0 - 10 > temp_f30)
                    ? (temp_r31->unkA0 - 10)
                    : (((temp_r31->unkA0 > temp_f30)
                            ? temp_f30
                            : ((temp_r31->unkA0 + 10 < temp_f30) ? (temp_r31->unkA0 + 10)
                                                                 : ((temp_r31->unkA0 < temp_f30) ? temp_f30 : temp_r31->unkA0)))));
        temp_r31->unk74++;
        temp_f30 = temp_r31->unk74 / 24.0f;
        temp_f30 = (temp_f30 > 1.0f) ? 1.0f : temp_f30;
        temp_f30 = (0.5 * sind((temp_f30 * 180.0f) + 270.0f)) + 0.5;
        temp_f24 = 1.0f - temp_f30;
        if (lbl_1_bss_18 == -1) {
            Vec sp240;
            Vec sp234;
            sp240.x = (temp_r31->unkA0 * temp_f30) + (temp_r31->unk98 * temp_f24);
            sp240.y = (425.0f * temp_f30) + (temp_r31->unk9C * temp_f24);
            sp240.z = 55;
            Hu3D3Dto2D(&sp240, 1, &sp234);
            HuSprPosSet(temp_r31->unkA4, 0, sp234.x, sp234.y);
        }
        if (lbl_1_bss_44->work[0] == 1002 && temp_r31->unk74 >= 24) {
            for (temp_r23 = 0; temp_r23 < 3; temp_r23++) {
                s32 sp228[3] = { 1, 2, 0 };
                temp_r22 = (temp_r31->unk10 * 3) + ((temp_r31->unk10 < 2) ? sp228[temp_r23] : (2 - sp228[temp_r23]));
                if (fn_1_57C_inline(temp_r22, 9.5f, NULL, NULL) == 0) {
                    if (fn_1_57C_inline(temp_r22, 8.5f, NULL, NULL) == 0) {
                        break;
                    }
                }
            }
            if (temp_r23 != 3) {
                for (sp198 = lbl_1_bss_7884[temp_r22]; sp198 && sp198->unk48; sp198 = sp198->unk48)
                    ;
                for (temp_r23 = 0; temp_r23 < 2; temp_r23++) {
                    temp_r25 = (lbl_1_bss_0 + 1) % 238;
                    while (temp_r25 != lbl_1_bss_0) {
                        if (lbl_1_bss_2A6C[temp_r25].unk0 == 0) {
                            break;
                        }
                        temp_r25++;
                        temp_r25 = temp_r25 % 238;
                        if (temp_r25 == 0) {
                            OSReport("looped.\n");
                        }
                    }
                    if (temp_r25 == lbl_1_bss_0) {
                        OSReport("m413:error:block empty.\n");
                    }
                    lbl_1_bss_0 = temp_r25;
                    temp_r31->unk48[temp_r23] = &lbl_1_bss_2A6C[temp_r25];
                    lbl_1_bss_2A6C[temp_r25].unk0 = temp_r31->unk50[temp_r31->unk60][temp_r23];
                    lbl_1_bss_2A6C[temp_r25].unk1 = 2;
                    lbl_1_bss_2A6C[temp_r25].unk3 = 1 << temp_r31->unk10;
                    lbl_1_bss_2A6C[temp_r25].unk2 = temp_r31->unk10;
                    lbl_1_bss_2A6C[temp_r25].unk18 = temp_r22;
                    lbl_1_bss_2A6C[temp_r25].unk1C.x = temp_r22;
                    lbl_1_bss_2A6C[temp_r25].unk1C.y = temp_r23 + 8.9375f;
                    lbl_1_bss_2A6C[temp_r25].unk1C.z = 0;
                    lbl_1_bss_2A6C[temp_r25].unk8[0] = lbl_1_bss_2A6C[temp_r25].unk8[1] = lbl_1_bss_2A6C[temp_r25].unk8[2]
                        = lbl_1_bss_2A6C[temp_r25].unk8[3] = 0;
                    lbl_1_bss_2A6C[temp_r25].unk2C = 0;
                    lbl_1_bss_2A6C[temp_r25].unk30 = 0;
                    lbl_1_bss_2A6C[temp_r25].unk34 = 0;
                    lbl_1_bss_2A6C[temp_r25].unk50 = temp_r31;
                }
                temp_r31->unk48[1]->unk48 = NULL;
                temp_r31->unk48[1]->unk4C = temp_r31->unk48[0];
                temp_r31->unk48[0]->unk48 = temp_r31->unk48[1];
                temp_r31->unk48[0]->unk4C = sp198;
                if (!sp198) {
                    lbl_1_bss_7884[temp_r31->unk48[0]->unk18] = temp_r31->unk48[0];
                }
                else {
                    temp_r31->unk48[0]->unk4C->unk48 = temp_r31->unk48[0];
                }
                temp_r31->unk60++;
                if (temp_r31->unk60 >= 8) {
                    fn_1_EC0(temp_r31);
                    temp_r31->unk60 = 0;
                }
                temp_r31->unk63[0] = temp_r31->unk48[0]->unk0;
                temp_r31->unk63[1] = temp_r31->unk48[1]->unk0;
                temp_r31->unk65[0] = 1;
                if (((temp_r31->unk68 + 5) / 7) != ((temp_r31->unk6C + 5) / 7)) {
                    if (((temp_r31->unk68 + 5) / 7) % 4 == 2) {
                        temp_r31->unk50[temp_r31->unk60][0] = 5;
                        temp_r31->unk50[temp_r31->unk60][1] = 5;
                    }
                    else {
                        temp_r31->unk50[temp_r31->unk60][rand8() % 2] = 5;
                    }
                }
                temp_r31->unk6C = temp_r31->unk68;
                temp_r31->unk72 = 1;
                temp_r31->unk74 = 0;
                temp_r31->unk71 = 20;
                temp_r31->unk70 = 0;
                temp_r31->unk7C = -1;
                temp_r31->unk80 = -1;
                if (temp_r31->unk1C == -1) {
                    temp_r31->unk84 = 0;
                    temp_r31->unk88 = 0;
                    temp_r31->unk8C = temp_r31->unk48[0]->unk18;
                    temp_r31->unk90 = 0;
                }
                temp_r31->unk78 = 0;
                temp_r31->unk79 = 0;
                HuSprAttrReset(temp_r31->unkA4, 0, HUSPR_ATTR_DISPOFF);
                HuSprAttrReset(temp_r31->unkA4, 0, HUSPR_ATTR_REVERSE);
                {
                    s32 sp258[12] = {};
                    s32 sp194;
                    for (sp194 = 0; sp194 < 3; sp194++) {
                        StructBss2A6C *sp190;
                        for (sp190 = lbl_1_bss_7884[sp194 + (temp_r31->unk10 * 3)]; sp190; sp190 = sp190->unk48) {

                            sp258[sp194] += (sp190 && sp190->unk0 && (sp190->unk1 & 0x2) == 0 && sp258[sp194] < 9);
                        }
                    }
                    Hu3DModelRotSet(object->model[4], 0, ((sp258[0] + sp258[1] + sp258[2] >= 22) ? -90 : 0), 0);
                }
            }
            else {
                s32 sp21C[3];
                s32 sp18C;
                for (sp18C = 0; sp18C < 3; sp18C++) {
                    s32 sp188;
                    StructBss2A6C *sp184;
                    for (sp184 = lbl_1_bss_7884[sp18C + (temp_r31->unk10 * 3)], sp188 = 0; sp188 < 9; sp184 = sp184->unk48, sp188++) {
                        if (!sp184 || sp184->unk1 != 1) {
                            break;
                        }
                    }
                    sp21C[sp18C] = sp188;
                }
                if (sp21C[0] >= 9 && sp21C[1] >= 9 && sp21C[2] >= 9) {
                    temp_r31->unk78 += temp_r31->unk78 < 255;
                    Hu3DModelRotSet(object->model[4], 0, -90, 0);
                    temp_r31->unk79 = 1;
                }
                else {
                    temp_r31->unk79 = 0;
                }
            }
        }
    }
    else if (temp_r31->unk72 == 1) {
        if (!temp_r31->unk48[0] || !temp_r31->unk48[1]) {
            temp_r31->unk72 = 2;
            temp_r31->unk74 = 0;
            HuSprAttrSet(temp_r31->unkA4, 0, HUSPR_ATTR_REVERSE);
        }
        else {
            s32 temp_r26;
            s32 sp180;

            sp180 = (temp_r31->unkC == 1 || temp_r31->unkC == 14) ? temp_r31->unk0 : 0;
            temp_r26 = temp_r31->unk70;
            if (temp_r31->unk1C != -1) {
                temp_r26 = (HuPadBtnDown[temp_r31->unk1C] & (PAD_BUTTON_X | PAD_BUTTON_Y))
                    ? (temp_r31->unk70 + 2)
                    : (temp_r31->unk70 + ((HuPadBtnDown[temp_r31->unk1C] & PAD_BUTTON_A) ? 1 : 0)
                        + ((HuPadBtnDown[temp_r31->unk1C] & PAD_BUTTON_B) ? -1 : 0));
            }
            else {
                if (temp_r31->unk80 != -1 && temp_r31->unk80 != temp_r31->unk70 && temp_r31->unk84 > 5) {
                    temp_r26 = temp_r31->unk80;
                    temp_r31->unk84 = 0;
                }
                else {
                    temp_r31->unk84++;
                }
            }
            temp_r26 = (temp_r26 >= 4) ? (temp_r26 - 4) : ((temp_r26 < 0) ? (temp_r26 + 4) : temp_r26);
            temp_r31->unk74++;
            if (temp_r31->unk1C == -1) {
                s32 sp20C[4] = { 120, 60, 25, 2 };
                s32 sp200[3] = { 60, 45, 25 };
                temp_r31->unk90 = (temp_r31->unk8C == temp_r31->unk48[0]->unk18 && temp_r31->unk8C != temp_r31->unk7C) ? (temp_r31->unk90 + 1) : 0;
                temp_r31->unk8C = temp_r31->unk48[0]->unk18;
                if (temp_r31->unk7C == -1 && temp_r31->unk90 >= sp20C[temp_r31->unk20]
                    || (temp_r31->unk20 >= 1 && (temp_r31->unk90 >= sp200[temp_r31->unk20 - 1]))) {
                    s32 sp1F0[4] = { 30, 30, 20, 10 };
                    fn_1_10B8(temp_r31);
                    temp_r31->unk84 = 0;
                    temp_r31->unk88 = 0;
                    temp_r31->unk94 = (rand8() % sp1F0[temp_r31->unk20]) - (sp1F0[temp_r31->unk20] / 2);
                }
            }
            if (lbl_1_bss_18 == -1) {
                if (temp_r31->unk1C != -1) {
                    temp_r31->unk48[0]->unk1C.z = temp_r31->unk48[1]->unk1C.z
                        = -0.03125f + ((HuPadStkY[temp_r31->unk1C] < -36) ? (-0.26875f * ((-HuPadStkY[temp_r31->unk1C] - 36) / 36.0f)) : 0);
                    temp_r31->unk4 = (HuPadStkY[temp_r31->unk1C] < -36) ? 1 : 0;
                }
                else {
                    s32 sp1E4[3] = { 50, 30, 25 };
                    s32 sp1D8[3] = { 90, 80, 70 };

                    temp_r31->unk4
                        = ((temp_r31->unk20
                              && (temp_r31->unk88 > temp_r31->unk94 + sp1E4[temp_r31->unk20 - 1] || temp_r31->unk90 > sp1D8[temp_r31->unk20 - 1])))
                        ? 1
                        : 0;
                    temp_r31->unk48[0]->unk1C.z = temp_r31->unk48[1]->unk1C.z = -0.03125f + (temp_r31->unk4 ? -0.26875f : 0.0f);
                }
            }
            else {
                temp_r31->unk48[0]->unk1C.z = temp_r31->unk48[1]->unk1C.z = 0;
            }
            if (lbl_1_bss_18 == -1 && sp180) {
                if (fn_1_57C_inline(temp_r31->unk48[0]->unk18_u + sp180, temp_r31->unk48[0]->unk1C.y, temp_r31->unk48[0], NULL) == 0) {
                    if (fn_1_57C_inline(temp_r31->unk48[1]->unk18_u + sp180, temp_r31->unk48[1]->unk1C.y, temp_r31->unk48[1], NULL) == 0) {
                        float sp17C = temp_r31->unk48[0]->unk18;
                        float sp178 = temp_r31->unk48[1]->unk18;
                        fn_1_6D0(temp_r31->unk48[0]->unk18_u + sp180, temp_r31->unk48[0]->unk1C.y, temp_r31->unk48[0]);
                        fn_1_6D0(temp_r31->unk48[1]->unk18_u + sp180, temp_r31->unk48[1]->unk1C.y, temp_r31->unk48[1]);
                        temp_r31->unk48[0]->unk1C.x = (sp17C * 0.5) + (0.5 * temp_r31->unk48[0]->unk18);
                        temp_r31->unk48[1]->unk1C.x = (sp178 * 0.5) + (0.5 * temp_r31->unk48[1]->unk18);
                    }
                }
            }
            if (lbl_1_bss_18 != -1) {
                temp_r26 = temp_r31->unk70;
            }
            if (temp_r26 != temp_r31->unk70) {
                StructBss2A6C *temp_r29 = temp_r31->unk48[0];
                StructBss2A6C *temp_r30 = temp_r31->unk48[1];
                s32 sp174 = temp_r29->unk18;
                float temp_f25 = temp_r29->unk1C.y;
                s32 sp1C8[4] = { 0, 1, 0, -1 };
                s32 sp1B8[4] = { 1, 0, -1, 0 };
                StructBss2A6C *sp170;
                if (fn_1_57C_inline(sp174 + sp1C8[temp_r26], temp_f25 + sp1B8[temp_r26], temp_r30, &sp170) == 0) {
                    if (temp_r31->unk70 != temp_r26) {
                        temp_r30->unk5 = 1;
                        temp_r30->unk4 = (((((temp_r26 - temp_r31->unk70) + 8) % 4) - 1) * 4) + temp_r31->unk70 + 1;
                    }
                    temp_r31->unk70 = temp_r26;
                    fn_1_6D0(sp174 + sp1C8[temp_r26], temp_f25 + sp1B8[temp_r26], temp_r30);
                    temp_r30->unk1C.x = temp_r30->unk18;
                }
                else {
                    float temp_f31;
                    s32 temp_r24;
                    if (temp_r26 % 2 == 0) {
                        s32 sp16C = (temp_r26 == 2) ? 1 : 0;
                        temp_f31 = temp_f25 + ((sp16C == 1) ? sp1B8[temp_r26] : sp1B8[temp_r26]);
                        fn_1_57C_inline(sp174, temp_f31, (sp16C == 0) ? temp_r30 : temp_r30, &sp170);
                        if (temp_r26 == 2) {
                            if (!sp170 || sp170->unk1C.y <= temp_f31) {
                                temp_f31 = ((sp16C == 1) ? 1.0f : 0.0f) + ((sp170) ? sp170->unk1C.y + 1.0f : 0.0f);
                                temp_r24 = sp174;
                            }
                            else {
                                temp_f31 = (sp170->unk1C.y - 1.0f) - (sp16C == 0);
                                temp_r24 = sp174;
                            }
                        }
                        else {
                            if (sp170->unk1C.y >= temp_f31) {
                                temp_f31 = ((sp16C == 1) ? 1.0f : 0.0f) + ((sp170) ? sp170->unk1C.y - 2.0f : 0.0f);
                                temp_r24 = sp174;
                            }
                            else {
                                temp_f31 = (sp170->unk1C.y - 1.0f) - (sp16C == 0);
                                temp_r24 = sp174;
                            }
                        }
                    }
                    else {
                        temp_r24 = sp174 - sp1C8[temp_r26];
                        temp_f31 = temp_f25;
                    }
                    if (fn_1_57C_inline(temp_r24, temp_f31, temp_r29, NULL) == 0) {
                        if (fn_1_57C_inline(temp_r24 + sp1C8[temp_r26], temp_f31 + sp1B8[temp_r26], temp_r30, NULL) == 0) {
                            float sp168 = temp_r31->unk48[0]->unk18;
                            float sp164 = temp_r31->unk48[1]->unk18;
                            if (temp_r31->unk70 != temp_r26) {
                                temp_r30->unk5 = 1;
                                temp_r30->unk4 = (((((temp_r26 - temp_r31->unk70) + 8) % 4) - 1) * 4) + temp_r31->unk70 + 1;
                            }
                            temp_r31->unk70 = temp_r26;
                            if (temp_r26 == 2) {
                                fn_1_6D0(temp_r24, temp_f31 + (0.5 * (float)sp1B8[temp_r26]), temp_r29);
                                fn_1_6D0(temp_r24 + sp1C8[temp_r26], temp_f31 + sp1B8[temp_r26], temp_r30);
                                fn_1_6D0(temp_r24, temp_f31, temp_r29);
                            }
                            else {
                                fn_1_6D0(temp_r24, temp_f31, temp_r29);
                                fn_1_6D0(temp_r24 + sp1C8[temp_r26], temp_f31 + sp1B8[temp_r26], temp_r30);
                            }
                            temp_r31->unk48[0]->unk1C.x = (sp168 * 0.5) + (0.5 * temp_r31->unk48[0]->unk18);
                            temp_r31->unk48[1]->unk1C.x = (sp164 * 0.5) + (0.5 * temp_r31->unk48[1]->unk18);
                        }
                    }
                }
            }
        }
        if (temp_r31->unk48[0]) {
            temp_r31->unk98 = 10.0 + ((100.0 * ((temp_r31->unk48[0]->unk18 + temp_r31->unk48[0]->unk1C.x) / 2.0)) - 500);
            temp_r31->unk9C = 25.0f + ((100.0f * temp_r31->unk48[0]->unk1C.y) - 500.0f);
        }
        if (lbl_1_bss_18 == -1) {
            Vec sp1AC;
            Vec sp1A0;
            sp1AC.x = temp_r31->unk98;
            sp1AC.y = temp_r31->unk9C;
            sp1AC.z = 55;
            Hu3D3Dto2D(&sp1AC, 1, &sp1A0);
            HuSprPosSet(temp_r31->unkA4, 0, sp1A0.x, sp1A0.y);
        }
    }
}

void fn_1_8AC8(StructBss2A6C *arg0, StructSp14C8 *arg1);

#define CHECK_2E48(arg0, arg1, arg2)                                                                                                                 \
    (((arg0)-1 <= 0 || (arg2[(arg0)-1][(arg1)] && arg2[(arg0)-1][(arg1)]->unk0))                                                                     \
        && ((arg0)-1 >= 11 || (arg2[(arg0) + 1][(arg1)] && arg2[(arg0) + 1][(arg1)]->unk0))                                                          \
        && ((arg1)-1 <= 0 || (arg2[(arg0)][(arg1)-1] && arg2[(arg0)][(arg1)-1]->unk0))                                                               \
        && ((arg1)-1 >= 8 || (arg2[(arg0)][(arg1) + 1] && arg2[(arg0)][(arg1) + 1]->unk0))                                                           \
        && ((arg0)-1 >= 11 || (arg1)-1 <= 0 || (arg2[(arg0) + 1][(arg1)-1] && arg2[(arg0) + 1][(arg1)-1]->unk0))                                     \
        && ((arg0)-1 >= 11 || (arg1)-1 >= 8 || (arg2[(arg0) + 1][(arg1) + 1] && arg2[(arg0) + 1][(arg1) + 1]->unk0))                                 \
        && ((arg0)-1 <= 0 || (arg1)-1 <= 0 || (arg2[(arg0)-1][(arg1)-1] && arg2[(arg0)-1][(arg1)-1]->unk0))                                          \
        && ((arg0)-1 <= 0 || (arg1)-1 >= 8 || (arg2[(arg0)-1][(arg1) + 1] && arg2[(arg0)-1][(arg1) + 1]->unk0)))

void fn_1_52A4(s32 arg0)
{
    omObjData *sp1EC = lbl_1_bss_30;
    StructBss2A6C *sp2E48[14][19] = {};
    StructBss2A6C *sp1E8 = NULL;
    StructBss2A6C *temp_r31;
    StructBss2A6C *temp_r30;
    s32 temp_r29;
    s32 temp_r23;
    s32 temp_r19;
    s32 temp_r18;
    float temp_f31;
    float temp_f30;
    float temp_f29;

    StructSp14C8 sp14C8[204];
    StructBss2A6C *spD58[476];
    StructSp14C8 *spA28[204];
    float sp6F8[204];
    float sp3C8[204];
    s16 sp230[204];

    for (temp_r18 = 0; temp_r18 < 12; temp_r18++) {
        for (temp_r31 = lbl_1_bss_7884[temp_r18]; temp_r31; temp_r31 = temp_r31->unk48) {
            s32 sp1E4 = temp_r31->unk1;
            s32 sp1E0 = (((sp1E4 & 0x2) == 0 && (arg0 == 4)) || ((sp1E4 & 0x2) && (temp_r31->unk3 & (1 << arg0))));
            temp_f29 = (sp1E0) ? temp_r31->unk1C.z : 0;
            temp_r31->unk2C = (void *)(temp_r31->unk30 = temp_r31->unk34 = NULL);
            temp_r31->unk38 = temp_r31->unk3C = temp_r31->unk40 = temp_r31->unk44 = NULL;
            if (arg0 == 4) {
                temp_r31->unk5 += temp_r31->unk4 != 0 && temp_r31->unk5 != 0;
                temp_r31->unk5 = (temp_r31->unk4 == 0 || (temp_r31->unk5 > (((temp_r31->unk4 - 1) / 4 == 1) ? 15 : 15))) ? 0 : temp_r31->unk5;
                temp_r31->unk4 = (temp_r31->unk5 == 0) ? 0 : temp_r31->unk4;
                temp_r31->unk1C.x = (0.5 * temp_r31->unk18) + (0.5 * temp_r31->unk1C.x);
            }
            if (temp_r31->unk0) {
                s32 sp1DC = 0;
                StructBss2A6C *sp1D8;
                if ((temp_r31->unk1 & 0x1) && temp_r31->unk1C.y == 0.0f && !temp_r31->unk4C) {
                    sp1DC = 1;
                    sp1D8 = NULL;
                }
                else if ((temp_r31->unk1 & 0x1) && temp_r31->unk4C && (temp_r31->unk4C->unk1C.y == temp_r31->unk1C.y - 1.0f)) {
                    sp1DC = 2;
                    sp1D8 = temp_r31->unk4C;
                }
                else {
                    if (fn_1_57C(temp_r18, temp_r31->unk1C.y + temp_f29, temp_r31, &sp1D8)) {
                        if (!sp1D8 || temp_r31->unk1C.y + temp_f29 >= sp1D8->unk1C.y) {
                            sp1DC = 2;
                        }
                    }
                }
                if (sp1DC != 0) {
                    if (temp_r31->unk1 & 0x2) {
                        float temp_f28 = (temp_r31->unk1C.y + temp_f29) - ((!sp1D8) ? 0.0f : (1.0f + sp1D8->unk1C.y));
                        temp_f28 = temp_r31->unk1C.y - ((!sp1D8) ? 0.0f : (1.0f + sp1D8->unk1C.y));
                        if (temp_r31->unk50->unk48[0]->unk18 != temp_r31->unk50->unk48[1]->unk18) {
                            temp_r31->unk50->unk48[0]->unk1C.y = ((!sp1D8) ? 0.0f : (1.0f + sp1D8->unk1C.y));
                            temp_r31->unk50->unk48[1]->unk1C.y = ((!sp1D8) ? 0.0f : (1.0f + sp1D8->unk1C.y));
                        }
                        else {
                            temp_r31->unk50->unk48[0]->unk1C.y -= temp_f28;
                            temp_r31->unk50->unk48[1]->unk1C.y -= temp_f28;
                        }
                        temp_r31->unk50->unk48[0]->unk1C.z = 0;
                        temp_r31->unk50->unk48[1]->unk1C.z = 0;
                        if (sp1E0) {
                            if (!sp1D8 || ((sp1D8->unk1 & 0x1) && (sp1D8->unk1 & 0x2) == 0)) {
                                temp_r31->unk50->unk71 -= (temp_r31->unk50->unk71 != 0 && lbl_1_bss_18 == -1);
                            }
                        }
                        if (temp_r31->unk50->unk71 == 0
                            || temp_r31->unk50->unk4 != 0 && (!sp1D8 || ((sp1D8->unk1 & 0x1) && (sp1D8->unk1 & 0x2) == 0))) {
                            temp_r31->unk50->unk48[0]->unk1 &= ~0x2;
                            temp_r31->unk50->unk48[1]->unk1 &= ~0x2;
                            temp_r31->unk50->unk48[0]->unk1 |= 0x10;
                            temp_r31->unk50->unk48[1]->unk1 |= 0x10;
                            temp_r31->unk1 |= 0x1;
                            if (temp_r31->unk50->unk48[0]->unk18 != temp_r31->unk50->unk48[1]->unk18) {
                                s32 sp1D4;
                                s32 sp1D0 = (temp_r31 == temp_r31->unk50->unk48[1]) ? 1 : 0;
                                s32 sp1CC = temp_r31->unk50->unk48[sp1D0]->unk18;
                                s32 sp1C8 = temp_r31->unk50->unk48[1 - sp1D0]->unk18;
                                float sp1C4 = temp_r31->unk50->unk48[sp1D0]->unk1C.y;
                                float sp1C0 = temp_r31->unk50->unk48[1 - sp1D0]->unk1C.y;
                                sp1D4 = (sp1CC < sp1C8 || (sp1CC == sp1C8 && sp1C4 < sp1C0)) ? 1 : 0;
                                if (sp1D4 == 1) {
                                    StructBss2A6C *temp_r21 = temp_r31->unk50->unk48[1 - sp1D0];
                                    StructBss2A6C *temp_r20 = (temp_r21) ? temp_r21->unk4C : NULL;
                                    if (temp_r21) {
                                        if ((!temp_r20 && temp_r21->unk1C.y == 0.0f)
                                            || (temp_r20 && temp_r21->unk1C.y == temp_r20->unk1C.y + 1.0f && (temp_r20->unk1 & 0x1)
                                                && (temp_r20->unk1 & 0x2) == 0)) {
                                            temp_r21->unk1C.y = (temp_r20) ? (temp_r20->unk1C.y + 1.0f) : 0.0f;
                                            temp_r21->unk1 &= ~0x1;
                                            temp_r21->unk1 |= (temp_r20 && ((temp_r20->unk1 & 0x1) == 0 || (temp_r20->unk1 & 0x2) != 0)) ? 0 : 1;
                                            temp_r21->unk1C.z
                                                = (temp_r21->unk1 & 0x1) ? -0.010416667f : ((!temp_r20) ? -0.010416667f : temp_r20->unk1C.z);
                                            sp1E8 = temp_r21;
                                        }
                                    }
                                }
                            }
                            temp_r31->unk4 = temp_r31->unk5 = 0;
                            if (temp_r31->unk50->unk48[0]->unk18 == temp_r31->unk50->unk48[1]->unk18) {
                                s32 sp1BC = (temp_r31->unk50->unk48[1] == temp_r31) ? 1 : 0;
                                s32 sp1B8 = temp_r31->unk50->unk48[0]->unk1C.y > temp_r31->unk50->unk48[1]->unk1C.y;
                                temp_r31->unk50->unk48[1 - sp1B8]->unk1C.y = 1 + temp_r31->unk50->unk48[sp1B8]->unk1C.y;
                                temp_r31->unk50->unk48[1 - sp1B8]->unk1C.z = -0.010416667f;
                                temp_r31->unk50->unk48[0]->unk1 |= 0x1;
                                temp_r31->unk50->unk48[1]->unk1 |= 0x1;
                                temp_r31->unk50->unk48[0]->unk4 = temp_r31->unk50->unk48[0]->unk5 = 0;
                                temp_r31->unk50->unk48[1]->unk4 = temp_r31->unk50->unk48[1]->unk5 = 0;
                                temp_r31->unk38 = (temp_r31->unk50->unk48[1] == temp_r31) ? temp_r31->unk50->unk48[0] : temp_r31->unk50->unk48[1];
                                if (sp1BC) {
                                    temp_r31->unk50->unk48[0]->unk1 |= 0x8;
                                }
                                else {
                                    temp_r31->unk50->unk48[1]->unk1 |= 0x8;
                                }
                            }
                            temp_r31->unk50->unk48[0] = NULL;
                            temp_r31->unk50->unk48[1] = NULL;
                        }
                    }
                    else {
                        temp_r31->unk1C.y = (sp1D8) ? (1.0f + sp1D8->unk1C.y) : 0.0f;
                        temp_r31->unk1 &= ~0x1;
                        temp_r31->unk1 |= (sp1D8 && ((sp1D8->unk1 & 0x1) == 0 || (sp1D8->unk1 & 0x2) != 0)) ? 0 : 1;
                        temp_r31->unk1C.z = (temp_r31->unk1 & 0x1) ? -0.010416667f : ((!sp1D8) ? -0.010416667f : sp1D8->unk1C.z);
                    }
                }
                else {
                    temp_r31->unk1C.y += temp_f29;
                    temp_r31->unk1C.z = (sp1E0) ? ((temp_r31->unk1 & 0x3) ? 0.0f : -0.010416667f + temp_r31->unk1C.z) : temp_r31->unk1C.z;
                    if (temp_r31->unk1 & 0x1) {
                        temp_r31->unk1 &= ~0x1;
                    }
                }
            }
            if ((temp_r31->unk1 & 0x1) && (sp1E4 & 0x1) && (temp_r31->unk1 & 0x8) == 0 && temp_r31 != sp1E8) {
                temp_r31->unk8[0] = temp_r31->unk8[1] = temp_r31->unk8[2] = temp_r31->unk8[3] = 0;
                temp_r31->unk3 = 0;
                temp_r31->unk1 &= ~0x10;
            }
            temp_r31->unk1 &= ~0x8;
            if ((temp_r31->unk1 & 0x1) && (temp_r31->unk1 & 0x2) == 0) {
                sp2E48[temp_r31->unk18 + 1][(int)temp_r31->unk1C.y + 1] = temp_r31;
            }
            if (temp_r31->unk1 & 0x2) {
                temp_r31->unk1C.z = 0;
            }
        }
    }
    temp_r23 = 0;
    {
        s32 sp1B4;
        for (temp_r18 = 0; temp_r18 < 12; temp_r18++) {
            StructBss2A6C *sp1B0 = (temp_r18 < 11) ? lbl_1_bss_7884[temp_r18 + 1] : NULL;
            StructBss2A6C *sp1AC = NULL;
            StructBss2A6C *sp1A8 = NULL;
            float sp1A4 = (sp1B0) ? (sp1B0->unk1C.y) : 0.0f;
            for (temp_r31 = lbl_1_bss_7884[temp_r18]; temp_r31; temp_r31 = temp_r31->unk48) {
                s32 sp1A0 = temp_r31->unk18 + 1;
                s32 sp19C = (int)temp_r31->unk1C.y + 1;
                if ((temp_r31->unk1 & 0x1) && (temp_r31->unk1 & 0x2) == 0) {
                    if (sp2E48[sp1A0][sp19C + 1]) {
                        temp_r31->unk38 = sp2E48[sp1A0][sp19C + 1];
                        temp_r31->unk38->unk3C = temp_r31;
                    }
                    if (sp2E48[sp1A0 + 1][sp19C]) {
                        sp1B0 = sp2E48[sp1A0 + 1][sp19C];
                        temp_r31->unk44 = sp1B0;
                        temp_r31->unk44->unk40 = temp_r31;
                    }
                    sp1AC = sp2E48[sp1A0 + 1][sp19C + 1];
                    sp1A8 = sp2E48[sp1A0 + 1][sp19C - 1];
                    if (temp_r31->unk0 == 5 && temp_r31->unk2C == NULL && temp_r31->unk1C.y <= 8.0f && sp19C - 1 < 9) {
                        s32 sp198 = temp_r31->unk0 == 5;
                        sp14C8[temp_r23].unk0 = 5;
                        sp14C8[temp_r23].unk4[0] = (sp198) ? temp_r31->unk8[0] : temp_r30->unk8[0];
                        sp14C8[temp_r23].unk4[1] = (sp198) ? temp_r31->unk8[0] : temp_r30->unk8[1];
                        sp14C8[temp_r23].unk4[2] = (sp198) ? temp_r31->unk8[0] : temp_r30->unk8[2];
                        sp14C8[temp_r23].unk4[3] = (sp198) ? temp_r31->unk8[0] : temp_r30->unk8[3];
                        sp14C8[temp_r23].unk1 = 1;
                        sp14C8[temp_r23].unk2 = 0;
                        sp14C8[temp_r23].unk14 = (sp198) ? temp_r31 : temp_r30;
                        sp14C8[temp_r23].unk18 = (sp198) ? temp_r31 : temp_r30;
                        sp14C8[temp_r23].unk1C = 0;
                        if (sp198) {
                            temp_r31->unk30 = NULL;
                            temp_r31->unk34 = NULL;
                            temp_r31->unk2C = &sp14C8[temp_r23];
                        }
                        else {
                            temp_r30->unk30 = NULL;
                            temp_r30->unk34 = NULL;
                            temp_r30->unk2C = &sp14C8[temp_r23];
                        }
                        temp_r23++;
                    }
                    for (temp_r29 = 0; temp_r29 < ((temp_r31 && temp_r31->unk0 == 5) ? 2 : 0) + 2; temp_r29++) {
                        temp_r30 = (temp_r29 == 0) ? temp_r31->unk48 : ((temp_r29 == 1) ? sp1B0 : ((temp_r29 == 2) ? sp1AC : sp1A8));
                        if (temp_r30 && (temp_r30->unk1 & 0x1)) {
                            if (temp_r29 != 1 || temp_r31->unk1C.y == temp_r30->unk1C.y) {
                                if (temp_r31->unk0 == temp_r30->unk0) {
                                    if ((temp_r31->unk0 >= 1 && temp_r31->unk0 <= 4)
                                        || (temp_r31->unk0 == 5 && (temp_r31->unk1C.y <= 8.0f || temp_r30->unk1C.y <= 8.0f))) {
                                        StructSp14C8 *temp_r28 = temp_r31->unk2C;
                                        StructSp14C8 *temp_r27 = temp_r30->unk2C;
                                        if (temp_r31->unk2C && temp_r30->unk2C) {
                                            if (temp_r31->unk2C != temp_r30->unk2C) {
                                                StructBss2A6C *sp194 = temp_r28->unk14;
                                                StructBss2A6C *sp190 = temp_r27->unk14;
                                                while (1) {
                                                    sp190->unk2C = temp_r28;
                                                    if (!sp190->unk34) {
                                                        break;
                                                    }
                                                    sp190 = sp190->unk34;
                                                }
                                                temp_r27->unk14->unk30 = temp_r28->unk18;
                                                temp_r28->unk18->unk34 = temp_r27->unk14;
                                                temp_r28->unk4[0] = (temp_r28->unk4[0] > temp_r27->unk4[0]) ? temp_r28->unk4[0] : temp_r27->unk4[0];
                                                temp_r28->unk4[1] = (temp_r28->unk4[1] > temp_r27->unk4[1]) ? temp_r28->unk4[1] : temp_r27->unk4[1];
                                                temp_r28->unk4[2] = (temp_r28->unk4[2] > temp_r27->unk4[2]) ? temp_r28->unk4[2] : temp_r27->unk4[2];
                                                temp_r28->unk4[3] = (temp_r28->unk4[3] > temp_r27->unk4[3]) ? temp_r28->unk4[3] : temp_r27->unk4[3];
                                                temp_r28->unk1 = temp_r28->unk1 + temp_r27->unk1;
                                                temp_r28->unk2 |= temp_r27->unk2;
                                                temp_r28->unk18 = sp190;
                                                temp_r27->unk14 = temp_r27->unk18 = NULL;
                                                temp_r27->unk1 = 0;
                                                temp_r27->unk0 = 0;
                                                temp_r27->unk1C = temp_r28;
                                            }
                                        }
                                        else {
                                            if (temp_r31->unk2C) {
                                                temp_r30->unk2C = temp_r31->unk2C;
                                                temp_r28->unk18->unk34 = temp_r30;
                                                temp_r30->unk30 = temp_r28->unk18;
                                                temp_r28->unk18 = temp_r30;
                                                temp_r28->unk1++;
                                                temp_r28->unk2 |= temp_r30->unk3;
                                                temp_r28->unk4[0] = (temp_r28->unk4[0] < temp_r30->unk8[0]) ? temp_r30->unk8[0] : temp_r28->unk4[0];
                                                temp_r28->unk4[1] = (temp_r28->unk4[1] < temp_r30->unk8[1]) ? temp_r30->unk8[1] : temp_r28->unk4[1];
                                                temp_r28->unk4[2] = (temp_r28->unk4[2] < temp_r30->unk8[2]) ? temp_r30->unk8[2] : temp_r28->unk4[2];
                                                temp_r28->unk4[3] = (temp_r28->unk4[3] < temp_r30->unk8[3]) ? temp_r30->unk8[3] : temp_r28->unk4[3];
                                            }
                                            else if (temp_r30->unk2C) {
                                                temp_r31->unk2C = temp_r30->unk2C;
                                                temp_r27->unk18->unk34 = temp_r31;
                                                temp_r31->unk30 = temp_r27->unk18;
                                                temp_r27->unk18 = temp_r31;
                                                temp_r27->unk1++;
                                                temp_r27->unk2 |= temp_r31->unk3;
                                                temp_r27->unk4[0] = (temp_r27->unk4[0] < temp_r31->unk8[0]) ? temp_r31->unk8[0] : temp_r27->unk4[0];
                                                temp_r27->unk4[1] = (temp_r27->unk4[1] < temp_r31->unk8[1]) ? temp_r31->unk8[1] : temp_r27->unk4[1];
                                                temp_r27->unk4[2] = (temp_r27->unk4[2] < temp_r31->unk8[2]) ? temp_r31->unk8[2] : temp_r27->unk4[2];
                                                temp_r27->unk4[3] = (temp_r27->unk4[3] < temp_r31->unk8[3]) ? temp_r31->unk8[3] : temp_r27->unk4[3];
                                            }
                                            else {
                                                sp14C8[temp_r23].unk0 = temp_r31->unk0;
                                                sp14C8[temp_r23].unk4[0]
                                                    = (temp_r31->unk8[0] > temp_r30->unk8[0]) ? temp_r31->unk8[0] : temp_r30->unk8[0];
                                                sp14C8[temp_r23].unk4[1]
                                                    = (temp_r31->unk8[1] > temp_r30->unk8[1]) ? temp_r31->unk8[1] : temp_r30->unk8[1];
                                                sp14C8[temp_r23].unk4[2]
                                                    = (temp_r31->unk8[2] > temp_r30->unk8[2]) ? temp_r31->unk8[2] : temp_r30->unk8[2];
                                                sp14C8[temp_r23].unk4[3]
                                                    = (temp_r31->unk8[3] > temp_r30->unk8[3]) ? temp_r31->unk8[3] : temp_r30->unk8[3];
                                                sp14C8[temp_r23].unk1 = 2;
                                                sp14C8[temp_r23].unk2 = (temp_r31->unk3 | temp_r30->unk3);
                                                sp14C8[temp_r23].unk14 = temp_r31;
                                                sp14C8[temp_r23].unk18 = temp_r30;
                                                sp14C8[temp_r23].unk1C = NULL;
                                                temp_r31->unk30 = NULL;
                                                temp_r31->unk34 = temp_r30;
                                                temp_r30->unk30 = temp_r31;
                                                temp_r30->unk34 = NULL;
                                                temp_r31->unk2C = &sp14C8[temp_r23];
                                                temp_r30->unk2C = &sp14C8[temp_r23];
                                                temp_r23++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for (temp_r29 = 0; temp_r29 < temp_r23; temp_r29++) {
            StructBss2A6C *sp18C;
            if (sp14C8[temp_r29].unk0 != 5) {
                continue;
            }
            sp18C = sp14C8[temp_r29].unk14;
            for (temp_r19 = 0; temp_r19 < sp14C8[temp_r29].unk1; temp_r19++) {
                s32 temp_r24 = sp18C->unk18 + 1;
                s32 temp_r25 = (int)sp18C->unk1C.y + 1;
                if (sp14C8[temp_r29].unk0 != 0 && temp_r25 <= 9) {
                    if (!CHECK_2E48(temp_r24, temp_r25, sp2E48)) {
                        sp14C8[temp_r29].unk0 = 0;
                    }
                    else {
                        sp14C8[temp_r29].unk2 |= ((sp2E48[temp_r24 - 1][temp_r25]) ? sp2E48[temp_r24 - 1][temp_r25]->unk3 : 0)
                            | ((sp2E48[temp_r24 + 1][temp_r25]) ? sp2E48[temp_r24 + 1][temp_r25]->unk3 : 0)
                            | ((sp2E48[temp_r24][temp_r25 - 1]) ? sp2E48[temp_r24][temp_r25 - 1]->unk3 : 0)
                            | ((sp2E48[temp_r24][temp_r25 + 1]) ? sp2E48[temp_r24][temp_r25 + 1]->unk3 : 0)
                            | ((sp2E48[temp_r24 + 1][temp_r25 - 1]) ? sp2E48[temp_r24 + 1][temp_r25 - 1]->unk3 : 0)
                            | ((sp2E48[temp_r24 + 1][temp_r25 + 1]) ? sp2E48[temp_r24 + 1][temp_r25 + 1]->unk3 : 0)
                            | ((sp2E48[temp_r24 - 1][temp_r25 - 1]) ? sp2E48[temp_r24 - 1][temp_r25 - 1]->unk3 : 0)
                            | ((sp2E48[temp_r24 - 1][temp_r25 + 1]) ? sp2E48[temp_r24 - 1][temp_r25 + 1]->unk3 : 0);
                    }
                    sp18C = sp18C->unk34;
                    if (!sp18C) {
                        break;
                    }
                }
            }
        }
        for (temp_r29 = 0; temp_r29 < temp_r23; temp_r29++) {
            if ((sp14C8[temp_r29].unk0 >= 1 && sp14C8[temp_r29].unk0 <= 4 && sp14C8[temp_r29].unk1 >= 3) || sp14C8[temp_r29].unk0 == 5) {
                fn_1_38C(&sp14C8[temp_r29].unk2, sp14C8[temp_r29].unk4);
            }
        }
        sp1B4 = 1;
        while (sp1B4 >= 0) {
            s32 temp_r22 = 0;
            s32 sp188 = 0;
            for (temp_r29 = 0; temp_r29 < temp_r23; temp_r29++) {
                if ((!sp1B4 && (sp14C8[temp_r29].unk0 >= 1 && sp14C8[temp_r29].unk0 <= 4 && sp14C8[temp_r29].unk1 >= 3))
                    || (sp1B4 == 1 && sp14C8[temp_r29].unk0 == 5)) {
                    StructBss2A6C *temp_r26 = sp14C8[temp_r29].unk14;
                    s32 sp184 = 0;
                    s32 sp180 = 0;
                    float temp_f31 = -1;
                    float temp_f30 = -1;
                    if (sp14C8[temp_r29].unk0 == 5) {
                        lbl_1_bss_D0++;
                        lbl_1_bss_D0 %= 5;
                        lbl_1_bss_D4[lbl_1_bss_D0][1] = 1;
                        lbl_1_bss_D4[lbl_1_bss_D0][0] = 0;
                        for (temp_r19 = 0; temp_r19 < 10; temp_r19++) {
                            Hu3DModelAttrSet(lbl_1_bss_30->model[((lbl_1_bss_D0 * 10) + 13 + temp_r19)], HU3D_ATTR_DISPOFF);
                        }
                    }
                    for (temp_r19 = 0; temp_r19 < sp14C8[temp_r29].unk1; temp_r19++) {
                        if (-1.0f == temp_f31) {
                            sp180 = 1;
                            temp_f31 = temp_r26->unk18;
                            temp_f30 = temp_r26->unk1C.y;
                        }
                        else {
                            sp180++;
                            temp_f31 = (temp_f31 * (1.0 - (1.0 / sp180))) + (temp_r26->unk18 * (1.0 / sp180));
                            temp_f30 = (temp_f30 * (1.0 - (1.0 / sp180))) + (temp_r26->unk1C.y * (1.0 / sp180));
                        }
                        if (sp14C8[temp_r29].unk0 == 5) {
                            if (lbl_1_bss_D4[lbl_1_bss_D0][0] < 10) {
                                Hu3DModelPosSet(lbl_1_bss_30->model[((lbl_1_bss_D0 * 10) + 13 + lbl_1_bss_D4[lbl_1_bss_D0][0])],
                                    (((temp_r26->unk18 * 100) - 500.0) - 50.0), 50.0f + ((100.0f * temp_r26->unk1C.y) - 500.0f), 120);
                                Hu3DModelAttrReset(
                                    lbl_1_bss_30->model[((lbl_1_bss_D0 * 10) + 13 + lbl_1_bss_D4[lbl_1_bss_D0][0])], HU3D_ATTR_DISPOFF);
                                Hu3DMotionTimeSet(lbl_1_bss_30->model[((lbl_1_bss_D0 * 10) + 13 + lbl_1_bss_D4[lbl_1_bss_D0][0])], 2.0f);
                                lbl_1_bss_D4[lbl_1_bss_D0][0]++;
                                lbl_1_bss_B8.unk4 += 4;
                                if (lbl_1_bss_D4[lbl_1_bss_D0][0] == 1) {
                                    lbl_1_bss_B8.unk4 += 7;
                                }
                            }
                            fn_1_8AC8(temp_r26->unk38, &sp14C8[temp_r29]);
                            fn_1_8AC8((temp_r26->unk44 && temp_r26->unk44->unk38) ? temp_r26->unk44->unk38 : temp_r26->unk44, &sp14C8[temp_r29]);
                            fn_1_8AC8((temp_r26->unk40 && temp_r26->unk40->unk38) ? temp_r26->unk40->unk38 : temp_r26->unk40, &sp14C8[temp_r29]);
                            spD58[temp_r22] = temp_r26->unk38;
                            temp_r22++;
                            spD58[temp_r22] = temp_r26->unk3C;
                            temp_r22++;
                            if (temp_r26->unk44) {
                                spD58[temp_r22] = temp_r26->unk44->unk38;
                                temp_r22++;
                                spD58[temp_r22] = temp_r26->unk44->unk3C;
                                temp_r22++;
                            }
                            spD58[temp_r22] = temp_r26->unk44;
                            temp_r22++;
                            if (temp_r26->unk40) {
                                spD58[temp_r22] = temp_r26->unk40->unk38;
                                temp_r22++;
                                spD58[temp_r22] = temp_r26->unk40->unk3C;
                                temp_r22++;
                            }
                            spD58[temp_r22] = temp_r26->unk40;
                            temp_r22++;
                            spD58[temp_r22] = temp_r26;
                            temp_r22++;
                        }
                        else {
                            fn_1_8AC8(temp_r26, &sp14C8[temp_r29]);
                            sp184 += fn_1_7F8(temp_r26, &sp14C8[temp_r29]);
                        }
                        temp_r26 = temp_r26->unk34;
                        if (!temp_r26) {
                            break;
                        }
                    }
                    if (sp14C8[temp_r29].unk0 == 5 && (sp14C8[temp_r29].unk2 & 0xF)) {
                        Work19C8 *sp220[4];
                        s32 sp17C;
                        for (sp17C = 0; sp17C < 4; sp17C++) {
                            if ((1 << sp17C) & (sp14C8[temp_r29].unk2)) {
                                sp220[sp17C] = lbl_1_bss_34[sp17C]->data;
                                omVibrate(sp220[sp17C]->unk14, 12, 6, 6);
                            }
                        }
                    }
                    if (lbl_1_bss_48[(sp14C8[temp_r29].unk0 == 5) ? 0 : 1].unk0 < 3) {
                        lbl_1_bss_48[(sp14C8[temp_r29].unk0 == 5) ? 0 : 1].unk4[lbl_1_bss_48[(sp14C8[temp_r29].unk0 == 5) ? 0 : 1].unk0]
                            = 0.45 * (((temp_f31 - 5.0) - 0.5) / 5.5);
                        lbl_1_bss_48[(sp14C8[temp_r29].unk0 == 5) ? 0 : 1].unk0++;
                    }
                    if (sp1B4 == 0 && sp184 > 0 && lbl_1_bss_18 == -1) {
                        s32 sp178 = 0;
                        s32 sp174 = fn_1_4C0(&sp14C8[temp_r29].unk2, sp14C8[temp_r29].unk4);
                        Vec sp214 = { 0, 0, 50 };
                        s32 temp_r17;
                        for (temp_r17 = 0; temp_r17 < 4; temp_r17++) {
                            sp178 += ((1 << temp_r17) != 0) & sp14C8[temp_r29].unk2;
                        }
                        sp178--;
                        sp214.x = (100.0f * temp_f31) - 500.0;
                        sp214.y = 100 + ((100 * temp_f30) - 500);
                        sp214.x += sp178 * 12;
                        sp214.y -= sp178 * 30;
                        for (temp_r17 = 3; temp_r17 >= 0; temp_r17--) {
                            if ((1 << temp_r17) & sp14C8[temp_r29].unk2) {
                                Vec sp208;
                                lbl_1_bss_2684[lbl_1_bss_2680].unkC = 1;
                                lbl_1_bss_2684[lbl_1_bss_2680].unk8 = sp184;
                                lbl_1_bss_2684[lbl_1_bss_2680].unk10 = 1 << temp_r17;
                                Hu3D3Dto2D(&sp214, 1, &sp208);
                                lbl_1_bss_2684[lbl_1_bss_2680].unk0 = sp208.x;
                                lbl_1_bss_2684[lbl_1_bss_2680].unk4 = sp208.y;
                                lbl_1_bss_2680++;
                                lbl_1_bss_2680 %= 50;
                                sp214.x -= 24.0f;
                                sp214.y += 60.0f;
                            }
                        }
                        sp174 = (sp174 > 3) ? 3 : sp174;
                        if (lbl_1_bss_48[sp174 + 3].unk0 < 3) {
                            lbl_1_bss_48[sp174 + 3].unk4[lbl_1_bss_48[sp174 + 3].unk0] = 0.45 * (((temp_f31 - 5.0) - 0.5) / 5.5);
                            lbl_1_bss_48[sp174 + 3].unk0++;
                        }
                    }
                    spA28[sp188] = &sp14C8[temp_r29];
                    sp230[sp188] = temp_r22;
                    sp6F8[sp188] = temp_f31;
                    sp3C8[sp188] = temp_f30;
                    sp188++;
                }
            }
            for (temp_r29 = 0; temp_r29 < sp188; temp_r29++) {
                s32 sp170 = 0;

                for (temp_r19 = (temp_r29 < 1) ? 0 : sp230[temp_r29 - 1]; temp_r19 < sp230[temp_r29]; temp_r19++) {
                    sp170 += fn_1_7F8(spD58[temp_r19], spA28[temp_r29]);
                }
                if (sp1B4 == 1 && sp170 > 0 && lbl_1_bss_18 == -1) {
                    s32 sp16C;
                    s32 sp168 = 0;
                    s32 sp164 = fn_1_4C0(&spA28[temp_r29]->unk2, spA28[temp_r29]->unk4);
                    Vec sp1FC = { 0, 0, 50 };
                    for (sp16C = 0; sp16C < 4; sp16C++) {
                        sp168 += ((1 << sp16C) != 0) & spA28[temp_r29]->unk2;
                    }
                    sp168--;
                    sp1FC.x = (100.0f * sp6F8[temp_r29]) - 500.0;
                    sp1FC.y = 100 + ((100 * sp3C8[temp_r29]) - 500);
                    sp1FC.x += sp168 * 12;
                    sp1FC.y -= sp168 * 30;
                    for (sp16C = 3; sp16C >= 0; sp16C--) {
                        if ((1 << sp16C) & spA28[temp_r29]->unk2) {
                            Vec sp1F0;
                            lbl_1_bss_2684[lbl_1_bss_2680].unkC = 1;
                            lbl_1_bss_2684[lbl_1_bss_2680].unk8 = sp170;
                            lbl_1_bss_2684[lbl_1_bss_2680].unk10 = 1 << sp16C;
                            Hu3D3Dto2D(&sp1FC, 1, &sp1F0);
                            lbl_1_bss_2684[lbl_1_bss_2680].unk0 = sp1F0.x;
                            lbl_1_bss_2684[lbl_1_bss_2680].unk4 = sp1F0.y;
                            lbl_1_bss_2680++;
                            lbl_1_bss_2680 %= 50;
                            sp1FC.x -= 24.0f;
                            sp1FC.y += 60.0f;
                        }
                    }
                    sp164 = (sp164 > 3) ? 3 : sp164;
                    if (lbl_1_bss_48[sp164 + 3].unk0 < 3) {
                        lbl_1_bss_48[sp164 + 3].unk4[lbl_1_bss_48[sp164 + 3].unk0] = 0.45 * (((sp6F8[temp_r29] - 5.0) - 0.5) / 5.5);
                        lbl_1_bss_48[sp164 + 3].unk0++;
                    }
                }
            }
            sp1B4--;
        }
    }
}
#undef CHECK_2E48

void fn_1_8AC8(StructBss2A6C *arg0, StructSp14C8 *arg1)
{
    StructBss2A6C *temp_r31 = arg0;
    if (!arg0) {
        return;
    }
    if (arg0->unk0 == 0) {
        return;
    }
    while (temp_r31->unk48) {
        if (!temp_r31->unk48->unk0 || (temp_r31->unk48->unk1 & 0x1) == 0 || temp_r31->unk48->unk1C.y != temp_r31->unk1C.y + 1.0f) {
            break;
        }
        temp_r31 = temp_r31->unk48;
        temp_r31->unk8[0] = arg1->unk4[0] + ((arg1->unk2 & 0x1) ? 1 : 0);
        temp_r31->unk8[1] = arg1->unk4[1] + ((arg1->unk2 & 0x2) ? 1 : 0);
        temp_r31->unk8[2] = arg1->unk4[2] + ((arg1->unk2 & 0x4) ? 1 : 0);
        temp_r31->unk8[3] = arg1->unk4[3] + ((arg1->unk2 & 0x8) ? 1 : 0);
        temp_r31->unk3 = arg1->unk2;
    }
}

void fn_1_8C10(omObjData *object)
{
    s32 temp_r31;
    s32 temp_r30;

    Work19C8 *sp88[4];
    lbl_1_bss_4++;
    {
        s32 temp_r23;
        for (temp_r23 = 0; temp_r23 < 4; temp_r23++) {
            fn_1_19C8(lbl_1_bss_34[temp_r23]);
            fn_1_52A4(temp_r23);
        }
    }

    fn_1_52A4(4);
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        sp88[temp_r31] = lbl_1_bss_34[temp_r31]->data;
    }
    if (lbl_1_bss_18 == -1) {
        if (sp88[0]->unk24 >= 100 || sp88[1]->unk24 >= 100 || sp88[2]->unk24 >= 100 || sp88[3]->unk24 >= 100) {
            s32 sp78[4] = { 0, 1, 2, 3 };
            for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                s32 temp_r22 = rand8() % 4;
                if (sp88[temp_r22]->unk24 >= 100) {
                    lbl_1_bss_18 = temp_r22;
                    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
                        if (temp_r30 != temp_r22) {
                            if (sp88[temp_r30]->unk24 >= 100) {
                                sp88[temp_r30]->unk24 = sp88[temp_r30]->unk28;
                            }
                        }
                    }
                }
                else {
                    for (temp_r30 = temp_r22; temp_r30 < 3 - temp_r31; temp_r30++) {
                        sp78[temp_r30] = sp78[temp_r30 + 1];
                    }
                }
            }
        }
    }
    temp_r31 = (sp88[0]->unk79 != 0) + (sp88[1]->unk79 != 0) + (sp88[2]->unk79 != 0) + (sp88[3]->unk79 != 0);
    if (lbl_1_bss_18 == -1 && temp_r31 == 3) {
        for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
            if (!sp88[temp_r30]->unk78) {
                lbl_1_bss_18 = temp_r30;
            }
        }
    }
    if (lbl_1_bss_18 == -1 && temp_r31 == 4) {
        lbl_1_bss_18 = 4;
    }
    if (lbl_1_bss_18 != -1) {
        for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
            if (sp88[temp_r31]->unk48[0]) {
                sp88[temp_r31]->unk48[0]->unk1 &= ~0x2;
            }
            if (sp88[temp_r31]->unk48[1]) {
                sp88[temp_r31]->unk48[1]->unk1 &= ~0x2;
            }
            sp88[temp_r31]->unk48[0] = NULL;
            sp88[temp_r31]->unk48[1] = NULL;
        }
    }
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        sp88[temp_r31]->unk44 = (sp88[temp_r31]->unk40 == sp88[temp_r31]->unk24) ? sp88[temp_r31]->unk44 + 1 : 0;
        sp88[temp_r31]->unk40 += (sp88[temp_r31]->unk40 < sp88[temp_r31]->unk24) ? 0.375 : 0;
        sp88[temp_r31]->unk40 = (sp88[temp_r31]->unk40 > sp88[temp_r31]->unk24) ? (float)sp88[temp_r31]->unk24 : sp88[temp_r31]->unk40;
        for (temp_r30 = 0; temp_r30 < 3; temp_r30++) {
            float temp_f28 = sp88[temp_r31]->unk40;
            float sp4C = (s32)(temp_f28 / 100.0f) % 10;
            float temp_f22 = (s32)(temp_f28 / 10.0f) % 10;
            float temp_f24 = ((s32)temp_f28) % 10;
            float temp_f23 = temp_f28 - (s32)temp_f28;
            float temp_f25 = (temp_r30 == 0) ? ((sp88[temp_r31]->unk24 / 100) % 10)
                                             : ((temp_r30 == 1) ? ((sp88[temp_r31]->unk24 / 10) % 10) : sp88[temp_r31]->unk24 % 10);
            s32 sp98[5] = { 0, 15, -9, 3, 0 };
            switch (temp_r30) {
                case 0:
                    temp_f25 = sp4C + (temp_f23 * ((9.0f == temp_f24 && 9.0f == temp_f22) ? 1.0 : 0.0));
                    break;

                case 1:
                    temp_f25 = temp_f22 + (temp_f23 * ((9.0f == temp_f24) ? 1.0 : 0.0));
                    break;

                case 2:
                    temp_f25 = temp_f24 + temp_f23;
                    break;
            }
            Hu3DModelRotSet(lbl_1_bss_34[temp_r31]->model[temp_r30 + 1], 36.0f * temp_f25, 0, 0);
        }
    }
    {
        s32 spAC[8][3] = { 255, 64, 64, 32, 192, 255, 255, 128, 255, 32, 208, 32, 224, 32, 224, 230, 128, 32, 255, 240, 32, 160, 160, 160 };
        s32 temp_r29 = lbl_1_bss_2680;
        s32 temp_r28 = 0;
        Work19C8 *sp68[4];
        for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {
            sp68[temp_r28] = lbl_1_bss_34[temp_r28]->data;
        }
        do {
            temp_r29--;
            temp_r29 = (temp_r29 < 0) ? temp_r29 + 50 : temp_r29;
            if (lbl_1_bss_2684[temp_r29].unkC == 0 || (lbl_1_bss_2684[temp_r29].unk10 & 0xF) == 0) {
                HuSprAttrSet(lbl_1_bss_14, temp_r28, HUSPR_ATTR_DISPOFF);
            }
            else {
                s32 temp_r26 = 0;
                u32 temp_r19;
                s32 temp_r18;

                s32 temp_r24;

                s32 sp58[4];
                temp_r18 = ((lbl_1_bss_2684[temp_r29].unk8 >= 10) ? 2 : 1) + 1;
                if (lbl_1_bss_2684[temp_r29].unk10 & 0x1) {
                    sp58[temp_r26] = 0;
                    temp_r26++;
                }
                if (lbl_1_bss_2684[temp_r29].unk10 & 0x2) {
                    sp58[temp_r26] = 1;
                    temp_r26++;
                }
                if (lbl_1_bss_2684[temp_r29].unk10 & 0x4) {
                    sp58[temp_r26] = 2;
                    temp_r26++;
                }
                if (lbl_1_bss_2684[temp_r29].unk10 & 0x8) {
                    sp58[temp_r26] = 3;
                    temp_r26++;
                }
                temp_r19 = sp68[sp58[lbl_1_bss_4 % temp_r26]]->unk18;
                for (temp_r24 = 0; temp_r24 < temp_r18; temp_r28++, temp_r24++) {
                    HuSprPosSet(lbl_1_bss_14, temp_r28, (temp_r24 * 14) + (lbl_1_bss_2684[temp_r29].unk0 - ((temp_r18 * 14) / 2)),
                        lbl_1_bss_2684[temp_r29].unk4 - lbl_1_bss_2684[temp_r29].unkC);
                    HuSprAttrReset(lbl_1_bss_14, temp_r28, HUSPR_ATTR_DISPOFF);
                    HuSprColorSet(lbl_1_bss_14, temp_r28, spAC[temp_r19][0], spAC[temp_r19][1], spAC[temp_r19][2]);
                    HuSprTPLvlSet(lbl_1_bss_14, temp_r28,
                        (lbl_1_bss_2684[temp_r29].unkC <= 30) ? 1.0f : (1.0f - ((lbl_1_bss_2684[temp_r29].unkC - 30) / 10.0f)));
                    HuSprBankSet(lbl_1_bss_14, temp_r28,
                        (temp_r24 == 0)
                            ? 10
                            : ((temp_r24 == 2 || temp_r18 == 2) ? lbl_1_bss_2684[temp_r29].unk8 % 10 : ((lbl_1_bss_2684[temp_r29].unk8 / 10) % 10)));
                }
            }
            lbl_1_bss_2684[temp_r29].unkC += lbl_1_bss_2684[temp_r29].unkC > 0;
            if (lbl_1_bss_2684[temp_r29].unkC >= 40) {
                lbl_1_bss_2684[temp_r29].unkC = 0;
            }

        } while (temp_r29 != lbl_1_bss_2680);
        for (; temp_r28 < 150; temp_r28++) {
            HuSprAttrSet(lbl_1_bss_14, temp_r28, HUSPR_ATTR_DISPOFF);
        }
    }
    {
        s32 temp_r27 = lbl_1_bss_FC;
        s32 temp_r25;
        s32 temp_r17;
        for (temp_r17 = 0; temp_r17 < 300; temp_r17++) {
            temp_r27 = temp_r27 + 1;
            temp_r27 %= 300;
            if (!lbl_1_bss_100[temp_r27].unk0) {
                continue;
            }
            lbl_1_bss_100[temp_r27].unk4.x += lbl_1_bss_100[temp_r27].unk10.x;
            lbl_1_bss_100[temp_r27].unk4.y += lbl_1_bss_100[temp_r27].unk10.y;
            lbl_1_bss_100[temp_r27].unk4.z += lbl_1_bss_100[temp_r27].unk10.z;
            lbl_1_bss_100[temp_r27].unk10.y += -1.5;
            if (lbl_1_bss_100[temp_r27].unk4.y < -1000.0f) {
                lbl_1_bss_100[temp_r27].unk0 = 0;
            }
            lbl_1_bss_100[temp_r27].unk1C += 9;
        }
        for (temp_r25 = 0; temp_r25 < 5; temp_r25++) {
            if (lbl_1_bss_D4[temp_r25][0] > 0) {
                lbl_1_bss_D4[temp_r25][1]++;
                if (lbl_1_bss_D4[temp_r25][1] > 30) {
                    s32 temp_r21;
                    lbl_1_bss_D4[temp_r25][0] = 0;
                    lbl_1_bss_D4[temp_r25][1] = 0;
                    for (temp_r21 = 0; temp_r21 < 10; temp_r21++) {
                        Hu3DModelAttrSet(object->model[(temp_r25 * 10) + 13 + temp_r21], HU3D_ATTR_DISPOFF);
                    }
                }
            }
        }
        if (lbl_1_bss_44->work[0] >= 1002) {
            float temp_f27 = 0;
            float temp_f26 = 0;
            if (lbl_1_bss_B8.unk0 % 2 >= 0) {
                lbl_1_bss_B8.unk8 = lbl_1_bss_B8.unkC.y;
                lbl_1_bss_B8.unkC.x = lbl_1_bss_B8.unkC.z;
                do {
                    lbl_1_bss_B8.unkC.y = (2.0 * (rand8() / 255.0)) - 1.0;
                    lbl_1_bss_B8.unkC.z = (2.0 * (rand8() / 255.0)) - 1.0;
                    lbl_1_bss_B8.unkC.y = 0;
                } while (VECMagPoint(lbl_1_bss_B8.unkC.y - lbl_1_bss_B8.unk8, lbl_1_bss_B8.unkC.z - lbl_1_bss_B8.unkC.x, 0) < 0.75);
            }
            temp_f27 = lbl_1_bss_B8.unk8;
            temp_f26 = lbl_1_bss_B8.unkC.x;
            temp_f27 *= lbl_1_bss_B8.unk4 * 2;
            temp_f26 *= lbl_1_bss_B8.unk4 * 2;
            lbl_1_bss_B8.unk0 = !lbl_1_bss_B8.unk0;
            lbl_1_bss_B8.unk4 = (lbl_1_bss_B8.unk4 > 24) ? 23 : ((lbl_1_bss_B8.unk4 - 1 > 0) ? lbl_1_bss_B8.unk4 - 1 : 0);
            Hu3DCameraPosSet(1, temp_f27, 37.139069 + temp_f26, 2599.7346f, 0, 1, 0, temp_f27, 50.0f + temp_f26, 0);
        }
        if (lbl_1_bss_18 != -1) {
            float temp_f30;
            s32 temp_r20;
            lbl_1_bss_10++;
            temp_f30 = 1.0f - ((lbl_1_bss_10 > 180) ? 1.0f : (lbl_1_bss_10 / 180.0f));
            Hu3DMotionSpeedSet(lbl_1_bss_30->model[0], 0.5 * temp_f30);
            for (temp_r20 = 0; temp_r20 < 4; temp_r20++) {
                Hu3DMotionSpeedSet(lbl_1_bss_34[temp_r20]->model[5], 0.5 * temp_f30);
            }
            if (temp_f30 > 0.0f && lbl_1_data_4[0] != -1) {
                HuAudFXPitchSet(lbl_1_data_4[0], -8192.0f + (8192.0f * temp_f30));
                HuAudFXPitchSet(lbl_1_data_4[1], -8192.0f + (8192.0f * temp_f30));
                HuAudFXVolSet(lbl_1_data_4[0], 63.0f + (64.0f * temp_f30));
                HuAudFXVolSet(lbl_1_data_4[1], 63.0f + (64.0f * temp_f30));
            }
            else {
                if (lbl_1_data_4[0] != -1) {
                    HuAudFXStop(lbl_1_data_4[0]);
                    HuAudFXStop(lbl_1_data_4[1]);
                    lbl_1_data_4[0] = lbl_1_data_4[1] = -1;
                }
            }
        }
    }
}

void fn_1_D700(omObjData *object);

void fn_1_A53C(omObjData *object)
{
    Work19C8 *sp28[4];
    s32 temp_r31;
    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
        sp28[temp_r31] = lbl_1_bss_34[temp_r31]->data;
    }
    for (temp_r31 = 0; temp_r31 < 7; temp_r31++) {
        s32 sp38[7] = { 1422, 1423, 1424, 1425, 1426, 1427, 1428 };
        if (lbl_1_bss_48[temp_r31].unk0 > 3) {
            lbl_1_bss_48[temp_r31].unk0 = 3;
        }
        if (lbl_1_bss_48[temp_r31].unk0 > 0) {
            s32 temp_r19 = HuAudFXPlay(sp38[temp_r31]);
            HuAudFXPanning(temp_r19, 0.5 + ((63 * lbl_1_bss_48[temp_r31].unk4[lbl_1_bss_48[temp_r31].unk0 - 1]) + 64));
            lbl_1_bss_48[temp_r31].unk0--;
        }
    }
    if (omSysExitReq && !WipeStatGet()) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = fn_1_D700;
    }
    switch (object->work[0]) {
        case 1000:
            if (!WipeStatGet()) {
                s32 temp_r29;
                s32 temp_r28;
                s32 temp_r27;
                s32 temp_r26;
                lbl_1_bss_2C++;
                if (lbl_1_bss_2C == 10.0f) {
                    lbl_1_bss_2C = 50.0f;
                }
                temp_r29 = (lbl_1_bss_2C > 180.0f) ? 255.0 : ((lbl_1_bss_2C > 120.0f) ? (255.0 * ((lbl_1_bss_2C - 120.0f) / 60.0)) : 0.0);
                temp_r29 = (lbl_1_bss_2C >= 235.0f)
                    ? 255
                    : ((lbl_1_bss_2C >= 205.0f) ? 192 : ((lbl_1_bss_2C >= 190.0f) ? 128 : (((lbl_1_bss_2C >= 160.0f) ? 64 : 0))));
                Hu3DGLightColorSet(lbl_1_bss_1C, temp_r29, temp_r29, temp_r29, 255);
                for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {

                    Hu3DMotionTimeSet(lbl_1_bss_34[temp_r28]->model[0], 60.0 + (40.0 * (temp_r29 / 255.0)));
                    for (temp_r27 = 0; temp_r27 < 3; temp_r27++) {
                        Hu3DMotionTimeSet(lbl_1_bss_34[temp_r28]->model[temp_r27 + 1], 60.0 + (40.0 * (temp_r29 / 255.0)));
                    }
                    Hu3DMotionTimeSet(lbl_1_bss_34[temp_r28]->model[4], 60.0 + (40.0 * (temp_r29 / 255.0)));
                }
                Hu3DMotionSpeedSet(
                    lbl_1_bss_30->model[0], 0.5 * ((lbl_1_bss_2C < 100.0f) ? 0.0 : ((lbl_1_bss_2C < 320.0f) ? ((lbl_1_bss_2C - 100) / 220.0) : 1.0)));
                for (temp_r26 = 0; temp_r26 < 4; temp_r26++) {
                    Hu3DMotionSpeedSet(lbl_1_bss_34[temp_r26]->model[5],
                        0.5 * ((lbl_1_bss_2C < 100.0f) ? 0.0 : ((lbl_1_bss_2C < 280.0f) ? ((lbl_1_bss_2C - 100) / 180.0) : 1.0)));
                }
                if (100.0f == lbl_1_bss_2C) {
                    Hu3DMotionSpeedSet(lbl_1_bss_30->model[1], 1.0f);
                    omVibrate(sp28[0]->unk14, 12, 4, 2);
                    omVibrate(sp28[1]->unk14, 12, 4, 2);
                    omVibrate(sp28[2]->unk14, 12, 4, 2);
                    omVibrate(sp28[3]->unk14, 12, 4, 2);
                    HuAudFXPlay(1431);
                }
                if (145.0f == lbl_1_bss_2C) {
                    lbl_1_data_4[0] = HuAudFXPlay(1429);
                }
                if (160.0f == lbl_1_bss_2C) {
                    lbl_1_data_4[1] = HuAudFXPlay(1430);
                }
                if (350.0f < lbl_1_bss_2C) {
                    object->work[0]++;
                    lbl_1_bss_2C = 0;
                }
            }
            break;

        case 1001:
            lbl_1_bss_2C++;
            if (5.0f == lbl_1_bss_2C && lbl_1_bss_20 < 0) {
                lbl_1_bss_20 = MGSeqStartCreate();
            }
            if (lbl_1_bss_2C >= 5.0f && lbl_1_data_0 == -1 && (MGSeqStatGet(lbl_1_bss_20) & 0x10)) {
                lbl_1_data_0 = HuAudSeqPlay(71);
            }
            if (lbl_1_bss_2C >= 5.0f && !MGSeqStatGet(lbl_1_bss_20) && lbl_1_bss_20 >= 0) {
                object->work[0]++;
                lbl_1_bss_20 = -1;
                lbl_1_bss_2C = 0;
            }
            else {
                float temp_f26 = (lbl_1_bss_2C > 60.0f) ? 1.0 : ((lbl_1_bss_2C > 0.0f) ? (lbl_1_bss_2C / 60.0) : 0.0);
                float temp_f27 = 1.0f - temp_f26;
                float temp_f31 = 830.0f * temp_f27;
                float temp_f30 = (-1792.0f * temp_f27) + (50.0f * temp_f26);
                float temp_f29 = (2854.0f * temp_f27) + (3500.0f * temp_f26);
                float temp_f25 = ((2578.212 * temp_f27) + (2600.0 * temp_f26)) / VECMagPoint(temp_f31, temp_f30, temp_f29);
                temp_f31 *= temp_f25;
                temp_f30 *= temp_f25;
                temp_f29 *= temp_f25;
                Hu3DCameraPosSet(1, temp_f31, temp_f30, temp_f29, -0.05f * temp_f27, 1, 0, 0, 50 * temp_f26, 0);
                (void)temp_f27;
            }
            break;

        case 1002:
            if (lbl_1_bss_18 != -1) {
                object->work[0] = 1003;
                lbl_1_bss_2C = 0;
            }
            break;

        case 1003:
            if (lbl_1_bss_20 < 0 && lbl_1_bss_2C == 0.0f) {
                lbl_1_bss_20 = MGSeqFinishCreate();
                for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                    Work19C8 *temp_r25 = lbl_1_bss_34[temp_r31]->data;
                    HuSprAttrSet(temp_r25->unkA4, 0, HUSPR_ATTR_DISPOFF);
                }
                if (lbl_1_data_0 != -1) {
                    HuAudSeqFadeOut(lbl_1_data_0, 100);
                }
            }
            else if (!MGSeqStatGet(lbl_1_bss_20)) {
                lbl_1_bss_2C++;
                if (lbl_1_bss_2C >= 30.0f) {
                    object->work[0]++;
                    lbl_1_bss_2C = 0;
                    if (lbl_1_bss_18 != 4) {
                        lbl_1_bss_20 = MGSeqWinCreate(sp28[lbl_1_bss_18]->unk18, -1, -1, -1);
                        GWPlayerCoinWinSet(sp28[lbl_1_bss_18]->unk14, 10);
                        HuAudSStreamPlay(1);
                    }
                    else if (lbl_1_bss_18 == 4) {
                        lbl_1_bss_20 = MGSeqDrawCreate();
                        HuAudSStreamPlay(4);
                    }
                    for (temp_r31 = 0; temp_r31 < 4; temp_r31++) {
                        Hu3DModelRotSet(lbl_1_bss_34[temp_r31]->model[4], 0, (lbl_1_bss_18 == temp_r31) ? 90 : -90, 0);
                    }
                }
            }
            break;

        case 1004:
            lbl_1_bss_2C++;
            if (210.0f < lbl_1_bss_2C) {
                lbl_1_bss_20 = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                object->func = fn_1_D700;
            }
            break;

        default:
            OSReport("*** main mode error(%d)!!\n", object->work[0]);

            break;
    }
}

void fn_1_B6C4(ModelData *arg0, Mtx arg1)
{
    GXLoadPosMtxImm(arg1, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    {
        s8 sp60[9] = { -1, 0, 1, 2, 3, 4, -1, -1, -1 };
        char *sp6C[6] = { "m413_11-m413_11", "m413_12-m413_12", "m413_13-m413_13", "m413_14-m413_14", "g005m3A-bomhei_A", "g005m3B-bomhei_B" };
        s8 sp28[6] = { 3, 4, 5, 6, 11, 12 };
        char *sp50[4] = { "m413_11b-m413_11b", "m413_12b-m143_12b", "m413_13b-m413_13b", "twest-m413_14b" };
        s8 sp24[4] = { 7, 8, 9, 10 };
        s32 temp_r27;
        Mtx spB4;
        Mtx sp84;
        for (temp_r27 = 0; temp_r27 < 12; temp_r27++) {
            StructBss2A6C *temp_r31;
            for (temp_r31 = lbl_1_bss_7884[temp_r27]; temp_r31; temp_r31 = temp_r31->unk48) {
                float temp_f31;
                if (temp_r31->unk0) {
                    s32 temp_r19 = 100;
                    s32 temp_r18 = 100;
                    float temp_f30 = temp_r31->unk1C.x;
                    float temp_f29 = temp_r31->unk1C.y;
                    float temp_f27 = 0;
                    if (temp_r31->unk4 && temp_r31->unk5) {
                        s32 sp40[4] = { 0, 1, 0, -1 };
                        s32 sp30[4] = { 1, 0, -1, 0 };
                        s32 temp_r24 = (temp_r31->unk4 + 3) % 4;
                        s32 temp_r26 = ((((temp_r31->unk4 + 3) % 4) + (9 + ((temp_r31->unk4 - 1) / 4)))) % 4;
                        s32 temp_r25 = 0;
                        float temp_f28 = 1;
                        temp_f30 -= sp40[temp_r26];
                        temp_f29 -= sp30[temp_r26];
                        switch ((temp_r31->unk4 - 1) / 4) {
                            case 0:
                            case 2:
                                for (temp_r25 = temp_r31->unk5 - 1; temp_r25 > 0; temp_r25--) {
                                    temp_f28 /= 2.0;
                                }
                                temp_f31 = 1.0f - temp_f28;
                                temp_r26 = (temp_r24 + 3 == temp_r26) ? (temp_r26 - 4) : ((temp_r24 - 3 == temp_r26) ? (temp_r26 + 4) : temp_r26);
                                temp_f30 += sind((temp_f28 * (temp_r24 * 90)) + (temp_f31 * (temp_r26 * 90)));
                                temp_f29 += cosd((temp_f28 * (temp_r24 * 90)) + (temp_f31 * (temp_r26 * 90)));
                                break;

                            case 1:
                                for (temp_r25 = temp_r31->unk5 - 1; temp_r25 > 0; temp_r25--) {
                                    temp_f28 /= 2.0;
                                }
                                temp_f31 = (temp_r31->unk5 - 1) / 3.0;
                                temp_f31 = (temp_f31 < 0.0f) ? 0.0f : ((temp_f31 > 1.0f) ? 1.0f : temp_f31);
                                temp_f31 = (0.75 * ((1.0f - temp_f28))) + (0.25 * temp_f31);
                                temp_f28 = 1.0f - temp_f31;
                                temp_f30 += sp40[temp_r24] * cosd(temp_f31 * 180.0f);
                                temp_f29 += sp30[temp_r24] * cosd(temp_f31 * 180.0f);
                                temp_f27 += sind(temp_f31 * 180.0f);

                                break;

                            default:
                                break;
                        }
                    }
                    temp_f30 = (temp_f30 * temp_r19) - (temp_r19 * 6);
                    temp_f29 = (temp_f29 * temp_r18) - (temp_r18 * 5);
                    temp_f27 = 100 * temp_f27;
                    if (sp60[temp_r31->unk0] != -1) {
                        s32 temp_r21 = sp60[temp_r31->unk0]
                            + (temp_r31->unk0 == 5 && ((temp_r31->unk1C.z < 0.0f && (temp_r31->unk1 & 0x1) == 0) || (temp_r31->unk1 & 0x2) != 0));
                        MTXTrans(spB4, 50 + temp_f30, 50 + temp_f29, temp_f27);
                        MTXConcat(arg1, spB4, spB4);
                        Hu3DModelObjDraw(lbl_1_bss_30->model[sp28[temp_r21]], sp6C[temp_r21], spB4);
                    }
                }
            }
        }
        for (temp_r27 = 0; temp_r27 < 4; temp_r27++) {
            s32 temp_r29;
            for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
                s32 temp_r17 = 25;
                s32 sp20 = (temp_r27 * 300) - 450;
                s32 sp1C = (505 - temp_r17) + (temp_r29 * (temp_r17 * 2));
                Work19C8 *temp_r30 = lbl_1_bss_34[temp_r27]->data;
                s32 temp_r23 = temp_r30->unk50[temp_r30->unk60][temp_r29];
                if (temp_r30->unk65[0] == 0 || temp_r30->unk65[0] > 7) {
                    if (sp60[temp_r23] != -1) {
                        MTXScale(spB4, 0.5f, 0.5f, 0.5f);
                        MTXTrans(sp84, sp20, sp1C + ((temp_r30->unk65[0]) ? (200.0f * ((15 - temp_r30->unk65[0]) / 15.0f)) : 0.0f), 125.0f);
                        MTXConcat(sp84, spB4, spB4);
                        MTXConcat(arg1, spB4, spB4);
                        Hu3DModelObjDraw(lbl_1_bss_30->model[sp28[sp60[temp_r23]]], sp6C[sp60[temp_r23]], spB4);
                    }
                }
                if (temp_r30->unk65[0] != 0 && temp_r30->unk65[0] < (15 - (temp_r29 * 4)) && sp60[temp_r30->unk63[temp_r29]] != -1) {
                    MTXScale(spB4, 0.5f, 0.5f, 0.5f);
                    MTXTrans(sp84, sp20, sp1C, 125.0 - (0.25 * (40.0f * (temp_r30->unk65[0] / 15.0f))));
                    MTXConcat(sp84, spB4, spB4);
                    MTXConcat(arg1, spB4, spB4);
                    Hu3DModelObjDraw(lbl_1_bss_30->model[sp28[sp60[temp_r30->unk63[temp_r29]]]], sp6C[sp60[temp_r30->unk63[temp_r29]]], spB4);
                }
            }
        }
        {
            s32 temp_r28 = lbl_1_bss_FC;
            s32 temp_r20;
            for (temp_r20 = 0; temp_r20 < 300; temp_r20++) {
                temp_r28++;
                temp_r28 %= 300;
                if (lbl_1_bss_100[temp_r28].unk0) {
                    MTXScale(spB4, 0.4f, 0.4f, 0.4f);
                    MTXRotDeg(sp84, 'x', 360.0 * (lbl_1_bss_100[temp_r28].unk1C / 255.0));
                    MTXConcat(sp84, spB4, spB4);
                    MTXRotDeg(sp84, 'z', 360.0 * (lbl_1_bss_100[temp_r28].unk1D / 255.0));
                    MTXConcat(sp84, spB4, spB4);
                    MTXTrans(sp84, lbl_1_bss_100[temp_r28].unk4.x, lbl_1_bss_100[temp_r28].unk4.y, lbl_1_bss_100[temp_r28].unk4.z);
                    MTXConcat(sp84, spB4, spB4);
                    MTXConcat(arg1, spB4, spB4);
                    Hu3DModelObjDraw(lbl_1_bss_30->model[sp24[sp60[lbl_1_bss_100[temp_r28].unk0]]], sp50[sp60[lbl_1_bss_100[temp_r28].unk0]], spB4);
                }
            }
        }
    }
}

void fn_1_C6E0(omObjData *object)
{
    s32 temp_r30;
    memset(lbl_1_bss_2A6C, 0, sizeof(lbl_1_bss_2A6C));
    memset(lbl_1_bss_7884, 0, sizeof(lbl_1_bss_7884));
    memset(lbl_1_bss_2684, 0, sizeof(lbl_1_bss_2684));
    lbl_1_bss_2680 = 0;
    memset(lbl_1_bss_100, 0, sizeof(lbl_1_bss_100));
    lbl_1_bss_FC = 0;
    memset(lbl_1_bss_D4, 0, sizeof(lbl_1_bss_D4));
    lbl_1_bss_D0 = 0;
    memset(lbl_1_bss_B8, 0, sizeof(lbl_1_bss_B8));
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M413, 0x00));
    omSetTra(object, 0, 0, 0);
    Hu3DMotionSpeedSet(object->model[0], 0);
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M413, 0x01));
    Hu3DMotionSpeedSet(object->model[1], 0);
    Hu3DModelPosSet(object->model[1], 0, 0, 0);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    object->model[2] = Hu3DHookFuncCreate(fn_1_B6C4);
    Hu3DModelLayerSet(object->model[2], 1);
    for (temp_r30 = 0; temp_r30 < 4; temp_r30++) {
        object->model[temp_r30 + 3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M413, 0x03) + temp_r30);
        Hu3DModelAttrSet(object->model[temp_r30 + 3], HU3D_ATTR_DISPOFF);
        object->model[temp_r30 + 7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M413, 0x07) + temp_r30);
        Hu3DModelAttrSet(object->model[temp_r30 + 7], HU3D_ATTR_DISPOFF);
    }
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        s32 temp_r28;
        if (temp_r30 == 0) {
            temp_r28 = DATA_MAKE_NUM(DATADIR_M413, 0x0B);
        }
        else {
            temp_r28 = DATA_MAKE_NUM(DATADIR_M413, 0x0C);
        }
        object->model[temp_r30 + 11] = Hu3DModelCreateFile(temp_r28);
        Hu3DModelAttrSet(object->model[temp_r30 + 11], HU3D_ATTR_DISPOFF);
    }
    for (temp_r30 = 0; temp_r30 < 5; temp_r30++) {
        s32 temp_r29;
        object->model[(temp_r30 * 10) + 13] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M413, 0x1E));
        for (temp_r29 = 0; temp_r29 < 10; temp_r29++) {
            if (temp_r29 != 0) {
                object->model[(13 + (temp_r30 * 10) + temp_r29)] = Hu3DModelLink(object->model[(temp_r30 * 10) + 13]);
            }
            Hu3DModelAttrSet(object->model[(13 + (temp_r30 * 10) + temp_r29)], HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(object->model[(13 + (temp_r30 * 10) + temp_r29)], 2);
        }
    }
    {
        void *temp_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_M413, 0x1F), MEMORY_DEFAULT_NUM, HEAP_DATA);
        AnimData *temp_r26 = HuSprAnimRead(temp_r27);
        lbl_1_bss_14 = HuSprGrpCreate(150);
        for (temp_r30 = 0; temp_r30 < 150; temp_r30++) {
            s16 temp_r25 = HuSprCreate(temp_r26, 0, 0);
            HuSprGrpMemberSet(lbl_1_bss_14, temp_r30, temp_r25);
            HuSprAttrSet(lbl_1_bss_14, temp_r30, HUSPR_ATTR_DISPOFF);
            HuSprColorSet(lbl_1_bss_14, temp_r30, 255, 255, 255);
            HuSprTPLvlSet(lbl_1_bss_14, temp_r30, 1.0f);
            HuSprPriSet(lbl_1_bss_14, temp_r30, 256 + temp_r30);
        }
    }
    object->func = fn_1_8C10;
}

void fn_1_CBB4(omObjData *object)
{
    s32 sp8[4] = { 0, 1, 2, 3 };
    s32 temp_r27 = 0;
    Work19C8 *temp_r31 = object->data;
    s32 temp_r29;
    s32 temp_r28;
    memset(temp_r31, 0, sizeof(Work19C8));
    if (object->work[0] == 0) {
        lbl_1_data_C[0] = lbl_1_data_C[1] = lbl_1_data_C[2] = lbl_1_data_C[3] = -1;
        for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
            s32 temp_r26;
        repeat_iter:
            temp_r26 = rand8() % 4;
            if (lbl_1_data_C[temp_r26] != -1) {
                goto repeat_iter;
            }
            lbl_1_data_C[temp_r26] = temp_r29;
        }
    }
    for (temp_r29 = 0; temp_r29 < 4; temp_r29++) {
        for (temp_r28 = 0; temp_r28 < 4; temp_r28++) {
            if (temp_r29 == lbl_1_data_C[temp_r28]) {
                sp8[temp_r27] = temp_r28;
                temp_r27++;
            }
        }
    }
    temp_r31->unk0 = temp_r31->unk4 = temp_r31->unk8 = temp_r31->unkC = 0;
    temp_r31->unk10 = object->work[0];
    temp_r31->unk14 = sp8[temp_r31->unk10];
    if (temp_r31->unk14 == 4) {
        OSReport("m413:wrong player group\n");
        temp_r31->unk14 = temp_r31->unk10;
    }
    temp_r31->unk18 = GWPlayerCfg[temp_r31->unk14].character;
    temp_r31->unk1C = (GWPlayerCfg[temp_r31->unk14].iscom) ? -1 : GWPlayerCfg[temp_r31->unk14].pad_idx;
    temp_r31->unk20 = (temp_r31->unk1C != -1) ? 0 : GWPlayerCfg[temp_r31->unk14].diff;
    temp_r31->unk2C = -1;
    temp_r31->unk24 = 0;
    temp_r31->unk28 = temp_r31->unk24;
    temp_r31->unk40 = temp_r31->unk24;
    temp_r31->unk44 = 100;
    temp_r31->unk72 = 2;
    temp_r31->unk74 = 0;
    fn_1_EC0(temp_r31);
    temp_r31->unk60 = 0;
    temp_r31->unk68 = ((rand8() % 4) * 7) + 3;
    temp_r31->unk6C = temp_r31->unk68;
    temp_r31->unk71 = 20;
    temp_r31->unk70 = 0;
    temp_r31->unk98 = 0;
    temp_r31->unk9C = 0;
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M413, 0x02));
    Hu3DModelLayerSet(object->model[0], 1);
    object->model[1] = Hu3DModelLink(object->model[0]);
    object->model[2] = Hu3DModelLink(object->model[0]);
    object->model[3] = Hu3DModelLink(object->model[0]);
    Hu3DModelPosSet(object->model[1], (temp_r31->unk10 * 300) - 525, -602, 40);
    Hu3DModelPosSet(object->model[2], (temp_r31->unk10 * 300) - 450, -602, 40);
    Hu3DModelPosSet(object->model[3], (temp_r31->unk10 * 300) - 375, -602, 40);
    Hu3DMotionTimeSet(object->model[1], 60.0f);
    Hu3DMotionTimeSet(object->model[2], 60.0f);
    Hu3DMotionTimeSet(object->model[3], 60.0f);
    Hu3DMotionSpeedSet(object->model[1], 0.0f);
    Hu3DMotionSpeedSet(object->model[2], 0.0f);
    Hu3DMotionSpeedSet(object->model[3], 0.0f);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(object->model[0], 60.0f);
    Hu3DMotionSpeedSet(object->model[0], 0.0f);
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M413, 0x0D) + temp_r31->unk18);
    Hu3DModelPosSet(object->model[4], (temp_r31->unk10 * 300) - 450, 670, 60);
    Hu3DMotionTimeSet(object->model[4], 60.0f);
    Hu3DMotionSpeedSet(object->model[4], 0.0f);
    object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M413, 0x15) + temp_r31->unk18);
    Hu3DModelPosSet(object->model[5], (temp_r31->unk10 * 300) - 450, 0, 0);
    Hu3DModelAttrSet(object->model[5], HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(object->model[5], 0.0f);
    {
        AnimData *temp_r23 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGCONST, 0x38) + GWPlayerCfg[temp_r31->unk14].character);
        s16 temp_r22;
        temp_r31->unkA4 = HuSprGrpCreate(1);
        temp_r22 = HuSprCreate(temp_r23, 0, 0);
        HuSprGrpMemberSet(temp_r31->unkA4, 0, temp_r22);
        HuSprAttrSet(temp_r31->unkA4, 0, HUSPR_ATTR_LOOP | HUSPR_ATTR_DISPOFF | HUSPR_ATTR_LINEAR);
        HuSprColorSet(temp_r31->unkA4, 0, 255, 255, 255);
        HuSprTPLvlSet(temp_r31->unkA4, 0, 1);
        HuSprPriSet(temp_r31->unkA4, 0, 512);
        HuSprScaleSet(temp_r31->unkA4, 0, 0.875f, 0.875f);
        HuSprSpeedSet(temp_r31->unkA4, 0, 1.0f);
    }

    object->func = fn_1_19C4;
}

void fn_1_D340(omObjData *object)
{
    object->work[0] = 1000;
    memset(lbl_1_bss_48, 0, sizeof(StructBss48));
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    object->func = fn_1_A53C;
}

void ObjectSetup(void)
{
    s32 i;
    OSReport("******* M413 ObjectSetup *********\n");
    HuAudSndGrpSet(38);
    lbl_1_bss_24 = omInitObjMan(600, 8192);
    omGameSysInit(lbl_1_bss_24);
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    Hu3DCameraPerspectiveSet(1, 40, 10, 20000, 1.2f);
    {
        Vec sp54 = { 616.5714f, -1331.2f, 2120.1142f };
        Vec sp48 = { -0.05f, 1.0f, 0.0f };
        Vec sp3C = { 0, 0, 0 };
        Vec sp30 = { 0, 0, 0 };
        Vec sp24 = { 0, 0, -1 };
        Hu3DCameraPosSetV(1, &sp54, &sp48, &sp3C);
    }
    {
        Vec sp18 = { -822.5f, 6743.0f, 4625.5f };
        Vec spC = { 0.1545085f, -0.788462f, -0.5850064f };
        GXColor sp8 = { 0, 0, 0, 255 };
        lbl_1_bss_1C = Hu3DGLightCreateV(&sp18, &spC, &sp8);
    }
    Hu3DGLightStaticSet(lbl_1_bss_1C, 1);
    Hu3DGLightSpotSet(lbl_1_bss_1C, 20, 2);
    lbl_1_bss_20 = -1;
    lbl_1_bss_18 = -1;
    lbl_1_bss_30 = omAddObjEx(lbl_1_bss_24, 101, 63, 0, 1, fn_1_C6E0);
    for (i = 0; i < 4; i++) {
        omObjData *object = lbl_1_bss_34[i] = omAddObjEx(lbl_1_bss_24, 100, 6, 0, 0, fn_1_CBB4);
        object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(Work19C8), MEMORY_DEFAULT_NUM);
        object->work[0] = i;
    }
    lbl_1_bss_44 = omAddObjEx(lbl_1_bss_24, 102, 0, 0, -1, fn_1_D340);
}

void fn_1_D700(omObjData *object)
{
    if (!WipeStatGet()) {
        if (lbl_1_bss_20 >= 0) {
            MGSeqKill(lbl_1_bss_20);
        }
        MGSeqKillAll();
        HuAudAllStop();
        omOvlReturnEx(1, 1);
    }
}
