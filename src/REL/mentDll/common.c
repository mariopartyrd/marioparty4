#include "REL/mentDll.h"
#include "ext_math.h"
#include "game/board/tutorial.h"
#include "game/hu3d.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "math.h"

static HUPROCESS *objman;
// TODO: unknown type
extern s32 gameConfigs[];

s32 menuSoundFXTbl[][4] = {
    { 0x00000037, 0x00000038, 0x00000036, 0x00000039 },
    { 0x00000043, 0x00000045, 0x00000044, 0x00000043 },
    { 0x00000040, 0x00000042, 0x00000041, 0x00000040 },
    { 0x0000004B, 0x0000004D, 0x0000004C, 0x0000004B },
    { 0x00000046, 0x00000048, 0x00000047, 0x00000046 },
    { 0x0000003E, 0x0000003F, 0x0000003E, 0x0000003E },
    { 0x0000003A, 0x0000003B, 0x0000003C, 0xFFFFFFFF },
};

static s32 availControlsWin = -1;

// char lbl_1_data_74[] = ">>>>>>>>>> CAMERA DATA <<<<<<<<<<";
// char lbl_1_data_96[] = "CENTER : %.2f, %.2f, %.2f";
// char lbl_1_data_B0[] = "ROT    : %.2f, %.2f, %.2f";
// char lbl_1_data_CA[] = "ZOOM   : %.2f";

extern s32 _prolog();
extern void _epilog();
void ObjectSetup(void);
void destroyAvailControlsWin(s32);
typedef void (*VoidFunc)(void);
extern const VoidFunc _ctors[];
extern const VoidFunc _dtors[];

void fn_1_0(OMOBJ *arg0)
{
    if (WipeStatGet() == 0) {
        arg0->objFunc = NULL;
        omOvlReturnEx(1, 1);
    }
}

void fn_1_4C(OMOBJ *object)
{
    if (omSysExitReq != 0) {
        object->objFunc = fn_1_0;
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    }
}

s32 _prolog(void)
{
    const VoidFunc *ctors = _ctors;
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
    ObjectSetup();
    return 0;
}

void _epilog(void)
{
    const VoidFunc *dtors = _dtors;
    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}

void ObjectSetup(void)
{
    _ClearFlag(0x1000BU);
    boardTutorialF = 0;
    objman = omInitObjMan(0x3E, 0x2000);
    omGameSysInit(objman);
    gameConfigs[0] = omovlevtno;
    gameConfigs[1] = omovlstat;
    MenuMain(objman);
    omAddObjEx(objman, 0x2000, 0U, 0U, -1, fn_1_4C);
}

f32 LerpClamped(f32 start, f32 end, f32 weight, f32 max_weight)
{
    if (max_weight <= weight) {
        return end;
    }
    return start + ((weight / max_weight) * (end - start));
}

f32 WeightedBlend(f32 start, f32 end, f32 weight)
{
    return (end + (start * (weight - 1.0f))) / weight;
}

// fn_1_254
f32 CosEaseClamped(f32 start, f32 end, f32 progress, f32 maxProgress)
{
    if (progress >= maxProgress) {
        return end;
    }
    return (start + ((end - start) * (1.0 - cosd((90.0f / maxProgress) * progress))));
}

// fn_1_32C
f32 SinEaseClamped(f32 start, f32 end, f32 progress, f32 maxProgress)
{
    if (progress >= maxProgress) {
        return end;
    }
    return start + (end - start) * sind((90.0f / maxProgress) * progress);
}

f32 SinOscillateClamped(f32 start, f32 end, f32 progress, f32 maxProgress)
{
    if (progress >= maxProgress) {
        return start;
    }
    return (start + ((end - start) * sind((360.0f / maxProgress) * progress)));
}

void MenuPrcSleep(s32 time)
{
    HuPrcSleep(time);
}

void MenuPrcVSleep(void)
{
    HuPrcVSleep();
}

void MenuPrcSleepLoop(void)
{
    while (1) {
        HuPrcVSleep();
    }
}

void MenuLightInit(void)
{
    s32 lightId = 0;

    lightId = Hu3DGLightCreate(0.0f, 700.0f, 1200.0f, 0.0f, -1.0f, 0.0f, 255, 255, 255);
    Hu3DGLightPosAimSet(lightId, 0.0f, 700.0f, 1200.0f, 0.0f, 0.0f, 640.0f);
    Hu3DGLightInfinitytSet(lightId);
}

void MenuShadowInit(s32 eventNo)
{
    Vec shadowPos = { 0.0f, 3000.0f, 800.0f };
    Vec shadowTarget = { 0.0f, 0.0f, 640.0f };
    Vec shadowUp = { 0.0f, 1.0f, 0.0f };

    if (eventNo == 3) {
        shadowPos.x = shadowTarget.x = 1200.0f;
    }
    Hu3DShadowCreate(45.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&shadowPos, &shadowUp, &shadowTarget);
}

void MenuWinInit(void)
{
    HuWinInit(1);
}

