#include "ext_math.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfex.h"
#include "game/hsfman.h"
#include "game/wipe.h"
#include "game/window.h"

#include "REL/present.h"

#define NUM_CHARACTERS 8

#define PRESENT_MDL_MAX 134
#define PRESENT_MAX 60

#define PRESENT_COUNT_CHAR_ROOM 6
#define PRESENT_COUNT_MG_ROOM 11

#define PRESENT_CONSTELLATION 5

#define ROOM_MARIO 0
#define ROOM_LUIGI 1
#define ROOM_PEACH 2
#define ROOM_YOSHI 3
#define ROOM_WARIO 4
#define ROOM_TROPHY 5
#define ROOM_DK 6
#define ROOM_DAISY 7
#define ROOM_WALUIGI 8
#define ROOM_MG 9
#define ROOM_MAX 9

#define ROOM_CHANGE_LEFT 1
#define ROOM_CHANGE_RIGHT 2

typedef struct PresentWork {
    /* 0x00 */ BOOL cursorVisibleF;
    /* 0x04 */ BOOL roomNotEmptyF;
    /* 0x08 */ BOOL constellationSelF;
    /* 0x0C */ s32 execMode;
    /* 0x10 */ omObjData *object[PRESENT_MDL_MAX];
    /* 0x228 */ PresentWindow *presentDescWindow;
    /* 0x22C */ PresentWindow *btnLegendWindow;
    /* 0x230 */ s16 cursor;
    /* 0x234 */ s32 room;
    /* 0x238 */ s32 idxInRoom;
    /* 0x23C */ float rot;
    /* 0x240 */ float rotPrev;
    /* 0x244 */ float rotTarget;
    /* 0x248 */ float timeRot;
    /* 0x24C */ float presentFallingTime;
    /* 0x250 */ float rotSpeed;
    /* 0x254 */ float presentFallingSpeed;
    /* 0x258 */ float cursorTime;
    /* 0x25C */ float cursorSpeed;
    /* 0x260 */ Vec2f cursorPos;
    /* 0x268 */ Vec2f newCursorPos;
    /* 0x270 */ BOOL presentUnlockedF[PRESENT_MAX];
    /* 0x360 */ char unk360[4];
} PresentWork; /* size = 0x364 */

typedef struct UnkLightDataStruct {
    /* 0x00 */ Vec src;
    /* 0x0C */ Vec dest;
    /* 0x18 */ GXColor color;
} UnkLightDataStruct; /* size = 0x1C */ // same as option::state::UnkLightDataStruct

typedef struct PresentData {
    /* 0x00 */ s32 cursorPosIdx;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 nameMess;
    /* 0x0C */ s32 descMess;
} PresentData; /* size = 0x10 */

typedef struct RoomData {
    /* 0x00 */ s32 presentCount;
    /* 0x04 */ PresentData presentData[11];
} RoomData; /* size = 0xB4 */

typedef struct PresentDistanceStruct {
    /* 0x00 */ s32 present;
    /* 0x04 */ float distance;
} PresentDistanceStruct; /* size = 0x08 */

static void ExecSelectRoom(omObjData *object);
static void ChangeRoom(omObjData *object, s32 direction);
static void ExecSelectPresent(omObjData *object);
static void GetCursorPos(omObjData *object, float *x, float *y, float *z);
static void SetCameraRot(omObjData *object, float rot, s32 duration);
static void RotateCamera(omObjData *object);
static BOOL CameraRotationDoneCheck(omObjData *object);
static void ShowHidePresents(omObjData *object);
static BOOL PresentUnlocked(omObjData *object, s32 room, s32 present);
static s32 UnlockedPresents(omObjData *object, s32 room);
static s32 MoveCursor(omObjData *object, s32 arg1);
static s32 TotalPresentsInRoom(s32 room);
static void ExecPresentGet(omObjData *object);
static s32 fn_1_393C(s32 arg0, s32 arg1);

static UnkLightDataStruct lightTbl = {
    { 0.0f, 400.0f, 0.0f },
    { 0.0f, -400.0f, -500.0f },
    { 255, 255, 255, 255 },
};
static omObjFunc execModeTbl[] = { NULL, ExecSelectRoom, ExecSelectPresent, ExecPresentGet };

