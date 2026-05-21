#include "game/esprite.h"
#include "game/data.h"
#include "game/sprite.h"

typedef struct esprite_s {
    s16 memberNo;
    s16 animNo;
} ESPRITE;

typedef struct espanim_s {
    /* 0x00 */ u32 dataNum;
    /* 0x04 */ u16 useCnt;
    /* 0x08 */ ANIMDATA *anim;
} ESPANIM; // Size 0xC

ESPRITE esprite[HUSPR_MAX];
ESPANIM espanim[HUSPR_MAX];

static HUSPRGRPID gid;

void espInit(void) {
    s32 i;

    gid = HuSprGrpCreate(0x180);
    for (i = 0; i < HUSPR_MAX; i++) {
        esprite[i].memberNo = i;
        esprite[i].animNo = -1;
    }
    for (i = 0; i < HUSPR_MAX; i++) {
        espanim[i].useCnt = 0;
    }
}

s16 espEntry(unsigned int dataNum, s16 prio, s16 bank) {
    ESPANIM *animFree;
    ESPANIM *anim;
    ESPRITE *esp;
    void *data;
    s16 sprNo;
    s16 i;
    s32 animFreeId;

    esp = esprite;
    for (i = 0; i < HUSPR_MAX; esp++, i++) {
        if (esp->animNo == -1) {
            break;
        }
    }
    if (i == HUSPR_MAX) {
        return -1;
    }
    anim = espanim;
    animFree = NULL;
    for (animFreeId = 0; animFreeId < HUSPR_MAX; anim++, animFreeId++) {
        if (anim->useCnt != 0) {
            if (anim->dataNum == dataNum) {
                animFree = NULL;
                break;
            }
        } else if (animFree == NULL) {
            animFree = anim;
        }
    }
    if (animFreeId == HUSPR_MAX) {
        if (animFree == NULL) {
            return -1;
        }
        data = HuDataSelHeapReadNum(dataNum, MEMORY_DEFAULT_NUM, HEAP_DATA);
        if (data == NULL) {
            return -1;
        }
        animFree->dataNum = dataNum;
        animFree->anim = HuSprAnimRead(data);
        anim = animFree;
    }
    sprNo = HuSprCreate(anim->anim, prio, bank);
    if (sprNo == -1) {
        if (animFree != NULL) {
            HuSprAnimKill(anim->anim);
        }
        return -1;
    }
    anim->useCnt++;
    esp->animNo = anim - espanim;
    HuSprGrpMemberSet(gid, esp->memberNo, sprNo);
    return i;
}

void espKill(s16 espId) {
    HuSprGrpMemberKill(gid, esprite[espId].memberNo);
    espanim[esprite[espId].animNo].useCnt--;
    esprite[espId].animNo = -1;
}

s16 espGrpIDGet(void) {
    return gid;
}

void espDispOn(s16 espId) {
    HuSprAttrReset(gid, esprite[espId].memberNo, 4);
}

void espDispOff(s16 espId) {
    HuSprAttrSet(gid, esprite[espId].memberNo, 4);
}

void espAttrSet(s16 espId, u16 attr) {
    HuSprAttrSet(gid, esprite[espId].memberNo, attr);
}

void espAttrReset(s16 espId, u16 attr) {
    HuSprAttrReset(gid, esprite[espId].memberNo, attr);
}

void espPosSet(s16 espId, float posX, float posY) {
    HuSprPosSet(gid, esprite[espId].memberNo, posX, posY);
}

void espScaleSet(s16 espId, float scaleX, float scaleY) {
    HuSprScaleSet(gid, esprite[espId].memberNo, scaleX, scaleY);
}

void espZRotSet(s16 espId, float zRot) {
    HuSprZRotSet(gid, esprite[espId].memberNo, zRot);
}

void espTPLvlSet(s16 espId, float tpLvl) {
    HuSprTPLvlSet(gid, esprite[espId].memberNo, tpLvl);
}

void espColorSet(s16 espId, u8 r, u8 g, u8 b) {
    HuSprColorSet(gid, esprite[espId].memberNo, r, g, b);
}

void espSpeedSet(s16 espId, float speed) {
    HuSprSpeedSet(gid, esprite[espId].memberNo, speed);
}

void espBankSet(s16 espId, s16 bank) {
    HuSprBankSet(gid, esprite[espId].memberNo, bank);
}

void espDrawNoSet(s16 espId, s16 drawNo) {
    HuSprDrawNoSet(gid, esprite[espId].memberNo, drawNo);
}

void espPriSet(s16 espId, s16 pri) {
    HuSprPriSet(gid, esprite[espId].memberNo, pri);
}
