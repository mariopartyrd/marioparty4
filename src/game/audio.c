#include "game/audio.h"
#include "game/chrman.h"
#include "game/memory.h"
#include "game/gamework.h"
#include "game/armem.h"
#include "game/msm.h"
#include "game/object.h"
#include "game/wipe.h"
#include "game/gamework_data.h"

#define HUMSMHEAP_SIZE 0x13FC00

#define MSM_FILE_PATH "/sound/mpgcsnd.msm"
#define PDT_FILE_PATH "/sound/mpgcstr.pdt"

static int HuSePlay(int seId, MSM_SEPARAM *param);

s32 charVoiceGroupStat[8];
static s32 sndFXBuf[64][2];

static s16 Hu3DAudVol;
static s16 sndGroupBak;
static BOOL auxANoBak;
static BOOL auxBNoBak;
static s8 HuAuxAVol;
static s8 HuAuxBVol;
float Snd3DBackSurDisOffset;
float Snd3DFrontSurDisOffset;
float Snd3DStartDisOffset;
float Snd3DSpeedOffset;
float Snd3DDistOffset;
BOOL musicOffF;
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

    msmInit.heap = HuMemDirectMalloc(HEAP_MUSIC, HUMSMHEAP_SIZE);
    msmInit.heapSize = HUMSMHEAP_SIZE;
    msmInit.msmPath = MSM_FILE_PATH;
    msmInit.pdtPath = PDT_FILE_PATH;
    msmInit.open = NULL;
    msmInit.read = NULL;
    msmInit.close = NULL;
    msmAram.skipARInit = TRUE;
    msmAram.aramEnd = HU_AMEM_BASE;
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
    sndGroupBak = MSM_GRPSET_NONE;
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

    if (omSysExitReq) {
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
    MSM_SEPARAM param;

    if (omSysExitReq == 0) {
        param.flag = MSM_SEPARAM_PAN;
        param.pan = pan;
        msmSeSetParam(seNo, &param);
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
    if (omSysExitReq) {
        return;
    }
    msmSeUpdataListener(pos, heading);
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

void HuAudFXPauseAll(BOOL pauseF) {
    msmSePauseAll(pauseF, 100);
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

    if (musicOffF || omSysExitReq) {
        return 0;
    }
    channel = msmMusPlay(musId, NULL);
    return channel;
}

void HuAudSeqStop(s32 musNo) {
    if (musicOffF || omSysExitReq) {
        return;
    }
    msmMusStop(musNo, 0);
}

void HuAudSeqFadeOut(s32 musNo, s32 speed) {
    if (musicOffF) {
        return;
    }
    msmMusStop(musNo, speed);
}

void HuAudSeqAllFadeOut(s32 speed) {
    s16 i;

    for (i = 0; i < MSM_MUS_MAX; i++) {
        if (msmMusGetStatus(i) == MSM_MUS_PLAY) {
            msmMusStop(i, speed);
        }
    }
}

void HuAudSeqAllStop(void) {
    msmMusStopAll(FALSE, 0);
}

void HuAudSeqPauseAll(BOOL pause) {
    msmMusPauseAll(pause, 100);
}

void HuAudSeqPause(s32 musNo, s32 pause, s32 speed) {
    if (musicOffF || omSysExitReq) {
        return;
    }
    msmMusPause(musNo, pause, speed);
}

s32 HuAudSeqMidiCtrlGet(s32 musNo, s8 channel, s8 ctrl) {
    if (musicOffF || omSysExitReq) {
        return 0;
    }
    return msmMusGetMidiCtrl(musNo, channel, ctrl);
}

s32 HuAudSStreamPlay(s16 streamId) {
    MSM_STREAMPARAM param;
    s32 result;

    if (musicOffF || omSysExitReq) {
        return 0;
    }
    param.flag = MSM_STREAMPARAM_NONE ;
    result = msmStreamPlay(streamId, &param);
    return result;
}

void HuAudSStreamStop(s32 seNo) {
    if (musicOffF) {
        return;
    }
    msmStreamStop(seNo, 0);
}

void HuAudSStreamFadeOut(s32 seNo, s32 speed) {
    if (musicOffF) {
        return;
    }
    msmStreamStop(seNo, speed);
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
    { DLL_bootdll, MSM_GRPSET_NONE, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_instdll, MSM_GRPSET_NONE, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m401dll, MSM_GRPSET_MG401, MSM_AUXA_DEFAULT, 2, 64, 64 },
    { DLL_m402dll, MSM_GRPSET_MG402, MSM_AUXA_DEFAULT, 3, 48, 32 },
    { DLL_m403dll, MSM_GRPSET_MG403, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m404dll, MSM_GRPSET_MG404, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m405dll, MSM_GRPSET_MG405, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, 64, 32 },
    { DLL_m406dll, MSM_GRPSET_MG406, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m407dll, MSM_GRPSET_MG407, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m408dll, MSM_GRPSET_MG408, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m409dll, MSM_GRPSET_MG409, MSM_AUXA_DEFAULT, 4, -1, -1 },
    { DLL_m410dll, MSM_GRPSET_MG410, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m411dll, MSM_GRPSET_MG411, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m412dll, MSM_GRPSET_MG412, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m413dll, MSM_GRPSET_MG413, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m414dll, MSM_GRPSET_MG414, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m415dll, MSM_GRPSET_MG415, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m416dll, MSM_GRPSET_MG416, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m417dll, MSM_GRPSET_MG417, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m418dll, MSM_GRPSET_MG418, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, 64, 64 },
    { DLL_m419dll, MSM_GRPSET_MG419, MSM_AUXA_DEFAULT, 6, -1, -1 },
    { DLL_m420dll, MSM_GRPSET_MG420, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m421dll, MSM_GRPSET_MG421, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m422dll, MSM_GRPSET_MG422, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m423dll, MSM_GRPSET_MG423, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m424dll, MSM_GRPSET_MG424, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m425dll, MSM_GRPSET_MG425, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m426dll, MSM_GRPSET_MG426, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m427dll, MSM_GRPSET_MG427, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, 64, 72 },
    { DLL_m428dll, MSM_GRPSET_MG428, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m429dll, MSM_GRPSET_MG429, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m430dll, MSM_GRPSET_MG430, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m431dll, MSM_GRPSET_MG431, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m432dll, MSM_GRPSET_MG432, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, 48, 32 },
    { DLL_m433dll, MSM_GRPSET_MG433, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m434dll, MSM_GRPSET_MG434, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m435dll, MSM_GRPSET_MG435, MSM_AUXA_DEFAULT, 9, 32, 64 },
    { DLL_m436dll, MSM_GRPSET_MG436, MSM_AUXA_DEFAULT, 10, 32, 64 },
    { DLL_m437dll, MSM_GRPSET_MG437, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, 32, 64 },
    { DLL_m438dll, MSM_GRPSET_MG438, MSM_AUXA_DEFAULT, 11, -1, -1 },
    { DLL_m439dll, MSM_GRPSET_MG439, MSM_AUXA_DEFAULT, 12, 48, 32 },
    { DLL_m440dll, MSM_GRPSET_MG440, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m441dll, MSM_GRPSET_MG441, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m442dll, MSM_GRPSET_MG442, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m443dll, MSM_GRPSET_MG443, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m444dll, MSM_GRPSET_MG444, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m445dll, MSM_GRPSET_MG445, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m446dll, MSM_GRPSET_MG446, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m447dll, MSM_GRPSET_MG447, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m448dll, MSM_GRPSET_MG448, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m449dll, MSM_GRPSET_MG449, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m450dll, MSM_GRPSET_MG450, MSM_AUXA_DEFAULT, 13, 64, 64 },
    { DLL_m451dll, MSM_GRPSET_MG451, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m453dll, MSM_GRPSET_MG453, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m455dll, MSM_GRPSET_MG455, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m456dll, MSM_GRPSET_MG456, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m457dll, MSM_GRPSET_MG457, MSM_AUXA_DEFAULT, 14, 64, 32 },
    { DLL_m458dll, MSM_GRPSET_MG458, MSM_AUXA_DEFAULT, 15, 64, 32 },
    { DLL_m459dll, MSM_GRPSET_MG459, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m460dll, MSM_GRPSET_MG460, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m461dll, MSM_GRPSET_MG461, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m462dll, MSM_GRPSET_MG462, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_m463dll, MSM_GRPSET_MG463, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_mentdll, MSM_GRPSET_NONE, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_mgmodedll, MSM_GRPSET_CMN, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_modeseldll, MSM_GRPSET_INIT, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_modeltestdll, MSM_GRPSET_MG401, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_msetupdll, MSM_GRPSET_INIT, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_mstorydll, MSM_GRPSET_MSTORY, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_mstory2dll, MSM_GRPSET_MSTORY, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_mstory3dll, MSM_GRPSET_MSTORY3, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_nisdll, MSM_GRPSET_BD1, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_option, MSM_GRPSET_NONE, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_present, MSM_GRPSET_NONE, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_resultdll, MSM_GRPSET_NONE, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_safdll, MSM_GRPSET_INIT, MSM_AUXA_DEFAULT, 2, 127, 127 },
    { DLL_selmenuDLL, MSM_GRPSET_INIT, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_w01dll, MSM_GRPSET_BD1, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_w02dll, MSM_GRPSET_BD2, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_w03dll, MSM_GRPSET_BD3, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_w04dll, MSM_GRPSET_BD4, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_w05dll, MSM_GRPSET_BD5, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_w06dll, MSM_GRPSET_BD6, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_w10dll, MSM_GRPSET_BD10, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_w20dll, MSM_GRPSET_BD20, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_w21dll, MSM_GRPSET_BD21, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_mpexdll, 4, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_ztardll, MSM_GRPSET_NONE, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_e3setupDLL, MSM_GRPSET_INIT, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_staffdll, MSM_GRPSET_NONE, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, -1, -1 },
    { DLL_NONE, MSM_GRPSET_NONE, MSM_AUXA_DEFAULT, MSM_AUXB_DEFAULT, 0, 0 }
};

void HuAudDllSndGrpSet(u16 ovl) {
    SNDGRPTBL *sndGrpP;
    s16 grpSet;

    sndGrpP = sndGrpTable;
    while (1) {
        if (sndGrpP->ovl == ovl) {
            grpSet = sndGrpP->grpSet;
            break;
        }
        if (sndGrpP->ovl == DLL_NONE) {
            grpSet = 0x12;
            break;
        }
        sndGrpP++;
    }
    if (grpSet != MSM_GRPSET_NONE) {
        OSReport("SOUND ##########################\n");
        HuAudSndGrpSetSet(grpSet);
        if (sndGrpP->auxANo != auxANoBak || sndGrpP->auxBNo != auxBNoBak) {
            msmSysSetAux(sndGrpP->auxANo, sndGrpP->auxBNo);
            OSReport("Change AUX %d,%d\n", sndGrpP->auxANo, sndGrpP->auxBNo);
            auxANoBak = sndGrpP->auxANo;
            auxBNoBak = sndGrpP->auxBNo;
            HuPrcVSleep();
        }
        HuAudAUXVolSet(sndGrpP->auxAVol, sndGrpP->auxBVol);
        OSReport("##########################\n");
    }
}

#define SNDGRP_TIMEOUT 500

#define SNDGRP_WAIT(tickStart) \
    while((msmMusGetNumPlay(TRUE) != 0 || msmSeGetNumPlay(TRUE) != 0) && OSTicksToMilliseconds(OSGetTick()-(tickStart)) < SNDGRP_TIMEOUT)


void HuAudSndGrpSetSet(s16 grpSet) {
    void *buf;
    OSTick tickStart;
    s32 numPlay;
    s32 result;

    if (sndGroupBak != grpSet) {
        msmMusStopAll(1, 0);
        msmSeStopAll(1, 0);
        tickStart = OSGetTick();
        SNDGRP_WAIT(tickStart);
        OSReport("%d\n", OSTicksToMilliseconds(OSGetTick() - tickStart));
        if (OSTicksToMilliseconds(OSGetTick() - tickStart) >= 500) {
            numPlay = msmSeGetNumPlay(1);
            OSReport("Timed Out! Mus %d:SE %d\n", msmMusGetNumPlay(TRUE), numPlay);
        }
        OSReport("GroupSet %d\n", grpSet);
        sndGroupBak = grpSet;
        result = msmSysDelGroupAll();
        buf = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(1));
        result = msmSysLoadGroupSet(grpSet, buf);\
        OSReport("***********GroupSet Error %d\n", result);
        HuMemDirectFree(buf);
    }
}

void HuAudSndGrpSet(s16 grpId) {
    void *buf;

    buf = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(grpId));
    msmSysLoadGroup(grpId, buf, FALSE);
    HuMemDirectFree(buf);
}

