#include "REL/option.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/sprite.h"
#include "game/window.h"

#include "dolphin.h"
#include "ext_math.h"
#include "version.h"

#ifndef __MWERKS__
#include "game/gamework.h"
#endif

#define RECORD_TYPE_BOARD 0
#define RECORD_TYPE_MG 1

#define CHARACTERS_MAX 8
#define BOARDS_MAX 6

#define PLAY_COUNT_NUM_DIGITS 4
#define WIN_COUNT_NUM_DIGITS 3
#define MAX_COINS_NUM_DIGITS 4
#define MAX_STARS_NUM_DIGITS 4
#define MG_SCORE_NUM_DIGITS 8
#define MG_TIME_NUM_DIGITS 8

#define DISPLAY_TYPE_TIME 0
#define DISPLAY_TYPE_SCORE 1

typedef struct {
    /* 0x00 */ s32 playCount;
    /* 0x04 */ s32 winCount[8];
    /* 0x24 */ s32 maxCoins;
    /* 0x28 */ s32 maxStars;
} BoardRecordData; // Size 0x2C

typedef struct {
    /* 0x000 */ omObjData *system;
    /* 0x004 */ omObjData *hand;
    /* 0x008 */ OptionWindow *window[10];
    /* 0x030 */ s32 execMode;
    /* 0x034 */ s16 sprList[153];
    /* 0x166 */ s16 unk166[3];
    /* 0x16C */ s32 recordType;
    /* 0x170 */ s32 board;
    /* 0x174 */ s32 mgPage;
    /* 0x178 */ BoardRecordData boardRecord[6];
    /* 0x280 */ s32 mgRecord[6];
    /* 0x298 */ s32 cameraDoneF;
    /* 0x29C */ s32 changeTimer;
} RecordWork; // Size 0x2A0

typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 mess;
    /* 0x08 */ s32 displayType;
} MGTable; // Size 0x0C

#define MODE_DISABLED 0
#define MODE_HANDLE_RECORD 1

static void ExecRecord(omObjData *object);
static omObjData *CreateSystem(void);
static void KillSystem(omObjData *object);
static void StartSystemMotion(omObjData *object, s32 type);
static omObjData *CreateHand(void);
static void KillHand(omObjData *object);
static void CreateSpr(omObjData *object);
static void KillSpr(omObjData *object);
static s32 GetDigit(s32 value, s32 place);
static void ShowBoard(omObjData *object, s32 board);
static void HideBoard(omObjData *object);
static void ShowTotal(omObjData *object);
static void HideTotal(omObjData *object);
static void ShowMG(omObjData *object, s32 page);
static void HideMG(omObjData *object);

omObjData *optionRecord;

static const s32 mgRecordIdxTbl[] = { 0, 1, 2, 3, 5, 10 };

static omObjFunc execModeTbl[] = { NULL, ExecRecord };

