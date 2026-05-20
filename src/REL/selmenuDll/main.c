#include "game/board/main.h"
#include "game/armem.h"
#include "game/audio.h"
#ifndef __MWERKS__
#include "game/chrman.h"
#endif
#include "game/data.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/wipe.h"

#include "math.h"
#include <string.h>

#ifdef __MWERKS__
// MSM Definitions
static s8 *msmSeGetIndexPtr(s16 datano);
static void msmMusSetMasterVolume(s32 value);
#else
#include "game/msm.h"
#endif

#ifndef __MWERKS__
extern s32 rand8(void);
#endif

#define SM_PAGE_MAX 7
#define SM_PAGE_SIZE 10

#define SM_KEY_LEFT 0x0004
#define SM_KEY_RIGHT 0x0008
#define SM_KEY_UP 0x0001
#define SM_KEY_DOWN 0x0002

static char *smCharTbl[] = { "Mario", "Luigi", "Peach", "Yoshi", "Wario", "Donkey", "Daisy", "Waluigi" };

typedef struct sm_entry {
    u16 enabled;
    char *name;
    OMOVL overlay;
} SMEntry;

static SMEntry smMenuTbl[SM_PAGE_MAX * SM_PAGE_SIZE] = {
    { 1, "401:WAKUGURI DIVING", DLL_m401dll },
    { 1, "402:PURURUN! BIGSLIME", DLL_m402dll },
    { 1, "403:TAORERUKABE!", DLL_m403dll },
    { 1, "404:CRAYON RUNNER", DLL_m404dll },
    { 1, "405:MEDREY RACE", DLL_m405dll },
    { 1, "406:SKI RACE", DLL_m406dll },
    { 1, "407:BATTANDOMINO", DLL_m407dll },
    { 1, "408:SKY DIVE", DLL_m408dll },
    { 1, "409:CRAY SHOT", DLL_m409dll },
    { 1, "410:JANJAN FREE THROW", DLL_m410dll },
    { 1, "411:PAZZLE DE PONG", DLL_m411dll },
    { 1, "412:SNOW THROW", DLL_m412dll },
    { 1, "413:BOMBHEI PAZZLE!", DLL_m413dll },
    { 1, "414:NERATTE UTE!", DLL_m414dll },
    { 1, "415:PYONPYON STAMP", DLL_m415dll },
    { 1, "416:MAMORE FIRE", DLL_m416dll },
    { 1, "417:MARIO SURFER", DLL_m417dll },
    { 1, "418:TAIHOU KAKURENBO", DLL_m418dll },
    { 1, "419:BANANA DE KOROBASE", DLL_m419dll },
    { 1, "420:WATER BATTLE", DLL_m420dll },
    { 1, "421:BODY BALOON", DLL_m421dll },
    { 1, "422:BELCON COIN", DLL_m422dll },
    { 1, "423:GOAL AND GOAL", DLL_m423dll },
    { 1, "424:CLANE CATCH", DLL_m424dll },
    { 1, "425:AIR DOSSUN", DLL_m425dll },
    { 1, "426:KYOROKYORO PANIC", DLL_m426dll },
    { 1, "427:BOAT RACE", DLL_m427dll },
    { 1, "428:THE ROCK CLIME", DLL_m428dll },
    { 1, "429:TREASURE FOREST", DLL_m429dll },
    { 1, "430:PARASAILING GO", DLL_m430dll },
    { 1, "431:GURUGURU BOX", DLL_m431dll },
    { 1, "432:PAIR DE RACE", DLL_m432dll },
    { 1, "433:BEACH VOLLEY", DLL_subchrseldll },
    { 1, "434:KINGYOSUKUI", DLL_m434dll },
    { 1, "435:KOOPA DARTS", DLL_m435dll },
    { 1, "436:KOOPANO AREGA TABETAI!", DLL_m436dll },
    { 1, "437:FUSEN RAKUGO", DLL_m437dll },
    { 1, "438:SYAKUNETSU WANWAN ATTACK", DLL_m438dll },
    { 1, "439:GURUGURU DANGEROUS", DLL_m439dll },
    { 1, "440:NEO KOOPA BAKUDAN", DLL_m440dll },
    { 1, "441:HIRAHIRA CHOUCHO", DLL_m441dll },
    { 1, "442:SUIMYAKU HORE2", DLL_m442dll },
    { 1, "443:DRUG RACE", DLL_m443dll },
    { 1, "444:MIRACLE PINBALL", DLL_m444dll },
    { 1, "445:KINOPIO HAMMER", DLL_m445dll },
    { 1, "446:3MAI SOROERO!", DLL_m446dll },
    { 1, "447:IQ BLOCK", DLL_m447dll },
    { 1, "448:FUMIKURI", DLL_m448dll },
    { 1, "449:NOKO2 KOURA PAZZLE", DLL_m449dll },
    { 1, "450:LAST GAME", DLL_m450dll },
    { 1, "451:PAZZLE", DLL_m451dll },
    { 1, "455:BURUTTE 1BAN", DLL_m455dll },
    { 1, "456:MOGUTTE 1BAN", DLL_m456dll },
    { 1, "457:SUMOH", DLL_m457dll },
    { 1, "458:PSYCOLO BATTLE", DLL_m458dll },
    { 1, "459:Dr.WARIO", DLL_m459dll },
    { 1, "460:", DLL_m460dll },
    { 1, "461:BOMBHEI SCRANBLE", DLL_m461dll },
    { 1, "462:", DLL_m462dll },
    { 1, "***:MESS CHECK", DLL_messdll },
    { 1, "***:BOARD W01", DLL_w01dll },
    { 1, "***:BOARD W02", DLL_w02dll },
    { 1, "***:BOARD W03", DLL_w03dll },
    { 1, "***:BOARD W04", DLL_w04dll },
    { 1, "***:BOARD W05", DLL_w05dll },
    { 1, "***:BOARD W06", DLL_w06dll },
    { 1, "***:BOARD W20", DLL_w20dll },
    { 1, "***:BOARD W21", DLL_w21dll },
    { 1, "***:STAFF", DLL_staffdll },
    { 1, "***:STORY TEST", DLL_mstory4dll },
};

