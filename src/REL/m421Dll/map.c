#include "game/hu3d.h"

#include "REL/m421Dll.h"

void fn_1_B1C0(omObjData *object);
void fn_1_B398(omObjData *object);

omObjData *lbl_1_bss_58;

void fn_1_B15C(Process *work)
{
    omObjData *object = omAddObjEx(work, 0x1E, 6, 0, -1, fn_1_B1C0);
    lbl_1_bss_58 = object;
    object->work[0] = 0;
}

void fn_1_B1BC(void) { }

void fn_1_B1C0(omObjData *var_r31)
{
    omSetTra(var_r31, 0.0f, 0.0f, 0.0f);
    var_r31->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M421, 0x02));
    Hu3DModelLayerSet(var_r31->model[0], 1);
    Hu3DModelShadowMapSet(var_r31->model[0]);

    var_r31->model[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M421, 0x00));
    Hu3DModelLayerSet(var_r31->model[1], 1);

    var_r31->model[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M421, 0x01));
    Hu3DModelLayerSet(var_r31->model[2], 5);

    var_r31->model[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M421, 0x05));
    Hu3DModelLayerSet(var_r31->model[3], 1);
    Hu3DModelAttrSet(var_r31->model[3], HU3D_MOTATTR_LOOP);

    var_r31->model[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M421, 0x03));
    Hu3DModelLayerSet(var_r31->model[4], 5);
    Hu3DModelAttrSet(var_r31->model[4], HU3D_MOTATTR_LOOP);

    var_r31->model[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M421, 0x04));
    Hu3DModelLayerSet(var_r31->model[5], 5);
    Hu3DMotionTimeSet(var_r31->model[5], 0.0f);
    var_r31->work[0] = 0;
    var_r31->work[1] = 0;
    var_r31->func = fn_1_B398;
}

void fn_1_B398(omObjData *object) { }

void fn_1_B39C(void)
{
    Hu3DMotionTimeSet(lbl_1_bss_58->model[5], 0.0f);
}