omObjData *OptionRecordCreate(void)
{
    omObjData *object;
    RecordWork *work;
    s32 i;
    s32 character;

    object = omAddObjEx(optionObjMan, 1003, 0, 0, 1, NULL);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(RecordWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    for (i = 0; i < BOARDS_MAX; i++) {
        work->boardRecord[i].playCount = GWBoardPlayCountGet(i);
        work->boardRecord[i].maxStars = GWBoardMaxStarsGet(i);
        work->boardRecord[i].maxCoins = GWBoardMaxCoinsGet(i);
        for (character = 0; character < CHARACTERS_MAX; character++) {
            work->boardRecord[i].winCount[character] = GWBoardWinCountGet(character, i);
        }
    }
    for (i = 0; i < BOARDS_MAX; i++) {
        work->mgRecord[i] = GWMGRecordGet(mgRecordIdxTbl[i]);
    }
    work->board = 0;
    work->mgPage = 0;
    work->recordType = RECORD_TYPE_BOARD;
    work->system = CreateSystem();
    work->hand = CreateHand();
    CreateSpr(object);
    OptionRecordExecModeSet(object, MODE_DISABLED);
    return object;
}

void OptionRecordKill(omObjData *object)
{
    RecordWork *work = object->data;

    KillSystem(work->system);
    KillHand(work->hand);
    KillSpr(object);
    HuMemDirectFree(work);
}

void OptionRecordExecModeSet(omObjData *object, s32 execMode)
{
    RecordWork *work = object->data;

    work->execMode = execMode;
    object->func = execModeTbl[execMode];
    object->unk10 = 0;
    object->unk10 = 0;
}

s32 OptionRecordExecModeGet(omObjData *object)
{
    RecordWork *work = object->data;

    return work->execMode;
}

static void ExecRecord(omObjData *object)
{
    RecordWork *work = object->data;
    Vec pos;
    s32 i;

    switch (object->unk10) {
        case 0:
            work->window[0] = OptionWinCreate(0);
            work->window[1] = OptionWinCreate(1);
            for (i = 0; i < 8; i++) {
                work->window[i + 2] = OptionWinCreate(3);
            }
            OptionCameraFocusSet(optionCamera, 519.0f, 125.0f, 300.0f, 0x28);
            OptionCameraTargetSet(optionCamera, 308.98f, 125.0f, 178.74f, 0x28);
            work->board = 0;
            work->mgPage = 0;
            work->cameraDoneF = 0;
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            if (OptionCameraDoneCheck(optionCamera) != 0) {
                break;
            }
            OptionRumbleMotionShowStart(optionRumble);
            espBankSet(work->sprList[47], 0);
            espBankSet(work->sprList[48], 2);
            espPosSet(work->sprList[47], 46.0f, 240.0f);
            espPosSet(work->sprList[48], 494.0f, 240.0f);
            if (work->recordType == RECORD_TYPE_BOARD) {
                OptionFadeSprite(work->sprList[47], 1, 10);
                OptionFadeSprite(work->sprList[48], 1, 10);
                work->changeTimer = 0;
            }
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            HideBoard(object);
            HideMG(object);
            HideTotal(object);
            switch (work->recordType) {
                case RECORD_TYPE_BOARD:
                    if (work->board < 6) {
                        ShowBoard(object, work->board);
                    }
                    else {
                        ShowTotal(object);
                    }
                    OptionWinAnimIn(work->window[0]);
                    OptionWinMesSet(work->window[0], MAKE_MESSID(47, 5));
                    break;
                case RECORD_TYPE_MG:
                    ShowMG(object, work->mgPage);
                    OptionWinAnimIn(work->window[0]);
                    OptionWinMesSet(work->window[0], MAKE_MESSID(47, 6));
                    break;
            }
            OptionWinAnimIn(work->window[1]);
            OptionWinMesSet(work->window[1], MAKE_MESSID(47, 169));
            if (!work->cameraDoneF) {
                Hu3DModelAttrReset(work->hand->model[0], HU3D_ATTR_DISPOFF);
                work->cameraDoneF = TRUE;
            }
            pos.x = 505.0 * -sind(305);
            pos.z = 505.0 * cosd(305);
            pos.y = 144.0f - 14.0f * work->recordType;
            omSetTra(work->hand, pos.x, pos.y, pos.z);
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            if (work->changeTimer > 0) {
                work->changeTimer--;
                break;
            }
            espBankSet(work->sprList[47], 0);
            espBankSet(work->sprList[48], 2);
            object->unk10 = 4;
            /* fallthrough */
        case 4:
            if (work->window[1]->state != 0) {
                break;
            }
            if (OptionPadCheck(PAD_BUTTON_B)) {
                HuAudFXPlay(3);
                object->unk10 = 5;
            }
            else if (OptionPadDStkRepCheck(8) != 0 && work->recordType == RECORD_TYPE_MG) {
                work->recordType = RECORD_TYPE_BOARD;
                work->board = 0;
                StartSystemMotion(work->system, work->recordType);
                OptionFadeSprite(work->sprList[47], 1, 5);
                OptionFadeSprite(work->sprList[48], 1, 5);
                work->changeTimer = 5;
                HuAudFXPlay(0x83F);
                object->unk10 = 2;
            }
            else if (OptionPadDStkRepCheck(4) != 0 && work->recordType == RECORD_TYPE_BOARD) {
                work->recordType = RECORD_TYPE_MG;
                work->mgPage = 0;
                StartSystemMotion(work->system, work->recordType);
                OptionFadeSprite(work->sprList[47], 0, 5);
                OptionFadeSprite(work->sprList[48], 0, 5);
                work->changeTimer = 5;
                HuAudFXPlay(0x83F);
                object->unk10 = 2;
            }
            else {
                switch (work->recordType) {
                    case RECORD_TYPE_BOARD:
                        if (OptionPadCheck(PAD_TRIGGER_L)) {
                            if (--work->board < 0) {
                                work->board = 6;
                            }
                            if (GWGameStat.open_w06 == 0 && work->board == 5) {
                                work->board--;
                            }
                            HuAudFXPlay(0x840);
                            espBankSet(work->sprList[47], 1);
                            work->changeTimer = 10;
                            object->unk10 = 2;
                            return;
                        }
                        if (OptionPadCheck(PAD_TRIGGER_R)) {
                            if (++work->board >= 7) {
                                work->board = 0;
                            }
                            if (GWGameStat.open_w06 == 0 && work->board == 5) {
                                work->board++;
                            }
                            HuAudFXPlay(0x840);
                            espBankSet(work->sprList[48], 3);
                            work->changeTimer = 10;
                            object->unk10 = 2;
                        }
                        break;
                    case RECORD_TYPE_MG:
                        break;
                }
            }
            break;
        case 5:
            OptionRumbleMotionHideStart(optionRumble);
            if (work->recordType == RECORD_TYPE_BOARD) {
                OptionFadeSprite(work->sprList[47], 0, 10);
                OptionFadeSprite(work->sprList[48], 0, 10);
            }
            OptionWinAnimOut(work->window[0]);
            OptionWinAnimOut(work->window[1]);
            Hu3DModelAttrSet(work->hand->model[0], HU3D_ATTR_DISPOFF);
            object->unk10 = 6;
            /* fallthrough */
        case 6:
            if (work->window[1]->state == 0 && OptionRumbleMotionCheck(optionRumble) == 0) {
                for (i = 0; i < 10; i++) {
                    OptionWinKill(work->window[i]);
                }
                HideBoard(object);
                HideMG(object);
                HideTotal(object);
                OptionCameraFocusSet(optionCamera, 519.62f, 120.0f, 300.0f, 40);
                OptionCameraTargetSet(optionCamera, 0.0f, 120.0f, 0.0f, 0x28);
                OptionRecordExecModeSet(object, MODE_DISABLED);
            }
            break;
    }
}

static omObjData *CreateSystem(void)
{
    omObjData *object;

    object = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 1));
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(object->model[0], 0);
    Hu3DMotionStartEndSet(object->model[0], 0.0f, 6.0f);
    Hu3DMotionTimeSet(object->model[0], 6.0f);
    return object;
}

