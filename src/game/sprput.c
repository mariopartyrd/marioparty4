#include "game/sprite.h"
#include "game/hsfman.h"
#include "game/init.h"
#include "game/disp.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"
#include "dolphin/vi.h"

static void *bmpNoCC[8];
static short HuSprLayerDrawNo[8];

static short bmpCCIdx;

void mtxTransCat(Mtx matrix, float x, float y, float z);

static void HuSprLayerHook(short layer);

void HuSprDispInit(void)
{
    Mtx44 proj;
    short i;
    for(i=0; i<8; i++) {
        bmpNoCC[i] = NULL;
    }
    bmpCCIdx = 0;
    GXInvalidateTexAll();
    MTXOrtho(proj, 0, HU_DISP_HEIGHT, 0, HU_DISP_WIDTH, 0, 10);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    if(RenderMode->field_rendering) {
        GXSetViewportJitter(0, 0, HU_FB_WIDTH, HU_FB_HEIGHT, 0, 1, VIGetNextField());
    } else {
        GXSetViewport(0, 0, HU_FB_WIDTH, HU_FB_HEIGHT, 0, 1);
    }
    GXSetScissor(0, 0, HU_FB_WIDTH, HU_FB_HEIGHT);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
}

void HuSprDisp(HuSprite *sprite)
{
    short i;
    AnimData *anim = sprite->data;
    AnimPatData *pat = sprite->pat_data;
    Vec axis = {0, 0, 1};
    Mtx modelview, rot;
    short color_sum;
    HuSprFunc func;
    
    GXSetScissor(sprite->scissor_x, sprite->scissor_y, sprite->scissor_w, sprite->scissor_h);
    if(sprite->attr & HUSPR_ATTR_FUNC) {
        if(sprite->func) {
            func = sprite->func;
            func(sprite);
            HuSprDispInit();
        }
        
    } else {
        AnimLayerData *layer;
        AnimBmpData *bg_bmp;
        GXColor color;
        GXSetNumTexGens(1);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        color.r = color.g = color.b = color.a = 255;
        GXSetChanAmbColor(GX_COLOR0A0, color);
        GXSetChanMatColor(GX_COLOR0A0, color);
        color.r = sprite->r;
        color.g = sprite->g;
        color.b = sprite->b;
        color.a = sprite->a;
        color_sum = color.r+color.g+color.b+color.a;
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C0, GX_CC_CPREV, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
        if(sprite->attr & HUSPR_ATTR_ADDCOL) {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
        } else if(sprite->attr & HUSPR_ATTR_INVCOL) {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
        } else {
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        }
        if(sprite->bg) {
            AnimPatData *bg_pat;
            AnimFrameData *bg_frame;
            bg_frame = sprite->bg->bank[sprite->bg_bank].frame;
            bg_pat = &sprite->bg->pat[bg_frame->pat];
            layer = bg_pat->layer;
            bg_bmp = &sprite->bg->bmp[layer->bmpNo];
            HuSprTexLoad(sprite->bg, layer->bmpNo, 1, GX_CLAMP, GX_CLAMP, GX_NEAR);
            GXSetNumIndStages(1);
            GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, bg_bmp->sizeX*16, bg_bmp->sizeY*16);
            GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
            GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_16, GX_ITS_16);
            GXSetTevIndTile(GX_TEVSTAGE0, GX_INDTEXSTAGE0, 16, 16, 16, 16, GX_ITF_4, GX_ITM_0, GX_ITB_NONE, GX_ITBA_OFF);
        }
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(GX_FALSE);
        if(0 != sprite->z_rot) {
            MTXRotAxisDeg(rot, &axis, sprite->z_rot);
            MTXScale(modelview, sprite->scale_x, sprite->scale_y, 1.0f);
            MTXConcat(rot, modelview, modelview);
        } else {
            MTXScale(modelview, sprite->scale_x, sprite->scale_y, 1.0f);
        }
        mtxTransCat(modelview, sprite->x, sprite->y, 0);
        MTXConcat(*sprite->group_mtx, modelview, modelview);
        GXLoadPosMtxImm(modelview, GX_PNMTX0);
        for(i=pat->layerNum-1; i>=0; i--) {
            float pos[4][2];
            float texcoord_x1, texcoord_y1, texcoord_x2, texcoord_y2;
            AnimBmpData *bmp;
            layer = &pat->layer[i];
            bmp = &anim->bmp[layer->bmpNo];
            if(!bmp) {
                continue;
            }
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            HuSprTexLoad(anim, layer->bmpNo, 0, sprite->wrap_s, sprite->wrap_t, (sprite->attr & HUSPR_ATTR_LINEAR) ? GX_LINEAR : GX_NEAR);
            if(layer->alpha != 255 || color_sum != 255*4) {
                color.a = (u16)(sprite->a*layer->alpha) >> 8;
                GXSetTevColor(GX_TEVSTAGE1, color);
                GXSetNumTevStages(2);
            } else {
                GXSetNumTevStages(1);
            }
            if(!sprite->bg) {
                pos[0][0] = layer->vtx[0]-pat->centerX;
                pos[0][1] = layer->vtx[1]-pat->centerY;
                pos[1][0] = layer->vtx[2]-pat->centerX;
                pos[1][1] = layer->vtx[3]-pat->centerY;
                pos[2][0] = layer->vtx[4]-pat->centerX;
                pos[2][1] = layer->vtx[5]-pat->centerY;
                pos[3][0] = layer->vtx[6]-pat->centerX;
                pos[3][1] = layer->vtx[7]-pat->centerY;
                if(layer->flip & ANIM_LAYER_FLIPX) {
                    texcoord_x2 = layer->startX/(float)bmp->sizeX;
                    texcoord_x1 = (layer->startX+layer->sizeX)/(float)bmp->sizeX;
                } else {
                    texcoord_x1 = layer->startX/(float)bmp->sizeX;
                    texcoord_x2 = (layer->startX+layer->sizeX)/(float)bmp->sizeX;
                }
                if(layer->flip & ANIM_LAYER_FLIPY) {
                    texcoord_y2 = layer->startY/(float)bmp->sizeY;
                    texcoord_y1 = (layer->startY+layer->sizeY)/(float)bmp->sizeY;
                } else {
                    texcoord_y1 = layer->startY/(float)bmp->sizeY;
                    texcoord_y2 = (layer->startY+layer->sizeY)/(float)bmp->sizeY;
                }
            } else {
                pos[0][0] = pos[3][0] = -(bg_bmp->sizeX*16)/2;
                pos[0][1] = pos[1][1] = -(bg_bmp->sizeY*16)/2;
                pos[2][0] = pos[1][0] = pos[0][0]+(bg_bmp->sizeX*16);
                pos[2][1] = pos[3][1] = pos[0][1]+(bg_bmp->sizeY*16);
                texcoord_x1 = texcoord_y1 =  1.0/(bg_bmp->sizeX*16);
                texcoord_x2 = texcoord_y2 = 1.0f;
            }
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(pos[0][0], pos[0][1], 0);
            GXTexCoord2f32(texcoord_x1*sprite->tex_scale_x, texcoord_y1*sprite->tex_scale_y);
            GXPosition3f32(pos[1][0], pos[1][1], 0);
            GXTexCoord2f32(texcoord_x2*sprite->tex_scale_x, texcoord_y1*sprite->tex_scale_y);
            GXPosition3f32(pos[2][0], pos[2][1], 0);
            GXTexCoord2f32(texcoord_x2*sprite->tex_scale_x, texcoord_y2*sprite->tex_scale_y);
            GXPosition3f32(pos[3][0], pos[3][1], 0);
            GXTexCoord2f32(texcoord_x1*sprite->tex_scale_x, texcoord_y2*sprite->tex_scale_y);
            GXEnd();
        }
        if(sprite->bg) {
            GXSetNumIndStages(0);
            GXSetTevDirect(GX_TEVSTAGE0);
            GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
        }
    }
}

