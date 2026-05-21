#include "REL/m437Dll.h"
#include "game/hu3d.h"

#include "ext_math.h"
#include "string.h"

void fn_1_11618(StructBss50* arg0);
s32 fn_1_1174C(StructBss50* arg0);
void fn_1_12494(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void fn_1_12958(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6);
void fn_1_129B8(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6);
void fn_1_12A1C(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6);
void fn_1_12A80(StructBss160* arg0);
void fn_1_12B00(StructBss160* arg0, StructBss160* arg1, float arg2);
void fn_1_13128(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3);
void fn_1_133A4(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3);
void fn_1_13B88(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3);
void fn_1_13FDC(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3);
void fn_1_14468(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3, float arg4);
void fn_1_14B84(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3);
void fn_1_15048(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3);
void fn_1_15D3C(StructFn15CD0* arg0, s32 arg1);
void fn_1_15DA4(StructFn15CD0* arg0, s32 arg1);
void fn_1_15DB4(StructFn15CD0* arg0);
void fn_1_15DC0(StructFn15CD0* arg0, s32 arg1);
float fn_1_15E10(s32 arg0, s32 arg1, s32 arg2);
float fn_1_16154(s32 arg0, s32 arg1);
float fn_1_162E4(s32 arg0, float arg1, float arg2);
void fn_1_16348(omObjData* arg0);
void fn_1_1634C(Process* arg0, StructFn15CD0* arg1, s32 arg2, const char* arg3, s32 arg4, s32 arg5);

const char* lbl_1_data_3D0[] = {
    "c000m1-ske_head",
    "c001m1-ske_head",
    "c002m1-ske_head",
    "c003m1-ske_head",
    "c004m1-ske_head",
    "c005m1-ske_head",
    "c006m1-ske_head",
    "c007m1-ske_head"
};

s32 lbl_1_data_3F0[][2] = {
    { 0x100, 1 },
    { 0x100, 1 },
    {  0x80, 0 },
    {  0x80, 0 },
    {  0x80, 0 },
    { 0x100, 1 },
    {  0x80, 0 },
    {  0x80, 0 }
};

// Similar to mgmodedll/main.c::fn_1_240E4 (identical in behavior)
float fn_1_11348(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg2 / arg3) * (arg1 - arg0);
}

float fn_1_11370(float arg0, float arg1, float arg2) {
    if (arg2 <= 1.0f) {
        return arg1;
    }
    return (arg1 + arg0 * (arg2 - 1.0f)) / arg2;
}

// Identical to mgmodedll/main.c::fn_1_24204
float fn_1_113B0(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * sind((90.0f / arg3) * arg2);
}

// Identical to mgmodedll/main.c::fn_1_242CC
float fn_1_11478(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * sind((360.0f / arg3) * arg2);
}

// Identical to mgmodedll/main.c::fn_1_2412C
float fn_1_11540(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * (1.0 - cosd((90.0f / arg3) * arg2));
}

void fn_1_11618(StructBss50* arg0) {
    arg0->unk10 = 0;
    arg0->unk14 = arg0->unk04[arg0->unk00].unk08;
    arg0->unk08 = arg0->unk04[arg0->unk00].unk00;
    arg0->unk0C = arg0->unk04[arg0->unk00].unk04;
}

void fn_1_11668(StructBss50* arg0, StructData204* arg1) {
    arg0->unk00 = 0;
    arg0->unk04 = arg1;
    fn_1_11618(arg0);
}

s32 fn_1_116C4(StructBss50* arg0) {
    arg0->unk00++;
    fn_1_11618(arg0);
    if (arg0->unk08 == NULL && arg0->unk0C == NULL) {
        return 1;
    }
    return 0;
}

s32 fn_1_1174C(StructBss50* arg0) {
    arg0->unk00--;
    if (arg0->unk00 < 0) {
        return 1;
    }
    fn_1_11618(arg0);
    return 0;
}

s32 fn_1_117C0(StructBss50* arg0, s32 arg1) {
    arg0->unk00 = arg1;
    if (arg0->unk00 < 0) {
        return 1;
    }
    fn_1_11618(arg0);
    if (arg0->unk08 == NULL && arg0->unk0C == NULL) {
        return 1;
    }
    return 0;
}

s32 fn_1_11854(StructBss50* arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0->unk10 += arg1;
        if (arg0->unk10 >= arg0->unk14) {
            return 1;
        }
    } else {
        return arg0->unk10;
    }
    return 0;
}

