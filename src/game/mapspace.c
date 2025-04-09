#include "game/mapspace.h"
#include "game/hsfman.h"

#include "math.h"

extern void HuSetVecF(Vec*, double, double, double);

static BOOL PolygonRangeCheck(HsfMapAttr *arg0, float arg1, float arg2, float *arg3, float arg4);
static s32 DefIfnnerMapCircle(Vec *arg0, s16 *arg1, Vec *arg2, Vec *arg3);
static s32 CalcPPLength(float *arg0, s16 *arg1, Vec *arg2);
static float MapIflnnerCalc(float arg0, float arg1, float arg2, Vec *arg3, Vec *arg4, Vec *arg5);
static float MapCalcPoint(float arg0, float arg1, float arg2, Vec *arg3, u16 *arg4);
static BOOL AreaCheck(float arg0, float arg1, u16 *arg2, Vec *arg3);
static s32 MapIflnnerTriangle(float arg0, float arg1, u16 *arg2, Vec *arg3);
static s32 MapIflnnerQuadrangle(float arg0, float arg1, u16 *arg2, Vec *arg3);
static BOOL GetPolygonCircleMtx(s16 *arg0, Vec *arg1, float *arg2, float *arg3);
static s32 PrecalcPntToTriangle(Vec *arg0, Vec *arg1, Vec *arg2, Vec* arg3, Vec *arg4, Vec *arg5);
static void DefSetHitFace(float arg0, float arg1, float arg2);

omObjData *MapObject[16];
Mtx MapMT;
Mtx MapMTR;
static Vec MTRAdd;
static Vec FieldVec;
s32 ColisionIdx[10][3];
Vec HitFaceVec[32];
static Vec OldXYZ;
Vec HitFace[32];
u8 CharObject[0x30];

float AddX;
float AddZ;
s32 nMap;
s32 nChar;
s32 HitFaceCount;
static HsfData *AttrHsf;
static Vec *topvtx;
s32 ColisionCount;

void MapWall(float arg0, float arg1, float arg2, float arg3) {
    float sp28[4];
    float sp18[4];
    float var_f31;
    float var_f30;
    float var_f29;
    omObjData *var_r25;
    ModelData *var_r26;
    HsfData *temp_r29;
    HsfMapAttr *sp14;
    HsfMapAttr *var_r31;
    s32 temp_r24;
    s32 i;
    s32 j;

    for (i = 0; i < nMap; i++) {
        var_r25 = MapObject[i];
        temp_r24 = MapObject[i]->model[0];
        sp18[0] = sp28[0] = arg1;
        sp18[1] = sp28[1] = arg2;
        sp18[2] = sp28[2] = arg3;
        sp18[3] = sp28[3] = arg0;
        var_f31 = sp28[3];
        CharRotInv(MapMT, MapMTR, (Vec*) sp18, var_r25);
        ColisionCount = 0;
        HitFaceCount = 0;
        var_r26 = &Hu3DData[temp_r24];
        temp_r29 = var_r26->hsfData;
        AttrHsf = temp_r29;
        sp14 = AttrHsf->mapAttr;
        var_r31 = temp_r29->mapAttr;
        for (j = 0; j < temp_r29->mapAttrCnt; j++, var_r31++) {
            var_f30 = sp18[0];
            var_f29 = sp18[2];
            sp18[3] = arg0;
            if (var_r31->minX <= var_f30 + var_f31 && var_r31->maxX > var_f30 - var_f31
                && var_r31->minZ <= var_f29 + var_f31 && var_r31->maxZ > var_f29 - var_f31) {
                MapWallCheck(sp28, sp18, var_r31);
            }
        }
    }
}

void MapWallCheck(float *arg0, float *arg1, HsfMapAttr *arg2) {
    u32 var_r30;
    u16 temp_r29;
    u16 *var_r31;
    s32 var_r28;
    Mtx sp10;

    var_r28 = 0;
    var_r28 = 0;
    topvtx = AttrHsf->vertex->data;
    var_r31 = arg2->data;
    MTRAdd.x = AddX;
    MTRAdd.z = AddZ;
    MTRAdd.y = 0.0f;
    MTXInvXpose(MapMT, sp10);
    MTXMultVec(sp10, &MTRAdd, &MTRAdd);
    for (var_r30 = 0; var_r30 < arg2->dataLen;) {
        temp_r29 = *var_r31;
        if (temp_r29 & 0x8000) {
            GetPolygonCircleMtx((s16*) var_r31, topvtx, arg0, arg1);
            var_r28++;
        }
        var_r30 += (temp_r29 & 0xFF) + 1;
        var_r31 += (temp_r29 & 0xFF) + 1;
    }
}

