#ifndef _STRING_H_
#define _STRING_H_

#include "stddef.h"

#ifdef __MWERKS__
__declspec(section ".init") void* memcpy(void* dest, const void* src, size_t n);
__declspec(section ".init") void __fill_mem(void* dest, int val, size_t count);
__declspec(section ".init") void* memset(void* dest, int val, size_t count);
#else
void* memcpy(void* dest, const void* src, size_t n);
void __fill_mem(void* dest, int val, size_t count);
void* memset(void* dest, int val, size_t count);
#endif

int memcmp(const void* lhs, const void* rhs, size_t count);
void* __memrchr(const void* ptr, int ch, size_t count);
void* memchr(const void* ptr, int ch, size_t count);
void* memmove(void* dst, const void* src, size_t n);
char* strrchr(const char* str, int c);
char* strchr(const char* str, int c);
int strncmp(const char* str1, const char* str2, size_t n);
int strcmp(const char* str1, const char* str2);
char* strcat(char* dst, const char* src);
char* strncpy(char* dst, const char* src, size_t n);
char* strcpy(char* dst, const char* src);
size_t strlen(const char* str);

#endif
