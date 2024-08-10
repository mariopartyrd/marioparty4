#include "ext_math.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/sprite.h"

#include "REL/m410Dll.h"

typedef void (*lbl_1_bss_44_type)(u16, u16, u16);

omObjData *lbl_1_bss_5C;
omObjData *lbl_1_bss_58;
omObjData *lbl_1_bss_54;
float lbl_1_bss_50;
float lbl_1_bss_4C;
float lbl_1_bss_48;
lbl_1_bss_44_type lbl_1_bss_44;
Process *lbl_1_bss_40;
s32 lbl_1_bss_3C;
s32 lbl_1_bss_38;
s32 lbl_1_bss_34;
s32 lbl_1_bss_30;

s16 lbl_1_data_D8 = 0x0384;
s32 lbl_1_data_DC[]
    = { DATA_MAKE_NUM(DATADIR_M410, 0), DATA_MAKE_NUM(DATADIR_M410, 1), DATA_MAKE_NUM(DATADIR_M410, 2), DATA_MAKE_NUM(DATADIR_M410, 3),
          DATA_MAKE_NUM(DATADIR_M410, 4), DATA_MAKE_NUM(DATADIR_M410, 5), DATA_MAKE_NUM(DATADIR_M410, 6), DATA_MAKE_NUM(DATADIR_M410, 7) };

void fn_1_34C0(omObjData *object);
void fn_1_3614(omObjData *object);
void fn_1_3BE0(s16 arg0);
float fn_1_48D8(UnkM410Struct2 *arg0, u8 *arg1);
float fn_1_4C04(Vec arg0, Vec arg1, float arg8, Vec arg2, Vec arg3, float arg9);
float fn_1_4FEC(Vec arg0, Vec arg1, float arg8, Vec arg2, Vec arg3, float arg9, float argA);
float fn_1_55C8(Vec arg0, Vec arg1, float arg8, Vec arg2, float arg9);
s32 fn_1_598C(Vec *arg0, Vec *arg1, float arg8, Vec *arg2, Vec *arg3, float arg9, float argA);
void fn_1_5AF4(UnkM410Struct2 *arg0, u8 arg1);
void fn_1_5CA0(Vec arg0, Vec arg1, Vec arg2, Vec *arg3, Vec *arg4);
void fn_1_61DC(UnkM410Struct2 *arg0, UnkM410Struct2 *arg1);
void fn_1_6364(UnkM410Struct2 *arg0, UnkM410Struct2 *arg1);
void fn_1_66B8(UnkM410Struct2 *arg0, UnkM410Struct2 *arg1);
void fn_1_67D4(omObjData *object);
void fn_1_6968(omObjData *object);
void fn_1_6D84(omObjData *object);
void fn_1_6DB4(omObjData *object);
void fn_1_7138(omObjData *object);
void fn_1_7464(omObjData *object);
void fn_1_7494(void);
void fn_1_7520(Vec *arg0);
void fn_1_75A0(ModelData *model, ParticleData *particle, Mtx matrix);

void fn_1_33A8(Process *objman)
{
    lbl_1_bss_5C = omAddObjEx(objman, 3, 3, 0, -1, fn_1_34C0);
    lbl_1_bss_54 = omAddObjEx(objman, 5, 54, 3, -1, fn_1_6DB4);
    lbl_1_bss_58 = omAddObjEx(objman, 7, 60, 0, -1, fn_1_67D4);
    lbl_1_bss_44 = NULL;
    lbl_1_bss_40 = objman;
    lbl_1_bss_3C = 300;
    fn_1_7494();
}

void fn_1_3484(void)
{
    fn_1_6D84(lbl_1_bss_58);
    fn_1_7464(lbl_1_bss_54);
}

void fn_1_34C0(omObjData *object)
{
    s32 var_r30;

    object->stat |= 0x100;
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        if (!var_r30) {
            object->model[var_r30] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M410, 12));
        } else {
            object->model[var_r30] = Hu3DModelLink(*object->model);
        }
        Hu3DModelPosSet(object->model[var_r30], 0.0f, 140.0f + (140.0f * var_r30), -790.0f);
    }
    object->func = fn_1_3614;
    Hu3DLayerHookSet(7, fn_1_3BE0);
    lbl_1_bss_50 = lbl_1_bss_4C = lbl_1_bss_48 = 0.0f;
}

void fn_1_3614(omObjData *object)
{
    float var_f31;
    float var_f30;
    float var_f29;
    ModelData *var_r30;
    s32 var_r29;
    s16 var_r28;

    switch (object->work[0]) {
    case 0:
        if (fn_1_2804() == 1) {
            object->work[0]++;
            object->work[1] = 256;
        }
        break;
    case 1:
        if (!--object->work[1]) {
            object->work[0]++;
            object->work[1] = 90;
            lbl_1_bss_50 = 0.0f;
            lbl_1_bss_4C = -10.000001f;
            lbl_1_bss_48 = 2.0000002f;
            lbl_1_bss_34 = HuAudFXPlay(1381);
        }
        break;
    case 2:
        if (!--object->work[1]) {
            object->work[0]++;
            lbl_1_bss_4C = 0.0f;
            lbl_1_bss_48 = 0.40000007f;
        }
        break;
    case 3:
        if (fn_1_281C() == 2) {
            object->work[0]++;
            lbl_1_bss_4C = -2.0000002f;
            lbl_1_bss_48 = 0.05000001f;
        }
        break;
    }
    if (fn_1_281C() == 2) {
        if (!--lbl_1_data_D8) {
            lbl_1_bss_4C = -lbl_1_bss_4C;
            lbl_1_data_D8 = 900;
        }
    } else if (fn_1_281C() > 2) {
        lbl_1_bss_4C = 0.0f;
    }
    if (lbl_1_bss_50 != lbl_1_bss_4C) {
        if (lbl_1_bss_50 < lbl_1_bss_4C) {
            lbl_1_bss_50 += lbl_1_bss_48;
            if (lbl_1_bss_50 > lbl_1_bss_4C) {
                lbl_1_bss_50 = lbl_1_bss_4C;
            }
        } else {
            lbl_1_bss_50 -= lbl_1_bss_48;
            if (lbl_1_bss_50 < lbl_1_bss_4C) {
                lbl_1_bss_50 = lbl_1_bss_4C;
            }
        }
    }
    if (lbl_1_bss_34 >= 0) {
        var_r28 = 512.0 * fabs(lbl_1_bss_50);
        if (var_r28 > 127) {
            var_r28 = 127;
        }
        HuAudFXVolSet(lbl_1_bss_34, var_r28);
        var_f31 = (0.5 * (16384.0 * fabs(lbl_1_bss_50))) - 8191.0;
        if (var_f31 < -8191.0f) {
            var_f31 = -8191.0f;
        } else if (var_f31 > 8191.0f) {
            var_f31 = 8191.0f;
        }
        HuAudFXPitchSet(lbl_1_bss_34, var_f31);
    }

    for (var_r29 = 0; var_r29 < 3; var_r29++) {
        var_r30 = &Hu3DData[object->model[var_r29]];
        if (var_r29 & 1) {
            var_f29 = lbl_1_bss_50;
        } else {
            var_f29 = -lbl_1_bss_50;
        }
        var_f30 = var_f29;
        var_r30->pos.x += var_f30;
        if (var_f30 < 0.0) {
            if (var_r30->pos.x <= -40.0f) {
                var_r30->pos.x += 40.0f;
            }
        } else {
            if (var_r30->pos.x >= 40.0f) {
                var_r30->pos.x -= 40.0f;
            }
        }
    }
}

