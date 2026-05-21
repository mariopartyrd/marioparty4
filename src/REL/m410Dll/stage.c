#include "game/hu3d.h"
#include "game/object.h"

void fn_1_31FC(omObjData *object);
void fn_1_3350(omObjData *object);

void fn_1_31A4(Process *process)
{
    omObjData *var_r31;

    var_r31 = omAddObjEx(process, 30, 6, 0, -1, fn_1_31FC);
    var_r31->work[0] = 0;
}

void fn_1_31F8(void) { }

void fn_1_31FC(omObjData *object)
{
    omSetTra(object, 0.0f, 0.0f, 0.0f);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M410, 13));
    Hu3DModelShadowMapSet(object->model[0]);
    object->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M410, 14));
    object->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M410, 15));
    object->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M410, 16));
    Hu3DModelAttrSet(object->model[3], HU3D_MOTATTR_LOOP);
    object->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M410, 17));
    Hu3DModelAttrSet(object->model[4], HU3D_MOTATTR_LOOP);
    object->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M410, 18));
    object->func = fn_1_3350;
}

void fn_1_3350(omObjData *object)
{
    Hu3DModelPosSet(object->model[5], Center.x, Center.y, Center.z);
}
