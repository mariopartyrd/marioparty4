#include "game/audio.h"
#include "game/memory.h"
#include "game/msm.h"
#include "game/object.h"
#include "game/wipe.h"
#include "game/gamework_data.h"

static int HuSePlay(int seId, MSM_SEPARAM *param);

extern s16 omSysExitReq;

s32 charVoiceGroupStat[8];
static s32 sndFXBuf[64][2];

static s16 Hu3DAudVol;
static s16 sndGroupBak;
static s32 auxANoBak;
static s32 auxBNoBak;
static s8 HuAuxAVol;
static s8 HuAuxBVol;
float Snd3DBackSurDisOffset;
float Snd3DFrontSurDisOffset;
float Snd3DStartDisOffset;
float Snd3DSpeedOffset;
float Snd3DDistOffset;
s32 musicOffF;
u8 fadeStat;

static char *lbl_8012E9AC[] = {
    "sound/MPNGC02.son",
    "sound/MPNGC16.son",
    ""
};


void HuAudInit(void)
{
    MSM_INIT msmInit;
    MSM_ARAM msmAram;

    s32 result;
    s16 i;

    msmInit.heap = HuMemDirectMalloc(HEAP_MUSIC, 0x13FC00);
    msmInit.heapSize = 0x13FC00;
    msmInit.msmPath = "/sound/mpgcsnd.msm";
    msmInit.pdtPath = "/sound/mpgcstr.pdt";
    msmInit.open = NULL;
    msmInit.read = NULL;
    msmInit.close = NULL;
    msmAram.skipARInit = TRUE;
    msmAram.aramEnd = 0x808000;
    result = msmSysInit(&msmInit, &msmAram);

    if (result < 0) {
        OSReport("MSM(Sound Manager) Error:Error Code %d\n", result);
        while (1);
    }
    if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
        msmSysSetOutputMode(SND_OUTPUTMODE_MONO);
    } else {
        msmSysSetOutputMode(SND_OUTPUTMODE_SURROUND);
    }
    for (i = 0; i < 64; i++) {
        sndFXBuf[i][0] = -1;
    }
    for (i = 0; i < 8; i++) {
        charVoiceGroupStat[i] = 0;
    }
    sndGroupBak = -1;
    auxANoBak = auxBNoBak = -1;
    fadeStat = 0;
    musicOffF = 0;
}

s32 HuAudStreamPlay(char *name, BOOL flag) {
    return 0;
}

void HuAudStreamVolSet(s16 vol) {
    AISetStreamVolLeft(vol);
    AISetStreamVolRight(vol);
    Hu3DAudVol = vol;
}

void HuAudStreamPauseOn(void) {
    AISetStreamPlayState(0);
}

void HuAudStreamPauseOff(void) {
    AISetStreamPlayState(1);
}

void HuAudStreamFadeOut(s32 arg0) {
}

void HuAudAllStop(void) {
    HuAudSeqAllStop();
    HuAudFXAllStop();
    HuAudSStreamAllStop();
}

void HuAudFadeOut(s32 speed) {
    HuAudFXAllStop();
    HuAudSeqAllFadeOut(speed);
    HuAudSStreamAllFadeOut(speed);
}

int HuAudFXPlay(int seId)
{
    WipeState *wipe = &wipeData;

    if (omSysExitReq != 0 || (wipeData.mode == WIPE_MODE_OUT && wipe->time / wipe->duration > 0.5)) {
        return 0;
    }
    return HuAudFXPlayVolPan(seId, MSM_VOL_MAX, MSM_PAN_CENTER);
}

int HuAudFXPlayVol(int seId, s16 vol) {
    if (omSysExitReq != 0) {
        return 0;
    }
    return HuAudFXPlayVolPan(seId, vol, MSM_PAN_CENTER);
}

int HuAudFXPlayVolPan(int seId, s16 vol, s16 pan)
{
    MSM_SEPARAM seParam;

    if (omSysExitReq != 0) {
        return 0;
    }
    seParam.flag = MSM_SEPARAM_VOL|MSM_SEPARAM_PAN;
    seParam.vol = vol;
    seParam.pan = pan;
    return HuSePlay(seId, &seParam);
}

void HuAudFXStop(int seNo) {
    msmSeStop(seNo, 0);
}

void HuAudFXAllStop(void) {
    msmSeStopAll(0, 0);
}

void HuAudFXFadeOut(int seNo, s32 speed) {
    msmSeStop(seNo, speed);
}

void HuAudFXPanning(int seNo, s16 pan) {
    MSM_SEPARAM seParam;

    if (omSysExitReq == 0) {
        seParam.flag = MSM_SEPARAM_PAN;
        seParam.pan = pan;
        msmSeSetParam(seNo, &seParam);
    }
}

void HuAudFXListnerSet(Vec *pos, Vec *heading, float sndDist, float sndSpeed)
{
    if(omSysExitReq) {
      return;
    }
    HuAudFXListnerSetEX(pos, heading,
        sndDist + Snd3DDistOffset,
        sndSpeed + Snd3DSpeedOffset,
        Snd3DStartDisOffset,
        Snd3DFrontSurDisOffset + (0.25 * sndDist + Snd3DStartDisOffset),
        Snd3DBackSurDisOffset + (0.25 * sndDist + Snd3DStartDisOffset));
}

void HuAudFXListnerSetEX(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis)
{
    MSM_SELISTENER listener;
    if(omSysExitReq) {
      return;
    }
    listener.flag = MSM_LISTENER_STARTDIS|MSM_LISTENER_FRONTSURDIS|MSM_LISTENER_BACKSURDIS;
    listener.startDis = startDis + Snd3DStartDisOffset;
    listener.frontSurDis = frontSurDis + Snd3DFrontSurDisOffset;
    listener.backSurDis = backSurDis + Snd3DBackSurDisOffset;
    msmSeSetListener(pos, heading, sndDist + Snd3DDistOffset, sndSpeed + Snd3DSpeedOffset, &listener);
    OSReport("//////////////////////////////////\n");
    OSReport("sndDist %f\n", sndDist);
    OSReport("sndSpeed %f\n", sndSpeed);
    OSReport("startDis %f\n", listener.startDis);
    OSReport("frontSurDis %f\n", listener.frontSurDis);
    OSReport("backSurDis %f\n", listener.backSurDis);
    OSReport("//////////////////////////////////\n");
}

void HuAudFXListnerUpdate(Vec *pos, Vec *heading)
{
    if (omSysExitReq == 0) {
        msmSeUpdataListener(pos, heading);
    }
}

int HuAudFXEmiterPlay(int seId, Vec *pos)
{
    MSM_SEPARAM seParam;
    if(omSysExitReq) {
      return 0;
    }
    seParam.flag = MSM_SEPARAM_POS;
    seParam.pos.x = pos->x;
    seParam.pos.y = pos->y;
    seParam.pos.z = pos->z;
    return HuSePlay(seId, &seParam);
}

void HuAudFXEmiterUpDate(int seNo, Vec *pos)
{
    MSM_SEPARAM param;
    if(omSysExitReq) {
        return;
    }
    param.flag = MSM_SEPARAM_POS;
    param.pos.x = pos->x;
    param.pos.y = pos->y;
    param.pos.z = pos->z;
    msmSeSetParam(seNo, &param);
}

void HuAudFXListnerKill(void) {
    msmSeDelListener();
}

void HuAudFXPauseAll(s32 pause) {
    msmSePauseAll(pause, 0x64);
}

s32 HuAudFXStatusGet(int seNo) {
    return msmSeGetStatus(seNo);
}

s32 HuAudFXPitchSet(int seNo, s16 pitch)
{
    MSM_SEPARAM param;
    if(omSysExitReq) {
        return 0;
    }
    param.flag = MSM_SEPARAM_PITCH;
    param.pitch = pitch;
    return msmSeSetParam(seNo, &param);
}

s32 HuAudFXVolSet(int seNo, s16 vol)
{
    MSM_SEPARAM param;

    if(omSysExitReq) {
        return 0;
    }
    param.flag = MSM_SEPARAM_VOL;
    param.vol = vol;
    return msmSeSetParam(seNo, &param);
}

s32 HuAudSeqPlay(s16 musId) {
    s32 channel;

    if (musicOffF != 0 || omSysExitReq != 0) {
        return 0;
    }
    channel = msmMusPlay(musId, NULL);
    return channel;
}

