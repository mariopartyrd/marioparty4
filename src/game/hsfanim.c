#include "game/hu3d.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXVert.h"
#include "game/init.h"
#include "game/memory.h"
#include "game/process.h"
#include "game/sprite.h"

#include "ext_math.h"
#include <string.h>

#ifndef __MWERKS__
#include "game/frand.h"
#endif

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ char unk0A[2];
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ Vec unk18;
    /* 0x24 */ Vec unk24;
    /* 0x30 */ float unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ HU3DPARMANPARAM *unk3C;
} ParManProcUserData; // Size 0x40

static void particleFunc(HU3DMODEL *arg0, Mtx arg1);
static void ParManFunc(void);
static void ParManHook(HU3DMODEL *arg0, HU3DPARTICLE *arg1, Mtx matrix);

u32 frand(void);

extern u32 GlobalCounter;

HU3DTEXANIM Hu3DTexAnimData[HU3D_TEXANIM_MAX];
HU3DTEXSCROLL Hu3DTexScrData[16];
static Process *parManProc[64];

void Hu3DAnimInit(void) {
    HU3DTEXANIM *var_r30;
    HU3DTEXSCROLL *var_r29;
    s16 i;

    var_r30 = Hu3DTexAnimData;
    for (i = 0; i < HU3D_TEXANIM_MAX; i++, var_r30++) {
        var_r30->modelId = -1;
    }
    var_r29 = Hu3DTexScrData;
    for (i = 0; i < HU3D_TEXSCROLL_MAX; i++, var_r29++) {
        var_r29->modelId = -1;
    }
}

s16 Hu3DAnimCreate(void *dataP, s16 modelId, char *bmpName) {
    HU3DTEXANIM *var_r31;
    HSFATTRIBUTE *var_r29;
    HSFDATA *temp_r27;
    HsfdrawStruct01 *var_r30;
    s16 i;
    s16 var_r25;
    s16 var_r28;

    var_r31 = Hu3DTexAnimData;
    for (var_r28 = 0; var_r28 < HU3D_TEXANIM_MAX; var_r28++, var_r31++) {
        if (var_r31->modelId == -1) {
            break;
        }
    }
    if (var_r28 == HU3D_TEXANIM_MAX) {
        OSReport("Error: TexAnim Over\n");
        return -1;
    }
    temp_r27 = Hu3DData[modelId].hsf;
    var_r29 = temp_r27->attribute;
    for (i = var_r25 = 0; i < temp_r27->attributeNum; i++, var_r29++) {
        if (strcmp(bmpName, var_r29->bitmap->name) == 0) {
            if (!var_r29->animWorkP) {
                var_r30 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r30), (u32) Hu3DData[modelId].mallocNo);
                var_r29->animWorkP = var_r30;
                var_r30->unk00 = 0;
            } else {
                var_r30 = var_r29->animWorkP;
            }
            var_r30->unk00 |= 1;
            var_r30->unk02 = var_r28;
            var_r30->unk2C = var_r30->unk30 = 1.0f;
            var_r30->unk34 = var_r30->unk38 = 0.0f;
            var_r25++;
        }
    }
    if (var_r25 == 0) {
        OSReport("Error: Not Found TexAnim Name\n");
        return -1;
    }
    if (!dataP) {
        var_r31->anim = NULL;
    } else {
        var_r31->anim = HuSprAnimRead(dataP);
    }
    var_r31->modelId = modelId;
    var_r31->time = 0.0f;
    var_r31->bank = 0;
    var_r31->anmNo = 0;
    var_r31->attr = 0;
    var_r31->speed = 1.0f;
    return var_r28;
}

s16 Hu3DAnimLink(s16 linkAnimId, s16 modelId, char *bmpName) {
    HU3DTEXANIM *var_r24 = &Hu3DTexAnimData[linkAnimId];
    HU3DTEXANIM *var_r31;
    ANIMDATA *temp_r4;
    HSFATTRIBUTE *var_r29;
    HSFDATA *temp_r27;
    HsfdrawStruct01 *var_r30;
    s16 var_r28;
    s16 i;
    s16 var_r25;

    var_r31 = Hu3DTexAnimData;
    for (var_r28 = 0; var_r28 < HU3D_TEXANIM_MAX; var_r28++, var_r31++) {
        if (var_r31->modelId == -1) {
            break;
        }
    }
    if (var_r28 == HU3D_TEXANIM_MAX) {
        OSReport("Error: TexAnim Over\n");
        return -1;
    }
    temp_r27 = Hu3DData[modelId].hsf;
    var_r29 = temp_r27->attribute;
    for (i = var_r25 = 0; i < temp_r27->attributeNum; i++, var_r29++) {
        if (strcmp(bmpName, var_r29->bitmap->name) == 0) {
            if (!var_r29->animWorkP) {
                var_r30 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r30), (u32) Hu3DData[modelId].mallocNo);
                var_r29->animWorkP = var_r30;
            } else {
                var_r30 = var_r29->animWorkP;
            }
            var_r30->unk02 = var_r28;
            var_r30->unk2C = var_r30->unk30 = 1.0f;
            var_r30->unk34 = var_r30->unk38 = 0.0f;
            var_r25++;
        }
    }
    if (var_r25 == 0) {
        OSReport("Error: Not Found TexAnim Name\n");
        return -1;
    }
    var_r31->anim = var_r24->anim;
    var_r31->anim->useNum++;
    var_r31->modelId = modelId;
    var_r31->time = 0.0f;
    var_r31->bank = 0;
    var_r31->anmNo = 0;
    var_r31->attr = 0;
    var_r31->speed = 1.0f;
    return var_r28;
}

void Hu3DAnimKill(s16 animId) {
    HU3DTEXANIM *temp_r31 = &Hu3DTexAnimData[animId];
    HSFDATA *temp_r28 = Hu3DData[temp_r31->modelId].hsf;
    HSFATTRIBUTE *var_r30;
    HsfdrawStruct01 *temp_r29;
    s16 i;

    if (temp_r28) {
        var_r30 = temp_r28->attribute;
        for (i = 0; i < temp_r28->attributeNum; i++, var_r30++) {
            if (var_r30->animWorkP) {
                temp_r29 = var_r30->animWorkP;
                if (temp_r29->unk02 == animId) {
                    temp_r29->unk00 &= ~1;
                    if (temp_r29->unk00 == 0) {
                        var_r30->animWorkP = NULL;
                        HuMemDirectFree(temp_r29);
                    }
                }
            }
        }
    }
    temp_r31->modelId = -1;
    if (--temp_r31->anim->useNum <= 0) {
        HuMemDirectFree(temp_r31->anim);
    }
}