static void WinTransition(s32 winId, f32 centerX, f32 centerY, s32 toSmallF)
{
    WindowData *winPtr;
    f32 smallPosX;
    f32 smallPosY;
    f32 winPosX;
    f32 winPosY;
    f32 width;
    f32 height;
    f32 smallScaleX;
    f32 smallScaleY;
    f32 posX;
    f32 posY;
    f32 scaleX;
    f32 scaleY;
    s32 time;

    winPtr = (WindowData *)&winData[winId];
    winPosX = winPtr->pos_x;
    winPosY = winPtr->pos_y;
    width = winPtr->w;
    height = winPtr->h;
    smallPosX = winPosX + (width * centerX);
    smallScaleX = 4.0f / width;

    // adjust horizontal position
    if (((4.0f + smallPosX) - (winPosX + width)) >= 0.0f) {
        smallPosX = (winPosX + width) - 4.0f;
    }
    else {
        if ((winPosX - (smallPosX - 2.0f)) >= 0.0f) {
            smallPosX = winPosX;
        }
        else {
            smallPosX = smallPosX - 2.0f;
        }
    }

    smallPosY = winPosY + (height * centerY);
    smallScaleY = 4.0f / height;

    // adjust vertical position
    if (((4.0f + smallPosY) - (winPosY + height)) >= 0.0f) {
        smallPosY = (winPosY + height) - 4.0f;
    }
    else {
        if ((winPosY - (smallPosY - 2.0f)) >= 0.0f) {
            smallPosY = winPosY;
        }
        else {
            smallPosY = smallPosY - 2.0f;
        }
    }

    if (toSmallF != 0) {
        HuWinPosSet(winId, smallPosX, smallPosY);
        HuWinScaleSet(winId, smallScaleX, smallScaleY);
        posX = smallPosX;
        scaleX = smallScaleX;
        posY = smallPosY;
        scaleY = smallScaleY;
    }
    else {
        HuWinPosSet(winId, winPosX, winPosY);
        HuWinScaleSet(winId, 1.0f, 1.0f);
        posX = winPosX;
        scaleX = 1.0f;
        posY = winPosY;
        scaleY = 1.0f;
    }
    HuWinDispOn(winId);

    // animation loop
    for (time = 0; time <= 15; ++time) {
        HuPrcVSleep();
        if (toSmallF != 0) {
            if (time <= 0xA) {
                posX = (time >= 10.0f) ? winPosX : (f32)(smallPosX + ((winPosX - smallPosX) * sind(9.0f * time)));
                scaleX = (time >= 10.0f) ? 1.0f : (f32)(smallScaleX + ((1.0f - smallScaleX) * sind(9.0f * time)));
            }
            else {
                posY = ((time - 0xA) >= 5.0f) ? winPosY : (f32)(smallPosY + ((winPosY - smallPosY) * sind(18.0f * (time - 0xA))));
                scaleY = ((time - 0xA) >= 5.0f) ? 1.0f : (f32)(smallScaleY + ((1.0f - smallScaleY) * sind(18.0f * (time - 0xA))));
            }
        }
        else if (time <= 0xA) {
            posY = (time >= 10.0f) ? smallPosY : (f32)(winPosY + ((smallPosY - winPosY) * sind(9.0f * time)));
            scaleY = (time >= 10.0f) ? smallScaleY : (f32)(1.0 + ((smallScaleY - 1.0f) * sind(9.0f * time)));
        }
        else {
            posX = ((time - 0xA) >= 5.0f) ? smallPosX : (f32)(winPosX + ((smallPosX - winPosX) * sind(18.0f * (time - 0xA))));
            scaleX = ((time - 0xA) >= 5.0f) ? smallScaleX : (f32)(1.0 + ((smallScaleX - 1.0f) * sind(18.0f * (time - 0xA))));
        }
        HuWinPosSet(winId, posX, posY);
        HuWinScaleSet(winId, scaleX, scaleY);
    }

    if (toSmallF != 0) {
        HuWinPosSet(winId, winPosX, winPosY);
        HuWinScaleSet(winId, 1.0f, 1.0f);
    }
    else {
        HuWinPosSet(winId, smallPosX, smallPosY);
        HuWinScaleSet(winId, smallScaleX, smallScaleY);
    }
    HuPrcVSleep();
}

static s32 OpenWin(s32 xAlign, s32 y, s32 width, s32 height, f32 centerX, f32 centerY, s32 mode, s32 arg4, s32 messageId)
{
    f32 winSize[2];
    s32 winId;

    if (mode % 2 == 0) {
        width = (width * 0x15) + 0x10;
        height = (height * 0x1A) + 0x10;
        y = (445.0f - height);
        switch (xAlign) {
            case -1:
                xAlign = 0x10;
                break;
            case 0:
                xAlign = (1.0f + ((576.0f - width) / 2));
                break;
            case 1:
                xAlign = (556.0f - width);
                break;
        }
    }
    else {
        HuWinMesMaxSizeGet(1, winSize, messageId);
        width = winSize[0];
        height = winSize[1];
        xAlign = (556.0f - width);
        y = (445.0f - height);
    }
    winId = HuWinExCreateStyled(xAlign, y, width, height, -1, 1);
    if (mode == 1) {
        HuWinAttrSet(winId, 0x10U);
    }
    HuWinMesPalSet(winId, 7U, 0U, 0U, 0U);
    winData[winId].active_pad = 1;
    WinTransition(winId, centerX, centerY, 1);
    return winId;
}

