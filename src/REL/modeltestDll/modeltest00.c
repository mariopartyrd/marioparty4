#include "math.h"
#include "game/chrman.h"
#include "game/wipe.h"
#include "game/pad.h"

#include "REL/modeltestDll.h"

// -------------------------------------------------------------------------- //

omObjData * unk_bss_9FC;
omObjData * lbl_1_bss_9F8;
omObjData * lbl_1_bss_9F4;
s16 lbl_1_bss_9EC[4];
s16 lbl_1_bss_9AC[4][8];
Process * lbl_1_bss_9A8;
u16 lbl_1_data_358[4] = {1, 2, 4, 8};

// -------------------------------------------------------------------------- //

void fn_1_34B0()
{
    Process * temp_r30;
    s16 var_r31;
    
    OSReport("******* MODELTESTObjectSetup *********\n");

    temp_r30 = omInitObjMan(0x32, 0x2000);
    CRot.x = -22.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 60.0f;
    Center.z = 0.0f;
    CZoom = 400.0f;

    for (var_r31 = 0; var_r31 < 4; ++var_r31)
    {
        Hu3DCameraCreate(lbl_1_data_358[var_r31]);
        Hu3DCameraPerspectiveSet(lbl_1_data_358[var_r31], 45.0f, 20.0f, 20000.0f, 1.2f);
        Hu3DCameraViewportSet(lbl_1_data_358[var_r31], (var_r31 & 1) * 320, ((var_r31 & 2) != 0) ? 0xF0 : 0, 320.0f, 240.0f, 0.0f, 1.0f);
        Hu3DCameraScissorSet(lbl_1_data_358[var_r31], (var_r31 & 1) * 320, ((var_r31 & 2) != 0) ? 0xF0 : 0, 320, 240);
    }

    lbl_1_bss_9F4 = omAddObjEx(temp_r30, 0, 0x20U, 0x20U, -1, fn_1_37DC);
    lbl_1_bss_9F8 = omAddObjEx(temp_r30, 0x7FDA, 0U, 0U, -1, fn_1_439C);
    lbl_1_bss_9A8 = HuPrcCreate(fn_1_46F0, 0x64U, 0x2000U, 0);

    Hu3DBGColorSet(0x20U, 0x80U, 0x80U);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
}

// -------------------------------------------------------------------------- //

static inline void HuControlCamCenter(Point3d *sp18, Point3d *sp30) {
    s8 temp_r28;

    temp_r28 = HuPadSubStkX[0] & 0xF8;
    if (temp_r28 != 0) {
        Center.x += 0.05f * (sp30->x * temp_r28);
        Center.y += 0.05f * (sp30->y * temp_r28);
        Center.z += 0.05f * (sp30->z * temp_r28);
    }
    VECNormalize(sp18, sp30);
    temp_r28 = -(HuPadSubStkY[0] & 0xF8);
    if (temp_r28 != 0) {
        Center.x += 0.05f * (sp30->x * temp_r28);
        Center.y += 0.05f * (sp30->y * temp_r28);
        Center.z += 0.05f * (sp30->z * temp_r28);
    }
}

// -------------------------------------------------------------------------- //

void fn_1_37DC(omObjData *)
{
    Point3d sp3C;
    Point3d sp30;
    Point3d sp24;
    Point3d sp18;
    float temp_f31;
    
    if ((HuPadBtnDown[0] & PAD_BUTTON_START) != 0) {
        if (lbl_1_bss_9A8) {
            HuPrcKill(lbl_1_bss_9A8);
        }
        omOvlReturnEx(1, 1);
        return;
    }

    if ((HuPadBtn[0] & PAD_BUTTON_UP) != 0) {
        CRot.x += 2.0f;
    }
    if ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0) {
        CRot.x -= 2.0f;
    }
    if ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0) {
        CRot.y += 2.0f;
    }
    if ((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) {
        CRot.y -= 2.0f;
    }

    CZoom += HuPadTrigL[0] / 2;
    CZoom -= HuPadTrigR[0] / 2;

    sp3C.x = Center.x + (CZoom * (sin((M_PI * CRot.y) / 180.0) * cos((M_PI * CRot.x) / 180.0)));
    sp3C.y = (Center.y + (CZoom * -sin((M_PI * CRot.x) / 180.0)));
    sp3C.z = (Center.z + (CZoom * (cos((M_PI * CRot.y) / 180.0) * cos((M_PI * CRot.x) / 180.0))));
    sp30.x = Center.x - sp3C.x;
    sp30.y = Center.y - sp3C.y;
    sp30.z = Center.z - sp3C.z;
    sp24.x = (sin((M_PI * CRot.y) / 180.0) * sin((M_PI * CRot.x) / 180.0));
    sp24.y = cos((M_PI * CRot.x) / 180.0);
    sp24.z = (cos((M_PI * CRot.y) / 180.0) * sin((M_PI * CRot.x) / 180.0));
    temp_f31 = CRot.z;
    
    sp18.x = sp24.x * (sp30.x * sp30.x + (1.0f - sp30.x * sp30.x) * cos((M_PI * temp_f31) / 180.0))
            + sp24.y * (sp30.x * sp30.y * (1.0f - cos((M_PI * temp_f31) / 180.0)) - sp30.z * sin((M_PI * temp_f31) / 180.0))
            + sp24.z * (sp30.x * sp30.z * (1.0f - cos((M_PI * temp_f31) / 180.0)) + sp30.y * sin((M_PI * temp_f31) / 180.0));

    sp18.y = sp24.y * (sp30.y * sp30.y + (1.0f - sp30.y * sp30.y) * cos((M_PI * temp_f31) / 180.0))
            + sp24.x * (sp30.x * sp30.y * (1.0f - cos((M_PI * temp_f31) / 180.0)) + sp30.z * sin((M_PI * temp_f31) / 180.0))
            + sp24.z * (sp30.y * sp30.z * (1.0f - cos((M_PI * temp_f31) / 180.0)) - sp30.x * sin((M_PI * temp_f31) / 180.0));
        
    sp18.z = sp24.z * (sp30.z * sp30.z + (1.0f - sp30.z * sp30.z) * cos((M_PI * temp_f31) / 180.0))
            + (sp24.x * (sp30.x * sp30.z * (1.0 - cos((M_PI * temp_f31) / 180.0)) - sp30.y * sin((M_PI * temp_f31) / 180.0))
            + sp24.y * (sp30.y * sp30.z * (1.0 - cos((M_PI * temp_f31) / 180.0)) + sp30.x * sin((M_PI * temp_f31) / 180.0)));

    VECCrossProduct(&sp24, &sp30, &sp30);
    VECNormalize(&sp30, &sp30);

    HuControlCamCenter(&sp18, &sp30);
}

