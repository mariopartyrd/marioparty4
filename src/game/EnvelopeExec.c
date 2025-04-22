#include "game/EnvelopeExec.h"
#include "game/hsfex.h"

#include "string.h"

static void SetEnvelopMtx(HsfObject *arg0, HsfObject *arg1, Mtx arg2);
static void SetEnvelopMain(HsfData *arg0);
static void SetEnvelop(HsfCenv *arg0);
static void SetMtx(HsfObject *arg0, Mtx arg1);
static void SetRevMtx(void);
static HsfSkeleton *SearchSklenton(char *arg0);

Vec *Vertextop;
Mtx *MtxTop;
static u32 nObj;
static u32 nMesh;
static HsfObject *objtop;
static HsfData *CurHsf;
static Vec *vtxenv;
static Vec *normenv;
static Vec *normtop;
static s32 Meshcnt;
static s32 Meshno;

void InitEnvelope(HsfData *arg0) {
    HsfBuffer *spC;
    HsfBuffer *sp8;
    HsfMatrix *temp_r28;
    HsfObject *var_r31;
    HsfSkeleton *var_r30;
    Mtx sp10;
    s32 i;
    s32 j;

    if (arg0->cenvCnt != 0) {
        var_r31 = arg0->object;
        for (Meshcnt = i = 0; i < arg0->objectCnt; i++, var_r31++) {
            if (var_r31->type == 2) {
                if (var_r31->data.vtxtop) {
                    spC = var_r31->data.vertex;
                    sp8 = var_r31->data.normal;
                    Meshcnt++;
                } else {
                    continue;
                }
            }
            var_r30 = arg0->skeleton;
            for (j = 0; j < arg0->skeletonCnt; j++, var_r30++) {
                if (strcmp(var_r31->name, var_r30->name) == 0) {
                    var_r31->data.base.pos.x = var_r30->transform.pos.x;
                    var_r31->data.base.pos.y = var_r30->transform.pos.y;
                    var_r31->data.base.pos.z = var_r30->transform.pos.z;
                    var_r31->data.base.rot.x = var_r30->transform.rot.x;
                    var_r31->data.base.rot.y = var_r30->transform.rot.y;
                    var_r31->data.base.rot.z = var_r30->transform.rot.z;
                    var_r31->data.base.scale.x = var_r30->transform.scale.x;
                    var_r31->data.base.scale.y = var_r30->transform.scale.y;
                    var_r31->data.base.scale.z = var_r30->transform.scale.z;
                }
            }
            var_r31->data.curr.pos.x = var_r31->data.base.pos.x;
            var_r31->data.curr.pos.y = var_r31->data.base.pos.y;
            var_r31->data.curr.pos.z = var_r31->data.base.pos.z;
            var_r31->data.curr.rot.x = var_r31->data.base.rot.x;
            var_r31->data.curr.rot.y = var_r31->data.base.rot.y;
            var_r31->data.curr.rot.z = var_r31->data.base.rot.z;
            var_r31->data.curr.scale.x = var_r31->data.base.scale.x;
            var_r31->data.curr.scale.y = var_r31->data.base.scale.y;
            var_r31->data.curr.scale.z = var_r31->data.base.scale.z;
        }
        CurHsf = arg0;
        objtop = arg0->object;
        temp_r28 = CurHsf->matrix;
        if (temp_r28) {
            MtxTop = temp_r28->data;
            nObj = temp_r28->count;
            nMesh = temp_r28->base_idx;
        }
        MTXIdentity(sp10);
        SetMtx(arg0->root, sp10);
        SetRevMtx();
    }
}