void fn_1_3BE0(s16 arg0) // what happens with the argument?
{
    UnkM410Struct4 sp1B0[128]; // TODO get size right
    UnkM410Struct2 *spC0[60]; // TODO get size right
    Vec spB4;
    Vec spA8;

    u8 sp8;

    f32 var_f31;
    f32 var_f30;
    f32 var_f29;

    UnkM410Struct2 *var_r31;
    UnkM410Struct2 *var_r30;
    s32 var_r29;
    UnkM410Struct2 *var_r28;
    u8 var_r27;
    s32 var_r26;
    s32 var_r25;
    s32 var_r24;
    omObjData *var_r23;
    omObjData **var_r22;

    var_r24 = 0;
    if (omPauseChk()) {
		
        return;
    }

    for (var_r25 = 0, var_r31 = lbl_1_bss_58->data, var_r29 = 0; var_r29 < 60; var_r29++, var_r31++) {
        if (var_r31->unk_00_field0) {
            spC0[var_r25++] = var_r31;
            var_r31->unk_10 = var_r31->unk_04;
        }
    }
    for (var_r29 = 0; var_r29 < var_r25; var_r29++) {
        var_r31 = spC0[var_r29];
        var_r31->unk_00_field5 = 0;
        var_r31->unk_40 = 0;
        var_r31->unk_3C = 0;
    }
    for (var_r31 = lbl_1_bss_54->data, var_r29 = 0; var_r29 < 18; var_r29++, var_r31++) {
        var_r31->unk_40 = 0;
        var_r31->unk_10 = var_r31->unk_04;
    }
    var_f30 = 1.0f;
    do {
        for (var_r27 = 0, var_f29 = var_f30, var_r29 = 0; var_r29 < var_r25; var_r29++) {
            var_r30 = spC0[var_r29];
            if (var_r30->unk_00_field5) {
                continue;
            }
            if (var_r30->unk_3C >= 8) {
                var_r30->unk_1C.x = var_r30->unk_1C.y = var_r30->unk_1C.z = 0.0f;
                continue;
            }
            var_r30->unk_00_field5 = 1;
            if (!var_r30->unk_00_field1) {
                var_f31 = fn_1_48D8(var_r30, &sp8);
                if (var_f31 >= 0.0f && var_f31 < var_f30) {
                    var_r30->unk_00_field5 = 0;
                    if (var_f31 <= var_f29) {
                        if (var_f31 < var_f29) {
                            var_r27 = 0;
                        }
                        sp1B0[var_r27].unk_00 = 0;
                        sp1B0[var_r27].unk_08 = var_r30;
                        sp1B0[var_r27].unk_04 = sp8;
                        var_r27++;
                        var_f29 = var_f31;
                        if (!var_r30->unk_00_field3 && (sp8 & 2) && var_r30->unk_1C.y < 0.0f) {
                            var_r30->unk_00_field3 = 1;
                            var_r30->unk_36 = 240;
                        }
                    }
                }
            }

            for (var_r26 = 0; var_r26 < var_r25; var_r26++) {
                var_r28 = spC0[var_r26];
                if (var_r30 != var_r28 && (var_r30->unk_40 != var_r28 || var_r28->unk_40 != var_r30)
                    && !(var_r30->unk_00_field3 ^ var_r28->unk_00_field3)) {
                    var_f31 = fn_1_4C04(var_r30->unk_04, var_r30->unk_1C, var_r30->unk_28, var_r28->unk_04, var_r28->unk_1C, var_r28->unk_28);
                    if (var_f31 >= 0.0f && var_f31 < var_f30) {
                        var_r30->unk_00_field5 = 0;
                        if (var_f31 <= var_f29) {
                            if (var_f31 < var_f29) {
                                var_r27 = 0;
                            }
                            sp1B0[var_r27].unk_00 = 1;
                            sp1B0[var_r27].unk_08 = var_r30;
                            sp1B0[var_r27].unk_0C_unk = var_r28;
                            var_r27++;
                            var_f29 = var_f31;
                        }
                    }
                }
            }
            var_r22 = omGetGroupMemberListEx(lbl_1_bss_40, 0);
            for (var_r26 = 0; var_r26 < 4; var_r26++) {
                var_r23 = var_r22[var_r26];
                if (var_r30->unk_40 != var_r23 && var_r30->unk_00_field3) {
                    var_f31 = fn_1_55C8(var_r30->unk_04, var_r30->unk_1C, var_r30->unk_28, var_r23->trans, 30.000002f);
                    if (var_f31 >= 0.0f && var_f31 < var_f30) {
                        var_r30->unk_00_field5 = 0;
                        if (var_f31 <= var_f29) {
                            if (var_f31 < var_f29) {
                                var_r27 = 0;
                            }
                            sp1B0[var_r27].unk_00 = 2;
                            sp1B0[var_r27].unk_08 = var_r30;
                            sp1B0[var_r27].unk_0C_obj = var_r23;
                            var_r27++;
                            var_f29 = var_f31;
                        }
                    }
                }
            }
            if (!var_r30->unk_00_field3) {
                var_r28 = lbl_1_bss_54->data;

                for (var_r26 = 0; var_r26 < 18; var_r26++, var_r28++) {
                    if (var_r30->unk_40 != var_r28 || var_r28->unk_40 != var_r30) {
                        var_f31 = fn_1_4FEC(var_r30->unk_04, var_r30->unk_1C, var_r30->unk_28, var_r28->unk_04, var_r28->unk_1C, var_r28->unk_28, var_r28->unk_2C);
                        if (var_f31 >= 0.0f && var_f31 < var_f30) {
                            var_r30->unk_00_field5 = 0;
                            if (var_f31 <= var_f29) {
                                if (var_f31 < var_f29) {
                                    var_r27 = 0;
                                }
                                sp1B0[var_r27].unk_00 = 3;
                                sp1B0[var_r27].unk_08 = var_r30;
                                sp1B0[var_r27].unk_0C_unk = var_r28;
                                var_r27++;
                                var_f29 = var_f31;
                            }
                        }
                    }
                }
            }
        }
        if (!var_r27) {
            break;
        }
        for (var_r29 = 0; var_r29 < var_r25; var_r29++) {
            var_r31 = spC0[var_r29];
            var_r31->unk_04.x += var_r31->unk_1C.x * var_f29 * var_f30;
            var_r31->unk_04.y += var_r31->unk_1C.y * var_f29 * var_f30;
            var_r31->unk_04.z += var_r31->unk_1C.z * var_f29 * var_f30;
        }
        var_r31 = lbl_1_bss_54->data;

        for (var_r29 = 0; var_r29 < 18; var_r29++, var_r31++) {
            var_r31->unk_04.x += var_r31->unk_1C.x * var_f29 * var_f30;
            var_r31->unk_04.y += var_r31->unk_1C.y * var_f29 * var_f30;
            var_r31->unk_04.z += var_r31->unk_1C.z * var_f29 * var_f30;
        }
        for (var_r29 = 0; var_r29 < var_r27; var_r29++) {
            switch (sp1B0[var_r29].unk_00) {
            case 0:
                fn_1_5AF4(sp1B0[var_r29].unk_08, sp1B0[var_r29].unk_04);
                sp1B0[var_r29].unk_08->unk_40 = NULL;
                sp1B0[var_r29].unk_08->unk_3C++;
                break;
            case 1:
                fn_1_61DC(sp1B0[var_r29].unk_08, sp1B0[var_r29].unk_0C_unk);
                sp1B0[var_r29].unk_08->unk_40 = sp1B0[var_r29].unk_0C_unk;
                sp1B0[var_r29].unk_0C_unk->unk_40 = sp1B0[var_r29].unk_08;
                sp1B0[var_r29].unk_08->unk_3C++;
                sp1B0[var_r29].unk_0C_unk->unk_3C++;
                break;
            case 2:
                fn_1_66B8(sp1B0[var_r29].unk_08, sp1B0[var_r29].unk_0C_unk);
                sp1B0[var_r29].unk_08->unk_40 = sp1B0[var_r29].unk_0C_unk;
                sp1B0[var_r29].unk_08->unk_3C++;
                break;
            case 3:
                fn_1_6364(sp1B0[var_r29].unk_08, sp1B0[var_r29].unk_0C_unk);
                sp1B0[var_r29].unk_08->unk_40 = sp1B0[var_r29].unk_0C_unk;
                sp1B0[var_r29].unk_0C_unk->unk_40 = sp1B0[var_r29].unk_08;
                sp1B0[var_r29].unk_08->unk_3C++;
                sp1B0[var_r29].unk_08->unk_44 = 2;
                if (VECMag(&sp1B0[var_r29].unk_08->unk_1C) > 10.0f) {
                    HuAudFXPlay(1377);
                }
                break;
            }
        }
        var_f30 *= 1.0f - var_f29;
        var_r24++;
    } while (var_r24 < 100);
	(void)var_r24;
	
    for (var_r29 = 0; var_r29 < var_r25; var_r29++) {
        var_r31 = spC0[var_r29];
        var_r31->unk_04.x += var_r31->unk_1C.x * var_f30;
        var_r31->unk_04.y += var_r31->unk_1C.y * var_f30;
        var_r31->unk_04.z += var_r31->unk_1C.z * var_f30;
    }
    var_r31 = lbl_1_bss_54->data;

    for (var_r29 = 0; var_r29 < 18; var_r29++, var_r31++) {
        var_r31->unk_04.x += var_r31->unk_1C.x * var_f30;
        var_r31->unk_04.y += var_r31->unk_1C.y * var_f30;
        var_r31->unk_04.z += var_r31->unk_1C.z * var_f30;
    }
    for (var_r29 = 0; var_r29 < var_r25; var_r29++) {
        var_r30 = spC0[var_r29];
        VECSubtract(&var_r30->unk_04, &var_r30->unk_10, &spB4);
        var_r28 = lbl_1_bss_54->data;

        for (var_r26 = 0; var_r26 < 18; var_r26++, var_r28++) {
            VECSubtract(&var_r28->unk_04, &var_r28->unk_10, &spA8);
            if (fn_1_598C(&var_r30->unk_10, &spB4, var_r30->unk_28, &var_r28->unk_10, &spA8, var_r28->unk_28, var_r28->unk_2C)
                && !var_r30->unk_00_field1 && var_r28->unk_38 == NULL) {
                var_r30->unk_00_field1 = 1;
                var_r30->unk_38 = var_r28;
                var_r30->unk_36 = 10;
                var_r28->unk_00_field4 = 1;
                var_r28->unk_38 = var_r30;
                if (lbl_1_bss_44 != NULL) {
                    lbl_1_bss_44(var_r30->unk_34, (var_r28->unk_34 & 1) + 1, var_r28->unk_32);
                    if (fn_1_281C() == 2) {
                        omVibrate(var_r30->unk_34, 12, 6, 6);
                        HuAudFXPlay(9);
                        HuAudFXPlay(1378);
                    }
                }
            }
        }
    }
}

