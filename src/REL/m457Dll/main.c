#include "dolphin/pad.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfdraw.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "string.h"

#include "ext_math.h"
#include "version.h"

s32 rand8(void);

#define MSM_SE_BOWSER_LAUGH 0x3A
#define MSM_SE_BOWSER_HOWL 0x3E
#define MSM_SE_KOOPA_KID_DROP 0x5B
#define MSM_SE_PLAYER_DROP 0x33D
#define MSM_SE_WIND 0x6D7
#define MSM_SE_INVINCIBILITY 0x7E6

#define MSM_MUS_BACKGROUND 0x4D

#define MODEL_ID_PLAYER_PLAYER 0

#define MODEL_ID_GAME_SKY 0
#define MODEL_ID_GAME_RING 1
#define MODEL_ID_GAME_MUSHROOM 2
#define MODEL_ID_GAME_INVINCE_SHINING 3
#define MODEL_ID_GAME_INVINCE_SPARKS 4
#define MODEL_ID_GAME_KOOPA_KID 5
#define MODEL_ID_GAME_WAR_FAN 6

#define CHARACTER_BOWSER -1
#define PAD_IDX_COM -1

#define PLAYER_STATE_INITIAL_ADVANCE 2 // TODO is this right?
#define PLAYER_STATE_FALLING 16

#define PREV_TRIG_L 0
#define PREV_TRIG_R 1

typedef struct PlayerData {
    /* 0x00 */ s32 group;
    /* 0x04 */ s32 player;
    /* 0x08 */ s32 character;
    /* 0x0C */ s32 padIdx;
    /* 0x10 */ s32 diff;
    /* 0x14 */ s32 state;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 invinceTime;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 stamina;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 prevTrig;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ float unk48;
    /* 0x4C */ s32 unk4C;
} PlayerData; // Size 0x50

typedef struct StructBss78 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ float unk04[3];
} StructBss78; // Size 0x10

typedef struct StructData28C {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
} StructData28C; // Size 0x18

typedef struct SparkData {
    /* 0x00 */ float scale;
    /* 0x04 */ float xOffset;
    /* 0x08 */ float yOffset;
} SparkData; // Size 0x0C

static void M457Exit(omObjData *object);

static StructBss78 lbl_1_bss_78[5];
static omObjData *mainObj;
static omObjData *omViewObj;
static omObjData *playerObj[2];
static omObjData *gameObj;
static s32 lbl_1_bss_60;
static s32 gameState;
static char lbl_1_bss_58[4]; // unused
static s32 lbl_1_bss_54;
static s32 lbl_1_bss_50;
static Process *objman;
static s32 lightId;
static s32 lbl_1_bss_44;
static s32 lbl_1_bss_40;
static s32 lbl_1_bss_3C;
static char lbl_1_bss_38[4]; // unused
static float lbl_1_bss_34;
static float lbl_1_bss_30;
static float lbl_1_bss_2C;
static float lbl_1_bss_28;
static s32 lbl_1_bss_24;
static s32 lbl_1_bss_20;
static s32 lbl_1_bss_1C;
static s32 lbl_1_bss_18;
static BOOL againstBrowserF;
static s32 m457MesEndF;
static char lbl_1_bss_8[8]; // unused
static s32 lbl_1_bss_4;
static char lbl_1_bss_0[4]; // unused

s32 sprDataNumTbl[] = { DATA_MAKE_NUM(DATADIR_M457, 23), DATA_MAKE_NUM(DATADIR_M457, 22), DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_M457, 24), DATA_MAKE_NUM(DATADIR_M457, 24), DATA_MAKE_NUM(DATADIR_M457, 24), DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0), DATA_MAKE_NUM(DATADIR_M457, 23), DATA_MAKE_NUM(DATADIR_M457, 22), DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_M457, 24), DATA_MAKE_NUM(DATADIR_M457, 24), DATA_MAKE_NUM(DATADIR_M457, 24), DATA_MAKE_NUM(DATADIR_M457, 24),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0), DATA_MAKE_NUM(DATADIR_M457, 27), DATA_MAKE_NUM(DATADIR_M457, 28), DATA_MAKE_NUM(DATADIR_M457, 25),
    DATA_MAKE_NUM(DATADIR_M457, 25), DATA_MAKE_NUM(DATADIR_M457, 25), DATA_MAKE_NUM(DATADIR_M457, 25), DATA_MAKE_NUM(DATADIR_M457, 25) };

s32 sprIdTbl[23] = { 0 };

s32 lbl_1_data_B8[] = { DATA_MAKE_NUM(DATADIR_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MARIOMOT, 5), DATA_MAKE_NUM(DATADIR_MARIOMOT, 6),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 112), DATA_MAKE_NUM(DATADIR_MARIOMOT, 111), DATA_MAKE_NUM(DATADIR_M457, 8), DATA_MAKE_NUM(DATADIR_M457, 0),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 12), DATA_MAKE_NUM(DATADIR_MARIOMOT, 13), DATA_MAKE_NUM(DATADIR_MARIOMOT, 21),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 23), DATA_MAKE_NUM(DATADIR_MARIOMOT, 24) };

u32 lbl_1_data_E8[] = { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 };

u32 lbl_1_data_118[] = { DATA_MAKE_NUM(DATADIR_BKOOPA, 8), DATA_MAKE_NUM(DATADIR_BKOOPA, 10), 0, DATA_MAKE_NUM(DATADIR_M457, 31),
    DATA_MAKE_NUM(DATADIR_M457, 32), DATA_MAKE_NUM(DATADIR_M457, 33), DATA_MAKE_NUM(DATADIR_M457, 34), DATA_MAKE_NUM(DATADIR_M457, 35),
    DATA_MAKE_NUM(DATADIR_M457, 36), DATA_MAKE_NUM(DATADIR_M457, 37), DATA_MAKE_NUM(DATADIR_M457, 29), DATA_MAKE_NUM(DATADIR_M457, 30) };

u8 lbl_1_data_148[12] = { 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1 };
s32 lbl_1_data_154[12] = { 8, 0, 0, 8, 5, 8, 4, 2, 2, 8, 8, 8 };
s32 lbl_1_data_184[12] = { 0 };

float lbl_1_data_1B4[9][3] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 20.0f }, { 20.0f, 70.0f, 20.0f }, { 20.0f, 20.0f, 20.0f },
    { 50.0f, -70.0f, 0.0f }, { 20.0f, 60.0f, 20.0f }, { 100.0f, 0.0f, 50.0f }, { -70.0f, -70.0f, -70.0f } };

SparkData sparkDataTbl[9] = { { 1.5f, 45.0f, 270.0f }, { 1.7f, 45.0f, 270.0f }, { 1.8f, 45.0f, 270.0f }, { 1.6f, 45.0f, 270.0f },
    { 1.7f, 5.0f, 270.0f }, { 2.0f, -85.0f, 295.0f }, { 1.8f, 45.0f, 270.0f }, { 2.0f, 40.0f, 330.0f }, { 2.25f, -30.0f, 300.0f } };

StructData28C lbl_1_data_28C = { 0 };

s16 lbl_1_data_2A4 = -1;
s16 lbl_1_data_2A6 = -1;
s32 backgroundMusNo = -1;
s32 windSeNo = -1;
s16 lbl_1_data_2B0 = -1;
s32 invincibilitySeNo = -1;
s32 lbl_1_data_2B8 = 10 * REFRESH_RATE;

static void CameraPrintDebug(void)
{
    Center.x += 10.0 * (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) - ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0));
    Center.z -= 10.0 * (((HuPadBtn[0] & PAD_BUTTON_UP) != 0) - ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0));
    Center.y += 10.0 * (((HuPadBtn[0] & PAD_BUTTON_Y) != 0) - ((HuPadBtn[0] & PAD_BUTTON_X) != 0));
    CZoom += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_X) != 0) - ((HuPadBtn[0] & PAD_BUTTON_Y) != 0));
    CRot.y += HuPadSubStkX[0] / 16.0;
    CRot.x += HuPadSubStkY[0] / -16.0;
    print8(64, 392, 1.0f, "%f,%f,%f", Center.x, Center.y, Center.z);
    print8(64, 408, 1.0f, "%f,%f,%f", CRot.x, CRot.y, CRot.z);
    print8(64, 424, 1.0f, "%f", CZoom);
}