static const s32 presentMdlTbl[PRESENT_MDL_MAX] = {
    DATA_MAKE_NUM(DATADIR_PRESENT, 108),
    DATA_MAKE_NUM(DATADIR_PRESENT, 107),
    DATA_MAKE_NUM(DATADIR_PRESENT, 0),
    DATA_MAKE_NUM(DATADIR_PRESENT, 1),
    DATA_MAKE_NUM(DATADIR_PRESENT, 2),
    DATA_MAKE_NUM(DATADIR_PRESENT, 3),
    DATA_MAKE_NUM(DATADIR_PRESENT, 4),
    DATA_MAKE_NUM(DATADIR_PRESENT, 5),
    DATA_MAKE_NUM(DATADIR_PRESENT, 6),
    DATA_MAKE_NUM(DATADIR_PRESENT, 7),
    DATA_MAKE_NUM(DATADIR_PRESENT, 8),
    DATA_MAKE_NUM(DATADIR_PRESENT, 9),
    DATA_MAKE_NUM(DATADIR_PRESENT, 10),
    DATA_MAKE_NUM(DATADIR_PRESENT, 11),
    DATA_MAKE_NUM(DATADIR_PRESENT, 12),
    DATA_MAKE_NUM(DATADIR_PRESENT, 13),
    DATA_MAKE_NUM(DATADIR_PRESENT, 14),
    DATA_MAKE_NUM(DATADIR_PRESENT, 15),
    DATA_MAKE_NUM(DATADIR_PRESENT, 16),
    DATA_MAKE_NUM(DATADIR_PRESENT, 17),
    DATA_MAKE_NUM(DATADIR_PRESENT, 18),
    DATA_MAKE_NUM(DATADIR_PRESENT, 19),
    DATA_MAKE_NUM(DATADIR_PRESENT, 20),
    DATA_MAKE_NUM(DATADIR_PRESENT, 21),
    DATA_MAKE_NUM(DATADIR_PRESENT, 22),
    DATA_MAKE_NUM(DATADIR_PRESENT, 23),
    DATA_MAKE_NUM(DATADIR_PRESENT, 24),
    DATA_MAKE_NUM(DATADIR_PRESENT, 25),
    DATA_MAKE_NUM(DATADIR_PRESENT, 26),
    DATA_MAKE_NUM(DATADIR_PRESENT, 27),
    DATA_MAKE_NUM(DATADIR_PRESENT, 28),
    DATA_MAKE_NUM(DATADIR_PRESENT, 29),
    DATA_MAKE_NUM(DATADIR_PRESENT, 30),
    DATA_MAKE_NUM(DATADIR_PRESENT, 31),
    DATA_MAKE_NUM(DATADIR_PRESENT, 32),
    DATA_MAKE_NUM(DATADIR_PRESENT, 33),
    DATA_MAKE_NUM(DATADIR_PRESENT, 34),
    DATA_MAKE_NUM(DATADIR_PRESENT, 35),
    DATA_MAKE_NUM(DATADIR_PRESENT, 36),
    DATA_MAKE_NUM(DATADIR_PRESENT, 37),
    DATA_MAKE_NUM(DATADIR_PRESENT, 38),
    DATA_MAKE_NUM(DATADIR_PRESENT, 39),
    DATA_MAKE_NUM(DATADIR_PRESENT, 40),
    DATA_MAKE_NUM(DATADIR_PRESENT, 41),
    DATA_MAKE_NUM(DATADIR_PRESENT, 42),
    DATA_MAKE_NUM(DATADIR_PRESENT, 43),
    DATA_MAKE_NUM(DATADIR_PRESENT, 44),
    DATA_MAKE_NUM(DATADIR_PRESENT, 45),
    DATA_MAKE_NUM(DATADIR_PRESENT, 46),
    DATA_MAKE_NUM(DATADIR_PRESENT, 47),
    DATA_MAKE_NUM(DATADIR_PRESENT, 48),
    DATA_MAKE_NUM(DATADIR_PRESENT, 49),
    DATA_MAKE_NUM(DATADIR_PRESENT, 50),
    DATA_MAKE_NUM(DATADIR_PRESENT, 51),
    DATA_MAKE_NUM(DATADIR_PRESENT, 52),
    DATA_MAKE_NUM(DATADIR_PRESENT, 53),
    DATA_MAKE_NUM(DATADIR_PRESENT, 54),
    DATA_MAKE_NUM(DATADIR_PRESENT, 55),
    DATA_MAKE_NUM(DATADIR_PRESENT, 56),
    DATA_MAKE_NUM(DATADIR_PRESENT, 57),
    DATA_MAKE_NUM(DATADIR_PRESENT, 58),
    DATA_MAKE_NUM(DATADIR_PRESENT, 59),
    DATA_MAKE_NUM(DATADIR_PRESENT, 60),
    DATA_MAKE_NUM(DATADIR_PRESENT, 61),
    DATA_MAKE_NUM(DATADIR_PRESENT, 62),
    DATA_MAKE_NUM(DATADIR_PRESENT, 63),
    DATA_MAKE_NUM(DATADIR_PRESENT, 64),
    DATA_MAKE_NUM(DATADIR_PRESENT, 65),
    DATA_MAKE_NUM(DATADIR_PRESENT, 66),
    DATA_MAKE_NUM(DATADIR_PRESENT, 67),
    DATA_MAKE_NUM(DATADIR_PRESENT, 68),
    DATA_MAKE_NUM(DATADIR_PRESENT, 69),
    DATA_MAKE_NUM(DATADIR_PRESENT, 70),
    DATA_MAKE_NUM(DATADIR_PRESENT, 71),
    DATA_MAKE_NUM(DATADIR_PRESENT, 72),
    DATA_MAKE_NUM(DATADIR_PRESENT, 73),
    DATA_MAKE_NUM(DATADIR_PRESENT, 74),
    DATA_MAKE_NUM(DATADIR_PRESENT, 75),
    DATA_MAKE_NUM(DATADIR_PRESENT, 76),
    DATA_MAKE_NUM(DATADIR_PRESENT, 77),
    DATA_MAKE_NUM(DATADIR_PRESENT, 78),
    DATA_MAKE_NUM(DATADIR_PRESENT, 79),
    DATA_MAKE_NUM(DATADIR_PRESENT, 80),
    DATA_MAKE_NUM(DATADIR_PRESENT, 81),
    DATA_MAKE_NUM(DATADIR_PRESENT, 82),
    DATA_MAKE_NUM(DATADIR_PRESENT, 83),
    DATA_MAKE_NUM(DATADIR_PRESENT, 84),
    DATA_MAKE_NUM(DATADIR_PRESENT, 85),
    DATA_MAKE_NUM(DATADIR_PRESENT, 86),
    DATA_MAKE_NUM(DATADIR_PRESENT, 87),
    DATA_MAKE_NUM(DATADIR_PRESENT, 88),
    DATA_MAKE_NUM(DATADIR_PRESENT, 89),
    DATA_MAKE_NUM(DATADIR_PRESENT, 90),
    DATA_MAKE_NUM(DATADIR_PRESENT, 91),
    DATA_MAKE_NUM(DATADIR_PRESENT, 92),
    DATA_MAKE_NUM(DATADIR_PRESENT, 93),
    DATA_MAKE_NUM(DATADIR_PRESENT, 94),
    DATA_MAKE_NUM(DATADIR_PRESENT, 95),
    DATA_MAKE_NUM(DATADIR_PRESENT, 96),
    DATA_MAKE_NUM(DATADIR_PRESENT, 97),
    DATA_MAKE_NUM(DATADIR_PRESENT, 98),
    DATA_MAKE_NUM(DATADIR_PRESENT, 99),
    DATA_MAKE_NUM(DATADIR_PRESENT, 100),
    DATA_MAKE_NUM(DATADIR_PRESENT, 101),
    DATA_MAKE_NUM(DATADIR_PRESENT, 102),
    DATA_MAKE_NUM(DATADIR_PRESENT, 103),
    DATA_MAKE_NUM(DATADIR_PRESENT, 104),
    DATA_MAKE_NUM(DATADIR_PRESENT, 105),
    DATA_MAKE_NUM(DATADIR_PRESENT, 106),
    DATA_MAKE_NUM(DATADIR_PRESENT, 109),
    DATA_MAKE_NUM(DATADIR_PRESENT, 111),
    DATA_MAKE_NUM(DATADIR_PRESENT, 113),
    DATA_MAKE_NUM(DATADIR_PRESENT, 115),
    DATA_MAKE_NUM(DATADIR_PRESENT, 117),
    DATA_MAKE_NUM(DATADIR_PRESENT, 119),
    DATA_MAKE_NUM(DATADIR_PRESENT, 121),
    DATA_MAKE_NUM(DATADIR_PRESENT, 123),
    DATA_MAKE_NUM(DATADIR_PRESENT, 125),
    DATA_MAKE_NUM(DATADIR_PRESENT, 110),
    DATA_MAKE_NUM(DATADIR_PRESENT, 112),
    DATA_MAKE_NUM(DATADIR_PRESENT, 114),
    DATA_MAKE_NUM(DATADIR_PRESENT, 116),
    DATA_MAKE_NUM(DATADIR_PRESENT, 118),
    DATA_MAKE_NUM(DATADIR_PRESENT, 120),
    DATA_MAKE_NUM(DATADIR_PRESENT, 122),
    DATA_MAKE_NUM(DATADIR_PRESENT, 124),
    DATA_MAKE_NUM(DATADIR_PRESENT, 127),
    DATA_MAKE_NUM(DATADIR_PRESENT, 128),
    DATA_MAKE_NUM(DATADIR_PRESENT, 129),
    DATA_MAKE_NUM(DATADIR_PRESENT, 130),
    DATA_MAKE_NUM(DATADIR_PRESENT, 131),
    DATA_MAKE_NUM(DATADIR_PRESENT, 132),
    DATA_MAKE_NUM(DATADIR_PRESENT, 133),
    DATA_MAKE_NUM(DATADIR_PRESENT, 134),
};

