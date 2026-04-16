#include "ext_math.h"
#include "game/armem.h"
#include "game/audio.h"
#include "game/disp.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/wipe.h"

#include "REL/mpexDll.h"

#ifndef __MWERKS__
float fn_1_1B52C(float arg8, float arg9, float argA, float argB);
float fn_1_1B554(float, float, float);
float fn_1_1B574(float arg0, float arg1, float arg2, float arg3);
float fn_1_1B64C(float arg0, float arg1, float arg2, float arg3);
#endif

void fn_1_230();
void fn_1_A70(MpexDllUnkStruct *arg0);

MpexDllUnkStruct lbl_1_bss_64;
s32 lbl_1_bss_4[0x18];
Process *lbl_1_bss_0;

void fn_1_A0(void)
{
    if (HuPadBtnDown[0] & PAD_BUTTON_Y) {
        OSReport("\n###################################################################### HEAP\n\n");
        HuMemHeapDump(HuMemHeapPtrGet(HEAP_SYSTEM), -1);
        OSReport("\n###################################################################### SOUND\n\n");
        HuMemHeapDump(HuMemHeapPtrGet(HEAP_MUSIC), -1);
        OSReport("\n###################################################################### MODEL\n\n");
        HuMemHeapDump(HuMemHeapPtrGet(HEAP_DATA), -1);
        OSReport("\n###################################################################### DVD\n\n");
        HuMemHeapDump(HuMemHeapPtrGet(HEAP_DVD), -1);
        OSReport("\n###################################################################### SPACE\n\n");
        HuMemHeapDump(HuMemHeapPtrGet(HEAP_MISC), -1);
        OSReport("\n###################################################################### ARAM\n\n");
        HuAMemDump();
    }
}

void fn_1_188(omObjData *object)
{
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1, 1);
    }
}

void fn_1_1C0(omObjData *object)
{
    if (omSysExitReq != 0) {
        HuAudFadeOut(0x3E8);
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
        object->func = fn_1_188;
    }
}

void ObjectSetup(void)
{
    mgPracticeEnableF = 0;
    lbl_1_bss_0 = omInitObjMan(0x3E, 0x2000);
    GWSystem.mg_next = 0xFFFF;
    fn_1_3044(lbl_1_bss_0);
}

void fn_1_298(void)
{
    s32 var_r31;

    var_r31 = -1;
    var_r31 = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0xFF, 0xFF, 0xFF);
    Hu3DGLightPosAimSet(var_r31, 0.0f, 1000.0f, 1000.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightInfinitytSet(var_r31);
}

void fn_1_374(void)
{
    Vec sp20 = { 0.0f, 3000.0f, 3000.0f };
    Vec sp14 = { 0.0f, 0.0f, 0.0f };
    Vec sp8 = { 0.0f, 1.0f, 0.0f };

    Hu3DShadowCreate(45.0f, 2000.0f, 25000.0f);
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);
    Hu3DShadowTPLvlSet(0.8f);
}

void fn_1_438(void)
{
    MpexDllUnkStruct *var_r31 = &lbl_1_bss_64;

    if (HuPadBtn[0] & PAD_BUTTON_B) {
        if (HuPadBtn[0] & 0x20) {
            var_r31->unk_08.z -= (HuPadStkY[0] / 10.0f);
        }
        else {
            var_r31->unk_08.x += HuPadStkX[0] / 10.0f;
            var_r31->unk_08.y += (HuPadStkY[0] / 10.0f);
        }
    }
    if (HuPadBtn[0] & PAD_BUTTON_Y) {
        var_r31->unk_20.x -= HuPadStkY[0] / 100.0f;
        var_r31->unk_20.y += (HuPadStkX[0] / 100.0f);
        if (var_r31->unk_20.x < 0.0f) {
            var_r31->unk_20.x += 360.0f;
        }
        if (var_r31->unk_20.x >= 360.0f) {
            var_r31->unk_20.x -= 360.0f;
        }
        if (var_r31->unk_20.y < 0.0f) {
            var_r31->unk_20.y += 360.0f;
        }
        if (var_r31->unk_20.y >= 360.0f) {
            var_r31->unk_20.y -= 360.0f;
        }
    }
    if (HuPadBtn[0] & PAD_BUTTON_X) {
        var_r31->unk_38 -= (HuPadStkY[0] / 10.0f);
    }
    print8(0x18, 0x28, 1.0f, ">>>>>>>>>> CAMERA DATA <<<<<<<<<<");
    print8(0x18, 0x32, 1.0f, "CENTER : %.2f, %.2f, %.2f", var_r31->unk_08.x, var_r31->unk_08.y, var_r31->unk_08.z);
    print8(0x18, 0x3C, 1.0f, "ROT    : %.2f, %.2f, %.2f", var_r31->unk_20.x, var_r31->unk_20.y, var_r31->unk_20.z);
    print8(0x18, 0x46, 1.0f, "ZOOM   : %.2f", var_r31->unk_38);
}

