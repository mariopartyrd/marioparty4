#include "REL/modeseldll.h"
#include "ext_math.h"
#include "game/audio.h"
#include "game/board/ui.h"
#include "game/disp.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"

#include <msm/msmsys.h>

typedef struct camera_view_params {
    Vec rot;
    Vec pos;
    float zoom;
} CameraViewParams;

CameraViewParams cameraViewTbl[] = { { { 0, 0, 0 }, { 0, 0, 0 }, 1500 }, { { 0, 0, 0 }, { 0, 0, 0 }, 524 } };

OMOBJ *cameraObj;
HUPROCESS *modeSelObjMan;
s32 exitF[2];
Vec cameraRotTarget;
Vec cameraPosTarget;
float cameraZoomTarget;
Vec cameraRot[4];
Vec cameraPos[2];
float cameraZoom[2];
s32 cameraDebugF;

void ModeSelMain(void);
void ModeSelSceneInit(void);
void ModeSelExitMain(void);
void ModeSelCameraUpdate(OMOBJ *object);
void ModeSelCameraDebugUpdate(OMOBJ *object);
void ModeSelCameraMove(void);

void ObjectSetup(void)
{
    s32 light;
    OSReport("******* MS ObjectSetup *********\n");
    modeSelObjMan = omInitObjMan(50, 8192);
    omGameSysInit(modeSelObjMan);
    cameraRot[0].x = -70;
    cameraRot[0].y = 0;
    cameraRot[0].z = 0;
    cameraPos[0].x = 0;
    cameraPos[0].y = 130;
    cameraPos[0].z = -186;
    cameraZoom[0] = 1360;
    cameraRotTarget = cameraRot[0];
    cameraPosTarget = cameraPos[0];
    cameraZoomTarget = cameraZoom[0];
    exitF[0] = 0;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30, 20, 8000, 1.2f);
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(1, 0, 16, 640, 448);
    light = Hu3DGLightCreate(0, 100, 1000, 0, -0.5, -1, 255, 255, 255);
    Hu3DGLightInfinitytSet(light);
    HuPrcChildCreate(ModeSelMain, 100, 16384, 0, modeSelObjMan);
    HuPrcChildCreate(ModeSelExitMain, 200, 4096, 0, modeSelObjMan);
    cameraObj = omAddObjEx(modeSelObjMan, 32730, 0, 0, -1, ModeSelCameraUpdate);
    omAddObjEx(modeSelObjMan, 0, 32, 32, -1, ModeSelCameraDebugUpdate);
    Hu3DBGColorSet(0, 0, 0);
    mgBoardHostEnableF = 0;
    HuWinInit(1);
    mgPracticeEnableF = 0;
    mgQuitExtraF = 0;
}

