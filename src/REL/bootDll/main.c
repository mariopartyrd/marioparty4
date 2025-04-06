#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/memory.h"
#include "game/msm.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/thpmain.h"
#include "game/window.h"
#include "game/wipe.h"
#include "math.h"


#include "data_num/title.h"

#define HU_PAD_BTN_ALL (HuPadBtn[0] | HuPadBtn[1] | HuPadBtn[2] | HuPadBtn[3])
#define HU_PAD_BTNDOWN_ALL (HuPadBtnDown[0] | HuPadBtnDown[1] | HuPadBtnDown[2] | HuPadBtnDown[3])
#define HU_PAD_DSTK_ALL (HuPadDStkRep[0] | HuPadDStkRep[1] | HuPadDStkRep[2] | HuPadDStkRep[3])

extern int SystemInitF;

static omObjData *debugOutView;
Process *objman;
Vec debugCamRot[2];
Vec debugCamPos[2];
float debugCamZoom[2];

Vec lbl_1_bss_10;

static s16 demoWinId;

static s16 titleMdlId[3];
static s16 bootGrpId;

s16 lbl_1_bss_4;
#if VERSION_PAL
static BOOL initLanguageF;
#endif
s32 debugCamOnF;

void BootExec(void);
static void UpdateDemoMess(void);
#if VERSION_NTSC
void BootProgExec(void);
#endif
void BootTitleCreate(void);
BOOL BootTitleExec(void);

void *NintendoDataDecode(void);