static u32 cameraMaskTbl[] = { (1 << 0), (1 << 1), (1 << 2), (1 << 3) };

static u32 lbl_1_data_844[] = { 0, 1, 2, 3, 4, 5 };

static char *dvdMusTbl[] = { "sound/mu_016a.dvd", "sound/mu_047a.dvd", "sound/mu_052a.dvd", "sound/mu_054a.dvd", "sound/mu_101a.dvd",
    "sound/mu_108a.dvd", "sound/mu002a.dvd", "" };

static s16 smPage;
static s16 smSelectPosBackup[SM_PAGE_MAX];
static omObjData *smMainObj;
static omObjData *outViewObj;
static PlayerConfig smPlayerCfg[4];
static s16 smSelectPos;
static s16 smSelectPosExit = -1;
static u16 btnDown;
static u16 keyDStk;
static u16 keyDStkDown;
static u16 btnDownAll[4];
static u16 keyDStkAll[4];
static u16 keyDStkAllDown[4];
static u16 keyDStkAllPrev[4] = {};

static void SMInit(omObjData *object);
static void SMRand8Tick(omObjData *object);

void ObjectSetup(void)
{
    static char *funcId = "SMOBJECTSETUP\n";
    s32 i;
    Process *objman;
    Vec pos, dir;

    OSReport("ObjectSetup:%08x\n", ObjectSetup);
    OSReport("\n\n\n******* SMObjectSetup *********\n");
    OSReport(funcId);
    objman = omInitObjMan(50, 8192);
    for (i = 0; i < 4; i++) {
        if (GWPlayerCfg[i].character >= 8) {
            break;
        }
    }
    if (i != 4) {
        for (i = 0; i < 4; i++) {
            GWPlayerCfg[i].character = i;
        }
    }
    smMainObj = omAddObjEx(objman, 0, 0, 0, -1, SMInit);
    outViewObj = omAddObjEx(objman, 32730, 0, 0, -1, omOutViewMulti);
    omAddObjEx(objman, 0, 0, 0, -1, SMRand8Tick);
    outViewObj->work[0] = 4;
    for (i = 0; i < 4; i++) {
        CRotM[i].x = -20.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 50.0f;
        CenterM[i].z = 0.0f;
        CZoomM[i] = 500.0f;
        Hu3DCameraCreate(cameraMaskTbl[i]);
        Hu3DCameraPerspectiveSet(cameraMaskTbl[i], 45.0f, 20.0f, 25000.0f, 4.0f / 3.0f);
        Hu3DCameraViewportSet(cameraMaskTbl[i], (i % 2) * 320.0f, (i / 2) * 240.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    }
    Hu3DGLightCreate(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, -1.0f, 255, 255, 255);
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 200.0f;
    dir.x = dir.y = 0.0f;
    dir.z = -1.0f;
    SetDefLight(&pos, &dir, 255, 255, 255, 64, 64, 64, 255, 255, 255);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    GWMGTypeSet(-1);
    _ClearFlag(FLAG_ID_MAKE(1, 0));
    GWSystem.turn = 1;
    GWSystem.max_turn = 20;
}

static void CopyPlayerCfg(PlayerConfig *dst, PlayerConfig *src)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        *dst++ = *src++;
    }
}