static const RoomData roomTbl[10] = {
    {
        0x00000006,
        {
            { 0x00000002, 0x00000008, 0x00320006, 0x00320042 },
            { 0x00000003, 0x00000009, 0x00320007, 0x00320043 },
            { 0x00000004, 0x0000000A, 0x00320008, 0x00320044 },
            { 0x00000005, 0x0000000B, 0x00320009, 0x00320045 },
            { 0x00000006, 0x0000000C, 0x0032000A, 0x00320046 },
            { 0x00000007, 0x0000000D, 0x0032000B, 0x00320047 },
        },
    },
    {
        0x00000006,
        {
            { 0x0000000E, 0x00000014, 0x0032000C, 0x00320048 },
            { 0x0000000F, 0x00000015, 0x0032000D, 0x00320049 },
            { 0x00000010, 0x00000016, 0x0032000E, 0x0032004A },
            { 0x00000011, 0x00000017, 0x0032000F, 0x0032004B },
            { 0x00000012, 0x00000018, 0x00320010, 0x0032004C },
            { 0x00000013, 0x00000019, 0x00320011, 0x0032004D },
        },
    },
    {
        0x00000006,
        {
            { 0x0000001A, 0x00000020, 0x00320012, 0x0032004E },
            { 0x0000001B, 0x00000021, 0x00320013, 0x0032004F },
            { 0x0000001C, 0x00000022, 0x00320014, 0x00320050 },
            { 0x0000001D, 0x00000023, 0x00320015, 0x00320051 },
            { 0x0000001E, 0x00000024, 0x00320016, 0x00320052 },
            { 0x0000001F, 0x00000025, 0x00320017, 0x00320053 },
        },
    },
    {
        0x00000006,
        {
            { 0x00000026, 0x0000002C, 0x00320018, 0x00320054 },
            { 0x00000027, 0x0000002D, 0x00320019, 0x00320055 },
            { 0x00000028, 0x0000002E, 0x0032001A, 0x00320056 },
            { 0x00000029, 0x0000002F, 0x0032001B, 0x00320057 },
            { 0x0000002A, 0x00000030, 0x0032001C, 0x00320058 },
            { 0x0000002B, 0x00000031, 0x0032001D, 0x00320059 },
        },
    },
    {
        0x00000006,
        {
            { 0x00000032, 0x00000038, 0x0032001E, 0x0032005A },
            { 0x00000033, 0x00000039, 0x0032001F, 0x0032005B },
            { 0x00000034, 0x0000003A, 0x00320020, 0x0032005C },
            { 0x00000035, 0x0000003B, 0x00320021, 0x0032005D },
            { 0x00000036, 0x0000003C, 0x00320022, 0x0032005E },
            { 0x00000037, 0x0000003D, 0x00320023, 0x0032005F },
        },
    },
    {
        0x00000001,
        { { 0x00000001, 0xFFFFFFFF, 0x00320041, 0x00320041 } },
    },
    {
        0x00000006,
        {
            { 0x0000003E, 0x00000044, 0x00320024, 0x00320060 },
            { 0x0000003F, 0x00000045, 0x00320025, 0x00320061 },
            { 0x00000040, 0x00000046, 0x00320026, 0x00320062 },
            { 0x00000041, 0x00000047, 0x00320027, 0x00320063 },
            { 0x00000042, 0x00000048, 0x00320028, 0x00320064 },
            { 0x00000043, 0x00000049, 0x00320029, 0x00320065 },
        },
    },
    {
        0x00000006,
        {
            { 0x0000004A, 0x00000050, 0x0032002A, 0x00320066 },
            { 0x0000004B, 0x00000051, 0x0032002B, 0x00320067 },
            { 0x0000004C, 0x00000052, 0x0032002C, 0x00320068 },
            { 0x0000004D, 0x00000053, 0x0032002D, 0x00320069 },
            { 0x0000004E, 0x00000054, 0x0032002E, 0x0032006A },
            { 0x0000004F, 0x00000055, 0x0032002F, 0x0032006B },
        },
    },
    {
        0x00000006,
        {
            { 0x00000056, 0x0000005C, 0x00320030, 0x0032006C },
            { 0x00000057, 0x0000005D, 0x00320031, 0x0032006D },
            { 0x00000058, 0x0000005E, 0x00320032, 0x0032006E },
            { 0x00000059, 0x0000005F, 0x00320033, 0x0032006F },
            { 0x0000005A, 0x00000060, 0x00320034, 0x00320070 },
            { 0x0000005B, 0x00000061, 0x00320035, 0x00320071 },
        },
    },
    {
        0x0000000B,
        {
            { 0x00000062, 0xFFFFFFFF, 0x00320036, 0x00320072 },
            { 0x00000063, 0xFFFFFFFF, 0x00320037, 0x00320073 },
            { 0x00000064, 0xFFFFFFFF, 0x00320038, 0x00320074 },
            { 0x00000065, 0xFFFFFFFF, 0x00320039, 0x00320075 },
            { 0x00000066, 0xFFFFFFFF, 0x0032003A, 0x00320076 },
            { 0x00000067, 0xFFFFFFFF, 0x0032003B, 0x00320077 },
            { 0x00000068, 0xFFFFFFFF, 0x0032003C, 0x00320078 },
            { 0x00000069, 0xFFFFFFFF, 0x0032003D, 0x00320079 },
            { 0x0000006A, 0xFFFFFFFF, 0x0032003E, 0x0032007A },
            { 0x0000006B, 0xFFFFFFFF, 0x0032003F, 0x0032007B },
            { 0x0000006C, 0xFFFFFFFF, 0x00320040, 0x0032007C },
        },
    },
};

