#include "types.h"
#include "game/chrman.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/humath.h"
#include "game/object.h"
#include "game/process.h"
#include "game/sprite.h"

#include "ext_math.h"
#include <string.h>

#ifndef __MWERKS__
#include "game/frand.h"
#endif

#include "data_num/effect.h"

typedef struct CharWork_s {
    /* 0x00 */ HU3DMODELID modelId;
    /* 0x02 */ s16 model;
    /* 0x04 */ s16 motNoCurr;
    /* 0x06 */ s16 motNoShiftCurr;
    /* 0x08 */ s16 motNoPrev;
    /* 0x0A */ s16 motNoShiftPrev;
    /* 0x0C */ HU3DMOTID motId[CHAR_MOT_MAX];
    /* 0x4C */ s16 motNoTbl[CHAR_MOT_MAX];
    /* 0x8C */ u8 voiceFlag[CHAR_MOT_MAX];
    /* 0xAC */ u32 attr;
    /* 0xB0 */ s8 stepFx;
    /* 0xB4 */ HuVecF pos;
    /* 0xC0 */ AMEM_PTR motAMemP;
    /* 0xC4 */ Process *process;
} CHARWORK; // Size 0xC8

typedef struct EffectData_s {
    /* 0x00 */ s32 dataNum;
    /* 0x04 */ s16 maxCnt;
    /* 0x06 */ s16 blendMode;
    /* 0x08 */ s32 motCnt;
} EFFECTDATA; // Size 0xC

typedef struct EffectParam_s {
    /* 0x00 */ u32 attr;
    /* 0x04 */ GXColor colorBegin;
    /* 0x08 */ GXColor colorEnd;
    /* 0x0C */ HuVecF vel;
    /* 0x18 */ HuVecF velDecay;
    /* 0x24 */ float gravity;
    /* 0x28 */ u32 zero;
    /* 0x2C */ float scaleVel;
    /* 0x30 */ float alphaBase;
    /* 0x34 */ float colorWeight;
} EFFECTPARAM; // Size 0x38

static void UpdateChar(void);
static void UpdateCharAnim(s16 charNo, HU3DMODELID modelId, s16 motNo, u8 voiceFlag, s16 frameNo, HuVecF *ofs);
static s32 _CharFXPlay(s16 charNo, s16 seNo, u8 voiceFlag);
static void EffectInit(void);
static s16 EffectDustCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param);
static s16 EffectSmokeCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param);
static s16 EffectDotCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param);
static s16 EffectStarCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param);
static s16 EffectWarnCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param);
static s16 EffectBirdCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param);
static s16 EffectCreate(s16 type, s16 cameraBit, float posX, float posY, float posZ, float scale, EFFECTPARAM *param);
static void UpdateEffect(ModelData *model, ParticleData *particle, Mtx matrix);
static void RotateEffect(HU3DPARTICLEDATA *particleDataP);
static void PlayEffectSound(HU3DPARTICLEDATA *particleDataP);
static void CreateHookDust(void);
static void UpdateModelEffect(HU3DPARTICLEDATA *particleDataP);
static void UpdateNpcDust(void);
static s32 PlayStepVoice(s16 charNo, s16 seId, u8 voiceFlag);

static CHARWORK charWork[CHARNO_MAX];
static s16 effectMdl[CHAR_EFFECT_AND_PARTICLE_MAX];
static EFFECTPARAM *particleData[CHAR_EFFECT_AND_PARTICLE_MAX];
static Process *itemHookProcess[CHAR_MOT_MAX];
//holds normal characters 0-7, then more characters 8-14
static u16 dustFlags[CHARNO_MAX  + CHAR_NPC_MAX];
static u8 lbl_801975CE[0x82]; // Unused?

static s32 skipAnimUpdate;
static void *effectAMemP;

static u8 lbl_801D35F0[8] = { 0x0C, 0x00, 0x17, 0x75, 0x1E, 0x1E, 0x1D, 0x18 };
static u8 lbl_801D35F8[8] = { 0x0D, 0x00, 0x17, 0x54, 0x1E, 0x00, 0x00, 0x23 };
static u8 lbl_801D3600[8] = { 0x0A, 0x00, 0x19, 0x63, 0x26, 0x00, 0x10, 0x0F };
static u8 lbl_801D3608[8] = { 0x0D, 0x00, 0x17, 0x69, 0x0D, 0x1E, 0x1D, 0x14 };
static u8 lbl_801D3610[8] = { 0x15, 0x1E, 0x16, 0x54, 0x0F, 0x62, 0x39, 0x0A };

static EFFECTDATA effectDataTbl[8] = {
    { EFFECT_ANM_danger, 10, 0, 2 },
    { EFFECT_ANM_hatena, 10, 0, 2 },
    { EFFECT_ANM_dust, 150, 1, 0 },
    { EFFECT_ANM_smoke, 70, 0, 0 },
    { EFFECT_ANM_star, 300, 1, 0 },
    { EFFECT_ANM_glow, 300, 1, 0 },
    { EFFECT_ANM_circle, 200, 1, 0 },
    { EFFECT_ANM_bird, 12, 0, 2 },
};

static s32 charDirTbl[CHARNO_MAX][3] = {
    { DATADIR_MARIOMDL0, DATADIR_MARIOMDL1, DATADIR_MARIOMOT },
    { DATADIR_LUIGIMDL0, DATADIR_LUIGIMDL1, DATADIR_LUIGIMOT },
    { DATADIR_PEACHMDL0, DATADIR_PEACHMDL1, DATADIR_PEACHMOT },
    { DATADIR_YOSHIMDL0, DATADIR_YOSHIMDL1, DATADIR_YOSHIMOT },
    { DATADIR_WARIOMDL0, DATADIR_WARIOMDL1, DATADIR_WARIOMOT },
    { DATADIR_DONKEYMDL0, DATADIR_DONKEYMDL1, DATADIR_DONKEYMOT },
    { DATADIR_DAISYMDL0, DATADIR_DAISYMDL1, DATADIR_DAISYMOT },
    { DATADIR_WALUIGIMDL0, DATADIR_WALUIGIMDL1, DATADIR_WALUIGIMOT },
};

static EFFECTPARAM dustEffParam
    = { 0, 0x80, 0x80, 0x80, 0xFF, 0x40, 0x20, 0x00, 0xFF, { 0.0f, 2.0f, 1.0f }, 0.95f, 0.95f, 0.95f, 0.0f, 0x00000000, 1.0f, -5.0f, 0.02f };

static EFFECTPARAM effectDotParam
    = { 0, 0xFF, 0x40, 0x40, 0x80, 0xFF, 0x40, 0x40, 0x80, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f, 0.0f, 0x00000000, -5.0f, 0.0f, 0.0f };

static EFFECTPARAM effectStarParam
    = { 0, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, { 0.0f, 0.0f, 0.0f }, 0.95f, 0.95f, 0.95f, 0.0f, 0x00000000, -0.5f, -10.0f, 0.0f };

static EFFECTPARAM effectWarnParam
    = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, { 0.0f, 20.0f, 0.0f }, 0.95f, 0.85f, 0.95f, 0.0f, 0x00000000, 1.0f, -5.0f, 0.0f };

static EFFECTPARAM effectSmokeParam
    = { 0, 0x80, 0x20, 0x20, 0xFF, 0x00, 0x00, 0x00, 0xFF, { 0.0f, 10.0f, 0.0f }, 1.0f, 0.95f, 1.0f, 0.0f, 0x00000000, 5.0f, -13.0f, 0.1f };

static s8 lbl_801309A0[32]
    = { 10, 32, -1, -1, 20, 40, -1, -1, 12, 37, -1, -1, 4, 25, -1, -1, 5, 30, -1, -1, 16, 1, 24, 39, 23, 50, -1, -1, 19, 39, -1, -1 };

static s8 lbl_801309C0[32]
    = { 15, 29, -1, -1, 5, 19, -1, -1, 5, 22, -1, -1, 12, 28, -1, -1, 18, 35, -1, -1, 1, 8, 12, -1, 0, 16, -1, -1, 12, 28, -1, -1 };

static s8 lbl_801309E0[16] = { 5, 7, 6, 9, 10, 11, 9, -1, 9, 11, 9, -1, 8, -1, 10, -1 };

void CharInit(void)
{
    s16 i;
    s16 j;
    
    for (i = 0; i < CHARNO_MAX; i++) {
        CHARWORK *workP = &charWork[i];
        workP->motAMemP = 0;
        for (j = 0; j < ARRAY_COUNT(workP->motId); j++) {
            workP->motId[j] = HU3D_MOTID_NONE;
        }
        workP->modelId = HU3D_MODELID_NONE;
        workP->process = NULL;
    }
    if (!effectAMemP) {
        effectAMemP = (void *)HuAR_DVDtoARAM(0x120000);
    }
    for (i = 0; i < CHAR_EFFECT_AND_PARTICLE_MAX; i++) {
        effectMdl[i] = -1;
        particleData[i] = NULL;
    }
    for (i = 0; i < ARRAY_COUNT(itemHookProcess); i++) {
        itemHookProcess[i] = NULL;
    }
}

AMEM_PTR CharMotionAMemPGet(s16 charNo)
{
    return charWork[charNo].motAMemP;
}

void CharMotionInit(s16 charNo)
{
    if (charNo >= CHARNO_MAX  || charNo < 0 || charNo == 0xFF) {
        return;
    } else {
        CHARWORK *workP = &charWork[charNo];
        if (!workP->motAMemP) {
            workP->motAMemP = HuAR_DVDtoARAM(charDirTbl[charNo][2]);
        }
    }
}

void CharMotionClose(s16 charNo)
{
    CHARWORK *workP = &charWork[charNo];
    if (workP->motAMemP) {
        HuARFree(workP->motAMemP);
        workP->motAMemP = 0;
    }
}

void CharDataClose(s16 charNo)
{
    s16 i;

    if (charNo == CHARNO_NONE) {
        for (i = 0; i < CHARNO_MAX; i++) {
            CharDataClose(i);
        }
    }
    else {
        HuDataDirClose(charDirTbl[charNo][0]);
        HuDataDirClose(charDirTbl[charNo][1]);
        HuDataDirClose(charDirTbl[charNo][2]);
        CharMotionClose(charNo);
    }
}