static void SetEnvelopMtx(HsfObject *arg0, HsfObject *arg1, Mtx arg2) {
    Mtx sp6C;
    Mtx sp3C;
    Mtx spC;
    s32 var_r29;
    s32 i;

    MTXTrans(spC, arg1->data.curr.pos.x, arg1->data.curr.pos.y, arg1->data.curr.pos.z);
    MTXConcat(arg2, spC, sp3C);
    if (arg1->data.curr.rot.z) {
        MTXRotRad(sp6C, 'z', MTXDegToRad(arg1->data.curr.rot.z));
        MTXConcat(sp3C, sp6C, sp3C);
    }
    if (arg1->data.curr.rot.y) {
        MTXRotRad(sp6C, 'y', MTXDegToRad(arg1->data.curr.rot.y));
        MTXConcat(sp3C, sp6C, sp3C);
    }
    if (arg1->data.curr.rot.x) {
        MTXRotRad(sp6C, 'x', MTXDegToRad(arg1->data.curr.rot.x));
        MTXConcat(sp3C, sp6C, sp3C);
    }
    if (arg1->data.curr.scale.x != 1.0f) {
        sp3C[0][0] *= arg1->data.curr.scale.x;
        sp3C[1][0] *= arg1->data.curr.scale.x;
        sp3C[2][0] *= arg1->data.curr.scale.x;
    }
    if (arg1->data.curr.scale.y != 1.0f) {
        sp3C[0][1] *= arg1->data.curr.scale.y;
        sp3C[1][1] *= arg1->data.curr.scale.y;
        sp3C[2][1] *= arg1->data.curr.scale.y;
    }
    if (arg1->data.curr.scale.z != 1.0f) {
        sp3C[0][2] *= arg1->data.curr.scale.z;
        sp3C[1][2] *= arg1->data.curr.scale.z;
        sp3C[2][2] *= arg1->data.curr.scale.z;
    }
    var_r29 = arg1 - arg0;
    MTXCopy(sp3C, MtxTop[nMesh + var_r29]);
    for (i = 0; i < arg1->data.childrenCount; i++) {
        SetEnvelopMtx(arg0, arg1->data.children[i], sp3C);
    }
}

void EnvelopeProc(HsfData *arg0) {
    HsfMatrix *temp_r31;
    HsfObject *temp_r29;
    Mtx sp8;

    CurHsf = arg0;
    temp_r31 = CurHsf->matrix;
    MtxTop = temp_r31->data;
    nObj = temp_r31->count;
    nMesh = temp_r31->base_idx;
    temp_r29 = arg0->root;
    MTXIdentity(sp8);
    SetEnvelopMtx(arg0->object, temp_r29, sp8);
    SetEnvelopMain(arg0);
}

void InitVtxParm(HsfData *arg0) {
    HsfObject *var_r31;
    s32 i;

    var_r31 = arg0->object;
    for (i = 0; i < arg0->objectCnt; i++, var_r31++) {
        if (var_r31->type == 2) {
            var_r31->data.unk120[0] = 0;
        }
    }
}

static void SetEnvelopMain(HsfData *arg0) {
    void *sp10;
    void *spC;
    void *sp8;
    HsfBuffer *temp_r28;
    HsfBuffer *temp_r30;
    HsfObject *var_r31;
    s32 i;
    s32 j;
    HsfCenv *var_r25;

    var_r31 = arg0->object;
    for (Meshno = i = 0; i < arg0->objectCnt; i++, var_r31++) {
        if (var_r31->type == 2) {
            MTXInverse(MtxTop[&var_r31[nMesh] - arg0->object], MtxTop[Meshno]);
            temp_r30 = var_r31->data.vertex;
            temp_r28 = var_r31->data.normal;
            if (var_r31->data.unk120[0] != 0) {
                Vertextop = temp_r30->data;
            } else {
                Vertextop = (Vec*)var_r31->data.vtxtop;
            }
            vtxenv = temp_r30->data;
            normtop = (Vec*)var_r31->data.normtop;
            normenv = temp_r28->data;
            var_r25 = var_r31->data.cenv;
            for (j = 0; j < var_r31->data.cenvCnt; j++, var_r25++) {
                SetEnvelop(var_r25);
            }
            sp10 = temp_r30->data;
            spC = var_r31->data.vtxtop;
            sp8 = temp_r30->data;
            DCStoreRangeNoSync(normenv, temp_r28->count * sizeof(Vec));
            DCStoreRangeNoSync(vtxenv, temp_r30->count * sizeof(Vec));
            Meshno++;
        }
    }
}

static void SetEnvelop(HsfCenv *arg0) {
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    s32 sp10;
    u32 spC;
    u32 sp8;
    HsfCenvDual *var_r20;
    HsfCenvDualWeight *var_r30;
    HsfCenvMulti *var_r19;
    HsfCenvMultiWeight *var_r25;
    HsfCenvSingle *var_r27;
    Vec *temp_r22;
    Vec *temp_r26;
    Vec *temp_r28;
    Vec *temp_r31;
    float temp_f31;
    MtxPtr var_r29;
    s32 temp_r18;
    s32 temp_r21;
    s32 i;
    s32 j;
    Mtx sp1A0;
    Mtx sp170;
    Mtx sp140;
    Mtx sp110;
    Mtx spE0;
    Mtx spB0;
    Mtx sp80;
    Mtx sp50;

    var_r27 = arg0->singleData;
    for (i = 0; i < arg0->singleCount; i++, var_r27++) {
        temp_r18 = var_r27->normal;
        temp_r21 = var_r27->pos;
        temp_r28 = &vtxenv[temp_r21];
        temp_r31 = &Vertextop[temp_r21];
        temp_r22 = &normenv[temp_r18];
        temp_r26 = &normtop[temp_r18];
        MTXConcat(MtxTop[nMesh + var_r27->target], MtxTop[nMesh + nObj + nObj * Meshno + var_r27->target], sp140);
        MTXConcat(MtxTop[Meshno], sp140, sp1A0);
        Hu3DMtxScaleGet(&sp1A0[0], &sp14);
        if (sp14.x != 1.0f || sp14.y != 1.0f || sp14.z != 1.0f) {
            MTXScale(spE0, 1.0 / sp14.x, 1.0 / sp14.y, 1.0 / sp14.z);
            MTXConcat(spE0, sp1A0, sp170);
            MTXInvXpose(sp170, sp170);
        } else {
            MTXInvXpose(sp1A0, sp170);
        }
        if (var_r27->posCnt == 1) {
            MTXMultVec(sp1A0, temp_r31, temp_r28);
            MTXMultVec(sp170, temp_r26, temp_r22);
        } else if (var_r27->posCnt <= 6) {
            MTXMultVecArray(sp1A0, temp_r31, temp_r28, var_r27->posCnt);
            MTXMultVecArray(sp170, temp_r26, temp_r22, var_r27->normalCnt);
        } else {
            MTXReorder(sp1A0, (ROMtxPtr) sp140);
            MTXReorder(sp170, (ROMtxPtr) sp110);
            MTXROMultVecArray((ROMtxPtr) sp140, temp_r31, temp_r28, var_r27->posCnt);
            MTXROMultVecArray((ROMtxPtr) sp110, temp_r26, temp_r22, var_r27->normalCnt);
        }
    }
    var_r20 = arg0->dualData;
    for (i = 0; i < arg0->dualCount; i++, var_r20++) {
        spC = var_r20->target1;
        sp8 = var_r20->target2;
        MTXConcat(MtxTop[nMesh + spC], MtxTop[nMesh + nObj + nObj * Meshno + spC], sp140);
        MTXConcat(MtxTop[Meshno], sp140, sp1A0);
        MTXConcat(MtxTop[nMesh + sp8], MtxTop[nMesh + nObj + nObj * Meshno + sp8], sp140);
        MTXConcat(MtxTop[Meshno], sp140, (float (*)[4]) &spB0[0]);
        var_r30 = var_r20->weight;
        for (j = 0; j < var_r20->weightCnt; j++, var_r30++) {
            temp_r18 = var_r30->normal;
            temp_r21 = var_r30->pos;
            temp_r28 = &vtxenv[temp_r21];
            temp_r31 = &Vertextop[temp_r21];
            temp_r22 = &normenv[temp_r18];
            temp_r26 = &normtop[temp_r18];
            temp_f31 = var_r30->weight;
            sp140[0][0] = sp1A0[0][0] * temp_f31;
            sp140[1][0] = sp1A0[1][0] * temp_f31;
            sp140[2][0] = sp1A0[2][0] * temp_f31;
            sp140[0][1] = sp1A0[0][1] * temp_f31;
            sp140[1][1] = sp1A0[1][1] * temp_f31;
            sp140[2][1] = sp1A0[2][1] * temp_f31;
            sp140[0][2] = sp1A0[0][2] * temp_f31;
            sp140[1][2] = sp1A0[1][2] * temp_f31;
            sp140[2][2] = sp1A0[2][2] * temp_f31;
            sp140[0][3] = sp1A0[0][3] * temp_f31;
            sp140[1][3] = sp1A0[1][3] * temp_f31;
            sp140[2][3] = sp1A0[2][3] * temp_f31;
            temp_f31 = 1.0f - var_r30->weight;
            sp110[0][0] = spB0[0][0] * temp_f31;
            sp110[1][0] = spB0[1][0] * temp_f31;
            sp110[2][0] = spB0[2][0] * temp_f31;
            sp110[0][1] = spB0[0][1] * temp_f31;
            sp110[1][1] = spB0[1][1] * temp_f31;
            sp110[2][1] = spB0[2][1] * temp_f31;
            sp110[0][2] = spB0[0][2] * temp_f31;
            sp110[1][2] = spB0[1][2] * temp_f31;
            sp110[2][2] = spB0[2][2] * temp_f31;
            sp110[0][3] = spB0[0][3] * temp_f31;
            sp110[1][3] = spB0[1][3] * temp_f31;
            sp110[2][3] = spB0[2][3] * temp_f31;
            if (sp80 == sp110 || sp80 == sp140) {
                var_r29 = sp50;
            } else {
                var_r29 = sp80;
            }
            var_r29[0][0] = sp110[0][0] + sp140[0][0];
            var_r29[0][1] = sp110[0][1] + sp140[0][1];
            var_r29[0][2] = sp110[0][2] + sp140[0][2];
            var_r29[0][3] = sp110[0][3] + sp140[0][3];
            var_r29[1][0] = sp110[1][0] + sp140[1][0];
            var_r29[1][1] = sp110[1][1] + sp140[1][1];
            var_r29[1][2] = sp110[1][2] + sp140[1][2];
            var_r29[1][3] = sp110[1][3] + sp140[1][3];
            var_r29[2][0] = sp110[2][0] + sp140[2][0];
            var_r29[2][1] = sp110[2][1] + sp140[2][1];
            var_r29[2][2] = sp110[2][2] + sp140[2][2];
            var_r29[2][3] = sp110[2][3] + sp140[2][3];
            if (var_r29 == sp50) {
                MTXCopy(sp50, sp80);
            }
            Hu3DMtxScaleGet(&sp80[0], &sp14);
            if (sp14.x != 1.0f || sp14.y != 1.0f || sp14.z != 1.0f) {
                MTXScale(spE0, 1.0 / sp14.x, 1.0 / sp14.y, 1.0 / sp14.z);
                MTXConcat(spE0, sp80, sp110);
                MTXInvXpose(sp110, sp110);
            } else {
                MTXInvXpose(sp80, sp110);
            }
            if (var_r30->posCnt == 1) {
                MTXMultVec(sp80, temp_r31, temp_r28);
            } else if (var_r30->posCnt <= 6) {
                MTXMultVecArray(sp80, temp_r31, temp_r28, var_r30->posCnt);
            } else {
                MTXReorder(sp80, (ROMtxPtr) sp140);
                MTXROMultVecArray((ROMtxPtr) sp140, temp_r31, temp_r28, var_r30->posCnt);
            }
            if (var_r30->normalCnt != 0) {
                if (var_r30->normalCnt == 1) {
                    MTXMultVec(sp110, temp_r26, temp_r22);
                } else if (var_r30->normalCnt <= 6) {
                    MTXMultVecArray(sp110, temp_r26, temp_r22, var_r30->normalCnt);
                } else {
                    MTXReorder(sp110, (ROMtxPtr) sp140);
                    MTXROMultVecArray((ROMtxPtr) sp140, temp_r26, temp_r22, var_r30->normalCnt);
                }
            }
        }
    }
    var_r19 = arg0->multiData;
    for (i = 0; i < arg0->multiCount; i++, var_r19++) {
        var_r25 = var_r19->weight;
        temp_r18 = var_r19->normal;
        temp_r21 = var_r19->pos;
        temp_r28 = &vtxenv[temp_r21];
        temp_r31 = &Vertextop[temp_r21];
        temp_r22 = &normenv[temp_r18];
        temp_r26 = &normtop[temp_r18];
        sp38.x = sp38.y = sp38.z = 0.0f;
        sp20.x = sp20.y = sp20.z = 0.0f;
        sp10 = 0;
        for (j = 0; j < var_r19->weightCnt; j++, var_r25++) {
            MTXConcat(MtxTop[nMesh + var_r25->target], MtxTop[nMesh + nObj + nObj * Meshno + var_r25->target], sp1A0);
            MTXConcat(MtxTop[Meshno], sp1A0, sp1A0);
            MTXInvXpose(sp1A0, sp170);
            MTXMultVec(sp1A0, temp_r31, &sp44);
            MTXMultVec(sp170, temp_r26, &sp2C);
            sp44.x = var_r25->value * (sp44.x - temp_r31->x);
            sp44.y = var_r25->value * (sp44.y - temp_r31->y);
            sp44.z = var_r25->value * (sp44.z - temp_r31->z);
            VECAdd(&sp38, &sp44, &sp38);
            sp2C.x = var_r25->value * (sp2C.x - temp_r26->x);
            sp2C.y = var_r25->value * (sp2C.y - temp_r26->y);
            sp2C.z = var_r25->value * (sp2C.z - temp_r26->z);
            VECAdd(&sp20, &sp2C, &sp20);
        }
        temp_r28->x = temp_r31->x + sp38.x;
        temp_r28->y = temp_r31->y + sp38.y;
        temp_r28->z = temp_r31->z + sp38.z;
        temp_r22->x = temp_r26->x + sp20.x;
        temp_r22->y = temp_r26->y + sp20.y;
        temp_r22->z = temp_r26->z + sp20.z;
    }
    temp_r21 = arg0->vtxCount;
    temp_r28 = &vtxenv[temp_r21];
    temp_r31 = &Vertextop[temp_r21];
    for (i = 0; i < arg0->copyCount; i++, temp_r28++, temp_r31++) {
        temp_r28->x = temp_r31->x;
        temp_r28->y = temp_r31->y;
        temp_r28->z = temp_r31->z;
    }
}

static void SetMtx(HsfObject *arg0, Mtx arg1) {
    HsfSkeleton *temp_r3;
    Mtx spFC;
    Mtx spCC;
    Mtx sp9C;
    s32 temp_r25;
    s32 i;

    temp_r3 = SearchSklenton(arg0->name);
    if (temp_r3) {
        arg0->data.base.pos.x = temp_r3->transform.pos.x;
        arg0->data.base.pos.y = temp_r3->transform.pos.y;
        arg0->data.base.pos.z = temp_r3->transform.pos.z;
        arg0->data.base.rot.x = temp_r3->transform.rot.x;
        arg0->data.base.rot.y = temp_r3->transform.rot.y;
        arg0->data.base.rot.z = temp_r3->transform.rot.z;
        arg0->data.base.scale.x = temp_r3->transform.scale.x;
        arg0->data.base.scale.y = temp_r3->transform.scale.y;
        arg0->data.base.scale.z = temp_r3->transform.scale.z;
    }
    MTXTrans(spFC, arg0->data.base.pos.x, arg0->data.base.pos.y, arg0->data.base.pos.z);
    MTXScale(spCC, arg0->data.base.scale.x, arg0->data.base.scale.y, arg0->data.base.scale.z);
    MTXConcat(arg1, spFC, spFC);
    MTXRotRad(sp9C, 'z', MTXDegToRad(arg0->data.base.rot.z));
    MTXConcat(spFC, sp9C, spFC);
    MTXRotRad(sp9C, 'y', MTXDegToRad(arg0->data.base.rot.y));
    MTXConcat(spFC, sp9C, spFC);
    MTXRotRad(sp9C, 'x', MTXDegToRad(arg0->data.base.rot.x));
    MTXConcat(spFC, sp9C, spFC);
    MTXConcat(spFC, spCC, spFC);
    temp_r25 = arg0 - objtop;
    MTXCopy(spFC, MtxTop[nMesh + temp_r25]);
    for (i = 0; i < arg0->data.childrenCount; i++) {
        SetMtx(arg0->data.children[i], spFC);
    }
}

static void SetRevMtx(void) {
    HsfObject *var_r29;
    s32 var_r28;
    s32 i;
    s32 var_r30;
    Mtx sp38;
    Mtx sp8;

    var_r29 = CurHsf->object;
    for (var_r28 = i = 0; i < CurHsf->objectCnt; i++, var_r29++) {
        if (var_r29->type == 2) {
            MTXCopy(MtxTop[nMesh + i], sp8);
            for (var_r30 = 0; var_r30 < CurHsf->objectCnt; var_r30++) {
                MTXInverse(MtxTop[nMesh + var_r30], sp38);
                MTXConcat(sp38, sp8, MtxTop[nMesh + nObj + nObj * var_r28 + var_r30]);
            }
            MTXInverse(MtxTop[nMesh + i], sp8);
            var_r28++;
        }
    }
}

static HsfSkeleton *SearchSklenton(char *arg0) {
    HsfSkeleton *var_r31;
    s32 i;

    var_r31 = CurHsf->skeleton;
    for (i = 0; i < CurHsf->skeletonCnt; i++, var_r31++) {
        if (strcmp(arg0, var_r31->name) == 0) {
            return var_r31;
        }
    }
    return NULL;
}
