#include "dolphin.h"

static u32 frand_seed;

extern s32 rand8(void);

static inline u32 frandom(u32 param)
{
    s32 rand2, rand3;

    if (param == 0) {
        param = rand8();
        param = param ^ (s64)OSGetTime();
        param ^= 0xD826BC89;
    }

    rand2 = param / (u32)0x1F31D;
    rand3 = param - (rand2 * 0x1F31D);
    param = rand2 * 0xB14;
    param =  param - rand3 * 0x41A7;
    return param;
}

u32 frand(void) {
    return frand_seed = frandom(frand_seed);
}

f32 frandf(void) {
    u32 value = frand();
    f32 ret;
    value &= 0x7FFFFFFF;
    ret = (f32)value/2147483648;
    return ret;
}

u32 frandmod(u32 arg0) {
    u32 ret;
    frand_seed = frandom(frand_seed);
#ifdef TARGET_PC
    if (arg0 == 0) {
        ret = (frand_seed & 0x7FFFFFFF);
        return ret;
    }
#endif
    ret = (frand_seed & 0x7FFFFFFF)%arg0;
    return ret;
}
