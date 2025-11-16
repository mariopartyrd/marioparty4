#include "game/audio.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/wipe.h"


#include "REL/m434Dll.h"
#include "ext_math.h"
#include "game/gamework_data.h"
#include "game/minigame_seq.h"
#include "math.h"
#include "version.h"


typedef struct bss_7480_struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    float unkC;
    float unk10;
    Vec unk14;
} Bss7480Struct;

omObjData *lbl_1_bss_7880;
Bss7480Struct lbl_1_bss_7480[32];
float lbl_1_bss_6480[1024];
u8 lbl_1_bss_6080[1024];
u16 lbl_1_bss_5880[1024];

s32 lbl_1_data_2C0[] = { 0x410005, 0x410006 };

void fn_1_6A88(omObjData *object);

void fn_1_6860(Process *objman)
{
    float temp_f31;
    Vec spC;
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    omObjData *temp_r28;
    for (temp_r31 = 0; temp_r31 < 32; temp_r31++) {
        lbl_1_bss_7480[temp_r31].unk4 = lbl_1_bss_7480[temp_r31].unk0 = 0;
        lbl_1_bss_7480[temp_r31].unkC = lbl_1_bss_7480[temp_r31].unk10 = 0;
        lbl_1_bss_7480[temp_r31].unk8 = -1;
    }
    spC.y = 0;
    spC.z = -650;
    for (temp_r31 = 0; temp_r31 < 32; temp_r31++) {
        temp_r30 = temp_r31 * 32;
        spC.x = -650.0f;
        for (temp_r29 = 0; temp_r29 < 32; temp_r29++, temp_r30++) {
            lbl_1_bss_6480[temp_r30] = 0;
            lbl_1_bss_6080[temp_r30] = 0;
            lbl_1_bss_5880[temp_r30] = 0;
            temp_f31 = VECMag(&spC);
            if (temp_f31 < 522.0f) {
                lbl_1_bss_6080[temp_r30] = 1;
            }
            spC.x += (1300.0f / 32.0f);
        }
        spC.z += (1300.0f / 32.0f);
    }
    temp_r28 = lbl_1_bss_7880 = omAddObjEx(objman, 30, 1, 0, -1, fn_1_6A88);
    temp_r28->work[0] = 0;
}

void fn_1_6A84(void) { }

typedef struct work_6A88 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    Vec unk1C;
    Vec unk28;
    Vec unk34;
    Vec unk40;
    float unk4C;
} Work6A88;

void fn_1_6D7C(ModelData *model, Mtx mtx);
void fn_1_6DB8(omObjData *object);

s32 fn_1_8254(s32 arg0, Vec *arg1);

void fn_1_6A88(omObjData *object)
{
    float temp_f31;
    float temp_f30;
    s16 sp8[2];
    Work6A88 *temp_r31;
    s32 temp_r30;
    s32 temp_r28;
    Work6A88 *temp_r27;
    temp_r27 = HuMemDirectMallocNum(HEAP_SYSTEM, 20 * sizeof(Work6A88), MEMORY_DEFAULT_NUM);
    object->data = temp_r27;
    memset(temp_r27, 0, 20 * sizeof(Work6A88));
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        sp8[temp_r30] = Hu3DModelCreateFile(lbl_1_data_2C0[temp_r30]);
    }
    temp_r31 = temp_r27;
    for (temp_r30 = 0; temp_r30 < 20; temp_r30++, temp_r31++) {
        temp_r28 = 0;
        if (temp_r30 >= 15) {
            temp_r28++;
        }
        temp_r31->unk0 = temp_r28 + 1;
        temp_r31->unk2 = Hu3DModelLink(sp8[temp_r28]);
        Hu3DModelCameraSet(temp_r31->unk2, 4);
        Hu3DModelLayerSet(temp_r31->unk2, 4);
        temp_f31 = frandmod(360);
        temp_f30 = frandmod(464);
        temp_r31->unk4C = temp_f31;
        temp_r31->unk1C.x = temp_f30 * sind(temp_f31);
        temp_r31->unk1C.y = -50.0f;
        temp_r31->unk1C.z = temp_f30 * cosd(temp_f31);
        temp_r31->unk34.z = frandmod(360);
        temp_r31->unk40.y = 1.0f;
        temp_r31->unk40.z = 0;
        temp_r31->unk10 = 1;
        temp_r31->unk14 = 0;
        temp_r31->unkE = -1;
        temp_r31->unkC = 0;
        temp_r31->unk18 = fn_1_8254(-1, &temp_r31->unk1C);
        temp_r31->unkA = 20;
    }
    for (temp_r30 = 0; temp_r30 < 2; temp_r30++) {
        if (sp8[temp_r30] > 0) {
            Hu3DModelKill(sp8[temp_r30]);
        }
    }
    object->work[1] = 140;
    object->model[0] = Hu3DHookFuncCreate(fn_1_6D7C);
    Hu3DModelCameraSet(object->model[0], 8);
    Hu3DModelLayerSet(object->model[0], 7);
    object->func = fn_1_6DB8;
}