// -------------------------------------------------------------------------- //

void fn_1_439C(omObjData * )
{
    s16 var_r31;
    f32 temp_f30;
    f32 temp_f31;
    f32 sp10;
    Point3d sp2C;
    Point3d sp20;
    Point3d sp14;
    for (var_r31 = 0; var_r31 < 4; ++var_r31)
    {
        temp_f31 = CRot.x;
        temp_f30 = CRot.y + (var_r31 * 90);
        sp10 = CRot.z;
        sp2C.x = Center.x + (CZoom * (sin((M_PI * temp_f30) / 180.0) * (cos((M_PI * temp_f31) / 180.0))));
        sp2C.y = Center.y + (CZoom * -sin((M_PI * temp_f31) / 180.0));
        sp2C.z = Center.z + (CZoom * (cos((M_PI * temp_f30) / 180.0) * (cos((M_PI * temp_f31) / 180.0))));
        
        sp20.x = Center.x;
        sp20.y = Center.y;
        sp20.z = Center.z;

        sp14.x = sin((M_PI * temp_f30) / 180.0) * (sin((M_PI * temp_f31) / 180.0));
        sp14.y = cos((M_PI * temp_f31) / 180.0);
        sp14.z = cos((M_PI * temp_f30) / 180.0) * (sin((M_PI * temp_f31) / 180.0));

         Hu3DCameraPosSet(lbl_1_data_358[var_r31], sp2C.x, sp2C.y, sp2C.z, sp14.x, sp14.y, sp14.z, sp20.x, sp20.y, sp20.z);
    }
}

// -------------------------------------------------------------------------- //

const Point3d lbl_1_rodata_18C = {0.0f, 0.0f, 0.0f};
const Point3d lbl_1_rodata_198 = {0.0f, 1.0f, 0.0f};

// -------------------------------------------------------------------------- //

void fn_1_46F0(void)
{
    Point3d sp20;
    Point3d sp14;
    Point3d sp8;
    s16 var_r31;
    s16 var_r30;

    sp14 = lbl_1_rodata_18C;
    sp8 = lbl_1_rodata_198;

    Hu3DGLightCreate(0.0f, 500.0f, 1000.0f, 0.0f, -0.5f, -1.0f, 0xFFU, 0xFFU, 0xFFU);
    Hu3DShadowCreate(45.0f, 500.0f, 8000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowSizeSet(0xC0U);

    sp20.x = -500.0f;
    sp20.y = 1000.0f;
    sp20.z = 1000.0f;
    Hu3DShadowPosSet(&sp20, &sp8, &sp14);

    for (var_r31 = 0; var_r31 < 4; ++var_r31)
    {
        var_r30 = var_r31;
        lbl_1_bss_9EC[var_r31] = CharModelCreate(var_r30, 8);
        Hu3DModelShadowSet(lbl_1_bss_9EC[var_r31]);
        lbl_1_bss_9AC[var_r31][0] = CharModelMotionCreate(var_r30, 0x5F0002);
        CharModelMotionSet(var_r30, lbl_1_bss_9AC[var_r31][0]);
        Hu3DModelAttrSet(lbl_1_bss_9EC[var_r31], 0x40000001U);
        Hu3DModelCameraSet(lbl_1_bss_9EC[var_r31], lbl_1_data_358[var_r31]);
        Hu3DModelPosSet(lbl_1_bss_9EC[var_r31], ((( var_r31 / 4) * 200) - 100), 0.0f, (-( var_r31 % 4) * 150));
        Hu3DModelPosSet(lbl_1_bss_9EC[var_r31], 0.0f, 0.0f, 0.0f);
        CharModelMotionDataClose(var_r30);
    }

    var_r31 = Hu3DModelCreateFile(0x700024);
    Hu3DModelScaleSet(var_r31, 5.0f, 5.0f, 5.0f);
    Hu3DModelShadowMapSet(var_r31);

    while (TRUE)
    {
        if ((HuPadBtnDown[0] & PAD_BUTTON_Y) != 0) {
            Hu3DCameraKill(2);
            Hu3DCameraKill(4);
            Hu3DCameraKill(8);
            sp20.x = 
            sp20.z = 
            sp20.y = 0.0f;
            sp20.y += 200.0f;
            CharModelCoinEffectCreate(4, &sp20);
        }
        HuPrcVSleep();
    }
}

// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //