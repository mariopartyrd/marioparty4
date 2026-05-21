#include "REL/m435Dll.h"
#include "game/hu3d.h"

#include "ext_math.h"
#include "string.h"

float fn_1_1526C(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg2 / arg3) * (arg1 - arg0);
}

float fn_1_15294(float arg0, float arg1, float arg2) {
    if (arg2 <= 1.0f) {
        return arg1;
    }
    return (arg1 + arg0 * (arg2 - 1.0f)) / arg2;
}

float fn_1_152D4(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * sind((90.0f / arg3) * arg2);
}

float fn_1_1539C(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * (1.0 - cosd((90.0f / arg3) * arg2));
}

void fn_1_15474(StructBss84* arg0) {
    arg0->unk04 = 0;
    arg0->unk08 = arg0->unk0C[arg0->unk00].unk08;
    arg0->unk10 = arg0->unk0C[arg0->unk00].unk00;
    arg0->unk14 = arg0->unk0C[arg0->unk00].unk04;
}

void fn_1_154C4(StructBss84* arg0, StructData3A0* arg1) {
    arg0->unk00 = 0;
    arg0->unk0C = arg1;
    fn_1_15474(arg0);
}

s32 fn_1_15520(StructBss84* arg0) {
    arg0->unk00++;
    fn_1_15474(arg0);
    if (arg0->unk10 == NULL && arg0->unk14 == NULL) {
        return 1;
    }
    return 0;
}

s32 fn_1_155A8(StructBss84* arg0) {
    arg0->unk00--;
    if (arg0->unk00 < 0) {
        return 1;
    }
    fn_1_15474(arg0);
    return 0;
}

void fn_1_1561C(StructBss84* arg0, s32 arg1) {
    arg0->unk00 = arg1;
    fn_1_15474(arg0);
}

s32 fn_1_15670(StructBss84* arg0, s32 arg1) {
    if (arg1 == 0) {
        return arg0->unk04;
    }
    arg0->unk04 += arg1;
    if (arg0->unk04 >= arg0->unk08) {
        return 1;
    }
    return 0;
}

s32 fn_1_156AC(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0->motion[arg2] == Hu3DMotionIDGet(arg0->model[0])) {
        if (arg4 != 0) {
            if (Hu3DMotionTimeGet(arg0->model[arg1]) >= arg3) {
                return 1;
            }
        } else if (Hu3DMotionTimeGet(arg0->model[arg1]) <= arg3) {
            return 1;
        }
    }
    return 0;
}

void fn_1_157BC(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    switch (arg4) {
        case 0:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, HU3D_MOTATTR_NONE);
            break;
        case 1:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, HU3D_MOTATTR_LOOP);
            break;
        case 2:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, HU3D_MOTATTR_PAUSE);
            break;
    }
}

void fn_1_15934(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0->motion[arg2] != Hu3DMotionIDGet(arg0->model[arg1]) && arg0->motion[arg2] != Hu3DMotionShiftIDGet(arg0->model[arg1])) {
        fn_1_157BC(arg0, arg1, arg2, arg3, arg4);
    }
}

void fn_1_15AFC(StructBssE08* arg0, Vec* arg1, Vec* arg2) {
    float temp_f31;
    float temp_f29;
    float temp_f30;
    float temp_f27;

    temp_f31 = arg1->x - arg2->x;
    temp_f29 = arg1->y - arg2->y;
    temp_f30 = arg1->z - arg2->z;
    arg0->unk18 = arg2->x;
    arg0->unk1C = arg2->y;
    arg0->unk20 = arg2->z;
    arg0->unk40 = sqrtf(temp_f31 * temp_f31 + temp_f29 * temp_f29 + temp_f30 * temp_f30);
    temp_f27 = atan2d(temp_f30, temp_f31);
    arg0->unk30 = -atan2d(temp_f29, temp_f31 * cosd(-temp_f27) + temp_f30 * -sind(-temp_f27));
    arg0->unk34 = -(temp_f27 - 90.0f);
    arg0->unk38 = 0.0f;
}

void fn_1_15E14(StructBssE08* arg0) {
    arg0->unk0C = arg0->unk18;
    arg0->unk10 = arg0->unk1C;
    arg0->unk14 = arg0->unk20;
    arg0->unk24 = arg0->unk30;
    arg0->unk28 = arg0->unk34;
    arg0->unk2C = arg0->unk38;
    arg0->unk3C = arg0->unk40;
}

void fn_1_15E50(StructBssE08* arg0) {
    arg0->unk44 = 0.0f;
    arg0->unk18 = arg0->unk0C;
    arg0->unk1C = arg0->unk10;
    arg0->unk20 = arg0->unk14;
    arg0->unk30 = arg0->unk24;
    arg0->unk34 = arg0->unk28;
    arg0->unk38 = arg0->unk2C;
    arg0->unk40 = arg0->unk3C;
}

void fn_1_15E9C(StructBssE08* arg0, StructBssE08* arg1, float arg2) {
    arg0->unk0C = fn_1_15294(arg0->unk0C, arg1->unk18, arg2);
    arg0->unk10 = fn_1_15294(arg0->unk10, arg1->unk1C, arg2);
    arg0->unk14 = fn_1_15294(arg0->unk14, arg1->unk20, arg2);
    arg0->unk24 = fn_1_15294(arg0->unk24, arg1->unk30, arg2);
    arg0->unk28 = fn_1_15294(arg0->unk28, arg1->unk34, arg2);
    arg0->unk2C = fn_1_15294(arg0->unk2C, arg1->unk38, arg2);
    arg0->unk3C = fn_1_15294(arg0->unk3C, arg1->unk40, arg2);
}

void fn_1_161B0(StructBssE08* arg0, float arg1) {
    fn_1_15E9C(arg0, arg0, arg1);
}

void fn_1_164C4(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3) {
    arg1->unk18 = fn_1_1526C(arg0->unk18, arg1->unk0C, arg2, arg3);
    arg1->unk1C = fn_1_1526C(arg0->unk1C, arg1->unk10, arg2, arg3);
    arg1->unk20 = fn_1_1526C(arg0->unk20, arg1->unk14, arg2, arg3);
    arg1->unk30 = fn_1_1526C(arg0->unk30, arg1->unk24, arg2, arg3);
    arg1->unk34 = fn_1_1526C(arg0->unk34, arg1->unk28, arg2, arg3);
    arg1->unk38 = fn_1_1526C(arg0->unk38, arg1->unk2C, arg2, arg3);
    arg1->unk40 = fn_1_1526C(arg0->unk40, arg1->unk3C, arg2, arg3);
}

void fn_1_16740(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3) {
    fn_1_164C4(arg0, arg1, arg2, arg3);
    arg0->unk0C = arg1->unk18;
    arg0->unk10 = arg1->unk1C;
    arg0->unk14 = arg1->unk20;
    arg0->unk24 = arg1->unk30;
    arg0->unk28 = arg1->unk34;
    arg0->unk2C = arg1->unk38;
    arg0->unk3C = arg1->unk40;
}

void fn_1_169F4(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3, float arg4) {
    fn_1_164C4(arg0, arg1, arg2, arg3);
    fn_1_15E9C(arg0, arg1, arg4);
}

void fn_1_16F24(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3) {
    arg1->unk18 = fn_1_152D4(arg0->unk18, arg1->unk0C, arg2, arg3);
    arg1->unk1C = fn_1_152D4(arg0->unk1C, arg1->unk10, arg2, arg3);
    arg1->unk20 = fn_1_152D4(arg0->unk20, arg1->unk14, arg2, arg3);
    arg1->unk30 = fn_1_152D4(arg0->unk30, arg1->unk24, arg2, arg3);
    arg1->unk34 = fn_1_152D4(arg0->unk34, arg1->unk28, arg2, arg3);
    arg1->unk38 = fn_1_152D4(arg0->unk38, arg1->unk2C, arg2, arg3);
    arg1->unk40 = fn_1_152D4(arg0->unk40, arg1->unk3C, arg2, arg3);
}

void fn_1_17378(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3) {
    fn_1_16F24(arg0, arg1, arg2, arg3);
    arg0->unk0C = arg1->unk18;
    arg0->unk10 = arg1->unk1C;
    arg0->unk14 = arg1->unk20;
    arg0->unk24 = arg1->unk30;
    arg0->unk28 = arg1->unk34;
    arg0->unk2C = arg1->unk38;
    arg0->unk3C = arg1->unk40;
}

void fn_1_17804(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3, float arg4) {
    fn_1_16F24(arg0, arg1, arg2, arg3);
    fn_1_15E9C(arg0, arg1, arg4);
}

void fn_1_17F20(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3) {
    arg1->unk18 = fn_1_1539C(arg0->unk18, arg1->unk0C, arg2, arg3);
    arg1->unk1C = fn_1_1539C(arg0->unk1C, arg1->unk10, arg2, arg3);
    arg1->unk20 = fn_1_1539C(arg0->unk20, arg1->unk14, arg2, arg3);
    arg1->unk30 = fn_1_1539C(arg0->unk30, arg1->unk24, arg2, arg3);
    arg1->unk34 = fn_1_1539C(arg0->unk34, arg1->unk28, arg2, arg3);
    arg1->unk38 = fn_1_1539C(arg0->unk38, arg1->unk2C, arg2, arg3);
    arg1->unk40 = fn_1_1539C(arg0->unk40, arg1->unk3C, arg2, arg3);
}

void fn_1_183E4(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3) {
    fn_1_17F20(arg0, arg1, arg2, arg3);
    arg0->unk0C = arg1->unk18;
    arg0->unk10 = arg1->unk1C;
    arg0->unk14 = arg1->unk20;
    arg0->unk24 = arg1->unk30;
    arg0->unk28 = arg1->unk34;
    arg0->unk2C = arg1->unk38;
    arg0->unk3C = arg1->unk40;
}

void fn_1_188E0(StructBssE08* arg0, StructBssE08* arg1, float arg2, float arg3, float arg4) {
    fn_1_17F20(arg0, arg1, arg2, arg3);
    fn_1_15E9C(arg0, arg1, arg4);
}

void fn_1_1906C(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    float var_f31;
    float var_f30;
    float temp_f29;
    float temp_f28;

    sp2C.x = arg2->x;
    sp2C.y = arg2->y;
    sp2C.z = arg2->z;
    sp20.x = arg3->x;
    sp20.y = arg3->y;
    sp20.z = arg3->z;
    var_f31 = Hu3DData[arg0->model[arg1]].rot.y;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    } else if (var_f31 >= 360.0f) {
        var_f31 -= 360.0f;
    }
    temp_f29 = arg5;
    temp_f28 = arg6;
    if (arg7 != 0) {
        sp14.x = fn_1_1526C(sp2C.x, sp20.x, temp_f29, temp_f28);
        sp14.y = fn_1_1526C(sp2C.y, sp20.y, temp_f29, temp_f28);
        sp14.z = fn_1_1526C(sp2C.z, sp20.z, temp_f29, temp_f28);
        if (arg1 == 0) {
            omSetTra(arg0, sp14.x, sp14.y, sp14.z);
        } else {
            Hu3DModelPosSet(arg0->model[arg1], sp14.x, sp14.y, sp14.z);
        }
    }
    if (arg8 == 0) {
        return;
    }
    var_f30 = -(atan2d(sp20.z - sp2C.z, sp20.x - sp2C.x) - 90.0);
    if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    } else if (var_f30 >= 360.0f) {
        var_f30 -= 360.0f;
    }
    if (var_f30 >= 180.0f) {
        if (var_f31 - var_f30 >= 180.0f) {
            var_f31 -= 360.0f;
        }
        if (var_f31 - var_f30 < -180.0f) {
            var_f31 += 360.0f;
        }
    } else {
        if (var_f31 - var_f30 > 180.0f) {
            var_f31 -= 360.0f;
        }
        if (var_f31 - var_f30 <= -180.0f) {
            var_f31 += 360.0f;
        }
    }
    var_f31 = (var_f30 + var_f31 * (arg4 - 1)) / arg4;
    if (arg1 == 0) {
        arg0->rot.y = var_f31;
    } else {
        Hu3DData[arg0->model[arg1]].rot.y = var_f31;
    }
}

