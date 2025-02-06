#include "REL/mgmodedll.h"
#include "game/audio.h"
#include "game/wipe.h"

#include "ext_math.h"

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ void (*unk04)(omObjData *, ...);
    /* 0x08 */ s32 unk08[4];
    /* 0x18 */ char unk18[4];
    /* 0x1C */ s32 unk1C[4];
    /* 0x2C */ char unk2C[4];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ char unk38[0xC];
    /* 0x44 */ s32 unk44[2];
} StructBss2050; // Size unknown

typedef struct {
    /* 0x00 */ char unk00[8];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ char unk0C[0x10];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ char unk20[0x10];
    /* 0x30 */ s32 unk30;
} UnkFunc1EE58Struct; // Size unknown

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
} StructBss3CC; // Size 0x30

void fn_1_19A30(StructBss8 *arg0);
void fn_1_19B8C(void);
void fn_1_19D00(void);
void fn_1_19E94(void);
void fn_1_19F5C(omObjData *arg0);
void fn_1_1A564(void);
void fn_1_1A6A0(void);
void fn_1_1A8E8(void);
void fn_1_1AA28(void);
void fn_1_1AB58(void);
void fn_1_1AC88(StructBss2050 *arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_1B260(s32 arg0);
void fn_1_1BCEC(void);
void fn_1_1BECC(void);
void fn_1_1C09C(StructBss2050 *arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_1CB4C(void);
void fn_1_1CEB0(omObjData *arg0, StructBss8_24 *arg1);
void fn_1_1D49C(StructBss8_24 *arg0);
s32 fn_1_1D688(StructBss8_24 *arg0);
void fn_1_1DD74(s32 arg0, StructBss8_24 *arg1);
void fn_1_1E608(StructBss8_24 *arg0);
void fn_1_1EB20(StructBss8_24 *arg0);
void fn_1_1EBE8(void);
void fn_1_1ED20(void);
void fn_1_1EE58(s32 arg0, UnkFunc1EE58Struct *arg1);
void fn_1_1F32C(omObjData *arg0);
void fn_1_1FABC(void);
void fn_1_1FC44(s32 arg0);
void fn_1_20728(void);
s32 fn_1_20970(void);
void fn_1_20E84(s32 arg0);
void fn_1_20FD4(s32 arg0);
s32 fn_1_211B4(void);
s32 fn_1_214A4(void);
s32 fn_1_21CA4(void);
s32 fn_1_2228C(s32 arg0);
void fn_1_22728(void);
void fn_1_22C08(omObjData *arg0);
void fn_1_231F0(omObjData *arg0);
float fn_1_240E4(float arg0, float arg1, float arg2, float arg3);
float fn_1_2410C(float arg0, float arg1, float arg2);
float fn_1_2412C(float arg0, float arg1, float arg2, float arg3);
float fn_1_24204(float arg0, float arg1, float arg2, float arg3);
float fn_1_242CC(float arg0, float arg1, float arg2, float arg3);
void fn_1_24388(s32 arg0);
void fn_1_243B0(void);
void fn_1_243D0(void);
void fn_1_243E4(void);
void fn_1_244C0(s32 arg0);
void fn_1_245A8(void);
void fn_1_245CC(s32 arg0, float arg1, float arg2, s32 arg3);
s32 fn_1_25014(s32 arg0, s32 arg1, s32 arg2, s32 arg3, float arg4, float arg5, s32 arg6, s32 arg7, s32 arg8);
void fn_1_25524(s32 arg0, float arg1, float arg2);
void fn_1_255EC(s32 arg0, s32 arg1);
void fn_1_2567C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 fn_1_257B0(s32 arg0);
void fn_1_257F8(s32 arg0, s32 arg1, s32 arg2);
void fn_1_25EC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_1_26004(s32 arg0, Vec arg1, float arg2, float arg3, float arg4, s32 arg5, s32 arg6);
void fn_1_26790(s32 arg0, s32 arg1, float arg2, float arg3);

char lbl_1_bss_209C_pad[8]; // Could be part of StructBss2050.
StructBss2050 lbl_1_bss_2050;
StructBss8_24 lbl_1_bss_1E10[4];
omObjData *lbl_1_bss_1E0C;
StructBss3CC lbl_1_bss_3CC[140];
s32 lbl_1_bss_3C8;
StructBss8 *lbl_1_bss_3C4;
Process *lbl_1_bss_3C0;

s32 lbl_1_data_1E0 = 1; // Unused.

void fn_1_18DF8(Process *arg0, StructBss8 *arg1)
{
    s32 i;

    lbl_1_bss_3C0 = arg0;
    lbl_1_bss_3C4 = arg1;
    fn_1_245A8();
    fn_1_243E4();
    fn_1_244C0(1);
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    CRot.x = -10.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2900.0f;
    Hu3DModelPosSet(lbl_1_bss_3C4->unkC, 0.0f, 0.0f, 460.0f);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk10, 0, 1);
    fn_1_25EC8(lbl_1_bss_3C4->unk0, lbl_1_bss_3C4->unk8, 0, 2);
    lbl_1_bss_1E0C = omAddObjEx(lbl_1_bss_3C0, 0x1000, 141, 16, -1, fn_1_231F0);
    HuPrcChildCreate(fn_1_19E94, 100, 0x2000, 0, HuPrcCurrentGet());
    for (i = 0; i < 4; i++) {
        HuPrcChildCreate(fn_1_19D00, 100, 0x2000, 0, HuPrcCurrentGet());
    }
}

void fn_1_19018(void)
{
    Vec sp14 = { 0.0f, 0.0f, 640.0f };
    float temp_f31;
    s32 temp_r30;
    s32 i;

    fn_1_243B0();
    for (i = 1; i < 140; i++) {
        Hu3DModelAttrReset(lbl_1_bss_1E0C->model[i], HU3D_ATTR_DISPOFF);
    }
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, -1);
    for (i = 0; i < 240; i++) {
        fn_1_243B0();
        temp_f31 = fn_1_24204(2900.0f, 1150.0f, i, 180.0f);
        CZoom = fn_1_2410C(CZoom, temp_f31, 15.0f);
        if (i == 90) {
            fn_1_25EC8(lbl_1_bss_3C4->unk0, lbl_1_bss_3C4->unk8, 0, 0);
        }
    }
    lbl_1_bss_1E0C->work[0] = 1;
    temp_f31 = CZoom;
    for (i = 0; i < 90; i++) {
        fn_1_243B0();
        CZoom = fn_1_2410C(CZoom, fn_1_24204(temp_f31, 1600.0f, i, 60.0f), 10.0f);
        Center.y = fn_1_2410C(Center.y, fn_1_24204(0.0f, 215.0f, i, 60.0f), 10.0f);
        CRot.x = fn_1_2410C(CRot.x, fn_1_24204(-10.0f, 0.0f, i, 60.0f), 10.0f);
    }
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk14, 0xF, 1);
    fn_1_26004(lbl_1_bss_3C4->unkC, sp14, 0.0f, 3.0f, 0.0f, 1, 0);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk10, 0xF, 1);
    HuPrcSleep(30);
    HuAudSeqPlay(44);
    fn_1_25EC8(lbl_1_bss_3C4->unk0, lbl_1_bss_3C4->unk4, 0, 0);
    fn_1_24388(60);
    temp_r30 = fn_1_2530C(0, 0, 0);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk18, 0xF, 1);
    HuAudFXPlay(0x43);
    fn_1_25838(temp_r30, MAKE_MESSID(40, 0), -1, -1);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk10, 0xF, 1);
    fn_1_25584(temp_r30);
    fn_1_24388(60);
}

s32 fn_1_194C8(s32 arg0)
{
    s32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 i;

    var_r30 = 10;
    var_r29 = 0;
    var_r28 = 0;
    if (arg0 == 4) {
        var_r28 = 1;
        var_r30 = 0;
        if (lbl_1_bss_3C4->unk1C == 0 || lbl_1_bss_3C4->unk1C == 3) {
            for (i = 0; i < 4; i++) {
                if (lbl_1_bss_1E10[i].unk60 == 1) {
                    break;
                }
            }
            if (i != 4) {
                var_r29 = 2;
            }
            else {
                var_r29 = 1;
            }
        }
        else {
            var_r29 = 3;
        }
    }
    else {
        lbl_1_bss_3C4->unk1C = arg0;
        fn_1_19B8C();
    }
    while (TRUE) {
        fn_1_243B0();
        switch (var_r30) {
            case 10:
                var_r30 = 0;
                fn_1_20728();
                var_r29 = fn_1_20970();
                fn_1_20E84(lbl_1_bss_3C4->unk1C);
                if (var_r29 == -99) {
                    var_r30 = -99;
                }
                break;
            case 0:
                var_r30 = 1;
                fn_1_20FD4(lbl_1_bss_3C4->unk1C);
                while (TRUE) {
                    fn_1_243B0();
                    switch (var_r29) {
                        case 1:
                            var_r29 = fn_1_211B4();
                            break;
                        case 2:
                            var_r29 = fn_1_214A4();
                            break;
                        case 3:
                            if (lbl_1_bss_3C4->unk1C == 0 || lbl_1_bss_3C4->unk1C == 3) {
                                var_r29 = 5;
                            }
                            else if (lbl_1_bss_3C4->unk1C == 2) {
                                var_r29 = fn_1_21CA4();
                            }
                            else {
                                var_r29 = fn_1_2228C(var_r28);
                                var_r28 = 0;
                            }
                            break;
                    }
                    if (var_r29 == 0) {
                        var_r30 = 10;
                        break;
                    }
                    else if (var_r29 == 5) {
                        var_r30 = 99;
                        break;
                    }
                }
                fn_1_22728();
                break;
        }
        if (var_r30 == 99 || var_r30 == -99) {
            break;
        }
    }
    if (var_r30 == -99) {
        var_r30 = 0;
    }
    else {
        for (i = 0; i < 4; i++) {
            lbl_1_bss_3C4->unk24[i].unk5C = lbl_1_bss_1E10[i].unk5C;
            lbl_1_bss_3C4->unk24[i].unk60 = lbl_1_bss_1E10[i].unk60;
            lbl_1_bss_3C4->unk24[i].unk64 = lbl_1_bss_1E10[i].unk64;
            lbl_1_bss_3C4->unk24[i].unk68 = lbl_1_bss_1E10[i].unk68;
            lbl_1_bss_3C4->unk24[i].unk6C = lbl_1_bss_1E10[i].unk6C;
        }
        if (lbl_1_bss_3C4->unk1C == 1) {
            switch (lbl_1_bss_2050.unk1C[0]) {
                case 1:
                    lbl_1_bss_3C4->unk24[0].unk5C = lbl_1_bss_3C4->unk24[1].unk5C = 0;
                    lbl_1_bss_3C4->unk24[2].unk5C = lbl_1_bss_3C4->unk24[3].unk5C = 1;
                    break;
                case 2:
                    lbl_1_bss_3C4->unk24[0].unk5C = lbl_1_bss_3C4->unk24[2].unk5C = 0;
                    lbl_1_bss_3C4->unk24[1].unk5C = lbl_1_bss_3C4->unk24[3].unk5C = 1;
                    break;
                case 3:
                    lbl_1_bss_3C4->unk24[0].unk5C = lbl_1_bss_3C4->unk24[3].unk5C = 0;
                    lbl_1_bss_3C4->unk24[1].unk5C = lbl_1_bss_3C4->unk24[2].unk5C = 1;
                    break;
                default:
                    OSReport("########## ERROR : TAGMODE TEAMSET\n");
                    lbl_1_bss_3C4->unk24[0].unk5C = lbl_1_bss_3C4->unk24[1].unk5C = 0;
                    lbl_1_bss_3C4->unk24[2].unk5C = lbl_1_bss_3C4->unk24[3].unk5C = 1;
                    break;
            }
        }
        else if (lbl_1_bss_3C4->unk1C == 2) {
            switch (lbl_1_bss_2050.unk1C[0]) {
                case 0:
                    lbl_1_bss_3C4->unk20 = 3;
                    break;
                case 1:
                    lbl_1_bss_3C4->unk20 = 5;
                    break;
                case 2:
                    lbl_1_bss_3C4->unk20 = 7;
                    break;
                default:
                    OSReport("########## ERROR : KNUKIMODE TURNSET\n");
                    lbl_1_bss_3C4->unk20 = 3;
                    break;
            }
        }
        var_r30 = 1;
    }
    return var_r30;
}

void fn_1_19A30(StructBss8 *arg0)
{
    s32 i;

    OSReport("\n\n>>>>>>>>>>>>>>>>>>>> ENTRANCE HELP\n\n");
    switch (arg0->unk1C) {
        case 0:
            OSReport("MG_MODE : FREE PLAY MODE!!\n");
            break;
        case 1:
            OSReport("MG_MODE : TAG PLAY MODE!!\n");
            break;
        case 2:
            OSReport("MG_MODE : NUKE PLAY MODE!!\n");
            break;
        case 3:
            OSReport("MG_MODE : BINGO PLAY MODE!!\n");
            break;
    }
    if (arg0->unk1C == 2) {
        OSReport("\nTURN : %d\n", arg0->unk20);
    }
    OSReport("\nNO) GRP:COM:DIF:CHR:PAD\n");
    for (i = 0; i < 4; i++) {
        OSReport("%2d) %3d:%3d:%3d:%3d:%3d\n", i, arg0->unk24[i].unk5C, arg0->unk24[i].unk60, arg0->unk24[i].unk64, arg0->unk24[i].unk68,
            arg0->unk24[i].unk6C);
    }
    OSReport("\n>>>>>>>>>>>>>>>>>>>> ENTRANCE HELP\n\n");
}

void fn_1_19B8C(void)
{
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        lbl_1_bss_2050.unk1C[i] = lbl_1_bss_2050.unk08[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            lbl_1_bss_1E10[i].unk80[j] = lbl_1_bss_1E10[i].unk70[j] = 0;
        }
        lbl_1_bss_1E10[i].unk58 = i;
        lbl_1_bss_1E10[i].unk5C = 0;
        lbl_1_bss_1E10[i].unk60 = i;
        if (lbl_1_bss_1E10[i].unk60 > 0) {
            lbl_1_bss_1E10[i].unk60 = 1;
        }
        lbl_1_bss_1E10[i].unk64 = 0;
        lbl_1_bss_1E10[i].unk68 = i;
        lbl_1_bss_1E10[i].unk6C = i;
    }
}

