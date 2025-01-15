#include "msm/msmse.h"
#include "msm/msmfio.h"
#include "msm/msmmem.h"

typedef struct {
    /* 0x00 */ SND_VOICEID unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s8 unk0A;
    /* 0x0B */ s8 unk0B;
    /* 0x0C */ s8 unk0C;
    /* 0x0D */ s8 unk0D;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s8 unk10;
    /* 0x11 */ s8 unk11;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ SND_PARAMETER_INFO unk14;
    /* 0x1C */ SND_PARAMETER unk1C[5];
    /* 0x30 */ s8 unk30;
    /* 0x31 */ s8 unk31;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ volatile s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s8 unk3C;
    /* 0x3D */ char unk3D[3];
    /* 0x40 */ volatile s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s8 unk48;
    /* 0x49 */ char unk49[3];
    /* 0x4C */ SND_EMITTER unk4C;
    /* 0x9C */ SND_FVECTOR unk9C;
    /* 0xA8 */ SND_FVECTOR unkA8;
    /* 0xB4 */ s8 unkB4;
    /* 0xB5 */ char unkB5[3];
} msmSeStruct00; // Size 0xB8

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ char unk07[1];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ MSMSE* unk0C;
    /* 0x10 */ msmSeStruct00* unk10;
    /* 0x14 */ SND_LISTENER unk14;
    /* 0xA4 */ SND_FVECTOR unkA4;
    /* 0xB0 */ SND_FVECTOR unkB0;
    /* 0xBC */ SND_FVECTOR unkBC;
    /* 0xC8 */ SND_FVECTOR unkC8;
    /* 0xD4 */ float unkD4;
    /* 0xD8 */ u16 unkD8;
    /* 0xDA */ u16 unkDA;
} msmSeStruct02; // Size 0xDC

msmSeStruct02 se;

static void msmSeFade(msmSeStruct00* arg0) {
    u8 temp_r3;

    if (arg0->unk0A == 3) {
        return;
    }
    if (arg0->unk34 > 0) {
        if (--arg0->unk38 == 0) {
            arg0->unk34 = 0;
            arg0->unk34 = 0;
            if (arg0->unk34 != 0) {
                arg0->unk38 = arg0->unk34;
                arg0->unk3C = 0x7F;
            } else {
                arg0->unk0A = 1;
                if ((arg0->unk13 & 1) && arg0->unkB4 == 1) {
                    sndRemoveEmitter(&arg0->unk4C);
                } else {
                    sndFXKeyOff(arg0->unk00);
                }
            }
        } else {
            arg0->unk3C = arg0->unk38 * 0x7F / arg0->unk34;
            temp_r3 = arg0->unk0C * arg0->unk30 * arg0->unk3C * arg0->unk48 / 2048383;
            if ((arg0->unk13 & 1) && arg0->unkB4 == 1) {
                arg0->unkA8.x = arg0->unkA8.y = arg0->unkA8.z = 0.0f;
                sndUpdateEmitter(&arg0->unk4C, &arg0->unk9C, &arg0->unkA8, temp_r3, NULL);
            } else {
                sndFXVolume(arg0->unk00, temp_r3);
            }
        }
    } else if (arg0->unk34 < 0) {
        if (++arg0->unk38 >= -arg0->unk34) {
            arg0->unk34 = 0;
            arg0->unk3C = 0x7F;
        } else {
            arg0->unk3C = arg0->unk38 * 0x7F / -arg0->unk34;
        }
        temp_r3 = arg0->unk0C * arg0->unk30 * arg0->unk3C * arg0->unk48 / 2048383;
        if ((arg0->unk13 & 1) && arg0->unkB4 == 1) {
            arg0->unkA8.x = arg0->unkA8.y = arg0->unkA8.z = 0.0f;
            sndUpdateEmitter(&arg0->unk4C, &arg0->unk9C, &arg0->unkA8, temp_r3, NULL);
        } else {
            sndFXVolume(arg0->unk00, temp_r3);
        }
    }
}