void HuAudSeqStop(s32 musNo) {
    if (musicOffF != 0 || omSysExitReq != 0) {
        return;
    }
    msmMusStop(musNo, 0);
}

void HuAudSeqFadeOut(s32 musNo, s32 speed) {
    if (musicOffF == 0) {
        msmMusStop(musNo, speed);
    }
}

void HuAudSeqAllFadeOut(s32 speed) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (msmMusGetStatus(i) == 2) {
            msmMusStop(i, speed);
        }
    }
}

void HuAudSeqAllStop(void) {
    msmMusStopAll(0, 0);
}

void HuAudSeqPauseAll(s32 pause) {
    msmMusPauseAll(pause, 0x64);
}

void HuAudSeqPause(s32 musNo, s32 pause, s32 speed) {
    if (musicOffF != 0 || omSysExitReq != 0) {
        return;
    }
    msmMusPause(musNo, pause, speed);
}

s32 HuAudSeqMidiCtrlGet(s32 musNo, s8 channel, s8 ctrl) {
    if (musicOffF != 0 || omSysExitReq != 0) {
        return 0;
    }
    return msmMusGetMidiCtrl(musNo, channel, ctrl);
}

s32 HuAudSStreamPlay(s16 streamId) {
    MSM_STREAMPARAM param;
    s32 result;

    if (musicOffF != 0 || omSysExitReq != 0) {
        return 0;
    }
    param.flag = MSM_STREAMPARAM_NONE ;
    result = msmStreamPlay(streamId, &param);
    return result;
}

void HuAudSStreamStop(s32 seNo) {
    if (musicOffF == 0) {
        msmStreamStop(seNo, 0);
    }
}

void HuAudSStreamFadeOut(s32 seNo, s32 speed) {
    if (musicOffF == 0) {
        msmStreamStop(seNo, speed);
    }
}

void HuAudSStreamAllFadeOut(s32 speed) {
    msmStreamStopAll(speed);
}

void HuAudSStreamAllStop(void) {
    msmStreamStopAll(0);
}

s32 HuAudSStreamStatGet(s32 seNo) {
    return msmStreamGetStatus(seNo);
}

SNDGRPTBL sndGrpTable[] = {
    { OVL_BOOT, -1, 0,  1, -1, -1 },
    { OVL_INST, -1, 0,  1, -1, -1 },
    { OVL_M401, 18, 0,  2, 64, 64 },
    { OVL_M402, 19, 0,  3, 48, 32 },
    { OVL_M403, 20, 0,  1, -1, -1 },
    { OVL_M404, 21, 0,  1, -1, -1 },
    { OVL_M405, 22, 0,  1, 64, 32 },
    { OVL_M406, 23, 0,  1, -1, -1 },
    { OVL_M407, 24, 0,  1, -1, -1 },
    { OVL_M408, 25, 0,  1, -1, -1 },
    { OVL_M409, 26, 0,  4, -1, -1 },
    { OVL_M410, 27, 0,  1, -1, -1 },
    { OVL_M411, 28, 0,  1, -1, -1 },
    { OVL_M412, 29, 0,  1, -1, -1 },
    { OVL_M413, 30, 0,  1, -1, -1 },
    { OVL_M414, 31, 0,  1, -1, -1 },
    { OVL_M415, 32, 0,  1, -1, -1 },
    { OVL_M416, 33, 0,  1, -1, -1 },
    { OVL_M417, 34, 0,  1, -1, -1 },
    { OVL_M418, 35, 0,  1, 64, 64 },
    { OVL_M419, 36, 0,  6, -1, -1 },
    { OVL_M420, 37, 0,  1, -1, -1 },
    { OVL_M421, 38, 0,  1, -1, -1 },
    { OVL_M422, 39, 0,  1, -1, -1 },
    { OVL_M423, 40, 0,  1, -1, -1 },
    { OVL_M424, 41, 0,  1, -1, -1 },
    { OVL_M425, 42, 0,  1, -1, -1 },
    { OVL_M426, 43, 0,  1, -1, -1 },
    { OVL_M427, 44, 0,  1, 64, 72 },
    { OVL_M428, 45, 0,  1, -1, -1 },
    { OVL_M429, 46, 0,  1, -1, -1 },
    { OVL_M430, 47, 0,  1, -1, -1 },
    { OVL_M431, 48, 0,  1, -1, -1 },
    { OVL_M432, 49, 0,  1, 48, 32 },
    { OVL_M433, 50, 0,  1, -1, -1 },
    { OVL_M434, 51, 0,  1, -1, -1 },
    { OVL_M435, 52, 0,  9, 32, 64 },
    { OVL_M436, 53, 0, 10, 32, 64 },
    { OVL_M437, 54, 0,  1, 32, 64 },
    { OVL_M438, 55, 0, 11, -1, -1 },
    { OVL_M439, 56, 0, 12, 48, 32 },
    { OVL_M440, 57, 0,  1, -1, -1 },
    { OVL_M441, 58, 0,  1, -1, -1 },
    { OVL_M442, 59, 0,  1, -1, -1 },
    { OVL_M443, 60, 0,  1, -1, -1 },
    { OVL_M444, 61, 0,  1, -1, -1 },
    { OVL_M445, 62, 0,  1, -1, -1 },
    { OVL_M446, 63, 0,  1, -1, -1 },
    { OVL_M447, 64, 0,  1, -1, -1 },
    { OVL_M448, 65, 0,  1, -1, -1 },
    { OVL_M449, 66, 0,  1, -1, -1 },
    { OVL_M450, 67, 0, 13, 64, 64 },
    { OVL_M451, 68, 0,  1, -1, -1 },
    { OVL_M453, 69, 0,  1, -1, -1 },
    { OVL_M455, 70, 0,  1, -1, -1 },
    { OVL_M456, 71, 0,  1, -1, -1 },
    { OVL_M457, 72, 0, 14, 64, 32 },
    { OVL_M458, 73, 0, 15, 64, 32 },
    { OVL_M459, 74, 0,  1, -1, -1 },
    { OVL_M460, 75, 0,  1, -1, -1 },
    { OVL_M461, 76, 0,  1, -1, -1 },
    { OVL_M462, 77, 0,  1, -1, -1 },
    { OVL_M463, 78, 0,  1, -1, -1 },
    { OVL_MENT, -1, 0,  1, -1, -1 },
    { OVL_MGMODE, 1, 0,  1, -1, -1 },
    { OVL_MODESEL, 0, 0,  1, -1, -1 },
    { OVL_MODELTEST, 18, 0,  1, -1, -1 },
    { OVL_MSETUP, 0, 0,  1, -1, -1 },
    { OVL_MSTORY, 5, 0,  1, -1, -1 },
    { OVL_MSTORY2, 5, 0,  1, -1, -1 },
    { OVL_MSTORY3, 8, 0,  1, -1, -1 },
    { OVL_NIS, 9, 0,  1, -1, -1 },
    { OVL_OPTION, -1, 0,  1, -1, -1 },
    { OVL_PRESENT, -1, 0,  1, -1, -1 },
    { OVL_RESULT, -1, 0,  1, -1, -1 },
    { OVL_SAF, 0, 0,  2, 127, 127 },
    { OVL_SELMENU, 0, 0,  1, -1, -1 },
    { OVL_W01, 9, 0,  1, -1, -1 },
    { OVL_W02, 10, 0,  1, -1, -1 },
    { OVL_W03, 11, 0,  1, -1, -1 },
    { OVL_W04, 12, 0,  1, -1, -1 },
    { OVL_W05, 13, 0,  1, -1, -1 },
    { OVL_W06, 14, 0,  1, -1, -1 },
    { OVL_W10, 15, 0,  1, -1, -1 },
    { OVL_W20, 16, 0,  1, -1, -1 },
    { OVL_W21, 17, 0,  1, -1, -1 },
    { OVL_MPEX, 4, 0,  1, -1, -1 },
    { OVL_ZTAR, -1, 0,  1, -1, -1 },
    { OVL_E3SETUP, 0, 0,  1, -1, -1 },
    { OVL_STAFF, -1, 0,  1, -1, -1 },
    { OVL_INVALID, -1, 0,  1, 0, 0 }
};