void fn_1_6DBC(omObjData *object);

void fn_1_6D7C(ModelData *model, Mtx mtx)
{
    if (!omPauseChk()) {
        fn_1_6DBC(lbl_1_bss_7880);
    }
}

void fn_1_6DB8(omObjData *object) { }

void fn_1_7DF0(void);
s32 fn_1_84D0(Work6A88 *arg0);
void fn_1_85C4(Work6A88 *arg0, Vec *arg1);

void fn_1_6DBC(omObjData *object)
{
    Vec sp8;
    float temp_f31;
    float temp_f30;
    Work6A88 *temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    s32 temp_r24;
    Work6A88 *temp_r23;
    temp_r23 = object->data;
    fn_1_7DF0();
    if (object->work[1]) {
        object->work[1]--;
        return;
    }
    temp_r26 = 0;
    temp_r31 = temp_r23;
    for (temp_r27 = 0; temp_r27 < 20; temp_r27++, temp_r31++) {
        temp_r30 = 0;
        temp_r24 = 0;
        switch (temp_r31->unk4) {
            case 0:
                if (temp_r31->unkC == 0) {
                    temp_r24 = fn_1_84D0(temp_r31);
                    if (temp_r24) {
                        temp_r30 = 1;
                        temp_r31->unkC = 60;
                    }
                }
                else {
                    temp_r31->unkC--;
                }
                if (temp_r31->unkC == 0 && temp_r31->unk40.y > temp_r31->unk40.z) {
                    temp_r30 = 1;
                }
                else {
                    VECSubtract(&temp_r31->unk28, &temp_r31->unk1C, &sp8);
                    temp_f31 = VECMag(&sp8);
                    if (temp_f31 < 50.0f) {
                        temp_r30 = 1;
                    }
                }
                if (temp_r30) {
                    if (temp_r31->unkC == 0) {
                        temp_f31 = frandmod(1000);
                        temp_f30 = frandmod(1000);
                        if (temp_f31 > temp_f30) {
                            temp_f30 = temp_f31;
                        }
                        temp_f30 = 0.53f * temp_f30;
                        temp_f31 = temp_r31->unk4C + ((0.06f * frandmod(1000)) - 30);
                        temp_r31->unk4C = temp_f31;
                        temp_r31->unk28.x = temp_f30 * sind(temp_f31);
                        temp_r31->unk28.z = temp_f30 * cosd(temp_f31);
                    }
                    else {
                        fn_1_85C4(temp_r31, &temp_r31->unk28);
                    }
                    temp_r31->unk28.y = temp_r31->unk1C.y;
                    temp_r31->unk40.y = 0;
                    temp_r31->unk40.z = frandmod(200) + 100.0f;
                    temp_r31->unk34.y = 200;
                    if (temp_r31->unkC) {
                        temp_r31->unk34.y *= 2.0f;
                    }
                }
                VECSubtract(&temp_r31->unk28, &temp_r31->unk1C, &sp8);
                temp_r31->unk40.x = atan2d(sp8.x, sp8.z);
                if (temp_r31->unkC != 0) {
                    temp_r31->unk34.z = fn_1_6690(temp_r31->unk34.z, temp_r31->unk40.x, 0.15f);
                    temp_r31->unk4C = atan2d(temp_r31->unk28.x, temp_r31->unk28.z);
                }
                else {
                    temp_r31->unk34.z = fn_1_6690(temp_r31->unk34.z, temp_r31->unk40.x, 0.07f);
                }
                if (temp_r31->unkC != 0) {
                    temp_r31->unk34.y += (300.0f - temp_r31->unk34.y) * 0.02f;
                }
                else {
                    temp_r31->unk34.y += (75.0f - temp_r31->unk34.y) * 0.02f;
                }
                temp_r31->unk34.x += (temp_r31->unk34.y - temp_r31->unk34.x) * 0.2f;
                temp_r31->unk1C.x += sind(temp_r31->unk34.z) * ((1.0f / REFRESH_RATE) * temp_r31->unk34.x);
                temp_r31->unk1C.z += cosd(temp_r31->unk34.z) * ((1.0f / REFRESH_RATE) * temp_r31->unk34.x);
                temp_r31->unk40.y += (1.0f / REFRESH_RATE) * temp_r31->unk34.x;
                temp_r31->unk18 = fn_1_8254(temp_r31->unk18, &temp_r31->unk1C);
                Hu3DModelPosSetV(temp_r31->unk2, &temp_r31->unk1C);
                Hu3DModelRotSet(temp_r31->unk2, 0, temp_r31->unk34.z, 0);
                break;

            case 1:
                temp_r31->unk34.z += 1.0f / REFRESH_RATE * 180.0f;
                Hu3DModelPosSetV(temp_r31->unk2, &temp_r31->unk1C);
                Hu3DModelRotSet(temp_r31->unk2, 0, temp_r31->unk34.z, 0);
                if (fn_1_1D54() == 4) {
                    Hu3DModelAttrSet(temp_r31->unk2, HU3D_ATTR_DISPOFF);
                }
                break;

            case 2:
                if (temp_r31->unk14) {
                    if (temp_r31->unk8 == 0) {
                        sp8.x = (0.1f * frandmod(1000) + 500.0f) - 50.0f;
                        sp8.y = temp_r31->unk1C.y;
                        sp8.z = (0.1f * frandmod(1000) + 500.0f) - 50.0f;
                        if (temp_r31->unk1C.x < 0.0f) {
                            sp8.x = -sp8.x;
                        }
                        VECSubtract(&sp8, &temp_r31->unk1C, &sp8);
                        temp_r31->unk40.x = temp_r31->unk34.z = atan2d(sp8.x, sp8.z);
                        temp_r31->unk28.x = (1.0f / REFRESH_RATE) * sp8.x;
                        temp_r31->unk28.y = 400*(1.0f/REFRESH_RATE);
                        temp_r31->unk28.z = (1.0f / REFRESH_RATE) * sp8.z;
                        temp_r31->unk8++;
                        HuAudFXPlay(1734);
                    }
                    temp_r29 = 0;
                    if (temp_r31->unk1C.y <= -15.000001f) {
                        temp_r29 = 1;
                    }
                    temp_r31->unk28.y += -980*(1.0f/REFRESH_RATE)*(1.0f/REFRESH_RATE);
                    VECAdd(&temp_r31->unk1C, &temp_r31->unk28, &temp_r31->unk1C);
                    if (!temp_r29 && temp_r31->unk1C.y <= -15.000001f) {
                        fn_1_43AC(&temp_r31->unk1C);
                        if (temp_r31->unkE >= 0) {
                            omVibrate(temp_r31->unkE, 12, 6, 6);
                            temp_r31->unkE = -1;
                        }
                        HuAudFXPlay(1741);
                    }
                    sp8 = temp_r31->unk28;
                    sp8.y = 0;
                    temp_f31 = VECMag(&sp8);
                    temp_f31 = atan2d(temp_r31->unk28.y, temp_f31);
                    Hu3DModelPosSetV(temp_r31->unk2, &temp_r31->unk1C);
                    Hu3DModelRotSet(temp_r31->unk2, -temp_f31, temp_r31->unk34.z, 0);
                    if (temp_r31->unk1C.y <= -50.0) {
                        temp_r31->unk14 = 0;
                        temp_r31->unk40.z = 0;
                        temp_r31->unk40.y = 1;
                        temp_r31->unk4++;
                    }
                }

                break;

            case 3:
                if (temp_r31->unk40.y > temp_r31->unk40.z) {
                    temp_r30 = 1;
                }
                VECSubtract(&temp_r31->unk28, &temp_r31->unk1C, &sp8);
                temp_f31 = VECMag(&sp8);
                if (temp_f31 < 30.000002f) {
                    temp_r30 = 1;
                }
                if (temp_r30) {
                    temp_f31 = frandmod(360);
                    temp_f30 = (0.08f * frandmod(1000)) + 20;
                    temp_r31->unk28.x = temp_f30 * sind(temp_f31);
                    temp_r31->unk28.z = temp_f30 * cosd(temp_f31);
                    temp_r31->unk28.y = -50;
                    temp_r31->unk1C.y = temp_r31->unk28.y;
                    temp_r31->unk28.x += 480.00003f;
                    temp_r31->unk28.z += 480.00003f;
                    if (temp_r31->unk1C.x < 0.0f) {
                        temp_r31->unk28.x *= -1.0f;
                    }
                    temp_r31->unk40.y = 0;
                    temp_r31->unk40.z = frandmod(100) + 100.0f;
                    temp_r31->unk34.y = 100;
                    if (frandmod(100) < 5) {
                        temp_r31->unk4++;
                        temp_r31->unk8 = 0;
                        HuAudFXPlay(1740);
                    }
                }
                VECSubtract(&temp_r31->unk28, &temp_r31->unk1C, &sp8);
                temp_r31->unk40.x = atan2d(sp8.x, sp8.z);
                temp_r31->unk34.z = fn_1_6690(temp_r31->unk34.z, temp_r31->unk40.x, 0.07f);
                temp_r31->unk34.y += (50.0f - temp_r31->unk34.y) * 0.02f;
                temp_r31->unk34.x += (temp_r31->unk34.y - temp_r31->unk34.x) * 0.2f;
                temp_r31->unk1C.x += sind(temp_r31->unk34.z) * ((1.0f / REFRESH_RATE) * temp_r31->unk34.x);
                temp_r31->unk1C.z += cosd(temp_r31->unk34.z) * ((1.0f / REFRESH_RATE) * temp_r31->unk34.x);
                temp_r31->unk40.y += (1.0f / REFRESH_RATE) * temp_r31->unk34.x;
                Hu3DModelPosSetV(temp_r31->unk2, &temp_r31->unk1C);
                Hu3DModelRotSet(temp_r31->unk2, 0, temp_r31->unk34.z, 0);

                break;

            case 4:
                if (temp_r31->unk8 == 0) {
                    sp8.x = (0.1f * frandmod(1000) + 480.00003f) - 50.0f;
                    sp8.y = temp_r31->unk1C.y;
                    sp8.z = (0.1f * frandmod(1000) + 480.00003f) - 50.0f;
                    if (temp_r31->unk1C.x < 0) {
                        sp8.x = -sp8.x;
                    }
                    VECSubtract(&sp8, &temp_r31->unk1C, &sp8);
                    temp_r31->unk40.x = temp_r31->unk34.z = atan2d(sp8.x, sp8.z);
                    temp_r31->unk28.x = (1.0f / REFRESH_RATE) * sp8.x;
                    temp_r31->unk28.y = 400*(1.0f/REFRESH_RATE);
                    temp_r31->unk28.z = (1.0f / REFRESH_RATE) * sp8.z;
                    temp_r31->unk8++;
                }
                temp_r29 = temp_r25 = 0;
                if (temp_r31->unk1C.y <= -15.000001f) {
                    temp_r29 = 1;
                }
                temp_r31->unk28.y += -980*(1.0f/REFRESH_RATE)*(1.0f/REFRESH_RATE);
                VECAdd(&temp_r31->unk1C, &temp_r31->unk28, &temp_r31->unk1C);
                if (temp_r31->unk1C.y <= -15.000001f) {
                    temp_r25 = 1;
                }
                if (temp_r29 != temp_r25) {
                    fn_1_43AC(&temp_r31->unk1C);
                    if (temp_r31->unk28.y < 0.0f) {
                        HuAudFXPlay(1741);
                    }
                }
                sp8 = temp_r31->unk28;
                sp8.y = 0;
                temp_f31 = VECMag(&sp8);
                temp_f31 = atan2d(temp_r31->unk28.y * 0.3f, temp_f31);
                Hu3DModelPosSetV(temp_r31->unk2, &temp_r31->unk1C);
                Hu3DModelRotSet(temp_r31->unk2, -temp_f31, temp_r31->unk34.z, 0);
                if (temp_r31->unk1C.y <= -50.0) {
                    temp_r31->unk40.z = 0;
                    temp_r31->unk40.y = 1;
                    temp_r31->unk4--;
                }
                break;
        }
        if (temp_r31->unk4 < 2) {
            temp_r26++;
        }
    }
    if (temp_r26 == 0) {
        fn_1_1D9C();
    }
}