s32 OpenWindowBottom(s32 xAlign, s32 arg1, s32 arg2)
{
    return OpenWin(xAlign, 0, 0x15, 2, 0.5f, 0.5f, 2, 0, 0);
}

static void DestroyWinCenterVanish(s32 winId, f32 centerX, f32 centerY)
{
    HuWinMesSet(winId, 0x250004);
    HuPrcVSleep();
    WinTransition(winId, centerX, centerY, 0);
    HuWinExCleanup(winId);
}

void DestroyWin(s32 winId)
{
    HuWinMesSet(winId, 0x250004);
    HuPrcVSleep();
    WinTransition(winId, 0.5f, 0.5f, 0);
    HuWinExCleanup(winId);
}

void WinWaitMess(s32 winId, s32 sleepDur)
{
    if ((sleepDur == -999) || (sleepDur == 0)) {
        return;
    }
    if (sleepDur == -1000) {
        do {
            HuPrcVSleep();
        } while (HuWinStatGet(winId) == 1);
        return;
    }
    if (sleepDur > 0) {
        HuPrcSleep(sleepDur);
        return;
    }
    HuWinComKeyReset();
    HuWinMesWait(winId);
    HuWinComKeyReset();
}

static void WinWaitAllMess(s32 winId, s32 mess, s32 maxWaits, s32 sleepDur)
{
    s32 i;
    s32 temp_r28 = 0;
    s32 var_r30 = 0;

    (void)winId;

    temp_r28 = HuWinKeyWaitNumGet(mess);
    if ((maxWaits == -1) || (maxWaits >= (s32)(temp_r28 - 1))) {
        maxWaits = temp_r28 - 1;
    }
    HuWinComKeyReset();
    for (i = 0; i < temp_r28; i++) {
        var_r30 = 0;
        do {
            HuPrcVSleep();
        } while (HuWinStatGet(winId) != 1);

        if (i == maxWaits) {
            HuWinAttrSet(winId, 0x400);
            var_r30 = 1;
        }

        while (1) {
            HuPrcVSleep();
            if (var_r30 != 0) {
                if (var_r30 == 1 && HuWinStatGet(winId) != 1) {
                    var_r30 = 2;
                }
                else if (var_r30 == 2) {
                    HuPrcSleep(sleepDur);
                    HuWinAttrReset(winId, 0x400);
                    HuWinKeyWaitEntry(winId);
                    break;
                }
            }
            else if (HuWinStatGet(winId) != 1) {
                break;
            }
        }
    }
    HuWinComKeyReset();
    HuWinMesWait(winId);
    HuWinComKeyReset();
    HuWinComKeyReset();
}

static s32 WinGetChoice(s32 winId, s32 startChoice)
{
    s32 choice;

    HuWinComKeyReset();
    choice = HuWinChoiceGet(winId, startChoice);
    HuWinComKeyReset();
    return choice;
}

void MenuWinInsertMesSet(s32 winId, s32 mess, s32 index)
{
    HuWinInsertMesSet(winId, mess, index);
}

void WinSetMessAndWait(s32 winId, s32 mess, s32 maxWaits, s32 sleepDur)
{
    if (sleepDur == -999) {
        HuWinMesSpeedSet(winId, 0);
    }
    else {
        HuWinMesSpeedSet(winId, 1);
    }
    HuWinMesSet(winId, mess);
    if (maxWaits == -1) {
        if ((sleepDur != -999) && (sleepDur != 0)) {
            if (sleepDur == -1000) {
                do {
                    HuPrcVSleep();
                } while (HuWinStatGet(winId) == 1);
                return;
            }
            if (sleepDur > 0) {
                HuPrcSleep(sleepDur);
                return;
            }
            HuWinComKeyReset();
            HuWinMesWait(winId);
            HuWinComKeyReset();
        }
    }
    else {
        WinWaitAllMess(winId, mess, maxWaits, sleepDur);
    }
}

s32 OpenConfirmDlgYesDef(s32 mess, s32 mode, s32 arg2)
{
    s32 winId;
    s32 choice = 0;

    winId = OpenWin(0, 0, 0, 0, 0.5f, 0.5f, mode, 0, mess);
    HuWinMesSet(winId, mess);
    choice = WinGetChoice(winId, 0);
    DestroyWinCenterVanish(winId, 0.5f, 0.5f);
    return choice;
}