void fn_1_81C(omObjData *object)
{
    MpexDllUnkStruct *var_r31 = &lbl_1_bss_64;
    if (var_r31->unk_00 != NULL) {
        var_r31->unk_00();
    }
    Center.x = var_r31->unk_08.x;
    Center.y = var_r31->unk_08.y;
    Center.z = var_r31->unk_08.z;
    CRot.x = var_r31->unk_20.x;
    CRot.y = var_r31->unk_20.y;
    CRot.z = var_r31->unk_20.z;
    CZoom = var_r31->unk_38;
}

void fn_1_8D4(MpexDllUnkFunc arg0)
{
    lbl_1_bss_64.unk_00 = arg0;
    fn_1_A70(&lbl_1_bss_64);
}

void fn_1_910(MpexDllUnkFunc arg0)
{
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, HU_FB_WIDTHF, HU_FB_HEIGHTF, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 5000.0f, 1.2f);
    lbl_1_bss_64.unk_00 = arg0;
    lbl_1_bss_64.unk_04 = fn_1_438;
    omAddObjEx(lbl_1_bss_0, 0x7FDA, 0, 0, -1, omOutView);
    omAddObjEx(lbl_1_bss_0, 0x7FD9, 0, 0, -1, fn_1_81C);
}

void fn_1_A34(MpexDllUnkStruct *arg0)
{
    arg0->unk_08.x = arg0->unk_14.x;
    arg0->unk_08.y = arg0->unk_14.y;
    arg0->unk_08.z = arg0->unk_14.z;
    arg0->unk_20.x = arg0->unk_2C.x;
    arg0->unk_20.y = arg0->unk_2C.y;
    arg0->unk_20.z = arg0->unk_2C.z;
    arg0->unk_38 = arg0->unk_3C;
}

void fn_1_A70(MpexDllUnkStruct *arg0)
{
    arg0->unk_40 = 0;
    arg0->unk_14.x = arg0->unk_08.x;
    arg0->unk_14.y = arg0->unk_08.y;
    arg0->unk_14.z = arg0->unk_08.z;
    arg0->unk_2C.x = arg0->unk_20.x;
    arg0->unk_2C.y = arg0->unk_20.y;
    arg0->unk_2C.z = arg0->unk_20.z;
    arg0->unk_3C = arg0->unk_38;
}

void fn_1_AB4(MpexDllUnkStruct *arg0, MpexDllUnkStruct *arg1, float arg8)
{
    arg0->unk_08.x = fn_1_1B554(arg0->unk_08.x, arg1->unk_14.x, arg8);
    arg0->unk_08.y = fn_1_1B554(arg0->unk_08.y, arg1->unk_14.y, arg8);
    arg0->unk_08.z = fn_1_1B554(arg0->unk_08.z, arg1->unk_14.z, arg8);
    arg0->unk_20.x = fn_1_1B554(arg0->unk_20.x, arg1->unk_2C.x, arg8);
    arg0->unk_20.y = fn_1_1B554(arg0->unk_20.y, arg1->unk_2C.y, arg8);
    arg0->unk_20.z = fn_1_1B554(arg0->unk_20.z, arg1->unk_2C.z, arg8);
    arg0->unk_38 = fn_1_1B554(arg0->unk_38, arg1->unk_3C, arg8);
}

