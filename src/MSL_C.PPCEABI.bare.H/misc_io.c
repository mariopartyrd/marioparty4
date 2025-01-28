#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/abort_exit.h"

void __stdio_atexit(void) {
    __stdio_exit = __close_all;
}
