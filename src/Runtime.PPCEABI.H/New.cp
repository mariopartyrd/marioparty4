#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/alloc.h"
#include "PowerPC_EABI_Support/Runtime/New.h"

void operator delete(void* arg0) throw() {
    if (arg0 != 0) {
        free(arg0);
    }
}
