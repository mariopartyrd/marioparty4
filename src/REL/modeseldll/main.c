#include "REL/modeseldll.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"
#include "ext_math.h"

typedef struct camera_view_params {
    Vec rot;
    Vec pos;
    float zoom;
} CameraViewParams;

CameraViewParams lbl_1_data_0[] = { { { 0, 0, 0 }, { 0, 0, 0 }, 1500 }, { { 0, 0, 0 }, { 0, 0, 0 }, 524 } };

omObjData *lbl_1_bss_7C;
Process *lbl_1_bss_78;
s32 lbl_1_bss_70[2];
Vec lbl_1_bss_64;
Vec lbl_1_bss_58;
float lbl_1_bss_54;
Vec lbl_1_bss_24[4];
Vec lbl_1_bss_C[2];
float lbl_1_bss_4[2];
s32 lbl_1_bss_0;

void fn_1_414(void);
void fn_1_9F4(void);
void fn_1_AF0(void);
void fn_1_B8C(omObjData *object);
void fn_1_F40(omObjData *object);
void fn_1_1B6C(void);

void ObjectSetup(void)
{
    s32 light;
    OSReport("******* MS ObjectSetup *********\n");
    lbl_1_bss_78 = omInitObjMan(50, 8192);
    omGameSysInit(lbl_1_bss_78);
    lbl_1_bss_24[0].x = -70;
    lbl_1_bss_24[0].y = 0;
    lbl_1_bss_24[0].z = 0;
    lbl_1_bss_C[0].x = 0;
    lbl_1_bss_C[0].y = 130;
    lbl_1_bss_C[0].z = -186;
    lbl_1_bss_4[0] = 1360;
    lbl_1_bss_64 = lbl_1_bss_24[0];
    lbl_1_bss_58 = lbl_1_bss_C[0];
    lbl_1_bss_54 = lbl_1_bss_4[0];
    lbl_1_bss_70[0] = 0;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30, 20, 8000, 1.2f);
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(1, 0, 16, 640, 448);
    light = Hu3DGLightCreate(0, 100, 1000, 0, -0.5, -1, 255, 255, 255);
    Hu3DGLightInfinitytSet(light);
    HuPrcChildCreate(fn_1_414, 100, 16384, 0, lbl_1_bss_78);
    HuPrcChildCreate(fn_1_AF0, 200, 4096, 0, lbl_1_bss_78);
    lbl_1_bss_7C = omAddObjEx(lbl_1_bss_78, 32730, 0, 0, -1, fn_1_B8C);
    omAddObjEx(lbl_1_bss_78, 0, 32, 32, -1, fn_1_F40);
    Hu3DBGColorSet(0, 0, 0);
    mgBoardHostEnableF = 0;
    HuWinInit(1);
    mgPracticeEnableF = 0;
    mgQuitExtraF = 0;
}