void fn_1_7DF0(void)
{
    Vec sp14;
    Vec sp8;
    float temp_f31;
    float temp_f30;

    Bss7480Struct *temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    s32 temp_r24;

    temp_r31 = lbl_1_bss_7480;
    temp_r31 = lbl_1_bss_7480;
    for (temp_r30 = 0; temp_r30 < 32; temp_r30++, temp_r31++) {
        if (temp_r31->unk0 == 0) {
            continue;
        }
        temp_r31->unk0--;
        if (temp_r31->unk4) {
            temp_r31->unk4--;
            temp_r31->unkC += (temp_r31->unk10 - temp_r31->unkC) * 0.2f;
        }
        else {
            if (temp_r31->unk0 < 100.0f) {
                temp_r31->unkC *= 0.98f;
            }
        }
    }
    for (temp_r30 = 0; temp_r30 < 1024; temp_r30++) {
        lbl_1_bss_6480[temp_r30] = 0;
    }
    temp_r31 = lbl_1_bss_7480;
    for (temp_r30 = 0; temp_r30 < 32; temp_r30++, temp_r31++) {
        if (temp_r31->unk0 == 0) {
            continue;
        }
        temp_r28 = (16.0f / 650.0f) * (650.0f + (temp_r31->unk14.x - temp_r31->unkC));
        temp_r25 = 1.0f + (temp_r28 + ((16.0f / 650.0f) * (2.0f * temp_r31->unkC)));
        temp_r29 = (16.0f / 650.0f) * (650.0f + (temp_r31->unk14.z - temp_r31->unkC));
        temp_r24 = 1.0f + (temp_r29 + ((16.0f / 650.0f) * (2.0f * temp_r31->unkC)));
        if (temp_r28 < 0) {
            temp_r28 = 0;
        }
        if (temp_r25 > 32) {
            temp_r25 = 32;
        }
        if (temp_r29 < 0) {
            temp_r29 = 0;
        }
        if (temp_r24 > 32) {
            temp_r24 = 32;
        }
        temp_f30 = 1.0f / temp_r31->unkC;
        sp14.y = 0;
        sp14.z = ((1300.0f / 32.0f) * temp_r29) - 650.0f;
        while (temp_r29 < temp_r24) {
            sp14.x = ((1300.0f / 32.0f) * temp_r28) - 650.0f;
            temp_r26 = temp_r28 + (32 * temp_r29);
            for (temp_r27 = temp_r28; temp_r27 < temp_r25; temp_r27++, temp_r26++) {
                VECSubtract(&temp_r31->unk14, &sp14, &sp8);
                temp_f31 = 1.0f - (temp_f30 * VECMag(&sp8));
                if (temp_f31 > 0.0f) {
                    lbl_1_bss_6480[temp_r26] += temp_f31;
                }
                sp14.x += (1300.0f / 32.0f);
            }
            sp14.z += (1300.0f / 32.0f);
            temp_r29++;
        }
    }
}