static void KillSystem(omObjData *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
}

static void StartSystemMotion(omObjData *object, s32 type)
{
    s16 model = object->model[0];

    switch (type) {
        case RECORD_TYPE_BOARD:
            Hu3DMotionStartEndSet(model, 0.0f, 6.0f);
            Hu3DMotionTimeSet(model, 0.0f);
            break;
        case RECORD_TYPE_MG:
            Hu3DMotionStartEndSet(model, 6.0f, 12.0f);
            Hu3DMotionTimeSet(model, 6.0f);
            break;
    }
    Hu3DModelAttrReset(object->model[0], HU3D_MOTATTR_PAUSE);
}

static omObjData *CreateHand(void)
{
    omObjData *object;

    object = omAddObjEx(optionObjMan, 1003, 1, 0, 1, NULL);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 14));
    Hu3DModelLayerSet(object->model[0], 2);
    Hu3DModelAttrSet(object->model[0], HU3D_MOTATTR_LOOP);
    omSetRot(object, 30.0f, 190.0f, 0.0f);
    omSetSca(object, 0.6f, 0.6f, 0.6f);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF);
    return object;
}

static void KillHand(omObjData *object)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(object->model[i]);
    }
}

#define SPR_TBL_SIZE 153

static const s32 sprTbl[SPR_TBL_SIZE] = {
    DATA_MAKE_NUM(DATADIR_OPTION, 55),
    DATA_MAKE_NUM(DATADIR_OPTION, 56),
    DATA_MAKE_NUM(DATADIR_OPTION, 57),
    DATA_MAKE_NUM(DATADIR_OPTION, 58),
    DATA_MAKE_NUM(DATADIR_OPTION, 59),
    DATA_MAKE_NUM(DATADIR_OPTION, 60),
    DATA_MAKE_NUM(DATADIR_OPTION, 61),
    DATA_MAKE_NUM(DATADIR_OPTION, 62),
    DATA_MAKE_NUM(DATADIR_OPTION, 50),
    DATA_MAKE_NUM(DATADIR_OPTION, 51),
    DATA_MAKE_NUM(DATADIR_OPTION, 66),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 52),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 53),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 19),
    DATA_MAKE_NUM(DATADIR_OPTION, 20),
    DATA_MAKE_NUM(DATADIR_OPTION, 21),
    DATA_MAKE_NUM(DATADIR_OPTION, 22),
    DATA_MAKE_NUM(DATADIR_OPTION, 23),
    DATA_MAKE_NUM(DATADIR_OPTION, 24),
    DATA_MAKE_NUM(DATADIR_OPTION, 25),
    DATA_MAKE_NUM(DATADIR_OPTION, 26),
    DATA_MAKE_NUM(DATADIR_OPTION, 27),
    DATA_MAKE_NUM(DATADIR_OPTION, 28),
    DATA_MAKE_NUM(DATADIR_OPTION, 29),
    DATA_MAKE_NUM(DATADIR_OPTION, 30),
    DATA_MAKE_NUM(DATADIR_OPTION, 31),
    DATA_MAKE_NUM(DATADIR_OPTION, 32),
    DATA_MAKE_NUM(DATADIR_OPTION, 33),
    DATA_MAKE_NUM(DATADIR_OPTION, 34),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
    DATA_MAKE_NUM(DATADIR_OPTION, 54),
};