void CharClose(void)
{
    CharModelKill(CHARNO_NONE);
    CharDataClose(CHARNO_NONE);
    HuARFree((u32)effectAMemP);
    effectAMemP = NULL;
}

HU3DMODELID CharModelCreate(s16 charNo, s16 model)
{
    s16 sp8 = 0;
    CHARWORK *workP = &charWork[charNo];
    void *dataP;
    s16 *property;
    s16 modelId;
    s32 dataNum;

    if (workP->modelId != HU3D_MODELID_NONE) {
        Hu3DModelKill(workP->modelId);
    }
    if (model & CHAR_MODEL0) {
        dataNum = charDirTbl[charNo][0];
    }
    else if (model & CHAR_MODEL1) {
        dataNum = charDirTbl[charNo][1];
    }
    else if (model & CHAR_MODEL2) {
        dataNum = charDirTbl[charNo][1] | 1;
    }
    else {
        dataNum = charDirTbl[charNo][1] | 2;
    }
    dataP = HuDataSelHeapReadNum(dataNum, MEMORY_DEFAULT_NUM, HEAP_DATA);
    workP->modelId = modelId = Hu3DModelCreate(dataP);
    workP->process = HuPrcCreate(UpdateChar, 100, 16384, 0);
    workP->process->user_data = property = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(s16));
    workP->model = model;
    workP->attr = 0;
    *property = charNo;
    workP->stepFx = 0;
    EffectInit();
    return modelId;
}

static void EyeBmpUpdate(s16 charNo);

static void UpdateChar(void)
{
    HuVecF sp8;
    s16 *property = HuPrcCurrentGet()->user_data;
    CHARWORK *workP = &charWork[*property];
    ModelData *modelP = &Hu3DData[workP->modelId];
    s16 updateBmpF = FALSE;
    s16 i;

    while (1) {
        for (i = 0; i < CHAR_MOT_MAX; i++) {
            if (workP->motId[i] == modelP->unk_08) {
                break;
            }
        }
        skipAnimUpdate = 0;
        if (i != CHAR_MOT_MAX) {
            workP->motNoCurr = workP->motNoTbl[i];
            UpdateCharAnim(*property, workP->modelId, workP->motNoTbl[i], workP->voiceFlag[i], modelP->unk_64, &sp8);
            workP->motNoPrev = workP->motNoTbl[i];
        }
        else {
            workP->motNoCurr = -1;
        }
        if (modelP->unk_0C != -1) {
            for (i = 0; i < CHAR_MOT_MAX; i++) {
                if (workP->motId[i] == modelP->unk_0C) {
                    break;
                }
            }
            skipAnimUpdate = 1;
            updateBmpF = TRUE;
            if (i != CHAR_MOT_MAX) {
                workP->motNoShiftCurr = workP->motNoTbl[i];
                UpdateCharAnim(*property, workP->modelId, workP->motNoTbl[i], workP->voiceFlag[i], modelP->unk_84, &sp8);
                workP->motNoShiftPrev = workP->motNoTbl[i];
            }
            else {
                workP->motNoShiftCurr = -1;
            }
        }
        else if (updateBmpF) {
            EyeBmpUpdate(*property);
            updateBmpF = FALSE;
        }
        workP->pos = modelP->pos;
        HuPrcVSleep();
    }
}

