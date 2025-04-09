#include "game/fault.h"
#include "stdarg.h"
#include "stdio.h"

typedef struct rgb_color {
    u8 r;
    u8 g;
    u8 b;
} RGBColor;

typedef struct xfb_geometry {
    void* frame_buffers[4];
    u16 width;
    u16 height;
    u16 mode;
} XFBGeometry;

static RGBColor XFB_Colors[5] = {
    { 0x00, 0x80, 0x80 },
    { 0xFF, 0x80, 0x80 },
    { 0xC0, 0x80, 0x80 },
    { 0x80, 0x80, 0x80 },
    { 0x40, 0x80, 0x80 }
};

#ifdef TARGET_PC
u8 Ascii8x8_1bpp[0x800];
#else
#include "Ascii8x8_1bpp.inc"
#endif

static XFBGeometry XFB_Geometry;

static s32 (*XFB_putc)(u8 c, s32 x, s32 y);

static RGBColor Draw_Color;

static s32 x_start;
static s32 y_start;

static s32 XFB_putcProgressive(u8 arg0, s32 arg1, s32 arg2);
static s32 XFB_putcInterlace(u8 arg0, s32 arg1, s32 arg2);
static s32 XFB_puts(s8* arg0, s32 arg1, s32 arg2);
static s32 XFB_putcS(u8 arg0, s32 arg1, s32 arg2);
static void XFB_WriteBackCache(void);
static void XFB_CR(s32 arg0, s32* arg1, s32* arg2);

void OSPanic(const char* file, int line, const char* msg, ...) {
    static char* titleMes = "OSPanic encounterd:";
    
    va_list args;
    s32 sp74;
    s32 sp70;
    char buffer[1024];
    s32 puts;

    sp74 = x_start = 0x10;
    sp70 = y_start = 0x20;
    puts = XFB_puts((s8*)titleMes, sp74, sp70);
    XFB_CR(puts + 1, &sp74, &sp70);
    sprintf(buffer, "%s:%d", file, line);
    puts = XFB_puts((s8*)buffer, sp74, sp70);
    XFB_CR(puts, &sp74, &sp70);
    va_start(args, msg);
    vsnprintf(buffer, 0x400U, msg, &args[0]);
#ifdef TARGET_PC
    fputs(buffer, stderr);
#endif
    puts = XFB_puts((s8*)buffer, sp74, sp70);
    XFB_CR(puts, &sp74, &sp70);
    XFB_WriteBackCache();
    PPCHalt();
    va_end(args);
}

void HuFaultInitXfbDirectDraw(GXRenderModeObj *mode) {
    s32 i;
    
    for (i = 0; i < 4; i++) {
        XFB_Geometry.frame_buffers[i] = 0;
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

void HuFaultSetXfbAddress(s16 index, void* value) {
    if (index >= 0 && index < 4) {
        XFB_Geometry.frame_buffers[index] = value;
    }
}

static void XFB_WriteBackCache(void) {
    s32 i;
    void* frame_buffer;
    u32 temp_r29;

    temp_r29 = XFB_Geometry.width * 2 * XFB_Geometry.height;
    
    if (temp_r29 != 0) {
        for (i = 0; i < 4; i += 1) {
            frame_buffer = XFB_Geometry.frame_buffers[i];
            
            if (frame_buffer) {
                DCStoreRange(frame_buffer, temp_r29);
            }
        }
    }
}

static void XFB_CR(s32 arg0, s32* x_ptr, s32* y_ptr) {
    s32 temp_r30;
    s32 y;
    s32 x;

    x = *x_ptr;
    y = *y_ptr;
    
    x = x_start;
    y += 0x12;
    
    temp_r30 = arg0 & 7;
    if (temp_r30 != 0) {
        y += temp_r30 * 0x12;
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
    RGBColor sp8;
    s32 var_r26;
    s32 var_r25;
    s32 var_r27;
    s32 var_r29;
    RGBColor* temp_r3;
    
    var_r27 = 0;
    sp8 = Draw_Color;
    
    if (x + 0x11 >= XFB_Geometry.width) {
        XFB_CR(0, &x, &y);
        var_r27++;
    }
    
    Draw_Color = XFB_Colors[0];
    XFB_putc(c, x, y - 2);
    XFB_putc(c, x, y + 2);
    XFB_putc(c, x - 1, y);
    XFB_putc(c, x + 1, y);
    
    Draw_Color = sp8;
    XFB_putc(c, x, y);
    
    return var_r27;
}

static s32 XFB_putcProgressive(u8 c, s32 x, s32 y) {
    s32 result;
    s32 temp_r20;
    u8 red;
    u8 blue;
    u8 green;
    s32 i;
    s32 j;
    s32 var_r23;
    u8* var_r29;
    s32 k;
    s32 var_r27;
    s32 var_r26;
    u32 temp_r31;
    u32 var_r30;
    u32 var_r22;
    u8* frame_buffer;
    
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
    
    red = Draw_Color.r;
    green = Draw_Color.g;
    blue = Draw_Color.b;
    
    temp_r20 = XFB_Geometry.width * 2;
    var_r23 = (x & 0xFFFE) * 2 + y * temp_r20;
    var_r29 = Ascii8x8_1bpp + (c * 8);
    
    i = 8;
    
    while (i != 0) {
        j = 2;
        
        while (j != 0) {
            for (k = 0; k < 4; k ++) {
                frame_buffer = XFB_Geometry.frame_buffers[k];
                
                if (frame_buffer != 0) {
                    frame_buffer += var_r23;
                    
                    var_r22 = *var_r29;
                    var_r30 = 0;
                    var_r26 = 0;
                    while (var_r26 < 0x10) {
                        if (var_r22 & 0xF != 0) {
                            var_r30 |= 3 << var_r26;
                        }
                        var_r26 += 2;
                        var_r22 >>= 1;
                    }
                    var_r27 = 8;
                    if ((s32) (x & 1) != 0) {
                        var_r30 *= 2;
                        var_r27 = 0xA;
                    }
                    
                    while (var_r27 != 0) {
                        if ((u32) (var_r30 & 3) != 0) {
                            frame_buffer[1] = blue;
                            frame_buffer[3] = green;
                            
                            if ((u32) (var_r30 & 1) != 0) {
                                frame_buffer[0] = red;
                            }
                            if ((u32) (var_r30 & 2) != 0) {
                                frame_buffer[2] = red;
                            }
                        }
                        var_r27 -= 1;
                        frame_buffer += 4;
                        var_r30 = var_r30 >> 2;
                    }
                }
            }
            
            j -= 1;
            var_r23 += temp_r20;
        }
        i -= 1;
        var_r29 += 1;
    }
    
    return result;
}

static s32 XFB_putcInterlace(u8 c, s32 x, s32 y) {
    u8 red;
    u8 blue;
    u8 green;
    s32 temp_r23;
    s32 i;
    s32 var_r25;
    u8* var_r28;
    s32 j;
    s16 var_r29;
    s32 var_r30;
    u8* var_r31;
    
    if (c == 0) {
        return -1;
    }
    
    if (x + 8 >= XFB_Geometry.width || y + 8 >= XFB_Geometry.height) {
        return -1;
    }

    red = Draw_Color.r;
    green = Draw_Color.g;
    blue = Draw_Color.b;
    
    temp_r23 = XFB_Geometry.width * 2;
    var_r25 = ((x & 0xFFFE) * 2) + ((y >> 1) * temp_r23);
    var_r28 = Ascii8x8_1bpp + c * 8;
    
    i = 8;
    
    while (i != 0) {
        for (j = 0; j < 4; j += 2) {
            var_r30 = j;
            
            if ((s32) (y & 1) != 0) {
                var_r30 += 1;
            }
            
            var_r31 = XFB_Geometry.frame_buffers[var_r30];
            
            if (var_r31) {
                var_r31 = var_r31 + var_r25;
                var_r29 = *var_r28;
                var_r30 = 4;
                
                if (x & 1) {
                    var_r29 = (s16)var_r29 * 2;
                    var_r30 = 5;
                }

                while (var_r30) {
                    if (var_r29 & 3) {
                        var_r31[1] = blue;
                        var_r31[3] = green;
                        
                        if (var_r29 & 1) {
                            var_r31[0] = red;
                        }
                        if (var_r29 & 2) {
                            var_r31[2] = red;
                        }
                    }
                    
                    var_r30 -= 1;
                    var_r31 += 4;
                    var_r29 >>= 2;
                }
            }
        }
        
        i -= 1;
        y += 1;
        var_r28 += 1;
        var_r25 += temp_r23;
    }
    
    return 0;
}
