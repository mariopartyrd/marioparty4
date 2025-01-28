#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_files.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/errno.h"

inline fpos_t _ftell(FILE* file) {
    int charsInUndoBuffer = 0;
    fpos_t position;
    unsigned char tmp_kind = file->file_mode.file_kind;

    if (!(tmp_kind == __disk_file || tmp_kind == __console_file) || file->file_state.error) {
        errno = EFPOS;
        return -1;
    }

    if (file->file_state.io_state == __neutral)
        return (file->position);

    position = file->buffer_position + (file->buffer_ptr - file->buffer);

    if (file->file_state.io_state >= __rereading) {
        charsInUndoBuffer = file->file_state.io_state - __rereading + 1;
        position -= charsInUndoBuffer;
    }

    return (position);
}

long ftell(FILE* file) {
    long retval;

    retval = (long)_ftell(file);

    return retval;
}

int _fseek(FILE* file, fpos_t offset, int file_mode) {
    fpos_t position;
    __pos_proc pos_proc;
    unsigned char tmp_kind = file->file_mode.file_kind;

    if (!(tmp_kind == __disk_file) || file->file_state.error) {
        errno = EFPOS;
        return (-1);
    }

    if (file->file_state.io_state == __writing) {
        if (__flush_buffer(file, NULL) != __no_io_error) {
            set_error(file);
            errno = EFPOS;
            return (-1);
        }
    }

    if (file_mode == SEEK_CUR) {
        file_mode = SEEK_SET;
        if ((position = _ftell(file)) < 0)
            position = 0;
        offset += position;
    }

    if ((file_mode != SEEK_END) && (file->file_mode.io_mode != __read_write) &&
        ((file->file_state.io_state == __reading) || (file->file_state.io_state == __rereading)))
    {
        if (offset >= file->position || offset < file->buffer_position) {
            file->file_state.io_state = __neutral;
        } else {
            file->buffer_ptr = file->buffer + (offset - file->buffer_position);
            file->buffer_length = file->position - offset;
            file->file_state.io_state = __reading;
        }
    } else {
        file->file_state.io_state = __neutral;
    }

    if (file->file_state.io_state == __neutral) {
        if ((pos_proc = file->position_fn) != NULL && pos_proc(file->handle, &offset, file_mode, file->idle_fn)) {
            set_error(file);
            errno = EFPOS;
            return -1;
        }

        file->file_state.eof = 0;
        file->position = offset;
        file->buffer_length = 0;
    }

    return 0;
}

int fseek(FILE * file, long offset, int file_mode)
{
    fpos_t real_offset = (fpos_t)offset;
    int retval;		

    retval = _fseek(file, real_offset, file_mode);

    return(retval);
}
