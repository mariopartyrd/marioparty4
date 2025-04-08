#ifndef _VERSION_H
#define _VERSION_H

#define VERSION_NO_ENG0 0
#define VERSION_NO_ENG1 1
#define VERSION_NO_PAL0 2
#define VERSION_NO_PAL2 3
#define VERSION_NO_JP 4

#define VERSION_ENG (VERSION == VERSION_NO_ENG0 || VERSION == VERSION_NO_ENG1)
#define VERSION_PAL (VERSION == VERSION_NO_PAL0 || VERSION == VERSION_NO_PAL2)
#define VERSION_JP (VERSION == VERSION_NO_JP)
#define VERSION_NTSC (!VERSION_PAL)

#define VERSION_REV0 (VERSION == VERSION_NO_ENG0 || VERSION == VERSION_NO_PAL0 || VERSION == VERSION_NO_JP)
#define VERSION_REV1 (!VERSION_REV0)

#if VERSION_PAL
#define REFRESH_RATE 50
#else
#define REFRESH_RATE 60
#endif

#if _WIN32
#ifdef TARGET_DOL
#define SHARED_SYM __declspec(dllexport)
#else
#define SHARED_SYM __declspec(dllimport)
#endif

#else
    #define SHARED_SYM
#endif

#endif
