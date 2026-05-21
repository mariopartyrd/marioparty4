#include "game/fault.h"
#include <stdarg.h>
#include <stdio.h>

typedef struct Xfb_Color_s {
    u8 y;
    u8 cb;
    u8 cr;
} XFB_COLOR;

typedef struct Xfb_Geometry_s {
    void* fb[4];
    u16 width;
    u16 height;
    u16 mode;
} XFB_GEOMETRY;

static XFB_COLOR XFB_Colors[5] = {
    { 0x00, 0x80, 0x80 },
    { 0xFF, 0x80, 0x80 },
    { 0xC0, 0x80, 0x80 },
    { 0x80, 0x80, 0x80 },
    { 0x40, 0x80, 0x80 }
};

#include "Ascii8x8_1bpp.inc"

static XFB_GEOMETRY XFB_Geometry;

static s32 (*XFB_putc)(u8 c, s32 x, s32 y);

static XFB_COLOR Draw_Color;

static s32 x_start;
static s32 y_start;

static s32 XFB_putcProgressive(u8 arg0, s32 arg1, s32 arg2);
static s32 XFB_putcInterlace(u8 arg0, s32 arg1, s32 arg2);
static s32 XFB_puts(s8* arg0, s32 arg1, s32 arg2);
static s32 XFB_putcS(u8 arg0, s32 arg1, s32 arg2);
static void XFB_WriteBackCache(void);
static void XFB_CR(s32 value, s32* arg1, s32* arg2);

void OSPanic(const char* file, int line, const char* msg, ...) {
    static char* titleMes = "OSPanic encounterd:";
    
    va_list sp78;
    s32 sp74;
    s32 sp70;
    char sp84[1024];
    s32 puts;

    sp74 = x_start = 0x10;
    sp70 = y_start = 0x20;
    puts = XFB_puts((s8*)titleMes, sp74, sp70);
    XFB_CR(puts + 1, &sp74, &sp70);
    sprintf(sp84, "%s:%d", file, line);
    puts = XFB_puts((s8*)sp84, sp74, sp70);
    XFB_CR(puts, &sp74, &sp70);
    va_start(sp78, msg);
    vsnprintf(sp84, 0x400U, msg, &sp78[0]);
    puts = XFB_puts((s8*)sp84, sp74, sp70);
    XFB_CR(puts, &sp74, &sp70);
    XFB_WriteBackCache();
    PPCHalt();
    va_end(sp78);
}

void HuFaultInitXfbDirectDraw(GXRenderModeObj *mode) {
    s32 i;
    
    for (i = 0; i < 4; i++) {
        XFB_Geometry.fb[i] = 0;
    }
    
    XFB_Geometry.width = 0;
    XFB_Geometry.height = 0;
    XFB_Geometry.mode = 0;
    
    XFB_putc = XFB_putcProgressive;
    Draw_Color = XFB_Colors[1];
    
    if (mode) {
        XFB_Geometry.width = ((u16)mode->fbWidth + 0xF) & 0xFFFFFFF0;
        XFB_Geometry.height = mode->xfbHeight;
        XFB_Geometry.mode = mode->xFBmode;
        
        if (XFB_Geometry.mode == 0) {
            XFB_putc = XFB_putcInterlace;
        } else {
            XFB_putc = XFB_putcProgressive;
        }
    }
}

void HuFaultSetXfbAddress(s16 id, void* addr) {
    if (id >= 0 && id < 4) {
        XFB_Geometry.fb[id] = addr;
    }
}

static void XFB_WriteBackCache(void) {
    s32 i;
    void* fb;
    u32 size;

    size = XFB_Geometry.width * 2 * XFB_Geometry.height;

    if (size != 0) {
        for (i = 0; i < 4; i += 1) {
            fb = XFB_Geometry.fb[i];

            if (fb) {
                DCStoreRange(fb, size);
            }
        }
    }
}

static void XFB_CR(s32 value, s32* x_ptr, s32* y_ptr) {
    s32 numLines;
    s32 y;
    s32 x;

    x = *x_ptr;
    y = *y_ptr;

    x = x_start;
    y += 0x12;

    numLines = value & 7;
    if (numLines != 0) {
        y += numLines * 0x12;
    }

    *x_ptr = x;
    *y_ptr = y;
}

static s32 XFB_puts(s8* message, s32 x, s32 y) {
    s32 i;
    s32 temp_r31;
    s8 current_char;
    
    i = 0;
    
    do {
        current_char = *message++;
        
        if (current_char == '\n') {
            XFB_CR(0, &x, &y);
            
            i += 1;
        } else {
            temp_r31 = XFB_putcS(current_char, x, y);
            
            if (temp_r31 >= 0) {
                if (temp_r31 != 0) {
                    temp_r31 -= 1;

                    XFB_CR(temp_r31, &x, &y);
                    
                    i += temp_r31 + 1;
                }
                x += 0x10;
            } else {
                break;
            }
        }
    } while(current_char != 0);
    
    return i;
}