void fn_1_C84(MpexDllUnkStruct *arg0, float arg8, float argB)
{
    arg0->unk_08.x = fn_1_1B554(arg0->unk_08.x, arg0->unk_14.x, arg8);
    arg0->unk_08.y = fn_1_1B554(arg0->unk_08.y, arg0->unk_14.y, arg8);
    arg0->unk_08.z = fn_1_1B554(arg0->unk_08.z, arg0->unk_14.z, arg8);
    arg0->unk_20.x = fn_1_1B554(arg0->unk_20.x, arg0->unk_2C.x, arg8);
    arg0->unk_20.y = fn_1_1B554(arg0->unk_20.y, arg0->unk_2C.y, arg8);
    arg0->unk_20.z = fn_1_1B554(arg0->unk_20.z, arg0->unk_2C.z, arg8);
    arg0->unk_38 = fn_1_1B554(arg0->unk_38, arg0->unk_3C, arg8);
}

void fn_1_E48(MpexDllUnkStruct *arg0, MpexDllUnkStruct *arg1, float arg8, float arg9, float argC)
{
    arg1->unk_14.x = fn_1_1B52C(arg0->unk_14.x, arg1->unk_08.x, arg8, arg9);
    arg1->unk_14.y = fn_1_1B52C(arg0->unk_14.y, arg1->unk_08.y, arg8, arg9);
    arg1->unk_14.z = fn_1_1B52C(arg0->unk_14.z, arg1->unk_08.z, arg8, arg9);
    arg1->unk_2C.x = fn_1_1B52C(arg0->unk_2C.x, arg1->unk_20.x, arg8, arg9);
    arg1->unk_2C.y = fn_1_1B52C(arg0->unk_2C.y, arg1->unk_20.y, arg8, arg9);
    arg1->unk_2C.z = fn_1_1B52C(arg0->unk_2C.z, arg1->unk_20.z, arg8, arg9);
    arg1->unk_3C = fn_1_1B52C(arg0->unk_3C, arg1->unk_38, arg8, arg9);
}

void fn_1_1048(MpexDllUnkStruct *arg0, MpexDllUnkStruct *arg1, float arg8, float arg9, float argC)
{
    arg1->unk_14.x = fn_1_1B52C(arg0->unk_14.x, arg1->unk_08.x, arg8, arg9);
    arg1->unk_14.y = fn_1_1B52C(arg0->unk_14.y, arg1->unk_08.y, arg8, arg9);
    arg1->unk_14.z = fn_1_1B52C(arg0->unk_14.z, arg1->unk_08.z, arg8, arg9);
    arg1->unk_2C.x = fn_1_1B52C(arg0->unk_2C.x, arg1->unk_20.x, arg8, arg9);
    arg1->unk_2C.y = fn_1_1B52C(arg0->unk_2C.y, arg1->unk_20.y, arg8, arg9);
    arg1->unk_2C.z = fn_1_1B52C(arg0->unk_2C.z, arg1->unk_20.z, arg8, arg9);
    arg1->unk_3C = fn_1_1B52C(arg0->unk_3C, arg1->unk_38, arg8, arg9);
    arg0->unk_08.x = arg1->unk_14.x;
    arg0->unk_08.y = arg1->unk_14.y;
    arg0->unk_08.z = arg1->unk_14.z;
    arg0->unk_20.x = arg1->unk_2C.x;
    arg0->unk_20.y = arg1->unk_2C.y;
    arg0->unk_20.z = arg1->unk_2C.z;
    arg0->unk_38 = arg1->unk_3C;
}