static void CalcBtns(void)
{
    s32 i;
    keyDStk = keyDStkDown = btnDown = 0;
    for (i = 0; i < 4; i++) {
        keyDStkAll[i] = keyDStkAllDown[i] = btnDownAll[i] = 0;
        if ((HuPadDStkRep[i] | HuPadBtn[i]) & PAD_BUTTON_LEFT) {
            keyDStkAll[i] |= SM_KEY_LEFT;
        }
        if ((HuPadDStkRep[i] | HuPadBtn[i]) & PAD_BUTTON_RIGHT) {
            keyDStkAll[i] |= SM_KEY_RIGHT;
        }
        if ((HuPadDStkRep[i] | HuPadBtn[i]) & PAD_BUTTON_UP) {
            keyDStkAll[i] |= SM_KEY_UP;
        }
        if ((HuPadDStkRep[i] | HuPadBtn[i]) & PAD_BUTTON_DOWN) {
            keyDStkAll[i] |= SM_KEY_DOWN;
        }
        btnDownAll[i] |= HuPadBtnDown[i];
        keyDStkAllDown[i] = (keyDStkAll[i] ^ keyDStkAllPrev[i]) & keyDStkAll[i];
        keyDStkAllPrev[i] = keyDStkAll[i];
        keyDStk |= keyDStkAll[i];
        keyDStkDown |= keyDStkAllDown[i];
        btnDown |= btnDownAll[i];
    }
}

static void DrawPage(void)
{
    s32 i;
    SMEntry *entry;
    fontcolor = FONT_COLOR_YELLOW;
    print8(200, 160, 2.5f, "PAGE:%d/%d", smPage + 1, SM_PAGE_MAX);
    for (i = 0; i < SM_PAGE_SIZE; i++) {
        entry = &smMenuTbl[(smPage * SM_PAGE_SIZE) + i];
        if (entry->enabled == 1) {
            if (i == smSelectPos) {
                fontcolor = FONT_COLOR_CYAN;
            }
            else {
                fontcolor = FONT_COLOR_GREEN;
            }
        }
        else {
            fontcolor = FONT_COLOR_DARK_GREEN;
        }
        print8(100, (float)((i + 10) * 8) * 2.5f, 2.5f, "%s", entry->name);
    }
}

static void MoveSMCursor(s16 amount);

static void MoveSMPage(s16 amount)
{
    s16 page;
    s32 i;
    u16 enabled;
    s16 page_old;
    enabled = 0;
    page = smPage;
    page_old = page;
    do {
        page += amount;
        if (page >= SM_PAGE_MAX) {
            page = 0;
        }
        else if (page < 0) {
            page = SM_PAGE_MAX - 1;
        }
        for (i = 0; i < SM_PAGE_SIZE; i++) {
            if (smMenuTbl[(page * SM_PAGE_SIZE) + i].enabled == 1) {
                enabled = 1;
                break;
            }
        }
    } while (!enabled);
    smPage = page;
    if (page_old == -1) {
        smSelectPos = -1;
        MoveSMCursor(1);
        smSelectPosBackup[smPage] = smSelectPos;
    }
    else {
        smSelectPosBackup[page_old] = smSelectPos;
        smSelectPos = smSelectPosBackup[smPage];
    }
}

static void MoveSMCursor(s16 amount)
{
    s16 pos;
    pos = smSelectPos;
    do {
        pos += amount;
        if (pos >= SM_PAGE_SIZE) {
            pos = 0;
        }
        else if (pos < 0) {
            pos = SM_PAGE_SIZE - 1;
        }
    } while (!smMenuTbl[(smPage * SM_PAGE_SIZE) + pos].enabled);
    smSelectPos = pos;
    (void)pos;
}

static s16 SMChangeChar(s16 player, s16 offset);
static void SMUpdate(omObjData *object);

static void SMInit(omObjData *object)
{
    s32 i, j;
    OSReport("SMinit:%08x\n", SMInit);
    omDLLDBGOut();
    Hu3DBGColorSet(0, 0, 0);
    CopyPlayerCfg(smPlayerCfg, GWPlayerCfg);
    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 4; j++) {
            if (smPlayerCfg[i].character == smPlayerCfg[j].character) {
                smPlayerCfg[j].character = SMChangeChar(j, -1);
            }
        }
    }
    smPage = -1;
    for (i = 0; i < SM_PAGE_MAX; i++) {
        for (j = 0; j < SM_PAGE_SIZE; j++) {
            if (smMenuTbl[(i * SM_PAGE_SIZE) + j].enabled == 1) {
                break;
            }
        }
        if (j == SM_PAGE_SIZE) {
            smSelectPosBackup[i] = -1;
        }
        else {
            smSelectPosBackup[i] = j;
        }
    }
    MoveSMPage(1);
    if (mgSeqOvlPrev != DLL_NONE) {
        for (i = 0; i < SM_PAGE_MAX * SM_PAGE_SIZE; i++) {
            if (mgSeqOvlPrev == smMenuTbl[i].overlay && smMenuTbl[i].enabled == 1) {
                smPage = i / SM_PAGE_SIZE;
                smSelectPos = i % SM_PAGE_SIZE;
                smSelectPosBackup[smPage] = smSelectPos;
                break;
            }
        }
    }
    object->func = SMUpdate;
}

static void SMGroupGen(s32 index);
static void SMCharInit(omObjData *object);
static void SMPlayerCfgInit(omObjData *object);
static void SMSound3DInit(omObjData *object);

