#include "game/audio.h"
#include "game/esprite.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/wipe.h"
#include "rel_sqrt_consts.h"

#include "REL/present.h"

omObjData *lbl_1_bss_18;
omObjData *lbl_1_bss_14;
omObjData *lbl_1_bss_10;
omObjData *lbl_1_bss_C;
omObjData *lbl_1_bss_8;
Process *lbl_1_bss_4;
omObjData *lbl_1_bss_0;

void fn_1_254(void);
void fn_1_45C(void);
void fn_1_5EC(omObjData *object);

void ObjectSetup(void)
{
    lbl_1_bss_4 = omInitObjMan(150, 8192);
    omGameSysInit(lbl_1_bss_4);
    HuWinInit(1);
    lbl_1_bss_0 = omAddObjEx(lbl_1_bss_4, 1000, 0, 0, 0, fn_1_5EC);
    lbl_1_bss_0->unk10 = 0;
    lbl_1_bss_18 = fn_1_39A8();
}

void fn_1_144(s16 arg0, s32 arg1, s32 arg2)
{
    Process *var_r30;
    UnkPresentStruct6 *var_r31;

    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkPresentStruct6), MEMORY_DEFAULT_NUM);
    var_r31->unk_00 = arg0;
    var_r31->unk_08 = 1.0f / arg2;
    if (arg1) {
        var_r31->unk_08 = var_r31->unk_08;
        var_r31->unk_04 = 0.0f;
    } else {
        var_r31->unk_08 = -var_r31->unk_08;
        var_r31->unk_04 = 1.0f;
    }
    espDispOn(var_r31->unk_00);
    espTPLvlSet(var_r31->unk_00, var_r31->unk_04);
    var_r30 = HuPrcChildCreate(fn_1_254, 100, 5376, 0, HuPrcCurrentGet());
    var_r30->user_data = var_r31;
}

void fn_1_254(void)
{
    UnkPresentStruct6 *var_r31;

    var_r31 = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        var_r31->unk_04 = var_r31->unk_04 + var_r31->unk_08;
        if (var_r31->unk_04 > 1.0f) {
            var_r31->unk_04 = 1.0f;
            break;
        } else if (var_r31->unk_04 < 0.0f) {
            var_r31->unk_04 = 0.0f;
            break;
        } else {
            espTPLvlSet(var_r31->unk_00, var_r31->unk_04);
            HuPrcVSleep();
        }
    }
    espTPLvlSet(var_r31->unk_00, var_r31->unk_04);
    if (var_r31->unk_08 < 0.0f) {
        espDispOff(var_r31->unk_00);
    }
    HuMemDirectFree(var_r31);
    HuPrcEnd();
}

void fn_1_334(s16 arg0, s32 arg1, float arg8, s32 arg2)
{
    Process *var_r30;
    UnkPresentStruct6Weird *var_r31; // TODO correct type? why are only 12 bytes allocated?
    var_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, 12, MEMORY_DEFAULT_NUM);
    var_r31->unk_00 = arg0;
    var_r31->unk_0C = 1.0f / arg2;
    var_r31->unk_04 = arg8;

    if (arg1) {
        var_r31->unk_0C = var_r31->unk_0C;
        var_r31->unk_08 = 0.0f;
    } else {
        var_r31->unk_0C = -var_r31->unk_0C;
        var_r31->unk_08 = 1.0f;
    }
    Hu3DModelTPLvlSet(var_r31->unk_00, var_r31->unk_08 * var_r31->unk_04);
    Hu3DModelAttrReset(var_r31->unk_00, 1);
    var_r30 = HuPrcChildCreate(fn_1_45C, 100, 5376, 0, HuPrcCurrentGet());
    var_r30->user_data = var_r31;
}

void fn_1_45C(void)
{
    UnkPresentStruct6Weird *var_r31; // TODO correct type? how is 0C possible?

    var_r31 = HuPrcCurrentGet()->user_data;
    while (TRUE) {
        var_r31->unk_08 = var_r31->unk_08 + var_r31->unk_0C;
        if (var_r31->unk_08 > 1.0f) {
            var_r31->unk_08 = 1.0f;
            break;
        } else if (var_r31->unk_08 < 0.0f) {
            var_r31->unk_08 = 0.0f;
            break;
        } else {
            Hu3DModelTPLvlSet(var_r31->unk_00, var_r31->unk_08 * var_r31->unk_04);
            HuPrcVSleep();
        }
    }
    Hu3DModelTPLvlSet(var_r31->unk_00, var_r31->unk_08 * var_r31->unk_04);
    if (var_r31->unk_0C < 0.0f) {
        Hu3DModelAttrSet(var_r31->unk_00, 1);
    }
    HuMemDirectFree(var_r31);
    HuPrcEnd();
}

u32 fn_1_550(u16 arg0)
{
    u32 var_r31;

    var_r31 = HuPadBtnDown[0] & arg0;
    return var_r31 != 0;
}

u32 fn_1_584(u16 arg0)
{
    u32 var_r31;

    var_r31 = HuPadDStkRep[0] & arg0;
    return var_r31 != 0;
}

u32 fn_1_5B8(u16 arg0)
{
    u32 var_r31;

    var_r31 = HuPadDStk[0] & arg0;
    return var_r31 != 0;
}

void fn_1_5EC(omObjData *object)
{
    switch (object->unk10) {
    case 0:
        object->unk10 = 1;
    case 1:
        if (!omSysExitReq) {
            break;
        }
        object->unk10 = 2;
    case 2:
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        HuAudFadeOut(1000);
        object->unk10 = 3;
        break;
    case 3:
        if (!WipeStatGet()) {
            fn_1_3B18(lbl_1_bss_18);
            omOvlReturnEx(1, 1);
        }
        break;
    default:
        break;
    }
}