void Hu3DAnimModelKill(s16 modelId) {
    HU3DTEXANIM *var_r26 = &Hu3DTexAnimData[0];
    s16 i;

    for (i = 0; i < HU3D_TEXANIM_MAX; i++, var_r26++) {
        if (var_r26->modelId == modelId) {
            Hu3DAnimKill(i);
        }
    }
}

void Hu3DAnimAllKill(void) {
    HU3DTEXANIM *var_r26 = &Hu3DTexAnimData[0];
    s16 i;

    for (i = 0; i < HU3D_TEXANIM_MAX; i++, var_r26++) {
        if (var_r26->modelId != -1) {
            Hu3DAnimKill(i);
        }
    }
    Hu3DTexScrollAllKill();
}

void Hu3DAnimAttrSet(s16 animId, u16 attr) {
    HU3DTEXANIM *temp_r31 = &Hu3DTexAnimData[animId];

    temp_r31->attr |= attr;
}

void Hu3DAnimAttrReset(s16 animId, s32 attr) {
    HU3DTEXANIM *temp_r31 = &Hu3DTexAnimData[animId];

    temp_r31->attr &= ~attr;
}

void Hu3DAnimSpeedSet(s16 animId, float speed) {
    HU3DTEXANIM *temp_r31 = &Hu3DTexAnimData[animId];

    temp_r31->speed = speed;
}

void Hu3DAnimBankSet(s16 animId, s32 bank) {
    HU3DTEXANIM *temp_r31 = &Hu3DTexAnimData[animId];

    temp_r31->bank = bank;
    temp_r31->anmNo = temp_r31->time = 0.0f;
}

void Hu3DAnmNoSet(s16 animId, u16 anmNo) {
    HU3DTEXANIM *temp_r31 = &Hu3DTexAnimData[animId];

    temp_r31->anmNo = anmNo;
    temp_r31->time = 0.0f;
}

s32 Hu3DAnimSet(HU3DMODEL *arg0, HSFATTRIBUTE *arg1, s16 arg2) {
    HsfdrawStruct01 *temp_r30;
    HU3DTEXANIM *temp_r29;
    ANIMDATA *temp_r27;
    ANIMBMP *temp_r28;
    ANIMLAYER *temp_r31;
    ANIMPAT *temp_r25;
    s16 temp_r24;
    s16 var_r23;
    s16 var_r22;

    temp_r30 = arg1->animWorkP;
    temp_r29 = &Hu3DTexAnimData[temp_r30->unk02];
    temp_r27 = temp_r29->anim;
    temp_r24 = temp_r27->bank[temp_r29->bank].frame[temp_r29->anmNo].pat;
    if (temp_r24 == -1) {
        return 0;
    }
    var_r23 = (arg1->wrapS == 1) ? 1 : 0;
    var_r22 = (arg1->wrapT == 1) ? 1 : 0;
    temp_r25 = &temp_r27->pat[temp_r24];
    temp_r31 = temp_r25->layer;
    temp_r28 = &temp_r27->bmp[temp_r31->bmpNo];
    HuSprTexLoad(temp_r29->anim, temp_r31->bmpNo, arg2, var_r23, var_r22,
        (arg0->attr & HU3D_ATTR_TEX_NEAR) ? GX_NEAR : GX_LINEAR);
    temp_r30->unk2C = (float) temp_r31->sizeX / temp_r28->sizeX;
    temp_r30->unk30 = (float) temp_r31->sizeY / temp_r28->sizeY;
    temp_r30->unk34 = (float) temp_r31->startX / temp_r28->sizeX;
    temp_r30->unk38 = (float) temp_r31->startY / temp_r28->sizeY;
    return 1;
}

void Hu3DAnimExec(void) {
    HU3DTEXANIM *var_r30;
    HU3DTEXSCROLL *var_r31;
    ANIMDATA *var_r25;
    ANIMBANK *temp_r28;
    ANIMFRAME *var_r29;
    s16 var_r26;
    s16 i;

    var_r30 = Hu3DTexAnimData;
    for (i = 0; i < HU3D_TEXANIM_MAX; i++, var_r30++) {
        if (var_r30->modelId != -1 && (Hu3DPauseF == 0 || (var_r30->attr & 0x20))) {
            var_r25 = var_r30->anim;
            temp_r28 = &var_r25->bank[var_r30->bank];
            var_r29 = &temp_r28->frame[var_r30->anmNo];
            if (!(var_r30->attr & 1) || (var_r29->time == -1 && (var_r30->attr & 2))) {
                for (var_r26 = 0; var_r26 < (s32) var_r30->speed * minimumVcount; var_r26++) {
                    var_r30->time += 1.0f;
                    if (var_r30->time >= var_r29->time) {
                        var_r30->anmNo++;
                        var_r30->time -= var_r29->time;
                        if (var_r30->anmNo >= temp_r28->timeNum || var_r29[1].time == -1) {
                            var_r30->anmNo = 0;
                        }
                        var_r29 = &temp_r28->frame[var_r30->anmNo];
                    }
                }
                var_r30->time += var_r30->speed * minimumVcount - var_r26;
                if (var_r30->time >= var_r29->time) {
                    var_r30->anmNo++;
                    var_r30->time -= var_r29->time;
                    if (var_r30->anmNo >= temp_r28->timeNum || var_r29[1].time == -1) {
                        var_r30->anmNo = 0;
                    }
                }
            }
        }
    }
    var_r31 = Hu3DTexScrData;
    for (i = 0; i < HU3D_TEXSCROLL_MAX; i++, var_r31++) {
        if (var_r31->modelId != -1) {
            if (Hu3DPauseF != 0 && !(var_r31->attr & 8)) {
                PSMTXRotRad(var_r31->texMtx, 'Z', MTXDegToRad(var_r31->rot));
                mtxTransCat(var_r31->texMtx, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
            } else {
                if (var_r31->attr & 1) {
                    VECAdd(&var_r31->pos, &var_r31->posMove, &var_r31->pos);
                    if (var_r31->pos.x > 1.0f) {
                        var_r31->pos.x -= 1.0f;
                    }
                    if (var_r31->pos.y > 1.0f) {
                        var_r31->pos.y -= 1.0f;
                    }
                    if (var_r31->pos.z > 1.0f) {
                        var_r31->pos.z -= 1.0f;
                    }
                    if (var_r31->pos.x < -1.0f) {
                        var_r31->pos.x += 1.0f;
                    }
                    if (var_r31->pos.y < -1.0f) {
                        var_r31->pos.y += 1.0f;
                    }
                    if (var_r31->pos.z < -1.0f) {
                        var_r31->pos.z += 1.0f;
                    }
                }
                if (var_r31->attr & 2) {
                    var_r31->rot += var_r31->rotMove;
                    if (var_r31->rot > 360.0f) {
                        var_r31->rot -= 360.0f;
                    }
                    if (var_r31->rot < -360.0f) {
                        var_r31->rot += 360.0f;
                    }
                }
                PSMTXRotRad(var_r31->texMtx, 'Z', MTXDegToRad(var_r31->rot));
                mtxTransCat(var_r31->texMtx, var_r31->pos.x, var_r31->pos.y, var_r31->pos.z);
            }
        }
    }
}

s16 Hu3DTexScrollCreate(s16 modelId, char *bmpName) {
    HU3DTEXSCROLL *var_r31;
    HSFDATA *temp_r27;
    HSFATTRIBUTE *var_r29;
    HsfdrawStruct01 *var_r30;
    s16 i;
    s16 var_r25;
    s16 var_r28;

    var_r31 = Hu3DTexScrData;
    for (var_r28 = 0; var_r28 < HU3D_TEXSCROLL_MAX; var_r28++, var_r31++) {
        if (var_r31->modelId == -1) {
            break;
        }
    }
    if (var_r28 == HU3D_TEXSCROLL_MAX) {
        OSReport("Error: TexScroll Over\n");
        return -1;
    }
    temp_r27 = Hu3DData[modelId].hsf;
    var_r29 = temp_r27->attribute;
    for (i = var_r25 = 0; i < temp_r27->attributeNum; i++, var_r29++) {
        if (strcmp(bmpName, var_r29->bitmap->name) == 0) {
            if (!var_r29->animWorkP) {
                var_r30 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r30), (u32) Hu3DData[modelId].mallocNo);
                var_r29->animWorkP = var_r30;
                var_r30->unk00 = 0;
            } else {
                var_r30 = var_r29->animWorkP;
            }
            var_r30->unk00 |= 2;
            var_r30->unk04 = var_r28;
            var_r30->unk2C = var_r30->unk30 = 1.0f;
            var_r30->unk34 = var_r30->unk38 = 0.0f;
            var_r25++;
        }
    }
    if (var_r25 == 0) {
        OSReport("Error: Not Found TexAnim Name\n");
        return -1;
    }
    var_r31->modelId = modelId;
    var_r31->attr = 0;
    var_r31->pos.x = var_r31->pos.y = var_r31->pos.z = 0.0f;
    var_r31->rot = 0.0f;
    PSMTXIdentity(var_r31->texMtx);
    return var_r28;
}