static void CreateSpr(omObjData *object)
{
    RecordWork *work = object->data;
    s32 i;

    for (i = 0; i < SPR_TBL_SIZE; i++) {
        work->sprList[i] = espEntry(sprTbl[i], 0, 0);
        espDrawNoSet(work->sprList[i], 0x40);
        espDispOff(work->sprList[i]);
    }
    espBankSet(work->sprList[47], 0);
    espBankSet(work->sprList[48], 2);
    HuSprExecLayerSet(0x40, 1);
}

static void KillSpr(omObjData *object)
{
    RecordWork *work = object->data;
    s32 i;

    for (i = 0; i < SPR_TBL_SIZE; i++) {
        espKill(work->sprList[i]);
    }
}

static s32 GetDigit(s32 value, s32 place)
{
    s32 i;

    i = 1;
    while (place-- != 0) {
        i *= 10;
    }
    return (value % (i * 10)) / i;
}

static void ShowBoard(omObjData *object, s32 board)
{
    RecordWork *work = object->data;
    s32 value;
    s32 i;
    s32 j;

    espPosSet(work->sprList[board], 275.0f, 72.0f);
    value = work->boardRecord[work->board].playCount;
    for (i = 0; i < PLAY_COUNT_NUM_DIGITS; i++) {
        espPosSet(work->sprList[i + 11], (VERSION_NTSC ? 323.0f : 392.0f) + 20.0f * i, 116.0f);
        if (value > 999) {
            espBankSet(work->sprList[i + 11], i + 10);
        }
        else {
            espBankSet(work->sprList[i + 11], GetDigit(value, 3 - i));
        }
    }
    espPosSet(work->sprList[8], 416.0f, 120.0f);
    value = work->boardRecord[work->board].maxCoins;
    for (i = 0; i < MAX_COINS_NUM_DIGITS; i++) {
        espPosSet(work->sprList[i + 15], (VERSION_NTSC ? 364.0f : 392.0f) + 20.0f * i, 268.0f);
        if (value > 999) {
            espBankSet(work->sprList[i + 15], i + 10);
        }
        else {
            espBankSet(work->sprList[i + 15], GetDigit(value, 3 - i));
        }
    }
#if VERSION_NTSC
    espPosSet(work->sprList[9], 456.0f, 268.0f);
#endif
    value = work->boardRecord[work->board].maxStars;
    for (i = 0; i < MAX_STARS_NUM_DIGITS; i++) {
        espPosSet(work->sprList[i + 19], (VERSION_NTSC ? 364.0f : 392.0f) + 20.0f * i, 312.0f);
        if (value > 999) {
            espBankSet(work->sprList[i + 19], i + 10);
        }
        else {
            espBankSet(work->sprList[i + 19], GetDigit(value, 3 - i));
        }
    }
#if VERSION_NTSC
    espPosSet(work->sprList[10], 456.0f, 312.0f);
#endif
    for (i = 0; i < CHARACTERS_MAX; i++) {
        espPosSet(work->sprList[i + 49], 92.0f + 50.0f * i, 200.0f);
        for (j = 0; j < WIN_COUNT_NUM_DIGITS; j++) {
            espPosSet(work->sprList[i * 3 + 23 + j], 80.0f + 50.0f * i + 12.0f * j, 230.0f);
            espBankSet(work->sprList[i * 3 + 23 + j], GetDigit(work->boardRecord[work->board].winCount[i], 2 - j));
        }
    }
    espPosSet(work->sprList[47], 48.0f, 240.0f);
    espPosSet(work->sprList[48], 492.0f, 240.0f);
    espDispOn(work->sprList[board]);
    for (i = 0; i < PLAY_COUNT_NUM_DIGITS; i++) {
        espDispOn(work->sprList[i + 11]);
    }
#if VERSION_NTSC
    espDispOn(work->sprList[8]);
#endif
    for (i = 0; i < MAX_COINS_NUM_DIGITS; i++) {
        espDispOn(work->sprList[i + 15]);
    }
#if VERSION_NTSC
    espDispOn(work->sprList[9]);
#endif
    for (i = 0; i < MAX_STARS_NUM_DIGITS; i++) {
        espDispOn(work->sprList[i + 19]);
    }
    espDispOn(work->sprList[10]);
    for (i = 0; i < CHARACTERS_MAX; i++) {
        espDispOn(work->sprList[i + 49]);
        for (j = 0; j < WIN_COUNT_NUM_DIGITS; j++) {
            espDispOn(work->sprList[i * 3 + 23 + j]);
        }
    }
    for (i = 0; i < 4; i++) {
        OptionWinDispOn(work->window[i + 2]);
    }
    OptionWinPosSet(work->window[2], 64.0f, 96.0f);
    OptionWinMesSet(work->window[2], MAKE_MESSID(47, 19));
    OptionWinPosSet(work->window[3], 64.0f, 140.0f);
    OptionWinMesSet(work->window[3], MAKE_MESSID(47, 20));
    OptionWinPosSet(work->window[4], 64.0f, 248.0f);
    OptionWinMesSet(work->window[4], MAKE_MESSID(47, 21));
    OptionWinPosSet(work->window[5], 64.0f, 292.0f);
    OptionWinMesSet(work->window[5], MAKE_MESSID(47, 22));
}

