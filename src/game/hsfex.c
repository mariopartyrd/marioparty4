#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"

#include "math.h"

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ float unk04;
    /* 0x08 */ Vec unk08;
    /* 0x14 */ Vec unk14;
    /* 0x20 */ Vec unk20;
} HsfexStruct02; // Size 0x2C

static void SetObjCamMotion(s16 arg0, HsfTrack *arg1, float arg2, HsfexStruct02 *arg3);

void CamMotionEx2(s16 arg0, s16 arg1, float arg2, s16 arg3) {
    CameraData *temp_r30;
    s16 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            break;
        }
    }
    temp_r30 = &Hu3DCamera[i];
    CamMotionEx(arg0, arg1, &temp_r30->pos, &temp_r30->up, &temp_r30->target, arg2, arg3);
}

void CamMotionEx(s16 arg0, s16 arg1, Vec *arg2, Vec *arg3, Vec *arg4, float arg5, s16 arg6) {
    Vec sp3C;
    float sp2C[4];
    float sp1C[4];
    float temp_f29;
    float var_f27;
    float var_f26;
    float var_f30;
    float var_f31;
    s16 sp1A;
    s16 var_r25;
    s16 var_r29;
    s16 var_r30;
    HsfexStruct02 *var_r31;
    CameraData *temp_r27;
    ModelData *temp_r23;
    HsfData *temp_r22;
    MotionData *temp_r19;
    HsfData *temp_r18;
    HsfObject *temp_r24;
    HsfTrack *temp_r20;
    HsfMotion *temp_r26;
    HsfexStruct02 *temp_r21;
    HsfTrack *var_r28;

    temp_r23 = &Hu3DData[arg0];
    temp_r19 = &Hu3DMotion[temp_r23->unk_08];
    temp_r22 = temp_r23->hsfData;
    temp_r18 = temp_r19->unk_04;
    temp_r26 = temp_r18->motion;
    for (var_r25 = 0; var_r25 < 16; var_r25++) {
        if (arg1 & (1 << var_r25)) {
            break;
        }
    }
    temp_r27 = &Hu3DCamera[var_r25];
    temp_f29 = temp_r26->len;
    sp1A = 0.5f + (temp_f29 / 6.0f) + 1.0f;
    var_r31 = temp_r21 = HuMemDirectMallocNum(HEAP_SYSTEM, (sp1A + 1) * sizeof(HsfexStruct02), MEMORY_DEFAULT_NUM);
    var_r31->unk00 = 0.0f;
    var_r31->unk08 = *arg2;
    var_r31->unk20 = *arg4;
    var_r31->unk14 = *arg3;
    var_r31++;
    for (var_r29 = 1, var_f31 = 0.0f; var_f31 <= temp_f29; var_r31++, var_r29++) {
        var_r31->unk00 = var_f31;
        var_r28 = temp_r26->track;
        temp_r20 = &var_r28[temp_r26->numTracks];
        while (var_r28 < temp_r20) {
            if (var_r28->type == 2) {
                temp_r24 = &temp_r22->object[var_r28->target];
                if (temp_r24->type == 7) {
                    SetObjCamMotion(arg0, var_r28, GetCurve(var_r28, var_f31), var_r31);
                }
            }
            var_r28++;
        }
        var_f31 += 6.0f;
    }
    if (var_f31 != temp_f29) {
        var_r31->unk00 = temp_f29;
        var_r28 = temp_r26->track;
        temp_r20 = &var_r28[temp_r26->numTracks];
        while (var_r28 < temp_r20) {
            if (var_r28->type == 2) {
                temp_r24 = &temp_r22->object[var_r28->target];
                if (temp_r24->type == 7) {
                    SetObjCamMotion(arg0, var_r28, GetCurve(var_r28, temp_f29), var_r31);
                }
            }
            var_r28++;
        }
        var_r29++;
    }
    var_r31 = temp_r21;
    var_r31->unk04 = 0.0f;
    var_f26 = 0.0f;
    for (var_f31 = var_f26; var_f31 < var_r29 - 1; var_f31 += 1.0f, var_r31++) {
        VECSubtract(&var_r31[1].unk08, &var_r31[0].unk08, &sp3C);
        var_r31[1].unk04 = VECMag(&sp3C);
        var_f26 += var_r31[1].unk04;
    }
    var_r31 = temp_r21;
    var_f27 = 0.0f;
    var_f31 = var_f27;
    while (var_f31 < var_r29) {
        var_f27 += var_r31->unk04;
        var_r31->unk00 = arg5 * (var_f27 / var_f26);
        var_f31 += 1.0f;
        var_r31++;
    }
    var_f31 = 0.0f;
    while (var_f31 <= arg5) {
        switch (arg6) {
            case 0:
                var_f30 = var_f31;
                break;
            case 1:
                var_f30 = arg5 * sin(90.0f * (var_f31 / arg5) * M_PI / 180.0);
                break;
            case 2:
                var_f30 = arg5 * (1.0 - cos(90.0f * (var_f31 / arg5) * M_PI / 180.0));
                break;
            }
        var_r31 = temp_r21;
        for (var_r30 = 0; var_r30 < var_r29; var_r30++, var_r31++) {
            if (var_r31->unk00 <= var_f30 && var_r31[1].unk00 > var_f30) {
                break;
            }
        }
        if (var_r30 != var_r29) {
            if (var_r30 == 0) {
                sp1C[0] = -1.0f;
            } else {
                sp1C[0] = var_r31[-1].unk00;
            }
            sp1C[1] = var_r31->unk00;
            if (var_r30 >= var_r29 - 1) {
                sp1C[2] = 1.0f + var_r31->unk00;
            }
            sp1C[2] = var_r31[1].unk00;
            if (var_r30 >= var_r29 - 2) {
                sp1C[3] = 1.0f + sp1C[2];
            } else {
                sp1C[3] = var_r31[2].unk00;
            }
            if (var_r30 == 0) {
                sp2C[0] = var_r31[0].unk08.x;
            } else {
                sp2C[0] = var_r31[-1].unk08.x;
            }
            sp2C[1] = var_r31[0].unk08.x;
            if (var_r30 >= var_r29 - 1) {
                sp2C[2] = sp2C[1];
            } else {
                sp2C[2] = var_r31[1].unk08.x;
            }
            if (var_r30 >= var_r29 - 2) {
                sp2C[3] = sp2C[2];
            } else {
                sp2C[3] = var_r31[2].unk08.x;
            }
            temp_r27->pos.x = InterpolateBMLine(sp2C, sp1C, var_f30);
            if (var_r30 == 0) {
                sp2C[0] = var_r31[0].unk08.y;
            } else {
                sp2C[0] = var_r31[-1].unk08.y;
            }
            sp2C[1] = var_r31[0].unk08.y;
            if (var_r30 >= var_r29 - 1) {
                sp2C[2] = sp2C[1];
            } else {
                sp2C[2] = var_r31[1].unk08.y;
            }
            if (var_r30 >= var_r29 - 2) {
                sp2C[3] = sp2C[2];
            } else {
                sp2C[3] = var_r31[2].unk08.y;
            }
            temp_r27->pos.y = InterpolateBMLine(sp2C, sp1C, var_f30);
            if (var_r30 == 0) {
                sp2C[0] = var_r31[0].unk08.z;
            } else {
                sp2C[0] = var_r31[-1].unk08.z;
            }
            sp2C[1] = var_r31[0].unk08.z;
            if (var_r30 >= var_r29 - 1) {
                sp2C[2] = sp2C[1];
            } else {
                sp2C[2] = var_r31[1].unk08.z;
            }
            if (var_r30 >= var_r29 - 2) {
                sp2C[3] = sp2C[2];
            } else {
                sp2C[3] = var_r31[2].unk08.z;
            }
            temp_r27->pos.z = InterpolateBMLine(sp2C, sp1C, var_f30);
            if (var_r30 == 0) {
                sp2C[0] = var_r31[0].unk20.x;
            } else {
                sp2C[0] = var_r31[-1].unk20.x;
            }
            sp2C[1] = var_r31[0].unk20.x;
            if (var_r30 >= var_r29 - 1) {
                sp2C[2] = sp2C[1];
            } else {
                sp2C[2] = var_r31[1].unk20.x;
            }
            if (var_r30 >= var_r29 - 2) {
                sp2C[3] = sp2C[2];
            } else {
                sp2C[3] = var_r31[2].unk20.x;
            }
            temp_r27->target.x = InterpolateBMLine(sp2C, sp1C, var_f30);
            if (var_r30 == 0) {
                sp2C[0] = var_r31->unk20.y;
            } else {
                sp2C[0] = var_r31[-1].unk20.y;
            }
            sp2C[1] = var_r31->unk20.y;
            if (var_r30 >= var_r29 - 1) {
                sp2C[2] = sp2C[1];
            } else {
                sp2C[2] = var_r31[1].unk20.y;
            }
            if (var_r30 >= var_r29 - 2) {
                sp2C[3] = sp2C[2];
            } else {
                sp2C[3] = var_r31[2].unk20.y;
            }
            temp_r27->target.y = InterpolateBMLine(sp2C, sp1C, var_f30);
            if (var_r30 == 0) {
                sp2C[0] = var_r31->unk20.z;
            } else {
                sp2C[0] = var_r31[-1].unk20.z;
            }
            sp2C[1] = var_r31->unk20.z;
            if (var_r30 >= var_r29 - 1) {
                sp2C[2] = sp2C[1];
            } else {
                sp2C[2] = var_r31[1].unk20.z;
            }
            if (var_r30 >= var_r29 - 2) {
                sp2C[3] = sp2C[2];
            } else {
                sp2C[3] = var_r31[2].unk20.z;
            }
            temp_r27->target.z = InterpolateBMLine(sp2C, sp1C, var_f30);
            if (var_r30 == 0) {
                sp2C[0] = var_r31->unk14.x;
            } else {
                sp2C[0] = var_r31[-1].unk14.x;
            }
            sp2C[1] = var_r31->unk14.x;
            if (var_r30 >= var_r29 - 1) {
                sp2C[2] = sp2C[1];
            } else {
                sp2C[2] = var_r31[1].unk14.x;
            }
            if (var_r30 >= var_r29 - 2) {
                sp2C[3] = sp2C[2];
            } else {
                sp2C[3] = var_r31[2].unk14.x;
            }
            temp_r27->up.x = InterpolateBMLine(sp2C, sp1C, var_f30);
            if (var_r30 == 0) {
                sp2C[0] = var_r31->unk14.y;
            } else {
                sp2C[0] = var_r31[-1].unk14.y;
            }
            sp2C[1] = var_r31->unk14.y;
            if (var_r30 >= var_r29 - 1) {
                sp2C[2] = sp2C[1];
            } else {
                sp2C[2] = var_r31[1].unk14.y;
            }
            if (var_r30 >= var_r29 - 2) {
                sp2C[3] = sp2C[2];
            } else {
                sp2C[3] = var_r31[2].unk14.y;
            }
            temp_r27->up.y = InterpolateBMLine(sp2C, sp1C, var_f30);
            if (var_r30 == 0) {
                sp2C[0] = var_r31->unk14.z;
            } else {
                sp2C[0] = var_r31[-1].unk14.z;
            }
            sp2C[1] = var_r31->unk14.z;
            if (var_r30 >= var_r29 - 1) {
                sp2C[2] = sp2C[1];
            } else {
                sp2C[2] = var_r31[1].unk14.z;
            }
            if (var_r30 >= var_r29 - 2) {
                sp2C[3] = sp2C[2];
            } else {
                sp2C[3] = var_r31[2].unk14.z;
            }
            temp_r27->up.z = InterpolateBMLine(sp2C, sp1C, var_f30);
            HuPrcVSleep();
            var_f31 += 1.0f;
        } else {
            break;
        }
    }
    HuMemDirectFree(temp_r21);
}

static void SetObjCamMotion(s16 arg0, HsfTrack *arg1, float arg2, HsfexStruct02 *arg3) {
    ModelData *temp_r31 = &Hu3DData[arg0];
    Vec sp18;
    Vec spC;

    switch (arg1->channel) {
        case 8:
            arg3->unk08.x = temp_r31->scale.x * (arg2 + temp_r31->pos.x);
            break;
        case 9:
            arg3->unk08.y = temp_r31->scale.y * (arg2 + temp_r31->pos.y);
            break;
        case 10:
            arg3->unk08.z = temp_r31->scale.z * (arg2 + temp_r31->pos.z);
            break;
        case 11:
            arg3->unk20.x = temp_r31->scale.x * (arg2 + temp_r31->pos.x);
            break;
        case 12:
            arg3->unk20.y = temp_r31->scale.y * (arg2 + temp_r31->pos.y);
            break;
        case 13:
            arg3->unk20.z = temp_r31->scale.z * (arg2 + temp_r31->pos.z);
            break;
        case 14:
            VECSubtract(&arg3->unk08, &arg3->unk20, &spC);
            VECNormalize(&spC, &spC);
            sp18.x = spC.x * spC.y * (1.0 - cos(M_PI * arg2 / 180.0)) - spC.z * sin(M_PI * arg2 / 180.0);
            sp18.y = spC.y * spC.y + (1.0f - spC.y * spC.y) * cos(M_PI * arg2 / 180.0);
            sp18.z = spC.y * spC.z * (1.0 - cos(M_PI * arg2 / 180.0)) + spC.x * sin(M_PI * arg2 / 180.0);
            VECNormalize(&sp18, &arg3->unk14);
            break;
    }
}

float InterpolateBMLine(float *arg0, float *arg1, float arg2) {
    float sp8[2];
    float temp_f22;
    float var_f21;
    float temp_f20;
    float temp_f29;
    float temp_f31;
    float var_f28;
    float var_f27;
    float var_f26;
    float var_f25;
    float var_f24;
    float var_f23;
    float var_f30;
    s32 var_r30;
    s32 var_r29;
    s32 i;

    if (arg0[0] == arg0[1] && arg0[0] == arg0[2] && arg0[0] == arg0[3]) {
        return arg0[0];
    }
    for (i = 1; i <= 2; i++) {
        sp8[i - 1] = 0.5f * ((arg0[i] - arg0[i - 1]) / (arg1[i] - arg1[i - 1]) + (arg0[i + 1] - arg0[i]) / (arg1[i + 1] - arg1[i]));
    }
    temp_f29 = 0.5f * (arg1[2] + arg1[1]);
    var_r30 = 0;
    if (sp8[1] - sp8[0] != 0.0f) {
        temp_f22 = (sp8[1] * arg1[2] - sp8[0] * arg1[1] - (arg0[2] - arg0[1])) / (sp8[1] - sp8[0]);
        var_r29 = 0;
        if (arg1[1] <= temp_f22 && temp_f22 <= arg1[2]) {
            var_r29 = 1;
        }
        var_r30 = (var_r29 != 0) ? 1 : 0;
    }
    if (var_r30 == 1) {
        temp_f31 = temp_f29 - arg1[1];
        temp_f20 = (arg0[2] - arg0[1]) / (arg1[2] - arg1[1]) - (sp8[1] - sp8[0]) / 2;
        var_f28 = temp_f20 * temp_f31 + ((sp8[1] - sp8[0]) / (2.0f * (arg1[2] - arg1[1]))) * temp_f31 * temp_f31 + arg0[1];
        var_f27 = temp_f20 + temp_f31 * ((sp8[1] - sp8[0]) / (arg1[2] - arg1[1]));
    } else {
        temp_f31 = temp_f29 - arg1[1];
        var_f28 = (arg0[2] + arg0[1]) * (temp_f31 / (arg1[2] - arg1[1]));
        var_f27 = 2.0f * (arg0[2] - arg0[1]) / (arg1[2] - arg1[1]) - (sp8[1] + sp8[0]) * (temp_f31 / (arg1[2] - arg1[1]));
    }
    if (arg2 < temp_f29) {
        var_f30 = arg1[1];
        var_f26 = arg0[1];
        var_f25 = sp8[0];
        var_f24 = temp_f29;
        var_f21 = var_f28;
        var_f23 = var_f27;
    } else {
        var_f30 = temp_f29;
        var_f26 = var_f28;
        var_f25 = var_f27;
        var_f24 = arg1[2];
        var_f21 = arg0[2];
        var_f23 = sp8[1];
    }
    return ((var_f23 - var_f25) / (2.0f * (var_f24 - var_f30))) * (arg2 - var_f30) * (arg2 - var_f30) + (arg2 - var_f30) * ((var_f21 - var_f26) / (var_f24 - var_f30) - (var_f23 - var_f25) / 2) + var_f26;
}

void Hu3D2Dto3D(Vec *arg0, s16 arg1, Vec *arg2) {
    CameraData *temp_r31;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    s16 i;
    Mtx spC;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            break;
        }
    }
    temp_r31 = &Hu3DCamera[i];
    temp_f30 = sin((temp_r31->fov / 2) * M_PI / 180.0) / cos((temp_r31->fov / 2) * M_PI / 180.0);
    temp_f31 = temp_f30 * arg0->z * 2.0f;
    temp_f29 = temp_f31 * 1.2f;
    temp_f28 = arg0->x / 576.0f;
    temp_f27 = arg0->y / 480.0f;
    arg2->x = (temp_f28 - 0.5) * temp_f29;
    arg2->y = -(temp_f27 - 0.5) * temp_f31;
    arg2->z = -arg0->z;
    C_MTXLookAt(spC, &temp_r31->pos, &temp_r31->up, &temp_r31->target);
    PSMTXInverse(spC, spC);
    PSMTXMultVec(spC, arg2, arg2);
}

void Hu3D3Dto2D(Vec *arg0, s16 arg1, Vec *arg2) {
    Vec sp10;
    CameraData *temp_r31;
    float temp_f31;
    float temp_f30;
    s16 i;
    Mtx sp1C;

    for (i = 0; i < 16; i++) {
        if (arg1 & (1 << i)) {
            break;
        }
    }
    temp_r31 = &Hu3DCamera[i];
    C_MTXLookAt(sp1C, &temp_r31->pos, &temp_r31->up, &temp_r31->target);
    PSMTXMultVec(sp1C, arg0, &sp10);
    temp_f31 = (sin((temp_r31->fov / 2) * M_PI / 180.0) / cos((temp_r31->fov / 2) * M_PI / 180.0)) * sp10.z * 1.2f;
    temp_f30 = (sin((temp_r31->fov / 2) * M_PI / 180.0) / cos((temp_r31->fov / 2) * M_PI / 180.0)) * sp10.z;
    arg2->x = 288.0f + sp10.x * (288.0f / -temp_f31);
    arg2->y = 240.0f + sp10.y * (240.0f / temp_f30);
    arg2->z = 0.0f;
}

