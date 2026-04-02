
#include "dolphin/DVDPriv.h"
#include "dolphin/os.h"
#include "dolphin/os/OSBootInfo.h"

typedef struct FSTEntry FSTEntry;

struct FSTEntry {
	unsigned int isDirAndStringOff;
	unsigned int parentOrPosition;
	unsigned int nextEntryOrLength;
};

static OSBootInfo* BootInfo;
static FSTEntry* FstStart;
static char* FstStringStart;
static u32 MaxEntryNum;
static u32 currentDirectory = 0;
OSThreadQueue __DVDThreadQueue;
u32 __DVDLongFileNameFlag = 0;

static void cbForReadAsync(s32 result, DVDCommandBlock* block);
static void cbForReadSync(s32 result, DVDCommandBlock* block);
static void cbForSeekAsync(s32 result, DVDCommandBlock* block);
static void cbForSeekSync(s32 result, DVDCommandBlock* block);
static void cbForPrepareStreamAsync(s32 result, DVDCommandBlock* block);
static void cbForPrepareStreamSync(s32 result, DVDCommandBlock* block);

void __DVDFSInit() {
	BootInfo = (OSBootInfo*)OSPhysicalToCached(0);
	FstStart = (FSTEntry*)BootInfo->FSTLocation;

	if (FstStart) {
		MaxEntryNum = FstStart[0].nextEntryOrLength;
		FstStringStart = (char*)&(FstStart[MaxEntryNum]);
	}
}

/* For convenience */
#define entryIsDir(i) (((FstStart[i].isDirAndStringOff & 0xff000000) == 0) ? FALSE : TRUE)
#define stringOff(i) (FstStart[i].isDirAndStringOff & ~0xff000000)
#define parentDir(i) (FstStart[i].parentOrPosition)
#define nextDir(i) (FstStart[i].nextEntryOrLength)
#define filePosition(i) (FstStart[i].parentOrPosition)
#define fileLength(i) (FstStart[i].nextEntryOrLength)

static BOOL isSame(const char* path, const char* string) {
	while (*string != '\0') {
		if (tolower(*path++) != tolower(*string++)) {
			return FALSE;
		}
	}

	if ((*path == '/') || (*path == '\0')) {
		return TRUE;
	}

	return FALSE;
}

s32 DVDConvertPathToEntrynum(char* pathPtr) {
	const char* ptr;
	char* stringPtr;
	BOOL isDir;
	u32 length;
	u32 dirLookAt;
	u32 i;
	const char* origPathPtr = pathPtr;
	const char* extentionStart;
	BOOL illegal;
	BOOL extention;

	dirLookAt = currentDirectory;

	while (1) {

		if (*pathPtr == '\0') {
			return (s32)dirLookAt;
		} else if (*pathPtr == '/') {
			dirLookAt = 0;
			pathPtr++;
			continue;
		} else if (*pathPtr == '.') {
			if (*(pathPtr + 1) == '.') {
				if (*(pathPtr + 2) == '/') {
					dirLookAt = parentDir(dirLookAt);
					pathPtr += 3;
					continue;
				} else if (*(pathPtr + 2) == '\0') {
					return (s32)parentDir(dirLookAt);
				}
			} else if (*(pathPtr + 1) == '/') {
				pathPtr += 2;
				continue;
			} else if (*(pathPtr + 1) == '\0') {
				return (s32)dirLookAt;
			}
		}

		if (__DVDLongFileNameFlag == 0) {
			extention = FALSE;
			illegal = FALSE;

			for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++) {
				if (*ptr == '.') {
					if ((ptr - pathPtr > 8) || (extention == TRUE)) {
						illegal = TRUE;
						break;
					}
					extention = TRUE;
					extentionStart = ptr + 1;

				} else if (*ptr == ' ')
					illegal = TRUE;
			}

			if ((extention == TRUE) && (ptr - extentionStart > 3))
				illegal = TRUE;

			if (illegal)
				OSPanic(__FILE__, 376,
								"DVDConvertEntrynumToPath(possibly DVDOpen or DVDChangeDir or DVDOpenDir): "
								"specified directory or file (%s) doesn't match standard 8.3 format. This is a "
								"temporary restriction and will be removed soon\n",
								origPathPtr);
		} else {
			for (ptr = pathPtr; (*ptr != '\0') && (*ptr != '/'); ptr++)
				;
		}

		isDir = (*ptr == '\0') ? FALSE : TRUE;
		length = (u32)(ptr - pathPtr);

		ptr = pathPtr;

		for (i = dirLookAt + 1; i < nextDir(dirLookAt); i = entryIsDir(i) ? nextDir(i) : (i + 1)) {
			if ((entryIsDir(i) == FALSE) && (isDir == TRUE)) {
				continue;
			}

			stringPtr = FstStringStart + stringOff(i);

			if (isSame(ptr, stringPtr) == TRUE) {
				goto next_hier;
			}
		}

		return -1;

	next_hier:
		if (!isDir) {
			return (s32)i;
		}

		dirLookAt = i;
		pathPtr += length + 1;
	}
}

BOOL DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo) {
	if ((entrynum < 0) || (entrynum >= MaxEntryNum) || entryIsDir(entrynum)) {
		return FALSE;
	}

	fileInfo->startAddr = filePosition(entrynum);
	fileInfo->length = fileLength(entrynum);
	fileInfo->callback = (DVDCallback)NULL;
	fileInfo->cb.state = DVD_STATE_END;

	return TRUE;
}