void HuAudDllSndGrpSet(u16 ovl) {
    SNDGRPTBL *sndGrp;
    s16 grpSet;

    sndGrp = sndGrpTable;
    while (1) {
        if (sndGrp->ovl == ovl) {
            grpSet = sndGrp->grpSet;
            break;
        }
        if (sndGrp->ovl == OVL_INVALID) {
            grpSet = 0x12;
            break;
        }
        sndGrp++;
    }
    if (grpSet != -1) {
        OSReport("SOUND ##########################\n");
        HuAudSndGrpSetSet(grpSet);
        if (sndGrp->auxANo != auxANoBak || sndGrp->auxBNo != auxBNoBak) {
            msmSysSetAux(sndGrp->auxANo, sndGrp->auxBNo);
            OSReport("Change AUX %d,%d\n", sndGrp->auxANo, sndGrp->auxBNo);
            auxANoBak = sndGrp->auxANo;
            auxBNoBak = sndGrp->auxBNo;
            HuPrcVSleep();
        }
        HuAudAUXVolSet(sndGrp->auxAVol, sndGrp->auxBVol);
        OSReport("##########################\n");
    }
}

void HuAudSndGrpSetSet(s16 dataSize) {
    void *buf;
    OSTick osTick;
    s32 numPlay;
    s32 err;

    if (sndGroupBak != dataSize) {
        msmMusStopAll(1, 0);
        msmSeStopAll(1, 0);
        osTick = OSGetTick();
        while ((msmMusGetNumPlay(1) != 0 || msmSeGetNumPlay(1) != 0)
            && OSTicksToMilliseconds(OSGetTick() - osTick) < 500);
        OSReport("%d\n", OSTicksToMilliseconds(OSGetTick() - osTick));
        if (OSTicksToMilliseconds(OSGetTick() - osTick) >= 500) {
            numPlay = msmSeGetNumPlay(1);
            OSReport("Timed Out! Mus %d:SE %d\n", msmMusGetNumPlay(1), numPlay);
        }
        OSReport("GroupSet %d\n", dataSize);
        sndGroupBak = dataSize;
        err = msmSysDelGroupAll();
        buf = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(1));
        err = msmSysLoadGroupSet(dataSize, buf);
        OSReport("***********GroupSet Error %d\n", err);
        HuMemDirectFree(buf);
    }
}

void HuAudSndGrpSet(s16 grpId) {
    void *buf;

    buf = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(grpId));
    msmSysLoadGroup(grpId, buf, 0);
    HuMemDirectFree(buf);
}

void HuAudSndCommonGrpSet(s16 grpId, s32 groupCheck) {
    s16 err;
    OSTick osTick;
    void *buf;
    s16 i;

    for (i = 0; i < 8; i++) {
        charVoiceGroupStat[i] = 0;
    }
    msmMusStopAll(1, 0);
    msmSeStopAll(1, 0);
    osTick = OSGetTick();
    while ((msmMusGetNumPlay(1) != 0 || msmSeGetNumPlay(1) != 0)
        && OSTicksToMilliseconds(OSGetTick() - osTick) < 500);
    OSReport("CommonGrpSet %d\n", grpId);
    if (groupCheck != 0) {
        err = msmSysDelGroupBase(0);
        if (err < 0) {
            OSReport("Del Group Error %d\n", err);
        }
    }
    buf = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(grpId));
    msmSysLoadGroupBase(grpId, buf);
    HuMemDirectFree(buf);
    sndGroupBak = -1;
}

void HuAudAUXSet(s32 auxA, s32 auxB) {
    if (auxA == -1) {
        auxA = 0;
    }
    if (auxB == -1) {
        auxB = 1;
    }
    msmSysSetAux(auxA, auxB);
}

void HuAudAUXVolSet(s8 auxA, s8 auxB) {
    HuAuxAVol = auxA;
    HuAuxBVol = auxB;
}