void ModeSelMain(void)
{
    ModeSelSceneInit();
    if (omovlevtno) {
        HuAudSeqPlay(43);
    }
    else {
        if (!FileSelectExec()) {
            WipeColorSet(0, 0, 0);
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
            HuAudSeqAllFadeOut(1000);
            while (WipeStatGet()) {
                HuPrcVSleep();
            }
            #if VERSION_PAL
            if(GwLanguageSave != -1) {
                GWGameStat.language = GwLanguageSave;
            } else if(GwLanguage != -1) {
                GWGameStat.language = GwLanguage;
            }
            #endif
            omOvlReturnEx(1, 1);
            while (1) {
                HuPrcVSleep();
            }
        }
        else {
            s16 grpId;
            s16 sprId;
            #if VERSION_PAL
            HuWinAllKill();
            HuWinInit(1);
            #endif
            grpId = HuSprGrpCreate(1);
            sprId = HuTHPSprCreateVol("movie/opmov_s00.thp", 0, 3000, 70.0);
            HuSprGrpMemberSet(grpId, 0, sprId);
            HuSprPosSet(grpId, 0, 288, 240);
            HuSprDrawNoSet(grpId, 0, 127);
            HuPrcSleep(2);
            espAttrSet(modeSelSprId[0], HUSPR_ATTR_DISPOFF);
            HuAudFXStop(fileSelectFxId);
            while (!HuTHPEndCheck()) {
                HuPrcVSleep();
            }
            HuTHPClose();
            HuSprGrpKill(grpId);
        }
    }
    espAttrReset(modeSelSprId[9], HUSPR_ATTR_DISPOFF);
    espDrawNoSet(modeSelSprId[9], 127);
    {
        s16 result = ModeSelExec();
        if (result == -1) {
            HuAudSeqAllFadeOut(1000);
            WipeColorSet(0, 0, 0);
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);

            while (WipeStatGet()) {
                HuPrcVSleep();
            }
            omOvlGotoEx(DLL_modeseldll, 1, 0, 0);
            while (1) {
                HuPrcVSleep();
            }
        }
        else {
            s16 i;
            OMOVLHIS *his;
            for (i = 0; i < 4; i++) {
                GWPlayerCfg[i].pad_idx = i;
                if (!HuPadStatGet(i)) {
                    GWPlayerCfg[i].iscom = 0;
                }
                else {
                    GWPlayerCfg[i].iscom = 1;
                }
            }
            his = omOvlHisGet(0);
            omOvlHisChg(0, his->ovl, 1, his->stat);
            _ClearFlag(FLAG_ID_MAKE(1, 0));
            _ClearFlag(FLAG_ID_MAKE(1, 8));
            _ClearFlag(FLAG_ID_MAKE(1, 12));
            _ClearFlag(FLAG_ID_MAKE(1, 11));
            GWGameStat.sound_mode = msmSysGetOutputMode();
            switch (result) {
                case 0:
                    GWMGExplainSet(GWGameStat.party_pause.explain_mg);
                    GWMGShowComSet(GWGameStat.party_pause.show_com_mg);
                    GWMGListSet(GWGameStat.party_pause.mg_list);
                    GWMessSpeedSet(GWGameStat.party_pause.mess_speed);
                    GWSaveModeSet(GWGameStat.party_pause.save_mode);
                    omOvlCallEx(DLL_mentdll, 1, 0, 0);
                    break;

                case 1:
                    GWMGExplainSet(GWGameStat.story_pause.explain_mg);
                    GWMGShowComSet(GWGameStat.story_pause.show_com_mg);
                    GWMGListSet(GWGameStat.story_pause.mg_list);
                    GWMessSpeedSet(GWGameStat.story_pause.mess_speed);
                    GWSaveModeSet(GWGameStat.story_pause.save_mode);
                    omOvlCallEx(DLL_mentdll, 1, 1, 0);
                    break;

                case 2:
                    omOvlCallEx(DLL_mgmodedll, 1, 0, 0);
                    break;

                case 3:
                    omOvlCallEx(DLL_mentdll, 1, 3, 0);
                    break;

                case 4:
                    omOvlCallEx(DLL_mentdll, 1, 4, 0);
                    break;

                case 5:
                    omOvlCallEx(DLL_mpexdll, 1, 0, 0);
                    break;
            }
            while (1) {
                HuPrcVSleep();
            }
        }
    }
}

void ModeSelSceneInit(void)
{
    Vec pos;
    Vec target;
    Vec up;
    Hu3DShadowCreate(20, 100, 5000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowSizeSet(192);
    target.x = target.y = target.z = 0;
    pos.x = 500;
    pos.z = 1000;
    pos.y = 2000;
    up.x = 0;
    up.y = 1;
    up.z = 0;
    Hu3DShadowPosSet(&pos, &up, &target);
    ModeSelModelCreate(modeSelModelTbl);
    ModeSelSpriteCreate(modeSelSpriteTbl);
}

void ModeSelExitMain(void)
{
    s16 i;
    while (1) {
        if (exitF[0] || omSysExitReq) {
            break;
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        GWPlayerCfg[i].character = -1;
    }
    BoardStatusKill();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

u16 cameraBitTbl[] = { 1, 2 };

void ModeSelCameraUpdate(OMOBJ *object)
{
    s16 i;
    for (i = 0; i < 1; i++) {
        Vec pos, target, up;
        float x, y, z;

        x = cameraRot[i].x;
        y = cameraRot[i].y;
        z = cameraRot[i].z;

        pos.x = (((sind(y) * cosd(x)) * cameraZoom[i]) + cameraPos[i].x);
        pos.y = (-sind(x) * cameraZoom[i]) + cameraPos[i].y;
        pos.z = ((cosd(y) * cosd(x)) * cameraZoom[i]) + cameraPos[i].z;
        target.x = cameraPos[i].x;
        target.y = cameraPos[i].y;
        target.z = cameraPos[i].z;
        up.x = sind(y) * sind(x);
        up.y = cosd(x);
        up.z = cosd(y) * sind(x);
        Hu3DCameraPosSet(cameraBitTbl[i], pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
    }
}

void ModeSelCameraDebugUpdate(OMOBJ *object)
{
    Vec pos;
    Vec offset;
    Vec dir;
    Vec y_offset;

    f32 z_rot;
    s8 stick_pos;

    if (!cameraDebugF) {
        ModeSelCameraMove();
        return;
    }
    cameraRot[0].y += 0.1f * HuPadStkX[0];
    cameraRot[0].x += 0.1f * HuPadStkY[0];
    cameraZoom[0] += HuPadTrigL[0] / 2;
    cameraZoom[0] -= HuPadTrigR[0] / 2;
    if (HuPadBtnDown[0] & PAD_BUTTON_B) {
        OSReport("%f,%f,%f\n", cameraRot[0].x, cameraRot[0].y, cameraRot[0].z);
        OSReport("%f,%f,%f\n", cameraPos[0].x, cameraPos[0].y, cameraPos[0].z);
        OSReport("%f\n", cameraZoom[0]);
    }
    if (cameraZoom[0] < 100.0f) {
        cameraZoom[0] = 100.0f;
    }
    pos.x = cameraPos[0].x + (cameraZoom[0] * (sind(cameraRot[0].y) * cosd(cameraRot[0].x)));
    pos.y = (cameraPos[0].y + (cameraZoom[0] * -sind(cameraRot[0].x)));
    pos.z = (cameraPos[0].z + (cameraZoom[0] * (cosd(cameraRot[0].y) * cosd(cameraRot[0].x))));
    offset.x = cameraPos[0].x - pos.x;
    offset.y = cameraPos[0].y - pos.y;
    offset.z = cameraPos[0].z - pos.z;
    dir.x = (sind(cameraRot[0].y) * sind(cameraRot[0].x));
    dir.y = cosd(cameraRot[0].x);
    dir.z = (cosd(cameraRot[0].y) * sind(cameraRot[0].x));
    z_rot = cameraRot[0].z;
    y_offset.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * cosd(z_rot))
        + dir.y * (offset.x * offset.y * (1.0f - cosd(z_rot)) - offset.z * sind(z_rot))
        + dir.z * (offset.x * offset.z * (1.0f - cosd(z_rot)) + offset.y * sind(z_rot));

    y_offset.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * cosd(z_rot))
        + dir.x * (offset.x * offset.y * (1.0f - cosd(z_rot)) + offset.z * sind(z_rot))
        + dir.z * (offset.y * offset.z * (1.0f - cosd(z_rot)) - offset.x * sind(z_rot));

    y_offset.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * cosd(z_rot))
        + (dir.x * (offset.x * offset.z * (1.0 - cosd(z_rot)) - offset.y * sind(z_rot))
            + dir.y * (offset.y * offset.z * (1.0 - cosd(z_rot)) + offset.x * sind(z_rot)));

    VECCrossProduct(&dir, &offset, &offset);
    VECNormalize(&offset, &offset);
    stick_pos = (HuPadSubStkX[0] & 0xF8);
    if (stick_pos != 0) {
        cameraPos[0].x += 0.05f * (offset.x * stick_pos);
        cameraPos[0].y += 0.05f * (offset.y * stick_pos);
        cameraPos[0].z += 0.05f * (offset.z * stick_pos);
    }
    VECNormalize(&y_offset, &offset);
    stick_pos = -(HuPadSubStkY[0] & 0xF8);
    if (stick_pos != 0) {
        cameraPos[0].x += 0.05f * (offset.x * stick_pos);
        cameraPos[0].y += 0.05f * (offset.y * stick_pos);
        cameraPos[0].z += 0.05f * (offset.z * stick_pos);
    }
}

void ModeSelCameraMove(void)
{
    Vec delta_vec;
    float delta_zoom;
    if (exitF[0]) {
        return;
    }
    VECSubtract(&cameraRotTarget, &cameraRot[0], &delta_vec);
    if (VECMag(&delta_vec) > 0.2) {
        VECScale(&delta_vec, &delta_vec, 0.05f);
        VECAdd(&cameraRot[0], &delta_vec, &cameraRot[0]);
    }
    else {
        cameraRot[0] = cameraRotTarget;
    }
    VECSubtract(&cameraPosTarget, &cameraPos[0], &delta_vec);
    if (VECMag(&delta_vec) > 0.2) {
        VECScale(&delta_vec, &delta_vec, 0.05f);
        VECAdd(&cameraPos[0], &delta_vec, &cameraPos[0]);
    }
    else {
        cameraPos[0] = cameraPosTarget;
    }
    delta_zoom = cameraZoomTarget - cameraZoom[0];
    if (sqrtf(delta_zoom * delta_zoom) > 0.2) {
        delta_zoom *= 0.05f;
        cameraZoom[0] += delta_zoom;
    }
    else {
        cameraZoom[0] = cameraZoomTarget;
    }
}

void ModeSelCameraViewMove(s16 view)
{
    cameraRotTarget = cameraViewTbl[view].rot;
    cameraPosTarget = cameraViewTbl[view].pos;
    cameraZoomTarget = cameraViewTbl[view].zoom;
}

void ModeSelCameraViewSet(s16 view)
{
    s16 i;
    cameraRot[0] = cameraViewTbl[view].rot;
    cameraRotTarget = cameraRot[0];
    cameraPos[0] = cameraViewTbl[view].pos;
    cameraPosTarget = cameraPos[0];
    cameraZoomTarget = cameraZoom[0] = cameraViewTbl[view].zoom;
    ModeSelCameraUpdate(NULL);
}

float ModeSelCameraZoomDistGet(void)
{
    float delta_zoom = cameraZoomTarget - cameraZoom[0];
    return sqrtf(delta_zoom * delta_zoom);
}
