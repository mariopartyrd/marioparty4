#include "version.h"
#if VERSION_PAL
#include "dolphin.h"
#include "game/card.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/hsfman.h"
#include "game/hsfanim.h"
#include "game/window.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/minigame_seq.h"

#include "math.h"
#include "ext_math.h"

#include "data_num/title.h"

s32 flagFileTbl[] = {
    TITLE_FLAG_EN_ANM,
    TITLE_FLAG_ES_ANM,
    TITLE_FLAG_IT_ANM,
    TITLE_FLAG_FR_ANM,
    TITLE_FLAG_GE_ANM
};

extern int SystemInitF;

extern Process *objman;
extern Vec debugCamRot[2];
extern Vec debugCamPos[2];
extern float debugCamZoom[2];

void DebugCamOutView(omObjData *obj);
void DebugCamUpdate(omObjData *obj);

BOOL LanguageMenuExec(void)
{
    s16 language = GWLanguageGet()-1;
    s16 i;
    s16 gid;
    s16 time;
    s16 choiceChange;
    AnimData *anim;
    s16 sprid;
    s16 choice;
    omObjData *outView;
    omObjData *updateCamera;
    s16 modelId[5];
    s16 winId[5];
    
    float winSize[2];
    float dist;
    float posX;
    float posZ;
    
    for(i=0; i<4; i++) {
        GWPlayerCfg[i].character = i;
    }
    gid = HuSprGrpCreate(1);
    anim = HuSprAnimReadFile(TITLE_LANGUAGEBG_ANM);
    sprid = HuSprCreate(anim, 0, 0);
    HuSprGrpMemberSet(gid, 0, sprid);
    HuSprDrawNoSet(gid, 0, 127);
    HuSprPosSet(gid, 0, 288, 240);
    HuSprTPLvlSet(gid, 0, 0.6f);
    Hu3DFogSet(350, 2000, 128, 128, 128);
    debugCamRot[0].x = -20;
    debugCamRot[0].y = 0;
    debugCamRot[0].z = 0;
    debugCamPos[0].x = 0;
    debugCamPos[0].y = 20;
    debugCamPos[0].z = -7;
    debugCamZoom[0] = 600;
    
    Hu3DCameraPerspectiveSet(HU3D_CAM0, 60, 20, 5000, 1.2f);
    outView = omAddObjEx(objman, 32730, 0, 0, -1, DebugCamOutView);
    updateCamera = omAddObjEx(objman, 0, 32, 32, -1, DebugCamUpdate);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    if(!SystemInitF) {
        void *group_samp;
        HuWindowInit();
        group_samp = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(0));
        msmSysLoadGroup(0, group_samp, 0);
        HuMemDirectFree(group_samp);
    }
    for(i=0; i<5; i++) {
        modelId[i] = Hu3DModelCreateFile(TITLE_FLAG_HSF);
        anim = HuSprAnimReadFile(flagFileTbl[i]);
        Hu3DAnimCreate(anim, modelId[i], "flag");
        Hu3DModelPosSet(modelId[i], sind(i*72)*200, 70, cosd(i*72)*200);
        Hu3DModelRotSet(modelId[i], -20, 0, 0);
    }
    for(time=1; time<=30; time++) {
        dist = 1.0-(time/30.0);
        for(i=0; i<5; i++) {
            Hu3DModelPosSet(modelId[i], sind((dist*180.0f)+(i*72)+(language*72))*(200+(300*dist)), 70, cosd((dist*180.0f)+(i*72)+(language*72))*(200+(300*dist)));
        }
        HuPrcVSleep();
    }
    HuWinInit(1);
    HuWinMesMaxSizeGet(5, winSize, 0x380000, 0x380005, 0x38000A, 0x38000F, 0x380014);
    winId[0] = HuWinExCreateStyled(-10000, 50, winSize[0], winSize[1], -1, 0);
    HuWinAttrSet(winId[0], 0x800);
    HuWinMesSet(winId[0], 0x380000+(language*5));
    HuWinBGTPLvlSet(winId[0], 0);
    HuWinMesSpeedSet(winId[0], 0);
    HuWinDispOn(winId[0]);
    HuWinMesMaxSizeGet(5, winSize, 0x380001, 0x380006, 0x38000B, 0x380010, 0x380015);
    winId[1] = HuWinExCreateStyled(-10000, 100, winSize[0], winSize[1], -1, 0);
    HuWinAttrSet(winId[1], 0x800);
    HuWinMesSet(winId[1], 0x380001+(language*5));
    HuWinBGTPLvlSet(winId[1], 0);
    HuWinMesSpeedSet(winId[1], 0);
    HuWinDispOn(winId[1]);
    HuWinMesMaxSizeGet(5, winSize, 0x380002, 0x380007, 0x38000C, 0x380011, 0x380016);
    winId[2] = HuWinExCreateStyled(-10000, 340, winSize[0], winSize[1], -1, 0);
    HuWinAttrSet(winId[2], 0x800);
    HuWinMesSet(winId[2], 0x380002+(language*5));
    HuWinBGTPLvlSet(winId[2], 0);
    HuWinMesSpeedSet(winId[2], 0);
    HuWinDispOn(winId[2]);
    HuWinMesMaxSizeGet(5, winSize, 0x380004, 0x380009, 0x38000E, 0x380013, 0x380018);
    winId[4] = HuWinExCreateStyled(-10000, (448-winSize[1])-10, winSize[0], winSize[1], -1, 0);
    HuWinAttrSet(winId[4], 0x800);
    choiceChange = FALSE;
    while(1) {
        if(HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
            HuAudFXPlay(0);
            for(time=0; time<=10; time++) {
                for(i=0; i<5; i++) {
                    posX = sind((72.0*language)+(i*72)-(72.0*(time/10.0)))*200;
                    posZ = cosd((72.0*language)+(i*72)-(72.0*(time/10.0)))*200;
                    Hu3DModelPosSet(modelId[i], posX, 70, posZ);
                }
                HuPrcVSleep();
            }
            language--;
            if(language < 0) {
                language = 4;
            }
            choiceChange = TRUE;
        } else if(HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
            HuAudFXPlay(0);
            for(time=0; time<=10; time++) {
                for(i=0; i<5; i++) {
                    posX = sind((72.0*language)+(i*72)+(72.0*(time/10.0)))*200;
                    posZ = cosd((72.0*language)+(i*72)+(72.0*(time/10.0)))*200;
                    Hu3DModelPosSet(modelId[i], posX, 70, posZ);
                }
                HuPrcVSleep();
            }
            language++;
            if(language >= 5) {
                language = 0;
            }
            choiceChange = TRUE;
        }
        if(choiceChange) {
            HuWinMesSet(winId[0], 0x380000+(language*5));
            HuWinMesSet(winId[1], 0x380001+(language*5));
            HuWinMesSet(winId[2], 0x380002+(language*5));
            choiceChange = FALSE;
        }
        if(HuPadBtnDown[0] & PAD_BUTTON_A) {
            HuAudFXPlay(1);
            HuWinHomeClear(winId[4]);
            HuWinExAnimIn(winId[4]);
            HuWinMesSet(winId[4], 0x380004+(language*5));
            HuWinMesWait(winId[4]);
            choice = HuWinChoiceGet(winId[4], 0);
            if(choice == 0) {
                GwLanguage = GwLanguageSave = language+1;
                GWLanguageSet(GwLanguage);
                break;
            }
            HuWinExAnimOut(winId[4]);
        }
        if(GwLanguage != -1 && (HuPadBtnDown[0] & PAD_BUTTON_B)) {
            HuAudFXPlay(3);
            break;
        }
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuSprGrpKill(gid);
    for(i=0; i<5; i++) {
        Hu3DModelKill(modelId[i]);
    }
    omDelObjEx(objman, outView);
    omDelObjEx(objman, updateCamera);
    if(SystemInitF == 0) {
        CharInit();
        MGSeqInit();
    }
    HuWinAllKill();
    Hu3DFogClear();
    return TRUE;
}

