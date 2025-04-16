#include "game/process.h"
#include "game/gamework_data.h"
#include "game/board/item.h"
#include "game/object.h"
#include "game/board/main.h"
#include "game/board/player.h"
#include "game/board/ui.h"
#include "game/board/model.h"

#include "game/objsub.h"

#include "ext_math.h"
#include "math.h"

#include <game/audio.h>
#include <game/board/tutorial.h>
#include <game/board/window.h>
#include <game/hsfex.h>

SHARED_SYM extern s32 boardTutorialData[4];


static void KillMushroom();
static void MushroomMain();
static void KillItemMdl(void);
static void MarkKillBox(void);
static void InitBox(s32 arg0);

static const float boxOfs[2] = {-150.0f, 150.0f};
static omObjData *boxObj[2] = {NULL, NULL};
static s16 itemMdl = -1;
static s8 itemResult;
static u8 pickerChoice;
static omObjData* itemGiveObj;
static Process* mushroomProc;

void BoardMushroomExec(s32 arg0) {
    omVibrate(arg0, 0xC, 6, 6);
    mushroomProc = HuPrcChildCreate(MushroomMain, 0x2003U, 0x3800U, 0, boardMainProc);
    HuPrcDestructorSet2(mushroomProc, KillMushroom);
    
    while (mushroomProc != NULL) {
        HuPrcVSleep();
    }
    
    GWPlayer[arg0].color = 3;
}


typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
        u8 unk00_field2 : 3;
        u8 unk00_field5 : 2;
        u8 unk00_field7 : 1;
    };
    char unk01[1];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    f32 unk_08;
} boxObjWork;

static void SetBoxHide(s32 arg0);
static void SetBoxCenter(s32 arg0);
static void SetBoxShow(s32 arg0);
static void WaitBoxOpen(s32 arg0);
static void WaitBoxCenter(s32 arg0);
static s32 CheckBox(void);
static void StartItemGive(s32 arg0);
static void ShowItemMdl(void);
static void WaitItemGive(void);

static void MushroomMain(void) {
    Vec sp14[2];
    Vec sp8;
    s32 curPlayer;
    s8 var_r29;
    boxObjWork* box;
    s32 var_r27;
    s32 var_r26;
    s32 i;

    var_r29 = -1;
    curPlayer = GWSystem.player_curr;
    BoardCameraViewSet(3);
    HuAudFXPlay(0x34A);
    BoardPlayerMotBlendSet(curPlayer, 0, 15);
    
    while (BoardPlayerMotBlendCheck(curPlayer) == 0) {
        HuPrcVSleep();
    }
    
    BoardCameraMotionWait();
    BoardPlayerIdleSet(curPlayer);
    
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        BoardTutorialHookExec(13, 0);
        boardTutorialData[0] = 0;
    }
    
    if ((GWSystem.max_turn - GWSystem.turn) == 0) {
        BoardWinCreate(0, MAKE_MESSID(5, 3), -1);
        BoardWinWait();
        BoardWinKill();
    } else if (BoardPlayerItemCount(curPlayer) == 3) {
        BoardWinCreate(0, MAKE_MESSID(5, 0), -1);
        BoardWinWait();
        BoardWinKill();
    } else {
        while (1) {
            InitBox(curPlayer);
            
            while (CheckBox() == 0) {
                HuPrcVSleep();
            }
    
            for (i = 0; i < 2; i++) {
                box = OM_GET_WORK_PTR(boxObj[i], boxObjWork);
                BoardModelPosGet(box->unk_02, &sp8);
                Hu3D3Dto2D(&sp8, 1, &sp14[i]);
                sp14[i].y += 32.0f;
                sp14[i].z = 0.0f;
            }
            
            if (GWPlayer[curPlayer].com != 0) {
                BoardRand();
                var_r26 = 0; //inline?
                var_r29 = var_r26;
                if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
                    var_r29 = 0;
                }
            }
            
            BoardPickerCreate(curPlayer, 2, &sp14[0], var_r29);
            BoardPickerBackFlagSet(0);
            
            while (BoardPickerDoneCheck() == 0) {
                HuPrcVSleep();
            }
            
            pickerChoice = BoardPickerChoiceGet();
            SetBoxShow(pickerChoice);
            SetBoxHide(pickerChoice ^ 1);
            WaitBoxCenter(pickerChoice);
            BoardPlayerMotionStart(curPlayer, 11, 0);
            
            while (BoardPlayerMotionTimeGet(curPlayer) < 27.0f) {
                HuPrcVSleep();
            }
            
            HuAudFXPlay(0x30C);
            StartItemGive(curPlayer);
            WaitBoxOpen(pickerChoice);
            ShowItemMdl();
            SetBoxCenter(pickerChoice);
            
            while (BoardPlayerMotionEndCheck(curPlayer) == 0) {
                HuPrcVSleep();
            }
            
            WaitItemGive();
            
            if (itemResult != 0) {
                var_r27 = MAKE_MESSID(5, 1);
            } else {
                var_r27 = MAKE_MESSID(5, 2);
            }
            
            BoardPlayerMotionShiftSet(curPlayer, 0xC, 0.0f, 4.0f, HU3D_MOTATTR_NONE);
            HuPrcSleep(4);
            BoardWinCreate(0, var_r27, -1);
            BoardWinWait();
            BoardWinKill();
            MarkKillBox();
            BoardPlayerMotionEndWait(curPlayer);
            BoardPlayerIdleSet(curPlayer);
            if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
                BoardPlayerIdleSet(curPlayer);
                BoardTutorialHookExec(14, 0);
                if (++boardTutorialData[0] < 2) {
                    KillItemMdl();
                    continue;
                }
            }
            break;
        }
    }
    HuPrcEnd();
}

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
        u8 unk00_field2 : 3;
        u8 unk00_field5 : 2;
        u8 unk00_field7 : 1;
    };
    char unk01[1];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    f32 unk_08;
} ItemGiveWork2;