omObjData *PresentCreate(void)
{
    s32 i;
    s32 j;
    s16 light;
    LightData *lightData;

    omObjData *object = omAddObjEx(presentObjMan, 1003, 0, 0, 1, NULL);
    PresentWork *work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(PresentWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    work->room = 0;
    work->idxInRoom = 0;
    work->rot = 0.0f;
    work->timeRot = 1.0f;
    work->rotSpeed = 0.0f;

    for (i = 0; i < PRESENT_MAX; i++) {
        work->presentUnlockedF[i] = GWGameStat.present[i];
    }

    for (i = 0; i < PRESENT_MAX - 1; i++) {
        if (!work->presentUnlockedF[i]) {
            break;
        }
    }
    if (i == PRESENT_MAX - 1) {
        work->presentUnlockedF[PRESENT_MAX - 1] = TRUE;
    }
    Hu3DLighInit();
    light = Hu3DGLightCreateV(&lightTbl.src, &lightTbl.dest, &lightTbl.color);
    Hu3DGLightInfinitytSet(light);
    Hu3DGLightStaticSet(light, 1);
    lightData = &Hu3DGlobalLight[light];
    lightData->unk_00 |= 0x8000;

    for (i = 0; i < PRESENT_MDL_MAX; i++) {
        work->object[i] = omAddObjEx(presentObjMan, 1003, 1, 0, 1, NULL);
        work->object[i]->model[0] = Hu3DModelCreateFile(presentMdlTbl[i]);
        Hu3DModelLayerSet(work->object[i]->model[0], 0);
        Hu3DModelAttrSet(work->object[i]->model[0], 1);
    }

    for (j = 0; j < 8; j++) {
        for (i = 0; i < 6; i++) {
            Hu3DModelLayerSet(work->object[i + 2 + j * 6 * 2]->model[0], 1);
        }
    }
    Hu3DModelShadowMapSet(work->object[0]->model[0]);
    ShowHidePresents(object);
    work->cursor = espEntry(DATA_MAKE_NUM(DATADIR_PRESENT, 135), 0, 0);
    espDispOff(work->cursor);
    work->presentDescWindow = PresentWinCreate(0);
    work->btnLegendWindow = PresentWinCreate(1);
    SetCameraRot(object, work->room * 36.0f, 1);
    RotateCamera(object);
    PresentExecModeSet(object, PRESENT_MODE_NONE);

    (void)light;
    return object;
}

void PresentKill(omObjData *object)
{
    s32 i;

    PresentWork *work = object->data;
    PresentWinKill(work->presentDescWindow);
    PresentWinKill(work->btnLegendWindow);

    for (i = 0; i < PRESENT_MDL_MAX; i++) {
        Hu3DModelKill(work->object[i]->model[0]);
    }
    espKill(work->cursor);
    HuMemDirectFree(work);
}

void PresentExecModeSet(omObjData *object, s32 execMode)
{
    PresentWork *work = object->data;

    work->execMode = execMode;
    object->func = execModeTbl[execMode];
    object->unk10 = 0;
    object->unk10 = 0;
}

s32 PresentExecModeGet(omObjData *object)
{
    PresentWork *work = object->data;
    return work->execMode;
}

static const s32 roomIdxTbl[NUM_CHARACTERS] = {
    ROOM_MARIO,
    ROOM_LUIGI,
    ROOM_PEACH,
    ROOM_YOSHI,
    ROOM_WARIO,
    ROOM_DK,
    ROOM_DAISY,
    ROOM_WALUIGI,
};

void PresentSelectedIDSet(omObjData *object, s32 id)
{
    PresentWork *work = object->data;

    if (id < 48) {
        work->room = roomIdxTbl[id / PRESENT_COUNT_CHAR_ROOM];
        work->idxInRoom = id % PRESENT_COUNT_CHAR_ROOM;
        return;
    }
    if (id < 59) {
        work->room = ROOM_MG;
        work->idxInRoom = (id - 48) % PRESENT_COUNT_MG_ROOM;
        return;
    }
    work->room = ROOM_TROPHY;
    work->idxInRoom = 0;
}

static const s32 roomMessTbl[] = { 0, 1, 2, 3, 4, 0, 5, 6, 7, 0 };

static void ExecSelectRoom(omObjData *object)
{
    Vec cursorPos;
    s32 mess;

    PresentWork *work = object->data;

    switch (object->unk10) {
        case 0:
            work->cursorVisibleF = FALSE;
            work->constellationSelF = FALSE;
            object->unk10 = 1;
        case 1:
            if (work->constellationSelF) {
                PresentCameraTargetSet(presentCamera, 0.0f, 220.0f, 250.0f, 30);
                PresentCameraFocusSet(presentCamera, 0.0f, 420.0f, -600.0f, 30);
            }
            else {
                PresentCameraTargetSet(presentCamera, 0.0f, 220.0f, 250.0f, 30);
                PresentCameraFocusSet(presentCamera, 0.0f, 0.0f, -600.0f, 30);
            }
            object->unk10 = 2;
        case 2:
            if (!PresentCameraDoneCheck(presentCamera) && !work->presentDescWindow->state && !CameraRotationDoneCheck(object)) {
                PresentWinAnimIn(work->presentDescWindow);
                PresentWinAnimIn(work->btnLegendWindow);
                if (work->constellationSelF) {
                    mess = MAKE_MESSID(0x32, 0x80);
                }
                else if (work->room == ROOM_TROPHY) {
                    mess = MAKE_MESSID(0x32, 0x85);
                }
                else {
                    mess = MAKE_MESSID(0x32, 0x7e);
                }
                PresentWinMesSet(work->btnLegendWindow, mess);
                switch (work->room) {
                    case ROOM_MARIO:
                    case ROOM_LUIGI:
                    case ROOM_PEACH:
                    case ROOM_YOSHI:
                    case ROOM_WARIO:
                    case ROOM_DK:
                    case ROOM_DAISY:
                    case ROOM_WALUIGI:
                        if (work->constellationSelF) {
                            if (PresentUnlocked(object, work->room, ROOM_TROPHY)) {
                                mess = MAKE_MESSID(0x32, 0x05);
                            }
                            else {
                                mess = MAKE_MESSID(0x32, 0x82);
                            }
                        }
                        else if (UnlockedPresents(object, work->room) > 0) {
                            mess = MAKE_MESSID(0x32, 0x01);
                        }
                        else {
                            mess = MAKE_MESSID(0x32, 0x81);
                        }
                        PresentWinMesSet(work->presentDescWindow, mess);
                        PresentWinInsertMesSet(work->presentDescWindow, roomMessTbl[work->room], 0);
                        break;
                    case ROOM_TROPHY:
                        if (PresentUnlocked(object, ROOM_TROPHY, 0)) {
                            mess = MAKE_MESSID(0x32, 0x41);
                        }
                        else {
                            mess = MAKE_MESSID(0x32, 0x84);
                        }
                        PresentWinMesSet(work->presentDescWindow, mess);
                        break;
                    case ROOM_MG:
                        if (UnlockedPresents(object, ROOM_MG) > 0) {
                            mess = MAKE_MESSID(0x32, 0x83);
                        }
                        else {
                            mess = MAKE_MESSID(0x32, 0x81);
                        }
                        PresentWinMesSet(work->presentDescWindow, mess);
                        break;
                    default:
                        break;
                }
                if (work->constellationSelF) {
                    cursorPos.x = 0.0f;
                    cursorPos.y = 600.0f;
                    cursorPos.z = -500.0f;
                }
                else {
                    cursorPos.x = 0.0f;
                    cursorPos.y = 210.0f;
                    cursorPos.z = -500.0f;
                }
                Hu3D3Dto2D(&cursorPos, 1, &cursorPos);
                cursorPos.y -= 15.0f;
                cursorPos.x -= 20.0f;
                espPosSet(work->cursor, cursorPos.x, cursorPos.y);
                if (!work->cursorVisibleF) {
                    PresentFadeSprite(work->cursor, TRUE, 5);
                    work->cursorVisibleF = TRUE;
                }
                object->unk10 = 3;
            }
            break;
        case 3:
            if (!work->presentDescWindow->state) {
                if (PresentPadCheck(PAD_BUTTON_B) && !work->constellationSelF) {
                    PresentFadeSprite(work->cursor, FALSE, 5);
                    work->cursorVisibleF = FALSE;
                    PresentWinAnimOut(work->presentDescWindow);
                    PresentWinAnimOut(work->btnLegendWindow);
                    HuAudFXPlay(3);
                    object->unk10 = 4;
                }
                else if (PresentPadCheck(PAD_BUTTON_A) && !work->constellationSelF) {
                    if (work->room != ROOM_TROPHY) {
                        PresentFadeSprite(work->cursor, FALSE, 5);
                        work->cursorVisibleF = FALSE;
                        PresentWinAnimOut(work->presentDescWindow);
                        PresentWinAnimOut(work->btnLegendWindow);
                        HuAudFXPlay(2);
                        PresentExecModeSet(object, PRESENT_MODE_SELECT_PRESENT);
                    }
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_UP) && !work->constellationSelF) {
                    if (work->room != ROOM_TROPHY && work->room != ROOM_MG) {
                        work->constellationSelF = TRUE;
                        PresentFadeSprite(work->cursor, FALSE, 5);
                        work->cursorVisibleF = FALSE;
                        PresentWinAnimOut(work->presentDescWindow);
                        PresentWinAnimOut(work->btnLegendWindow);
                        HuAudFXPlay(0);
                        object->unk10 = 1;
                    }
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_DOWN) && work->constellationSelF) {
                    work->constellationSelF = FALSE;
                    PresentFadeSprite(work->cursor, FALSE, 5);
                    work->cursorVisibleF = FALSE;
                    PresentWinAnimOut(work->presentDescWindow);
                    PresentWinAnimOut(work->btnLegendWindow);
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_LEFT)) {
                    ChangeRoom(object, ROOM_CHANGE_LEFT);
                    HuAudFXPlay(0);
                    object->unk10 = 2;
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_RIGHT)) {
                    ChangeRoom(object, ROOM_CHANGE_RIGHT);
                    HuAudFXPlay(0);
                    object->unk10 = 2;
                }
            }
            break;
        case 4:
            PresentExecModeSet(object, PRESENT_MODE_NONE);
            break;
    }
    RotateCamera(object);
}

