#include "dolphin/mtx.h"
#include "dolphin/gx/GXPriv.h"
#include "math.h"

#define R_RET fp1
#define FP2 fp2
#define FP3 fp3
#define FP4 fp4
#define FP5 fp5
#define FP6 fp6
#define FP7 fp7
#define FP8 fp8
#define FP9 fp9
#define FP10 fp10
#define FP11 fp11
#define FP12 fp12
#define FP13 fp13

void C_VECAdd(const Vec *a, const Vec *b, Vec *c) {
    ASSERTMSGLINE(0x57, a, "VECAdd():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(0x58, b, "VECAdd():  NULL VecPtr 'b' ");
    ASSERTMSGLINE(0x59, c, "VECAdd():  NULL VecPtr 'ab' ");
    c->x = a->x + b->x;
    c->y = a->y + b->y;
    c->z = a->z + b->z;
}

#ifdef GEKKO
asm void PSVECAdd(const register Vec *vec1, const register Vec *vec2, register Vec *ret)
{
    // clang-format off
	nofralloc;
	psq_l     FP2,  0(vec1), 0, 0;
	psq_l     FP4,  0(vec2), 0, 0;
	ps_add    FP6, FP2, FP4;
	psq_st    FP6,  0(ret), 0, 0;
	psq_l     FP3,   8(vec1), 1, 0;
	psq_l     FP5,   8(vec2), 1, 0;
	ps_add    FP7, FP3, FP5;
	psq_st    FP7,   8(ret), 1, 0;
	blr
    // clang-format on
}
#endif

void C_VECSubtract(const Vec *a, const Vec *b, Vec *c) {
    ASSERTMSGLINE(0x9C, a, "VECSubtract():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(0x9D, b, "VECSubtract():  NULL VecPtr 'b' ");
    ASSERTMSGLINE(0x9E, c, "VECSubtract():  NULL VecPtr 'a_b' ");
    c->x = a->x - b->x;
    c->y = a->y - b->y;
    c->z = a->z - b->z;
}

#ifdef GEKKO
asm void PSVECSubtract(const register Vec *vec1, const register Vec *vec2, register Vec *ret)
{
    // clang-format off
	nofralloc;
	psq_l     FP2,  0(vec1), 0, 0;
	psq_l     FP4,  0(vec2), 0, 0;
	ps_sub    FP6, FP2, FP4;
	psq_st    FP6, 0(ret), 0, 0;
	psq_l     FP3,   8(vec1), 1, 0;
	psq_l     FP5,   8(vec2), 1, 0;
	ps_sub    FP7, FP3, FP5;
	psq_st    FP7,  8(ret), 1, 0;
	blr
    // clang-format on
}
#endif

void C_VECScale(const Vec *src, Vec *dst, f32 scale)
{
    f32 s;

    s = 1.0f / sqrtf(src->z * src->z + src->x * src->x + src->y * src->y);
    dst->x = src->x * s;
    dst->y = src->y * s;
    dst->z = src->z * s;
}

#ifdef GEKKO
asm void PSVECScale(register const Vec *src, register Vec *dst, register f32 scale)
{
#// clang-format off
	nofralloc
	psq_l        f0, 0(src), 0, 0
    psq_l        f2, 8(src), 1, 0
    ps_muls0     f0, f0, f1
    psq_st       f0, 0(dst), 0, 0
    ps_muls0     f0, f2, f1
    psq_st       f0, 8(dst), 1, 0
    blr
    // clang-format on
}
#endif

void C_VECNormalize(const Vec *src, Vec *unit) {
    f32 mag;

    ASSERTMSGLINE(0x127, src, "VECNormalize():  NULL VecPtr 'src' ");
    ASSERTMSGLINE(0x128, unit, "VECNormalize():  NULL VecPtr 'unit' ");
    mag = (src->z * src->z) + ((src->x * src->x) + (src->y * src->y));
    ASSERTMSGLINE(0x12D, 0.0f != mag, "VECNormalize():  zero magnitude vector ");
    mag = 1.0f/ sqrtf(mag);
    unit->x = src->x * mag;
    unit->y = src->y * mag;
    unit->z = src->z * mag;
}

#ifdef GEKKO
void PSVECNormalize(const register Vec *vec1, register Vec *ret)
{
    // clang-format off
	register f32 half  = 0.5f;
	register f32 three = 3.0f;
	register f32 xx_zz, xx_yy;
	register f32 square_sum;
	register f32 ret_sqrt;
	register f32 n_0, n_1;
	asm {
		psq_l       FP2, 0(vec1), 0, 0;
		ps_mul      xx_yy, FP2, FP2;
		psq_l       FP3, 8(vec1), 1, 0;
		ps_madd     xx_zz, FP3, FP3, xx_yy;
		ps_sum0     square_sum, xx_zz, FP3, xx_yy;
		frsqrte     ret_sqrt, square_sum;
		fmuls       n_0, ret_sqrt, ret_sqrt;
		fmuls       n_1, ret_sqrt, half;
		fnmsubs     n_0, n_0, square_sum, three;
		fmuls       ret_sqrt, n_0, n_1;
		ps_muls0    FP2, FP2, ret_sqrt;
		psq_st      FP2, 0(ret), 0, 0;
		ps_muls0    FP3, FP3, ret_sqrt;
		psq_st      FP3, 8(ret), 1, 0;
	}
    // clang-format on
}
#endif

f32 C_VECSquareMag(const Vec *v) {
    f32 sqmag;

    ASSERTMSGLINE(0x182, v, "VECMag():  NULL VecPtr 'v' ");

    sqmag = v->z * v->z + ((v->x * v->x) + (v->y * v->y));
    return sqmag;
}

#ifdef GEKKO
asm f32 PSVECSquareMag(register const Vec *v) {
    // clang-format off
	nofralloc
    psq_l      f0, 0(v), 0, 0
    ps_mul     f0, f0, f0
    lfs        f1, 8(v)
    ps_madd    f1, f1, f1, f0
    ps_sum0    f1, f1, f0, f0
    blr
    // clang-format on
}
#endif

f32 C_VECMag(const Vec *v) {
    return sqrtf(C_VECSquareMag(v));
}

#ifdef GEKKO
f32 PSVECMag(const register Vec *v)
{
    register f32 v_xy, v_zz, square_mag;
    register f32 ret_mag, n_0, n_1;
    register f32 three, half, zero;
    // clang-format off
	asm {
		psq_l       v_xy, 0(v), 0, 0
		ps_mul      v_xy, v_xy, v_xy
		lfs         v_zz, 8(v)
		ps_madd     square_mag, v_zz, v_zz, v_xy
    }
    // clang-format on
    half = 0.5f;
    // clang-format off
    asm {
		ps_sum0     square_mag, square_mag, v_xy, v_xy
		frsqrte     ret_mag, square_mag
    }
    // clang-format on
    three = 3.0f;
    // clang-format off
asm {
		fmuls       n_0, ret_mag, ret_mag
		fmuls       n_1, ret_mag, half
		fnmsubs     n_0, n_0, square_mag, three
		fmuls       ret_mag, n_0, n_1
        fsel        ret_mag, ret_mag, ret_mag, square_mag
		fmuls       square_mag, square_mag, ret_mag
	}
    // clang-format on
    return square_mag;
}
#endif

f32 C_VECDotProduct(const Vec *a, const Vec *b) {
    f32 dot;

    ASSERTMSGLINE(0x1D1, a, "VECDotProduct():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(0x1D2, b, "VECDotProduct():  NULL VecPtr 'b' ");
    dot = (a->z * b->z) + ((a->x * b->x) + (a->y * b->y));
    return dot;
}

#ifdef GEKKO
asm f32 PSVECDotProduct(const register Vec *vec1, const register Vec *vec2)
{
    // clang-format off
	nofralloc;
    psq_l      f2, 4(r3), 0, 0 /* qr0 */
    psq_l      f3, 4(r4), 0, 0 /* qr0 */
    ps_mul     f2, f2, f3
    psq_l      f5, 0(r3), 0, 0 /* qr0 */
    psq_l      f4, 0(r4), 0, 0 /* qr0 */
    ps_madd    f3, f5, f4, f2
    ps_sum0    f1, f3, f2, f2
    blr
    // clang-format on
}
#endif

void C_VECCrossProduct(const Vec *a, const Vec *b, Vec *axb) {
    Vec vTmp;

    ASSERTMSGLINE(0x20F, a, "VECCrossProduct():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(0x210, b, "VECCrossProduct():  NULL VecPtr 'b' ");
    ASSERTMSGLINE(0x211, axb, "VECCrossProduct():  NULL VecPtr 'axb' ");

    vTmp.x = (a->y * b->z) - (a->z * b->y);
    vTmp.y = (a->z * b->x) - (a->x * b->z);
    vTmp.z = (a->x * b->y) - (a->y * b->x);
    axb->x = vTmp.x;
    axb->y = vTmp.y;
    axb->z = vTmp.z;
}

#ifdef GEKKO
asm void PSVECCrossProduct(register const Vec *a, register const Vec *b, register Vec *axb)
{
    // clang-format off
	nofralloc
    psq_l          f1, 0(b), 0, 0
    lfs            f2, 8(a)
    psq_l          f0, 0(a), 0, 0
    ps_merge10     f6, f1, f1
    lfs            f3, 8(b)
    ps_mul         f4, f1, f2
    ps_muls0       f7, f1, f0
    ps_msub        f5, f0, f3, f4
    ps_msub        f8, f0, f6, f7
    ps_merge11     f9, f5, f5
    ps_merge01     f10, f5, f8
    psq_st         f9, 0(axb), 1, 0
    ps_neg         f10, f10
    psq_st         f10, 4(axb), 0, 0
    blr
    // clang-format on
}
#endif

void C_VECHalfAngle(const Vec *a, const Vec *b, Vec *half)
{
    Vec a0;
    Vec b0;
    Vec ab;

    a0.x = -a->x;
    a0.y = -a->y;
    a0.z = -a->z;

    b0.x = -b->x;
    b0.y = -b->y;
    b0.z = -b->z;

    VECNormalize(&a0, &a0);
    VECNormalize(&b0, &b0);
    VECAdd(&a0, &b0, &ab);

    if (VECDotProduct(&ab, &ab) > 0.0f) {
        VECNormalize(&ab, half);
    }
    else {
        *half = ab;
    }
}

void C_VECReflect(const Vec *src, const Vec *normal, Vec *dst)
{
    Vec a0;
    Vec b0;
    f32 dot;

    a0.x = -src->x;
    a0.y = -src->y;
    a0.z = -src->z;

    VECNormalize(&a0, &a0);
    VECNormalize(normal, &b0);

    dot = VECDotProduct(&a0, &b0);
    dst->x = b0.x * 2.0f * dot - a0.x;
    dst->y = b0.y * 2.0f * dot - a0.y;
    dst->z = b0.z * 2.0f * dot - a0.z;

    VECNormalize(dst, dst);
}

f32 C_VECSquareDistance(const Vec *a, const Vec *b) {
    Vec diff;

    diff.x = a->x - b->x;
    diff.y = a->y - b->y;
    diff.z = a->z - b->z;
    return (diff.z * diff.z) + ((diff.x * diff.x) + (diff.y * diff.y));
}

#ifdef GEKKO
asm f32 PSVECSquareDistance(register const Vec *a, register const Vec *b) {
    // clang-format off
	nofralloc
    psq_l      f0, 4(a), 0, 0
    psq_l      f1, 4(b), 0, 0
    ps_sub     f2, f0, f1
    psq_l      f0, 0(a), 0, 0
    psq_l      f1, 0(b), 0, 0
    ps_mul     f2, f2, f2
    ps_sub     f0, f0, f1
    ps_madd    f1, f0, f0, f2
    ps_sum0    f1, f1, f2, f2
    blr
    // clang-format on
}
#endif

f32 C_VECDistance(const Vec *a, const Vec *b) {
    return sqrtf(C_VECSquareDistance(a, b));
}

#ifdef GEKKO
f32 PSVECDistance(register const Vec *a, register const Vec *b)
{

    register f32 half_c;
    register f32 three_c;
    register f32 dist;

    // clang-format off
	asm {
		psq_l       f0, 4(a), 0, 0 /* qr0 */
        psq_l       f1, 4(b), 0, 0 /* qr0 */
        ps_sub      f2, f0, f1
        psq_l       f0, 0(a), 0, 0 /* qr0 */
        psq_l       f1, 0(b), 0, 0 /* qr0 */
        ps_mul      f2, f2, f2
        ps_sub      f0, f0, f1    
	}

    half_c = 0.5f;

    asm {
        ps_madd     f0, f0, f0, f2
        ps_sum0     f0, f0, f2, f2
    }

    three_c = 3.0f;

    asm {
        frsqrte     dist, f0
        fmuls       f2, dist, dist
        fmuls       dist, dist, half_c
        fnmsubs     f2, f2, f0, three_c
        fmuls       dist, f2, dist
        fsel        dist, dist, dist, f0
        fmuls       dist, f0, dist
    }

    return dist;
    // clang-format on
}
#endif