void Hu3DMtxTransGet(Mtx arg0, Vec *arg1) {
    arg1->x = arg0[0][3];
    arg1->y = arg0[1][3];
    arg1->z = arg0[2][3];
}

static inline float GetAngleXY(float arg0, float arg1) {
    if (arg1 == 0.0f) {
        if (arg0 >= 0.0f) {
            return M_PI / 2;
        } else {
            return -(M_PI / 2);
        }
    } else {
        return atan2f(arg0, arg1);
    }
}

void Hu3DMtxRotGet(Mtx arg0, Vec *arg1) {
    float sp48;
    float sp44;
    float sp3C;
    float sp34;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    float var_f25;
    float temp_f24;

    temp_f28 = arg0[0][0] * arg0[0][0] + arg0[1][0] * arg0[1][0] + arg0[2][0] * arg0[2][0];
    sp44 = sqrtf(temp_f28);
    if (!(sp44 < 0.00000001f)) {
        temp_f27 = arg0[0][1] * arg0[0][1] + arg0[1][1] * arg0[1][1] + arg0[2][1] * arg0[2][1];
        sp3C = sqrtf(temp_f27);
        if (!(sp3C < 0.00000001f)) {
            temp_f26 = arg0[0][2] * arg0[0][2] + arg0[1][2] * arg0[1][2] + arg0[2][2] * arg0[2][2];
            sp34 = sqrtf(temp_f26);
            if (!(sp34 < 0.00000001f)) {
                temp_f24 = -arg0[2][0] / sp44;
                if (temp_f24 >= 1.0f) {
                    var_f25 = M_PI / 2;
                } else if (temp_f24 <= -1.0f) {
                    var_f25 = -(M_PI / 2);
                } else {
                    var_f25 = asinf(temp_f24);
                }
                arg1->y = var_f25;
                sp48 = cos(arg1->y);
                if (sp48 >= 0.00000001f) {
                    arg1->x = GetAngleXY(arg0[2][1] / sp3C, arg0[2][2] / sp34);
                    arg1->z = GetAngleXY(arg0[1][0], arg0[0][0]);
                } else {
                    arg1->x = GetAngleXY(arg0[0][1], arg0[1][1]);
                    arg1->z = 0.0f;
                }
                arg1->x = MTXRadToDeg(arg1->x);
                arg1->y = MTXRadToDeg(arg1->y);
                arg1->z = MTXRadToDeg(arg1->z);
                return;
            }
        }
    }
    arg1->x = 0.0f;
    arg1->y = 0.0f;
    arg1->z = 0.0f;
}