static void ChangeRoom(omObjData *object, s32 direction)
{
    float rotAbs;
    float rot;
    float rotTarget;

    s32 special;
    s32 change;
    s32 duration;

    PresentWork *work = object->data;

    for (special = 0, rotAbs = 0.0f;; special++) {
        rotAbs += 36.0f;
        if (direction == ROOM_CHANGE_LEFT) {
            change = -1;
        }
        else {
            change = 1;
        }
        work->room += change;
        if (work->room < ROOM_MARIO) {
            work->room = ROOM_MAX;
        }
        else if (work->room >= ROOM_MAX + 1) {
            work->room = ROOM_MARIO;
        }
        if (!work->constellationSelF || (work->room != ROOM_TROPHY && work->room != ROOM_MG)) {
            break;
        }
    }
    if (direction == ROOM_CHANGE_LEFT) {
        rot = -rotAbs;
    }
    else {
        rot = rotAbs;
    }
    rotTarget = work->rot + rot;
    if (special == 0) {
        duration = 30;
    }
    else {
        duration = 45;
    }
    SetCameraRot(object, rotTarget, duration);
}

static void ExecSelectPresent(omObjData *object)
{
    float cursorX;
    float cursorY;

    PresentWork *work = object->data;
    s32 idxInRoom = work->idxInRoom;
    s32 room = work->room;
    switch (object->unk10) {
        case 0:
            PresentCameraTargetSet(presentCamera, 0.0f, 220.0f, -120.0f, 30);
            PresentCameraFocusSet(presentCamera, 0.0f, 0.0f, -600.0f, 30);
            work->roomNotEmptyF = UnlockedPresents(object, room) > 0;
            work->cursorVisibleF = FALSE;
            work->idxInRoom = 0;
            if (work->roomNotEmptyF) {
                s32 totalPresents = TotalPresentsInRoom(work->room);
                s32 i;
                // set the initial present to the highest unlocked one
                for (i = 0; i < totalPresents; i++) {
                    if (PresentUnlocked(object, room, i)) {
                        work->idxInRoom = i;
                        break;
                    }
                }
            }
            object->unk10 = 1;
        case 1:
            if (PresentCameraDoneCheck(presentCamera)) {
                break;
            }
            PresentWinAnimIn(work->presentDescWindow);
            PresentWinAnimIn(work->btnLegendWindow);
            PresentWinMesSet(work->btnLegendWindow, MAKE_MESSID(0x32, 0x7F));

            if (work->roomNotEmptyF) {
                PresentWinMesSet(work->presentDescWindow, roomTbl[room].presentData[idxInRoom].descMess);
            }
            else {
                PresentWinMesSet(work->presentDescWindow, MAKE_MESSID(0x32, 0x03));
            }
            work->cursorTime = 0.0f;
            work->cursorSpeed = 1.0f / 6.0f;
            if (work->roomNotEmptyF) {
                Vec cursorPos;
                GetCursorPos(work->object[roomTbl[room].presentData[idxInRoom].cursorPosIdx], &cursorPos.x, &cursorPos.y, &cursorPos.z);
                Hu3D3Dto2D(&cursorPos, 1, &cursorPos);
                cursorPos.y -= 15.0f;
                cursorPos.x -= 20.0f;
                if (!work->cursorVisibleF) {
                    PresentFadeSprite(work->cursor, TRUE, 5);
                    work->cursorVisibleF = TRUE;
                    work->cursorPos.x = cursorPos.x;
                    work->cursorPos.y = cursorPos.y;
                }
                else {
                    work->cursorPos.x = work->newCursorPos.x;
                    work->cursorPos.y = work->newCursorPos.y;
                }
                work->newCursorPos.x = cursorPos.x;
                work->newCursorPos.y = cursorPos.y;
                object->unk10 = 2;
            }
            else {
                object->unk10 = 3;
                break;
            }
        case 2:
            cursorX = work->cursorPos.x + (work->cursorTime * (work->newCursorPos.x - work->cursorPos.x));
            cursorY = work->cursorPos.y + (work->cursorTime * (work->newCursorPos.y - work->cursorPos.y));
            espPosSet(work->cursor, cursorX, cursorY);
            if ((work->cursorTime += work->cursorSpeed) < 1.0f) {
                break;
            }
            espPosSet(work->cursor, work->newCursorPos.x, work->newCursorPos.y);
            object->unk10 = 3;
        case 3:
            if (PresentPadCheck(PAD_BUTTON_B)) {
                PresentWinAnimOut(work->presentDescWindow);
                PresentWinAnimOut(work->btnLegendWindow);
                HuAudFXPlay(3);
                object->unk10 = 4;
            }
            else if (work->roomNotEmptyF) {
                if (PresentPadDStkRepCheck(PAD_BUTTON_LEFT) && PresentPadDStkCheck(PAD_BUTTON_UP)) {
                    idxInRoom = MoveCursor(object, 5);
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_LEFT) && PresentPadDStkCheck(PAD_BUTTON_DOWN)) {
                    idxInRoom = MoveCursor(object, 9);
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_RIGHT) && PresentPadDStkCheck(PAD_BUTTON_UP)) {
                    idxInRoom = MoveCursor(object, 6);
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_RIGHT) && PresentPadDStkCheck(PAD_BUTTON_DOWN)) {
                    idxInRoom = MoveCursor(object, 10);
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_LEFT)) {
                    idxInRoom = MoveCursor(object, 1);
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_RIGHT)) {
                    idxInRoom = MoveCursor(object, 2);
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_UP)) {
                    idxInRoom = MoveCursor(object, 4);
                }
                else if (PresentPadDStkRepCheck(PAD_BUTTON_DOWN)) {
                    idxInRoom = MoveCursor(object, 8);
                }
            }
            else {
                break;
            }
            if (idxInRoom == -1) {
                idxInRoom = work->idxInRoom;
            }
            if (idxInRoom != work->idxInRoom) {
                work->idxInRoom = idxInRoom;
                object->unk10 = 1;
                HuAudFXPlay(0);
            }
            break;
        case 4:
            if (work->cursorVisibleF) {
                PresentFadeSprite(work->cursor, FALSE, 5);
            }
            PresentExecModeSet(object, PRESENT_MODE_SELECT_ROOM);
            break;
        default:
            break;
    }
}

