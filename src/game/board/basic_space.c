#include "game/board/basic_space.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/tutorial.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/gamework_data.h"
#include "math.h"
#include "ext_math.h"
#include "stdlib.h"

typedef struct bit_copy {
    struct {
        u8 hide : 1;
        u8 minus : 1;
        u8 update : 1;
        u8 mode : 3;
    };
    s8 index;
    s8 tens;
    s8 ones;
    u16 time;
    u16 angle;
    s16 sign_model;
    s16 tens_model;
    s16 ones_model;
    s16 coin_model;
} coinChg;

static void CreateCoinChg(coinChg*, Vec*);
static void UpdateCoinChg(omObjData*);
static void CoinChgAppear(omObjData*, coinChg*);
static void CoinChgSeparate(omObjData*, coinChg*);
static void CoinChgShow(omObjData*, coinChg*);
static void CoinChgDisappear(omObjData*, coinChg*);

extern void BoardCameraViewSet(s32);
extern void BoardPlayerPosGet(s32, Vec*);
extern void BoardPlayerMotionEndWait(s32);
extern void BoardPlayerCoinsAdd(s32, s32);
extern void BoardPlayerIdleSet(s32);
extern void BoardCameraMotBlendSet(s32, s16, s16);
extern s32 BoardPlayerMotBlendCheck(s32);

static omObjData *coinChgObj[4] = {
    NULL,
    NULL,
    NULL,
    NULL
};

static s32 coinDigitMdl[10] = {
	DATA_MAKE_NUM(DATADIR_BOARD, 12),
	DATA_MAKE_NUM(DATADIR_BOARD, 13),
	DATA_MAKE_NUM(DATADIR_BOARD, 14),
	DATA_MAKE_NUM(DATADIR_BOARD, 15),
	DATA_MAKE_NUM(DATADIR_BOARD, 16),
	DATA_MAKE_NUM(DATADIR_BOARD, 17),
	DATA_MAKE_NUM(DATADIR_BOARD, 18),
	DATA_MAKE_NUM(DATADIR_BOARD, 19),
	DATA_MAKE_NUM(DATADIR_BOARD, 20),
	DATA_MAKE_NUM(DATADIR_BOARD, 21),
};

/**
 * @brief Handle what happens when a player lands on a blue space.
 * 
 * @details This function is called when a player lands on a blue space and
 * does the following:
 * 
 *   * Focuses the camera on the player and puts them in a good state
 *   * Checks if the player is in tutorial mode and executes the tutorial hook
 *   * Determines how many coins to award the player
 *   * Displays the coin gain to the player
 *   * Adds coins to the player's inventory one at a time
 *   * Removes the coin gain display
 *   * Sets the player's colour to blue (used for minigames)
 * 
 * @param [in] player The player who landed on the space.
 * @param [in] space The space the player landed on.
 */
void BoardLandBlueExec(s32 player, s32 space) {
    Vec pos;
    s32 i;
    s8 coin_chg;
    s32 coins;
	
    // Focus camera on the player and position player towards the camera
    BoardCameraViewSet(2);
    BoardPlayerMotBlendSet(player, 0, 15);
    while (BoardPlayerMotBlendCheck(player) == 0) {
        HuPrcVSleep();
    }

    // Check if the player is in tutorial mode and execute the tutorial hook
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        BoardCameraMotionWait();
        BoardTutorialHookExec(10, 0);
    }

    // Set the value of the coins to receive, modifying as necessary
    coins = 3;
    if (GWSystem.last5_effect == 1) {
        coins *= 2;
    }

    // Creates and displays the coin change model above the player
    BoardPlayerPosGet(player, &pos);
    pos.y += 250.0f;
    coin_chg = BoardCoinChgCreate(&pos, coins);
    HuAudFXPlay(839);
    BoardCameraMotionWait();
    BoardPlayerMotionShiftSet(player, 12, 0.0f, 4.0f, HU3D_MOTATTR_NONE);
    
    // Add coins to the player's inventory one at a time
    for (i = 0; i < coins; i++) {
        BoardPlayerCoinsAdd(player, 1);
        HuAudFXPlay(7);
        HuPrcSleep(6);
    }

    // Wait for the coin change model to disappear
    HuAudFXPlay(15);
    while (BoardCoinChgExist(coin_chg) == 0) {
        HuPrcVSleep();
    }

    // Set player's colour to blue and finish the sequence
    GWPlayer[player].color = 1;
    BoardPlayerMotionEndWait(player);
    BoardPlayerIdleSet(player);
}