static void M457PlayerExec(omObjData *object)
{
    PlayerData *playerData = object->data;
    PlayerData *opponentData = playerObj[1 - object->work[0]]->data;
    float unused = 0.0f;
    float unused2 = 0.0f;
    float unused3 = 0.0f;
    s32 unused4 = 0;
    s16 var_r29 = -1;
    s16 var_r26 = -1;
    s16 var_r22 = -1;
    BOOL aPressedF = (playerData->padIdx == PAD_IDX_COM) ? 0 : ((HuPadBtnDown[playerData->padIdx] & PAD_BUTTON_A) > 0);
    BOOL rPressedF = (playerData->padIdx == PAD_IDX_COM) ? 0 : ((HuPadBtnDown[playerData->padIdx] & PAD_TRIGGER_R) > 0);
    BOOL lPressedF = (playerData->padIdx == PAD_IDX_COM) ? 0 : ((HuPadBtnDown[playerData->padIdx] & PAD_TRIGGER_L) > 0);
    s32 i;

    if (playerData->padIdx == PAD_IDX_COM) {
        playerData->unk3C--;
        if (playerData->unk3C <= 0) {
            if (playerData->state == 1) {
                aPressedF = TRUE;
            }
            else {
                rPressedF = lPressedF = TRUE;
            }
            if (playerData->state >= 8 || (playerData->state >= 3 && playerData->unk18 >= 10)) {
                switch (playerData->diff) {
                    case 0:
                        playerData->unk3C = rand8() % 14 + 4 + (playerData->state != 8 ? 28 - playerData->unk18 : 0);
                        break;
                    case 1:
                        playerData->unk3C = rand8() % 9 + 4 + (playerData->state != 8 ? 28 - playerData->unk18 : 0);
                        break;
                    case 2:
                        playerData->unk3C = rand8() % 10 + 12
                            + ((playerData->state != 8 && playerData->unk18 >= 9 && playerData->unk18 <= 13) ? 13 - playerData->unk18 : 0);
                        break;
                    case 3:
                        playerData->unk3C = rand8() % 5 + 4
                            + ((playerData->state != 8 && playerData->unk18 >= 2 && playerData->unk18 <= 17) ? 17 - playerData->unk18 : 0);
                        if (opponentData->invinceTime > 0 || playerData->state == 7) {
                            // don't waste stamina
                            lPressedF = rPressedF = 0;
                        }
                        break;
                }
            }
        }
    }
    if (playerData->prevTrig == PREV_TRIG_L) {
        lPressedF = FALSE;
    }
    if (playerData->prevTrig == PREV_TRIG_R) {
        rPressedF = FALSE;
    }
    if (playerData->unk20 > 0) {
        aPressedF = FALSE;
        playerData->unk20--;
    }
    else if (aPressedF) {
        playerData->unk20 = 20;
    }
    if (playerData->unk24 > 0) {
        lPressedF = FALSE;
        playerData->unk24--;
    }
    else if (lPressedF) {
        playerData->unk24 = 6;
    }
    if (playerData->unk28 > 0) {
        rPressedF = FALSE;
        playerData->unk28--;
    }
    else if (rPressedF) {
        playerData->unk28 = 6;
    }
    if (gameState == 1008 && playerData->state >= 8 && playerData->state <= 14) {
        s32 prevStamina = playerData->stamina;
        if (lPressedF) {
            playerData->stamina -= 7;
        }
        if (rPressedF) {
            playerData->stamina -= 7;
        }
        if (prevStamina > 0 && playerData->stamina <= 0) {
            // cap at -1
            playerData->stamina = -1;
            playerData->unk4C = 1;
        }
    }
    if (lbl_1_bss_20 == 0 && gameState == 1008 && playerData->state >= 7 && playerData->state <= 14 && (lPressedF || rPressedF)) {
        playerData->prevTrig = lPressedF ? PREV_TRIG_L : rPressedF ? PREV_TRIG_R : PREV_TRIG_L;
    }
    if (playerData->group == 0) {
        playerObj[0]->trans.x -= playerData->unk48;
        playerObj[1]->trans.x -= opponentData->unk48;
    }
    switch (gameState) {
        case 1001:
            if (lbl_1_bss_60 == 0) {
                Hu3DModelAttrReset(object->model[MODEL_ID_PLAYER_PLAYER], HU3D_ATTR_DISPOFF);
            }
            if (lbl_1_bss_60 <= 30) {
                if (playerData->character == CHARACTER_BOWSER) {
                    Hu3DMotionTimeSet(object->model[MODEL_ID_PLAYER_PLAYER], 138.0f);
                }
                object->trans.y = 2400.0 * (1.0 - lbl_1_bss_60 / 30.0);
            }
            if (playerData->character != CHARACTER_BOWSER && lbl_1_bss_60 == 30) {
                var_r29 = 2;
            }
            if (lbl_1_bss_60 == 40 && playerData->character != CHARACTER_BOWSER) {
                var_r29 = 0;
            }
            if (lbl_1_bss_60 == 45 && playerData->character == CHARACTER_BOWSER) {
                var_r29 = 0;
                Hu3DMotionShiftSet(object->model[MODEL_ID_PLAYER_PLAYER], object->motion[var_r29], lbl_1_data_184[var_r29], 35.0f, HU3D_MOTATTR_LOOP);
                playerData->unk40 = var_r29;
            }
            if (lbl_1_bss_60 == 30) {
                lbl_1_data_28C.unk04 += 50;
            }
            if (lbl_1_bss_60 == 30) {
                HuAudFXPlay(MSM_SE_PLAYER_DROP);
            }
            break;
        case 1005:
            if (lbl_1_bss_60 == 0) {
                var_r29 = 3;
            }
            if (lbl_1_bss_60 == (s32)((21.0f / 18) * REFRESH_RATE)) {
                var_r29 = 4;
            }
            break;
        case 1006:
            if (lbl_1_bss_60 == 5) {
                var_r29 = 5;
            }
            break;
        case 1010:
            if (lbl_1_bss_44 == playerData->group && lbl_1_bss_60 >= 15) {
                if (lbl_1_bss_60 == 15) {
                    playerData->state = 0;
                    playerData->unk18 = 0;
                    if (playerData->character == CHARACTER_BOWSER) {
                        HuAudFXPlay(MSM_SE_BOWSER_LAUGH);
                    }
                }
                var_r29 = 10;
                if (object->rot.y > 180.0f) {
                    object->rot.y -= 360.0f;
                }
                object->rot.y *= 0.9;
            }
            if (lbl_1_bss_44 == 2 && lbl_1_bss_60 >= 15) {
                if (lbl_1_bss_60 == 15) {
                    playerData->state = 0;
                    playerData->unk18 = 0;
                }
                var_r29 = 11;
                if (object->rot.y > 180.0f) {
                    object->rot.y -= 360.0f;
                }
                object->rot.y *= 0.9;
            }
            break;
    }
    playerData->unk18 += (playerData->unk18 < 0x10000);
    if (playerData->state == 3 || playerData->state == 5) {
        if (playerData->unk18 == 1 && lbl_1_data_2B0 != -1) {
            HuWinExCleanup(lbl_1_data_2B0);
            lbl_1_data_2B0 = -1;
        }
        if ((playerData->state == 3 && playerData->unk18 == 23) || (playerData->state == 5 && playerData->unk18 == 15)) {
            float spFC[2];
            HuWinMesMaxSizeGet(1, spFC, MAKE_MESSID(48, 35));
            if (lbl_1_data_2B0 == -1) {
                lbl_1_data_2B0 = HuWinCreate(-10000.0f, 400.0f, spFC[0], spFC[1], 1);
            }
            HuWinBGTPLvlSet(lbl_1_data_2B0, 0.0f);
            HuWinMesSpeedSet(lbl_1_data_2B0, 0);
            HuWinMesSet(lbl_1_data_2B0, MAKE_MESSID(48, 35));
        }
    }
    switch (playerData->state) {
        case 0:
            if (gameState == 1008) {
                playerData->state = 1;
                playerData->unk18 = 0;
            }
            break;
        case 1:
            if (playerData->unk18 == 1 && playerData->padIdx == PAD_IDX_COM) {
                switch (playerData->diff) {
                    case 0:
                        playerData->unk3C = rand8() % 5 + 15;
                        break;
                    case 1:
                        playerData->unk3C = rand8() % 5 + 12;
                        break;
                    case 2:
                        playerData->unk3C = rand8() % 5 + 10;
                        break;
                    case 3:
                        playerData->unk3C = rand8() % 4 + 9;
                        break;
                }
            }
            // initial advance
            if (aPressedF) {
                playerData->state = PLAYER_STATE_INITIAL_ADVANCE;
                playerData->unk18 = 0;
                var_r29 = 6;
                object->trans.x += (playerData->group == 0) ? ((rand8() % 2) * 2 - 1) : 0;
            }
            break;
        case PLAYER_STATE_INITIAL_ADVANCE:
            object->trans.x += 8.695652f * (playerData->group == 0 ? 1 : -1);
            break;
        case 3:
            object->trans.x += 4.347826f * (playerData->group == 0 ? 1 : -1);
            if (playerData->unk18 >= 23) {
                playerData->state = 8;
                playerData->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 4:
            if (playerData->unk18 == 1) {
                var_r29 = 7;
            }
            object->trans.x += -4.347826f * (playerData->group == 0 ? 1 : -1);
            if (playerData->unk18 >= 23) {
                playerData->state = 8;
                playerData->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 5:
            object->trans.x += 8.695652f * (playerData->group == 0 ? 1 : -1);
            if (playerData->unk18 >= 15) {
                playerData->state = 8;
                playerData->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 6:
            if (playerData->unk18 == 1) {
                var_r29 = 8;
            }
            object->trans.x += -8.695652f * (playerData->group == 0 ? 1 : -1);
            if (playerData->unk18 >= 7) {
                playerData->state = 8;
                playerData->unk18 = 0;
                var_r26 = 7;
                var_r29 = 4;
            }
            if (playerData->unk18 >= 15) {
                playerData->state = 8;
                playerData->unk18 = 0;
            }
            break;
        case 8:
            if (playerData->stamina == 0) {
                var_r26 = 0;
                playerData->state = 7;
                playerData->unk18 = 1;
                playerData->unk34 = 0;
            }
            else {
                if (!lPressedF && !rPressedF) {
                    break;
                }
                playerData->state = 9;
                playerData->unk18 = 0;
                var_r26 = 3;
                var_r22 = (playerData->prevTrig == PREV_TRIG_L ? 0 : 11) + 5;
                var_r29 = 6;
                if (lbl_1_bss_20 == 1) {
                    playerData->prevTrig = lPressedF ? PREV_TRIG_L : rPressedF ? PREV_TRIG_R : PREV_TRIG_L;
                }
                break;
            }
            /* fallthrough */
        case 7:
            if (playerData->unk18 == 1) {
                s32 noStaminaSeIdTbl[] = { 0x12A, 0x16A, 0x1AA, 0x1EA, 0x22A, 0x26A, 0x2AA, 0x2EA, 0x03B };
                HuAudFXPlay(noStaminaSeIdTbl[playerData->character == CHARACTER_BOWSER ? 8 : playerData->character]);
                var_r29 = 9;
                playerData->unk4C = 0;
            }
            if (playerData->stamina > 0) {
                playerData->state = 8;
                playerData->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 9:
            object->trans.x += 8.695652f * (playerData->group == 0 ? 1 : -1);
            if (playerData->unk18 >= 23) {
                playerData->state = 8;
                playerData->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 12:
            if (playerData->unk18 == 7) {
                var_r26 = 0;
                var_r22 = 7;
                var_r29 = 7;
            }
            if (playerData->unk18 == 15) {
                var_r26 = 5;
                var_r29 = 4;
            }
            if (playerData->unk18 >= 20) {
                playerData->state = 8;
                playerData->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 10:
            object->trans.x += 4.347826f * (playerData->group == 0 ? 1 : -1);
            if (playerData->unk18 >= 23) {
                playerData->state = 8;
                playerData->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 11:
            object->trans.x += -4.347826f * (playerData->group == 0 ? 1 : -1);
            if (playerData->unk18 == 1) {
                var_r29 = 7;
            }
            if (playerData->unk18 >= 23) {
                playerData->state = 8;
                playerData->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 13:
            object->trans.x += 8.695652f * (playerData->group == 0 ? 1 : -1);
            if (playerData->unk18 >= 23) {
                playerData->state = 8;
                playerData->unk18 = 0;
                var_r29 = 4;
            }
            break;
        case 14:
            object->trans.x += -8.695652f * (playerData->group == 0 ? 1 : -1);
            if (playerData->unk18 == 1) {
                var_r29 = 8;
            }
            if (playerData->unk18 == 11) {
                var_r26 = 11;
                var_r29 = 4;
            }
            if (playerData->unk18 >= 23) {
                playerData->state = 8;
                playerData->unk18 = 0;
            }
            if (playerData->unk34 < 8) {
                playerData->unk34 = 8;
            }
            break;
        case 15:
            if (playerData->unk18 == 1 && playerData->invinceTime > 4) {
                playerData->invinceTime = 4;
            }
            if (playerData->unk18 == 1 && lbl_1_data_2B0 != -1) {
                HuWinExCleanup(lbl_1_data_2B0);
                lbl_1_data_2B0 = -1;
            }
            if (playerData->unk18 == 7) {
                var_r29 = 4;
                var_r26 = 20;
            }
            if (playerData->unk18 == REFRESH_RATE) {
                lbl_1_bss_44 = playerData->group;
                playerData->invinceTime = 0;
            }
            break;
        case PLAYER_STATE_FALLING:
            // make the player fall down in the correct direction
            object->trans.x += -39.130432f * (playerData->group == 0 ? 1 : -1);
            object->trans.y += 39.130432f;
            if (playerData->unk18 == 1) {
                s32 fallSeIdTbl[] = { 0x123, 0x163, 0x1A3, 0x1E3, 0x223, 0x263, 0x2A3, 0x2E3, 0x03C };
                HuAudFXPlay(fallSeIdTbl[playerData->character == CHARACTER_BOWSER ? 8 : playerData->character]);
                var_r29 = 8;
                var_r26 = 0;
                var_r22 = 6;
            }
            object->rot.z = (playerData->group == 0) ? -20 : 20;
            break;
        case 17:
            if (playerData->unk18 == 1 && playerData->invinceTime > 4) {
                playerData->invinceTime = 4;
            }
            if (playerData->unk18 == 1 && lbl_1_data_2B0 != -1) {
                HuWinExCleanup(lbl_1_data_2B0);
                lbl_1_data_2B0 = -1;
            }
            if (playerData->unk18 == 7) {
                var_r29 = 0;
                var_r26 = 10;
            }
            if (playerData->unk18 >= 7 && playerData->unk18 < 17) {
                object->trans.x += (playerData->group == 0 ? -1 : 1) * 2;
            }
            if (playerData->unk18 == REFRESH_RATE) {
                lbl_1_bss_44 = 2;
                playerData->invinceTime = 0;
            }
            break;
    }
    switch (playerData->state) {
        case 12:
            if (playerData->group == 0) {
                break;
            }
            /* fallthrough */
        case 3:
        case 5:
        case 10:
        case 13: {
            Vec sp104;
            s32 temp_r21;
            char *var_r18;

            s32 temp_r19 = Hu3DMotionTimeGet(object->model[MODEL_ID_PLAYER_PLAYER]);
            if ((opponentData->state != 4 && opponentData->state != 6) || opponentData->unk18 != 1) {
                if ((temp_r19 + 1) % 11 != 0 || (playerData->state == 12 && temp_r19 + 1 > 11)) {
                    break;
                }
            }
            temp_r21 = ((temp_r19 + 1) / 11 - 1) % 2;
            {
                char sp1D8[][50] = { "g000mN-itemhook_R", "g000mN-itemhook_L" };

                if (playerData->character != CHARACTER_BOWSER) {
                    var_r18 = CharModelHookNameGet(playerData->character, 1, (temp_r21 % 2 == 0) ? 0 : 1);
                }
                else {
                    var_r18 = (temp_r21 % 2 == 0) ? sp1D8[0] : sp1D8[1];
                }
            }
            Hu3DModelObjPosGet(object->model[MODEL_ID_PLAYER_PLAYER], var_r18, &sp104);
            Hu3DModelPosSet(gameObj->model[temp_r21 + 7], sp104.x + (playerData->group == 0 ? 1 : -1) * 50, sp104.y, 75.0f + sp104.z);
            Hu3DMotionTimeSet(gameObj->model[temp_r21 + 7], 2.0f);
            Hu3DModelAttrReset(gameObj->model[temp_r21 + 7], 1);
            if (lbl_1_bss_78[playerData->character == CHARACTER_BOWSER ? 1 : 0].unk00 < 3) {
                lbl_1_bss_78[playerData->character == CHARACTER_BOWSER ? 1 : 0]
                    .unk04[lbl_1_bss_78[playerData->character == CHARACTER_BOWSER ? 1 : 0].unk00]
                    = 0.0f;
                lbl_1_bss_78[playerData->character == CHARACTER_BOWSER ? 1 : 0].unk00++;
            }
            // bounds check
            if (fabs(playerObj[1 - playerData->group]->trans.x) >= 800.0 && (opponentData->state == 11 || opponentData->state == 14)) {
                playerData->state = 15;
                opponentData->state = PLAYER_STATE_FALLING;
                playerData->unk18 = opponentData->unk18 = 0;
                if (lbl_1_bss_78[4].unk00 < 3) {
                    lbl_1_bss_78[4].unk04[lbl_1_bss_78[4].unk00] = 0.0f;
                    lbl_1_bss_78[4].unk00++;
                }
                if (backgroundMusNo != -1) {
                    HuAudSeqFadeOut(backgroundMusNo, 100);
                    backgroundMusNo = -1;
                }
            }
        } break;
    }
    playerData->unk34++;
    if (playerData->state != PLAYER_STATE_FALLING && playerData->state != 15 && playerData->state != 17 && gameState == 1008
        && playerData->unk34 >= 30 && (playerData->unk34 - 30) % 30 == 0) {
        // regen stamina
        playerData->stamina += (playerData->unk4C == 0 || playerData->state == 7) ? 10 : 0;
    }
    // apply invincibility to stamina and cap it
    playerData->stamina = (playerData->invinceTime > 0 || playerData->stamina >= 100) ? 100 : (playerData->stamina < 0) ? 0 : playerData->stamina;
    for (i = 0; i < 5; i++) {
        float scale = (playerData->stamina >= i * 20 + 20) ? 1.0 : (playerData->stamina <= i * 20) ? 0.0 : (playerData->stamina - i * 20) / 20.0;
        espScaleSet(sprIdTbl[i + (playerData->group == 0 ? 2 : 10)], scale, scale);
        if (playerData->invinceTime > 0) {
            // stamina bar mushroom start positions/offsets
            s32 posXTbl[] = { 106, 469 };
            s32 posYTbl[] = { 78, 78 };
            s32 ofsXTbl[] = { 0, 0, -33, -9, 15, 39, 63, -68, 0, 0, -33, -9, 15, 39, 63, -68 }; // second half is unused
            s32 ofsYTbl[] = { 0, 0, -1, -1, -1, -1, -1, -2, 0, 0, -1, -1, -1, -1, -1, -2 };

            // make the mushrooms in the stamina bar glow
            espPosSet(sprIdTbl[i + 18], posXTbl[playerData->group] + ofsXTbl[i + 2], posYTbl[playerData->group] + ofsYTbl[i + 2]);
            espScaleSet(sprIdTbl[i + 18], (playerData->invinceTime % 4 == 0) ? 1.1 : 1.0, (playerData->invinceTime % 4 == 0) ? 1.1 : 1.0);
            espTPLvlSet(sprIdTbl[i + 18], (playerData->invinceTime % 4 < 2) ? 1.0 : (var_r22 % 4 == 2) ? 0.5 : 0.0);
            espDispOn(sprIdTbl[i + 18]);
        }
        else if (opponentData->invinceTime == 0) {
            espDispOff(sprIdTbl[i + 18]);
        }
    }
    if (playerData->invinceTime > 0) {
        s32 sp20 = (playerData->character != CHARACTER_BOWSER) ? playerData->character : 8;
        // make the player shine
        Hu3DModelPosSet(gameObj->model[MODEL_ID_GAME_INVINCE_SHINING],
            object->trans.x + sparkDataTbl[sp20].xOffset * (playerData->group == 0 ? 1 : -1), object->trans.y + sparkDataTbl[sp20].yOffset,
            150.0f + object->trans.z);
        Hu3DModelScaleSet(gameObj->model[MODEL_ID_GAME_INVINCE_SHINING], 0.75 * sparkDataTbl[sp20].scale, 0.75 * sparkDataTbl[sp20].scale,
            0.75 * sparkDataTbl[sp20].scale);
        Hu3DModelAttrReset(gameObj->model[MODEL_ID_GAME_INVINCE_SHINING], 1);
        Hu3DModelAttrSet(gameObj->model[MODEL_ID_GAME_INVINCE_SHINING], HU3D_ATTR_ZCMP_OFF);
        // add sparks
        Hu3DModelPosSet(gameObj->model[MODEL_ID_GAME_INVINCE_SPARKS],
            object->trans.x + sparkDataTbl[sp20].xOffset * (playerData->group == 0 ? 1 : -1), object->trans.y + sparkDataTbl[sp20].yOffset,
            150.0f + object->trans.z);
        Hu3DModelScaleSet(gameObj->model[MODEL_ID_GAME_INVINCE_SPARKS], 0.75 * sparkDataTbl[sp20].scale, 0.75 * sparkDataTbl[sp20].scale,
            0.75 * sparkDataTbl[sp20].scale);
        Hu3DModelAttrReset(gameObj->model[MODEL_ID_GAME_INVINCE_SPARKS], 1);
        Hu3DModelAttrSet(gameObj->model[MODEL_ID_GAME_INVINCE_SPARKS], HU3D_ATTR_ZCMP_OFF);
        playerData->invinceTime--;
        if (playerData->invinceTime == 0) {
            HuAudFXStop(invincibilitySeNo);
        }
    }
    else if (opponentData->invinceTime == 0) {
        Hu3DModelAttrSet(gameObj->model[MODEL_ID_GAME_INVINCE_SHINING], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(gameObj->model[MODEL_ID_GAME_INVINCE_SPARKS], HU3D_ATTR_DISPOFF);
    }
    if (playerData->unk44 >= 0) {
        var_r29 = playerData->unk44;
    }
    if (var_r29 >= 0 && var_r29 != playerData->unk40) {
        if (var_r26 == 0) {
            Hu3DMotionSet(object->model[MODEL_ID_PLAYER_PLAYER], object->motion[var_r29]);
            Hu3DMotionTimeSet(object->model[MODEL_ID_PLAYER_PLAYER], (var_r22 == -1) ? 0 : var_r22);
        }
        else {
            Hu3DMotionShiftSet(object->model[MODEL_ID_PLAYER_PLAYER], object->motion[var_r29], (var_r22 != -1) ? var_r22 : lbl_1_data_184[var_r29],
                (var_r26 != -1) ? var_r26 : lbl_1_data_154[var_r29], lbl_1_data_148[var_r29] ? HU3D_MOTATTR_NONE : HU3D_MOTATTR_LOOP);
        }
        playerData->unk40 = var_r29;
    }
    if (playerData->group == 1) {
        ModelData *playerModel = &Hu3DData[object->model[MODEL_ID_PLAYER_PLAYER]];
    }
}

s32 lbl_1_data_33C = -1;
float lbl_1_data_340 = 3500.0f;
float lbl_1_data_344 = 100.0f;
float lbl_1_data_348 = -59.0f;

static void M457GameExec(omObjData *object)
{
    PlayerData *sp158[2];
    omObjData *sp150[2];
    PlayerData *sp148[2];
    s32 sp140[2];
    omObjData *playerObjLocal[2];
    PlayerData *playerData[2];
    ModelData *temp_r24;
    ModelData *temp_r27;
    ModelData *mushroomModel;
    ModelData *temp_r29;
    float spAC;
    float spA8;
    float spA4;
    float temp_f20;
    float var_f19;
    float temp_f24;
    float temp_f23;
    float temp_f22;
    float var_f21;
    float temp_f27;
    float temp_f26;
    float temp_f25;
    float temp_f28;
    float temp_f29;
    float var_f31;
    s32 invinciblePlayerId;
    s32 var_r26;
    s32 var_r25;
    s32 var_r22;
    s32 var_r21;
    s32 var_r20;
    s32 var_r19;
    s32 i;

    for (i = 0; i < 2; i++) {
        sp158[i] = playerObj[i]->data;
    }
    lbl_1_bss_4++;
    switch (gameState) {
        case 1003:
            temp_f27 = 1800.0 * (1.0 - lbl_1_bss_60 / 30.0);
            temp_f27 = (temp_f27 < 0.0f) ? 0.0f : temp_f27;
            Hu3DModelPosSet(gameObj->model[MODEL_ID_GAME_KOOPA_KID], 0.0f, temp_f27, 0.0f);
            Hu3DModelAttrReset(gameObj->model[MODEL_ID_GAME_KOOPA_KID], HU3D_ATTR_DISPOFF);
            if (lbl_1_bss_60 == 31) {
                HuAudFXPlay(MSM_SE_KOOPA_KID_DROP);
            }
            if (lbl_1_bss_60 >= 31 && lbl_1_bss_60 <= 38) {
                temp_f24 = 1.0 - (lbl_1_bss_60 - 31) / 7.0;
                Hu3DModelRotSet(object->model[MODEL_ID_GAME_KOOPA_KID], 25.0 * (temp_f24 * 0.5 + temp_f24 * temp_f24 * 0.5), 0.0f, 0.0f);
            }
            break;
        case 1002:
            if (lbl_1_bss_60 == 0) {
                lbl_1_bss_3C = 0;
            }
            if (lbl_1_bss_60 == (REFRESH_RATE/15)*5) {
                espAttrReset(sprIdTbl[16], HUSPR_ATTR_DISPOFF);
            }
            if ((lbl_1_bss_60 >= (REFRESH_RATE/15)*5 && lbl_1_bss_60 <= REFRESH_RATE - 10)
                || (lbl_1_bss_60 >= 3 * REFRESH_RATE && lbl_1_bss_60 <= ((7*REFRESH_RATE)/2))) {
                spAC = (lbl_1_bss_60 <= 120) ? (lbl_1_bss_60 - ((REFRESH_RATE/15)*5)) / (0.5 * REFRESH_RATE)
                                             : (1.0 - (lbl_1_bss_60 - 3 * REFRESH_RATE) / (0.5 * REFRESH_RATE));
                espTPLvlSet(sprIdTbl[16], spAC);
            }
            if (lbl_1_bss_60 == (s32)(3.5 * REFRESH_RATE)) {
                espAttrSet(sprIdTbl[16], HUSPR_ATTR_DISPOFF);
            }
            break;
        case 1006:
            if (lbl_1_bss_60 == 0) {
                Hu3DMotionSet(object->model[MODEL_ID_GAME_KOOPA_KID], object->motion[2]);
                Hu3DModelAttrReset(object->model[MODEL_ID_GAME_KOOPA_KID], HU3D_MOTATTR_LOOP);
            }
            if (lbl_1_bss_60 == 15) {
                Hu3DModelAttrSet(object->model[MODEL_ID_GAME_KOOPA_KID], HU3D_MOTATTR_PAUSE);
            }
            break;
        case 1008:
            if (lbl_1_bss_60 == 1) {
                Hu3DModelAttrReset(object->model[MODEL_ID_GAME_KOOPA_KID], HU3D_MOTATTR_PAUSE);
                for (i = 0; i < 16; i++) {
                    espDispOn(sprIdTbl[i]);
                }
            }
#if VERSION_NTSC
            if (lbl_1_bss_60 <= 25) {
                temp_f28 = lbl_1_bss_60 / 25.0;
                temp_f26 = 1.0f - (1.0f - temp_f28) * (1.0f - temp_f28) * (1.0f - temp_f28);
                temp_f26 = 0.25 + 1.375 * temp_f26;
                temp_f23 = 1.0f - (1.0f - temp_f28) * (1.0f - temp_f28);
                temp_f23 = 2.0f * (1.0f - temp_f28);
                espAttrReset(sprIdTbl[17], HU3D_ATTR_SHADOW);
#if VERSION_ENG
                espScaleSet(sprIdTbl[17], 0.85 * temp_f26, 0.85 * temp_f26);
#else
                espScaleSet(sprIdTbl[17], temp_f26, temp_f26);
#endif
                espTPLvlSet(sprIdTbl[17], (temp_f23 > 1.0f) ? 1.0f : temp_f23);
            }
            else {
                espAttrSet(sprIdTbl[17], HUSPR_ATTR_DISPOFF);
            }
#endif
            for (i = 0; i < 2; i++) {
                sp150[i] = playerObj[i];
                sp148[i] = playerObj[i]->data;
            }
            for (i = 0; i < 2; i++) {
                sp140[i] = (sp148[1 - i]->invinceTime > 0) ? 2
                    : (sp148[i]->state == 8)               ? 2
                    : (sp148[i]->state == 1)               ? 1
                    : (sp148[i]->state == 9)               ? (sp148[i]->unk18 >= 0 ? 3 : 2)
                    : (sp148[i]->state == 2)               ? 4
                    : (sp148[i]->state == 7)               ? 0
                                                           : -1;
            }
            if (sp140[0] >= 0 && sp140[1] >= 0 && fabs(sp150[0]->trans.x - sp150[1]->trans.x) < 300.0) {
                sp150[0]->trans.x = (sp148[0]->invinceTime > 0) ? sp150[0]->trans.x
                    : (sp148[1]->invinceTime > 0)               ? (sp150[1]->trans.x - 300.0f)
                                                                : ((sp150[0]->trans.x + sp150[1]->trans.x) / 2.0 - 150.0);
                sp150[0]->trans.x = (sp150[0]->trans.x >= 650.0) ? 650.0 : (sp150[0]->trans.x <= -950.0) ? -950.0 : sp150[0]->trans.x;
                sp150[1]->trans.x = sp150[0]->trans.x + 300.0f;
                if (sp140[0] >= 3 || sp140[1] >= 3) {
                    var_r26 = (sp140[0] >= 3) ? 0 : 1;
                    var_r25 = 1 - var_r26;
                    switch (sp140[var_r25]) {
                        case 4:
                            if (sp150[var_r26]->trans.x * (var_r26 == 0 ? 1 : -1) < sp150[var_r25]->trans.x * (var_r25 == 0 ? 1 : -1)) {
                                var_r26 = 1 - var_r26;
                                var_r25 = 1 - var_r25;
                            }
                            sp148[var_r26]->state = 3;
                            sp148[var_r25]->state = 4;
                            break;
                        case 1:
                            sp148[var_r26]->state = 5;
                            sp148[var_r25]->state = 6;
                            break;
                        case 3:
                            sp148[var_r26]->state = 12;
                            sp148[var_r25]->state = 12;
                            break;
                        case 2:
                            sp148[var_r26]->state = 10;
                            sp148[var_r25]->state = 11;
                            break;
                        case 0:
                            sp148[var_r26]->state = 13;
                            sp148[var_r25]->state = 14;
                            break;
                    }
                    sp148[0]->unk18 = sp148[1]->unk18 = 0;
                }
            }
            /* fallthrough */
        case 1009:
            if (gameState != 1008 && lbl_1_bss_40 == 0) {
                break;
            }
            for (i = 0; i < 2; i++) {
                playerObjLocal[i] = playerObj[i];
                playerData[i] = playerObj[i]->data;
            }
            switch (lbl_1_bss_18) {
                case 0:
                    if (lbl_1_bss_40 == 0 && lbl_1_bss_18 == 0 && (playerObjLocal[0]->trans.x > -150.0f || playerObjLocal[1]->trans.x < 150.0f)) {
                        lbl_1_bss_18 = (-playerObjLocal[0]->trans.x < playerObjLocal[1]->trans.x ? 1 : 2);
                        Hu3DModelPosSet(gameObj->model[9], 0.0f, 100.0f, 0.0f);
                        Hu3DMotionTimeSet(gameObj->model[9], 0.0f);
                        Hu3DModelAttrReset(gameObj->model[9], HU3D_ATTR_DISPOFF);
                        if (lbl_1_bss_78[4].unk00 < 3) {
                            lbl_1_bss_78[4].unk04[lbl_1_bss_78[4].unk00] = 0.0f;
                            lbl_1_bss_78[4].unk00++;
                        }
                    }
                    if (lbl_1_bss_18 == 0) {
                        break;
                    }
                    /* fallthrough */
                case 1:
                case 2:
                    temp_r27 = &Hu3DData[object->model[MODEL_ID_GAME_KOOPA_KID]];
                    temp_r27->rot.y += (lbl_1_bss_18 == 1 ? 18 : -18);
                    temp_r27->rot.z = (lbl_1_bss_18 == 1 ? -20 : 20);
                    temp_r27->pos.x += 5.130000000000001 * (lbl_1_bss_18 == 1 ? 1 : -1);
                    temp_r27->pos.y += 47.0;
                    temp_r27->pos.z += -20.0f;
                    if (temp_r27->pos.y > 1800.0f) {
                        lbl_1_bss_18 += 2;
                    }
                    break;
            }
            switch (lbl_1_bss_1C) {
                case 0:
                case 2:
                    lbl_1_data_2B8 -= (lbl_1_bss_18 >= 3 && playerData[0]->state < 16 && playerData[1]->state < 16);
                    if (lbl_1_data_2B8 != 0) {
                        break;
                    }
                    Hu3DModelAttrReset(object->model[MODEL_ID_GAME_MUSHROOM], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(object->model[MODEL_ID_GAME_MUSHROOM],
                        (lbl_1_bss_1C == 0) ? 0.0 : (2.0 * ((rand8() % 256) / 255.0 - 0.5) * 400.0), 1500.0f, 0.0f);
                    lbl_1_bss_1C = 1;
                    /* fallthrough */
                case 1:
                    mushroomModel = &Hu3DData[object->model[MODEL_ID_GAME_MUSHROOM]];
                    // descend mushroom
                    mushroomModel->pos.y -= 10.0f;
                    if (mushroomModel->pos.y <= 225.0f) {
                        float playerDistsToMushroom[] = { 100000000.0f, 100000000.0f };
                        // make sure it doesn't fall through the ring
                        mushroomModel->pos.y = (mushroomModel->pos.y < 100.0f) ? 100.0f : mushroomModel->pos.y;
                        for (i = 0; i < 2; i++) {
                            if (fabs(playerObjLocal[i]->trans.x + (i == 0 ? 40 : -40) - mushroomModel->pos.x) < 180.0) {
                                playerDistsToMushroom[i] = fabs(playerObjLocal[i]->trans.x + (i == 0 ? 40 : -40) - mushroomModel->pos.x);
                            }
                        }
                        if (playerDistsToMushroom[0] != playerDistsToMushroom[1]) {
                            invinciblePlayerId = (playerDistsToMushroom[0] < playerDistsToMushroom[1]) ? 0 : 1;
                            Hu3DModelAttrSet(object->model[MODEL_ID_GAME_MUSHROOM], HU3D_ATTR_DISPOFF);
                            lbl_1_bss_1C = 2;
                            lbl_1_data_2B8 = 10 * REFRESH_RATE;
                            playerData[invinciblePlayerId]->invinceTime = 5 * REFRESH_RATE;
                            playerData[invinciblePlayerId]->unk4C = 0;
                            if (lbl_1_bss_78[3].unk00 < 3) {
                                lbl_1_bss_78[3].unk04[lbl_1_bss_78[3].unk00] = 0.0f;
                                lbl_1_bss_78[3].unk00++;
                            }
                            invincibilitySeNo = HuAudFXPlay(MSM_SE_INVINCIBILITY);
                        }
                    }
                    if (playerData[0]->state >= 16 || playerData[1]->state >= 16 || lbl_1_bss_40 != 0) {
                        lbl_1_bss_1C = 3;
                        lbl_1_data_2B8 = 0;
                    }
                    if (lbl_1_bss_1C == 1) {
                        break;
                    }
                    /* fallthrough */
                case 3:
                    lbl_1_data_2B8++;
                    if (lbl_1_data_2B8 < REFRESH_RATE && lbl_1_data_2B8 % 2 == 0) {
                        Hu3DModelAttrReset(object->model[MODEL_ID_GAME_MUSHROOM], HU3D_ATTR_DISPOFF);
                    }
                    else {
                        Hu3DModelAttrSet(object->model[MODEL_ID_GAME_MUSHROOM], HU3D_ATTR_DISPOFF);
                    }
                    break;
            }
            break;
    }
    switch (gameState) {
        case 1009:
            if (lbl_1_bss_40 == 0) {
                if (lbl_1_bss_60 <= 30) {
                    Hu3DModelPosSet(gameObj->model[MODEL_ID_GAME_KOOPA_KID], 0.0f, (30 - lbl_1_bss_60) * 50 * 0.94, 0.0f);
                    Hu3DModelRotSet(gameObj->model[MODEL_ID_GAME_KOOPA_KID], 0.0f, 0.0f, lbl_1_bss_18 == 3 ? -20 : 20);
                    Hu3DModelAttrReset(gameObj->model[MODEL_ID_GAME_KOOPA_KID], HU3D_ATTR_DISPOFF);
                }
                if (lbl_1_bss_60 == 30) {
                    Hu3DMotionSet(object->model[MODEL_ID_GAME_KOOPA_KID], object->motion[0]);
                    Hu3DModelAttrReset(object->model[MODEL_ID_GAME_KOOPA_KID], HU3D_MOTATTR_LOOP);
                }
                if (lbl_1_bss_60 == 30) {
                    HuAudFXPlay(MSM_SE_KOOPA_KID_DROP);
                }
                if (lbl_1_bss_60 >= 30 && lbl_1_bss_60 <= 37) {
                    temp_f22 = 1.0 - (lbl_1_bss_60 - 30) / 7.0;
                    Hu3DModelRotSet(object->model[MODEL_ID_GAME_KOOPA_KID], 25.0 * (temp_f22 * 0.5 + temp_f22 * temp_f22 * 0.5), 0.0f, 0.0f);
                }
            }
            else if (lbl_1_bss_18 == 0) {
                Hu3DMotionSet(gameObj->model[MODEL_ID_GAME_KOOPA_KID], object->motion[0]);
                Hu3DModelAttrReset(gameObj->model[MODEL_ID_GAME_KOOPA_KID], HU3D_MOTATTR_LOOP);
            }
            break;
        case 1010:
            if (lbl_1_bss_40 == 0) {
                if (lbl_1_bss_60 == 1) {
                    Hu3DMotionSet(object->model[MODEL_ID_GAME_KOOPA_KID], object->motion[3]);
                    Hu3DModelAttrReset(object->model[MODEL_ID_GAME_KOOPA_KID], HU3D_MOTATTR_LOOP);
                }
                temp_r24 = &Hu3DData[object->model[MODEL_ID_GAME_KOOPA_KID]];
                temp_f20 = (playerObj[lbl_1_bss_44]->trans.x < 0.0f) ? -90 : 90;
                temp_r24->rot.y = temp_f20 + 0.8 * (temp_r24->rot.y - temp_f20);
            }
            break;
    }
    var_r22 = lbl_1_data_33C;
    {
        float sp160[][6] = { { 3500.0f, 0.0f, 100.0f, 0.0f, -59.0f, 0.0f }, { 3200.0f, 0.0f, 100.0f, 0.0f, -30.0f, 0.0f },
            { 2100.0f, 0.0f, 200.0f, 0.0f, -30.0f, 0.0f }, { 2000.0f, 0.0f, 200.0f, 0.0f, -30.0f, 0.0f },
            { 800.0f, 0.0f, 200.0f, 0.0f, -89.0f, 0.0f }, { 1800.0f, 0.0f, 200.0f, 0.0f, -30.0f, 0.0f } };

        if (lbl_1_bss_44 != -1 && lbl_1_bss_40 == 0) {
            sp160[2][1] = playerObj[lbl_1_bss_44]->trans.x;
        }
        if (lbl_1_data_33C == -1) {
            lbl_1_data_33C = 0;
            lbl_1_bss_24 = 1;
            lbl_1_bss_28 = 1.0f;
        }
        if (lbl_1_data_33C == 0) {
            lbl_1_data_33C = 1;
            lbl_1_bss_24 = 1;
            lbl_1_bss_28 = 0.5f;
        }
        if (gameState == 1010 && lbl_1_bss_44 != 2 && lbl_1_bss_60 >= 15 && lbl_1_data_33C == 1) {
            lbl_1_data_33C = 2;
            lbl_1_bss_24 = 0;
            lbl_1_bss_28 = 0.0f;
        }
        if (var_r22 != lbl_1_data_33C && var_r22 != -1) {
            lbl_1_data_340 = CZoom;
            lbl_1_data_344 = Center.y;
            lbl_1_bss_30 = Center.z;
            lbl_1_data_348 = CRot.x;
            lbl_1_bss_34 = CRot.y;
        }
        if (lbl_1_bss_28 <= 1.0f) {
            if (lbl_1_bss_24 == 0) {
                lbl_1_bss_28 = 1.0 - 0.95 * (1.0f - lbl_1_bss_28);
                var_f31 = lbl_1_bss_28;
            }
            else {
                lbl_1_bss_28 += 0.008333333333333333;
                lbl_1_bss_28 = (lbl_1_bss_28 > 1.0f) ? 1.0f : lbl_1_bss_28;
                var_f31 = 0.5 + -0.5 * cosd(180.0f * lbl_1_bss_28);
            }
            lbl_1_bss_28 = (lbl_1_bss_28 > 1.0f) ? 1.0f : lbl_1_bss_28;
            CZoom = var_f31 * sp160[lbl_1_data_33C][0] + lbl_1_data_340 * (1.0f - var_f31);
            Center.x = var_f31 * sp160[lbl_1_data_33C][1] + lbl_1_bss_2C * (1.0f - var_f31);
            Center.y = var_f31 * sp160[lbl_1_data_33C][2] + lbl_1_data_344 * (1.0f - var_f31);
            Center.z = var_f31 * sp160[lbl_1_data_33C][3] + lbl_1_bss_30 * (1.0f - var_f31);
            CRot.x = var_f31 * sp160[lbl_1_data_33C][4] + lbl_1_data_348 * (1.0f - var_f31);
            CRot.y = var_f31 * sp160[lbl_1_data_33C][5] + lbl_1_bss_34 * (1.0f - var_f31);
        }
    }
    if (gameState == 1001) {
        var_f21 = 0.0f;
        temp_f25 = 0.0f;
        if (lbl_1_data_28C.unk00 % 2 >= 0) {
            lbl_1_data_28C.unk08 = lbl_1_data_28C.unk10;
            lbl_1_data_28C.unk0C = lbl_1_data_28C.unk14;
            do {
                lbl_1_data_28C.unk10 = 2.0 * (rand8() / 255.0) - 1.0;
                lbl_1_data_28C.unk14 = 2.0 * (rand8() / 255.0) - 1.0;
                lbl_1_data_28C.unk10 = 0.0f;
                temp_f29 = (lbl_1_data_28C.unk10 - lbl_1_data_28C.unk08) * (lbl_1_data_28C.unk10 - lbl_1_data_28C.unk08)
                    + (lbl_1_data_28C.unk14 - lbl_1_data_28C.unk0C) * (lbl_1_data_28C.unk14 - lbl_1_data_28C.unk0C);
            } while (sqrtf(temp_f29) < 0.75);
        }
        var_f21 = lbl_1_data_28C.unk08;
        temp_f25 = lbl_1_data_28C.unk0C;
        var_f21 *= lbl_1_data_28C.unk04 * 2;
        temp_f25 *= lbl_1_data_28C.unk04 * 2;
        lbl_1_data_28C.unk00 = !lbl_1_data_28C.unk00;
        lbl_1_data_28C.unk04 = (lbl_1_data_28C.unk04 > 24) ? 23 : (lbl_1_data_28C.unk04 - 1 > 0) ? (lbl_1_data_28C.unk04 - 1) : 0;
        Center.x = 0.0f;
        Center.y = 100.0f + temp_f25;
    }
    if (gameState >= 1008) {
        for (i = 0; i < 2; i++) {
            temp_r29 = &Hu3DData[playerObj[i]->model[MODEL_ID_PLAYER_PLAYER]];
            var_r21 = (sp158[i]->character != CHARACTER_BOWSER) ? sp158[i]->character : 8;
            var_r20 = (temp_r29->unk_08 == playerObj[i]->motion[4]) ? 0
                : (temp_r29->unk_08 == playerObj[i]->motion[6])     ? 1
                : (temp_r29->unk_08 == playerObj[i]->motion[7])     ? 2
                                                                    : -1;
            var_r19 = (temp_r29->unk_0C == playerObj[i]->motion[4]) ? 0
                : (temp_r29->unk_0C == playerObj[i]->motion[6])     ? 1
                : (temp_r29->unk_0C == playerObj[i]->motion[7])     ? 2
                                                                    : -1;
            spA8 = (var_r20 == -1) ? 0.0f : lbl_1_data_1B4[var_r21][var_r20];
            spA4 = (var_r19 == -1) ? 0.0f : lbl_1_data_1B4[var_r21][var_r19];
            var_f19 = (temp_r29->unk_0C == -1) ? 0.0f : (temp_r29->unk_80 == 0.0f) ? 1.0f : (temp_r29->unk_7C / temp_r29->unk_80);
            sp158[i]->unk48 = (i == 0 ? 1 : -1) * (spA8 * (1.0f - var_f19) + spA4 * var_f19);
            playerObj[i]->trans.x += sp158[i]->unk48;
            Hu3DModelPosSet(playerObj[i]->model[MODEL_ID_PLAYER_PLAYER], playerObj[i]->trans.x, playerObj[i]->trans.y, playerObj[i]->trans.z);
        }
    }
}

static void WrestleMesMain(void)
{
    PlayerData *playerData[2];
    s16 unk;
    s16 window;
    s32 i;

    unk = 0;
    for (i = 0; i < 2; i++) {
        playerData[i] = playerObj[i]->data;
    }
    HuWinComKeyWait(PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, REFRESH_RATE);
    HuWinComKeyReset();
    window = HuWinExCreateStyled(36.0f, 344.0f, 504, 96, 6, 0);
    HuWinBGTPLvlSet(window, 0.8f);
    HuWinMesSpeedSet(window, 1);
    HuWinExAnimIn(window);
    HuWinDisablePlayerSet(window,
        0xF & ((playerData[0]->padIdx != PAD_IDX_COM) ? ~(1 << playerData[0]->padIdx) : 0xF)
            & ((playerData[1]->padIdx != PAD_IDX_COM) ? ~(1 << playerData[1]->padIdx) : 0xF));
    HuWinMesSet(window, MAKE_MESSID(48, 31));
    if ((playerData[0]->padIdx == PAD_IDX_COM || playerData[0]->character == CHARACTER_BOWSER)
        && (playerData[1]->padIdx == PAD_IDX_COM || playerData[1]->character == CHARACTER_BOWSER)) {
        HuWinComKeyWait(PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, VERSION_JP ? 48 : REFRESH_RATE);
        HuWinComKeyWait(PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, VERSION_JP ? 90 : REFRESH_RATE);
        HuWinComKeyWait(PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, VERSION_JP ? 72 : REFRESH_RATE);
    }
    HuWinMesWait(window);
    HuWinExAnimOut(window);
    HuWinExCleanup(window);
    m457MesEndF = 0;
    HuPrcEnd();
}

static void ShoveMesMain(void)
{
    float var_f31;
    s16 temp_r31;
    WindowData *temp_r30;
    PlayerData *spC[2];
#if VERSION_PAL
    float var_f30;
    double var_f29;
    double var_f28;
    float sp14[2];
    float spC_2[2];
    WindowData *var_r29;
#endif
    s32 var_r28;
    s16 sp8;
    s32 var_r26;
    s32 i;

    sp8 = 0;
    for (i = 0; i < 2; i++) {
        spC[i] = playerObj[i]->data;
    }
    HuWinComKeyWait(PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, REFRESH_RATE);
    HuWinComKeyReset();
#if VERSION_NTSC
    temp_r31 = HuWinCreate(215.0f, 100.0f, 130, 37, 1);
#else
    HuWinMesMaxSizeGet(1, sp14, MAKE_MESSID(48, 32));
    temp_r31 = HuWinCreate(-10000.0f, 100.0f, sp14[0], 0x25, 1);
#endif
    HuSprColorSet(winData[temp_r31].group, 0, 0xFF, 0xFF, 0xCC);
    HuWinBGTPLvlSet(temp_r31, 0.9f);
    temp_r30 = &winData[temp_r31];
#if VERSION_PAL
    var_f29 = temp_r30->pos_x;
#endif
    temp_r30->mess_color = 0;
    temp_r30->mess_shadow_color = 9;
    temp_r30->attr |= 0x80;
    for (var_r28 = 15, var_f31 = 0.0f; var_r28 != 0; var_r28--, var_f31 += 2.0f / 30) {
        HuWinScaleSet(temp_r31, 1.0f, 1.0 * (1.0f - (1.0f - var_f31) * (1.0f - var_f31)));
#if VERSION_NTSC
        HuWinPosSet(temp_r31, 215.0f, 100.0 + 37.0 * (1.0f - (1.0f - var_f31) * (1.0f - var_f31)) / -4.0);
#else
        HuWinPosSet(temp_r31, var_f29, 100.0 + 37.0 * (1.0f - (1.0f - var_f31) * (1.0f - var_f31)) / -4.0);
#endif
        HuPrcVSleep();
    }
    HuWinScaleSet(temp_r31, 1.0f, 1.0f);
    HuWinMesSet(temp_r31, MAKE_MESSID(48, 32));
    HuPrcSleep(REFRESH_RATE);
    HuWinExAnimOut(temp_r31);
    HuWinExCleanup(temp_r31);
#if VERSION_PAL
    temp_r31 = 0;
#endif
    m457MesEndF = 0;
#if VERSION_PAL
    while (gameState != 1008) {
        HuPrcVSleep();
    }
    HuWinMesMaxSizeGet(1, spC_2, MAKE_MESSID(48, 33));
    temp_r31 = HuWinCreate(-10000.0f, 100.0f, spC_2[0], spC_2[1], 1);
    HuSprColorSet(winData[temp_r31].group, 0, 0xFF, 0xFF, 0xCC);
    HuWinBGTPLvlSet(temp_r31, 0.9f);
    var_r29 = &winData[temp_r31];
    var_f28 = var_r29->pos_x;
    var_r29->mess_color = 0;
    var_r29->mess_shadow_color = 9;
    var_r29->attr |= 0x80;
    for (var_r26 = 5, var_f30 = 0.0f; var_r26 != 0; var_r26--, var_f30 += 0.2f) {
        HuWinScaleSet(temp_r31, 1.0f, (double)(1.0f - ((1.0f - var_f30) * (1.0f - var_f30))));
        HuWinPosSet(temp_r31, var_f28, 100.0 + (((double)spC_2[1] * (1.0f - ((1.0f - var_f30) * (1.0f - var_f30)))) / -4.0));
        HuPrcVSleep();
    }
    HuWinScaleSet(temp_r31, 1.0f, 1.0f);
    HuWinMesSet(temp_r31, MAKE_MESSID(48, 33));
    HuWinMesSpeedSet(temp_r31, 0);
    HuPrcSleep(0x32);
    HuWinExAnimOut(temp_r31);
    HuWinExCleanup(temp_r31);
    temp_r31 = 0;
#endif
    HuPrcEnd();
}

static void M457Main(omObjData *object)
{
    PlayerData *playerData[2];
    float spC[2];
    s32 sp8;
    s32 i;

    for (i = 0; i < 5; i++) {
        s32 shoveSeIdTbl[] = { 0x7E1, 0x7E2, 0x7E3, 0x7E4, 0x7E5 };

        if (lbl_1_bss_78[i].unk00 > 3) {
            lbl_1_bss_78[i].unk00 = 3;
        }
        if (lbl_1_bss_78[i].unk00 > 0) {
            sp8 = HuAudFXPlay(shoveSeIdTbl[i]);
            lbl_1_bss_78[i].unk00--;
        }
    }
    for (i = 0; i < 2; i++) {
        playerData[i] = playerObj[i]->data;
    }
    if (omSysExitReq != 0 && WipeStatGet() == 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        object->func = M457Exit;
    }
    switch (gameState) {
        case 1000:
            if (WipeStatGet() == 0) {
                gameState++;
                lbl_1_bss_60 = 0;
            }
            break;
        case 1001:
            lbl_1_bss_60++;
            if (lbl_1_bss_60 == 60) {
                gameState = (againstBrowserF ? 1002 : 1003);
                lbl_1_bss_60 = 0;
            }
            break;
        case 1002:
            lbl_1_bss_60++;
            if (lbl_1_bss_60 > (s32)(3.5 * REFRESH_RATE)) {
                gameState++;
                lbl_1_bss_60 = 0;
            }
            break;
        case 1003:
            lbl_1_bss_60++;
            if (lbl_1_bss_60 == 60) {
                gameState = (againstBrowserF ? 1004 : 1005);
                lbl_1_bss_60 = 0;
            }
            break;
        case 1004:
            if (lbl_1_bss_60 == 0) {
                HuPrcChildCreate(WrestleMesMain, 100, 0x2000, 0, HuPrcCurrentGet());
                m457MesEndF = 1;
                lbl_1_bss_60++;
            }
            else if (m457MesEndF == 0) {
                lbl_1_bss_60++;
                if (playerData[0]->state == 0) {
                    gameState++;
                    lbl_1_bss_60 = 0;
                }
            }
            break;
        case 1005:
            lbl_1_bss_60++;
            if (lbl_1_bss_60 == (((REFRESH_RATE*REFRESH_RATE)+79)/80)*4) {
                gameState++;
                lbl_1_bss_60 = 0;
            }
            break;
        case 1006:
            if (lbl_1_bss_60 == 0) {
                HuWinMesMaxSizeGet(1, spC, MAKE_MESSID(48, 34));
                lbl_1_data_2B0 = HuWinCreate(-10000.0f, 400.0f, spC[0], spC[1], 1);
                HuWinBGTPLvlSet(lbl_1_data_2B0, 0.0f);
                HuWinMesSpeedSet(lbl_1_data_2B0, 0);
                HuWinMesSet(lbl_1_data_2B0, MAKE_MESSID(48, 34));
                HuPrcChildCreate(ShoveMesMain, 100, 0x2000, 0, HuPrcCurrentGet());
                m457MesEndF = 1;
                lbl_1_bss_60++;
            }
            else if (m457MesEndF == 0) {
                lbl_1_bss_60++;
                if (playerData[0]->state == 0) {
                    gameState++;
                    lbl_1_bss_60 = rand8() * (REFRESH_RATE / 2) % 5 + REFRESH_RATE;
                }
            }
            else {
                lbl_1_bss_60++;
            }
            break;
        case 1007:
            lbl_1_bss_60 -= 1;
            if (lbl_1_bss_60 <= 0) {
                gameState++;
                lbl_1_bss_60 = 0;
#if VERSION_NTSC
                HuAudFXPlay(MSM_SE_BOWSER_HOWL);
#endif
            }
            break;
        case 1008:
            lbl_1_bss_60++;
            if (lbl_1_bss_44 != -1) {
                gameState = 1009;
                lbl_1_bss_60 = 0;
                break;
            }
            if (lbl_1_data_2A6 == -1 && lbl_1_bss_60 >= 270 * REFRESH_RATE && playerData[0]->state < 16 && playerData[1]->state < 16) {
                lbl_1_data_2A6 = MGSeqTimerCreate(30);
            }
            if (lbl_1_data_2A6 == -1) {
                break;
            }
            if (playerData[0]->state < 16 && playerData[1]->state < 16) {
                MGSeqParamSet(lbl_1_data_2A6, 1, (301 * REFRESH_RATE - 1 - lbl_1_bss_60) / REFRESH_RATE);
                if (lbl_1_bss_60 > 300 * REFRESH_RATE) {
                    MGSeqParamSet(lbl_1_data_2A6, 2, -1);
                    lbl_1_data_2A6 = -1;
                }
            }
            if (lbl_1_bss_60 > 300 * REFRESH_RATE && playerData[0]->state < 16 && playerData[1]->state < 16) {
                gameState = 1009;
                lbl_1_bss_60 = 0;
                lbl_1_bss_40 = 1;
                playerData[0]->state = playerData[1]->state = 17;
                playerData[0]->unk18 = playerData[1]->unk18 = 0;
                MGSeqFinishCreate();
                if (backgroundMusNo != -1) {
                    HuAudSeqFadeOut(backgroundMusNo, 100);
                    backgroundMusNo = -1;
                }
            }
            break;
        case 1009:
            if (lbl_1_bss_60 == 1 && lbl_1_data_2A6 != -1) {
                MGSeqParamSet(lbl_1_data_2A6, 2, -1);
                lbl_1_data_2A6 = -1;
            }
            lbl_1_bss_60++;
            if (lbl_1_bss_60 >= 2 * REFRESH_RATE) {
                gameState++;
                lbl_1_bss_60 = 0;
            }
            break;
        case 1010:
            lbl_1_bss_60++;
            if (lbl_1_bss_60 == 15) {
                if (lbl_1_bss_44 != 2) {
                    if (playerData[lbl_1_bss_44]->character != CHARACTER_BOWSER) {
                        HuAudSStreamPlay(1);
                    }
                    else {
                        HuAudSStreamPlay(3);
                    }
                    if (againstBrowserF) {
                        if (lbl_1_bss_44 == 0) {
                            _SetFlag(FLAG_ID_MAKE(1, 7));
                        }
                    }
                    else {
                        GWPlayerCoinWinSet(playerData[lbl_1_bss_44]->player, 10);
                    }
                }
                else if (lbl_1_bss_44 == 2) {
                    HuAudSStreamPlay(4);
                }
            }
            if (((((REFRESH_RATE*3)+2)/4)*5.0f) < lbl_1_bss_60) {
                if (windSeNo != -1) {
                    HuAudFXStop(windSeNo);
                    windSeNo = -1;
                }
                lbl_1_data_2A4 = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                object->func = M457Exit;
            }
            break;
    }
}

static void M457GameSetup(omObjData *object)
{
    s32 i;

    for (i = 0; i < 2; i++) {
        PlayerData *playerData[2];
        playerData[i] = playerObj[i]->data;
    }
    object->model[MODEL_ID_GAME_KOOPA_KID] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_BKOOPA, 14));
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_KOOPA_KID], HU3D_MOTATTR_LOOP);
    object->model[MODEL_ID_GAME_WAR_FAN] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 38));
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_WAR_FAN], HU3D_MOTATTR_LOOP);
    Hu3DModelHookSet(object->model[MODEL_ID_GAME_KOOPA_KID], "g007m0-itemhook_r", object->model[MODEL_ID_GAME_WAR_FAN]);
    Hu3DModelPosSet(object->model[MODEL_ID_GAME_KOOPA_KID], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(object->model[MODEL_ID_GAME_KOOPA_KID], 15.0f, 0.0f, 0.0f);
    object->motion[0] = Hu3DJointMotionFile(object->model[MODEL_ID_GAME_KOOPA_KID], DATA_MAKE_NUM(DATADIR_M457, 39));
    object->motion[1] = Hu3DJointMotionFile(object->model[MODEL_ID_GAME_KOOPA_KID], DATA_MAKE_NUM(DATADIR_M457, 40));
    object->motion[2] = Hu3DJointMotionFile(object->model[MODEL_ID_GAME_KOOPA_KID], DATA_MAKE_NUM(DATADIR_M457, 41));
    object->motion[3] = Hu3DJointMotionFile(object->model[MODEL_ID_GAME_KOOPA_KID], DATA_MAKE_NUM(DATADIR_M457, 42));
    Hu3DMotionSet(object->model[MODEL_ID_GAME_KOOPA_KID], object->motion[0]);
    Hu3DModelLayerSet(object->model[MODEL_ID_GAME_WAR_FAN], 2);
    Hu3DModelLayerSet(object->model[MODEL_ID_GAME_KOOPA_KID], 2);
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_KOOPA_KID], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(object->model[MODEL_ID_GAME_WAR_FAN]);
    Hu3DModelShadowSet(object->model[MODEL_ID_GAME_KOOPA_KID]);
    object->model[MODEL_ID_GAME_SKY] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 16));
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_SKY], HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(object->model[MODEL_ID_GAME_SKY], 0.1f);
    Hu3DModelLayerSet(object->model[MODEL_ID_GAME_SKY], 1);
    object->model[MODEL_ID_GAME_RING] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 17));
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_RING], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowMapSet(object->model[MODEL_ID_GAME_RING]);
    Hu3DModelLayerSet(object->model[MODEL_ID_GAME_RING], 1);
    Hu3DModelScaleSet(object->model[MODEL_ID_GAME_RING], 1.0f, 1.0f, 1.0f);
    object->model[MODEL_ID_GAME_MUSHROOM] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 21));
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_MUSHROOM], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_MUSHROOM], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(object->model[MODEL_ID_GAME_MUSHROOM], 2);
    object->model[MODEL_ID_GAME_INVINCE_SHINING] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 19));
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_INVINCE_SHINING], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_INVINCE_SHINING], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(object->model[MODEL_ID_GAME_INVINCE_SHINING], 2);
    object->model[MODEL_ID_GAME_INVINCE_SPARKS] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 20));
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_INVINCE_SPARKS], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->model[MODEL_ID_GAME_INVINCE_SPARKS], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(object->model[MODEL_ID_GAME_INVINCE_SPARKS], 4);
    for (i = 0; i < 3; i++) {
        object->model[i + 7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M457, 18));
        Hu3DModelLayerSet(object->model[i + 7], 4);
        Hu3DModelAttrSet(object->model[i + 7], HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 16; i++) {
        s32 sp10[] = { 106, 469 };
        s32 sp8[] = { 78, 78 };
        s32 sp60[] = { 0, 0, -33, -9, 15, 39, 63, -68, 0, 0, -33, -9, 15, 39, 63, -68 };
        s32 sp20[] = { 0, 0, -1, -1, -1, -1, -1, -2, 0, 0, -1, -1, -1, -1, -1, -2 };

        if (sprDataNumTbl[i] == DATA_MAKE_NUM(DATADIR_MGCONST, 0)) {
            PlayerData *player = playerObj[i == 7 ? 0 : 1]->data;
            sprIdTbl[i]
                = espEntry((player->character == CHARACTER_BOWSER) ? DATA_MAKE_NUM(DATADIR_M457, 26) : (sprDataNumTbl[i] + player->character), 0, 0);
        }
        else {
            sprIdTbl[i] = espEntry(sprDataNumTbl[i], 0, 0);
        }
        espDrawNoSet(sprIdTbl[i], 0);
        espDispOff(sprIdTbl[i]);
        espAttrSet(sprIdTbl[i], HUSPR_ATTR_NOANIM);
        espBankSet(sprIdTbl[i], 0);
        espPriSet(sprIdTbl[i], 128 - i);
        espPosSet(sprIdTbl[i], sp60[i] + sp10[i < 8 ? 0 : 1], sp20[i] + sp8[i < 8 ? 0 : 1]);
        if ((i >= 8 ? i - 8 : i) != 0) {
            (void)1; // Required to match.
        }
        else {
            espTPLvlSet(sprIdTbl[i], 0.5f);
            espColorSet(sprIdTbl[i], 0, 0, 0);
        }
    }
    for (i = 16; i < 23; i++) {
        s32 temp_r28 = i - 16;
        s32 spFC[23] = { 288, 288 };
        s32 spA0[23] = { 240, 240 };

        sprIdTbl[i] = espEntry(sprDataNumTbl[i], 0, 0);
        espDrawNoSet(sprIdTbl[i], 0);
        espAttrSet(sprIdTbl[i], HUSPR_ATTR_NOANIM | HUSPR_ATTR_DISPOFF);
        espBankSet(sprIdTbl[i], 0);
        espPriSet(sprIdTbl[i], 128 - i);
        espPosSet(sprIdTbl[i], spFC[temp_r28], spA0[temp_r28]);
        espTPLvlSet(sprIdTbl[i], 1.0f);
    }
    object->func = M457GameExec;
}

