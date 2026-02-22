#include "REL/executor.h"
#include "dolphin/os.h"
#include "math.h"

extern s32 rand8(void);

void ObjectSetup(void) {
    OSReport("minigame dll setup\n");
}

unsigned char fn_1_CC(void) {
    return rand8();
}
