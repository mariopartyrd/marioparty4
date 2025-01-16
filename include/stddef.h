#ifndef _STDDEF_H_
#define _STDDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define offsetof(type, member) ((size_t) & (((type*)0)->member))

/* These break 1.2.5 */
//typedef __typeof__(sizeof(0)) size_t;
//typedef __typeof__((char*)0 - (char*)0) ptrdiff_t;
#ifdef __INTELLISENSE__
typedef unsigned int size_t;
typedef int ptrdiff_t;
#else
typedef unsigned long size_t;
typedef long ptrdiff_t;
#endif
#ifndef NULL
#define NULL 0L
#endif

#ifdef __cplusplus
}
#endif

#endif
