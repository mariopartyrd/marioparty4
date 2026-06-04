#include "REL/m418Dll.h"

f32 fn_1_A920(f32 arg0, f32 arg1, f32 arg2) {
    return (arg1 + (arg0 * (arg2 - 1.0f))) / arg2;
}

f32 fn_1_A940(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg2 >= arg3) {
        return arg1;
    }
    return arg0 + ((arg2 / arg3) * (arg1 - arg0));
}

f32 fn_1_A968(f32 arg8, f32 arg9, f32 argA, f32 argB) {
    if (argA >= argB) {
        return arg9;
    }
    return arg8 + (arg9 - arg8) * sind(((90.0f / argB) * argA));
}

f32 fn_1_AA30(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (arg2 >= arg3) {
        return arg0;
    }
    return arg0 + (arg1 - arg0) * sind((180.0f / arg3) * arg2);
}

f32 fn_1_AAEC(f32 arg8, f32 arg9, f32 argA, f32 argB) {
    if (argA >= argB) {
        return arg9;
    }
    return (arg8 + (arg9 - arg8) * (1.0 - cosd((90.0f / argB) * argA)));
}

void fn_1_ABC4(OMOBJ* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg4 == 1) {
        Hu3DMotionShiftSet(arg0->mdlId[arg1], arg0->mtnId[arg2], 0.0f, arg3, 0x40000001);
        return;
    }
    if (arg4 == 2) {
        Hu3DMotionShiftSet(arg0->mdlId[arg1], arg0->mtnId[arg2], 0.0f, arg3, 0x40000002);
        return;
    }
    Hu3DMotionShiftSet(arg0->mdlId[arg1], arg0->mtnId[arg2], 0.0f, arg3, 0);
}

void fn_1_AD14(OMOBJ* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0->work[3] != arg0->mtnId[arg2]) {
        arg0->work[3] = arg0->mtnId[arg2];
        if (arg4 == 1) {
            Hu3DMotionShiftSet(arg0->mdlId[arg1], arg0->mtnId[arg2], 0.0f, arg3, 0x40000001);
            return;
        }
        if (arg4 == 2) {
            Hu3DMotionShiftSet(arg0->mdlId[arg1], arg0->mtnId[arg2], 0.0f, arg3, 0x40000002);
            return;
        }
        Hu3DMotionShiftSet(arg0->mdlId[arg1], arg0->mtnId[arg2], 0.0f, arg3, 0);
    }
}

void fn_1_AE8C(M418DllUnkStruct7* arg0) {
    arg0->unk8 = 0;
    arg0->unkC = arg0->unk4[arg0->unk0].unk8;
    arg0->unk10 = (M418DllFunc)arg0->unk4[arg0->unk0].unk0;
    arg0->unk14 = (M418DllRetFunc)arg0->unk4[arg0->unk0].unk4;
}

void fn_1_AEDC(M418DllUnkStruct7* arg0, M418DllUnkStruct8* arg1) {
    arg0->unk0 = 0;
    arg0->unk4 = arg1;
    fn_1_AE8C(arg0);
}

s32 fn_1_AF38(M418DllUnkStruct7* arg0) {
    arg0->unk0++;
    fn_1_AE8C(arg0);
    if ((arg0->unk10 == NULL) && (arg0->unk14 == NULL)) {
        return 1;
    }
    return 0;
}

s32 fn_1_AFC0(M418DllUnkStruct7* arg0) {
    arg0->unk0--;
    if (arg0->unk0 < 0) {
        return 1;
    }
    fn_1_AE8C(arg0);
    return 0;
}

s32 fn_1_B034(M418DllUnkStruct7* arg0, s32 arg1) {
    arg0->unk0 = arg1;
    if (arg0->unk0 < 0) {
        return 1;
    }
    fn_1_AE8C(arg0);
    if ((arg0->unk10 == NULL) && (arg0->unk14 == NULL)) {
        return 1;
    }
    return 0;
}

s32 fn_1_B0C8(M418DllUnkStruct7* arg0, s32 arg1) {
    if (arg1 == 0) {
        return arg0->unk8;
    }
    arg0->unk8 += arg1;
    if (arg0->unk8 >= arg0->unkC) {
        return 1;
    }
    return 0;
}

void fn_1_B104(M418DllUnkStruct* arg0, Vec arg1, Vec arg2) {
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f27;

    temp_f31 = arg1.x - arg2.x;
    temp_f29 = arg1.y - arg2.y;
    temp_f30 = arg1.z - arg2.z;
    arg0->unk10.x = arg2.x;
    arg0->unk10.y = arg2.y;
    arg0->unk10.z = arg2.z;
    arg0->unk38 = sqrtf((temp_f30 * temp_f30) + ((temp_f31 * temp_f31) + (temp_f29 * temp_f29)));
    temp_f27 = atan2d(temp_f30, temp_f31);
    arg0->unk28.x = -atan2d(temp_f29, (temp_f31 * cosd(-temp_f27)) + (temp_f30 * -sind(-temp_f27)));
    arg0->unk28.y = -(temp_f27 - 90.0f);
    arg0->unk28.z = 0.0f;
}

void fn_1_B41C(M418DllUnkStruct* arg0) {
    arg0->center.x = arg0->unk10.x;
    arg0->center.y = arg0->unk10.y;
    arg0->center.z = arg0->unk10.z;
    arg0->rot.x = arg0->unk28.x;
    arg0->rot.y = arg0->unk28.y;
    arg0->rot.z = arg0->unk28.z;
    arg0->zoom = arg0->unk38;
}

void fn_1_B458(M418DllUnkStruct* arg0) {
    arg0->unk48 = 0.0f;
    arg0->unk10.x = arg0->center.x;
    arg0->unk10.y = arg0->center.y;
    arg0->unk10.z = arg0->center.z;
    arg0->unk28.x = arg0->rot.x;
    arg0->unk28.y = arg0->rot.y;
    arg0->unk28.z = arg0->rot.z;
    arg0->unk38 = arg0->zoom;
}

void fn_1_B4A4(M418DllUnkStruct* arg0, M418DllUnkStruct* arg1, f32 arg8) {
    arg0->center.x = fn_1_A920(arg0->center.x, arg1->unk10.x, arg8);
    arg0->center.y = fn_1_A920(arg0->center.y, arg1->unk10.y, arg8);
    arg0->center.z = fn_1_A920(arg0->center.z, arg1->unk10.z, arg8);
    arg0->rot.x = fn_1_A920(arg0->rot.x, arg1->unk28.x, arg8);
    arg0->rot.y = fn_1_A920(arg0->rot.y, arg1->unk28.y, arg8);
    arg0->rot.z = fn_1_A920(arg0->rot.z, arg1->unk28.z, arg8);
    arg0->zoom = fn_1_A920(arg0->zoom, arg1->unk38, arg8);
}

void fn_1_B710(M418DllUnkStruct* arg0, f32 arg1) {
    arg0->center.x = fn_1_A920(arg0->center.x, arg0->unk10.x, arg1);
    arg0->center.y = fn_1_A920(arg0->center.y, arg0->unk10.y, arg1);
    arg0->center.z = fn_1_A920(arg0->center.z, arg0->unk10.z, arg1);
    arg0->rot.x = fn_1_A920(arg0->rot.x, arg0->unk28.x, arg1);
    arg0->rot.y = fn_1_A920(arg0->rot.y, arg0->unk28.y, arg1);
    arg0->rot.z = fn_1_A920(arg0->rot.z, arg0->unk28.z, arg1);
    arg0->zoom = fn_1_A920(arg0->zoom, arg0->unk38, arg1);
}

void fn_1_B97C(M418DllUnkStruct* arg0, M418DllUnkStruct* arg1, f32 arg8, f32 arg9) {
    arg1->unk10.x = fn_1_A940(arg0->unk10.x, arg1->center.x, arg8, arg9);
    arg1->unk10.y = fn_1_A940(arg0->unk10.y, arg1->center.y, arg8, arg9);
    arg1->unk10.z = fn_1_A940(arg0->unk10.z, arg1->center.z, arg8, arg9);
    arg1->unk28.x = fn_1_A940(arg0->unk28.x, arg1->rot.x, arg8, arg9);
    arg1->unk28.y = fn_1_A940(arg0->unk28.y, arg1->rot.y, arg8, arg9);
    arg1->unk28.z = fn_1_A940(arg0->unk28.z, arg1->rot.z, arg8, arg9);
    arg1->unk38 = fn_1_A940(arg0->unk38, arg1->zoom, arg8, arg9);
}

