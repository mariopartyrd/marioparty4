#ifndef _DOLPHIN_OSBOOTINFO
#define _DOLPHIN_OSBOOTINFO

#include "dolphin/DVDPriv.h"
#include "dolphin/types.h"

typedef struct OSBootInfo_s {
  DVDDiskID DVDDiskID;
  u32 magic;
  u32 version;
  u32 memorySize;
  u32 consoleType;
  void* arenaLo;
  void* arenaHi;
  void* FSTLocation;
  u32 FSTMaxLength;
} OSBootInfo;

typedef struct {
  BOOL valid;
  u32 restartCode;
  u32 bootDol;
  void* regionStart;
  void* regionEnd;
  BOOL argsUseDefault;
  void* argsAddr; // valid only when argsUseDefault = FALSE

} OSExecParams;

typedef struct BI2Debug {
  s32 debugMonSize;  // 0x0
  s32 simMemSize;    // 0x4
  u32 argOffset;     // 0x8
  u32 debugFlag;     // 0xC
  int trackLocation; // 0x10
  int trackSize;     // 0x14
  u32 countryCode;   // 0x18
  u8 unk[8];         // 0x1C
  u32 padSpec;       // 0x24
} BI2Debug;

// Magic number defines.
#define OS_BOOTINFO_MAGIC 0x0D15EA5E
#define OS_BOOTINFO_MAGIC_JTAG 0xE5207C22
#define OS_DVD_MAGIC_NINTENDO 0xC2339F3D
#define OS_THREAD_STACK_MAGIC 0xDEADBABE

#define OS_BOOTROM_ADDR ((void*)0x81300000)

#endif // _DOLPHIN_OSBOOTINFO