float MapPos(float arg0, float arg1, float arg2, float arg3, Vec *arg4) {
    Vec sp14;
    float var_f31;
    float var_f29;
    float sp10;
    float var_f28;
    HsfMapAttr *var_r29;
    ModelData *var_r24;
    omObjData *temp_r27;
    s32 i;
    s32 j;
    HsfData *temp_r25;
    Mtx sp20;

    var_f31 = -100000.0f;
    ColisionCount = 0;
    for (i = 0; i < nMap; i++) {
        temp_r27 = MapObject[i];
        var_r24 = &Hu3DData[*temp_r27->model];
        temp_r25 = var_r24->hsfData;
        sp14.x = arg0;
        sp14.y = arg1;
        sp14.z = arg2;
        CharRotInv(MapMT, MapMTR, &sp14, temp_r27);
        var_f29 = sp14.x;
        var_f28 = sp14.z;
        AttrHsf = temp_r25;
        var_r29 = AttrHsf->mapAttr;
        for (j = 0; j < temp_r25->mapAttrCnt; j++, var_r29++) {
            if (var_r29->minX <= var_f29 && var_r29->maxX >= var_f29
                && var_r29->minZ <= var_f28 && var_r29->maxZ >= var_f28
                && PolygonRangeCheck(var_r29, var_f29, var_f28, &sp10, arg1 + arg3) == TRUE) {
                sp14.x = var_f29;
                sp14.y = sp10;
                sp14.z = var_f28;
                MTXMultVec(MapMT, &sp14, &sp14);
                sp10 = sp14.y;
                if (sp10 > arg1 + arg3 || fabs(arg1 - sp10) > fabs(arg1 - var_f31)) {
                    continue;
                }
                var_f31 = sp10;
                arg4->x = FieldVec.x;
                arg4->y = FieldVec.y;
                arg4->z = FieldVec.z;
                MTXInvXpose(MapMT, sp20);
                MTXMultVec(sp20, arg4, arg4);
                var_f31 = sp14.y;
            }
        }
    }
    if (var_f31 == -100000.0f) {
        arg4->x = 0.0f;
        arg4->y = 1.0f;
        arg4->x = 0.0f;
        return arg1;
    } else {
        return var_f31;
    }
}