void fn_1_19530(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6) {
    fn_1_1906C(arg0, arg1, arg2, arg3, 0, arg5, arg6, 1, 0);
}

void fn_1_19590(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6) {
    fn_1_1906C(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0, 1);
}

void fn_1_195F4(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6) {
    fn_1_1906C(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 1, 1);
}

void fn_1_19658(omObjData* arg0, s32 arg1, float arg2, s32 arg3) {
    float var_f31;
    float var_f30;

    var_f31 = Hu3DData[arg0->model[arg1]].rot.y;
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    } else if (var_f31 >= 360.0f) {
        var_f31 -= 360.0f;
    }
    var_f30 = arg2;
    if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    } else if (var_f30 >= 360.0f) {
        var_f30 -= 360.0f;
    }
    if (var_f30 >= 180.0f) {
        if (var_f31 - var_f30 >= 180.0f) {
            var_f31 -= 360.0f;
        }
        if (var_f31 - var_f30 < -180.0f) {
            var_f31 += 360.0f;
        }
    } else {
        if (var_f31 - var_f30 > 180.0f) {
            var_f31 -= 360.0f;
        }
        if (var_f31 - var_f30 <= -180.0f) {
            var_f31 += 360.0f;
        }
    }
    var_f31 = (var_f30 + var_f31 * (arg3 - 1)) / arg3;
    if (arg1 == 0) {
        arg0->rot.y = var_f31;
    } else {
        Hu3DData[arg0->model[arg1]].rot.y = var_f31;
    }
}

void fn_1_19894(StructFn19894* arg0, s32 arg1) {
    s32 var_r30;
    s32 i;

    var_r30 = -1;
    for (i = 0; i < 20; i++) {
        if (arg0->unk414[i] == -1) {
            var_r30 = i;
            break;
        }
    }
    if (var_r30 != -1) {
        arg0->unk414[var_r30] = arg1;
    }
}

void fn_1_198F8(StructFn19894* arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < 20; i++) {
        if (arg1 == -1) {
            arg0->unk414[i] = -1;
        } else if (arg0->unk414[i] == arg1) {
            arg0->unk414[i] = -1;
        }
    }
}

void fn_1_19960(StructFn19894* arg0, s32 arg1) {
    arg0->unk464 = arg1;
}

void fn_1_19968(StructFn19894* arg0, s32 arg1) {
    arg0->unk464 = -1;
}

void fn_1_19974(StructFn19894* arg0, s32 arg1) {
    arg0->unk04 = arg1;
}

float fn_1_1997C(s32 arg0, s32 arg1, s32 arg2) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    float var_f30;

    sp20.x = Hu3DData[arg0].pos.x;
    sp20.z = Hu3DData[arg0].pos.z;
    sp14.x = Hu3DData[arg1].pos.x;
    sp14.z = Hu3DData[arg1].pos.z;
    sp8.x = sp14.x - sp20.x;
    sp8.z = sp14.z - sp20.z;
    var_f30 = Hu3DData[arg0].rot.y;
    if (var_f30 >= 360.0f) {
        var_f30 -= 360.0f;
    } else if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    }
    if (var_f30 >= 360.0f) {
        var_f30 -= 360.0f;
    } else if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    }
    if (var_f30 >= 360.0f) {
        var_f30 -= 360.0f;
    } else if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    }
    var_f31 = atan2d(sp8.z, sp8.x) - 90.0;
    if (arg2 == 0) {
        var_f31 *= -1.0f;
    }
    if (arg2 != 0) {
        var_f31 += var_f30;
    } else {
        var_f31 -= var_f30;
    }
    if (var_f31 >= 180.0f) {
        var_f31 -= 360.0f;
    } else if (var_f31 < -180.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 >= 180.0f) {
        var_f31 -= 360.0f;
    } else if (var_f31 < -180.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 >= 180.0f) {
        var_f31 -= 360.0f;
    } else if (var_f31 < -180.0f) {
        var_f31 += 360.0f;
    }
    return var_f31;
}

