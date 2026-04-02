#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>

#include <dolphin/gx/GXPriv.h>

void GXProject(f32 x, f32 y, f32 z, const f32 mtx[3][4], const f32 *pm, const f32 *vp, f32 *sx, f32 *sy, f32 *sz)
{
    Vec peye;
    f32 xc;
    f32 yc;
    f32 zc;
    f32 wc;

    ASSERTMSGLINE(0xA8, pm && vp && sx && sy && sz, "GXGet*: invalid null pointer");

    peye.x = mtx[0][3] + ((mtx[0][2] * z) + ((mtx[0][0] * x) + (mtx[0][1] * y)));
    peye.y = mtx[1][3] + ((mtx[1][2] * z) + ((mtx[1][0] * x) + (mtx[1][1] * y)));
    peye.z = mtx[2][3] + ((mtx[2][2] * z) + ((mtx[2][0] * x) + (mtx[2][1] * y)));
    if (pm[0] == 0.0f) {
        xc = (peye.x * pm[1]) + (peye.z * pm[2]);
        yc = (peye.y * pm[3]) + (peye.z * pm[4]);
        zc = pm[6] + (peye.z * pm[5]);
        wc = 1.0f / -peye.z;
    }
    else {
        xc = pm[2] + (peye.x * pm[1]);
        yc = pm[4] + (peye.y * pm[3]);
        zc = pm[6] + (peye.z * pm[5]);
        wc = 1.0f;
    }
    *sx = (vp[2] / 2.0f) + (vp[0] + (wc * (xc * vp[2] / 2.0f)));
    *sy = (vp[3] / 2.0f) + (vp[1] + (wc * (-yc * vp[3] / 2.0f)));
    *sz = vp[5] + (wc * (zc * (vp[5] - vp[4])));
}

static void WriteProjPS(const register f32 proj[6], register volatile void *dest)
{
    register f32 p01, p23, p45;

    asm {
        psq_l  p01,  0(proj), 0, 0
        psq_l  p23,  8(proj), 0, 0
        psq_l  p45, 16(proj), 0, 0
        psq_st p01,  0(dest), 0, 0
        psq_st p23,  0(dest), 0, 0
        psq_st p45,  0(dest), 0, 0
    }
}

static void __GXSetProjection(void)
{
    u32 reg = 0x00061020;
    GX_WRITE_U8(0x10);
    GX_WRITE_U32(reg);
    GX_WRITE_XF_REG_F(32, gx->projMtx[0]);
    GX_WRITE_XF_REG_F(33, gx->projMtx[1]);
    GX_WRITE_XF_REG_F(34, gx->projMtx[2]);
    GX_WRITE_XF_REG_F(35, gx->projMtx[3]);
    GX_WRITE_XF_REG_F(36, gx->projMtx[4]);
    GX_WRITE_XF_REG_F(37, gx->projMtx[5]);
    GX_WRITE_XF_REG_2(38, gx->projType);
}

void GXSetProjection(f32 mtx[4][4], GXProjectionType type)
{
    CHECK_GXBEGIN(0x127, "GXSetProjection");

    gx->projType = type;
    gx->projMtx[0] = mtx[0][0];
    gx->projMtx[2] = mtx[1][1];
    gx->projMtx[4] = mtx[2][2];
    gx->projMtx[5] = mtx[2][3];
    if (type == GX_ORTHOGRAPHIC) {
        gx->projMtx[1] = mtx[0][3];
        gx->projMtx[3] = mtx[1][3];
    }
    else {
        gx->projMtx[1] = mtx[0][2];
        gx->projMtx[3] = mtx[1][2];
    }

    __GXSetProjection();
    gx->bpSentNot = 1;
}

#define qr0 0

void GXGetProjectionv(f32 *ptr)
{
    ASSERTMSGLINE(0x172, ptr, "GXGet*: invalid null pointer");

    ptr[0] = gx->projType;

    ptr[1] = gx->projMtx[0];
    ptr[2] = gx->projMtx[1];
    ptr[3] = gx->projMtx[2];
    ptr[4] = gx->projMtx[3];
    ptr[5] = gx->projMtx[4];
    ptr[6] = gx->projMtx[5];
}

static void WriteMTXPS4x3(const register f32 mtx[3][4], register volatile f32 *dest)
{
    register f32 a00_a01;
    register f32 a02_a03;
    register f32 a10_a11;
    register f32 a12_a13;
    register f32 a20_a21;
    register f32 a22_a23;

    asm {
        psq_l a00_a01, 0x00(mtx), 0, qr0
        psq_l a02_a03, 0x08(mtx), 0, qr0
        psq_l a10_a11, 0x10(mtx), 0, qr0
        psq_l a12_a13, 0x18(mtx), 0, qr0
        psq_l a20_a21, 0x20(mtx), 0, qr0
        psq_l a22_a23, 0x28(mtx), 0, qr0
        psq_st a00_a01, 0(dest), 0, qr0
        psq_st a02_a03, 0(dest), 0, qr0
        psq_st a10_a11, 0(dest), 0, qr0
        psq_st a12_a13, 0(dest), 0, qr0
        psq_st a20_a21, 0(dest), 0, qr0
        psq_st a22_a23, 0(dest), 0, qr0
    }
}

