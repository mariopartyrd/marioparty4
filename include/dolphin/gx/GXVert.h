#ifndef _DOLPHIN_GXVERT
#define _DOLPHIN_GXVERT

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GXFIFO_ADDR 0xCC008000

typedef union {
  u8 u8;
  u16 u16;
  u32 u32;
  u64 u64;
  s8 s8;
  s16 s16;
  s32 s32;
  s64 s64;
  f32 f32;
  f64 f64;
} PPCWGPipe;

#ifdef __MWERKS__
volatile PPCWGPipe GXWGFifo : GXFIFO_ADDR;
#else
#define GXWGFifo (*(volatile PPCWGPipe*)GXFIFO_ADDR)
#endif

#ifdef TARGET_PC

void GXPosition3f32(f32 x, f32 y, f32 z);
void GXPosition3u16(u16 x, u16 y, u16 z);
void GXPosition3s16(s16 x, s16 y, s16 z);
void GXPosition3u8(u8 x, u8 y, u8 z);
void GXPosition3s8(s8 x, s8 y, s8 z);

void GXPosition2f32(f32 x, f32 y);
void GXPosition2u16(u16 x, u16 y);
void GXPosition2s16(s16 x, s16 y);
void GXPosition2u8(u8 x, u8 y);
void GXPosition2s8(s8 x, s8 y);

void GXPosition1x16(u16 index);
void GXPosition1x8(u8 index);

void GXNormal3f32(f32 x, f32 y, f32 z);
void GXNormal3s16(s16 x, s16 y, s16 z);
void GXNormal3s8(s8 x, s8 y, s8 z);

void GXNormal1x16(u16 index);
void GXNormal1x8(u8 index);

void GXColor4u8(u8 r, u8 g, u8 b, u8 a);

void GXColor3u8(u8 r, u8 g, u8 b);

void GXColor1u32(u32 clr);
void GXColor1u16(u16 clr);

void GXColor1x16(u16 index);
void GXColor1x8(u8 index);

void GXTexCoord2f32(f32 s, f32 t);
void GXTexCoord2u16(u16 s, u16 t);
void GXTexCoord2s16(s16 s, s16 t);
void GXTexCoord2u8(u8 s, u8 t);
void GXTexCoord2s8(s8 s, s8 t);

void GXTexCoord1f32(f32 s, f32 t);
void GXTexCoord1u16(u16 s, u16 t);
void GXTexCoord1s16(s16 s, s16 t);
void GXTexCoord1u8(u8 s, u8 t);
void GXTexCoord1s8(s8 s, s8 t);

void GXTexCoord1x16(u16 index);
void GXTexCoord1x8(u8 index);

extern void GXEnd(void);

#else

static inline void GXPosition2f32(const f32 x, const f32 y) {
  GXWGFifo.f32 = x;
  GXWGFifo.f32 = y;
}

static inline void GXPosition2u16(const u16 x, const u16 y) {
  GXWGFifo.u16 = x;
  GXWGFifo.u16 = y;
}

static inline void GXPosition2s16(const s16 x, const s16 y) {
  GXWGFifo.s16 = x;
  GXWGFifo.s16 = y;
}

static inline void GXPosition3s16(const s16 x, const s16 y, const s16 z) {
  GXWGFifo.s16 = x;
  GXWGFifo.s16 = y;
  GXWGFifo.s16 = z;
}

static inline void GXPosition3u8(const u8 x, const u8 y, const u8 z) {
  GXWGFifo.u8 = x;
  GXWGFifo.u8 = y;
  GXWGFifo.u8 = z;
}

static inline void GXPosition3f32(const f32 x, const f32 y, const f32 z) {
  GXWGFifo.f32 = x;
  GXWGFifo.f32 = y;
  GXWGFifo.f32 = z;
}

static inline void GXNormal3s16(const s16 x, const s16 y, const s16 z) {
  GXWGFifo.s16 = x;
  GXWGFifo.s16 = y;
  GXWGFifo.s16 = z;
}

static inline void GXNormal3f32(const f32 x, const f32 y, const f32 z) {
  GXWGFifo.f32 = x;
  GXWGFifo.f32 = y;
  GXWGFifo.f32 = z;
}

static inline void GXColor1u32(const u32 v) {
  GXWGFifo.u32 = v;
}

static inline void GXColor3u8(const u8 r, const u8 g, const u8 b) {
  GXWGFifo.u8 = r;
  GXWGFifo.u8 = g;
  GXWGFifo.u8 = b;
}

static inline void GXColor4u8(const u8 r, const u8 g, const u8 b, const u8 a) {
  GXWGFifo.u8 = r;
  GXWGFifo.u8 = g;
  GXWGFifo.u8 = b;
  GXWGFifo.u8 = a;
}

static inline void GXTexCoord2s16(const s16 u, const s16 v) {
  GXWGFifo.s16 = u;
  GXWGFifo.s16 = v;
}

static inline void GXTexCoord2f32(const f32 u, const f32 v) {
  GXWGFifo.f32 = u;
  GXWGFifo.f32 = v;
}

static inline void GXPosition1x8(u8 index) {
  GXWGFifo.u8 = index;
}

static inline void GXColor1x8(u8 index) {
  GXWGFifo.u8 = index;
}

static inline void GXPosition1x16(u16 index) {
  GXWGFifo.u16 = index;
}

static inline void GXNormal1x16(u16 index) {
  GXWGFifo.u16 = index;
}

static inline void GXColor1x16(u16 index) {
  GXWGFifo.u16 = index;
}

static inline void GXTexCoord1x16(u16 index) {
  GXWGFifo.u16 = index;
}

static inline void GXUnknownu16(const u16 x) {
  GXWGFifo.u16 = x;
}

static inline void GXEnd(void) {}

#endif

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXVERT
