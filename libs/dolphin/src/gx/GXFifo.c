#include <dolphin/PPCArch.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <stddef.h>


#include <dolphin/gx/GXPriv.h>

static struct __GXFifoObj* CPUFifo;
static struct __GXFifoObj* GPFifo;
static OSThread* __GXCurrentThread;
static GXBool CPGPLinked;
static BOOL GXOverflowSuspendInProgress;
static GXBreakPtCallback BreakPointCB;
static u32 __GXOverflowCount;

void* __GXCurrentBP;

static void __GXFifoReadEnable(void);
static void __GXFifoReadDisable(void);
static void __GXFifoLink(u8 arg0);
static void __GXWriteFifoIntEnable(u8 arg0, u8 arg1);
static void __GXWriteFifoIntReset(u8 arg0, u8 arg1);

static void GXOverflowHandler(s16 interrupt, OSContext *context)
{
    ASSERTLINE(0x179, !GXOverflowSuspendInProgress);

    __GXOverflowCount++;
    __GXWriteFifoIntEnable(0, 1);
    __GXWriteFifoIntReset(1, 0);
    GXOverflowSuspendInProgress = TRUE;

    OSSuspendThread(__GXCurrentThread);
}

static void GXUnderflowHandler(s16 interrupt, OSContext *context)
{
    ASSERTLINE(0x1A3, GXOverflowSuspendInProgress);

	OSResumeThread(__GXCurrentThread);
	GXOverflowSuspendInProgress = FALSE;
	__GXWriteFifoIntReset(1U, 1U);
	__GXWriteFifoIntEnable(1U, 0U);
}

#define SOME_SET_REG_MACRO(reg, size, shift, val)                                                                                                    \
    do {                                                                                                                                             \
        (reg) = (u32)__rlwimi((u32)(reg), (val), (shift), (32 - (shift) - (size)), (31 - (shift)));                                                  \
    } while (0);

static void GXBreakPointHandler(s16 interrupt, OSContext *context)
{
	OSContext exceptionContext;

	gx->cpEnable = gx->cpEnable & 0xFFFFFFDF;
	__cpReg[1]   = gx->cpEnable;
	if (BreakPointCB != NULL) {
		OSClearContext(&exceptionContext);
		OSSetCurrentContext(&exceptionContext);
		BreakPointCB();
		OSClearContext(&exceptionContext);
		OSSetCurrentContext(context);
	}
}

static void GXCPInterruptHandler(s16 interrupt, OSContext *context)
{
    gx->cpStatus = GX_GET_CP_REG(0);
    if (GET_REG_FIELD(gx->cpEnable, 1, 3) && GET_REG_FIELD(gx->cpStatus, 1, 1)) {
        GXUnderflowHandler(interrupt, context);
    }
    if (GET_REG_FIELD(gx->cpEnable, 1, 2) && GET_REG_FIELD(gx->cpStatus, 1, 0)) {
        GXOverflowHandler(interrupt, context);
    }
    if (GET_REG_FIELD(gx->cpEnable, 1, 5) && GET_REG_FIELD(gx->cpStatus, 1, 4)) {
        GXBreakPointHandler(interrupt, context);
    }
}

void GXInitFifoBase(GXFifoObj *fifo, void *base, u32 size)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;

    ASSERTMSGLINE(0x21E, realFifo != CPUFifo, "GXInitFifoBase: fifo is attached to CPU");
    ASSERTMSGLINE(0x220, realFifo != GPFifo, "GXInitFifoBase: fifo is attached to GP");
    ASSERTMSGLINE(0x222, ((u32)base & 0x1F) == 0, "GXInitFifoBase: base must be 32B aligned");
    ASSERTMSGLINE(0x224, base != NULL, "GXInitFifoBase: base pointer is NULL");
    ASSERTMSGLINE(0x226, (size & 0x1F) == 0, "GXInitFifoBase: size must be 32B aligned");
    ASSERTMSGLINE(0x228, size >= 0x10000, "GXInitFifoBase: fifo is not large enough");

    realFifo->base = base;
    realFifo->top = (u8 *)base + size - 4;
    realFifo->size = size;
    realFifo->count = 0;
    GXInitFifoLimits(fifo, size - 0x4000, (size >> 1) & ~0x1F);
    GXInitFifoPtrs(fifo, base, base);
}