s32 LanguageBootGet(void)
{
    s16 result = -1;
    s16 i;
    s16 j;
    for(i=0; i<2; i++) {
        if(HuCardSlotCheck(i) < 0) {
            continue;
        }
        if(HuCardMount(i) < 0) {
            continue;
        }
        for(j=0; j<3; j++) {
            CARDFileInfo fileInfo;
            if(HuCardOpen(i, SaveFileNameTbl[j], &fileInfo) < 0) {
                continue;
            }
            if(HuCardRead(&fileInfo, &saveBuf, SAVE_BUF_SIZE, 0) < 0) {
                continue;
            }
            if(!SLCheckSumCheck()) {
                continue;
            }
            memcpy(&GWGameStat, &saveBuf.data.stat, sizeof(GameStat));
            if(GWGameStat.language < 1) {
                continue;
            }
            if(GWGameStat.language > 5) {
                continue;
            }
            result = GWGameStat.language;
            OSReport("Language %d\n", GWGameStat.language);
            HuCardClose(&fileInfo);
            HuCardUnMount(i);
            return result;
        }
        HuCardUnMount(i);
    }
    if(result == -1) {
        OSReport("OS Language %d\n", OSGetLanguage());
        switch(OSGetLanguage()) {
            case OS_LANG_ENGLISH:
                result = 1;
                break;
               
            case OS_LANG_GERMAN:
                result = 2;
                break;
            
            case OS_LANG_FRENCH:
                result = 3;
                break;
            
            case OS_LANG_SPANISH:
                result = 5;
                break;
            
            case OS_LANG_ITALIAN:
                result = 4;
                break;
            
            default:
                result = -1;
                break;
        }
    }
    return result;
}

#endif