BOOL PolygonRangeCheck(HsfMapAttr *arg0, float arg1, float arg2, float *arg3, float arg4) {
    Vec sp20;
    float temp_f29;
    float var_f27;
    u16 *var_r31;
    u16 temp_r29;
    s32 var_r28;
    s32 var_r27;
    s32 i;

    var_r28 = 0;
    var_r27 = 0;
    var_f27 = 100000.0f;
    topvtx = AttrHsf->vertex->data;
    var_r31 = arg0->data;
    for (i = 0; i < arg0->dataLen;) {
        temp_r29 = *var_r31;
        if (temp_r29 & 0x8000) {
            i += (temp_r29 & 0xFF) + 1;
            var_r31 += (temp_r29 & 0xFF) + 1;
        } else {
            switch (temp_r29 & 0xFF) {
                case 1:
                    i += 2;
                    var_r31 += 2;
                    break;
                case 2:
                    i += 3;
                    var_r31 += 3;
                    break;
                case 3:
                    if (AreaCheck(arg1, arg2, var_r31, topvtx) == TRUE) {
                        var_r28++;
                        if (MapIflnnerTriangle(arg1, arg2, var_r31, topvtx) == 1) {
                            temp_f29 = MapCalcPoint(arg1, 0.0f, arg2, topvtx, var_r31);
                            sp20.x = arg1;
                            sp20.y = temp_f29;
                            sp20.z = arg2;
                            MTXMultVec(MapMT, &sp20, &sp20);
                            if (arg4 > sp20.y && var_f27 > fabs(arg4 - sp20.y)) {
                                var_f27 = fabs(arg4 - sp20.y);
                                *arg3 = temp_f29;
                                var_r27 = 1;
                            }
                        }
                    }
                    i += 4;
                    var_r31 += 4;
                    break;
                case 4:
                    if (AreaCheck(arg1, arg2, var_r31, topvtx) == TRUE) {
                        var_r28++;
                        if (MapIflnnerQuadrangle(arg1, arg2, var_r31, topvtx) == 1) {
                            temp_f29 = MapCalcPoint(arg1, 0.0f, arg2, topvtx, var_r31);
                            sp20.x = arg1;
                            sp20.y = temp_f29;
                            sp20.z = arg2;
                            MTXMultVec(MapMT, &sp20, &sp20);
                            if (arg4 > sp20.y) {
                                if (var_f27 > fabs(arg4 - sp20.y)) {
                                    var_f27 = fabs(arg4 - sp20.y);
                                    *arg3 = temp_f29;
                                    var_r27 = 1;
                                }
                            }
                        }
                    }
                    i += 5;
                    var_r31 += 5;
                    break;
                default:
                    i++;
                    var_r31++;
                    break;
            }
        }
    }
    if (var_r27 != 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static s32 DefIfnnerMapCircle(Vec *arg0, s16 *arg1, Vec *arg2, Vec *arg3) {
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float var_f31;
    s32 var_r28;
    s32 var_r27;
    s32 var_r25;

    temp_f30 = arg0->x;
    temp_f29 = arg0->y;
    temp_f28 = arg0->z;
    var_r27 = *arg1 & 0xFF;
    arg1++;
    if (var_r27 == 3) {
        var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[0]], &arg2[arg1[1]], arg3);
        if (var_f31 > 0.0f) {
            for (var_r28 = 1; var_r28 < var_r27; var_r28++) {
                var_r25 = (var_r28 + 1) % var_r27;
                var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[var_r28]], &arg2[arg1[var_r25]], arg3);
                if (var_f31 < 0.0f) {
                    return 0;
                }
            }
            return 1;
        } else {
            for (var_r28 = 1; var_r28 < var_r27; var_r28++) {
                var_r25 = (var_r28 + 1) % var_r27;
                var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[var_r28]], &arg2[arg1[var_r25]], arg3);
                if (var_f31 > 0.0f) {
                    return 0;
                }
            }
            return 1;
        }
    } else if (var_r27 == 4) {
        var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[0]], &arg2[arg1[2]], arg3);
        if (var_f31 > 0.0f) {
            var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[2]], &arg2[arg1[3]], arg3);
            if (var_f31 < 0.0f) {
                var_r27 = 1;
            } else {
                var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[3]], &arg2[arg1[0]], arg3);
                if (var_f31 < 0.0f) {
                    var_r27 = 1;
                }
            }
        } else {
            var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[2]], &arg2[arg1[3]], arg3);
            if (var_f31 > 0.0f) {
                var_r27 = 1;
            } else {
                var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[3]], &arg2[arg1[0]], arg3);
                if (var_f31 > 0.0f) {
                    var_r27 = 1;
                }
            }
        }
        if (var_r27 != 0) {
            var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[0]], &arg2[arg1[3]], arg3);
            if (var_f31 > 0.0f) {
                var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[3]], &arg2[arg1[1]], arg3);
                if (var_f31 < 0.0f) {
                    return 0;
                }
                var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[1]], &arg2[arg1[0]], arg3);
                if (var_f31 < 0.0f) {
                    return 0;
                }
            } else {
                var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[3]], &arg2[arg1[1]], arg3);
                if (var_f31 > 0.0f) {
                    return 0;
                }
                var_f31 = MapIflnnerCalc(temp_f30, temp_f29, temp_f28, &arg2[arg1[1]], &arg2[arg1[0]], arg3);
                if (var_f31 > 0.0f) {
                    return 0;
                }
            }
        }
    }
    return 0;
}

static inline void MapspaceInlineFunc00(Vec *arg0) {
    float sp24;
    float sp28;
    float sp2C;
    float sp14;

    sp24 = arg0->x;
    sp28 = arg0->y;
    sp2C = arg0->z;
    sp14 = sqrtf(sp24 * sp24 + sp28 * sp28 + sp2C * sp2C);
    if (sp14 != 0.0f) {
        arg0->x /= sp14;
        arg0->y /= sp14;
        arg0->z /= sp14;
    }
}

static inline void MapspaceInlineFunc01(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3) {
    float sp48;
    float sp4C;
    float sp50;
    float temp_f18;
    float temp_f19;
    float temp_f20;

    sp48 = arg2->x - arg1->x;
    sp4C = arg2->y - arg1->y;
    sp50 = arg2->z - arg1->z;
    temp_f18 = arg3->x - arg1->x;
    temp_f19 = arg3->y - arg1->y;
    temp_f20 = arg3->z - arg1->z;
    arg0->x = sp4C * temp_f20 - sp50 * temp_f19;
    arg0->y = sp50 * temp_f18 - sp48 * temp_f20;
    arg0->z = sp48 * temp_f19 - sp4C * temp_f18;
    MapspaceInlineFunc00(arg0);
}