s32 OpenConfirmDlgNoDef(s32 mess, s32 mode, s32 arg2)
{
    s32 winId;
    s32 choice = 0;

    winId = OpenWin(0, 0, 0, 0, 0.5f, 0.5f, mode, 0, mess);
    HuWinMesSet(winId, mess);
    choice = WinGetChoice(winId, 1);
    DestroyWinCenterVanish(winId, 0.5f, 0.5f);
    return choice;
}

s32 OpenAvailControlsWin(s32 mess)
{
    f32 winSize[2];
    f32 x;
    f32 y;
    s32 ret;
    f32 sizeX;
    f32 sizeY;

    HuWinMesMaxSizeGet(1, winSize, mess);
    sizeX = winSize[0];
    sizeY = winSize[1];
    x = (576.0f - sizeX) / 2;
    y = 385.0f - sizeY;
    if (availControlsWin == -1) {
        availControlsWin = ret = HuWinExCreateStyled(x, y, sizeX, sizeY, -1, 1);
    }
    else {
        destroyAvailControlsWin(0);
        availControlsWin = ret = HuWinExCreateStyled(x, y, sizeX, sizeY, -1, 1);
    }
    HuWinBGTPLvlSet(availControlsWin, 0.0f);
    HuWinMesSet(availControlsWin, mess);
    HuWinMesSpeedSet(availControlsWin, 0);
    HuWinDispOn(availControlsWin);
    return availControlsWin;
}

void destroyAvailControlsWin(s32 arg0)
{
    if (availControlsWin != -1) {
        HuWinExCleanup(availControlsWin);
        availControlsWin = -1;
    }
}

void fn_1_236C(f32 arg9)
{
    MenuCamera *menuCameraRef = &menuCamera;

    if ((HuPadBtn[0] & 0x200)) {
        if ((HuPadBtn[0] & 0x20)) {
            menuCameraRef->center.z = menuCameraRef->center.z - (HuPadStkY[0] / 10.0f);
        }
        else {
            menuCameraRef->center.x += HuPadStkX[0] / 10.0f;
            menuCameraRef->center.y = menuCameraRef->center.y + (HuPadStkY[0] / 10.0f);
        }
    }
    if ((HuPadBtn[0] & 0x800)) {
        menuCameraRef->rot.x -= HuPadStkY[0] / 100.0f;
        menuCameraRef->rot.y = menuCameraRef->rot.y + (HuPadStkX[0] / 100.0f);
        if (menuCameraRef->rot.x < 0.0f) {
            menuCameraRef->rot.x += 360.0f;
        }

        if (menuCameraRef->rot.x >= 360.0f) {
            menuCameraRef->rot.x -= 360.0f;
        }
        if (menuCameraRef->rot.y < 0.0f) {
            menuCameraRef->rot.y += 360.0f;
        }
        if (menuCameraRef->rot.y >= 360.0f) {
            menuCameraRef->rot.y -= 360.0f;
        }
    }
    if ((HuPadBtn[0] & 0x400)) {
        menuCameraRef->zoom = menuCameraRef->zoom - (HuPadStkY[0] / 10.0f);
    }
    print8(0x18, 0x28, 1.0f, ">>>>>>>>>> CAMERA DATA <<<<<<<<<<");
    print8(0x18, 0x32, 1.0f, "CENTER : %.2f, %.2f, %.2f", menuCameraRef->center.x, menuCameraRef->center.y, menuCameraRef->center.z);
    print8(0x18, 0x3C, 1.0f, "ROT    : %.2f, %.2f, %.2f", menuCameraRef->rot.x, menuCameraRef->rot.y, menuCameraRef->rot.z);
    print8(0x18, 0x46, 1.0f, "ZOOM   : %.2f", menuCameraRef->zoom);
}

static void MenuSetupCamera(OMOBJ *obj)
{
    MenuCamera *menuCameraRef = &menuCamera;
    if (menuCameraRef->func != NULL) {
        menuCameraRef->func();
    }
    Center.x = menuCameraRef->center.x;
    Center.y = menuCameraRef->center.y;
    Center.z = menuCameraRef->center.z;
    CRot.x = menuCameraRef->rot.x;
    CRot.y = menuCameraRef->rot.y;
    CRot.z = menuCameraRef->rot.z;
    CZoom = menuCameraRef->zoom;
}

void moveCameraWithMethod(void (*cameraMoveMethod)(void))
{
    MenuCameraSnapshot(&menuCamera);
    menuCamera.func = cameraMoveMethod;
}

void MenuCameraInit(HUPROCESS *objman, void (*cameraIntroMethod)(void))
{
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 42.0f, 20.0f, 5000.0f, 1.2f);
    menuCamera.func = cameraIntroMethod;
    menuCamera.func2 = &fn_1_236C;
    omAddObjEx(objman, 0x7FDA, 0U, 0U, -1, omOutView);
    omAddObjEx(objman, 0x7FD9, 0U, 0U, -1, MenuSetupCamera);
}

