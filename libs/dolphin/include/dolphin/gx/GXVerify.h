#ifndef _DOLPHIN_GXVERIFY
#define _DOLPHIN_GXVERIFY

#include <dolphin/types.h>

typedef enum {
  GX_WARN_NONE,
  GX_WARN_SEVERE,
  GX_WARN_MEDIUM,
  GX_WARN_ALL
} GXWarningLevel;

#ifdef _DEBUG
extern void GXSetVerifyLevel(GXWarningLevel level);
#else
#define GXSetVerifyLevel(level) ((void)0)
#endif

typedef void (*GXVerifyCallback)(GXWarningLevel level, u32 id, const char* msg);

typedef struct __GXVerifyData {
  GXVerifyCallback cb;        // offset 0x0, size 0x4
  GXWarningLevel verifyLevel; // offset 0x4, size 0x4
  u32 xfRegs[80];             // offset 0x8, size 0x140
  u32 xfMtx[256];             // offset 0x148, size 0x400
  u32 xfNrm[96];              // offset 0x548, size 0x180
  u32 xfDMtx[256];            // offset 0x6C8, size 0x400
  u32 xfLight[128];           // offset 0xAC8, size 0x200
  u32 rasRegs[256];           // offset 0xCC8, size 0x400
  u8 xfRegsDirty[80];         // offset 0x10C8, size 0x50
  u8 xfMtxDirty[256];         // offset 0x1118, size 0x100
  u8 xfNrmDirty[96];          // offset 0x1218, size 0x60
  u8 xfDMtxDirty[256];        // offset 0x1278, size 0x100
  u8 xfLightDirty[128];       // offset 0x1378, size 0x80
} GXVerifyData;

#ifdef _DEBUG
GXVerifyCallback GXSetVerifyCallback(GXVerifyCallback cb);
#else
#define GXSetVerifyCallback(cb) ((GXVerifyCallback)0)
#endif

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXVERIFY
