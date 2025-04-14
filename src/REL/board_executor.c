#include "REL/board_executor.h"
#include "math.h"

#ifdef TARGET_PC
void ObjectSetup(void) {
    BoardObjectSetup(BoardCreate, BoardDestroy);
}
#else
static void ObjectSetup(void) {
    BoardObjectSetup(BoardCreate, BoardDestroy);
}
#endif

#ifdef __MWERKS__
s32 _prolog(void) {
    const VoidFunc* ctors = _ctors;
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
	ObjectSetup();
    return 0;
}

void _epilog(void) {
    const VoidFunc* dtors = _dtors;
    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}
#endif