void fn_1_2964(MenuCamera *arg0)
{
    arg0->center.x = arg0->prevCenter.x;
    arg0->center.y = arg0->prevCenter.y;
    arg0->center.z = arg0->prevCenter.z;
    arg0->rot.x = arg0->prevRot.x;
    arg0->rot.y = arg0->prevRot.y;
    arg0->rot.z = arg0->prevRot.z;
    arg0->zoom = arg0->prevZoom;
}

void MenuCameraSnapshot(MenuCamera *menuCamera)
{
    menuCamera->frames = 0.0f;
    menuCamera->prevCenter.x = menuCamera->center.x;
    menuCamera->prevCenter.y = menuCamera->center.y;
    menuCamera->prevCenter.z = menuCamera->center.z;
    menuCamera->prevRot.x = menuCamera->rot.x;
    menuCamera->prevRot.y = menuCamera->rot.y;
    menuCamera->prevRot.z = menuCamera->rot.z;
    menuCamera->prevZoom = menuCamera->zoom;
}

static inline f32 SmoothInterpolate(f32 start, f32 end, f32 weight)
{
    return (end + start * (weight - 1.0f)) / weight;
}

void fn_1_29E4(MenuCamera *arg0, MenuCamera *arg1, f32 arg8)
{
    arg0->center.x = SmoothInterpolate(arg0->center.x, arg1->prevCenter.x, arg8);
    arg0->center.y = SmoothInterpolate(arg0->center.y, arg1->prevCenter.y, arg8);
    arg0->center.z = SmoothInterpolate(arg0->center.z, arg1->prevCenter.z, arg8);
    arg0->rot.x = SmoothInterpolate(arg0->rot.x, arg1->prevRot.x, arg8);
    arg0->rot.y = SmoothInterpolate(arg0->rot.y, arg1->prevRot.y, arg8);
    arg0->rot.z = SmoothInterpolate(arg0->rot.z, arg1->prevRot.z, arg8);
    arg0->zoom = SmoothInterpolate(arg0->zoom, arg1->prevZoom, arg8);
}

void fn_1_2C50(MenuCamera *arg0, f32 arg8)
{
    arg0->center.x = SmoothInterpolate(arg0->center.x, arg0->prevCenter.x, arg8);
    arg0->center.y = SmoothInterpolate(arg0->center.y, arg0->prevCenter.y, arg8);
    arg0->center.z = SmoothInterpolate(arg0->center.z, arg0->prevCenter.z, arg8);
    arg0->rot.x = SmoothInterpolate(arg0->rot.x, arg0->prevRot.x, arg8);
    arg0->rot.y = SmoothInterpolate(arg0->rot.y, arg0->prevRot.y, arg8);
    arg0->rot.z = SmoothInterpolate(arg0->rot.z, arg0->prevRot.z, arg8);
    arg0->zoom = SmoothInterpolate(arg0->zoom, arg0->prevZoom, arg8);
}

inline f32 LinearInterpolation(f32 start, f32 end, f32 current, f32 total)
{
    if (total <= current) {
        return end;
    }
    else {
        return start + ((current / total) * (end - start));
    }
}

