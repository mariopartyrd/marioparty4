#include "msm/msmse.h"
#include "msm/msmfio.h"
#include "msm/msmmem.h"

#define SE_PLAYER_EMIT (1 << 0)

typedef struct SePlayer_s {
    SND_VOICEID vid;
    s32 no;
    s16 seId;
    s8 status;
    s8 busyF;
    s8 vol;
    s8 pan;
    s16 pitch;
    s8 span;
    s8 auxAVol;
    s8 auxBVol;
    u8 flag;
    SND_PARAMETER_INFO paramInfo;
    SND_PARAMETER param[5];
    s8 baseVol;
    s8 basePan;
    s16 basePitch;
    volatile s32 fadeMaxTime;
    s32 fadeTime;
    s8 fadeVol;
    volatile s32 pauseMaxTime;
    s32 pauseTime;
    s8 pauseVol;
    SND_EMITTER emitter;
    SND_FVECTOR emiPos;
    SND_FVECTOR emiDir;
    s8 emitterF;
} SE_PLAYER;

static struct {
    s32 seMax;
    s8 sfx;
    s8 baseGrpNumPlay;
    s8 numPlay;
    s32 no;
    MSM_SE *seData;
    SE_PLAYER *player;
    SND_LISTENER listener;
    SND_FVECTOR listenerPos;
    SND_FVECTOR listenerDir;
    SND_FVECTOR listenerHeading;
    SND_FVECTOR listenerUp;
    float sndDist;
    u16 groupId;
    u16 listenerF;
} se;

static void msmSeFade(SE_PLAYER *player) {
    u8 vol;

    if (player->status == MSM_SE_PAUSEOUT) {
        return;
    }
    if (player->fadeMaxTime > 0) {
        if (--player->fadeTime == 0) {
            player->fadeMaxTime = 0;
            player->fadeMaxTime = 0;
            if (player->fadeMaxTime != 0) {
                player->fadeTime = player->fadeMaxTime;
                player->fadeVol = 127;
            } else {
                player->status = 1;
                if ((player->flag & SE_PLAYER_EMIT) && player->emitterF == TRUE) {
                    sndRemoveEmitter(&player->emitter);
                } else {
                    sndFXKeyOff(player->vid);
                }
            }
        } else {
            player->fadeVol = player->fadeTime * 127 / player->fadeMaxTime;
            vol = player->vol * player->baseVol * player->fadeVol * player->pauseVol / (127*127*127);
            if ((player->flag & SE_PLAYER_EMIT) && player->emitterF == TRUE) {
                player->emiDir.x = player->emiDir.y = player->emiDir.z = 0.0f;
                sndUpdateEmitter(&player->emitter, &player->emiPos, &player->emiDir, vol, NULL);
            } else {
                sndFXVolume(player->vid, vol);
            }
        }
    } else if (player->fadeMaxTime < 0) {
        if (++player->fadeTime >= -player->fadeMaxTime) {
            player->fadeMaxTime = 0;
            player->fadeVol = 127;
        } else {
            player->fadeVol = player->fadeTime * 127 / -player->fadeMaxTime;
        }
        vol = player->vol * player->baseVol * player->fadeVol * player->pauseVol / (127*127*127);
        if ((player->flag & SE_PLAYER_EMIT) && player->emitterF == 1) {
            player->emiDir.x = player->emiDir.y = player->emiDir.z = 0.0f;
            sndUpdateEmitter(&player->emitter, &player->emiPos, &player->emiDir, vol, NULL);
        } else {
            sndFXVolume(player->vid, vol);
        }
    }
}

static void msmSePauseSub(SE_PLAYER* player, BOOL pause, s32 speed) {
    s32 time;

    time = speed / 15;
    if (pause) {
        if (player->status == MSM_SE_PAUSEIN) {
            if (time != 0) {
                player->pauseMaxTime = player->pauseTime = time;
                player->pauseVol = 127;
            } else {
                player->pauseVol = 0;
                sndFXVolume(player->vid, player->vol * player->baseVol * player->fadeVol * player->pauseVol / (127*127*127));
            }
            player->status = MSM_SE_PAUSEOUT;
        }
    } else {
        if (player->status == MSM_SE_PAUSEOUT) {
            if (time != 0) {
                if (player->pauseMaxTime != 0) {
                    player->pauseMaxTime = -time;
                } else {
                    player->pauseMaxTime = -time;
                    player->pauseTime = 0;
                    player->pauseVol = 0;
                }
            } else {
                player->pauseVol = 127;
                sndFXVolume(player->vid, player->vol * player->baseVol * player->fadeVol * player->pauseVol / (127*127*127));
            }
            player->status = MSM_SE_PAUSEIN;
        }
    }
}

static SE_PLAYER* msmSeSearchEntry(s32 seNo) {
    SE_PLAYER *player;
    s32 i;

    for (i = 0; i < se.sfx; i++) {
        player = &se.player[i];
        if (player->status != MSM_SE_DONE && player->no == seNo) {
            return player;
        }
    }
    return NULL;
}

void msmSePeriodicProc(void) {
    s32 i;
    SE_PLAYER* player;
    u8 vol;

    se.baseGrpNumPlay = se.numPlay = 0;
    for (i = 0; i < se.sfx; i++) {
        player = &se.player[i];
        if (player->busyF != 0) {
            continue;
        }
        switch (player->status) {
            case MSM_SE_PLAY:
            case MSM_SE_PAUSEIN:
                if ((player->flag & SE_PLAYER_EMIT) && player->emitterF == TRUE) {
                    if (!sndCheckEmitter(&player->emitter)) {
                        player->status = 0;
                    }
                } else {
                    if (sndFXCheck(player->vid) == SND_ID_ERROR) {
                        player->status = 0;
                    }
                }
                break;
        }
        if (player->status == 0) {
            continue;
        }
        if (msmSysCheckBaseGroup(se.seData[player->seId].gid) != 0) {
            se.baseGrpNumPlay++;
        } else {
            se.numPlay++;
        }
        if (player->pauseMaxTime > 0) {
            if (--player->pauseTime == 0) {
                player->pauseMaxTime = 0;
                player->pauseVol = 0;
            } else {
                player->pauseVol = player->pauseTime * 127 / player->pauseMaxTime;
            }
        } else if (player->pauseMaxTime < 0) {
            if (++player->pauseTime >= -player->pauseMaxTime) {
                player->pauseMaxTime = 0;
                player->pauseVol = 127;
            } else {
                player->pauseVol = player->pauseTime * 127 / -player->pauseMaxTime;
            }
        }
        vol = player->vol * player->baseVol * player->fadeVol * player->pauseVol / (127*127*127);
        if ((player->flag & SE_PLAYER_EMIT) && player->emitterF == TRUE) {
            player->emiDir.x = player->emiDir.y = player->emiDir.z = 0.0f;
            sndUpdateEmitter(&player->emitter, &player->emiPos, &player->emiDir, vol, NULL);
        } else {
            sndFXVolume(player->vid, vol);
        }
        msmSeFade(player);
    }
}

MSM_SE* msmSeGetIndexPtr(s32 seId) {
    if (seId < 0 || seId >= se.seMax) {
        return NULL;
    }
    return &se.seData[seId];
}

void msmSeDelListener(void) {
    if (se.listenerF != 0) {
        sndRemoveListener(&se.listener);
        se.listenerF = 0;
    }
}

s32 msmSeUpdataListener(Vec* pos, Vec* heading) {
    if (se.listenerF == 0) {
        return MSM_LISTENER_NO_UPDATA;
    }
    se.listenerDir.x = pos->x - se.listenerPos.x;
    se.listenerDir.y = pos->y - se.listenerPos.y;
    se.listenerDir.z = pos->z - se.listenerPos.z;
    se.listenerPos.x = pos->x;
    se.listenerPos.y = pos->y;
    se.listenerPos.z = pos->z;
    se.listenerHeading.x = heading->x;
    se.listenerHeading.y = heading->y;
    se.listenerHeading.z = heading->z;
    if (!sndUpdateListener(&se.listener, &se.listenerPos, &se.listenerDir, &se.listenerHeading, &se.listenerUp, 127, NULL)) {
        return MSM_LISTENER_NO_UPDATA;
    }
    return 0;
}