void Hu3DTexScrollKill(s16 texSrcId) {
    HU3DTEXSCROLL *temp_r28 = &Hu3DTexScrData[texSrcId];
    HSFDATA *temp_r29 = Hu3DData[temp_r28->modelId].hsf;
    HSFATTRIBUTE *var_r31;
    HsfdrawStruct01 *temp_r30;
    s16 i;

    if (temp_r29) {
        var_r31 = temp_r29->attribute;
        for (i = 0; i < temp_r29->attributeNum; i++, var_r31++) {
            if (var_r31->animWorkP) {
                temp_r30 = var_r31->animWorkP;
                if (temp_r30->unk04 == texSrcId) {
                    temp_r30->unk00 &= ~2;
                    if (temp_r30->unk00 == 0) {
                        var_r31->animWorkP = NULL;
                        HuMemDirectFree(temp_r30);
                    }
                }
            }
        }
    }
    temp_r28->modelId = -1;
}

void Hu3DTexScrollAllKill(void) {
    HU3DTEXSCROLL *var_r27;
    s16 i;

    var_r27 = Hu3DTexScrData;
    for (i = 0; i < HU3D_TEXSCROLL_MAX; i++, var_r27++) {
        if (var_r27->modelId != -1) {
            Hu3DTexScrollKill(i);
        }
    }
}

void Hu3DTexScrollPosSet(s16 texScrId, float posX, float posY, float posZ) {
    HU3DTEXSCROLL *temp_r31 = &Hu3DTexScrData[texScrId];

    temp_r31->attr &= ~1;
    temp_r31->pos.x = posX;
    temp_r31->pos.y = posY;
    temp_r31->pos.z = posZ;
}

void Hu3DTexScrollPosMoveSet(s16 texScrId, float posX, float posY, float posZ) {
    HU3DTEXSCROLL *temp_r31 = &Hu3DTexScrData[texScrId];

    temp_r31->attr |= 1;
    temp_r31->posMove.x = posX * minimumVcount;
    temp_r31->posMove.y = posY * minimumVcount;
    temp_r31->posMove.z = posZ * minimumVcount;
}

void Hu3DTexScrollRotSet(s16 texScrId, float rot) {
    HU3DTEXSCROLL *temp_r31 = &Hu3DTexScrData[texScrId];

    temp_r31->attr &= ~2;
    temp_r31->rot = rot;
}

void Hu3DTexScrollRotMoveSet(s16 texScrId, float rot) {
    HU3DTEXSCROLL *temp_r31 = &Hu3DTexScrData[texScrId];

    temp_r31->attr |= 2;
    temp_r31->rotMove = rot * minimumVcount;
}

void Hu3DTexScrollPauseDisableSet(s16 texScrId, BOOL pauseDisableF) {
    HU3DTEXSCROLL *temp_r31 = &Hu3DTexScrData[texScrId];

    if (pauseDisableF != 0) {
        temp_r31->attr |= 8;
        return;
    } else {
        temp_r31->attr &= ~8;
    }
}

s16 Hu3DParticleCreate(ANIMDATA *anim, s16 maxCnt) {
    HU3DMODEL *temp_r28;
    HU3DPARTICLE *temp_r31;
    HU3DPARTICLEDATA *var_r30;
    Vec *var_r27;
    s16 temp_r25;
    s16 i;
    void *temp_r24;

    temp_r25 = Hu3DHookFuncCreate((void*) &particleFunc);
    temp_r28 = &Hu3DData[temp_r25];
    Hu3DModelAttrSet(temp_r25, HU3D_ATTR_PARTICLE_KILL);
    temp_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(HU3DPARTICLE), temp_r28->mallocNo);
    temp_r28->hookData = temp_r31;
    temp_r31->anim = anim;
    anim->useNum++;
    temp_r31->maxCnt = maxCnt;
    temp_r31->blendMode = 0;
    temp_r31->hook = NULL;
    temp_r31->count = 0;
    temp_r31->attr = 0;
    temp_r31->prevCount = 0;
    temp_r31->dataCnt = temp_r31->emitCnt = 0;
    var_r30 = HuMemDirectMallocNum(HEAP_DATA, maxCnt * sizeof(HU3DPARTICLEDATA), temp_r28->mallocNo);
    temp_r31->data = var_r30;
    temp_r31->prevCounter = -1;
    for (i = 0; i < maxCnt; i++, var_r30++) {
        var_r30->scale = 0.0f;
        var_r30->unk04 = 0;
        var_r30->cameraBit = -1;
        var_r30->zRot = 0.0f;
        var_r30->pos.x = ((s32) (frand() & 0x7F) - 0x40) * 0x14;
        var_r30->pos.y = ((s32) (frand() & 0x7F) - 0x40) * 0x1E;
        var_r30->pos.z = ((s32) (frand() & 0x7F) - 0x40) * 0x14;
        var_r30->color.r = var_r30->color.g = var_r30->color.b = var_r30->color.a = 0xFF;
    }
    var_r27 = HuMemDirectMallocNum(HEAP_DATA, maxCnt * sizeof(Vec) * 4, temp_r28->mallocNo);
    temp_r31->vtxBuf = var_r27;
    for (i = 0; i < maxCnt * 4; i++, var_r27++) {
        var_r27->x = var_r27->y = var_r27->z = 0.0f;
    }
    temp_r24 = HuMemDirectMallocNum(HEAP_DATA, maxCnt * 0x60 + 0x80, temp_r28->mallocNo);
    temp_r31->dlBuf = temp_r24;
    DCInvalidateRange(temp_r24, maxCnt * 0x60 + 0x80);
    GXBeginDisplayList(temp_r24, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, maxCnt * 4);
    for (i = 0; i < maxCnt; i++) {
        GXPosition1x16(i*4);
        GXColor1x16(i);
        GXTexCoord1x16(0);
        GXPosition1x16((i*4)+1);
        GXColor1x16(i);
        GXTexCoord1x16(1);
        GXPosition1x16((i*4)+2);
        GXColor1x16(i);
        GXTexCoord1x16(2);
        GXPosition1x16((i*4)+3);
        GXColor1x16(i);
        GXTexCoord1x16(3);
    }
    temp_r31->dlSize = GXEndDisplayList();
    return temp_r25;
}