float fn_1_48D8(UnkM410Struct2 *arg0, u8 *arg1)
{
    float var_f31;
    float var_f30;
    float var_f29;

    var_f30 = 1.0f;
    if (0.0f == arg0->unk_1C.x && 0.0f == arg0->unk_1C.y && 0.0f == arg0->unk_1C.z) {
        return -1.0f;
    }
    *arg1 = 0;
    if (0.0f != arg0->unk_1C.x) {
        if (arg0->unk_1C.x < 0.0f) {
            var_f29 = (-500.0f - arg0->unk_04.x + arg0->unk_28) / arg0->unk_1C.x;
        } else {
            var_f29 = (500.0f - arg0->unk_04.x - arg0->unk_28) / arg0->unk_1C.x;
        }
        var_f31 = var_f29;
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
        }
        if (var_f31 >= 0.0f && var_f31 < 1.0f && var_f31 < var_f30) {
            *arg1 = 1;
            var_f30 = var_f31;
        }
    }
    if (arg0->unk_1C.y < 0.0f) {
        var_f31 = (-arg0->unk_04.y + arg0->unk_28) / arg0->unk_1C.y;
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
        }
        if (var_f31 >= 0.0f && var_f31 < 1.0f) {
            if (var_f31 == var_f30) {
                *arg1 |= 2;
            } else if (var_f31 < var_f30) {
                var_f30 = var_f31;
                *arg1 = 2;
            }
        }
    }
    if (arg0->unk_1C.z < 0.0f) {
        var_f31 = (-800.0f - arg0->unk_04.z + arg0->unk_28) / arg0->unk_1C.z;
        if (var_f31 < 0.0f) {
            var_f31 = 0.0f;
        }
        if (var_f31 >= 0.0f && var_f31 < 1.0f) {
            if (var_f31 == var_f30) {
                *arg1 |= 4;
            } else if (var_f31 < var_f30) {
                *arg1 = 4;
                var_f30 = var_f31;
            }
        }
    }
    if (var_f30 >= 0.0f && var_f30 < 1.0f) {
        return var_f30;
    }
    return -1.0f;
}