s32 msmSeSetListener(Vec* pos, Vec* heading, float sndDist, float sndSpeed, MSM_SELISTENER* listener) {
    SND_FVECTOR* listenerDir;
    SND_FVECTOR* listenerPos;
    SND_FVECTOR* listenerUp;
    SND_FVECTOR* listenerHeading;
    s32 flag;
    float startDis;
    float frontSurDis;
    float backSurDis;

    listenerPos = &se.listenerPos;
    listenerUp = &se.listenerUp;
    listenerHeading = &se.listenerHeading;
    listenerDir = &se.listenerDir;
    listenerPos->x = pos->x;
    listenerPos->y = pos->y;
    listenerPos->z = pos->z;
    listenerUp->x = listenerUp->z = 0.0f;
    listenerUp->y = 1.0f;
    listenerHeading->x = heading->x;
    listenerHeading->y = heading->y;
    listenerHeading->z = heading->z;
    listenerDir->x = listenerDir->y = listenerDir->z = 0.0f;
    se.sndDist = sndDist;
    flag = (listener != NULL) ? listener->flag : MSM_LISTENER_NONE;
    startDis = (flag & MSM_LISTENER_STARTDIS) ? listener->startDis : 0.0f;
    frontSurDis = (flag & MSM_LISTENER_FRONTSURDIS) ? listener->frontSurDis : (startDis + sndDist * 0.25f);
    backSurDis = (flag & MSM_LISTENER_BACKSURDIS) ? listener->backSurDis : (startDis + sndDist * 0.25f);
    if ((s32) sndAddListenerEx(&se.listener, listenerPos, listenerDir, listenerHeading, listenerUp,
        frontSurDis, backSurDis, sndSpeed, -startDis, SND_EMITTER_CONTINOUS, 127, NULL) == FALSE)
    {
        se.listenerF = FALSE;
        return MSM_LISTENER_NO_UPDATA;
    }
    se.listenerF = TRUE;
    return 0;
}

s32 msmSeGetEntryID(s32 seId, int* seNo) {
    SE_PLAYER* player;
    s32 i;
    s32 num;

    for (i = num = 0; i < se.sfx; i++) {
        player = &se.player[i];
        if (player->status != 0 && player->seId == seId) {
            if (seNo != NULL) {
                seNo[num] = player->no;
            }
            num++;
        }
    }
    return num;
}

s32 msmSeGetNumPlay(BOOL baseGrp) {
    switch (baseGrp) {
        case FALSE:
            return se.numPlay + se.baseGrpNumPlay;
        default:
            return se.numPlay;
    }
}

s32 msmSeGetStatus(int seNo) {
    SE_PLAYER* pan;

    pan = msmSeSearchEntry(seNo);
    if (pan == NULL) {
        return 0;
    }
    return pan->status;
}

void msmSeSetMasterVolume(s32 vol) {
    sndMasterVolume(vol & 127, 0, 0, 1);
}

s32 msmSeSetParam(int seNo, MSM_SEPARAM* param) {
    SE_PLAYER* player;
    int pan;
    s32 pitch;

    player = msmSeSearchEntry(seNo);
    if (player == NULL) {
        return MSM_ERR_INVALIDSE;
    }
    if (param->flag & MSM_SEPARAM_VOL) {
        player->busyF = TRUE;
        player->vol = param->vol;
        if (!(player->flag & SE_PLAYER_EMIT) || player->emitterF != TRUE) {
            sndFXVolume(player->vid, player->vol * player->baseVol * player->fadeVol * player->pauseVol / (127*127*127));
        }
        player->busyF = FALSE;
    }
    if (!(player->flag & SE_PLAYER_EMIT)) {
        if (param->flag & MSM_SEPARAM_PAN) {
            player->pan = param->pan;
            pan = player->pan + player->basePan - 64;
            if (pan < 0) {
                pan = 0;
            }
            if (pan > 127) {
                pan = 127;
            }
            sndFXPanning(player->vid, pan);
        }
        if (param->flag & MSM_SEPARAM_PITCH) {
            player->pitch = param->pitch;
            pitch = player->pitch + player->basePitch + 8192;
            if (pitch < 0) {
                pitch = 0;
            }
            if (pitch > 16383) {
                pitch = 16383;
            }
            sndFXPitchBend(player->vid, pitch);
        }
        if (param->flag & MSM_SEPARAM_SPAN) {
            player->span = param->span;
            sndFXSurroundPanning(player->vid, player->span);
        }
    } else if (player->emitterF == TRUE) {
        player->vid = sndEmitterVoiceID(&player->emitter);
        if (param->flag & MSM_SEPARAM_POS) {
            player->busyF = TRUE;
            player->emiDir.x = param->pos.x - player->emiPos.x;
            player->emiDir.y = param->pos.y - player->emiPos.y;
            player->emiDir.z = param->pos.z - player->emiPos.z;
            player->emiPos.x = param->pos.x;
            player->emiPos.y = param->pos.y;
            player->emiPos.z = param->pos.z;
            sndUpdateEmitter(&player->emitter, &player->emiPos, &player->emiDir, player->vol * player->baseVol * player->fadeVol * player->pauseVol / (127*127*127), NULL);
            player->busyF = FALSE;
        }
    }
    if (param->flag & MSM_SEPARAM_AUXVOLA) {
        player->auxAVol = param->auxAVol;
        sndFXReverb(player->vid, player->auxAVol);
    }
    if (param->flag & MSM_SEPARAM_AUXVOLB) {
        player->auxBVol = param->auxBVol;
        sndFXChorus(player->vid, player->auxBVol);
    }
    if (param->flag & MSM_SEPARAM_PAD) {
        sndSendMessage(player->vid, param->pad);
    }
    return 0;
}