static s32 XFB_putcS(u8 c, s32 x, s32 y) {
    XFB_COLOR colorOld;
    s32 crNum;

    crNum = 0;
    colorOld = Draw_Color;

    if (x + 0x11 >= XFB_Geometry.width) {
        XFB_CR(0, &x, &y);
        crNum++;
    }

    Draw_Color = XFB_Colors[0];
    XFB_putc(c, x, y - 2);
    XFB_putc(c, x, y + 2);
    XFB_putc(c, x - 1, y);
    XFB_putc(c, x + 1, y);

    Draw_Color = colorOld;
    XFB_putc(c, x, y);

    return crNum;
}

static s32 XFB_putcProgressive(u8 c, s32 x, s32 y) {
    s32 result;
    s32 pitch;
    u8 colorY;
    u8 colorCr;
    u8 colorCb;
    s32 i;
    s32 j;
    s32 xfbOfs;
    u8* src;
    s32 k;
    s32 width;
    s32 writeMaskIdx;
    u32 writeMask;
    u32 bits;
    u8* fb;

    result = 0;

    if (c == 0) {
        return -1;
    }

    if (x + 0x10 >= XFB_Geometry.width) {
        y += 0x12;
        x = x_start;
        result = 1;
    }

    if (y + 0x10 >= XFB_Geometry.height) {
        return -1;
    }

    colorY = Draw_Color.y;
    colorCb = Draw_Color.cb;
    colorCr = Draw_Color.cr;

    pitch = XFB_Geometry.width * 2;
    xfbOfs = (x & 0xFFFE) * 2 + y * pitch;
    src = Ascii8x8_1bpp + (c * 8);

    i = 8;

    while (i != 0) {
        j = 2;

        while (j != 0) {
            for (k = 0; k < 4; k ++) {
                fb = XFB_Geometry.fb[k];

                if (fb != 0) {
                    fb += xfbOfs;

                    bits = *src;
                    writeMask = 0;
                    writeMaskIdx = 0;
                    while (writeMaskIdx < 0x10) {
                        if (bits & 0xF != 0) {
                            writeMask |= 3 << writeMaskIdx;
                        }
                        writeMaskIdx += 2;
                        bits >>= 1;
                    }
                    width = 8;
                    if ((s32) (x & 1) != 0) {
                        writeMask *= 2;
                        width = 0xA;
                    }

                    while (width != 0) {
                        if ((u32) (writeMask & 3) != 0) {
                            fb[1] = colorCr;
                            fb[3] = colorCb;

                            if ((u32) (writeMask & 1) != 0) {
                                fb[0] = colorY;
                            }
                            if ((u32) (writeMask & 2) != 0) {
                                fb[2] = colorY;
                            }
                        }
                        width -= 1;
                        fb += 4;
                        writeMask = writeMask >> 2;
                    }
                }
            }

            j -= 1;
            xfbOfs += pitch;
        }
        i -= 1;
        src += 1;
    }
    
    return result;
}

static s32 XFB_putcInterlace(u8 c, s32 x, s32 y) {
    u8 colorY;
    u8 colorCr;
    u8 colorCb;
    s32 pitch;
    s32 i;
    s32 xfbOfs;
    u8* src;
    s32 j;
    s16 bits;
    s32 width;
    u8* fb;

    if (c == 0) {
        return -1;
    }

    if (x + 8 >= XFB_Geometry.width || y + 8 >= XFB_Geometry.height) {
        return -1;
    }

    colorY = Draw_Color.y;
    colorCb = Draw_Color.cb;
    colorCr = Draw_Color.cr;

    pitch = XFB_Geometry.width * 2;
    xfbOfs = ((x & 0xFFFE) * 2) + ((y >> 1) * pitch);
    src = Ascii8x8_1bpp + c * 8;

    i = 8;

    while (i != 0) {
        for (j = 0; j < 4; j += 2) {
            width = j;

            if ((s32) (y & 1) != 0) {
                width += 1;
            }

            fb = XFB_Geometry.fb[width];

            if (fb) {
                fb = fb + xfbOfs;
                bits = *src;
                width = 4;

                if (x & 1) {
                    bits = (s16)bits * 2;
                    width = 5;
                }

                while (width) {
                    if (bits & 3) {
                        fb[1] = colorCr;
                        fb[3] = colorCb;

                        if (bits & 1) {
                            fb[0] = colorY;
                        }
                        if (bits & 2) {
                            fb[2] = colorY;
                        }
                    }

                    width -= 1;
                    fb += 4;
                    bits >>= 2;
                }
            }
        }

        i -= 1;
        y += 1;
        src += 1;
        xfbOfs += pitch;
    }
    
    return 0;
}