/**
 * @brief Handle what happens when a player lands on a red space.
 * 
 * @details This function is called when a player lands on a red space and
 * does the following:
 * 
 *   * Focuses the camera on the player and puts them in a good state
 *   * Checks if the player is in tutorial mode and executes the tutorial hook
 *   * Determines how many coins to remove from the player
 *   * Displays the coin loss to the player
 *   * Removes coins to the player's inventory one at a time
 *   * Removes the coin loss display
 *   * Sets the player's colour to red (used for minigames)
 * 
 * @param [in] player The player who landed on the space.
 * @param [in] space The space the player landed on.
 */
void BoardLandRedExec(s32 player, s32 space) {
    Vec pos;
    s32 i;
    s8 coin_chg;
    s32 coins;

    // Focus camera on the player and position player towards the camera
    BoardCameraViewSet(2);
    omVibrate(player, 12, 6, 6);
    BoardPlayerMotBlendSet(player, 0, 15);
    while (BoardPlayerMotBlendCheck(player) == 0) {
        HuPrcVSleep();
    }

    // Check if the player is in tutorial mode and execute the tutorial hook
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        BoardCameraMotionWait();
        BoardTutorialHookExec(11, 0);
    }

    // Set the value of the coins to remove, modifying as necessary
    coins = 3;
    if (GWSystem.last5_effect == 1) {
        coins *= 2;
    }

    // Creates and displays the coin change model above the player
    BoardPlayerPosGet(player, &pos);
    pos.y += 250.0f;
    coin_chg = BoardCoinChgCreate(&pos, -coins);
    HuAudFXPlay(840);
    BoardCameraMotionWait();
    BoardPlayerMotionShiftSet(player, 13, 0.0f, 4.0f, HU3D_MOTATTR_NONE);

    // Remove coins to the player's inventory one at a time
    for (i = 0; i < coins; i++) {
        BoardPlayerCoinsAdd(player, -1);
        HuAudFXPlay(14);
        HuPrcSleep(6);
    }
    HuAudFXPlay(15);
    
    // Wait for the coin change model to disappear
    while (BoardCoinChgExist(coin_chg) == 0) {
        HuPrcVSleep();
    }

    // Set player's colour to red and finish the sequence
    GWPlayer[player].color = 2;
    BoardPlayerMotionEndWait(player);
    BoardPlayerIdleSet(player);
}

s8 BoardCoinChgCreate(Vec *pos, s8 value) {
    omObjData *obj = NULL;
    coinChg *coin_chg;
    s8 i;
    
    for (i = 0; i < 4; i++) {
        if (coinChgObj[i] == 0) {
            break;
        }
    }
    if (i == 4) {
        return -1;
    }
    
    obj = omAddObjEx(boardObjMan, 266, 0, 0, -1, &UpdateCoinChg);
    coinChgObj[i] = obj;
    coin_chg = OM_GET_WORK_PTR(obj, coinChg);
    coin_chg->hide = 0;
    coin_chg->update = 0;
    coin_chg->minus = (value < 0) ? 1 : 0;
    coin_chg->mode = 0;
    coin_chg->tens = abs(value) / 10;
    coin_chg->ones = abs(value) % 10;
    coin_chg->index = (s8) (i + 1);
    coin_chg->time = 0;
    coin_chg->angle = 0;
    CreateCoinChg(coin_chg, pos);
    obj->trans.x = pos->x;
    obj->trans.y = pos->y;
    obj->trans.z = pos->z;
    obj->rot.x = 0.0f;
    obj->rot.y = 0.01f;
    coin_chg->update = 1;
    return coin_chg->index;
}

s32 BoardCoinChgExist(s32 index) {
    coinChg *coin_chg;

    if ((index <= 0) || (index > 4)) {
        return index;
    }
    if (coinChgObj[index - 1] != 0) {
        coin_chg = OM_GET_WORK_PTR(coinChgObj[index - 1], coinChg);
        return 0;
    }
    return 1;
}

void BoardCoinChgHide(s32 index) {

    if ((index <= 0) || (index > 4)) {
        return;
    }
    if (coinChgObj[index - 1] != 0) {
        OM_GET_WORK_PTR(coinChgObj[index - 1], coinChg)->hide = 1;
    }
}

static const s32 coinSignMdl[2] = {
	DATA_MAKE_NUM(DATADIR_BOARD, 22),
	DATA_MAKE_NUM(DATADIR_BOARD, 23)
};

static void CreateCoinChg(coinChg *coin_chg, Vec *pos) {
    f32 time;

    if (coin_chg->minus != 0) {
        time = 2.5f;
    } else {
        time = 1.5f;
    }
    coin_chg->sign_model = BoardModelCreate(coinSignMdl[coin_chg->minus], NULL, 0);
    coin_chg->tens_model = BoardModelCreate(coinDigitMdl[coin_chg->tens], NULL, 0);
    coin_chg->ones_model = BoardModelCreate(coinDigitMdl[coin_chg->ones], NULL, 0);
    coin_chg->coin_model = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 0);
    BoardModelPosSetV(coin_chg->sign_model, pos);
    BoardModelPosSetV(coin_chg->tens_model, pos);
    BoardModelPosSetV(coin_chg->ones_model, pos);
    BoardModelPosSetV(coin_chg->coin_model, pos);
    BoardModelMotionStart(coin_chg->sign_model, 0, 0);
    BoardModelMotionStart(coin_chg->tens_model, 0, 0);
    BoardModelMotionStart(coin_chg->ones_model, 0, 0);
    BoardModelMotionTimeSet(coin_chg->sign_model, time);
    BoardModelMotionTimeSet(coin_chg->tens_model, time);
    BoardModelMotionTimeSet(coin_chg->ones_model, time);
    BoardModelMotionSpeedSet(coin_chg->sign_model, 0.0f);
    BoardModelMotionSpeedSet(coin_chg->tens_model, 0.0f);
    BoardModelMotionSpeedSet(coin_chg->ones_model, 0.0f);
    BoardModelScaleSet(coin_chg->sign_model, 0.001, 0.001, 0.001);
    BoardModelScaleSet(coin_chg->tens_model, 0.001, 0.001, 0.001);
    BoardModelScaleSet(coin_chg->ones_model, 0.001, 0.001, 0.001);
    BoardModelScaleSet(coin_chg->coin_model, 0.001, 0.001, 0.001);
    BoardModelLayerSet(coin_chg->sign_model, 1);
    BoardModelLayerSet(coin_chg->tens_model, 1);
    BoardModelLayerSet(coin_chg->ones_model, 1);
    BoardModelLayerSet(coin_chg->coin_model, 1);
    if (coin_chg->tens == 0) {
        BoardModelVisibilitySet(coin_chg->tens_model, 0);
    }
}

static void UpdateCoinChg(omObjData *object) {
    coinChg *coin_chg;

    coin_chg = OM_GET_WORK_PTR(object, coinChg);
    if ((coin_chg->hide != 0) || (BoardIsKill() != 0)) {
        if (coin_chg->coin_model != -1) {
            BoardModelKill(coin_chg->coin_model);
            coin_chg->coin_model = -1;
        }
        if (coin_chg->sign_model != -1) {
            BoardModelKill(coin_chg->sign_model);
            coin_chg->sign_model = -1;
        }
        if (coin_chg->tens_model != -1) {
            BoardModelKill(coin_chg->tens_model);
            coin_chg->tens_model = -1;
        }
        if (coin_chg->ones_model != -1) {
            BoardModelKill(coin_chg->ones_model);
            coin_chg->ones_model = -1;
        }
        coinChgObj[coin_chg->index - 1] = 0;
        omDelObjEx(HuPrcCurrentGet(), object);
        return;
    }
    if (coin_chg->update != 0) {
        if (coin_chg->time != 0) {
            coin_chg->time -= 1;
            return;
        }
        
        switch (coin_chg->mode) {
			case 0:
				CoinChgAppear(object, coin_chg);
				return;
			case 1:
				CoinChgSeparate(object, coin_chg);
				return;
			case 3:
				CoinChgShow(object, coin_chg);
				return;
			case 4:
				CoinChgDisappear(object, coin_chg);
				break;
        }
    }
}

static void CoinChgAppear(omObjData *object, coinChg *coin_chg) {
    f32 scale;
    f32 angle;

    OSu16tof32(&coin_chg->angle, &angle);
    angle = sind(angle);
    scale = angle;
    object->rot.x = 405.0f * angle;
    BoardModelScaleSet(coin_chg->coin_model, scale, scale, scale);
    BoardModelPosSet(coin_chg->coin_model, object->trans.x, object->trans.y, object->trans.z);
    BoardModelRotYSet(coin_chg->coin_model, object->rot.x);
    if (coin_chg->angle < 90) {
        coin_chg->angle += 6;
        return;
    }
    
    coin_chg->mode = 1;
    coin_chg->angle = 0;
    BoardModelScaleSet(coin_chg->sign_model, scale, scale, scale);
    BoardModelPosSet(coin_chg->sign_model, object->trans.x, object->trans.y, object->trans.z);
    BoardModelRotYSet(coin_chg->sign_model, object->rot.x);
    BoardModelScaleSet(coin_chg->ones_model, scale, scale, scale);
    BoardModelPosSet(coin_chg->ones_model, object->trans.x, object->trans.y, object->trans.z);
    BoardModelRotYSet(coin_chg->ones_model, object->rot.x);
    BoardModelScaleSet(coin_chg->tens_model, scale, scale, scale);
    BoardModelPosSet(coin_chg->tens_model, object->trans.x, object->trans.y, object->trans.z);
    BoardModelRotYSet(coin_chg->tens_model, object->rot.x);
}

static void CoinChgSeparate(omObjData *object, coinChg *coin_chg) {
    f32 y_offset;
    f32 x_scale;
    f32 spacing;
    f32 coin_x;
    f32 ones_x;
    f32 tens_x;
    f32 sign_x;

    OSu16tof32(&coin_chg->angle, &x_scale);
    
    if (coin_chg->tens != 0) {
        spacing = 140.0f;
    } else {
        spacing = 105.0f;
    }
    y_offset = 200.0 * sind(2.0f * x_scale);
    x_scale = sind(x_scale);
    object->rot.x = 45.0f + (315.0f * x_scale);
    if (coin_chg->tens != 0) {
        coin_x = object->trans.x + (x_scale * -spacing);
        sign_x = object->trans.x + ((x_scale * -spacing) / 3.0f);
        ones_x = object->trans.x + (x_scale * spacing);
        tens_x = object->trans.x + ((x_scale * spacing) / 3.0f);
    } else {
        sign_x = object->trans.x;
        tens_x = object->trans.x;
        ones_x = object->trans.x + (x_scale * spacing);
        coin_x = object->trans.x + (x_scale * -spacing);
    }
    BoardModelPosSet(coin_chg->coin_model, coin_x, object->trans.y + y_offset, object->trans.z);
    BoardModelPosSet(coin_chg->sign_model, sign_x, object->trans.y + y_offset, object->trans.z);
    BoardModelPosSet(coin_chg->ones_model, ones_x, object->trans.y + y_offset, object->trans.z);
    BoardModelPosSet(coin_chg->tens_model, tens_x, object->trans.y + y_offset, object->trans.z);
    BoardModelRotYSet(coin_chg->coin_model, object->rot.x);
    BoardModelRotYSet(coin_chg->sign_model, object->rot.x);
    BoardModelRotYSet(coin_chg->ones_model, object->rot.x);
    BoardModelRotYSet(coin_chg->tens_model, object->rot.x);
    if (coin_chg->angle < 90) {
        coin_chg->angle += 6;
        return;
    }
    object->trans.y += y_offset;
    coin_chg->mode = 3;
    coin_chg->angle = 0;
}