static void msmSePauseSub(msmSeStruct00* arg0, BOOL pause, s32 speed) {
    s32 temp_r3;

    temp_r3 = speed / 15;
    if (pause) {
        if (arg0->unk0A == 2) {
            if (temp_r3 != 0) {
                arg0->unk40 = arg0->unk44 = temp_r3;
                arg0->unk48 = 0x7F;
            } else {
                arg0->unk48 = 0;
                sndFXVolume(arg0->unk00, arg0->unk0C * arg0->unk30 * arg0->unk3C * arg0->unk48 / 2048383);
            }
            arg0->unk0A = 3;
        }
    } else {
        if (arg0->unk0A == 3) {
            if (temp_r3 != 0) {
                if (arg0->unk40 != 0) {
                    arg0->unk40 = -temp_r3;
                } else {
                    arg0->unk40 = -temp_r3;
                    arg0->unk44 = 0;
                    arg0->unk48 = 0;
                }
            } else {
                arg0->unk48 = 0x7F;
                sndFXVolume(arg0->unk00, arg0->unk0C * arg0->unk30 * arg0->unk3C * arg0->unk48 / 2048383);
            }
            arg0->unk0A = 2;
        }
    }
}

void msmSePeriodicProc(void) {
    s32 var_r26;
    msmSeStruct00* temp_r3;
    u8 temp_r3_3;

    se.unk05 = se.unk06 = 0;
    for (var_r26 = 0; var_r26 < se.unk04; var_r26++) {
        temp_r3 = &se.unk10[var_r26];
        if (temp_r3->unk0B != 0) {
            continue;
        }
        switch (temp_r3->unk0A) {
            case 1:
            case 2:
                if ((temp_r3->unk13 & 1) && temp_r3->unkB4 == 1) {
                    if (!sndCheckEmitter(&temp_r3->unk4C)) {
                        temp_r3->unk0A = 0;
                    }
                } else {
                    if (sndFXCheck(temp_r3->unk00) == SND_ID_ERROR) {
                        temp_r3->unk0A = 0;
                    }
                }
                break;
        }
        if (temp_r3->unk0A == 0) {
            continue;
        }
        if (msmSysCheckBaseGroup(se.unk0C[temp_r3->unk08].groupId) != 0) {
            se.unk05++;
        } else {
            se.unk06++;
        }
        if (temp_r3->unk40 > 0) {
            if (--temp_r3->unk44 == 0) {
                temp_r3->unk40 = 0;
                temp_r3->unk48 = 0;
            } else {
                temp_r3->unk48 = temp_r3->unk44 * 0x7F / temp_r3->unk40;
            }
        } else if (temp_r3->unk40 < 0) {
            if (++temp_r3->unk44 >= -temp_r3->unk40) {
                temp_r3->unk40 = 0;
                temp_r3->unk48 = 0x7F;
            } else {
                temp_r3->unk48 = temp_r3->unk44 * 0x7F / -temp_r3->unk40;
            }
        }
        temp_r3_3 = temp_r3->unk0C * temp_r3->unk30 * temp_r3->unk3C * temp_r3->unk48 / 2048383;
        if ((temp_r3->unk13 & 1) && temp_r3->unkB4 == 1) {
            temp_r3->unkA8.x = temp_r3->unkA8.y = temp_r3->unkA8.z = 0.0f;
            sndUpdateEmitter(&temp_r3->unk4C, &temp_r3->unk9C, &temp_r3->unkA8, temp_r3_3, NULL);
        } else {
            sndFXVolume(temp_r3->unk00, temp_r3_3);
        }
        msmSeFade(temp_r3);
    }
}

MSMSE* msmSeGetIndexPtr(s32 arg0) {
    if (arg0 < 0 || arg0 >= se.unk00) {
        return NULL;
    }
    return &se.unk0C[arg0];
}

void msmSeDelListener(void) {
    if (se.unkDA != 0) {
        sndRemoveListener(&se.unk14);
        se.unkDA = 0;
    }
}

s32 msmSeUpdataListener(Vec* pos, Vec* heading) {
    if (se.unkDA == 0) {
        return MSM_ERR_22;
    }
    se.unkB0.x = pos->x - se.unkA4.x;
    se.unkB0.y = pos->y - se.unkA4.y;
    se.unkB0.z = pos->z - se.unkA4.z;
    se.unkA4.x = pos->x;
    se.unkA4.y = pos->y;
    se.unkA4.z = pos->z;
    se.unkBC.x = heading->x;
    se.unkBC.y = heading->y;
    se.unkBC.z = heading->z;
    if (!sndUpdateListener(&se.unk14, &se.unkA4, &se.unkB0, &se.unkBC, &se.unkC8, 0x7F, NULL)) {
        return MSM_ERR_22;
    }
    return 0;
}