static void GetCursorPos(omObjData *object, float *x, float *y, float *z)
{
    Mtx sp8;

    Hu3DModelObjMtxGet(object->model[0], "cursor", sp8);
    *x = sp8[0][3];
    *y = sp8[1][3];
    *z = sp8[2][3];
}

static void SetCameraRot(omObjData *object, float rot, s32 duration)
{
    PresentWork *work = object->data;

    work->rotTarget = rot;
    work->rotPrev = work->rot;
    work->timeRot = 0.0f;
    work->rotSpeed = 1.0f / duration;
}

static void RotateCamera(omObjData *object)
{
    s32 i;
    PresentWork *work = object->data;

    if (work->timeRot < 1.0f) {
        float weight = sind(90.0f * work->timeRot);
        weight *= weight;
        work->rot = work->rotPrev + (weight * (work->rotTarget - work->rotPrev));

        if ((work->timeRot += work->rotSpeed) >= 1.0f) {
            work->rot = work->rotTarget;
        }
    }
    work->rot = fmod(work->rot, 360.0);

    if (work->rot < 0.0f) {
        work->rot += 360.0f;
    }

    for (i = 0; i < PRESENT_MDL_MAX; i++) {
        omSetRot(work->object[i], 0.0f, work->rot, 0.0f);
    }
}