void ObjectSetup(void)
{
    omOvlHisData *history;
    OSReport("******* Boot ObjectSetup *********\n");
    objman = omInitObjMan(50, 8192);
    debugCamRot[0].x = -67;
    debugCamRot[0].y = 40;
    debugCamRot[0].z = 0;
    debugCamPos[0].x = 260;
    debugCamPos[0].y = -103;
    debugCamPos[0].z = -18;
    debugCamZoom[0] = 2885;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30, 20, 15000, 1.2);
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    HuPrcCreate(BootExec, 100, 12288, 0);
    Hu3DBGColorSet(0, 0, 0);
    history = omOvlHisGet(0);
    omOvlHisChg(0, history->overlay, 1, history->stat);
    #if VERSION_PAL
    if(SystemInitF == FALSE) {
        initLanguageF = FALSE;
    } else {
        initLanguageF = TRUE;
    }
    #endif
}

 #if VERSION_PAL
 s32 LanguageBootGet(void);
 BOOL LanguageMenuExec(void);
 #endif

 void BootExec(void)
 {
     AnimData *data;
     s16 group;
     s16 sprite_nintendo;
     s16 sprite_hudson;
     s16 i;
     OSTick tick_prev;
     Process *curr = HuPrcCurrentGet();
     #if VERSION_NTSC
     if (omovlevtno == 0) {
         BootProgExec();
     }
     #else
     if(SystemInitF == FALSE) {
         GwLanguage = LanguageBootGet();
         if(GwLanguage == -1) {
             if(LanguageMenuExec()) {
                 SystemInitF = TRUE;
             }
         } else {
             GWLanguageSet(GwLanguage);
         }
     }
     #endif
     group = HuSprGrpCreate(2);
     data = HuSprAnimRead(NintendoDataDecode());
     sprite_nintendo = HuSprCreate(data, 0, 0);
     HuSprGrpMemberSet(group, 0, sprite_nintendo);
     HuSprPosSet(group, 0, 288, 240);
     HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
     if (omovlevtno != 0) {
         HuAudSndGrpSetSet(0);
         data = HuSprAnimReadFile(TITLE_HUDSON_ANM);
         sprite_hudson = HuSprCreate(data, 0, 0);
         HuSprGrpMemberSet(group, 1, sprite_hudson);
         HuSprPosSet(group, 1, 288, 240);
         HuSprAttrSet(group, 1, HUSPR_ATTR_DISPOFF);
         HuWinInit(1);
         BootTitleCreate();
         SystemInitF = 1;
     }
     else {
         s16 group_thp;
         BOOL skip_wait;
         float win_size[2];
         s16 sprite_thp;
         for (i = 0; i < 4; i++) {
             GWPlayerCfg[i].pad_idx = i;
         }
         #if VERSION_PAL
         if(SystemInitF) {
             data = HuSprAnimReadFile(TITLE_HUDSON_ANM);
             sprite_hudson = HuSprCreate(data, 0, 0);
             HuSprGrpMemberSet(group, 1, sprite_hudson);
             HuSprPosSet(group, 1, 288, 240);
             HuSprAttrSet(group, 1, HUSPR_ATTR_DISPOFF);
             HuAudSndGrpSetSet(0);
             BootTitleCreate();
             HuWinInit(1);
         }
         #endif
     repeat:
         HuSprAttrReset(group, 0, HUSPR_ATTR_DISPOFF);
         WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
         while (WipeStatGet()) {
             HuPrcVSleep();
         }
         WipeColorSet(255, 255, 255);
         if (!SystemInitF) {
             tick_prev = OSGetTick();
             CharManInit();
             HuWindowInit();
             MGSeqInit();
             HuWinInit(1);
             BootTitleCreate();
             data = HuSprAnimReadFile(TITLE_HUDSON_ANM);
             sprite_hudson = HuSprCreate(data, 0, 0);
             HuSprGrpMemberSet(group, 1, sprite_hudson);
             HuSprPosSet(group, 1, 288, 240);
             HuSprAttrSet(group, 1, HUSPR_ATTR_DISPOFF);
             while (OSTicksToMilliseconds(OSGetTick() - tick_prev) < 3000) {
                 HuPrcVSleep();
             }
         }
         else {
             for (i = 0; i < 180; i++) {
                 #if VERSION_NTSC
                 if (HuPadBtnDown[0] & (PAD_BUTTON_START | PAD_BUTTON_A)) {
                     break;
                 }
                 #else
                 if (initLanguageF && (HuPadBtnDown[0] & (PAD_BUTTON_START | PAD_BUTTON_A))) {
                     break;
                 } 
                 #endif
                 HuPrcVSleep();
             }
         }
         WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
         while (WipeStatGet()) {
             HuPrcVSleep();
         }
         HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
         HuSprAttrReset(group, 1, HUSPR_ATTR_DISPOFF);
         HuPrcSleep(60);
         WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
         while (WipeStatGet()) {
             HuPrcVSleep();
         }
         if (!SystemInitF) {
             void *group_samp;
             tick_prev = OSGetTick();
             group_samp = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(0));
             msmSysLoadGroup(0, group_samp, 0);
             HuMemDirectFree(group_samp);
             while (OSTicksToMilliseconds(OSGetTick() - tick_prev) < 3000) {
                 HuPrcVSleep();
             }
         }
         else {
             for (i = 0; i < 180; i++) {
                 #if VERSION_NTSC
                 if (HuPadBtnDown[0] & (PAD_BUTTON_START | PAD_BUTTON_A)) {
                     break;
                 }
                 #else
                 if (initLanguageF && (HuPadBtnDown[0] & (PAD_BUTTON_START | PAD_BUTTON_A))) {
                     break;
                 } 
                 #endif
                 HuPrcVSleep();
             }
         }
         #if VERSION_PAL
         initLanguageF = TRUE;
         #endif
         WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
         while (WipeStatGet()) {
             HuPrcVSleep();
         }
         tick_prev = OSGetTick();
         if (!SystemInitF) {
             HuAudSndGrpSetSet(0);
             SystemInitF = 1;
         }
         while (OSTicksToMilliseconds(OSGetTick() - tick_prev) < 1000) {
             HuPrcVSleep();
         }
         HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
         HuSprAttrSet(group, 1, HUSPR_ATTR_DISPOFF);
         group_thp = HuSprGrpCreate(1);
         sprite_thp = HuTHPSprCreateVol("movie/opmov_a00.thp", 0, 100, 122);
         HuSprGrpMemberSet(group_thp, 0, sprite_thp);
         HuSprPosSet(group_thp, 0, 288, 240);
         HuWinMesMaxSizeBetGet(win_size, MAKE_MESSID(54, 0), MAKE_MESSID(54, 4));
         demoWinId = HuWinCreate(-10000, 448 - win_size[1], win_size[0], win_size[1], 0);
         HuWinMesSpeedSet(demoWinId, 0);
         HuWinBGTPLvlSet(demoWinId, 0);
         HuWinPriSet(demoWinId, 10);
         HuWinAttrSet(demoWinId, 0x800);
         HuPrcSleep(5);
         WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
         while (WipeStatGet()) {
             HuPrcVSleep();
         }
         skip_wait = FALSE;
         while (!HuTHPEndCheck()) {
             UpdateDemoMess();
             if (HuPadBtnDown[0] & (PAD_BUTTON_START | PAD_BUTTON_A)) {
                 skip_wait = TRUE;
                 break;
             }
             HuPrcVSleep();
         }
         WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
         while (WipeStatGet()) {
             HuPrcVSleep();
         }
         HuWinKill(demoWinId);
         HuTHPClose();
         HuPrcVSleep();
         HuSprGrpKill(group_thp);
         if (!skip_wait) {
             HuPrcSleep(60);
         }
         skip_wait = FALSE;
     }
     if (!BootTitleExec()) {
         HuPrcSleep(60);
         goto repeat;
     }
     WipeColorSet(255, 255, 255);
     HuAudSStreamAllFadeOut(500);
     WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
     while (WipeStatGet()) {
         HuPrcVSleep();
     }
     HuPrcVSleep();
     if (omSysExitReq) {
         omOvlReturnEx(1, 1);
     }
     else {
         omOvlCallEx(OVL_MODESEL, 1, 0, 0);
     }
     for (i = 0; i < 4; i++) {
         GWPlayerCfg[i].character = -1;
     }
     HuPrcEnd();
     do {
         HuPrcVSleep();
     } while (1);
 }

 static s16 demoMessTimeTbl[] = {
     1686,
     1785,
     1850,
     1936,
     1993,
     2097,
     2135,
     2245,
     2258,
     2320,
     -1,
     -1,
 };

 static void UpdateDemoMess(void)
 {
     int frame = HuTHPFrameGet();
     int i;
     for (i = 0; demoMessTimeTbl[i * 2] != -1; i++) {
         if (frame == demoMessTimeTbl[i * 2]) {
             HuWinMesSet(demoWinId, MAKE_MESSID(54, i));
         }
         if (frame == demoMessTimeTbl[(i * 2) + 1]) {
             HuWinHomeClear(demoWinId);
         }
     }
 }

