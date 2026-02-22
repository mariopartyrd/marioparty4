#include "game/animdata.h"
#include "game/audio.h"
#include "game/hsfman.h"
#ifndef __MWERKS__
#include "game/minigame_seq.h"
#endif
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#ifndef __MWERKS__
#include "game/thpmain.h"
#endif
#include "game/window.h"
#include "game/wipe.h"

#include "math.h"

typedef struct StaffData {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ float unk_08;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ s32 logoGroupIdx;
    /* 0x14 */ s32 unk_14;
} StaffData;

static s16 imgGroup[26];
static s16 staffLogoGroup[3];
static s16 thpGroup;
static s16 thpCoverGroup;
static s32 staffSide;
static s32 currImg;
static omObjData *multiViewObj;

static StaffData staffData[] = {
    { 0x00340001, 0, 0.0f, 0, 0, 0 },
    { 0x00350000, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 72.0f, 0, 0, 0 },
    { 0x00340002, 0, 0.0f, 0, 0, 0 },
    { 0x00350001, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340003, 0, 0.0f, 0, 0, 0 },
    { 0x00350002, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340004, 0, 0.0f, 0, 0, 0 },
    { 0x00350003, 2, 0.0f, 0, 0, 0 },
    { 0x00350004, 2, 0.0f, 0, 0, 0 },
    { 0x00350005, 2, 0.0f, 0, 0, 0 },
    { 0x00350006, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00350007, 2, 0.0f, 0, 0, 0 },
    { 0x00350008, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340005, 0, 0.0f, 0, 0, 0 },
    { 0x00350009, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340006, 0, 0.0f, 0, 0, 0 },
    { 0x0035000A, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340007, 0, 0.0f, 0, 0, 0 },
    { 0x0034001C, 1, 0.0f, 0, 0, 0 },
    { 0x0035000B, 2, 0.0f, 0, 0, 0 },
    { 0x0035000C, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x0034001D, 1, 0.0f, 0, 0, 0 },
    { 0x0035000D, 2, 0.0f, 0, 0, 0 },
    { 0x0035000E, 2, 0.0f, 0, 0, 0 },
    { 0x0035000F, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00350010, 2, 0.0f, 0, 0, 0 },
    { 0x00350011, 2, 0.0f, 0, 0, 0 },
    { 0x00350012, 2, 0.0f, 0, 0, 0 },
    { 0x00350013, 2, 0.0f, 0, 0, 0 },
    { 0x00350014, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x0034001E, 1, 0.0f, 0, 0, 0 },
    { 0x00350015, 2, 0.0f, 0, 0, 0 },
    { 0x00350016, 2, 0.0f, 0, 0, 0 },
    { 0x00350017, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340008, 0, 0.0f, 0, 0, 0 },
    { 0x00350018, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340009, 0, 0.0f, 0, 0, 0 },
    { 0x00350019, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x0034000A, 0, 0.0f, 0, 0, 0 },
    { 0x0034001C, 1, 0.0f, 0, 0, 0 },
    { 0x0035001A, 2, 0.0f, 0, 0, 0 },
    { 0x0035001B, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x0034001D, 1, 0.0f, 0, 0, 0 },
    { 0x0035001C, 2, 0.0f, 0, 0, 0 },
    { 0x0035001D, 2, 0.0f, 0, 0, 0 },
    { 0x0035001E, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x0034001E, 1, 0.0f, 0, 0, 0 },
    { 0x0035001F, 2, 0.0f, 0, 0, 0 },
    { 0x00350020, 2, 0.0f, 0, 0, 0 },
    { 0x00350021, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x0034000B, 0, 0.0f, 0, 0, 0 },
    { 0x0034001F, 1, 0.0f, 0, 0, 0 },
    { 0x00350022, 2, 0.0f, 0, 0, 0 },
    { 0x00350023, 2, 0.0f, 0, 0, 0 },
    { 0x00350024, 2, 0.0f, 0, 0, 0 },
    { 0x00350025, 2, 0.0f, 0, 0, 0 },
    { 0x00350026, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00350027, 2, 0.0f, 0, 0, 0 },
    { 0x00350028, 2, 0.0f, 0, 0, 0 },
    { 0x00350029, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x0034001C, 1, 0.0f, 0, 0, 0 },
    { 0x0035002A, 2, 0.0f, 0, 0, 0 },
    { 0x0035002B, 2, 0.0f, 0, 0, 0 },
    { 0x0035002C, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x0034001D, 1, 0.0f, 0, 0, 0 },
    { 0x0035002D, 2, 0.0f, 0, 0, 0 },
    { 0x0035002E, 2, 0.0f, 0, 0, 0 },
    { 0x0035002F, 2, 0.0f, 0, 0, 0 },
    { 0x00350030, 2, 0.0f, 0, 0, 0 },
    { 0x00350031, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00350032, 2, 0.0f, 0, 0, 0 },
    { 0x00350033, 2, 0.0f, 0, 0, 0 },
    { 0x00350034, 2, 0.0f, 0, 0, 0 },
    { 0x00350035, 2, 0.0f, 0, 0, 0 },
    { 0x00350036, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x0034000C, 0, 0.0f, 0, 0, 0 },
    { 0x00350037, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x0034000D, 0, 0.0f, 0, 0, 0 },
    { 0x00350038, 2, 0.0f, 0, 0, 0 },
    { 0x00350039, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x0034000E, 0, 0.0f, 0, 0, 0 },
    { 0x0035003A, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x0034000F, 0, 0.0f, 0, 0, 0 },
    { 0x0035003B, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340010, 0, 0.0f, 0, 0, 0 },
    { 0x0035003C, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00340011, 0, 0.0f, 0, 0, 0 },
    { 0x0035003B, 2, 0.0f, 0, 0, 0 },
    { 0x0035003C, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00340012, 0, 0.0f, 0, 0, 0 },
    { 0x0035003D, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00340013, 0, 0.0f, 0, 0, 0 },
    { 0x0035003E, 2, 0.0f, 0, 0, 0 },
    { 0x0035003F, 2, 0.0f, 0, 0, 0 },
    { 0x00350040, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340014, 0, 0.0f, 0, 0, 0 },
    { 0x00350041, 2, 0.0f, 0, 0, 0 },
    { 0x00350042, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340015, 0, 0.0f, 0, 0, 0 },
    { 0x00350043, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340022, 0, 0.0f, 0, 0, 0 },
    { 0x00340024, 1, 0.0f, 0, 0, 0 },
    { 0x00350056, 2, 0.0f, 0, 0, 0 },
    { 0x00350057, 2, 0.0f, 0, 0, 0 },
    { 0x00350058, 2, 0.0f, 0, 0, 0 },
    { 0x00350059, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00340025, 1, 0.0f, 0, 0, 0 },
    { 0x0035005A, 2, 0.0f, 0, 0, 0 },
    { 0x0035005B, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340023, 0, 0.0f, 0, 0, 0 },
    { 0x0035005C, 2, 0.0f, 0, 0, 0 },
    { 0x0035005D, 2, 0.0f, 0, 0, 0 },
    { 0x0035005E, 2, 0.0f, 0, 0, 0 },
    { 0x0035005F, 2, 0.0f, 0, 0, 0 },
    { 0x00350060, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    #if VERSION_PAL
    { 0x00340026, 0, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00340027, 1, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00340028, 1, 0.0f, 0, 0, 0 },
    { 0x00350061, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00340029, 1, 0.0f, 0, 0, 0 },
    { 0x0034002A, 1, 0.0f, 0, 0, 0 },
    { 0x00350062, 2, 0.0f, 0, 0, 0 },
    { 0x0034002B, 1, 0.0f, 0, 0, 0 },
    { 0x00350063, 2, 0.0f, 0, 0, 0 },
    { 0x0034002C, 1, 0.0f, 0, 0, 0 },
    { 0x00350064, 2, 0.0f, 0, 0, 0 },
    { 0x0034002D, 1, 0.0f, 0, 0, 0 },
    { 0x00350065, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x0034002E, 1, 0.0f, 0, 0, 0 },
    { -3, 0, 72.0f, 0, 0, 0 },
    #endif
    { 0x00340016, 0, 0.0f, 0, 0, 0 },
    { 0x00350044, 2, 0.0f, 0, 0, 0 },
    #if VERSION_NTSC
    { 0x00350045, 2, 0.0f, 0, 0, 0 },
    #endif
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x00350046, 2, 0.0f, 0, 0, 0 },
    { 0x00350047, 2, 0.0f, 0, 0, 0 },
    { 0x00350048, 2, 0.0f, 0, 0, 0 },
    { 0x00350049, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 24.0f, 0, 0, 0 },
    { 0x0035004A, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x0035004B, 2, 0.0f, 0, 0, 0 },
    { 0x0035004C, 2, 0.0f, 0, 0, 0 },
    { 0x0035004D, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340017, 0, 0.0f, 0, 0, 0 },
    { 0x0035004E, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 48.0f, 0, 0, 0 },
    { 0x00340018, 0, 0.0f, 0, 0, 0 },
    { 0x0035004F, 2, 0.0f, 0, 0, 0 },
    { 0x00350050, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 72.0f, 0, 0, 0 },
    { 0x00340019, 0, 0.0f, 0, 0, 0 },
    { 0x00350038, 2, 0.0f, 0, 0, 0 },
    { 0x00350051, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 72.0f, 0, 0, 0 },
    { 0x0034001A, 0, 0.0f, 0, 0, 0 },
    { 0x00350052, 2, 0.0f, 0, 0, 0 },
    { 0x00350053, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 72.0f, 0, 0, 0 },
    { 0x0034001B, 0, 0.0f, 0, 0, 0 },
    { 0x00350054, 2, 0.0f, 0, 0, 0 },
    { 0x00350055, 2, 0.0f, 0, 0, 0 },
    { -3, 0, 74.0f, 0, 0, 0 },
    { -2, 0, 0.0f, 0, 0, 0 },
    { -1, 0, 0.0f, 0, 0, 0 },
};

