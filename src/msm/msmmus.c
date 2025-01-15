#include "msm/msmmus.h"
#include "msm/msmmem.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ SND_SEQID unk08;
    /* 0x0C */ void* unk0C;
    /* 0x10 */ void* unk10;
    /* 0x14 */ volatile s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s8 unk1C;
    /* 0x1D */ char unk1D[3];
    /* 0x20 */ volatile s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s8 unk28;
    /* 0x29 */ char unk29[3];
    /* 0x2C */ volatile s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ char unk34[1];
    /* 0x35 */ volatile s8 unk35;
    /* 0x36 */ s8 unk36;
    /* 0x37 */ char unk37[1];
    /* 0x38 */ SND_PLAYPARA unk38;
} msmMusStruct00; // Size 0x58

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s8 unk0C;
    /* 0x0D */ s8 unk0D;
    /* 0x0E */ char unk0E[2];
} msmMusStruct01; // Size 0x10

typedef struct {
    /* 0x000 */ s16 unk00;
    /* 0x002 */ s8 unk02;
    /* 0x003 */ s8 unk03;
    /* 0x004 */ s8 unk04;
    /* 0x005 */ char unk05[3];
    /* 0x008 */ s32 unk08;
    /* 0x00C */ msmMusStruct01* unk0C;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ void* unk14;
    /* 0x018 */ msmMusStruct00 unk18[1]; // unknown length
    /* 0x01C */ char unk70[0x108];
} msmMusStruct02; // Size 0x178

typedef struct {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ s32 unk0C;
} UnkGroupDataPtr; // Size unknown

static msmMusStruct02 mus;

static void msmMusPauseSub(msmMusStruct00* arg0, BOOL pause, s32 speed) {
    s32 temp_r30;

    temp_r30 = speed / 15;
    if (pause) {
        if (arg0->unk04 == 2) {
            if (temp_r30 != 0) {
                arg0->unk24 = temp_r30;
                arg0->unk20 = temp_r30;
                arg0->unk28 = 0x7F;
            } else {
                sndSeqPause(arg0->unk08);
                arg0->unk28 = 0;
            }
            arg0->unk04 = 3;
        }
    } else {
        if (arg0->unk04 == 3) {
            if (temp_r30 != 0) {
                if (arg0->unk20 != 0) {
                    arg0->unk20 = -temp_r30;
                } else {
                    sndSeqContinue(arg0->unk08);
                    arg0->unk20 = -temp_r30;
                    arg0->unk24 = 0;
                    arg0->unk28 = 0;
                }
            } else {
                sndSeqContinue(arg0->unk08);
                arg0->unk28 = 0x7F;
                sndSeqVolume(arg0->unk02 * arg0->unk03 * arg0->unk1C * arg0->unk28 / 2048383, 0, arg0->unk08, 0);
            }
            arg0->unk04 = 2;
        }
    }
}

static void msmMusPauseFade(msmMusStruct00* arg0) {
    if (arg0->unk20 > 0) {
        if (--arg0->unk24 == 0) {
            arg0->unk20 = 0;
            arg0->unk28 = 0;
            sndSeqPause(arg0->unk08);
        } else {
            arg0->unk28 = arg0->unk24 * 0x7F / arg0->unk20;
            sndSeqVolume(arg0->unk02 * arg0->unk03 * arg0->unk1C * arg0->unk28 / 2048383, 0, arg0->unk08, 0);
        }
    } else if (arg0->unk20 < 0) {
        if (++arg0->unk24 >= -arg0->unk20) {
            arg0->unk20 = 0;
            arg0->unk28 = 0x7F;
        } else {
            arg0->unk28 = arg0->unk24 * 0x7F / -arg0->unk20;
        }
        sndSeqVolume(arg0->unk02 * arg0->unk03 * arg0->unk1C * arg0->unk28 / 2048383, 0, arg0->unk08, 0);
    }
}