void fn_1_19D00(void)
{
    omObjData *temp_r30;
    s32 temp_r31;

    temp_r31 = lbl_1_bss_3C8++;
    temp_r30 = omAddObjEx(lbl_1_bss_3C0, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_1E10[temp_r31].unk0 = temp_r30;
    lbl_1_bss_1E10[temp_r31].unk4 = NULL;
    lbl_1_bss_1E10[temp_r31].unk58 = temp_r31;
    lbl_1_bss_1E10[temp_r31].unk5C = 0;
    lbl_1_bss_1E10[temp_r31].unk60 = temp_r31;
    if (lbl_1_bss_1E10[temp_r31].unk60 > 0) {
        lbl_1_bss_1E10[temp_r31].unk60 = 1;
    }
    lbl_1_bss_1E10[temp_r31].unk64 = 0;
    lbl_1_bss_1E10[temp_r31].unk68 = temp_r31;
    lbl_1_bss_1E10[temp_r31].unk6C = temp_r31;
    while (TRUE) {
        fn_1_243B0();
        if (lbl_1_bss_1E10[temp_r31].unk4 != NULL) {
            lbl_1_bss_1E10[temp_r31].unk4(temp_r30, &lbl_1_bss_1E10[temp_r31]);
        }
    }
}

void fn_1_19E94(void)
{
    omObjData *temp_r3;

    temp_r3 = omAddObjEx(lbl_1_bss_3C0, 0x100, 16, 16, -1, NULL);
    lbl_1_bss_2050.unk00 = temp_r3;
    lbl_1_bss_2050.unk04 = NULL;
    fn_1_1C09C(&lbl_1_bss_2050, 0, 0, 0);
    fn_1_1AC88(&lbl_1_bss_2050, 0, 0, 0);
    while (TRUE) {
        fn_1_243B0();
        if (lbl_1_bss_2050.unk04 != NULL) {
            lbl_1_bss_2050.unk04(temp_r3, &lbl_1_bss_2050);
        }
    }
}

s32 lbl_1_data_32C[][4] = { { 177, 104, 120, 55 }, { 251, 104, 458, 55 }, { 325, 104, 120, 142 }, { 399, 104, 458, 142 } };

s32 lbl_1_data_36C[][6]
    = { { 168, 90, 120, 51, 112, 55 }, { 248, 190, 458, 51, 466, 55 }, { 328, 90, 120, 222, 112, 282 }, { 408, 190, 458, 222, 466, 282 } };

s32 lbl_1_data_3CC[] = { 224, 456, 272, 292, 468, 282 };

float lbl_1_data_3E4[][5] = { { 262.0f, 119.0f, 1.3f, 227.0f, 455.0f }, { 314.0f, 168.0f, 0.75f, 265.0f, 416.0f },
    { 366.0f, 204.0f, 0.75f, 230.0f, 450.0f }, { 418.0f, 240.0f, 0.75f, 300.0f, 381.0f }, { -1.0f, 289.0f, 1.3f, 220.0f, 460.0f } };

s32 lbl_1_data_448[][4] = { { 262, 262, 262, 262 }, { 314, 307, 373, 373 }, { 366, 373, 307, 418 }, { 418, 418, 418, 307 } };

s32 lbl_1_data_488 = -1;

void fn_1_19F5C(omObjData *arg0)
{
    float var_f30;
    float var_f31;
    s32 temp_r28;
    s32 var_r29;
    s32 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 i;
    s32 j;

    temp_r28 = lbl_1_bss_2050.unk34;
    var_r29 = var_r27 = var_r26 = var_r25 = 0;
    lbl_1_bss_2050.unk1C[0] = 0;
    var_r29 = 1;
    for (i = 1; i < 4; i++) {
        if (lbl_1_bss_1E10[i].unk60 == 0) {
            var_r29++;
        }
    }
    var_r27 = 1;
    for (i = 1; i < 4; i++) {
        if (HuPadStatGet(i) != -1) {
            var_r27++;
        }
    }
    if (var_r27 >= 2) {
        fn_1_1AA28();
        if (HuPadStkX[lbl_1_bss_1E10->unk6C] >= 5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 2)) {
            var_r29++;
            var_r26 = 1;
        }
        else if (HuPadStkX[lbl_1_bss_1E10->unk6C] <= -5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 1)) {
            var_r29--;
            var_r26 = -1;
        }
    }
    else {
        fn_1_1AB58();
    }
    if (var_r29 < 1) {
        var_r29 = var_r27;
    }
    else if (var_r29 > var_r27) {
        if (var_r26 == 0) {
            var_r29 = var_r27;
            var_r25 = 1;
        }
        else {
            var_r29 = 1;
        }
    }
    if (var_r26 != 0 || var_r25 != 0) {
        lbl_1_bss_2050.unk1C[0] = 1;
        HuAudFXPlay(0);
        for (i = 0; i <= 10; i++) {
            if (i <= 5) {
                var_f30 = fn_1_24204(0.0f, 10.0f, i, 5.0f);
                var_f31 = fn_1_24204(1.0f, 0.0f, i, 5.0f);
            }
            else {
                var_f30 = fn_1_24204(10.0f, 0.0f, i - 5, 5.0f);
                var_f31 = fn_1_24204(0.0f, 1.0f, i - 5, 5.0f);
            }
            if (var_r26 == 1) {
                HuSprPosSet(temp_r28, 9, lbl_1_data_32C[3][0] + 50 + var_f30, lbl_1_data_32C[0][1]);
            }
            else if (var_r26 == -1) {
                HuSprPosSet(temp_r28, 8, lbl_1_data_32C[0][0] - 50 - var_f30, lbl_1_data_32C[0][1]);
            }
            for (j = 0; j < 4; j++) {
                if (j < var_r29 && lbl_1_bss_1E10[j].unk60 == 1) {
                    lbl_1_bss_1E10[j].unk70[3] = 0;
                    HuSprScaleSet(temp_r28, j, var_f31, 1.0f);
                    HuSprScaleSet(temp_r28, j + 4, var_f31, 1.0f);
                    if (i == 5) {
                        HuSprBankSet(temp_r28, j, 0);
                    }
                }
                else if (j >= var_r29 && lbl_1_bss_1E10[j].unk60 == 0) {
                    lbl_1_bss_1E10[j].unk70[3] = 1;
                    HuSprScaleSet(temp_r28, j, var_f31, 1.0f);
                    HuSprScaleSet(temp_r28, j + 4, var_f31, 1.0f);
                    if (i == 5) {
                        HuSprBankSet(temp_r28, j, 1);
                    }
                }
            }
            fn_1_243B0();
        }
        for (j = 0; j < 4; j++) {
            if (j < var_r29) {
                lbl_1_bss_1E10[j].unk60 = 0;
            }
            else {
                lbl_1_bss_1E10[j].unk60 = 1;
            }
        }
    }
    lbl_1_bss_2050.unk1C[0] = 0;
}

void fn_1_1A564(void)
{
    s32 temp_r30;
    s32 i;

    temp_r30 = lbl_1_bss_2050.unk34;
    for (i = 0; i < 19; i++) {
        HuSprAttrSet(temp_r30, i, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 4; i++) {
        HuSprBankSet(temp_r30, i, 0);
        lbl_1_bss_1E10[i].unk70[3] = lbl_1_bss_1E10[i].unk60 = 0;
        HuSprAttrReset(temp_r30, i, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(temp_r30, 4 + i, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(temp_r30, 10, HUSPR_ATTR_DISPOFF);
    for (i = 0; i < 4; i++) {
        HuSprAttrReset(temp_r30, 11 + i, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(temp_r30, 15 + i, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpPosSet(temp_r30, 0.0f, -500.0f);
}

void fn_1_1A6A0(void)
{
    float var_f31;
    s32 temp_r28;
    s32 i;

    temp_r28 = lbl_1_bss_2050.unk34;
    fn_1_1A564();
    for (i = 0; i <= 60; i++) {
        fn_1_243B0();
        if (i <= 50) {
            var_f31 = fn_1_24204(-500.0f, 10.0f, i, 50.0f);
        }
        else {
            var_f31 = fn_1_2412C(10.0f, 2.06f, i - 50, 10.0f);
        }
        HuSprGrpPosSet(temp_r28, 0.0f, var_f31);
    }
}

void fn_1_1A8E8(void)
{
    float var_f31;
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 i;

    spC = 0;
    sp8 = 0;
    temp_r30 = lbl_1_bss_2050.unk34;
    for (i = 0; i <= 60; i++) {
        fn_1_243B0();
        if (i <= 10) {
            var_f31 = fn_1_24204(2.06f, 10.0f, i, 10.0f);
        }
        else {
            var_f31 = fn_1_2412C(10.0f, -500.0f, i - 10, 50.0f);
        }
        HuSprGrpPosSet(temp_r30, 0.0f, var_f31);
    }
    fn_1_1B260(0);
}

void fn_1_1AA28(void)
{
    s32 temp_r31;

    temp_r31 = lbl_1_bss_2050.unk34;
    HuSprAttrReset(temp_r31, 8, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(temp_r31, 8, lbl_1_data_32C[0][0] - 50, lbl_1_data_32C[0][1]);
    HuSprAttrReset(temp_r31, 9, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(temp_r31, 9, lbl_1_data_32C[3][0] + 50, lbl_1_data_32C[0][1]);
}

void fn_1_1AB58(void)
{
    s32 temp_r31;

    temp_r31 = lbl_1_bss_2050.unk34;
    HuSprAttrSet(temp_r31, 8, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(temp_r31, 8, lbl_1_data_32C[0][0] - 50, lbl_1_data_32C[0][1]);
    HuSprAttrSet(temp_r31, 9, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(temp_r31, 9, lbl_1_data_32C[3][0] + 50, lbl_1_data_32C[0][1]);
}

void fn_1_1AC88(StructBss2050 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    AnimData *temp_r26;
    AnimData *temp_r25;
    s32 var_r29;
    s32 var_r28;
    s32 i;

    var_r29 = HuSprGrpCreate(19);
    arg0->unk34 = var_r29;
    temp_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 111));
    for (i = 0; i < 4; i++) {
        var_r28 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 99)), 1000, 0);
        HuSprGrpMemberSet(var_r29, i, var_r28);
        HuSprPosSet(var_r29, i, lbl_1_data_32C[i % 4][0], lbl_1_data_32C[0][1]);
        var_r28 = HuSprCreate(temp_r26, 1010, 0);
        HuSprGrpMemberSet(var_r29, 4 + i, var_r28);
        HuSprTPLvlSet(var_r29, 4 + i, 0.5f);
        HuSprPosSet(var_r29, 4 + i, lbl_1_data_32C[i % 4][0] + 1, lbl_1_data_32C[0][1] + 2);
    }
    temp_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 137));
    for (i = 0; i < 2; i++) {
        var_r28 = HuSprCreate(temp_r26, 0, 0);
        HuSprGrpMemberSet(var_r29, 8 + i, var_r28);
        HuSprBankSet(var_r29, 8 + i, i);
    }
    var_r28 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 98)), 2000, 0);
    HuSprGrpMemberSet(var_r29, 10, var_r28);
    HuSprTPLvlSet(var_r29, 10, 0.8f);
    fn_1_26790(var_r29, 10, 288.0f, 240.0f);
    temp_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 101));
    temp_r25 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 102));
    for (i = 0; i < 4; i++) {
        var_r28 = HuSprCreate(temp_r26, 1980, 0);
        HuSprGrpMemberSet(var_r29, 11 + i, var_r28);
        HuSprBankSet(var_r29, 11 + i, i);
        fn_1_26790(var_r29, 11 + i, lbl_1_data_32C[i][2], lbl_1_data_32C[i][3]);
        var_r28 = HuSprCreate(temp_r25, 1990, 0);
        HuSprGrpMemberSet(var_r29, 15 + i, var_r28);
        HuSprBankSet(var_r29, 15 + i, i);
        HuSprTPLvlSet(var_r29, 15 + i, 0.5f);
        fn_1_26790(var_r29, 15 + i, lbl_1_data_32C[i][2] + 1, lbl_1_data_32C[i][3] + 6);
    }
    fn_1_1A564();
}