static void SMUpdate(omObjData *object)
{
    CalcBtns();
    DrawPage();
    if (keyDStkDown & SM_KEY_UP) {
        MoveSMCursor(-1);
        SMGroupGen((smPage * SM_PAGE_SIZE) + smSelectPos);
        return;
    }
    if (keyDStkDown & SM_KEY_DOWN) {
        MoveSMCursor(1);
        SMGroupGen((smPage * SM_PAGE_SIZE) + smSelectPos);
        return;
    }
    if (keyDStkDown & SM_KEY_LEFT) {
        MoveSMPage(-1);
        SMGroupGen((smPage * SM_PAGE_SIZE) + smSelectPos);
        return;
    }
    if (keyDStkDown & SM_KEY_RIGHT) {
        MoveSMPage(1);
        SMGroupGen((smPage * SM_PAGE_SIZE) + smSelectPos);
        return;
    }
    if ((btnDown & PAD_BUTTON_A) || (btnDown & PAD_BUTTON_START)) {
        object->func = SMCharInit;
        return;
    }
    if (btnDown & PAD_BUTTON_Y) {
        object->func = SMPlayerCfgInit;
        return;
    }
    if (btnDown & PAD_TRIGGER_Z) {
        object->func = SMSound3DInit;
        return;
    }
    if (btnDown & PAD_BUTTON_X) {
        omOvlReturnEx(0, 1);
    }
}

static void SMGroupGen(s32 index)
{
    OMOVL overlay;
    s32 i;
    overlay = smMenuTbl[index].overlay;
    for (i = 0; i < 50; i++) {
        if (overlay == mgInfoTbl[i].ovl) {
            break;
        }
    }
    if (i == 50) {
        for (i = 0; i < 4; i++) {
            smPlayerCfg[i].group = i;
        }
        return;
    }
    switch (mgInfoTbl[i].type) {
        case 0:
        case 3:
        case 4:
        case 5:
        case 6:
            for (i = 0; i < 4; i++) {
                smPlayerCfg[i].group = i;
            }
            break;

        case 1:
            smPlayerCfg[0].group = 0;
            for (i = 1; i < 4; i++) {
                smPlayerCfg[i].group = 1;
            }
            break;

        case 2:
            for (i = 0; i < 2; i++) {
                smPlayerCfg[i].group = 0;
            }
            for (i = 2; i < 4; i++) {
                smPlayerCfg[i].group = 1;
            }
            break;
    }
    if (overlay == DLL_m430dll) {
        s32 team_cnt[2];
        s32 team_players[2][2];
        team_cnt[0] = team_cnt[1] = 0;
        for (i = 0; i < 4; i++) {
            team_players[smPlayerCfg[i].group][team_cnt[smPlayerCfg[i].group]++] = i;
        }
        if (frandBool()) {
            GWPlayerCfg[team_players[0][0]].group = 0;
            GWPlayerCfg[team_players[0][1]].group = 1;
        }
        else {
            GWPlayerCfg[team_players[0][0]].group = 1;
            GWPlayerCfg[team_players[0][1]].group = 0;
        }
        if (frandBool()) {
            GWPlayerCfg[team_players[1][0]].group = 2;
            GWPlayerCfg[team_players[1][1]].group = 3;
        }
        else {
            GWPlayerCfg[team_players[1][0]].group = 3;
            GWPlayerCfg[team_players[1][1]].group = 2;
        }
    }
}

static s16 charModelID[8];
static s16 playerDoneF[4];
static s16 charSelProhibitF[8];

static s32 charMdlTbl[] = {
    DATA_MAKE_NUM(DATADIR_SELMENU, 0),
    DATA_MAKE_NUM(DATADIR_SELMENU, 2),
    DATA_MAKE_NUM(DATADIR_SELMENU, 4),
    DATA_MAKE_NUM(DATADIR_SELMENU, 6),
    DATA_MAKE_NUM(DATADIR_SELMENU, 8),
    DATA_MAKE_NUM(DATADIR_SELMENU, 10),
    DATA_MAKE_NUM(DATADIR_SELMENU, 12),
    DATA_MAKE_NUM(DATADIR_SELMENU, 14),
};

static s32 charMdlMotTbl[] = {
    DATA_MAKE_NUM(DATADIR_SELMENU, 1),
    DATA_MAKE_NUM(DATADIR_SELMENU, 3),
    DATA_MAKE_NUM(DATADIR_SELMENU, 5),
    DATA_MAKE_NUM(DATADIR_SELMENU, 7),
    DATA_MAKE_NUM(DATADIR_SELMENU, 9),
    DATA_MAKE_NUM(DATADIR_SELMENU, 11),
    DATA_MAKE_NUM(DATADIR_SELMENU, 13),
    DATA_MAKE_NUM(DATADIR_SELMENU, 15),
};

static s16 SMChangeChar(s16 player, s16 offset)
{
    s32 i;
    s16 character;
    for (i = 0; i < 8; i++) {
        charSelProhibitF[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        if (smPlayerCfg[i].iscom) {
            continue;
        }
        charSelProhibitF[smPlayerCfg[i].character] = 1;
    }
    if (!offset) {
        return;
    }
    character = smPlayerCfg[player].character;
    do {
        character += offset;
        if (character < 0) {
            character = 7;
        }
        if (character >= 8) {
            character = 0;
        }
    } while (charSelProhibitF[character] != 0);
    return character;
}

static void SMCharDataClose(void)
{
    s32 i;
    for (i = 0; i < 8; i++) {
        Hu3DModelKill(charModelID[i]);
    }
}

static void CharRandomize(void)
{
    s32 i;
    s32 j;
    s32 valid_cnt;
    s32 valid_list[8];
    for (i = 0; i < 4; i++) {
        valid_cnt = 0;
        for (j = 0; j < 8; j++) {
            if (charSelProhibitF[j]) {
                continue;
            }
            valid_list[valid_cnt++] = j;
        }
        if (smPlayerCfg[i].iscom == 1) {
            smPlayerCfg[i].character = valid_list[rand8() % valid_cnt];
            charSelProhibitF[smPlayerCfg[i].character] = 1;
        }
    }
}

static void SMCharUpdate(omObjData *object);
static void SMExit(omObjData *object);

static void SMCharInit(omObjData *object)
{
    s32 i;
    for (i = 0; i < 8; i++) {
        void *data = HuDataSelHeapReadNum(charMdlTbl[i], MEMORY_DEFAULT_NUM, HEAP_DATA);
        charModelID[i] = Hu3DModelCreate(data);
        Hu3DModelPosSet(charModelID[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrSet(charModelID[i], HU3D_MOTATTR_LOOP);
        Hu3DMotionSet(charModelID[i], Hu3DJointMotionFile(charModelID[i], charMdlMotTbl[i]));
    }
    for (i = 0; i < 4; i++) {
        playerDoneF[i] = 0;
    }
    SMChangeChar(0, 0);
    object->func = SMCharUpdate;
}

static void SMCharUpdate(omObjData *object)
{
    s32 i;

    s16 port;
    s32 j;
    s16 w;
    s16 x;
    s16 y;
    s16 done_players;
    s16 num_players;

    for (i = 0; i < 8; i++) {
        Hu3DModelAttrSet(charModelID[i], HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 4; i++) {
        if (!smPlayerCfg[i].iscom) {
            Hu3DModelAttrReset(charModelID[smPlayerCfg[i].character], HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(charModelID[smPlayerCfg[i].character], cameraMaskTbl[i]);
        }
    }
    for (i = 0, done_players = 0, num_players = 0; i < 4; i++) {
        if (playerDoneF[i] == 1) {
            done_players++;
        }
        if (!smPlayerCfg[i].iscom) {
            num_players++;
        }
    }
    if (done_players == num_players) {
        SMChangeChar(0, 0);
        CharRandomize();
        CopyPlayerCfg(GWPlayerCfg, smPlayerCfg);
        CharDataClose(-1);
        OSReport("%d,%d,%d,%d\n", GWPlayerCfg[0].character, GWPlayerCfg[1].character, GWPlayerCfg[2].character, GWPlayerCfg[3].character);
        if (!CharMotionAMemPGet(GWPlayerCfg[0].character)) {
            CharMotionInit(GWPlayerCfg[0].character);
        }
        if (!CharMotionAMemPGet(GWPlayerCfg[1].character)) {
            CharMotionInit(GWPlayerCfg[1].character);
        }
        if (!CharMotionAMemPGet(GWPlayerCfg[2].character)) {
            CharMotionInit(GWPlayerCfg[2].character);
        }
        if (!CharMotionAMemPGet(GWPlayerCfg[3].character)) {
            CharMotionInit(GWPlayerCfg[3].character);
        }
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
        object->func = SMExit;
    }
    CalcBtns();
    for (i = 0; i < 4; i++) {
        port = smPlayerCfg[i].pad_idx;
        if (!playerDoneF[i]) {
            if (keyDStkAllDown[port] & SM_KEY_LEFT) {
                smPlayerCfg[port].character = SMChangeChar(i, -1);
            }
            if (keyDStkAllDown[port] & SM_KEY_RIGHT) {
                smPlayerCfg[port].character = SMChangeChar(i, 1);
            }
            if (btnDownAll[port] & PAD_BUTTON_A) {
                playerDoneF[i] = 1;
            }
        }
        if (HuPadBtnDown[port] & PAD_BUTTON_B) {
            if (done_players != 0) {
                playerDoneF[i] = 0;
            }
            else {
                SMCharDataClose();
                object->func = SMUpdate;
                return;
            }
        }
        if (btnDownAll[port] & PAD_BUTTON_START) {
            for (j = 0; j < 4; j++) {
                if (!smPlayerCfg[j].iscom) {
                    playerDoneF[j] = 1;
                }
            }
            return;
        }
        if (!smPlayerCfg[i].iscom) {
            w = strlen(smCharTbl[smPlayerCfg[i].character]);
            w *= 16;
            x = ((320 - w) / 2) + ((i % 2) * 320);
            y = 176 + ((i / 2) * 240);
            if (playerDoneF[i] == 1) {
                fontcolor = FONT_COLOR_WHITE;
                print8(x, y, 2.0f,
                    "\xFD\x08"
                    "%s",
                    smCharTbl[smPlayerCfg[i].character]);
            }
            else {
                fontcolor = FONT_COLOR_GREEN;
                print8(x, y, 2.0f,
                    "\xFD\x05"
                    "%s",
                    smCharTbl[smPlayerCfg[i].character]);
            }
        }
        else {
            w = 72;
            x = ((320 - w) / 2) + ((i % 2) * 320);
            y = 108 + ((i / 2) * 240);
            fontcolor = FONT_COLOR_YELLOW;
            print8(x, y, 3.0f,
                "\xFD\x07"
                "COM");
        }
    }
}

static void SMExit(omObjData *object)
{
    s32 mg;
    if (WipeStatGet()) {
        return;
    }
    while (HuARDMACheck())
        ;
    mg = omMgIndexGet(smMenuTbl[(smPage * SM_PAGE_SIZE) + smSelectPos].overlay);
    GWSystem.mg_next = mg;
    OSReport("mgNo=%d\n", mg);
    if (smMenuTbl[(smPage * SM_PAGE_SIZE) + smSelectPos].overlay == DLL_w10dll) {
        _SetFlag(0x1000B);
    }
    else if (smMenuTbl[(smPage * SM_PAGE_SIZE) + smSelectPos].overlay == DLL_w20dll) {
        BoardSaveInit(7);
        BoardPartyConfigSet(0, 0, 0, 20, 0, 0, 0, 0);
    }
    else if (smMenuTbl[(smPage * SM_PAGE_SIZE) + smSelectPos].overlay == DLL_w21dll) {
        BoardSaveInit(8);
        BoardPartyConfigSet(0, 0, 0, 20, 0, 0, 0, 0);
    }
    else {
        _ClearFlag(0x1000B);
    }
    if (mg == -1 || !(HuPadBtn[0] & PAD_TRIGGER_Z) || mgInfoTbl[mg].type == 5 || mgInfoTbl[mg].type == 3 || mgInfoTbl[mg].type == 6) {
        omOvlCallEx(smMenuTbl[(smPage * SM_PAGE_SIZE) + smSelectPos].overlay, 1, 0, 0);
    }
    else {
        omOvlCallEx(DLL_instdll, 1, 0, 0);
    }
    mgSeqOvlPrev = smMenuTbl[(smPage * SM_PAGE_SIZE) + smSelectPos].overlay;
    smSelectPosExit = smSelectPos;
}

static char *padCfgStrTbl[] = { "PLAYER:%d", " PAD%d:%s", "PADNO:%d", "  GRP:%d", "  DIF:%s" };

static s16 playerCfgSelF;
static s16 playerCfgPlayerPos;
static s16 playerCfgOptionPos;

#define DO_HILITE(option)                                                                                                                            \
    do {                                                                                                                                             \
        s32 color;                                                                                                                                   \
        if (playerCfgOptionPos == option) {                                                                                                          \
            color = fontcolor = FONT_COLOR_CYAN;                                                                                                     \
        }                                                                                                                                            \
        else {                                                                                                                                       \
            color = fontcolor = FONT_COLOR_GREEN;                                                                                                    \
        }                                                                                                                                            \
        (void)color;                                                                                                                                 \
    } while (0)

static void SMPlayerCfgDraw(void)
{
    s32 i;
    s16 x;
    s16 y;
    s16 w;
    char *comStr[] = { "HUMAN", "COM" };
    char *diffStr[] = { "EASY", "NORMAL", "HARD", "VERYHARD" };

    for (i = 0; i < 4; i++) {
        w = 128;
        x = ((320 - w) / 2) + ((i % 2) * 320);
        y = ((i / 2) * 240) + 48;
        if (playerCfgSelF == 0 && playerCfgPlayerPos == i) {
            fontcolor = FONT_COLOR_CYAN;
        }
        else {
            fontcolor = FONT_COLOR_GREEN;
        }
        print8(x, y, 2.0f, padCfgStrTbl[0], i);
        if (playerCfgSelF == 0) {
            fontcolor = FONT_COLOR_DARK_GREEN;
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 80, 2.0f, padCfgStrTbl[1], smPlayerCfg[i].pad_idx, comStr[smPlayerCfg[i].iscom]);
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 96, 2.0f, padCfgStrTbl[2], smPlayerCfg[i].pad_idx);
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 112, 2.0f, padCfgStrTbl[3], smPlayerCfg[i].group);
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 128, 2.0f, padCfgStrTbl[4], diffStr[smPlayerCfg[i].diff]);
        }
        else if (playerCfgSelF == 1 && playerCfgPlayerPos == i) {
            DO_HILITE(0);
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 80, 2.0f, padCfgStrTbl[1], smPlayerCfg[i].pad_idx, comStr[smPlayerCfg[i].iscom]);
            DO_HILITE(1);
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 96, 2.0f, padCfgStrTbl[2], smPlayerCfg[i].pad_idx);
            DO_HILITE(2);
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 112, 2.0f, padCfgStrTbl[3], smPlayerCfg[i].group);
            DO_HILITE(3);
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 128, 2.0f, padCfgStrTbl[4], diffStr[smPlayerCfg[i].diff]);
        }
        else {
            fontcolor = FONT_COLOR_DARK_GREEN;
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 80, 2.0f, padCfgStrTbl[1], smPlayerCfg[i].pad_idx, comStr[smPlayerCfg[i].iscom]);
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 96, 2.0f, padCfgStrTbl[2], smPlayerCfg[i].pad_idx);
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 112, 2.0f, padCfgStrTbl[3], smPlayerCfg[i].group);
            print8(((i % 2) * 320) + 64, ((i / 2) * 240) + 128, 2.0f, padCfgStrTbl[4], diffStr[smPlayerCfg[i].diff]);
        }
    }
}