void GXInitFifoPtrs(GXFifoObj *fifo, void *readPtr, void *writePtr)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;
    BOOL enabled;

    ASSERTMSGLINE(0x250, realFifo != CPUFifo, "GXInitFifoPtrs: fifo is attached to CPU");
    ASSERTMSGLINE(0x252, realFifo != GPFifo, "GXInitFifoPtrs: fifo is attached to GP");
    ASSERTMSGLINE(0x254, ((u32)readPtr & 0x1F) == 0, "GXInitFifoPtrs: readPtr not 32B aligned");
    ASSERTMSGLINE(0x256, ((u32)writePtr & 0x1F) == 0, "GXInitFifoPtrs: writePtr not 32B aligned");
    ASSERTMSGLINE(0x259, realFifo->base <= readPtr && readPtr < realFifo->top, "GXInitFifoPtrs: readPtr not in fifo range");
    ASSERTMSGLINE(0x25C, realFifo->base <= writePtr && writePtr < realFifo->top, "GXInitFifoPtrs: writePtr not in fifo range");

    enabled = OSDisableInterrupts();
    realFifo->rdPtr = readPtr;
    realFifo->wrPtr = writePtr;
    realFifo->count = (u8 *)writePtr - (u8 *)readPtr;
    if (realFifo->count < 0) {
        realFifo->count += realFifo->size;
    }
    OSRestoreInterrupts(enabled);
}

void GXInitFifoLimits(GXFifoObj *fifo, u32 hiWatermark, u32 loWatermark)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;

    ASSERTMSGLINE(0x281, realFifo != GPFifo, "GXInitFifoLimits: fifo is attached to GP");
    ASSERTMSGLINE(0x283, (hiWatermark & 0x1F) == 0, "GXInitFifoLimits: hiWatermark not 32B aligned");
    ASSERTMSGLINE(0x285, (loWatermark & 0x1F) == 0, "GXInitFifoLimits: loWatermark not 32B aligned");
    ASSERTMSGLINE(0x287, hiWatermark < realFifo->top - realFifo->base, "GXInitFifoLimits: hiWatermark too large");
    ASSERTMSGLINE(0x289, loWatermark < hiWatermark, "GXInitFifoLimits: hiWatermark below lo watermark");

    realFifo->hiWatermark = hiWatermark;
    realFifo->loWatermark = loWatermark;
}

void GXSetCPUFifo(GXFifoObj *fifo)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;
    BOOL enabled = OSDisableInterrupts();

    CPUFifo = realFifo;
    if (CPUFifo == GPFifo)
    {
        u32 reg = 0;

        __piReg[3] = (u32)realFifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32)realFifo->top & 0x3FFFFFFF;
        SET_REG_FIELD(0x294, reg, 21, 5, ((u32)realFifo->wrPtr & 0x3FFFFFFF) >> 5);
        SET_REG_FIELD(0x295, reg, 1, 26, 0);
        __piReg[5] = reg;
        CPGPLinked = GX_TRUE;
        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    }
    else
    {
        u32 reg;

        if (CPGPLinked)
        {
            __GXFifoLink(0);
            CPGPLinked = GX_FALSE;
        }
        __GXWriteFifoIntEnable(0, 0);
        reg = 0;
        __piReg[3] = (u32)realFifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32)realFifo->top & 0x3FFFFFFF;
        SET_REG_FIELD(0x2B7, reg, 21, 5, ((u32)realFifo->wrPtr & 0x3FFFFFFF) >> 5);
        SET_REG_FIELD(0x2B8, reg, 1, 26, 0);
        __piReg[5] = reg;
    }

    __sync();

    OSRestoreInterrupts(enabled);
}