void fn_1_1B260(s32 arg0)
{
    s32 temp_r30;
    s32 i;

    temp_r30 = lbl_1_bss_2050.unk30;
    for (i = 0; i < 86; i++) {
        HuSprAttrSet(temp_r30, i, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_1E10[i].unk60 != 0) {
            HuSprAttrSet(temp_r30, 16 + lbl_1_bss_1E10[i].unk58, HUSPR_ATTR_DISPOFF);
            HuSprAttrSet(temp_r30, 20 + lbl_1_bss_1E10[i].unk58, HUSPR_ATTR_DISPOFF);
        }
        else {
            HuSprAttrReset(temp_r30, 16 + lbl_1_bss_1E10[i].unk58, HUSPR_ATTR_DISPOFF);
            HuSprAttrReset(temp_r30, 20 + lbl_1_bss_1E10[i].unk58, HUSPR_ATTR_DISPOFF);
        }
        HuSprPosSet(
            temp_r30, 16 + lbl_1_bss_1E10[i].unk58, lbl_1_data_36C[lbl_1_bss_1E10[i].unk68 % 4][0], lbl_1_data_36C[lbl_1_bss_1E10[i].unk68 / 4][1]);
        HuSprPosSet(
            temp_r30, 20 + lbl_1_bss_1E10[i].unk58, lbl_1_data_36C[lbl_1_bss_1E10[i].unk68 % 4][0], lbl_1_data_36C[lbl_1_bss_1E10[i].unk68 / 4][1]);
    }
    for (i = 0; i < 8; i++) {
        HuSprBankSet(temp_r30, i, 0);
        HuSprAttrReset(temp_r30, i, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(temp_r30, 8 + i, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(temp_r30, 40, HUSPR_ATTR_DISPOFF);
    for (i = 0; i < 4; i++) {
        HuSprBankSet(temp_r30, 16 + i, 0);
        HuSprBankSet(temp_r30, 20 + i, 0);
        HuSprAttrReset(temp_r30, 41 + i, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(temp_r30, 45 + i, HUSPR_ATTR_DISPOFF);
        fn_1_26790(temp_r30, 41 + i, lbl_1_data_36C[i][2], lbl_1_data_36C[i][3]);
        fn_1_26790(temp_r30, 45 + i, lbl_1_data_36C[i][2], lbl_1_data_36C[i][3] + 6);
    }
    HuWinDispOff(lbl_1_bss_2050.unk44[0]);
    HuWinDispOff(lbl_1_bss_2050.unk44[1]);
    if (arg0 == 1) {
        HuSprAttrSet(temp_r30, 40, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(temp_r30, 53, HUSPR_ATTR_DISPOFF);
        for (i = 0; i < 4; i++) {
            fn_1_26790(temp_r30, 41 + i, lbl_1_data_36C[i][4], lbl_1_data_36C[i][5]);
            fn_1_26790(temp_r30, 45 + i, lbl_1_data_36C[i][4] + 1, lbl_1_data_36C[i][5] + 6);
        }
        for (i = 0; i < 4; i++) {
            HuSprAttrReset(temp_r30, 81 + i, HUSPR_ATTR_DISPOFF);
            HuSprBankSet(temp_r30, 81 + i, lbl_1_bss_1E10[i].unk60);
            HuSprPosSet(temp_r30, 81 + i, lbl_1_data_3E4[lbl_1_bss_1E10[i].unk58][0], lbl_1_data_3CC[2]);
            HuSprScaleSet(temp_r30, 81 + i, 1.0f, 1.0f);
            HuSprAttrReset(temp_r30, 65 + i, HUSPR_ATTR_DISPOFF);
            HuSprPosSet(temp_r30, 65 + i, lbl_1_data_3E4[i][0] + 1.0f, lbl_1_data_3CC[2] + 2);
        }
        HuWinDispOn(lbl_1_bss_2050.unk44[0]);
    }
    else if (arg0 == 2) {
        HuSprAttrSet(temp_r30, 40, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(temp_r30, 53, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(temp_r30, 56, HUSPR_ATTR_DISPOFF);
        HuSprBankSet(temp_r30, 56, 0);
        for (i = 0; i < 4; i++) {
            fn_1_26790(temp_r30, 41 + i, lbl_1_data_36C[i][4], lbl_1_data_36C[i][5]);
            fn_1_26790(temp_r30, 45 + i, lbl_1_data_36C[i][4] + 1, lbl_1_data_36C[i][5] + 6);
        }
        HuWinDispOn(lbl_1_bss_2050.unk44[1]);
    }
    HuWinPosSet(lbl_1_bss_2050.unk44[0], 140.0f, lbl_1_data_3CC[2] - 519);
    HuWinPosSet(lbl_1_bss_2050.unk44[1], 100.0f, lbl_1_data_3CC[2] - 519);
    HuSprPosSet(temp_r30, 54, lbl_1_data_3CC[3], lbl_1_data_3CC[2]);
    HuSprPosSet(temp_r30, 55, lbl_1_data_3CC[4], lbl_1_data_3CC[2]);
    HuSprGrpPosSet(temp_r30, 0.0f, -500.0f);
}

void fn_1_1BCEC(void)
{
    float var_f31;
    s32 sp8;
    s32 i;

    sp8 = lbl_1_bss_2050.unk30;
    for (i = 0; i <= 60; i++) {
        fn_1_243B0();
        if (i <= 50) {
            var_f31 = fn_1_24204(-500.0f, 10.0f, i, 50.0f);
        }
        else {
            var_f31 = fn_1_2412C(10.0f, 2.06f, i - 50, 10.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_2050.unk30, 0.0f, var_f31);
        HuWinPosSet(lbl_1_bss_2050.unk44[0], 120.0f, lbl_1_data_3CC[2] - 19 + var_f31);
        HuWinPosSet(lbl_1_bss_2050.unk44[1], 100.0f, lbl_1_data_3CC[2] - 19 + var_f31);
    }
}

void fn_1_1BECC(void)
{
    float var_f31;
    s32 i;

    for (i = 0; i <= 60; i++) {
        fn_1_243B0();
        if (i <= 10) {
            var_f31 = fn_1_24204(2.06f, 10.0f, i, 10.0f);
        }
        else {
            var_f31 = fn_1_2412C(10.0f, -500.0f, i - 10, 50.0f);
        }
        HuSprGrpPosSet(lbl_1_bss_2050.unk30, 0.0f, var_f31);
        HuWinPosSet(lbl_1_bss_2050.unk44[0], 120.0f, lbl_1_data_3CC[2] - 19 + var_f31);
        HuWinPosSet(lbl_1_bss_2050.unk44[1], 100.0f, lbl_1_data_3CC[2] - 19 + var_f31);
    }
}

void fn_1_1C09C(StructBss2050 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    AnimData *temp_r28;
    AnimData *temp_r26;
    AnimData *temp_r25;
    AnimData *temp_r24;
    AnimData *temp_r23;
    s32 var_r29;
    s32 var_r30;
    s32 i;

    var_r29 = arg0->unk30 = HuSprGrpCreate(86);
    temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 111));
    for (i = 0; i < 8; i++) {
        var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 103 + i)), 1000, 0);
        HuSprGrpMemberSet(var_r29, i, var_r30);
        HuSprPosSet(var_r29, i, lbl_1_data_36C[i % 4][0], lbl_1_data_36C[i / 4][1]);
        var_r30 = HuSprCreate(temp_r28, 1010, 0);
        HuSprGrpMemberSet(var_r29, 8 + i, var_r30);
        HuSprTPLvlSet(var_r29, 8 + i, 0.5f);
        HuSprPosSet(var_r29, 8 + i, lbl_1_data_36C[i % 4][0] + 1, (lbl_1_data_36C[i / 4][1] + 2));
    }
    for (i = 0; i < 4; i++) {
        var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 112 + i)), 0, 0);
        HuSprGrpMemberSet(var_r29, 16 + i, var_r30);
        var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 117 + i)), 10, 0);
        HuSprGrpMemberSet(var_r29, 20 + i, var_r30);
    }
    temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 116));
    temp_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 121));
    temp_r25 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 122));
    temp_r24 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 124));
    temp_r23 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 123));
    for (i = 0; i < 4; i++) {
        var_r30 = HuSprCreate(temp_r28, 0, 0);
        HuSprGrpMemberSet(var_r29, 24 + i, var_r30);
        var_r30 = HuSprCreate(temp_r26, 30, 0);
        HuSprGrpMemberSet(var_r29, 28 + i, var_r30);
        var_r30 = HuSprCreate(temp_r25, 10, 0);
        HuSprGrpMemberSet(var_r29, 32 + i, var_r30);
        var_r30 = HuSprCreate(temp_r24, 20, 0);
        HuSprGrpMemberSet(var_r29, 36 + i, var_r30);
        HuSprTPLvlSet(var_r29, 36 + i, 0.5f);
        var_r30 = HuSprCreate(temp_r23, 20, 0);
        HuSprGrpMemberSet(var_r29, 49 + i, var_r30);
    }
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 100)), 2000, 0);
    HuSprGrpMemberSet(var_r29, 40, var_r30);
    HuSprTPLvlSet(var_r29, 40, 0.8f);
    fn_1_26790(var_r29, 40, 288.0f, 240.0f);
    temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 101));
    temp_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 102));
    for (i = 0; i < 4; i++) {
        var_r30 = HuSprCreate(temp_r28, 1980, 0);
        HuSprGrpMemberSet(var_r29, 41 + i, var_r30);
        HuSprBankSet(var_r29, 41 + i, i);
        fn_1_26790(var_r29, 41 + i, lbl_1_data_36C[i][2], lbl_1_data_36C[i][3]);
        var_r30 = HuSprCreate(temp_r26, 1990, 0);
        HuSprGrpMemberSet(var_r29, 45 + i, var_r30);
        HuSprBankSet(var_r29, 45 + i, i);
        HuSprTPLvlSet(var_r29, 45 + i, 0.5f);
        fn_1_26790(var_r29, 45 + i, lbl_1_data_36C[i][2] + 1, lbl_1_data_36C[i][3] + 6);
    }
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 125)), 2000, 0);
    HuSprGrpMemberSet(var_r29, 53, var_r30);
    HuSprTPLvlSet(var_r29, 53, 0.8f);
    fn_1_26790(var_r29, 53, 288.0f, 240.0f);
    temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 137));
    for (i = 0; i < 2; i++) {
        var_r30 = HuSprCreate(temp_r28, 0, 0);
        HuSprGrpMemberSet(var_r29, 54 + i, var_r30);
        HuSprBankSet(var_r29, 54 + i, i);
    }
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 139)), 1000, 0);
    HuSprGrpMemberSet(var_r29, 56, var_r30);
    HuSprPosSet(var_r29, 56, 380.0f, lbl_1_data_3CC[2]);
    for (i = 0; i < 2; i++) {
        arg0->unk44[i] = HuWinExCreateStyled(0.0f, 0.0f, 200, 200, -1, 1);
        HuWinBGTPLvlSet(arg0->unk44[i], 0.0f);
        HuWinMesSet(arg0->unk44[i], MAKE_MESSID(27, 48 + i));
        HuWinMesSpeedSet(arg0->unk44[i], 0);
        HuWinDispOff(arg0->unk44[i]);
        winData[arg0->unk44[i]].mess_shadow_color = 0;
    }
    var_r30 = HuSprCreate(HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 138)), 990, 0);
    HuSprGrpMemberSet(var_r29, 85, var_r30);
    temp_r25 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 134));
    for (i = 0; i < 8; i++) {
        temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 126 + i));
        var_r30 = HuSprCreate(temp_r28, 1000, 0);
        HuSprGrpMemberSet(var_r29, 57 + i, var_r30);
        var_r30 = HuSprCreate(temp_r25, 1010, 0);
        HuSprGrpMemberSet(var_r29, 65 + i, var_r30);
    }
    temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 135));
    temp_r26 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 136));
    for (i = 0; i < 4; i++) {
        var_r30 = HuSprCreate(temp_r28, 990, 0);
        HuSprGrpMemberSet(var_r29, 73 + i, var_r30);
        var_r30 = HuSprCreate(temp_r26, 990, 0);
        HuSprGrpMemberSet(var_r29, 77 + i, var_r30);
    }
    temp_r28 = HuSprAnimReadFile(DATA_MAKE_NUM(DATADIR_MGMODE, 140));
    for (i = 0; i < 4; i++) {
        var_r30 = HuSprCreate(temp_r28, 990, 0);
        HuSprGrpMemberSet(var_r29, 81 + i, var_r30);
    }
    fn_1_1B260(0);
}

void fn_1_1CB4C(void)
{
    StructBss8_24 *temp_r30;
    float temp_f31;
    float temp_f30;
    s32 temp_r29;
    s32 i;
    s32 j;

    temp_r29 = lbl_1_bss_2050.unk30;
    for (i = 0; i < 8; i++) {
        HuSprBankSet(temp_r29, i, 0);
    }
    for (i = 0; i < 4; i++) {
        HuSprBankSet(temp_r29, 16 + i, 0);
        HuSprBankSet(temp_r29, 20 + i, 0);
        HuSprBankSet(temp_r29, 24 + i, 0);
        HuSprBankSet(temp_r29, 28 + i, 0);
        HuSprBankSet(temp_r29, 32 + i, 0);
    }
    for (i = 0; i <= 10; i++) {
        fn_1_243B0();
        for (j = 0; j < 4; j++) {
            temp_r30 = &lbl_1_bss_1E10[j];
            temp_f31 = fn_1_24204(lbl_1_data_36C[temp_r30->unk68 % 4][0], lbl_1_data_36C[temp_r30->unk58 % 4][0], i, 10.0f);
            temp_f30 = fn_1_24204(lbl_1_data_36C[temp_r30->unk68 / 4][1], lbl_1_data_36C[temp_r30->unk58 / 4][1], i, 10.0f);
            HuSprPosSet(temp_r29, 16 + temp_r30->unk58, temp_f31, temp_f30);
            HuSprPosSet(temp_r29, 20 + temp_r30->unk58, temp_f31, temp_f30);
        }
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_1E10[i].unk68 = lbl_1_bss_1E10[i].unk58;
        lbl_1_bss_1E10[i].unk70[0] = 0;
    }
}

void fn_1_1CEB0(omObjData *arg0, StructBss8_24 *arg1)
{
    float temp_f31;
    float temp_f30;
    s32 temp_r25;
    s32 var_r27;
    s32 var_r26;
    s32 temp_r24;
    s32 temp_r23;
    s32 var_r30;
    s32 var_r29;
    s32 i;

    temp_r25 = lbl_1_bss_2050.unk30;
    var_r27 = 0;
    var_r26 = 0;
    temp_r24 = var_r30 = arg1->unk68 % 4;
    temp_r23 = var_r29 = arg1->unk68 / 4;
    if (arg1->unk70[0] == 0) {
        if (HuPadBtnDown[arg1->unk6C] & 0x100) {
            arg1->unk70[0] = 1;
            HuSprBankSet(temp_r25, arg1->unk68, 1);
            HuSprBankSet(temp_r25, 16 + arg1->unk58, 1);
            HuSprBankSet(temp_r25, 20 + arg1->unk58, 1);
            HuAudFXPlay(0x6D + arg1->unk68);
        }
        else {
            if (HuPadStkX[arg1->unk6C] >= 5 || (HuPadBtn[arg1->unk6C] & 2)) {
                var_r30++;
                var_r27 = 1;
                if (var_r30 > 3) {
                    var_r30 = 3;
                }
            }
            else if (HuPadStkX[arg1->unk6C] <= -5 || (HuPadBtn[arg1->unk6C] & 1)) {
                var_r30--;
                var_r27 = -1;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
            }
            if (HuPadStkY[arg1->unk6C] <= -5 || (HuPadBtn[arg1->unk6C] & 4)) {
                var_r29++;
                var_r26 = 1;
                if (var_r29 > 1) {
                    var_r29 = 1;
                }
            }
            else if (HuPadStkY[arg1->unk6C] >= 5 || (HuPadBtn[arg1->unk6C] & 8)) {
                var_r29--;
                var_r26 = -1;
                if (var_r29 < 0) {
                    var_r29 = 0;
                }
            }
        }
    }
    else if (HuPadBtnDown[arg1->unk6C] & 0x200) {
        arg1->unk70[0] = 0;
        HuSprBankSet(temp_r25, arg1->unk68, 0);
        HuSprBankSet(temp_r25, 16 + arg1->unk58, 0);
        HuSprBankSet(temp_r25, 20 + arg1->unk58, 0);
        HuAudFXPlay(3);
    }
    if (arg1->unk68 != var_r30 + var_r29 * 4) {
        do {
            for (i = 0; i < 4; i++) {
                if (i != arg1->unk58 && lbl_1_bss_1E10[i].unk60 == 0 && var_r30 + var_r29 * 4 == lbl_1_bss_1E10[i].unk68) {
                    if (var_r27 == 0 || var_r26 == 0) {
                        if (var_r30 + var_r27 > 3 || var_r30 + var_r27 < 0) {
                            var_r30 = temp_r24;
                        }
                        else {
                            var_r30 += var_r27;
                        }
                        if (var_r29 + var_r26 > 1 || var_r29 + var_r26 < 0) {
                            var_r29 = temp_r23;
                        }
                        else {
                            var_r29 += var_r26;
                        }
                    }
                    else {
                        if (var_r30 + var_r27 <= 3 && var_r30 + var_r27 >= 0) {
                            var_r30 += var_r27;
                        }
                        else if (var_r29 + var_r26 <= 1 && var_r29 + var_r26 >= 0) {
                            var_r29 += var_r26;
                        }
                        else {
                            var_r30 = temp_r24;
                            var_r29 = temp_r23;
                        }
                    }
                    break;
                }
            }
        } while (i != 4);
        if (arg1->unk68 != var_r30 + var_r29 * 4) {
            arg1->unk68 = var_r30 + var_r29 * 4;
            HuAudFXPlay(0);
            for (i = 0; i <= 10; i++) {
                fn_1_243B0();
                temp_f31 = fn_1_24204(lbl_1_data_36C[temp_r24][0], lbl_1_data_36C[var_r30][0], i, 10.0f);
                temp_f30 = fn_1_24204(lbl_1_data_36C[temp_r23][1], lbl_1_data_36C[var_r29][1], i, 10.0f);
                HuSprPosSet(temp_r25, 16 + arg1->unk58, temp_f31, temp_f30);
                HuSprPosSet(temp_r25, 20 + arg1->unk58, temp_f31, temp_f30);
            }
        }
    }
}

void fn_1_1D49C(StructBss8_24 *arg0)
{
    s32 temp_r30;

    temp_r30 = lbl_1_bss_2050.unk30;
    arg0->unk64 = 0;
    HuSprBankSet(temp_r30, 32 + arg0->unk58, arg0->unk64);
    HuSprPosSet(temp_r30, 32 + arg0->unk58, lbl_1_data_36C[arg0->unk68 % 4][0], lbl_1_data_36C[arg0->unk68 / 4][1] + 35);
    HuSprPosSet(temp_r30, 36 + arg0->unk58, lbl_1_data_36C[arg0->unk68 % 4][0] + 1, lbl_1_data_36C[arg0->unk68 / 4][1] + 37);
    HuSprAttrReset(temp_r30, 32 + arg0->unk58, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(temp_r30, 36 + arg0->unk58, HUSPR_ATTR_DISPOFF);
}

s32 fn_1_1D688(StructBss8_24 *arg0)
{
    float var_f31;
    s32 i;
    s32 temp_r29;
    s32 var_r28;
    s32 var_r26;
    s32 var_r27;

    var_r28 = 0;
    temp_r29 = lbl_1_bss_2050.unk30;
    while (TRUE) {
        fn_1_243B0();
        var_r28 = 0;
        var_r26 = arg0->unk64;
        if (HuPadStkX[lbl_1_bss_1E10->unk6C] >= 5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 2)) {
            if (GWGameStat.veryHardUnlock == 1) {
                arg0->unk64++;
                var_r28 = 1;
                if (arg0->unk64 > 3) {
                    arg0->unk64 = 0;
                }
            }
            else {
                arg0->unk64++;
                var_r28 = 1;
                if (arg0->unk64 > 2) {
                    arg0->unk64 = 0;
                }
            }
        }
        else if (HuPadStkX[lbl_1_bss_1E10->unk6C] <= -5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 1)) {
            if (GWGameStat.veryHardUnlock == 1) {
                arg0->unk64--;
                var_r28 = -1;
                if (arg0->unk64 < 0) {
                    arg0->unk64 = 3;
                }
            }
            else {
                arg0->unk64--;
                var_r28 = -1;
                if (arg0->unk64 < 0) {
                    arg0->unk64 = 2;
                }
            }
        }
        else if (HuPadBtnDown[0] & 0x100) {
            var_r27 = 1;
            HuAudFXPlay(2);
            break;
        }
        else if (HuPadBtnDown[0] & 0x200) {
            var_r27 = 0;
            HuAudFXPlay(3);
            break;
        }
        if (arg0->unk64 != var_r26) {
            HuAudFXPlay(0);
            for (i = 0; i <= 5; i++) {
                fn_1_243B0();
                var_f31 = fn_1_24204(lbl_1_data_36C[arg0->unk68 % 4][0], lbl_1_data_36C[arg0->unk68 % 4][0] + var_r28 * 10, i, 5.0f);
                HuSprPosSet(temp_r29, 32 + arg0->unk58, var_f31, lbl_1_data_36C[arg0->unk68 / 4][1] + 35);
                HuSprPosSet(temp_r29, 36 + arg0->unk58, var_f31 + 1.0f, lbl_1_data_36C[arg0->unk68 / 4][1] + 37);
            }
            HuSprBankSet(temp_r29, 32 + arg0->unk58, arg0->unk64);
            for (i = 0; i <= 5; i++) {
                fn_1_243B0();
                var_f31 = fn_1_24204(lbl_1_data_36C[arg0->unk68 % 4][0] + var_r28 * 10, lbl_1_data_36C[arg0->unk68 % 4][0], i, 5.0f);
                HuSprPosSet(temp_r29, 32 + arg0->unk58, var_f31, lbl_1_data_36C[arg0->unk68 / 4][1] + 35);
                HuSprPosSet(temp_r29, 36 + arg0->unk58, var_f31 + 1.0f, lbl_1_data_36C[arg0->unk68 / 4][1] + 37);
            }
        }
    }
    if (var_r27 == 1) {
        HuSprPosSet(temp_r29, 49 + arg0->unk58, lbl_1_data_36C[arg0->unk68 % 4][0], lbl_1_data_36C[arg0->unk68 / 4][1] + 35);
        HuSprBankSet(temp_r29, 49 + arg0->unk58, arg0->unk64);
        HuSprAttrReset(temp_r29, 49 + arg0->unk58, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(temp_r29, 32 + arg0->unk58, HUSPR_ATTR_DISPOFF);
    }
    return var_r27;
}

void fn_1_1DD74(s32 arg0, StructBss8_24 *arg1)
{
    float temp_f31;
    float var_f30;
    s32 temp_r27;
    s32 var_r26;
    s32 var_r25;
    s32 sp8;
    s32 temp_r23;
    s32 temp_r22;
    s32 var_r30;
    s32 var_r29;
    s32 i;

    temp_r27 = lbl_1_bss_2050.unk30;
    var_r26 = 0;
    var_r25 = 0;
    sp8 = arg1->unk64;
    temp_r23 = var_r30 = arg1->unk68 % 4;
    temp_r22 = var_r29 = arg1->unk68 / 4;
    if (arg1->unk70[0] == 0) {
        if (HuPadBtnDown[lbl_1_bss_1E10->unk6C] & 0x100) {
            arg1->unk70[0] = 1;
            HuSprBankSet(temp_r27, arg1->unk68, 1);
            HuSprBankSet(temp_r27, 24 + arg1->unk58, 1);
            HuSprBankSet(temp_r27, 28 + arg1->unk58, 1);
            HuAudFXPlay(0x6D + arg1->unk68);
            fn_1_1D49C(arg1);
        }
        else {
            if (HuPadStkX[lbl_1_bss_1E10->unk6C] >= 5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 2)) {
                var_r30++;
                var_r26 = 1;
                if (var_r30 > 3) {
                    var_r30 = 3;
                }
            }
            else if (HuPadStkX[lbl_1_bss_1E10->unk6C] <= -5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 1)) {
                var_r30--;
                var_r26 = -1;
                if (var_r30 < 0) {
                    var_r30 = 0;
                }
            }
            if (HuPadStkY[lbl_1_bss_1E10->unk6C] <= -5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 4)) {
                var_r29++;
                var_r25 = 1;
                if (var_r29 > 1) {
                    var_r29 = 1;
                }
            }
            else if (HuPadStkY[lbl_1_bss_1E10->unk6C] >= 5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 8)) {
                var_r29--;
                var_r25 = -1;
                if (var_r29 < 0) {
                    var_r29 = 0;
                }
            }
        }
    }
    else if (HuPadBtnDown[lbl_1_bss_1E10->unk6C] & 0x200) {
        arg1->unk70[0] = arg1->unk70[2] = 0;
        HuSprBankSet(temp_r27, arg1->unk68, 0);
        HuSprBankSet(temp_r27, 24 + arg1->unk58, 0);
        HuSprBankSet(temp_r27, 28 + arg1->unk58, 0);
        HuSprAttrSet(temp_r27, 32 + arg1->unk58, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(temp_r27, 36 + arg1->unk58, HUSPR_ATTR_DISPOFF);
        HuAudFXPlay(3);
    }
    if (arg1->unk68 == var_r30 + var_r29 * 4) {
        return;
    }
    do {
        for (i = 0; i < 4; i++) {
            if (i != arg1->unk58 && lbl_1_bss_1E10[i].unk70[0] == 1 && var_r30 + var_r29 * 4 == lbl_1_bss_1E10[i].unk68) {
                if (var_r26 == 0 || var_r25 == 0) {
                    if (var_r30 + var_r26 > 3 || var_r30 + var_r26 < 0) {
                        var_r30 = temp_r23;
                    }
                    else {
                        var_r30 += var_r26;
                    }
                    if (var_r29 + var_r25 > 1 || var_r29 + var_r25 < 0) {
                        var_r29 = temp_r22;
                    }
                    else {
                        var_r29 += var_r25;
                    }
                }
                else {
                    if (var_r30 + var_r26 <= 3 && var_r30 + var_r26 >= 0) {
                        var_r30 += var_r26;
                    }
                    else if (var_r29 + var_r25 <= 1 && var_r29 + var_r25 >= 0) {
                        var_r29 += var_r25;
                    }
                    else {
                        var_r30 = temp_r23;
                        var_r29 = temp_r22;
                    }
                }
                break;
            }
        }
    } while (i != 4);
    if (arg1->unk68 != var_r30 + var_r29 * 4) {
        arg1->unk68 = var_r30 + var_r29 * 4;
        HuAudFXPlay(0);
        for (i = 0; i <= 10; i++) {
            fn_1_243B0();
            temp_f31 = fn_1_24204(lbl_1_data_36C[temp_r23][0], lbl_1_data_36C[var_r30][0], i, 10.0f);
            var_f30 = fn_1_24204(lbl_1_data_36C[temp_r22][1], lbl_1_data_36C[var_r29][1], i, 10.0f);
            HuSprPosSet(temp_r27, 24 + arg1->unk58, temp_f31, var_f30);
            HuSprPosSet(temp_r27, 28 + arg1->unk58, temp_f31, var_f30);
            HuSprPosSet(temp_r27, 32 + arg1->unk58, temp_f31, 35.0f + var_f30);
            HuSprPosSet(temp_r27, 36 + arg1->unk58, 1.0f + temp_f31, 37.0f + var_f30);
        }
    }
}

