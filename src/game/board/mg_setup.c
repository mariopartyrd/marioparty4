#include "game/board/mg_setup.h"
#include "game/audio.h"
#include "game/objsub.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/window.h"
#include "game/board/main.h"
#include "game/board/audio.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/ui.h"
#include "game/board/tutorial.h"
#include "game/board/window.h"

// structs
typedef struct structActiveMG {
    s16 unk_00;
    s8  unk_02;
    s8  unk_03;
    s32 unk_04;
} structActiveMG;

typedef struct unkSubstructR31 {
    s16 unk_00[4];
    char unk_08[0x14];
    Vec unk_1C[13][13];
} unkSubstructR31;

typedef struct bitcopy {
    struct {
        u8 field00_bit0 : 1;
        u8 field00_bit1 : 3;
        u8 field00_bit4 : 2;
        u8 field00_bit6 : 1;
        u8 field00_bit7 : 1;
    };
    struct {
        u8 field01_bit0 : 4;
    };
    u8 unk_02;
    s8 unk_03;
    s16 unk_04;
    u8 unk_06;
    u8 unk_07;
    f32 unk_08;
    unkSubstructR31* unk_0C;
} bitcopy;

// bss
static structActiveMG activeMG[4];
static s16 mgListAll[0x20];
static s16 mgPlay4P[8];

// data
static s32 mgSetupSprTbl[13] = {
    0x0007004B, 0x0007004C, 0x0007004D, 0x0007004E,
    0x0007004F, 0x00070052, 0x00070050, 0x00070051,
    0x00070053, 0x00070054, 0x00070055, 0x00070068,
    0x00070056
};
static Vec statusLayout4P[4] = {
    { 170.0f, 244.0f, 0.0f }, 
    { 406.0f, 244.0f, 0.0f },
    { 170.0f, 364.0f, 0.0f },
    { 406.0f, 364.0f, 0.0f },
};
static Vec statusLayout1Vs3[4] = {
    { 170.0f, 304.0f, 0.0f }, 
    { 406.0f, 224.0f, 0.0f },
    { 406.0f, 304.0f, 0.0f },
    { 406.0f, 384.0f, 0.0f },
};
static Vec statusLayout2Vs2[4] = {
    { 170.0f, 260.0f, 0.0f }, 
    { 170.0f, 348.0f, 0.0f },
    { 406.0f, 260.0f, 0.0f },
    { 406.0f, 348.0f, 0.0f },
};
static s32 luckyMessTbl[9] = {
    0x00140000, 0x00140005, 0x0014000A, 0x0014000F,
    0x00140014, 0x00140019, 0x00140000, 0x00140000,
    0x00140000
};

// sbss
static u8 mgType;
static s32 luckyF;
static f32 hilitePos;
static s16 mgNext;
static u8 mgPlay4PLen;
static u8 mgPlay1Vs3Len;
static u8 mgPlay2Vs2Len;
static u8 mgPlayBattleLen;
static s16 mgPlay1Vs3[3];
static s16 mgPlay2Vs2[3];
static s16 mgPlayBattle[2];
static u8 hiliteTimer;
static u8 hiliteBlinkLen;
static u8 hiliteShowF;
static omObjData* mgSetupObj;
static Process* mgSetupProc;


// sdata
static u8 luckyValue = 0xFF;
static s8 cursorPos = 0xFF;

// determined functions
static void DestroyMGSetup(void);
static void ExecMGSetup(void);
static void DetermineMGList(bitcopy*);
static void SetupStatusLayout(void);
static s32 GetMGType(void);
static s32 GetMGTypeTeam(void);
static void CreateMGSetup(void);
static void UpdateMGSetup(omObjData*);
static void CenterStatus(bitcopy*, omObjData*);
static void SeparateStatus(bitcopy*, omObjData*);
static void PopupVS(bitcopy*, omObjData*);
static void FallMGType(bitcopy*, omObjData*);
static void LuckyMGFall(bitcopy*, omObjData*);
static void HideLuckyValue(void);
static void UpdateLuckyValue(bitcopy*, omObjData*);
static void UpdateMGList(bitcopy*, omObjData*);

// FUNCTIONS //