void fn_1_1280(MpexDllUnkStruct *arg0, MpexDllUnkStruct *arg1, float arg8, float arg9, float argA, float argC)
{
    arg1->unk_14.x = fn_1_1B52C(arg0->unk_14.x, arg1->unk_08.x, arg8, arg9);
    arg1->unk_14.y = fn_1_1B52C(arg0->unk_14.y, arg1->unk_08.y, arg8, arg9);
    arg1->unk_14.z = fn_1_1B52C(arg0->unk_14.z, arg1->unk_08.z, arg8, arg9);
    arg1->unk_2C.x = fn_1_1B52C(arg0->unk_2C.x, arg1->unk_20.x, arg8, arg9);
    arg1->unk_2C.y = fn_1_1B52C(arg0->unk_2C.y, arg1->unk_20.y, arg8, arg9);
    arg1->unk_2C.z = fn_1_1B52C(arg0->unk_2C.z, arg1->unk_20.z, arg8, arg9);
    arg1->unk_3C = fn_1_1B52C(arg0->unk_3C, arg1->unk_38, arg8, arg9);
    arg0->unk_08.x = fn_1_1B554(arg0->unk_08.x, arg1->unk_14.x, argA);
    arg0->unk_08.y = fn_1_1B554(arg0->unk_08.y, arg1->unk_14.y, argA);
    arg0->unk_08.z = fn_1_1B554(arg0->unk_08.z, arg1->unk_14.z, argA);
    arg0->unk_20.x = fn_1_1B554(arg0->unk_20.x, arg1->unk_2C.x, argA);
    arg0->unk_20.y = fn_1_1B554(arg0->unk_20.y, arg1->unk_2C.y, argA);
    arg0->unk_20.z = fn_1_1B554(arg0->unk_20.z, arg1->unk_2C.z, argA);
    arg0->unk_38 = fn_1_1B554(arg0->unk_38, arg1->unk_3C, argA);
}

void fn_1_161C(MpexDllUnkStruct *arg0, MpexDllUnkStruct *arg1, float arg8, float arg9, float argC)
{
    arg1->unk_14.x = fn_1_1B64C(arg0->unk_14.x, arg1->unk_08.x, arg8, arg9);
    arg1->unk_14.y = fn_1_1B64C(arg0->unk_14.y, arg1->unk_08.y, arg8, arg9);
    arg1->unk_14.z = fn_1_1B64C(arg0->unk_14.z, arg1->unk_08.z, arg8, arg9);
    arg1->unk_2C.x = fn_1_1B64C(arg0->unk_2C.x, arg1->unk_20.x, arg8, arg9);
    arg1->unk_2C.y = fn_1_1B64C(arg0->unk_2C.y, arg1->unk_20.y, arg8, arg9);
    arg1->unk_2C.z = fn_1_1B64C(arg0->unk_2C.z, arg1->unk_20.z, arg8, arg9);
    arg1->unk_3C = fn_1_1B64C(arg0->unk_3C, arg1->unk_38, arg8, arg9);
}

void fn_1_181C(MpexDllUnkStruct *arg0, MpexDllUnkStruct *arg1, float arg8, float arg9, float argC)
{
    arg1->unk_14.x = fn_1_1B64C(arg0->unk_14.x, arg1->unk_08.x, arg8, arg9);
    arg1->unk_14.y = fn_1_1B64C(arg0->unk_14.y, arg1->unk_08.y, arg8, arg9);
    arg1->unk_14.z = fn_1_1B64C(arg0->unk_14.z, arg1->unk_08.z, arg8, arg9);
    arg1->unk_2C.x = fn_1_1B64C(arg0->unk_2C.x, arg1->unk_20.x, arg8, arg9);
    arg1->unk_2C.y = fn_1_1B64C(arg0->unk_2C.y, arg1->unk_20.y, arg8, arg9);
    arg1->unk_2C.z = fn_1_1B64C(arg0->unk_2C.z, arg1->unk_20.z, arg8, arg9);
    arg1->unk_3C = fn_1_1B64C(arg0->unk_3C, arg1->unk_38, arg8, arg9);
    arg0->unk_08.x = arg1->unk_14.x;
    arg0->unk_08.y = arg1->unk_14.y;
    arg0->unk_08.z = arg1->unk_14.z;
    arg0->unk_20.x = arg1->unk_2C.x;
    arg0->unk_20.y = arg1->unk_2C.y;
    arg0->unk_20.z = arg1->unk_2C.z;
    arg0->unk_38 = arg1->unk_3C;
}