// #if VERSION_NTSC

// static u16 progPosTbl[] = { 236, 313, 353, 313 };

// void BootProgExec(void)
// {
//     s16 i;
//     s16 option;
//     s16 group;
//     s16 sprite;
//     AnimData *data;
//     option = 0;
//     if (OSGetResetCode() != OS_RESET_RESTART) {
//         return;
//     }
//     if (VIGetDTVStatus() != VI_NON_INTERLACE) {
//         OSSetProgressiveMode(OS_PROGRESSIVE_MODE_OFF);
//         return;
//     }
//     if (OSGetProgressiveMode() == OS_PROGRESSIVE_MODE_OFF && !(HU_PAD_BTN_ALL & PAD_BUTTON_B)) {
//         return;
//     }
//     if (OSGetProgressiveMode() == OS_PROGRESSIVE_MODE_ON) {
//         VIConfigure(&GXNtsc480IntDf);
//         VIFlush();
//     }
//     group = HuSprGrpCreate(3);
//     data = HuSprAnimReadFile(TITLE_PROGRESSIVE_CHOOSE_ANM);
//     sprite = HuSprCreate(data, 0, 0);
//     HuSprGrpMemberSet(group, 0, sprite);
//     HuSprPosSet(group, 0, 288, 240);
//     data = HuSprAnimReadFile(TITLE_PROGRESSIVE_CURSOR_ON_ANM);
//     sprite = HuSprCreate(data, 0, 0);
//     HuSprGrpMemberSet(group, 1, sprite);
//     HuSprPosSet(group, 1, progPosTbl[option * 2], progPosTbl[(option * 2) + 1]);
//     data = HuSprAnimReadFile(TITLE_PROGRESSIVE_CURSOR_OFF_ANM);
//     sprite = HuSprCreate(data, 0, 0);
//     HuSprGrpMemberSet(group, 2, sprite);
//     HuSprPosSet(group, 2, progPosTbl[option * 2], progPosTbl[(option * 2) + 1]);
//     HuSprAttrSet(group, 2, HUSPR_ATTR_DISPOFF);
//     WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
//     while (WipeStatGet()) {
//         HuPrcVSleep();
//     }
//     for (i = 0; i < 600; i++) {
//         if (HU_PAD_DSTK_ALL & (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT)) {
//             option ^= 1;
//             HuSprPosSet(group, 1, progPosTbl[option * 2], progPosTbl[(option * 2) + 1]);
//             i = 0;
//         }
//         if (HU_PAD_BTNDOWN_ALL & PAD_BUTTON_A) {
//             HuSprAttrSet(group, 1, HUSPR_ATTR_DISPOFF);
//             HuSprPosSet(group, 2, progPosTbl[option * 2], progPosTbl[(option * 2) + 1]);
//             HuSprAttrReset(group, 2, HUSPR_ATTR_DISPOFF);
//             break;
//         }
//         HuPrcVSleep();
//     }
//     WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
//     while (WipeStatGet()) {
//         HuPrcVSleep();
//     }
//     if (!option) {
//         OSSetProgressiveMode(OS_PROGRESSIVE_MODE_ON);
//         VIConfigure(&GXNtsc480Prog);
//         VIFlush();
//         HuPrcSleep(100);
//     }
//     else {
//         OSSetProgressiveMode(OS_PROGRESSIVE_MODE_OFF);
//     }
//     HuSprGrpKill(group);
//     group = HuSprGrpCreate(1);
//     if (!option) {
//         data = HuSprAnimReadFile(TITLE_PROGRESSIVE_ON_ANM);
//     }
//     else {
//         data = HuSprAnimReadFile(TITLE_PROGRESSIVE_OFF_ANM);
//     }
//     sprite = HuSprCreate(data, 0, 0);
//     HuSprGrpMemberSet(group, 0, sprite);
//     HuSprPosSet(group, 0, 288, 240);
//     WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
//     while (WipeStatGet()) {
//         HuPrcVSleep();
//     }
//     HuPrcSleep(60);
//     for (i = 0; i < 180; i++) {
//         if (HU_PAD_BTNDOWN_ALL & PAD_BUTTON_A) {
//             break;
//         }
//         HuPrcVSleep();
//     }
//     WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
//     while (WipeStatGet()) {
//         HuPrcVSleep();
//     }
//     HuSprGrpKill(group);
//     HuPrcSleep(30);
// }

// #endif

// static u16 debugCamTbl[] = { 1, 2 };

// void DebugCamOutView(omObjData *obj)
// {
//     s16 i;
//     for (i = 0; i < 1; i++) {
//         Vec pos, target, up;
//         float x, y, z;

//         x = debugCamRot[i].x;
//         y = debugCamRot[i].y;
//         z = debugCamRot[i].z;

//         pos.x = (((sind(y) * cosd(x)) * debugCamZoom[i]) + debugCamPos[i].x);
//         pos.y = (-sind(x) * debugCamZoom[i]) + debugCamPos[i].y;
//         pos.z = ((cosd(y) * cosd(x)) * debugCamZoom[i]) + debugCamPos[i].z;
//         target.x = debugCamPos[i].x;
//         target.y = debugCamPos[i].y;
//         target.z = debugCamPos[i].z;
//         up.x = sind(y) * sind(x);
//         up.y = cosd(x);
//         up.z = cosd(y) * sind(x);
//         Hu3DCameraPosSet(debugCamTbl[i], pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
//     }
// }

// void DebugCamUpdate(omObjData *obj)
// {
//     Vec pos;
//     Vec offset;
//     Vec dir;
//     Vec y_offset;

//     f32 z_rot;
//     s8 stick_pos;
    
//     #if VERSION_NTSC
//     if ((HuPadBtnDown[0] & 0x800)) {
//         debugCamOnF = (debugCamOnF) ? 0 : 1;
//     }
//     #endif
//     if (debugCamOnF != 0) {
//         debugCamRot[0].y += 0.1f * HuPadStkX[0];
//         debugCamRot[0].x += 0.1f * HuPadStkY[0];
//         debugCamZoom[0] += HuPadTrigL[0] / 2;
//         debugCamZoom[0] -= HuPadTrigR[0] / 2;
//         if (debugCamZoom[0] < 100.0f) {
//             debugCamZoom[0] = 100.0f;
//         }
//         pos.x = debugCamPos[0].x + (debugCamZoom[0] * (sind(debugCamRot[0].y) * cosd(debugCamRot[0].x)));
//         pos.y = (debugCamPos[0].y + (debugCamZoom[0] * -sind(debugCamRot[0].x)));
//         pos.z = (debugCamPos[0].z + (debugCamZoom[0] * (cosd(debugCamRot[0].y) * cosd(debugCamRot[0].x))));
//         offset.x = debugCamPos[0].x - pos.x;
//         offset.y = debugCamPos[0].y - pos.y;
//         offset.z = debugCamPos[0].z - pos.z;
//         dir.x = (sind(debugCamRot[0].y) * sind(debugCamRot[0].x));
//         dir.y = cosd(debugCamRot[0].x);
//         dir.z = (cosd(debugCamRot[0].y) * sind(debugCamRot[0].x));
//         z_rot = debugCamRot[0].z;
//         y_offset.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * cosd(z_rot))
//             + dir.y * (offset.x * offset.y * (1.0f - cosd(z_rot)) - offset.z * sind(z_rot))
//             + dir.z * (offset.x * offset.z * (1.0f - cosd(z_rot)) + offset.y * sind(z_rot));

//         y_offset.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * cosd(z_rot))
//             + dir.x * (offset.x * offset.y * (1.0f - cosd(z_rot)) + offset.z * sind(z_rot))
//             + dir.z * (offset.y * offset.z * (1.0f - cosd(z_rot)) - offset.x * sind(z_rot));

//         y_offset.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * cosd(z_rot))
//             + (dir.x * (offset.x * offset.z * (1.0 - cosd(z_rot)) - offset.y * sind(z_rot))
//                 + dir.y * (offset.y * offset.z * (1.0 - cosd(z_rot)) + offset.x * sind(z_rot)));

//         VECCrossProduct(&dir, &offset, &offset);
//         VECNormalize(&offset, &offset);
//         stick_pos = (HuPadSubStkX[0] & 0xF8);
//         if (stick_pos != 0) {
//             debugCamPos[0].x += 0.05f * (offset.x * stick_pos);
//             debugCamPos[0].y += 0.05f * (offset.y * stick_pos);
//             debugCamPos[0].z += 0.05f * (offset.z * stick_pos);
//         }
//         VECNormalize(&y_offset, &offset);
//         stick_pos = -(HuPadSubStkY[0] & 0xF8);
//         if (stick_pos != 0) {
//             debugCamPos[0].x += 0.05f * (offset.x * stick_pos);
//             debugCamPos[0].y += 0.05f * (offset.y * stick_pos);
//             debugCamPos[0].z += 0.05f * (offset.z * stick_pos);
//         }
//     }
// }

