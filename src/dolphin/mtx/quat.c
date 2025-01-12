#include "dolphin/math.h"
#include "dolphin/mtx.h"

float acosf(float x);

float sinf(float x);
float cosf(float x);

void C_QUATAdd(const Quaternion *p, const Quaternion *q, Qtrn *r)
{
    r->x = p->x + q->x;
    r->y = p->y + q->y;
    r->z = p->z + q->z;
    r->w = p->w + q->w;
}

void PSQUATAdd(register const Quaternion *p, register const Quaternion *q, register Quaternion *r)
{
    asm {
      psq_l f0, 0x0(r3), 0, 0
      psq_l f1, 0x0(r4), 0, 0
      ps_add f0, f0, f1
      psq_st f0, 0x0(r5), 0, 0
      psq_l f0, 0x8(r3), 0, 0
      psq_l f1, 0x8(r4), 0, 0
      ps_add f0, f0, f1
      psq_st f0, 0x8(r5), 0, 0
    }
}

void PSQUATMultiply(register const Quaternion *a, register const Quaternion *b, register Quaternion *ab)
{
    asm {
        psq_l f0, 0(a), 0, 0
        psq_l f1, 8(a), 0, 0
        psq_l f2, 0(b), 0, 0
        ps_neg f5, f0
        psq_l f3, 8(b), 0, 0
        ps_neg f6, f1
        ps_merge01 f4, f5, f0
        ps_muls0 f7, f1, f2
        ps_muls0 f5, f5, f2
        ps_merge01 f1, f6, f1
        ps_muls1 f8, f4, f2
        ps_madds0 f7, f4, f3, f7
        ps_muls1 f2, f1, f2
        ps_madds0 f5, f1, f3, f5
        ps_madds1 f8, f6, f3, f8
        ps_merge10 f7, f7, f7
        ps_madds1 f2, f0, f3, f2
        ps_merge10 f5, f5, f5
        ps_add f7, f7, f2
        psq_st f7, 0(ab), 0, 0
        ps_sub f5, f5, f8
        psq_st f5, 8(ab), 0, 0
    }
}

void PSQUATNormalize(const register Quaternion *src, register Quaternion *unit)
{
    // sdata2
    (void)0.00001f;
    (void)0.0f;
    (void)0.5;
    (void)3.0;
    (void)1.0f;
    (void)0.5f;
    (void)3.0f;
    {
        register f32 vv1, vv2, vv3;
        register f32 vv4, vv5, vv6;
        register f32 vv7, vv8;
        register f32 vv9 = 0.00001f;
        register f32 vvA = 0.5F;
        register f32 vvB = 3.0F;
        asm
        {
            psq_l    vv1, 0(src), 0, 0;
            ps_mul   vv3, vv1, vv1;
            psq_l    vv2, 8(src), 0, 0;
            ps_sub   vv6, vv9, vv9;
            ps_madd  vv3, vv2, vv2, vv3;
            ps_sum0  vv3, vv3, vv3, vv3;
            frsqrte  vv4, vv3;
            ps_sub   vv5, vv3, vv9;
            fmul     vv7, vv4, vv4;
            fmul     vv8, vv4, vvA;
            fnmsub   vv7, vv7, vv3, vvB;
            fmul     vv4, vv7, vv8;
            ps_sel   vv4, vv5, vv4, vv6;
            ps_muls0 vv1, vv1, vv4;
            ps_muls0 vv2, vv2, vv4;
            psq_st   vv1, 0(unit), 0, 0;
            psq_st   vv2, 8(unit), 0, 0;
        }
    }
}

void PSQUATInverse(const register Quaternion *src, register Quaternion *inv)
{
    register f32 vv1, vv2, vv3, vv4;
    register f32 vv5, vv6, vv7, vv8, vv9, vvA, vvB;
    register f32 vvC = 1.0F;
    asm {
        psq_l       vv1, 0(src), 0, 0;
        ps_mul      vv5, vv1, vv1;
        psq_l       vv2, 8(src), 0, 0;
        ps_madd     vv5, vv2, vv2, vv5;
        ps_add      vvA, vvC, vvC;
        ps_sum0     vv5, vv5, vv5, vv5;
        fres        vv7, vv5;
        ps_neg      vv6, vv5;
        ps_nmsub    vv9, vv5, vv7, vvA;
        ps_mul      vv7, vv7, vv9;
        ps_sel vv7, vv6, vvC, vv7
        b           loc1;
    loc0:
        fmr         vv7, vvC;
    loc1:
        ps_neg      vv8, vv7;
        ps_muls1    vv4, vv7, vv2;
        ps_muls0    vv1, vv1, vv8;
        psq_st      vv4, 12(inv), 1, 0;
        ps_muls0    vv3, vv2, vv8;
        psq_st      vv1, 0(inv), 0, 0;
        psq_st      vv3, 8(inv), 1, 0;
    }
}

void C_QUATRotAxisRad(Quaternion *q, const Vec *axis, f32 rad)
{
    f32 tmp, tmp2, tmp3;
    Vec dst;

    tmp = rad;
    PSVECNormalize(axis, &dst);

    tmp2 = tmp * 0.5f;
    tmp3 = sinf(tmp * 0.5f);
    tmp = tmp3;
    tmp3 = cosf(tmp2);

    q->x = tmp * dst.x;
    q->y = tmp * dst.y;
    q->z = tmp * dst.z;
    q->w = tmp3;
}

void C_QUATMtx(Quaternion *r, const Mtx m)
{
    f32 vv0, vv1;
    s32 i, j, k;
    s32 idx[3] = { 1, 2, 0 };
    f32 vec[3];
    vv0 = m[0][0] + m[1][1] + m[2][2];
    if (vv0 > 0.0f) {
        vv1 = (f32)sqrtf(vv0 + 1.0f);
        r->w = vv1 * 0.5f;
        vv1 = 0.5f / vv1;
        r->x = (m[2][1] - m[1][2]) * vv1;
        r->y = (m[0][2] - m[2][0]) * vv1;
        r->z = (m[1][0] - m[0][1]) * vv1;
    }
    else {
        i = 0;
        if (m[1][1] > m[0][0])
            i = 1;
        if (m[2][2] > m[i][i])
            i = 2;
        j = idx[i];
        k = idx[j];
        vv1 = (f32)sqrtf((m[i][i] - (m[j][j] + m[k][k])) + 1.0f);
        vec[i] = vv1 * 0.5f;
        if (vv1 != 0.0f)
            vv1 = 0.5f / vv1;
        r->w = (m[k][j] - m[j][k]) * vv1;
        vec[j] = (m[i][j] + m[j][i]) * vv1;
        vec[k] = (m[i][k] + m[k][i]) * vv1;
        r->x = vec[0];
        r->y = vec[1];
        r->z = vec[2];
    }
}

void C_QUATSlerp(const Quaternion *p, const Quaternion *q, Quaternion *r, f32 t)
{
    f32 ratioA, ratioB;

    f32 value = 1.0f;
    f32 cosHalfTheta = p->x * q->x + p->y * q->y + p->z * q->z + p->w * q->w;

    if (cosHalfTheta < 0.0f) {
        cosHalfTheta = -cosHalfTheta;
        value = -value;
    }

    if (cosHalfTheta <= 0.9999899864196777f) {
        f32 halfTheta = acosf(cosHalfTheta);
        f32 sinHalfTheta = sinf(halfTheta);

        ratioA = sinf((1.0f - t) * halfTheta) / sinHalfTheta;
        ratioB = sinf(t * halfTheta) / sinHalfTheta;
        value *= ratioB;
    }
    else {
        ratioA = 1.0f - t;
        value *= t;
    }

    r->x = (ratioA * p->x) + (value * q->x);
    r->y = (ratioA * p->y) + (value * q->y);
    r->z = (ratioA * p->z) + (value * q->z);
    r->w = (ratioA * p->w) + (value * q->w);
}