void fn_1_1A54(MpexDllUnkStruct *arg0, MpexDllUnkStruct *arg1, float arg8, float arg9, float argA, float argC)
{
    arg1->unk_14.x = fn_1_1B64C(arg0->unk_14.x, arg1->unk_08.x, arg8, arg9);
    arg1->unk_14.y = fn_1_1B64C(arg0->unk_14.y, arg1->unk_08.y, arg8, arg9);
    arg1->unk_14.z = fn_1_1B64C(arg0->unk_14.z, arg1->unk_08.z, arg8, arg9);
    arg1->unk_2C.x = fn_1_1B64C(arg0->unk_2C.x, arg1->unk_20.x, arg8, arg9);
    arg1->unk_2C.y = fn_1_1B64C(arg0->unk_2C.y, arg1->unk_20.y, arg8, arg9);
    arg1->unk_2C.z = fn_1_1B64C(arg0->unk_2C.z, arg1->unk_20.z, arg8, arg9);
    arg1->unk_3C = fn_1_1B64C(arg0->unk_3C, arg1->unk_38, arg8, arg9);
    arg0->unk_08.x = fn_1_1B554(arg0->unk_08.x, arg1->unk_14.x, argA);
    arg0->unk_08.y = fn_1_1B554(arg0->unk_08.y, arg1->unk_14.y, argA);
    arg0->unk_08.z = fn_1_1B554(arg0->unk_08.z, arg1->unk_14.z, argA);
    arg0->unk_20.x = fn_1_1B554(arg0->unk_20.x, arg1->unk_2C.x, argA);
    arg0->unk_20.y = fn_1_1B554(arg0->unk_20.y, arg1->unk_2C.y, argA);
    arg0->unk_20.z = fn_1_1B554(arg0->unk_20.z, arg1->unk_2C.z, argA);
    arg0->unk_38 = fn_1_1B554(arg0->unk_38, arg1->unk_3C, argA);
}

void fn_1_1DF0(MpexDllUnkStruct *arg0, MpexDllUnkStruct *arg1, float arg8, float arg9, float argC)
{
    arg1->unk_14.x = fn_1_1B574(arg0->unk_14.x, arg1->unk_08.x, arg8, arg9);
    arg1->unk_14.y = fn_1_1B574(arg0->unk_14.y, arg1->unk_08.y, arg8, arg9);
    arg1->unk_14.z = fn_1_1B574(arg0->unk_14.z, arg1->unk_08.z, arg8, arg9);
    arg1->unk_2C.x = fn_1_1B574(arg0->unk_2C.x, arg1->unk_20.x, arg8, arg9);
    arg1->unk_2C.y = fn_1_1B574(arg0->unk_2C.y, arg1->unk_20.y, arg8, arg9);
    arg1->unk_2C.z = fn_1_1B574(arg0->unk_2C.z, arg1->unk_20.z, arg8, arg9);
    arg1->unk_3C = fn_1_1B574(arg0->unk_3C, arg1->unk_38, arg8, arg9);
}

void fn_1_1FF0(MpexDllUnkStruct *arg0, MpexDllUnkStruct *arg1, float arg8, float arg9, float argC)
{
    arg1->unk_14.x = fn_1_1B574(arg0->unk_14.x, arg1->unk_08.x, arg8, arg9);
    arg1->unk_14.y = fn_1_1B574(arg0->unk_14.y, arg1->unk_08.y, arg8, arg9);
    arg1->unk_14.z = fn_1_1B574(arg0->unk_14.z, arg1->unk_08.z, arg8, arg9);
    arg1->unk_2C.x = fn_1_1B574(arg0->unk_2C.x, arg1->unk_20.x, arg8, arg9);
    arg1->unk_2C.y = fn_1_1B574(arg0->unk_2C.y, arg1->unk_20.y, arg8, arg9);
    arg1->unk_2C.z = fn_1_1B574(arg0->unk_2C.z, arg1->unk_20.z, arg8, arg9);
    arg1->unk_3C = fn_1_1B574(arg0->unk_3C, arg1->unk_38, arg8, arg9);
    arg0->unk_08.x = arg1->unk_14.x;
    arg0->unk_08.y = arg1->unk_14.y;
    arg0->unk_08.z = arg1->unk_14.z;
    arg0->unk_20.x = arg1->unk_2C.x;
    arg0->unk_20.y = arg1->unk_2C.y;
    arg0->unk_20.z = arg1->unk_2C.z;
    arg0->unk_38 = arg1->unk_3C;
}

void fn_1_2228(MpexDllUnkStruct *arg0, MpexDllUnkStruct *arg1, float arg8, float arg9, float argA, float argC)
{
    arg1->unk_14.x = fn_1_1B574(arg0->unk_14.x, arg1->unk_08.x, arg8, arg9);
    arg1->unk_14.y = fn_1_1B574(arg0->unk_14.y, arg1->unk_08.y, arg8, arg9);
    arg1->unk_14.z = fn_1_1B574(arg0->unk_14.z, arg1->unk_08.z, arg8, arg9);
    arg1->unk_2C.x = fn_1_1B574(arg0->unk_2C.x, arg1->unk_20.x, arg8, arg9);
    arg1->unk_2C.y = fn_1_1B574(arg0->unk_2C.y, arg1->unk_20.y, arg8, arg9);
    arg1->unk_2C.z = fn_1_1B574(arg0->unk_2C.z, arg1->unk_20.z, arg8, arg9);
    arg1->unk_3C = fn_1_1B574(arg0->unk_3C, arg1->unk_38, arg8, arg9);
    arg0->unk_08.x = fn_1_1B554(arg0->unk_08.x, arg1->unk_14.x, argA);
    arg0->unk_08.y = fn_1_1B554(arg0->unk_08.y, arg1->unk_14.y, argA);
    arg0->unk_08.z = fn_1_1B554(arg0->unk_08.z, arg1->unk_14.z, argA);
    arg0->unk_20.x = fn_1_1B554(arg0->unk_20.x, arg1->unk_2C.x, argA);
    arg0->unk_20.y = fn_1_1B554(arg0->unk_20.y, arg1->unk_2C.y, argA);
    arg0->unk_20.z = fn_1_1B554(arg0->unk_20.z, arg1->unk_2C.z, argA);
    arg0->unk_38 = fn_1_1B554(arg0->unk_38, arg1->unk_3C, argA);
}

void fn_1_25C4(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    switch (arg4) {
        case 0:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0);
            break;
        case 1:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0x40000001);
            break;
        case 2:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0x40000002);
            break;
    }
}

void fn_1_273C(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    if (arg0->work[3] != arg0->motion[arg2]) {
        arg0->work[3] = arg0->motion[arg2];
        switch (arg4) {
            case 0:
                Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0);
                break;
            case 1:
                Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0x40000001);
                break;
            case 2:
                Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0x40000002);
                break;
        }
    }
}

void fn_1_28DC(void) { }

