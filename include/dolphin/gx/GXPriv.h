#ifndef _DOLPHIN_GXPRIV
#define _DOLPHIN_GXPRIV

#include "dolphin/gx.h"
#include "dolphin/os.h"

#ifndef NDEBUG
#define ASSERTLINE(line, cond) \
    ((cond) || (OSPanic(__FILE__, line, "Failed assertion " #cond), 0))

#define ASSERTMSGLINE(line, cond, msg) \
    ((cond) || (OSPanic(__FILE__, line, msg), 0))

// This is dumb but we dont have a Metrowerks way to do variadic macros in the macro to make this done in a not scrubby way.
#define ASSERTMSG1LINE(line, cond, msg, arg1) \
    ((cond) || (OSPanic(__FILE__, line, msg, arg1), 0))
    
#define ASSERTMSG2LINE(line, cond, msg, arg1, arg2) \
    ((cond) || (OSPanic(__FILE__, line, msg, arg1, arg2), 0))

#define ASSERTMSGLINEV(line, cond, ...) \
    ((cond) || (OSPanic(__FILE__, line, __VA_ARGS__), 0))

#else
#define ASSERTLINE(line, cond) (void)0
#define ASSERTMSGLINE(line, cond, msg) (void)0
#define ASSERTMSG1LINE(line, cond, msg, arg1) (void)0
#define ASSERTMSG2LINE(line, cond, msg, arg1, arg2) (void)0
#define ASSERTMSGLINEV(line, cond, ...) (void)0
#endif

typedef struct GXLightObjInt {
  u32 padding[3];
  u32 color;
  float a0;
  float a1;
  float a2;
  float k0;
  float k1;
  float k2;
  float px;
  float py;
  float pz;
  float nx;
  float ny;
  float nz;
} GXLightObjInt;

#define XF_LIGHT_BASE 0x0600
#define XF_LIGHT_SIZE 0x10

#define GX_FIFO_ADDR 0xCC008000

#define GX_WRITE_U8(v) (GXWGFifo.u8 = v)
#define GX_WRITE_U16(us) (GXWGFifo.u16 = (u16)(us))
#define GX_WRITE_U32(v) (GXWGFifo.u32 = v)
#define GX_WRITE_F32(f) (GXWGFifo.f32 = (f32)(f))

#if DEBUG
#define VERIF_XF_REG(addr, value) \
do { \
    s32 regAddr = (addr); \
    if (regAddr >= 0 && regAddr < 0x50) { \
        __gxVerif->xfRegs[regAddr] = (value); \
        __gxVerif->xfRegsDirty[regAddr] = 1; \
    } \
} while (0)
#define VERIF_XF_REG_alt(addr, value) \
do { \
    s32 xfAddr = (addr); \
    if (xfAddr >= 0 && xfAddr < 0x50) { \
        __gxVerif->xfRegs[xfAddr] = (value); \
        __gxVerif->xfRegsDirty[xfAddr] = 1; \
    } \
} while (0)
#define VERIF_RAS_REG(value) (__gxVerif->rasRegs[((value) & 0xFF000000) >> 24] = value)
#define VERIF_MTXLIGHT(addr, data) \
do { \
    s32 xfAddr; \
    if (addr < 0x400U) { \
        __gxVerif->xfMtx[addr] = data; \
        __gxVerif->xfMtxDirty[addr] = 1; \
    } else if (addr < 0x500U) { \
        xfAddr = addr - 0x400; \
        __gxVerif->xfNrm[xfAddr] = data; \
        __gxVerif->xfNrmDirty[xfAddr] = 1; \
    } else if (addr < 0x600U) { \
        xfAddr = addr - 0x500; \
        __gxVerif->xfDMtx[xfAddr] = data; \
        __gxVerif->xfDMtxDirty[xfAddr] = 1; \
    } else if (addr < 0x680U) { \
        xfAddr = addr - 0x600; \
        __gxVerif->xfLight[xfAddr] = data; \
        __gxVerif->xfLightDirty[xfAddr] = 1; \
    } else { \
        xfAddr = addr - 0x1000; \
        if ((xfAddr >= 0) && (xfAddr < 0x50)) { \
            __gxVerif->xfRegs[xfAddr] = data; \
            __gxVerif->xfRegsDirty[xfAddr] = 1; \
        } \
    } \
} while (0)
#else
#define VERIF_XF_REG(addr, value) ((void)0)
#define VERIF_XF_REG_alt(addr, value) ((void)0)
#define VERIF_RAS_REG(value) ((void)0)
#endif

#define GX_WRITE_XF_REG(addr, value) \
do { \
    GX_WRITE_U8(0x10); \
    GX_WRITE_U32(0x1000 + (addr)); \
    GX_WRITE_U32(value); \
    VERIF_XF_REG(addr, value); \
} while (0)

#if DEBUG
#define GX_WRITE_XF_REG_2(addr, value) \
do { \
    u32 xfData = (value); &xfData; \
    GX_WRITE_U32(value); \
    VERIF_XF_REG_alt(addr, xfData); \
} while (0)
#define GX_WRITE_XF_REG_F(addr, value) \
do { \
    f32 xfData = (value); \
    GX_WRITE_F32(value); \
    VERIF_XF_REG_alt(addr, *(u32 *)&xfData); \
} while (0)
#else
#define GX_WRITE_XF_REG_2(addr, value) \
do { \
    GX_WRITE_U32(value); \
} while (0)
#define GX_WRITE_XF_REG_F(addr, value) \
do { \
    GX_WRITE_F32(value); \
} while (0)
#endif

#define GX_WRITE_RAS_REG(value) \
do { \
    GX_WRITE_U8(0x61); \
    GX_WRITE_U32(value); \
    VERIF_RAS_REG(value); \
} while (0)

#define GX_WRITE_SOME_REG2(a, b, c, addr) \
do { \
    long regAddr; \
    GX_WRITE_U8(a); \
    GX_WRITE_U8(b); \
    GX_WRITE_U32(c); \
    regAddr = addr; \
    if (regAddr >= 0 && regAddr < 4) { \
        gx->indexBase[regAddr] = c; \
    } \
} while (0)
#define GX_WRITE_SOME_REG3(a, b, c, addr) \
do { \
    long regAddr; \
    GX_WRITE_U8(a); \
    GX_WRITE_U8(b); \
    GX_WRITE_U32(c); \
    regAddr = addr; \
    if (regAddr >= 0 && regAddr < 4) { \
        gx->indexStride[regAddr] = c; \
    } \
} while (0)
#define GX_WRITE_SOME_REG4(a, b, c, addr) \
do { \
    long regAddr; \
    GX_WRITE_U8(a); \
    GX_WRITE_U8(b); \
    GX_WRITE_U32(c); \
    regAddr = addr; \
} while (0)

#define GET_REG_FIELD(reg, size, shift) ((int)((reg) >> (shift)) & ((1 << (size)) - 1))

#define SET_REG_FIELD(line, reg, size, shift, val) \
do { \
    ASSERTMSGLINE(line, ((u32)(val) & ~((1 << (size)) - 1)) == 0, "GX Internal: Register field out of range"); \
    (reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)); \
} while (0)

#define GX_REG_ASSERT(c) ASSERTMSG(c, "GX Internal: Register field out of range")

#define GX_FLAG_SET(regOrg, newFlag, regName)                                                      \
  do {                                                                                             \
    GX_REG_ASSERT(!((newFlag) & ~((1 << (regName##_SIZE)) - 1)));                                  \
    (regOrg) = (((u32)(regOrg) & ~(regName##_MASK)) |                                              \
                (((u32)(newFlag) << (regName##_SHIFT)) & (regName##_MASK)));                       \
  } while (0)

#define GX_GENMODE_ID 0
#define GX_GENMODE_REG_ID_SIZE 8
#define GX_GENMODE_REG_ID_SHIFT 24
#define GX_GENMODE_REG_ID_MASK 0xff000000
#define GX_GENMODE_GET_REG_ID(genMode)                                                               \
  ((((u32)(genMode)) & GX_GENMODE_REG_ID_MASK) >> GX_GENMODE_REG_ID_SHIFT)

#define GX_BPMASK_ID 15
#define GX_BPMASK_REG_ID_SIZE 8
#define GX_BPMASK_REG_ID_SHIFT 24
#define GX_BPMASK_REG_ID_MASK 0xff000000

#define GX_LPSIZE_ID 34
#define GX_LPSIZE_REG_ID_SIZE 8
#define GX_LPSIZE_REG_ID_SHIFT 24
#define GX_LPSIZE_REG_ID_MASK 0xff000000

#define TEV_COLOR_ENV_REG_ID_SIZE 8
#define TEV_COLOR_ENV_REG_ID_SHIFT 24
#define TEV_COLOR_ENV_REG_ID_MASK 0xff000000

#define TEV_ALPHA_ENV_REG_ID_SIZE 8
#define TEV_ALPHA_ENV_REG_ID_SHIFT 24
#define TEV_ALPHA_ENV_REG_ID_MASK 0xff000000

#define TEV_COLOR_ENV_0_ID 0x000000c0
#define TEV_ALPHA_ENV_0_ID 0x000000c1
#define TEV_COLOR_ENV_1_ID 0x000000c2
#define TEV_ALPHA_ENV_1_ID 0x000000c3
#define TEV_COLOR_ENV_2_ID 0x000000c4
#define TEV_ALPHA_ENV_2_ID 0x000000c5
#define TEV_COLOR_ENV_3_ID 0x000000c6
#define TEV_ALPHA_ENV_3_ID 0x000000c7
#define TEV_COLOR_ENV_4_ID 0x000000c8
#define TEV_ALPHA_ENV_4_ID 0x000000c9
#define TEV_COLOR_ENV_5_ID 0x000000ca
#define TEV_ALPHA_ENV_5_ID 0x000000cb
#define TEV_COLOR_ENV_6_ID 0x000000cc
#define TEV_ALPHA_ENV_6_ID 0x000000cd
#define TEV_COLOR_ENV_7_ID 0x000000ce
#define TEV_ALPHA_ENV_7_ID 0x000000cf
#define TEV_COLOR_ENV_8_ID 0x000000d0
#define TEV_ALPHA_ENV_8_ID 0x000000d1
#define TEV_COLOR_ENV_9_ID 0x000000d2
#define TEV_ALPHA_ENV_9_ID 0x000000d3
#define TEV_COLOR_ENV_A_ID 0x000000d4
#define TEV_ALPHA_ENV_A_ID 0x000000d5
#define TEV_COLOR_ENV_B_ID 0x000000d6
#define TEV_ALPHA_ENV_B_ID 0x000000d7
#define TEV_COLOR_ENV_C_ID 0x000000d8
#define TEV_ALPHA_ENV_C_ID 0x000000d9
#define TEV_COLOR_ENV_D_ID 0x000000da
#define TEV_ALPHA_ENV_D_ID 0x000000db
#define TEV_COLOR_ENV_E_ID 0x000000dc
#define TEV_ALPHA_ENV_E_ID 0x000000dd
#define TEV_COLOR_ENV_F_ID 0x000000de
#define TEV_ALPHA_ENV_F_ID 0x000000df

#define TEV_KSEL_REG_ID_SIZE 8
#define TEV_KSEL_REG_ID_SHIFT 24
#define TEV_KSEL_REG_ID_MASK 0xff000000

#define TEV_KSEL_0_ID 0x000000f6
#define TEV_KSEL_1_ID 0x000000f7
#define TEV_KSEL_2_ID 0x000000f8
#define TEV_KSEL_3_ID 0x000000f9
#define TEV_KSEL_4_ID 0x000000fa
#define TEV_KSEL_5_ID 0x000000fb
#define TEV_KSEL_6_ID 0x000000fc
#define TEV_KSEL_7_ID 0x000000fd

#define RAS_IREF_ID 39
#define RAS_IREF_REG_ID_SIZE 8
#define RAS_IREF_REG_ID_SHIFT 24
#define RAS_IREF_REG_ID_MASK 0xff000000

#define RAS_TREF0_ID 40
#define RAS_TREF_REG_ID_SIZE 8
#define RAS_TREF_REG_ID_SHIFT 24
#define RAS_TREF_REG_ID_MASK 0xff000000

#define SU_TS0_REG_ID_SIZE 8
#define SU_TS0_REG_ID_SHIFT 24
#define SU_TS0_REG_ID_MASK 0xff000000

#define SU_TS1_REG_ID_SIZE 8
#define SU_TS1_REG_ID_SHIFT 24
#define SU_TS1_REG_ID_MASK 0xff000000

#define SU_SCIS0_ID 0x00000020
#define SU_SCIS1_ID 0x00000021

#define SU_SCIS0_REG_ID_SIZE 8
#define SU_SCIS0_REG_ID_SHIFT 24
#define SU_SCIS0_REG_ID_MASK 0xff000000

#define SU_SCIS1_REG_ID_SIZE 8
#define SU_SCIS1_REG_ID_SHIFT 24
#define SU_SCIS1_REG_ID_MASK 0xff000000

#define SU_SSIZE0_ID 0x00000030
#define SU_TSIZE0_ID 0x00000031
#define SU_SSIZE1_ID 0x00000032
#define SU_TSIZE1_ID 0x00000033
#define SU_SSIZE2_ID 0x00000034
#define SU_TSIZE2_ID 0x00000035
#define SU_SSIZE3_ID 0x00000036
#define SU_TSIZE3_ID 0x00000037
#define SU_SSIZE4_ID 0x00000038
#define SU_TSIZE4_ID 0x00000039
#define SU_SSIZE5_ID 0x0000003a
#define SU_TSIZE5_ID 0x0000003b
#define SU_SSIZE6_ID 0x0000003c
#define SU_TSIZE6_ID 0x0000003d
#define SU_SSIZE7_ID 0x0000003e
#define SU_TSIZE7_ID 0x0000003f

#define GX_ZMODE_ID 64
#define GX_ZMODE_REG_ID_SIZE 8
#define GX_ZMODE_REG_ID_SHIFT 24
#define GX_ZMODE_REG_ID_MASK 0xff000000

#define GX_CMODE0_ID 65
#define GX_CMODE0_REG_ID_SIZE 8
#define GX_CMODE0_REG_ID_SHIFT 24
#define GX_CMODE0_REG_ID_MASK 0xff000000

#define GX_CMODE1_ID 66
#define GX_CMODE1_REG_ID_SIZE 8
#define GX_CMODE1_REG_ID_SHIFT 24
#define GX_CMODE1_REG_ID_MASK 0xff000000

#define PE_CONTROL_ID 67
#define PE_CONTROL_REG_ID_SIZE 8
#define PE_CONTROL_REG_ID_SHIFT 24
#define PE_CONTROL_REG_ID_MASK 0xff000000

#define PE_COPY_CMD_GAMMA_SIZE 2
#define PE_COPY_CMD_GAMMA_SHIFT 7
#define PE_COPY_CMD_GAMMA_MASK 0x00000180

#define GEN_MODE_REG_ID_SIZE 8
#define GEN_MODE_REG_ID_SHIFT 24
#define GEN_MODE_REG_ID_MASK 0xff000000

#define GX_OPCODE_INDEX_SIZE 3
#define GX_OPCODE_INDEX_SHIFT 0
#define GX_OPCODE_INDEX_MASK 0x00000007

#define GX_OPCODE_CMD_SHIFT 3

#define GX_OPCODE(index, cmd)                                                                      \
  ((((u32)(index)) << GX_OPCODE_INDEX_SHIFT) | (((u32)(cmd)) << GX_OPCODE_CMD_SHIFT))

#ifdef _DEBUG
#define GX_WRITE_RA_REG(reg)                                                                       \
  {                                                                                                \
    GX_WRITE_U8(GX_OPCODE(1, 12));                                                                 \
    GX_WRITE_U32((reg));                                                                           \
    __gxVerif->rasRegs[GX_GENMODE_GET_REG_ID(reg)] = reg;                                             \
  }
#else
#define GX_WRITE_RA_REG(reg)                                                                       \
  {                                                                                                \
    GX_WRITE_U8(GX_OPCODE(1, 12));                                                                 \
    GX_WRITE_U32((reg));                                                                           \
  }
#endif

#define CP_STREAM_REG_INDEX_SIZE 4
#define CP_STREAM_REG_INDEX_SHIFT 0
#define CP_STREAM_REG_INDEX_MASK 0x0000000f

#define CP_STREAM_REG_ADDR_SIZE 4
#define CP_STREAM_REG_ADDR_SHIFT    4
#define CP_STREAM_REG_ADDR_MASK 0x000000f0

#define CP_STREAM_REG(index, addr)                                                                 \
  ((((unsigned long)(index)) << CP_STREAM_REG_INDEX_SHIFT) |                                       \
   (((unsigned long)(addr)) << CP_STREAM_REG_ADDR_SHIFT))

#ifdef _DEBUG
#define GX_WRITE_CP_STRM_REG(addr, vtxfmt, data)                                                   \
  {                                                                                                \
    s32 regAddr;                                                                                   \
    GX_WRITE_U8(GX_OPCODE(0, 1));                                                                  \
    GX_WRITE_U8(CP_STREAM_REG((vtxfmt), (addr)));                                                  \
    GX_WRITE_U32((data));                                                                          \
    regAddr = (vtxfmt)-GX_POS_MTX_ARRAY + GX_VA_POS;                                               \
    if ((addr) == 10) {                                                                            \
      if (regAddr >= 0 && regAddr < 4)                                                             \
        gx->indexBase[regAddr] = (data);                                                           \
    } else if ((addr) == 11) {                                                                     \
      if (regAddr >= 0 && regAddr < 4)                                                             \
        gx->indexStride[regAddr] = (data);                                                         \
    }                                                                                              \
  }
#else
#define GX_WRITE_CP_STRM_REG(addr, vtxfmt, data)                                                   \
  {                                                                                                \
    GX_WRITE_U8(GX_OPCODE(0, 1));                                                                  \
    GX_WRITE_U8(CP_STREAM_REG((vtxfmt), (addr)));                                                  \
    GX_WRITE_U32((data));                                                                          \
  }
#endif

#define PE_REFRESH_REG_ID_SIZE 8
#define PE_REFRESH_REG_ID_SHIFT 24
#define PE_REFRESH_REG_ID_MASK 0xff000000

#define PE_REFRESH_INTERVAL_SHIFT 0
#define PE_REFRESH_ENABLE_SHIFT 9
#define PE_REFRESH_TOTAL_SIZE 32
#define PE_REFRESH(interval, enable, rid)                                                          \
  ((((u32)(interval)) << PE_REFRESH_INTERVAL_SHIFT) |                                              \
   (((u32)(enable)) << PE_REFRESH_ENABLE_SHIFT) | (((u32)(rid)) << PE_REFRESH_REG_ID_SHIFT))

#define TX_REFRESH_REG_ID_SIZE 8
#define TX_REFRESH_REG_ID_SHIFT 24
#define TX_REFRESH_REG_ID_MASK 0xff000000

#define TX_REFRESH_INTERVAL_SHIFT 0
#define TX_REFRESH_ENABLE_SHIFT 10
#define TX_REFRESH_TOTAL_SIZE 32
#define TX_REFRESH(interval, enable, rid)                                                          \
  ((((u32)(interval)) << TX_REFRESH_INTERVAL_SHIFT) |                                              \
   (((u32)(enable)) << TX_REFRESH_ENABLE_SHIFT) | (((u32)(rid)) << TX_REFRESH_REG_ID_SHIFT))

#define GX_VAT_REG_A_UNK_SIZE 1
#define GX_VAT_REG_A_UNK_SHIFT 30
#define GX_VAT_REG_A_UNK_MASK 0x40000000

#define GX_VAT_REG_B_UNK_SIZE 1
#define GX_VAT_REG_B_UNK_SHIFT 31
#define GX_VAT_REG_B_UNK_MASK 0x80000000

#define GX_GET_MEM_REG(offset) (*(volatile u16*)((volatile u16*)(__memReg) + (offset)))
#define GX_GET_CP_REG(offset)  (*(volatile u16*)((volatile u16*)(__cpReg) + (offset)))
#define GX_GET_PE_REG(offset)  (*(volatile u16*)((volatile u16*)(__peReg) + (offset)))
#define GX_GET_PI_REG(offset)  (*(volatile u32*)((volatile u32*)(__piReg) + (offset)))

#define GX_SET_MEM_REG(offset, val) (*(volatile u16*)((volatile u16*)(__memReg) + (offset)) = val)
#define GX_SET_CP_REG(offset, val)  (*(volatile u16*)((volatile u16*)(__cpReg) + (offset)) = val)
#define GX_SET_PE_REG(offset, val)  (*(volatile u16*)((volatile u16*)(__peReg) + (offset)) = val)
#define GX_SET_PI_REG(offset, val)  (*(volatile u32*)((volatile u32*)(__piReg) + (offset)) = val)

#define CHECK_GXBEGIN(line, name) ASSERTMSGLINE(line, !__GXinBegin, "'" name "' is not allowed between GXBegin/GXEnd")

/* GXAttr.c */

void __GXSetVCD(void);
void __GXSetVAT(void);

/* GXBump.c */

void __GXUpdateBPMask(void);
void __GXFlushTextureState(void);

/* GXFifo.c */

// GXFifoObj private data
struct __GXFifoObj {
    u8 *base;
    u8 *top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    void *rdPtr;
    void *wrPtr;
    s32 count;
    u8 bind_cpu;
    u8 bind_gp;
};

void __GXSaveCPUFifoAux(struct __GXFifoObj *realFifo);
void __GXFifoInit(void);
void __GXInsaneWatermark(void);
void __GXCleanGPFifo(void);

/* GXGeometry.c */

void __GXSetDirtyState(void);
void __GXSendFlushPrim(void);
void __GXSetGenMode(void);

/* GXInit.c */
void __GXInitGX();
void __GXInitRevisionBits(void);

typedef struct __GXData_struct {
  u16 vNumNot;
  u16 bpSentNot;
  u16 vNum;
  u16 vLim;
  u32 cpEnable;
  u32 cpStatus;
  u32 cpClr;
  u32 vcdLo;
  u32 vcdHi;
  u32 vatA[8];
  u32 vatB[8];
  u32 vatC[8];
  u32 lpSize;
  u32 matIdxA;
  u32 matIdxB;
  u32 indexBase[4];
  u32 indexStride[4];
  u32 ambColor[2];
  u32 matColor[2];
  u32 suTs0[8];
  u32 suTs1[8];
  u32 suScis0;
  u32 suScis1;
  u32 tref[8];
  u32 iref;
  u32 bpMask;
  u32 IndTexScale0;
  u32 IndTexScale1;
  u32 tevc[16];
  u32 teva[16];
  u32 tevKsel[8];
  u32 cmode0;
  u32 cmode1;
  u32 zmode;
  u32 peCtrl;
  u32 cpDispSrc;
  u32 cpDispSize;
  u32 cpDispStride;
  u32 cpDisp;
  u32 cpTexSrc;
  u32 cpTexSize;
  u32 cpTexStride;
  u32 cpTex;
  GXBool cpTexZ;
  u32 genMode;
  GXTexRegion TexRegions[8];
  GXTexRegion TexRegionsCI[4];
  u32 nextTexRgn;
  u32 nextTexRgnCI;
  GXTlutRegion TlutRegions[20];
  GXTexRegion* (*texRegionCallback)(GXTexObj*, GXTexMapID);
  GXTlutRegion* (*tlutRegionCallback)(u32);
  GXAttrType nrmType;
  GXBool hasNrms;
  GXBool hasBiNrms;
  u32 projType;
  f32 projMtx[6];
  f32 vpLeft;
  f32 vpTop;
  f32 vpWd;
  f32 vpHt;
  f32 vpNearz;
  f32 vpFarz;
  u8 fgRange;
  f32 fgSideX;
  u32 tImage0[8];
  u32 tMode0[8];
  u32 texmapId[16];
  u32 tcsManEnab;
  u32 tevTcEnab;
  GXPerf0 perf0;
  GXPerf1 perf1;
  u32 perfSel;
  GXBool inDispList;
  GXBool dlSaveContext;
  u8 dirtyVAT;
  u32 dirtyState;
} GXData;

extern GXData* gx;
extern u16 *__memReg;
extern u16 *__peReg;
extern u16 *__cpReg;
extern u32 *__piReg;
// #define gx __GXData

/* GXMisc.c */

void __GXBypass(u32 reg);
u16 __GXReadPEReg(u32 reg);
void __GXPEInit(void);
void __GXAbort();

/* GXPerf.c */
void __GXSetBWDials(u16 cpDial, u16 tcDial, u16 peDial, u16 cpuRdDial, u16 cpuWrDial);

#ifdef __MWERKS__
static inline u32 __GXReadCPCounterU32(u32 regAddrL, u32 regAddrH) {
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

    ctrH0 = GX_GET_CP_REG(regAddrH);

    do {
        ctrH1 = ctrH0;
        ctrL = GX_GET_CP_REG(regAddrL);
        ctrH0 = GX_GET_CP_REG(regAddrH);
    } while (ctrH0 != ctrH1);

    return (ctrH0 << 0x10) | ctrL;
}

static inline u32 __GXReadMEMCounterU32(u32 regAddrL, u32 regAddrH) {
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

    ctrH0 = GX_GET_MEM_REG(regAddrH);

    do {
        ctrH1 = ctrH0;
        ctrL = GX_GET_MEM_REG(regAddrL);
        ctrH0 = GX_GET_MEM_REG(regAddrH);
    } while (ctrH0 != ctrH1);

    return (ctrH0 << 0x10) | ctrL;
}

static inline u32 __GXReadPECounterU32(u32 regAddrL, u32 regAddrH) {
    u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

    ctrH0 = GX_GET_PE_REG(regAddrH);

    do {
        ctrH1 = ctrH0;
        ctrL = GX_GET_PE_REG(regAddrL);
        ctrH0 = GX_GET_PE_REG(regAddrH);
    } while (ctrH0 != ctrH1);

    return (ctrH0 << 0x10) | ctrL;
}
#endif

/* GXSave.c */

void __GXShadowDispList(void *list, u32 nbytes);
void __GXShadowIndexState(u32 idx_reg, u32 reg_data);
void __GXPrintShadowState(void);

/* GXStubs.c */

void __GXSetRange(float nearz, float fgSideX);

/* GXTexture.c */

void __GetImageTileCount(GXTexFmt fmt, u16 wd, u16 ht, u32 *rowTiles, u32 *colTiles, u32 *cmpTiles);
void __GXSetSUTexRegs(void);
void __GXGetSUTexSize(GXTexCoordID coord, u16 *width, u16 *height);
void __GXSetTmemConfig(u32 config);

/* GXTransform.c */

void __GXSetMatrixIndex(GXAttr matIdxAttr);

#endif // _DOLPHIN_GXPRIV
