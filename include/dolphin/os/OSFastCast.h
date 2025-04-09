#ifndef _DOLPHIN_OSFASTCAST
#define _DOLPHIN_OSFASTCAST

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_GQR_F32 0x0000
#define OS_GQR_U8 0x0004
#define OS_GQR_U16 0x0005
#define OS_GQR_S8 0x0006
#define OS_GQR_S16 0x0007

#define OS_FASTCAST_U8 2
#define OS_FASTCAST_U16 3
#define OS_FASTCAST_S8 4
#define OS_FASTCAST_S16 5
// clang-format off
static inline void OSInitFastCast(void) {
#ifdef __MWERKS__
  asm
  {
        li      r3, OS_GQR_U8
        oris    r3, r3, OS_GQR_U8
        mtspr   GQR2, r3

        li      r3, OS_GQR_U16
        oris    r3, r3, OS_GQR_U16
        mtspr   GQR3, r3

        li      r3, OS_GQR_S8
        oris    r3, r3, OS_GQR_S8
        mtspr   GQR4, r3

        li      r3, OS_GQR_S16
        oris    r3, r3, OS_GQR_S16
        mtspr   GQR5, r3
  }
#else

#endif
}
// clang-format off

static inline s16 __OSf32tos16(register f32 inF)
{
#ifdef __MWERKS__
	u32 tmp;
	register u32* tmpPtr = &tmp;
	register s16 out;
	// clang-format off
    asm {
        psq_st inF, 0(tmpPtr), 0x1, OS_FASTCAST_S16
        lha out, 0(tmpPtr)
    }
  // clang-format on

  return out;
#else
  return (s16) inF;
#endif
}

static inline void OSf32tos16(f32 *f, s16 *out) { *out = __OSf32tos16(*f); }

static inline u8 __OSf32tou8(register f32 inF)
{
#ifdef __MWERKS__
  u32 tmp;
  register u32 *tmpPtr = &tmp;
  register u8 out;
  // clang-format off
    asm {
        psq_st inF, 0(tmpPtr), 0x1, OS_FASTCAST_U8
        lbz out, 0(tmpPtr)
    }
  // clang-format on

  return out;
#else 
  return (u8)inF;
#endif
}

static inline void OSf32tou8(f32 *f, u8 *out) { *out = __OSf32tou8(*f); }

static inline s8 __OSf32tos8(register f32 inF)
{
#ifdef __MWERKS__
  u32 tmp;
  register u32 *tmpPtr = &tmp;
  register s8 out;
  // clang-format off
    asm {
        psq_st inF, 0(tmpPtr), 0x1, OS_FASTCAST_S8
        lbz out, 0(tmpPtr)
		extsb out, out //HACK to match fast cast inlines
    }
  // clang-format on

  return out;
#else
  return (s8) inF;
#endif
}

static inline void OSf32tos8(f32 *f, s8 *out) { *out = __OSf32tos8(*f); }

static inline u16 __OSf32tou16(register f32 inF)
{
#ifdef __MWERKS__
  u32 tmp;
  register u32 *tmpPtr = &tmp;
  register u16 out;
  // clang-format off
    asm {
        psq_st inF, 0(tmpPtr), 0x1, OS_FASTCAST_U16
        lbz out, 0(tmpPtr)
    }
  // clang-format on

  return out;
#else
  return (u16) inF;
#endif
}

static inline void OSf32tou16(f32 *f, u16 *out) { *out = __OSf32tou16(*f); }

static inline float __OSs8tof32(register const s8* arg) {
#ifdef __MWERKS__
    register float ret;

    asm {
        psq_l ret, 0(arg), 1, OS_FASTCAST_S8
    }

    return ret;
#else
  return (f32)*arg;
#endif
}

static inline void OSs8tof32(const s8* in, float* out) { *out = __OSs8tof32(in); }

static inline float __OSs16tof32(register const s16* arg) {
#ifdef __MWERKS__
    register float ret;

    asm {
        psq_l ret, 0(arg), 1, OS_FASTCAST_S16
    }

    return ret;
#else
  return (f32)*arg;
#endif
}

static inline void OSs16tof32(const s16* in, float* out) { *out = __OSs16tof32(in); }

static inline float __OSu8tof32(register const u8* arg) {
#ifdef __MWERKS__
    register float ret;

    asm {
        psq_l ret, 0(arg), 1, OS_FASTCAST_U8
    }

    return ret;
#else
  return (f32)*arg; 
#endif
}

static inline void OSu8tof32(const u8* in, float* out) { *out = __OSu8tof32(in); }

static inline float __OSu16tof32(register const u16* arg) {
#ifdef __MWERKS__
    register float ret;

    asm {
        psq_l ret, 0(arg), 1, OS_FASTCAST_U16
    }

    return ret;
#else
  return (f32)*arg;
#endif
}

static inline void OSu16tof32(const u16* in, float* out) { *out = __OSu16tof32(in); }

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_OSFASTCAST