static void WriteMTXPS3x3from3x4(register f32 mtx[3][4], register volatile f32 *dest)
{
    register f32 a00_a01;
    register f32 a02_a03;
    register f32 a10_a11;
    register f32 a12_a13;
    register f32 a20_a21;
    register f32 a22_a23;

    asm {
        psq_l  a00_a01, 0x00(mtx), 0, qr0
        lfs    a02_a03, 0x08(mtx)
        psq_l  a10_a11, 0x10(mtx), 0, qr0
        lfs    a12_a13, 0x18(mtx)
        psq_l  a20_a21, 0x20(mtx), 0, qr0
        lfs    a22_a23, 0x28(mtx)
        psq_st a00_a01, 0(dest), 0, qr0
        stfs   a02_a03, 0(dest)
        psq_st a10_a11, 0(dest), 0, qr0
        stfs   a12_a13, 0(dest)
        psq_st a20_a21, 0(dest), 0, qr0
        stfs   a22_a23, 0(dest)
    }
}

static void WriteMTXPS4x2(const register f32 mtx[2][4], register volatile f32 *dest)
{
    register f32 a00_a01;
    register f32 a02_a03;
    register f32 a10_a11;
    register f32 a12_a13;

    asm {
        psq_l a00_a01, 0x00(mtx), 0, qr0
        psq_l a02_a03, 0x08(mtx), 0, qr0
        psq_l a10_a11, 0x10(mtx), 0, qr0
        psq_l a12_a13, 0x18(mtx), 0, qr0
        psq_st a00_a01, 0(dest), 0, qr0
        psq_st a02_a03, 0(dest), 0, qr0
        psq_st a10_a11, 0(dest), 0, qr0
        psq_st a12_a13, 0(dest), 0, qr0
    }
}

#pragma peephole off
#pragma dont_inline on
void GXLoadPosMtxImm(f32 mtx[3][4], u32 id)
{
    u32 reg;
    u32 addr;

    CHECK_GXBEGIN(0x1FB, "GXLoadPosMtxImm");

    addr = id * 4;
    reg = addr | 0xB0000;

    GX_WRITE_U8(0x10);
    GX_WRITE_U32(reg);
    WriteMTXPS4x3(mtx, &GXWGFifo.f32);
}

void GXLoadNrmMtxImm(f32 mtx[3][4], u32 id)
{
    u32 reg;
    u32 addr;

    CHECK_GXBEGIN(0x24C, "GXLoadNrmMtxImm");

    addr = id * 3 + 0x400;
    reg = addr | 0x80000;

    GX_WRITE_U8(0x10);
    GX_WRITE_U32(reg);
    WriteMTXPS3x3from3x4((void *)mtx, &GXWGFifo.f32);
}

void GXSetCurrentMtx(u32 id)
{
    CHECK_GXBEGIN(0x2C4, "GXSetCurrentMtx");
    SET_REG_FIELD(0x2C8, gx->matIdxA, 6, 0, id);
    __GXSetMatrixIndex(GX_VA_PNMTXIDX);
}

void GXLoadTexMtxImm(f32 mtx[][4], u32 id, GXTexMtxType type)
{
    u32 reg;
    u32 addr;
    u32 count;

    CHECK_GXBEGIN(0x2E5, "GXLoadTexMtxImm");

    if (id >= GX_PTTEXMTX0) {
        addr = (id - GX_PTTEXMTX0) * 4 + 0x500;
        ASSERTMSGLINE(0x2EF, type == GX_MTX3x4, "GXLoadTexMtx: Invalid matrix type");
    }
    else {
        addr = id * 4;
    }
    count = (type == GX_MTX2x4) ? 8 : 12;
    reg = addr | ((count - 1) << 16);

    GX_WRITE_U8(0x10);
    GX_WRITE_U32(reg);
    if (type == GX_MTX3x4) {
        WriteMTXPS4x3(mtx, &GXWGFifo.f32);
    }
    else {
        WriteMTXPS4x2(mtx, &GXWGFifo.f32);
    }
}
#pragma dont_inline reset