#if VERSION_NTSC
static float staffLogoPosTbl[] = { 460.0f, 293.0f, 293.0f };
#else
static float staffLogoPosTbl[] = { 460.0f, 290.0f, 293.0f };
#endif

static void MainProc(void);
static void CreateStaff(void);
static void ShowPicture(void);

void ObjectSetup(void)
{
    Process *process;

    process = omInitObjMan(0x32, 0x2000);
    omGameSysInit(process);
    HuWinInit(1);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 10000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    multiViewObj = omAddObjEx(process, 0x7FDA, 0, 0, -1, omOutViewMulti);
    multiViewObj->work[0] = 1;
    CRotM[0].x = -35.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = -250.0f;
    CZoomM[0] = 4820.0f;
    Hu3DBGColorSet(0, 0, 0);
    CreateStaff();
    HuPrcChildCreate(MainProc, 0x1000, 0x2000, 0, HuPrcCurrentGet());
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
}

static void ExitProc(void)
{
    while (TRUE) {
        if (omSysExitReq == 1) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(1000);
            HuPrcSleep(60);
            MGSeqKillAll();
            omOvlReturnEx(1, 1);

            while (TRUE) {
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }

    while (!omSysExitReq) {
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudFadeOut(1000);
    HuPrcSleep(60);
    MGSeqKillAll();
    omOvlReturnEx(1, 1);

    while (TRUE) {
        HuPrcVSleep();
    }
}

static void CreateStaff(void)
{
    void *var_r29;
    AnimData *var_r28;
    s16 var_r30;
    s32 var_r31;

    staffSide = 0;
    currImg = 0;

    for (var_r31 = 0; var_r31 < 26; var_r31++) {
        var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_STAFF, var_r31), MEMORY_DEFAULT_NUM, HEAP_DATA);
        var_r28 = HuSprAnimRead(var_r29);
        var_r30 = HuSprCreate(var_r28, 16386, 0);
        imgGroup[var_r31] = HuSprGrpCreate(1);
        HuSprGrpMemberSet(imgGroup[var_r31], 0, var_r30);
        if (staffSide != 0) {
            HuSprGrpPosSet(imgGroup[var_r31], 380.0f, 240.0f);
        }
        else {
            HuSprGrpPosSet(imgGroup[var_r31], 200.0f, 240.0f);
        }
        HuSprAttrSet(imgGroup[var_r31], 0, HUSPR_ATTR_DISPOFF);
    }

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        int languageNo;
        #if VERSION_NTSC
        var_r29 = HuDataSelHeapReadNum(var_r31 + DATA_MAKE_NUM(DATADIR_STAFF, 0x1A), MEMORY_DEFAULT_NUM, HEAP_DATA);
        #else
        if(var_r31 == 2) {
            switch(GWGameStat.language) {
                case 1:
                    languageNo = 0;
                    break;
                
                case 2:
                    languageNo = 1;
                    break;
                
                case 4:
                    languageNo = 3;
                    break;
                
                default:
                    languageNo = 2;
                    break;
                    
            }
            
            var_r29 = HuDataSelHeapReadNum(var_r31 + DATA_MAKE_NUM(DATADIR_STAFF, 0x1A) + languageNo, MEMORY_DEFAULT_NUM, HEAP_DATA);
        } else {
            var_r29 = HuDataSelHeapReadNum(var_r31 + DATA_MAKE_NUM(DATADIR_STAFF, 0x1A), MEMORY_DEFAULT_NUM, HEAP_DATA);
        }
        #endif
        
        var_r28 = HuSprAnimRead(var_r29);
        var_r30 = HuSprCreate(var_r28, 256, 0);
        staffLogoGroup[var_r31] = HuSprGrpCreate(1);
        HuSprGrpMemberSet(staffLogoGroup[var_r31], 0, var_r30);
        HuSprAttrSet(staffLogoGroup[var_r31], 0, HUSPR_ATTR_DISPOFF);
    }
    thpGroup = HuSprGrpCreate(1);
    var_r30 = HuTHPSprCreate("movie/stmov_a00.thp", 0, 16386);
    HuSprGrpMemberSet(thpGroup, 0, var_r30);
    HuSprGrpScaleSet(thpGroup, 0.65f, 0.65f);
    HuSprGrpPosSet(thpGroup, 280.0f, 200.0f);
    HuSprAttrSet(thpGroup, 0, HUSPR_ATTR_DISPOFF);
    HuTHPStop();
    #if VERSION_NTSC
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_STAFF, 0x1D), MEMORY_DEFAULT_NUM, HEAP_DATA);
    #else
    var_r29 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_STAFF, 0x20), MEMORY_DEFAULT_NUM, HEAP_DATA);
    #endif
    var_r28 = HuSprAnimRead(var_r29);
    var_r30 = HuSprCreate(var_r28, 16385, 0);
    thpCoverGroup = HuSprGrpCreate(1);
    HuSprGrpMemberSet(thpCoverGroup, 0, var_r30);
    HuSprGrpScaleSet(thpCoverGroup, 40.0f, 40.0f);
    HuSprGrpPosSet(thpCoverGroup, 280.0f, 200.0f);
    HuSprAttrSet(thpCoverGroup, 0, HUSPR_ATTR_DISPOFF);
    HuPrcChildCreate(ShowPicture, 4096, 8192, 0, HuPrcCurrentGet());
    HuPrcChildCreate(ExitProc, 4096, 4096, 0, HuPrcCurrentGet());
}

