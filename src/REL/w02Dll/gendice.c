#include "REL/w02Dll.h"
#ifndef __MWERKS__
#include "game/audio.h"
#include "game/hsfex.h"
#include "game/board/pause.h"
#endif
#include "ext_math.h"

typedef struct {
    union {
        /* 0x00 */ struct {
            u8 unk7 : 1;
            u8 unk6 : 1;
            u8 unk3 : 3;
            u8 unk1 : 2;
            u8 unk0 : 1;
        };
        u8 unk00;
    };
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
} WorkGenDice;

/* EXTERN FUNCTIONS */
void fn_1_13D0(void);
void fn_1_1574(m02GenDice *arg0);
void fn_1_1794(m02GenDice *arg0);
void fn_1_1850(omObjData *object);
void fn_1_1F94(m02GenDice *arg0, s32 arg1);
void fn_1_2030(m02GenDice *arg0);
void fn_1_2100(m02GenDice *arg0, s32 arg1);
void fn_1_2220(m02GenDice *arg0);
s32 fn_1_233C(m02GenDice *arg0);
void fn_1_23FC(m02GenDice *arg0, s32 arg1);
void fn_1_23B4(m02GenDice *arg0, s32 arg1);
void fn_1_272C(m02GenDice *arg0);

/* LOCAL FUNCTIONS */
void fn_1_1254(m02GenDice *arg0)
{
    Vec sp8;
    s32 i;

    OSReport("m02GenDiceCreate\n");
    arg0->unk2C = HuPrcChildCreate(fn_1_13D0, 0x2005, 0x2000, 0, boardMainProc);
    arg0->unk2C->user_data = arg0;
    arg0->unk94 = 0;
    arg0->unk9C = 0;
    arg0->unk28 = 0;
    Hu3D3Dto2D(&arg0->unk0C, 1, &sp8);

    /* Initialize Matrix */
    arg0->unk64[0] = arg0->unk64[1] = arg0->unk7C = sp8;
    arg0->unk7C.y = arg0->unk64[1].y = arg0->unk64[0].y = 155;
    arg0->unk7C.z = arg0->unk64[1].z = arg0->unk64[0].z = 1400;
    arg0->unk96 = -1;

    for (i = 0; i < 3; i++) {
        arg0->unk3C[i] = 0;
        arg0->unk50[i] = 0;
        arg0->unk30[i] = -1;
        arg0->unk48[i] = -1;
        arg0->unk88[i] = -1;
    }
}

void fn_1_13D0(void)
{
    s32 var_r29;
    s32 i;
    s32 var_r30_2;
    m02GenDice *temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk36[0] = temp_r31->unk36[1] = temp_r31->unk36[2] = 0;
    var_r29 = 0;
    temp_r31->unk96 = 0;
    while (temp_r31->unk96 < temp_r31->unk00) {
        fn_1_1574(temp_r31);
        fn_1_1794(temp_r31);
        while (temp_r31->unk9C == 0) {
            HuPrcVSleep();
        }
        fn_1_2220(temp_r31);
        while (temp_r31->unk9C != 0) {
            HuPrcVSleep();
        }
        temp_r31->unk96 += 1;
    }

    for (i = 0; i < temp_r31->unk00; i++) {
        var_r29 += temp_r31->unk36[i];
    }
    OSReport("Dice res: %d\n", var_r29);

    while (fn_1_233C(temp_r31) == 0) {
        HuPrcVSleep();
    }
    temp_r31->unk94 = (s16)var_r29;
    temp_r31->unk28 = 1;
    if (temp_r31->unk22 != 0) {
        for (i = 0; i < temp_r31->unk00; i++) {
            fn_1_23B4(temp_r31, i);
        }
        temp_r31->unk2C = NULL;
        HuPrcEnd();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_1518(m02GenDice *arg0)
{
    OSReport("m02GenDiceKill\n");
    if (arg0->unk2C) {
        HuPrcKill(arg0->unk2C);
    }
    fn_1_2030(arg0);
    fn_1_272C(arg0);
}

void fn_1_1574(m02GenDice *arg0)
{
    Vec sp8;
    f32 temp_f0;
    omObjData *temp_r3;
    s32 temp_r28;
    WorkGenDice *temp_r29;

    temp_r28 = arg0->unk96;
    arg0->unk30[temp_r28] = BoardModelCreate(arg0->unk04, NULL, 0);
    arg0->unk98 = 0.5f + BoardRandMod(arg0->unk1A);
    BoardModelMotionStart(arg0->unk30[temp_r28], 0, 0x40000001U);
    BoardModelMotionSpeedSet(arg0->unk30[temp_r28], 0);
    BoardModelMotionTimeSet(arg0->unk30[temp_r28], arg0->unk98);
    temp_r3 = omAddObjEx(boardObjMan, 0x102, 0U, 0U, -1, fn_1_1850);
    temp_r29 = (WorkGenDice *)temp_r3->work;

    temp_r29->unk7 = 0;
    temp_r29->unk6 = 0;
    temp_r29->unk3 = 0;
    temp_r29->unk1 = temp_r28;

    temp_r29->unk04 = 0;
    temp_r29->unk01 = 3;
    temp_r29->unk02 = 0;
    temp_r3->unk10 = (u32)arg0;
    arg0->unk3C[temp_r28] = temp_r3;
    sp8 = arg0->unk0C;
    sp8.y += (250.0f * arg0->unk24);
    temp_r3->trans.x = sp8.x;
    temp_r3->trans.y = sp8.y;
    temp_r3->trans.z = sp8.z;
    temp_r3->scale.x = 0;
    temp_r3->scale.y = 0;
    temp_r3->scale.z = 0;
    sp8.z += 70.0f;
    HuAudFXPlay(0x302);
}

void fn_1_1794(m02GenDice *arg0)
{
    WorkGenDice *temp_r30;

    temp_r30 = OM_GET_WORK_PTR(arg0->unk3C[arg0->unk96], WorkGenDice);
    while (temp_r30->unk3 != 1) {
        HuPrcVSleep();
    }
}

s32 fn_1_17F4(m02GenDice *arg0)
{
    WorkGenDice *temp;
    if (arg0->unk96 < 0) {
        return 0;
    }
    temp = OM_GET_WORK_PTR(arg0->unk3C[arg0->unk96], WorkGenDice);
    if (temp->unk3 != 1) {
        return 0;
    }
    return 1;
}

void fn_1_1850(omObjData *object)
{
    WorkGenDice *temp_r29;
    m02GenDice *temp_r27;
    s16 temp_r26;
    s16 temp_r25;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    temp_r27 = (m02GenDice *)object->unk10;
    temp_r29 = OM_GET_WORK_PTR(object, WorkGenDice);
    if (temp_r29->unk7 || BoardIsKill()) {
        fn_1_1F94(temp_r27, temp_r29->unk1);
        temp_r27->unk3C[temp_r29->unk1] = NULL;
        omDelObjEx(HuPrcCurrentGet(), object);
        return;
    }
    if (BoardPauseActiveCheck()) {
        return;
    }
    switch (temp_r29->unk3) {
        case 0:
            if (temp_r29->unk06 >= 1080) {
                temp_r29->unk3 = 1;
                object->scale.x = object->scale.y = object->scale.z = 1;

                object->rot.y = temp_r29->unk04 = 0;
            }
            else {
                if (!temp_r29->unk04 && temp_r27->unk88[temp_r29->unk1] == -1) {
                    temp_r27->unk88[temp_r29->unk1] = HuAudFXPlay(768);
                }
                object->rot.y = temp_r29->unk06 % 360;
                temp_r29->unk06 += 25;
                if (temp_r29->unk04 < 180) {
                    temp_f27 = 0;
                    temp_f28 = 1;
                }
                else {
                    temp_f27 = 1;
                    temp_f28 = 0.5f;
                }
                object->scale.x = (temp_f28 * sind((float)(temp_r29->unk04 % 180))) + temp_f27;
                object->scale.y = object->scale.x;
                object->scale.z = object->scale.x;
                if (temp_r29->unk04 <= 360) {
                    if (temp_r29->unk04 < 180) {
                        temp_r29->unk04 += 6;
                    }
                    else {
                        temp_r29->unk04 += 18;
                    }
                    if (temp_r29->unk04 > 360) {
                        temp_r29->unk04 = 360;
                    }
                }
            }
            break;

        case 1:
            temp_r29->unk04 += 4;
            if (temp_r29->unk04 > 360) {
                temp_r29->unk04 -= 360;
            }
            OSs16tof32(&temp_r29->unk04, &temp_f29);
            object->trans.y += sind(temp_f29) * 0.2f;
            break;

        case 2:
            temp_r29->unk04++;
            if (temp_r29->unk04 >= 8) {
                if (temp_r27->unk88[temp_r29->unk1] != -1) {
                    HuAudFXStop(temp_r27->unk88[temp_r29->unk1]);
                    temp_r27->unk88[temp_r29->unk1] = -1;
                }
                HuAudFXPlay(771);
                HuAudFXPlay(780);
                temp_r29->unk3 = 3;
                temp_r29->unk04 = 0;
                fn_1_23FC(temp_r27, temp_r27->unk36[temp_r29->unk1]);
                fn_1_2100(temp_r27, temp_r29->unk1);
                Hu3DParManPosSet(temp_r27->unk48[temp_r29->unk1], object->trans.x, object->trans.y, object->trans.z);
                BoardModelVisibilitySet(temp_r27->unk30[temp_r29->unk1], 0);
            }
            else {
                OSs16tof32(&temp_r29->unk04, &temp_f29);
                if (temp_r29->unk04 < 4) {
                    object->trans.y += (0.5f * temp_f29) + 10.0f;
                    object->scale.x += (0.1f * sind(4.0f * temp_f29));
                    object->scale.y = object->scale.x;
                    object->scale.z = object->scale.x;
                }
                else {
                    BoardModelAlphaSet(temp_r27->unk30[temp_r29->unk1], 255 - (temp_r29->unk04 * 32));
                }
                object->trans.y += -0.49f * temp_f29 * temp_f29;
            }
            break;

        case 3:
            if (++temp_r29->unk04 >= 150) {
                temp_r29->unk7 = 1;
            }
            break;
    }
    if (!temp_r29->unk6 || temp_r29->unk3 != 3) {
        if (temp_r29->unk02++ > temp_r29->unk01) {
            temp_r29->unk02 = 0;
            temp_r25 = BoardModelMotionTimeGet(temp_r27->unk30[temp_r29->unk1]);
            do {
                temp_r26 = BoardRandMod(temp_r27->unk1A);
            } while (temp_r26 == temp_r25);
            BoardModelMotionTimeSet(temp_r27->unk30[temp_r29->unk1], temp_r26 + 0.5f);
        }
    }
    BoardModelPosSet(temp_r27->unk30[temp_r29->unk1], object->trans.x, object->trans.y, object->trans.z);
    BoardModelRotSet(temp_r27->unk30[temp_r29->unk1], object->rot.x, object->rot.y, object->rot.z);
    BoardModelScaleSet(temp_r27->unk30[temp_r29->unk1], object->scale.x, object->scale.y, object->scale.z);
}

void fn_1_1F94(m02GenDice *arg0, s32 arg1)
{
    if (arg0->unk30[arg1] != -1) {
        BoardModelKill(arg0->unk30[arg1]);
        arg0->unk30[arg1] = -1;
    }

    if (arg0->unk48[arg1] != -1) {
        Hu3DParManKill(arg0->unk48[arg1]);
        arg0->unk48[arg1] = -1;
    }
}

void fn_1_2030(m02GenDice *arg0)
{
    fn_1_1F94(arg0, 0);
    fn_1_1F94(arg0, 1);
    fn_1_1F94(arg0, 2);
}

HsfanimStruct00 lbl_1_data_2D8 = { 150, { 0x00, 0x00 }, // padding?
    50, 0, 65.0f, { 0.0f, -0.195f, 0.0f }, 100.0f, 0.99f, 40.0f, 0.999f, 0x0004,
    { 0xFF, 0xFF, 0x20, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00 } };

void fn_1_2100(m02GenDice *arg0, s32 arg1)
{
    s16 temp_r29;
    AnimData *temp_r28;
    void *temp_r27;
    temp_r27 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 0x01), MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r28 = HuSprAnimRead(temp_r27);
    arg0->unk48[arg1] = Hu3DParManCreate(temp_r28, 100, &lbl_1_data_2D8);
    Hu3DParManAttrSet(arg0->unk48[arg1], 0x108);
    Hu3DParManRotSet(arg0->unk48[arg1], 0, 0, 0);
    Hu3DParManVecSet(arg0->unk48[arg1], 0, 0.4f, 0.2f);
    temp_r29 = Hu3DParManModelIDGet(arg0->unk48[arg1]);
    Hu3DModelLayerSet(temp_r29, 2);
    Hu3DParticleBlendModeSet(temp_r29, 0);
}

void fn_1_2220(m02GenDice *arg0)
{
    s32 temp_r30;
    WorkGenDice *temp_r29;
    temp_r30 = arg0->unk96;
    temp_r29 = OM_GET_WORK_PTR(arg0->unk3C[temp_r30], WorkGenDice);
    temp_r29->unk3 = 2;
    temp_r29->unk04 = 0;
    BoardModelMotionSpeedSet(arg0->unk30[temp_r30], 0);

    arg0->unk36[temp_r30] = arg0->unk1C[temp_r30];
}

typedef struct {
    u8 field0_bit0 : 1;
    u8 field0_bit1 : 1;
    u8 field0_bit2 : 1;
    u8 field0_bit3 : 2;
    s8 unk01;
    s16 unk02;
    s16 unk04[2];
    float unk08;
} WorkGenDiceNum;

void fn_1_22BC(m02GenDice *arg0)
{
    s32 temp_r31;
    WorkGenDiceNum *temp_r30;
    for (temp_r31 = 0; temp_r31 < arg0->unk00; temp_r31++) {
        if (arg0->unk50[temp_r31]) {
            temp_r30 = OM_GET_WORK_PTR(arg0->unk50[temp_r31], WorkGenDiceNum);
            temp_r30->field0_bit1 = 1;
            temp_r30->field0_bit2 = 1;
            temp_r30->unk02 = 0;
        }
    }
}

s32 fn_1_233C(m02GenDice *arg0)
{
    s32 temp_r31;
    WorkGenDiceNum *temp_r30;
    for (temp_r31 = 0; temp_r31 < arg0->unk00; temp_r31++) {
        if (!arg0->unk50[temp_r31]) {
            continue;
        }
        temp_r30 = OM_GET_WORK_PTR(arg0->unk50[temp_r31], WorkGenDiceNum);
        if (temp_r30->field0_bit2) {
            return 0;
        }
    }
    return 1;
}

void fn_1_23B4(m02GenDice *arg0, s32 arg1)
{
    WorkGenDiceNum *work;
    if (!arg0->unk50[arg1]) {
        return;
    }
    work = OM_GET_WORK_PTR(arg0->unk50[arg1], WorkGenDiceNum);
    work->field0_bit0 = 1;
}

void fn_1_25D0(omObjData *object);

void fn_1_23FC(m02GenDice *arg0, s32 arg1)
{
    Vec spC;
    s16 sp8[2];
    WorkGenDiceNum *temp_r31;
    s16 temp_r29;
    omObjData *temp_r28;
    s32 temp_r26;
    s16 temp_r25;
    temp_r26 = arg0->unk96;
    if (arg1 > 99) {
        arg1 = 99;
    }
    sp8[0] = arg1 % 10;
    sp8[1] = arg1 / 10;
    spC = arg0->unk0C;
    spC.y += 300.0f;
    temp_r28 = omAddObjEx(boardObjMan, 258, 0, 0, -1, fn_1_25D0);
    temp_r28->unk10 = (u32)arg0;
    temp_r31 = OM_GET_WORK_PTR(temp_r28, WorkGenDiceNum);
    temp_r31->field0_bit0 = 0;
    temp_r31->field0_bit1 = 0;
    temp_r31->field0_bit2 = 0;
    temp_r31->field0_bit3 = temp_r26;
    temp_r31->unk08 = 0.3f;
    temp_r31->unk01 = arg1;
    temp_r31->unk02 = 360;
    for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
        temp_r25 = BoardModelCreate(arg0->unk08[sp8[temp_r29]], NULL, 0);
        BoardModelPosSetV(temp_r25, &spC);
        temp_r31->unk04[temp_r29] = temp_r25;
    }
    if (sp8[1] == 0) {
        BoardModelVisibilitySet(temp_r31->unk04[1], 0);
    }
    arg0->unk50[temp_r26] = temp_r28;
}