float fn_1_4C04(Vec arg0, Vec arg1, float arg8, Vec arg2, Vec arg3, float arg9)
{
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f22;
    float var_f21;

    VECSubtract(&arg2, &arg0, &arg2);
    VECSubtract(&arg3, &arg1, &arg3);
    if (VECMag(&arg2) > arg9 + (arg8 + VECMag(&arg3))) {
        return -1.0f;
    }
    var_f22 = (arg8 + arg9) * (arg8 + arg9);
    var_f28 = arg3.z * arg3.z + (arg3.x * arg3.x + (arg3.y * arg3.y));
    var_f27 = 2.0f * (arg3.z * arg2.z + (arg3.x * arg2.x + arg3.y * arg2.y));
    var_f21 = (arg2.z * arg2.z + (arg2.x * arg2.x + arg2.y * arg2.y)) - var_f22;
    if (0.0f == var_f28) {
        return -1.0f;
    }
    var_f30 = var_f27 * var_f27 - 4.0f * var_f28 * var_f21;
    if (var_f30 <= 0.0f) {
        return -1.0f;
    }
    var_f30 = sqrtf(var_f30);
    var_f26 = (-var_f27 + var_f30) / (2.0f * var_f28);
    var_f29 = (-var_f27 - var_f30) / (2.0f * var_f28);
    if (var_f26 * var_f29 < 0.0f && var_f29 < 0.0f) {
        if (var_f26 > fabs(var_f29)) {
            return 0.0f;
        }
    }
    if (var_f29 >= 0.0f && var_f29 < 1.0f) {
        return var_f29;
    }
    return -1.0f;
}

float fn_1_4FEC(Vec arg0, Vec arg1, float arg8, Vec arg2, Vec arg3, float arg9, float argA)
{
    float sp2C;

    float var_f28;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;
    float var_f22;
    float var_f21;
    float var_f18;

    VECSubtract(&arg0, &arg2, &arg0);
    VECSubtract(&arg1, &arg3, &arg1);

    if (VECMag(&arg0) > (arg8) + VECMag(&arg1) + arg9 + argA) {
        return -1.0f;
    }
    arg8 += arg9;
    var_f24 = VECMagXZ(&arg0);

    var_f23 = VECSumXZ(&arg0, &arg1) - var_f24;

    var_f22 = (var_f23 * var_f23) + (arg1.y * arg1.y);
    var_f21 = 2.0f * ((arg0.y * arg1.y) + ((-argA * var_f23) + (var_f24 * var_f23)));
    sp2C = (arg0.y * arg0.y + (((argA * argA) + (var_f24 * var_f24)) - (2.0f * argA * var_f24))) - (arg8 * arg8);
    if (0.0f == var_f22) {
        return -1.0f;
    }
    var_f28 = (var_f21 * var_f21) - (4.0f * var_f22 * sp2C);
    if (var_f28 < 0.0f) {
        return -1.0f;
    }

    var_f28 = sqrtf(var_f28);
    var_f18 = (-var_f21 + var_f28) / (2.0f * var_f22);
    var_f25 = (-var_f21 - var_f28) / (2.0f * var_f22);

    if (var_f18 * var_f25 < 0.0f && var_f25 < 0.0f) {
        if (var_f18 > fabs(var_f25)) {
            return 0.0f;
        }
    }
    if (var_f25 >= 0.0f && var_f25 < 1.0f) {
        return var_f25;
    }
    return -1.0f;
}

float fn_1_55C8(Vec arg0, Vec arg1, float arg8, Vec arg2, float arg9)
{
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f22;
    float var_f21;

    VECSubtract(&arg0, &arg2, &arg0);
    arg0.y = 0.0f;
    arg1.y = 0.0f;
    if (VECMag(&arg0) > arg8 + VECMag(&arg1) + arg9) {
        return -1.0f;
    }
    var_f22 = (arg8 + arg9) * (arg8 + arg9);
    var_f28 = (arg1.x * arg1.x) + (arg1.z * arg1.z);
    var_f27 = 2.0f * ((arg1.x * arg0.x) + (arg1.z * arg0.z));
    var_f21 = ((arg0.x * arg0.x) + (arg0.z * arg0.z)) - var_f22;
    if (0.0f == var_f28) {
        return -1.0f;
    }
    var_f30 = (var_f27 * var_f27) - (4.0f * var_f28 * var_f21);
    if (var_f30 <= 0.0f) {
        return -1.0f;
    }
    var_f30 = sqrtf(var_f30);
    var_f26 = (-var_f27 + var_f30) / (2.0f * var_f28);
    var_f29 = (-var_f27 - var_f30) / (2.0f * var_f28);
    if (var_f26 * var_f29 < 0.0f && var_f29 < 0.0f) {
        if (var_f26 > fabs(var_f29)) {
            return 0.0f;
        }
    }
    if (var_f29 >= 0.0f && var_f29 < 1.0f) {
        return var_f29;
    }
    return -1.0f;
}

s32 fn_1_598C(Vec *arg0, Vec *arg1, float arg8, Vec *arg2, Vec *arg3, float arg9, float argA)
{
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    float var_f31;

    VECSubtract(arg0, arg2, &sp38);
    VECSubtract(arg1, arg3, &sp2C);
    if (VECMag(&sp38) > arg8 + VECMag(&sp2C) + arg9 + argA) {
        return 0;
    }
    if (sp2C.y < 0.0f) {
        var_f31 = -sp38.y / sp2C.y;
        if (var_f31 >= 0.0f && var_f31 < 1.0f) {
            sp20.x = var_f31 * sp2C.x + sp38.x;
            sp20.y = var_f31 * sp2C.y + sp38.y;
            sp20.z = var_f31 * sp2C.z + sp38.z;
            if (VECMag(&sp20) < argA) {
                return 1;
            }
        }
    }
    return 0;
}

void fn_1_5AF4(UnkM410Struct2 *arg0, u8 arg1)
{
    if (arg1 & 1) {
        arg0->unk_1C.x = -arg0->unk_1C.x;
    }
    if (arg1 & 2) {
        arg0->unk_1C.y = -arg0->unk_1C.y;
        if (fabs(arg0->unk_1C.y) < 4.0) {
            arg0->unk_1C.y = 0.0f;
        }
        if (fabs(arg0->unk_1C.y) > 10.0) {
            if (arg0->unk_04.z < -400.0f) {
                HuAudFXPlay(1380);
            } else {
                HuAudFXPlay(1379);
            }
        }
    }
    if (arg1 & 4) {
        arg0->unk_1C.z = -arg0->unk_1C.z;
    }
    arg0->unk_1C.x *= 0.7f;
    arg0->unk_1C.y *= 0.7f;
    arg0->unk_1C.z *= 0.7f;
}