void fn_1_1E608(StructBss8_24 *arg0)
{
    s32 temp_r30;
    s32 i;

    temp_r30 = lbl_1_bss_2050.unk30;
    while (TRUE) {
        for (i = 0; i < 4; i++) {
            if (i != arg0->unk58 && lbl_1_bss_1E10[i].unk70[0] == 1 && arg0->unk68 == lbl_1_bss_1E10[i].unk68) {
                arg0->unk68++;
                break;
            }
        }
        if (i == 4) {
            break;
        }
    };
    arg0->unk64 = 0;
    HuSprBankSet(temp_r30, arg0->unk68, 0);
    HuSprBankSet(temp_r30, 24 + arg0->unk58, 0);
    HuSprBankSet(temp_r30, 28 + arg0->unk58, 0);
    HuSprBankSet(temp_r30, 32 + arg0->unk58, arg0->unk64);
    HuSprBankSet(temp_r30, 49 + arg0->unk58, arg0->unk64);
    HuSprPosSet(temp_r30, 24 + arg0->unk58, lbl_1_data_36C[arg0->unk68 % 4][0], lbl_1_data_36C[arg0->unk68 / 4][1]);
    HuSprPosSet(temp_r30, 28 + arg0->unk58, lbl_1_data_36C[arg0->unk68 % 4][0], lbl_1_data_36C[arg0->unk68 / 4][1]);
    HuSprPosSet(temp_r30, 32 + arg0->unk58, lbl_1_data_36C[arg0->unk68 % 4][0], lbl_1_data_36C[arg0->unk68 / 4][1] + 35);
    HuSprPosSet(temp_r30, 36 + arg0->unk58, lbl_1_data_36C[arg0->unk68 % 4][0] + 1, lbl_1_data_36C[arg0->unk68 / 4][1] + 37);
    HuSprPosSet(temp_r30, 49 + arg0->unk58, lbl_1_data_36C[arg0->unk68 % 4][0] + 1, lbl_1_data_36C[arg0->unk68 / 4][1] + 37);
    arg0->unk70[2] = 0;
    HuSprAttrReset(temp_r30, 24 + arg0->unk58, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(temp_r30, 28 + arg0->unk58, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(temp_r30, 32 + arg0->unk58, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(temp_r30, 36 + arg0->unk58, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(temp_r30, 49 + arg0->unk58, HUSPR_ATTR_DISPOFF);
}

void fn_1_1EB20(StructBss8_24 *arg0)
{
    s32 temp_r30;

    temp_r30 = lbl_1_bss_2050.unk30;
    HuSprBankSet(temp_r30, arg0->unk68, 0);
    HuSprAttrSet(temp_r30, 24 + arg0->unk58, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(temp_r30, 28 + arg0->unk58, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(temp_r30, 32 + arg0->unk58, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(temp_r30, 36 + arg0->unk58, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(temp_r30, 49 + arg0->unk58, HUSPR_ATTR_DISPOFF);
}

void fn_1_1EBE8(void)
{
    s32 temp_r30;
    s32 i;

    temp_r30 = lbl_1_bss_2050.unk30;
    HuSprPosSet(temp_r30, 54, lbl_1_data_3CC[3], lbl_1_data_3CC[2]);
    HuSprPosSet(temp_r30, 55, lbl_1_data_3CC[4], lbl_1_data_3CC[2]);
    for (i = 0; i < 2; i++) {
        HuSprAttrReset(temp_r30, 54 + i, HUSPR_ATTR_DISPOFF);
    }
}

void fn_1_1ED20(void)
{
    s32 temp_r30;
    s32 i;

    temp_r30 = lbl_1_bss_2050.unk30;
    HuSprPosSet(temp_r30, 54, lbl_1_data_3CC[3], lbl_1_data_3CC[2]);
    HuSprPosSet(temp_r30, 55, lbl_1_data_3CC[4], lbl_1_data_3CC[2]);
    for (i = 0; i < 2; i++) {
        HuSprAttrSet(temp_r30, 54 + i, HUSPR_ATTR_DISPOFF);
    }
}

void fn_1_1EE58(s32 arg0, UnkFunc1EE58Struct *arg1)
{
    float var_f31;
    float var_f30;
    s32 temp_r29;
    s32 var_r28;
    s32 sp8;
    s32 i;

    temp_r29 = arg1->unk30;
    var_r28 = 0;
    sp8 = arg1->unk08;
    lbl_1_bss_2050.unk1C[3] = 0;
    arg1->unk08 = 1;
    if (HuPadStkX[lbl_1_bss_1E10->unk6C] >= 5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 2)) {
        var_r28 = 1;
        arg1->unk1C++;
        if (arg1->unk1C > 2) {
            arg1->unk1C = 0;
        }
    }
    else if (HuPadStkX[lbl_1_bss_1E10->unk6C] <= -5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 1)) {
        var_r28 = -1;
        arg1->unk1C--;
        if (arg1->unk1C < 0) {
            arg1->unk1C = 2;
        }
    }
    if (var_r28 != 0) {
        lbl_1_bss_2050.unk1C[3] = 1;
        HuAudFXPlay(0);
        for (i = 0; i <= 10; i++) {
            fn_1_243B0();
            if (i <= 5) {
                var_f31 = fn_1_24204(0.0f, 10.0f, i, 5.0f);
                var_f30 = fn_1_24204(1.0f, 0.0f, i, 5.0f);
            }
            else {
                var_f31 = fn_1_24204(10.0f, 0.0f, i - 5, 5.0f);
                var_f30 = fn_1_24204(0.0f, 1.0f, i - 5, 5.0f);
            }
            if (var_r28 == 1) {
                HuSprPosSet(temp_r29, 55, lbl_1_data_3CC[4] + var_f31, lbl_1_data_3CC[2]);
                HuSprPosSet(temp_r29, 56, 380.0f + var_f31, lbl_1_data_3CC[2]);
            }
            else {
                HuSprPosSet(temp_r29, 54, lbl_1_data_3CC[3] - var_f31, lbl_1_data_3CC[2]);
                HuSprPosSet(temp_r29, 56, 380.0f - var_f31, lbl_1_data_3CC[2]);
            }
            HuSprScaleSet(temp_r29, 56, 1.0f, var_f30);
            if (i == 6) {
                HuSprBankSet(temp_r29, 56, arg1->unk1C);
            }
        }
    }
    lbl_1_bss_2050.unk1C[3] = 0;
}

void fn_1_1F32C(omObjData *arg0)
{
    float var_f31;
    float var_f30;
    s32 temp_r29;
    s32 var_r28;
    s32 var_r27;
    s32 j;
    s32 i;

    var_r27 = 0;
    temp_r29 = lbl_1_bss_2050.unk30;
    lbl_1_bss_2050.unk1C[3] = 0;
    var_r28 = lbl_1_bss_2050.unk1C[0] - var_r27;
    if (var_r28 > 3) {
        var_r28 = 0;
    }
    else if (var_r28 < 0) {
        var_r28 = 3;
    }
    if (HuPadStkX[lbl_1_bss_1E10->unk6C] >= 5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 2)) {
        var_r27 = 1;
        lbl_1_bss_2050.unk1C[3] = 1;
        HuAudFXPlay(0);
        lbl_1_bss_2050.unk1C[0]++;
        if (lbl_1_bss_2050.unk1C[0] > 3) {
            lbl_1_bss_2050.unk1C[0] = 1;
        }
    }
    else if (HuPadStkX[lbl_1_bss_1E10->unk6C] <= -5 || (HuPadBtn[lbl_1_bss_1E10->unk6C] & 1)) {
        var_r27 = -1;
        lbl_1_bss_2050.unk1C[3] = 1;
        HuAudFXPlay(0);
        lbl_1_bss_2050.unk1C[0]--;
        if (lbl_1_bss_2050.unk1C[0] < 1) {
            lbl_1_bss_2050.unk1C[0] = 3;
        }
    }
    if (var_r27 != 0) {
        for (i = 0; i <= 10; i++) {
            fn_1_243B0();
            if (i <= 5) {
                var_f31 = fn_1_24204(0.0f, 10.0f, i, 5.0f);
                var_f30 = fn_1_24204(1.0f, 0.0f, i, 5.0f);
            }
            else {
                var_f31 = fn_1_24204(10.0f, 0.0f, i - 5, 5.0f);
                var_f30 = fn_1_24204(0.0f, 1.0f, i - 5, 5.0f);
            }
            if (var_r27 == 1) {
                HuSprPosSet(temp_r29, 55, lbl_1_data_3CC[1] + var_f31, lbl_1_data_3CC[2]);
            }
            else {
                HuSprPosSet(temp_r29, 54, lbl_1_data_3CC[0] - var_f31, lbl_1_data_3CC[2]);
            }
            if (lbl_1_bss_2050.unk1C[0] != 0) {
                var_f30 = fn_1_24204(0.0f, 1.0f, i, 10.0f);
            }
            else {
                var_f30 = fn_1_24204(1.0f, 0.0f, i, 10.0f);
            }
            HuSprScaleSet(temp_r29, 85, var_f30, var_f30);
            for (j = 0; j < 4; j++) {
                var_f31 = fn_1_24204(
                    lbl_1_data_448[lbl_1_bss_1E10[j].unk58][var_r28], lbl_1_data_448[lbl_1_bss_1E10[j].unk58][lbl_1_bss_2050.unk1C[0]], i, 10.0f);
                HuSprPosSet(temp_r29, 57 + lbl_1_bss_1E10[j].unk68, var_f31, lbl_1_data_3CC[2]);
                HuSprPosSet(temp_r29, 65 + j, var_f31 + 1.0f, lbl_1_data_3CC[2] + 2);
                if (lbl_1_bss_1E10[j].unk60 != 0) {
                    HuSprPosSet(temp_r29, 77 + j, var_f31, lbl_1_data_3CC[2] + 21);
                }
                else {
                    HuSprPosSet(temp_r29, 73 + j, var_f31 - 8.0f, lbl_1_data_3CC[2] - 21);
                }
            }
        }
    }
    lbl_1_bss_2050.unk1C[3] = 0;
}

void fn_1_1FABC(void)
{
    s32 temp_r30;
    s32 i;

    temp_r30 = lbl_1_bss_2050.unk30;
    for (i = 0; i < 4; i++) {
        HuSprAttrSet(temp_r30, 77 + i, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(temp_r30, 73 + i, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(temp_r30, 57 + lbl_1_bss_1E10[i].unk68, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(temp_r30, 85, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(temp_r30, 65 + lbl_1_bss_1E10[i].unk58, HUSPR_ATTR_DISPOFF);
        HuSprScaleSet(temp_r30, 77 + i, 0.0f, 0.0f);
        HuSprScaleSet(temp_r30, 73 + i, 0.0f, 0.0f);
        HuSprScaleSet(temp_r30, 57 + lbl_1_bss_1E10[i].unk68, 0.0f, 0.0f);
        HuSprScaleSet(temp_r30, 81 + i, 1.0f, 1.0f);
    }
}

void fn_1_1FC44(s32 arg0)
{
    float var_f31;
    float var_f30;
    s32 temp_r30;
    s32 var_r27;
    s32 i;
    s32 j;

    temp_r30 = lbl_1_bss_2050.unk30;
    if (arg0 == 2) {
        for (i = 0; i < 2; i++) {
            HuSprAttrSet(temp_r30, 54 + i, HUSPR_ATTR_DISPOFF);
        }
        return;
    }
    for (i = 0; i < 4; i++) {
        HuSprAttrReset(temp_r30, 57 + lbl_1_bss_1E10[i].unk68, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(temp_r30, 57 + lbl_1_bss_1E10[i].unk68, lbl_1_data_3E4[lbl_1_bss_1E10[i].unk58][0], lbl_1_data_3CC[2]);
        if (arg0 == 0) {
            HuSprScaleSet(temp_r30, 57 + lbl_1_bss_1E10[i].unk68, 0.0f, 1.0f);
        }
        else {
            HuSprScaleSet(temp_r30, 57 + lbl_1_bss_1E10[i].unk68, 1.0f, 1.0f);
        }
        if (lbl_1_bss_1E10[i].unk60 != 0) {
            HuSprAttrReset(temp_r30, 77 + i, HUSPR_ATTR_DISPOFF);
            HuSprBankSet(temp_r30, 77 + i, lbl_1_bss_1E10[i].unk64);
            HuSprPosSet(temp_r30, 77 + i, lbl_1_data_3E4[lbl_1_bss_1E10[i].unk58][0], lbl_1_data_3CC[2] + 21);
            if (arg0 == 0) {
                HuSprScaleSet(temp_r30, 77 + i, 0.0f, 1.0f);
            }
            else {
                HuSprScaleSet(temp_r30, 77 + i, 1.0f, 1.0f);
            }
        }
        else {
            HuSprAttrReset(temp_r30, 73 + i, HUSPR_ATTR_DISPOFF);
            HuSprBankSet(temp_r30, 73 + i, lbl_1_bss_1E10[i].unk58);
            HuSprPosSet(temp_r30, 73 + i, lbl_1_data_3E4[lbl_1_bss_1E10[i].unk58][0] - 8.0f, lbl_1_data_3CC[2] - 21);
            if (arg0 == 0) {
                HuSprScaleSet(temp_r30, 73 + i, 0.0f, 1.0f);
            }
            else {
                HuSprScaleSet(temp_r30, 73 + i, 1.0f, 1.0f);
            }
        }
    }
    HuSprAttrReset(temp_r30, 85, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(temp_r30, 85, 340.0f, lbl_1_data_3CC[2]);
    HuSprScaleSet(temp_r30, 85, 0.0f, 0.0f);
    if (arg0 == 0) {
        lbl_1_bss_2050.unk1C[0] = 1;
        var_r27 = 0;
    }
    else {
        var_r27 = lbl_1_bss_2050.unk1C[0];
        lbl_1_bss_2050.unk1C[0] = 0;
    }
    for (i = 0; i <= 10; i++) {
        if (i <= 5) {
            var_f31 = fn_1_24204(1.0f, 0.0f, i, 5.0f);
        }
        else {
            var_f31 = fn_1_24204(0.0f, 1.0f, i - 5, 5.0f);
        }
        for (j = 0; j < 4; j++) {
            HuSprScaleSet(temp_r30, 65 + j, var_f31, 1.0f);
            if ((i > 5 && arg0 == 0) || (i <= 5 && arg0 == 1)) {
                HuSprScaleSet(temp_r30, 57 + lbl_1_bss_1E10[j].unk68, var_f31, 1.0f);
                if (lbl_1_bss_1E10[j].unk60 != 0) {
                    HuSprScaleSet(temp_r30, 77 + j, var_f31, 1.0f);
                }
                else {
                    HuSprScaleSet(temp_r30, 73 + j, var_f31, 1.0f);
                }
            }
            else {
                HuSprScaleSet(temp_r30, 81 + j, var_f31, 1.0f);
            }
            var_f30 = fn_1_24204(
                lbl_1_data_448[lbl_1_bss_1E10[j].unk58][var_r27], lbl_1_data_448[lbl_1_bss_1E10[j].unk58][lbl_1_bss_2050.unk1C[0]], i, 10.0f);
            HuSprPosSet(temp_r30, 57 + lbl_1_bss_1E10[j].unk68, var_f30, lbl_1_data_3CC[2]);
            HuSprPosSet(temp_r30, 65 + j, var_f30 + 1.0f, lbl_1_data_3CC[2] + 2);
            if (lbl_1_bss_1E10[j].unk60 != 0) {
                HuSprPosSet(temp_r30, 77 + j, var_f30, lbl_1_data_3CC[2] + 21);
            }
            else {
                HuSprPosSet(temp_r30, 73 + j, var_f30 - 8.0f, lbl_1_data_3CC[2] - 21);
            }
        }
        if (lbl_1_bss_2050.unk1C[0] != 0) {
            var_f31 = fn_1_24204(0.0f, 1.0f, i, 10.0f);
        }
        else {
            var_f31 = fn_1_24204(1.0f, 0.0f, i, 10.0f);
        }
        HuSprScaleSet(temp_r30, 85, var_f31, var_f31);
        fn_1_243B0();
    }
    HuSprPosSet(temp_r30, 54, lbl_1_data_3CC[0], lbl_1_data_3CC[2]);
    HuSprPosSet(temp_r30, 55, lbl_1_data_3CC[1], lbl_1_data_3CC[2]);
    if (arg0 == 0) {
        for (i = 0; i < 2; i++) {
            HuSprAttrReset(temp_r30, 54 + i, HUSPR_ATTR_DISPOFF);
        }
    }
    else {
        for (i = 0; i < 2; i++) {
            HuSprAttrSet(temp_r30, 54 + i, HUSPR_ATTR_DISPOFF);
        }
    }
}

void fn_1_20728(void)
{
    fn_1_1A6A0();
}

s32 fn_1_20970(void)
{
    s32 var_r23;
    s32 temp_r26;
    s32 temp_r28;
    s32 var_r24;
    s32 var_r29;
    s32 var_r30;
    s32 var_r25;
    s32 temp_r27;
    s32 i;

    var_r23 = 0;
    temp_r26 = fn_1_2530C(0, 0, 0);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk18, 0xF, 1);
    fn_1_25838(temp_r26, MAKE_MESSID(26, 5), -1, -1);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk10, 0xF, 1);
    fn_1_243B0();
    fn_1_25CA8(MAKE_MESSID(26, 33));
    temp_r28 = lbl_1_bss_2050.unk34;
    HuSprAttrReset(temp_r28, 8, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(temp_r28, 8, lbl_1_data_32C[0][0] - 50, lbl_1_data_32C[0][1]);
    HuSprAttrReset(temp_r28, 9, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(temp_r28, 9, lbl_1_data_32C[3][0] + 50, lbl_1_data_32C[0][1]);
    lbl_1_bss_2050.unk04 = (void *)fn_1_19F5C;
    var_r24 = 99;
    var_r23 = 0;
    while (TRUE) {
        fn_1_243B0();
        var_r30 = 0;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1E10[i].unk70[3] == 0) {
                var_r30++;
            }
        }
        if (var_r24 != var_r30) {
            var_r24 = var_r30;
            fn_1_25838(temp_r26, MAKE_MESSID(26, 27 + var_r30), -1, -999);
        }
        if (lbl_1_bss_2050.unk1C[0] != 0) {
            continue;
        }
        if (HuPadBtnDown[lbl_1_bss_1E10->unk6C] & 0x100) {
            var_r29 = 1;
            HuAudFXPlay(2);
            lbl_1_bss_2050.unk04 = NULL;
            fn_1_24388(2);
            var_r30 = var_r25 = 0;
            for (i = 0; i < 4; i++) {
                if (lbl_1_bss_1E10[i].unk60 == 0) {
                    var_r25++;
                }
            }
            for (i = 0; i < 4; i++) {
                if (var_r30 < var_r25) {
                    if (HuPadStatGet(i) != -1) {
                        var_r30++;
                        lbl_1_bss_1E10[i].unk60 = 0;
                    }
                    else {
                        lbl_1_bss_1E10[i].unk60 = 1;
                    }
                }
            }
            break;
        }
        else if (HuPadBtnDown[lbl_1_bss_1E10->unk6C] & 0x200) {
            var_r29 = -99;
            HuAudFXPlay(3);
            break;
        }
    }
    temp_r27 = lbl_1_bss_2050.unk34;
    HuSprAttrSet(temp_r27, 8, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(temp_r27, 8, lbl_1_data_32C[0][0] - 50, lbl_1_data_32C[0][1]);
    HuSprAttrSet(temp_r27, 9, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(temp_r27, 9, lbl_1_data_32C[3][0] + 50, lbl_1_data_32C[0][1]);
    lbl_1_bss_2050.unk04 = NULL;
    fn_1_25E74(0);
    fn_1_25584(temp_r26);
    if (var_r29 != -99) {
        var_r30 = 0;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1E10[i].unk60 == 0) {
                var_r30++;
            }
        }
        if (var_r30 == 0) {
            var_r29 = 2;
        }
        else {
            var_r29 = 1;
        }
    }
    return var_r29;
}

void fn_1_20E84(s32 arg0)
{
    float var_f31;
    s32 sp10;
    s32 spC;
    s32 temp_r30;
    s32 i;

    spC = 0;
    sp10 = 0;
    temp_r30 = lbl_1_bss_2050.unk34;
    for (i = 0; i <= 60; i++) {
        fn_1_243B0();
        if (i <= 10) {
            var_f31 = fn_1_24204(2.06f, 10.0f, i, 10.0f);
        }
        else {
            var_f31 = fn_1_2412C(10.0f, -500.0f, i - 10, 50.0f);
        }
        HuSprGrpPosSet(temp_r30, 0.0f, var_f31);
    }
    fn_1_1B260(0);
    fn_1_1CB4C();
    fn_1_1B260(arg0);
}

void fn_1_20FD4(s32 arg0)
{
    fn_1_1BCEC();
}

s32 fn_1_211B4(void)
{
    s32 var_r27;
    s32 sp8;
    s32 var_r29;
    s32 var_r28;
    s32 var_r30;
    s32 i;

    var_r27 = 0;
    sp8 = 0;
    fn_1_1CB4C();
    var_r28 = fn_1_2530C(0, 0, 0);
    HuWinPushKeySet(var_r28, 0x300);
    fn_1_243B0();
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk18, 0xF, 1);
    fn_1_25838(var_r28, MAKE_MESSID(26, 9), -1, -1);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk10, 0xF, 1);
    fn_1_25CA8(MAKE_MESSID(26, 32));
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_1E10[i].unk60 == 0) {
            lbl_1_bss_1E10[i].unk4 = (void *)fn_1_1CEB0;
        }
    }
    while (TRUE) {
        fn_1_243B0();
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1E10[i].unk60 == 0 && (HuPadBtnDown[lbl_1_bss_1E10[i].unk6C] & 0x100)) {
                var_r27 = 1;
            }
        }
        if (lbl_1_bss_1E10->unk70[0] == 0 && (HuPadBtnDown[lbl_1_bss_1E10->unk6C] & 0x200)) {
            HuAudFXPlay(3);
            var_r30 = 0;
            break;
        }
        else {
            for (i = 0; i < 4; i++) {
                if (lbl_1_bss_1E10[i].unk60 == 0 && lbl_1_bss_1E10[i].unk70[0] != 1) {
                    break;
                }
            }
            if (i == 4) {
                var_r30 = 2;
                break;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_1E10[i].unk4 = NULL;
    }
    fn_1_25E74(0);
    fn_1_25584(var_r28);
    if (var_r30 == 2) {
        var_r29 = 0;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1E10[i].unk60 != 0) {
                lbl_1_bss_1E10[i].unk68 = 0;
                var_r29++;
            }
        }
        if (var_r29 == 0) {
            var_r30 = 3;
        }
        else {
            var_r30 = 2;
        }
    }
    else {
        var_r30 = 0;
    }
    return var_r30;
}

s32 fn_1_214A4(void)
{
    s32 var_r30;
    s32 var_r24;
    s32 var_r23;
    s32 var_r21;
    s32 sp8;
    s32 temp_r22;
    s32 var_r28;
    s32 var_r29;
    s32 i;

    var_r30 = -1;
    var_r24 = -1;
    var_r23 = -1;
    var_r21 = -1;
    sp8 = 0;
    temp_r22 = fn_1_2530C(0, 0, 0);
    while (TRUE) {
        fn_1_243B0();
        var_r28 = 0;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1E10[i].unk60 != 0 && lbl_1_bss_1E10[i].unk70[0] == 0) {
                var_r28++;
            }
        }
        HuWinInsertMesSet(temp_r22, MAKE_MESSID(26, 35 + var_r28), 1);
        if (var_r23 == -1) {
            fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk18, 0xF, 1);
        }
        fn_1_25838(temp_r22, MAKE_MESSID(26, 40), -1, var_r23);
        if (var_r23 == -1) {
            fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk10, 0xF, 1);
        }
        var_r23 = -999;
        fn_1_25CA8(MAKE_MESSID(26, 32));
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1E10[i].unk60 != 0 && lbl_1_bss_1E10[i].unk70[0] == 0) {
                var_r30 = i;
                lbl_1_bss_1E10[i].unk70[1] = var_r24;
                fn_1_1E608(&lbl_1_bss_1E10[i]);
                lbl_1_bss_1E10[i].unk4 = (void *)fn_1_1DD74;
                break;
            }
        }
        while (TRUE) {
            fn_1_243B0();
            if ((HuPadBtnDown[lbl_1_bss_1E10->unk6C] & 0x200) && lbl_1_bss_1E10[var_r30].unk70[0] == 0) {
                HuAudFXPlay(3);
                if (var_r24 == -1) {
                    var_r29 = 0;
                    break;
                }
                else {
                    var_r29 = 1;
                    break;
                }
            }
            else if (lbl_1_bss_1E10[var_r30].unk70[0] == 1) {
                for (i = 0; i < 4; i++) {
                    if (lbl_1_bss_1E10[i].unk70[0] == 0) {
                        lbl_1_bss_1E10[i].unk68 = 0;
                    }
                }
                lbl_1_bss_1E10[var_r30].unk4 = NULL;
                fn_1_25838(temp_r22, MAKE_MESSID(26, 34), -1, -999);
                fn_1_25CA8(MAKE_MESSID(26, 35));
                var_r29 = fn_1_1D688(&lbl_1_bss_1E10[var_r30]);
                if (var_r29 == 1) {
                    lbl_1_bss_1E10[var_r30].unk70[2] = 1;
                    var_r29 = 4;
                    var_r24 = var_r30;
                }
                else {
                    lbl_1_bss_1E10[var_r30].unk70[2] = 0;
                    var_r29 = 4;
                    lbl_1_bss_1E10[var_r30].unk70[0] = 0;
                    fn_1_1EB20(&lbl_1_bss_1E10[var_r30]);
                    fn_1_1E608(&lbl_1_bss_1E10[var_r30]);
                }
                break;
            }
        }
        for (i = 0; i < 4; i++) {
            lbl_1_bss_1E10[i].unk4 = NULL;
        }
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1E10[i].unk70[0] == 0) {
                break;
            }
        }
        if (i == 4) {
            var_r29 = 3;
            break;
        }
        else {
            if (var_r29 == 1) {
                fn_1_1E608(&lbl_1_bss_1E10[var_r30]);
                fn_1_1EB20(&lbl_1_bss_1E10[var_r30]);
                fn_1_1E608(&lbl_1_bss_1E10[lbl_1_bss_1E10[var_r30].unk70[1]]);
                var_r24 = lbl_1_bss_1E10[lbl_1_bss_1E10[var_r30].unk70[1]].unk70[1];
                lbl_1_bss_1E10[lbl_1_bss_1E10[var_r30].unk70[1]].unk70[0] = 0;
            }
            else if (var_r29 != 4) {
                if (var_r29 == 0) {
                    fn_1_1EB20(&lbl_1_bss_1E10[var_r30]);
                }
                break;
            }
        }
        var_r21 = -1;
    }
    fn_1_25E74(0);
    fn_1_25584(temp_r22);
    if (var_r29 == 0) {
        var_r28 = 0;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1E10[i].unk60 == 0) {
                var_r28++;
            }
        }
        if (var_r28 != 0) {
            var_r29 = 1;
        }
        else {
            var_r29 = 0;
        }
    }
    return var_r29;
}

s32 fn_1_21CA4(void)
{
    s32 sp8;
    s32 temp_r27;
    s32 var_r22;
    s32 var_r28;
    s32 i;
    s32 j;

    sp8 = 0;
    temp_r27 = fn_1_2530C(0, 0, 0);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk18, 0xF, 1);
    fn_1_25838(temp_r27, MAKE_MESSID(40, 14), -1, -1);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk10, 0xF, 1);
    fn_1_243B0();
    fn_1_25CA8(MAKE_MESSID(26, 33));
    fn_1_1EBE8();
    lbl_1_bss_2050.unk04 = (void *)fn_1_1EE58;
    var_r22 = 99;
    while (TRUE) {
        fn_1_243B0();
        if (var_r22 != lbl_1_bss_2050.unk1C[0]) {
            var_r22 = lbl_1_bss_2050.unk1C[0];
            HuWinInsertMesSet(temp_r27, MAKE_MESSID(27, 52 + lbl_1_bss_2050.unk1C[0]), 0);
            fn_1_25838(temp_r27, MAKE_MESSID(27, 51), -1, -999);
        }
        if (lbl_1_bss_2050.unk1C[3] != 0) {
            continue;
        }
        if (HuPadBtnDown[lbl_1_bss_1E10->unk6C] & 0x100) {
            var_r28 = 5;
            HuAudFXPlay(2);
            break;
        }
        else if (HuPadBtnDown[lbl_1_bss_1E10->unk6C] & 0x200) {
            var_r28 = -99;
            HuAudFXPlay(3);
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (lbl_1_bss_1E10[i].unk60 == 1) {
                        lbl_1_bss_1E10[i].unk70[j] = 0;
                        lbl_1_bss_1E10[i].unk80[j] = 0;
                        fn_1_1EB20(&lbl_1_bss_1E10[i]);
                        lbl_1_bss_1E10[i].unk68 = 0;
                    }
                }
            }
            break;
        }
    }
    fn_1_1ED20();
    lbl_1_bss_2050.unk04 = NULL;
    fn_1_25E74(0);
    fn_1_25584(temp_r27);
    if (var_r28 == -99) {
        j = 0;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1E10[i].unk60 == 1) {
                j++;
            }
        }
        if (j == 0) {
            var_r28 = 1;
        }
        else {
            var_r28 = 2;
        }
    }
    return var_r28;
}