void fn_1_83C8(s32 arg0);

s32 fn_1_8254(s32 arg0, Vec *arg1)
{
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    s32 sp8[9][2] = { -1, -1, 0, -1, 1, -1, -1, 0, 0, 0, 1, 0, -1, 1, 0, 1, 1, 1 };
    fn_1_83C8(arg0);
    arg0 = -1;
    temp_r29 = (16.0f / 650.0f) * (650.0f + arg1->x);
    temp_r30 = (16.0f / 650.0f) * (650.0f + arg1->z);
    if (temp_r29 >= 0 && temp_r29 < 32 && temp_r30 >= 0 && temp_r30 < 32) {
        arg0 = temp_r29 + (32 * temp_r30);
        for (temp_r31 = 0; temp_r31 < 9; temp_r31++) {
            temp_r28 = temp_r29 + sp8[temp_r31][0];
            temp_r27 = temp_r30 + sp8[temp_r31][1];
            if (temp_r28 >= 0 && temp_r28 < 32 && temp_r27 >= 0 && temp_r27 < 32) {
                lbl_1_bss_5880[temp_r28 + (32 * temp_r27)]++;
            }
        }
    }
    return arg0;
}

void fn_1_83C8(s32 arg0)
{
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27;
    s32 sp8[9][2] = { -1, -1, 0, -1, 1, -1, -1, 0, 0, 0, 1, 0, -1, 1, 0, 1, 1, 1 };
    if (arg0 < 0 || arg0 >= 1024) {
        return;
    }
    temp_r28 = arg0 % 32;
    temp_r27 = (arg0 - temp_r28) / 32;
    for (temp_r31 = 0; temp_r31 < 9; temp_r31++) {
        temp_r30 = temp_r28 + sp8[temp_r31][0];
        temp_r29 = temp_r27 + sp8[temp_r31][1];
        if (temp_r30 >= 0 && temp_r30 < 32 && temp_r29 >= 0 && temp_r29 < 32) {
            lbl_1_bss_5880[temp_r30 + (32 * temp_r29)]--;
        }
    }
}