static void KillMushroom(void) {
    ItemGiveWork2* temp_r31;

    MarkKillBox();
    
    if (itemGiveObj) {
        temp_r31 = OM_GET_WORK_PTR(itemGiveObj, ItemGiveWork2);
        temp_r31->unk00_field0 = 1;
    }
    
    KillItemMdl();
    mushroomProc = NULL;
}

typedef struct {
    struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 2;
        u8 unk00_field2 : 5;
    };
    char unk01[1];
    s16 unk_02;
    f32 unk_04;
    f32 unk_08;
} itemObjWork;

static void CenterBox(ItemGiveWork2*, omObjData*);
static void ExitBox(ItemGiveWork2* arg0, omObjData* arg1);
static void HideBox(ItemGiveWork2*, omObjData*);
static void ShowBox(ItemGiveWork2*, omObjData*);


static void BoxMain(omObjData* arg0) {
    ItemGiveWork2* temp_r30;

    temp_r30 = OM_GET_WORK_PTR(arg0, ItemGiveWork2);

    if ((temp_r30->unk00_field0) || (BoardIsKill() != 0)) {
        BoardModelKill(temp_r30->unk_02);
        boxObj[temp_r30->unk00_field1] = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    switch (temp_r30->unk00_field2) {
    case 0:
        ShowBox(temp_r30, arg0);
        break;
    case 2:
        CenterBox(temp_r30, arg0);
        break;
    case 3:
        ExitBox(temp_r30, arg0);
        break;
    case 4:
        HideBox(temp_r30, arg0);
        break;
    }
    BoardModelPosSet(temp_r30->unk_02, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotSet(temp_r30->unk_02, arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

static void ShowBox(ItemGiveWork2* arg0, omObjData* arg1) {
    Vec sp8;

    BoardPlayerPosGet(arg0->unk00_field5, &sp8);
    sp8.y += 300.0f;
    
    if (arg0->unk_08 >= 90.0f) {
        arg0->unk_08 = 90.0f;
        arg0->unk00_field7 = 1;
        arg0->unk00_field2 = 1;
    }
    
    OSs16tof32(&arg0->unk_06, &arg1->rot.y);
    arg1->trans.y = (sp8.y + (700.0f * cosd(arg0->unk_08)));
    arg0->unk_08 += 1.5f;
    arg0->unk_06 += 30;
}


static void ExitBox(ItemGiveWork2* arg0, omObjData* arg1) {
    Vec spC;
    s16 sp8;
    f32 temp;

    sp8 = (arg0->unk_06 % 360);
    OSs16tof32(&sp8, &temp);
    BoardPlayerPosGet(arg0->unk00_field5, &spC);
    spC.y += 300.0f;

    if (arg0->unk_08 <= 0.0f) {
        arg0->unk_08 = 0.0f;
        arg0->unk00_field2 = 1;
    }

    arg1->trans.y = spC.y + (700.0f * cosd(arg0->unk_08));
    arg1->rot.y = sind(temp);
    arg0->unk_08 -= 1.5f;
    arg0->unk_06 -= 30;
}

static void HideBox(ItemGiveWork2* arg0, omObjData* arg1) {
    arg0->unk_04 -= 4;

    if (arg0->unk_04 < 0) {
        arg0->unk00_field2 = 1;
        arg0->unk_04 = 0;
    }

    BoardModelAlphaSet(arg0->unk_02, arg0->unk_04);
}

static void CenterBox(ItemGiveWork2* arg0, omObjData* arg1) {
    Vec sp20;
    Vec sp14;
    Vec sp8;

    sp14.x = arg1->trans.x;
    sp14.y = arg1->trans.y;
    sp14.z = arg1->trans.z;
    BoardPlayerPosGet(arg0->unk00_field5, &sp20);
    VECSubtract(&sp20, &sp14, &sp8);
    VECScale(&sp8, &sp8, 0.2f);
    VECAdd(&sp8, &sp14, &sp14);

    if (BoardVecMaxDistXZCheck(&sp20, &sp14, 3.0f) != 0) {
        arg1->trans.x = sp20.x;
        arg1->trans.z = sp20.z;
        arg0->unk00_field2 = 1;
    }
    
    arg1->trans.x = sp14.x;
    arg1->trans.z = sp14.z;
}

static void InitBox(s32 arg0) {
    Vec sp10;
    s32 sp8[2] = {DATA_MAKE_NUM(DATADIR_BOARD, 0x6D), DATA_MAKE_NUM(DATADIR_BOARD, 0x6E)};
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 i;
    boxObjWork* temp_r31;

    BoardPlayerPosGet(arg0, &sp10);

    for (i = 0; i < 2; i++) {
        boxObj[i] = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, BoxMain);
        temp_r31 = OM_GET_WORK_PTR(boxObj[i], boxObjWork);
        temp_r31->unk00_field0 = 0;
        temp_r31->unk00_field7 = 0;
        temp_r31->unk00_field5 = arg0;
        temp_r31->unk00_field1 = i;
        temp_r31->unk00_field2 = 0;
        temp_r31->unk_06 = 0;
        temp_r31->unk_08 = 0.0f;
        temp_r31->unk_04 = 0xFF;
        boxObj[i]->trans.x = sp10.x + boxOfs[i];
        boxObj[i]->trans.y = 700.0f + sp10.y;
        boxObj[i]->trans.z = sp10.z;
        boxObj[i]->rot.x = 0.0f;
        boxObj[i]->rot.y = 180.0f;
        boxObj[i]->rot.z = 0.0f;
        temp_r31->unk_02 = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 5), NULL, 0);
        BoardModelPosSet(temp_r31->unk_02, boxObj[i]->trans.x, boxObj[i]->trans.y, boxObj[i]->trans.z);
        BoardModelMotionSpeedSet(temp_r31->unk_02, 0.0f);
        BoardModelLayerSet(temp_r31->unk_02, 2U);        
    }
    
    HuAudFXPlay(0x340);
    if (BoardRandFloat() < 0.5f) {
        var_r28 = 0;
    } else {
        var_r28 = 1;
    }
    itemResult = (s8) var_r28;
    if (BoardRandFloat() < 0.5f) {
        var_r27 = 0;
    } else {
        var_r27 = 1;
    }
    var_r29 = var_r27;
    if (GWBoardGet() == BOARD_ID_EXTRA2) {
        itemResult = 0;
    }
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        itemResult = (boardTutorialData[0] ^ 1);
        var_r29 = 0;
    }
    itemMdl = BoardModelCreate(sp8[itemResult], NULL, 0);
    BoardModelVisibilitySet(itemMdl, 0);
    temp_r31 = OM_GET_WORK_PTR(boxObj[var_r29], boxObjWork);
    BoardModelScaleSet(temp_r31->unk_02, 1.5f, 1.5f, 1.5f);
}

static void MarkKillBox(void) {
    s32 i;
    boxObjWork* temp_r30;

    for (i = 0; i < 2; i++) {
        if (boxObj[i]) {
            temp_r30 = OM_GET_WORK_PTR(boxObj[i], boxObjWork);
            temp_r30->unk00_field0 = 1;            
        }
    }
}

static void SetBoxHide(s32 arg0) {
    boxObjWork* temp_r31 = OM_GET_WORK_PTR(boxObj[arg0], boxObjWork);

    temp_r31->unk00_field2 = 3;
}

static void SetBoxCenter(s32 arg0) {
    boxObjWork* temp_r31 = OM_GET_WORK_PTR(boxObj[arg0], boxObjWork);
    
    temp_r31->unk00_field2 = 4;
    HuAudFXPlay(0x341);
}

static void SetBoxShow(s32 arg0) {
    boxObjWork* temp_r31 = OM_GET_WORK_PTR(boxObj[arg0], boxObjWork);

    temp_r31->unk00_field2 = 2;
}

static void WaitBoxOpen(s32 arg0) {
    boxObjWork* temp_r31 = OM_GET_WORK_PTR(boxObj[arg0], boxObjWork);
    
    BoardModelMotionSpeedSet(temp_r31->unk_02, 2.0f);
    do {
        HuPrcVSleep();
    } while (BoardModelMotionEndCheck(temp_r31->unk_02) == 0);
}

