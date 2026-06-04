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

static void particleFunc(HU3DMODEL *arg0, Mtx arg1);
static void ParManFunc(void);
static void ParManHook(HU3DMODEL *arg0, HU3DPARTICLE *arg1, Mtx mtx);

extern u32 GlobalCounter;

HU3DTEXANIM Hu3DTexAnimData[HU3D_TEXANIM_MAX];
HU3DTEXSCROLL Hu3DTexScrData[HU3D_TEXSCROLL_MAX];
static HUPROCESS *parManProc[64];

void Hu3DAnimInit(void) {
    HU3DTEXANIM *texAnimP;
    HU3DTEXSCROLL *texScrP;
    s16 i;

    texAnimP = Hu3DTexAnimData;
    for (i = 0; i < HU3D_TEXANIM_MAX; i++, texAnimP++) {
        texAnimP->modelId = HU3D_MODELID_NONE;
    }
    texScrP = Hu3DTexScrData;
    for (i = 0; i < HU3D_TEXSCROLL_MAX; i++, texScrP++) {
        texScrP->modelId = HU3D_MODELID_NONE;
    }
}

HU3DANIMID Hu3DAnimCreate(void *dataP, HU3DMODELID modelId, char *bmpName) {
    HU3DTEXANIM *texAnimP;
    HSFATTRIBUTE *attrP;
    HSFDATA *hsf;
    s16 i;
    s16 bmpNum;
    HU3DANIMID animId;

    texAnimP = &Hu3DTexAnimData[0];
    for (animId = 0; animId < HU3D_TEXANIM_MAX; animId++, texAnimP++) {
        if (texAnimP->modelId == HU3D_MODELID_NONE) {
            break;
        }
    }
    if (animId == HU3D_TEXANIM_MAX) {
        OSReport("Error: TexAnim Over\n");
        return HU3D_ANIMID_NONE;
    }
    hsf = Hu3DData[modelId].hsf;
    attrP = hsf->attribute;
    for (i = bmpNum = 0; i < hsf->attributeNum; i++, attrP++) {
        if (strcmp(bmpName, attrP->bitmap->name) == 0) {
            HU3DATTRANIM *attrAnimP;
            if (!attrP->animWorkP) {
                attrAnimP = HuMemDirectMallocNum(HEAP_DATA, sizeof(*attrAnimP), (u32) Hu3DData[modelId].mallocNo);
                attrP->animWorkP = attrAnimP;
                attrAnimP->attr = 0;
            } else {
                attrAnimP = attrP->animWorkP;
            }
            attrAnimP->attr |= 1;
            attrAnimP->animId = animId;
            attrAnimP->scale.x = attrAnimP->scale.y = 1.0f;
            attrAnimP->trans.x = attrAnimP->trans.y = 0.0f;
            bmpNum++;
        }
    }
    if (bmpNum == 0) {
        OSReport("Error: Not Found TexAnim Name\n");
        return HU3D_ANIMID_NONE;
    }
    if (!dataP) {
        texAnimP->anim = NULL;
    } else {
        texAnimP->anim = HuSprAnimRead(dataP);
    }
    texAnimP->modelId = modelId;
    texAnimP->time = 0.0f;
    texAnimP->bank = 0;
    texAnimP->anmNo = 0;
    texAnimP->attr = 0;
    texAnimP->speed = 1.0f;
    return animId;
}

s16 Hu3DAnimLink(HU3DANIMID linkAnimId, HU3DMODELID modelId, char *bmpName) {
    HU3DTEXANIM *linkTexAnimP = &Hu3DTexAnimData[linkAnimId];
    HU3DTEXANIM *texAnimP;
    HSFATTRIBUTE *attrP;
    HSFDATA *hsf;
    HU3DANIMID animId;
    s16 i;
    s16 bmpNum;

    texAnimP = Hu3DTexAnimData;
    for (animId = 0; animId < HU3D_TEXANIM_MAX; animId++, texAnimP++) {
        if (texAnimP->modelId == HU3D_MODELID_NONE) {
            break;
        }
    }
    if (animId == HU3D_TEXANIM_MAX) {
        OSReport("Error: TexAnim Over\n");
        return HU3D_ANIMID_NONE;
    }
    hsf = Hu3DData[modelId].hsf;
    attrP = hsf->attribute;
    for (i = bmpNum = 0; i < hsf->attributeNum; i++, attrP++) {
        if (strcmp(bmpName, attrP->bitmap->name) == 0) {
            HU3DATTRANIM *attrAnimP;
            if (!attrP->animWorkP) {
                attrAnimP = HuMemDirectMallocNum(HEAP_DATA, sizeof(*attrAnimP), (u32) Hu3DData[modelId].mallocNo);
                attrP->animWorkP = attrAnimP;
            } else {
                attrAnimP = attrP->animWorkP;
            }
            attrAnimP->animId = animId;
            attrAnimP->scale.x = attrAnimP->scale.y = 1.0f;
            attrAnimP->trans.x = attrAnimP->trans.y = 0.0f;
            bmpNum++;
        }
    }
    if (bmpNum == 0) {
        OSReport("Error: Not Found TexAnim Name\n");
        return HU3D_ANIMID_NONE;
    }
    texAnimP->anim = linkTexAnimP->anim;
    texAnimP->anim->useNum++;
    texAnimP->modelId = modelId;
    texAnimP->time = 0.0f;
    texAnimP->bank = 0;
    texAnimP->anmNo = 0;
    texAnimP->attr = 0;
    texAnimP->speed = 1.0f;
    return animId;
}

void Hu3DAnimKill(HU3DANIMID animId) {
    HU3DTEXANIM *texAnimP = &Hu3DTexAnimData[animId];
    HSFDATA *hsf = Hu3DData[texAnimP->modelId].hsf;
    HSFATTRIBUTE *attrP;
    HU3DATTRANIM *attrAnimP;
    s16 i;

    if (hsf) {
        attrP = hsf->attribute;
        for (i = 0; i < hsf->attributeNum; i++, attrP++) {
            if (attrP->animWorkP) {
                attrAnimP = attrP->animWorkP;
                if (attrAnimP->animId == animId) {
                    attrAnimP->attr &= ~HU3D_ATTRANIM_ATTR_ANIM2D;
                    if (attrAnimP->attr == HU3D_ATTRANIM_ATTR_NONE) {
                        attrP->animWorkP = NULL;
                        HuMemDirectFree(attrAnimP);
                    }
                }
            }
        }
    }
    texAnimP->modelId = HU3D_MODELID_NONE;
    if (--texAnimP->anim->useNum <= 0) {
        HuMemDirectFree(texAnimP->anim);
    }
}

void Hu3DAnimModelKill(HU3DMODELID modelId) {
    HU3DTEXANIM *texAnimP = &Hu3DTexAnimData[0];
    HU3DANIMID animId;

    for (animId = 0; animId < HU3D_TEXANIM_MAX; animId++, texAnimP++) {
        if (texAnimP->modelId == modelId) {
            Hu3DAnimKill(animId);
        }
    }
}

void Hu3DAnimAllKill(void) {
    HU3DTEXANIM *texAnimP = &Hu3DTexAnimData[0];
    HU3DANIMID animId;

    for (animId = 0; animId < HU3D_TEXANIM_MAX; animId++, texAnimP++) {
        if (texAnimP->modelId != HU3D_MODELID_NONE) {
            Hu3DAnimKill(animId);
        }
    }
    Hu3DTexScrollAllKill();
}

void Hu3DAnimAttrSet(HU3DANIMID animId, u16 attr) {
    HU3DTEXANIM *texAnimP = &Hu3DTexAnimData[animId];

    texAnimP->attr |= attr;
}

void Hu3DAnimAttrReset(HU3DANIMID animId, s32 attr) {
    HU3DTEXANIM *texAnimP = &Hu3DTexAnimData[animId];

    texAnimP->attr &= ~attr;
}

void Hu3DAnimSpeedSet(HU3DANIMID animId, float speed) {
    HU3DTEXANIM *texAnimP = &Hu3DTexAnimData[animId];

    texAnimP->speed = speed;
}

void Hu3DAnimBankSet(HU3DANIMID animId, s32 bank) {
    HU3DTEXANIM *texAnimP = &Hu3DTexAnimData[animId];

    texAnimP->bank = bank;
    texAnimP->anmNo = texAnimP->time = 0.0f;
}

void Hu3DAnmNoSet(HU3DANIMID animId, u16 anmNo) {
    HU3DTEXANIM *texAnimP = &Hu3DTexAnimData[animId];

    texAnimP->anmNo = anmNo;
    texAnimP->time = 0.0f;
}

s32 Hu3DAnimSet(HU3DMODEL *modelP, HSFATTRIBUTE *attrP, s16 texSlotNo) {
    HU3DATTRANIM *attrAnimP;
    HU3DTEXANIM *texAnimP;
    ANIMDATA *anim;
    ANIMBMP *bmp;
    ANIMLAYER *layer;
    ANIMPAT *pat;
    s16 patNo;
    s16 wrapS;
    s16 wrapT;

    attrAnimP = attrP->animWorkP;
    texAnimP = &Hu3DTexAnimData[attrAnimP->animId];
    anim = texAnimP->anim;
    patNo = anim->bank[texAnimP->bank].frame[texAnimP->anmNo].pat;
    if (patNo == -1) {
        return FALSE;
    }
    wrapS = (attrP->wrapS == TRUE) ? TRUE : FALSE;
    wrapT = (attrP->wrapT == TRUE) ? TRUE : FALSE;
    pat = &anim->pat[patNo];
    layer = pat->layer;
    bmp = &anim->bmp[layer->bmpNo];
    HuSprTexLoad(texAnimP->anim, layer->bmpNo, texSlotNo, wrapS, wrapT,
        (modelP->attr & HU3D_ATTR_TEX_NEAR) ? GX_NEAR : GX_LINEAR);
    attrAnimP->scale.x = (float) layer->sizeX / bmp->sizeX;
    attrAnimP->scale.y = (float) layer->sizeY / bmp->sizeY;
    attrAnimP->trans.x = (float) layer->startX / bmp->sizeX;
    attrAnimP->trans.y = (float) layer->startY / bmp->sizeY;
    return TRUE;
}

void Hu3DAnimExec(void) {
    HU3DTEXANIM *texAnimP;
    HU3DTEXSCROLL *texScrP;
    ANIMDATA *anim;
    ANIMBANK *bank;
    ANIMFRAME *frame;
    s16 j;
    s16 i;

    texAnimP = Hu3DTexAnimData;
    for (i = 0; i < HU3D_TEXANIM_MAX; i++, texAnimP++) {
        if (texAnimP->modelId != HU3D_MODELID_NONE && (Hu3DPauseF == FALSE || (texAnimP->attr & HU3D_ANIM_ATTR_PAUSE))) {
            anim = texAnimP->anim;
            bank = &anim->bank[texAnimP->bank];
            frame = &bank->frame[texAnimP->anmNo];
            if (!(texAnimP->attr & HU3D_ANIM_ATTR_ANIMON) || (frame->time == -1 && (texAnimP->attr & HU3D_ANIM_ATTR_LOOP))) {
                for (j = 0; j < (s32) texAnimP->speed * minimumVcount; j++) {
                    texAnimP->time += 1.0f;
                    if (texAnimP->time >= frame->time) {
                        texAnimP->anmNo++;
                        texAnimP->time -= frame->time;
                        if (texAnimP->anmNo >= bank->timeNum || frame[1].time == -1) {
                            texAnimP->anmNo = 0;
                        }
                        frame = &bank->frame[texAnimP->anmNo];
                    }
                }
                texAnimP->time += texAnimP->speed * minimumVcount - j;
                if (texAnimP->time >= frame->time) {
                    texAnimP->anmNo++;
                    texAnimP->time -= frame->time;
                    if (texAnimP->anmNo >= bank->timeNum || frame[1].time == -1) {
                        texAnimP->anmNo = 0;
                    }
                }
            }
        }
    }
    texScrP = Hu3DTexScrData;
    for (i = 0; i < HU3D_TEXSCROLL_MAX; i++, texScrP++) {
        if (texScrP->modelId != HU3D_MODELID_NONE) {
            if (Hu3DPauseF && !(texScrP->attr & HU3D_TEXSCR_ATTR_PAUSEDISABLE)) {
                MTXRotRad(texScrP->texMtx, 'Z', MTXDegToRad(texScrP->rot));
                mtxTransCat(texScrP->texMtx, texScrP->pos.x, texScrP->pos.y, texScrP->pos.z);
            } else {
                if (texScrP->attr & HU3D_TEXSCR_ATTR_POSMOVE) {
                    VECAdd(&texScrP->pos, &texScrP->posMove, &texScrP->pos);
                    if (texScrP->pos.x > 1.0f) {
                        texScrP->pos.x -= 1.0f;
                    }
                    if (texScrP->pos.y > 1.0f) {
                        texScrP->pos.y -= 1.0f;
                    }
                    if (texScrP->pos.z > 1.0f) {
                        texScrP->pos.z -= 1.0f;
                    }
                    if (texScrP->pos.x < -1.0f) {
                        texScrP->pos.x += 1.0f;
                    }
                    if (texScrP->pos.y < -1.0f) {
                        texScrP->pos.y += 1.0f;
                    }
                    if (texScrP->pos.z < -1.0f) {
                        texScrP->pos.z += 1.0f;
                    }
                }
                if (texScrP->attr & 2) {
                    texScrP->rot += texScrP->rotMove;
                    if (texScrP->rot > 360.0f) {
                        texScrP->rot -= 360.0f;
                    }
                    if (texScrP->rot < -360.0f) {
                        texScrP->rot += 360.0f;
                    }
                }
                MTXRotRad(texScrP->texMtx, 'Z', MTXDegToRad(texScrP->rot));
                mtxTransCat(texScrP->texMtx, texScrP->pos.x, texScrP->pos.y, texScrP->pos.z);
            }
        }
    }
}

s16 Hu3DTexScrollCreate(HU3DMODELID modelId, char *bmpName) {
    HU3DTEXSCROLL *texScrP;
    HSFDATA *hsf;
    HSFATTRIBUTE *attrP;
    s16 i;
    s16 bmpNum;
    s16 texScrId;

    texScrP = Hu3DTexScrData;
    for (texScrId = 0; texScrId < HU3D_TEXSCROLL_MAX; texScrId++, texScrP++) {
        if (texScrP->modelId == HU3D_MODELID_NONE) {
            break;
        }
    }
    if (texScrId == HU3D_TEXSCROLL_MAX) {
        OSReport("Error: TexScroll Over\n");
        return HU3D_TEXSCRID_NONE;
    }
    hsf = Hu3DData[modelId].hsf;
    attrP = hsf->attribute;
    for (i = bmpNum = 0; i < hsf->attributeNum; i++, attrP++) {
        if (strcmp(bmpName, attrP->bitmap->name) == 0) {
            HU3DATTRANIM *attrAnimP;
            if (!attrP->animWorkP) {
                attrAnimP = HuMemDirectMallocNum(HEAP_DATA, sizeof(*attrAnimP), (u32) Hu3DData[modelId].mallocNo);
                attrP->animWorkP = attrAnimP;
                attrAnimP->attr = 0;
            } else {
                attrAnimP = attrP->animWorkP;
            }
            attrAnimP->attr |= 2;
            attrAnimP->texScrId = texScrId;
            attrAnimP->scale.x = attrAnimP->scale.y = 1.0f;
            attrAnimP->trans.x = attrAnimP->trans.y = 0.0f;
            bmpNum++;
        }
    }
    if (bmpNum == 0) {
        OSReport("Error: Not Found TexAnim Name\n");
        return HU3D_TEXSCRID_NONE;
    }
    texScrP->modelId = modelId;
    texScrP->attr = 0;
    texScrP->pos.x = texScrP->pos.y = texScrP->pos.z = 0.0f;
    texScrP->rot = 0.0f;
    MTXIdentity(texScrP->texMtx);
    return texScrId;
}

void Hu3DTexScrollKill(HU3DTEXSCRID texSrcId) {
    HU3DTEXSCROLL *texScrP = &Hu3DTexScrData[texSrcId];
    HSFDATA *hsf = Hu3DData[texScrP->modelId].hsf;
    HSFATTRIBUTE *attrP;
    s16 i;

    if (hsf) {
        attrP = hsf->attribute;
        for (i = 0; i < hsf->attributeNum; i++, attrP++) {
            if (attrP->animWorkP) {
                HU3DATTRANIM *attrAnimP = attrP->animWorkP;
                if (attrAnimP->texScrId == texSrcId) {
                    attrAnimP->attr &= ~HU3D_ATTRANIM_ATTR_TEXMTX;
                    if (attrAnimP->attr == HU3D_ATTRANIM_ATTR_NONE) {
                        attrP->animWorkP = NULL;
                        HuMemDirectFree(attrAnimP);
                    }
                }
            }
        }
    }
    texScrP->modelId = HU3D_MODELID_NONE;
}

void Hu3DTexScrollAllKill(void) {
    HU3DTEXSCROLL *texScrP;
    HU3DTEXSCRID texScrId;

    texScrP = Hu3DTexScrData;
    for (texScrId = 0; texScrId < HU3D_TEXSCROLL_MAX; texScrId++, texScrP++) {
        if (texScrP->modelId != HU3D_MODELID_NONE) {
            Hu3DTexScrollKill(texScrId);
        }
    }
}

void Hu3DTexScrollPosSet(HU3DTEXSCRID texScrId, float posX, float posY, float posZ) {
    HU3DTEXSCROLL *temp_r31 = &Hu3DTexScrData[texScrId];

    temp_r31->attr &= ~1;
    temp_r31->pos.x = posX;
    temp_r31->pos.y = posY;
    temp_r31->pos.z = posZ;
}

void Hu3DTexScrollPosMoveSet(HU3DTEXSCRID texScrId, float posX, float posY, float posZ) {
    HU3DTEXSCROLL *texScrP = &Hu3DTexScrData[texScrId];

    texScrP->attr |= HU3D_TEXSCR_ATTR_POSMOVE;
    texScrP->posMove.x = posX * minimumVcount;
    texScrP->posMove.y = posY * minimumVcount;
    texScrP->posMove.z = posZ * minimumVcount;
}

void Hu3DTexScrollRotSet(HU3DTEXSCRID texScrId, float rot) {
    HU3DTEXSCROLL *texScrP = &Hu3DTexScrData[texScrId];

    texScrP->attr &= ~HU3D_TEXSCR_ATTR_ROTMOVE;
    texScrP->rot = rot;
}

void Hu3DTexScrollRotMoveSet(HU3DTEXSCRID texScrId, float rot) {
    HU3DTEXSCROLL *texScrP = &Hu3DTexScrData[texScrId];

    texScrP->attr |= HU3D_TEXSCR_ATTR_ROTMOVE;
    texScrP->rotMove = rot * minimumVcount;
}

void Hu3DTexScrollPauseDisableSet(HU3DTEXSCRID texScrId, BOOL pauseDisableF) {
    HU3DTEXSCROLL *texScrP = &Hu3DTexScrData[texScrId];

    if (pauseDisableF) {
        texScrP->attr |= HU3D_TEXSCR_ATTR_PAUSEDISABLE;
    } else {
        texScrP->attr &= ~HU3D_TEXSCR_ATTR_PAUSEDISABLE;
    }
}