void Hu3DParticleScaleSet(s16 modelId, float scale) {
    HU3DMODEL *temp_r25 = &Hu3DData[modelId];
    HU3DPARTICLE *temp_r31 = temp_r25->hookData;
    HU3DPARTICLEDATA *var_r30;
    s16 i;

    var_r30 = temp_r31->data;
    for (i = 0; i < temp_r31->maxCnt; i++, var_r30++) {
        var_r30->scale = scale;
    }
}

void Hu3DParticleZRotSet(s16 modelId, float zRot) {
    HU3DMODEL *temp_r28 = &Hu3DData[modelId];
    HU3DPARTICLE *temp_r31 = temp_r28->hookData;
    HU3DPARTICLEDATA *var_r30;
    s16 i;

    var_r30 = temp_r31->data;
    for (i = 0; i < temp_r31->maxCnt; i++, var_r30++) {
        var_r30->zRot = zRot;
    }
}

void Hu3DParticleColSet(s16 modelId, u8 r, u8 g, u8 b) {
    HU3DMODEL *temp_r28 = &Hu3DData[modelId];
    HU3DPARTICLE *temp_r30 = temp_r28->hookData;
    HU3DPARTICLEDATA *var_r31;
    s16 i;

    var_r31 = temp_r30->data;
    for (i = 0; i < temp_r30->maxCnt; i++, var_r31++) {
        var_r31->color.r = r;
        var_r31->color.g = g;
        var_r31->color.b = b;
    }
}

void Hu3DParticleTPLvlSet(s16 modelId, float tpLvl) {
    HU3DMODEL *temp_r28 = &Hu3DData[modelId];
    HU3DPARTICLE *temp_r31 = temp_r28->hookData;
    HU3DPARTICLEDATA *var_r30;
    u8 var_r27;
    s16 i;

    var_r30 = temp_r31->data;
    var_r27 = tpLvl * 255.0f;
    for (i = 0; i < temp_r31->maxCnt; i++, var_r30++) {
        var_r30->color.a = var_r27;
    }
}

void Hu3DParticleBlendModeSet(s16 modelId, u8 blendMode) {
    HU3DMODEL *temp_r31 = &Hu3DData[modelId];
    HU3DPARTICLE *temp_r30 = temp_r31->hookData;

    temp_r30->blendMode = blendMode;
}

void Hu3DParticleHookSet(s16 modelId, HU3DPARTICLEHOOK hook) {
    HU3DMODEL *temp_r31 = &Hu3DData[modelId];
    HU3DPARTICLE *temp_r30 = temp_r31->hookData;

    temp_r30->hook = hook;
}

void Hu3DParticleAttrSet(s16 modelId, u8 attr) {
    HU3DMODEL *temp_r31 = &Hu3DData[modelId];
    HU3DPARTICLE *temp_r30 = temp_r31->hookData;

    temp_r30->attr |= attr;
}

void Hu3DParticleAttrReset(s16 modelId, u8 attr) {
    HU3DMODEL *temp_r31 = &Hu3DData[modelId];
    HU3DPARTICLE *temp_r30 = temp_r31->hookData;

    temp_r30->attr &= ~attr;
}

void Hu3DParticleCntSet(s16 modelId, s16 count) {
    HU3DMODEL *temp_r31 = &Hu3DData[modelId];
    HU3DPARTICLE *temp_r30 = temp_r31->hookData;

    temp_r30->count = count;
}

void Hu3DParticleAnimModeSet(s16 modelId, s16 animBank) {
    HU3DMODEL *temp_r30 = &Hu3DData[modelId];
    HU3DPARTICLE *temp_r31 = temp_r30->hookData;

    temp_r31->attr |= 8;
    temp_r31->animBank = animBank;
    temp_r31->animTime = 0.0f;
    temp_r31->animNo = 0;
    temp_r31->animSpeed = 1.0f;
}

static Vec basePos[] = {
    { -0.5f,  0.5f, 0.0f },
    {  0.5f,  0.5f, 0.0f },
    {  0.5f, -0.5f, 0.0f },
    { -0.5f, -0.5f, 0.0f }
};

static float baseST[] = {
    0.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 1.0f
};