void BoardMGSetupExec(void) {
    mgSetupProc = HuPrcChildCreate(&ExecMGSetup, 0x2006, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(mgSetupProc, &DestroyMGSetup);
    while (mgSetupProc != 0) {
        HuPrcVSleep();
    }
}

static void DestroyMGSetup(void) {
    GWSystem.player_curr = 0;
    mgSetupProc = NULL;
}

static inline s32 setupObjGet(void) {
    bitcopy* work = (bitcopy*) mgSetupObj->work;
    return work->field00_bit1;
}

static void ExecMGSetup(void) {
    s32 sp60[9] = {
        0x750000, 0x760000, 0x770000,
        0x780000, 0x790000, 0x7A0000,
        0x7B0000, 0x7C0000, 0x7D0000
    };
    Vec sp54;
    u16 var_r24;
    s32 var_r22;
    s32 var_r23;
    s32 var_r31;
    u32 var_r30;
    bitcopy* temp_r29;
    bitcopy* temp_r28;
    bitcopy* temp_r27;
    bitcopy* temp_r26;
    bitcopy* temp_r25;

    luckyF = 0;
    mgNext = 0;
    GWSystem.player_curr = -1;
	GWLuckyValueSet(1);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        activeMG[var_r31].unk_00 = -1;
        activeMG[var_r31].unk_04 = 0;
    }
    BoardPlayerMoveAwayStartCurr(GWPlayer[GWSystem.player_curr].space_curr, 1);
    BoardCameraMoveSet(0);
    BoardCameraTargetSpaceSet(BoardSpaceStarGetCurr());
    sp54.x = 0.0f;
    sp54.y = 150.0f;
    sp54.z = 0.0f;
    BoardCameraMotionStartEx(-1, NULL, &sp54, 1300.0f, -1.0f, 21);
    BoardCameraMotionWait();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 21);
    
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardFilterFadeInit(0x1E, 0xA0U);
    CreateMGSetup();
    while (setupObjGet() != 7) {
        HuPrcVSleep();
    }
    if (BoardRandMod(0x64U) < 5U) {
        HuPrcSleep(0x1E);
        luckyF = 1;
        temp_r29 = (bitcopy*) mgSetupObj->work;
        temp_r29->field00_bit1 = 4;
        temp_r29->unk_02 = 0;
        temp_r29->unk_03 = 0;
        temp_r29->unk_04 = 0;
        HuAudFXPlay(0x35C);
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
        temp_r28 = (bitcopy*) mgSetupObj->work;
        temp_r28->field00_bit1 = 1;
        temp_r28->unk_02 = 0;
        temp_r28->unk_03 = 0;
        temp_r28->unk_04 = 0;
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
        var_r30 = luckyMessTbl[GWBoardGet()];
        BoardWinCreate(2, var_r30, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
        temp_r27 = (bitcopy*) mgSetupObj->work;
        temp_r27->field00_bit1 = 5;
        temp_r27->unk_02 = 0;
        temp_r27->unk_03 = 0;
        temp_r27->unk_04 = 0;
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
        switch (GWLuckyValueGet()) {
            case 1:
                var_r30 = luckyMessTbl[GWBoardGet()] + 1;
                break;
            case 2:
                var_r30 = luckyMessTbl[GWBoardGet()] + 2;
                break;
            case 3:
                var_r30 = luckyMessTbl[GWBoardGet()] + 3;
                break;
        }
        BoardWinCreate(2, var_r30, BoardWinPortraitGetStar());
        BoardWinWait();
        var_r30 = luckyMessTbl[GWBoardGet()] + 4;
        BoardWinCreate(2, var_r30, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
        HideLuckyValue();
    } else {
        temp_r26 = (bitcopy*) mgSetupObj->work;
        temp_r26->field00_bit1 = 1;
        temp_r26->unk_02 = 0;
        temp_r26->unk_03 = 0;
        temp_r26->unk_04 = 0;
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
    }
    temp_r25 = (bitcopy*) mgSetupObj->work;
    temp_r25->field00_bit1 = 6;
    temp_r25->unk_02 = 0;
    temp_r25->unk_03 = 0;
    temp_r25->unk_04 = 0;
    while (setupObjGet() != 7) {
        HuPrcVSleep();
    }
    HuDataDirClose(0x70000);
    HuDataDirClose(0x20000);
    HuDataDirClose(sp60[GWBoardGet()]);
    HuPrcSleep(2);
    if (_CheckFlag(FLAG_ID_MAKE(0, 11)) != 0) {
        var_r23 = 0x140000;
    } else {
        var_r23 = mgInfoTbl[mgNext].data_dir;
    }
    var_r22 = BoardDataDirReadAsync(var_r23);
    BoardAudSeqFadeOut(0, 1000);
    _SetFlag(FLAG_ID_MAKE(1, 14));
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, -1);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXAllStop();
    _SetFlag(FLAG_ID_MAKE(1, 28));
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        BoardStatusItemHideSet(var_r31, 1);
    }
    ((bitcopy*) (mgSetupObj->work))->field00_bit0 = 1;
    BoardDataAsyncWait(var_r22);
    var_r24 = mgNext + 0x191;
    BoardMGSetupPlayPush(mgType, var_r24);
    GWMGTypeSet(-1);
    GWMGAvailSet(var_r24);
    GWSystem.mg_next = var_r24 - 0x191;
    _SetFlag(0x10002U);
    if (GWSystem.turn == GWSystem.max_turn) {
        _SetFlag(0xAU);
    }
    BoardNextOvlSet(3);
    HuPrcEnd();
}

static void DetermineMGList(bitcopy* arg0) {
    MgInfo* var_r31;
    s32 temp_r23;
    s32 var_r30;
    s16* var_r28;
    s32 var_r22;
    s32 var_r21;
    s32 var_r24;
    s32 var_r27;
    u32 temp_r20;
    s32 var_r29;
    u32 var_r19;
    s32 temp_r18;
    u32* temp_r26;
    s16* temp_r25;

    var_r24 = 0;
    var_r31 = mgInfoTbl;
    
    for (var_r27 = 0; var_r31->ovl != 0xFFFF; var_r31++, var_r27++) {
        if ((var_r31->flag & 1) == 0) {
            mgListAll[var_r24] = (var_r31 - mgInfoTbl) + 0x191;
            var_r24++;
        }
    }
    mgListAll[var_r24] = -1;
    temp_r26 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r27 * 4, 0x10000000U);
    temp_r25 = HuMemDirectMallocNum(HEAP_SYSTEM, var_r27 * 2, 0x10000000U);
    var_r31 = mgInfoTbl;
    
    for (var_r29 = var_r30 = 0; var_r30 < var_r27; var_r30++, var_r31++) {
        if ((mgType == var_r31->type) && (var_r31->ovl != 0x29)) {
            if ((GWMGListGet() != 2) || (GWMGCustomGet(var_r30 + 0x191) != 0)) {
                if (GWMGListGet() == 1) {
                    var_r21 = 0;
                    var_r28 = &mgListAll[0];
                    while (*var_r28 != -1) {
                        if (var_r30 + 0x191 == *var_r28) {
                            var_r21 = 1;
                            break;
                        }
                        var_r28++;
                    }
                    if (var_r21 != 0) continue;
                }
                temp_r26[var_r29] = var_r31->name_mess;
                temp_r25[var_r29] = var_r30;
                var_r29++;
            }
        }
    }

    var_r19 = var_r29;
    var_r30 = 0;
    while (var_r30 < arg0->field01_bit0) {
        var_r29 = BoardRandMod(var_r19);
        temp_r20 = temp_r26[var_r29];
        temp_r23 = temp_r25[var_r29];
        temp_r18 = temp_r23 + 0x191;

        if (GWMGListGet() == 2 || BoardMGSetupPlaySearch(mgType, temp_r18) == 0) {
            var_r22 = 0;
            for (var_r29 = 0; var_r29 < var_r30; var_r29++) {
                if (temp_r20 == activeMG[var_r29].unk_04) {
                    var_r22 = 1;
                    break;
                }
            }
            if (var_r22 == 0) {
                if (GWMGAvailGet(temp_r23 + 0x191) == 0) {
                    activeMG[var_r30].unk_03 = 0;
                } else {
                    activeMG[var_r30].unk_03 = 1;
                }
                activeMG[var_r30].unk_04 = temp_r20;
                activeMG[var_r30].unk_02 = temp_r23;
                var_r30++;
            }
        }
    }
    HuMemDirectFree(temp_r26);
    HuMemDirectFree(temp_r25);
}