#undef DO_HILITE
static void SMPlayerCfgUpdate(omObjData *object);

static void SMPlayerCfgInit(omObjData *object)
{
    playerCfgSelF = 0;
    playerCfgPlayerPos = 0;
    playerCfgOptionPos = 0;
    object->func = SMPlayerCfgUpdate;
}

static void SMPlayerCfgUpdate(omObjData *object)
{
    s32 offset;
    SMPlayerCfgDraw();
    CalcBtns();
    if (!playerCfgSelF) {
        if (keyDStkDown & SM_KEY_LEFT) {
            offset = ((playerCfgPlayerPos & 0x1) - 1) & 0x1;
            playerCfgPlayerPos = (playerCfgPlayerPos & 0xFFFE) + offset;
        }
        else {
            if (keyDStkDown & SM_KEY_RIGHT) {
                offset = ((playerCfgPlayerPos & 0x1) + 1) & 0x1;
                playerCfgPlayerPos = (playerCfgPlayerPos & 0xFFFE) + offset;
            }
            else if (keyDStkDown & SM_KEY_DOWN) {
                if ((playerCfgPlayerPos += 2) >= 4) {
                    playerCfgPlayerPos -= 4;
                }
            }
            else if (keyDStkDown & SM_KEY_UP) {
                if ((playerCfgPlayerPos -= 2) < 0) {
                    playerCfgPlayerPos += 4;
                }
            }
        }
        if (btnDown & PAD_BUTTON_A) {
            playerCfgSelF = 1;
            return;
        }
        if ((btnDown & PAD_BUTTON_B) || (btnDown & PAD_BUTTON_Y)) {
            object->func = SMUpdate;
        }
    }
    else if (keyDStkDown & SM_KEY_UP) {
        if (--playerCfgOptionPos < 0) {
            playerCfgOptionPos = 3;
        }
    }
    else if (keyDStkDown & SM_KEY_DOWN) {
        if (++playerCfgOptionPos > 3) {
            playerCfgOptionPos = 0;
        }
    }
    else if (keyDStkDown & SM_KEY_LEFT) {
        switch (playerCfgOptionPos) {
            case 0:
                smPlayerCfg[playerCfgPlayerPos].iscom ^= 1;
                break;

            case 1:
                if (--smPlayerCfg[playerCfgPlayerPos].pad_idx < 0) {
                    smPlayerCfg[playerCfgPlayerPos].pad_idx = 3;
                }
                break;

            case 2:
                if (--smPlayerCfg[playerCfgPlayerPos].group < 0) {
                    smPlayerCfg[playerCfgPlayerPos].group = 3;
                }
                break;

            case 3:
                if (--smPlayerCfg[playerCfgPlayerPos].diff < 0) {
                    smPlayerCfg[playerCfgPlayerPos].diff = 3;
                }
                break;
        };
    }
    else if (keyDStkDown & SM_KEY_RIGHT) {
        switch (playerCfgOptionPos) {
            case 0:
                smPlayerCfg[playerCfgPlayerPos].iscom ^= 1;
                break;

            case 1:
                if (++smPlayerCfg[playerCfgPlayerPos].pad_idx > 3) {
                    smPlayerCfg[playerCfgPlayerPos].pad_idx = 0;
                }
                break;

            case 2:
                if (++smPlayerCfg[playerCfgPlayerPos].group > 3) {
                    smPlayerCfg[playerCfgPlayerPos].group = 0;
                }
                break;

            case 3:
                if (++smPlayerCfg[playerCfgPlayerPos].diff > 3) {
                    smPlayerCfg[playerCfgPlayerPos].diff = 0;
                }
                break;
        }
    }
    else if ((btnDown & PAD_BUTTON_A) || (btnDown & PAD_BUTTON_B)) {
        playerCfgSelF = 0;
    }
    else if (btnDown & PAD_BUTTON_Y) {
        object->func = SMUpdate;
    }
}