void fn_1_28E0(omObjData *arg0, s32 arg1, Vec arg2, float arg8, float arg9, float argA, s32 arg3, s32 arg4)
{
    Vec sp4C;
    Vec sp40;
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;

    s32 var_r29 = 0;
    s32 var_r28 = 0;
    s32 var_r26;

    sp40.x = Hu3DData[arg0->model[arg1]].pos.x;
    sp40.y = Hu3DData[arg0->model[arg1]].pos.y;
    sp40.z = Hu3DData[arg0->model[arg1]].pos.z;

    sp34.x = arg2.x;
    sp34.y = arg2.y;
    sp34.z = arg2.z;

    sp1C.x = Hu3DData[arg0->model[arg1]].rot.x;
    sp1C.y = Hu3DData[arg0->model[arg1]].rot.y;
    sp1C.z = Hu3DData[arg0->model[arg1]].rot.z;

    sp10.x = 0.0f;
    sp10.y = arg8;
    sp10.z = 0.0f;

    if ((sp34.x - sp40.x) >= 0.0f) {
        var_r29 = 1;
    }
    else {
        var_r29 = 0;
    }
    if ((sp34.z - sp40.z) >= 0.0f) {
        var_r28 = 1;
    }
    else {
        var_r28 = 0;
    }
    while (arg3 != 0) {
        fn_1_1B7D0(1);
        sp28.y = -((atan2d(sp34.z - sp40.z, sp34.x - sp40.x)) - 90.0);
        if (sp28.y < 0.0f) {
            sp28.y += 360.0f;
        }
        else if (sp28.y >= 360.0f) {
            sp28.y -= 360.0f;
        }
        if (arg4 != 0) {
            if (sp28.y >= 180.0f) {
                if ((sp1C.y - sp28.y) >= 180.0f) {
                    sp1C.y -= 360.0f;
                }
                if ((sp1C.y - sp28.y) < -180.0f) {
                    sp1C.y += 360.0f;
                }
            }
            else {
                if ((sp1C.y - sp28.y) > 180.0f) {
                    sp1C.y -= 360.0f;
                }
                if ((sp1C.y - sp28.y) <= -180.0f) {
                    sp1C.y += 360.0f;
                }
            }
        }
        sp4C.x = (sp40.x += (arg9 * sind(sp28.y)));
        sp4C.z = (sp40.z += (arg9 * cosd(sp28.y)));
        if (var_r29 == 1) {
            if (sp40.x >= sp34.x) {
                sp4C.x = sp40.x = sp34.x;
                var_r29 = 2;
            }
        }
        else if ((var_r29 == 0) && (sp40.x <= sp34.x)) {
            sp4C.x = sp40.x = sp34.x;
            var_r29 = 2;
        }
        if (var_r28 == 1) {
            if (sp40.z >= sp34.z) {
                sp4C.z = sp40.z = sp34.z;
                var_r28 = 2;
            }
        }
        else if ((var_r28 == 0) && (sp40.z <= sp34.z)) {
            sp4C.z = sp40.z = sp34.z;
            var_r28 = 2;
        }
        if (arg4 != 0) {
            sp1C.y = fn_1_1B554(sp1C.y, sp28.y, argA);
        }
        Hu3DModelPosSet(arg0->model[arg1], sp4C.x, sp40.y, sp4C.z);
        Hu3DModelRotSet(arg0->model[arg1], sp1C.x, sp1C.y, sp1C.z);

        if (var_r29 == 2 && var_r28 == 2) {
            break;
        }
    };

    sp1C.y = Hu3DData[arg0->model[arg1]].rot.y;
    if (arg4 != 0) {
        for (var_r26 = 0; var_r26 <= argA; var_r26++) {
            fn_1_1B7D0(1);
            if (sp10.y >= 180.0f) {
                if ((sp1C.y - sp10.y) >= 180.0f) {
                    sp1C.y -= 360.0f;
                }
                if ((sp1C.y - sp10.y) < -180.0f) {
                    sp1C.y += 360.0f;
                }
            }
            else {
                if ((sp1C.y - sp10.y) > 180.0f) {
                    sp1C.y -= 360.0f;
                }
                if ((sp1C.y - sp10.y) <= -180.0f) {
                    sp1C.y += 360.0f;
                }
            }
            sp10.z = fn_1_1B52C(sp1C.y, sp10.y, var_r26, argA);
            Hu3DModelRotSet(arg0->model[arg1], sp1C.x, sp10.z, sp1C.z);
        }
    }
}