// void BootTitleCreate(void)
// {
//     s16 model;
//     s16 sprite;
//     AnimData *sprite_data;
//     s16 i;
//     titleMdlId[0] = model = Hu3DModelCreateFile(TITLE_CHAR_HSF);
//     Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
//     Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
//     titleMdlId[1] = model = Hu3DModelCreateFile(TITLE_CUBE_HSF);
//     Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
//     Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
//     titleMdlId[2] = model = Hu3DModelCreateFile(TITLE_SKY_HSF);
//     Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
//     Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
//     Hu3DModelCameraInfoSet(model, 1);
//     Hu3DModelLightInfoSet(model, 1);
//     #if VERSION_NTSC
//     bootGrpId = HuSprGrpCreate(4);
//     #else
//     bootGrpId = HuSprGrpCreate(13);
//     #endif
//     sprite_data = HuSprAnimReadFile(TITLE_BG_ANM);
//     sprite = HuSprCreate(sprite_data, 0, 0);
//     HuSprGrpMemberSet(bootGrpId, 0, sprite);
//     HuSprAttrSet(bootGrpId, 0, HUSPR_ATTR_DISPOFF);
//     HuSprDrawNoSet(bootGrpId, 0, 127);
//     HuSprPosSet(bootGrpId, 0, 288, 240);
//     sprite_data = HuSprAnimReadFile(TITLE_COPYRIGHT_ANM);
//     sprite = HuSprCreate(sprite_data, 1, 0);
//     HuSprGrpMemberSet(bootGrpId, 1, sprite);
//     HuSprAttrSet(bootGrpId, 1, HUSPR_ATTR_DISPOFF);
//     HuSprPosSet(bootGrpId, 1, 288, 420);
//     #if VERSION_NTSC
//     sprite_data = HuSprAnimReadFile(TITLE_PRESS_START_ANM);
//     sprite = HuSprCreate(sprite_data, 2, 0);
//     HuSprGrpMemberSet(bootGrpId, 2, sprite);
//     HuSprAttrSet(bootGrpId, 2, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_LINEAR);
//     HuSprPosSet(bootGrpId, 2, 288, 380);
//     sprite_data = HuSprAnimReadFile(TITLE_LOGO_ANM);
//     sprite = HuSprCreate(sprite_data, 0, 0);
//     HuSprGrpMemberSet(bootGrpId, 3, sprite);
//     HuSprAttrSet(bootGrpId, 3, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_LINEAR);
//     HuSprPosSet(bootGrpId, 3, 288, 200);
//     #else
//     sprite_data = HuSprAnimReadFile(TITLE_LOGO_ANM);
//     sprite = HuSprCreate(sprite_data, 0, 0);
//     HuSprGrpMemberSet(bootGrpId, 2, sprite);
//     HuSprAttrSet(bootGrpId, 2, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_LINEAR);
//     HuSprPosSet(bootGrpId, 2, 288, 200);
//     for(i=0; i<5; i++) {
//         sprite_data = HuSprAnimReadFile(TITLE_PRESS_START_EN_ANM+i);
//         sprite = HuSprCreate(sprite_data, 3+i, 0);
//         HuSprGrpMemberSet(bootGrpId, 3+i, sprite);
//         HuSprAttrSet(bootGrpId, 3+i, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_LINEAR);
//         HuSprPosSet(bootGrpId, 3+i, 288, 340);
//     }
//     for(i=0; i<5; i++) {
//         sprite_data = HuSprAnimReadFile(TITLE_LANGUAGE_EN_ANM+i);
//         sprite = HuSprCreate(sprite_data, 8+i, 0);
//         HuSprGrpMemberSet(bootGrpId, 8+i, sprite);
//         HuSprAttrSet(bootGrpId, 8+i, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_LINEAR);
//         HuSprPosSet(bootGrpId, 8+i, 288, 380);
//     }
//     #endif
// }