void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field)
{
    f32 sx;
    f32 sy;
    f32 sz;
    f32 ox;
    f32 oy;
    f32 oz;
    f32 zmin;
    f32 zmax;
    u32 reg;

    CHECK_GXBEGIN(0x387, "GXSetViewport"); // not the correct function name

    if (field == 0) {
        top -= 0.5f;
    }
    sx = wd / 2.0f;
    sy = -ht / 2.0f;
    ox = 342.0f + (left + (wd / 2.0f));
    oy = 342.0f + (top + (ht / 2.0f));
    zmin = 1.6777215e7f * nearz;
    zmax = 1.6777215e7f * farz;
    sz = zmax - zmin;
    oz = zmax;
    gx->vpLeft = left;
    gx->vpTop = top;
    gx->vpWd = wd;
    gx->vpHt = ht;
    gx->vpNearz = nearz;
    gx->vpFarz = farz;
    if (gx->fgRange != 0) {
        __GXSetRange(nearz, gx->fgSideX);
    }
    reg = 0x5101A;
    GX_WRITE_U8(0x10);
    GX_WRITE_U32(reg);
    GX_WRITE_XF_REG_F(26, sx);
    GX_WRITE_XF_REG_F(27, sy);
    GX_WRITE_XF_REG_F(28, sz);
    GX_WRITE_XF_REG_F(29, ox);
    GX_WRITE_XF_REG_F(30, oy);
    GX_WRITE_XF_REG_F(31, oz);
    gx->bpSentNot = 1;
}

void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz)
{
    GXSetViewportJitter(left, top, wd, ht, nearz, farz, 1U);
}

void GXGetViewportv(f32 *vp)
{
    ASSERTMSGLINE(0x3C8, vp, "GXGet*: invalid null pointer");

    vp[0] = gx->vpLeft;
    vp[1] = gx->vpTop;
    vp[2] = gx->vpWd;
    vp[3] = gx->vpHt;
    vp[4] = gx->vpNearz;
    vp[5] = gx->vpFarz;
}

// maybe get it from melee?
void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht)
{
    u32 tp;
    u32 lf;
    u32 bm;
    u32 rt;

    CHECK_GXBEGIN(0x418, "GXSetScissor");
    ASSERTMSGLINE(0x419, left < 1706, "GXSetScissor: Left origin > 1708");
    ASSERTMSGLINE(0x41A, top < 1706, "GXSetScissor: top origin > 1708");
    ASSERTMSGLINE(0x41B, left + wd < 1706, "GXSetScissor: right edge > 1708");
    ASSERTMSGLINE(0x41C, top + ht < 1706, "GXSetScissor: bottom edge > 1708");

    tp = top + 342;
    lf = left + 342;
    bm = tp + ht - 1;
    rt = lf + wd - 1;

    SET_REG_FIELD(0x423, gx->suScis0, 11, 0, tp);
    SET_REG_FIELD(0x424, gx->suScis0, 11, 12, lf);
    SET_REG_FIELD(0x426, gx->suScis1, 11, 0, bm);
    SET_REG_FIELD(0x427, gx->suScis1, 11, 12, rt);

    GX_WRITE_RAS_REG(gx->suScis0);
    GX_WRITE_RAS_REG(gx->suScis1);
    gx->bpSentNot = 0;
}

void GXSetScissorBoxOffset(s32 x_off, s32 y_off)
{
    u32 reg = 0;
    u32 hx;
    u32 hy;

    CHECK_GXBEGIN(0x45F, "GXSetScissorBoxOffset");

    ASSERTMSGLINE(0x462, (u32)(x_off + 342) < 2048, "GXSetScissorBoxOffset: Invalid X offset");
    ASSERTMSGLINE(0x464, (u32)(y_off + 342) < 2048, "GXSetScissorBoxOffset: Invalid Y offset");

    hx = (u32)(x_off + 342) >> 1;
    hy = (u32)(y_off + 342) >> 1;

    SET_REG_FIELD(0x469, reg, 10, 0, hx);
    SET_REG_FIELD(0x46A, reg, 10, 10, hy);
    SET_REG_FIELD(0x46B, reg, 8, 24, 0x59);
    GX_WRITE_RAS_REG(reg);
    gx->bpSentNot = 0;
}
#pragma peephole on

void GXSetClipMode(GXClipMode mode)
{
    CHECK_GXBEGIN(0x47F, "GXSetClipMode");
    GX_WRITE_XF_REG(5, mode);
    gx->bpSentNot = 1;
}

void __GXSetMatrixIndex(GXAttr matIdxAttr)
{
    if (matIdxAttr < GX_VA_TEX4MTXIDX) {
        GX_WRITE_SOME_REG4(8, 0x30, gx->matIdxA, -12);
        GX_WRITE_XF_REG(24, gx->matIdxA);
    }
    else {
        GX_WRITE_SOME_REG4(8, 0x40, gx->matIdxB, -12);
        GX_WRITE_XF_REG(25, gx->matIdxB);
    }
    gx->bpSentNot = 1;
}
