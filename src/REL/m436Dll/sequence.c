#include "REL/m436Dll.h"
#include "game/hu3d.h"

#include "ext_math.h"

float fn_1_110FC(float arg0, float arg1, float arg2) {
    if (arg2 <= 1.0f) {
        return arg1;
    }
    return (arg1 + arg0 * (arg2 - 1.0f)) / arg2;
}

float fn_1_1113C(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg2 / arg3) * (arg1 - arg0);
}

float fn_1_11164(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * sind((90.0f / arg3) * arg2);
}

float fn_1_1122C(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * sind((360.0f / arg3) * arg2);
}

float fn_1_112F4(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + (arg1 - arg0) * (1.0 - cosd((90.0f / arg3) * arg2));
}

void fn_1_113CC(omObjData* arg0, s32 arg1, omObjData* arg2, s32 arg3) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;

    sp20.x = Hu3DData[arg0->model[arg1]].pos.x;
    sp20.z = Hu3DData[arg0->model[arg1]].pos.z;
    sp2C.x = Hu3DData[arg2->model[arg3]].pos.x;
    sp2C.z = Hu3DData[arg2->model[arg3]].pos.z;
    sp14.y = Hu3DData[arg0->model[arg1]].rot.y;
    sp8.x = sp2C.x - sp20.x;
    sp8.z = sp2C.z - sp20.z;
    sp14.x = -(atan2d(sp8.z, sp8.x) - 90.0);
    if (sp14.x >= 360.0f) {
        sp14.x -= 360.0f;
    }
    if (sp14.x < 0.0f) {
        sp14.x += 360.0f;
    }
    if (sp14.x >= 180.0f) {
        if (sp14.y - sp14.x >= 180.0f) {
            sp14.y -= 360.0f;
        }
        if (sp14.y - sp14.x < -180.0f) {
            sp14.y += 360.0f;
        }
    } else {
        if (sp14.y - sp14.x > 180.0f) {
            sp14.y -= 360.0f;
        }
        if (sp14.y - sp14.x <= -180.0f) {
            sp14.y += 360.0f;
        }
    }
    sp14.y = (9.0f * sp14.y + sp14.x) / 10.0f;
    if (arg1 == 0) {
        arg0->rot.y = sp14.y;
    } else {
        Hu3DData[arg0->model[arg1]].rot.y = sp14.y;
    }
}

s32 fn_1_11708(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
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

void fn_1_11818(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
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

void fn_1_11990(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    arg0->work[3] = arg0->motion[arg2];
    fn_1_11818(arg0, arg1, arg2, arg3, arg4);
}

void fn_1_11B18(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0->work[3] != arg0->motion[arg2]) {
        arg0->work[3] = arg0->motion[arg2];
        fn_1_11990(arg0, arg1, arg2, arg3, arg4);
    }
}

void fn_1_11CC8(StructBssC0* arg0) {
    arg0->unk08 = 0;
    arg0->unk0C = arg0->unk04[arg0->unk00].unk08;
    arg0->unk10 = arg0->unk04[arg0->unk00].unk00;
    arg0->unk14 = arg0->unk04[arg0->unk00].unk04;
}

void fn_1_11D18(StructBssC0* arg0, StructData1E8* arg1) {
    arg0->unk00 = 0;
    arg0->unk04 = arg1;
    fn_1_11CC8(arg0);
}

s32 fn_1_11D74(StructBssC0* arg0) {
    arg0->unk00++;
    fn_1_11CC8(arg0);
    if (arg0->unk10 == NULL && arg0->unk14 == NULL) {
        return 1;
    }
    return 0;
}

s32 fn_1_11DFC(StructBssC0* arg0) {
    arg0->unk00--;
    if (arg0->unk00 < 0) {
        return 1;
    }
    fn_1_11CC8(arg0);
    return 0;
}

s32 fn_1_11E70(StructBssC0* arg0, s32 arg1) {
    arg0->unk00 = arg1;
    if (arg0->unk00 < 0) {
        return 1;
    }
    fn_1_11CC8(arg0);
    if (arg0->unk10 == NULL && arg0->unk14 == NULL) {
        return 1;
    }
    return 0;
}

s32 fn_1_11F04(StructBssC0* arg0, s32 arg1) {
    if (arg1 == 0) {
        return arg0->unk08;
    }
    arg0->unk08 += arg1;
    if (arg0->unk08 >= arg0->unk0C) {
        return 1;
    }
    return 0;
}

void fn_1_11F40(StructBss32C* arg0, float* arg1, float* arg2) {
    float temp_f31;
    float temp_f29;
    float temp_f30;
    float temp_f27;

    temp_f31 = arg1[0] - arg2[0];
    temp_f29 = arg1[1] - arg2[1];
    temp_f30 = arg1[2] - arg2[2];
    arg0->unk10 = arg2[0];
    arg0->unk14 = arg2[1];
    arg0->unk18 = arg2[2];
    arg0->unk38 = sqrtf(temp_f31 * temp_f31 + temp_f29 * temp_f29 + temp_f30 * temp_f30);
    temp_f27 = atan2d(temp_f30, temp_f31);
    arg0->unk28 = -(atan2d(temp_f29, temp_f31 * cosd(-temp_f27) + temp_f30 * -sind(-temp_f27)));
    arg0->unk2C = -(temp_f27 - 90.0f);
    arg0->unk30 = 0.0f;
}

void fn_1_12258(StructBss32C* arg0) {
    arg0->unk04 = arg0->unk10;
    arg0->unk08 = arg0->unk14;
    arg0->unk0C = arg0->unk18;
    arg0->unk1C = arg0->unk28;
    arg0->unk20 = arg0->unk2C;
    arg0->unk24 = arg0->unk30;
    arg0->unk34 = arg0->unk38;
}

void fn_1_12294(StructBss32C* arg0) {
    arg0->unk3C = 0.0f;
    arg0->unk10 = arg0->unk04;
    arg0->unk14 = arg0->unk08;
    arg0->unk18 = arg0->unk0C;
    arg0->unk28 = arg0->unk1C;
    arg0->unk2C = arg0->unk20;
    arg0->unk30 = arg0->unk24;
    arg0->unk38 = arg0->unk34;
}

void fn_1_122E0(StructBss32C* arg0, StructBss32C* arg1, float arg2) {
    arg0->unk04 = fn_1_110FC(arg0->unk04, arg1->unk10, arg2);
    arg0->unk08 = fn_1_110FC(arg0->unk08, arg1->unk14, arg2);
    arg0->unk0C = fn_1_110FC(arg0->unk0C, arg1->unk18, arg2);
    arg0->unk1C = fn_1_110FC(arg0->unk1C, arg1->unk28, arg2);
    arg0->unk20 = fn_1_110FC(arg0->unk24, arg1->unk2C, arg2);
    arg0->unk24 = fn_1_110FC(arg0->unk20, arg1->unk30, arg2);
    arg0->unk34 = fn_1_110FC(arg0->unk34, arg1->unk38, arg2);
}

void fn_1_125F4(StructBss32C* arg0, float arg1) {
    fn_1_122E0(arg0, arg0, arg1);
}

void fn_1_12908(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3) {
    arg1->unk10 = fn_1_1113C(arg0->unk10, arg1->unk04, arg2, arg3);
    arg1->unk14 = fn_1_1113C(arg0->unk14, arg1->unk08, arg2, arg3);
    arg1->unk18 = fn_1_1113C(arg0->unk18, arg1->unk0C, arg2, arg3);
    arg1->unk28 = fn_1_1113C(arg0->unk28, arg1->unk1C, arg2, arg3);
    arg1->unk2C = fn_1_1113C(arg0->unk30, arg1->unk20, arg2, arg3);
    arg1->unk30 = fn_1_1113C(arg0->unk2C, arg1->unk24, arg2, arg3);
    arg1->unk38 = fn_1_1113C(arg0->unk38, arg1->unk34, arg2, arg3);
}

void fn_1_12B84(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3) {
    fn_1_12908(arg0, arg1, arg2, arg3);
    arg0->unk04 = arg1->unk10;
    arg0->unk08 = arg1->unk14;
    arg0->unk0C = arg1->unk18;
    arg0->unk1C = arg1->unk28;
    arg0->unk20 = arg1->unk2C;
    arg0->unk24 = arg1->unk30;
    arg0->unk34 = arg1->unk38;
}

void fn_1_12E38(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3, float arg4) {
    fn_1_12908(arg0, arg1, arg2, arg3);
    fn_1_122E0(arg0, arg1, arg4);
}

void fn_1_13368(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3) {
    arg1->unk10 = fn_1_11164(arg0->unk10, arg1->unk04, arg2, arg3);
    arg1->unk14 = fn_1_11164(arg0->unk14, arg1->unk08, arg2, arg3);
    arg1->unk18 = fn_1_11164(arg0->unk18, arg1->unk0C, arg2, arg3);
    arg1->unk28 = fn_1_11164(arg0->unk28, arg1->unk1C, arg2, arg3);
    arg1->unk2C = fn_1_11164(arg0->unk30, arg1->unk20, arg2, arg3);
    arg1->unk30 = fn_1_11164(arg0->unk2C, arg1->unk24, arg2, arg3);
    arg1->unk38 = fn_1_11164(arg0->unk38, arg1->unk34, arg2, arg3);
}

void fn_1_137BC(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3) {
    fn_1_13368(arg0, arg1, arg2, arg3);
    arg0->unk04 = arg1->unk10;
    arg0->unk08 = arg1->unk14;
    arg0->unk0C = arg1->unk18;
    arg0->unk1C = arg1->unk28;
    arg0->unk20 = arg1->unk2C;
    arg0->unk24 = arg1->unk30;
    arg0->unk34 = arg1->unk38;
}

void fn_1_13C48(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3, float arg4) {
    fn_1_13368(arg0, arg1, arg2, arg3);
    fn_1_122E0(arg0, arg1, arg4);
}

void fn_1_14364(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3) {
    arg1->unk10 = fn_1_112F4(arg0->unk10, arg1->unk04, arg2, arg3);
    arg1->unk14 = fn_1_112F4(arg0->unk14, arg1->unk08, arg2, arg3);
    arg1->unk18 = fn_1_112F4(arg0->unk18, arg1->unk0C, arg2, arg3);
    arg1->unk28 = fn_1_112F4(arg0->unk28, arg1->unk1C, arg2, arg3);
    arg1->unk2C = fn_1_112F4(arg0->unk30, arg1->unk20, arg2, arg3);
    arg1->unk30 = fn_1_112F4(arg0->unk2C, arg1->unk24, arg2, arg3);
    arg1->unk38 = fn_1_112F4(arg0->unk38, arg1->unk34, arg2, arg3);
}

void fn_1_14828(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3) {
    fn_1_14364(arg0, arg1, arg2, arg3);
    arg0->unk04 = arg1->unk10;
    arg0->unk08 = arg1->unk14;
    arg0->unk0C = arg1->unk18;
    arg0->unk1C = arg1->unk28;
    arg0->unk20 = arg1->unk2C;
    arg0->unk24 = arg1->unk30;
    arg0->unk34 = arg1->unk38;
}

void fn_1_14D24(StructBss32C* arg0, StructBss32C* arg1, float arg2, float arg3, float arg4) {
    fn_1_14364(arg0, arg1, arg2, arg3);
    fn_1_122E0(arg0, arg1, arg4);
}