#define BOARD_SPR_HIDE_COUNT 53

static const s32 boardSprHideTbl[BOARD_SPR_HIDE_COUNT] = { 0, 1, 2, 3, 4, 5, 49, 50, 51, 52, 53, 54, 55, 56, 8, 9, 10, 11, 12, 13, 14, 23, 24, 25, 26,
    27, 28, 29, 30, 31, 32, 33, 34, 38, 39, 40, 35, 36, 37, 41, 42, 43, 44, 45, 46, 15, 16, 17, 18, 19, 20, 21, 22 };

static void HideBoard(omObjData *object)
{
    RecordWork *work = object->data;
    s32 i;

    for (i = 0; i < BOARD_SPR_HIDE_COUNT; i++) {
        espDispOff(work->sprList[boardSprHideTbl[i]]);
    }
    for (i = 0; i < 4; i++) {
        OptionWinDispOff(work->window[i + 2]);
    }
}

static void ShowTotal(omObjData *object)
{
    RecordWork *work = object->data;
    s32 winCount;
    s32 i;
    s32 j;

    espPosSet(work->sprList[6], 275.0f, 72.0f);
    for (i = 0; i < CHARACTERS_MAX; i++) {
        espPosSet(work->sprList[i + 57], 148.0f + 80.0f * (i % 4), 172.0f + 104.0f * (i / 4));
        for (j = 0, winCount = 0; j < BOARDS_MAX; j++) {
            winCount += work->boardRecord[j].winCount[i];
        }
        for (j = 0; j < WIN_COUNT_NUM_DIGITS; j++) {
            espPosSet(work->sprList[i * 3 + 65 + j], 132.0f + 80.0f * (i % 4) + 16.0f * j, 218.0f + 104.0f * (i / 4));
            espBankSet(work->sprList[i * 3 + 65 + j], GetDigit(winCount, 2 - j));
        }
    }
    espDispOn(work->sprList[6]);
    for (i = 0; i < CHARACTERS_MAX; i++) {
        espDispOn(work->sprList[i + 57]);
        for (j = 0; j < 3; j++) {
            espDispOn(work->sprList[i * 3 + 65 + j]);
        }
    }
    OptionWinPosSet(work->window[2], 136.0f, 96.0f);
    OptionWinMesSet(work->window[2], MAKE_MESSID(47, 23));
    OptionWinDispOn(work->window[2]);
}

#define TOTAL_SPR_HIDE_COUNT 33

static const s32 totalSprHideTbl[TOTAL_SPR_HIDE_COUNT]
    = { 6, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88 };

static void HideTotal(omObjData *object)
{
    RecordWork *work = object->data;
    s32 i;

    for (i = 0; i < TOTAL_SPR_HIDE_COUNT; i++) {
        espDispOff(work->sprList[totalSprHideTbl[i]]);
    }
    OptionWinDispOff(work->window[2]);
}

static const MGTable mgTbl[6] = {
    { 405, MAKE_MESSID(23, 5), DISPLAY_TYPE_TIME },
    { 407, MAKE_MESSID(23, 7), DISPLAY_TYPE_SCORE },
    { 427, MAKE_MESSID(23, 27), DISPLAY_TYPE_TIME },
    { 432, MAKE_MESSID(23, 32), DISPLAY_TYPE_TIME },
    { 443, MAKE_MESSID(23, 43), DISPLAY_TYPE_TIME },
    { 456, MAKE_MESSID(23, 54), DISPLAY_TYPE_TIME },
};

static void ShowMG(omObjData *object, s32 page)
{
    RecordWork *work = object->data;
    s32 value;
    s32 mg;
    s32 timeDigit;
    s32 timeCenti;
    s32 scoreDigit;
    s32 timeMin;
    s32 timeSec;
    s32 mgAvail;
    BOOL dispZeroF;
    s32 nameMess;
    s32 i;
    s32 j;

    espPosSet(work->sprList[7], 275.0f, 72.0f);
    espPosSet(work->sprList[47], 48.0f, 240.0f);
    espPosSet(work->sprList[48], 492.0f, 240.0f);
    espDispOn(work->sprList[7]);
    for (i = 0; i < 8; i++) {
        dispZeroF = FALSE;
        mg = i + page * 8;
        if (mg >= 6) {
            break;
        }
        mgAvail = GWMGAvailGet(mgTbl[mg].id);
        value = work->mgRecord[mg];
        if (mgAvail) {
            switch (mgTbl[mg].displayType) {
                case DISPLAY_TYPE_SCORE:
                    for (j = 0; j < MG_SCORE_NUM_DIGITS; j++) {
                        scoreDigit = GetDigit(value, 7 - j);
                        if (scoreDigit != 0 || dispZeroF || j >= 7) {
                            espPosSet(work->sprList[i * 8 + 89 + j], 336.0f + 16.0f * j, 116.0f + 40.0f * i);
                            espBankSet(work->sprList[i * 8 + 89 + j], scoreDigit);
                            espDispOn(work->sprList[i * 8 + 89 + j]);
                            dispZeroF = TRUE;
                        }
                    }
                    break;
                case DISPLAY_TYPE_TIME:
                    timeMin = value / (60 * REFRESH_RATE);
                    timeSec = (value % (60 * REFRESH_RATE)) / REFRESH_RATE;
                    timeCenti = (value % (60 * REFRESH_RATE)) % REFRESH_RATE;
                    if (mgTbl[mg].id == 405 || mgTbl[mg].id == 432) {
                        timeCenti *= (101.5f / REFRESH_RATE);
                    }
                    else {
                        timeCenti *= (100.0f / REFRESH_RATE);
                    }
                    for (j = 1; j < MG_TIME_NUM_DIGITS; j++) {
                        espPosSet(work->sprList[i * 8 + 89 + j], 336.0f + 16.0f * j, 116.0f + 40.0f * i);
                        switch (j) {
                            case 0:
                                timeDigit = GetDigit(timeMin, 1);
                                break;
                            case 1:
                                timeDigit = GetDigit(timeMin, 0);
                                break;
                            case 3:
                                timeDigit = GetDigit(timeSec, 1);
                                break;
                            case 4:
                                timeDigit = GetDigit(timeSec, 0);
                                break;
                            case 6:
                                timeDigit = GetDigit(timeCenti, 1);
                                break;
                            case 7:
                                timeDigit = GetDigit(timeCenti, 0);
                                break;
                            case 2:
                                timeDigit = 11;
                                break;
                            case 5:
                                timeDigit = 12;
                                break;
                        }
                        espBankSet(work->sprList[i * 8 + 89 + j], timeDigit);
                        espDispOn(work->sprList[i * 8 + 89 + j]);
                    }
                    break;
            }
        }
        else {
            for (j = 0; j < MG_SCORE_NUM_DIGITS; j++) {
                espPosSet(work->sprList[i * 8 + 89 + j], 336.0f + 16.0f * j, 116.0f + 40.0f * i);
                espBankSet(work->sprList[i * 8 + 89 + j], 0);
                espDispOn(work->sprList[i * 8 + 89 + j]);
            }
        }
        OptionWinPosSet(work->window[i + 2], 60.0f, 96.0f + 40.0f * i);
        nameMess = mgAvail ? mgTbl[mg].mess : MAKE_MESSID(35, 0);
        OptionWinMesSet(work->window[i + 2], nameMess);
        OptionWinDispOn(work->window[i + 2]);
    }
}

#define MG_SPR_HIDE_COUNT 65

static const s32 mgSprHideTbl[65] = { 7, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
    113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141,
    142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152 };

static void HideMG(omObjData *object)
{
    RecordWork *temp_r30 = object->data;
    s32 i;

    for (i = 0; i < MG_SPR_HIDE_COUNT; i++) {
        espDispOff(temp_r30->sprList[mgSprHideTbl[i]]);
    }
    for (i = 0; i < 8; i++) {
        OptionWinDispOff(temp_r30->window[i + 2]);
    }
}