void fn_1_2694(WorkGenDiceNum *arg0);
void fn_1_2830(m02GenDice *arg0, WorkGenDiceNum *arg1, s32 arg2);
void fn_1_2BE4(m02GenDice *arg0, WorkGenDiceNum *arg1, s32 arg2);

void fn_1_25D0(omObjData *object)
{
    WorkGenDiceNum *temp_r31;
    m02GenDice *temp_r30;
    temp_r30 = (m02GenDice *)object->unk10;
    temp_r31 = OM_GET_WORK_PTR(object, WorkGenDiceNum);
    if (temp_r31->field0_bit0 || BoardIsKill()) {
        fn_1_2694(temp_r31);
        temp_r30->unk50[temp_r31->field0_bit3] = NULL;
        omDelObjEx(HuPrcCurrentGet(), object);
        return;
    }
    if (BoardPauseActiveCheck()) {
        return;
    }
    fn_1_2830(temp_r30, temp_r31, temp_r31->field0_bit1);
    fn_1_2BE4(temp_r30, temp_r31, temp_r31->field0_bit1);
}

void fn_1_2694(WorkGenDiceNum *arg0)
{
    s32 i;
    for (i = 0; i < 2; i++) {
        if (arg0->unk04[i] == -1) {
            continue;
        }
        OSReport("%d:GenDiceNumExitOM Kill %d\n", i, arg0->unk04[i]);
        BoardModelKill(arg0->unk04[i]);
        arg0->unk04[i] = -1;
        (void)i;
    }
}

