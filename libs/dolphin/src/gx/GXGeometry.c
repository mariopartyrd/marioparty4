#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <stddef.h>

#include <dolphin/gx/GXPriv.h>

void __GXSetDirtyState(void)
{
    if (gx->dirtyState & 1) {
        __GXSetSUTexRegs();
    }
    if (gx->dirtyState & 2) {
        __GXUpdateBPMask();
    }
    if (gx->dirtyState & 4) {
        __GXSetGenMode();
    }
    if (gx->dirtyState & 8) {
        __GXSetVCD();
    }
    if (gx->dirtyState & 0x10) {
        __GXSetVAT();
    }
    if (gx->dirtyState & 0x18) {
        __GXCalculateVLim();
    }
    gx->dirtyState = 0;
}

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts)
{
    ASSERTMSGLINE(0x167, vtxfmt < 8, "GXBegin: Format Index is out of range");
    ASSERTMSGLINE(0x168, !__GXinBegin, "GXBegin: called inside another GXBegin/GXEnd");

    if (gx->dirtyState != 0) {
        __GXSetDirtyState();
    }
    if (*(u32 *)&gx->vNumNot == 0) { // checks both vNum and bpSentNot
        __GXSendFlushPrim();
    }
    GX_WRITE_U8(vtxfmt | type);
    GX_WRITE_U16(nverts);
}

void __GXSendFlushPrim(void)
{
    u32 i;
    u32 numD = gx->vNum * gx->vLim;

    GX_WRITE_U8(0x98);
    GX_WRITE_U16(gx->vNum);
    for (i = 0; i < numD; i += 4) {
        GX_WRITE_U32(0);
    }
    gx->bpSentNot = 1;
}

void GXSetLineWidth(u8 width, GXTexOffset texOffsets)
{
    CHECK_GXBEGIN(0x1B8, "GXSetLineWidth");
    SET_REG_FIELD(0x1B9, gx->lpSize, 8, 0, width);
    SET_REG_FIELD(0x1BA, gx->lpSize, 3, 16, texOffsets);
    GX_WRITE_RAS_REG(gx->lpSize);
    gx->bpSentNot = 0;
}

void GXGetLineWidth(u8 *width, GXTexOffset *texOffsets)
{
    ASSERTMSGLINE(0x1CF, width != NULL && texOffsets != NULL, "GXGet*: invalid null pointer");

    *width = GET_REG_FIELD(gx->lpSize, 8, 0);
    *texOffsets = GET_REG_FIELD(gx->lpSize, 3, 16);
}

void GXSetPointSize(u8 pointSize, GXTexOffset texOffsets)
{
    CHECK_GXBEGIN(0x1E4, "GXSetPointSize");
    SET_REG_FIELD(0x1E5, gx->lpSize, 8, 8, pointSize);
    SET_REG_FIELD(0x1E6, gx->lpSize, 3, 19, texOffsets);
    GX_WRITE_RAS_REG(gx->lpSize);
    gx->bpSentNot = 0;
}

void GXGetPointSize(u8 *pointSize, GXTexOffset *texOffsets)
{
    ASSERTMSGLINE(0x1FB, pointSize != NULL && texOffsets != NULL, "GXGet*: invalid null pointer");

    *pointSize = (int)GET_REG_FIELD(gx->lpSize, 8, 8);
    *texOffsets = GET_REG_FIELD(gx->lpSize, 3, 19);
}

void GXEnableTexOffsets(GXTexCoordID coord, u8 line_enable, u8 point_enable)
{
    CHECK_GXBEGIN(0x211, "GXEnableTexOffsets");

    ASSERTMSGLINE(0x213, coord < 8, "GXEnableTexOffsets: Invalid coordinate Id");

    SET_REG_FIELD(0x215, gx->suTs0[coord], 1, 18, line_enable);
    SET_REG_FIELD(0x216, gx->suTs0[coord], 1, 19, point_enable);
    GX_WRITE_RAS_REG(gx->suTs0[coord]);
    gx->bpSentNot = 0;
}

void GXSetCullMode(GXCullMode mode)
{
    GXCullMode hwMode;

    CHECK_GXBEGIN(0x21D, "GXSetCullMode");
    switch (mode) {
        case GX_CULL_FRONT:
            hwMode = GX_CULL_BACK;
            break;
        case GX_CULL_BACK:
            hwMode = GX_CULL_FRONT;
            break;
        default:
            hwMode = mode;
            break;
    }
    SET_REG_FIELD(0x225, gx->genMode, 2, 14, hwMode);
    gx->dirtyState |= 4;
}

void GXGetCullMode(GXCullMode *mode)
{
    GXCullMode hwMode = gx->genMode;
    *mode = ((hwMode >> 0xD) & 0x2) | (((((int)hwMode >> 0xE) & 0x2) >> 0x1));
}

void GXSetCoPlanar(GXBool enable)
{
    u32 reg;

    CHECK_GXBEGIN(0x265, "GXSetCoPlanar");

    SET_REG_FIELD(0x267, gx->genMode, 1, 19, enable);
    reg = 0xFE080000;
    GX_WRITE_RAS_REG(reg);
    GX_WRITE_RAS_REG(gx->genMode);
}

void __GXSetGenMode(void)
{
    GX_WRITE_RAS_REG(gx->genMode);
    gx->bpSentNot = 0;
}
