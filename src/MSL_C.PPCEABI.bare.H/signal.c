#include <stddef.h>

void* signal_funcs[6];

// regalloc: https://decomp.me/scratch/ufAYK
int raise(int arg0) {
    void (*temp_r31)(int);
    void** temp_r3;

    if (arg0 < 1 || arg0 > 6) {
        return -1;
    }
    temp_r3 = &signal_funcs[arg0];
    temp_r31 = *(--temp_r3);
    if ((unsigned long) temp_r31 != 1) {
        *temp_r3 = NULL;
    }
    if ((unsigned long) temp_r31 == 1 || (temp_r31 == NULL && arg0 == 1)) {
        return 0;
    }
    if (temp_r31 == NULL) {
        exit(0);
    }
    temp_r31(arg0);
    return 0;
}