void HuSprTexLoad(AnimData *anim, short bmp, short slot, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, GXTexFilter filter)
{
    GXTexObj tex_obj;
    GXTlutObj tlut_obj;
    AnimBmpData *bmp_ptr = &anim->bmp[bmp];
    short sizeX = bmp_ptr->sizeX;
    short sizeY = bmp_ptr->sizeY;
    switch(bmp_ptr->dataFmt & ANIM_BMP_FMTMASK) {
        case ANIM_BMP_RGBA8:
            GXInitTexObj(&tex_obj, bmp_ptr->data, sizeX, sizeY, GX_TF_RGBA8, wrap_s, wrap_t, GX_FALSE);
            break;
            
        case ANIM_BMP_RGB5A3:
        case ANIM_BMP_RGB5A3_DUPE:
            GXInitTexObj(&tex_obj, bmp_ptr->data, sizeX, sizeY, GX_TF_RGB5A3, wrap_s, wrap_t, GX_FALSE);
            break;
            
        case ANIM_BMP_C8:
            GXInitTlutObj(&tlut_obj, bmp_ptr->palData, GX_TL_RGB5A3, bmp_ptr->palNum);
            GXLoadTlut(&tlut_obj, slot);
            GXInitTexObjCI(&tex_obj,bmp_ptr->data, sizeX, sizeY, GX_TF_C8, wrap_s, wrap_t, GX_FALSE, slot);
            break;
            
        case ANIM_BMP_C4:
            GXInitTlutObj(&tlut_obj, bmp_ptr->palData, GX_TL_RGB5A3, bmp_ptr->palNum);
            GXLoadTlut(&tlut_obj, slot);
            GXInitTexObjCI(&tex_obj,bmp_ptr->data, sizeX, sizeY, GX_TF_C4, wrap_s, wrap_t, GX_FALSE, slot);
            break;
            
        case ANIM_BMP_IA8:
            GXInitTexObj(&tex_obj, bmp_ptr->data, sizeX, sizeY, GX_TF_IA8, wrap_s, wrap_t, GX_FALSE);
            break;
            
        case ANIM_BMP_IA4:
            GXInitTexObj(&tex_obj, bmp_ptr->data, sizeX, sizeY, GX_TF_IA4, wrap_s, wrap_t, GX_FALSE);
            break;
            
        case ANIM_BMP_I8:
            GXInitTexObj(&tex_obj, bmp_ptr->data, sizeX, sizeY, GX_TF_I8, wrap_s, wrap_t, GX_FALSE);
            break;
        
        case ANIM_BMP_I4:
            GXInitTexObj(&tex_obj, bmp_ptr->data, sizeX, sizeY, GX_TF_I4, wrap_s, wrap_t, GX_FALSE);
            break;
            
        case ANIM_BMP_A8:
            GXInitTexObj(&tex_obj, bmp_ptr->data, sizeX, sizeY, GX_CTF_A8, wrap_s, wrap_t, GX_FALSE);
            break;
            
        case ANIM_BMP_CMPR:
            GXInitTexObj(&tex_obj, bmp_ptr->data, sizeX, sizeY, GX_TF_CMPR, wrap_s, wrap_t, GX_FALSE);
            break;
            
        default:
            break;
    }
    GXInitTexObjLOD(&tex_obj, filter, filter, 0, 0, 0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&tex_obj, slot);
#ifdef TARGET_PC
    GXDestroyTexObj(&tex_obj);
    GXDestroyTlutObj(&tlut_obj);
#endif
}

void HuSprExecLayerSet(short draw_no, short layer)
{
    HuSprLayerDrawNo[layer] = draw_no;
    Hu3DLayerHookSet(layer, HuSprLayerHook);
}

static void HuSprLayerHook(short layer)
{
    HuSprDispInit();
    HuSprExec(HuSprLayerDrawNo[layer]);
}
