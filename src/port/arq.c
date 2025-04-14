#include <stdio.h>
#include <string.h>
#include <dolphin.h>

extern u8 ARAM[16 * 1024 * 1024];

void ARQPostRequest(ARQRequest *task, u32 owner, u32 type, u32 priority,
    uintptr_t source, uintptr_t dest, u32 length, ARQCallback callback)
{
    printf("ARQPostRequest: 0x%X, 0x%X, 0x%X\n",
        (unsigned int)source, (unsigned int)dest, (unsigned int)length);
    switch (type)
    {
    case ARQ_TYPE_MRAM_TO_ARAM:
        memcpy(ARAM + dest, (void *)source, length);
        callback((uintptr_t)task);
        break;
    case ARQ_TYPE_ARAM_TO_MRAM:
        memcpy((void *)dest, ARAM + source, length);
        callback((uintptr_t)task);
        break;
    }
}