static void SetupStatusLayout(void) {
    s32 var_r27;
    s32 var_r26;
    s32 var_r28;
    s32 var_r30;
    s32 var_r29;
    s32 var_r31;

    if (mgType != 0) {
        if (mgType == 1) {
            for (var_r28 = var_r31 = 0; var_r31 < 4; var_r31++) {
                if (GWPlayer[var_r31].color == 2) {
                    var_r27 = var_r31;
                    GWPlayer[var_r31].team_backup = GWPlayerTeamGet(var_r31);
                    GWPlayerCfg[var_r31].group = 0;
                    var_r28++;
                } else {
                    GWPlayer[var_r31].team_backup = GWPlayerTeamGet(var_r31);
                    GWPlayerCfg[var_r31].group = 1;
                    var_r26 = var_r31;
                }
            }
            if (var_r28 == 1) {
                BoardStatusTargetPosSet(var_r27, statusLayout1Vs3);
                var_r30 = 1;
                
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    if (var_r31 != var_r27) {
                        BoardStatusTargetPosSet(var_r31, &statusLayout1Vs3[var_r30++]);
                    }
                }
                return;
            }
            BoardStatusTargetPosSet(var_r26, statusLayout1Vs3);
            var_r29 = 1;
            
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (var_r31 == var_r26) {
                    GWPlayer[var_r31].team_backup = GWPlayerTeamGet(var_r31);
                    GWPlayerCfg[var_r31].group = 0;
                } else {
                    BoardStatusTargetPosSet(var_r31, &statusLayout1Vs3[var_r29++]);
                    GWPlayer[var_r31].team_backup = GWPlayerTeamGet(var_r31);
                    GWPlayerCfg[var_r31].group = 1;
                }
            }
            return;
        }
        var_r30 = 2;
        for (var_r29 = var_r31 = 0; var_r31 < 4; var_r31++) {
            if (GWPlayer[var_r31].color == 2) {
                BoardStatusTargetPosSet(var_r31, &statusLayout2Vs2[var_r29++]);
                GWPlayer[var_r31].team_backup = GWPlayerTeamGet(var_r31);
                GWPlayerCfg[var_r31].group = 0;
            } else {
                BoardStatusTargetPosSet(var_r31, &statusLayout2Vs2[var_r30++]);
                GWPlayer[var_r31].team_backup = GWPlayerTeamGet(var_r31);
                GWPlayerCfg[var_r31].group = 1;
            }
        }
    }
}

static s32 GetMGType(void) {
    s32 var_r27;
    s32 var_r28;
    s32 var_r30;
    s32 var_r31;
    s32 var_r25;
    s32 var_r26;
    s8 var_r29;

    for (var_r28 = var_r30 = var_r27 = var_r31 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayer[var_r31].color == 2) {
            var_r30++;
        } else if (GWPlayer[var_r31].color == 1) {
            var_r28++;
        } else {
            var_r27++;
        }
    }
    if ((var_r30 != 2) || (var_r28 != 2)) {
        if (var_r27 == 4) {
            var_r31 = BoardRandMod(4);
            GWPlayer[var_r31].color = 1;
            var_r27 = 3;
            var_r28 = 1;
            var_r30 = 0;
        }
        var_r26 = var_r25 = -1;
        if (var_r30 == 3) {
            var_r26 = 2;
            var_r25 = 1;
        } else if (var_r28 == 3) {
            var_r26 = 1;
            var_r25 = 2;
        }
        if (((var_r27 >= 3) || ((var_r27 == 2) && (var_r28 == 1) && (var_r30 == 1))) && (BoardRandMod(0x64U) > 0x28U)) {
            if (var_r30 == 1) {
                var_r29 = 2;
            } else {
                var_r29 = 1;
            }
            do {
                var_r31 = BoardRandMod(4);
            } while (GWPlayer[var_r31].color != 3);
            GWPlayer[var_r31].color = var_r29;
            if (var_r29 == 1) {
                var_r29 = 2;
            } else {
                var_r29 = 1;
            }
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if (GWPlayer[var_r31].color == 3) {
                    GWPlayer[var_r31].color = var_r29;
                }
            }
        } else {
            
            for (var_r31 = 0; var_r31 < 4; var_r31++) {
                if ((GWPlayer[var_r31].color == 3) || (GWPlayer[var_r31].color == 0)) {
                    if (var_r26 == -1) {
                        if (BoardRandMod(0x64) < 0x32) {
                            var_r29 = 2;
                        } else {
                            var_r29 = 1;
                        }
                    } else if (BoardRandMod(0x64) < 0x5A) {
                        var_r29 = var_r26;
                    } else {
                        var_r29 = var_r25;
                    }
                    GWPlayer[var_r31].color = var_r29;
                }
            }
        }
    }
    
    
    for (var_r30 = var_r28 = var_r31 = 0; var_r31 < 4; var_r31++) {
        if (GWPlayer[var_r31].color == 2) {
            var_r30++;
        } else if (GWPlayer[var_r31].color == 1) {
            var_r28++;
        }
    }

    if (var_r30 == 1 || var_r30 == 3) {
        return 1;
    } else if (var_r30 == 2) {
        return 2;
    } else {
        return 0;
    }
}

static void UnusedFloat(void)
{
	(void)288.0f;
	(void)-98.0f;
	(void)674.0f;
}

