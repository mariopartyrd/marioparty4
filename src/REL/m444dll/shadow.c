#include "game/hsfman.h"
#include "game/object.h"

#include "ext_math.h"

void fn_1_D9F4(s16);

void fn_1_D9C8(void)
{
    Hu3DLayerHookSet(7, fn_1_D9F4);
}

void fn_1_D9F4(s16 arg0)
{
    Mtx44 sp64;
    Mtx sp34;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    GXColor spC;
    CameraData *var_r31;

    var_r31 = &Hu3DCamera[0];
    C_MTXPerspective(sp64, var_r31->fov, var_r31->aspect, var_r31->nnear, var_r31->ffar);
    GXSetProjection(sp64, GX_PERSPECTIVE);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 0x280, 0x1E0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    spC.a = 0xFF;
    GXSetTevColor(GX_TEVREG0, spC);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetAlphaCompare(GX_GEQUAL, 0, GX_AOP_AND, GX_GEQUAL, 0);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    sp28.x = sp28.y = sp28.z = 0.0f;
    sp1C.x = sp1C.y = 0.0f;
    sp1C.z = -100.0f;
    sp10.x = sp10.z = 0.0f;
    sp10.y = 1.0f;
    C_MTXLookAt(sp34, &sp28, &sp10, &sp1C);
    GXLoadPosMtxImm(sp34, 0);
    sp28.x = 1.2f * (10000.0 * -sin(var_r31->fov / 2));
    sp28.y = (2.5f / 3) * (10000.0 * -sin(var_r31->fov / 2));
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-sp28.x, -sp28.y, -10000.0f);
    GXPosition3f32(sp28.x, -sp28.y, -10000.0f);
    GXPosition3f32(sp28.x, sp28.y, -10000.0f);
    GXPosition3f32(-sp28.x, sp28.y, -10000.0f);
    GXEnd();
}
