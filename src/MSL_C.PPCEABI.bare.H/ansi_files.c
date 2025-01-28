#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/file_io.h"

static unsigned char stdin_buff[0x100];
static unsigned char stdout_buff[0x100];
static unsigned char stderr_buff[0x100];

FILE __files[4] = {
    {0,
     {0, 1, 1, 2, 0},
     {0, 0, 0, 0},
     0,
     0,
     0,
     {0, 0},
     {0, 0},
     0,
     stdin_buff,
     sizeof(stdin_buff),
     stdin_buff,
     0,
     0,
     0,
     0,
     NULL,
     &__read_console,
     &__write_console,
     &__close_console,
     0,
     &__files[1]},
    {1,
     {0, 2, 1, 2, 0},
     {0, 0, 0, 0},
     0,
     0,
     0,
     {0, 0},
     {0, 0},
     0,
     stdout_buff,
     sizeof(stdout_buff),
     stdout_buff,
     0,
     0,
     0,
     0,
     NULL,
     &__read_console,
     &__write_console,
     &__close_console,
     0,
     &__files[2]},
    {2,
     {0, 2, 0, 2, 0},
     {0, 0, 0, 0},
     0,
     0,
     0,
     {0, 0},
     {0, 0},
     0,
     stderr_buff,
     sizeof(stderr_buff),
     stderr_buff,
     0,
     0,
     0,
     0,
     NULL,
     &__read_console,
     &__write_console,
     &__close_console,
     0,
     &__files[3]},
};

void __close_all() {
    FILE* p = &__files[0];
    FILE* plast;

    while (p != NULL) {
        if (p->file_mode.file_kind != __closed_file) {
            fclose(p);
        }

        plast = p;
        p = p->next_file_struct;
        if (plast->is_dynamically_allocated)
            free(plast);
        else {
            plast->file_mode.file_kind = __string_file;
            if ((p != NULL) && p->is_dynamically_allocated)
                plast->next_file_struct = NULL;
        }
    }
}

unsigned int __flush_all() {
  unsigned int retval = 0;
  FILE* __stream;

    __stream = &__files[0];
    while (__stream) {
        if ((__stream->file_mode.file_kind) && (fflush(__stream))) {
            retval = -1;
        }
        __stream = __stream->next_file_struct;
    };

    return retval;
}