static void particleFunc(HU3DMODEL *arg0, Mtx arg1) {
    Vec *var_r30;
    float temp_f31;
    float temp_f29;
    float temp_f30;
    s16 temp_r20;
    s16 var_r19;
    s32 i;
    ANIMFRAME *var_r28;
    ANIMPAT *temp_r21;
    ANIMDATA *temp_r22;
    ANIMBANK *temp_r25;
    ANIMBMP *temp_r24;
    ANIMLAYER *temp_r27;
    HU3DPARTICLE *temp_r31;
    HU3DPARTICLEDATA *var_r29;
    HU3DPARTICLEHOOK var_r17;
    Mtx sp128;
    Mtx spF8;
    Mtx spC8;
    Vec sp98[4];
    Vec sp68[4];
    Vec sp38[4];
    ROMtx sp8;

    temp_r31 = arg0->hookData;
    temp_r22 = temp_r31->anim;
    if (HmfInverseMtxF3X3(arg1, sp128) == 0) {
        PSMTXIdentity(sp128);
    }
    PSMTXReorder(sp128, sp8);
    if ((Hu3DPauseF == 0 || (arg0->attr & HU3D_ATTR_NOPAUSE)) && temp_r31->hook && temp_r31->prevCounter != GlobalCounter) {
        var_r17 = temp_r31->hook;
        var_r17(arg0, temp_r31, arg1);
    }
    var_r29 = temp_r31->data;
    var_r30 = temp_r31->vtxBuf;
    PSMTXROMultVecArray(sp8, &basePos[0], sp38, 4);
    for (i = 0, var_r19 = 0; i < temp_r31->maxCnt; i++, var_r29++) {
        if (var_r29->scale && (var_r29->cameraBit & Hu3DCameraBit)) {
            if (!var_r29->zRot) {
                temp_f31 = var_r29->scale;
                var_r30->x = sp38[0].x * temp_f31 + var_r29->pos.x;
                var_r30->y = sp38[0].y * temp_f31 + var_r29->pos.y;
                var_r30->z = sp38[0].z * temp_f31 + var_r29->pos.z;
                var_r30++;
                var_r30->x = sp38[1].x * temp_f31 + var_r29->pos.x;
                var_r30->y = sp38[1].y * temp_f31 + var_r29->pos.y;
                var_r30->z = sp38[1].z * temp_f31 + var_r29->pos.z;
                var_r30++;
                var_r30->x = sp38[2].x * temp_f31 + var_r29->pos.x;
                var_r30->y = sp38[2].y * temp_f31 + var_r29->pos.y;
                var_r30->z = sp38[2].z * temp_f31 + var_r29->pos.z;
                var_r30++;
                var_r30->x = sp38[3].x * temp_f31 + var_r29->pos.x;
                var_r30->y = sp38[3].y * temp_f31 + var_r29->pos.y;
                var_r30->z = sp38[3].z * temp_f31 + var_r29->pos.z;
                var_r30++;
            } else {
                VECScale(&basePos[0], &sp98[0], var_r29->scale);
                VECScale(&basePos[1], &sp98[1], var_r29->scale);
                VECScale(&basePos[2], &sp98[2], var_r29->scale);
                VECScale(&basePos[3], &sp98[3], var_r29->scale);
                PSMTXRotRad(spC8, 'Z', var_r29->zRot);
                PSMTXConcat(sp128, spC8, spF8);
                PSMTXMultVecArray(spF8, sp98, sp68, 4);
                VECAdd(&sp68[0], &var_r29->pos, var_r30++);
                VECAdd(&sp68[1], &var_r29->pos, var_r30++);
                VECAdd(&sp68[2], &var_r29->pos, var_r30++);
                VECAdd(&sp68[3], &var_r29->pos, var_r30++);
            }
            var_r19 = 1;
        } else {
            var_r30->x = var_r30->y = var_r30->z = 0.0f;
            var_r30++;
            var_r30->x = var_r30->y = var_r30->z = 0.0f;
            var_r30++;
            var_r30->x = var_r30->y = var_r30->z = 0.0f;
            var_r30++;
            var_r30->x = var_r30->y = var_r30->z = 0.0f;
            var_r30++;
        }
    }
    if (var_r19 != 0) {
        DCFlushRangeNoSync(temp_r31->vtxBuf, temp_r31->maxCnt * sizeof(Vec) * 4);
        GXLoadPosMtxImm(arg1, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        if (shadowModelDrawF != 0) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetZMode(0, GX_LEQUAL, 0);
        } else {
            temp_r20 = (temp_r31->anim->bmp->dataFmt & 0xF);
            if (temp_r20 == 7 || temp_r20 == 8) {
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
            } else {
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            }
            if (arg0->attr & HU3D_ATTR_ZWRITE_OFF) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            } else {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            }
        }
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        if (temp_r31->attr & 8) {
            temp_r25 = &temp_r22->bank[temp_r31->animBank];
            var_r28 = &temp_r25->frame[temp_r31->animNo];
            temp_r21 = &temp_r22->pat[var_r28->pat];
            HuSprTexLoad(temp_r31->anim, temp_r21->layer->bmpNo, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
            if (Hu3DPauseF == 0 || (arg0->attr & HU3D_ATTR_NOPAUSE)) {
                for (i = 0; i < (s32) temp_r31->animSpeed * minimumVcount; i++) {
                    temp_r31->animTime += 1.0f;
                    if (temp_r31->animTime >= var_r28->time) {
                        temp_r31->animNo++;
                        temp_r31->animTime -= var_r28->time;
                        if (temp_r31->animNo >= temp_r25->timeNum || var_r28[1].time == -1) {
                            temp_r31->animNo = 0;
                        }
                    }
                    var_r28 = &temp_r25->frame[temp_r31->animNo];
                }
                temp_r31->animTime += temp_r31->animSpeed * minimumVcount - i;
                if (temp_r31->animTime >= var_r28->time) {
                    temp_r31->animNo++;
                    temp_r31->animTime -= var_r28->time;
                    if (temp_r31->animNo >= temp_r25->timeNum || var_r28[1].time == -1) {
                        temp_r31->animNo = 0;
                    }
                }
            }
            temp_r27 = temp_r21->layer;
            temp_r24 = &temp_r22->bmp[temp_r27->bmpNo];
            temp_f29 = (float) temp_r27->sizeX / temp_r24->sizeX;
            temp_f30 = (float) temp_r27->sizeY / temp_r24->sizeY;
            PSMTXScale(sp128, temp_f29, temp_f30, 1.0f);
            temp_f29 = (float) temp_r27->startX / temp_r24->sizeX;
            temp_f30 = (float) temp_r27->startY / temp_r24->sizeY;
            mtxTransCat(sp128, temp_f29, temp_f30, 0.0f);
            GXLoadTexMtxImm(sp128, GX_TEXMTX0, GX_MTX2x4);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        } else {
            HuSprTexLoad(temp_r31->anim, 0, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
        }
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(0);
        switch (temp_r31->blendMode) {
            case 0:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
                break;
            case 1:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
                break;
            case 2:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
                break;
        }
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_RGBA6, 0);
        GXSetArray(GX_VA_POS, temp_r31->vtxBuf, 0xC);
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetArray(GX_VA_CLR0, &temp_r31->data->color, 0x44);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
        GXSetArray(GX_VA_TEX0, baseST, 8);
        GXCallDisplayList(temp_r31->dlBuf, temp_r31->dlSize);
    }
    if (shadowModelDrawF == 0) {
        if (!(temp_r31->attr & 2) && Hu3DPauseF == 0) {
            temp_r31->count++;
        }
        if (temp_r31->prevCount != 0 && temp_r31->prevCount <= temp_r31->count) {
            if (temp_r31->attr & 1) {
                temp_r31->count = 0;
            }
            temp_r31->count = temp_r31->prevCount;
        }
        temp_r31->prevCounter = GlobalCounter;
    }
}