void GXSetGPFifo(GXFifoObj *fifo)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;
    BOOL enabled = OSDisableInterrupts();

    __GXFifoReadDisable();
    __GXWriteFifoIntEnable(0, 0);
    GPFifo = realFifo;

    GX_SET_CP_REG(16, (u32)realFifo->base & 0xFFFF);
    GX_SET_CP_REG(18, (u32)realFifo->top & 0xFFFF);
    GX_SET_CP_REG(24, realFifo->count & 0xFFFF);
    GX_SET_CP_REG(26, (u32)realFifo->wrPtr & 0xFFFF);
    GX_SET_CP_REG(28, (u32)realFifo->rdPtr & 0xFFFF);
    GX_SET_CP_REG(20, (u32)realFifo->hiWatermark & 0xFFFF);
    GX_SET_CP_REG(22, (u32)realFifo->loWatermark & 0xFFFF);
    GX_SET_CP_REG(17, ((u32)realFifo->base & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(19, ((u32)realFifo->top & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(25, realFifo->count >> 16);
    GX_SET_CP_REG(27, ((u32)realFifo->wrPtr & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(29, ((u32)realFifo->rdPtr & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(21, (u32)realFifo->hiWatermark >> 16);
    GX_SET_CP_REG(23, (u32)realFifo->loWatermark >> 16);

    __sync();

    if (CPUFifo == GPFifo) {
        CPGPLinked = GX_TRUE;
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    }
    else {
        CPGPLinked = GX_FALSE;
        __GXWriteFifoIntEnable(0, 0);
        __GXFifoLink(0);
    }
    __GXWriteFifoIntReset(1, 1);
    __GXFifoReadEnable();
    OSRestoreInterrupts(enabled);
}

void GXSaveCPUFifo(GXFifoObj *fifo)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;
    ASSERTMSGLINE(0x343, realFifo == CPUFifo, "GXSaveCPUFifo: fifo is not attached to CPU");
    __GXSaveCPUFifoAux(realFifo);
}

#define SOME_MACRO1(fifo)                                                                                                                            \
    do {                                                                                                                                             \
        u32 temp = GX_GET_CP_REG(29) << 16;                                                                                                          \
        temp |= GX_GET_CP_REG(28);                                                                                                                   \
        fifo->rdPtr = OSPhysicalToCached(temp);                                                                                                      \
    } while (0)

#define SOME_MACRO2(fifo)                                                                                                                            \
    do {                                                                                                                                             \
        u32 temp = GX_GET_CP_REG(25) << 16;                                                                                                          \
        temp |= GX_GET_CP_REG(24);                                                                                                                   \
        fifo->count = temp;                                                                                                                          \
    } while (0)

void __GXSaveCPUFifoAux(struct __GXFifoObj *realFifo)
{
    BOOL enabled = OSDisableInterrupts();

    GXFlush();
    realFifo->base = OSPhysicalToCached(__piReg[3]);
    realFifo->top = OSPhysicalToCached(__piReg[4]);
    realFifo->wrPtr = OSPhysicalToCached(__piReg[5] & 0xFBFFFFFF);
    if (CPGPLinked) {
        SOME_MACRO1(realFifo);
        SOME_MACRO2(realFifo);
    } else {
        realFifo->count = (u8 *)realFifo->wrPtr - (u8 *)realFifo->rdPtr;
        if (realFifo->count < 0)
            realFifo->count += realFifo->size;
    }
    OSRestoreInterrupts(enabled);
}

void GXSaveGPFifo(GXFifoObj *fifo)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;
    unsigned long cpStatus;
    unsigned char readIdle;
    unsigned long temp;

    ASSERTMSGLINE(0x38C, realFifo == GPFifo, "GXSaveGPFifo: fifo is not attached to GP");
    cpStatus = GX_GET_CP_REG(0);
    readIdle = GET_REG_FIELD(cpStatus, 1, 2);
    ASSERTMSGLINE(0x393, readIdle, "GXSaveGPFifo: GP is not idle");

    SOME_MACRO1(realFifo);
    SOME_MACRO2(realFifo);
}

void GXGetGPStatus(GXBool *overhi, GXBool *underlow, GXBool *readIdle, GXBool *cmdIdle, GXBool *brkpt)
{
    gx->cpStatus = GX_GET_CP_REG(0);
    *overhi = GET_REG_FIELD(gx->cpStatus, 1, 0);
    *underlow = (int)GET_REG_FIELD(gx->cpStatus, 1, 1);
    *readIdle = (int)GET_REG_FIELD(gx->cpStatus, 1, 2);
    *cmdIdle = (int)GET_REG_FIELD(gx->cpStatus, 1, 3);
    *brkpt = (int)GET_REG_FIELD(gx->cpStatus, 1, 4);
}

void GXGetFifoStatus(GXFifoObj *fifo, GXBool *overhi, GXBool *underflow, u32 *fifoCount, GXBool *cpuWrite, GXBool *gpRead, GXBool *fifowrap)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;

    *underflow = GX_FALSE;
    *overhi = GX_FALSE;
    *fifoCount = 0;
    *fifowrap = GX_FALSE;
    if (realFifo == GPFifo) {
        SOME_MACRO1(realFifo);
        SOME_MACRO2(realFifo);
    }
    if (realFifo == CPUFifo) {
        GXFlush();
        __GXSaveCPUFifoAux(realFifo);
        *fifowrap = (int)GET_REG_FIELD(GX_GET_PI_REG(5), 1, 26);
    }
    *overhi = (realFifo->count > realFifo->hiWatermark);
    *underflow = (realFifo->count < realFifo->loWatermark);
    *fifoCount = (realFifo->count);
    *cpuWrite = (CPUFifo == realFifo);
    *gpRead = (GPFifo == realFifo);
}

void GXGetFifoPtrs(GXFifoObj *fifo, void **readPtr, void **writePtr)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;

    if (realFifo == CPUFifo) {
        realFifo->wrPtr = OSPhysicalToCached(GX_GET_PI_REG(5) & 0xFBFFFFFF);
    }
    if (realFifo == GPFifo) {
        SOME_MACRO1(realFifo);
        SOME_MACRO2(realFifo);
    }
    else {
        realFifo->count = (u8 *)realFifo->wrPtr - (u8 *)realFifo->rdPtr;
        if (realFifo->count < 0) {
            realFifo->count += realFifo->size;
        }
    }
    *readPtr = realFifo->rdPtr;
    *writePtr = realFifo->wrPtr;
}

void *GXGetFifoBase(const GXFifoObj *fifo)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;

    return realFifo->base;
}

u32 GXGetFifoSize(const GXFifoObj *fifo)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;

    return realFifo->size;
}

void GXGetFifoLimits(const GXFifoObj *fifo, u32 *hi, u32 *lo)
{
    struct __GXFifoObj *realFifo = (struct __GXFifoObj *)fifo;

    *hi = realFifo->hiWatermark;
    *lo = realFifo->loWatermark;
}

GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb)
{
    GXBreakPtCallback oldcb = BreakPointCB;
    BOOL enabled = OSDisableInterrupts();

    BreakPointCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}

void *__GXCurrentBP;

void GXEnableBreakPt(void *break_pt)
{
    BOOL enabled = OSDisableInterrupts();

    __GXFifoReadDisable();
    GX_SET_CP_REG(30, (u32)break_pt);
    GX_SET_CP_REG(31, ((u32)break_pt >> 16) & 0x3FFF);
    SOME_SET_REG_MACRO(gx->cpEnable, 1, 1, 1);
    SOME_SET_REG_MACRO(gx->cpEnable, 1, 5, 1);
    GX_SET_CP_REG(1, gx->cpEnable);
    __GXCurrentBP = break_pt;
    __GXFifoReadEnable();
    OSRestoreInterrupts(enabled);
}

void GXDisableBreakPt(void)
{
    BOOL enabled = OSDisableInterrupts();

    SOME_SET_REG_MACRO(gx->cpEnable, 1, 1, 0);
    SOME_SET_REG_MACRO(gx->cpEnable, 1, 5, 0);
    GX_SET_CP_REG(1, gx->cpEnable);
    __GXCurrentBP = NULL;
    OSRestoreInterrupts(enabled);
}

void __GXFifoInit(void)
{
    __OSSetInterruptHandler(0x11, GXCPInterruptHandler);
    __OSUnmaskInterrupts(0x4000);
    __GXCurrentThread = OSGetCurrentThread();
    GXOverflowSuspendInProgress = FALSE;
    CPUFifo = NULL;
    GPFifo = NULL;
}

static void __GXFifoReadEnable(void)
{
    SET_REG_FIELD(0, gx->cpEnable, 1, 0, 1);
    GX_SET_CP_REG(1, gx->cpEnable);
}

static void __GXFifoReadDisable(void)
{
    SET_REG_FIELD(0, gx->cpEnable, 1, 0, 0);
    GX_SET_CP_REG(1, gx->cpEnable);
}

static void __GXFifoLink(u8 en)
{
    SET_REG_FIELD(0x4DA, gx->cpEnable, 1, 4, (en != 0) ? 1 : 0);
    GX_SET_CP_REG(1, gx->cpEnable);
}

static void __GXWriteFifoIntEnable(u8 hiWatermarkEn, u8 loWatermarkEn)
{
    SET_REG_FIELD(0x4F0, gx->cpEnable, 1, 2, hiWatermarkEn);
    SET_REG_FIELD(0x4F1, gx->cpEnable, 1, 3, loWatermarkEn);
    GX_SET_CP_REG(1, gx->cpEnable);
}

static void __GXWriteFifoIntReset(u8 hiWatermarkClr, u8 loWatermarkClr)
{
    SET_REG_FIELD(0x508, gx->cpClr, 1, 0, hiWatermarkClr);
    SET_REG_FIELD(0x509, gx->cpClr, 1, 1, loWatermarkClr);
    GX_SET_CP_REG(2, gx->cpClr);
}