void HuAudSndCommonGrpSet(s16 grp, BOOL delGrpF) {
    OSTick tickStart;
    s16 result;
    void *buf;
    s16 i;

    for (i = 0; i < CHARNO_MAX; i++) {
        charVoiceGroupStat[i] = 0;
    }
    msmMusStopAll(TRUE, 0);
    msmSeStopAll(TRUE, 0);
    tickStart = OSGetTick();
    SNDGRP_WAIT(tickStart);
    OSReport("CommonGrpSet %d\n", grp);
    if (delGrpF != 0) {
        result = msmSysDelGroupBase(0);
        if (result < 0) {
            OSReport("Del Group Error %d\n", result);
        }
    }
    buf = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(grp));
    msmSysLoadGroupBase(grp, buf);
    HuMemDirectFree(buf);
    sndGroupBak = MSM_GRPSET_NONE;
}

void HuAudAUXSet(s32 auxA, s32 auxB) {
    if (auxA == MSM_AUX_NONE) {
        auxA = MSM_AUXA_DEFAULT;
    }
    if (auxB == MSM_AUX_NONE) {
        auxB = MSM_AUXB_DEFAULT;
    }
    msmSysSetAux(auxA, auxB);
}

void HuAudAUXVolSet(s8 volA, s8 volB) {
    HuAuxAVol = volA;
    HuAuxBVol = volB;
}

void HuAudSndCharGrpSet(s16 ovl) {
    SNDGRPTBL *sndGrpP;
    OSTick tickStart;
    s16 grpSet;
    s16 charNo;
    s16 loadNum;
    s16 result;
    void *buf;
    s16 i;

    if (ovl != DLL_NONE) {
        sndGrpP = sndGrpTable;
        while (1) {
            if (sndGrpP->ovl == ovl && sndGrpP->grpSet == MSM_GRPSET_NONE) {
                return;
            }
            if (sndGrpP->ovl == DLL_NONE) {
                break;
            }
            sndGrpP++;
        }
    }
    for (i = loadNum = 0; i < GW_PLAYER_MAX; i++) {
        charNo = GWPlayerCfg[i].character;
        if (charNo < 0 || charNo >= CHARNO_MAX || charNo == 0xFF || charVoiceGroupStat[charNo] != 0) {
            loadNum++;
        }
    }
    if (loadNum < GW_PLAYER_MAX) {
        for (i = 0; i < CHARNO_MAX; i++) {
            charVoiceGroupStat[i] = 0;
        }
        msmMusStopAll(TRUE, 0);
        msmSeStopAll(TRUE, 0);
        tickStart = OSGetTick();
        SNDGRP_WAIT(tickStart);
        OSReport("############CharGrpSet\n");
        result = msmSysDelGroupBase(0);
        if (result < 0) {
            OSReport("Del Group Error %d\n", result);
        } else {
            OSReport("Del Group OK\n");
        }
        for (i = 0; i < GW_PLAYER_MAX; i++) {
            charNo = GWPlayerCfg[i].character;
            if (charNo >= 0 && charNo < CHARNO_MAX && charNo != 0xFF) {
                charVoiceGroupStat[charNo] = 1;
                grpSet = charNo + 10;
                buf = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(grpSet));
                #if VERSION_NTSC
                msmSysLoadGroupBase(grpSet, buf);
                #else
                result = msmSysLoadGroupBase(grpSet, buf);
                #endif
                HuMemDirectFree(buf);
            }
        }
        sndGroupBak = MSM_GRPSET_NONE;
    }
}

s32 PlayerFXPlay(s16 player, s16 seId) {
    s16 charNo = GWPlayerCfg[player].character;

    return CharFXPlay(charNo, seId);
}

s32 PlayerFXPlayPos(s16 player, s16 seId, Vec *pos) {
    s16 charNo = GWPlayerCfg[player].character;

    return CharFXPlayPos(charNo, seId, pos);
}

void PlayerFXStop(s16 player, s16 seId) {
    s16 charNo = GWPlayerCfg[player].character;

    CharFXStop(charNo, seId);
}

s32 CharFXPlay(s16 charNo, s16 seId)
{
    MSM_SEPARAM param;

    if (omSysExitReq) {
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

s32 CharFXPlayPos(s16 charNo, s16 seId, Vec *pos) {
    MSM_SEPARAM param;

    if (omSysExitReq) {
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

void CharFXStop(s16 charNo, s16 seId) {
    int entrySeNo[MSM_ENTRY_SENO_MAX];
    u16 entryNum;
    u16 i;
    seId += (charNo << 6);
    entryNum = msmSeGetEntryID(seId, entrySeNo);
    for (i = 0; i < entryNum; i++) {
        msmSeStop(entrySeNo[i], 0);
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