s32 msmSeSetListener(Vec* pos, Vec* heading, float sndDist, float sndSpeed, MSM_SELISTENER* listener) {
    SND_FVECTOR* temp_b0;
    SND_FVECTOR* temp_a4;
    SND_FVECTOR* temp_c8;
    SND_FVECTOR* temp_bc;
    s32 var_r3;
    float var_f4;
    float var_f0;
    float var_f0_2;

    temp_a4 = &se.unkA4;
    temp_c8 = &se.unkC8;
    temp_bc = &se.unkBC;
    temp_b0 = &se.unkB0;
    temp_a4->x = pos->x;
    temp_a4->y = pos->y;
    temp_a4->z = pos->z;
    temp_c8->x = temp_c8->z = 0.0f;
    temp_c8->y = 1.0f;
    temp_bc->x = heading->x;
    temp_bc->y = heading->y;
    temp_bc->z = heading->z;
    temp_b0->x = temp_b0->y = temp_b0->z = 0.0f;
    se.unkD4 = sndDist;
    var_r3 = (listener != NULL) ? listener->flag : 0;
    var_f4 = (var_r3 & 1) ? listener->startDis : 0.0f;
    var_f0 = (var_r3 & 2) ? listener->frontSurDis : (var_f4 + sndDist * 0.25f);
    var_f0_2 = (var_r3 & 4) ? listener->backSurDis : (var_f4 + sndDist * 0.25f);
    if ((s32) sndAddListenerEx(&se.unk14, temp_a4, temp_b0, temp_bc, temp_c8,
        var_f0, var_f0_2, sndSpeed, -var_f4, 1, 0x7F, NULL) == FALSE)
    {
        se.unkDA = 0;
        return MSM_ERR_22;
    }
    se.unkDA = 1;
    return 0;
}

s32 msmSeGetEntryID(s32 seId, int* seNo) {
    msmSeStruct00* temp_r8;
    s32 var_r9;
    s32 var_r10;

    for (var_r9 = var_r10 = 0; var_r9 < se.unk04; var_r9++) {
        temp_r8 = &se.unk10[var_r9];
        if (temp_r8->unk0A != 0 && temp_r8->unk08 == seId) {
            if (seNo != NULL) {
                seNo[var_r10] = temp_r8->unk04;
            }
            var_r10++;
        }
    }
    return var_r10;
}

s32 msmSeGetNumPlay(BOOL baseGrp) {
    switch (baseGrp) {
        case FALSE:
            return se.unk06 + se.unk05;
        default:
            return se.unk06;
    }
}

static inline msmSeStruct00* msmSeGetStatus_inline(s32 seNo) {
    msmSeStruct00* var_r4;
    s32 var_ctr;

    for (var_ctr = 0; var_ctr < se.unk04; var_ctr++) {
        var_r4 = &se.unk10[var_ctr];
        if (var_r4->unk0A != 0 && var_r4->unk04 == seNo) {
            return var_r4;
        }
    }
    return NULL;
}

s32 msmSeGetStatus(int seNo) {
    msmSeStruct00* var_r4;

    var_r4 = msmSeGetStatus_inline(seNo);
    if (var_r4 == NULL) {
        return 0;
    }
    return var_r4->unk0A;
}

void msmSeSetMasterVolume(s32 arg0) {
    sndMasterVolume(arg0 & 0x7F, 0, 0, 1);
}