static void M457PlayerSetup(omObjData *object)
{
    s32 opponentPlayerGroup;
    PlayerData *playerData;
    PlayerData *opponentData;
    s32 i;

    playerData = object->data;
    opponentData = playerObj[1 - object->work[0]]->data;
    memset(playerData, 0, sizeof(*playerData));
    playerData->group = object->work[0];
    playerData->player = (GWPlayerCfg[0].group == playerData->group) ? 0
        : (GWPlayerCfg[1].group == playerData->group)                ? 1
        : (GWPlayerCfg[2].group == playerData->group)                ? 2
        : (GWPlayerCfg[3].group == playerData->group)                ? 3
                                                                     : 4;
    opponentPlayerGroup = (GWPlayerCfg[0].group == 1 - playerData->group) ? 0
        : (GWPlayerCfg[1].group == 1 - playerData->group)                 ? 1
        : (GWPlayerCfg[2].group == 1 - playerData->group)                 ? 2
        : (GWPlayerCfg[3].group == 1 - playerData->group)                 ? 3
                                                                          : 4;
    if (playerData->player == 4) {
        OSReport("m457:wrong player group\n");
        playerData->player = playerData->group;
    }
    if (playerData->group == 1 && againstBrowserF) {
        playerData->character = -1;
        playerData->padIdx = PAD_IDX_COM;
        playerData->player = -1;
        playerData->diff = 1;
    }
    else {
        playerData->character = GWPlayerCfg[playerData->player].character;
        playerData->padIdx = (playerData->character == CHARACTER_BOWSER || GWPlayerCfg[playerData->player].iscom)
            ? PAD_IDX_COM
            : GWPlayerCfg[playerData->player].pad_idx;
        playerData->diff = (playerData->padIdx != PAD_IDX_COM) ? 0 : GWPlayerCfg[playerData->player].diff;
    }
    playerData->state = 0;
    playerData->stamina = 100;
    playerData->unk34 = 0;
    playerData->prevTrig = -1;
    playerData->unk2C = -1;
    playerData->unk3C = 10000;
    playerData->unk40 = 1;
    playerData->unk44 = -1;
    if (playerData->character != CHARACTER_BOWSER) {
        object->model[MODEL_ID_PLAYER_PLAYER] = CharModelCreate(playerData->character, 1);
    }
    else {
        object->model[MODEL_ID_PLAYER_PLAYER] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_BKOOPA, 7));
    }
    omSetTra(object, 0.0f, playerData->group == 0 ? 0 : 300, 0.0f);
    if (playerData->character != CHARACTER_BOWSER) {
        omSetSca(object, 2.5f, 2.5f, 2.5f);
    }
    else {
        omSetSca(object, 2.0f, 2.0f, 2.0f);
    }
    for (i = 0; i < 12; i++) {
        if (playerData->character != CHARACTER_BOWSER) {
            object->motion[i] = CharModelMotionCreate(playerData->character, lbl_1_data_B8[i] + (lbl_1_data_E8[i] != 0 ? playerData->character : 0));
        }
        else if (lbl_1_data_118[i] != 0) {
            object->motion[i] = Hu3DJointMotionFile(object->model[MODEL_ID_PLAYER_PLAYER], lbl_1_data_118[i]);
        }
    }
    Hu3DMotionSet(object->model[MODEL_ID_PLAYER_PLAYER], object->motion[playerData->unk40]);
    Hu3DMotionTimeSet(object->model[MODEL_ID_PLAYER_PLAYER], 10.0f);
    Hu3DModelAttrReset(object->model[MODEL_ID_PLAYER_PLAYER], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(object->model[MODEL_ID_PLAYER_PLAYER]);
    Hu3DModelAttrSet(object->model[MODEL_ID_PLAYER_PLAYER], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(object->model[MODEL_ID_PLAYER_PLAYER], 3);
    CharModelLayerSetAll2(4);
    object->rot.y = playerData->group * 180 + 90;
    object->trans.x = (playerData->group == 0 ? -1 : 1) * 300;
    object->func = M457PlayerExec;
}

static void M457Setup(omObjData *object)
{
    gameState = 1000;
    lbl_1_bss_60 = 0;
    lbl_1_bss_54 = 0;
    lbl_1_bss_50 = 0;
    if (backgroundMusNo == -1) {
        backgroundMusNo = HuAudSeqPlay(MSM_MUS_BACKGROUND);
    }
    windSeNo = HuAudFXPlay(MSM_SE_WIND);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    object->func = M457Main;
}

void ObjectSetup(void)
{
    omObjData *object;
    s32 i;

    OSReport("******* M457 ObjectSetup *********\n");
    objman = omInitObjMan(600, 0x2000);
    omGameSysInit(objman);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    CZoom = 3200.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = -100.0f;
    CRot.x = -30.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    {
        Vec pos = { 0.0f, 0.0f, 0.0f };
        Vec destination = { 0.25f, -0.75f, -0.45f };
        GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };

        lightId = Hu3DGLightCreateV(&pos, &destination, &color);
    }
    Hu3DGLightStaticSet(lightId, 1);
    Hu3DGLightInfinitytSet(lightId);
    {
        Vec camPos;
        Vec camUp;
        Vec camTarget;

        camPos.x = 0.0f;
        camPos.y = 10000.0f;
        camPos.z = 0.0f;
        camUp.x = 0.0f;
        camUp.y = 1.0f;
        camUp.z = 0.0f;
        camTarget.x = 0.0f;
        camTarget.y = 0.0f;
        camTarget.z = 0.5f;
        Hu3DShadowCreate(12.0f, 9000.0f, 10010.0f);
        Hu3DShadowTPLvlSet(0.625f);
        Hu3DShadowPosSet(&camPos, &camUp, &camTarget);
    }
    Hu3DShadowSizeSet(224);
    lbl_1_data_2A4 = -1;
    lbl_1_bss_44 = -1;
    againstBrowserF = _CheckFlag(FLAG_ID_MAKE(1, 0)) != 0;
    HuWinInit(1);
    gameObj = omAddObjEx(objman, 101, 10, 4, 1, M457GameSetup);
    for (i = 0; i < 2; i++) {
        object = playerObj[i] = omAddObjEx(objman, 100, 1, 12, 0, M457PlayerSetup);
        object->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(PlayerData), MEMORY_DEFAULT_NUM);
        object->work[0] = i;
    }
    omViewObj = omAddObjEx(objman, 0x7FDA, 0, 0, -1, omOutView);
    mainObj = omAddObjEx(objman, 103, 0, 0, -1, M457Setup);
}

static void M457Exit(omObjData *object)
{
    PlayerData *playerData;
    s32 i;

    if (WipeStatGet() == 0) {
        for (i = 0; i < 2; i++) {
            playerData = playerObj[i]->data;
        }
        if (lbl_1_data_2A4 >= 0) {
            MGSeqKill(lbl_1_data_2A4);
        }
        MGSeqKillAll();
        HuAudAllStop();
        omOvlReturnEx(1, 1);
    }
}