void fn_1_5CA0(Vec arg0, Vec arg1, Vec arg2, Vec *arg3, Vec *arg4)
{
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    sp34 = arg1;
    var_f31 = VECMag(&sp34);
    if (var_f31 < 0.001f) {
        arg3->x = arg3->y = arg3->z = 0.0f;
        arg4->x = arg4->y = arg4->z = 0.0f;
        return;
    }
    VECNormalize(&sp34, &sp34);
    var_f31 *= 0.9f;
    VECSubtract(&arg2, &arg0, &sp28);
    VECNormalize(&sp28, &sp28);
    var_f28 = VECDotProduct(&sp34, &sp28);
    if (var_f28 < 0.0f) {
        arg3->x = arg1.x;
        arg3->y = arg1.y;
        arg3->z = arg1.z;
        arg4->x = arg4->y = arg4->z = 0.0f;
        return;
    }
    var_f29 = var_f31 * var_f28;
    var_f30 = var_f31 - var_f29;
    if (var_f30 < 0.001f) {
        arg3->x = arg3->y = arg3->z = 0.0f;
    } else {
        VECCrossProduct(&sp34, &sp28, &sp10);
        VECNormalize(&sp10, &sp10);
        VECCrossProduct(&sp28, &sp10, &sp1C);
        VECNormalize(&sp1C, &sp1C);
        arg3->x = sp1C.x * var_f30;
        arg3->y = sp1C.y * var_f30;
        arg3->z = sp1C.z * var_f30;
    }
    arg4->x = sp28.x * var_f29;
    arg4->y = sp28.y * var_f29;
    arg4->z = sp28.z * var_f29;
}

void fn_1_5EDC(UnkM410Struct2 *arg0, UnkM410Struct2 *arg1)
{
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    float var_f29;

    arg0->unk_1C.x *= 0.9f;
    arg0->unk_1C.y *= 0.9f;
    arg0->unk_1C.z *= 0.9f;
    VECSubtract(&arg0->unk_04, &arg1->unk_04, &sp14);
    VECNormalize(&sp14, &sp8);
    var_f30 = (arg0->unk_28 + arg1->unk_28) - VECMag(&sp14);
    if (var_f30 > 0.001f) {
        VECSubtract(&arg0->unk_1C, &arg1->unk_1C, &sp14);
        if (VECMag(&sp14) < 0.001f) {
            arg0->unk_04.x += sp8.x * var_f30;
            arg0->unk_04.y += sp8.y * var_f30;
            arg0->unk_04.z += sp8.z * var_f30;
        } else {
            VECNormalize(&sp14, &sp14);
            arg0->unk_04.x -= sp14.x * var_f30;
            arg0->unk_04.y -= sp14.y * var_f30;
            arg0->unk_04.z -= sp14.z * var_f30;
        }
    }
    var_f31 = ((-arg0->unk_1C.x * sp8.x) - (arg0->unk_1C.y * sp8.y)) - (arg0->unk_1C.z * sp8.z);
    if (var_f31 > 0.0f) {
        arg0->unk_1C.x += 2.0f * sp8.x * var_f31;
        arg0->unk_1C.y += 2.0f * sp8.y * var_f31;
        arg0->unk_1C.z += 2.0f * sp8.z * var_f31;
    }
    VECSubtract(&arg1->unk_1C, &arg0->unk_1C, &sp14);
    var_f29 = VECMag(&sp14);
    if (var_f29 < 0.001f) {
        return;
    }
    VECNormalize(&sp14, &sp14);
    var_f31 = VECDotProduct(&sp8, &sp14);
    if (var_f31 > 0.0f) {
        arg0->unk_1C.x += sp8.x * var_f31 * var_f29;
        arg0->unk_1C.y += sp8.y * var_f31 * var_f29;
        arg0->unk_1C.z += sp8.z * var_f31 * var_f29;
    }
}

void fn_1_61DC(UnkM410Struct2 *arg0, UnkM410Struct2 *arg1)
{
    Vec sp74;
    Vec sp68;
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    Vec *var_r29;
    Vec *var_r28;
    Vec *var_r27;
    Vec *var_r26;
    Vec *var_r25;
    Vec *var_r24;

    if (arg0->unk_00_field1 || arg1->unk_00_field1) {
        if (arg0->unk_00_field1) {
            fn_1_5EDC(arg1, arg0);
        } else {
            fn_1_5EDC(arg0, arg1);
        }
        return;
    }
    fn_1_5CA0(arg0->unk_04, arg0->unk_1C, arg1->unk_04, &sp68, &sp74);
    fn_1_5CA0(arg1->unk_04, arg1->unk_1C, arg0->unk_04, &sp50, &sp5C);
    VECAdd(&sp68, &sp5C, &arg0->unk_1C);
    VECAdd(&sp74, &sp50, &arg1->unk_1C);
}

void fn_1_6364(UnkM410Struct2 *arg0, UnkM410Struct2 *arg1)
{
    Vec sp20;
    Vec sp14;
    Vec sp8;

    float var_f31;
    float var_f30;

    arg0->unk_1C.x *= 0.7f;
    arg0->unk_1C.y *= 0.7f;
    arg0->unk_1C.z *= 0.7f;
    VECSubtract(&arg0->unk_04, &arg1->unk_04, &sp14);

    sp14.y = 0.0f;
    VECNormalize(&sp14, &sp14);

    sp20.x = sp14.x * arg1->unk_2C + arg1->unk_04.x;
    sp20.y = arg1->unk_04.y;
    sp20.z = sp14.z * arg1->unk_2C + arg1->unk_04.z;

    VECSubtract(&arg0->unk_04, &sp20, &sp14);
    VECNormalize(&sp14, &sp8);
    var_f31 = (arg0->unk_28 + arg1->unk_28) - VECMag(&sp14);

    if (var_f31 > 0.001f) {
        VECSubtract(&arg0->unk_1C, &arg1->unk_1C, &sp14);
        if (VECMag(&sp14) < 0.001f) {
            arg0->unk_04.x += sp8.x * var_f31;
            arg0->unk_04.y += sp8.y * var_f31;
            arg0->unk_04.z += sp8.z * var_f31;
        } else {
            VECNormalize(&sp14, &sp14);
            arg0->unk_04.x -= sp14.x * var_f31;
            arg0->unk_04.y -= sp14.y * var_f31;
            arg0->unk_04.z -= sp14.z * var_f31;
        }
    }
    var_f30 = -arg0->unk_1C.x * sp8.x - arg0->unk_1C.y * sp8.y - arg0->unk_1C.z * sp8.z;
    if (var_f30 > 0.0f) {
        arg0->unk_1C.x += 2.0f * sp8.x * var_f30;
        arg0->unk_1C.y += 2.0f * sp8.y * var_f30;
        arg0->unk_1C.z += 2.0f * sp8.z * var_f30;
    }
    VECSubtract(&arg1->unk_1C, &arg0->unk_1C, &sp14);
    var_f31 = VECMag(&sp14);
    if (!(var_f31 < 0.001f)) {
        VECNormalize(&sp14, &sp14);
        var_f30 = VECDotProduct(&sp8, &sp14);
        if (var_f30 > 0.0f) {
            arg0->unk_1C.x += sp8.x * var_f30 * var_f31;
            arg0->unk_1C.y += sp8.y * var_f30 * var_f31;
            arg0->unk_1C.z += sp8.z * var_f30 * var_f31;
        }
    }
}

