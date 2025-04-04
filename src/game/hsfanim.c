#include "game/hsfanim.h"
#include "dolphin/gx/GXStruct.h"
#include "game/hsfdraw.h"
#include "game/init.h"
#include "game/memory.h"
#include "game/process.h"
#include "game/sprite.h"

#include "ext_math.h"
#include "string.h"

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
    /* 0x3C */ HsfanimStruct00 *unk3C;
} ParManProcUserData; // Size 0x40

static void particleFunc(ModelData *arg0, Mtx arg1);
static void ParManFunc(void);
static void ParManHook(ModelData *arg0, ParticleData *arg1, Mtx matrix);

u32 frand(void);

extern u32 GlobalCounter;

Hu3DTexAnimDataStruct Hu3DTexAnimData[HU3D_TEXANIM_MAX];
Hu3DTexScrDataStruct Hu3DTexScrData[16];
static Process *parManProc[64];

void Hu3DAnimInit(void) {
    Hu3DTexAnimDataStruct *var_r30;
    Hu3DTexScrDataStruct *var_r29;
    s16 i;

    var_r30 = Hu3DTexAnimData;
    for (i = 0; i < HU3D_TEXANIM_MAX; i++, var_r30++) {
        var_r30->unk06 = -1;
    }
    var_r29 = Hu3DTexScrData;
    for (i = 0; i < HU3D_TEXSCROLL_MAX; i++, var_r29++) {
        var_r29->unk02 = -1;
    }
}