void Hu3DParManInit(void) {
    s16 i;

    for (i = 0; i < 64; i++) {
        parManProc[i] = NULL;
    }
}

s16 Hu3DParManCreate(ANIMDATA *anim, s16 maxCnt, HU3DPARMANPARAM *param) {
    HU3DMODEL *temp_r25;
    HU3DPARTICLE *temp_r29;
    ParManProcUserData *temp_r3_2;
    HU3DPARTICLEDATA *var_r28;
    s16 temp_r3;
    s16 var_r26;
    s16 var_r30;

    for (var_r30 = 0; var_r30 < 64; var_r30++) {
        if (!parManProc[var_r30]) {
            break;
        }
    }
    if (var_r30 == 64) {
        return -1;
    }
    temp_r3 = Hu3DParticleCreate(anim, maxCnt);
    Hu3DParticleHookSet(temp_r3, ParManHook);
    temp_r25 = &Hu3DData[temp_r3];
    temp_r29 = temp_r25->hookData;
    temp_r29->dataCnt = var_r30;
    var_r28 = temp_r29->data;
    for (var_r26 = 0; var_r26 < temp_r29->maxCnt; var_r26++, var_r28++) {
        var_r28->scale = 0.0f;
    }
    parManProc[var_r30] = HuPrcCreate(ParManFunc, 100, 0x1000, 0);
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(ParManProcUserData), MEMORY_DEFAULT_NUM);
    parManProc[var_r30]->user_data = temp_r3_2;
    temp_r3_2->unk00 = temp_r3;
    temp_r3_2->unk3C = param;
    temp_r3_2->unk02 = 0;
    temp_r3_2->unk0C.x = temp_r3_2->unk0C.y = temp_r3_2->unk0C.z = 0.0f;
    temp_r3_2->unk18.x = 0.0f;
    temp_r3_2->unk18.y = 1.0f;
    temp_r3_2->unk18.z = 1.0f;
    temp_r3_2->unk24.x = 0.0f;
    temp_r3_2->unk24.y = 0.0f;
    temp_r3_2->unk24.z = 0.0f;
    temp_r3_2->unk30 = 1.0f;
    temp_r3_2->unk34 = 0.0f;
    temp_r3_2->unk04 = 0;
    temp_r3_2->unk06 = var_r30;
    return var_r30;
}

s16 Hu3DParManLink(s16 linkParManId, HU3DPARMANPARAM *param) {
    ParManProcUserData *temp_r29;
    ParManProcUserData *temp_r3;
    s16 var_r30;

    for (var_r30 = 0; var_r30 < 64; var_r30++) {
        if (!parManProc[var_r30]) {
            break;
        }
    }
    if (var_r30 == 64) {
        return -1;
    }
    temp_r29 = parManProc[linkParManId]->user_data;
    parManProc[var_r30] = HuPrcCreate(ParManFunc, 100, 0x1000, 0);
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(ParManProcUserData), MEMORY_DEFAULT_NUM);
    parManProc[var_r30]->user_data = temp_r3;
    temp_r3->unk00 = temp_r29->unk00;
    temp_r3->unk3C = param;
    temp_r3->unk02 = 0;
    temp_r3->unk0C.x = temp_r3->unk0C.y = temp_r3->unk0C.z = 0.0f;
    temp_r3->unk18.x = 0.0f;
    temp_r3->unk18.y = 1.0f;
    temp_r3->unk18.z = 1.0f;
    temp_r3->unk24.x = 0.0f;
    temp_r3->unk24.y = 0.0f;
    temp_r3->unk24.z = 0.0f;
    temp_r3->unk30 = 1.0f;
    temp_r3->unk34 = 0.0f;
    temp_r3->unk04 = 0;
    temp_r3->unk06 = var_r30;
    return var_r30;
}

void Hu3DParManKill(s16 parManId) {
    ParManProcUserData *temp_r26;
    ParManProcUserData *temp_r30;
    HU3DPARTICLEDATA *var_r29;
    HU3DMODEL *temp_r25;
    HU3DPARTICLE *temp_r27;
    s16 i;

    if (parManProc[parManId]) {
        temp_r30 = parManProc[parManId]->user_data;
        temp_r25 = &Hu3DData[temp_r30->unk00];
        temp_r27 = temp_r25->hookData;
        var_r29 = temp_r27->data;
        for (i = 0; i < temp_r27->maxCnt; i++, var_r29++) {
            if (var_r29->parManId == parManId) {
                var_r29->scale = 0.0f;
            }
        }
        for (i = 0; i < 64; i++) {
            if (parManProc[i] && i != parManId) {
                temp_r26 = parManProc[i]->user_data;
                if (temp_r26->unk00 == temp_r30->unk00) {
                    break;
                }
            }
        }
        if (i == 64) {
            Hu3DModelKill(temp_r30->unk00);
        }
        HuPrcKill(parManProc[parManId]);
        parManProc[parManId] = NULL;
        HuMemDirectFree(temp_r30);
    }
}

void Hu3DParManAllKill(void) {
    s16 i;

    for (i = 0; i < 64; i++) {
        if (parManProc[i]) {
            Hu3DParManKill(i);
        }
    }
}

void *Hu3DParManPtrGet(s16 parManId) {
    return parManProc[parManId]->user_data;
}

void Hu3DParManPosSet(s16 parManId, float posX, float posY, float posZ) {
    ParManProcUserData *temp_r31 = parManProc[parManId]->user_data;

    temp_r31->unk0C.x = posX;
    temp_r31->unk0C.y = posY;
    temp_r31->unk0C.z = posZ;
}

void Hu3DParManVecSet(s16 parManId, float x, float y, float z) {
    ParManProcUserData *temp_r31 = parManProc[parManId]->user_data;

    temp_r31->unk18.x = x;
    temp_r31->unk18.y = y;
    temp_r31->unk18.z = z;
}

void Hu3DParManRotSet(s16 parManId, float rotX, float rotY, float rotZ) {
    ParManProcUserData *temp_r31 = parManProc[parManId]->user_data;
    Mtx sp18;

    mtxRot(sp18, rotX, rotY, rotZ);
    temp_r31->unk18.x = sp18[0][2];
    temp_r31->unk18.y = sp18[1][2];
    temp_r31->unk18.z = sp18[2][2];
}

void Hu3DParManAttrSet(s16 parManId, s32 attr) {
    ParManProcUserData *temp_r31 = parManProc[parManId]->user_data;

    temp_r31->unk02 |= attr;
}

void Hu3DParManAttrReset(s16 parManId, s32 attr) {
    ParManProcUserData *temp_r31 = parManProc[parManId]->user_data;

    temp_r31->unk02 &= ~attr;
}

s16 Hu3DParManModelIDGet(s16 parManId) {
    ParManProcUserData *temp_r31 = parManProc[parManId]->user_data;

    return temp_r31->unk00;
}

