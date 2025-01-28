#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"

static inline int __init_uart_console(void) {
    int err = 0;
    static int initialized = 0;

    if (initialized == 0) {
        err = InitializeUART(57600);
        if (err == 0)
            initialized = 1;
    }

    return (err);
}

int __write_console(__file_handle handle, unsigned char* buffer, size_t* count, __idle_proc idle_proc) {
    if (__init_uart_console() != 0) {
        return 1;
    }

    if (WriteUARTN(buffer, *count) != 0) {
        *count = 0;
        return 1;
    }

    __TRK_write_console(handle, buffer, count, idle_proc);
    return 0;
}

int __close_console() {
    return 0;
}
