#ifndef _TYPES_H_
#define _TYPES_H_

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

//a bit of a hack to get the size of a member from a struct type
#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

//a bit of a hack to get the array count of a member from a struct type
#define ARRAY_COUNT_OF_MEMBER(type, member) \
    (sizeof(((type *)0)->member) / sizeof(((type *)0)->member[0]))

#include "dolphin/types.h"

#endif
