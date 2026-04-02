#ifndef _DOLPHIN_CARDPRIV
#define _DOLPHIN_CARDPRIV

#ifdef __cplusplus
extern "C" {
#endif

#define CARD_FAT_AVAIL 0x0000u
#define CARD_FAT_CHECKSUM 0x0000u
#define CARD_FAT_CHECKSUMINV 0x0001u
#define CARD_FAT_CHECKCODE 0x0002u
#define CARD_FAT_FREEBLOCKS 0x0003u
#define CARD_FAT_LASTSLOT 0x0004u

#define CARD_PAGE_SIZE 128u
#define CARD_SEG_SIZE 512u

#define CARD_NUM_SYSTEM_BLOCK 5
#define CARD_SYSTEM_BLOCK_SIZE (8 * 1024u)

#define CARD_MAX_MOUNT_STEP (CARD_NUM_SYSTEM_BLOCK + 2)

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 _padding0;
    u8 bannerFormat;
    u8 fileName[CARD_FILENAME_MAX];
    u32 time; // seconds since 01/01/2000 midnight

    u32 iconAddr; // 0xffffffff if not used
    u16 iconFormat;
    u16 iconSpeed;

    u8 permission;
    u8 copyTimes;
    u16 startBlock;
    u16 length;
    u8 _padding1[2];

    u32 commentAddr; // 0xffffffff if not used
} CARDDir;

typedef struct CARDDirCheck {
    u8 padding0[64 - 2 * 4];
    u16 padding1;
    s16 checkCode;
    u16 checkSum;
    u16 checkSumInv;
} CARDDirCheck;

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u16 size;
    u16 pageSize;
    s32 sectorSize;
    u16 cBlock;
    u16 vendorID;
    s32 latency;
    u8 id[12];
    int mountStep;
    int formatStep;
    u32 scramble;
    DSPTaskInfo task;
    void *workArea;
    CARDDir *currentDir;
    u16 *currentFat;
    OSThreadQueue threadQueue;
    u8 cmd[9];
    s32 cmdlen;
    vu32 mode;
    int retry;
    int repeat;
    u32 addr;
    void *buffer;
    s32 xferred;
    u16 freeNo;
    u16 startBlock;
    CARDFileInfo *fileInfo;
    CARDCallback extCallback;
    CARDCallback txCallback;
    CARDCallback exiCallback;
    CARDCallback apiCallback;
    CARDCallback xferCallback;
    CARDCallback eraseCallback;
    CARDCallback unlockCallback;
    OSAlarm alarm;
    u32 cid;
    const DVDDiskID *diskID;
} CARDControl;

typedef struct CARDID {
    u8 serial[32]; // flashID[12] + timebase[8] + counterBias[4] + language[4] + XXX[4]
    u16 deviceID;
    u16 size;
    u16 encode; // character set -- 0: S-JIS, 1: ANSI

    u8 padding[512 - 32 - 5 * 2];

    u16 checkSum;
    u16 checkSumInv;
} CARDID;

void __CARDDefaultApiCallback(s32 chan, s32 result);
s32 __CARDEraseSector(s32 chan, u32 addr, CARDCallback callback);
s32 __CARDPutControlBlock(struct CARDControl *card, s32 result);
void __CARDSyncCallback(s32 chan, s32 result);
u16 *__CARDGetFatBlock(CARDControl *card);

/* CARDBios */
void __CARDExtHandler(s32 chan, OSContext *context);
void __CARDExiHandler(s32 chan, OSContext *context);
void __CARDTxHandler(s32 chan, OSContext *context);
void __CARDUnlockedHandler(s32 chan, OSContext *context);
s32 __CARDEnableInterrupt(s32 chan, BOOL enable);
s32 __CARDReadStatus(s32 chan, u8 *status);
s32 __CARDReadVendorID(s32 chan, u16 *vendorId);
s32 __CARDClearStatus(s32 chan);
s32 __CARDStart(s32 chan, CARDCallback txCallback, CARDCallback exiCallback);
s32 __CARDReadSegment(s32 chan, CARDCallback callback);
s32 __CARDWritePage(s32 chan, CARDCallback callback);
u16 __CARDGetFontEncode(void);
void __CARDSetDiskID(const DVDDiskID *id);
s32 __CARDGetControlBlock(s32 chan, struct CARDControl **pcard);
s32 __CARDSync(s32 chan);

/* CARDBlock */
s32 __CARDAllocBlock(s32 chan, u32 cBlock, CARDCallback callback);
s32 __CARDFreeBlock(s32 chan, u16 nBlock, CARDCallback callback);
s32 __CARDUpdateFatBlock(s32 chan, u16 *fat, CARDCallback callback);

/* CARDCheck */
void __CARDCheckSum(void *ptr, int length, u16 *checksum, u16 *checksumInv);
s32 __CARDVerify(CARDControl *card);

/* CARDDir */
CARDDir *__CARDGetDirBlock(CARDControl *card);
s32 __CARDUpdateDir(s32 chan, CARDCallback callback);

/* CARDFormat */
s32 __CARDFormatRegionAsync(s32 chan, u16 encode, CARDCallback callback);

/* CARDMount */
void __CARDMountCallback(s32 chan, s32 result);

/* CARDOpen */
BOOL __CARDCompareFileName(CARDDir *ent, const char *fileName);
s32 __CARDAccess(CARDControl *card, CARDDir *ent);
BOOL __CARDIsPublic(CARDDir *ent);
s32 __CARDIsReadable(CARDControl *card, CARDDir *ent);
s32 __CARDGetFileNo(CARDControl *card, const char *fileName, s32 *pfileNo);
BOOL __CARDIsOpened(CARDControl *card, s32 fileNo);

/* CARDRdwr */
s32 __CARDRead(s32 chan, u32 addr, s32 length, void *dst, CARDCallback callback);
s32 __CARDWrite(s32 chan, u32 addr, s32 length, void *dst, CARDCallback callback);

/* CARDRead */
s32 __CARDSeek(CARDFileInfo *fileInfo, s32 length, s32 offset, CARDControl **pcard);

/* CARDUnlock */
s32 __CARDUnlock(s32 chan, u8 flashID[12]);

#define CARDIsValidBlockNo(card, iBlock) (CARD_NUM_SYSTEM_BLOCK <= (iBlock) && (iBlock) < (card)->cBlock)
#define __CARDGetDirCheck(dir) ((CARDDirCheck *)&(dir)[CARD_MAX_FILE])

#define TRUNC(n, a) (((u32)(n)) & ~((a)-1))
#define OFFSET(n, a) (((u32)(n)) & ((a)-1))

extern CARDControl __CARDBlock[2];
extern DVDDiskID __CARDDiskNone;
extern u16 __CARDVendorID;

#ifdef __cplusplus
}
#endif
#endif // _DOLPHIN_CARDPRIV