void fn_1_BBF8(M418DllUnkStruct* arg0, M418DllUnkStruct* arg1, f32 arg8, f32 arg9) {
    fn_1_B97C(arg0, arg1, arg8, arg9);
    arg0->center.x = arg1->unk10.x;
    arg0->center.y = arg1->unk10.y;
    arg0->center.z = arg1->unk10.z;
    arg0->rot.x = arg1->unk28.x;
    arg0->rot.y = arg1->unk28.y;
    arg0->rot.z = arg1->unk28.z;
    arg0->zoom = arg1->unk38;
}

void fn_1_BEAC(M418DllUnkStruct* arg0, M418DllUnkStruct* arg1, f32 arg2, f32 arg3, f32 arg4) {
    fn_1_B97C(arg0, arg1, arg2, arg3);
    fn_1_B4A4(arg0, arg1, arg4);
}

void fn_1_C318(M418DllUnkStruct* arg0, M418DllUnkStruct* arg1, f32 arg8, f32 arg9) {
    arg1->unk10.x = fn_1_A968(arg0->unk10.x, arg1->center.x, arg8, arg9);
    arg1->unk10.y = fn_1_A968(arg0->unk10.y, arg1->center.y, arg8, arg9);
    arg1->unk10.z = fn_1_A968(arg0->unk10.z, arg1->center.z, arg8, arg9);
    arg1->unk28.x = fn_1_A968(arg0->unk28.x, arg1->rot.x, arg8, arg9);
    arg1->unk28.y = fn_1_A968(arg0->unk28.y, arg1->rot.y, arg8, arg9);
    arg1->unk28.z = fn_1_A968(arg0->unk28.z, arg1->rot.z, arg8, arg9);
    arg1->unk38 = fn_1_A968(arg0->unk38, arg1->zoom, arg8, arg9);
}

void fn_1_C76C(M418DllUnkStruct* arg0, M418DllUnkStruct* arg1, f32 arg8, f32 arg9) {
    fn_1_C318(arg0, arg1, arg8, arg9);
    arg0->center.x = arg1->unk10.x;
    arg0->center.y = arg1->unk10.y;
    arg0->center.z = arg1->unk10.z;
    arg0->rot.x = arg1->unk28.x;
    arg0->rot.y = arg1->unk28.y;
    arg0->rot.z = arg1->unk28.z;
    arg0->zoom = arg1->unk38;
}

void fn_1_CBF8(M418DllUnkStruct* arg0, M418DllUnkStruct* arg1, f32 arg2, f32 arg3, f32 arg4) {
    fn_1_C318(arg0, arg1, arg2, arg3);
    fn_1_B4A4(arg0, arg1, arg4);
}

void fn_1_D250(M418DllUnkStruct* arg0, M418DllUnkStruct* arg1, f32 arg8, f32 arg9) {
    arg1->unk10.x = fn_1_AAEC(arg0->unk10.x, arg1->center.x, arg8, arg9);
    arg1->unk10.y = fn_1_AAEC(arg0->unk10.y, arg1->center.y, arg8, arg9);
    arg1->unk10.z = fn_1_AAEC(arg0->unk10.z, arg1->center.z, arg8, arg9);
    arg1->unk28.x = fn_1_AAEC(arg0->unk28.x, arg1->rot.x, arg8, arg9);
    arg1->unk28.y = fn_1_AAEC(arg0->unk28.y, arg1->rot.y, arg8, arg9);
    arg1->unk28.z = fn_1_AAEC(arg0->unk28.z, arg1->rot.z, arg8, arg9);
    arg1->unk38 = fn_1_AAEC(arg0->unk38, arg1->zoom, arg8, arg9);
}

void fn_1_D714(M418DllUnkStruct* arg0, M418DllUnkStruct* arg1, f32 arg8, f32 arg9) {
    fn_1_D250(arg0, arg1, arg8, arg9);
    arg0->center.x = arg1->unk10.x;
    arg0->center.y = arg1->unk10.y;
    arg0->center.z = arg1->unk10.z;
    arg0->rot.x = arg1->unk28.x;
    arg0->rot.y = arg1->unk28.y;
    arg0->rot.z = arg1->unk28.z;
    arg0->zoom = arg1->unk38;
}

void fn_1_DC10(M418DllUnkStruct* arg0, M418DllUnkStruct* arg1, f32 arg2, f32 arg3, f32 arg4) {
    fn_1_D250(arg0, arg1, arg2, arg3);
    fn_1_B4A4(arg0, arg1, arg4);
}
