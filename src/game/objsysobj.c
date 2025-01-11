#include "game/object.h"
#include "game/hsfman.h"
#include "game/pad.h"
#include "game/objsub.h"
#include "game/minigame_seq.h"
#include "game/sprite.h"
#include "game/hsfman.h"
#include "game/audio.h"
#include "ext_math.h"

Vec CRot;
Vec Center;
float CZoom;
Vec CRotM[16];
Vec CenterM[16];
float CZoomM[16];

s16 omDBGMenuButton;

void omOutView(omObjData *object)
{
	Vec pos, target, up;
	float rot_x = CRot.x;
	float rot_y = CRot.y;
	float rot_z = CRot.z;
	pos.x = (sind(rot_y)*cosd(rot_x)*CZoom)+Center.x;
	pos.y = (-sind(rot_x)*CZoom)+Center.y;
	pos.z = (cosd(rot_y)*cosd(rot_x)*CZoom)+Center.z;
	target.x = Center.x;
	target.y = Center.y;
	target.z = Center.z;
	up.x = sind(rot_y)*sind(rot_x);
	up.y = cosd(rot_x);
	up.z = cosd(rot_y)*sind(rot_x);
	Hu3DCameraPosSet(1, pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
}

void omOutViewMulti(omObjData *object)
{
	u8 i;
	for(i=0; i<object->work[0]; i++) {
		Vec pos, target, up;
		float rot_x = CRotM[i].x;
		float rot_y = CRotM[i].y;
		float rot_z = CRotM[i].z;
		pos.x = (sind(rot_y)*cosd(rot_x)*CZoomM[i])+CenterM[i].x;
		pos.y = (-sind(rot_x)*CZoomM[i])+CenterM[i].y;
		pos.z = (cosd(rot_y)*cosd(rot_x)*CZoomM[i])+CenterM[i].z;
		target.x = CenterM[i].x;
		target.y = CenterM[i].y;
		target.z = CenterM[i].z;
		up.x = sind(rot_y)*sind(rot_x);
		up.y = cosd(rot_x);
		up.z = cosd(rot_y)*sind(rot_x);
		Hu3DCameraPosSetV((1 << i), &pos, &up, &target);
	}
}


void omSystemKeyCheckSetup(Process *objman)
{
	omObjData *object;
	object = omAddObjEx(objman, 32731, 0, 0, -1, omSystemKeyCheck);
	omDBGSysKeyObj = object;
	omSetStatBit(object, 0xA0);
	object->work[0] = 0;
	object->work[1] = 0;
	object->work[2] = 0;
}

void omSystemKeyCheck(omObjData *object)
{
	if(!omSysPauseEnableFlag) {
		return;
	}
	if(object->work[0] & 0x1) {
		u32 pad = object->work[1];
		if(pad != (u16)-1 && HuPadStatGet(pad) == 0 && (HuPadBtnDown[pad] & PAD_BUTTON_START)) {
			object->work[0] |= 0x200;
		}
		if(object->work[0] & 0x200) {
			if(omMgIndexGet(omcurovl) != -1) {
				MGSeqPauseKill();
			} else {
				object->work[0] |= 0x100;
			}
		}
		if(object->work[0] & 0x100) {
			object->work[0] &= ~0x301;
			omAllPause(0);
			HuPrcAllPause(0);
			Hu3DPauseSet(0);
			HuSprPauseSet(0);
			HuAudFXPauseAll(0);
			HuAudSeqPauseAll(0);
		}
	} else {
		s32 i;
		s16 pause = 0;
		if(WipeStatGet() || omCurrentOvlGet() == OVL_INVALID || omSysExitReq) {
			return;
		}
		for(i=0; i<4; i++) {
			if(HuPadStatGet(i) == 0 && (HuPadBtnDown[i] & PAD_BUTTON_START)) {
				pause = 1;
				break;
			}
		}
		if(object->work[0] & 0x80) {
			object->work[0] &= ~0x80;
			pause = 1;
			i = (u16)-1;
		}
		if(pause) {
			object->work[0] |= 0x1;
			object->work[1] = i;
			omAllPause(1);
			HuPrcAllPause(1);
			Hu3DPauseSet(1);
			HuSprPauseSet(1);
			HuAudFXPauseAll(1);
			HuAudSeqPauseAll(1);
			if(omMgIndexGet(omcurovl) != -1) {
				MGSeqPauseInit();
			}
			HuPadRumbleAllStop();
		}
	}
}


void omSysPauseEnable(u8 flag)
{
	omSysPauseEnableFlag = flag;
}

void omSysPauseCtrl(s16 flag)
{
	if(!omDBGSysKeyObj) {
		return;
	}
	omDBGSysKeyObj->work[0] &= ~0x180;
	if(flag) {
		omDBGSysKeyObj->work[0] |= 0x80;
	} else {
		omDBGSysKeyObj->work[0] |= 0x100;
	}
}