static void UpdateCharAnim(s16 charNo, HU3DMODELID modelId, s16 motNo, u8 voiceFlag, s16 frameNo, HuVecF *ofs)
{
    HuVecF pos;
    HuVecF hitPos;
    ModelData *modelP;
    s16 var_r19;
    ParticleData *var_r18;
    ModelData *var_r17;
    HU3DPARTICLEDATA *var_r27;
    CHARWORK *workP;
    Mtx hitMtx;
    u32 attrOld;
    s16 var_r20;
    s16 i;
    
    modelP = &Hu3DData[modelId];
    workP = &charWork[charNo];
    attrOld = 0;
    if (skipAnimUpdate == 0 && (modelP->motion_attr & HU3D_MOTATTR_PAUSE)) {
        return;
    }
    switch (motNo) {
        case 2:
            if (skipAnimUpdate == 0 && modelP->unk_68 <= 0.5) {
                break;
            }
            if (skipAnimUpdate != 0 && modelP->unk_88 <= 0.5) {
                break;
            }
            if (!(frameNo & 0xF) && !(workP->attr & 0x10)) {
                dustEffParam.vel.x = 2.0 * -sind(modelP->rot.y);
                dustEffParam.vel.y = 1.0 + 0.1 * frandmod(10);
                dustEffParam.vel.z = 2.0 * -cosd(modelP->rot.y);
                pos.x = modelP->pos.x + modelP->scale.x * (frandmod(50) - 25);
                pos.y = modelP->pos.y;
                pos.z = modelP->pos.z + modelP->scale.x * (frandmod(50) - 25);
                EffectDustCreate(modelId, pos.x, pos.y, pos.z, frandmod(10) + 30, &dustEffParam);
            }
            for (i = 0; i < 4; i++) {
                if (lbl_801309A0[charNo * 4 + i] == frameNo) {
                    PlayStepVoice(charNo, 0x101, voiceFlag);
                    break;
                }
            }
            break;
        case 3:
            if (skipAnimUpdate == 0 && modelP->unk_68 <= 0.5) {
                break;
            }
            if (skipAnimUpdate != 0 && modelP->unk_88 <= 0.5) {
                break;
            }
            if (!(frameNo & 3) && !(workP->attr & 0x10)) {
                dustEffParam.vel.x = 4.0 * -sind(modelP->rot.y);
                dustEffParam.vel.y = 2.0 + 0.1 * frandmod(10);
                dustEffParam.vel.z = 4.0 * -cosd(modelP->rot.y);
                pos.x = modelP->pos.x + modelP->scale.x * (frandmod(50) - 25);
                pos.y = modelP->pos.y;
                pos.z = modelP->pos.z + modelP->scale.x * (frandmod(50) - 25);
                EffectDustCreate(modelId, pos.x, pos.y, pos.z, frandmod(10) + 30, &dustEffParam);
            }
            for (i = 0; i < 4; i++) {
                if (lbl_801309C0[charNo * 4 + i] == frameNo) {
                    PlayStepVoice(charNo, 0x105, voiceFlag);
                    break;
                }
            }
            break;
        case 4:
            if (frameNo < 5 && !(workP->attr & 0x10)) {
                dustEffParam.vel.x = 6.0 * sind(modelP->rot.y);
                dustEffParam.vel.z = 6.0 * cosd(modelP->rot.y);
                for (i = 0; i < 5; i++) {
                    dustEffParam.vel.y = 2.0 + 0.1 * frandmod(10);
                    pos.x = modelP->pos.x + modelP->scale.x * (frandmod(50) - 25);
                    pos.y = modelP->pos.y;
                    pos.z = modelP->pos.z + modelP->scale.x * (frandmod(50) - 25);
                    EffectDustCreate(modelId, pos.x, pos.y, pos.z, 20.0f, &dustEffParam);
                }
            }
            if (frameNo == 0) {
                PlayStepVoice(charNo, 0x10D, voiceFlag);
            }
            break;
        case 6:
            if (frameNo == 5 && !(workP->attr & 0x10)) {
                for (i = 0; i < 8; i++) {
                    dustEffParam.vel.x = 4.0 * sind(45.0f * i) * modelP->scale.x;
                    dustEffParam.vel.y = 0.0f;
                    dustEffParam.vel.z = 4.0 * cosd(45.0f * i) * modelP->scale.x;
                    EffectDustCreate(modelId, modelP->pos.x, modelP->pos.y + 10.0f * modelP->scale.x, modelP->pos.z, 20.0f, &dustEffParam);
                }
                for (i = 0; i < 8; i++) {
                    dustEffParam.vel.x = 2.0 * sind(45.0f * i + 22.5) * modelP->scale.x;
                    dustEffParam.vel.y = 0.0f;
                    dustEffParam.vel.z = 2.0 * cosd(45.0f * i + 22.5) * modelP->scale.x;
                    EffectDustCreate(modelId, modelP->pos.x, modelP->pos.y + 10.0f * modelP->scale.x, modelP->pos.z, 20.0f, &dustEffParam);
                }
            }
            for (i = 0; i < 2; i++) {
                if (lbl_801309E0[charNo * 2 + i] == frameNo) {
                    PlayStepVoice(charNo, 0x10D, voiceFlag);
                    break;
                }
            }
            break;
        case 7:
            if (motNo == 7) {
                Hu3DModelObjMtxGet(modelId, CharModelItemHookGet(charNo, workP->model, 0), hitMtx);
                var_r20 = 10;
            }
            else {
                Hu3DModelObjMtxGet(modelId, CharModelItemHookGet(charNo, workP->model, 1), hitMtx);
                var_r20 = 13;
            }
            if (frameNo <= var_r20 && !(workP->attr & 0x10)) {
                effectDotParam.vel.x = 0.0f;
                effectDotParam.vel.y = 0.0f;
                effectDotParam.vel.z = 0.0f;
                effectDotParam.scaleVel = -5.0f;
                pos.x = hitMtx[0][3];
                pos.y = hitMtx[1][3];
                pos.z = hitMtx[2][3];
                if (frameNo != 0) {
                    VECSubtract(&pos, ofs, &hitPos);
                    var_r20 = 0.2 * sqrtf(hitPos.x * hitPos.x + hitPos.y * hitPos.y + hitPos.z * hitPos.z);
                    if (var_r20 > 5) {
                        var_r20 = 5;
                    }
                    if (var_r20 < 1) {
                        var_r20 = 1;
                    }
                    for (i = 1; i <= var_r20; i++) {
                        hitPos.x = ofs->x + (pos.x - ofs->x) * ((float)i / var_r20);
                        hitPos.y = ofs->y + (pos.y - ofs->y) * ((float)i / var_r20);
                        hitPos.z = ofs->z + (pos.z - ofs->z) * ((float)i / var_r20);
                        EffectDotCreate(modelId, hitPos.x, hitPos.y, hitPos.z, 50.0f, &effectDotParam);
                    }
                }
                else {
                    EffectDotCreate(modelId, pos.x, pos.y, pos.z, 40.0f, &effectDotParam);
                }
                *ofs = pos;
            }
            break;
        case 0xA:
            if (frameNo == 0) {
                if (!(workP->attr & 0x10)) {
                    for (i = 0; i < 8; i++) {
                        effectStarParam.vel.x = 10.0 * sind(45.0f * i) * modelP->scale.x;
                        effectStarParam.vel.y = 0.0f;
                        effectStarParam.vel.z = 10.0 * cosd(45.0f * i) * modelP->scale.x;
                        EffectStarCreate(
                            modelId, modelP->pos.x, modelP->pos.y + 10.0f * modelP->scale.x, modelP->pos.z, 40.0f, &effectStarParam);
                    }
                    for (i = 0; i < 8; i++) {
                        dustEffParam.vel.x = 4.0 * sind(45.0f * i + 22.5) * modelP->scale.x;
                        dustEffParam.vel.y = 0.0f;
                        dustEffParam.vel.z = 4.0 * cosd(45.0f * i + 22.5) * modelP->scale.x;
                        EffectDustCreate(
                            modelId, modelP->pos.x, modelP->pos.y + 10.0f * modelP->scale.x, modelP->pos.z, 20.0f, &dustEffParam);
                    }
                }
                _CharFXPlay(charNo, 0x119, voiceFlag);
            }
            break;
        case 0x1B:
            if (modelP->unk_0C != -1 && skipAnimUpdate == 0) {
                break;
            }
            if (!(workP->attr & 0x10)) {
                if (frameNo == 10) {
                    var_r19 = EffectWarnCreate(modelId, modelP->pos.x, modelP->pos.y + 100.0f, modelP->pos.z, 20.0f, &effectWarnParam);
                    if (var_r19 == -1) {
                        break;
                    }
                    var_r17 = &Hu3DData[effectMdl[0]];
                    var_r18 = var_r17->unk_120;
                    var_r27 = &var_r18->data[var_r19];
                    var_r27->unk02 = 0;
                    var_r27->unk08.x = modelId;
                    if (charNo == 7) {
                        var_r27->unk08.y = 190.0f;
                    }
                    else if (charNo == 2 || charNo == 5 || charNo == 6) {
                        var_r27->unk08.y = 140.0f;
                    }
                    else {
                        var_r27->unk08.y = 120.0f;
                    }
                    var_r27->unk14.x = var_r27->unk14.z = 0.0f;
                    var_r27->unk14.y = 100.0f;
                }
                if (frameNo == 30) {
                    for (i = 0; i < 8; i++) {
                        dustEffParam.vel.x = 4.0 * sind(45.0f * i + 22.5) * modelP->scale.x;
                        dustEffParam.vel.y = 0.0f;
                        dustEffParam.vel.z = 4.0 * cosd(45.0f * i + 22.5) * modelP->scale.x;
                        EffectDustCreate(
                            modelId, modelP->pos.x, modelP->pos.y + 10.0f * modelP->scale.x, modelP->pos.z, 20.0f, &dustEffParam);
                    }
                }
            }
            break;
        case 0x1C:
            if (modelP->unk_0C != -1 && skipAnimUpdate == 0) {
                break;
            }
            if (!(workP->attr & 0x10) && frameNo == 0) {
                var_r19 = EffectWarnCreate(modelId, modelP->pos.x, modelP->pos.y + 100.0f, modelP->pos.z, 20.0f, &effectWarnParam);
                if (var_r19 == -1) {
                    break;
                }
                var_r17 = &Hu3DData[effectMdl[0]];
                var_r18 = var_r17->unk_120;
                var_r27 = &var_r18->data[var_r19];
                var_r27->unk02 = 0;
                var_r27->unk08.x = modelId;
                if (charNo == 7) {
                    var_r27->unk08.y = 150.0f;
                }
                else if (charNo == 2 || charNo == 5 || charNo == 6) {
                    var_r27->unk08.y = 120.0f;
                }
                else {
                    var_r27->unk08.y = 100.0f;
                }
                var_r27->unk14.x = var_r27->unk14.z = 0.0f;
                var_r27->unk14.y = 100.0f;
            }
            break;
        case 0x15:
        case 0x16:
        case 0x79:
            if (!(workP->attr & 1) && !(workP->attr & 0x10)) {
                _CharFXPlay(charNo, 0x11A, voiceFlag);
                for (i = 0; i < 3; i++) {
                    var_r19 = EffectBirdCreate(
                        modelId, modelP->pos.x, modelP->pos.y + 100.0f * modelP->scale.x, modelP->pos.z, 1.0f, &effectWarnParam);
                    if (var_r19 == -1) {
                        break;
                    }
                    var_r17 = &Hu3DData[effectMdl[7]];
                    var_r18 = var_r17->unk_120;
                    var_r27 = &var_r18->data[var_r19];
                    var_r27->unk02 = 1;
                    var_r27->time = 0;
                    var_r27->unk08.x = charNo;
                    var_r27->unk08.y = i * 0x78;
                    workP->attr |= 1;
                }
            }
            break;
        case 0x13:
            if ((frameNo & 1) && !(workP->attr & 0x10)) {
                Hu3DModelObjMtxGet(modelId, CharModelItemHookGet(charNo, workP->model, 4), hitMtx);
                pos.x = hitMtx[0][3];
                pos.y = hitMtx[1][3];
                pos.z = hitMtx[2][3];
                EffectSmokeCreate(modelId, pos.x, pos.y, pos.z, 20.0f, &effectSmokeParam);
            }
            break;
        case 5:
            if (frameNo == 0) {
                if (workP->stepFx == 4) {
                    _CharFXPlay(charNo, 0x10A, voiceFlag);
                }
                else if (workP->stepFx == 5) {
                    _CharFXPlay(charNo, 0x10C, voiceFlag);
                }
                else {
                    _CharFXPlay(charNo, 0x115, voiceFlag);
                }
            }
            break;
        case 8:
            if (frameNo == 0) {
                _CharFXPlay(charNo, 0x118, voiceFlag);
            }
            break;
        case 0x14:
        case 0x50:
            if (frameNo == 0 && !(workP->attr & 0x14)) {
                _CharFXPlay(charNo, 0x123, voiceFlag);
            }
            break;
        case 0x3B:
        case 0x48:
            if (frameNo == 0 && !(workP->attr & 0x12)) {
                _CharFXPlay(charNo, 0x122, voiceFlag);
            }
            break;
        case 0x3F:
        case 0x53:
        case 0x57:
            if (frameNo == 0 && !(workP->attr & 0x12)) {
                _CharFXPlay(charNo, 0x124, voiceFlag);
            }
            workP->attr |= 2;
            attrOld |= 2;
            break;
        case 0x4B:
            if (frameNo == lbl_801D3600[charNo] && !(workP->attr & 0x12)) {
                _CharFXPlay(charNo, 0x124, voiceFlag);
                workP->attr |= 2;
                attrOld |= 2;
            }
            break;
        case 0x4C:
            if (frameNo == lbl_801D3608[charNo] && !(workP->attr & 0x12)) {
                _CharFXPlay(charNo, 0x124, voiceFlag);
                workP->attr |= 2;
                attrOld |= 2;
            }
            break;
        case 0x17:
            if (!(workP->attr & 0x12)) {
                if (omcurovl < DLL_w01dll && frameNo == lbl_801D35F0[charNo]) {
                    _CharFXPlay(charNo, 0x124, voiceFlag);
                    workP->attr |= 2;
                    attrOld |= 2;
                }
                else if (omcurovl >= DLL_w01dll && frameNo == lbl_801D35F8[charNo]) {
                    _CharFXPlay(charNo, 0x122, voiceFlag);
                    workP->attr |= 2;
                    attrOld |= 2;
                }
            }
            break;
        case 0x18:
            if (frameNo == lbl_801D3610[charNo] && !(workP->attr & 0x14)) {
                _CharFXPlay(charNo, 0x121, voiceFlag);
                workP->attr |= 4;
                attrOld |= 4;
            }
            break;
        case 0x2A:
        case 0x72:
            if (frameNo == 0 && !(workP->attr & 0x14)) {
                _CharFXPlay(charNo, 0x121, voiceFlag);
            }
            workP->attr |= 4;
            attrOld |= 4;
            break;
        case 0x49:
        case 0x4E:
            if (frameNo == 0 && !(workP->attr & 0x14)) {
                _CharFXPlay(charNo, 0x12E, voiceFlag);
            }
            workP->attr |= 4;
            attrOld |= 4;
            break;
    }
    if (skipAnimUpdate == 0) {
        if (!(attrOld & 4)) {
            workP->attr &= ~4;
        }
        if (!(attrOld & 2)) {
            workP->attr &= ~2;
        }
    }
}

static s32 _CharFXPlay(s16 charNo, s16 seNo, u8 voiceFlag)
{
    CHARWORK *workP = &charWork[charNo];
    ModelData *modelP = &Hu3DData[workP->modelId];
    if (voiceFlag & 1) {
        return;
    }
    if (workP->attr & 8) {
        return CharFXPlayPos(charNo, seNo, &modelP->pos);
    }
    else {
        return CharFXPlay(charNo, seNo);
    }
}

static void EffectInit(void)
{
    HU3DPARTICLEDATA *particleDataP;
    ParticleData *particleP;
    void *data;
    AnimData *anim;
    s16 effInitF;
    s16 i;
    s16 j;

    effInitF = FALSE;
    for (i = 0; i < CHAR_EFFECT_AND_PARTICLE_MAX; i++) {
        if (effectMdl[i] == -1) {
            data = HuDataSelHeapReadNum(effectDataTbl[i].dataNum, MEMORY_DEFAULT_NUM, HEAP_DATA);
            anim = HuSprAnimRead(data);
            effectMdl[i] = Hu3DParticleCreate(anim, effectDataTbl[i].maxCnt);
            if (i == CHAR_EFFECT_AND_PARTICLE_MAX - 1) {
                Hu3DParticleAnimModeSet(effectMdl[i], 0);
            }
            Hu3DParticleHookSet(effectMdl[i], UpdateEffect);
            if (!particleData[i]) {
                particleData[i] = HuMemDirectMalloc(HEAP_SYSTEM, effectDataTbl[i].maxCnt * sizeof(EFFECTPARAM));
            }
            Hu3DParticleBlendModeSet(effectMdl[i], effectDataTbl[i].blendMode);
            particleP = Hu3DData[effectMdl[i]].unk_120;
            particleP->unk_02 = 0;
            particleP->unk_1C = particleData[i];
            particleP->unk_34 = 1;
            particleDataP = particleP->data;
            for (j = 0; j < particleP->unk_30; j++, particleDataP++) {
                particleDataP->unk2C = 0.0f;
            }
            effInitF = TRUE;
        }
    }
    if (effInitF != 0) {
        HuDataDirClose(DATADIR_EFFECT);
    }
}

static s16 EffectDustCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param)
{
    ModelData *modelP = &Hu3DData[modelId];
    if (effectMdl[2] == -1) {
        return -1;
    }
    scale *= modelP->scale.x;
    return EffectCreate(effectMdl[2], modelP->camera, posX, posY, posZ, scale, param);
}

static s16 EffectSmokeCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param)
{
    ModelData *modelP = &Hu3DData[modelId];
    if (effectMdl[3] == -1) {
        return -1;
    }
    scale *= modelP->scale.x;
    return EffectCreate(effectMdl[3], modelP->camera, posX, posY, posZ, scale, param);
}

static s16 EffectDotCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param)
{
    ModelData *modelP = &Hu3DData[modelId];
    if (effectMdl[6] == -1) {
        return -1;
    }
    scale *= modelP->scale.x;
    return EffectCreate(effectMdl[6], modelP->camera, posX, posY, posZ, scale, param);
}

static s16 EffectStarCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param)
{
    ModelData *modelP = &Hu3DData[modelId];
    if (effectMdl[4] == -1) {
        return -1;
    }
    scale *= modelP->scale.x;
    return EffectCreate(effectMdl[4], modelP->camera, posX, posY, posZ, scale, param);
}

static s16 EffectWarnCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param)
{
    ModelData *modelP = &Hu3DData[modelId];
    if (effectMdl[0] == -1) {
        return -1;
    }
    scale *= modelP->scale.x;
    return EffectCreate(effectMdl[0], modelP->camera, posX, posY, posZ, scale, param);
}

static s16 EffectBirdCreate(s16 modelId, float posX, float posY, float posZ, float scale, EFFECTPARAM *param)
{
    ModelData *modelP = &Hu3DData[modelId];
    if (effectMdl[7] == -1) {
        return -1;
    }
    scale *= modelP->scale.x;
    return EffectCreate(effectMdl[7], modelP->camera, posX, posY, posZ, scale, param);
}

static s16 EffectCreate(s16 type, s16 cameraBit, float posX, float posY, float posZ, float scale, EFFECTPARAM *param)
{
    ModelData *modelP = &Hu3DData[type];
    ParticleData *particleP = modelP->unk_120;
    EFFECTPARAM *effParam = particleP->unk_1C;
    HU3DPARTICLEDATA *particleDataP = &particleP->data[particleP->unk_02];
    s16 i;
    for (i = particleP->unk_02; i < particleP->unk_30; i++, particleDataP++) {
        if (!particleDataP->unk2C) {
            break;
        }
    }
    if (i >= particleP->unk_30) {
        particleDataP = particleP->data;
        for (i = 0; i < particleP->unk_30; i++, particleDataP++) {
            if (!particleDataP->unk2C) {
                break;
            }
        }
    }
    if (i != particleP->unk_30) {
        effParam[i] = *param;
        particleDataP->unk06 = cameraBit;
        particleDataP->unk34.x = posX;
        particleDataP->unk34.y = posY;
        particleDataP->unk34.z = posZ;
        particleDataP->unk08 = param->vel;
        particleDataP->unk40.r = param->colorBegin.r;
        particleDataP->unk40.g = param->colorBegin.g;
        particleDataP->unk40.b = param->colorBegin.b;
        particleDataP->unk40.a = param->colorBegin.a;
        particleDataP->unk28 = scale;
        particleDataP->unk2C = scale;
        particleDataP->time = 0;
        particleDataP->unk02 = HU3D_PARMANID_NONE;
        particleP->unk_02 = i;
    }
    else {
        return -1;
    }
    return i;
}

static void UpdateEffect(ModelData *model, ParticleData *particle, Mtx matrix)
{
    EFFECTPARAM *effParam = particle->unk_1C;
    HU3DPARTICLEDATA *particleDataP;
    s16 var_r28;
    s16 i;

    if (particle->unk_34 == 0) {
        particleDataP = particle->data;
        for (i = 0; i < particle->unk_30; i++, particleDataP++) {
            particleDataP->unk2C = 0.0f;
        }
    }
    particleDataP = particle->data;
    for (i = 0; i < particle->unk_30; i++, particleDataP++) {
        if (particleDataP->unk2C) {
            if (particleDataP->unk02 == -1) {
                particleDataP->unk08.x *= effParam[i].velDecay.x;
                particleDataP->unk08.y *= effParam[i].velDecay.y;
                particleDataP->unk08.z *= effParam[i].velDecay.z;
                VECAdd(&particleDataP->unk08, &particleDataP->unk34, &particleDataP->unk34);
                particleDataP->unk08.y += effParam[i].gravity;
                var_r28 = particleDataP->unk40.r + effParam[i].colorWeight * (effParam[i].colorEnd.r - effParam[i].colorBegin.r);
                if (var_r28 < 0) {
                    var_r28 = 0;
                }
                else if (var_r28 > 0xFF) {
                    var_r28 = 0xFF;
                }
                particleDataP->unk40.r = var_r28;
                var_r28 = particleDataP->unk40.g + effParam[i].colorWeight * (effParam[i].colorEnd.g - effParam[i].colorBegin.g);
                if (var_r28 < 0) {
                    var_r28 = 0;
                }
                else if (var_r28 > 0xFF) {
                    var_r28 = 0xFF;
                }
                particleDataP->unk40.g = var_r28;
                var_r28 = particleDataP->unk40.b + effParam[i].colorWeight * (effParam[i].colorEnd.b - effParam[i].colorBegin.b);
                if (var_r28 < 0) {
                    var_r28 = 0;
                }
                else if (var_r28 > 0xFF) {
                    var_r28 = 0xFF;
                }
                particleDataP->unk40.b = var_r28;
                var_r28 = particleDataP->unk40.a + effParam[i].alphaBase;
                if (var_r28 < 1) {
                    particleDataP->unk2C = 0.0f;
                }
                particleDataP->unk40.a = var_r28;
                if (particleDataP->unk2C) {
                    if (effParam[i].attr & 1) {
                        particleDataP->unk2C = particleDataP->unk28 * (((particleDataP->time + i) & 1) ? 1.0 : 0.5);
                    }
                    else {
                        particleDataP->unk2C = particleDataP->unk28;
                    }
                    particleDataP->unk28 += effParam[i].scaleVel;
                    if (particleDataP->unk28 <= 0.01f) {
                        particleDataP->unk2C = 0.0f;
                    }
                }
                particleDataP->time++;
            }
            else {
                switch (particleDataP->unk02) {
                    case 0:
                        RotateEffect(particleDataP);
                        break;
                    case 1:
                        PlayEffectSound(particleDataP);
                        break;
                    case 2:
                        UpdateModelEffect(particleDataP);
                        break;
                }
            }
        }
    }
    DCStoreRangeNoSync(particle->data, particle->unk_30 * sizeof(HU3DPARTICLEDATA));
}

static void RotateEffect(HU3DPARTICLEDATA *particleDataP)
{
    ModelData *modelP = &Hu3DData[(s32)particleDataP->unk08.x];
    float var_f31;

    if (particleDataP->time < 8) {
        var_f31 = 0.3 + sind(40.0f + 10.0f * (particleDataP->time + 1));
        particleDataP->unk2C = 50.0f * var_f31 * modelP->scale.x;
        particleDataP->unk40.a = 0xFF;
        var_f31 = 0.3 + sind(15.0f * (particleDataP->time + 1));
    }
    else {
        var_f31 = 0.3 + sind(135);
    }
    var_f31 *= modelP->scale.x;
    particleDataP->unk34.x = modelP->pos.x + particleDataP->unk14.x * var_f31;
    particleDataP->unk34.y = modelP->pos.y + particleDataP->unk08.y * modelP->scale.x + particleDataP->unk14.y * var_f31;
    particleDataP->unk34.z = modelP->pos.z + particleDataP->unk14.z * var_f31;
    if (particleDataP->time > 20) {
        particleDataP->unk40.a -= 32;
        particleDataP->unk2C -= 8.0f * modelP->scale.x;
        if (particleDataP->unk2C < 0.0f) {
            particleDataP->unk2C = 0.0f;
        }
    }
    particleDataP->time++;
}

static float voiceParam[16]
    = { 110.0f, 160.0f, 110.0f, 160.0f, 150.0f, 180.0f, 130.0f, 160.0f, 130.0f, 160.0f, 150.0f, 160.0f, 150.0f, 180.0f, 120.0f, 210.0f };

