#include "game/object.h"
#include "math.h"

void fn_1_68(omObjData *object);

void ObjectSetup(void)
{
    Process *process = omInitObjMan(0xA, 0x2000);
    omObjData *object = omAddObjEx(process, 0, 0, 0, -1, fn_1_68);
    u32 *work = object->work;
}

void fn_1_68(omObjData *object)
{
    s8 *work = (s8 *)object->work;
    if (*work != 0) {
        (void)work;
        return;
    }
}

#include "src/REL/executor.c"
