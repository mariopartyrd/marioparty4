#include "REL/m447dll.h"

#include "ext_math.h"

float fn_1_7D94(float* arg0, float* arg1);
void fn_1_7F64(float* arg0, float arg1, float* arg2, float* arg3);
s32 fn_1_89BC(float* arg0, float* arg1);

void fn_1_7B54(Vec* arg0, Vec* arg1, s32 arg2, float arg3) {
    float temp_f29;
    float var_f30;
    float var_f31;
    s32 temp_r29;
    s32 var_r30;
    s32 i;

    temp_r29 = arg2 - 1;
    arg0->x = 0.0f;
    arg0->y = 0.0f;
    arg0->z = 0.0f;
    arg3 = (arg2 + 1) * arg3 - 1.0f;
    for (i = -2; i <= temp_r29 + 2; i++) {
        var_r30 = i;
        if (i < 0) {
            var_r30 = 0;
        }
        if (i > temp_r29) {
            var_r30 = temp_r29;
        }
        var_f31 = arg3 - i;
        if (var_f31 < 0.0f) {
            var_f31 = -var_f31;
        }
        if (var_f31 < 1.0f) {
            var_f30 = (3.0f * var_f31 * var_f31 * var_f31 - 6.0f * var_f31 * var_f31 + 4.0f) / 6.0f;
        } else if (var_f31 < 2.0f) {
            temp_f29 = var_f31 - 2.0f;
            var_f30 = -temp_f29 * temp_f29 * temp_f29 / 6.0f;
        } else {
            var_f30 = 0.0f;
        }
        arg0->x += var_f30 * arg1[var_r30].x;
        arg0->y += var_f30 * arg1[var_r30].y;
        arg0->z += var_f30 * arg1[var_r30].z;
    }
}

float fn_1_7D94(float* arg0, float* arg1) {
    float var_f30;
    float var_f31;
    float temp_f29;
    float var_f28;
    s32 var_r31;

    var_f30 = arg1[0] - arg0[0];
    var_f31 = arg1[1] - arg0[1];
    if (var_f30 >= 0.0f) {
        if (var_f31 >= 0.0f) {
            var_r31 = 0;
        } else {
            var_r31 = 3;
            temp_f29 = var_f30;
            var_f30 = -var_f31;
            var_f31 = temp_f29;
        }
    } else {
        if (var_f31 >= 0.0f) {
            var_r31 = 1;
            temp_f29 = var_f30;
            var_f30 = var_f31;
            var_f31 = -temp_f29;
        } else {
            var_r31 = 2;
            var_f30 = -var_f30;
            var_f31 = -var_f31;
        }
    }
    if (var_f31 > var_f30) {
        var_f28 = M_PI / 2 - atan2d(var_f30, var_f31);
    } else {
        var_f28 = atan2d(var_f31, var_f30);
    }
    return var_f28 + (M_PI / 2) * var_r31;
}

void fn_1_7F64(float* arg0, float arg1, float* arg2, float* arg3) {
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;

    // 57.29578 = 180 / M_PI (1 rad in degrees)
    temp_f31 = cosd(-(57.29578f * arg1));
    temp_f30 = sind(-(57.29578f * arg1));
    temp_f29 = arg2[0] - arg0[0];
    temp_f28 = arg2[1] - arg0[1];
    arg3[0] = temp_f29 * temp_f31 + temp_f28 * temp_f30 + arg0[0];
    arg3[1] = -temp_f29 * temp_f30 + temp_f28 * temp_f31 + arg0[1];
}

s32 fn_1_80BC(float* arg0, float* arg1, float* arg2) {
    float sp40[2];
    float sp38[2];
    float sp30[2];
    float sp2C;
    float var_f26;

    sp40[0] = 0.0f;
    sp40[1] = 0.0f;
    sp38[0] = arg0[0] - arg1[0];
    sp38[1] = arg0[1] - arg1[1];
    sp2C = fn_1_7D94(arg1, &arg1[2]);
    fn_1_7F64(sp40, -sp2C, sp38, sp30);
    if (ABS(sp30[1]) > arg0[2]) {
        return 0;
    }
    var_f26 = sqrtf(arg0[2] * arg0[2] - sp30[1] * sp30[1]);
    sp38[0] = arg0[0] + var_f26;
    sp38[1] = arg0[1] - sp30[1];
    fn_1_7F64(arg0, sp2C, sp38, arg2);
    if (var_f26 == 0.0f) {
        return 1;
    }
    sp38[0] = arg0[0] - var_f26;
    sp38[1] = arg0[1] - sp30[1];
    fn_1_7F64(arg0, sp2C, sp38, &arg2[2]);
    return 2;
}

s32 fn_1_879C(float* arg0, float* arg1, s32 arg2, s32 arg3) {
    float spC[2];
    float var_f28;

    spC[0] = arg0[0] - arg1[0];
    spC[1] = arg0[1] - arg1[1];
    var_f28 = sqrtf(spC[0] * spC[0] + spC[1] * spC[1]);
    if (var_f28 < arg0[2] + arg1[2]) {
        if (var_f28 == 0.0f) {
            spC[0] = 0.0f;
            spC[1] = -1.0f;
        } else {
            spC[0] /= var_f28;
            spC[1] /= var_f28;
            if (arg3 != 0) {
                arg1[0] -= spC[0];
                arg1[1] -= spC[1];
            }
        }
        if (arg2 != 0) {
            arg0[0] = arg1[0] + spC[0] * (arg0[2] + arg1[2]);
            arg0[1] = arg1[1] + spC[1] * (arg0[2] + arg1[2]);
        }
        return 1;
    }
    return 0;
}

s32 fn_1_89BC(float* arg0, float* arg1) {
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f26;
    float temp_f27;
    float temp_f24;

    temp_f26 = arg0[2] * arg0[2] - 2.0f * arg0[0] * arg0[2] + arg0[0] * arg0[0] + arg0[3] * arg0[3] - 2.0f * arg0[1] * arg0[3] + arg0[1] * arg0[1];
    temp_f27 = 2.0f * (arg0[0] * arg0[2] - arg0[2] * arg1[0] + arg0[0] * arg0[0] + arg0[1] * arg0[3] - arg0[3] * arg1[1] + arg0[1] * arg0[1]);
    temp_f24 = arg0[0] * arg0[0] - 2.0f * arg0[0] * arg1[0] + arg1[0] * arg1[0] + arg0[1] * arg0[1] - 2.0f * arg0[1] * arg1[1] + arg1[1] * arg1[1] - arg1[2] * arg1[2];
    if (temp_f26 == 0.0f) {
        if (temp_f27 != 0.0f) {
            return 1;
        } else {
            return 0;
        }
    }
    temp_f30 = temp_f27 * temp_f27 - 4.0f * temp_f26 * temp_f24;
    if (temp_f30 < 0.0f) {
        return 0;
    }
    temp_f30 = sqrtf(temp_f30);
    temp_f29 = (-temp_f27 + temp_f30) / (2.0f * temp_f26);
    temp_f28 = (-temp_f27 - temp_f30) / (2.0f * temp_f26);
    if (temp_f29 < temp_f28) {
        if (temp_f29 >= 0.0f && temp_f29 > 1.0f) {
            return 1;
        }
        if (temp_f28 >= 0.0f && temp_f28 < 1.0f) {
            return 1;
        }
    } else {
        if (temp_f28 >= 0.0f && temp_f28 < 1.0f) {
            return 1;
        }
        if (temp_f29 >= 0.0f && temp_f29 < 1.0f) {
            return 1;
        }
    }
    return 0;
}