static BOOL CameraRotationDoneCheck(omObjData *object)
{
    PresentWork *work = object->data;
    return work->timeRot < 1.0f;
}

s32 roomIdxTbl2[NUM_CHARACTERS] = {
    ROOM_MARIO,
    ROOM_LUIGI,
    ROOM_PEACH,
    ROOM_YOSHI,
    ROOM_WARIO,
    ROOM_DK,
    ROOM_DAISY,
    ROOM_WALUIGI,
};

static void ShowHidePresents(omObjData *object)
{
    PresentWork *work = object->data;
    s32 character;
    s32 i;

    Hu3DModelAttrReset(work->object[0]->model[0], 1);

    for (character = 0; character < NUM_CHARACTERS; character++) {
        s32 j;
        if (UnlockedPresents(object, roomIdxTbl2[character]) > 0) {
            Hu3DModelAttrReset(work->object[character + 109]->model[0], 1);
        }

        for (j = 0, i = 0; i < PRESENT_COUNT_CHAR_ROOM; i++) {
            if (PresentUnlocked(object, roomIdxTbl2[character], i)) {
                Hu3DModelAttrReset(work->object[character * PRESENT_COUNT_CHAR_ROOM * 2 + 2 + i]->model[0], 1);
                Hu3DModelAttrReset(work->object[character * PRESENT_COUNT_CHAR_ROOM * 2 + 8 + i]->model[0], 1);
                j++;
            }
        }
        if (j >= 6) {
            Hu3DModelAttrReset(work->object[character + 118]->model[0], 1);
        }
    }
    if (UnlockedPresents(object, ROOM_MG) > 0) {
        Hu3DModelAttrReset(work->object[117]->model[0], 1);
    }
    for (i = 0; i < PRESENT_COUNT_MG_ROOM; i++) {
        if (PresentUnlocked(object, ROOM_MG, i)) {
            Hu3DModelAttrReset(work->object[i + 98]->model[0], 1);
        }
    }
    if (PresentUnlocked(object, ROOM_TROPHY, 0)) {
        Hu3DModelAttrReset(work->object[1]->model[0], 1);
    }
    for (i = 0; i < NUM_CHARACTERS; i++) {
        if (PresentUnlocked(object, roomIdxTbl2[i], PRESENT_CONSTELLATION)) {
            Hu3DModelAttrReset(work->object[i + 126]->model[0], 1);
        }
    }
}

static const s32 roomPresentOffsetTbl[] = { 0, 6, 12, 18, 24, 59, 30, 36, 42, 48 };

static BOOL PresentUnlocked(omObjData *object, s32 room, s32 present)
{
    PresentWork *work = object->data;
    return work->presentUnlockedF[roomPresentOffsetTbl[room] + present] != 0;
}

static s32 UnlockedPresents(omObjData *object, s32 room)
{
    s32 i;
    s32 unlockedPresents;
    s32 presentCount = TotalPresentsInRoom(room);

    for (unlockedPresents = 0, i = 0; i < presentCount; i++) {
        if (PresentUnlocked(object, room, i)) {
            unlockedPresents++;
        }
    }

    return unlockedPresents;
}