void Hu3DMtxScaleGet(Mtx arg0, Vec *arg1) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    sp2C.x = arg0[0][0];
    sp2C.y = arg0[1][0];
    sp2C.z = arg0[2][0];
    arg1->x = VECMag(&sp2C);
    VECNormalize(&sp2C, &sp2C);
    sp20.x = arg0[0][1];
    sp20.y = arg0[1][1];
    sp20.z = arg0[2][1];
    sp38.x = VECDotProduct(&sp2C, &sp20);
    VECScale(&sp2C, &sp8, sp38.x);
    VECSubtract(&sp20, &sp8, &sp20);
    arg1->y = VECMag(&sp20);
    VECNormalize(&sp20, &sp20);
    sp38.x /= arg1->y;
    sp14.x = arg0[0][2];
    sp14.y = arg0[1][2];
    sp14.z = arg0[2][2];
    sp38.z = VECDotProduct(&sp20, &sp14);
    VECScale(&sp20, &sp8, sp38.z);
    VECSubtract(&sp14, &sp8, &sp14);
    sp38.y = VECDotProduct(&sp2C, &sp14);
    VECScale(&sp2C, &sp8, sp38.y);
    VECSubtract(&sp14, &sp8, &sp14);
    arg1->z = VECMag(&sp14);
    VECNormalize(&sp14, &sp14);
    VECCrossProduct(&sp20, &sp14, &sp8);
    if (VECDotProduct(&sp2C, &sp8) < 0.0) {
        arg1->x *= -1.0;
        arg1->y *= -1.0;
        arg1->z *= -1.0;
    }
}