static void msmMusFade(msmMusStruct00* arg0) {
    if (arg0->unk04 != 2) {
        return;
    }
    if (arg0->unk14 > 0) {
        if (--arg0->unk18 == 0) {
            if (arg0->unk04 != 0) {
                arg0->unk14 = 0;
                if (arg0->unk14 != 0) {
                    arg0->unk18 = arg0->unk14;
                    arg0->unk1C = 0x7F;
                } else {
                    sndSeqStop(arg0->unk08);
                    arg0->unk04 = 1;
                }
            }
        } else {
            arg0->unk1C = arg0->unk18 * 0x7F / arg0->unk14;
            sndSeqVolume(arg0->unk02 * arg0->unk03 * arg0->unk1C * arg0->unk28 / 2048383, 0, arg0->unk08, 0);
        }
    } else if (arg0->unk14 < 0) {
        if (++arg0->unk18 >= -arg0->unk14) {
            arg0->unk14 = 0;
            arg0->unk1C = 0x7F;
        } else {
            arg0->unk1C = arg0->unk18 * 0x7F / -arg0->unk14;
        }
        sndSeqVolume(arg0->unk02 * arg0->unk03 * arg0->unk1C * arg0->unk28 / 2048383, 0, arg0->unk08, 0);
    }
}

void msmMusFdoutEnd(void) {
}

void msmMusPeriodicProc(void) {
    s32 var_r26;
    msmMusStruct00* temp_r25;

    mus.unk04 = mus.unk03 = 0;
    for (var_r26 = 0; var_r26 < mus.unk02; var_r26++) {
        temp_r25 = &mus.unk18[var_r26];
        if (temp_r25->unk05 != 0) {
            continue;
        }
        switch (temp_r25->unk04) {
            case 1:
            case 2:
                if (sndSeqGetValid(temp_r25->unk08) == FALSE) {
                    temp_r25->unk04 = 0;
                }
                break;
        }
        if (temp_r25->unk04 == 0) {
            continue;
        }
        if (msmSysCheckBaseGroup(mus.unk0C[temp_r25->unk00].unk00) != 0) {
            mus.unk04++;
        } else {
            mus.unk03++;
        }
        msmMusPauseFade(temp_r25);
        if (temp_r25->unk04 == 2 && temp_r25->unk2C != 0) {
            if (++temp_r25->unk30 >= temp_r25->unk2C) {
                temp_r25->unk2C = 0;
                temp_r25->unk02 = temp_r25->unk36;
            } else {
                temp_r25->unk02 = temp_r25->unk35 + temp_r25->unk30 * (temp_r25->unk36 - temp_r25->unk35) / temp_r25->unk2C;
            }
            sndSeqVolume(temp_r25->unk02 * temp_r25->unk03 * temp_r25->unk1C * temp_r25->unk28 / 2048383, 0, temp_r25->unk08, 0);
        }
        msmMusFade(temp_r25);
    }
}

s32 msmMusGetMidiCtrl(int musNo, s32 channel, s32 ctrl) {
    msmMusStruct00* temp_ptr;

    if (musNo < 0 || musNo >= mus.unk02) {
        return MSM_ERR_OUTOFMUS;
    }
    temp_ptr = &mus.unk18[musNo];
    if (sndSeqGetValid(temp_ptr->unk08) == TRUE) {
        return sndSeqGetMidiCtrl(temp_ptr->unk08, channel & 0xF, ctrl);
    }
    return 0;
}

s32 msmMusGetNumPlay(BOOL baseGrp) {
    switch (baseGrp) {
        case FALSE:
            return mus.unk03 + mus.unk04;
        default:
            return mus.unk03;
    }
}

s32 msmMusGetStatus(int musNo) {
    if (musNo < 0 || musNo >= mus.unk02) {
        return MSM_ERR_OUTOFMUS;
    }
    return mus.unk18[musNo].unk04;
}

void msmMusSetMasterVolume(s32 arg0) {
    sndMasterVolume(arg0 & 0x7F, 0, 1, 0);
}

s32 msmMusSetParam(s32 arg0, MSM_MUSPARAM* arg1) {
    msmMusStruct00* temp_r31;

    if (arg0 < 0 || arg0 >= mus.unk02) {
        return MSM_ERR_OUTOFMUS;
    }
    temp_r31 = &mus.unk18[arg0];
    if (arg1->flag & MSM_MUSPARAM_VOL) {
        temp_r31->unk2C = arg1->fadeSpeed / 15;
        if (temp_r31->unk2C != 0) {
            temp_r31->unk05 = 1;
            temp_r31->unk30 = 0;
            temp_r31->unk35 = temp_r31->unk02;
            temp_r31->unk36 = arg1->vol & 0x7F;
            temp_r31->unk05 = 0;
        } else {
            temp_r31->unk02 = arg1->vol & 0x7F;
            sndSeqVolume(temp_r31->unk02 * temp_r31->unk03 * temp_r31->unk1C * temp_r31->unk28 / 2048383, 0, temp_r31->unk08, 0);
        }
    }
    if (arg1->flag & MSM_MUSPARAM_SPEED) {
        sndSeqSpeed(temp_r31->unk08, (arg1->speed << 8) / 100);
    }
    return 0;
}