static s32 GetMGTypeTeam(void) {
    s8 sp12[4];
    s8 spE[4];
    s8 spA[4];
    s8 sp8[2] = { 2, 1 };
    s32 var_r30;
    s32 var_r31;
    s32 temp_r25;
    s8 var_r27;
    s8 var_r26;
    s8 var_r28;
    s8* var_r29; 

    spA[0] = spA[1] = spA[2] = spA[3] = -1;
    spE[0] = spE[1] = spE[2] = spE[3] = -1;
    sp12[0] = sp12[1] = sp12[2] = sp12[3] = -1;
    
    for (var_r28 = var_r27 = var_r26 = var_r31 = 0; var_r31 < 4; var_r31++) {
        switch (GWPlayer[var_r31].color) {
        case 2:
            sp12[var_r28] = var_r31;
            var_r28++;
            break;
        case 1:
            spE[var_r26] = var_r31;
            var_r26++;
            break;
        default:
            spA[var_r27] = var_r31;
            var_r27++;
            break;
        }
    }
    if (var_r27 != 0) {
        
        for (var_r31 = 0; var_r31 < var_r27; var_r31++) {
            GWPlayer[spA[var_r31]].color = sp8[BoardRandMod(2)];
        }
        return GetMGTypeTeam();
    }
    if ((var_r28 == 4) || (var_r26 == 4)) {
        return 0;
    }
    if ((var_r28 == 1) || (var_r26 == 1)) {
        if (var_r28 == 1) {
            var_r29 = sp12;
        } else {
            var_r29 = spE;
        }
        if (BoardRandMod(0x64U) < 0x46U) {
            var_r30 = BoardPlayerSameTeamFind(*var_r29);
            GWPlayer[*var_r29].color = GWPlayer[var_r30].color;
            return 0;
        }
        var_r30 = BoardPlayerSameTeamFind(*var_r29);
        GWPlayer[var_r30].color = GWPlayer[*var_r29].color;
        return 2;
    }
    var_r30 = BoardPlayerSameTeamFind(sp12[0]);
    if (GWPlayer[sp12[0]].color != GWPlayer[var_r30].color) {
        temp_r25 = GWPlayer[var_r30].color;
        GWPlayer[var_r30].color = GWPlayer[sp12[0]].color;

        
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if ((var_r31 != sp12[0]) && (var_r31 != var_r30)) {
                break;
            }
        }
        GWPlayer[var_r31].color = temp_r25;
        var_r30 = BoardPlayerSameTeamFind(var_r31);
        GWPlayer[var_r30].color = temp_r25;
    }
    return 2;
}

static void CreateMGSetup(void) {
    s32 var_r30;
    unkSubstructR31* temp_r31;
    bitcopy* temp_r28;
    bitcopy* temp_r29;

    mgSetupObj = omAddObjEx(boardObjMan, 0x200, 0U, 0U, -1, UpdateMGSetup);
    temp_r28 = (bitcopy*) mgSetupObj->work;
    temp_r28->field00_bit0 = 0;
    temp_r29 = (bitcopy*) mgSetupObj->work;
    temp_r29->field00_bit1 = 0;
    temp_r29->unk_02 = 0;
    temp_r29->unk_03 = 0;
    temp_r29->unk_04 = 0;
    temp_r28->unk_0C = HuMemDirectMallocNum(HEAP_SYSTEM, 0x154, 0x10000000U);
    temp_r31 = temp_r28->unk_0C;
    temp_r31->unk_00[0] = HuSprGrpCreate(0xD);
    
    for (var_r30 = 0; var_r30 < 13; var_r30++) {
        BoardSpriteCreate(mgSetupSprTbl[var_r30], 0x5DC, NULL, &temp_r31->unk_00[var_r30] + 1);
        HuSprGrpMemberSet(*temp_r31->unk_00, var_r30, *(&temp_r31->unk_00[var_r30] + 1));
        HuSprAttrSet(*temp_r31->unk_00, var_r30, 4);
        temp_r31->unk_1C[0][var_r30].x = temp_r31->unk_1C[0][var_r30].y = temp_r31->unk_1C[0][var_r30].z = 0.0f;
        temp_r31->unk_1C[1][var_r30].x = temp_r31->unk_1C[1][var_r30].y = temp_r31->unk_1C[1][var_r30].z = 0.0f;
    }
    HuSprGrpPosSet(temp_r31->unk_00[0], 288.0f, 240.0f);
}

static void UpdateMGSetup(omObjData* arg0) {
    bitcopy* var_r31;
    s32 var_r29;

    var_r31 = (bitcopy*) arg0->work;
    if (var_r31->field00_bit0 != 0 || BoardIsKill() != 0) {
        for (var_r29 = 0; var_r29 < 4; var_r29++) {
            if (activeMG[var_r29].unk_00 != -1) {
                HuWinKill(activeMG[var_r29].unk_00);
                activeMG[var_r29].unk_00 = -1;
            }
        }
        HuSprGrpKill(var_r31->unk_0C->unk_00[0]);
        HuMemDirectFree(var_r31->unk_0C);
        mgSetupObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
    } else if (var_r31->unk_06 != 0) {
        var_r31->unk_06--;
    } else {
        switch (var_r31->field00_bit1) {
            case 0:
                CenterStatus(var_r31, arg0);
                break;
            case 1:
                SeparateStatus(var_r31, arg0);
                break;
            case 2:
                PopupVS(var_r31, arg0);
                break;
            case 3:
                FallMGType(var_r31, arg0);
                break;
            case 4:
                LuckyMGFall(var_r31, arg0);
                break;
            case 5:
                UpdateLuckyValue(var_r31, arg0);
                break;
            case 6:
                UpdateMGList(var_r31, arg0);
                break;
				
			case 7:
				break;
        }
    }
}

static void CenterStatus(bitcopy* arg0, omObjData* arg1) {
    s32 var_r31;
    bitcopy* temp_r30;

    if (arg0->unk_02 == 0) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            BoardStatusItemHideSet(var_r31, 0);
            BoardStatusTargetPosSet(var_r31, &statusLayout4P[var_r31]);
        }
        arg0->unk_02 = 1;
        HuAudFXPlay(0x354);
        return;
    }
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (!BoardStatusStopCheck(var_r31)) {
            return;
        }
    }
    if ((s32) GWSystem.team != 0) {
        mgType = GetMGTypeTeam();
    } else {
        mgType = GetMGType();
    }
    if (mgType == 0) {
        arg0->field01_bit0 = 4;
    } else {
        arg0->field01_bit0 = 3;
    }
    SetupStatusLayout();
    DetermineMGList(arg0);
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        BoardTutorialHookExec(0x1A, 0);
    }
    temp_r30 = (bitcopy*) mgSetupObj->work;
    temp_r30->field00_bit1 = 2;
    temp_r30->unk_02 = 0;
    temp_r30->unk_03 = 0;
    temp_r30->unk_04 = 0;
}

