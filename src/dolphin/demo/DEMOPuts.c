#include "stdarg.h"
#include "stdio.h"
#include <dolphin.h>
#include <dolphin/demo.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#include <dolphin/demoPriv.h>

extern unsigned long DEMOFontBitmap[]; // size: 0x0, address: 0x0

// .bss
static struct _GXTexObj fontTexObj; // size: 0x20, address: 0x0

// .sbss
static long fontShift; // size: 0x4, address: 0x0

// functions
static void DrawFontChar(int x, int y, int z, int xChar, int yChar);
static void LoadSheet(void *image, enum _GXTexMapID texMapID);

void DEMOSetFontType(DMFontType attr)
{
    switch (attr) {
        case DM_FT_RVS:
            GXSetBlendMode(2, 0, 0, 0xC);
            break;
        case DM_FT_XLU:
            GXSetBlendMode(1, 1, 1, 0);
            break;
        case DM_FT_OPQ:
        default:
            GXSetBlendMode(1, 1, 0, 0);
            break;
    }
}

void DEMOLoadFont(enum _GXTexMapID texMap, enum _GXTexMtx texMtx, DMTexFlt texFlt)
{
    float fontTMtx[3][4];
    unsigned short width;
    unsigned short height;

    width = 64;
    height = 0x1800 / width;
    GXInitTexObj(&fontTexObj, (void *)DEMOFontBitmap, width, (u16)height, 0, 0, 0, 0);
    if (texFlt == 0) {
        GXInitTexObjLOD(&fontTexObj, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f);
        fontShift = 0;
    }
    GXLoadTexObj(&fontTexObj, texMap);
    MTXScale(fontTMtx, 1.0f / width, 1.0f / height, 1.0f);
    GXLoadTexMtxImm(fontTMtx, texMtx, 1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(0, 1, 4, texMtx);
#ifdef TARGET_PC
  GXDestroyTexObj(&fontTexObj);
#endif
}

void DEMOSetupScrnSpc(long width, long height, float depth)
{
    float pMtx[4][4];
    float mMtx[3][4];

    MTXOrtho(pMtx, 0.0f, height, 0.0f, width, 0.0f, -depth);
    GXSetProjection(pMtx, 1);
    MTXIdentity(mMtx);
    GXLoadPosMtxImm(mMtx, 0);
    GXSetCurrentMtx(0);
}

void DEMOInitCaption(long font_type, long width, long height)
{
    DEMOSetupScrnSpc(width, height, 100.0f);
    GXSetZMode(1, 7, 1);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetTevOp(0, 3);
    GXSetTevOrder(0, 0, 0, 0xFF);
    DEMOLoadFont(0, 0x1E, 0);
    DEMOSetFontType(font_type);
}

void DEMOPuts(s16 x, s16 y, s16 z, char *string)
{
    char *str;
    long s;
    long t;
    long c;
    long w;
    long len;
    long i;

    str = string;
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 3, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 3, 1);

    // calc len
    len = 0;
    while (1) {
        c = *(str++);
        if ((c >= 0x20) && (c <= 0x7F)) {
            len++;
            continue;
        }

        if (len > 0) {
            GXBegin(0x80, 0, len * 4);
            for (i = 0; i < len; i++) {
                w = string[i] - 0x20;
                s = fontShift + ((w % 8) * 0x10);
                t = fontShift + ((w / 8) * 0x10);
                GXPosition3s16(x + (i * 8), y, z);
                GXTexCoord2s16(s, t);
                GXPosition3s16(x + (i * 8) + 8, y, z);
                GXTexCoord2s16(s + 0x10, t);
                GXPosition3s16(x + (i * 8) + 8, y + 8, z);
                GXTexCoord2s16(s + 0x10, t + 0x10);
                GXPosition3s16(x + (i * 8), y + 8, z);
                GXTexCoord2s16(s, t + 0x10);
            }
            GXEnd();
            len = 0;
        }

        string = str;
        if (c == 0xA) {
            y += 0x8;
        }
        else {
            break;
        }
    }
}

void DEMOPrintf(s16 x, s16 y, s16 z, char *fmt, ...)
{
    va_list vlist;
    char buf[256];

    va_start(vlist, fmt);
    vsprintf(buf, fmt, vlist);
    DEMOPuts(x, y, z, buf);
    va_end(vlist);
}