void msmMusPauseAll(BOOL pause, s32 speed) {
    s32 var_r27;
    msmMusStruct00* temp_r26;

    for (var_r27 = 0; var_r27 < mus.unk02; var_r27++) {
        temp_r26 = &mus.unk18[var_r27];
        if (temp_r26->unk04 != 0) {
            temp_r26->unk05 = 1;
            msmMusPauseSub(temp_r26, pause, speed);
            temp_r26->unk05 = 0;
        }
    }
}

s32 msmMusPause(int musNo, BOOL pause, s32 speed) {
    msmMusStruct00* temp_r31;

    if (musNo < 0 || musNo >= mus.unk02) {
        return MSM_ERR_OUTOFMUS;
    }
    temp_r31 = &mus.unk18[musNo];
    temp_r31->unk05 = 1;
    msmMusPauseSub(temp_r31, pause, speed);
    temp_r31->unk05 = 0;
    return 0;
}

void msmMusStopAll(BOOL checkGrp, s32 speed) {
    s32 var_r28;
    msmMusStruct00* temp_r27;

    for (var_r28 = 0; var_r28 < mus.unk02; var_r28++) {
        temp_r27 = &mus.unk18[var_r28];
        if (temp_r27->unk04 == 0) {
            continue;
        }
        temp_r27->unk05 = 1;
        switch (checkGrp) {
            case FALSE:
                if (temp_r27->unk04 != 0) {
                    temp_r27->unk14 = speed / 15;
                    if (temp_r27->unk14 != 0) {
                        temp_r27->unk18 = temp_r27->unk14;
                        temp_r27->unk1C = 0x7F;
                    } else {
                        sndSeqStop(temp_r27->unk08);
                        temp_r27->unk04 = 1;
                    }
                }
                break;
            default:
                if (msmSysCheckBaseGroup(mus.unk0C[temp_r27->unk00].unk00) == 0 && temp_r27->unk04 != 0) {
                    temp_r27->unk14 = speed / 15;
                    if (temp_r27->unk14 != 0) {
                        temp_r27->unk18 = temp_r27->unk14;
                        temp_r27->unk1C = 0x7F;
                    } else {
                        sndSeqStop(temp_r27->unk08);
                        temp_r27->unk04 = 1;
                    }
                }
                break;
        }
        temp_r27->unk05 = 0;
    }
}

s32 msmMusStop(int musNo, s32 speed) {
    msmMusStruct00* temp_r30;

    if (musNo < 0 || musNo >= mus.unk02) {
        return MSM_ERR_OUTOFMUS;
    }
    temp_r30 = &mus.unk18[musNo];
    temp_r30->unk05 = 1;
    if (temp_r30->unk04 != 0) {
        temp_r30->unk14 = speed / 15;
        if (temp_r30->unk14 != 0) {
            temp_r30->unk18 = temp_r30->unk14;
            temp_r30->unk1C = 0x7F;
        } else {
            sndSeqStop(temp_r30->unk08);
            temp_r30->unk04 = 1;
        }
    }
    temp_r30->unk05 = 0;
    return 0;
}

int msmMusPlay(int musId, MSM_MUSPARAM* musParam) {
    s32 var_r30;
    int var_r29;
    s32 temp_r3_3;
    UnkGroupDataPtr* temp_r3_2;
    msmMusStruct01* temp_r28;
    msmMusStruct00* temp_r27;
    DVDFileInfo sp10;

    if (musId < 0 || musId >= mus.unk00) {
        return MSM_ERR_INVALIDID;
    }
    temp_r28 = &mus.unk0C[musId];
    if (temp_r28->unk00 == 0xFFFF) {
        return MSM_ERR_REMOVEDID;
    }
    if (msmSysCheckLoadGroupID(temp_r28->unk00) == 0) {
        return MSM_ERR_GRP_NOTLOADED;
    }
    var_r30 = (musParam != NULL) ? musParam->flag : 0;
    var_r29 = (var_r30 & MSM_MUSPARAM_CHAN) ? musParam->chan : 0;
    if (var_r29 < 0 || var_r29 >= mus.unk02) {
        return MSM_ERR_OUTOFMUS;
    }
    temp_r27 = &mus.unk18[var_r29];
    if (temp_r27->unk04 != 0) {
        sndSeqStop(temp_r27->unk08);
    }
    if (temp_r28->unk0C < 0) {
        if (temp_r27->unk00 != musId) {
            if (msmFioOpen(mus.unk08, &sp10) != 1) {
                return MSM_ERR_OPENFAIL;
            }
            if (msmFioRead(&sp10, temp_r27->unk0C, temp_r28->unk08, temp_r28->unk04 + mus.unk10) < 0) {
                msmFioClose(&sp10);
                return MSM_ERR_READFAIL;
            }
            msmFioClose(&sp10);
            temp_r27->unk10 = temp_r27->unk0C;
        }
    } else {
        temp_r3_2 = msmSysGetGroupDataPtr(temp_r28->unk0C);
        if (temp_r3_2 == NULL) {
            return MSM_ERR_MUSGRP_NOTLOADED;
        }
        temp_r27->unk10 = (void*) ((u32) temp_r3_2 + temp_r3_2->unk0C + temp_r28->unk04);
    }
    temp_r27->unk05 = 1;
    temp_r27->unk03 = temp_r28->unk0D;
    temp_r27->unk2C = 0;
    temp_r27->unk20 = 0;
    temp_r27->unk14 = 0;
    temp_r27->unk28 = 0x7F;
    temp_r27->unk1C = 0x7F;
    temp_r27->unk38.flags = 4;
    temp_r27->unk38.volume.time = 0;
    temp_r27->unk02 = (var_r30 & MSM_MUSPARAM_VOL) ? musParam->vol : 0x7F;
    temp_r27->unk38.volume.target = temp_r27->unk03 * temp_r27->unk1C * temp_r27->unk02 / 16129;
    if (var_r30 & MSM_MUSPARAM_PAUSE) {
        temp_r27->unk38.flags |= 0x10;
    }
    if (var_r30 & MSM_MUSPARAM_SPEED) {
        temp_r27->unk38.flags |= 2;
        temp_r27->unk38.speed = musParam->speed * 256 / 100;
    }
    if (var_r30 & MSM_MUSPARAM_FADESPEED) {
        temp_r27->unk14 = -(musParam->fadeSpeed / 15);
        if (temp_r27->unk14 != 0) {
            temp_r27->unk18 = 0;
            temp_r27->unk1C = 0;
            temp_r27->unk38.volume.target = 0;
        }
    }
    temp_r3_3 = sndSeqPlayEx(temp_r28->unk00, temp_r28->unk02, temp_r27->unk10, &temp_r27->unk38, 0);
    if (temp_r3_3 == SND_ID_ERROR) {
        temp_r27->unk05 = 0;
        return MSM_ERR_PLAYFAIL;
    }
    temp_r27->unk08 = temp_r3_3;
    temp_r27->unk00 = musId;
    temp_r27->unk04 = (temp_r27->unk38.flags & 0x10) ? 3 : 2;
    temp_r27->unk05 = 0;
    return var_r29;
}

s32 msmMusInit(sysData* arg0, DVDFileInfo* arg1) {
    s32 temp_r4;
    s32 var_r8;

    mus.unk00 = 0;
    mus.unk02 = 0;
    mus.unk04 = 0;
    mus.unk03 = 0;
    if (arg0->unk10->unk4 == 0) {
        return 0;
    }
    temp_r4 = arg0->unkC->unk2C;
    if (temp_r4 == 0) {
        return 0;
    }
    if ((mus.unk0C = msmMemAlloc(temp_r4)) == NULL) {
        return MSM_ERR_OUTOFMEM;
    }
    if (msmFioRead(arg1, mus.unk0C, arg0->unkC->unk2C, arg0->unkC->unk28) < 0) {
        return MSM_ERR_READFAIL;
    }
    temp_r4 = arg0->unk10->unk20;
    if (temp_r4 != 0) {
        if ((mus.unk14 = msmMemAlloc(temp_r4 * arg0->unk10->unk8)) == NULL) {
            return MSM_ERR_OUTOFMEM;
        }
    } else {
        mus.unk14 = NULL;
    }
    mus.unk00 = arg0->unk10->unk4;
    mus.unk02 = arg0->unk10->unk8;
    mus.unk10 = arg0->unkC->unk48;
    mus.unk08 = arg0->unk0;
    for (var_r8 = 0; var_r8 < mus.unk02; var_r8++) {
        mus.unk18[var_r8].unk0C = (void*) ((u32) mus.unk14 + arg0->unk10->unk20 * var_r8);
        mus.unk18[var_r8].unk00 = -1;
        mus.unk18[var_r8].unk05 = 0;
    }
    return 0;
}