static s32 CalcPPLength(float *arg0, s16 *arg1, Vec *arg2) {
    Vec *temp_r29;
    Vec sp68;
    float temp_f25;
    float temp_f24;
    float temp_f23;
    float temp_f22;
    float temp_f21;
    float sp5C;
    float sp58;
    float sp54;
    s16 temp_r24;
    s16 temp_r22;
    s32 var_r23;

    var_r23 = -1;
    temp_r24 = arg1[0];
    if (!(temp_r24 & 0x8000)) {
        return 0;
    }
    if ((temp_r24 & 0xFF) == 4) {
        MapspaceInlineFunc01(&sp68, &arg2[arg1[1]], &arg2[arg1[4]], &arg2[arg1[3]]);
    } else {
        MapspaceInlineFunc01(&sp68, &arg2[arg1[1]], &arg2[arg1[2]], &arg2[arg1[3]]);
    }
    temp_r22 = arg1[1];
    temp_r29 = &arg2[temp_r22];
    sp5C = temp_r29->x;
    sp58 = temp_r29->y;
    sp54 = temp_r29->z;
    temp_f24 = sp5C - arg0[0];
    temp_f23 = sp58 - arg0[1];
    temp_f22 = sp54 - arg0[2];
    temp_f21 = sp68.x * temp_f24 + sp68.y * temp_f23 + sp68.z * temp_f22;
    if (temp_f21 >= 0.0f) {
        var_r23 = 1;
    }
    if (fabs(temp_f21) > arg0[3]) {
        return 0;
    }
    temp_f25 = sp68.x * temp_f24 + sp68.y * temp_f23 + sp68.z * temp_f22;
    arg0[0] += sp68.x * temp_f25;
    arg0[1] += sp68.y * temp_f25;
    arg0[2] += sp68.z * temp_f25;
    return var_r23;
}

static float MapIflnnerCalc(float arg0, float arg1, float arg2, Vec *arg3, Vec *arg4, Vec *arg5) {
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    float temp_f25;

    temp_f31 = arg3->x - arg0;
    temp_f30 = arg3->y - arg1;
    temp_f29 = arg3->z - arg2;
    temp_f28 = arg4->x - arg0;
    temp_f27 = arg4->y - arg1;
    temp_f26 = arg4->z - arg2;
    temp_f25 = arg5->x * (temp_f30 * temp_f26 - temp_f29 * temp_f27)
        + arg5->y * (temp_f29 * temp_f28 - temp_f31 * temp_f26)
        + arg5->z * (temp_f31 * temp_f27 - temp_f30 * temp_f28);
    return temp_f25;
}

static float MapCalcPoint(float arg0, float arg1, float arg2, Vec *arg3, u16 *arg4) {
    Vec sp40;
    float sp3C;
    float sp38;
    float sp34;
    float sp30;
    float sp2C;
    float sp28;
    float var_f28;
    float var_f26;
    float var_f25;
    float var_f27;
    float var_f24;
    s32 temp_r27;
    Vec *temp_r30;

    temp_r27 = ColisionCount - 1;
    temp_r30 = &arg3[ColisionIdx[temp_r27][0]];
    sp34 = temp_r30->x;
    sp38 = temp_r30->y;
    sp3C = temp_r30->z;
    sp30 = arg0;
    var_f26 = arg1;
    sp2C = arg2;
    sp28 = 1.0f;
    MapspaceInlineFunc01(&sp40, &arg3[ColisionIdx[temp_r27][0]], &arg3[ColisionIdx[temp_r27][1]], &arg3[ColisionIdx[temp_r27][2]]);
    var_f25 = sp40.x;
    var_f27 = sp40.y;
    var_f24 = sp40.z;
    FieldVec.x = var_f25;
    FieldVec.y = var_f27;
    FieldVec.z = var_f24;
    var_f28 = var_f25 * (sp34 - sp30) + var_f27 * (sp38 - var_f26) + var_f24 * (sp3C - sp2C);
    var_f28 /= var_f27;
    return var_f26 + sp28 * var_f28;
}