// BOOL BootTitleExec(void)
// {
//     float scale;
//     float scale_time;
//     int seNo[32];
//     s16 pressStartMemberNo;
//     s16 languageMemberNo;
//     s16 i;
//     s16 choice;
//     float temp;
//     repeat:
//     Hu3DModelAttrReset(titleMdlId[0], HU3D_ATTR_DISPOFF);
//     Hu3DModelAttrReset(titleMdlId[1], HU3D_ATTR_DISPOFF);
//     HuSprAttrReset(bootGrpId, 0, HUSPR_ATTR_DISPOFF);
//     HuSprAttrReset(bootGrpId, 1, HUSPR_ATTR_DISPOFF);
//     OSReport(">>>>>>>>MSM_SE_SEL_01 %d\n", msmSeGetEntryID(2092, seNo));
//     OSReport(">>>>>>>>SE Num %d\n", msmSeGetNumPlay(0));
//     HuAudSStreamPlay(20);
//     WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
//     while (WipeStatGet()) {
//         HuPrcVSleep();
//     }
//     #if VERSION_NTSC
//     HuSprAttrReset(bootGrpId, 3, HUSPR_ATTR_DISPOFF);
//     for (i = 1; i <= 50; i++) {
//         scale = (cosd(i * 1.8) * 10.0) + 1.0;
//         HuSprScaleSet(bootGrpId, 3, scale, scale);
//         HuSprTPLvlSet(bootGrpId, 3, i / 50.0);
//         HuPrcVSleep();
//     }
//     HuSprAttrReset(bootGrpId, 2, HUSPR_ATTR_DISPOFF);
//     #else
//     HuSprAttrReset(bootGrpId, 2, HUSPR_ATTR_DISPOFF);
//     for (i = 1; i <= 50; i++) {
//         scale = (cosd(i * 1.8) * 10.0) + 1.0;
//         HuSprScaleSet(bootGrpId, 2, scale, scale);
//         HuSprTPLvlSet(bootGrpId, 2, i / 50.0);
//         HuPrcVSleep();
//     }
//     if(GwLanguage == -1) {
//         pressStartMemberNo = 3;
//         languageMemberNo = 8;
//     } else {
//         pressStartMemberNo = GwLanguage+3-1;
//         languageMemberNo = GwLanguage+8-1;
//     }
//     HuSprAttrReset(bootGrpId, pressStartMemberNo, HUSPR_ATTR_DISPOFF);
//     HuSprAttrReset(bootGrpId, languageMemberNo, HUSPR_ATTR_DISPOFF);
//     for(i=1; i<=20; i++) {
//         scale = sind(i*4.5);
//         HuSprScaleSet(bootGrpId, pressStartMemberNo, scale, scale);
//         HuSprScaleSet(bootGrpId, languageMemberNo, scale*0.7, scale*0.7);
//         HuPrcVSleep();
//     }
//     choice = 0;
//     scale_time = 0;
//     #endif
    
//     #if VERSION_NTSC
//     for (i = scale_time = 0; i < 1800; i++) {
//     #else
//     for (i = temp = 0; i < 1800; i++) { 
//     #endif
//         #if VERSION_PAL
//         if((choice == 0 && (HuPadDStkRep[0] & PAD_BUTTON_DOWN)) || (choice != 0 && (HuPadDStkRep[0] & PAD_BUTTON_UP))) {
//             HuAudFXPlay(0);
//             for(i=1; i<=10; i++) {
//                 scale = ((1-(i/10.0))*(((cosd(scale_time)*0.1)+0.9)-0.7))+0.7;
//                 if(choice == 0) {
//                     HuSprScaleSet(bootGrpId, pressStartMemberNo, scale, scale);
//                 } else {
//                     HuSprScaleSet(bootGrpId, languageMemberNo, scale, scale);
//                 }
//                 scale = ((1-(i/10.0))*(((cosd(scale_time/3.0)*0.05)+0.65)-1.0))+1.0;
//                 if(choice == 0) {
//                     HuSprScaleSet(bootGrpId, languageMemberNo, scale, scale);
//                 } else {
//                     HuSprScaleSet(bootGrpId, pressStartMemberNo, scale, scale);
//                 }
//                 HuPrcVSleep();
//             }
//             choice ^= 1;
//             scale_time = 0;
//         }
//         if (HuPadBtnDown[0] & (PAD_BUTTON_START|PAD_BUTTON_A)) {
//             if(choice == 0) {
//                 s32 ret = HuAudFXPlay(2092);
//                 if (ret < 0) {
//                     OSReport(">>>>>Error %d\n", ret);
//                 }
//                 HuSprAttrSet(bootGrpId, 2, HUSPR_ATTR_DISPOFF);
//                 return 1;
//             } else {
//                 HuAudFXPlay(1);
//                 HuAudSStreamAllFadeOut(500);
//                 WipeColorSet(255, 255, 255);
//                 WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
//                 while (WipeStatGet()) {
//                     HuPrcVSleep();
//                 }
//                 Hu3DModelAttrSet(titleMdlId[0], HU3D_ATTR_DISPOFF);
//                 Hu3DModelAttrSet(titleMdlId[1], HU3D_ATTR_DISPOFF);
//                 Hu3DModelAttrSet(titleMdlId[2], HU3D_ATTR_DISPOFF);
//                 HuSprAttrSet(bootGrpId, 0, HUSPR_ATTR_DISPOFF);
//                 HuSprAttrSet(bootGrpId, 1, HUSPR_ATTR_DISPOFF);
//                 HuSprAttrSet(bootGrpId, 2, HUSPR_ATTR_DISPOFF);
//                 HuSprAttrSet(bootGrpId, 2, HUSPR_ATTR_DISPOFF);
//                 for(i=0; i<5; i++) {
//                     HuSprAttrSet(bootGrpId, i+3, HUSPR_ATTR_DISPOFF);
//                 }
//                 for(i=0; i<5; i++) {
//                     HuSprAttrSet(bootGrpId, i+8, HUSPR_ATTR_DISPOFF);
//                 }
//                 LanguageMenuExec();
//                 Hu3DModelCameraInfoSet(titleMdlId[2], 1);
//                 Hu3DModelLightInfoSet(titleMdlId[2], 1);
//                 HuWinInit(1);
//                 goto repeat;
//             }
//         }
//         scale = (cosd(scale_time) * 0.1) + 0.9;
//         if(choice == 0) {
//             HuSprScaleSet(bootGrpId, pressStartMemberNo, scale, scale);
//         } else {
//             HuSprScaleSet(bootGrpId, languageMemberNo, scale, scale);
//         }
//         scale = (cosd(scale_time/3.0) * 0.05) + 0.65;
//         if(choice == 0) {
//             HuSprScaleSet(bootGrpId, languageMemberNo, scale, scale);
//         } else {
//             HuSprScaleSet(bootGrpId, pressStartMemberNo, scale, scale);
//         }
//         scale_time += 5;
//         HuPrcVSleep();
//         #else
//         if (i <= 10) {
//             HuSprTPLvlSet(bootGrpId, 2, i / 10.0);
//         }
//         if (HuPadBtnDown[0] & PAD_BUTTON_START) {
//             s32 ret = HuAudFXPlay(2092);
//             if (ret < 0) {
//                 OSReport(">>>>>Error %d\n", ret);
//             }
//             HuSprAttrSet(bootGrpId, 2, HUSPR_ATTR_DISPOFF);
//             return 1;
//         }
//         scale = (sind(i * scale_time) * 0.1) + 0.9;
//         scale_time += 0.05;
//         if (scale_time > 5) {
//             scale_time = 5;
//         }
//         HuSprScaleSet(bootGrpId, 2, scale, scale);
//         HuPrcVSleep();
//         #endif
        
