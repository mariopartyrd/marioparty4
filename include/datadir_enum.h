#ifndef DATADIR_ENUM
#define DATADIR_ENUM

#define DATADIR(name, path) DATADIR_ID_##name,

enum {
    #include "datadir_table.h"
    DATADIR_ID_MAX
};

#undef DATADIR

#define DATADIR(name, path) DATADIR_##name = (DATADIR_ID_##name) << 16,

enum {
    #include "datadir_table.h"
};

#undef DATADIR

// TODO change to DATANUM
#define DATA_MAKE_NUM(dir, file) ((dir)+(file))

#define FILENUM(dataNum) ((dataNum) & 0xFFFF)
#define DIRNUM(dataNum) ((dataNum) & 0xFFFF0000)

#endif
