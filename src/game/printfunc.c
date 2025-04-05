#include "game/printfunc.h"
#include "dolphin.h"
#include "game/disp.h"
#include "game/init.h"

#include "stdarg.h"
#include "stdio.h"

extern u8 ank8x8_4b[];

struct strline_data {
    u16 type;
    u16 color;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 empstrline_next;
    float scale;
    char str[80];
    GXColor win_color;
};

static struct strline_data strline[256];
static char pfStrBuf[256];

int fontcolor;
u16 empstrline;
u16 strlinecnt;
BOOL saftyFrameF;

static void WireDraw(void);

static GXColor ATTRIBUTE_ALIGN(32) fcoltbl[16] = { { 0, 0, 0, 255 }, { 0, 0, 128, 255 }, { 128, 0, 0, 255 }, { 128, 0, 128, 255 }, { 0, 128, 0, 255 },
    { 0, 128, 128, 255 }, { 128, 128, 0, 255 }, { 128, 128, 128, 255 }, { 128, 128, 128, 128 }, { 0, 0, 255, 255 }, { 255, 0, 0, 255 },
    { 255, 0, 255, 255 }, { 0, 255, 0, 255 }, { 0, 255, 255, 255 }, { 255, 255, 0, 255 }, { 255, 255, 255, 255 } };

void pfInit(void)
{
    int i;
    fontcolor = 15;
    empstrline = 0;

    for (i = 0; i < 256; i++) {
        strline[i].str[0] = 0;
    }
    pfClsScr();
}

void pfClsScr(void)
{
    int i;
    empstrline = 0;
    strlinecnt = 0;
    for (i = 0; i < 256; i++) {
        strline[i].empstrline_next = i + 1;
        strline[i].type = 0;
        if (strline[i].str[0] != 0) {
            strline[i].str[0] = 0;
        }
    }
}

s16 print8(s16 x, s16 y, float scale, char *str, ...)
{
    struct strline_data *strline_curr;
    char *src = pfStrBuf;
    char *dst;
    s16 ret;
    va_list list;
    strline_curr = &strline[empstrline];
    if (strlinecnt >= 256) {
        return -1;
    }
    va_start(list, str);
    vsprintf(pfStrBuf, str, list);
    strlinecnt++;
    ret = empstrline;
    empstrline = strline_curr->empstrline_next;
    strline_curr->type = 0;
    strline_curr->color = fontcolor;
    strline_curr->x = x;
    strline_curr->y = y;
    strline_curr->scale = scale;
    dst = strline_curr->str;
    while (*src) {
        *dst++ = *src++;
    }
    *dst = 0;
    va_end(list);
    return ret;
}

s16 printWin(s16 x, s16 y, s16 w, s16 h, GXColor *color)
{
    struct strline_data *strline_curr;
    s16 ret;
    char *src = pfStrBuf;
    strline_curr = &strline[empstrline];
    if (strlinecnt >= 256) {
        return -1;
    }
    strlinecnt++;
    ret = empstrline;
    empstrline = strline_curr->empstrline_next;
    strline_curr->type = 1;
    strline_curr->win_color.r = color->r;
    strline_curr->win_color.g = color->g;
    strline_curr->win_color.b = color->b;
    strline_curr->win_color.a = color->a;
    strline_curr->x = x;
    strline_curr->y = y;
    strline_curr->w = w;
    strline_curr->h = h;
    return ret;
}

void pfDrawFonts(void)
{
    GXTexObj font_tex;
    Mtx44 proj;
    Mtx modelview;
    int i;
    s16 x, y, w, h;

    u16 strline_count = strlinecnt;
    if (saftyFrameF) {
        WireDraw();
    }
    MTXOrtho(proj, 0, HU_FB_HEIGHT, 0, HU_FB_WIDTH, 0, 10);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    MTXIdentity(modelview);
    GXLoadPosMtxImm(modelview, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetViewport(0, 0, RenderMode->fbWidth, RenderMode->efbHeight, 0, 1);
    GXSetScissor(0, 0, RenderMode->fbWidth, RenderMode->efbHeight);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSETARRAY(GX_VA_CLR0, fcoltbl, sizeof(fcoltbl), sizeof(GXColor));
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXInvalidateTexAll();
    GXInitTexObj(&font_tex, ank8x8_4b, 128, 128, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&font_tex, GX_NEAR, GX_NEAR, 0, 0, 0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&font_tex, GX_TEXMAP0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaUpdate(GX_TRUE);
    for (i = 0; i < 256; i++) {
        x = strline[i].x;
        y = strline[i].y;
        if (strline[i].type == 1) {
            w = strline[i].w;
            h = strline[i].h;
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
            GXSetTevColor(GX_TEVREG0, strline[i].win_color);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetNumTevStages(1);
            GXSetNumTexGens(0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition2s16(x, y);
            GXPosition2s16(x + w, y);
            GXPosition2s16(x + w, y + h);
            GXPosition2s16(x, y + h);
            GXEnd();
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
            GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
            GXSETARRAY(GX_VA_CLR0, fcoltbl, sizeof(fcoltbl), sizeof(GXColor));
            GXSetNumTevStages(1);
            GXSetNumTexGens(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
            GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        }
        else {
            if (strline[i].str[0] != '\0') {
                float shadow_ofs_x, shadow_ofs_y;
                float char_w;
                float char_h;
                float texcoord_x, texcoord_y;
                char *str;
                u16 color;
                s16 shadow_color;
                float scale;
                char_w = char_h = 8.0f * strline[i].scale;
                str = strline[i].str;
                color = strline[i].color;
                shadow_color = -1;
                scale = 1.0f;
                while (*str) {
                    char c = *str++;
                    switch (c) {
                        case 255:
                            c = *str++;
                            scale = c / 16.0f;
                            char_w = 8.0f * strline[i].scale * scale;
                            char_h = 8.0f * strline[i].scale * scale;
                            break;

                        case 254:
                            color = (*str++) - 1;
                            break;

                        case 253:
                            shadow_color = (*str++) - 1;
                            shadow_ofs_x = 1.3333333f * strline[i].scale * scale;
                            shadow_ofs_y = 1.3333333f * strline[i].scale * scale;
                            break;

                        default:
                            texcoord_x = (c % 16) / 16.0f;
                            texcoord_y = ((c / 16) / 16.0f) + (1 / 128.0f);
                            if (shadow_color < 0) {
                                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                                GXPosition3s16(x, y, 0);
                                GXColor1x8(color);
                                GXTexCoord2f32(texcoord_x, texcoord_y);
                                GXPosition3s16(x + char_w, y, 0);
                                GXColor1x8(color);
                                GXTexCoord2f32(texcoord_x + (1 / 16.0f), texcoord_y);
                                GXPosition3s16(x + char_w, y + char_h, 0);
                                GXColor1x8(color);
                                GXTexCoord2f32(texcoord_x + (1 / 16.0f), texcoord_y + (1 / 16.0f));
                                GXPosition3s16(x, y + char_h, 0);
                                GXColor1x8(color);
                                GXTexCoord2f32(texcoord_x, texcoord_y + (1 / 16.0f));
                                GXEnd();
                            }
                            else {
                                GXBegin(GX_QUADS, GX_VTXFMT0, 8);
                                GXPosition3s16(x + shadow_ofs_x, y + shadow_ofs_y, 0);
                                GXColor1x8(shadow_color);
                                GXTexCoord2f32(texcoord_x, texcoord_y);
                                GXPosition3s16(x + char_w + shadow_ofs_x, y + shadow_ofs_y, 0);
                                GXColor1x8(shadow_color);
                                GXTexCoord2f32(texcoord_x + (1 / 16.0f), texcoord_y);
                                GXPosition3s16(x + char_w + shadow_ofs_x, y + char_h + shadow_ofs_y, 0);
                                GXColor1x8(shadow_color);
                                GXTexCoord2f32(texcoord_x + (1 / 16.0f), texcoord_y + (1 / 16.0f));
                                GXPosition3s16(x + shadow_ofs_x, y + char_h + shadow_ofs_y, 0);
                                GXColor1x8(shadow_color);
                                GXTexCoord2f32(texcoord_x, texcoord_y + (1 / 16.0f));
                                GXPosition3s16(x, y, 0);
                                GXColor1x8(color);
                                GXTexCoord2f32(texcoord_x, texcoord_y);
                                GXPosition3s16(x + char_w, y, 0);
                                GXColor1x8(color);
                                GXTexCoord2f32(texcoord_x + (1 / 16.0f), texcoord_y);
                                GXPosition3s16(x + char_w, y + char_h, 0);
                                GXColor1x8(color);
                                GXTexCoord2f32(texcoord_x + (1 / 16.0f), texcoord_y + (1 / 16.0f));
                                GXPosition3s16(x, y + char_h, 0);
                                GXColor1x8(color);
                                GXTexCoord2f32(texcoord_x, texcoord_y + (1 / 16.0f));
                                GXEnd();
                            }
                            x += char_w;
                            if (x > HU_FB_WIDTH) {
                                x = 0;
                                y += char_h;
                            }
                            break;
                    }
                }
            }
        }
    }
}

#define SAFETY_W 16
#define SAFETY_H 40

static void WireDraw(void)
{
    Mtx44 proj;
    Mtx modelview;
    MTXOrtho(proj, 0, HU_DISP_HEIGHT, 0, HU_DISP_WIDTH, 0, 10);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    if (RenderMode->field_rendering) {
        GXSetViewportJitter(0, 0, HU_FB_WIDTH, HU_FB_HEIGHT, 0, 1, VIGetNextField());
    }
    else {
        GXSetViewport(0, 0, HU_FB_WIDTH, HU_FB_HEIGHT, 0, 1);
    }
    GXSetScissor(0, 0, HU_FB_WIDTH, HU_FB_HEIGHT);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGB, GX_RGB8, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    MTXIdentity(modelview);
    GXLoadPosMtxImm(modelview, GX_PNMTX0);
    GXBegin(GX_LINES, 0, 8);
    GXPosition2f32(SAFETY_W, SAFETY_H);
    GXColor3u8(255, 0, 0);
    GXPosition2f32(SAFETY_W, HU_DISP_HEIGHT - SAFETY_H);
    GXColor3u8(255, 0, 0);
    GXPosition2f32(SAFETY_W, SAFETY_H);
    GXColor3u8(255, 0, 0);
    GXPosition2f32(HU_DISP_WIDTH - SAFETY_W, SAFETY_H);
    GXColor3u8(255, 0, 0);
    GXPosition2f32(HU_DISP_WIDTH - SAFETY_W, HU_DISP_HEIGHT - SAFETY_H);
    GXColor3u8(255, 0, 0);
    GXPosition2f32(HU_DISP_WIDTH - SAFETY_W, SAFETY_H);
    GXColor3u8(255, 0, 0);
    GXPosition2f32(HU_DISP_WIDTH - SAFETY_W, HU_DISP_HEIGHT - SAFETY_H);
    GXColor3u8(255, 0, 0);
    GXPosition2f32(SAFETY_W, HU_DISP_HEIGHT - SAFETY_H);
    GXColor3u8(255, 0, 0);
    GXEnd();
}