void fn_1_66B8(UnkM410Struct2 *arg0, UnkM410Struct2 *arg1) // TODO maybe UnkM410Struct3?
{
    Vec spC;
    float var_f31;

    VECSubtract(&arg0->unk_04, (Vec *)&arg1->unk_10.z, &spC);
    spC.y = 0.0f;
    VECNormalize(&spC, &spC);
    var_f31 = -arg0->unk_1C.x * spC.x - arg0->unk_1C.z * spC.z;
    arg0->unk_1C.x += 2.0f * spC.x * var_f31;
    arg0->unk_1C.z += 2.0f * spC.z * var_f31;
    arg0->unk_1C.x *= 0.5f;
    arg0->unk_1C.y *= 0.5f;
    arg0->unk_1C.z *= 0.5f;
}

void fn_1_67D4(omObjData *arg0)
{
    s32 var_r30;
    UnkM410Struct2 *var_r29;
    s16 var_r28;

    arg0->stat |= 0x100;
    var_r29 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM410Struct2) * 60, MEMORY_DEFAULT_NUM);
    arg0->data = var_r29;
    memset(var_r29, 0, 4320);

    for (var_r30 = 0; var_r30 < 60; var_r30++, var_r29++) {
        var_r29->unk_32 = var_r30;
        var_r29->unk_34 = var_r30 / 15;
        if ((var_r30 % 15) == 0) {
            arg0->model[var_r30] = Hu3DModelCreateFile(lbl_1_data_DC[GWPlayerCfg[var_r29->unk_34].character]);
            var_r28 = arg0->model[var_r30];
        } else {
            arg0->model[var_r30] = Hu3DModelLink(var_r28);
        }
        var_r29->unk_30 = arg0->model[var_r30];
        Hu3DModelAttrSet(arg0->model[var_r30], 1);
        Hu3DModelShadowSet(arg0->model[var_r30]);
    }
    arg0->func = fn_1_6968;
}

void fn_1_6968(omObjData *object)
{
    Mtx sp14;
    Vec sp8;
    float var_f31;
    float var_f30;
    UnkM410Struct2 *var_r31;
    s32 var_r30;
    ModelData *var_r28;

    var_r31 = object->data;

    for (var_r30 = 0; var_r30 < 60; var_r30++, var_r31++) {
        if (!var_r31->unk_00_field0) {
            Hu3DModelAttrSet(var_r31->unk_30, 1);
            continue;
        }
        if (var_r31->unk_00_field1) {
            Hu3DModelObjPosGet(var_r31->unk_38->unk_30, "i_hook", &sp8);
            VECSubtract(&sp8, &var_r31->unk_04, &sp8);
            if (var_r31->unk_36 != 0) {
                var_f31 = cosd(90.0f * var_r31->unk_36 / 10.0f);
                var_r31->unk_1C.x = var_f31 * sp8.x;
                var_r31->unk_1C.y = var_f31 * sp8.y;
                var_r31->unk_1C.z = var_f31 * sp8.z;
                var_r31->unk_36--;
            } else {
                var_r31->unk_1C = sp8;
            }
        } else {
            var_r31->unk_1C.y += -0.95277786f;
            if (var_r31->unk_00_field3 && (fn_1_281C() != 4 || (fn_1_281C() == 4 && var_r31->unk_36 < 15))) {
                if (--var_r31->unk_36 == 0) {
                    var_r31->unk_00_field0 = 0;
                }
                if (var_r31->unk_36 < 15) {
                    var_r31->unk_00_field2 ^= 1;
                }
            }
            if (!var_r31->unk_44) {
                if (0.0f != var_r31->unk_1C.x || 0.0f != var_r31->unk_1C.z) {
                    sp8.x = var_r31->unk_1C.z;
                    sp8.y = 0.0f;
                    sp8.z = -var_r31->unk_1C.x;
                    var_f30 = VECMag(&sp8) / 30.000002f;
                    if (var_f30 >= 0.001f) {
                        PSMTXRotAxisRad(sp14, &sp8, var_f30);
                        var_r28 = &Hu3DData[object->model[var_r30]];
                        PSMTXConcat(sp14, var_r28->unk_F0, var_r28->unk_F0);
                    }
                }
            } else {
                var_r31->unk_44--;
            }
        }
        if (var_r31->unk_00_field2) {
            Hu3DModelAttrReset(var_r31->unk_30, 1);
        } else {
            Hu3DModelAttrSet(var_r31->unk_30, 1);
        }
        Hu3DModelPosSet(object->model[var_r30], var_r31->unk_04.x, var_r31->unk_04.y, var_r31->unk_04.z);
    }
    if (fn_1_281C() > 2 && fn_1_28DC() == 1) {
        var_r31 = lbl_1_bss_58->data;

        for (var_r30 = 0; var_r30 < 60; var_r30++, var_r31++) {
            if (var_r31->unk_00_field0) {
                fn_1_7520(&var_r31->unk_04);
                Hu3DModelAttrSet(var_r31->unk_30, 1);
                var_r31->unk_00_field0 = 0;
            }
        }
        lbl_1_bss_58->func = NULL;
        Hu3DModelAttrReset(lbl_1_bss_38, 1);
        fn_1_287C(4);
    }
}

void fn_1_6D84(omObjData *object)
{
    HuMemDirectFree(object->data);
}

s32 lbl_1_data_104[] = { DATA_MAKE_NUM(DATADIR_M410, 8), DATA_MAKE_NUM(DATADIR_M410, 9), DATA_MAKE_NUM(DATADIR_M410, 8) };