BOOL DVDOpen(char* fileName, DVDFileInfo* fileInfo) {
	s32 entry;
	char currentDir[128];

	entry = DVDConvertPathToEntrynum(fileName);

	if (0 > entry) {
		DVDGetCurrentDir(currentDir, 128);
		OSReport("Warning: DVDOpen(): file '%s' was not found under %s.\n", fileName, currentDir);
		return FALSE;
	}

	if (entryIsDir(entry)) {
		return FALSE;
	}

	fileInfo->startAddr = filePosition(entry);
	fileInfo->length = fileLength(entry);
	fileInfo->callback = (DVDCallback)NULL;
	fileInfo->cb.state = DVD_STATE_END;

	return TRUE;
}

BOOL DVDClose(DVDFileInfo* fileInfo) {
	DVDCancel(&(fileInfo->cb));
	return TRUE;
}

static u32 myStrncpy(char* dest, char* src, u32 maxlen) {
	u32 i = maxlen;

	while ((i > 0) && (*src != 0)) {
		*dest++ = *src++;
		i--;
	}

	return (maxlen - i);
}

static u32 entryToPath(u32 entry, char* path, u32 maxlen) {
	char* name;
	u32 loc;

	if (entry == 0) {
		return 0;
	}

	name = FstStringStart + stringOff(entry);

	loc = entryToPath(parentDir(entry), path, maxlen);

	if (loc == maxlen) {
		return loc;
	}

	*(path + loc++) = '/';

	loc += myStrncpy(path + loc, name, maxlen - loc);

	return loc;
}

static BOOL DVDConvertEntrynumToPath(s32 entrynum, char* path, u32 maxlen) {
	u32 loc;

	loc = entryToPath((u32)entrynum, path, maxlen);

	if (loc == maxlen) {
		path[maxlen - 1] = '\0';
		return FALSE;
	}

	if (entryIsDir(entrynum)) {
		if (loc == maxlen - 1) {
			path[loc] = '\0';
			return FALSE;
		}

		path[loc++] = '/';
	}

	path[loc] = '\0';
	return TRUE;
}

BOOL DVDGetCurrentDir(char* path, u32 maxlen) {
	return DVDConvertEntrynumToPath((s32)currentDirectory, path, maxlen);
}

BOOL DVDChangeDir(char* dirName) {
	s32 entry;
	entry = DVDConvertPathToEntrynum(dirName);
	if ((entry < 0) || (entryIsDir(entry) == FALSE)) {
		return FALSE;
	}

	currentDirectory = (u32)entry;

	return TRUE;
}

BOOL DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset,
											DVDCallback callback, s32 prio) {

	if (!((0 <= offset) && (offset < fileInfo->length))) {
		OSPanic(__FILE__, 739, "DVDReadAsync(): specified area is out of the file  ");
	}

	if (!((0 <= offset + length) && (offset + length < fileInfo->length + DVD_MIN_TRANSFER_SIZE))) {
		OSPanic(__FILE__, 745, "DVDReadAsync(): specified area is out of the file  ");
	}

	fileInfo->callback = callback;
	DVDReadAbsAsyncPrio(&(fileInfo->cb), addr, length, (s32)(fileInfo->startAddr + offset),
											cbForReadAsync, prio);

	return TRUE;
}
#ifndef offsetof
#define offsetof(type, memb) ((u32) & ((type*)0)->memb)
#endif

static void cbForReadAsync(s32 result, DVDCommandBlock* block) {
	DVDFileInfo* fileInfo;

	fileInfo = (DVDFileInfo*)((char*)block - offsetof(DVDFileInfo, cb));
	if (fileInfo->callback) {
		(fileInfo->callback)(result, fileInfo);
	}
}

/* This is based on the revolution SDK, these may not match in all cases I have also left the line numbers at 0 */
BOOL DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio) {
	BOOL result;
	DVDCommandBlock* block;
	s32 state;
	BOOL enabled;
	s32 retVal;

	if (!((0 <= offset) && (offset < fileInfo->length))) {
		OSPanic(__FILE__, 809, "DVDRead(): specified area is out of the file  ");
	}

	if (!((0 <= offset + length) && (offset + length < fileInfo->length + DVD_MIN_TRANSFER_SIZE))) {
		OSPanic(__FILE__, 815, "DVDRead(): specified area is out of the file  ");
	}

	block = &(fileInfo->cb);

	result = DVDReadAbsAsyncPrio(block, addr, length, (s32)(fileInfo->startAddr + offset),
															 cbForReadSync, prio);

	if (result == FALSE) {
		return -1;
	}

	enabled = OSDisableInterrupts();

	while(1) {
		state = ((volatile DVDCommandBlock*)block)->state;

		if (state == DVD_STATE_END) {
			retVal = (s32)block->transferredSize;
			break;
		}
		if (state == DVD_STATE_FATAL_ERROR) {
			retVal = DVD_RESULT_FATAL_ERROR;
			break;
		}
		if (state == DVD_STATE_CANCELED) {
			retVal = DVD_RESULT_CANCELED;
			break;
		}

		OSSleepThread(&__DVDThreadQueue);
	}

	OSRestoreInterrupts(enabled);
	return retVal;
}

/* This is based on the revolution SDK, these may not match in all cases */
static void cbForReadSync(s32 result, DVDCommandBlock* block) { OSWakeupThread(&__DVDThreadQueue); }