void Hu3DParManTimeLimitSet(s16 parManId, s32 timeLimit) {
    ParManProcUserData *temp_r31 = parManProc[parManId]->user_data;

    temp_r31->unk04 = timeLimit;
}

void Hu3DParManVacumeSet(s16 parManId, float x, float y, float z, float speed) {
    ParManProcUserData *temp_r31;

    Hu3DParManAttrSet(parManId, 0x200);
    temp_r31 = parManProc[parManId]->user_data;
    temp_r31->unk24.x = x;
    temp_r31->unk24.y = y;
    temp_r31->unk24.z = z;
    temp_r31->unk30 = speed;
}

void Hu3DParManColorSet(s16 parManId, s16 color) {
    ParManProcUserData *temp_r31;

    Hu3DParManAttrSet(parManId, 0x1000);
    temp_r31 = parManProc[parManId]->user_data;
    temp_r31->unk08 = color;
}

static void ParManFunc(void) {
    Process *temp_r25;
    ParManProcUserData *temp_r31;
    HU3DPARMANPARAM *temp_r30;
    HU3DMODEL *temp_r27;
    HU3DPARTICLE *temp_r28;
    HU3DPARTICLEDATA *var_r29;
    HU3DPARTICLEDATA *temp_r23;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f30;
    float temp_f31;
    float var_f26;
    float var_f28;
    float var_f27;
    float var_f29;
    s16 var_r24;
    s16 var_r26;

    temp_r25 = HuPrcCurrentGet();
    temp_r31 = temp_r25->user_data;
    temp_r30 = temp_r31->unk3C;
    temp_r27 = &Hu3DData[temp_r31->unk00];
    while (1) {
        if (Hu3DPauseF != 0 && !(temp_r27->attr & HU3D_ATTR_NOPAUSE)) {
            HuPrcVSleep();
            continue;
        }
        temp_r28 = temp_r27->hookData;
        var_r29 = temp_r28->data;
        if (temp_r31->unk02 & 0x400) {
            // Bug? Likely to be (u32) (temp_r30->unk04 * 0.1 * 1000.0)
            var_f27 = temp_r30->accelRange * 0.9 + (s32) frandmod((u32) temp_r30->accelRange * 0.1 * 1000.0) / 1000.0f;
        } else if (temp_r31->unk02 & 0x800) {
            var_f27 = temp_r30->accelRange * 0.7 + (s32) frandmod((u32) temp_r30->accelRange * 0.3 * 1000.0) / 1000.0f;
        } else {
            var_f27 = temp_r30->accelRange;
        }
        temp_r31->unk34 += var_f27;
        var_r26 = 0;
        temp_r23 = &((HU3DPARTICLEDATA*) temp_r28->data)[temp_r28->maxCnt];
        if (temp_r31->unk02 & 0x100) {
            var_f26 = (s32) frandmod((u32) (360.0f / temp_r30->accelRange) * 100) / 100;
        }
        while (temp_r31->unk34 >= 1.0f) {
            if (temp_r31->unk02 & 1) {
                temp_r31->unk34 -= 1.0f;
            } else {
                while (var_r29 < temp_r23) {
                    if (!var_r29->scale) {
                        temp_f31 = temp_r30->scaleBase;
                        if (temp_r31->unk02 & 0x10) {
                            temp_f31 = temp_f31 * 0.9 + (s32) frandmod((u32) (temp_f31 * 0.1 * 1000.0)) / 1000.0f;
                        } else if (temp_r31->unk02 & 0x20) {
                            temp_f31 = temp_f31 * 0.7 + (s32) frandmod((u32) (temp_f31 * 0.3 * 1000.0)) / 1000.0f;
                        }
                        var_r29->scaleBase = temp_f31;
                        var_r29->scale = temp_f31;
                        var_r29->pos = temp_r31->unk0C;
                        sp20.x = (s32) frandmod((u32) (temp_r30->scaleRange * 2.0f)) - temp_r30->scaleRange;
                        sp20.y = (s32) frandmod((u32) (temp_r30->scaleRange * 2.0f)) - temp_r30->scaleRange;
                        sp20.z = (s32) frandmod((u32) (temp_r30->scaleRange * 2.0f)) - temp_r30->scaleRange;
                        VECNormalize(&sp20, &sp20);
                        VECScale(&sp20, &sp20, temp_r30->scaleRange);
                        VECAdd(&sp20, &var_r29->pos, &var_r29->pos);
                        VECNormalize(&temp_r31->unk18, &sp2C);
                        if (temp_r31->unk02 & 0x100) {
                            var_f28 = var_f26 + (360.0f / temp_r30->accelRange) * var_r26;
                            var_f29 = temp_r30->angleRange;
                        } else {
                            var_f28 = (s32) frandmod(360);
                            if (temp_r30->angleRange) {
                                var_f29 = (s32) frandmod((u32) temp_r30->angleRange);
                            } else {
                                var_f29 = 0.0f;
                            }
                        }
                        if (sp2C.x * sp2C.x < 0.000001 && sp2C.z * sp2C.z < 0.000001) {
                            sp8.x = 1.0f;
                            sp8.y = sp8.z = 0.0f;
                        } else {
                            if (sp2C.y * sp2C.y > 0.000001) {
                                sp14.x = sp2C.x;
                                sp14.y = 0.0f;
                                sp14.z = sp2C.z;
                            } else {
                                sp14.x = sp2C.x;
                                sp14.y = 1.0f;
                                sp14.z = sp2C.z;
                            }
                            VECCrossProduct(&sp14, &sp2C, &sp8);
                        }
                        VECNormalize(&sp8, &sp8);
                        temp_f31 = sind(var_f28);
                        temp_f30 = cosd(var_f28);
                        sp14.x = sp8.x * (sp2C.x * sp2C.x + temp_f30 * (1.0f - sp2C.x * sp2C.x))
                            + sp8.y * (sp2C.x * sp2C.y * (1.0f - temp_f30) - sp2C.z * temp_f31)
                            + sp8.z * (sp2C.x * sp2C.z * (1.0f - temp_f30) + sp2C.y * temp_f31);
                        sp14.y = sp8.x * (sp2C.x * sp2C.y * (1.0f - temp_f30) + sp2C.z * temp_f31)
                            + sp8.y * (sp2C.y * sp2C.y + temp_f30 * (1.0f - sp2C.y * sp2C.y))
                            + sp8.z * (sp2C.y * sp2C.z * (1.0f - temp_f30) - sp2C.x * temp_f31);
                        sp14.z = sp8.x * (sp2C.x * sp2C.z * (1.0f - temp_f30) - sp2C.y * temp_f31)
                            + sp8.y * (sp2C.y * sp2C.z * (1.0f - temp_f30) + sp2C.x * temp_f31)
                            + sp8.z * (sp2C.z * sp2C.z + temp_f30 * (1.0f - sp2C.z * sp2C.z));
                        VECCrossProduct(&sp14, &sp2C, &sp8);
                        temp_f31 = sind(var_f29);
                        temp_f30 = cosd(var_f29);
                        sp14.x = sp2C.x * (sp8.x * sp8.x + temp_f30 * (1.0f - sp8.x * sp8.x))
                            + sp2C.y * (sp8.x * sp8.y * (1.0f - temp_f30) - sp8.z * temp_f31)
                            + sp2C.z * (sp8.x * sp8.z * (1.0f - temp_f30) + sp8.y * temp_f31);
                        sp14.y = sp2C.x * (sp8.x * sp8.y * (1.0f - temp_f30) + sp8.z * temp_f31)
                            + sp2C.y * (sp8.y * sp8.y + temp_f30 * (1.0f - sp8.y * sp8.y))
                            + sp2C.z * (sp8.y * sp8.z * (1.0f - temp_f30) - sp8.x * temp_f31);
                        sp14.z = sp2C.x * (sp8.x * sp8.z * (1.0f - temp_f30) - sp8.y * temp_f31)
                            + sp2C.y * (sp8.y * sp8.z * (1.0f - temp_f30) + sp8.x * temp_f31)
                            + sp2C.z * (sp8.z * sp8.z + temp_f30 * (1.0f - sp8.z * sp8.z));
                        VECNormalize(&sp14, &sp14);
                        temp_f31 = temp_r30->speedBase;
                        if (temp_r31->unk02 & 2) {
                            temp_f31 = temp_f31 * 0.9 + (s32) frandmod((u32) (temp_f31 * 0.1 * 1000.0)) / 1000.0f;
                        } else if (temp_r31->unk02 & 4) {
                            temp_f31 = temp_f31 * 0.7 + (s32) frandmod((u32) (temp_f31 * 0.3 * 1000.0)) / 1000.0f;
                        } else if (temp_r31->unk02 & 8) {
                            temp_f31 = (s32) frandmod((u32) (temp_f31 * 1000.0f)) / 1000.0f;
                        }
                        VECScale(&sp14, &var_r29->vel, temp_f31);
                        var_r29->accel = temp_r30->gravity;
                        var_r29->speedDecay = temp_r30->speedDecay;
                        if (temp_r31->unk02 & 0x1000) {
                            var_r29->colorIdx = var_r24 = temp_r31->unk08;
                        } else {
                            var_r29->colorIdx = var_r24 = frandmod(temp_r30->colorNum);
                        }
                        var_r29->color = temp_r30->colorStart[var_r24];
                        var_r29->time = 0;
                        var_r29->parManId = temp_r31->unk06;
                        break;
                    } else {
                        var_r29++;
                    }
                }
                temp_r31->unk34 -= 1.0f;
                var_r26++;
            }
        }
        if (temp_r31->unk04 != 0) {
            temp_r31->unk04--;
            if (temp_r31->unk04 == 0) {
                temp_r31->unk02 |= 1;
            }
        }
        HuPrcVSleep();
    }
}