s16 Hu3DParticleCreate(ANIMDATA *anim, s16 maxCnt) {
    HU3DMODEL *modelP;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;
    Vec *vtxBuf;
    s16 modelId;
    s16 i;
    void *dlBuf;

    modelId = Hu3DHookFuncCreate(particleFunc);
    modelP = &Hu3DData[modelId];
    Hu3DModelAttrSet(modelId, HU3D_ATTR_PARTICLE_KILL);
    particleP = HuMemDirectMallocNum(HEAP_DATA, sizeof(HU3DPARTICLE), modelP->mallocNo);
    modelP->hookData = particleP;
    particleP->anim = anim;
    anim->useNum++;
    particleP->maxCnt = maxCnt;
    particleP->blendMode = HU3D_PARTICLE_BLEND_NORMAL;
    particleP->hook = NULL;
    particleP->count = 0;
    particleP->attr = HU3D_PARTICLE_ATTR_NONE;
    particleP->prevCount = 0;
    particleP->dataCnt = particleP->emitCnt = 0;
    particleDataP = HuMemDirectMallocNum(HEAP_DATA, maxCnt * sizeof(HU3DPARTICLEDATA), modelP->mallocNo);
    particleP->data = particleDataP;
    particleP->prevCounter = -1;
    for (i = 0; i < maxCnt; i++, particleDataP++) {
        particleDataP->scale = 0.0f;
        particleDataP->unk04 = 0;
        particleDataP->cameraBit = HU3D_CAM_ALL;
        particleDataP->zRot = 0.0f;
        particleDataP->pos.x = ((s32) (frand() & 0x7F) - 64) * 20;
        particleDataP->pos.y = ((s32) (frand() & 0x7F) - 64) * 30;
        particleDataP->pos.z = ((s32) (frand() & 0x7F) - 64) * 20;
        particleDataP->color.r = particleDataP->color.g = particleDataP->color.b = particleDataP->color.a = 0xFF;
    }
    vtxBuf = HuMemDirectMallocNum(HEAP_DATA, maxCnt * sizeof(Vec) * 4, modelP->mallocNo);
    particleP->vtxBuf = vtxBuf;
    for (i = 0; i < maxCnt * 4; i++, vtxBuf++) {
        vtxBuf->x = vtxBuf->y = vtxBuf->z = 0.0f;
    }
    dlBuf = HuMemDirectMallocNum(HEAP_DATA, maxCnt * 0x60 + 0x80, modelP->mallocNo);
    particleP->dlBuf = dlBuf;
    DCInvalidateRange(dlBuf, maxCnt * 0x60 + 0x80);
    GXBeginDisplayList(dlBuf, 0x20000);
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
    particleP->dlSize = GXEndDisplayList();
    return modelId;
}

void Hu3DParticleScaleSet(HU3DMODELID modelId, float scale) {
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HU3DPARTICLE *particleP = modelP->hookData;
    HU3DPARTICLEDATA *particleDataP;
    s16 i;

    particleDataP = particleP->data;
    for (i = 0; i < particleP->maxCnt; i++, particleDataP++) {
        particleDataP->scale = scale;
    }
}

void Hu3DParticleZRotSet(HU3DMODELID modelId, float zRot) {
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HU3DPARTICLE *particleP = modelP->hookData;
    HU3DPARTICLEDATA *particleDataP;
    s16 i;

    particleDataP = particleP->data;
    for (i = 0; i < particleP->maxCnt; i++, particleDataP++) {
        particleDataP->zRot = zRot;
    }
}

void Hu3DParticleColSet(HU3DMODELID modelId, u8 r, u8 g, u8 b) {
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HU3DPARTICLE *particleP = modelP->hookData;
    HU3DPARTICLEDATA *particleDataP;
    s16 i;

    particleDataP = particleP->data;
    for (i = 0; i < particleP->maxCnt; i++, particleDataP++) {
        particleDataP->color.r = r;
        particleDataP->color.g = g;
        particleDataP->color.b = b;
    }
}

void Hu3DParticleTPLvlSet(HU3DMODELID modelId, float tpLvl) {
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HU3DPARTICLE *particleP = modelP->hookData;
    HU3DPARTICLEDATA *particleDataP;
    u8 alpha;
    s16 i;

    particleDataP = particleP->data;
    alpha = tpLvl * 255.0f;
    for (i = 0; i < particleP->maxCnt; i++, particleDataP++) {
        particleDataP->color.a = alpha;
    }
}

void Hu3DParticleBlendModeSet(HU3DMODELID modelId, u8 blendMode) {
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HU3DPARTICLE *particleP = modelP->hookData;

    particleP->blendMode = blendMode;
}

void Hu3DParticleHookSet(HU3DMODELID modelId, HU3DPARTICLEHOOK hook) {
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HU3DPARTICLE *particleP = modelP->hookData;

    particleP->hook = hook;
}

void Hu3DParticleAttrSet(HU3DMODELID modelId, u8 attr) {
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HU3DPARTICLE *particleP = modelP->hookData;

    particleP->attr |= attr;
}

void Hu3DParticleAttrReset(HU3DMODELID modelId, u8 attr) {
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HU3DPARTICLE *particleP = modelP->hookData;

    particleP->attr &= ~attr;
}

void Hu3DParticleCntSet(HU3DMODELID modelId, s16 count) {
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HU3DPARTICLE *particleP = modelP->hookData;

    particleP->count = count;
}

