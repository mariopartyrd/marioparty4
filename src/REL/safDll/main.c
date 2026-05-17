#include "dolphin.h"
#include "game/hsfman.h"
#include "game/gamework_data.h"
#include "game/printfunc.h"
#include "game/pad.h"
#include "math.h"

s32 lbl_1_data_0 = 100;
#if VERSION_NTSC
s32 lbl_1_bss_0[192];
#endif

void fn_1_0(void)
{

}

void safMarioEyeDim(s16 id)
{
	ModelData *model = &Hu3DData[id];
	HsfData *hsf = model->hsfData;
	HsfMaterial *material = hsf->material;
	s16 i, j;
	for(i=0; i<hsf->materialCnt; i++, material++) {
		for(j=0; j<material->numAttrs; j++) {
			HsfAttribute *attr = &hsf->attribute[material->attrs[j]];
			if(strcmp(attr->bitmap->name, "s3c000m1_eyes") == 0 || strcmp(attr->bitmap->name, "mario_eyes") == 0) {
				break;
			}
		}
		if(j == material->numAttrs) {
			material->color[0] *= 0.6f;
			material->color[1] *= 0.3f;
			material->color[2] *= 0.3f;
			material->litColor[0] *= 0.6f;
			material->litColor[1] *= 0.3f;
			material->litColor[2] *= 0.3f;
		}
	}
}

void safSaveTest(void)
{
	OSTick time_write;
	OSTick time_read;
	s16 character = GWPlayerCfg[0].character;
	SLLoad();
	time_write = time_read = 0;
	while(1) {
		print8(16, 420, 1.5f, "READ  TIME %d", OSTicksToMilliseconds(time_read));
		print8(16, 430, 1.5f, "WRITE TIME %d", OSTicksToMilliseconds(time_write));
		HuPrcVSleep();
		if(HuPadBtnDown[0] & PAD_BUTTON_Y) {
			CharFXStop(character, 282);
			time_write = OSGetTick();
			SLSave();
			time_write = OSGetTick()-time_write;
		}
		if(HuPadBtnDown[0] & PAD_BUTTON_X) {
			time_read = OSGetTick();
			SLLoad();
			time_read = OSGetTick()-time_read;
		}
	}
}