static void SMRand8Tick(omObjData *object)
{
    rand8();
}

void fn_1_450C(void) { }

static s16 emiCompDataNo;
static s16 emiCompVal;
static s16 smSound3DPos;
s16 lbl_1_bss_0;

static void SMSound3DUpdate(omObjData *object);
static void SMSound3DDraw(void);

static void SMSound3DInit(omObjData *object)
{
    s8 *data = msmSeGetIndexPtr(emiCompDataNo);
    emiCompVal = data[12];
    object->func = SMSound3DUpdate;
}

static void SMSound3DUpdate(omObjData *object)
{
    float increment;
    s8 *data;

    CalcBtns();
    if (keyDStkDown & SM_KEY_UP) {
        smSound3DPos--;
        if (smSound3DPos < 0) {
            smSound3DPos = 7;
        }
    }
    if (keyDStkDown & SM_KEY_DOWN) {
        smSound3DPos++;
        if (smSound3DPos >= 8) {
            smSound3DPos = 0;
        }
    }
    if (keyDStkDown & (SM_KEY_LEFT | SM_KEY_RIGHT)) {
        if (keyDStkDown & SM_KEY_RIGHT) {
            increment = 10;
        }
        else {
            increment = -10;
        }
        if (HuPadBtn[0] & PAD_TRIGGER_Z) {
            increment *= 10.0f;
        }
        switch (smSound3DPos) {
            case 0:
                Snd3DDistOffset += increment;
                break;

            case 1:
                Snd3DSpeedOffset += increment;
                break;

            case 2:
                Snd3DStartDisOffset += increment;
                break;

            case 3:
                Snd3DFrontSurDisOffset += increment;
                break;

            case 4:
                Snd3DBackSurDisOffset += increment;
                break;

            case 5:
                emiCompDataNo += increment / 10.0f;
                if (emiCompDataNo < 0) {
                    emiCompDataNo = 0;
                }
                data = msmSeGetIndexPtr(emiCompDataNo);
                emiCompVal = data[12];
                break;

            case 6:
                emiCompVal += increment / 10.0f;
                if (emiCompVal > 127) {
                    emiCompVal = 127;
                }
                if (emiCompVal < -127) {
                    emiCompVal = -127;
                }
                data = msmSeGetIndexPtr(emiCompDataNo);
                data[12] = emiCompVal;
                break;

            case 7:
                musicOffF = (musicOffF) ? 0 : 1;
                if (musicOffF) {
                    msmMusSetMasterVolume(0);
                }
                else {
                    msmMusSetMasterVolume(127);
                }
                break;
        }
    }
    if (btnDown & PAD_BUTTON_START) {
        switch (smSound3DPos) {
            case 0:
                Snd3DDistOffset = 0;
                break;

            case 1:
                Snd3DSpeedOffset = 0;
                break;

            case 2:
                Snd3DStartDisOffset = 0;
                break;

            case 3:
                Snd3DFrontSurDisOffset = 0;
                break;

            case 4:
                Snd3DBackSurDisOffset = 0;
                break;

            case 5:
                emiCompDataNo = 0;
                break;

            case 6:
                emiCompVal = 0;
                break;

            case 7:
                musicOffF = 0;
                break;
        }
    }

    if (btnDown & PAD_BUTTON_B) {
        object->func = SMUpdate;
    }
    SMSound3DDraw();
}