static void SeparateStatus(bitcopy* arg0, omObjData* arg1) {
    Vec sp8;
    f32 temp_f30;
    f32 temp_f29;
    s32 var_r28;
    bitcopy* temp_r29;
    unkSubstructR31* temp_r27;

    temp_r27 = arg0->unk_0C;
    switch (arg0->unk_02) {
        case 0:
            for (var_r28 = 0; var_r28 < 4; var_r28++) {
                BoardStatusPosGet(var_r28, &sp8);
                if (sp8.x < 288.0f) {
                    sp8.x = -98.0f;
                } else {
                    sp8.x = 674.0f;
                }
                BoardStatusTargetPosSet(var_r28, &sp8);
            }
            arg0->unk_02 = 1;
            arg0->unk_03 = 0;
            return;
    case 1:
        if ((s8) arg0->unk_03 >= 0x5A) {
            arg0->unk_03 = 0;
            temp_r29 = (bitcopy*) mgSetupObj->work;
            temp_r29->field00_bit1 = 7;
            temp_r29->unk_02 = 0;
            temp_r29->unk_03 = 0;
            temp_r29->unk_04 = 0;
            return;
        }
        OSu8tof32((u8*)&arg0->unk_03, &temp_f29);
        temp_f30 = sin((temp_f29 * M_PI) / 180.0) * 4.0 + 1.0;
        arg0->unk_03 += 6;
        if (arg0->unk_03 > 0x5A) {
            arg0->unk_03 = 0x5A;
        }
        HuSprScaleSet(temp_r27->unk_00[0], 0, temp_f30, temp_f30);
        if (arg0->unk_03 > 0x3C) {
            HuSprTPLvlSet(temp_r27->unk_00[0], 0, (90.0f - arg0->unk_03) / 30.0f);
        }
    }
}

static void PopupVS(bitcopy* arg0, omObjData* arg1) {
    f32 var_f30;
    f32 temp_f31;
    bitcopy* temp_r28;
    unkSubstructR31* temp_r29;

    temp_r29 = arg0->unk_0C;
    if (arg0->unk_02 == 0) {
        HuSprAttrReset(temp_r29->unk_00[0], 0, 4);
        HuSprAttrSet(temp_r29->unk_00[0], 0, 8);
        HuSprScaleSet(temp_r29->unk_00[0], 0, 0.001f, 0.001f);
        HuSprPosSet(temp_r29->unk_00[0], 0, 0.0f, 64.0f);
        arg0->unk_02 = 1;
        HuAudFXPlay(0x355);
        return;
    }
    OSs16tof32(&arg0->unk_04, &temp_f31);
    if (arg0->unk_04 < 0x5A) {
        var_f30 = 2.0 * sin((M_PI * temp_f31) / 180.0);
    } else {
        var_f30 = 1.0 + sin((M_PI * temp_f31) / 180.0);
        if (arg0->unk_04 >= 0xB4) {
            var_f30 = 1.0f;
            temp_r28 = (bitcopy*) mgSetupObj->work;
            temp_r28->field00_bit1 = 3;
            temp_r28->unk_02 = 0;
            temp_r28->unk_03 = 0;
            temp_r28->unk_04 = 0;
            arg0->unk_06 = 0x3C;
        }
    }
    HuSprScaleSet(temp_r29->unk_00[0], 0, var_f30, var_f30);
    arg0->unk_04 += 9;
    if ((_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) && arg0->field00_bit1 == 3) {
        BoardTutorialHookExec(0x1B, 0);
        if (*boardTutorialData == 1) {
            arg0->field00_bit1 = 0;
        }
    }
}

static void FallMGType(bitcopy* arg0, omObjData* arg1) {
    Vec sp10;
    s16 sp8[3] = { 3, 1, 2 };
    Vec* temp_r4;
    Vec* temp_r5;
    s16 temp_r30;
    bitcopy* temp_r29;
    unkSubstructR31* temp_r31;

    temp_r31 = arg0->unk_0C;
    temp_r30 = sp8[mgType];
    if (arg0->unk_02 == 0) {
        HuSprAttrReset(temp_r31->unk_00[0], temp_r30, 4);
        temp_r31->unk_1C[0][temp_r30].y = -284.0f;
        temp_r31->unk_1C[1][temp_r30].y = -128.0f;
        arg0->unk_02 = 1;
    }
    VECSubtract(&temp_r31->unk_1C[1][temp_r30], &temp_r31->unk_1C[0][temp_r30], &sp10);
    if (VECMag(&sp10) <= 1.0f) {
        temp_r31->unk_1C[0][temp_r30] = temp_r31->unk_1C[1][temp_r30];
        temp_r29 = (bitcopy*) mgSetupObj->work;
        temp_r29->field00_bit1 = 7;
        temp_r29->unk_02 = 0;
        temp_r29->unk_03 = 0;
        temp_r29->unk_04 = 0;
    } else {
        VECScale(&sp10, &sp10, 0.1f);
        VECAdd(&sp10, &temp_r31->unk_1C[0][temp_r30], &temp_r31->unk_1C[0][temp_r30]);
    }
    HuSprPosSet(temp_r31->unk_00[0], temp_r30, temp_r31->unk_1C[0][temp_r30].x, temp_r31->unk_1C[0][temp_r30].y);
}

static void LuckyMGFall(bitcopy* arg0, omObjData* arg1) {
    u16 spC;
    u16 spA;
    s16 sp8[3] = { 3, 1, 2 };
    Vec* temp_r25;
    Vec* temp_r27;
    Vec* temp_r28;
    s16 temp_r24;
    bitcopy* temp_r26;
    u8 temp_r0;
    unkSubstructR31* temp_r29;
    f32 var_f30;
    
    temp_r29 = arg0->unk_0C;
    temp_r24 = sp8[mgType];
    temp_r28 = &temp_r29->unk_1C[0][4];
    temp_r25 = &temp_r29->unk_1C[1][4];
    temp_r27 = &temp_r29->unk_1C[0][temp_r24];
    switch (arg0->unk_02) {
        case 0:
            HuSprAttrReset(temp_r29->unk_00[0], 4, 4);
            temp_r28->y = -284.0f;
            temp_r25->y = -128.0f;
            arg0->unk_02 = 1;
            break;
        case 1:
            temp_r28->y += 10.0f;
            if (temp_r25->y < temp_r28->y) {
                arg0->unk_02 = 2;
                arg0->unk_03 = 0;
                temp_r28->y = temp_r25->y;
                HuAudFXPlay(0x35D);
            }
            break;
        case 2:
            temp_r27->y += 10.0f;
            if (328.0f < temp_r27->y) {
                HuSprAttrReset(temp_r29->unk_00[0], temp_r24, 4);
                temp_r26 = (bitcopy*) mgSetupObj->work;
                temp_r26->field00_bit1 = 7;
                temp_r26->unk_02 = 0;
                temp_r26->unk_03 = 0;
                temp_r26->unk_04 = 0;
            } else if (arg0->unk_03 < 0x1E) {
                OSs8tof32(&arg0->unk_03, &var_f30);
                HuSprZRotSet(temp_r29->unk_00[0], temp_r24, var_f30);
                arg0->unk_03++;
            }
            break;
    }
    HuSprPosSet(temp_r29->unk_00[0], 4, temp_r28->x, temp_r28->y);
    HuSprPosSet(temp_r29->unk_00[0], temp_r24, temp_r27->x, temp_r27->y);
}

static void HideLuckyValue(void) {
    f32 var_f31;
    bitcopy* temp;
    unkSubstructR31* temp_r31;

    temp = (bitcopy*) mgSetupObj->work;
    temp_r31 = temp->unk_0C;
    
    for (var_f31 = 1.0f; var_f31 > 0.1f; var_f31 -= 0.1f) {
        HuSprTPLvlSet(temp_r31->unk_00[0], 8, var_f31);
        HuSprTPLvlSet(temp_r31->unk_00[0], 9, var_f31);
        HuPrcVSleep();
    }
    HuSprAttrSet(temp_r31->unk_00[0], 8, 4);
    HuSprAttrSet(temp_r31->unk_00[0], 9, 4);
}

static void UpdateLuckyValue(bitcopy* arg0, omObjData* arg1) {
    s32 var_r23;
    f32 temp_f29;
    s32 temp_r3;
    bitcopy* temp_r26;
    unkSubstructR31* temp_r27;
    f32 temp_f28;
    u8 spC;

    temp_r27 = arg0->unk_0C;
    switch (arg0->unk_02) {
        case 0:
            HuSprAttrReset(temp_r27->unk_00[0], 8, 4);
            HuSprAttrReset(temp_r27->unk_00[0], 9, 4);
            HuSprAttrSet(temp_r27->unk_00[0], 8, 8);
            HuSprAttrSet(temp_r27->unk_00[0], 9, 8);
            HuSprPosSet(temp_r27->unk_00[0], 8, 0.0f, 0.0f);
            HuSprPosSet(temp_r27->unk_00[0], 9, 0.0f, 0.0f);
            HuSprScaleSet(temp_r27->unk_00[0], 8, 0.001f, 0.001f);
            HuSprScaleSet(temp_r27->unk_00[0], 9, 0.001f, 0.001f);
            HuSprBankSet(temp_r27->unk_00[0], 9, 1);
            arg0->unk_04 = 0;
            arg0->unk_02 = 1;
            arg0->unk_03 = 0;
            temp_r3 = BoardRandMod(0x64U);
            if (temp_r3 < 0x55) {
				GWLuckyValueSet(2);
                return;
            }
            if (temp_r3 >= 0x5F) return;
			GWLuckyValueSet(3);
            return;
        case 1:
            if (arg0->unk_03 < 0x5A) {
                OSu8tof32((u8*) &arg0->unk_03, &temp_f28);
                temp_f29 = sin((M_PI * temp_f28) / 180.0);
                HuSprScaleSet(temp_r27->unk_00[0], 8, temp_f29, temp_f29);
                HuSprScaleSet(temp_r27->unk_00[0], 9, temp_f29, temp_f29);
                arg0->unk_03 += 2;
                return;
            }
            arg0->unk_02 = 2;
            arg0->unk_06 = BoardRandMod(0xCU) + 0x12;
            arg0->unk_03 = 0;
            arg0->unk_08 = 0.8f;
            return;
        case 2:
            arg0->unk_08 *= 0.97f;
            hilitePos += arg0->unk_08;
            if (hilitePos >= 3.0f) {
                hilitePos = 0.0f;
            }
            OSf32tos8(&hilitePos, (s8*)&spC);
            if (spC != luckyValue) {
                HuAudFXPlay(0x304);
                luckyValue = spC;
            }
            HuSprBankSet(temp_r27->unk_00[0], 9, luckyValue);
            if (arg0->unk_08 < 0.05f) {
                if (luckyValue != GWLuckyValueGet() - 1) {
                    arg0->unk_08 *= 1.0309278f;
                    return;
                }
                HuAudFXPlay(0x305);
                HuAudFXPlay(0x357);
                HuAudFXPlay(0x358);
                arg0->unk_02 = 3;
                arg0->unk_03 = 0;
                arg0->unk_04 = 0;
                return;
            }
            break;
        case 3:
            arg0->unk_04 += 8;
            if (arg0->unk_04 >= 0x438) {
                temp_r26 = (bitcopy*) mgSetupObj->work;
                temp_r26->field00_bit1 = 7;
                temp_r26->unk_02 = 0;
                temp_r26->unk_03 = 0;
                temp_r26->unk_04 = 0;
                return;
            }
            temp_f28 = (arg0->unk_04 % 360);
            temp_f29 = (1.0 + (0.5 * sin((M_PI * temp_f28) / 180.0)));
            HuSprScaleSet(temp_r27->unk_00[0], 8, temp_f29, temp_f29);
            HuSprScaleSet(temp_r27->unk_00[0], 9, temp_f29, temp_f29);
            break;
    }
}