void fn_1_414(void)
{
    fn_1_9F4();
    if (omovlevtno) {
        HuAudSeqPlay(43);
    }
    else {
        if (!fn_1_37DC()) {
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
            espAttrSet(lbl_1_bss_152[0], HUSPR_ATTR_DISPOFF);
            HuAudFXStop(lbl_1_data_100);
            while (!HuTHPEndCheck()) {
                HuPrcVSleep();
            }
            HuTHPClose();
            HuSprGrpKill(grpId);
        }
    }
    espAttrReset(lbl_1_bss_152[9], HUSPR_ATTR_DISPOFF);
    espDrawNoSet(lbl_1_bss_152[9], 127);
    {
        s16 result = fn_1_2490();
        if (result == -1) {
            HuAudSeqAllFadeOut(1000);
            WipeColorSet(0, 0, 0);
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);

            while (WipeStatGet()) {
                HuPrcVSleep();
            }
            omOvlGotoEx(OVL_MODESEL, 1, 0, 0);
            while (1) {
                HuPrcVSleep();
            }
        }
        else {
            s16 i;
            omOvlHisData *his;
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
            omOvlHisChg(0, his->overlay, 1, his->stat);
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
                    omOvlCallEx(OVL_MENT, 1, 0, 0);
                    break;

                case 1:
                    GWMGExplainSet(GWGameStat.story_pause.explain_mg);
                    GWMGShowComSet(GWGameStat.story_pause.show_com_mg);
                    GWMGListSet(GWGameStat.story_pause.mg_list);
                    GWMessSpeedSet(GWGameStat.story_pause.mess_speed);
                    GWSaveModeSet(GWGameStat.story_pause.save_mode);
                    omOvlCallEx(OVL_MENT, 1, 1, 0);
                    break;

                case 2:
                    omOvlCallEx(OVL_MGMODE, 1, 0, 0);
                    break;

                case 3:
                    omOvlCallEx(OVL_MENT, 1, 3, 0);
                    break;

                case 4:
                    omOvlCallEx(OVL_MENT, 1, 4, 0);
                    break;

                case 5:
                    omOvlCallEx(OVL_MPEX, 1, 0, 0);
                    break;
            }
            while (1) {
                HuPrcVSleep();
            }
        }
    }
}

void fn_1_9F4(void)
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
    fn_1_BED8(lbl_1_data_428);
    fn_1_C168(lbl_1_data_93C);
}

void fn_1_AF0(void)
{
    s16 i;
    while (1) {
        if (lbl_1_bss_70[0] || omSysExitReq) {
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

u16 lbl_1_data_6E[] = { 1, 2 };

void fn_1_B8C(omObjData *object)
{
    s16 i;
    for (i = 0; i < 1; i++) {
        Vec pos, target, up;
        float x, y, z;

        x = lbl_1_bss_24[i].x;
        y = lbl_1_bss_24[i].y;
        z = lbl_1_bss_24[i].z;

        pos.x = (((sind(y) * cosd(x)) * lbl_1_bss_4[i]) + lbl_1_bss_C[i].x);
        pos.y = (-sind(x) * lbl_1_bss_4[i]) + lbl_1_bss_C[i].y;
        pos.z = ((cosd(y) * cosd(x)) * lbl_1_bss_4[i]) + lbl_1_bss_C[i].z;
        target.x = lbl_1_bss_C[i].x;
        target.y = lbl_1_bss_C[i].y;
        target.z = lbl_1_bss_C[i].z;
        up.x = sind(y) * sind(x);
        up.y = cosd(x);
        up.z = cosd(y) * sind(x);
        Hu3DCameraPosSet(lbl_1_data_6E[i], pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
    }
}

void fn_1_F40(omObjData *object)
{
    Vec pos;
    Vec offset;
    Vec dir;
    Vec y_offset;

    f32 z_rot;
    s8 stick_pos;

    if (!lbl_1_bss_0) {
        fn_1_1B6C();
        return;
    }
    lbl_1_bss_24[0].y += 0.1f * HuPadStkX[0];
    lbl_1_bss_24[0].x += 0.1f * HuPadStkY[0];
    lbl_1_bss_4[0] += HuPadTrigL[0] / 2;
    lbl_1_bss_4[0] -= HuPadTrigR[0] / 2;
    if (HuPadBtnDown[0] & PAD_BUTTON_B) {
        OSReport("%f,%f,%f\n", lbl_1_bss_24[0].x, lbl_1_bss_24[0].y, lbl_1_bss_24[0].z);
        OSReport("%f,%f,%f\n", lbl_1_bss_C[0].x, lbl_1_bss_C[0].y, lbl_1_bss_C[0].z);
        OSReport("%f\n", lbl_1_bss_4[0]);
    }
    if (lbl_1_bss_4[0] < 100.0f) {
        lbl_1_bss_4[0] = 100.0f;
    }
    pos.x = lbl_1_bss_C[0].x + (lbl_1_bss_4[0] * (sind(lbl_1_bss_24[0].y) * cosd(lbl_1_bss_24[0].x)));
    pos.y = (lbl_1_bss_C[0].y + (lbl_1_bss_4[0] * -sind(lbl_1_bss_24[0].x)));
    pos.z = (lbl_1_bss_C[0].z + (lbl_1_bss_4[0] * (cosd(lbl_1_bss_24[0].y) * cosd(lbl_1_bss_24[0].x))));
    offset.x = lbl_1_bss_C[0].x - pos.x;
    offset.y = lbl_1_bss_C[0].y - pos.y;
    offset.z = lbl_1_bss_C[0].z - pos.z;
    dir.x = (sind(lbl_1_bss_24[0].y) * sind(lbl_1_bss_24[0].x));
    dir.y = cosd(lbl_1_bss_24[0].x);
    dir.z = (cosd(lbl_1_bss_24[0].y) * sind(lbl_1_bss_24[0].x));
    z_rot = lbl_1_bss_24[0].z;
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
        lbl_1_bss_C[0].x += 0.05f * (offset.x * stick_pos);
        lbl_1_bss_C[0].y += 0.05f * (offset.y * stick_pos);
        lbl_1_bss_C[0].z += 0.05f * (offset.z * stick_pos);
    }
    VECNormalize(&y_offset, &offset);
    stick_pos = -(HuPadSubStkY[0] & 0xF8);
    if (stick_pos != 0) {
        lbl_1_bss_C[0].x += 0.05f * (offset.x * stick_pos);
        lbl_1_bss_C[0].y += 0.05f * (offset.y * stick_pos);
        lbl_1_bss_C[0].z += 0.05f * (offset.z * stick_pos);
    }
}

void fn_1_1B6C(void)
{
    Vec delta_vec;
    float delta_zoom;
    if (lbl_1_bss_70[0]) {
        return;
    }
    VECSubtract(&lbl_1_bss_64, &lbl_1_bss_24[0], &delta_vec);
    if (VECMag(&delta_vec) > 0.2) {
        VECScale(&delta_vec, &delta_vec, 0.05f);
        VECAdd(&lbl_1_bss_24[0], &delta_vec, &lbl_1_bss_24[0]);
    }
    else {
        lbl_1_bss_24[0] = lbl_1_bss_64;
    }
    VECSubtract(&lbl_1_bss_58, &lbl_1_bss_C[0], &delta_vec);
    if (VECMag(&delta_vec) > 0.2) {
        VECScale(&delta_vec, &delta_vec, 0.05f);
        VECAdd(&lbl_1_bss_C[0], &delta_vec, &lbl_1_bss_C[0]);
    }
    else {
        lbl_1_bss_C[0] = lbl_1_bss_58;
    }
    delta_zoom = lbl_1_bss_54 - lbl_1_bss_4[0];
    if (sqrtf(delta_zoom * delta_zoom) > 0.2) {
        delta_zoom *= 0.05f;
        lbl_1_bss_4[0] += delta_zoom;
    }
    else {
        lbl_1_bss_4[0] = lbl_1_bss_54;
    }
}

void fn_1_1E30(s16 view)
{
    lbl_1_bss_64 = lbl_1_data_0[view].rot;
    lbl_1_bss_58 = lbl_1_data_0[view].pos;
    lbl_1_bss_54 = lbl_1_data_0[view].zoom;
}

void fn_1_1EC0(s16 view)
{
    s16 i;
    lbl_1_bss_24[0] = lbl_1_data_0[view].rot;
    lbl_1_bss_64 = lbl_1_bss_24[0];
    lbl_1_bss_C[0] = lbl_1_data_0[view].pos;
    lbl_1_bss_58 = lbl_1_bss_C[0];
    lbl_1_bss_54 = lbl_1_bss_4[0] = lbl_1_data_0[view].zoom;
    fn_1_B8C(NULL);
}

float fn_1_2368(void)
{
    float delta_zoom = lbl_1_bss_54 - lbl_1_bss_4[0];
    return sqrtf(delta_zoom * delta_zoom);
}
