#include "dolphin.h"
#include "game/wipe.h"
#include "game/memory.h"
#include "game/flag.h"
#include "game/board/tutorial.h"
#include "version.h"

s16 HuSysVWaitGet(s16 old);

typedef s32 (*fadeFunc)(void);

SHARED_SYM WipeState wipeData;
BOOL wipeFadeInF;

static void WipeColorFill(GXColor color);
static void WipeFrameStill(GXColor color);


static s32 WipeNormalFade(void);
static s32 WipeCrossFade(void);
static s32 WipeDummyFade(void);

static fadeFunc fadeInFunc[3] = { WipeNormalFade, WipeCrossFade, WipeDummyFade };
static fadeFunc fadeOutFunc[3] = { WipeNormalFade, WipeCrossFade, WipeDummyFade };

void WipeInit(GXRenderModeObj *rmode)
{
	WipeState *wipe;
	s32 i;
	wipe = &wipeData;
	wipe->unk00 = 0;
	wipe->unk04 = 0;
	wipe->copy_data = NULL;
	wipe->stat = WIPE_TYPE_NORMAL;
	wipe->mode = WIPE_MODE_BLANK;
	wipe->type = 0;
	wipe->keep_copy = 0;
	for(i=0; i<8; i++) {
		wipe->unk10[i] = NULL;
	}
	wipe->color.r = wipe->color.g = wipe->color.b = wipe->color.a = 0;
	wipe->w = rmode->fbWidth;
	wipe->h = rmode->efbHeight;
	wipe->x = 0;
	wipe->y = 0;
}

void WipeExecAlways(void)
{
	s32 i;
	WipeState *wipe;
	wipe = &wipeData;
	switch(wipe->mode) {
		case WIPE_MODE_BLANK:
			wipe->type;
			wipe->color.a = 255;
			if(wipe->copy_data) {
				WipeFrameStill(wipe->color);
			} else {
				WipeColorFill(wipe->color);
			}
			break;
			
		case WIPE_MODE_IN:
			if(wipe->type < WIPE_TYPE_DUMMY) {
				wipe->stat = fadeInFunc[wipe->type]();
			} else {
				wipe->stat = 0;
			}
			wipe->time += HuSysVWaitGet(0);
			if(wipe->stat) {
				return;
			}
			if(wipe->copy_data) {
				if(!wipe->keep_copy) {
					HuMemDirectFree(wipe->copy_data);
				}
				wipe->copy_data = NULL;
			}
			
			for(i=0; i<8; i++) {
				if(wipe->unk10[i] != NULL) {
					HuMemDirectFree(wipe->unk10[i]);
					wipe->unk10[i] = NULL;
				}
			}
			wipe->unk0C = 0;
			wipe->time = 0;
			wipe->mode = 0;
			break;
			
		case WIPE_MODE_OUT:
			if(wipe->type < WIPE_TYPE_DUMMY) {
				wipe->stat = fadeOutFunc[wipe->type]();
			} else {
				wipe->stat = 0;
			}
			wipe->time += HuSysVWaitGet(0);
			if(wipe->stat) {
				return;
			}
			wipe->time = 0;
			wipe->mode = WIPE_MODE_BLANK;
			break;
			
		case 0:
			break;
	}
}

void WipeCreate(s16 mode, s16 type, s16 duration)
{
	WipeState *wipe;
#ifdef __MWERKS__ // TODO PC
	if(_CheckFlag(FLAG_ID_MAKE(1, 11)) && boardTutorialF) {
		return;
	}
#endif
	wipe = &wipeData;
	if(wipe->stat) {
		return;
	}
	if(mode == WIPE_MODE_IN || mode == WIPE_MODE_OUT) {
		if(mode == WIPE_MODE_IN) {
			wipeFadeInF = TRUE;
		}
		wipe->mode = mode;
		wipe->stat = 1;
		if(type >= 0) {
			wipe->type = type;
		}
		if(duration > 0) {
			wipe->duration = duration;
		} else {
			if(mode == WIPE_MODE_IN) {
				wipe->duration = 30.0f;
			} else {
				wipe->duration = 30.0f;
			}
		}
		wipe->time = 0;
	}
}

void WipeColorSet(u8 r, u8 g, u8 b)
{
	#if VERSION_PAL
	if(r > 160 && g > 160 && b > 160) {
		r = g = b = 160;
	}
	#endif
	wipeData.color.r = r;
	wipeData.color.g = g;
	wipeData.color.b = b;
}

u8 WipeStatGet(void)
{
	return wipeData.stat;
}

static s32 WipeDummyFade(void)
{
	return 0;
}

static s32 WipeNormalFade(void)
{
	u8 alpha;
	WipeState *wipe = &wipeData;
	if(wipe->duration == 0) {
		return 0;
	}
	alpha = (wipe->time/wipe->duration)*255.0f;
	switch(wipe->mode) {
		case WIPE_MODE_IN:
			wipe->color.a = 255-alpha;
			break;
			
		case WIPE_MODE_OUT:
			wipe->color.a = alpha;
			break;
			
		default:
			return 0;
	}
	WipeColorFill(wipe->color);
	if(wipe->time >= wipe->duration) {
		return 0;
	} else {
		return 1;
	}
}