static f32 cursorYTbl[4] = {
    64.0f, 88.0f, 112.0f, 136.0f
};
static f32 hiliteYTbl[4] = {
    60.0f, 84.0f, 108.0f, 132.0f
};
static GXColor hiliteColTbl[3] = {
    { 0xF8, 0xF2, 0x13, 0x00 },
    { 0xF8, 0xF2, 0x13, 0x00 },
    { 0xF8, 0xF2, 0x13, 0x00 }
};

static void UpdateMGList(bitcopy* arg0, omObjData* arg1) {
    f32 sp18[2];
    s32 sp14;
    f32 var_f26;
    f32 var_f25;
    f32 var_f24;
    f32 temp_f27;
    s32 temp_r22;
    s16 temp_r3;
    s8 var_r17;
    GXColor* temp_r18;
    s32 var_r23;
    bitcopy* temp_r21;
    unkSubstructR31* temp_r24;
    
    temp_r24 = arg0->unk_0C;
    temp_r22 = mgType + 5;
    switch (arg0->unk_02) {                        /* irregular */
        case 0:
            HuSprAttrSet(temp_r24->unk_00[0], temp_r22, 8);
            HuSprAttrReset(temp_r24->unk_00[0], temp_r22, 4);
            HuSprPosSet(temp_r24->unk_00[0], temp_r22, 0.0f, 32.0f);
            HuSprScaleSet(temp_r24->unk_00[0], temp_r22, 0.001f, 0.001f);
            arg0->unk_04 = 0;
            arg0->unk_02 = 1;
            arg0->unk_03 = 0;
            hilitePos = 0.0f;
            
            for (var_r23 = 0; var_r23 < arg0->field01_bit0; var_r23++) {
                HuWinMesSizeCancelCRSet(1);
                HuWinMesMaxSizeGet(1, &sp18[0], activeMG[var_r23].unk_04);
                var_f25 = 152.0f;
                var_f24 = 280.0f + (var_r23 * 0x18);
                temp_r3 = HuWinCreate(var_f25, var_f24, sp18[0], sp18[1], 0);
                HuWinBGTPLvlSet(temp_r3, 0.0f);
                HuWinMesSpeedSet(temp_r3, 0);
                HuWinDispOff(temp_r3);
                HuWinAttrSet(temp_r3, 0x100);
                if (activeMG[var_r23].unk_03 != 0) {
                    sp14 = activeMG[var_r23].unk_04;
                } else {
                    sp14 = 0x90001;
                }
                HuWinMesSet(temp_r3, sp14);
                activeMG[var_r23].unk_00 = temp_r3;
            }
            return;
        case 1:
            if (arg0->unk_03 < 0x5A) {
                OSu8tof32((u8*) &arg0->unk_03, &var_f26);
                temp_f27 = sin((M_PI * var_f26) / 180.0);
                arg0->unk_03 += 3;
                HuSprScaleSet(temp_r24->unk_00[0], temp_r22, temp_f27, temp_f27);
                return;
            }
            
            for (var_r23 = 0; var_r23 < arg0->field01_bit0; var_r23++) {
                HuWinDispOn(activeMG[var_r23].unk_00);
            }
            HuSprAttrReset(temp_r24->unk_00[0], 0xA, 4);
            HuSprAttrSet(temp_r24->unk_00[0], 0xA, 8);
            HuSprPosSet(temp_r24->unk_00[0], 0xA, -148.0f, cursorYTbl[0]);
            temp_r18 = &hiliteColTbl[mgType];
            HuSprAttrReset(temp_r24->unk_00[0], 0xC, 4);
            HuSprPosSet(temp_r24->unk_00[0], 0xC, 0.0f, hiliteYTbl[0]);
            HuSprTPLvlSet(temp_r24->unk_00[0], 0xC, 0.7f);
            HuSprScaleSet(temp_r24->unk_00[0], 0xC, 32.0f, 3.5f);
            HuSprColorSet(temp_r24->unk_00[0], 0xC, temp_r18->r, temp_r18->g, temp_r18->b);
            arg0->unk_02 = 2;
            arg0->unk_03 = 0;
            arg0->unk_08 = 0.7f;
            arg0->unk_07 = 0x23 - BoardRandMod(0x1EU);
            return;
        case 2:
            hilitePos += arg0->unk_08;
            if (hilitePos >= arg0->field01_bit0) {
                hilitePos = 0.0f;
            }
            OSf32tos8(&hilitePos, &var_r17);
            if (var_r17 != cursorPos) {
                HuAudFXPlay(0x304);
                cursorPos = var_r17;
            }
            HuSprPosSet(temp_r24->unk_00[0], 0xA, -148.0f, cursorYTbl[cursorPos]);
            HuSprPosSet(temp_r24->unk_00[0], 0xC, 0.0f, hiliteYTbl[cursorPos]);
            if (arg0->unk_07 != 0) {
                arg0->unk_07--;
                return;
            }
            arg0->unk_02 = 3;
            return;
        case 3:
            arg0->unk_08 *= 0.97f;
            hilitePos += arg0->unk_08;
            if (hilitePos >= arg0->field01_bit0) {
                hilitePos = 0.0f;
            }
            OSf32tos8(&hilitePos, &var_r17);
            if (var_r17 != cursorPos) {
                HuAudFXPlay(0x304);
                cursorPos = var_r17;
            }
            HuSprPosSet(temp_r24->unk_00[0], 0xA, -148.0f, cursorYTbl[cursorPos]);
            HuSprPosSet(temp_r24->unk_00[0], 0xC, 0.0f, hiliteYTbl[cursorPos]);
            if (!(arg0->unk_08 < (0.02f + (0.02f * BoardRandFloat())))) return; // weird hacky garbage
            HuAudFXPlay(0x305);
            arg0->unk_02 = 4;
            arg0->unk_03 = 0;
            hiliteTimer = 0;
            hiliteShowF = 1;
            hiliteBlinkLen = 5;
            mgNext = activeMG[cursorPos].unk_02;
            HuWinMesSet(activeMG[cursorPos].unk_00, activeMG[cursorPos].unk_04);
            return;
        case 4:
            if (arg0->unk_03++ > 0x78U) {
                HuSprAttrSet(temp_r24->unk_00[0], 0xA, 4);
                HuSprAttrSet(temp_r24->unk_00[0], 0xC, 4);
                
                for (var_r23 = 0; var_r23 < arg0->field01_bit0; var_r23++) {
                    HuWinDispOff(activeMG[var_r23].unk_00);
                }
                arg0->unk_02 = 5;
                arg0->unk_03 = 0;
                return;
            }
            if (hiliteTimer < hiliteBlinkLen) {
                hiliteTimer++;
            } else {
                hiliteShowF ^= 1;
                hiliteTimer = 0;
            }
            if (hiliteShowF != 0) {
                HuSprAttrReset(temp_r24->unk_00[0], 0xC, 4);
                return;
            }
            HuSprAttrSet(temp_r24->unk_00[0], 0xC, 4);
            return;
        case 5:
            if (arg0->unk_03 < 0x5A) {
                OSu8tof32((u8*) &arg0->unk_03, &var_f26);
                temp_f27 = (1.0 + (2.0 * sin((M_PI * var_f26) / 180.0)));
                arg0->unk_03 += 4;
                if (arg0->unk_03 > 0x5A) {
                    arg0->unk_03 = 0x5A;
                }
                HuSprScaleSet(temp_r24->unk_00[0], temp_r22, temp_f27, temp_f27);
                if (arg0->unk_03 > 0x3C) {
                    HuSprTPLvlSet(temp_r24->unk_00[0], temp_r22, (90.0f - arg0->unk_03) / 30.0f);
                    return;
                }
            } else {
                HuSprAttrSet(temp_r24->unk_00[0], temp_r22, 4);
                
                for (var_r23 = 0; var_r23 < arg0->field01_bit0; var_r23++) {
                    HuWinDispOff(activeMG[var_r23].unk_00);
                }
                arg0->unk_03 = 0;
                arg0->unk_02 = 6;
                temp_r21 = (bitcopy*) mgSetupObj->work;
                temp_r21->field00_bit1 = 7;
                temp_r21->unk_02 = 0;
                temp_r21->unk_03 = 0;
                temp_r21->unk_04 = 0;
            }
            break;
    }
}