/* Returns the index of the newly selected present inside the room */
static s32 MoveCursor(omObjData *object, s32 arg1)
{
    PresentDistanceStruct availablePresents[10];
    Vec cursorPos;

    float angle;

    PresentWork *work = object->data;
    s32 present;
    s32 i;
    s32 j;
    s32 var_r23;
    s32 totalPresents = TotalPresentsInRoom(work->room);
    s32 unlockedPresents = UnlockedPresents(object, work->room);

    if (unlockedPresents == 1) {
        return work->idxInRoom;
    }

    GetCursorPos(work->object[roomTbl[work->room].presentData[work->idxInRoom].cursorPosIdx], &cursorPos.x, &cursorPos.y, &cursorPos.z);
    Hu3D3Dto2D(&cursorPos, 1, &cursorPos);
    for (i = 0, j = 0; i == 0 && j < 1; j++) {
        for (i = 0, present = 0; present < totalPresents; present++) {
            Vec cursorPosNew;
            float dx, dy;
            if (present == work->idxInRoom) {
                continue;
            }
            if (!PresentUnlocked(object, work->room, present)) {
                continue;
            }
            GetCursorPos(work->object[roomTbl[work->room].presentData[present].cursorPosIdx], &cursorPosNew.x, &cursorPosNew.y, &cursorPosNew.z);
            Hu3D3Dto2D(&cursorPosNew, 1, &cursorPosNew);
            dx = cursorPos.x - cursorPosNew.x;
            dy = cursorPos.y - cursorPosNew.y;
            angle = fmod(atan2d(dx, dy), 360.0);
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            if ((arg1 == 1 && angle >= 45.0f && angle < 135.0f) || (arg1 == 2 && angle >= 225.0f && angle < 315.0f)
                || (arg1 == 8 && angle >= 135.0f && angle < 225.0f)
                || (arg1 == 4 && (angle >= 0.0f && angle < 45.0f || angle >= 315.0f && angle < 360.0f))
                || (arg1 == 5 && angle >= 0.0f && angle < 90.0f) || (arg1 == 9 && angle >= 90.0f && angle < 180.0f)
                || (arg1 == 6 && angle >= 270.0f && angle < 360.0f) || (arg1 == 10 && angle >= 180.0f && angle < 270.0f)) {
                availablePresents[i].present = present;
                availablePresents[i].distance = sqrtf(dx * dx + dy * dy);
                i++;
            }
        }

        if (i != 0) {
            continue;
        }
        switch (arg1) {
            case 0:
                break;
            case 1:
                arg1 = 2;
                break;
            case 2:
                arg1 = 1;
                break;
            case 3:
                break;
            case 4:
                arg1 = 8;
                break;
            case 7:
                break;
            case 8:
                arg1 = 4;
                break;
            case 5:
                arg1 = 10;
                break;
            case 9:
                arg1 = 6;
                break;
            case 6:
                arg1 = 9;
                break;
            case 10:
                arg1 = 5;
                break;
            default:
                break;
        }
    }
    if (i == 0) {
        return work->idxInRoom;
    }
    do {
        for (var_r23 = 0, present = 0; present < (i - 1); present++) {
            if (availablePresents[present].distance > availablePresents[present + 1].distance) {
                PresentDistanceStruct next = availablePresents[present + 1];
                availablePresents[present + 1] = availablePresents[present];
                availablePresents[present] = next;
                var_r23 = 1;
            }
        }
    } while (var_r23);
    return availablePresents[(j <= 1) ? 0 : i - 1].present;
}

static const s32 totalPresentCntTbl[10] = { 6, 6, 6, 6, 6, 1, 6, 6, 6, 11 };

static s32 TotalPresentsInRoom(s32 room)
{
    return totalPresentCntTbl[room];
}

static const s32 presentItemIdxTbl[10] = { 2, 14, 26, 38, 50, 0, 62, 74, 86, 0 };
static const s32 lbl_1_rodata_B18[10] = { 8, 20, 32, 44, 56, 0, 68, 80, 92, 0 };
static const s32 constellationIdxTbl[10] = { 126, 127, 128, 129, 130, 0, 131, 132, 133, 0 };
static const s32 roofIdxTbl[10] = { 118, 119, 120, 121, 122, 0, 123, 124, 125, 0 };

static void ExecPresentGet(omObjData *object)
{
    f32 weight;
    f32 rot;

    PresentWork *work = object->data;

    switch (object->unk10) {
        case 0:
            rot = 36.0f * work->room;
            SetCameraRot(object, rot, 1);
            RotateCamera(object);
            Hu3DModelAttrSet(work->object[work->idxInRoom + lbl_1_rodata_B18[work->room]]->model[0], 1);
            Hu3DModelAttrSet(work->object[roofIdxTbl[work->room]]->model[0], 1);
            Hu3DModelAttrSet(work->object[constellationIdxTbl[work->room]]->model[0], 1);
            work->presentFallingTime = 0.0f;
            work->presentFallingSpeed = 1.0f / 360.0f;
            object->unk10 = 1;
        case 1:
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 120);
            object->unk10 = 2;
        case 2:
            weight = sind(90.0f * work->presentFallingTime);
            weight *= weight;
            PresentCameraTargetSet(presentCamera, 0.0f, 820.0f - (600.0f * weight), -120.0f, 1);
            PresentCameraFocusSet(presentCamera, 0.0f, 680.0f - (680.0f * weight), -600.0f, 1);
            omSetTra(work->object[work->idxInRoom + presentItemIdxTbl[work->room]], 0.0f, 840.0f - (840.0f * weight), 0.0f);
            if ((work->presentFallingTime += work->presentFallingSpeed) < 1.0f) {
                return;
            }
            if (fn_1_393C(work->room, work->idxInRoom)) {
                FadeSpriteWithMultiplier(work->object[work->idxInRoom + lbl_1_rodata_B18[work->room]]->model[0], 1, 0.4f, 30);
            }
            object->unk10 = 3;
        case 3:
            PresentWinAnimIn(work->presentDescWindow);
            PresentWinInsertMesSet(work->presentDescWindow, roomTbl[work->room].presentData[work->idxInRoom].nameMess, 0);
            PresentWinMesSet(work->presentDescWindow, MAKE_MESSID(0x32, 0x04));
            PresentWinMesWait(work->presentDescWindow);
            object->unk10 = 4;
        case 4:
            if (work->presentDescWindow->state) {
                break;
            }
            object->unk10 = 5;
        case 5:
            PresentWinAnimOut(work->presentDescWindow);
            object->unk10 = 6;
        case 6:
            if (!work->presentDescWindow->state) {
                PresentExecModeSet(object, PRESENT_MODE_NONE);
            }
            break;
    }
}

static const s32 lbl_1_rodata_BA4[][2] = { { 7, 1 } };

static s32 fn_1_393C(s32 arg0, s32 arg1)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 1; var_r31++) {
        if (arg0 == lbl_1_rodata_BA4[var_r31][0] && arg1 == lbl_1_rodata_BA4[var_r31][1]) {
            return 0;
        }
    }
    return 1;
}