static void PlayEffectSound(HU3DPARTICLEDATA *particleDataP)
{
    ModelData *modelP;
    CHARWORK *workP;
    s16 temp_r26;
    s16 temp_r28;
    s16 var_r25;

    temp_r28 = particleDataP->unk08.x;
    workP = &charWork[temp_r28];
    modelP = &Hu3DData[workP->modelId];
    if (particleDataP->time < 0x14 && particleDataP->unk2C < 40.0f * modelP->scale.x) {
        particleDataP->unk2C += 4.0f * modelP->scale.x;
    }
    particleDataP->unk40.a = 0xFF;
    if (workP->motNoCurr == 0x16 || workP->motNoShiftCurr == 0x16) {
        var_r25 = voiceParam[temp_r28 * 2];
    }
    else {
        var_r25 = voiceParam[temp_r28 * 2 + 1];
    }
    temp_r26 = (particleDataP->time * 5) % 360;
    particleDataP->unk34.x = modelP->pos.x + 40.0 * sind(particleDataP->unk08.y + temp_r26) * modelP->scale.x;
    particleDataP->unk34.y = modelP->pos.y + var_r25 * modelP->scale.x;
    particleDataP->unk34.z = modelP->pos.z + 40.0 * cosd(particleDataP->unk08.y + temp_r26) * modelP->scale.x;
    particleDataP->time++;
    if (particleDataP->time >= 0x8F) {
        particleDataP->time = 0x48;
    }
    if (workP->motNoCurr != 0x15 && workP->motNoCurr != 0x16 && workP->motNoCurr != 0x79 && particleDataP->time > 0x1E) {
        particleDataP->unk2C -= 4.0f * modelP->scale.x;
        if (particleDataP->unk2C < 0.0f) {
            particleDataP->unk2C = 0.0f;
            workP->attr &= ~1;
            if (particleDataP->unk08.y == 0.0) {
                _CharFXPlay(temp_r28, 0x100, workP->attr);
            }
        }
    }
}

HU3DMOTID CharMotionCreate(s16 charNo, s32 data_num)
{
    CHARWORK *workP = &charWork[charNo];
    s16 i;
    s16 motNo;
    u32 dir;
    void *data;

    if (workP->modelId == -1) {
        return -1;
    }
    for (motNo = 0; motNo < 32; motNo++) {
        if (workP->motId[motNo] == -1) {
            break;
        }
    }
    if (motNo == CHAR_MOT_MAX) {
        return HU3D_MOTID_NONE;
    }
    dir = data_num & 0xFFFF0000;
    for (i = 0; i < CHARNO_MAX; i++) {
        if (dir == charDirTbl[i][2]) {
            break;
        }
    }
    if (i != CHARNO_MAX  || dir == 0) {
        data_num &= 0xFFFF;
        data = HuAR_ARAMtoMRAMFileRead(data_num | charDirTbl[charNo][2], MEMORY_DEFAULT_NUM, HEAP_DATA);
        if (!data) {
            data = HuDataSelHeapReadNum(data_num | charDirTbl[charNo][2], MEMORY_DEFAULT_NUM, HEAP_DATA);
        }
        workP->motNoTbl[motNo] = data_num;
    }
    else {
        data = HuDataSelHeapReadNum(data_num, MEMORY_DEFAULT_NUM, HEAP_DATA);
        workP->motNoTbl[motNo] = HU3D_MOTID_NONE;
    }
    workP->motId[motNo] = Hu3DJointMotion(workP->modelId, data);
    workP->voiceFlag[motNo] = 0;
    return workP->motId[motNo];
}

void CharMotionNoSet(s16 charNo, HU3DMOTID motId, s32 motNo)
{
    CHARWORK *workP = &charWork[charNo];
    s16 i;

    for (i = 0; i < ARRAY_COUNT(workP->motId); i++) {
        if (workP->motId[i] == motId) {
            break;
        }
    }
    if (i != ARRAY_COUNT(workP->motId)) {
        workP->motNoTbl[i] = motNo;
    }
}

void CharMotionKill(s16 charNo, u32 motId)
{
    CHARWORK *workP = &charWork[charNo];
    s16 i;

    for (i = 0; i < ARRAY_COUNT(workP->motId); i++) {
        if (workP->motId[i] == motId) {
            break;
        }
    }
    workP->motId[i] = -1;
    Hu3DMotionKill(motId);
}

void CharMotionDataClose(s16 charNo)
{
    s16 i;

    if (charNo == CHARNO_NONE) {
        for (i = 0; i < CHARNO_MAX; i++) {
            CharMotionDataClose(i);
        }
    }
    else {
        HuDataDirClose(charDirTbl[charNo][2]);
    }
}

void CharModelDataClose(s16 charNo)
{
    s16 i;

    if (charNo == CHARNO_NONE) {
        for (i = 0; i < CHARNO_MAX; i++) {
            CharModelDataClose(i);
            // Required to match.
            (void)i;
            (void)charNo;
        }
    }
    else {
        HuDataDirClose(charDirTbl[charNo][0]);
        HuDataDirClose(charDirTbl[charNo][1]);
        HuDataDirClose(charDirTbl[charNo][2]);
    }
}

void CharModelKill(s16 charNo)
{
    CHARWORK *workP;
    s16 i;

    if (charNo == CHARNO_NONE) {
        for (i = 0; i < CHARNO_MAX; i++) {
            CharModelKill(i);
        }
        for (i = 0; i < ARRAY_COUNT(dustFlags); i++) {
            dustFlags[i] = 0;
        }
        return;
    }
    CharMotionDataClose(charNo);
    workP = &charWork[charNo];
    for (i = 0; i < ARRAY_COUNT(workP->motId); i++) {
        if (workP->motId[i] != HU3D_MOTID_NONE) {
            Hu3DMotionKill(workP->motId[i]);
        }
        workP->motId[i] = HU3D_MOTID_NONE;
    }
    if (workP->modelId != HU3D_MODELID_NONE) {
        Hu3DModelKill(workP->modelId);
    }
    workP->modelId = HU3D_MODELID_NONE;
    for (i = 0; i < CHARNO_MAX; i++) {
        if (charWork[i].modelId != HU3D_MODELID_NONE) {
            break;
        }
    }
    if (i == CHARNO_MAX) {
        for (i = 0; i < CHAR_EFFECT_AND_PARTICLE_MAX; i++) {
            if (effectMdl[i] != HU3D_MODELID_NONE) {
                Hu3DModelKill(effectMdl[i]);
            }
            effectMdl[i] = HU3D_MODELID_NONE;
        }
    }
    if (workP->process) {
        HuMemDirectFree(workP->process->user_data);
        HuPrcKill(workP->process);
        for (i = 0; i < ARRAY_COUNT(itemHookProcess); i++) {
            if (itemHookProcess[i]) {
                HuPrcKill(itemHookProcess[i]);
            }
            itemHookProcess[i] = NULL;
        }
        workP->process = NULL;
    }
}

void CharMotionSet(s16 charNo, HU3DMOTID motId)
{
    CHARWORK *workP = &charWork[charNo];
    MotionData *motP = &Hu3DMotion[motId];
    EyeBmpUpdate(charNo);
    Hu3DMotionSet(workP->modelId, motId);
}

static void EyeBmpUpdate(s16 charNo)
{
    CHARWORK *workP = &charWork[charNo];
    ModelData *modelP = &Hu3DData[workP->modelId];
    HSFATTRIBUTE *attrP = modelP->hsfData->attribute;
    s16 modelBit;
    s16 i;
    char **eyeBmp;
    
    for (i = 0, modelBit = 1; i < 4; i++, modelBit <<= 1) {
        if (modelBit & workP->model) {
            break;
        }
    }
    if (i < 4) {
        eyeBmp = CharModelEyeBmpGet(charNo, workP->model);
        for (i = 0; i < modelP->hsfData->attributeNum; i++, attrP++) {
            if ((attrP->bitmap->name[0] == eyeBmp[0][0] && strcmp(attrP->bitmap->name, eyeBmp[0]) == 0)
            || (attrP->bitmap->name[0] == eyeBmp[1][0] && strcmp(attrP->bitmap->name, eyeBmp[1]) == 0)) {
                if (attrP->animWorkP) {
                    HsfdrawStruct01 *particleDataP = attrP->animWorkP;
                    particleDataP->unk08 = particleDataP->unk0C = particleDataP->unk10 = 0.0f;
                    particleDataP->unk14 = particleDataP->unk18 = particleDataP->unk1C = 0.0f;
                }
            }
        }
    }
}

char *charEyeBmpNameTbl[64] = { "s3c000m1_eyes", "s3c000m1_eyes", "s3c000m1_eyes", "s3c000m1_eyes", "s3c000m2_eyes", "s3c000m2_eyes", "s3c000m3_eyes",
    "s3c000m3_eyes", "S3c001m0_eye", "S3c001m0_eye", "S3c001m1_eye", "S3c001m1_eye", "c001m3_eye", "c001m3_eye", "c001m3_eye", "c001m3_eye",
    "s3c002m0_r_eye", "s3c002m0_l_eye", "s3c002m1_r_eye", "s3c002m1_l_eye", "s3c002m2_r_eye", "s3c002m2_l_eye", "", "", "eye1", "eye2", "S3c003m1",
    "S3c003m1", "eye1", "eye2", "eye1", "eye2", "GC-eyes", "GC-eyes", "s3c004m1_eye", "s3c004m1_eye", "Clswario_eye_l1_AUTO12",
    "Clswario_eye_l1_AUTO13", "", "", "m_donkey_eye4", "m_donkey_eye5", "S3donkey_eye", "S3donkey_eye", "m_donkey_eye1", "m_donkey_eye2", "", "",
    "GC-eyes", "GC-eyes", "s3c007m1_Eye_L", "s3c007m1_Eye_R", "mat87", "mat89", "", "", "clswaluigi_eye_l1_AUTO1", "clswaluigi_eye_l1_AUTO2",
    "s3c007_m1_eye", "s3c007_m1_eye", "clswaluigi_eye_l1_AUTO9", "clswaluigi_eye_l1_AUTO10", "", "" };

char **CharModelEyeBmpGet(s16 charNo, s16 model)
{
    s16 bit;
    s16 i;

    for (i = 0, bit = 1; i < 3; i++, bit <<= 1) {
        if (bit & model) {
            break;
        }
    }
    return &charEyeBmpNameTbl[charNo * (CHAR_MODEL_MAX * 2) + i * 2];
}

static char *hookNameTbl[CHARNO_MAX * 5]
    = { "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body", "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr",
          "a-itemhook-fl", "a-itemhook-body", "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body", "a-itemhook-r",
          "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body", "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl",
          "a-itemhook-body", "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body", "a-itemhook-r", "a-itemhook-l",
          "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body", "a-itemhook-r", "a-itemhook-l", "a-itemhook-fr", "a-itemhook-fl", "a-itemhook-body" };