static void MoveStaff(void)
{
    float sp8[2];
    float var_f30;
    float var_f31;
    s16 var_r30;
    u32 var_r29;
    StaffData *var_r31;

    var_r31 = HuPrcCurrentGet()->user_data;
    var_r31->unk_14 = 0;
    switch (var_r31->unk_00) {
        case -2:
            HuSprAttrReset(staffLogoGroup[var_r31->logoGroupIdx], 0, HUSPR_ATTR_DISPOFF);
            var_f31 = staffLogoPosTbl[var_r31->logoGroupIdx];
            var_f30 = 576.0f;
            break;
        default:
            HuWinMesMaxSizeGet(1, sp8, var_r31->unk_00);
            var_r29 = 0;
            switch (var_r31->unk_04) {
                case 3:
                    var_f31 = 320.0f - (0.75f * sp8[0]) / 2;
                    break;
                case 0:
                    var_f31 = 10.0f;
                    if (staffSide == 0) {
                        var_f31 += 240.0f;
                    }
                    break;
                case 1:
                    var_f31 = 30.0f;
                    if (staffSide == 0) {
                        var_f31 += 240.0f;
                    }
                    break;
                case 2:
                    var_f31 = 550.0f - (0.75f * sp8[0]);
                    if (staffSide != 0) {
                        var_f31 -= 240.0f;
                    }
                    var_r29 = 0x1000;
                    break;
            }
            var_f30 = 476.0f;
            var_r30 = HuWinCreate(var_f31, var_f30, sp8[0], sp8[1], 1);
            HuWinAttrSet(var_r30, var_r29);
            HuWinPriSet(var_r30, 256);
            HuWinBGTPLvlSet(var_r30, 0.0f);
            HuWinMesSpeedSet(var_r30, 0);
            HuWinMesSet(var_r30, var_r31->unk_00);
            HuWinScaleSet(var_r30, 0.75f, 0.75f);
            switch (var_r31->unk_04) {
                case 0:
                case 1:
                    HuWinMesPalSet(var_r30, 7, 96, 240, 255);
                    break;
                default:
                    HuWinMesPalSet(var_r30, 7, 255, 255, 255);
                    break;
            }
            break;
    }
    while (TRUE) {
        var_f30 -= 0.4f;
        if (var_r31->unk_00 == -2) {
            if (var_f30 < -114.0f) {
                break;
            }
        }
        else if (var_f30 < -24.0f) {
            break;
        }
        if (var_r31->unk_00 == -2) {
            HuSprGrpPosSet(staffLogoGroup[var_r31->logoGroupIdx], var_f31, var_f30);
        }
        else {
            HuWinPosSet(var_r30, var_f31, var_f30);
        }
        HuPrcVSleep();
    }
    var_r31->unk_14 = 1;
    if (var_r31->unk_00 == -2) {
        HuSprAttrSet(staffLogoGroup[var_r31->logoGroupIdx], 0, HUSPR_ATTR_DISPOFF);
    }
    else {
        HuWinKill(var_r30);
    }
    HuPrcVSleep();
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void HidePicture(void)
{
    s32 prevImg;

    prevImg = currImg;
    currImg++;
    if (staffSide != 0) {
        HuSprGrpPosSet(imgGroup[currImg], 380.0f, 240.0f);
    }
    else {
        HuSprGrpPosSet(imgGroup[currImg], 200.0f, 240.0f);
    }
    HuSprAttrSet(imgGroup[prevImg], 0, HUSPR_ATTR_DISPOFF);
    HuPrcSleep(20);
    HuSprAttrReset(imgGroup[currImg], 0, HUSPR_ATTR_DISPOFF);
    HuPrcKill(HuPrcCurrentGet());
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void ShowPicture(void)
{
    float var_f31;
    s32 var_r31;

    HuPrcSleep(360);
    HuSprAttrReset(imgGroup[currImg], 0, HUSPR_ATTR_DISPOFF);

    for (var_r31 = 0, var_f31 = 0.0f; var_r31 < 30; var_r31++, var_f31 += 1.0f / 30.0f) {
        HuSprTPLvlSet(imgGroup[currImg], 0, var_f31);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(imgGroup[currImg], 0, 1.0f);

    while (TRUE) {
        #if VERSION_NTSC
        if (currImg >= 24) {
            HuPrcSleep(430);
        } else {
            HuPrcSleep(550);
        }
        #else
        if (currImg >= 24) {
            HuPrcSleep(480);
        } else {
            HuPrcSleep(600);
        }
        #endif
        if (currImg >= 25) {
            break;
        }
        HuPrcChildCreate(HidePicture, 0x1000, 0x2000, 0, HuPrcCurrentGet());
    }

    for (var_r31 = 0, var_f31 = 1.0f; var_r31 < 30; var_r31++, var_f31 -= 1.0f / 30.0f) {
        HuSprTPLvlSet(imgGroup[25], 0, var_f31);
        HuPrcVSleep();
    }
    HuSprAttrSet(imgGroup[25], 0, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(imgGroup[25], 0, HUSPR_ATTR_DISPOFF);

    while (TRUE) {
        HuPrcVSleep();
    }
}

static void MainProc(void)
{
    s32 var_r31;
    StaffData *var_r30;
    s32 var_r29;
    Process *var_r28;
    s32 var_r27;
    float var_f29;
    float var_f30;
    float var_f31;

    HuPrcSleep(60);
    var_r27 = HuAudSStreamPlay(22);

    for (var_r31 = 0;; var_r31++) {
        var_r30 = &staffData[var_r31];
        if (var_r30->unk_00 == -1) {
            break;
        }

        switch (var_r30->unk_00) {
            case -3:
                HuPrcSleep(var_r30->unk_08 / 0.4f);
                break;
            default:
                var_r28 = HuPrcChildCreate(MoveStaff, 0x1000, 0x2000, 0, HuPrcCurrentGet());
                var_r28->user_data = var_r30;
                if (var_r30->unk_0C == 1) {
                    staffSide++;
                    staffSide &= 1;
                    HuPrcChildCreate(HidePicture, 0x1000, 0x2000, 0, HuPrcCurrentGet());
                }
                else {
                    HuPrcSleep(60);
                }
                break;
        }
    }
    var_r30 = &staffData[var_r31 - 1];

    while (var_r30->unk_14 == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(60);
    HuSprAttrReset(staffLogoGroup[1], 0, HUSPR_ATTR_DISPOFF);
    var_f29 = staffLogoPosTbl[1];
    var_f30 = 526.0f;
    var_r29 = 0;

    while (TRUE) {
        var_f30 -= 0.4f;
        if (var_f30 < 400.0f) {
            break;
        }
        if ((var_r29 == 0) && (var_f30 < 506.0f)) {
            var_r29 = 1;
            HuAudSStreamFadeOut(var_r27, 6000);
        }
        HuSprGrpPosSet(staffLogoGroup[1], var_f29, var_f30);
        HuPrcVSleep();
    }
    HuSprGrpPosSet(staffLogoGroup[1], var_f29, 400.0f);
    #if VERSION_NTSC
    HuPrcSleep(240);
    #else
    HuPrcSleep(60);
    #endif
    HuSprAttrReset(thpGroup, 0, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(thpCoverGroup, 0, HUSPR_ATTR_DISPOFF);
    HuTHPRestart();

    for (var_r31 = 0, var_f31 = 1.0f; var_r31 < 90; var_r31++, var_f31 -= 0.1f / 9.0f) {
        HuSprTPLvlSet(thpCoverGroup, 0, var_f31);
        HuPrcVSleep();
    }
    HuSprAttrSet(thpCoverGroup, 0, HUSPR_ATTR_DISPOFF);

    while (HuTHPFrameGet() < 450) {
        HuPrcVSleep();
    }
    HuSprAttrReset(thpCoverGroup, 0, HUSPR_ATTR_DISPOFF);

    for (var_r31 = 0, var_f31 = 0.0f; var_r31 < 120; var_r31++, var_f31 += 0.05f / 6.0f) {
        HuSprTPLvlSet(thpCoverGroup, 0, var_f31);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(thpCoverGroup, 0, 1.0f);
    HuSprAttrSet(thpGroup, 0, HUSPR_ATTR_DISPOFF);
    HuTHPClose();

    for (var_r31 = 0, var_f31 = 1.0f; var_r31 < 30; var_r31++, var_f31 -= 1.0f / 30.0f) {
        HuSprTPLvlSet(staffLogoGroup[1], 0, var_f31);
        HuPrcVSleep();
    }
    HuSprAttrSet(staffLogoGroup[1], 0, HUSPR_ATTR_DISPOFF);
    HuPrcSleep(120);
    HuSprAttrReset(staffLogoGroup[2], 0, HUSPR_ATTR_DISPOFF);
    #if VERSION_NTSC
    HuSprGrpPosSet(staffLogoGroup[2], 280.0f, 240.0f);
    #else
    HuSprGrpPosSet(staffLogoGroup[2], 275.0f, 240.0f);
    #endif
    for (var_r31 = 0, var_f31 = 0.0f; var_r31 < 30; var_r31++, var_f31 += 1.0f / 30.0f) {
        HuSprTPLvlSet(staffLogoGroup[2], 0, var_f31);
        HuPrcVSleep();
    }
    #if VERSION_NTSC
    HuPrcSleep(600);
    #else
    HuPrcSleep(480);
    #endif
    while (TRUE) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (HuPadBtn[var_r31] & PAD_BUTTON_START) {
                break;
            }
        }
        if (var_r31 < 4) {
            break;
        }
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudFadeOut(1000);
    HuPrcSleep(60);
    MGSeqKillAll();
    omOvlReturnEx(1, 1);

    while (TRUE) {
        HuPrcVSleep();
    }
}