void fn_1_2EBC(MenuCamera *arg0, MenuCamera *arg1, f32 arg8, f32 arg9)
{
    arg1->prevCenter.x = LinearInterpolation(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = LinearInterpolation(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = LinearInterpolation(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = LinearInterpolation(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = LinearInterpolation(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = LinearInterpolation(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = LinearInterpolation(arg0->prevZoom, arg1->zoom, arg8, arg9);
}

void fn_1_3138(MenuCamera *arg0, MenuCamera *arg1, f32 arg8, f32 arg9)
{
    arg1->prevCenter.x = LinearInterpolation(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = LinearInterpolation(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = LinearInterpolation(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = LinearInterpolation(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = LinearInterpolation(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = LinearInterpolation(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = LinearInterpolation(arg0->prevZoom, arg1->zoom, arg8, arg9);

    arg0->center.x = arg1->prevCenter.x;
    arg0->center.y = arg1->prevCenter.y;
    arg0->center.z = arg1->prevCenter.z;
    arg0->rot.x = arg1->prevRot.x;
    arg0->rot.y = arg1->prevRot.y;
    arg0->rot.z = arg1->prevRot.z;
    arg0->zoom = arg1->prevZoom;
}

void fn_1_33EC(MenuCamera *arg0, MenuCamera *arg1, f32 arg8, f32 arg9, f32 argA)
{
    arg1->prevCenter.x = LinearInterpolation(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = LinearInterpolation(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = LinearInterpolation(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = LinearInterpolation(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = LinearInterpolation(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = LinearInterpolation(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = LinearInterpolation(arg0->prevZoom, arg1->zoom, arg8, arg9);

    arg0->center.x = SmoothInterpolate(arg0->center.x, arg1->prevCenter.x, argA);
    arg0->center.y = SmoothInterpolate(arg0->center.y, arg1->prevCenter.y, argA);
    arg0->center.z = SmoothInterpolate(arg0->center.z, arg1->prevCenter.z, argA);

    arg0->rot.x = SmoothInterpolate(arg0->rot.x, arg1->prevRot.x, argA);
    arg0->rot.y = SmoothInterpolate(arg0->rot.y, arg1->prevRot.y, argA);
    arg0->rot.z = SmoothInterpolate(arg0->rot.z, arg1->prevRot.z, argA);

    arg0->zoom = SmoothInterpolate(arg0->zoom, arg1->prevZoom, argA);
}

void fn_1_3858(MenuCamera *arg0, MenuCamera *arg1, f32 arg8, f32 arg9)
{
    arg1->prevCenter.x = SinEaseClamped(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = SinEaseClamped(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = SinEaseClamped(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = SinEaseClamped(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = SinEaseClamped(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = SinEaseClamped(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = SinEaseClamped(arg0->prevZoom, arg1->zoom, arg8, arg9);
}

void fn_1_3CAC(MenuCamera *arg0, MenuCamera *arg1, f32 arg8, f32 arg9)
{
    arg1->prevCenter.x = SinEaseClamped(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = SinEaseClamped(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = SinEaseClamped(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = SinEaseClamped(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = SinEaseClamped(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = SinEaseClamped(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = SinEaseClamped(arg0->prevZoom, arg1->zoom, arg8, arg9);

    arg0->center.x = arg1->prevCenter.x;
    arg0->center.y = arg1->prevCenter.y;
    arg0->center.z = arg1->prevCenter.z;

    arg0->rot.x = arg1->prevRot.x;
    arg0->rot.y = arg1->prevRot.y;
    arg0->rot.z = arg1->prevRot.z;

    arg0->zoom = arg1->prevZoom;
}

void MenuCameraSinEaseFollow(MenuCamera *srcCamera, MenuCamera *targetCamera, f32 progress, f32 maxProgress, f32 weight)
{
    targetCamera->prevCenter.x = SinEaseClamped(srcCamera->prevCenter.x, targetCamera->center.x, progress, maxProgress);
    targetCamera->prevCenter.y = SinEaseClamped(srcCamera->prevCenter.y, targetCamera->center.y, progress, maxProgress);
    targetCamera->prevCenter.z = SinEaseClamped(srcCamera->prevCenter.z, targetCamera->center.z, progress, maxProgress);

    targetCamera->prevRot.x = SinEaseClamped(srcCamera->prevRot.x, targetCamera->rot.x, progress, maxProgress);
    targetCamera->prevRot.y = SinEaseClamped(srcCamera->prevRot.y, targetCamera->rot.y, progress, maxProgress);
    targetCamera->prevRot.z = SinEaseClamped(srcCamera->prevRot.z, targetCamera->rot.z, progress, maxProgress);

    targetCamera->prevZoom = SinEaseClamped(srcCamera->prevZoom, targetCamera->zoom, progress, maxProgress);

    srcCamera->center.x = SmoothInterpolate(srcCamera->center.x, targetCamera->prevCenter.x, weight);
    srcCamera->center.y = SmoothInterpolate(srcCamera->center.y, targetCamera->prevCenter.y, weight);
    srcCamera->center.z = SmoothInterpolate(srcCamera->center.z, targetCamera->prevCenter.z, weight);

    srcCamera->rot.x = SmoothInterpolate(srcCamera->rot.x, targetCamera->prevRot.x, weight);
    srcCamera->rot.y = SmoothInterpolate(srcCamera->rot.y, targetCamera->prevRot.y, weight);
    srcCamera->rot.z = SmoothInterpolate(srcCamera->rot.z, targetCamera->prevRot.z, weight);

    srcCamera->zoom = SmoothInterpolate(srcCamera->zoom, targetCamera->prevZoom, weight);
}

void fn_1_4790(MenuCamera *arg0, MenuCamera *arg1, f32 arg8, f32 arg9)
{
    arg1->prevCenter.x = CosEaseClamped(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = CosEaseClamped(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = CosEaseClamped(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = CosEaseClamped(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = CosEaseClamped(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = CosEaseClamped(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = CosEaseClamped(arg0->prevZoom, arg1->zoom, arg8, arg9);
}

void fn_1_4C54(MenuCamera *arg0, MenuCamera *arg1, f32 arg8, f32 arg9)
{
    arg1->prevCenter.x = CosEaseClamped(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = CosEaseClamped(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = CosEaseClamped(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = CosEaseClamped(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = CosEaseClamped(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = CosEaseClamped(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = CosEaseClamped(arg0->prevZoom, arg1->zoom, arg8, arg9);

    arg0->center.x = arg1->prevCenter.x;
    arg0->center.y = arg1->prevCenter.y;
    arg0->center.z = arg1->prevCenter.z;

    arg0->rot.x = arg1->prevRot.x;
    arg0->rot.y = arg1->prevRot.y;
    arg0->rot.z = arg1->prevRot.z;

    arg0->zoom = arg1->prevZoom;
}

void MenuCameraCosEaseFollow(MenuCamera *srcCamera, MenuCamera *targetCamera, f32 progress, f32 maxProgress, f32 weight)
{
    targetCamera->prevCenter.x = CosEaseClamped(srcCamera->prevCenter.x, targetCamera->center.x, progress, maxProgress);
    targetCamera->prevCenter.y = CosEaseClamped(srcCamera->prevCenter.y, targetCamera->center.y, progress, maxProgress);
    targetCamera->prevCenter.z = CosEaseClamped(srcCamera->prevCenter.z, targetCamera->center.z, progress, maxProgress);

    targetCamera->prevRot.x = CosEaseClamped(srcCamera->prevRot.x, targetCamera->rot.x, progress, maxProgress);
    targetCamera->prevRot.y = CosEaseClamped(srcCamera->prevRot.y, targetCamera->rot.y, progress, maxProgress);
    targetCamera->prevRot.z = CosEaseClamped(srcCamera->prevRot.z, targetCamera->rot.z, progress, maxProgress);

    targetCamera->prevZoom = CosEaseClamped(srcCamera->prevZoom, targetCamera->zoom, progress, maxProgress);

    srcCamera->center.x = SmoothInterpolate(srcCamera->center.x, targetCamera->prevCenter.x, weight);
    srcCamera->center.y = SmoothInterpolate(srcCamera->center.y, targetCamera->prevCenter.y, weight);
    srcCamera->center.z = SmoothInterpolate(srcCamera->center.z, targetCamera->prevCenter.z, weight);

    srcCamera->rot.x = SmoothInterpolate(srcCamera->rot.x, targetCamera->prevRot.x, weight);
    srcCamera->rot.y = SmoothInterpolate(srcCamera->rot.y, targetCamera->prevRot.y, weight);
    srcCamera->rot.z = SmoothInterpolate(srcCamera->rot.z, targetCamera->prevRot.z, weight);

    srcCamera->zoom = SmoothInterpolate(srcCamera->zoom, targetCamera->prevZoom, weight);
}

void motionShift(OMOBJ *obj, s32 mdlId, s32 mtnId, s32 shiftTime, s32 attr)
{
    switch (attr) {
        case 0:
            Hu3DMotionShiftSet(obj->mdlId[mdlId], obj->mtnId[mtnId], 0.0f, shiftTime, 0);
            break;
        case 1:
            Hu3DMotionShiftSet(obj->mdlId[mdlId], obj->mtnId[mtnId], 0.0f, shiftTime, 0x40000001);
            break;
        case 2:
            Hu3DMotionShiftSet(obj->mdlId[mdlId], obj->mtnId[mtnId], 0.0f, shiftTime, 0x40000002);
            break;
    }
    obj->work[0] = obj->work[1] = obj->work[2] = 0;
}

void motionShiftIfChanged(OMOBJ *obj, s32 mdlId, s32 mtnId, s32 shiftTime, s32 attr)
{
    if (obj->work[3] != obj->mtnId[mtnId]) {
        obj->work[3] = obj->mtnId[mtnId];
        switch (attr) {
            case 0:
                Hu3DMotionShiftSet(obj->mdlId[mdlId], obj->mtnId[mtnId], 0.0f, shiftTime, 0);
                break;
            case 1:
                Hu3DMotionShiftSet(obj->mdlId[mdlId], obj->mtnId[mtnId], 0.0f, shiftTime, 0x40000001);
                break;
            case 2:
                Hu3DMotionShiftSet(obj->mdlId[mdlId], obj->mtnId[mtnId], 0.0f, shiftTime, 0x40000002);
                break;
        }
        obj->work[0] = obj->work[1] = obj->work[2] = 0;
    }
}

void fn_1_5B50(OMOBJ *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    (void)arg1;
    Hu3DMotionShiftSet(arg0->mdlId[1], arg0->mtnId[arg1], 0.0f, arg3, 0);
    arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
    arg0->work[0] = 1;
    arg0->work[1] = arg2;
    arg0->work[2] = arg3 + 1;
}

void motionShiftTick(OMOBJ *obj)
{
    s32 mdlId;

    if (obj->work[0] != 0) {
        if (obj->work[2] != 0) {
            obj->work[2] -= 1;
            return;
        }
        if ((obj->work[2] == 0) && (Hu3DMotionEndCheck(obj->mdlId[1]) != 0)) {
            mdlId = obj->work[1];
            Hu3DMotionShiftSet(obj->mdlId[1], obj->mtnId[mdlId], 0.0f, 15.0f, 0x40000001);
            obj->work[0] = obj->work[1] = obj->work[2] = 0;
            obj->work[0] = obj->work[1] = obj->work[2] = 0;
        }
    }
}

void WaitAnimEnd(OMOBJ *obj, s32 mdlId, s32 initialDelay)
{
    HuPrcSleep(initialDelay + 1);
    do {
        HuPrcVSleep();
    } while (Hu3DMotionEndCheck(obj->mdlId[mdlId]) == 0);
}

void MenuMoveChar(OMOBJ *obj, s32 mdlId, Vec targePos, float endRotAngle, float speed, float rotDur, s32 enableMove, s32 enableRot)
{
    s32 xApprDir = 0; // 0 = moving toward target in negative-X, 1 = moving toward target in positive-X, 2 = X has reached target.
    s32 zApprDir = 0;

    Vec nextTickPos;
    Vec curPos;
    Vec targetPos;
    Vec FacingAngle;
    Vec curRot;
    Vec targetRot;
    curPos.x = Hu3DData[obj->mdlId[mdlId]].pos.x;
    curPos.y = Hu3DData[obj->mdlId[mdlId]].pos.y;
    curPos.z = Hu3DData[obj->mdlId[mdlId]].pos.z;
    targetPos.x = targePos.x;
    targetPos.y = targePos.y;
    targetPos.z = targePos.z;
    curRot.x = Hu3DData[obj->mdlId[mdlId]].rot.x;
    curRot.y = Hu3DData[obj->mdlId[mdlId]].rot.y;
    curRot.z = Hu3DData[obj->mdlId[mdlId]].rot.z;
    targetRot.x = 0;
    targetRot.y = endRotAngle;
    targetRot.z = 0;
    if (targetPos.x - curPos.x >= 0.0f) {
        xApprDir = 1;
    }
    else {
        xApprDir = 0;
    }
    if (targetPos.z - curPos.z >= 0.0f) {
        zApprDir = 1;
    }
    else {
        zApprDir = 0;
    }
    while (enableMove) {
        MenuPrcVSleep();
        FacingAngle.y = -(atan2d(targetPos.z - curPos.z, targetPos.x - curPos.x) - 90);
        if (FacingAngle.y < 0.0f) {
            FacingAngle.y += 360.0f;
        }
        else if (FacingAngle.y >= 360.0f) {
            FacingAngle.y -= 360.0f;
        }
        if (enableRot) {
            if (FacingAngle.y >= 180.0f) {
                if (curRot.y - FacingAngle.y >= 180.0f) {
                    curRot.y -= 360.0f;
                }
                if (curRot.y - FacingAngle.y < -180.0f) {
                    curRot.y += 360.0f;
                }
            }
            else {
                if (curRot.y - FacingAngle.y > 180.0f) {
                    curRot.y -= 360.0f;
                }
                if (curRot.y - FacingAngle.y <= -180.0f) {
                    curRot.y += 360.0f;
                }
            }
        }
        nextTickPos.x = curPos.x = curPos.x + (speed * sind(FacingAngle.y));
        nextTickPos.z = curPos.z = curPos.z + (speed * cosd(FacingAngle.y));
        if (xApprDir == 1) {
            if (curPos.x >= targetPos.x) {
                nextTickPos.x = curPos.x = targetPos.x;
                xApprDir = 2;
            }
        }
        else if (xApprDir == 0) {
            if (curPos.x <= targetPos.x) {
                nextTickPos.x = curPos.x = targetPos.x;
                xApprDir = 2;
            }
        }
        if (zApprDir == 1) {
            if (curPos.z >= targetPos.z) {
                nextTickPos.z = curPos.z = targetPos.z;
                zApprDir = 2;
            }
        }
        else if (zApprDir == 0) {
            if (curPos.z <= targetPos.z) {
                nextTickPos.z = curPos.z = targetPos.z;
                zApprDir = 2;
            }
        }
        if (enableRot) {
            curRot.y = WeightedBlend(curRot.y, FacingAngle.y, rotDur);
        }
        Hu3DModelPosSet(obj->mdlId[mdlId], nextTickPos.x, curPos.y, nextTickPos.z);
        Hu3DModelRotSet(obj->mdlId[mdlId], curRot.x, curRot.y, curRot.z);
        if (xApprDir == 2 && zApprDir == 2) {
            break;
        }
    }
    curRot.y = Hu3DData[obj->mdlId[mdlId]].rot.y;
    if (enableRot) {
        s32 i;
        for (i = 0; i <= rotDur; i++) {
            MenuPrcVSleep();
            if (targetRot.y >= 180.0f) {
                if (curRot.y - targetRot.y >= 180.0f) {
                    curRot.y -= 360.0f;
                }
                if (curRot.y - targetRot.y < -180.0f) {
                    curRot.y += 360.0f;
                }
            }
            else {
                if (curRot.y - targetRot.y > 180.0f) {
                    curRot.y -= 360.0f;
                }
                if (curRot.y - targetRot.y <= -180.0f) {
                    curRot.y += 360.0f;
                }
            }
            targetRot.z = LerpClamped(curRot.y, targetRot.y, i, rotDur);
            Hu3DModelRotSet(obj->mdlId[mdlId], curRot.x, targetRot.z, curRot.z);
        }
    }
}

void sprPosSetYPad(s32 grpId, s32 memberNo, float posX, float posY)
{
    HuSprPosSet(grpId, memberNo, posX, posY + 0.5f);
}