char *CharModelItemHookGet(s16 charNo, s16 model, s16 hookNo)
{
    s16 i;
    s16 bit;

    for (i = 0, bit = 1; i < 3; i++, bit <<= 1) {
        if (bit & model) {
            break;
        }
    }
    return hookNameTbl[charNo * 5 + hookNo];
}

void CharMotionTimeSet(s16 charNo, float time)
{
    CHARWORK *workP = &charWork[charNo];

    Hu3DMotionTimeSet(workP->modelId, time);
}

float CharMotionTimeGet(s16 charNo)
{
    CHARWORK *workP = &charWork[charNo];

    return Hu3DMotionTimeGet(workP->modelId);
}

float CharMotionMaxTimeGet(s16 charNo)
{
    CHARWORK *workP = &charWork[charNo];

    return Hu3DMotionMaxTimeGet(workP->modelId);
}

s32 CharMotionEndCheck(s16 charNo)
{
    CHARWORK *workP = &charWork[charNo];

    return Hu3DMotionEndCheck(workP->modelId);
}

s16 CharMotionShiftIDGet(s16 charNo)
{
    CHARWORK *workP = &charWork[charNo];

    return Hu3DMotionShiftIDGet(workP->modelId);
}

void CharMotionShiftSet(s16 charNo, HU3DMOTID motId, float start, float end, u32 attr)
{
    CHARWORK *workP = &charWork[charNo];
    MotionData *motP = &Hu3DMotion[motId];

    Hu3DMotionShiftSet(workP->modelId, motId, start, end, attr);
}

float CharMotionShiftTimeGet(s16 charNo)
{
    CHARWORK *workP = &charWork[charNo];

    return Hu3DMotionShiftTimeGet(workP->modelId);
}

void CharMotionSpeedSet(s16 charNo, float speed)
{
    CHARWORK *workP = &charWork[charNo];

    Hu3DMotionSpeedSet(workP->modelId, speed);
}

void CharEffectLayerSet(s16 layerNo)
{
    s16 i;

    for (i = 0; i < CHAR_EFFECT_AND_PARTICLE_MAX; i++) {
        if (effectMdl[i] != HU3D_MODELID_NONE) {
            Hu3DModelLayerSet(effectMdl[i], layerNo);
        }
    }
}

static inline Process *CharModelItemHookCreateInlineFunc(void)
{
    s16 i;

    for (i = 0; i < ARRAY_COUNT(itemHookProcess); i++) {
        if (!itemHookProcess[i]) {
            break;
        }
    }
    if (i == ARRAY_COUNT(itemHookProcess)) {
        return NULL;
    }
    else {
        itemHookProcess[i] = HuPrcCreate(CreateHookDust, 0x64, 0x2000, 0);
        return itemHookProcess[i];
    }
}

typedef struct HookDustWork_s {
    u16 cameraBit;
    HU3DMODELID modelId;
} HOOKDUSTWORK; // Size 4

void CharModelHookDustCreate(s16 charNo, char *objName)
{
    CHARWORK *workP = &charWork[charNo];
    ModelData *modelP = &Hu3DData[workP->modelId];
    HSFOBJECT *objPtr = Hu3DModelObjPtrGet(workP->modelId, objName);
    HsfConstData *constData;
    Process *process;
    HOOKDUSTWORK *hookDustWork;
    s16 hookMdlId;
    Mtx hookMtx;
    HuVecF temp;

    Hu3DModelObjMtxGet(workP->modelId, objName, hookMtx);
    constData = objPtr->constData;
    hookMdlId = constData->hook;
    if (hookMdlId != HU3D_MODELID_NONE) {
        Hu3DModelHookObjReset(workP->modelId, objName);
        process = CharModelItemHookCreateInlineFunc();
        if (!process) {
            Hu3DModelAttrSet(hookMdlId, HU3D_ATTR_DISPOFF);
            return;
        }
        process->user_data = hookDustWork = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(HOOKDUSTWORK), MEMORY_DEFAULT_NUM);
        modelP = &Hu3DData[hookMdlId];
        Hu3DMtxTransGet(hookMtx, &temp);
        Hu3DModelPosSetV(hookMdlId, &temp);
        Hu3DMtxRotGet(hookMtx, &temp);
        mtxRot(modelP->unk_F0, temp.x, temp.y, temp.z);
        Hu3DMtxScaleGet(hookMtx, &temp);
        Hu3DModelScaleSetV(hookMdlId, &temp);
        hookDustWork->modelId = hookMdlId;
        hookDustWork->cameraBit = modelP->camera;
    }
}

static void CreateHookDust(void)
{
    Mtx rootMtx;
    HuVecF pos;
    Process *process;
    s16 j;
    s16 i;
    HOOKDUSTWORK *hookDustWork = HuPrcCurrentGet()->user_data;
    ModelData *modelP = &Hu3DData[hookDustWork->modelId];
    Hu3DModelObjMtxGet(hookDustWork->modelId, "", rootMtx);
    pos.x = PGMinPos.x + (PGMaxPos.x - PGMinPos.x) / 2;
    pos.y = PGMinPos.y + (PGMaxPos.y - PGMinPos.y) / 2;
    pos.z = PGMinPos.z + (PGMaxPos.z - PGMinPos.z) / 2;
    for (i = 0; i < 40; i++) {
        modelP->pos.y += 4.0f;
        mtxRotCat(modelP->unk_F0, 24.0f, 0.0f, 0.0f);
        modelP->scale.x *= 0.95f;
        modelP->scale.y *= 0.95f;
        modelP->scale.z *= 0.95f;
        HuPrcVSleep();
    }
    Hu3DModelObjMtxGet(hookDustWork->modelId, "", rootMtx);
    pos.x = PGMinPos.x + (PGMaxPos.x - PGMinPos.x) / 2;
    pos.y = PGMinPos.y + (PGMaxPos.y - PGMinPos.y) / 2;
    pos.z = PGMinPos.z + (PGMaxPos.z - PGMinPos.z) / 2;
    Hu3DModelAttrSet(hookDustWork->modelId, HU3D_ATTR_DISPOFF);
    dustEffParam.vel.x = 0.0f;
    dustEffParam.vel.y = 0.0f;
    dustEffParam.vel.z = 0.0f;
    EffectDustCreate(hookDustWork->modelId, pos.x, pos.y, pos.z, 40.0f, &dustEffParam);
    for (i = 0; i < 8; i++) {
        dustEffParam.vel.x = frandmod(10) - 5;
        dustEffParam.vel.y = frandmod(10) - 5;
        dustEffParam.vel.z = frandmod(10) - 5;
        EffectDustCreate(hookDustWork->modelId, pos.x, pos.y, pos.z, 20.0f, &dustEffParam);
    }
    PSMTXIdentity(modelP->unk_F0);
    process = HuPrcCurrentGet();
    for (j = 0; j < ARRAY_COUNT(itemHookProcess); j++) {
        if (itemHookProcess[j] == process) {
            HuPrcKill(process);
            itemHookProcess[j] = NULL;
        }
    }
    while (1) {
        HuPrcVSleep();
    }
}

static EFFECTPARAM modelSmokeEffParam
    = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0x40, 0x20, 0x00, 0xFF, { 0.0f, 2.0f, 1.0f }, 0.95f, 0.95f, 0.95f, 0.0f, 0x00000000, 1.0f, -5.0f, 0.02f };

void CharEffectSmokeCreate(s16 cameraBit, HuVecF *pos)
{
    s16 effectNo;
    s16 i;
    HU3DPARTICLEDATA *particleDataP;
    ParticleData *particleP;
    ModelData *modelP;

    for (i = 0; i < CHAR_EFFECT_AND_PARTICLE_MAX; i++) {
        effectNo = EffectCreate(effectMdl[3], cameraBit, pos->x, pos->y, pos->z, 20.0f, &modelSmokeEffParam);
        if (effectNo == -1) {
            break;
        }
        modelP = &Hu3DData[effectMdl[3]];
        particleP = modelP->unk_120;
        particleDataP = &particleP->data[effectNo];
        particleDataP->unk02 = 2;
        particleDataP->unk08.x = 30.0 * sind(i * 45);
        particleDataP->unk08.y = 30.0 * cosd(i * 45);
        particleDataP->unk08.z = 0.0f;
        particleDataP->unk14 = *pos;
        particleDataP->unk20 = 1.15f;
        particleDataP->unk24 = 0.1f * (frandmod(20) - 10);
        particleDataP->unk40.a = 0xFF - frandmod(3) * 16;
    }
    for (i = 0; i < CHAR_EFFECT_AND_PARTICLE_MAX; i++) {
        effectNo = EffectCreate(effectMdl[3], cameraBit, pos->x, pos->y, pos->z, 10.0f, &modelSmokeEffParam);
        if (effectNo == -1) {
            break;
        }
        modelP = &Hu3DData[effectMdl[3]];
        particleP = modelP->unk_120;
        particleDataP = &particleP->data[effectNo];
        particleDataP->unk02 = 2;
        particleDataP->unk08.x = frandmod(100) - 50;
        particleDataP->unk08.y = frandmod(100) - 50;
        particleDataP->unk08.z = frandmod(100) - 50;
        particleDataP->unk14 = *pos;
        particleDataP->unk20 = 1.15f;
        particleDataP->unk24 = 0.1f * (frandmod(20) - 10);
        particleDataP->unk40.a = 0xFF - frandmod(3) * 16;
    }
    effectNo = EffectCreate(effectMdl[3], cameraBit, pos->x, pos->y, pos->z, 10.0f, &modelSmokeEffParam);
    if (effectNo != -1) {
        modelP = &Hu3DData[effectMdl[3]];
        particleP = modelP->unk_120;
        particleDataP = &particleP->data[effectNo];
        particleDataP->unk02 = 2;
        particleDataP->unk08.x = 0.0f;
        particleDataP->unk08.y = 0.0f;
        particleDataP->unk08.z = 0.0f;
        particleDataP->unk14 = *pos;
        particleDataP->unk24 = 0.0f;
        particleDataP->unk20 = 1.15f;
        particleDataP->unk40.a = 0xFF;
    }
}

static void UpdateModelEffect(HU3DPARTICLEDATA *particleDataP)
{
    float speed;
    float angle;
    s16 alpha;

    angle = 20.0f + 3.75f * particleDataP->time;
    if (angle > 90.0f) {
        angle = 90.0f;
    }
    speed = sind(angle);
    particleDataP->unk34.x = particleDataP->unk14.x + particleDataP->unk08.x * speed;
    particleDataP->unk34.y = particleDataP->unk14.y + particleDataP->unk08.y * speed;
    particleDataP->unk34.z = particleDataP->unk14.z + particleDataP->unk08.z * speed;
    particleDataP->unk2C *= particleDataP->unk20;
    particleDataP->unk20 -= 0.01;
    if (particleDataP->unk20 < 1.0f) {
        particleDataP->unk20 = 1.0f;
    }
    if (particleDataP->time > 8) {
        alpha = particleDataP->unk40.a;
        alpha -= 8;
        if (alpha < 0) {
            particleDataP->unk40.a = 0;
            particleDataP->unk2C = 0.0f;
        }
        else {
            particleDataP->unk40.a = alpha;
        }
    }
    particleDataP->time++;
}

static EFFECTPARAM coinEffParam
    = { 1, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, { 0.0f, 2.0f, 1.0f }, 0.95f, 1.0f, 0.95f, -0.1f, 0x00000000, -0.2f, -8.0f, 0.0f };

void CharEffectCoinGlowCreate(s16 cameraBit, HuVecF *pos)
{
    s16 i;
    for (i = 0; i < 16; i++) {
        s16 angle = i * (360.0f / 16.0f);
        s16 effectNo;
        coinEffParam.vel.x = 5.0 * sind(angle);
        coinEffParam.vel.y = 0.1f * (frandmod(100) - 50);
        coinEffParam.vel.z = 5.0 * cosd(angle);
        effectNo = EffectCreate(effectMdl[5], cameraBit, pos->x, pos->y, pos->z, 30.0f, &coinEffParam);
        if (effectNo == -1) {
            break;
        }
    }
}

static EFFECTPARAM modelHitEffParam
    = { 0, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x80, 0x00, 0xFF, { 0.0f, 2.0f, 1.0f }, 0.95f, 0.95f, 0.95f, 0.0f, 0x00000000, -0.2f, -16.0f, 0.05f };

static EFFECTPARAM hitGlowEffParam
    = { 0, 0xE0, 0x20, 0x20, 0xFF, 0xE0, 0x20, 0x20, 0xFF, { 0.0f, 2.0f, 1.0f }, 1.0f, 1.0f, 1.0f, 0.0f, 0x00000000, -0.2f, -12.0f, 0.05f };

void CharModelHitCreate(s16 charNo)
{
    CHARWORK *workP = &charWork[charNo];
    ModelData *modelP = &Hu3DData[workP->modelId];
    s16 motNo;
    Mtx mtx;
    HuVecF pos;
    HuVecF radius;

    for (motNo = 0; motNo < ARRAY_COUNT(workP->motId); motNo++) {
        if (workP->motId[motNo] == modelP->unk_08) {
            break;
        }
    }
    if (motNo != ARRAY_COUNT(workP->motId)) {
        Hu3DModelObjMtxGet(workP->modelId, "test11_tex_we-itemhook-r", mtx);
        pos.x = mtx[0][3];
        pos.y = mtx[1][3];
        pos.z = mtx[2][3];
        mtxRot(mtx, modelP->rot.x, modelP->rot.y, modelP->rot.z);
        radius.x = mtx[0][2];
        radius.y = mtx[1][2];
        radius.z = mtx[2][2];
        VECScale(&radius, &radius, 20.0f);
        VECAdd(&pos, &radius, &pos);
        CharEffectHitCreate(modelP->camera, &pos, &modelP->rot);
    }
}

void CharEffectHitCreate(s16 cameraBit, HuVecF *pos, HuVecF *rot)
{
    Mtx mtx;
    HuVecF radius;
    HuVecF dir;
    HuVecF vel;
    s16 effectNo;
    s16 i;
    
    mtxRot(mtx, rot->x, rot->y, rot->z);
    radius.x = mtx[0][2];
    radius.y = mtx[1][2];
    radius.z = mtx[2][2];
    for (i = 0; i < 8; i++) {
        float angle = i * 45;
        dir.x = radius.x * radius.y * (1.0 - cosd(angle)) - radius.z * sind(angle);
        dir.y = radius.y * radius.y + (1.0f - radius.y * radius.y) * cosd(angle);
        dir.z = radius.y * radius.z * (1.0 - cosd(angle)) + radius.x * sind(angle);
        VECNormalize(&dir, &dir);
        VECScale(&dir, &modelHitEffParam.vel, 10.0f);
        effectNo = EffectCreate(effectMdl[4], cameraBit, pos->x, pos->y, pos->z, 20.0f, &modelHitEffParam);
        if (effectNo == -1) {
            break;
        }
        VECScale(&radius, &vel, -2.0 - 0.1 * frandmod(20));
        VECScale(&dir, &dir, 2.0f);
        VECAdd(&dir, &vel, &hitGlowEffParam.vel);
        effectNo = EffectCreate(effectMdl[6], cameraBit, pos->x, pos->y, pos->z, 20.0f, &hitGlowEffParam);
        if (effectNo == -1) {
            break;
        }
    }
}

static EFFECTPARAM shoeHitEffParam
    = { 0, 0x20, 0x20, 0xFF, 0xFF, 0x80, 0xFF, 0x20, 0xFF, 0.0f, 2.0f, 1.0f, 0.95f, 0.95f, 0.95f, 0.0f, 0x00000000, -0.2f, -16.0f, 0.06f };

static EFFECTPARAM shoeHitGlowEffParam
    = { 0, 0x20, 0xE0, 0x20, 0xFF, 0x20, 0xE0, 0x20, 0xFF, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0x00000000, -0.2f, -12.0f, 0.05f };

void CharModelShoeHitCreate(s16 charNo)
{
    Mtx mtx;
    HuVecF pos;
    HuVecF radius;
    CHARWORK *workP = &charWork[charNo];
    ModelData *modelP = &Hu3DData[workP->modelId];

    Hu3DModelObjMtxGet(workP->modelId, "test11_tex_we-ske_R_shoe1", mtx);
    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];
    mtxRot(mtx, modelP->rot.x, modelP->rot.y, modelP->rot.z);
    radius.x = mtx[0][2];
    radius.y = mtx[1][2];
    radius.z = mtx[2][2];
    VECScale(&radius, &radius, 30.0f);
    VECAdd(&pos, &radius, &pos);
    CharEffectShoeHitCreate(modelP->camera, &pos, &modelP->rot);
}

void CharEffectShoeHitCreate(s16 cameraBit, HuVecF *pos, HuVecF *rot)
{
    Mtx mtx;
    HuVecF radius;
    HuVecF dir;
    HuVecF vel;
    s16 effectNo;
    s16 i;
    
    mtxRot(mtx, rot->x, rot->y, rot->z);
    radius.x = mtx[0][2];
    radius.y = mtx[1][2];
    radius.z = mtx[2][2];
    for (i = 0; i < 8; i++) {
        float angle = i * 45;
        dir.x = radius.x * radius.y * (1.0 - cosd(angle)) - radius.z * sind(angle);
        dir.y = radius.y * radius.y + (1.0f - radius.y * radius.y) * cosd(angle);
        dir.z = radius.y * radius.z * (1.0 - cosd(angle)) + radius.x * sind(angle);
        VECNormalize(&dir, &dir);
        VECScale(&dir, &shoeHitEffParam.vel, 10.0f);
        effectNo = EffectCreate(effectMdl[4], cameraBit, pos->x, pos->y, pos->z, 20.0f, &shoeHitEffParam);
        if (effectNo == -1) {
            break;
        }
        VECScale(&radius, &vel, -2.0 - 0.1 * frandmod(20));
        VECScale(&dir, &dir, 2.0f);
        VECAdd(&dir, &vel, &shoeHitGlowEffParam.vel);
        effectNo = EffectCreate(effectMdl[6], cameraBit, pos->x, pos->y, pos->z, 20.0f, &shoeHitGlowEffParam);
        if (effectNo == -1) {
            break;
        }
    }
}

void CharModelLayerSetAll2(s16 layerNo)
{
    CharEffectLayerSet(layerNo);
}

void CharMotionVoiceOnSet(s16 charNo, s16 motion, BOOL voiceOn)
{
    CHARWORK *workP = &charWork[charNo];
    s16 i;

    if (workP->modelId == HU3D_MODELID_NONE) {
        return;
    }
    for (i = 0; i < ARRAY_COUNT(workP->motId); i++) {
        if (workP->motId[i] == motion) {
            break;
        }
    }
    if (i != ARRAY_COUNT(workP->motId)) {
        if (!voiceOn) {
            workP->voiceFlag[i] |= 1;
        }
        else {
            workP->voiceFlag[i] &= ~1;
        }
    }
}

void CharModelVoicePanAutoSet(s16 charNo, BOOL voicePanAuto)
{
    CHARWORK *workP = &charWork[charNo];
    if (voicePanAuto) {
        workP->attr |= 8;
    }
    else {
        workP->attr &= ~8;
    }
}

void CharModelFxFlagSet(s16 charNo, BOOL fxFlag)
{
    CHARWORK *workP = &charWork[charNo];

    if (charNo >= CHARNO_MAX ) {
        if (!fxFlag) {
            dustFlags[charNo] |= 0x10;
        }
        else {
            dustFlags[charNo] &= ~0x10;
        }
        return;
    }
    if (!fxFlag) {
        workP->attr |= 0x10;
    }
    else {
        workP->attr &= ~0x10;
    }
}

typedef struct NpcDustWork_s {
    HU3DMODELID modelId;
    HU3DMOTID motId;
    s16 type;
    s16 npcNo;
} NPCDUSTWORK;