s16 Hu3DAnimCreate(void *arg0, s16 arg1, char *arg2) {
    Hu3DTexAnimDataStruct *var_r31;
    HsfAttribute *var_r29;
    HsfData *temp_r27;
    HsfdrawStruct01 *var_r30;
    s16 i;
    s16 var_r25;
    s16 var_r28;

    var_r31 = Hu3DTexAnimData;
    for (var_r28 = 0; var_r28 < HU3D_TEXANIM_MAX; var_r28++, var_r31++) {
        if (var_r31->unk06 == -1) {
            break;
        }
    }
    if (var_r28 == HU3D_TEXANIM_MAX) {
        OSReport("Error: TexAnim Over\n");
        return -1;
    }
    temp_r27 = Hu3DData[arg1].hsfData;
    var_r29 = temp_r27->attribute;
    for (i = var_r25 = 0; i < temp_r27->attributeCnt; i++, var_r29++) {
        if (strcmp(arg2, var_r29->bitmap->name) == 0) {
            if (!var_r29->unk04) {
                var_r30 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r30), (u32) Hu3DData[arg1].unk_48);
                var_r29->unk04 = var_r30;
                var_r30->unk00 = 0;
            } else {
                var_r30 = var_r29->unk04;
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
    if (!arg0) {
        var_r31->unk10 = NULL;
    } else {
        var_r31->unk10 = HuSprAnimRead(arg0);
    }
    var_r31->unk06 = arg1;
    var_r31->unk08 = 0.0f;
    var_r31->unk02 = 0;
    var_r31->unk04 = 0;
    var_r31->unk00 = 0;
    var_r31->unk0C = 1.0f;
    return var_r28;
}

s16 Hu3DAnimLink(s16 arg0, s16 arg1, char *arg2) {
    Hu3DTexAnimDataStruct *var_r24 = &Hu3DTexAnimData[arg0];
    Hu3DTexAnimDataStruct *var_r31;
    AnimData *temp_r4;
    HsfAttribute *var_r29;
    HsfData *temp_r27;
    HsfdrawStruct01 *var_r30;
    s16 var_r28;
    s16 i;
    s16 var_r25;

    var_r31 = Hu3DTexAnimData;
    for (var_r28 = 0; var_r28 < HU3D_TEXANIM_MAX; var_r28++, var_r31++) {
        if (var_r31->unk06 == -1) {
            break;
        }
    }
    if (var_r28 == HU3D_TEXANIM_MAX) {
        OSReport("Error: TexAnim Over\n");
        return -1;
    }
    temp_r27 = Hu3DData[arg1].hsfData;
    var_r29 = temp_r27->attribute;
    for (i = var_r25 = 0; i < temp_r27->attributeCnt; i++, var_r29++) {
        if (strcmp(arg2, var_r29->bitmap->name) == 0) {
            if (!var_r29->unk04) {
                var_r30 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r30), (u32) Hu3DData[arg1].unk_48);
                var_r29->unk04 = var_r30;
            } else {
                var_r30 = var_r29->unk04;
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
    var_r31->unk10 = var_r24->unk10;
    var_r31->unk10->useNum++;
    var_r31->unk06 = arg1;
    var_r31->unk08 = 0.0f;
    var_r31->unk02 = 0;
    var_r31->unk04 = 0;
    var_r31->unk00 = 0;
    var_r31->unk0C = 1.0f;
    return var_r28;
}

void Hu3DAnimKill(s16 arg0) {
    Hu3DTexAnimDataStruct *temp_r31 = &Hu3DTexAnimData[arg0];
    HsfData *temp_r28 = Hu3DData[temp_r31->unk06].hsfData;
    HsfAttribute *var_r30;
    HsfdrawStruct01 *temp_r29;
    s16 i;

    if (temp_r28) {
        var_r30 = temp_r28->attribute;
        for (i = 0; i < temp_r28->attributeCnt; i++, var_r30++) {
            if (var_r30->unk04) {
                temp_r29 = var_r30->unk04;
                if (temp_r29->unk02 == arg0) {
                    temp_r29->unk00 &= ~1;
                    if (temp_r29->unk00 == 0) {
                        var_r30->unk04 = NULL;
                        HuMemDirectFree(temp_r29);
                    }
                }
            }
        }
    }
    temp_r31->unk06 = -1;
    if (--temp_r31->unk10->useNum <= 0) {
        HuMemDirectFree(temp_r31->unk10);
    }
}

void Hu3DAnimModelKill(s16 arg0) {
    Hu3DTexAnimDataStruct *var_r26 = &Hu3DTexAnimData[0];
    s16 i;

    for (i = 0; i < HU3D_TEXANIM_MAX; i++, var_r26++) {
        if (var_r26->unk06 == arg0) {
            Hu3DAnimKill(i);
        }
    }
}

void Hu3DAnimAllKill(void) {
    Hu3DTexAnimDataStruct *var_r26 = &Hu3DTexAnimData[0];
    s16 i;

    for (i = 0; i < HU3D_TEXANIM_MAX; i++, var_r26++) {
        if (var_r26->unk06 != -1) {
            Hu3DAnimKill(i);
        }
    }
    Hu3DTexScrollAllKill();
}

void Hu3DAnimAttrSet(s16 arg0, u16 arg1) {
    Hu3DTexAnimDataStruct *temp_r31 = &Hu3DTexAnimData[arg0];

    temp_r31->unk00 |= arg1;
}

void Hu3DAnimAttrReset(s16 arg0, s32 arg1) {
    Hu3DTexAnimDataStruct *temp_r31 = &Hu3DTexAnimData[arg0];

    temp_r31->unk00 &= ~arg1;
}

void Hu3DAnimSpeedSet(s16 arg0, float arg1) {
    Hu3DTexAnimDataStruct *temp_r31 = &Hu3DTexAnimData[arg0];

    temp_r31->unk0C = arg1;
}

void Hu3DAnimBankSet(s16 arg0, s32 arg1) {
    Hu3DTexAnimDataStruct *temp_r31 = &Hu3DTexAnimData[arg0];

    temp_r31->unk02 = arg1;
    temp_r31->unk04 = temp_r31->unk08 = 0.0f;
}

void Hu3DAnmNoSet(s16 arg0, u16 arg1) {
    Hu3DTexAnimDataStruct *temp_r31 = &Hu3DTexAnimData[arg0];

    temp_r31->unk04 = arg1;
    temp_r31->unk08 = 0.0f;
}

s32 Hu3DAnimSet(ModelData *arg0, HsfAttribute *arg1, s16 arg2) {
    HsfdrawStruct01 *temp_r30;
    Hu3DTexAnimDataStruct *temp_r29;
    AnimData *temp_r27;
    AnimBmpData *temp_r28;
    AnimLayerData *temp_r31;
    AnimPatData *temp_r25;
    s16 temp_r24;
    s16 var_r23;
    s16 var_r22;

    temp_r30 = arg1->unk04;
    temp_r29 = &Hu3DTexAnimData[temp_r30->unk02];
    temp_r27 = temp_r29->unk10;
    temp_r24 = temp_r27->bank[temp_r29->unk02].frame[temp_r29->unk04].pat;
    if (temp_r24 == -1) {
        return 0;
    }
    var_r23 = (arg1->wrap_s == 1) ? 1 : 0;
    var_r22 = (arg1->wrap_t == 1) ? 1 : 0;
    temp_r25 = &temp_r27->pat[temp_r24];
    temp_r31 = temp_r25->layer;
    temp_r28 = &temp_r27->bmp[temp_r31->bmpNo];
    HuSprTexLoad(temp_r29->unk10, temp_r31->bmpNo, arg2, var_r23, var_r22,
        (arg0->attr & HU3D_ATTR_TEX_NEAR) ? GX_NEAR : GX_LINEAR);
    temp_r30->unk2C = (float) temp_r31->sizeX / temp_r28->sizeX;
    temp_r30->unk30 = (float) temp_r31->sizeY / temp_r28->sizeY;
    temp_r30->unk34 = (float) temp_r31->startX / temp_r28->sizeX;
    temp_r30->unk38 = (float) temp_r31->startY / temp_r28->sizeY;
    return 1;
}

void Hu3DAnimExec(void) {
    Hu3DTexAnimDataStruct *var_r30;
    Hu3DTexScrDataStruct *var_r31;
    AnimData *var_r25;
    AnimBankData *temp_r28;
    AnimFrameData *var_r29;
    s16 var_r26;
    s16 i;

    var_r30 = Hu3DTexAnimData;
    for (i = 0; i < HU3D_TEXANIM_MAX; i++, var_r30++) {
        if (var_r30->unk06 != -1 && (Hu3DPauseF == 0 || (var_r30->unk00 & 0x20))) {
            var_r25 = var_r30->unk10;
            temp_r28 = &var_r25->bank[var_r30->unk02];
            var_r29 = &temp_r28->frame[var_r30->unk04];
            if (!(var_r30->unk00 & 1) || (var_r29->time == -1 && (var_r30->unk00 & 2))) {
                for (var_r26 = 0; var_r26 < (s32) var_r30->unk0C * minimumVcount; var_r26++) {
                    var_r30->unk08 += 1.0f;
                    if (var_r30->unk08 >= var_r29->time) {
                        var_r30->unk04++;
                        var_r30->unk08 -= var_r29->time;
                        if (var_r30->unk04 >= temp_r28->timeNum || var_r29[1].time == -1) {
                            var_r30->unk04 = 0;
                        }
                        var_r29 = &temp_r28->frame[var_r30->unk04];
                    }
                }
                var_r30->unk08 += var_r30->unk0C * minimumVcount - var_r26;
                if (var_r30->unk08 >= var_r29->time) {
                    var_r30->unk04++;
                    var_r30->unk08 -= var_r29->time;
                    if (var_r30->unk04 >= temp_r28->timeNum || var_r29[1].time == -1) {
                        var_r30->unk04 = 0;
                    }
                }
            }
        }
    }
    var_r31 = Hu3DTexScrData;
    for (i = 0; i < HU3D_TEXSCROLL_MAX; i++, var_r31++) {
        if (var_r31->unk02 != -1) {
            if (Hu3DPauseF != 0 && !(var_r31->unk00 & 8)) {
                MTXRotRad(var_r31->unk3C, 'Z', MTXDegToRad(var_r31->unk34));
                mtxTransCat(var_r31->unk3C, var_r31->unk04.x, var_r31->unk04.y, var_r31->unk04.z);
            } else {
                if (var_r31->unk00 & 1) {
                    VECAdd(&var_r31->unk04, &var_r31->unk1C, &var_r31->unk04);
                    if (var_r31->unk04.x > 1.0f) {
                        var_r31->unk04.x -= 1.0f;
                    }
                    if (var_r31->unk04.y > 1.0f) {
                        var_r31->unk04.y -= 1.0f;
                    }
                    if (var_r31->unk04.z > 1.0f) {
                        var_r31->unk04.z -= 1.0f;
                    }
                    if (var_r31->unk04.x < -1.0f) {
                        var_r31->unk04.x += 1.0f;
                    }
                    if (var_r31->unk04.y < -1.0f) {
                        var_r31->unk04.y += 1.0f;
                    }
                    if (var_r31->unk04.z < -1.0f) {
                        var_r31->unk04.z += 1.0f;
                    }
                }
                if (var_r31->unk00 & 2) {
                    var_r31->unk34 += var_r31->unk38;
                    if (var_r31->unk34 > 360.0f) {
                        var_r31->unk34 -= 360.0f;
                    }
                    if (var_r31->unk34 < -360.0f) {
                        var_r31->unk34 += 360.0f;
                    }
                }
                MTXRotRad(var_r31->unk3C, 'Z', MTXDegToRad(var_r31->unk34));
                mtxTransCat(var_r31->unk3C, var_r31->unk04.x, var_r31->unk04.y, var_r31->unk04.z);
            }
        }
    }
}

s16 Hu3DTexScrollCreate(s16 arg0, char *arg1) {
    Hu3DTexScrDataStruct *var_r31;
    HsfData *temp_r27;
    HsfAttribute *var_r29;
    HsfdrawStruct01 *var_r30;
    s16 i;
    s16 var_r25;
    s16 var_r28;

    var_r31 = Hu3DTexScrData;
    for (var_r28 = 0; var_r28 < HU3D_TEXSCROLL_MAX; var_r28++, var_r31++) {
        if (var_r31->unk02 == -1) {
            break;
        }
    }
    if (var_r28 == HU3D_TEXSCROLL_MAX) {
        OSReport("Error: TexScroll Over\n");
        return -1;
    }
    temp_r27 = Hu3DData[arg0].hsfData;
    var_r29 = temp_r27->attribute;
    for (i = var_r25 = 0; i < temp_r27->attributeCnt; i++, var_r29++) {
        if (strcmp(arg1, var_r29->bitmap->name) == 0) {
            if (!var_r29->unk04) {
                var_r30 = HuMemDirectMallocNum(HEAP_DATA, sizeof(*var_r30), (u32) Hu3DData[arg0].unk_48);
                var_r29->unk04 = var_r30;
                var_r30->unk00 = 0;
            } else {
                var_r30 = var_r29->unk04;
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
    var_r31->unk02 = arg0;
    var_r31->unk00 = 0;
    var_r31->unk04.x = var_r31->unk04.y = var_r31->unk04.z = 0.0f;
    var_r31->unk34 = 0.0f;
    MTXIdentity(var_r31->unk3C);
    return var_r28;
}

void Hu3DTexScrollKill(s16 arg0) {
    Hu3DTexScrDataStruct *temp_r28 = &Hu3DTexScrData[arg0];
    HsfData *temp_r29 = Hu3DData[temp_r28->unk02].hsfData;
    HsfAttribute *var_r31;
    HsfdrawStruct01 *temp_r30;
    s16 i;

    if (temp_r29) {
        var_r31 = temp_r29->attribute;
        for (i = 0; i < temp_r29->attributeCnt; i++, var_r31++) {
            if (var_r31->unk04) {
                temp_r30 = var_r31->unk04;
                if (temp_r30->unk04 == arg0) {
                    temp_r30->unk00 &= ~2;
                    if (temp_r30->unk00 == 0) {
                        var_r31->unk04 = NULL;
                        HuMemDirectFree(temp_r30);
                    }
                }
            }
        }
    }
    temp_r28->unk02 = -1;
}

void Hu3DTexScrollAllKill(void) {
    Hu3DTexScrDataStruct *var_r27;
    s16 i;

    var_r27 = Hu3DTexScrData;
    for (i = 0; i < HU3D_TEXSCROLL_MAX; i++, var_r27++) {
        if (var_r27->unk02 != -1) {
            Hu3DTexScrollKill(i);
        }
    }
}

void Hu3DTexScrollPosSet(s16 arg0, float arg1, float arg2, float arg3) {
    Hu3DTexScrDataStruct *temp_r31 = &Hu3DTexScrData[arg0];

    temp_r31->unk00 &= ~1;
    temp_r31->unk04.x = arg1;
    temp_r31->unk04.y = arg2;
    temp_r31->unk04.z = arg3;
}

void Hu3DTexScrollPosMoveSet(s16 arg0, float arg1, float arg2, float arg3) {
    Hu3DTexScrDataStruct *temp_r31 = &Hu3DTexScrData[arg0];

    temp_r31->unk00 |= 1;
    temp_r31->unk1C.x = arg1 * minimumVcount;
    temp_r31->unk1C.y = arg2 * minimumVcount;
    temp_r31->unk1C.z = arg3 * minimumVcount;
}

void Hu3DTexScrollRotSet(s16 arg0, float arg1) {
    Hu3DTexScrDataStruct *temp_r31 = &Hu3DTexScrData[arg0];

    temp_r31->unk00 &= ~2;
    temp_r31->unk34 = arg1;
}

void Hu3DTexScrollRotMoveSet(s16 arg0, float arg1) {
    Hu3DTexScrDataStruct *temp_r31 = &Hu3DTexScrData[arg0];

    temp_r31->unk00 |= 2;
    temp_r31->unk38 = arg1 * minimumVcount;
}

void Hu3DTexScrollPauseDisableSet(s16 arg0, s32 arg1) {
    Hu3DTexScrDataStruct *temp_r31 = &Hu3DTexScrData[arg0];

    if (arg1 != 0) {
        temp_r31->unk00 |= 8;
        return;
    } else {
        temp_r31->unk00 &= ~8;
    }
}

s16 Hu3DParticleCreate(AnimData *arg0, s16 arg1) {
    ModelData *temp_r28;
    ParticleData *temp_r31;
    HsfanimStruct01 *var_r30;
    Vec *var_r27;
    s16 temp_r25;
    s16 i;
    void *temp_r24;

    temp_r25 = Hu3DHookFuncCreate((void*) &particleFunc);
    temp_r28 = &Hu3DData[temp_r25];
    Hu3DModelAttrSet(temp_r25, HU3D_ATTR_PARTICLE_KILL);
    temp_r31 = HuMemDirectMallocNum(HEAP_DATA, sizeof(ParticleData), temp_r28->unk_48);
    temp_r28->unk_120 = temp_r31;
    temp_r31->unk_44 = arg0;
    arg0->useNum++;
    temp_r31->unk_30 = arg1;
    temp_r31->unk_2C = 0;
    temp_r31->unk_54 = NULL;
    temp_r31->unk_34 = 0;
    temp_r31->unk_2D = 0;
    temp_r31->unk_3C = 0;
    temp_r31->unk_00 = temp_r31->unk_02 = 0;
    var_r30 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(HsfanimStruct01), temp_r28->unk_48);
    temp_r31->unk_48 = var_r30;
    temp_r31->unk_38 = -1;
    for (i = 0; i < arg1; i++, var_r30++) {
        var_r30->unk2C = 0.0f;
        var_r30->unk04 = 0;
        var_r30->unk06 = -1;
        var_r30->unk30 = 0.0f;
        var_r30->unk34.x = ((s32) (frand() & 0x7F) - 0x40) * 0x14;
        var_r30->unk34.y = ((s32) (frand() & 0x7F) - 0x40) * 0x1E;
        var_r30->unk34.z = ((s32) (frand() & 0x7F) - 0x40) * 0x14;
        var_r30->unk40.r = var_r30->unk40.g = var_r30->unk40.b = var_r30->unk40.a = 0xFF;
    }
    var_r27 = HuMemDirectMallocNum(HEAP_DATA, arg1 * sizeof(Vec) * 4, temp_r28->unk_48);
    temp_r31->unk_4C = var_r27;
    for (i = 0; i < arg1 * 4; i++, var_r27++) {
        var_r27->x = var_r27->y = var_r27->z = 0.0f;
    }
    temp_r24 = HuMemDirectMallocNum(HEAP_DATA, arg1 * 0x60 + 0x80, temp_r28->unk_48);
    temp_r31->unk_50 = temp_r24;
    DCInvalidateRange(temp_r24, arg1 * 0x60 + 0x80);
    GXBeginDisplayList(temp_r24, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, arg1 * 4);
    for (i = 0; i < arg1; i++) {
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
    temp_r31->unk_40 = GXEndDisplayList();
    return temp_r25;
}

void Hu3DParticleScaleSet(s16 arg0, float arg1) {
    ModelData *temp_r25 = &Hu3DData[arg0];
    ParticleData *temp_r31 = temp_r25->unk_120;
    HsfanimStruct01 *var_r30;
    s16 i;

    var_r30 = temp_r31->unk_48;
    for (i = 0; i < temp_r31->unk_30; i++, var_r30++) {
        var_r30->unk2C = arg1;
    }
}

void Hu3DParticleZRotSet(s16 arg0, float arg1) {
    ModelData *temp_r28 = &Hu3DData[arg0];
    ParticleData *temp_r31 = temp_r28->unk_120;
    HsfanimStruct01 *var_r30;
    s16 i;

    var_r30 = temp_r31->unk_48;
    for (i = 0; i < temp_r31->unk_30; i++, var_r30++) {
        var_r30->unk30 = arg1;
    }
}

void Hu3DParticleColSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    ModelData *temp_r28 = &Hu3DData[arg0];
    ParticleData *temp_r30 = temp_r28->unk_120;
    HsfanimStruct01 *var_r31;
    s16 i;

    var_r31 = temp_r30->unk_48;
    for (i = 0; i < temp_r30->unk_30; i++, var_r31++) {
        var_r31->unk40.r = arg1;
        var_r31->unk40.g = arg2;
        var_r31->unk40.b = arg3;
    }
}

void Hu3DParticleTPLvlSet(s16 arg0, float arg1) {
    ModelData *temp_r28 = &Hu3DData[arg0];
    ParticleData *temp_r31 = temp_r28->unk_120;
    HsfanimStruct01 *var_r30;
    u8 var_r27;
    s16 i;

    var_r30 = temp_r31->unk_48;
    var_r27 = arg1 * 255.0f;
    for (i = 0; i < temp_r31->unk_30; i++, var_r30++) {
        var_r30->unk40.a = var_r27;
    }
}

void Hu3DParticleBlendModeSet(s16 arg0, u8 arg1) {
    ModelData *temp_r31 = &Hu3DData[arg0];
    ParticleData *temp_r30 = temp_r31->unk_120;

    temp_r30->unk_2C = arg1;
}

void Hu3DParticleHookSet(s16 arg0, ParticleHook arg1) {
    ModelData *temp_r31 = &Hu3DData[arg0];
    ParticleData *temp_r30 = temp_r31->unk_120;

    temp_r30->unk_54 = arg1;
}

void Hu3DParticleAttrSet(s16 arg0, u8 arg1) {
    ModelData *temp_r31 = &Hu3DData[arg0];
    ParticleData *temp_r30 = temp_r31->unk_120;

    temp_r30->unk_2D |= arg1;
}

void Hu3DParticleAttrReset(s16 arg0, u8 arg1) {
    ModelData *temp_r31 = &Hu3DData[arg0];
    ParticleData *temp_r30 = temp_r31->unk_120;

    temp_r30->unk_2D &= ~arg1;
}

void Hu3DParticleCntSet(s16 arg0, s16 arg1) {
    ModelData *temp_r31 = &Hu3DData[arg0];
    ParticleData *temp_r30 = temp_r31->unk_120;

    temp_r30->unk_34 = arg1;
}

void Hu3DParticleAnimModeSet(s16 arg0, s16 arg1) {
    ModelData *temp_r30 = &Hu3DData[arg0];
    ParticleData *temp_r31 = temp_r30->unk_120;

    temp_r31->unk_2D |= 8;
    temp_r31->unk_20 = arg1;
    temp_r31->unk_28 = 0.0f;
    temp_r31->unk_22 = 0;
    temp_r31->unk_24 = 1.0f;
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

static void particleFunc(ModelData *arg0, Mtx arg1) {
    Vec *var_r30;
    float temp_f31;
    float temp_f29;
    float temp_f30;
    s16 temp_r20;
    s16 var_r19;
    s32 i;
    AnimFrameData *var_r28;
    AnimPatData *temp_r21;
    AnimData *temp_r22;
    AnimBankData *temp_r25;
    AnimBmpData *temp_r24;
    AnimLayerData *temp_r27;
    ParticleData *temp_r31;
    HsfanimStruct01 *var_r29;
    ParticleHook var_r17;
    Mtx sp128;
    Mtx spF8;
    Mtx spC8;
    Vec sp98[4];
    Vec sp68[4];
    Vec sp38[4];
    ROMtx sp8;

    temp_r31 = arg0->unk_120;
    temp_r22 = temp_r31->unk_44;
    if (HmfInverseMtxF3X3(arg1, sp128) == 0) {
        MTXIdentity(sp128);
    }
    MTXReorder(sp128, sp8);
    if ((Hu3DPauseF == 0 || (arg0->attr & HU3D_ATTR_NOPAUSE)) && temp_r31->unk_54 && temp_r31->unk_38 != GlobalCounter) {
        var_r17 = temp_r31->unk_54;
        var_r17(arg0, temp_r31, arg1);
    }
    var_r29 = temp_r31->unk_48;
    var_r30 = temp_r31->unk_4C;
    MTXROMultVecArray(sp8, &basePos[0], sp38, 4);
    for (i = 0, var_r19 = 0; i < temp_r31->unk_30; i++, var_r29++) {
        if (var_r29->unk2C && (var_r29->unk06 & Hu3DCameraBit)) {
            if (!var_r29->unk30) {
                temp_f31 = var_r29->unk2C;
                var_r30->x = sp38[0].x * temp_f31 + var_r29->unk34.x;
                var_r30->y = sp38[0].y * temp_f31 + var_r29->unk34.y;
                var_r30->z = sp38[0].z * temp_f31 + var_r29->unk34.z;
                var_r30++;
                var_r30->x = sp38[1].x * temp_f31 + var_r29->unk34.x;
                var_r30->y = sp38[1].y * temp_f31 + var_r29->unk34.y;
                var_r30->z = sp38[1].z * temp_f31 + var_r29->unk34.z;
                var_r30++;
                var_r30->x = sp38[2].x * temp_f31 + var_r29->unk34.x;
                var_r30->y = sp38[2].y * temp_f31 + var_r29->unk34.y;
                var_r30->z = sp38[2].z * temp_f31 + var_r29->unk34.z;
                var_r30++;
                var_r30->x = sp38[3].x * temp_f31 + var_r29->unk34.x;
                var_r30->y = sp38[3].y * temp_f31 + var_r29->unk34.y;
                var_r30->z = sp38[3].z * temp_f31 + var_r29->unk34.z;
                var_r30++;
            } else {
                VECScale(&basePos[0], &sp98[0], var_r29->unk2C);
                VECScale(&basePos[1], &sp98[1], var_r29->unk2C);
                VECScale(&basePos[2], &sp98[2], var_r29->unk2C);
                VECScale(&basePos[3], &sp98[3], var_r29->unk2C);
                MTXRotRad(spC8, 'Z', var_r29->unk30);
                MTXConcat(sp128, spC8, spF8);
                MTXMultVecArray(spF8, sp98, sp68, 4);
                VECAdd(&sp68[0], &var_r29->unk34, var_r30++);
                VECAdd(&sp68[1], &var_r29->unk34, var_r30++);
                VECAdd(&sp68[2], &var_r29->unk34, var_r30++);
                VECAdd(&sp68[3], &var_r29->unk34, var_r30++);
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
        DCFlushRangeNoSync(temp_r31->unk_4C, temp_r31->unk_30 * sizeof(Vec) * 4);
        GXLoadPosMtxImm(arg1, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        if (shadowModelDrawF != 0) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetZMode(0, GX_LEQUAL, 0);
        } else {
            temp_r20 = (temp_r31->unk_44->bmp->dataFmt & 0xF);
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
        if (temp_r31->unk_2D & 8) {
            temp_r25 = &temp_r22->bank[temp_r31->unk_20];
            var_r28 = &temp_r25->frame[temp_r31->unk_22];
            temp_r21 = &temp_r22->pat[var_r28->pat];
            HuSprTexLoad(temp_r31->unk_44, temp_r21->layer->bmpNo, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
            if (Hu3DPauseF == 0 || (arg0->attr & HU3D_ATTR_NOPAUSE)) {
                for (i = 0; i < (s32) temp_r31->unk_24 * minimumVcount; i++) {
                    temp_r31->unk_28 += 1.0f;
                    if (temp_r31->unk_28 >= var_r28->time) {
                        temp_r31->unk_22++;
                        temp_r31->unk_28 -= var_r28->time;
                        if (temp_r31->unk_22 >= temp_r25->timeNum || var_r28[1].time == -1) {
                            temp_r31->unk_22 = 0;
                        }
                    }
                    var_r28 = &temp_r25->frame[temp_r31->unk_22];
                }
                temp_r31->unk_28 += temp_r31->unk_24 * minimumVcount - i;
                if (temp_r31->unk_28 >= var_r28->time) {
                    temp_r31->unk_22++;
                    temp_r31->unk_28 -= var_r28->time;
                    if (temp_r31->unk_22 >= temp_r25->timeNum || var_r28[1].time == -1) {
                        temp_r31->unk_22 = 0;
                    }
                }
            }
            temp_r27 = temp_r21->layer;
            temp_r24 = &temp_r22->bmp[temp_r27->bmpNo];
            temp_f29 = (float) temp_r27->sizeX / temp_r24->sizeX;
            temp_f30 = (float) temp_r27->sizeY / temp_r24->sizeY;
            MTXScale(sp128, temp_f29, temp_f30, 1.0f);
            temp_f29 = (float) temp_r27->startX / temp_r24->sizeX;
            temp_f30 = (float) temp_r27->startY / temp_r24->sizeY;
            mtxTransCat(sp128, temp_f29, temp_f30, 0.0f);
            GXLoadTexMtxImm(sp128, GX_TEXMTX0, GX_MTX2x4);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        } else {
            HuSprTexLoad(temp_r31->unk_44, 0, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
        }
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(0);
        switch (temp_r31->unk_2C) {
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
        GXSETARRAY(GX_VA_POS, temp_r31->unk_4C, temp_r31->unk_30 * 4 * sizeof(Vec), sizeof(Vec));
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSETARRAY(GX_VA_CLR0, &temp_r31->unk_48->unk40, temp_r31->unk_30 * sizeof(GXColor), 0x44);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
        GXSETARRAY(GX_VA_TEX0, baseST, sizeof(baseST), 8);
        GXCallDisplayList(temp_r31->unk_50, temp_r31->unk_40);
    }
    if (shadowModelDrawF == 0) {
        if (!(temp_r31->unk_2D & 2) && Hu3DPauseF == 0) {
            temp_r31->unk_34++;
        }
        if (temp_r31->unk_3C != 0 && temp_r31->unk_3C <= temp_r31->unk_34) {
            if (temp_r31->unk_2D & 1) {
                temp_r31->unk_34 = 0;
            }
            temp_r31->unk_34 = temp_r31->unk_3C;
        }
        temp_r31->unk_38 = GlobalCounter;
    }
}

void Hu3DParManInit(void) {
    s16 i;

    for (i = 0; i < 64; i++) {
        parManProc[i] = NULL;
    }
}

s16 Hu3DParManCreate(AnimData *arg0, s16 arg1, HsfanimStruct00 *arg2) {
    ModelData *temp_r25;
    ParticleData *temp_r29;
    ParManProcUserData *temp_r3_2;
    HsfanimStruct01 *var_r28;
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
    temp_r3 = Hu3DParticleCreate(arg0, arg1);
    Hu3DParticleHookSet(temp_r3, ParManHook);
    temp_r25 = &Hu3DData[temp_r3];
    temp_r29 = temp_r25->unk_120;
    temp_r29->unk_00 = var_r30;
    var_r28 = temp_r29->unk_48;
    for (var_r26 = 0; var_r26 < temp_r29->unk_30; var_r26++, var_r28++) {
        var_r28->unk2C = 0.0f;
    }
    parManProc[var_r30] = HuPrcCreate(ParManFunc, 100, 0x1000, 0);
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(ParManProcUserData), MEMORY_DEFAULT_NUM);
    parManProc[var_r30]->user_data = temp_r3_2;
    temp_r3_2->unk00 = temp_r3;
    temp_r3_2->unk3C = arg2;
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

s16 Hu3DParManLink(s16 arg0, HsfanimStruct00 *arg1) {
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
    temp_r29 = parManProc[arg0]->user_data;
    parManProc[var_r30] = HuPrcCreate(ParManFunc, 100, 0x1000, 0);
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(ParManProcUserData), MEMORY_DEFAULT_NUM);
    parManProc[var_r30]->user_data = temp_r3;
    temp_r3->unk00 = temp_r29->unk00;
    temp_r3->unk3C = arg1;
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

void Hu3DParManKill(s16 arg0) {
    ParManProcUserData *temp_r26;
    ParManProcUserData *temp_r30;
    HsfanimStruct01 *var_r29;
    ModelData *temp_r25;
    ParticleData *temp_r27;
    s16 i;

    if (parManProc[arg0]) {
        temp_r30 = parManProc[arg0]->user_data;
        temp_r25 = &Hu3DData[temp_r30->unk00];
        temp_r27 = temp_r25->unk_120;
        var_r29 = temp_r27->unk_48;
        for (i = 0; i < temp_r27->unk_30; i++, var_r29++) {
            if (var_r29->unk02 == arg0) {
                var_r29->unk2C = 0.0f;
            }
        }
        for (i = 0; i < 64; i++) {
            if (parManProc[i] && i != arg0) {
                temp_r26 = parManProc[i]->user_data;
                if (temp_r26->unk00 == temp_r30->unk00) {
                    break;
                }
            }
        }
        if (i == 64) {
            Hu3DModelKill(temp_r30->unk00);
        }
        HuPrcKill(parManProc[arg0]);
        parManProc[arg0] = NULL;
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

void *Hu3DParManPtrGet(s16 arg0) {
    return parManProc[arg0]->user_data;
}

void Hu3DParManPosSet(s16 arg0, float arg1, float arg2, float arg3) {
    ParManProcUserData *temp_r31 = parManProc[arg0]->user_data;

    temp_r31->unk0C.x = arg1;
    temp_r31->unk0C.y = arg2;
    temp_r31->unk0C.z = arg3;
}

void Hu3DParManVecSet(s16 arg0, float arg1, float arg2, float arg3) {
    ParManProcUserData *temp_r31 = parManProc[arg0]->user_data;

    temp_r31->unk18.x = arg1;
    temp_r31->unk18.y = arg2;
    temp_r31->unk18.z = arg3;
}

void Hu3DParManRotSet(s16 arg0, float arg1, float arg2, float arg3) {
    ParManProcUserData *temp_r31 = parManProc[arg0]->user_data;
    Mtx sp18;

    mtxRot(sp18, arg1, arg2, arg3);
    temp_r31->unk18.x = sp18[0][2];
    temp_r31->unk18.y = sp18[1][2];
    temp_r31->unk18.z = sp18[2][2];
}

void Hu3DParManAttrSet(s16 arg0, s32 arg1) {
    ParManProcUserData *temp_r31 = parManProc[arg0]->user_data;

    temp_r31->unk02 |= arg1;
}

void Hu3DParManAttrReset(s16 arg0, s32 arg1) {
    ParManProcUserData *temp_r31 = parManProc[arg0]->user_data;

    temp_r31->unk02 &= ~arg1;
}

s16 Hu3DParManModelIDGet(s16 arg0) {
    ParManProcUserData *temp_r31 = parManProc[arg0]->user_data;

    return temp_r31->unk00;
}

void Hu3DParManTimeLimitSet(s16 arg0, s32 arg1) {
    ParManProcUserData *temp_r31 = parManProc[arg0]->user_data;

    temp_r31->unk04 = arg1;
}

void Hu3DParManVacumeSet(s16 arg0, float arg1, float arg2, float arg3, float arg4) {
    ParManProcUserData *temp_r31;

    Hu3DParManAttrSet(arg0, 0x200);
    temp_r31 = parManProc[arg0]->user_data;
    temp_r31->unk24.x = arg1;
    temp_r31->unk24.y = arg2;
    temp_r31->unk24.z = arg3;
    temp_r31->unk30 = arg4;
}

void Hu3DParManColorSet(s16 arg0, s16 arg1) {
    ParManProcUserData *temp_r31;

    Hu3DParManAttrSet(arg0, 0x1000);
    temp_r31 = parManProc[arg0]->user_data;
    temp_r31->unk08 = arg1;
}

static void ParManFunc(void) {
    Process *temp_r25;
    ParManProcUserData *temp_r31;
    HsfanimStruct00 *temp_r30;
    ModelData *temp_r27;
    ParticleData *temp_r28;
    HsfanimStruct01 *var_r29;
    HsfanimStruct01 *temp_r23;
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
        temp_r28 = temp_r27->unk_120;
        var_r29 = temp_r28->unk_48;
        if (temp_r31->unk02 & 0x400) {
            // Bug? Likely to be (u32) (temp_r30->unk04 * 0.1 * 1000.0)
            var_f27 = temp_r30->unk04 * 0.9 + (s32) frandmod((u32) temp_r30->unk04 * 0.1 * 1000.0) / 1000.0f;
        } else if (temp_r31->unk02 & 0x800) {
            var_f27 = temp_r30->unk04 * 0.7 + (s32) frandmod((u32) temp_r30->unk04 * 0.3 * 1000.0) / 1000.0f;
        } else {
            var_f27 = temp_r30->unk04;
        }
        temp_r31->unk34 += var_f27;
        var_r26 = 0;
        temp_r23 = &((HsfanimStruct01*) temp_r28->unk_48)[temp_r28->unk_30];
        if (temp_r31->unk02 & 0x100) {
            var_f26 = (s32) frandmod((u32) (360.0f / temp_r30->unk04) * 100) / 100;
        }
        while (temp_r31->unk34 >= 1.0f) {
            if (temp_r31->unk02 & 1) {
                temp_r31->unk34 -= 1.0f;
            } else {
                while (var_r29 < temp_r23) {
                    if (!var_r29->unk2C) {
                        temp_f31 = temp_r30->unk24;
                        if (temp_r31->unk02 & 0x10) {
                            temp_f31 = temp_f31 * 0.9 + (s32) frandmod((u32) (temp_f31 * 0.1 * 1000.0)) / 1000.0f;
                        } else if (temp_r31->unk02 & 0x20) {
                            temp_f31 = temp_f31 * 0.7 + (s32) frandmod((u32) (temp_f31 * 0.3 * 1000.0)) / 1000.0f;
                        }
                        var_r29->unk28 = temp_f31;
                        var_r29->unk2C = temp_f31;
                        var_r29->unk34 = temp_r31->unk0C;
                        sp20.x = (s32) frandmod((u32) (temp_r30->unk08 * 2.0f)) - temp_r30->unk08;
                        sp20.y = (s32) frandmod((u32) (temp_r30->unk08 * 2.0f)) - temp_r30->unk08;
                        sp20.z = (s32) frandmod((u32) (temp_r30->unk08 * 2.0f)) - temp_r30->unk08;
                        VECNormalize(&sp20, &sp20);
                        VECScale(&sp20, &sp20, temp_r30->unk08);
                        VECAdd(&sp20, &var_r29->unk34, &var_r29->unk34);
                        VECNormalize(&temp_r31->unk18, &sp2C);
                        if (temp_r31->unk02 & 0x100) {
                            var_f28 = var_f26 + (360.0f / temp_r30->unk04) * var_r26;
                            var_f29 = temp_r30->unk0C;
                        } else {
                            var_f28 = (s32) frandmod(360);
                            if (temp_r30->unk0C) {
                                var_f29 = (s32) frandmod((u32) temp_r30->unk0C);
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
                        temp_f31 = temp_r30->unk1C;
                        if (temp_r31->unk02 & 2) {
                            temp_f31 = temp_f31 * 0.9 + (s32) frandmod((u32) (temp_f31 * 0.1 * 1000.0)) / 1000.0f;
                        } else if (temp_r31->unk02 & 4) {
                            temp_f31 = temp_f31 * 0.7 + (s32) frandmod((u32) (temp_f31 * 0.3 * 1000.0)) / 1000.0f;
                        } else if (temp_r31->unk02 & 8) {
                            temp_f31 = (s32) frandmod((u32) (temp_f31 * 1000.0f)) / 1000.0f;
                        }
                        VECScale(&sp14, &var_r29->unk08, temp_f31);
                        var_r29->unk14 = temp_r30->unk10;
                        var_r29->unk20 = temp_r30->unk20;
                        if (temp_r31->unk02 & 0x1000) {
                            var_r29->unk24 = var_r24 = temp_r31->unk08;
                        } else {
                            var_r29->unk24 = var_r24 = frandmod(temp_r30->unk2C);
                        }
                        var_r29->unk40 = temp_r30->unk2E[var_r24];
                        var_r29->unk00 = 0;
                        var_r29->unk02 = temp_r31->unk06;
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

static void ParManHook(ModelData *model, ParticleData *particle, Mtx matrix) {
    HsfanimStruct00 *temp_r26;
    ParManProcUserData *temp_r28;
    HsfanimStruct01 *var_r29;
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
        var_r29 = particle->unk_48;
        for (i = 0; i < particle->unk_30; i++, var_r29++) {
            if (var_r29->unk2C) {
                temp_r28 = parManProc[var_r29->unk02]->user_data;
                temp_r26 = temp_r28->unk3C;
                if (temp_r28->unk02 & 0x40) {
                    var_r29->unk2C = var_r29->unk28 * jitterTbl[(temp_r28->unk38 + i) & 7];
                } else {
                    var_r29->unk2C = var_r29->unk28;
                }
                if (!(temp_r28->unk02 & 0x80)) {
                    sp8 = var_r29->unk00;
                    var_r29->unk34.x += var_r29->unk08.x + var_r29->unk14.x;
                    var_r29->unk34.y += var_r29->unk08.y + var_r29->unk14.y;
                    var_r29->unk34.z += var_r29->unk08.z + var_r29->unk14.z;
                    VECScale(&var_r29->unk08, &var_r29->unk08, var_r29->unk20);
                    VECAdd(&temp_r26->unk10, &var_r29->unk14, &var_r29->unk14);
                    if (temp_r28->unk02 & 0x200) {
                        VECSubtract(&temp_r28->unk24, &var_r29->unk34, &sp1C);
                        VECNormalize(&sp1C, &sp1C);
                        VECScale(&sp1C, &sp1C, temp_r28->unk30);
                        VECAdd(&sp1C, &var_r29->unk14, &var_r29->unk14);
                        VECAdd(&var_r29->unk08, &var_r29->unk14, &sp1C);
                        VECSubtract(&temp_r28->unk24, &var_r29->unk34, &sp10);
                        temp_f29 = VECSquareMag(&sp1C);
                        if (VECSquareMag(&sp10) <= temp_f29) {
                            var_r29->unk2C = 0.0f;
                            continue;
                        }
                    }
                    var_r29->unk28 *= temp_r26->unk28;
                    var_f30 = (float) var_r29->unk00 / temp_r26->unk00;
                    if (var_f30 > 1.0f) {
                        var_f30 = 1.0f;
                    }
                    OSf32tos16(&var_r29->unk24, &temp_r31);
                    temp_r27 = &temp_r26->unk2E[temp_r31];
                    temp_r24 = &temp_r26->unk3E[temp_r31];
                    var_r29->unk40.r = temp_r27->r + var_f30 * (temp_r24->r - temp_r27->r);
                    var_r29->unk40.g = temp_r27->g + var_f30 * (temp_r24->g - temp_r27->g);
                    var_r29->unk40.b = temp_r27->b + var_f30 * (temp_r24->b - temp_r27->b);
                    var_r29->unk40.a = temp_r27->a + var_f30 * (temp_r24->a - temp_r27->a);
                    if (var_r29->unk2C < 0.01 || var_r29->unk00 >= temp_r26->unk00) {
                        var_r29->unk2C = 0.0f;
                    }
                    var_r29->unk00++;
                }
            }
        }
        temp_r28 = parManProc[particle->unk_00]->user_data;
        temp_r28->unk38++;
        DCStoreRangeNoSync(particle->unk_48, particle->unk_30 * sizeof(HsfanimStruct01));
    }
}
