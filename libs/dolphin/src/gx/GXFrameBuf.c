#include <dolphin/gx.h>
#include <dolphin/os.h>

#include <dolphin/gx/GXPriv.h>

GXRenderModeObj GXNtsc240Ds = { 1, 640, 240, 240, 40, 0, 640, 480, 0, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };

GXRenderModeObj GXNtsc240DsAa = { 1, 640, 240, 240, 40, 0, 640, 480, 0, 0, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };

GXRenderModeObj GXNtsc240Int = { 0, 640, 240, 240, 40, 0, 640, 480, 0, 1, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };

GXRenderModeObj GXNtsc240IntAa = { 0, 640, 240, 240, 40, 0, 640, 480, 0, 1, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };

GXRenderModeObj GXNtsc480IntDf = { 0, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 } };

GXRenderModeObj GXNtsc480Int = { 0, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };

GXRenderModeObj GXNtsc480IntAa = { 0, 640, 242, 480, 40, 0, 640, 480, 1, 0, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 } };

GXRenderModeObj GXNtsc480Prog = { 2, 640, 480, 480, 40, 0, 640, 480, 0, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };

GXRenderModeObj GXNtsc480ProgSoft = { 2, 640, 480, 480, 40, 0, 640, 480, 0, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 } };

GXRenderModeObj GXNtsc480ProgAa = { 2, 640, 242, 480, 40, 0, 640, 480, 0, 0, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 } };