void msmSePauseAll(BOOL pause, s32 speed) {
    s32 i;
    SE_PLAYER* player;

    for (i = 0; i < se.sfx; i++) {
        player = &se.player[i];
        player->busyF = TRUE;
        msmSePauseSub(player, pause, speed);
        player->busyF = FALSE;
    }
}

void msmSeStopAll(BOOL checkGrp, s32 speed) {
    SE_PLAYER* player;
    s32 i;

    for (i = 0; i < se.sfx; i++) {
        player = &se.player[i];
        if (player->status == MSM_MUS_DONE) {
            continue;
        }
        player->busyF = TRUE;
        switch (checkGrp) {
            case FALSE:
                player->fadeMaxTime = speed / 15;
                if (player->fadeMaxTime != 0) {
                    player->fadeTime = player->fadeMaxTime;
                    player->fadeVol = 127;
                } else {
                    player->status = 1;
                    if ((player->flag & SE_PLAYER_EMIT) && player->emitterF == TRUE) {
                        sndRemoveEmitter(&player->emitter);
                    } else {
                        sndFXKeyOff(player->vid);
                    }
                }
                break;
            default:
                if (msmSysCheckBaseGroup(se.seData[player->seId].gid) == 0) {
                    player->fadeMaxTime = speed / 15;
                    if (player->fadeMaxTime != 0) {
                        player->fadeTime = player->fadeMaxTime;
                        player->fadeVol = 127;
                    } else {
                        player->status = 1;
                        if ((player->flag & SE_PLAYER_EMIT) && player->emitterF == TRUE) {
                            sndRemoveEmitter(&player->emitter);
                        } else {
                            sndFXKeyOff(player->vid);
                        }
                    }
                }
                break;
        }
        player->busyF = FALSE;
    }
}

s32 msmSeStop(int seNo, s32 speed) {
    SE_PLAYER* player;

    player = msmSeSearchEntry(seNo);
    if (player == NULL) {
        return MSM_ERR_INVALIDSE;
    }
    player->busyF = TRUE;
    player->fadeMaxTime = speed / 15;
    if (player->fadeMaxTime != 0) {
        player->fadeTime = player->fadeMaxTime;
        player->fadeVol = 127;
    } else {
        player->status = MSM_MUS_STOP;
        if ((player->flag & SE_PLAYER_EMIT) && player->emitterF == TRUE) {
            sndRemoveEmitter(&player->emitter);
        } else {
            sndFXKeyOff(player->vid);
        }
    }
    player->busyF = FALSE;
    return 0;
}

static inline BOOL msmSeUpdateBaseParam(SE_PLAYER* player, MSM_SEPARAM* param) {
    BOOL listenerF = FALSE;

    if (param != NULL) {
        if (param->flag & MSM_SEPARAM_VOL) {
            player->vol = param->vol;
        }
        if (param->flag & MSM_SEPARAM_PAN) {
            player->pan = param->pan;
        }
        if (param->flag & MSM_SEPARAM_PITCH) {
            player->pitch = param->pitch;
        }
        if (param->flag & MSM_SEPARAM_SPAN) {
            player->span = param->span;
        }
        if (param->flag & MSM_SEPARAM_AUXVOLA) {
            player->auxAVol = param->auxAVol;
        }
        if (param->flag & MSM_SEPARAM_AUXVOLB) {
            player->auxBVol = param->auxBVol;
        }
        if ((param->flag & MSM_SEPARAM_POS) && se.listenerF != 0) {
            listenerF = TRUE;
        }
    }
    player->paramInfo.paraArray = player->param;
    return listenerF;
}