void fn_1_6DB4(omObjData *object)
{
    UnkM410Struct2 *var_r31;
    s32 var_r29;
    s16 var_r28;

    object->stat |= 0x100;
    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkM410Struct2) * 18, MEMORY_DEFAULT_NUM);
    object->data = var_r31;
    memset(var_r31, 0, sizeof(UnkM410Struct2) * 18);

    for (var_r29 = 0; var_r29 < 18; var_r29++, var_r31++) {
        var_r31->unk_34 = var_r29 / 6;
        object->model[var_r29] = Hu3DModelCreateFile(lbl_1_data_104[var_r31->unk_34]);
        var_r28 = object->model[var_r29];
		(void)var_r28;
        Hu3DModelAttrSet(object->model[var_r29], 0x40000002);
        Hu3DData[object->model[var_r29]].cluster_attr[0] = 0;
        var_r31->unk_30 = object->model[var_r29];
        var_r31->unk_32 = var_r29;
        var_r31->unk_04.x = (250.0f * (var_r29 % 6)) - 750.0f;

        if ((var_r31->unk_34 & 1) == 0) {
            var_r31->unk_04.x += 125.0f;
        }
        var_r31->unk_04.y = 140.0f + (140.0f * var_r31->unk_34);
        var_r31->unk_04.z = -700.0f;
        var_r31->unk_28 = 1.0f;
        var_r31->unk_2C = 50.0f;
        Hu3DModelPosSet(object->model[var_r29], var_r31->unk_04.x, var_r31->unk_04.y, var_r31->unk_04.z);

        if (!var_r29) {
            object->model[var_r29 + 0x12] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M410, 10));
        } else {
            object->model[var_r29 + 0x12] = Hu3DModelLink(object->model[18]);
        }
        Hu3DModelShadowMapSet(object->model[var_r29 + 18]);
        Hu3DModelPosSet(object->model[var_r29 + 18], var_r31->unk_04.x, var_r31->unk_04.y, var_r31->unk_04.z);
        if (!var_r29) {
            object->model[var_r29 + 36] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M410, 11));

        } else {
            object->model[var_r29 + 36] = Hu3DModelLink(object->model[36]);
        }
        Hu3DModelPosSet(object->model[var_r29 + 0x24], 20.0f + var_r31->unk_04.x, -10.0f + var_r31->unk_04.y, var_r31->unk_04.z);
    }
    object->func = fn_1_7138;
}

void fn_1_7138(omObjData *object)
{
    float var_f31;
    UnkM410Struct2 *var_r31;
    s32 var_r29;

    var_r31 = object->data;

    for (var_r29 = 0; var_r29 < 18; var_r29++, var_r31++) {
        if (var_r31->unk_34 & 1) {
            var_f31 = lbl_1_bss_50;
        } else {
            var_f31 = -lbl_1_bss_50;
        }
        var_r31->unk_1C.x = var_f31;
        if (var_r31->unk_00_field4) {
            Hu3DModelAttrReset(object->model[var_r29], 0x40000002);
            Hu3DMotionSpeedSet(object->model[var_r29], 4.0f);
            Hu3DMotionSet(object->model[var_r29], 0);
            Hu3DMotionClusterNoSet(object->model[var_r29], Hu3DData[object->model[var_r29]].unk_10[0], 0);
            Hu3DData[object->model[var_r29]].unk_B4[0] = 4.0f;
            var_r31->unk_00_field4 = 0;
        }
        if (var_r31->unk_1C.x < 0.0f) {
            if (var_r31->unk_04.x < -750.0f) {
                var_r31->unk_04.x += 1500.0f;
                var_r31->unk_00_field6 = 1;
            }
        } else if (var_r31->unk_04.x > 750.0f) {
            var_r31->unk_04.x -= 1500.0f;
            var_r31->unk_00_field6 = 1;
        }
        if (var_r31->unk_00_field6) {
            if (var_r31->unk_38 != NULL) {
                var_r31->unk_38->unk_00_field0 = 0;
                var_r31->unk_38 = NULL;
                Hu3DMotionClusterNoSet(object->model[var_r29], Hu3DData[object->model[var_r29]].unk_10[0], 0);
                Hu3DData[object->model[var_r29]].unk_B4[0] = 0.0f;
            }
            var_r31->unk_00_field6 = 0;
        }
        Hu3DModelPosSet(object->model[var_r29], var_r31->unk_04.x, var_r31->unk_04.y, var_r31->unk_04.z);
        Hu3DModelPosSet(object->model[var_r29 + 18], var_r31->unk_04.x, var_r31->unk_04.y, var_r31->unk_04.z);
        Hu3DModelPosSet(object->model[var_r29 + 36], 20.0f + var_r31->unk_04.x, -10.0f + var_r31->unk_04.y, var_r31->unk_04.z);
    }
}

void fn_1_7464(omObjData *object)
{
    HuMemDirectFree(object->data);
}

void fn_1_7494(void)
{
    AnimData *var_r31;

    var_r31 = HuSprAnimRead(HuDataReadNum(DATA_MAKE_NUM(DATADIR_EFFECT, 2), MEMORY_DEFAULT_NUM));
    lbl_1_bss_38 = Hu3DParticleCreate(var_r31, 60);
    Hu3DParticleHookSet(lbl_1_bss_38, fn_1_75A0);
    Hu3DModelAttrSet(lbl_1_bss_38, 1);
}

void fn_1_7520(Vec *arg0)
{
    ParticleData *var_r30;
    HsfanimStruct01 *var_r31;

    var_r30 = Hu3DData[lbl_1_bss_38].unk_120;
    var_r31 = &var_r30->unk_48[var_r30->unk_02++];
    var_r31->unk2C = 100.0f;
    var_r31->unk34.x = arg0->x;
    var_r31->unk34.y = arg0->y;
    var_r31->unk34.z = arg0->z;
}

s32 lbl_1_data_110 = 60;

void fn_1_75A0(ModelData *model, ParticleData *particle, Mtx matrix)
{
    HsfanimStruct01 *var_r30;
    s32 var_r29;
    s32 var_r28;

    if (!particle->unk_00) {
        particle->unk_00 = 1;
        var_r30 = &particle->unk_48[particle->unk_02];
        for (var_r29 = particle->unk_02; var_r29 < particle->unk_30; var_r29++, var_r30++) {
            var_r30->unk2C = 0.0f;
        }
    }
    var_r28 = (lbl_1_data_110 * 0xFF) / 60;
    var_r30 = particle->unk_48;

    for (var_r29 = 0; var_r29 < particle->unk_02; var_r29++, var_r30++) {
		var_r30->unk40.a = var_r28; // 43?
    }
    if (--lbl_1_data_110 == 0) {
		model->attr |= 1;
    }
    DCStoreRange(particle->unk_48, particle->unk_30 * 0x44);
}

s32 fn_1_76B8(Vec arg0, Vec arg1, u16 arg2)
{
    UnkM410Struct2 *var_r31 = lbl_1_bss_58->data;
    s32 var_r30;

    var_r31 = &var_r31[arg2 * 15];
	for(var_r30=0; var_r30<15; var_r30++, var_r31++) {
		if (!var_r31->unk_00_field0) {
			*(s16 *)var_r31 = 0;
			var_r31->unk_00_field0 = 1;
			var_r31->unk_00_field2 = 1;
			var_r31->unk_04 = arg0;
			var_r31->unk_1C = arg1;
			var_r31->unk_28 = 30.000002f;
			var_r31->unk_38 = NULL;
			var_r31->unk_36  = 0;
			return 1;
		}
	}
	return 0;
}