static float jitterTbl[] = {
    1.0f, 0.9f, 0.7f, 0.5f,
    0.5f, 0.7f, 0.9f, 1.0f
};

static void ParManHook(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx matrix) {
    HU3DPARMANPARAM *temp_r26;
    ParManProcUserData *temp_r28;
    HU3DPARTICLEDATA *var_r29;
    GXColor *temp_r24;
    GXColor *temp_r27;
    Vec sp1C;
    Vec sp10;
    float temp_f29;
    float var_f30;
    s16 temp_r31;
    s16 sp8;
    s16 i;

    if (Hu3DPauseF == 0 || (model->attr & HU3D_ATTR_NOPAUSE)) {
        var_r29 = particle->data;
        for (i = 0; i < particle->maxCnt; i++, var_r29++) {
            if (var_r29->scale) {
                temp_r28 = parManProc[var_r29->parManId]->user_data;
                temp_r26 = temp_r28->unk3C;
                if (temp_r28->unk02 & 0x40) {
                    var_r29->scale = var_r29->scaleBase * jitterTbl[(temp_r28->unk38 + i) & 7];
                } else {
                    var_r29->scale = var_r29->scaleBase;
                }
                if (!(temp_r28->unk02 & 0x80)) {
                    sp8 = var_r29->time;
                    var_r29->pos.x += var_r29->vel.x + var_r29->accel.x;
                    var_r29->pos.y += var_r29->vel.y + var_r29->accel.y;
                    var_r29->pos.z += var_r29->vel.z + var_r29->accel.z;
                    VECScale(&var_r29->vel, &var_r29->vel, var_r29->speedDecay);
                    VECAdd(&temp_r26->gravity, &var_r29->accel, &var_r29->accel);
                    if (temp_r28->unk02 & 0x200) {
                        VECSubtract(&temp_r28->unk24, &var_r29->pos, &sp1C);
                        VECNormalize(&sp1C, &sp1C);
                        VECScale(&sp1C, &sp1C, temp_r28->unk30);
                        VECAdd(&sp1C, &var_r29->accel, &var_r29->accel);
                        VECAdd(&var_r29->vel, &var_r29->accel, &sp1C);
                        VECSubtract(&temp_r28->unk24, &var_r29->pos, &sp10);
                        temp_f29 = VECSquareMag(&sp1C);
                        if (VECSquareMag(&sp10) <= temp_f29) {
                            var_r29->scale = 0.0f;
                            continue;
                        }
                    }
                    var_r29->scaleBase *= temp_r26->scaleDecay;
                    var_f30 = (float) var_r29->time / temp_r26->maxTime;
                    if (var_f30 > 1.0f) {
                        var_f30 = 1.0f;
                    }
                    OSf32tos16(&var_r29->colorIdx, &temp_r31);
                    temp_r27 = &temp_r26->colorStart[temp_r31];
                    temp_r24 = &temp_r26->colorEnd[temp_r31];
                    var_r29->color.r = temp_r27->r + var_f30 * (temp_r24->r - temp_r27->r);
                    var_r29->color.g = temp_r27->g + var_f30 * (temp_r24->g - temp_r27->g);
                    var_r29->color.b = temp_r27->b + var_f30 * (temp_r24->b - temp_r27->b);
                    var_r29->color.a = temp_r27->a + var_f30 * (temp_r24->a - temp_r27->a);
                    if (var_r29->scale < 0.01 || var_r29->time >= temp_r26->maxTime) {
                        var_r29->scale = 0.0f;
                    }
                    var_r29->time++;
                }
            }
        }
        temp_r28 = parManProc[particle->dataCnt]->user_data;
        temp_r28->unk38++;
        DCStoreRangeNoSync(particle->data, particle->maxCnt * sizeof(HU3DPARTICLEDATA));
    }
}