s32 CharNpcDustSet(HU3DMODELID modelId, HU3DMOTID motId, s16 type, s16 npcNo)
{
    Process *parent = HuPrcCurrentGet();
    Process *process = HuPrcChildCreate(UpdateNpcDust, 0x64, 0x2000, 0, parent);
    
    if (process) {
        NPCDUSTWORK *work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(NPCDUSTWORK), MEMORY_DEFAULT_NUM);
        process->user_data = work;
        work->modelId = modelId;
        work->motId = motId;
        work->type = type;
        work->npcNo = npcNo;
        EffectInit();
    }
}

s32 CharNpcDustVoiceOffSet(HU3DMODELID modelId, HU3DMOTID motId, s16 type)
{
    s32 ret; // ! - uninitialized

    CharNpcDustSet(modelId, motId, type, CHAR_NPC_NONE);
    return ret;
}

static s8 npcSeTimeTbl[] = { 0x07, 0x20, 0x10, 0x28, 0x01, 0x1E, 0xE7, 0xE7, 0x01, 0x1E, 0x01, 0x1A, 0x01, 0x14, 0x13, 0x20, 0x02, 0x13 };

static u16 lbl_80131158[] = {
    0x0051,
    0x0053,
    0x0057,
    0x0101,
    0x0059,
    0x005B,
    0x0055,
    0x0069,
    0x006A,
};

// Unused?
static s8 lbl_8013116A[] = { 0x01, 0x20, 0x01, 0x15, 0x0A, 0x1E, 0xE7, 0xE7, 0x01, 0x1E, 0x01, 0x10, 0x01, 0x11, 0xE7, 0xE7, 0xE7, 0xE7 };

static u16 lbl_8013117C[] = { 0x0052, 0x0054, 0x0058, 0x0101, 0x005A, 0x005C, 0x0056, 0x0069, 0x006A };

static s8 lbl_8013118E[] = { 0x03, 0x37, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0x01, 0x1A, 0xE7, 0xE7 };

static u16 lbl_8013119C[] = { 0x0051, 0x0053, 0x0057, 0x0101, 0x0059, 0x0068, 0x0055 };

static s8 lbl_801311AA[] = { 0x04, 0x11, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0x01, 0x10, 0xE7, 0xE7 };

static u16 lbl_801311B8[] = { 0x0052, 0x0054, 0x0058, 0x0101, 0x005A, 0x0067, 0x0056 };

static s8 lbl_801311C6[] = { 0x01, 0x17, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7 };

static u16 lbl_801311D4[] = { 0x0051, 0x0053, 0x0057, 0x0101, 0x0059, 0x005B, 0x0055 };

static void UpdateNpcDust(void)
{
    HuVecF pos;
    ModelData *modelP;
    NPCDUSTWORK *work;
    s16 modelId;
    s16 time;
    s16 npcNo;
    s16 i;

    work = HuPrcCurrentGet()->user_data;
    modelId = work->modelId;
    time = 0;
    modelP = &Hu3DData[work->modelId];
    npcNo = work->npcNo - 8;
    while (1) {
        HuPrcVSleep();
        if (work->motId != Hu3DMotionIDGet(modelId)) {
            continue;
        }
        if (modelP->attr & 1) {
            continue;
        }
        time = Hu3DMotionTimeGet(modelId);
        switch (work->type) {
            case 0:
                if (!(time & 0xF) && !(dustFlags[npcNo] & 0x10)) {
                    dustEffParam.vel.x = 2.0 * -sind(modelP->rot.y);
                    dustEffParam.vel.y = 1.0 + 0.1 * frandmod(10);
                    dustEffParam.vel.z = 2.0 * -cosd(modelP->rot.y);
                    pos.x = modelP->pos.x + (frandmod(50) - 25);
                    pos.y = modelP->pos.y;
                    pos.z = modelP->pos.z + (frandmod(50) - 25);
                    EffectDustCreate(modelId, pos.x, pos.y, pos.z, frandmod(10) + 30, &dustEffParam);
                }
                if (work->npcNo != CHAR_NPC_NONE) {
                    for (i = 0; i < 2; i++) {
                        if (npcSeTimeTbl[npcNo * 2 + i] == time * 2) {
                            HuAudFXPlay(lbl_80131158[npcNo]);
                            break;
                        }
                    }
                }
                break;
            case 1:
                if (!(time & 3) && !(dustFlags[npcNo] & 0x10)) {
                    dustEffParam.vel.x = 4.0 * -sind(modelP->rot.y);
                    dustEffParam.vel.y = 2.0 + 0.1 * frandmod(10);
                    dustEffParam.vel.z = 4.0 * -cosd(modelP->rot.y);
                    pos.x = modelP->pos.x + (frandmod(50) - 25);
                    pos.y = modelP->pos.y;
                    pos.z = modelP->pos.z + (frandmod(50) - 25);
                    EffectDustCreate(modelId, pos.x, pos.y, pos.z, frandmod(10) + 30, &dustEffParam);
                }
                if (work->npcNo != CHAR_NPC_NONE) {
                    for (i = 0; i < 2; i++) {
                        if (npcSeTimeTbl[npcNo * 2 + i] == time * 2) {
                            HuAudFXPlay(lbl_8013117C[npcNo]);
                            break;
                        }
                    }
                }
                break;
            case 2:
                if (npcNo != CHAR_NPC_NONE) {
                    if (!(time & 0x1F) && !(dustFlags[npcNo] & 0x10)) {
                        dustEffParam.vel.x = 2.0 * -sind(modelP->rot.y);
                        dustEffParam.vel.y = 1.0 + 0.1 * frandmod(10);
                        dustEffParam.vel.z = 2.0 * -cosd(modelP->rot.y);
                        pos.x = modelP->pos.x + (frandmod(50) - 25);
                        pos.y = modelP->pos.y;
                        pos.z = modelP->pos.z + (frandmod(50) - 25);
                        EffectDustCreate(modelId, pos.x, pos.y, pos.z, frandmod(10) + 30, &dustEffParam);
                    }
                    for (i = 0; i < 2; i++) {
                        if (lbl_8013118E[npcNo * 2 + i] == time * 2) {
                            HuAudFXPlay(lbl_8013119C[npcNo]);
                            break;
                        }
                    }
                }
                break;
            case 3:
                if (npcNo != CHAR_NPC_NONE) {
                    if (!(time & 3) && !(dustFlags[npcNo] & 0x10)) {
                        dustEffParam.vel.x = 2.0 * -sind(modelP->rot.y);
                        dustEffParam.vel.y = 1.0 + 0.1 * frandmod(10);
                        dustEffParam.vel.z = 2.0 * -cosd(modelP->rot.y);
                        pos.x = modelP->pos.x + (frandmod(50) - 25);
                        pos.y = modelP->pos.y;
                        pos.z = modelP->pos.z + (frandmod(50) - 25);
                        EffectDustCreate(modelId, pos.x, pos.y, pos.z, frandmod(10) + 30, &dustEffParam);
                    }
                    for (i = 0; i < 2; i++) {
                        if (lbl_801311AA[npcNo * 2 + i] == time * 2) {
                            HuAudFXPlay(lbl_801311B8[npcNo]);
                            break;
                        }
                    }
                }
                break;
            case 4:
                if (npcNo != CHAR_NPC_NONE) {
                    if (!(time & 7) && !(dustFlags[npcNo] & 0x10)) {
                        dustEffParam.vel.x = 2.0 * -sind(modelP->rot.y);
                        dustEffParam.vel.y = 1.0 + 0.1 * frandmod(10);
                        dustEffParam.vel.z = 2.0 * -cosd(modelP->rot.y);
                        pos.x = modelP->pos.x + (frandmod(50) - 25);
                        pos.y = modelP->pos.y;
                        pos.z = modelP->pos.z + (frandmod(50) - 25);
                        EffectDustCreate(modelId, pos.x, pos.y, pos.z, frandmod(10) + 30, &dustEffParam);
                    }
                    for (i = 0; i < 2; i++) {
                        if (lbl_801311C6[npcNo * 2 + i] == time * 2) {
                            HuAudFXPlay(lbl_801311D4[npcNo]);
                            break;
                        }
                    }
                }
                break;
            case 5:
                if (time != 0) {
                    break;
                }
                if (dustFlags[npcNo] & 0x10) {
                    break;
                }
                for (i = 0; i < CHAR_EFFECT_AND_PARTICLE_MAX; i++) {
                    effectStarParam.vel.x = 10.0 * sind(45.0f * i) * modelP->scale.x;
                    effectStarParam.vel.y = 0.0f;
                    effectStarParam.vel.z = 10.0 * cosd(45.0f * i) * modelP->scale.x;
                    EffectStarCreate(
                        modelId, modelP->pos.x, modelP->pos.y + 10.0f * modelP->scale.x, modelP->pos.z, 40.0f, &effectStarParam);
                }
                for (i = 0; i < CHAR_EFFECT_AND_PARTICLE_MAX; i++) {
                    dustEffParam.vel.x = 4.0 * sind(45.0f * i + 22.5) * modelP->scale.x;
                    dustEffParam.vel.y = 0.0f;
                    dustEffParam.vel.z = 4.0 * cosd(45.0f * i + 22.5) * modelP->scale.x;
                    EffectDustCreate(
                        modelId, modelP->pos.x, modelP->pos.y + 10.0f * modelP->scale.x, modelP->pos.z, 20.0f, &dustEffParam);
                }
                if (npcNo != CHAR_NPC_NONE) {
                    HuAudFXPlay(0x61);
                }
                break;
        }
    }
}

void CharModelStepFxSet(s16 charNo, s32 stepFx)
{
    CHARWORK *workP = &charWork[charNo];

    workP->stepFx = stepFx;
}

static s32 PlayStepVoice(s16 charNo, s16 seId, u8 voiceFlag)
{
    CHARWORK *workP = &charWork[charNo];
    ModelData *modelP = &Hu3DData[workP->modelId];
    if (voiceFlag & 1) {
        return;
    }
    if (workP->stepFx == 4) {
        seId = 0x109;
    }
    else if (workP->stepFx == 5) {
        seId = 0x10B;
    }
    else {
        seId += workP->stepFx;
    }
    if (workP->attr & 8) {
        return CharFXPlayPos(charNo, seId, &modelP->pos);
    }
    else {
        return CharFXPlay(charNo, seId);
    }
}