static void CoinChgShow(omObjData* object, coinChg* coin_chg) {
    Vec pos;
    f32 angle;
    f32 y_pos;

    OSu16tof32(&coin_chg->angle, &angle);
    angle = sind(angle);
    if (coin_chg->minus != 0) {
        y_pos = (-50.0f * angle) + object->trans.y;
    } else {
        y_pos = (50.0f * angle) + object->trans.y;
    }
    BoardModelPosGet(coin_chg->coin_model, &pos);
    BoardModelPosSet(coin_chg->coin_model, pos.x, y_pos, pos.z);
    BoardModelPosGet(coin_chg->sign_model, &pos);
    BoardModelPosSet(coin_chg->sign_model, pos.x, y_pos, pos.z);
    BoardModelPosGet(coin_chg->ones_model, &pos);
    BoardModelPosSet(coin_chg->ones_model, pos.x, y_pos, pos.z);
    BoardModelPosGet(coin_chg->tens_model, &pos);
    BoardModelPosSet(coin_chg->tens_model, pos.x, y_pos, pos.z);
    if (coin_chg->angle < 90) {
        coin_chg->angle += 6;
        return;
    }
    coin_chg->mode = 4;
    coin_chg->angle = 0;
    coin_chg->time = 18;
    object->scale.x = 1.0f;
    object->scale.y = 1.0f;
}

static void CoinChgDisappear(omObjData* object, coinChg* coin_chg) {
    const u16 angle = ((coin_chg->angle * 2) % 180);
    f32 rot;
    
    OSu16tof32(&angle, &rot);
    if (angle <= 90.0f) {
        object->scale.x = 0.5 * cosd(rot);
        object->scale.y = 2.5 * sind(rot);
    } else {
        object->scale.x = 2.5 * sind(rot);
        object->scale.y = 0.5 * cosd(rot);
    }
    if (0.0f == object->scale.x) {
        object->scale.x = 0.0001f;
    }
    if (0.0f == object->scale.y) {
        object->scale.y = 0.0001f;
    }
    BoardModelScaleSet(coin_chg->coin_model, object->scale.x, object->scale.y, 1.0f);
    BoardModelScaleSet(coin_chg->sign_model, object->scale.x, object->scale.y, 1.0f);
    BoardModelScaleSet(coin_chg->ones_model, object->scale.x, object->scale.y, 1.0f);
    BoardModelScaleSet(coin_chg->tens_model, object->scale.x, object->scale.y, 1.0f);
    if (coin_chg->angle < 90) {
        coin_chg->angle += 3;
        if (coin_chg->angle > 90) {
            coin_chg->angle = 90;
        }
    } else {
        BoardModelVisibilitySet(coin_chg->sign_model, 0);
        BoardModelVisibilitySet(coin_chg->tens_model, 0);
        BoardModelVisibilitySet(coin_chg->ones_model, 0);
        BoardModelVisibilitySet(coin_chg->coin_model, 0);
        coin_chg->hide = 1;
    }
}