//     }
//     WipeColorSet(255, 255, 255);
//     WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
//     while (WipeStatGet()) {
//         HuPrcVSleep();
//     }
//     Hu3DModelAttrSet(titleMdlId[0], HU3D_ATTR_DISPOFF);
//     Hu3DModelAttrSet(titleMdlId[1], HU3D_ATTR_DISPOFF);
//     Hu3DModelAttrSet(titleMdlId[2], HU3D_ATTR_DISPOFF);
//     #if VERSION_NTSC
//     HuSprAttrSet(bootGrpId, 0, HUSPR_ATTR_DISPOFF);
//     HuSprAttrSet(bootGrpId, 1, HUSPR_ATTR_DISPOFF);
//     HuSprAttrSet(bootGrpId, 2, HUSPR_ATTR_DISPOFF);
//     HuSprAttrSet(bootGrpId, 3, HUSPR_ATTR_DISPOFF);
//     #else
//     HuSprAttrSet(bootGrpId, 0, HUSPR_ATTR_DISPOFF);
//     HuSprAttrSet(bootGrpId, 1, HUSPR_ATTR_DISPOFF);
//     HuSprAttrSet(bootGrpId, 2, HUSPR_ATTR_DISPOFF);
//     for(i=0; i<5; i++) {
//         HuSprAttrSet(bootGrpId, i+3, HUSPR_ATTR_DISPOFF);
//     }
//     for(i=0; i<5; i++) {
//         HuSprAttrSet(bootGrpId, i+8, HUSPR_ATTR_DISPOFF);
//     }
//     #endif
//     return 0;
// }

// #include "nintendoData.inc"

// void *NintendoDataDecode(void)
// {
//     u32 *src = (u32 *)nintendoData;
//     u32 size = *src++;
//     void *dst = HuMemDirectMalloc(HEAP_DATA, size);
//     int decode_type = *src++;
//     if(dst) {
//         HuDecodeData(src, dst, size, decode_type);
//     }
//     return dst;
// }