float fn_1_19CC0(s32 arg0, s32 arg1) {
    Vec sp24;
    Vec sp18;
    Vec spC;

    sp24.x = Hu3DData[arg0].pos.x;
    sp24.z = Hu3DData[arg0].pos.z;
    sp18.x = Hu3DData[arg1].pos.x;
    sp18.z = Hu3DData[arg1].pos.z;
    spC.x = sp18.x - sp24.x;
    spC.z = sp18.z - sp24.z;
    return sqrtf(spC.x * spC.x + spC.z * spC.z);
}

void fn_1_19E50(omObjData* arg0) {
    StructFn19894* temp_r31;
    float var_f30;
    float var_f27;
    float var_f28;
    float var_f24;
    s32 i;

    temp_r31 = arg0->data;
    var_f30 = 0.0f;
    var_f27 = 0.0f;
    var_f28 = 0.0f;
    var_f24 = temp_r31->unk474;
    if (temp_r31->unk04 != 11) {
        if (temp_r31->unk04 == 0 || temp_r31->unk04 == 10) {
            temp_r31->unk04 = 10;
            temp_r31->unk47C = fn_1_15294(temp_r31->unk47C, 0.0f, 5.0f);
            Hu3DMotionForceSet(temp_r31->unk08, temp_r31->unk10, temp_r31->unk468, temp_r31->unk47C);
            if (temp_r31->unk410++ >= 10) {
                temp_r31->unk410 = 0;
                temp_r31->unk04 = 11;
                Hu3DMotionNoMotReset(temp_r31->unk08, temp_r31->unk10, temp_r31->unk468);
            }
            return;
        }
        if (temp_r31->unk464 >= 0) {
            var_f30 = fn_1_1997C(temp_r31->unk08, temp_r31->unk464, temp_r31->unk46C);
            if (var_f30 >= temp_r31->unk478 || var_f30 <= -temp_r31->unk478) {
                var_f30 = 0.0f;
            }
            temp_r31->unk47C = fn_1_15294(temp_r31->unk47C, var_f30, temp_r31->unk470);
        } else {
            for (i = 0; i < 20; i++) {
                if (temp_r31->unk414[i] < 0) {
                    continue;
                }
                var_f28 = fn_1_19CC0(temp_r31->unk08, temp_r31->unk414[i]);
                if (var_f28 <= temp_r31->unk474) {
                    var_f30 = fn_1_1997C(temp_r31->unk08, temp_r31->unk414[i], temp_r31->unk46C);
                    if (var_f30 <= temp_r31->unk478 && var_f30 >= -temp_r31->unk478 && var_f28 <= var_f24) {
                        var_f27 = var_f30;
                        var_f24 = var_f28;
                    }
                }
            }
            temp_r31->unk47C = fn_1_15294(temp_r31->unk47C, var_f27, temp_r31->unk470);
        }
        Hu3DMotionForceSet(temp_r31->unk08, temp_r31->unk10, temp_r31->unk468, temp_r31->unk47C);
    }
}

void fn_1_1A33C(Process* arg0, StructFn19894* arg1, s32 arg2, char* arg3, s32 arg4, s32 arg5) {
    fn_1_19974(arg1, 1);
    arg1->unk08 = arg2;
    strcpy(arg1->unk10, arg3);
    fn_1_19968(arg1, -1);
    fn_1_198F8(arg1, -1);
    arg1->unk470 = 5.0f;
    arg1->unk474 = 10000.0f;
    arg1->unk478 = 90.0f;
    arg1->unk410 = 0;
    arg1->unk47C = 0.0f;
    arg1->unk468 = arg4;
    arg1->unk46C = arg5;
    arg1->unk00 = omAddObjEx(arg0, 0x3000, 0, 0, -1, fn_1_19E50);
    arg1->unk00->data = arg1;
}
