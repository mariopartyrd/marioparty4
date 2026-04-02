#include <string.h>

#include <dolphin/gx.h>
#include <dolphin/os.h>

#include <dolphin/gx/GXPriv.h>

static struct __GXFifoObj DisplayListFifo;
static volatile struct __GXFifoObj *OldCPUFifo;
static struct __GXData_struct __savedGXdata;

void GXBeginDisplayList(void *list, u32 size)
{
    struct __GXFifoObj *CPUFifo = (struct __GXFifoObj *)GXGetCPUFifo();

    CHECK_GXBEGIN(0x89, "GXBeginDisplayList");
    ASSERTMSGLINE(0x8A, !__GXData->inDispList, "GXBeginDisplayList: display list already in progress");
    ASSERTMSGLINE(0x8B, (size & 0x1F) == 0, "GXBeginDisplayList: size is not 32 byte aligned");
    ASSERTMSGLINE(0x8C, ((u32)list & 0x1F) == 0, "GXBeginDisplayList: list is not 32 byte aligned");
    if (gx->dirtyState != 0) {
        __GXSetDirtyState();
    }
    if (gx->dlSaveContext != 0) {
        memcpy(&__savedGXdata, gx, sizeof(__savedGXdata));
    }
    DisplayListFifo.base = (u8 *)list;
    DisplayListFifo.top = (u8 *)list + size - 4;
    DisplayListFifo.size = size;
    DisplayListFifo.count = 0;
    DisplayListFifo.rdPtr = list;
    DisplayListFifo.wrPtr = list;
    gx->inDispList = 1;
    GXSaveCPUFifo((GXFifoObj *)CPUFifo);
    OldCPUFifo = CPUFifo;
    GXSetCPUFifo((GXFifoObj *)&DisplayListFifo);
}

unsigned long GXEndDisplayList(void)
{
    u32 ov;
    BOOL enabled;
    u32 cpenable;

    CHECK_GXBEGIN(0xB5, "GXEndDisplayList");
    ASSERTMSGLINE(0xB6, gx->inDispList == TRUE, "GXEndDisplayList: no display list in progress");
    if (gx->dirtyState != 0) {
        __GXSetDirtyState();
    }
    ov = (__piReg[5] >> 26) & 1;
    __GXSaveCPUFifoAux(&DisplayListFifo);
    ASSERTMSGLINE(0xC3, !ov, "GXEndDisplayList: display list commands overflowed buffer");
    GXSetCPUFifo((GXFifoObj *)OldCPUFifo);
    if (gx->dlSaveContext != 0) {
        enabled = OSDisableInterrupts();
        cpenable = gx->cpEnable;
        memcpy(gx, &__savedGXdata, sizeof(*gx));
        gx->cpEnable = cpenable;
        OSRestoreInterrupts(enabled);
    }
    gx->inDispList = 0;
    if (!ov) {
        return DisplayListFifo.count;
    }
    return 0;
}

void GXCallDisplayList(const void *list, u32 nbytes)
{
    CHECK_GXBEGIN(0xEC, "GXCallDisplayList");
    ASSERTMSGLINE(0xED, !gx->inDispList, "GXCallDisplayList: display list already in progress");
    ASSERTMSGLINE(0xEE, (nbytes & 0x1F) == 0, "GXCallDisplayList: nbytes is not 32 byte aligned");
    ASSERTMSGLINE(0xEF, ((u32)list & 0x1F) == 0, "GXCallDisplayList: list is not 32 byte aligned");

    if (gx->dirtyState != 0) {
        __GXSetDirtyState();
    }
    if (*(u32 *)&gx->vNumNot == 0) { // checks both vNum and bpSent
        __GXSendFlushPrim();
    }
    GX_WRITE_U8(0x40);
    GX_WRITE_U32((u32)list);
    GX_WRITE_U32(nbytes);
}