int msmSePlay(int seId, MSM_SEPARAM* param) {
    SE_PLAYER* player;
    SND_EMITTER* emitter;
    MSM_SE* seData;
    int pitch;
    s32 pan;
    s32 i;
    s32 emiFlag;

    if (seId < 0 || seId >= se.seMax) {
        return MSM_ERR_INVALIDID;
    }
    seData = &se.seData[seId];
    if (seData->gid == 0xFFFF) {
        return MSM_ERR_REMOVEDID;
    }
    for (i = 0; i < se.sfx; i++) {
        player = &se.player[i];
        if (player->status == 0) {
            break;
        }
    }
    if (i == se.sfx) {
        return MSM_ERR_CHANLIMIT;
    }
    player->baseVol = seData->vol;
    player->basePan = seData->pan;
    player->basePitch = seData->pitchBend;
    player->vol = 127;
    player->pan = 64;
    player->span = seData->span;
    player->pitch = 0;
    player->auxAVol = seData->reverb;
    player->auxBVol = seData->chorus;
    player->pauseMaxTime = 0;
    player->fadeMaxTime = 0;
    player->pauseVol = 127;
    player->fadeVol = 127;
    player->emitterF = 0;
    if (msmSeUpdateBaseParam(player, param)) {
        player->emiPos.x = param->pos.x;
        player->emiPos.y = param->pos.y;
        player->emiPos.z = param->pos.z;
        player->param[0].ctrl = SND_MIDICTRL_REVERB;
        player->param[0].paraData.value7 = player->auxAVol;
        player->param[1].ctrl = SND_MIDICTRL_CHORUS;
        player->param[1].paraData.value7 = player->auxBVol;
        player->paramInfo.numPara = 2;
        player->emiDir.x = player->emiDir.y = player->emiDir.z = 0.0f;
        if (seData->emitterF == TRUE) {
            emitter = &player->emitter;
            emiFlag = SND_EMITTER_DOPPLERFX|SND_EMITTER_CONTINOUS;
        } else {
            emitter = NULL;
            emiFlag = SND_EMITTER_DOPPLERFX;
        }
        player->emitterF = seData->emitterF;
        player->vid = sndAddEmitterParaEx(emitter, &player->emiPos, &player->emiDir, se.sndDist, seData->emiComp / 127.0f, emiFlag, seData->fxId, se.groupId++, player->vol * player->baseVol / 127, 0, NULL, &player->paramInfo);
        if (emitter != NULL) {
            if (!sndCheckEmitter(emitter)) {
                return MSM_ERR_PLAYFAIL;
            }
        } else {
            if (player->vid == -1) {
                return MSM_ERR_PLAYFAIL;
            }
        }
        player->flag |= 1;
    } else {
        player->param[0].ctrl = SND_MIDICTRL_VOLUME;
        player->param[0].paraData.value14 = (player->vol * player->baseVol / 127) * 129;
        pan = player->pan + player->basePan - 64;
        if (pan < 0) {
            pan = 0;
        }
        if (pan > 127) {
            pan = 127;
        }
        player->param[1].ctrl = SND_MIDICTRL_PANNING;
        player->param[1].paraData.value14 = pan * 129;
        player->param[2].ctrl = SND_MIDICTRL_REVERB;
        player->param[2].paraData.value7 = player->auxAVol;
        player->param[3].ctrl = SND_MIDICTRL_CHORUS;
        player->param[3].paraData.value7 = player->auxBVol;
        pitch = player->pitch + player->basePitch + 8192;
        if (pitch > 16383) {
            pitch = 16383;
        } else if (pitch < 0) {
            pitch = 0;
        }
        player->param[4].ctrl = SND_MIDICTRL_PITCHBEND;
        player->param[4].paraData.value14 = pitch;
        player->paramInfo.numPara = 5;
        player->vid = sndFXStartParaInfo(seData->fxId, 0xFF, 0xFF, 0, &player->paramInfo);
        if (player->vid == -1) {
            return MSM_ERR_PLAYFAIL;
        }
        sndFXSurroundPanning(player->vid, player->span);
        player->flag &= ~1;
    }
    player->busyF = 1;
    player->seId = seId;
    player->no = se.no++;
    player->status = 2;
    player->busyF = 0;
    return player->no;
}

s32 msmSeInit(MSM_SYS* arg0, DVDFileInfo* arg1) {
    s32 playerSize;

    se.sfx = 0;
    se.seMax = 0;
    se.baseGrpNumPlay = 0;
    se.numPlay = 0;
    se.listenerF = 0;
    if (arg0->info->seMax == 0) {
        return 0;
    }
    if ((se.seData = msmMemAlloc(arg0->header->seSize)) == NULL) {
        return MSM_ERR_OUTOFMEM;
    }
    if (msmFioRead(arg1, se.seData, arg0->header->seSize, arg0->header->seOfs) < 0) {
        return MSM_ERR_READFAIL;
    }
    playerSize = arg0->info->sfx * sizeof(SE_PLAYER);
    if ((se.player = msmMemAlloc(playerSize)) == NULL) {
        return MSM_ERR_OUTOFMEM;
    }
    memset(se.player, 0, playerSize);
    se.seMax = arg0->info->seMax;
    se.sfx = arg0->info->sfx;
    se.no = 1;
    return 0;
}