#define DO_HILITE(pos)                                                                                                                               \
    do {                                                                                                                                             \
        if (smSound3DPos == pos) {                                                                                                                   \
            fontcolor = FONT_COLOR_GREEN;                                                                                                            \
        }                                                                                                                                            \
        else {                                                                                                                                       \
            fontcolor = FONT_COLOR_DARK_GREEN;                                                                                                       \
        }                                                                                                                                            \
    } while (0)

static void SMSound3DDraw(void)
{
    char *onOffStr[] = { " ON", "OFF" };
    fontcolor = FONT_COLOR_YELLOW;
    print8(200, 64, 2.0f, "3DSound Config.");
    DO_HILITE(0);
    print8(140, 96, 2.0f, "Max Distance   %5.1f", Snd3DDistOffset);
    DO_HILITE(1);
    print8(140, 112, 2.0f, "Sound Speed    %5.1f", Snd3DSpeedOffset);
    DO_HILITE(2);
    print8(140, 128, 2.0f, "Start Distance %5.1f", Snd3DStartDisOffset);
    DO_HILITE(3);
    print8(140, 144, 2.0f, "Front Distance %5.1f", Snd3DFrontSurDisOffset);
    DO_HILITE(4);
    print8(140, 160, 2.0f, "Back Distance  %5.1f", Snd3DBackSurDisOffset);
    DO_HILITE(5);
    print8(140, 176, 2.0f, "emiComp DataNo  %04d", emiCompDataNo);
    DO_HILITE(6);
    print8(140, 192, 2.0f, "emiComp VAL      %3d", emiCompVal);
    DO_HILITE(7);
    print8(140, 208, 2.0f, "Music            %s", onOffStr[(musicOffF) ? 1 : 0]);
}

#undef DO_HILITE