s32 msmSeSetParam(int seNo, MSM_SEPARAM* param) {
    msmSeStruct00* var_r31;
    int temp_r3;
    s32 var_r4;

    var_r31 = msmSeGetStatus_inline(seNo);
    if (var_r31 == NULL) {
        return MSM_ERR_6F;
    }
    if (param->flag & MSM_SEPARAM_VOL) {
        var_r31->unk0B = 1;
        var_r31->unk0C = param->vol;
        if (!(var_r31->unk13 & 1) || var_r31->unkB4 != 1) {
            sndFXVolume(var_r31->unk00, var_r31->unk0C * var_r31->unk30 * var_r31->unk3C * var_r31->unk48 / 2048383);
        }
        var_r31->unk0B = 0;
    }
    if (!(var_r31->unk13 & 1)) {
        if (param->flag & MSM_SEPARAM_PAN) {
            var_r31->unk0D = param->pan;
            temp_r3 = var_r31->unk0D + var_r31->unk31 - 0x40;
            if (temp_r3 < 0) {
                temp_r3 = 0;
            }
            if (temp_r3 > 0x7F) {
                temp_r3 = 0x7F;
            }
            sndFXPanning(var_r31->unk00, temp_r3);
        }
        if (param->flag & MSM_SEPARAM_PITCH) {
            var_r31->unk0E = param->pitch;
            var_r4 = var_r31->unk0E + var_r31->unk32 + 0x2000;
            if (var_r4 < 0) {
                var_r4 = 0;
            }
            if (var_r4 > 0x3FFF) {
                var_r4 = 0x3FFF;
            }
            sndFXPitchBend(var_r31->unk00, var_r4);
        }
        if (param->flag & MSM_SEPARAM_SPAN) {
            var_r31->unk10 = param->span;
            sndFXSurroundPanning(var_r31->unk00, var_r31->unk10);
        }
    } else if (var_r31->unkB4 == 1) {
        var_r31->unk00 = sndEmitterVoiceID(&var_r31->unk4C);
        if (param->flag & MSM_SEPARAM_POS) {
            var_r31->unk0B = 1;
            var_r31->unkA8.x = param->pos.x - var_r31->unk9C.x;
            var_r31->unkA8.y = param->pos.y - var_r31->unk9C.y;
            var_r31->unkA8.z = param->pos.z - var_r31->unk9C.z;
            var_r31->unk9C.x = param->pos.x;
            var_r31->unk9C.y = param->pos.y;
            var_r31->unk9C.z = param->pos.z;
            sndUpdateEmitter(&var_r31->unk4C, &var_r31->unk9C, &var_r31->unkA8, var_r31->unk0C * var_r31->unk30 * var_r31->unk3C * var_r31->unk48 / 2048383, NULL);
            var_r31->unk0B = 0;
        }
    }
    if (param->flag & MSM_SEPARAM_AUXVOLA) {
        var_r31->unk11 = param->auxAVol;
        sndFXReverb(var_r31->unk00, var_r31->unk11);
    }
    if (param->flag & MSM_SEPARAM_AUXVOLB) {
        var_r31->unk12 = param->auxBVol;
        sndFXChorus(var_r31->unk00, var_r31->unk12);
    }
    if (param->flag & MSM_SEPARAM_PAD) {
        sndSendMessage(var_r31->unk00, param->pad);
    }
    return 0;
}

void msmSePauseAll(BOOL pause, s32 speed) {
    s32 var_r27;
    msmSeStruct00* temp_r26;

    for (var_r27 = 0; var_r27 < se.unk04; var_r27++) {
        temp_r26 = &se.unk10[var_r27];
        temp_r26->unk0B = 1;
        msmSePauseSub(temp_r26, pause, speed);
        temp_r26->unk0B = 0;
    }
}

void msmSeStopAll(BOOL checkGrp, s32 speed) {
    msmSeStruct00* temp_r28;
    s32 var_r27;

    for (var_r27 = 0; var_r27 < se.unk04; var_r27++) {
        temp_r28 = &se.unk10[var_r27];
        if (temp_r28->unk0A == 0) {
            continue;
        }
        temp_r28->unk0B = 1;
        switch (checkGrp) {
            case FALSE:
                temp_r28->unk34 = speed / 15;
                if (temp_r28->unk34 != 0) {
                    temp_r28->unk38 = temp_r28->unk34;
                    temp_r28->unk3C = 0x7F;
                } else {
                    temp_r28->unk0A = 1;
                    if ((temp_r28->unk13 & 1) && temp_r28->unkB4 == 1) {
                        sndRemoveEmitter(&temp_r28->unk4C);
                    } else {
                        sndFXKeyOff(temp_r28->unk00);
                    }
                }
                break;
            default:
                if (msmSysCheckBaseGroup(se.unk0C[temp_r28->unk08].groupId) == 0) {
                    temp_r28->unk34 = speed / 15;
                    if (temp_r28->unk34 != 0) {
                        temp_r28->unk38 = temp_r28->unk34;
                        temp_r28->unk3C = 0x7F;
                    } else {
                        temp_r28->unk0A = 1;
                        if ((temp_r28->unk13 & 1) && temp_r28->unkB4 == 1) {
                            sndRemoveEmitter(&temp_r28->unk4C);
                        } else {
                            sndFXKeyOff(temp_r28->unk00);
                        }
                    }
                }
                break;
        }
        temp_r28->unk0B = 0;
    }
}