void __GXInsaneWatermark(void)
{
    struct __GXFifoObj *realFifo = GPFifo;

    realFifo->hiWatermark = realFifo->loWatermark + 512;
    GX_SET_CP_REG(20, (realFifo->hiWatermark & 0x3FFFFFFF) & 0xFFFF);
    GX_SET_CP_REG(21, (realFifo->hiWatermark & 0x3FFFFFFF) >> 16);
}

void __GXCleanGPFifo(void)
{
    GXFifoObj dummyFifo;
    GXFifoObj *gpFifo = GXGetGPFifo();
    GXFifoObj *cpuFifo = GXGetCPUFifo();
    void *base = GXGetFifoBase(gpFifo);

    dummyFifo = *gpFifo;
    GXInitFifoPtrs(&dummyFifo, base, base);
    GXSetGPFifo(&dummyFifo);
    if (cpuFifo == gpFifo) {
        GXSetCPUFifo(&dummyFifo);
    }
    GXInitFifoPtrs(gpFifo, base, base);
    GXSetGPFifo(gpFifo);
    if (cpuFifo == gpFifo) {
        GXSetCPUFifo(cpuFifo);
    }
}

OSThread *GXSetCurrentGXThread(void)
{
    BOOL enabled;
    struct OSThread *prev;

    enabled = OSDisableInterrupts();
    prev = __GXCurrentThread;
    ASSERTMSGLINE(0x561, !GXOverflowSuspendInProgress, "GXSetCurrentGXThread: Two threads cannot generate GX commands at the same time!");
    __GXCurrentThread = OSGetCurrentThread();
    OSRestoreInterrupts(enabled);
    return prev;
}

OSThread *GXGetCurrentGXThread(void)
{
    return __GXCurrentThread;
}

GXFifoObj *GXGetCPUFifo(void)
{
    return (GXFifoObj *)CPUFifo;
}

GXFifoObj *GXGetGPFifo(void)
{
    return (GXFifoObj *)GPFifo;
}

u32 GXGetOverflowCount(void)
{
    return __GXOverflowCount;
}

u32 GXResetOverflowCount(void)
{
    u32 oldcount;

    oldcount = __GXOverflowCount;
    __GXOverflowCount = 0;
    return oldcount;
}

// NONMATCHING
volatile void *GXRedirectWriteGatherPipe(void *ptr)
{
    u32 reg = 0;
    BOOL enabled = OSDisableInterrupts();

    CHECK_GXBEGIN(0x5D5, "GXRedirectWriteGatherPipe");
    ASSERTLINE(0x5D6, OFFSET(ptr, 32) == 0);
    ASSERTLINE(0x5D8, !IsWGPipeRedirected);

    GXFlush();
    while (PPCMfwpar() & 1) { }
    PPCMtwpar((u32)OSUncachedToPhysical((void *)GXFIFO_ADDR));
    if (CPGPLinked) {
        __GXFifoLink(0);
        __GXWriteFifoIntEnable(0, 0);
    }
    CPUFifo->wrPtr = OSPhysicalToCached(GX_GET_PI_REG(5) & 0xFBFFFFFF);
    GX_SET_PI_REG(3, 0);
    GX_SET_PI_REG(4, 0x04000000);
    SET_REG_FIELD(0x5F7, reg, 21, 5, ((u32)ptr & 0x3FFFFFFF) >> 5);
    reg &= 0xFBFFFFFF;
    GX_SET_PI_REG(5, reg);
    PPCSync();
    OSRestoreInterrupts(enabled);
    return (volatile void *)GXFIFO_ADDR;
}

// NONMATCHING
void GXRestoreWriteGatherPipe(void)
{
    u32 reg = 0; // r31
    u32 i; // r29
    BOOL enabled; // r28

    ASSERTLINE(0x610, IsWGPipeRedirected);
    enabled = OSDisableInterrupts();
    for (i = 0; i < 31; i++) {
        GXWGFifo.u8 = 0;
    }
    PPCSync();
    while (PPCMfwpar() & 1) { }
    PPCMtwpar((u32)OSUncachedToPhysical((void *)GXFIFO_ADDR));
    GX_SET_PI_REG(3, (u32)CPUFifo->base & 0x3FFFFFFF);
    GX_SET_PI_REG(4, (u32)CPUFifo->top & 0x3FFFFFFF);
    SET_REG_FIELD(0x62A, reg, 21, 5, ((u32)CPUFifo->wrPtr & 0x3FFFFFFF) >> 5);
    reg &= 0xFBFFFFFF;
    GX_SET_PI_REG(5, reg);
    if (CPGPLinked) {
        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    }
    PPCSync();
    OSRestoreInterrupts(enabled);
}
