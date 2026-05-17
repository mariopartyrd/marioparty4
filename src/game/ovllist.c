#include "game/dvd.h"
#include "game/object.h"

#define DLL(name) { "dll/" #name ".rel", 0 },

FileListEntry _ovltbl[] = {
    #include "ovl_table.h"
    { NULL, -1 }
};

#undef DLL