s32 msmSeStop(int seNo, s32 speed) {
    msmSeStruct00* var_r31;

    var_r31 = msmSeGetStatus_inline(seNo);
    if (var_r31 == NULL) {
        return MSM_ERR_6F;
    }
    var_r31->unk0B = 1;
    var_r31->unk34 = speed / 15;
    if (var_r31->unk34 != 0) {
        var_r31->unk38 = var_r31->unk34;
        var_r31->unk3C = 0x7F;
    } else {
        var_r31->unk0A = 1;
        if ((var_r31->unk13 & 1) && var_r31->unkB4 == 1) {
            sndRemoveEmitter(&var_r31->unk4C);
        } else {
            sndFXKeyOff(var_r31->unk00);
        }
    }
    var_r31->unk0B = 0;
    return 0;
}

static inline BOOL msmSeInline00(msmSeStruct00* arg0, MSM_SEPARAM* param) {
    BOOL var_r0 = FALSE;

    if (param != NULL) {
        if (param->flag & MSM_SEPARAM_VOL) {
            arg0->unk0C = param->vol;
        }
        if (param->flag & MSM_SEPARAM_PAN) {
            arg0->unk0D = param->pan;
        }
        if (param->flag & MSM_SEPARAM_PITCH) {
            arg0->unk0E = param->pitch;
        }
        if (param->flag & MSM_SEPARAM_SPAN) {
            arg0->unk10 = param->span;
        }
        if (param->flag & MSM_SEPARAM_AUXVOLA) {
            arg0->unk11 = param->auxAVol;
        }
        if (param->flag & MSM_SEPARAM_AUXVOLB) {
            arg0->unk12 = param->auxBVol;
        }
        if ((param->flag & MSM_SEPARAM_POS) && se.unkDA != 0) {
            var_r0 = TRUE;
        }
    }
    arg0->unk14.paraArray = arg0->unk1C;
    return var_r0;
}