s32 fn_1_11890(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
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

void fn_1_119A0(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
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

void fn_1_11B18(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0->motion[arg2] != Hu3DMotionIDGet(arg0->model[arg1]) && arg0->motion[arg2] != Hu3DMotionShiftIDGet(arg0->model[arg1])) {
        fn_1_119A0(arg0, arg1, arg2, arg3, arg4);
    }
}

s32 fn_1_11CE0(omObjData* arg0, Vec arg1, float arg2, float arg3, float arg4, float arg5, s32 arg6) {
    float var_f31;
    float var_f30;
    float var_f26;
    float var_f27;

    var_f31 = arg1.x - arg0->trans.x;
    var_f30 = arg0->trans.z - arg1.z;
    var_f26 = 90.0 + atan2d(var_f30, var_f31);
    var_f27 = sqrtf(var_f31 * var_f31 + var_f30 * var_f30);
    if (var_f27 <= arg4) {
        var_f31 = var_f30 = 0.0f;
    } else {
        var_f31 = 72.0f * (var_f31 / var_f27);
        var_f30 = 72.0f * (var_f30 / var_f27);
    }
    var_f27 = arg3 * (sqrtf(var_f31 * var_f31 + var_f30 * var_f30) / 72.0f);
    if (var_f27 >= arg3) {
        var_f27 = arg3;
    } else if (var_f27 <= 1.0f) {
        var_f31 = var_f30 = var_f27 = 0.0f;
    }
    if (var_f31 != 0.0f || var_f30 != 0.0f || arg2 >= 0.0f) {
        if (arg2 >= 0.0f && var_f31 == 0.0f && var_f30 == 0.0f) {
            var_f26 = arg2;
        }
        if (var_f26 >= 180.0f) {
            if (arg0->rot.y - var_f26 >= 180.0f) {
                arg0->rot.y -= 360.0f;
            }
            if (arg0->rot.y - var_f26 < -180.0f) {
                arg0->rot.y += 360.0f;
            }
        } else {
            if (arg0->rot.y - var_f26 > 180.0f) {
                arg0->rot.y -= 360.0f;
            }
            if (arg0->rot.y - var_f26 <= -180.0f) {
                arg0->rot.y += 360.0f;
            }
        }
        arg0->rot.y = (var_f26 + arg0->rot.y * (arg5 - 1.0f)) / arg5;
    }
    arg0->trans.x += var_f27 * sind(arg0->rot.y);
    arg0->trans.z += var_f27 * cosd(arg0->rot.y);
    if (arg6 != 0) {
        if (var_f27 > 0.0f) {
            if (arg6 == 1 || arg6 == 3) {
                if (arg0->motion[1] != Hu3DMotionIDGet(arg0->model[0]) && arg0->motion[1] != Hu3DMotionShiftIDGet(arg0->model[0])) {
                    Hu3DMotionShiftSet(arg0->model[0], arg0->motion[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                }
            } else if (arg0->motion[10] != Hu3DMotionIDGet(arg0->model[0]) && arg0->motion[10] != Hu3DMotionShiftIDGet(arg0->model[0])) {
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[10], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
            }
        } else {
            if (arg0->motion[0] != Hu3DMotionIDGet(arg0->model[0]) && arg0->motion[0] != Hu3DMotionShiftIDGet(arg0->model[0])) {
                Hu3DMotionShiftSet(arg0->model[0], arg0->motion[0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
            }
            return 1;
        }
    }
    return 0;
}

void fn_1_12494(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
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
        sp14.x = fn_1_11348(sp2C.x, sp20.x, temp_f29, temp_f28);
        sp14.y = fn_1_11348(sp2C.y, sp20.y, temp_f29, temp_f28);
        sp14.z = fn_1_11348(sp2C.z, sp20.z, temp_f29, temp_f28);
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

void fn_1_12958(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6) {
    fn_1_12494(arg0, arg1, arg2, arg3, 0, arg5, arg6, 1, 0);
}

void fn_1_129B8(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6) {
    fn_1_12494(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0, 1);
}

void fn_1_12A1C(omObjData* arg0, s32 arg1, Vec* arg2, Vec* arg3, s32 arg4, s32 arg5, s32 arg6) {
    fn_1_12494(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 1, 1);
}

void fn_1_12A80(StructBss160* arg0) {
    arg0->unk08 = arg0->unk14;
    arg0->unk0C = arg0->unk18;
    arg0->unk10 = arg0->unk1C;
    arg0->unk20 = arg0->unk2C;
    arg0->unk24 = arg0->unk30;
    arg0->unk28 = arg0->unk34;
    arg0->unk38 = arg0->unk3C;
}

void fn_1_12ABC(StructBss160* arg0) {
    arg0->unk40 = 0;
    arg0->unk14 = arg0->unk08;
    arg0->unk18 = arg0->unk0C;
    arg0->unk1C = arg0->unk10;
    arg0->unk2C = arg0->unk20;
    arg0->unk30 = arg0->unk24;
    arg0->unk34 = arg0->unk28;
    arg0->unk3C = arg0->unk38;
}

void fn_1_12B00(StructBss160* arg0, StructBss160* arg1, float arg2) {
    arg0->unk08 = fn_1_11370(arg0->unk08, arg1->unk14, arg2);
    arg0->unk0C = fn_1_11370(arg0->unk0C, arg1->unk18, arg2);
    arg0->unk10 = fn_1_11370(arg0->unk10, arg1->unk1C, arg2);
    arg0->unk20 = fn_1_11370(arg0->unk20, arg1->unk2C, arg2);
    arg0->unk24 = fn_1_11370(arg0->unk24, arg1->unk30, arg2);
    arg0->unk28 = fn_1_11370(arg0->unk28, arg1->unk34, arg2);
    arg0->unk38 = fn_1_11370(arg0->unk38, arg1->unk3C, arg2);
}

void fn_1_12E14(StructBss160* arg0, float arg1) {
    fn_1_12B00(arg0, arg0, arg1);
}

void fn_1_13128(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3) {
    arg1->unk14 = fn_1_11348(arg0->unk14, arg1->unk08, arg2, arg3);
    arg1->unk18 = fn_1_11348(arg0->unk18, arg1->unk0C, arg2, arg3);
    arg1->unk1C = fn_1_11348(arg0->unk1C, arg1->unk10, arg2, arg3);
    arg1->unk2C = fn_1_11348(arg0->unk2C, arg1->unk20, arg2, arg3);
    arg1->unk30 = fn_1_11348(arg0->unk30, arg1->unk24, arg2, arg3);
    arg1->unk34 = fn_1_11348(arg0->unk34, arg1->unk28, arg2, arg3);
    arg1->unk3C = fn_1_11348(arg0->unk3C, arg1->unk38, arg2, arg3);
}

void fn_1_133A4(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3) {
    fn_1_13128(arg0, arg1, arg2, arg3);
    arg0->unk08 = arg1->unk14;
    arg0->unk0C = arg1->unk18;
    arg0->unk10 = arg1->unk1C;
    arg0->unk20 = arg1->unk2C;
    arg0->unk24 = arg1->unk30;
    arg0->unk28 = arg1->unk34;
    arg0->unk38 = arg1->unk3C;
}

void fn_1_13658(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3, float arg4) {
    fn_1_13128(arg0, arg1, arg2, arg3);
    fn_1_12B00(arg0, arg1, arg4);
}

void fn_1_13B88(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3) {
    arg1->unk14 = fn_1_113B0(arg0->unk14, arg1->unk08, arg2, arg3);
    arg1->unk18 = fn_1_113B0(arg0->unk18, arg1->unk0C, arg2, arg3);
    arg1->unk1C = fn_1_113B0(arg0->unk1C, arg1->unk10, arg2, arg3);
    arg1->unk2C = fn_1_113B0(arg0->unk2C, arg1->unk20, arg2, arg3);
    arg1->unk30 = fn_1_113B0(arg0->unk30, arg1->unk24, arg2, arg3);
    arg1->unk34 = fn_1_113B0(arg0->unk34, arg1->unk28, arg2, arg3);
    arg1->unk3C = fn_1_113B0(arg0->unk3C, arg1->unk38, arg2, arg3);
}

void fn_1_13FDC(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3) {
    fn_1_13B88(arg0, arg1, arg2, arg3);
    arg0->unk08 = arg1->unk14;
    arg0->unk0C = arg1->unk18;
    arg0->unk10 = arg1->unk1C;
    arg0->unk20 = arg1->unk2C;
    arg0->unk24 = arg1->unk30;
    arg0->unk28 = arg1->unk34;
    arg0->unk38 = arg1->unk3C;
}

void fn_1_14468(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3, float arg4) {
    fn_1_13B88(arg0, arg1, arg2, arg3);
    fn_1_12B00(arg0, arg1, arg4);
}

void fn_1_14B84(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3) {
    arg1->unk14 = fn_1_11540(arg0->unk14, arg1->unk08, arg2, arg3);
    arg1->unk18 = fn_1_11540(arg0->unk18, arg1->unk0C, arg2, arg3);
    arg1->unk1C = fn_1_11540(arg0->unk1C, arg1->unk10, arg2, arg3);
    arg1->unk2C = fn_1_11540(arg0->unk2C, arg1->unk20, arg2, arg3);
    arg1->unk30 = fn_1_11540(arg0->unk30, arg1->unk24, arg2, arg3);
    arg1->unk34 = fn_1_11540(arg0->unk34, arg1->unk28, arg2, arg3);
    arg1->unk3C = fn_1_11540(arg0->unk3C, arg1->unk38, arg2, arg3);
}

void fn_1_15048(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3) {
    fn_1_14B84(arg0, arg1, arg2, arg3);
    arg0->unk08 = arg1->unk14;
    arg0->unk0C = arg1->unk18;
    arg0->unk10 = arg1->unk1C;
    arg0->unk20 = arg1->unk2C;
    arg0->unk24 = arg1->unk30;
    arg0->unk28 = arg1->unk34;
    arg0->unk38 = arg1->unk3C;
}

void fn_1_15544(StructBss160* arg0, StructBss160* arg1, float arg2, float arg3, float arg4) {
    fn_1_14B84(arg0, arg1, arg2, arg3);
    fn_1_12B00(arg0, arg1, arg4);
}

void fn_1_15CD0(StructFn15CD0* arg0, s32 arg1) {
    s32 var_r30;
    s32 i;

    var_r30 = -1;
    for (i = 0; i < 20; i++) {
        if (arg0->unk94[i] == -1) {
            var_r30 = i;
            break;
        }
    }
    if (var_r30 != -1) {
        arg0->unk94[var_r30] = arg1;
        arg0->unk00 = 1;
    }
}

void fn_1_15D3C(StructFn15CD0* arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < 20; i++) {
        if (arg1 == -1) {
            arg0->unk94[i] = -1;
        } else if (arg0->unk94[i] == arg1) {
            arg0->unk94[i] = -1;
        }
    }
}

void fn_1_15DA4(StructFn15CD0* arg0, s32 arg1) {
    arg0->unk90 = arg1;
    arg0->unk00 = 1;
}

void fn_1_15DB4(StructFn15CD0* arg0) {
    arg0->unk90 = -1;
}

void fn_1_15DC0(StructFn15CD0* arg0, s32 arg1) {
    arg0->unk00 = arg1;
}

void fn_1_15DC8(StructFn15CD0* arg0) {
    fn_1_15DC0(arg0, 0);
    fn_1_15D3C(arg0, -1);
    fn_1_15DB4(arg0);
}

float fn_1_15E10(s32 arg0, s32 arg1, s32 arg2) {
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

float fn_1_16154(s32 arg0, s32 arg1) {
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

float fn_1_162E4(s32 arg0, float arg1, float arg2) {
    return (arg2 + arg1 * (arg0 - 1)) / arg0;
}

void fn_1_16348(omObjData* arg0) {
}

void fn_1_1634C(Process* arg0, StructFn15CD0* arg1, s32 arg2, const char* arg3, s32 arg4, s32 arg5) {
    arg1->unk00 = 0;
    arg1->unk84 = arg2;
    strcpy(arg1->unk04, arg3);
    arg1->unk88 = arg4;
    arg1->unk8C = arg5;
    arg1->unk90 = -1;
    fn_1_15D3C(arg1, -1);
    arg1->unkE4 = omAddObjEx(arg0, 0x3000, 0, 0, -1, fn_1_16348);
    arg1->unkE4->data = arg1;
    arg1->unkE4->trans.x = 10.0f;
    arg1->unkE4->trans.y = 10000.0f;
    arg1->unkE4->trans.z = 10.0f;
    arg1->unkE4->rot.x = 0.0f;
    arg1->unkE4->rot.y = 0.0f;
    arg1->unkE4->rot.z = 0.0f;
    arg1->unkE4->work[0] = arg1->unkE4->work[1] = arg1->unkE4->work[2] = arg1->unkE4->work[3] = 0;
}

void fn_1_164B0(Process* arg0, StructFn15CD0* arg1, s32 arg2, const char* arg3) {
    fn_1_1634C(arg0, arg1, arg2, arg3, 0x100, 0);
}

void fn_1_1660C(Process* arg0, StructFn15CD0* arg1, s32 arg2, s32 arg3) {
    fn_1_1634C(arg0, arg1, arg2, lbl_1_data_3D0[arg3], lbl_1_data_3F0[arg3][0], lbl_1_data_3F0[arg3][1]);
}