void Hu3DParticleAnimModeSet(HU3DMODELID modelId, s16 animBank) {
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HU3DPARTICLE *particleP = modelP->hookData;

    particleP->attr |= HU3D_PARTICLE_ATTR_ANIMON;
    particleP->animBank = animBank;
    particleP->animTime = 0.0f;
    particleP->animNo = 0;
    particleP->animSpeed = 1.0f;
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
    HuVecF *vtxBuf;
    float scale;
    float x;
    float y;
    s16 bmpFmt;
    s16 dispF;
    s32 i;
    ANIMFRAME *animFrame;
    ANIMPAT *animPat;
    ANIMDATA *anim;
    ANIMBANK *animBank;
    ANIMBMP *animBmp;
    ANIMLAYER *animLayer;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;
    Mtx mtxInv;
    Mtx mtxPos;
    Mtx mtxRot;
    HuVecF scaleVtx[4];
    HuVecF finalVtx[4];
    HuVecF initVtx[4];
    ROMtx basePosMtx;

    particleP = arg0->hookData;
    anim = particleP->anim;
    if (HmfInverseMtxF3X3(arg1, mtxInv) == 0) {
        MTXIdentity(mtxInv);
    }
    PSMTXReorder(mtxInv, basePosMtx);
    if ((Hu3DPauseF == 0 || (arg0->attr & HU3D_ATTR_NOPAUSE)) && particleP->hook && particleP->prevCounter != GlobalCounter) {
        HU3DPARTICLEHOOK hook = particleP->hook;
        hook(arg0, particleP, arg1);
    }
    particleDataP = particleP->data;
    vtxBuf = particleP->vtxBuf;
    PSMTXROMultVecArray(basePosMtx, &basePos[0], initVtx, 4);
    for (i = 0, dispF = FALSE; i < particleP->maxCnt; i++, particleDataP++) {
        if (particleDataP->scale && (particleDataP->cameraBit & Hu3DCameraBit)) {
            if (!particleDataP->zRot) {
                scale = particleDataP->scale;
                vtxBuf->x = initVtx[0].x * scale + particleDataP->pos.x;
                vtxBuf->y = initVtx[0].y * scale + particleDataP->pos.y;
                vtxBuf->z = initVtx[0].z * scale + particleDataP->pos.z;
                vtxBuf++;
                vtxBuf->x = initVtx[1].x * scale + particleDataP->pos.x;
                vtxBuf->y = initVtx[1].y * scale + particleDataP->pos.y;
                vtxBuf->z = initVtx[1].z * scale + particleDataP->pos.z;
                vtxBuf++;
                vtxBuf->x = initVtx[2].x * scale + particleDataP->pos.x;
                vtxBuf->y = initVtx[2].y * scale + particleDataP->pos.y;
                vtxBuf->z = initVtx[2].z * scale + particleDataP->pos.z;
                vtxBuf++;
                vtxBuf->x = initVtx[3].x * scale + particleDataP->pos.x;
                vtxBuf->y = initVtx[3].y * scale + particleDataP->pos.y;
                vtxBuf->z = initVtx[3].z * scale + particleDataP->pos.z;
                vtxBuf++;
            } else {
                VECScale(&basePos[0], &scaleVtx[0], particleDataP->scale);
                VECScale(&basePos[1], &scaleVtx[1], particleDataP->scale);
                VECScale(&basePos[2], &scaleVtx[2], particleDataP->scale);
                VECScale(&basePos[3], &scaleVtx[3], particleDataP->scale);
                MTXRotRad(mtxRot, 'Z', particleDataP->zRot);
                MTXConcat(mtxInv, mtxRot, mtxPos);
                MTXMultVecArray(mtxPos, scaleVtx, finalVtx, 4);
                VECAdd(&finalVtx[0], &particleDataP->pos, vtxBuf++);
                VECAdd(&finalVtx[1], &particleDataP->pos, vtxBuf++);
                VECAdd(&finalVtx[2], &particleDataP->pos, vtxBuf++);
                VECAdd(&finalVtx[3], &particleDataP->pos, vtxBuf++);
            }
            dispF = TRUE;
        } else {
            vtxBuf->x = vtxBuf->y = vtxBuf->z = 0.0f;
            vtxBuf++;
            vtxBuf->x = vtxBuf->y = vtxBuf->z = 0.0f;
            vtxBuf++;
            vtxBuf->x = vtxBuf->y = vtxBuf->z = 0.0f;
            vtxBuf++;
            vtxBuf->x = vtxBuf->y = vtxBuf->z = 0.0f;
            vtxBuf++;
        }
    }
    if (dispF) {
        DCFlushRangeNoSync(particleP->vtxBuf, particleP->maxCnt * sizeof(Vec) * 4);
        GXLoadPosMtxImm(arg1, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        if (shadowModelDrawF != 0) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetZMode(0, GX_LEQUAL, 0);
        } else {
            bmpFmt = (particleP->anim->bmp->dataFmt & 0xF);
            if (bmpFmt == 7 || bmpFmt == 8) {
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
        if (particleP->attr & 8) {
            animBank = &anim->bank[particleP->animBank];
            animFrame = &animBank->frame[particleP->animNo];
            animPat = &anim->pat[animFrame->pat];
            HuSprTexLoad(particleP->anim, animPat->layer->bmpNo, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
            if (Hu3DPauseF == FALSE || (arg0->attr & HU3D_ATTR_NOPAUSE)) {
                for (i = 0; i < (s32) particleP->animSpeed * minimumVcount; i++) {
                    particleP->animTime += 1.0f;
                    if (particleP->animTime >= animFrame->time) {
                        particleP->animNo++;
                        particleP->animTime -= animFrame->time;
                        if (particleP->animNo >= animBank->timeNum || animFrame[1].time == -1) {
                            particleP->animNo = 0;
                        }
                    }
                    animFrame = &animBank->frame[particleP->animNo];
                }
                particleP->animTime += particleP->animSpeed * minimumVcount - i;
                if (particleP->animTime >= animFrame->time) {
                    particleP->animNo++;
                    particleP->animTime -= animFrame->time;
                    if (particleP->animNo >= animBank->timeNum || animFrame[1].time == -1) {
                        particleP->animNo = 0;
                    }
                }
            }
            animLayer = animPat->layer;
            animBmp = &anim->bmp[animLayer->bmpNo];
            x = (float) animLayer->sizeX / animBmp->sizeX;
            y = (float) animLayer->sizeY / animBmp->sizeY;
            MTXScale(mtxInv, x, y, 1.0f);
            x = (float) animLayer->startX / animBmp->sizeX;
            y = (float) animLayer->startY / animBmp->sizeY;
            mtxTransCat(mtxInv, x, y, 0.0f);
            GXLoadTexMtxImm(mtxInv, GX_TEXMTX0, GX_MTX2x4);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        } else {
            HuSprTexLoad(particleP->anim, 0, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
        }
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(0);
        switch (particleP->blendMode) {
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
        GXSetArray(GX_VA_POS, particleP->vtxBuf, sizeof(HuVecF));
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetArray(GX_VA_CLR0, &particleP->data->color, sizeof(HU3DPARTICLEDATA));
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
        GXSetArray(GX_VA_TEX0, baseST, sizeof(HuVec2f));
        GXCallDisplayList(particleP->dlBuf, particleP->dlSize);
    }
    if (shadowModelDrawF == FALSE) {
        if (!(particleP->attr & HU3D_PARTICLE_ATTR_STOPCNT) && Hu3DPauseF == FALSE) {
            particleP->count++;
        }
        if (particleP->prevCount != 0 && particleP->prevCount <= particleP->count) {
            if (particleP->attr & HU3D_PARTICLE_ATTR_RESETCNT) {
                particleP->count = 0;
            }
            particleP->count = particleP->prevCount;
        }
        particleP->prevCounter = GlobalCounter;
    }
}

void Hu3DParManInit(void) {
    s16 i;

    for (i = 0; i < HU3D_PARMAN_MAX; i++) {
        parManProc[i] = NULL;
    }
}

s16 Hu3DParManCreate(ANIMDATA *anim, s16 maxCnt, HU3DPARMANPARAM *param) {
    HU3DMODEL *modelP;
    HU3DPARTICLE *particleP;
    HU3DPARMAN *parManP;
    HU3DPARTICLEDATA *particleDataP;
    HU3DMODELID modelId;
    s16 i;
    HU3DPARMANID parManId;

    for (parManId = 0; parManId < HU3D_PARMAN_MAX; parManId++) {
        if (!parManProc[parManId]) {
            break;
        }
    }
    if (parManId == HU3D_PARMAN_MAX) {
        return HU3D_PARMANID_NONE;
    }
    modelId = Hu3DParticleCreate(anim, maxCnt);
    Hu3DParticleHookSet(modelId, ParManHook);
    modelP = &Hu3DData[modelId];
    particleP = modelP->hookData;
    particleP->dataCnt = parManId;
    particleDataP = particleP->data;
    for (i = 0; i < particleP->maxCnt; i++, particleDataP++) {
        particleDataP->scale = 0.0f;
    }
    parManProc[parManId] = HuPrcCreate(ParManFunc, 100, 0x1000, 0);
    parManP = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(HU3DPARMAN), MEMORY_DEFAULT_NUM);
    parManProc[parManId]->user_data = parManP;
    parManP->modelId = modelId;
    parManP->param = param;
    parManP->attr = HU3D_PARMAN_ATTR_NONE;
    parManP->pos.x = parManP->pos.y = parManP->pos.z = 0.0f;
    parManP->vec.x = 0.0f;
    parManP->vec.y = 1.0f;
    parManP->vec.z = 1.0f;
    parManP->vacuum.x = 0.0f;
    parManP->vacuum.y = 0.0f;
    parManP->vacuum.z = 0.0f;
    parManP->vacuumSpeed = 1.0f;
    parManP->accel = 0.0f;
    parManP->timeLimit = 0;
    parManP->parManId = parManId;
    return parManId;
}

HU3DPARMANID Hu3DParManLink(HU3DPARMANID linkParManId, HU3DPARMANPARAM *param) {
    HU3DPARMAN *linkParManP;
    HU3DPARMAN *parManP;
    HU3DPARMANID parManId;

    for (parManId = 0; parManId < HU3D_PARMAN_MAX; parManId++) {
        if (!parManProc[parManId]) {
            break;
        }
    }
    if (parManId == HU3D_PARMAN_MAX) {
        return HU3D_PARMANID_NONE;
    }
    linkParManP = parManProc[linkParManId]->user_data;
    parManProc[parManId] = HuPrcCreate(ParManFunc, 100, 0x1000, 0);
    parManP = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(HU3DPARMAN), MEMORY_DEFAULT_NUM);
    parManProc[parManId]->user_data = parManP;
    parManP->modelId = linkParManP->modelId;
    parManP->param = param;
    parManP->attr = HU3D_PARMAN_ATTR_NONE;
    parManP->pos.x = parManP->pos.y = parManP->pos.z = 0.0f;
    parManP->vec.x = 0.0f;
    parManP->vec.y = 1.0f;
    parManP->vec.z = 1.0f;
    parManP->vacuum.x = 0.0f;
    parManP->vacuum.y = 0.0f;
    parManP->vacuum.z = 0.0f;
    parManP->vacuumSpeed = 1.0f;
    parManP->accel = 0.0f;
    parManP->timeLimit = 0;
    parManP->parManId = parManId;
    return parManId;
}

void Hu3DParManKill(HU3DPARMANID parManId) {
    HU3DPARMAN *temp_r26;
    HU3DPARMAN *parManP;
    HU3DPARTICLEDATA *particleDataP;
    HU3DMODEL *modelP;
    HU3DPARTICLE *particleP;
    s16 i;

    if (parManProc[parManId]) {
        parManP = parManProc[parManId]->user_data;
        modelP = &Hu3DData[parManP->modelId];
        particleP = modelP->hookData;
        particleDataP = particleP->data;
        for (i = 0; i < particleP->maxCnt; i++, particleDataP++) {
            if (particleDataP->parManId == parManId) {
                particleDataP->scale = 0.0f;
            }
        }
        for (i = 0; i < HU3D_PARMAN_MAX; i++) {
            if (parManProc[i] && i != parManId) {
                temp_r26 = parManProc[i]->user_data;
                if (temp_r26->modelId == parManP->modelId) {
                    break;
                }
            }
        }
        if (i == HU3D_PARMAN_MAX) {
            Hu3DModelKill(parManP->modelId);
        }
        HuPrcKill(parManProc[parManId]);
        parManProc[parManId] = NULL;
        HuMemDirectFree(parManP);
    }
}

void Hu3DParManAllKill(void) {
    HU3DPARMANID parManId;

    for (parManId = 0; parManId < HU3D_PARMAN_MAX; parManId++) {
        if (parManProc[parManId]) {
            Hu3DParManKill(parManId);
        }
    }
}

HU3DPARMAN *Hu3DParManPtrGet(HU3DPARMANID parManId) {
    return parManProc[parManId]->user_data;
}

void Hu3DParManPosSet(HU3DPARMANID parManId, float posX, float posY, float posZ) {
    HU3DPARMAN *parManP = parManProc[parManId]->user_data;

    parManP->pos.x = posX;
    parManP->pos.y = posY;
    parManP->pos.z = posZ;
}

void Hu3DParManVecSet(HU3DPARMANID parManId, float x, float y, float z) {
    HU3DPARMAN *parManP = parManProc[parManId]->user_data;

    parManP->vec.x = x;
    parManP->vec.y = y;
    parManP->vec.z = z;
}

void Hu3DParManRotSet(HU3DPARMANID parManId, float rotX, float rotY, float rotZ) {
    HU3DPARMAN *parManP = parManProc[parManId]->user_data;
    Mtx rotMtx;

    mtxRot(rotMtx, rotX, rotY, rotZ);
    parManP->vec.x = rotMtx[0][2];
    parManP->vec.y = rotMtx[1][2];
    parManP->vec.z = rotMtx[2][2];
}

void Hu3DParManAttrSet(HU3DPARMANID parManId, s32 attr) {
    HU3DPARMAN *parManP = parManProc[parManId]->user_data;

    parManP->attr |= attr;
}

void Hu3DParManAttrReset(HU3DPARMANID parManId, s32 attr) {
    HU3DPARMAN *parManP = parManProc[parManId]->user_data;

    parManP->attr &= ~attr;
}

s16 Hu3DParManModelIDGet(HU3DPARMANID parManId) {
    HU3DPARMAN *parManP = parManProc[parManId]->user_data;

    return parManP->modelId;
}

void Hu3DParManTimeLimitSet(HU3DPARMANID parManId, s32 timeLimit) {
    HU3DPARMAN *parManP = parManProc[parManId]->user_data;

    parManP->timeLimit = timeLimit;
}

void Hu3DParManVacumeSet(HU3DPARMANID parManId, float x, float y, float z, float speed) {
    HU3DPARMAN *parManP;

    Hu3DParManAttrSet(parManId, HU3D_PARMAN_ATTR_VACUUM);
    parManP = parManProc[parManId]->user_data;
    parManP->vacuum.x = x;
    parManP->vacuum.y = y;
    parManP->vacuum.z = z;
    parManP->vacuumSpeed = speed;
}

void Hu3DParManColorSet(HU3DPARMANID parManId, s16 color) {
    HU3DPARMAN *parManP;

    Hu3DParManAttrSet(parManId, HU3D_PARMAN_ATTR_SETCOLOR);
    parManP = parManProc[parManId]->user_data;
    parManP->color = color;
}

static void ParManFunc(void) {
    HUPROCESS *processP;
    HU3DPARMAN *parManP;
    HU3DPARMANPARAM *param;
    HU3DMODEL *modelP;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;
    HU3DPARTICLEDATA *particleDataEnd;
    Vec vecDir;
    Vec vel;
    Vec dir;
    Vec up;
    float c;
    float s;
    float angleStart;
    float upRot;
    float accelVel;
    float rot;
    s16 colorIdx;
    s16 circleIdx;

    processP = HuPrcCurrentGet();
    parManP = processP->user_data;
    param = parManP->param;
    modelP = &Hu3DData[parManP->modelId];
    while (1) {
        if (Hu3DPauseF != 0 && !(modelP->attr & HU3D_ATTR_NOPAUSE)) {
            HuPrcVSleep();
            continue;
        }
        particleP = modelP->hookData;
        particleDataP = particleP->data;
        if (parManP->attr & HU3D_PARMAN_ATTR_RANDTIME90) {
            // Bug? Likely to be (u32) (temp_r30->unk04 * 0.1 * 1000.0)
            accelVel = param->accelRange * 0.9 + (s32) frandmod((u32) param->accelRange * 0.1 * 1000.0) / 1000.0f;
        } else if (parManP->attr & HU3D_PARMAN_ATTR_RANDTIME70) {
            accelVel = param->accelRange * 0.7 + (s32) frandmod((u32) param->accelRange * 0.3 * 1000.0) / 1000.0f;
        } else {
            accelVel = param->accelRange;
        }
        parManP->accel += accelVel;
        circleIdx = 0;
        particleDataEnd = &particleP->data[particleP->maxCnt];
        if (parManP->attr & HU3D_PARMAN_ATTR_RANDANGLE) {
            angleStart = (s32) frandmod((u32) (360.0f / param->accelRange) * 100) / 100;
        }
        while (parManP->accel >= 1.0f) {
            if (parManP->attr & HU3D_PARMAN_ATTR_TIMEUP) {
                parManP->accel -= 1.0f;
            } else {
                while (particleDataP < particleDataEnd) {
                    if (!particleDataP->scale) {
                        s = param->scaleBase;
                        if (parManP->attr & HU3D_PARMAN_ATTR_RANDSCALE90) {
                            s = s * 0.9 + (s32) frandmod((u32) (s * 0.1 * 1000.0)) / 1000.0f;
                        } else if (parManP->attr & HU3D_PARMAN_ATTR_RANDSCALE70) {
                            s = s * 0.7 + (s32) frandmod((u32) (s * 0.3 * 1000.0)) / 1000.0f;
                        }
                        particleDataP->scaleBase = s;
                        particleDataP->scale = s;
                        particleDataP->pos = parManP->pos;
                        vel.x = (s32) frandmod((u32) (param->scaleRange * 2.0f)) - param->scaleRange;
                        vel.y = (s32) frandmod((u32) (param->scaleRange * 2.0f)) - param->scaleRange;
                        vel.z = (s32) frandmod((u32) (param->scaleRange * 2.0f)) - param->scaleRange;
                        VECNormalize(&vel, &vel);
                        VECScale(&vel, &vel, param->scaleRange);
                        VECAdd(&vel, &particleDataP->pos, &particleDataP->pos);
                        VECNormalize(&parManP->vec, &vecDir);
                        if (parManP->attr & HU3D_PARMAN_ATTR_RANDANGLE) {
                            upRot = angleStart + (360.0f / param->accelRange) * circleIdx;
                            rot = param->angleRange;
                        } else {
                            upRot = (s32) frandmod(360);
                            if (param->angleRange) {
                                rot = (s32) frandmod((u32) param->angleRange);
                            } else {
                                rot = 0.0f;
                            }
                        }
                        if (vecDir.x * vecDir.x < 0.000001 && vecDir.z * vecDir.z < 0.000001) {
                            up.x = 1.0f;
                            up.y = up.z = 0.0f;
                        } else {
                            if (vecDir.y * vecDir.y > 0.000001) {
                                dir.x = vecDir.x;
                                dir.y = 0.0f;
                                dir.z = vecDir.z;
                            } else {
                                dir.x = vecDir.x;
                                dir.y = 1.0f;
                                dir.z = vecDir.z;
                            }
                            VECCrossProduct(&dir, &vecDir, &up);
                        }
                        VECNormalize(&up, &up);
                        s = sind(upRot);
                        c = cosd(upRot);
                        dir.x = up.x * (vecDir.x * vecDir.x + c * (1.0f - vecDir.x * vecDir.x))
                            + up.y * (vecDir.x * vecDir.y * (1.0f - c) - vecDir.z * s)
                            + up.z * (vecDir.x * vecDir.z * (1.0f - c) + vecDir.y * s);
                        dir.y = up.x * (vecDir.x * vecDir.y * (1.0f - c) + vecDir.z * s)
                            + up.y * (vecDir.y * vecDir.y + c * (1.0f - vecDir.y * vecDir.y))
                            + up.z * (vecDir.y * vecDir.z * (1.0f - c) - vecDir.x * s);
                        dir.z = up.x * (vecDir.x * vecDir.z * (1.0f - c) - vecDir.y * s)
                            + up.y * (vecDir.y * vecDir.z * (1.0f - c) + vecDir.x * s)
                            + up.z * (vecDir.z * vecDir.z + c * (1.0f - vecDir.z * vecDir.z));
                        VECCrossProduct(&dir, &vecDir, &up);
                        s = sind(rot);
                        c = cosd(rot);
                        dir.x = vecDir.x * (up.x * up.x + c * (1.0f - up.x * up.x))
                            + vecDir.y * (up.x * up.y * (1.0f - c) - up.z * s)
                            + vecDir.z * (up.x * up.z * (1.0f - c) + up.y * s);
                        dir.y = vecDir.x * (up.x * up.y * (1.0f - c) + up.z * s)
                            + vecDir.y * (up.y * up.y + c * (1.0f - up.y * up.y))
                            + vecDir.z * (up.y * up.z * (1.0f - c) - up.x * s);
                        dir.z = vecDir.x * (up.x * up.z * (1.0f - c) - up.y * s)
                            + vecDir.y * (up.y * up.z * (1.0f - c) + up.x * s)
                            + vecDir.z * (up.z * up.z + c * (1.0f - up.z * up.z));
                        VECNormalize(&dir, &dir);
                        s = param->speedBase;
                        if (parManP->attr & HU3D_PARMAN_ATTR_RANDSPEED90) {
                            s = s * 0.9 + (s32) frandmod((u32) (s * 0.1 * 1000.0)) / 1000.0f;
                        } else if (parManP->attr & HU3D_PARMAN_ATTR_RANDSPEED70) {
                            s = s * 0.7 + (s32) frandmod((u32) (s * 0.3 * 1000.0)) / 1000.0f;
                        } else if (parManP->attr & HU3D_PARMAN_ATTR_RANDSPEED100) {
                            s = (s32) frandmod((u32) (s * 1000.0f)) / 1000.0f;
                        }
                        VECScale(&dir, &particleDataP->vel, s);
                        particleDataP->accel = param->gravity;
                        particleDataP->speedDecay = param->speedDecay;
                        if (parManP->attr & HU3D_PARMAN_ATTR_SETCOLOR) {
                            particleDataP->colorIdx = colorIdx = parManP->color;
                        } else {
                            particleDataP->colorIdx = colorIdx = frandmod(param->colorNum);
                        }
                        particleDataP->color = param->colorStart[colorIdx];
                        particleDataP->time = 0;
                        particleDataP->parManId = parManP->parManId;
                        break;
                    } else {
                        particleDataP++;
                    }
                }
                parManP->accel -= 1.0f;
                circleIdx++;
            }
        }
        if (parManP->timeLimit != 0) {
            parManP->timeLimit--;
            if (parManP->timeLimit == 0) {
                parManP->attr |= HU3D_PARMAN_ATTR_TIMEUP;
            }
        }
        HuPrcVSleep();
    }
}

static float jitterTbl[] = {
    1.0f, 0.9f, 0.7f, 0.5f,
    0.5f, 0.7f, 0.9f, 1.0f
};

static void ParManHook(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx) {
    HU3DPARMANPARAM *param;
    HU3DPARMAN *parManP;
    HU3DPARTICLEDATA *particleDataP;
    GXColor *colorEnd;
    GXColor *colorStart;
    Vec vacuumAccel;
    Vec vacuumDist;
    float temp_f29;
    float weight;
    s16 colorIdx;
    s16 time;
    s16 i;

    if (Hu3DPauseF == FALSE || (model->attr & HU3D_ATTR_NOPAUSE)) {
        particleDataP = particle->data;
        for (i = 0; i < particle->maxCnt; i++, particleDataP++) {
            if (particleDataP->scale) {
                parManP = parManProc[particleDataP->parManId]->user_data;
                param = parManP->param;
                if (parManP->attr & HU3D_PARMAN_ATTR_SCALEJITTER) {
                    particleDataP->scale = particleDataP->scaleBase * jitterTbl[(parManP->jitterNo + i) & 7];
                } else {
                    particleDataP->scale = particleDataP->scaleBase;
                }
                if (!(parManP->attr & HU3D_PARMAN_ATTR_PAUSE)) {
                    time = particleDataP->time;
                    particleDataP->pos.x += particleDataP->vel.x + particleDataP->accel.x;
                    particleDataP->pos.y += particleDataP->vel.y + particleDataP->accel.y;
                    particleDataP->pos.z += particleDataP->vel.z + particleDataP->accel.z;
                    VECScale(&particleDataP->vel, &particleDataP->vel, particleDataP->speedDecay);
                    VECAdd(&param->gravity, &particleDataP->accel, &particleDataP->accel);
                    if (parManP->attr & HU3D_PARMAN_ATTR_VACUUM) {
                        VECSubtract(&parManP->vacuum, &particleDataP->pos, &vacuumAccel);
                        VECNormalize(&vacuumAccel, &vacuumAccel);
                        VECScale(&vacuumAccel, &vacuumAccel, parManP->vacuumSpeed);
                        VECAdd(&vacuumAccel, &particleDataP->accel, &particleDataP->accel);
                        VECAdd(&particleDataP->vel, &particleDataP->accel, &vacuumAccel);
                        VECSubtract(&parManP->vacuum, &particleDataP->pos, &vacuumDist);
                        temp_f29 = VECSquareMag(&vacuumAccel);
                        if (VECSquareMag(&vacuumDist) <= temp_f29) {
                            particleDataP->scale = 0.0f;
                            continue;
                        }
                    }
                    particleDataP->scaleBase *= param->scaleDecay;
                    weight = (float) particleDataP->time / param->maxTime;
                    if (weight > 1.0f) {
                        weight = 1.0f;
                    }
                    OSf32tos16(&particleDataP->colorIdx, &colorIdx);
                    colorStart = &param->colorStart[colorIdx];
                    colorEnd = &param->colorEnd[colorIdx];
                    particleDataP->color.r = colorStart->r + weight * (colorEnd->r - colorStart->r);
                    particleDataP->color.g = colorStart->g + weight * (colorEnd->g - colorStart->g);
                    particleDataP->color.b = colorStart->b + weight * (colorEnd->b - colorStart->b);
                    particleDataP->color.a = colorStart->a + weight * (colorEnd->a - colorStart->a);
                    if (particleDataP->scale < 0.01 || particleDataP->time >= param->maxTime) {
                        particleDataP->scale = 0.0f;
                    }
                    particleDataP->time++;
                }
            }
        }
        parManP = parManProc[particle->dataCnt]->user_data;
        parManP->jitterNo++;
        DCStoreRangeNoSync(particle->data, particle->maxCnt * sizeof(HU3DPARTICLEDATA));
    }
}