static void WaitBoxCenter(s32 arg0) {
    boxObjWork* temp_r31 = OM_GET_WORK_PTR(boxObj[arg0], boxObjWork);

    while (temp_r31->unk00_field2 != 1) {
        HuPrcVSleep();
    }
}

static s32 CheckBox(void) {
    s32 i;
    boxObjWork* box;
    
    for (i = 0; i < 2; i++) {
        box = OM_GET_WORK_PTR(boxObj[i], boxObjWork);
        if (box->unk00_field7 == 0) {
            return 0;
        }
    }
    return 1;
}

static void DoItemGive(omObjData* arg0) {
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    s32 sp8[2] = {0, 1};
    itemObjWork* temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, itemObjWork);
    
    if ((temp_r31->unk00_field0 != 0) || (BoardIsKill() != 0)) {
        KillItemMdl();
        itemGiveObj = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    
    BoardModelPosGet(itemMdl, &sp28);
    BoardModelRotGet(itemMdl, &sp1C);
    BoardPlayerPosGet(temp_r31->unk00_field1, &sp10);
    sp10.y += 180.0f;
    
    switch (temp_r31->unk00_field2) {
    case 2:
        if (temp_r31->unk_02 < 12) {
            temp_r31->unk_04 += 1.47f;
            sp28.y += temp_r31->unk_04;
        } else if (temp_r31->unk_02 <= 24) {
            BoardModelRotSet(itemMdl, 30.0f * temp_r31->unk_02, 0.0f, 0.0f);
        } else if (temp_r31->unk_02 > 36) {
            temp_r31->unk00_field2 = 0;
            return;
        }
        temp_r31->unk_02++;
        break;
    case 0:
        temp_r31->unk_04 += -1.47f;
        
        if (temp_r31->unk_08 > 0.001f) {
            temp_r31->unk_08 -= 0.005f;
        }
        
        sp28.y += temp_r31->unk_04;
        
        if (sp10.y > sp28.y) {
            BoardModelVisibilitySet(itemMdl, 0);
            HuAudFXPlay(0x30D);
            BoardPlayerItemAdd(temp_r31->unk00_field1, sp8[itemResult]);
            temp_r31->unk00_field2 = 1;
        }
        /* fallthrough */
        case 1:
        default:
            break;
    }

    BoardModelPosSetV(itemMdl, &sp28);
    BoardModelScaleSet(itemMdl, temp_r31->unk_08, temp_r31->unk_08, temp_r31->unk_08);
}

static void StartItemGive(s32 arg0) {
    Vec spC;
    itemObjWork* temp_r31;
    boxObjWork* box;

    itemGiveObj = omAddObjEx(boardObjMan, 0x102, 0U, 0U, -1, DoItemGive);
    temp_r31 = OM_GET_WORK_PTR(itemGiveObj, itemObjWork);

    temp_r31->unk00_field0 = 0;
    temp_r31->unk00_field1 = arg0;
    temp_r31->unk00_field2 = 1;
    temp_r31->unk_02 = 0;
    temp_r31->unk_04 = 0.0f;
    temp_r31->unk_08 = 1.0f;
    box = OM_GET_WORK_PTR(boxObj[pickerChoice], boxObjWork);
    BoardModelPosGet(box->unk_02, &spC);
    BoardModelPosSetV(itemMdl, &spC);
}

static void KillItemMdl(void) {
    if (itemMdl != -1) {
        BoardModelKill(itemMdl);
        itemMdl = -1;
    }
}

static void ShowItemMdl(void) {
    itemObjWork* temp_r31 = OM_GET_WORK_PTR(itemGiveObj, itemObjWork);
    temp_r31->unk00_field2 = 2;

    BoardModelVisibilitySet(itemMdl, 1);
}

static void WaitItemGive(void) {
    itemObjWork* temp_r31 = OM_GET_WORK_PTR(itemGiveObj, itemObjWork);

    while (temp_r31->unk00_field2 != 1) {
        HuPrcVSleep();
    }
}