static BOOL AreaCheck(float arg0, float arg1, u16 *arg2, Vec *arg3) {
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    s32 var_r29;
    s32 temp_r31;
    s32 i;

    var_f31 = var_f30 = -100000.0f;
    var_f29 = var_f28 = 100000.0f;
    var_r29 = *arg2 & 0xFF;
    arg2++;
    for (i = 0; i < var_r29; i++, arg2++) {
        temp_r31 = *arg2;
        if (var_f29 > arg3[temp_r31].x) {
            var_f29 = arg3[temp_r31].x;
        }
        if (var_f31 < arg3[temp_r31].x) {
            var_f31 = arg3[temp_r31].x;
        }
        if (var_f28 > arg3[temp_r31].z) {
            var_f28 = arg3[temp_r31].z;
        }
        if (var_f30 < arg3[temp_r31].z) {
            var_f30 = arg3[temp_r31].z;
        }
    }
    if (var_f29 <= arg0 && var_f31 >= arg0
        && var_f28 <= arg1 && var_f30 >= arg1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static inline float MapspaceInlineFunc02(float arg0, float arg1, Vec *arg2, Vec *arg3) {
    float sp54;
    float sp58;
    float sp5C;
    float sp60;
    float sp64;

    sp54 = arg2->x - arg0;
    sp58 = arg2->z - arg1;
    sp5C = arg3->x - arg0;
    sp60 = arg3->z - arg1;
    sp64 = -(sp58 * sp5C - sp54 * sp60);
    return sp64;
}

static s32 MapIflnnerTriangle(float arg0, float arg1, u16 *arg2, Vec *arg3) {
    Vec sp68;
    float var_f29;
    s32 var_r21;
    s32 i;

    MapspaceInlineFunc01(&sp68, &arg3[arg2[1]], &arg3[arg2[2]], &arg3[arg2[3]]);
    if (sp68.y == 0.0f) {
        return 0;
    }
    arg2++;
    var_f29 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[0]], &arg3[arg2[1]]);
    if (var_f29 > 0.0f) {
        for (i = 1; i < 3; i++) {
            var_r21 = (i + 1) % 3;
            var_f29 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[i]], &arg3[arg2[var_r21]]);
            if (var_f29 < 0.0f) {
                return 0;
            }
        }
    } else {
        for (i = 1; i < 3; i++) {
            var_r21 = (i + 1) % 3;
            var_f29 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[i]], &arg3[arg2[var_r21]]);
            if (var_f29 > 0.0f) {
                return 0;
            }
        }
    }
    ColisionIdx[ColisionCount][0] = arg2[0];
    ColisionIdx[ColisionCount][1] = arg2[1];
    ColisionIdx[ColisionCount][2] = arg2[2];
    ColisionCount++;
    return 1;
}

static s32 MapIflnnerQuadrangle(float arg0, float arg1, u16 *arg2, Vec *arg3) {
    Vec sp158;
    float var_f31;
    s32 var_r28;

    MapspaceInlineFunc01(&sp158, &arg3[arg2[1]], &arg3[arg2[2]], &arg3[arg2[3]]);
    if (sp158.y == 0.0f) {
        return 0;
    }
    var_r28 = 0;
    arg2++;
    var_f31 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[0]], &arg3[arg2[3]]);
    if (var_f31 > 0.0f) {
        var_f31 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[3]], &arg3[arg2[2]]);
        if (var_f31 < 0.0f) {
            var_r28 = 1;
        } else {
            var_f31 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[2]], &arg3[arg2[0]]);
            if (var_f31 < 0.0f) {
                var_r28 = 1;
            }
        }
    } else {
        var_f31 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[3]], &arg3[arg2[2]]);
        if (var_f31 > 0.0f) {
            var_r28 = 1;
        } else {
            var_f31 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[2]], &arg3[arg2[0]]);
            if (var_f31 > 0.0f) {
                var_r28 = 1;
            }
        }
    }
    if (var_r28 == 0) {
        ColisionIdx[ColisionCount][0] = arg2[0];
        ColisionIdx[ColisionCount][1] = arg2[3];
        ColisionIdx[ColisionCount][2] = arg2[2];
        ColisionCount++;
        return 1;
    }
    var_f31 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[0]], &arg3[arg2[1]]);
    if (var_f31 > 0.0f) {
        var_f31 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[1]], &arg3[arg2[3]]);
        if (var_f31 < 0.0f) {
            return 0;
        }
        var_f31 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[3]], &arg3[arg2[0]]);
        if (var_f31 < 0.0f) {
            return 0;
        }
    } else {
        var_f31 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[1]], &arg3[arg2[3]]);
        if (var_f31 > 0.0f) {
            return 0;
        }
        var_f31 = MapspaceInlineFunc02(arg0, arg1, &arg3[arg2[3]], &arg3[arg2[0]]);
        if (var_f31 > 0.0f) {
            return 0;
        }
    }
    ColisionIdx[ColisionCount][0] = arg2[0];
    ColisionIdx[ColisionCount][1] = arg2[1];
    ColisionIdx[ColisionCount][2] = arg2[3];
    ColisionCount++;
    return 1;
}

static inline s32 MapspaceInlineFunc03(float *spE0, s16 *temp_r31, Vec *arg1) {
    Vec spAC;
    Vec *temp_r21;
    float sp70;
    float sp74;
    float sp78;
    float sp7C;
    s16 sp8;

    MapspaceInlineFunc01(&spAC, &arg1[temp_r31[0]], &arg1[temp_r31[1]], &arg1[temp_r31[2]]);
    sp8 = temp_r31[1];
    temp_r21 = &arg1[sp8];
    sp70 = temp_r21->x;
    sp74 = temp_r21->y;
    sp78 = temp_r21->z;
    sp70 -= spE0[0];
    sp74 -= spE0[1];
    sp78 -= spE0[2];
    sp7C = spAC.x * sp70 + spAC.y * sp74 + spAC.z * sp78;
    return (sp7C < 0.0f) ? -1 : 1;
}

static BOOL GetPolygonCircleMtx(s16 *arg0, Vec *arg1, float *arg2, float *arg3) {
    Vec sp144[4];
    Vec sp120[3];
    float spE0[4];
    float spD0[4];
    float temp_f31;
    float temp_f30;
    float var_f21;
    Vec spC4;
    Vec spB8;
    s32 spA8;
    float spA4;
    s32 spA0;
    BOOL var_r17;
    s16 *temp_r31;
    Vec *temp_r29;
    Mtx spF0;

    spA8 = 0;
    spD0[0] = spE0[0] = arg3[0] + MTRAdd.x;
    spD0[1] = spE0[1] = arg3[1];
    spD0[2] = spE0[2] = arg3[2] + MTRAdd.z;
    spD0[3] = spE0[3] = arg3[3];
    temp_r31 = arg0 + 1;
    if ((spA0 = CalcPPLength(spE0, arg0, arg1)) == 0) {
        return 0;
    }
    spC4.x = spC4.y = spC4.z = 0.0f;
    if ((arg0[0] & 0xFF) == 4) {
        sp144[0].x = arg1[temp_r31[0]].x;
        sp144[0].y = arg1[temp_r31[0]].y;
        sp144[0].z = arg1[temp_r31[0]].z;
        sp144[1].x = arg1[temp_r31[1]].x;
        sp144[1].y = arg1[temp_r31[1]].y;
        sp144[1].z = arg1[temp_r31[1]].z;
        sp144[2].x = arg1[temp_r31[2]].x;
        sp144[2].y = arg1[temp_r31[2]].y;
        sp144[2].z = arg1[temp_r31[2]].z;
        sp144[3].x = arg1[temp_r31[3]].x;
        sp144[3].y = arg1[temp_r31[3]].y;
        sp144[3].z = arg1[temp_r31[3]].z;
        var_r17 = Hitcheck_Quadrangle_with_Sphere(sp144, (Vec*) spD0, spE0[3], &spC4);
    } else {
        sp120[0].x = arg1[temp_r31[0]].x;
        sp120[0].y = arg1[temp_r31[0]].y;
        sp120[0].z = arg1[temp_r31[0]].z;
        sp120[1].x = arg1[temp_r31[1]].x;
        sp120[1].y = arg1[temp_r31[1]].y;
        sp120[1].z = arg1[temp_r31[1]].z;
        sp120[2].x = arg1[temp_r31[2]].x;
        sp120[2].y = arg1[temp_r31[2]].y;
        sp120[2].z = arg1[temp_r31[2]].z;
        var_r17 = Hitcheck_Triangle_with_Sphere(sp120, (Vec*) spD0, spE0[3], &spC4);
    }
    if (var_r17 == TRUE) {
        spD0[0] = arg2[0] + AddX;
        spD0[1] = arg2[1];
        spD0[2] = arg2[2] + AddZ;
        MTXMultVec(MapMT, &spC4, &spC4);
        DefSetHitFace(spC4.x, spC4.y, spC4.z);
        temp_r29 = &HitFaceVec[HitFaceCount];
        MapspaceInlineFunc01(temp_r29, &arg1[arg0[0]], &arg1[arg0[1]], &arg1[arg0[2]]);
        temp_f31 = spC4.x - spD0[0];
        spA4 = spC4.y - spD0[1];
        temp_f30 = spC4.z - spD0[2];
        var_f21 = spE0[3] - sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30);
        HitFaceCount++;
        if (spA0 > 0) {
            spE0[0] = OldXYZ.x;
            spE0[1] = OldXYZ.y;
            spE0[2] = OldXYZ.z;
            MTXMultVec(MapMTR, (Vec*) &spE0, (Vec*) &spE0);
            if (MapspaceInlineFunc03(spE0, temp_r31, arg1) < 0) {
                spB8.x = spE0[0] - spD0[0];
                spB8.y = spE0[1] - spD0[1];
                spB8.z = spE0[2] - spD0[2];
                MapspaceInlineFunc00(&spB8);
                if (DefIfnnerMapCircle((Vec*) spD0, arg0 - 1, arg1, &spB8) == 1) {
                    var_f21 = spE0[3] + sqrtf(temp_f31 * temp_f31 + temp_f30 * temp_f30);
                }
            } else {
                var_f21 = 0.0f;
            }
        }
        if (var_f21 > 0.0f) {
            AppendAddXZ(-temp_f31, -temp_f30, var_f21);
            MTRAdd.x = AddX;
            MTRAdd.z = AddZ;
            MTRAdd.y = 0.0f;
            MTXInvXpose(MapMT, spF0);
            MTXMultVec(spF0, &MTRAdd, &MTRAdd);
        }
    }
    return var_r17;
}