static void WipeColorFill(GXColor color)
{
	static GXColor colorN = { 0xFF, 0xFF, 0xFF, 0xFF };
	Mtx44 proj;
	Mtx modelview;
	WipeState *wipe;
	u16 ulx, lrx, uly, lry;
	wipe = &wipeData;
	ulx = (s32)wipe->x;
	lrx = wipe->x+wipe->w;
	uly = (s32)wipe->y;
	lry = wipe->x+wipe->h+1;
	MTXOrtho(proj, uly, lry, ulx, lrx, 0, 10);
	GXSetProjection(proj, GX_ORTHOGRAPHIC);
	MTXIdentity(modelview);
	GXLoadPosMtxImm(modelview, GX_PNMTX0);
	GXSetCurrentMtx(GX_PNMTX0);
	GXSetViewport(0, 0, wipe->w, wipe->h+1, 0, 1);
	GXSetScissor(0, 0, wipe->w, wipe->h+1);
	GXClearVtxDesc();
	GXSetChanMatColor(GX_COLOR0A0, color);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
	GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
	GXSetAlphaUpdate(GX_FALSE);
	GXSetColorUpdate(GX_TRUE);
	GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition2u16(ulx, uly);
	GXPosition2u16(lrx, uly);
	GXPosition2u16(lrx, lry);
	GXPosition2u16(ulx, lry);
	GXEnd();
	GXSetChanMatColor(GX_COLOR0A0, colorN);
}

static s32 WipeCrossFade(void)
{
	u32 size;
	u8 alpha;
	WipeState *wipe = &wipeData;
	if(wipe->duration == 0) {
		return 0;
	}
	if(wipe->copy_data == NULL) {
		size = GXGetTexBufferSize(wipe->w, wipe->h, GX_TF_RGB565, GX_FALSE, 0);
		wipe->copy_data = HuMemDirectMallocNum(HEAP_DATA, size, 0x20000000);
		GXSetTexCopySrc(wipe->x, wipe->y, wipe->w, wipe->h);
		GXSetTexCopyDst(wipe->w, wipe->h, GX_TF_RGB565, GX_FALSE);
		GXCopyTex(wipe->copy_data, GX_FALSE);
		DCStoreRangeNoSync(wipe->copy_data, size);
	}
	alpha = (wipe->time/wipe->duration)*255.0f;
	switch(wipe->mode) {
		case WIPE_MODE_IN:
			wipe->color.a = 255-alpha;
			break;
			
		case WIPE_MODE_OUT:
			wipe->color.a = alpha;
			break;
			
		default:
			return 0;
	}
	WipeFrameStill(wipe->color);
	if(wipe->time >= wipe->duration) {
		return 0;
	} else {
		return 1;
	}
}

static void WipeFrameStill(GXColor color)
{
	GXTexObj tex;
	static GXColor colorN = { 0xFF, 0xFF, 0xFF, 0xFF };
	Mtx44 proj;
	Mtx modelview, temp;
	WipeState *wipe;
	u16 ulx, lrx, uly, lry;
	wipe = &wipeData;
	ulx = (s32)wipe->x;
	lrx = wipe->x+wipe->w;
	uly = (s32)wipe->y;
	lry = wipe->x+wipe->h+1;
	MTXOrtho(proj, uly, lry, ulx, lrx, 0, 10);
	GXSetProjection(proj, GX_ORTHOGRAPHIC);
	MTXIdentity(modelview);
	GXLoadPosMtxImm(modelview, GX_PNMTX0);
	GXSetCurrentMtx(GX_PNMTX0);
	GXSetViewport(0, 0, wipe->w, wipe->h+1, 0, 1);
	GXSetScissor(0, 0, wipe->w, wipe->h+1);
	GXClearVtxDesc();
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 1, GX_DF_CLAMP, GX_AF_SPOT);
	GXSetNumTexGens(1);
	GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
	GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	
	GXSetNumTevStages(2);
	GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C0, GX_CC_CPREV, GX_CC_ZERO);
	GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
	GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
	GXSetTevColor(GX_TEVSTAGE1, color);
	GXSetChanAmbColor(GX_COLOR0A0, colorN);
	GXSetChanMatColor(GX_COLOR0A0, colorN);
	GXInitTexObj(&tex, wipe->copy_data, wipe->w, wipe->h, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
	GXLoadTexObj(&tex, GX_TEXMAP0);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	MTXIdentity(temp);
	GXLoadPosMtxImm(temp, GX_PNMTX0);
	GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
	GXSetAlphaUpdate(GX_FALSE);
	GXSetColorUpdate(GX_TRUE);
	GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition2u16(ulx, uly);
	GXTexCoord2f32(0, 0);
	GXPosition2u16(lrx, uly);
	GXTexCoord2f32(1, 0);
	GXPosition2u16(lrx, lry);
	GXTexCoord2f32(1, 1);
	GXPosition2u16(ulx, lry);
	GXTexCoord2f32(0, 1);
	GXEnd();
	GXSetChanMatColor(GX_COLOR0A0, colorN);
#ifdef TARGET_PC
  	GXDestroyTexObj(&tex);
#endif
}