s32 fn_1_2228C(s32 arg0)
{
    s32 sp8;
    s32 temp_r30;
    s32 var_r26;
    s32 var_r27;
    s32 i;
    s32 j;

    sp8 = 0;
    temp_r30 = fn_1_2530C(0, 0, 0);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk18, 0xF, 1);
    fn_1_25838(temp_r30, MAKE_MESSID(40, 13), -1, -1);
    fn_1_25EC8(lbl_1_bss_3C4->unkC, lbl_1_bss_3C4->unk10, 0xF, 1);
    fn_1_243B0();
    fn_1_25CA8(MAKE_MESSID(26, 33));
    fn_1_1FC44(0);
    lbl_1_bss_2050.unk04 = (void *)fn_1_1F32C;
    var_r26 = 99;
    while (TRUE) {
        fn_1_243B0();
        if (var_r26 != lbl_1_bss_2050.unk1C[0]) {
            var_r26 = lbl_1_bss_2050.unk1C[0];
            switch (lbl_1_bss_2050.unk1C[0]) {
                case 1:
                    HuWinInsertMesSet(temp_r30, MAKE_MESSID(27, 30), 0);
                    HuWinInsertMesSet(temp_r30, MAKE_MESSID(27, 31), 1);
                    HuWinInsertMesSet(temp_r30, MAKE_MESSID(27, 32), 2);
                    break;
                case 2:
                    HuWinInsertMesSet(temp_r30, MAKE_MESSID(27, 31), 0);
                    HuWinInsertMesSet(temp_r30, MAKE_MESSID(27, 30), 1);
                    HuWinInsertMesSet(temp_r30, MAKE_MESSID(27, 32), 2);
                    break;
                case 3:
                    HuWinInsertMesSet(temp_r30, MAKE_MESSID(27, 32), 0);
                    HuWinInsertMesSet(temp_r30, MAKE_MESSID(27, 30), 1);
                    HuWinInsertMesSet(temp_r30, MAKE_MESSID(27, 31), 2);
                    break;
            }
            fn_1_25838(temp_r30, MAKE_MESSID(27, 50), -1, -999);
        }
        if (lbl_1_bss_2050.unk1C[3] != 0) {
            continue;
        }
        if (HuPadBtnDown[lbl_1_bss_1E10->unk6C] & 0x100) {
            var_r27 = 5;
            HuAudFXPlay(2);
            break;
        }
        else if (HuPadBtnDown[lbl_1_bss_1E10->unk6C] & 0x200) {
            var_r27 = -99;
            HuAudFXPlay(3);
            fn_1_1FC44(1);
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    if (lbl_1_bss_1E10[i].unk60 == 1) {
                        lbl_1_bss_1E10[i].unk70[j] = 0;
                        lbl_1_bss_1E10[i].unk80[j] = 0;
                        fn_1_1EB20(&lbl_1_bss_1E10[i]);
                    }
                }
            }
            break;
        }
    }
    fn_1_1FC44(2);
    lbl_1_bss_2050.unk04 = NULL;
    fn_1_25E74(0);
    fn_1_25584(temp_r30);
    if (var_r27 == -99) {
        j = 0;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_1E10[i].unk60 == 1) {
                j++;
            }
        }
        if (j == 0) {
            var_r27 = 1;
        }
        else {
            var_r27 = 2;
        }
    }
    return var_r27;
}

void fn_1_22728(void)
{
    s32 i;
    s32 j;

    fn_1_1BECC();
    fn_1_1FABC();
    if (lbl_1_bss_3C4->unk1C == 0 || lbl_1_bss_3C4->unk1C == 3) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (lbl_1_bss_1E10[i].unk60 == 1) {
                    lbl_1_bss_1E10[i].unk70[j] = 0;
                    lbl_1_bss_1E10[i].unk80[j] = 0;
                    fn_1_1EB20(&lbl_1_bss_1E10[i]);
                }
            }
        }
    }
}

void fn_1_22C08(omObjData *arg0)
{
    float var_f31;
    s32 i;

    for (i = 1; i < 10; i++) {
        if (CZoom <= 1200.0f || lbl_1_bss_3CC[i].unk1C == -200.0f) {
            if (lbl_1_bss_3CC[i].unk1C >= -100.0f) {
                lbl_1_bss_3CC[i].unk00 = 0;
                lbl_1_bss_3CC[i].unk1C = -200.0f;
                lbl_1_bss_3CC[i].unk24 = -99.0f;
                lbl_1_bss_3CC[i].unk04 = rand8() + 180;
            }
            var_f31 = fn_1_2412C(lbl_1_bss_3CC[i].unk10, 1000.0f, lbl_1_bss_3CC[i].unk00++, lbl_1_bss_3CC[i].unk04);
            Hu3DData[arg0->model[i]].pos.y = fn_1_2410C(Hu3DData[arg0->model[i]].pos.y, var_f31, 30.0f);
            Hu3DData[arg0->model[i]].pos.x
                = fn_1_2410C(Hu3DData[arg0->model[i]].pos.x, lbl_1_bss_3CC[i].unk18 + Hu3DData[arg0->model[i]].pos.x, 5.0f);
        }
    }
    for (i = 10; i < 140; i++) {
        Hu3DData[arg0->model[i]].pos.y = fn_1_242CC(lbl_1_bss_3CC[i].unk10, lbl_1_bss_3CC[i].unk1C, lbl_1_bss_3CC[i].unk00++, lbl_1_bss_3CC[i].unk04);
        if (lbl_1_bss_3CC[i].unk00 >= lbl_1_bss_3CC[i].unk04) {
            lbl_1_bss_3CC[i].unk00 = 0;
        }
    }
    for (i = 10; i < 140; i++) {
        if (0.0f == lbl_1_bss_3CC[i].unk24 && lbl_1_bss_3CC[i].unk14 > CZoom - 400.0f && lbl_1_bss_3CC[i].unk0C < 200.0f
            && lbl_1_bss_3CC[i].unk0C > -200.0f) {
            if (0.0f >= lbl_1_bss_3CC[i].unk0C) {
                lbl_1_bss_3CC[i].unk24 = -300.0f;
            }
            else {
                lbl_1_bss_3CC[i].unk24 = 300.0f;
            }
        }
        if (-99.0f != lbl_1_bss_3CC[i].unk24) {
            Hu3DData[arg0->model[i]].pos.x = fn_1_2410C(Hu3DData[arg0->model[i]].pos.x, lbl_1_bss_3CC[i].unk0C + lbl_1_bss_3CC[i].unk24, 30.0f);
        }
    }
    if (arg0->work[0] == 1) {
        for (i = 10; i < 140; i++) {
            Hu3DModelAttrSet(arg0->model[i], HU3D_ATTR_DISPOFF);
        }
    }
}

void fn_1_231F0(omObjData *arg0)
{
    float temp_f31;
    float temp_f30;
    float temp_f29;
    s32 var_r28;
    s32 i;
    s32 j;

    arg0->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MGMODE, 141));
    arg0->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MGMODE, 142));
    arg0->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MGMODE, 143));
    arg0->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_MGMODE, 144));
    Hu3DModelLayerSet(arg0->model[1], 3);
    Hu3DModelLayerSet(arg0->model[2], 3);
    Hu3DModelLayerSet(arg0->model[3], 3);
    Hu3DModelLayerSet(arg0->model[4], 3);
    for (i = 5; i < 140; i++) {
        arg0->model[i] = Hu3DModelLink(arg0->model[rand8() % 4 + 1]);
    }
    for (i = 1; i < 10; i++) {
        var_r28 = 0;
        do {
            temp_f31 = Hu3DData[arg0->model[i]].pos.x = 50.0f + rand8();
            if (i % 2 != 0) {
                lbl_1_bss_3CC[i].unk0C = Hu3DData[arg0->model[i]].pos.x *= -1.0f;
            }
            temp_f30 = Hu3DData[arg0->model[i]].pos.y = 50.0f + rand8();
            temp_f29 = Hu3DData[arg0->model[i]].pos.z = 750.0f + i * 5;
            for (j = 1; j < 10; j++) {
                if (i != j && lbl_1_bss_3CC[j].unk08 == 1) {
                    temp_f31 = Hu3DData[arg0->model[i]].pos.x - Hu3DData[arg0->model[j]].pos.x;
                    temp_f30 = Hu3DData[arg0->model[i]].pos.y - Hu3DData[arg0->model[j]].pos.y;
                    temp_f29 = Hu3DData[arg0->model[i]].pos.z - Hu3DData[arg0->model[j]].pos.z;
                    if (sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30) <= 100.0f) {
                        break;
                    }
                }
            }
            var_r28++;
        } while (j != 10 && var_r28 < 50);
        lbl_1_bss_3CC[i].unk08 = 1;
        lbl_1_bss_3CC[i].unk0C = lbl_1_bss_3CC[i].unk18 = Hu3DData[arg0->model[i]].pos.x;
        lbl_1_bss_3CC[i].unk10 = lbl_1_bss_3CC[i].unk1C = Hu3DData[arg0->model[i]].pos.y;
        lbl_1_bss_3CC[i].unk14 = lbl_1_bss_3CC[i].unk20 = Hu3DData[arg0->model[i]].pos.z;
        lbl_1_bss_3CC[i].unk18 = 0.025f * lbl_1_bss_3CC[i].unk0C;
        Hu3DModelScaleSet(arg0->model[i], 0.5f, 0.5f, 0.5f);
        Hu3DModelLayerSet(arg0->model[i], 3);
    }
    for (i = 10; i < 140; i++) {
        var_r28 = 0;
        do {
            temp_f31 = Hu3DData[arg0->model[i]].pos.x = rand8() * 2;
            if (i % 2 != 0) {
                Hu3DData[arg0->model[i]].pos.x *= -1.0f;
            }
            temp_f30 = Hu3DData[arg0->model[i]].pos.y = rand8() * 2 + 125;
            temp_f29 = Hu3DData[arg0->model[i]].pos.z = 800.0f + i * 10;
            for (j = 10; j < 140; j++) {
                if (i != j && lbl_1_bss_3CC[j].unk08 == 1) {
                    temp_f31 = Hu3DData[arg0->model[i]].pos.x - Hu3DData[arg0->model[j]].pos.x;
                    temp_f30 = Hu3DData[arg0->model[i]].pos.y - Hu3DData[arg0->model[j]].pos.y;
                    temp_f29 = Hu3DData[arg0->model[i]].pos.z - Hu3DData[arg0->model[j]].pos.z;
                    if (sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30 + temp_f29 * temp_f29) <= 100.0f) {
                        break;
                    }
                }
            }
            var_r28++;
        } while (j != 140 && var_r28 < 50);
        lbl_1_bss_3CC[i].unk08 = 1;
        Hu3DModelLayerSet(arg0->model[i], 3);
        lbl_1_bss_3CC[i].unk0C = lbl_1_bss_3CC[i].unk18 = Hu3DData[arg0->model[i]].pos.x;
        lbl_1_bss_3CC[i].unk10 = lbl_1_bss_3CC[i].unk1C = Hu3DData[arg0->model[i]].pos.y;
        lbl_1_bss_3CC[i].unk14 = lbl_1_bss_3CC[i].unk20 = Hu3DData[arg0->model[i]].pos.z;
        if (rand8() % 2 == 0) {
            lbl_1_bss_3CC[i].unk18 += rand8() % 30;
        }
        else {
            lbl_1_bss_3CC[i].unk18 -= rand8() % 30;
        }
        lbl_1_bss_3CC[i].unk1C += rand8() % 30 + 10;
        if (rand8() % 2 == 0) {
            lbl_1_bss_3CC[i].unk20 += rand8() % 30;
        }
        else {
            lbl_1_bss_3CC[i].unk20 -= rand8() % 30;
        }
        lbl_1_bss_3CC[i].unk24 = lbl_1_bss_3CC[i].unk28 = lbl_1_bss_3CC[i].unk2C = 0.0f;
        lbl_1_bss_3CC[i].unk04 = 360 + (rand8() * 2) % 360;
        lbl_1_bss_3CC[i].unk00 = rand8();
    }
    for (i = 1; i < 140; i++) {
        Hu3DModelAttrSet(arg0->model[i], HU3D_ATTR_DISPOFF);
    }
    arg0->func = fn_1_22C08;
}

float fn_1_240E4(float arg0, float arg1, float arg2, float arg3)
{
    if (arg3 <= arg2) {
        return arg1;
    }
    return arg0 + (arg2 / arg3) * (arg1 - arg0);
}

float fn_1_2410C(float arg0, float arg1, float arg2)
{
    return (arg1 + arg0 * (arg2 - 1.0f)) / arg2;
}

float fn_1_2412C(float arg0, float arg1, float arg2, float arg3)
{
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * (1.0 - cosd((90.0f / arg3) * arg2));
}

float fn_1_24204(float arg0, float arg1, float arg2, float arg3)
{
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * sind((90.0f / arg3) * arg2);
}

float fn_1_242CC(float arg0, float arg1, float arg2, float arg3)
{
    if (arg2 >= arg3) {
        return arg0;
    }
    return arg0 + (arg1 - arg0) * sind((360.0f / arg3) * arg2);
}

void fn_1_24388(s32 arg0)
{
    HuPrcSleep(arg0);
}

void fn_1_243B0(void)
{
    HuPrcVSleep();
}

void fn_1_243D0(void)
{
    while (TRUE) {
        HuPrcVSleep();
    }
}

void fn_1_243E4(void)
{
    s32 var_r31;

    var_r31 = 0;
    var_r31 = Hu3DGLightCreate(0.0f, 700.0f, 1200.0f, 0.0f, -1.0f, 0.0f, 0xFF, 0xFF, 0xFF);
    Hu3DGLightPosAimSet(var_r31, 0.0f, 700.0f, 1200.0f, 0.0f, 0.0f, 640.0f);
    Hu3DGLightInfinitytSet(var_r31);
}

void fn_1_244C0(s32 arg0)
{
    Vec sp24 = { 0.0f, 3000.0f, 800.0f };
    Vec sp18 = { 0.0f, 0.0f, 640.0f };
    Vec spC = { 0.0f, 1.0f, 0.0f };

    if (arg0 == 3) {
        sp24.x = sp18.x = 1200.0f;
    }
    Hu3DShadowCreate(45.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&sp24, &spC, &sp18);
}

void fn_1_245A8(void)
{
    HuWinInit(1);
}

