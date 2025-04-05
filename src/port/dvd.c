// Credits: Super Monkey Ball

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#include <windows.h>

#else
#include <unistd.h>
#endif
#include <dolphin.h>

#ifndef PATH_MAX
#define PATH_MAX 256
#endif

static char (*s_pathEntries)[PATH_MAX] = NULL;
static int s_pathEntriesCount = 0;
static char s_rootDir[PATH_MAX];

void DVDInit(void)
{
    chdir("GMPE01_00/files");
    if (getcwd(s_rootDir, sizeof(s_rootDir)) == NULL)
        exit(1);
}

BOOL DVDChangeDir(char *dir)
{
    printf("DVDChangeDir: %s\n", dir);
    if (dir[0] == '/') {
        char path[PATH_MAX];
        if (snprintf(path, sizeof(path), "%s/%s", s_rootDir, dir) >= PATH_MAX)
            return FALSE;
        return chdir(path) == 0;
    }
    else
        return chdir(dir) == 0;
}

s32 DVDConvertPathToEntrynum(char *pathPtr)
{
    int i;
    FILE *f;
    char absolute[PATH_MAX];

    printf("DVDConvertPathToEntrynum: %s\n", pathPtr);
#ifdef _WIN32
    if (GetFullPathNameA(pathPtr, sizeof(absolute), absolute, NULL) == 0)
        return -1;
#else
    if (realpath(pathPtr, absolute) == NULL)
        return -1;
#endif
    for (i = 0; i < s_pathEntriesCount; i++) {
        if (strcmp(absolute, s_pathEntries[i]) == 0)
            return i;
    }

    if (strlen(absolute) + 1 > PATH_MAX)
        return -1;

    // check if file exists
    f = fopen(absolute, "rb");
    if (f == NULL)
        return -1;
    fclose(f);

    // add new entry
    printf("size = %i\n", sizeof(*s_pathEntries));
    s_pathEntries = realloc(s_pathEntries, (s_pathEntriesCount + 1) * sizeof(*s_pathEntries));
    strcpy(s_pathEntries[s_pathEntriesCount], absolute);
    return s_pathEntriesCount++;
}

BOOL DVDOpen(char *fileName, DVDFileInfo *fileInfo)
{
    FILE *f;

    printf("DVDOpen: %s\n", fileName);
    f = fopen(fileName, "rb");
    if (f == NULL) {
        puts("open failed\n");
        return FALSE;
    }
    fileInfo->cb.addr = f;
    fseek(f, 0, SEEK_END);
    fileInfo->length = ftell(f);
    return TRUE;
}

BOOL DVDFastOpen(s32 entrynum, DVDFileInfo *fileInfo)
{
    printf("DVDFastOpen: %li\n", entrynum);
    if (entrynum < s_pathEntriesCount)
        return DVDOpen(s_pathEntries[entrynum], fileInfo);
    return FALSE;
}

BOOL DVDClose(DVDFileInfo *fileInfo)
{
    FILE *f = fileInfo->cb.addr;

    if (f != NULL)
        fclose(f);
    fileInfo->cb.addr = NULL;
    return TRUE;
}

BOOL DVDReadPrio(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset, s32 prio)
{
    FILE *f = fileInfo->cb.addr;
    BOOL success;

    printf("DVDReadPrio: length %li, offset %li\n", length, offset);
    fseek(f, offset, SEEK_SET);
    success = (fread(addr, length, 1, f) == 1) || feof(f);
    if (!success)
        puts("read failed");
    return TRUE;
}

BOOL DVDReadAsyncPrio(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset, DVDCallback callback, s32 prio)
{
    FILE *f = fileInfo->cb.addr;
    BOOL success;

    printf("DVDReadAsyncPrio: length %li, offset %li\n", length, offset);
    fseek(f, offset, SEEK_SET);
    success = (fread(addr, length, 1, f) == 1) || feof(f);
    if (!success)
        puts("read failed");
    callback(success ? 0 : -1, fileInfo);
    return TRUE;
}

BOOL DVDOpenDir(char *dirName, DVDDir *dir)
{
    puts("DVDOpenDir is a stub");
    return FALSE;
}

BOOL DVDCloseDir(DVDDir *dir)
{
    puts("DVDCloseDir is a stub");
    return FALSE;
}

BOOL DVDReadDir(DVDDir *dir, DVDDirEntry *dirent)
{
    puts("DVDReadDir is a stub");
    return FALSE;
}

s32 DVDGetDriveStatus(void)
{
    // puts("DVDGetDriveStatus is a stub");
    return 0;
}

void HuDvdErrorWatch(void)
{
    
}