s32 fn_1_84D0(Work6A88 *arg0)
{
    float temp_f31;
    Vec spC;
    Bss7480Struct *temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    temp_r31 = lbl_1_bss_7480;
    temp_r28 = 0;
    temp_r31 = lbl_1_bss_7480;
    for (temp_r29 = 0; temp_r29 < 32; temp_r29++, temp_r31++) {
        if (temp_r31->unk0 == 0) {
            continue;
        }
        VECSubtract(&temp_r31->unk14, &arg0->unk1C, &spC);
        temp_f31 = 1.0f - (VECMag(&spC) / temp_r31->unkC);
        if (temp_f31 < 0.3f) {
            continue;
        }
        temp_r30 = 1;
        if (temp_r31->unk4) {
            temp_r30++;
        }
        if (temp_r28 < temp_r30) {
            temp_r28 = temp_r30;
        }
    }
    return temp_r28;
}

void fn_1_85C4(Work6A88 *arg0, Vec *arg1)
{
    Vec sp24;
    Vec sp18;
    Vec spC;
    float temp_f31;
    float temp_f30;
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    sp18.x = sp18.y = sp18.z = 0;
    temp_f30 = 5000;
    sp24.y = 0;
    sp24.z = -650;
    for (temp_r30 = 0; temp_r30 < 32; temp_r30++) {
        temp_r31 = 32 * temp_r30;
        sp24.x = -650;
        for (temp_r29 = 0; temp_r29 < 32; temp_r29++, temp_r31++) {
            if (lbl_1_bss_6480[temp_r31] < 0.15f && lbl_1_bss_6080[temp_r31]) {
                VECSubtract(&arg0->unk1C, &sp24, &spC);
                temp_f31 = VECMag(&spC);
                if (temp_f31 > 81.25f) {
                    temp_f31 += 162.5f * lbl_1_bss_5880[temp_r31];
                    if (temp_f31 < temp_f30) {
                        temp_f30 = temp_f31;
                        sp18 = sp24;
                    }
                }
            }
            sp24.x += (1300.0f / 32.0f);
        }
        sp24.z += (1300.0f / 32.0f);
    }
    sp18.x += ((1300.0f / 32000.0f) * frandmod(1000)) - (1300.0f / 64.0f);
    sp18.z += ((1300.0f / 32000.0f) * frandmod(1000)) - (1300.0f / 64.0f);
    *arg1 = sp18;
}