void HuAudVoiceInit(s16 ovl) {
    SNDGRPTBL *sndGrp;
    OSTick osTick;
    s16 numNotChars;
    s16 grpId;
    s16 temp_r25;
    s16 character;
    
    void *buf;
    s16 i;

    if (ovl != OVL_INVALID) {
        sndGrp = sndGrpTable;
        while (1) {
            if (sndGrp->ovl == ovl && sndGrp->grpSet == -1) {
                return;
            }
            if (sndGrp->ovl == OVL_INVALID) {
                break;
            }
            sndGrp++;
        }
    }
    for (i = numNotChars = 0; i < 4; i++) {
        character = GWPlayerCfg[i].character;
        if (character < 0 || character >= 8 || character == 0xFF || charVoiceGroupStat[character] != 0) {
            numNotChars++;
        }
    }
    if (numNotChars < 4) {
        for (i = 0; i < 8; i++) {
            charVoiceGroupStat[i] = 0;
        }
        msmMusStopAll(1, 0);
        msmSeStopAll(1, 0);
        osTick = OSGetTick();
        while ((msmMusGetNumPlay(1) != 0 || msmSeGetNumPlay(1) != 0)
            && OSTicksToMilliseconds(OSGetTick() - osTick) < 500);
        OSReport("############CharGrpSet\n");
        temp_r25 = msmSysDelGroupBase(0);
        if (temp_r25 < 0) {
            OSReport("Del Group Error %d\n", temp_r25);
        } else {
            OSReport("Del Group OK\n");
        }
        for (i = 0; i < 4; i++) {
            character = GWPlayerCfg[i].character;
            if (character >= 0 && character < 8 && character != 0xFF) {
                charVoiceGroupStat[character] = 1;
                grpId = character + 10;
                buf = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(grpId));
                #if VERSION_NTSC
                msmSysLoadGroupBase(grpId, buf);
                #else
                temp_r25 = msmSysLoadGroupBase(grpId, buf);
                #endif
                HuMemDirectFree(buf);
            }
        }
        sndGroupBak = -1;
    }
}

s32 HuAudPlayerVoicePlay(s16 player, s16 seId) {
    s16 charNo = GWPlayerCfg[player].character;

    return HuAudCharVoicePlay(charNo, seId);
}

s32 HuAudPlayerVoicePlayPos(s16 player, s16 seId, Vec *pos) {
    s16 charNo = GWPlayerCfg[player].character;

    return HuAudCharVoicePlayPos(charNo, seId, pos);
}

void HuAudPlayerVoicePlayEntry(s16 player, s16 seId) {
    s16 charNo = GWPlayerCfg[player].character;

    HuAudCharVoicePlayEntry(charNo, seId);
}

s32 HuAudCharVoicePlay(s16 charNo, s16 seId)
{
    MSM_SEPARAM param;

    if (omSysExitReq != 0) {
        return 0;
    }
    seId += (charNo << 6);
    param.flag = MSM_SEPARAM_NONE;
    if (HuAuxAVol != -1) {
        param.flag |= MSM_SEPARAM_AUXVOLA;
    }
    if (HuAuxBVol != -1) {
        param.flag |= MSM_SEPARAM_AUXVOLB;
    }
    param.auxAVol = HuAuxAVol;
    param.auxBVol = HuAuxBVol;
    return HuSePlay(seId, &param);
}

s32 HuAudCharVoicePlayPos(s16 charNo, s16 seId, Vec *pos) {
    MSM_SEPARAM param;

    if (omSysExitReq != 0) {
        return 0;
    }
    seId += (charNo << 6);
    param.flag = MSM_SEPARAM_POS;
    if (HuAuxAVol != -1) {
        param.flag |= MSM_SEPARAM_AUXVOLA;
    }
    if (HuAuxBVol != -1) {
        param.flag |= MSM_SEPARAM_AUXVOLB;
    }
    param.auxAVol = HuAuxAVol;
    param.auxBVol = HuAuxBVol;
    param.pos.x = pos->x;
    param.pos.y = pos->y;
    param.pos.z = pos->z;
    return HuSePlay(seId, &param);
}

void HuAudCharVoicePlayEntry(s16 charNo, s16 seId) {
    int seNoTbl[MSM_ENTRY_SENO_MAX]; // size unknown (min: 30, max: 33)
    u16 id;
    u16 i;

    seId += (charNo << 6);
    id = msmSeGetEntryID(seId, seNoTbl);
    for (i = 0; i < id; i++) {
        msmSeStop(seNoTbl[i], 0);
    }
}

static int HuSePlay(int seId, MSM_SEPARAM *param)
{
    s32 result;

    result = msmSePlay(seId, param);
    if (result < 0) {
        OSReport("#########SE Entry Error<SE %d:ErrorNo %d>\n", seId, result);
    }
    return result;
}