void fn_1_77A4(u16 arg0, u16 arg1, u16 arg2)
{
    OSReport("GOAL!!(%d , %d , %d)\n", arg0, arg1, arg2);
}

void fn_1_77E8(void *arg0)
{
    lbl_1_bss_44 = arg0;
}

void fn_1_77F8(u16 arg0, Vec *arg1)
{
    UnkM410Struct2 *var_r31;

    var_r31 = &((UnkM410Struct2 *)lbl_1_bss_54->data)[arg0];
    arg1->x = var_r31->unk_04.x;
    arg1->y = var_r31->unk_04.y;
    arg1->z = var_r31->unk_04.z;
}

void fn_1_7840(u16 arg0, Vec *arg1)
{
    UnkM410Struct2 *var_r31;

    var_r31 = &((UnkM410Struct2 *)lbl_1_bss_54->data)[arg0];
    arg1->x = var_r31->unk_1C.x;
    arg1->y = var_r31->unk_1C.y;
    arg1->z = var_r31->unk_1C.z;
}

void fn_1_7888(u16 arg0, u16 arg1, Vec *arg2)
{
    Vec sp8;
    UnkM410Struct2 *var_r31;

    var_r31 = &((UnkM410Struct2 *)lbl_1_bss_54->data)[arg0];
    sp8.x = var_r31->unk_04.x + var_r31->unk_1C.x * arg1;
    sp8.y = var_r31->unk_04.y + var_r31->unk_1C.y * arg1;
    sp8.z = var_r31->unk_04.z + var_r31->unk_1C.z * arg1;
    if (var_r31->unk_1C.x < 0.0f) {
        while (sp8.x < -750.0f) {
            sp8.x += 1500.0f;
        }
    } else {
        while (sp8.x > 750.0f) {
            sp8.x -= 1500.0f;
        }
    }
    arg2->x = sp8.x;
    arg2->y = sp8.y;
    arg2->z = sp8.z;
}

s32 fn_1_79F8(s16 arg0, char *arg1, Mtx arg2)
{
    Mtx sp44;
    Mtx sp14;
    HsfData *var_r30;
    ModelData *var_r31;

    var_r31 = &Hu3DData[arg0];
    var_r30 = var_r31->hsfData;
    lbl_1_bss_30 = 0;
    mtxRot(sp14, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
    PSMTXScale(sp44, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
    PSMTXConcat(sp14, sp44, sp44);
    mtxTransCat(sp44, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
    fn_1_7AC4(var_r30->root, sp44, arg1, arg2);
    return lbl_1_bss_30;
}

void fn_1_7AC4(HsfObject *arg0, Mtx arg1, char *arg2, Mtx arg3)
{
    Mtx sp15C;
    Mtx sp12C;
    Mtx spFC;
    Mtx spCC;
    Mtx sp9C;
    Mtx sp6C;
    Mtx sp3C;
    Mtx spC;

    HsfTransform *var_r31;
    HsfTransform *var_r30;
    HsfTransform *var_r29;
    HsfTransform *var_r28;
    HsfObject *var_r27;
    HsfObject *var_r26;
    HsfObject *var_r25;
    u32 var_r23;
    u32 var_r22;
    u32 var_r21;
    u32 var_r20;

    if (lbl_1_bss_30) {
        return;
    }
    var_r31 = &arg0->data.curr;

    mtxRot(sp12C, var_r31->rot.x, var_r31->rot.y, var_r31->rot.z);
    PSMTXScale(sp15C, var_r31->scale.x, var_r31->scale.y, var_r31->scale.z);
    PSMTXConcat(sp12C, sp15C, sp15C);
    mtxTransCat(sp15C, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
    PSMTXConcat(arg1, sp15C, sp15C);
    if (!strcmp(arg2, arg0->name)) {
        PSMTXCopy(sp15C, arg3);
        lbl_1_bss_30 = 1;
    }

    for (var_r23 = 0; var_r23 < arg0->data.childrenCount; var_r23++) {
        var_r27 = arg0->data.children[var_r23];
        if (!lbl_1_bss_30) {
            var_r30 = &var_r27->data.curr;
            mtxRot(spFC, var_r30->rot.x, var_r30->rot.y, var_r30->rot.z);
            PSMTXScale(spCC, var_r30->scale.x, var_r30->scale.y, var_r30->scale.z);
            PSMTXConcat(spFC, spCC, spCC);
            mtxTransCat(spCC, var_r30->pos.x, var_r30->pos.y, var_r30->pos.z);
            PSMTXConcat(sp15C, spCC, spCC);
            if (!strcmp(arg2, var_r27->name)) {
                PSMTXCopy(spCC, arg3);
                lbl_1_bss_30 = 1;
            }
            for (var_r22 = 0; var_r22 < var_r27->data.childrenCount; var_r22++) {
                var_r26 = var_r27->data.children[var_r22];
                if (!lbl_1_bss_30) {
                    var_r29 = &var_r26->data.curr;
                    mtxRot(sp9C, var_r29->rot.x, var_r29->rot.y, var_r29->rot.z);
                    PSMTXScale(sp6C, var_r29->scale.x, var_r29->scale.y, var_r29->scale.z);
                    PSMTXConcat(sp9C, sp6C, sp6C);
                    mtxTransCat(sp6C, var_r29->pos.x, var_r29->pos.y, var_r29->pos.z);
                    PSMTXConcat(spCC, sp6C, sp6C);
                    if (!strcmp(arg2, var_r26->name)) {
                        PSMTXCopy(sp6C, arg3);
                        lbl_1_bss_30 = 1;
                    }

                    for (var_r21 = 0; var_r21 < var_r26->data.childrenCount; var_r21++) {
                        var_r25 = var_r26->data.children[var_r21];
                        if (!lbl_1_bss_30) {
                            var_r28 = &var_r25->data.curr;
                            mtxRot(sp3C, var_r28->rot.x, var_r28->rot.y, var_r28->rot.z);
                            PSMTXScale(spC, var_r28->scale.x, var_r28->scale.y, var_r28->scale.z);
                            PSMTXConcat(sp3C, spC, spC);
                            mtxTransCat(spC, var_r28->pos.x, var_r28->pos.y, var_r28->pos.z);
                            PSMTXConcat(sp6C, spC, spC);
                            if (!strcmp(arg2, var_r25->name)) {
                                PSMTXCopy(spC, arg3);
                                lbl_1_bss_30 = 1;
                            }

                            for (var_r20 = 0; var_r20 < var_r25->data.childrenCount; var_r20++) {
                                fn_1_7AC4(var_r25->data.children[var_r20], spC, arg2, arg3);
                            }
                        }
                    }
                }
            }
        }
    }
}