void fn_1_245CC(s32 arg0, float arg1, float arg2, s32 arg3)
{
    WindowData *temp_r29;
    float temp_f29;
    float temp_f28;
    float temp_f25;
    float temp_f24;
    float var_f31;
    float var_f30;
    float temp_f27;
    float temp_f26;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f20;
    s32 i;

    temp_r29 = &winData[arg0];
    temp_f29 = temp_r29->pos_x;
    temp_f28 = temp_r29->pos_y;
    temp_f25 = temp_r29->w;
    temp_f24 = temp_r29->h;
    var_f31 = temp_f29 + temp_f25 * arg1;
    temp_f27 = 4.0f / temp_f25;
    if (var_f31 + 4.0f - (temp_f29 + temp_f25) >= 0.0f) {
        var_f31 = temp_f29 + temp_f25 - 4.0f;
    }
    else {
        if (temp_f29 - (var_f31 - 2.0f) >= 0.0f) {
            var_f31 = temp_f29;
        }
        else {
            var_f31 = var_f31 - 2.0f;
        }
    }
    var_f30 = temp_f28 + temp_f24 * arg2;
    temp_f26 = 4.0f / temp_f24;
    if (var_f30 + 4.0f - (temp_f28 + temp_f24) >= 0.0f) {
        var_f30 = temp_f28 + temp_f24 - 4.0f;
    }
    else {
        if (temp_f28 - (var_f30 - 2.0f) >= 0.0f) {
            var_f30 = temp_f28;
        }
        else {
            var_f30 = var_f30 - 2.0f;
        }
    }
    if (arg3 != 0) {
        HuWinPosSet(arg0, var_f31, var_f30);
        HuWinScaleSet(arg0, temp_f27, temp_f26);
        var_f23 = var_f31;
        var_f21 = temp_f27;
        var_f22 = var_f30;
        var_f20 = temp_f26;
    }
    else {
        HuWinPosSet(arg0, temp_f29, temp_f28);
        HuWinScaleSet(arg0, 1.0f, 1.0f);
        var_f23 = temp_f29;
        var_f21 = 1.0f;
        var_f22 = temp_f28;
        var_f20 = 1.0f;
    }
    HuWinDispOn(arg0);
    for (i = 0; i <= 15; i++) {
        HuPrcVSleep();
        if (arg3 != 0) {
            if (i <= 10) {
                var_f23 = fn_1_24204(var_f31, temp_f29, i, 10.0f);
                var_f21 = fn_1_24204(temp_f27, 1.0f, i, 10.0f);
            }
            else {
                var_f22 = fn_1_24204(var_f30, temp_f28, i - 10, 5.0f);
                var_f20 = fn_1_24204(temp_f26, 1.0f, i - 10, 5.0f);
            }
        }
        else {
            if (i <= 10) {
                var_f22 = fn_1_24204(temp_f28, var_f30, i, 10.0f);
                var_f20 = fn_1_24204(1.0f, temp_f26, i, 10.0f);
            }
            else {
                var_f23 = fn_1_24204(temp_f29, var_f31, i - 10, 5.0f);
                var_f21 = fn_1_24204(1.0f, temp_f27, i - 10, 5.0f);
            }
        }
        HuWinPosSet(arg0, var_f23, var_f22);
        HuWinScaleSet(arg0, var_f21, var_f20);
    }
    if (arg3 != 0) {
        HuWinPosSet(arg0, temp_f29, temp_f28);
        HuWinScaleSet(arg0, 1.0f, 1.0f);
    }
    else {
        HuWinPosSet(arg0, var_f31, var_f30);
        HuWinScaleSet(arg0, temp_f27, temp_f26);
    }
    HuPrcVSleep();
}

s32 fn_1_25014(s32 arg0, s32 arg1, s32 arg2, s32 arg3, float arg4, float arg5, s32 arg6, s32 arg7, s32 arg8)
{
    float sp14[2];
    s32 temp_r30;

    if (arg6 % 2 == 0) {
        arg2 = arg2 * 21 + 16;
        arg3 = arg3 * 26 + 16;
        arg1 = 445.0f - arg3;
        switch (arg0) {
            case -1:
                arg0 = 16;
                break;
            case 0:
                arg0 = 1.0f + (576.0f - arg2) / 2;
                break;
            case 1:
                arg0 = 556.0f - arg2;
                break;
        }
    }
    else {
        HuWinMesMaxSizeGet(1, sp14, arg8);
        arg2 = sp14[0];
        arg3 = sp14[1];
        arg0 = 556.0f - arg2;
        arg1 = 445.0f - arg3;
    }
    temp_r30 = HuWinExCreateStyled(arg0, arg1, arg2, arg3, -1, 1);
    if (arg6 == 1) {
        HuWinAttrSet(temp_r30, 0x10);
    }
    HuWinMesPalSet(temp_r30, 7, 0, 0, 0);
    winData[temp_r30].active_pad = 1;
    fn_1_245CC(temp_r30, arg4, arg5, 1);
    return temp_r30;
}

s32 fn_1_2530C(s32 arg0, s32 arg1, s32 arg2)
{
    return fn_1_25014(arg0, 0, 21, 2, 0.5f, 0.5f, 0, 0, 0);
}

void fn_1_25524(s32 arg0, float arg1, float arg2)
{
    HuWinMesSet(arg0, MAKE_MESSID(37, 4));
    HuPrcVSleep();
    fn_1_245CC(arg0, arg1, arg2, 0);
    HuWinExCleanup(arg0);
}

void fn_1_25584(s32 arg0)
{
    fn_1_25524(arg0, 0.5f, 0.5f);
}

void fn_1_255EC(s32 arg0, s32 arg1)
{
    if (arg1 == -999 || arg1 == 0) {
        return;
    }
    if (arg1 == -1000) {
        do {
            HuPrcVSleep();
        } while (HuWinStatGet(arg0) == 1);
        return;
    }
    if (arg1 > 0) {
        HuPrcSleep(arg1);
        return;
    }
    HuWinComKeyReset();
    HuWinMesWait(arg0);
    HuWinComKeyReset();
}

void fn_1_2567C(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 i;
    s32 temp_r28;
    s32 var_r30;

    temp_r28 = 0;
    var_r30 = 0;
    temp_r28 = HuWinKeyWaitNumGet(arg1);
    if (arg2 == -1 || arg2 >= temp_r28 - 1) {
        arg2 = temp_r28 - 1;
    }
    HuWinComKeyReset();
    for (i = 0; i < temp_r28; i++) {
        var_r30 = 0;
        do {
            HuPrcVSleep();
        } while (HuWinStatGet(arg0) != 1);
        if (i == arg2) {
            HuWinAttrSet(arg0, 0x400);
            var_r30 = 1;
        }
        while (TRUE) {
            HuPrcVSleep();
            if (var_r30 != 0) {
                if (var_r30 == 1 && HuWinStatGet(arg0) != 1) {
                    var_r30 = 2;
                }
                else if (var_r30 == 2) {
                    HuPrcSleep(arg3);
                    HuWinAttrReset(arg0, 0x400);
                    HuWinKeyWaitEntry(arg0);
                    break;
                }
            }
            else if (HuWinStatGet(arg0) != 1) {
                break;
            }
        }
    }
    fn_1_255EC(arg0, -1); // The second arg could be any negative value different from -999 or -1000.
    HuWinComKeyReset();
}

s32 fn_1_257B0(s32 arg0)
{
    s32 temp_r31;

    HuWinComKeyReset();
    temp_r31 = HuWinChoiceGet(arg0, 0);
    HuWinComKeyReset();
    return temp_r31;
}

void fn_1_257F8(s32 arg0, s32 arg1, s32 arg2)
{
    HuWinInsertMesSet(arg0, arg1, arg2);
}

void fn_1_25838(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    if (arg3 == -999) {
        HuWinMesSpeedSet(arg0, 0);
    }
    else {
        HuWinMesSpeedSet(arg0, 1);
    }
    HuWinMesSet(arg0, arg1);
    if (arg2 == -1) {
        fn_1_255EC(arg0, arg3);
    }
    else {
        fn_1_2567C(arg0, arg1, arg2, arg3);
    }
}

s32 fn_1_2592C(s32 arg0, s32 arg1, s32 arg2)
{
    s32 var_r25;
    s32 temp_r27;

    var_r25 = 0;
    temp_r27 = fn_1_25014(0, 0, 0, 0, 0.5f, 0.5f, arg1, 0, arg0);
    HuWinMesSet(temp_r27, arg0);
    var_r25 = fn_1_257B0(temp_r27);
    fn_1_25524(temp_r27, 0.5f, 0.5f);
    return var_r25;
}

s32 fn_1_25CA8(s32 arg0)
{
    float sp8[2];
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    s32 var_r31;

    HuWinMesMaxSizeGet(1, sp8, arg0);
    temp_f31 = sp8[0];
    temp_f30 = sp8[1];
    temp_f29 = (576.0f - temp_f31) / 2;
    temp_f28 = 385.0f - temp_f30;
    if (lbl_1_data_488 == -1) {
        var_r31 = lbl_1_data_488 = HuWinExCreateStyled(temp_f29, temp_f28, temp_f31, temp_f30, -1, 1);
    }
    else {
        fn_1_25E74(lbl_1_data_488);
        var_r31 = lbl_1_data_488 = HuWinExCreateStyled(temp_f29, temp_f28, temp_f31, temp_f30, -1, 1);
    }
    HuWinBGTPLvlSet(lbl_1_data_488, 0.0f);
    HuWinMesSet(lbl_1_data_488, arg0);
    HuWinMesSpeedSet(lbl_1_data_488, 0);
    HuWinDispOn(lbl_1_data_488);
    return lbl_1_data_488;
}

void fn_1_25E74(s32 arg0)
{
    if (lbl_1_data_488 != -1) {
        HuWinExCleanup(lbl_1_data_488);
        lbl_1_data_488 = -1;
    }
}

void fn_1_25EC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    switch (arg3) {
        case 0:
            Hu3DMotionShiftSet(arg0, arg1, 0.0f, arg2, HU3D_MOTATTR_NONE);
            break;
        case 1:
            Hu3DMotionShiftSet(arg0, arg1, 0.0f, arg2, HU3D_MOTATTR_LOOP);
            break;
        case 2:
            Hu3DMotionShiftSet(arg0, arg1, 0.0f, arg2, HU3D_MOTATTR_PAUSE);
            break;
    }
}

void fn_1_26004(s32 arg0, Vec arg1, float arg2, float arg3, float arg4, s32 arg5, s32 arg6)
{
    Vec sp4C;
    Vec sp40;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    s32 var_r30;
    s32 var_r29;
    s32 i;

    var_r30 = 0;
    var_r29 = 0;
    sp40.x = Hu3DData[arg0].pos.x;
    sp40.y = Hu3DData[arg0].pos.y;
    sp40.z = Hu3DData[arg0].pos.z;
    sp34.x = arg1.x;
    sp34.y = arg1.y;
    sp34.z = arg1.z;
    sp1C.x = Hu3DData[arg0].rot.x;
    sp1C.y = Hu3DData[arg0].rot.y;
    sp1C.z = Hu3DData[arg0].rot.z;
    sp10.x = 0.0f;
    sp10.y = arg2;
    sp10.z = 0.0f;
    if (sp34.x - sp40.x >= 0.0f) {
        var_r30 = 1;
    }
    else {
        var_r30 = 0;
    }
    if (sp34.z - sp40.z >= 0.0f) {
        var_r29 = 1;
    }
    else {
        var_r29 = 0;
    }
    while (arg5 != 0) {
        HuPrcVSleep();
        sp28.y = -(atan2d(sp34.z - sp40.z, sp34.x - sp40.x) - 90.0);
        if (sp28.y < 0.0f) {
            sp28.y += 360.0f;
        }
        else if (sp28.y >= 360.0f) {
            sp28.y -= 360.0f;
        }
        if (arg6 != 0) {
            if (sp28.y >= 180.0f) {
                if (sp1C.y - sp28.y >= 180.0f) {
                    sp1C.y -= 360.0f;
                }
                if (sp1C.y - sp28.y < -180.0f) {
                    sp1C.y += 360.0f;
                }
            }
            else {
                if (sp1C.y - sp28.y > 180.0f) {
                    sp1C.y -= 360.0f;
                }
                if (sp1C.y - sp28.y <= -180.0f) {
                    sp1C.y += 360.0f;
                }
            }
        }
        sp4C.x = sp40.x += arg3 * sind(sp28.y);
        sp4C.z = sp40.z += arg3 * cosd(sp28.y);
        if (var_r30 == 1) {
            if (sp40.x >= sp34.x) {
                sp4C.x = sp40.x = sp34.x;
                var_r30 = 2;
            }
        }
        else if (var_r30 == 0) {
            if (sp40.x <= sp34.x) {
                sp4C.x = sp40.x = sp34.x;
                var_r30 = 2;
            }
        }
        if (var_r29 == 1) {
            if (sp40.z >= sp34.z) {
                sp4C.z = sp40.z = sp34.z;
                var_r29 = 2;
            }
        }
        else if (var_r29 == 0) {
            if (sp40.z <= sp34.z) {
                sp4C.z = sp40.z = sp34.z;
                var_r29 = 2;
            }
        }
        if (arg6 != 0) {
            sp1C.y = fn_1_2410C(sp1C.y, sp28.y, arg4);
        }
        Hu3DModelPosSet(arg0, sp4C.x, sp40.y, sp4C.z);
        Hu3DModelRotSet(arg0, sp1C.x, sp1C.y, sp1C.z);
        if (var_r30 == 2 && var_r29 == 2) {
            break;
        }
    }
    sp1C.y = Hu3DData[arg0].rot.y;
    if (arg6 != 0) {
        for (i = 0; i <= arg4; i++) {
            HuPrcVSleep();
            if (sp10.y >= 180.0f) {
                if (sp1C.y - sp10.y >= 180.0f) {
                    sp1C.y -= 360.0f;
                }
                if (sp1C.y - sp10.y < -180.0f) {
                    sp1C.y += 360.0f;
                }
            }
            else {
                if (sp1C.y - sp10.y > 180.0f) {
                    sp1C.y -= 360.0f;
                }
                if (sp1C.y - sp10.y <= -180.0f) {
                    sp1C.y += 360.0f;
                }
            }
            sp10.z = fn_1_240E4(sp1C.y, sp10.y, i, arg4);
            Hu3DModelRotSet(arg0, sp1C.x, sp10.z, sp1C.z);
        }
    }
}

void fn_1_26790(s32 arg0, s32 arg1, float arg2, float arg3)
{
    HuSprPosSet(arg0, arg1, arg2, arg3 + 0.5f);
}