static s32 PrecalcPntToTriangle(Vec *arg0, Vec *arg1, Vec *arg2, Vec* arg3, Vec *arg4, Vec *arg5) {
    Vec sp14;
    Vec sp8;
    float temp_f28;
    float temp_f30;
    float temp_f29;
    float temp_f31;

    HuSetVecF(&sp14, -arg4->x, -arg4->y, -arg4->z);
    temp_f28 = 1.0f / (-(arg1->z * arg2->y * arg3->x) + arg1->y * arg2->z * arg3->x + arg1->z * arg2->x * arg3->y - arg1->x * arg2->z * arg3->y - arg1->y * arg2->x * arg3->z + arg1->x * arg2->y * arg3->z);
    temp_f30 = temp_f28 * (arg2->z * (arg3->y * sp14.x - arg3->x * sp14.y) + arg2->y * (arg3->x * sp14.z - arg3->z * sp14.x) + arg2->x * (arg3->z * sp14.y - arg3->y * sp14.z));
    temp_f29 = temp_f28 * (arg1->z * (arg3->x * sp14.y - arg3->y * sp14.x) + arg1->y * (arg3->z * sp14.x - arg3->x * sp14.z) + arg1->x * (arg3->y * sp14.z - arg3->z * sp14.y));
    if (temp_f30 > 0.0f && temp_f29 > 0.0f && temp_f30 + temp_f29 > 1.0f) {
        VECSubtract(arg2, arg1, &sp14);
        VECSubtract(arg4, arg1, &sp8);
        temp_f31 = VECDotProduct(&sp14, &sp8) / VECDotProduct(&sp14, &sp14);
        if (temp_f31 <= 0.0f) {
            arg5 = arg1;
        } else {
            if (temp_f31 >= 1.0f) {
                arg5 = arg2;
            } else {
                VECScale(&sp14, &sp8, temp_f31);
                VECAdd(arg1, &sp8, arg5);
            }
        }
    } else if (temp_f29 < 0.0f) {
        temp_f31 = VECDotProduct(arg1, arg4) / VECDotProduct(arg1, arg1);
        if (temp_f31 <= 0.0f) {
            HuSetVecF(arg5, 0.0, 0.0, 0.0);
        } else {
            if (temp_f31 >= 1.0f) {
                arg5 = arg1;
            } else {
                VECScale(arg1, arg5, temp_f31);
            }
        }
    } else if (temp_f30 < 0.0f) {
        temp_f31 = VECDotProduct(arg2, arg4) / VECDotProduct(arg2, arg2);
        if (temp_f31 <= 0.0f) {
            HuSetVecF(arg5, 0.0, 0.0, 0.0);
        } else {
            if (temp_f31 >= 1.0f) {
                arg5 = arg2;
            } else {
                VECScale(arg2, arg5, temp_f31);
            }
        }
    } else {
        HuSetVecF(arg5, temp_f30 * arg1->x + temp_f29 * arg2->x, temp_f30 * arg1->y + temp_f29 * arg2->y, temp_f30 * arg1->z + temp_f29 * arg2->z);
    }
    return 1;
}

BOOL Hitcheck_Triangle_with_Sphere(Vec *arg0, Vec *arg1, float arg2, Vec *arg3) {
    Vec sp48;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    float var_f31;

    sp48.x = arg0[0].x;
    sp48.y = arg0[0].y;
    sp48.z = arg0[0].z;
    VECSubtract(&arg0[1], &arg0[0], &sp3C);
    VECSubtract(&arg0[2], &arg0[0], &sp30);
    VECCrossProduct(&sp3C, &sp30, &sp24);
    VECSubtract(arg1, &arg0[0], &sp18);
    PrecalcPntToTriangle(&sp48, &sp3C, &sp30, &sp24, &sp18, &spC);
    VECAdd(&spC, &sp48, arg3);
    var_f31 = VECDistance(arg3, arg1);
    if (var_f31 > arg2) {
        return FALSE;
    } else {
        return TRUE;
    }
}

BOOL Hitcheck_Quadrangle_with_Sphere(Vec *arg0, Vec *arg1, float arg2, Vec *arg3) {
    Vec sp6C;
    Vec sp60;
    Vec sp54;
    Vec sp48;
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    Vec spC;
    float temp_f30;
    float var_f31;

    sp6C.x = arg0->x;
    sp6C.y = arg0->y;
    sp6C.z = arg0->z;
    VECSubtract(&arg0[2], &arg0[0], &sp60);
    VECSubtract(&arg0[3], &arg0[0], &sp54);
    VECSubtract(&arg0[1], &arg0[0], &sp48);
    VECCrossProduct(&sp60, &sp54, &sp3C);
    VECSubtract(arg1, &arg0[0], &sp30);
    PrecalcPntToTriangle(&sp6C, &sp60, &sp54, &sp3C, &sp30, &sp24);
    VECAdd(&sp24, &sp6C, &sp18);
    PrecalcPntToTriangle(&sp6C, &sp54, &sp48, &sp3C, &sp30, &sp24);
    VECAdd(&sp24, &sp6C, &spC);
    var_f31 = VECDistance(&sp18, arg1);
    temp_f30 = VECDistance(&spC, arg1);
    if (temp_f30 > var_f31) {
        arg3->x = sp18.x;
        arg3->y = sp18.y;
        arg3->z = sp18.z;
    } else {
        var_f31 = temp_f30;
        arg3->x = spC.x;
        arg3->y = spC.y;
        arg3->z = spC.z;
    }
    if (var_f31 > arg2) {
        return FALSE;
    } else {
        return TRUE;
    }
}

static void DefSetHitFace(float arg0, float arg1, float arg2) {
    HitFace[HitFaceCount].x = arg0;
    HitFace[HitFaceCount].y = arg1;
    HitFace[HitFaceCount].z = arg2;
}

void AppendAddXZ(float arg0, float arg1, float arg2) {
    Vec spC;

    spC.x = arg0;
    spC.y = 0.0f;
    spC.z = arg1;
    MapspaceInlineFunc00(&spC);
    AddX += spC.x * arg2;
    AddZ += spC.z * arg2;
}

void CharRotInv(Mtx arg0, Mtx arg1, Vec *arg2, omObjData *arg3) {
    Mtx sp8;

    MTXTrans(arg0, arg3->trans.x, arg3->trans.y, arg3->trans.z);
    if (arg3->rot.z) {
        MTXRotRad(sp8, 'z', MTXDegToRad(arg3->rot.z));
        MTXConcat(arg0, sp8, arg0);
    }
    if (arg3->rot.y) {
        MTXRotRad(sp8, 'y', MTXDegToRad(arg3->rot.y));
        MTXConcat(arg0, sp8, arg0);
    }
    if (arg3->rot.x) {
        MTXRotRad(sp8, 'x', MTXDegToRad(arg3->rot.x));
        MTXConcat(arg0, sp8, arg0);
    }
    MTXInverse(arg0, arg1);
    MTXMultVec(arg1, arg2, arg2);
}