void fn_1_272C(m02GenDice *arg0)
{
    s32 i;
    WorkGenDiceNum *work;
    s32 j;
    for (i = 0; i < 3; i++) {
        if (!arg0->unk50[i]) {
            continue;
        }
        work = OM_GET_WORK_PTR(arg0->unk50[i], WorkGenDiceNum);
        for (j = 0; j < 2; j++) {
            if (work->unk04[j] == -1) {
                continue;
            }
            OSReport("%d:GenDiceNumOMKillAll %d\n", j, work->unk04[j]);
            BoardModelKill(work->unk04[j]);
            work->unk04[j] = -1;
            (void)j;
        }
        fn_1_23B4(arg0, i);
    }
}

void fn_1_2830(m02GenDice *arg0, WorkGenDiceNum *arg1, s32 arg2)
{
    float temp_f31;
    s16 temp_r31;
    Vec *temp_r29;
    s16 temp_r27;
    s32 sp8 = 0;
    Vec sp30;
    Vec sp24;
    Vec sp18 = { 288, 155, 1400 };
    Vec sp54[2];
    Vec sp3C[2] = { { 144, 155, 1400 }, { 432, 155, 1400 } };
    Vec sp6C[3] = { { 144, 155, 1400 }, { 432, 155, 1400 }, { 288, 155, 1400 } };
    Vec spC = { 288, 176, 1400 };
    temp_r27 = arg1->unk01 / 10;
    if (arg2) {
        temp_r29 = &spC;
        temp_f31 = -20.0f * arg1->field0_bit3;
    }
    else {
        switch (arg0->unk00) {
            case 1:
                temp_r29 = &arg0->unk7C;
                break;

            case 2:
            case 3:
                temp_r29 = &arg0->unk64[arg1->field0_bit3];
                break;
        }
        temp_f31 = 0;
    }
    for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
        if (temp_r27 == 0) {
            sp54[temp_r31].x = temp_r29->x;
        }
        else {
            if (temp_r31) {
                sp54[temp_r31].x = temp_r29->x - 30;
            }
            else {
                sp54[temp_r31].x = temp_r29->x + 30;
            }
        }
        sp54[temp_r31].y = temp_r29->y;
        sp54[temp_r31].z = temp_r29->z + temp_f31;
    }
    for (temp_r31 = 0; temp_r31 < 2; temp_r31++) {
        BoardModelPosGet(arg1->unk04[temp_r31], &sp30);
        Hu3D2Dto3D(&sp54[temp_r31], 1, &sp54[temp_r31]);
        VECSubtract(&sp54[temp_r31], &sp30, &sp24);
        if (VECMag(&sp24) < 0.01f) {
            arg1->field0_bit2 = 0;
            if (arg2 && arg1->field0_bit3) {
                BoardModelVisibilitySet(arg1->unk04[temp_r31], 0);
            }
        }
        else {
            arg1->field0_bit2 = 1;
        }
        VECScale(&sp24, &sp24, arg1->unk08);
        VECAdd(&sp30, &sp24, &sp30);
        BoardModelPosSetV(arg1->unk04[temp_r31], &sp30);
    }
}

void fn_1_2BE4(m02GenDice *arg0, WorkGenDiceNum *arg1, s32 arg2)
{
    s32 temp_r29;
    float temp_f30;
    if (arg2) {
        arg1->unk02 += 18;
        if (arg1->unk02 >= 360) {
            arg1->unk02 = 360;
        }
    }
    else {
        arg1->unk02 -= 18;
        if (arg1->unk02 <= 0) {
            arg1->unk02 = 0;
        }
    }
    OSs16tof32(&arg1->unk02, &temp_f30);
    for (temp_r29 = 0; temp_r29 < 2; temp_r29++) {
        if (arg1->unk04[temp_r29] == -1) {
            continue;
        }
        BoardModelRotSet(arg1->unk04[temp_r29], 0, temp_f30, 0);
    }
}
