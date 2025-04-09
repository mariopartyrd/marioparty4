#ifndef _CTYPE_H
#define _CTYPE_H

#include "dolphin/types.h"

extern unsigned char __ctype_map[256];
extern unsigned char __lower_map[256];
extern unsigned char __upper_map[256];

#define __control_char 0x01
#define __motion_char 0x02
#define __space_char 0x04
#define __punctuation 0x08
#define __digit 0x10
#define __hex_digit 0x20
#define __lower_case 0x40
#define __upper_case 0x80

#define __letter (__lower_case | __upper_case)
#define __alphanumeric (__letter | __digit)
#define __graphic (__alphanumeric | __punctuation)
#define __printable (__graphic | __space_char)
#define __whitespace (__motion_char | __space_char)
#define __control (__motion_char | __control_char)

#ifdef __MWERKS__
#define DECL_WEAK __declspec(weak)
#else
#define DECL_WEAK __attribute__((weak))
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    DECL_WEAK int isalpha(int __c);
    DECL_WEAK int isdigit(int __c);
    DECL_WEAK int isspace(int __c);
    DECL_WEAK int isupper(int __c);
    DECL_WEAK int isxdigit(int __c);

    DECL_WEAK int tolower(int __c);
    DECL_WEAK int toupper(int __c);

    // added underscore to avoid naming conflicts
    inline int _isalpha(int c) { return (int)(__ctype_map[(u8)c] & __letter); }
    inline int _isdigit(int c) { return (int)(__ctype_map[(u8)c] & __digit); }
    inline int _isspace(int c) { return (int)(__ctype_map[(u8)c] & __whitespace); }
    inline int _isupper(int c) { return (int)(__ctype_map[(u8)c] & __upper_case); }
    inline int _isxdigit(int c) { return (int)(__ctype_map[(u8)c] & __hex_digit); }
    inline int _tolower(int c) { return (c == -1 ? -1 : (int)__lower_map[(u8)c]); }
    inline int _toupper(int c) { return (c == -1 ? -1 : (int)__upper_map[(u8)c]); }

#ifdef __cplusplus
}
#endif
#endif