s32 fn_1_8884(Vec *arg0, float arg1, float arg2, float arg3, float arg4, float arg5, s32 arg6, s32 arg7)
{
    float temp_f31;
    float temp_f30;
    Vec sp24;
    Work6A88 *temp_r31;
    s32 temp_r30;
    s32 temp_r28;
    Work6A88 *temp_r23;
    temp_r23 = lbl_1_bss_7880->data;
    temp_r30 = -1;
    temp_r31 = temp_r23;
    for (temp_r28 = 0; temp_r28 < 20; temp_r28++, temp_r31++) {
        if (temp_r31->unk10 == 0) {
            continue;
        }
        VECSubtract(&temp_r31->unk1C, arg0, &sp24);
        temp_f30 = VECMag(&sp24);
        if (temp_f30 < arg1 || temp_f30 > arg2) {
            continue;
        }
        temp_f31 = atan2d(sp24.x, sp24.z);
        temp_f31 = fn_1_67AC(arg3, temp_f31);
        if (temp_f31 < arg4 || temp_f31 > arg5) {
            continue;
        }
        temp_r30++;
        if (arg6) {
            temp_r31->unk14 = 1;
            temp_r31->unk10 = 0;
            temp_r31->unk4 = 1;
            fn_1_83C8(temp_r31->unk18);
            temp_r31->unk18 = -1;
            temp_r31->unkE = arg7;
            HuAudFXPlay(1733);
            temp_r30 = temp_r28;
            break;
        }
    }
    if (!arg6) {
        temp_r30++;
    }
    return temp_r30;
}

void fn_1_8AEC(s16 arg0, Vec *arg1)
{
    Work6A88 *temp_r31;
    Work6A88 *temp_r30 = lbl_1_bss_7880->data;
    if (arg0 < 0 || arg0 >= 20) {
        return;
    }
    temp_r31 = &temp_r30[arg0];
    temp_r31->unk1C = *arg1;
}

void fn_1_8B58(s16 arg0)
{
    Work6A88 *temp_r31;
    s32 temp_r30;
    Work6A88 *temp_r28 = lbl_1_bss_7880->data;
    if (arg0 < 0 || arg0 >= 20) {
        return;
    }
    temp_r31 = &temp_r28[arg0];
    temp_r31->unk4 = 2;
    temp_r31->unk8 = 0;
    if (temp_r31->unk1C.x >= 0.0f) {
        temp_r30 = 1;
    }
    else {
        temp_r30 = 0;
    }
    fn_1_1C44(temp_r30, temp_r31->unk0);
}

void fn_1_8C14(s32 arg0, Vec *arg1, float arg2)
{
    Bss7480Struct *temp_r31;
    s32 temp_r30;
    temp_r31 = lbl_1_bss_7480;
    for (temp_r30 = 0; temp_r30 < 32; temp_r30++, temp_r31++) {
        if (temp_r31->unk0 && temp_r31->unk8 == arg0) {
            temp_r31->unk0 *= 0.8f;
        }
    }
    temp_r31 = lbl_1_bss_7480;
    for (temp_r30 = 0; temp_r30 < 32; temp_r30++, temp_r31++) {
        if (!temp_r31->unk0) {
            temp_r31->unk4 = 0.5 * REFRESH_RATE;
            temp_r31->unk0 = (REFRESH_RATE * (3.0f * arg2)) + 2.5f * REFRESH_RATE;
            temp_r31->unk8 = arg0;
            temp_r31->unk14 = *arg1;
            temp_r31->unkC = 0;
            temp_r31->unk10 = 150.0f + (250.0f * arg2);
            break;
        }
    }
}

s32 fn_1_8D78(Vec *arg0)
{
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r29 = -1;
    temp_r31 = (16.0f / 650.0f) * (670.3125f + arg0->x);
    temp_r30 = (16.0f / 650.0f) * (670.3125f + arg0->z);
    if (temp_r31 >= 0 && temp_r31 < 32 && temp_r30 >= 0 && temp_r30 < 32) {
        temp_r29 = temp_r31 + (32 * temp_r30);
    }
    return temp_r29;
}

s32 fn_1_8E2C(s32 arg0, Vec *arg1)
{
    s32 temp_r31;
    s32 temp_r30;
    if (arg0 < 0 || arg0 >= 1024) {
        arg1->x = arg1->y = arg1->z = 0;
        return 0;
    }
    temp_r31 = arg0 % 32;
    temp_r30 = (arg0 - temp_r31) / 32;
    arg1->x = ((1300.0f / 32.0f) * temp_r31) - 670.3125f;
    arg1->y = 0;
    arg1->z = ((1300.0f / 32.0f) * temp_r30) - 670.3125f;
    return 1;
}

s32 fn_1_8F3C(s32 arg0)
{
    s32 sp8[9][2] = { -1, -1, 0, -1, 1, -1, -1, 0, 0, 0, 1, 0, -1, 1, 0, 1, 1, 1 };
    if (arg0 < 0 || arg0 >= 1024) {
        return 0;
    }
    return lbl_1_bss_5880[arg0];
}

s32 fn_1_8FA0(Vec *arg0)
{
    s32 sp24[9][2] = { -1, -1, 0, -1, 1, -1, -1, 0, 0, 0, 1, 0, -1, 1, 0, 1, 1, 1 };
    Vec sp18;
    Vec spC;
    s32 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r27 = -1;
    float temp_f31;
    float temp_f30 = 5000;
    sp18.y = 0;
    sp18.z = -650;
    for (temp_r31 = 0; temp_r31 < 32; temp_r31++) {
        temp_r30 = temp_r31 * 32;
        sp18.x = -650;
        for (temp_r29 = 0; temp_r29 < 32; temp_r29++, temp_r30++) {
            temp_r28 = lbl_1_bss_5880[temp_r30];
            if (temp_r28 > 0) {
                VECSubtract(arg0, &sp18, &spC);
                temp_f31 = VECMag(&spC) + (0.2f * frandmod(1000));
                temp_f31 -= 50.0f * temp_r28;
                if (temp_f31 < temp_f30) {
                    temp_f30 = temp_f31;
                    temp_r27 = temp_r30;
                }
            }
            sp18.x += (1300.0f / 32.0f);
        }
        sp18.z += (1300.0f / 32.0f);
    }
    return temp_r27;
}
