#include "game/dvd.h"
#include "game/object.h"

#ifdef TARGET_PC

#ifdef _WIN32
#define OVL_DEFINE(name, path) { path ".dll", 0 },
#else
#define OVL_DEFINE(name, path) { path ".so", 0 },
#endif

#else

#define OVL_DEFINE(name, path) { "dll/" path ".rel", 0 },
#endif

FileListEntry _ovltbl[OVL_COUNT+1] = {
    #include "ovl_table.h"
    { NULL, -1 }
};

#undef OVL_DEFINE