void BoardMGSetupPlayClear(void) {
    mgPlay4PLen = mgPlay1Vs3Len = mgPlay2Vs2Len = mgPlayBattleLen = 0;
    memset(mgPlay4P, 0, 0x10);
    memset(mgPlay1Vs3, 0, 6);
    memset(mgPlay2Vs2, 0, 6);
    memset(mgPlayBattle, 0, 4);
}

s32 BoardMGSetupPlaySearch(s32 arg0, s16 arg1) {
    s16* var_r31;
    s16 var_r30;
    s16 var_r29;

    switch (arg0) {
        case 0:
            var_r29 = 8;
            var_r31 = mgPlay4P;
            break;
        case 1:
            var_r29 = 3;
            var_r31 = mgPlay1Vs3;
            break;
        case 2:
            var_r29 = 3;
            var_r31 = mgPlay2Vs2;
            break;
        case 4:
            var_r29 = 2;
            var_r31 = mgPlayBattle;
            break;
        default:
            return 0;
    }
    
    var_r30 = 0;
    while (var_r30 < var_r29) {
        if (arg1 == var_r31[var_r30]) {
            return 1;
        }
        var_r30++;
    }
    return 0;
}

void BoardMGSetupPlayPush(s32 arg0, s16 arg1) {
    s16 var_r29;
    s16 temp_r28;
    u8* var_r31;
    s16* var_r30;

    switch (arg0) {                                 /* irregular */
    case 0:
        var_r31 = &mgPlay4PLen;
        var_r29 = 8;
        var_r30 = mgPlay4P;
        break;
    case 1:
        var_r31 = &mgPlay1Vs3Len;
        var_r29 = 3;
        var_r30 = mgPlay1Vs3;
        break;
    case 2:
        var_r31 = &mgPlay2Vs2Len;
        var_r29 = 3;
        var_r30 = mgPlay2Vs2;
        break;
    case 4:
        var_r31 = &mgPlayBattleLen;
        var_r29 = 2;
        var_r30 = mgPlayBattle;
        break;
    default:
        return;
    }
    temp_r28 = *var_r31;
    var_r30[temp_r28] = arg1;
    *var_r31 = temp_r28 + 1;
    if (*var_r31 >= var_r29) {
        *var_r31 = 0;
    }
    return;
}

void BoardMGSetupTutorialExec(void) {
    s32 spC;
    s32 sp8;
    s16 var_r30;
    s16* temp_r31;
    s32 temp_r0;
    s32 var_r26;
    bitcopy* temp_r24;
    bitcopy* temp_r25;
    bitcopy* temp_r27;
    bitcopy* temp_r29;
    bitcopy* temp_r28;

    *boardTutorialData = 1;
    BoardFilterFadeInit(0x1E, 0xA0U);
    
    for (var_r26 = 0; var_r26 < 4; var_r26++) {
        activeMG[var_r26].unk_00 = -1;
        activeMG[var_r26].unk_04 = 0;
    }
    
    CreateMGSetup();
    while (setupObjGet() != 7) {
        HuPrcVSleep();
    }
    temp_r29 = (bitcopy*) mgSetupObj->work;
    temp_r29->field00_bit1 = 1;
    temp_r29->unk_02 = 0;
    temp_r29->unk_03 = 0;
    temp_r29->unk_04 = 0;
    while (setupObjGet() != 7) {
        HuPrcVSleep();
    }
    temp_r28 = (bitcopy*) mgSetupObj->work;
    temp_r28->field00_bit1 = 6;
    temp_r28->unk_02 = 0;
    temp_r28->unk_03 = 0;
    temp_r28->unk_04 = 0;
    while (setupObjGet() != 7) {
        HuPrcVSleep();
    }
    temp_r24 = (bitcopy*) mgSetupObj->work;
    temp_r24->field00_bit0 = 1;
    BoardFilterFadeOut(0x1E);
    HuPrcSleep(0x1E);
}