GXRenderModeObj GXMpal240Ds = { 9, 640, 240, 240, 40, 0, 640, 480, 0, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal240DsAa = { 9, 640, 240, 240, 40, 0, 640, 480, 0, 0, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal240Int = { 8, 640, 240, 240, 40, 0, 640, 480, 0, 1, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal240IntAa = { 8, 640, 240, 240, 40, 0, 640, 480, 0, 1, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal480IntDf = { 8, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 } };
GXRenderModeObj GXMpal480Int = { 8, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXMpal480IntAa = { 8, 640, 242, 480, 40, 0, 640, 480, 1, 0, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 } };
GXRenderModeObj GXPal264Ds = { 5, 640, 264, 264, 40, 11, 640, 528, 0, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal264DsAa = { 5, 640, 264, 264, 40, 11, 640, 528, 0, 0, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal264Int = { 4, 640, 264, 264, 40, 23, 640, 528, 0, 1, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal264IntAa = { 4, 640, 264, 264, 40, 23, 640, 528, 0, 1, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal528IntDf = { 4, 640, 528, 528, 40, 23, 640, 528, 1, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 } };
GXRenderModeObj GXPal528Int = { 4, 640, 528, 528, 40, 23, 640, 528, 1, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXPal524IntAa = { 4, 640, 264, 524, 40, 23, 640, 524, 1, 0, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 } };
GXRenderModeObj GXEurgb60Hz240Ds = { 21, 640, 240, 240, 40, 0, 640, 480, 0, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXEurgb60Hz240DsAa = { 21, 640, 240, 240, 40, 0, 640, 480, 0, 0, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXEurgb60Hz240Int = { 20, 640, 240, 240, 40, 0, 640, 480, 0, 1, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXEurgb60Hz240IntAa = { 20, 640, 240, 240, 40, 0, 640, 480, 0, 1, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXEurgb60Hz480IntDf = { 20, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 8, 8, 10, 12, 10, 8, 8 } };
GXRenderModeObj GXEurgb60Hz480Int = { 20, 640, 480, 480, 40, 0, 640, 480, 1, 0, 0,
    { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 0, 0, 21, 22, 21, 0, 0 } };
GXRenderModeObj GXEurgb60Hz480IntAa = { 20, 640, 242, 480, 40, 0, 640, 480, 1, 0, 1,
    { 3, 2, 9, 6, 3, 10, 3, 2, 9, 6, 3, 10, 9, 2, 3, 6, 9, 10, 9, 2, 3, 6, 9, 10 }, { 4, 8, 12, 16, 12, 8, 4 } };
GXRenderModeObj GXRmHW = { 1, 320, 240, 240, 40, 0, 640, 480, 0, 0, 0, { 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 },
    { 0, 0, 21, 22, 21, 0, 0 } };

void GXAdjustForOverscan(GXRenderModeObj *rmin, GXRenderModeObj *rmout, u16 hor, u16 ver)
{
    u16 hor2 = hor * 2;
    u16 ver2 = ver * 2;
    u32 verf;
    u32 mode;

    if (rmin != rmout) {
        *rmout = *rmin;
    }

    mode = rmin->viTVmode & 3;
    rmout->fbWidth = rmin->fbWidth - hor2;
    verf = (ver2 * rmin->efbHeight) / (u32)rmin->xfbHeight;
    rmout->efbHeight = rmin->efbHeight - verf;
    if (rmin->xFBmode == VI_XFBMODE_SF && ((rmin->viTVmode & 2) != 2)) {
        rmout->xfbHeight = rmin->xfbHeight - ver;
    }
    else {
        rmout->xfbHeight = rmin->xfbHeight - ver2;
    }

    rmout->viWidth = rmin->viWidth - hor2;
    rmout->viHeight = rmin->viHeight - ver2;
    rmout->viXOrigin = rmin->viXOrigin + hor;
    rmout->viYOrigin = rmin->viYOrigin + ver;
}

void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht)
{
    CHECK_GXBEGIN(0x4D3, "GXSetDispCopySrc");

    gx->cpDispSrc = 0;
    SET_REG_FIELD(0x4D6, gx->cpDispSrc, 10, 0, left);
    SET_REG_FIELD(0x4D7, gx->cpDispSrc, 10, 10, top);
    SET_REG_FIELD(0x4D7, gx->cpDispSrc, 8, 24, 0x49);

    gx->cpDispSize = 0;
    SET_REG_FIELD(0x4DB, gx->cpDispSize, 10, 0, wd - 1);
    SET_REG_FIELD(0x4DC, gx->cpDispSize, 10, 10, ht - 1);
    SET_REG_FIELD(0x4DC, gx->cpDispSize, 8, 24, 0x4A);
}

void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht)
{
    CHECK_GXBEGIN(0x4EF, "GXSetTexCopySrc");

    gx->cpTexSrc = 0;
    SET_REG_FIELD(0x4F2, gx->cpTexSrc, 10, 0, left);
    SET_REG_FIELD(0x4F3, gx->cpTexSrc, 10, 10, top);
    SET_REG_FIELD(0x4F3, gx->cpTexSrc, 8, 24, 0x49);

    gx->cpTexSize = 0;
    SET_REG_FIELD(0x4F7, gx->cpTexSize, 10, 0, wd - 1);
    SET_REG_FIELD(0x4F8, gx->cpTexSize, 10, 10, ht - 1);
    SET_REG_FIELD(0x4F8, gx->cpTexSize, 8, 24, 0x4A);
}

void GXSetDispCopyDst(u16 wd, u16 ht)
{
    u16 stride;

    ASSERTMSGLINE(0x50D, (wd & 0xF) == 0, "GXSetDispCopyDst: Width must be a multiple of 16");
    CHECK_GXBEGIN(0x50E, "GXSetDispCopyDst");

    stride = (int)wd * 2;
    gx->cpDispStride = 0;
    SET_REG_FIELD(0x514, gx->cpDispStride, 10, 0, (stride >> 5));
    SET_REG_FIELD(0x514, gx->cpDispStride, 8, 24, 0x4D);
}

void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap)
{
    u32 rowTiles;
    u32 colTiles;
    u32 cmpTiles;
    u32 peTexFmt;
    u32 peTexFmtH;

    CHECK_GXBEGIN(0x52F, "GXSetTexCopyDst");

    gx->cpTexZ = 0;
    peTexFmt = fmt & 0xF;
    ASSERTMSGLINEV(0x54E, peTexFmt < 13, "%s: invalid texture format", "GXSetTexCopyDst");

    if (fmt == GX_TF_Z16) {
        peTexFmt = 0xB;
    }
    switch (fmt) {
        case GX_TF_I4:
        case GX_TF_I8:
        case GX_TF_IA4:
        case GX_TF_IA8:
        case GX_CTF_YUVA8:
            SET_REG_FIELD(0, gx->cpTex, 2, 15, 3);
            break;
        default:
            SET_REG_FIELD(0, gx->cpTex, 2, 15, 2);
            break;
    }

    gx->cpTexZ = (fmt & _GX_TF_ZTF) == _GX_TF_ZTF;
    peTexFmtH = (peTexFmt >> 3) & 1;
    !peTexFmt;
    SET_REG_FIELD(0x565, gx->cpTex, 1, 3, peTexFmtH);
    peTexFmt = peTexFmt & 7;
    __GetImageTileCount(fmt, wd, ht, &rowTiles, &colTiles, &cmpTiles);

    gx->cpTexStride = 0;
    SET_REG_FIELD(0x56E, gx->cpTexStride, 10, 0, rowTiles * cmpTiles);
    SET_REG_FIELD(0x570, gx->cpTexStride, 8, 24, 0x4D);
    SET_REG_FIELD(0x570, gx->cpTex, 1, 9, mipmap);
    SET_REG_FIELD(0x571, gx->cpTex, 3, 4, peTexFmt);
}

void GXSetDispCopyFrame2Field(GXCopyMode mode)
{
    CHECK_GXBEGIN(0x582, "GXSetDispCopyFrame2Field");
    SET_REG_FIELD(0x583, gx->cpDisp, 2, 12, mode);
    SET_REG_FIELD(0x583, gx->cpTex, 2, 12, 0);
}

void GXSetCopyClamp(GXFBClamp clamp)
{
    u8 clmpB;
    u8 clmpT;

    CHECK_GXBEGIN(0x597, "GXSetCopyClamp");

    clmpT = (clamp & 1) == 1;
    clmpB = (clamp & 2) == 2;

    SET_REG_FIELD(0x59B, gx->cpDisp, 1, 0, clmpT);
    SET_REG_FIELD(0x59C, gx->cpDisp, 1, 1, clmpB);

    SET_REG_FIELD(0x59E, gx->cpTex, 1, 0, clmpT);
    SET_REG_FIELD(0x59F, gx->cpTex, 1, 1, clmpB);
}

static u32 __GXGetNumXfbLines(u32 efbHt, u32 iScale)
{
    u32 count;
    u32 realHt;
    u32 iScaleD;

    count = (efbHt - 1) * 0x100;
    realHt = (count / iScale) + 1;

    iScaleD = iScale;

    if (iScaleD > 0x80 && iScaleD < 0x100) {
        while (iScaleD % 2 == 0) {
            iScaleD /= 2;
        }

        if (efbHt % iScaleD == 0) {
            realHt++;
        }
    }

    if (realHt > 0x400) {
        realHt = 0x400;
    }

    return realHt;
}

u16 GXGetNumXfbLines(u16 efbHeight, f32 yScale)
{
    u32 iScale;
    ASSERTMSGLINE(0x5CE, yScale >= 1.0f, "GXGetNumXfbLines: Vertical scale must be >= 1.0");

    iScale = (u32)(256.0f / yScale) & 0x1FF;
    return __GXGetNumXfbLines(efbHeight, iScale);
}

f32 GXGetYScaleFactor(u16 efbHeight, u16 xfbHeight)
{
    f32 fScale;
    f32 yScale;
    u32 iScale;
    u32 tgtHt;
    u32 realHt;

    ASSERTMSGLINE(0x5E6, xfbHeight <= 1024, "GXGetYScaleFactor: Display copy only supports up to 1024 lines.\n");
    ASSERTMSGLINE(0x5E8, efbHeight <= xfbHeight, "GXGetYScaleFactor: EFB height should not be greater than XFB height.\n");

    tgtHt = xfbHeight;
    yScale = (f32)xfbHeight / (f32)efbHeight;
    iScale = (u32)(256.0f / yScale) & 0x1FF;
    realHt = __GXGetNumXfbLines(efbHeight, iScale);

    while (realHt > xfbHeight) {
        tgtHt--;
        yScale = (f32)tgtHt / (f32)efbHeight;
        iScale = (u32)(256.0f / yScale) & 0x1FF;
        realHt = __GXGetNumXfbLines(efbHeight, iScale);
    }

    fScale = yScale;
    while (realHt < xfbHeight) {
        fScale = yScale;
        tgtHt++;
        yScale = (f32)tgtHt / (f32)efbHeight;
        iScale = (u32)(256.0f / yScale) & 0x1FF;
        realHt = __GXGetNumXfbLines(efbHeight, iScale);
    }

    return fScale;
}

u32 GXSetDispCopyYScale(f32 vscale)
{
	u32 scale;
	GXBool check;
	u32 height;
	u32 reg;

	scale = (u32)(256.0f / vscale) & 0x1FF;
	check = (scale != 0x100);

	reg = 0;
	SET_REG_FIELD(0, reg, 9, 0, scale);
	SET_REG_FIELD(0, reg, 8, 24, 0x4E);
	GX_WRITE_RAS_REG(reg);
	gx->bpSentNot = GX_FALSE;

	SET_REG_FIELD(0, gx->cpDisp, 1, 10, check);

	height = (gx->cpDispSize >> 10 & 0x3FF) + 1;

	return __GXGetNumXfbLines(height, scale);
}

void GXSetCopyClear(GXColor clear_clr, u32 clear_z)
{
    u32 reg;

    CHECK_GXBEGIN(0x63C, "GXSetCopyClear");
    ASSERTMSGLINE(0x63E, clear_z <= 0xFFFFFF, "GXSetCopyClear: Z clear value is out of range");

    reg = 0;
    SET_REG_FIELD(0x641, reg, 8, 0, clear_clr.r);
    SET_REG_FIELD(0x642, reg, 8, 8, clear_clr.a);
    SET_REG_FIELD(0x642, reg, 8, 24, 0x4F);
    GX_WRITE_RAS_REG(reg);

    reg = 0;
    SET_REG_FIELD(0x647, reg, 8, 0, clear_clr.b);
    SET_REG_FIELD(0x648, reg, 8, 8, clear_clr.g);
    SET_REG_FIELD(0x648, reg, 8, 24, 0x50);
    GX_WRITE_RAS_REG(reg);

    reg = 0;
    SET_REG_FIELD(0x64D, reg, 24, 0, clear_z);
    SET_REG_FIELD(0x64D, reg, 8, 24, 0x51);
    GX_WRITE_RAS_REG(reg);
    gx->bpSentNot = 0;
}

void GXSetCopyFilter(GXBool aa, u8 sample_pattern[12][2], GXBool vf, u8 vfilter[7])
{
    u32 msLoc[4];
    u32 coeff0;
    u32 coeff1;

    CHECK_GXBEGIN(0x669, "GXSetCopyFilter");

    if (aa != 0) {
        msLoc[0] = 0;
        SET_REG_FIELD(0x66D, msLoc[0], 4, 0, sample_pattern[0][0]);
        SET_REG_FIELD(0x66E, msLoc[0], 4, 4, sample_pattern[0][1]);
        SET_REG_FIELD(0x66F, msLoc[0], 4, 8, sample_pattern[1][0]);
        SET_REG_FIELD(0x670, msLoc[0], 4, 12, sample_pattern[1][1]);
        SET_REG_FIELD(0x671, msLoc[0], 4, 16, sample_pattern[2][0]);
        SET_REG_FIELD(0x672, msLoc[0], 4, 20, sample_pattern[2][1]);
        SET_REG_FIELD(0x673, msLoc[0], 8, 24, 1);

        msLoc[1] = 0;
        SET_REG_FIELD(0x676, msLoc[1], 4, 0, sample_pattern[3][0]);
        SET_REG_FIELD(0x677, msLoc[1], 4, 4, sample_pattern[3][1]);
        SET_REG_FIELD(0x678, msLoc[1], 4, 8, sample_pattern[4][0]);
        SET_REG_FIELD(0x679, msLoc[1], 4, 12, sample_pattern[4][1]);
        SET_REG_FIELD(0x67A, msLoc[1], 4, 16, sample_pattern[5][0]);
        SET_REG_FIELD(0x67B, msLoc[1], 4, 20, sample_pattern[5][1]);
        SET_REG_FIELD(0x67C, msLoc[1], 8, 24, 2);

        msLoc[2] = 0;
        SET_REG_FIELD(0x67F, msLoc[2], 4, 0, sample_pattern[6][0]);
        SET_REG_FIELD(0x680, msLoc[2], 4, 4, sample_pattern[6][1]);
        SET_REG_FIELD(0x681, msLoc[2], 4, 8, sample_pattern[7][0]);
        SET_REG_FIELD(0x682, msLoc[2], 4, 12, sample_pattern[7][1]);
        SET_REG_FIELD(0x683, msLoc[2], 4, 16, sample_pattern[8][0]);
        SET_REG_FIELD(0x684, msLoc[2], 4, 20, sample_pattern[8][1]);
        SET_REG_FIELD(0x685, msLoc[2], 8, 24, 3);

        msLoc[3] = 0;
        SET_REG_FIELD(0x688, msLoc[3], 4, 0, sample_pattern[9][0]);
        SET_REG_FIELD(0x689, msLoc[3], 4, 4, sample_pattern[9][1]);
        SET_REG_FIELD(0x68A, msLoc[3], 4, 8, sample_pattern[10][0]);
        SET_REG_FIELD(0x68B, msLoc[3], 4, 12, sample_pattern[10][1]);
        SET_REG_FIELD(0x68C, msLoc[3], 4, 16, sample_pattern[11][0]);
        SET_REG_FIELD(0x68D, msLoc[3], 4, 20, sample_pattern[11][1]);
        SET_REG_FIELD(0x68E, msLoc[3], 8, 24, 4);
    }
    else {
        msLoc[0] = 0x01666666;
        msLoc[1] = 0x02666666;
        msLoc[2] = 0x03666666;
        msLoc[3] = 0x04666666;
    }
    GX_WRITE_RAS_REG(msLoc[0]);
    GX_WRITE_RAS_REG(msLoc[1]);
    GX_WRITE_RAS_REG(msLoc[2]);
    GX_WRITE_RAS_REG(msLoc[3]);

    coeff0 = 0;
    SET_REG_FIELD(0, coeff0, 8, 24, 0x53);
    coeff1 = 0;
    SET_REG_FIELD(0, coeff1, 8, 24, 0x54);
    if (vf != 0) {
        SET_REG_FIELD(0x6A6, coeff0, 6, 0, vfilter[0]);
        SET_REG_FIELD(0x6A7, coeff0, 6, 6, vfilter[1]);
        SET_REG_FIELD(0x6A8, coeff0, 6, 12, vfilter[2]);
        SET_REG_FIELD(0x6A9, coeff0, 6, 18, vfilter[3]);
        SET_REG_FIELD(0x6AA, coeff1, 6, 0, vfilter[4]);
        SET_REG_FIELD(0x6AB, coeff1, 6, 6, vfilter[5]);
        SET_REG_FIELD(0x6AC, coeff1, 6, 12, vfilter[6]);
    }
    else {
        SET_REG_FIELD(0, coeff0, 6, 0, 0);
        SET_REG_FIELD(0, coeff0, 6, 6, 0);
        SET_REG_FIELD(0, coeff0, 6, 12, 21);
        SET_REG_FIELD(0, coeff0, 6, 18, 22);
        SET_REG_FIELD(0, coeff1, 6, 0, 21);
        SET_REG_FIELD(0, coeff1, 6, 6, 0);
        SET_REG_FIELD(0, coeff1, 6, 12, 0);
    }
    GX_WRITE_RAS_REG(coeff0);
    GX_WRITE_RAS_REG(coeff1);
    gx->bpSentNot = 0;
}

void GXSetDispCopyGamma(GXGamma gamma)
{
    CHECK_GXBEGIN(0x6CD, "GXSetDispCopyGamma");
    SET_REG_FIELD(0x6CE, gx->cpDisp, 2, 7, gamma);
}

#if DEBUG
static void __GXVerifCopy(void *dest, u8 clear)
{
    u8 clmpT;
    u8 clmpB;
    u32 x0;
    u32 y0;
    u32 dx;
    u32 dy;

    CHECK_GXBEGIN(0x6E2, "GXCopyDisp");

    clmpT = GET_REG_FIELD(gx->cpDisp, 1, 0);
    clmpB = (u32)GET_REG_FIELD(gx->cpDisp, 1, 1);
    x0 = GET_REG_FIELD(gx->cpDispSrc, 10, 0);
    dx = GET_REG_FIELD(gx->cpDispSize, 10, 0) + 1;
    y0 = GET_REG_FIELD(gx->cpDispSrc, 10, 10);
    dy = GET_REG_FIELD(gx->cpDispSize, 10, 10) + 1;

    ASSERTMSGLINE(0x6EC, clmpT || y0 != 0, "GXCopy: Have to set GX_CLAMP_TOP if source top == 0");
    ASSERTMSGLINE(0x6EE, clmpB || y0 + dy <= 528, "GXCopy: Have to set GX_CLAMP_BOTTOM if source bottom > 528");
    ASSERTMSGLINE(0x6F3, (gx->peCtrl & 7) != 3 || clear == 0, "GXCopy: Can not do clear while pixel type is Z");
    if ((u32)(gx->peCtrl & 7) == 5) {
        ASSERTMSGLINE(0x6F9, clear == 0, "GXCopy: Can not clear YUV framebuffer");
        ASSERTMSGLINE(0x6FB, (x0 & 3) == 0, "GXCopy: Source x is not multiple of 4 for YUV copy");
        ASSERTMSGLINE(0x6FD, (y0 & 3) == 0, "GXCopy: Source y is not multiple of 4 for YUV copy");
        ASSERTMSGLINE(0x6FF, (dx & 3) == 0, "GXCopy: Source width is not multiple of 4 for YUV copy");
        ASSERTMSGLINE(0x701, (dy & 3) == 0, "GXCopy: Source height is not multiple of 4 for YUV copy");
    }
    else {
        ASSERTMSGLINE(0x705, (x0 & 1) == 0, "GXCopy: Source x is not multiple of 2 for RGB copy");
        ASSERTMSGLINE(0x707, (y0 & 1) == 0, "GXCopy: Source y is not multiple of 2 for RGB copy");
        ASSERTMSGLINE(0x709, (dx & 1) == 0, "GXCopy: Source width is not multiple of 2 for RGB copy");
        ASSERTMSGLINE(0x70B, (dy & 1) == 0, "GXCopy: Source height is not multiple of 2 for RGB copy");
    }
    ASSERTMSGLINE(0x70F, ((u32)dest & 0x1F) == 0, "GXCopy: Display destination address not 32B aligned");
}
#endif

void GXCopyDisp(void *dest, GXBool clear)
{
    u32 reg;
    u32 tempPeCtrl;
    u32 phyAddr;
    u8 changePeCtrl;

    CHECK_GXBEGIN(0x729, "GXCopyDisp");

#if DEBUG
    __GXVerifCopy(dest, clear);
#endif
    if (clear) {
        reg = gx->zmode;
        SET_REG_FIELD(0, reg, 1, 0, 1);
        SET_REG_FIELD(0, reg, 3, 1, 7);
        GX_WRITE_RAS_REG(reg);

        reg = gx->cmode0;
        SET_REG_FIELD(0, reg, 1, 0, 0);
        SET_REG_FIELD(0, reg, 1, 1, 0);
        GX_WRITE_RAS_REG(reg);
    }
    changePeCtrl = FALSE;
    if ((clear || (u32)GET_REG_FIELD(gx->peCtrl, 3, 0) == 3) && (u32)GET_REG_FIELD(gx->peCtrl, 1, 6) == 1) {
        changePeCtrl = TRUE;
        tempPeCtrl = gx->peCtrl;
        SET_REG_FIELD(0, tempPeCtrl, 1, 6, 0);
        GX_WRITE_RAS_REG(tempPeCtrl);
    }
    GX_WRITE_RAS_REG(gx->cpDispSrc);
    GX_WRITE_RAS_REG(gx->cpDispSize);
    GX_WRITE_RAS_REG(gx->cpDispStride);

    phyAddr = (u32)dest & 0x3FFFFFFF;
    reg = 0;
    SET_REG_FIELD(0x750, reg, 21, 0, phyAddr >> 5);
    SET_REG_FIELD(0x754, reg, 8, 24, 0x4B);
    GX_WRITE_RAS_REG(reg);

    SET_REG_FIELD(0x754, gx->cpDisp, 1, 11, clear);
    SET_REG_FIELD(0x754, gx->cpDisp, 1, 14, 1);
    SET_REG_FIELD(0x754, gx->cpDisp, 8, 24, 0x52);
    GX_WRITE_RAS_REG(gx->cpDisp);

    if (clear) {
        GX_WRITE_RAS_REG(gx->zmode);
        GX_WRITE_RAS_REG(gx->cmode0);
    }
    if (changePeCtrl) {
        GX_WRITE_RAS_REG(gx->peCtrl);
    }
    gx->bpSentNot = 0;
}

void GXCopyTex(void *dest, GXBool clear)
{
    u32 reg;
    u32 tempPeCtrl;
    u32 phyAddr;
    u8 changePeCtrl;

    CHECK_GXBEGIN(0x77C, "GXCopyTex");

#if DEBUG
    __GXVerifCopy(dest, clear);
#endif
    if (clear) {
        reg = gx->zmode;
        SET_REG_FIELD(0, reg, 1, 0, 1);
        SET_REG_FIELD(0, reg, 3, 1, 7);
        GX_WRITE_RAS_REG(reg);

        reg = gx->cmode0;
        SET_REG_FIELD(0, reg, 1, 0, 0);
        SET_REG_FIELD(0, reg, 1, 1, 0);
        GX_WRITE_RAS_REG(reg);
    }
    changePeCtrl = 0;
    tempPeCtrl = gx->peCtrl;
    if (gx->cpTexZ && ((tempPeCtrl & 7) != 3)) {
        changePeCtrl = 1;
        SET_REG_FIELD(0, tempPeCtrl, 3, 0, 3);
    }
    if (((clear != 0) || ((u32)(tempPeCtrl & 7) == 3)) && ((u32)((tempPeCtrl >> 6U) & 1) == 1)) {
        changePeCtrl = 1;
        SET_REG_FIELD(0, tempPeCtrl, 1, 6, 0);
    }
    if (changePeCtrl) {
        GX_WRITE_RAS_REG(tempPeCtrl);
    }
    GX_WRITE_RAS_REG(gx->cpTexSrc);
    GX_WRITE_RAS_REG(gx->cpTexSize);
    GX_WRITE_RAS_REG(gx->cpTexStride);

    phyAddr = (u32)dest & 0x3FFFFFFF;
    reg = 0;
    SET_REG_FIELD(0x7AD, reg, 21, 0, phyAddr >> 5);
    SET_REG_FIELD(0x7AD, reg, 8, 24, 0x4B);
    GX_WRITE_RAS_REG(reg);

    SET_REG_FIELD(0x7B1, gx->cpTex, 1, 11, clear);
    SET_REG_FIELD(0x7B1, gx->cpTex, 1, 14, 0);
    SET_REG_FIELD(0x7B1, gx->cpTex, 8, 24, 0x52);
    GX_WRITE_RAS_REG(gx->cpTex);

    if (clear != 0) {
        GX_WRITE_RAS_REG(gx->zmode);
        GX_WRITE_RAS_REG(gx->cmode0);
    }
    if (changePeCtrl) {
        GX_WRITE_RAS_REG(gx->peCtrl);
    }
    gx->bpSentNot = 0;
}

void GXClearBoundingBox(void)
{
    u32 reg;

    CHECK_GXBEGIN(0x7D3, "GXClearBoundingBox");
    reg = 0x550003FF;
    GX_WRITE_RAS_REG(reg);
    reg = 0x560003FF;
    GX_WRITE_RAS_REG(reg);
    gx->bpSentNot = 0;
}

void GXReadBoundingBox(u16 *left, u16 *top, u16 *right, u16 *bottom)
{
    *left = GX_GET_PE_REG(8);
    *top = GX_GET_PE_REG(10);
    *right = GX_GET_PE_REG(9);
    *bottom = GX_GET_PE_REG(11);
}