int msmSePlay(int seId, MSM_SEPARAM* param) {
    msmSeStruct00* var_r30;
    SND_EMITTER* var_r29;
    MSMSE* temp_r9;
    int var_r3_2;
    s32 var_r4;
    s32 var_r6;
    s32 var_r6_2;

    if (seId < 0 || seId >= se.unk00) {
        return MSM_ERR_INVALIDID;
    }
    temp_r9 = &se.unk0C[seId];
    if (temp_r9->groupId == 0xFFFF) {
        return MSM_ERR_REMOVEDID;
    }
    for (var_r6 = 0; var_r6 < se.unk04; var_r6++) {
        var_r30 = &se.unk10[var_r6];
        if (var_r30->unk0A == 0) {
            break;
        }
    }
    if (var_r6 == se.unk04) {
        return MSM_ERR_6E;
    }
    var_r30->unk30 = temp_r9->vol;
    var_r30->unk31 = temp_r9->pan;
    var_r30->unk32 = temp_r9->pitchBend;
    var_r30->unk0C = 0x7F;
    var_r30->unk0D = 0x40;
    var_r30->unk10 = temp_r9->span;
    var_r30->unk0E = 0;
    var_r30->unk11 = temp_r9->reverb;
    var_r30->unk12 = temp_r9->chorus;
    var_r30->unk40 = 0;
    var_r30->unk34 = 0;
    var_r30->unk48 = 0x7F;
    var_r30->unk3C = 0x7F;
    var_r30->unkB4 = 0;
    if (msmSeInline00(var_r30, param)) {
        var_r30->unk9C.x = param->pos.x;
        var_r30->unk9C.y = param->pos.y;
        var_r30->unk9C.z = param->pos.z;
        var_r30->unk1C[0].ctrl = SND_MIDICTRL_REVERB;
        var_r30->unk1C[0].paraData.value7 = var_r30->unk11;
        var_r30->unk1C[1].ctrl = SND_MIDICTRL_CHORUS;
        var_r30->unk1C[1].paraData.value7 = var_r30->unk12;
        var_r30->unk14.numPara = 2;
        var_r30->unkA8.x = var_r30->unkA8.y = var_r30->unkA8.z = 0.0f;
        if (temp_r9->doppler == 1) {
            var_r29 = &var_r30->unk4C;
            var_r6_2 = 9;
        } else {
            var_r29 = NULL;
            var_r6_2 = 8;
        }
        var_r30->unkB4 = temp_r9->doppler;
        var_r30->unk00 = sndAddEmitterParaEx(var_r29, &var_r30->unk9C, &var_r30->unkA8, se.unkD4, temp_r9->comp / 127.0f, var_r6_2, temp_r9->fxId, se.unkD8++, var_r30->unk0C * var_r30->unk30 / 127, 0, NULL, &var_r30->unk14);
        if (var_r29 != NULL) {
            if (!sndCheckEmitter(var_r29)) {
                return MSM_ERR_PLAYFAIL;
            }
        } else {
            if (var_r30->unk00 == -1) {
                return MSM_ERR_PLAYFAIL;
            }
        }
        var_r30->unk13 |= 1;
    } else {
        var_r30->unk1C[0].ctrl = SND_MIDICTRL_VOLUME;
        var_r30->unk1C[0].paraData.value14 = (var_r30->unk0C * var_r30->unk30 / 127) * 0x81;
        var_r4 = var_r30->unk0D + var_r30->unk31 - 0x40;
        if (var_r4 < 0) {
            var_r4 = 0;
        }
        if (var_r4 > 0x7F) {
            var_r4 = 0x7F;
        }
        var_r30->unk1C[1].ctrl = SND_MIDICTRL_PANNING;
        var_r30->unk1C[1].paraData.value14 = var_r4 * 0x81;
        var_r30->unk1C[2].ctrl = SND_MIDICTRL_REVERB;
        var_r30->unk1C[2].paraData.value7 = var_r30->unk11;
        var_r30->unk1C[3].ctrl = SND_MIDICTRL_CHORUS;
        var_r30->unk1C[3].paraData.value7 = var_r30->unk12;
        var_r3_2 = var_r30->unk0E + var_r30->unk32 + 0x2000;
        if (var_r3_2 > 0x3FFF) {
            var_r3_2 = 0x3FFF;
        } else if (var_r3_2 < 0) {
            var_r3_2 = 0;
        }
        var_r30->unk1C[4].ctrl = SND_MIDICTRL_PITCHBEND;
        var_r30->unk1C[4].paraData.value14 = var_r3_2;
        var_r30->unk14.numPara = 5;
        var_r30->unk00 = sndFXStartParaInfo(temp_r9->fxId, 0xFF, 0xFF, 0, &var_r30->unk14);
        if (var_r30->unk00 == -1) {
            return MSM_ERR_PLAYFAIL;
        }
        sndFXSurroundPanning(var_r30->unk00, var_r30->unk10);
        var_r30->unk13 &= ~1;
    }
    var_r30->unk0B = 1;
    var_r30->unk08 = seId;
    var_r30->unk04 = se.unk08++;
    var_r30->unk0A = 2;
    var_r30->unk0B = 0;
    return var_r30->unk04;
}

s32 msmSeInit(sysData* arg0, DVDFileInfo* arg1) {
    s32 temp_r29;

    se.unk04 = 0;
    se.unk00 = 0;
    se.unk05 = 0;
    se.unk06 = 0;
    se.unkDA = 0;
    if (arg0->unk10->unk6 == 0) {
        return 0;
    }
    if ((se.unk0C = msmMemAlloc(arg0->unkC->unk34)) == NULL) {
        return MSM_ERR_OUTOFMEM;
    }
    if (msmFioRead(arg1, se.unk0C, arg0->unkC->unk34, arg0->unkC->unk30) < 0) {
        return MSM_ERR_READFAIL;
    }
    temp_r29 = arg0->unk10->unk2 * sizeof(*se.unk10);
    if ((se.unk10 = msmMemAlloc(temp_r29)) == NULL) {
        return MSM_ERR_OUTOFMEM;
    }
    memset(se.unk10, 0, temp_r29);
    se.unk00 = arg0->unk10->unk6;
    se.unk04 = arg0->unk10->unk2;
    se.unk08 = 1;
    return 0;
}
