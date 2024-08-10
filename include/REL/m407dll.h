#include "game/object.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

typedef void (*ObjFuncs)(omObjData*);
