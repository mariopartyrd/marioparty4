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
        u8 kill : 1;
        u8 minus : 1;
        u8 update : 1;
        u8 mode : 3;
    };
    s8 no;
    s8 tens;
    s8 ones;
    u16 time;
    u16 angle;
    s16 sign_model;
    s16 tens_model;
    s16 ones_model;
    s16 coin_model;
} coinChg;

#define COIN_CHG_MODE_APPEAR 0
#define COIN_CHG_MODE_SEPARATE 1
#define COIN_CHG_MODE_SHOW 3
#define COIN_CHG_MODE_DISAPPEAR 4

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

    // Creates and displays the Coin Change model above the player
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

    // Wait for the Coin Change model to disappear
    HuAudFXPlay(15);
    while (BoardCoinChgKillCheck(coin_chg) == 0) {
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

    // Creates and displays the Coin Change model above the player
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
    
    // Wait for the Coin Change model to disappear
    while (BoardCoinChgKillCheck(coin_chg) == 0) {
        HuPrcVSleep();
    }

    // Set player's colour to red and finish the sequence
    GWPlayer[player].color = 2;
    BoardPlayerMotionEndWait(player);
    BoardPlayerIdleSet(player);
}

/**
 * @brief Creates a Coin Change object that shows the amount of
 *     coins a player gained/lost when on the map.
 *
 * @details This function is called when a player:
 *   * Lands on a blue or a red space
 *   * Wins coins in the gambling minigame
 *   * Loses coins stepping on a Sparky Sticker
 *   * Loses coins being stepped on by a player with a Mega Mushroom
 *
 * and does the following:
 *
 *   * Initializes a new Coin Change object and stores it into the earliest element of the Coin Change object array
 *   * Creates a new Coin Change on the board with the given `value`
 *   * Positions the object with `pos`
 *   * Starts the object's processes
 *   * Returns the position of the object in the Coin Change object array
 * 
 * @param [in] pos The position of the 
 * @param [in] value the amount of coins gained or lost by the player
 *
 * @return The position of the Coin Change object in the array
 */
s8 BoardCoinChgCreate(Vec *pos, s8 value) {
    omObjData *obj = NULL;
    coinChg *coin_chg;
    s8 i;
    
    // Find the earliest Coin Change object not initialized (and return with -1 if none)
    for (i = 0; i < 4; i++) {
        if (coinChgObj[i] == 0) {
            break;
        }
    }
    if (i == 4) {
        return -1;
    }
    
    // Initialize new Coin Change object
    obj = omAddObjEx(boardObjMan, 266, 0, 0, -1, &UpdateCoinChg);
    coinChgObj[i] = obj;

    // Setup and create object
    coin_chg = OM_GET_WORK_PTR(obj, coinChg);
    coin_chg->kill = 0;
    coin_chg->update = 0;
    coin_chg->minus = (value < 0) ? 1 : 0;
    coin_chg->mode = 0;
    coin_chg->tens = abs(value) / 10;
    coin_chg->ones = abs(value) % 10;
    coin_chg->no = (s8) (i + 1);
    coin_chg->time = 0;
    coin_chg->angle = 0;

    // Create board model for object
    CreateCoinChg(coin_chg, pos);

    // Position object
    obj->trans.x = pos->x;
    obj->trans.y = pos->y;
    obj->trans.z = pos->z;
    obj->rot.x = 0.0f;
    obj->rot.y = 0.01f;

    // Enable object
    coin_chg->update = 1;

    // Return the position of the Coin Change object in the array
    return coin_chg->no;
}

/**
 * @brief Checks if a Coin Change object has been killed.
 *
 * @details This function is called constantly to sleep until a Coin Change
 * object has been deleted and does the following:
 *
 *   * Returns `num` if `num` is less than zero or greater than four
 *   * Returns false if Coin Change object at `num - 1` exists
 *   * Returns true otherwise
 * 
 * @param [in] num Coin change object number
 * @return 0 if killed, 1 if exists, `num` if invalid
 */
s32 BoardCoinChgKillCheck(s32 num) {
    coinChg *coin_chg;

    // If num is invalid, return num
    if ((num <= 0) || (num > 4)) {
        return num;
    }

    // If Coin Change object at num exists, return 0
    if (coinChgObj[num - 1] != 0) {
        // possibly removed debug info for displaying object information
        coin_chg = OM_GET_WORK_PTR(coinChgObj[num - 1], coinChg);
        return 0;
    }

    // Otherwise (if Coin Change object doesn't exist), return 1
    return 1;
}

/**
 * @brief Kills Coin Change at the given position in the array, if valid
 *
 * @details This function is called when a player with the Mega Mushroom
 *      finishes or prematurely stops squishing another player. It does
 *      the following:
 *   * Marks a Coin Change object for deletion if valid
 * 
 * @param [in] num Coin change object number
 */
void BoardCoinChgKill(s32 num) {
    // Return early if num is invalid
    if ((num <= 0) || (num > 4)) {
        return;
    }

    // If object exists, mark it for deletion
    if (coinChgObj[num - 1] != 0) {
        OM_GET_WORK_PTR(coinChgObj[num - 1], coinChg)->kill = 1;
    }
}

static const s32 coinSignMdl[2] = {
	DATA_MAKE_NUM(DATADIR_BOARD, 22),
	DATA_MAKE_NUM(DATADIR_BOARD, 23)
};

/**
 * @brief Creates and starts animation of a Coin Change model
 * 
 * @details This function is called when creating a Coin Change object
 *     to create the models for each part of the Coin Change. It does
 *     the following:
 *
 *   * Determines the time the animation will take, depending on if
 *  the player loses or gains money (losing take longer)
 *   * Creates models for the coin, sign, tens digit, and ones digit
 *   * Positions the models at `pos`
 *   * Starts the animation of the sign, tens digit, and ones digit
 *   * Initializes the animations to not move and be very small
 *   * Sets all models to near top layer
 *   * Disables the tens digit model if the coin count is less than 10
 *
 * @param [in, out] coin_chg The Coin Change object data
 * @param [in] pos The position of where it should start its animation
 */
static void CreateCoinChg(coinChg *coin_chg, Vec *pos) {
    f32 time;

    // Determine time for animation, lasts longer if coins are lost
    if (coin_chg->minus != 0) {
        time = 2.5f;
    } else {
        time = 1.5f;
    }

    // Create 4 different models for each symbol to be displayed
    coin_chg->sign_model = BoardModelCreate(coinSignMdl[coin_chg->minus], NULL, 0);
    coin_chg->tens_model = BoardModelCreate(coinDigitMdl[coin_chg->tens], NULL, 0);
    coin_chg->ones_model = BoardModelCreate(coinDigitMdl[coin_chg->ones], NULL, 0);
    coin_chg->coin_model = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BOARD, 10), NULL, 0);

    // Position models all at origin for beginning of animation
    BoardModelPosSetV(coin_chg->sign_model, pos);
    BoardModelPosSetV(coin_chg->tens_model, pos);
    BoardModelPosSetV(coin_chg->ones_model, pos);
    BoardModelPosSetV(coin_chg->coin_model, pos);

    // Start animation for all models but coin
    BoardModelMotionStart(coin_chg->sign_model, 0, 0);
    BoardModelMotionStart(coin_chg->tens_model, 0, 0);
    BoardModelMotionStart(coin_chg->ones_model, 0, 0);

    // Set time for animation
    BoardModelMotionTimeSet(coin_chg->sign_model, time);
    BoardModelMotionTimeSet(coin_chg->tens_model, time);
    BoardModelMotionTimeSet(coin_chg->ones_model, time);

    // Set initial speed for animation
    BoardModelMotionSpeedSet(coin_chg->sign_model, 0.0f);
    BoardModelMotionSpeedSet(coin_chg->tens_model, 0.0f);
    BoardModelMotionSpeedSet(coin_chg->ones_model, 0.0f);

    // Scale all models to be very small
    BoardModelScaleSet(coin_chg->sign_model, 0.001, 0.001, 0.001);
    BoardModelScaleSet(coin_chg->tens_model, 0.001, 0.001, 0.001);
    BoardModelScaleSet(coin_chg->ones_model, 0.001, 0.001, 0.001);
    BoardModelScaleSet(coin_chg->coin_model, 0.001, 0.001, 0.001);

    // Set to near top layer for all models
    BoardModelLayerSet(coin_chg->sign_model, 1);
    BoardModelLayerSet(coin_chg->tens_model, 1);
    BoardModelLayerSet(coin_chg->ones_model, 1);
    BoardModelLayerSet(coin_chg->coin_model, 1);

    // disable visibility of tens digit if it is 0
    if (coin_chg->tens == 0) {
        BoardModelVisibilitySet(coin_chg->tens_model, 0);
    }
}

/**
 * @brief Updates the given Coin Change object for each frame
 *
 * @details This is the update function for a Coin Change model object
 *     It does the following:
 *
 *   * Kills the Coin Change object if it or the board is set to be deleted
 *   * Plays the current animation for the Coin Change object if it
 *     is set to be updated and the delay timer is not 0
 *   * The current animation is determined by the Coin Change object's mode, which can be:
 *     * APPEAR (0): Coin pops up while spinning
 *     * SEPARATE (1): The coin and text split from each other
 *     * SHOW (3): The text moves up/down, pauses afterward
 *     * DISAPPEAR (4): The models all shrink away
 *   * *There is no (2) mode*
 * 
 * @param [in, out] object Coin Change object
 */
static void UpdateCoinChg(omObjData *object) {
    coinChg *coin_chg;

    coin_chg = OM_GET_WORK_PTR(object, coinChg);

    // If the Coin Change object should be killed,
    // kill all models that exist, and clear value in array
    if ((coin_chg->kill != 0) || (BoardIsKill() != 0)) {
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
        coinChgObj[coin_chg->no - 1] = 0;
        omDelObjEx(HuPrcCurrentGet(), object);
        return;
    }

    // If object is set to update ...
    if (coin_chg->update != 0) {
        // Wait until time runs out
        if (coin_chg->time != 0) {
            coin_chg->time -= 1;
            return;
        }
        
        // Play currently set animation
        switch (coin_chg->mode) {
			case COIN_CHG_MODE_APPEAR:
				CoinChgAppear(object, coin_chg);
				return;
			case COIN_CHG_MODE_SEPARATE:
				CoinChgSeparate(object, coin_chg);
				return;
			case COIN_CHG_MODE_SHOW:
				CoinChgShow(object, coin_chg);
				return;
			case COIN_CHG_MODE_DISAPPEAR:
				CoinChgDisappear(object, coin_chg);
				break;
        }
    }
}

/**
 * @brief Plays the "appear" animation for a Coin Change object
 *
 * @details This function is called when the current animation mode
 *     is set to 0 (`COIN_CHG_MODE_APPEAR`) and does the following:
 *
 *   * Uses `coinChg.angle` as a smoothing value to scale and rotate the coin model
 *   * Increases the angle by 6 until it is greater than 90
 *   * When finished, sets mode to 1 (`COIN_CHG_MODE_SEPARATE`) and scales,
 *     positions, and rotates the other models to be in line with the coin
 * 
 * @param [in, out] object Coin Change object
 * @param [in, out] coin_chg Coin Change object data
 */
static void CoinChgAppear(omObjData *object, coinChg *coin_chg) {
    f32 scale;
    f32 angle;

    // Scale the object smoothly with sine
    OSu16tof32(&coin_chg->angle, &angle);
    angle = sind(angle);
    scale = angle;

    // Rotate the object linearly with the scale
    object->rot.x = 405.0f * angle;

    // scale, position, and rotate model
    BoardModelScaleSet(coin_chg->coin_model, scale, scale, scale);
    BoardModelPosSet(coin_chg->coin_model, object->trans.x, object->trans.y, object->trans.z);
    BoardModelRotYSet(coin_chg->coin_model, object->rot.x);

    // Increase angle if we haven't rotated enough
    if (coin_chg->angle < 90) {
        coin_chg->angle += 6;
        return;
    }
    
    // Otherwise, move to next animation and reset angle
    coin_chg->mode = COIN_CHG_MODE_SEPARATE;
    coin_chg->angle = 0;

    // Set other models to be where coin model is
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

/**
 * @brief Plays the "separate" animation for a Coin Change object
 * 
 * @details This function is called when the current animation mode
 *     is set to 1 (`COIN_CHG_MODE_SEPARATE`) and does the following:
 *
 *   * Sets up spacing between models, making it larger if there is no tens digit
 *   * Uses `angle` to separate models from each other by a bit each frame
 *   * When finished, resets `angle` and sets the animation mode to 3 (`COIN_CHG_MODE_SHOW`)
 *
 * @param [in, out] object Coin Change object
 * @param [in, out] coin_chg Coin Change object data
 */
static void CoinChgSeparate(omObjData *object, coinChg *coin_chg) {
    f32 y_offset;
    f32 x_scale;
    f32 spacing;
    f32 coin_x;
    f32 ones_x;
    f32 tens_x;
    f32 sign_x;

    // Get angle
    OSu16tof32(&coin_chg->angle, &x_scale);
    
    // Make spacing between models smaller if displaying more digits
    if (coin_chg->tens != 0) {
        spacing = 140.0f;
    } else {
        spacing = 105.0f;
    }
    
    // Get scale, position, and rotation for each model
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

    // Set position and rotation
    BoardModelPosSet(coin_chg->coin_model, coin_x, object->trans.y + y_offset, object->trans.z);
    BoardModelPosSet(coin_chg->sign_model, sign_x, object->trans.y + y_offset, object->trans.z);
    BoardModelPosSet(coin_chg->ones_model, ones_x, object->trans.y + y_offset, object->trans.z);
    BoardModelPosSet(coin_chg->tens_model, tens_x, object->trans.y + y_offset, object->trans.z);
    BoardModelRotYSet(coin_chg->coin_model, object->rot.x);
    BoardModelRotYSet(coin_chg->sign_model, object->rot.x);
    BoardModelRotYSet(coin_chg->ones_model, object->rot.x);
    BoardModelRotYSet(coin_chg->tens_model, object->rot.x);

    // Increase angle if we haven't separated enough
    if (coin_chg->angle < 90) {
        coin_chg->angle += 6;
        return;
    }

    // Set y position to new offset
    object->trans.y += y_offset;
    
    // Move to next animation and set angle to 0
    coin_chg->mode = COIN_CHG_MODE_SHOW;
    coin_chg->angle = 0;
}

/**
 * @brief Plays the "show" animation for a Coin Change object
 * 
 * @details This function is called when the current animation mode
 *     is set to 3 (`COIN_CHG_MODE_SHOW`) and does the following:
 *
 *   * Uses `angle` to move all models up or down each frame if the
 *     player gained or lost coins respectively
 *   * When finished:
 *     * Resets the angle and sets the animation mode to 4 (`COIN_CHG_MODE_DISAPPEAR`)
 *     * Sets update function to wait ~0.3 seconds
 *     * Sets the scale of the object to 1.
 *   
 * 
 * @param [in, out] object Coin Change object
 * @param [in, out] coin_chg Coin Change object data
 */
static void CoinChgShow(omObjData* object, coinChg* coin_chg) {
    Vec pos;
    f32 angle;
    f32 y_pos;

    // Get y offset
    OSu16tof32(&coin_chg->angle, &angle);
    angle = sind(angle);
    
    // Move down if negative, up if positive
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

    // Increase angle if we haven't moved enough
    if (coin_chg->angle < 90) {
        coin_chg->angle += 6;
        return;
    }
    
    // Move to next animation and set angle to 0
    coin_chg->mode = COIN_CHG_MODE_DISAPPEAR;
    coin_chg->angle = 0;

    // Set wait time to 0.3 seconds (or 0.36 seconds in PAL)
    coin_chg->time = 18;

    // Reset scale
    object->scale.x = 1.0f;
    object->scale.y = 1.0f;
}

/**
 * @brief Plays the "disappear" animation for a Coin Change object
 *     and, when finished, makes invisible and sets it to be killed
 *
 * @details This function is called when the current animation mode
 *     is set to 4 (`COIN_CHG_MODE_DISAPPEAR`) and does the following:
 *
 *   * Splits the animation into 2: the animation initially stretches
 *     the text vertically, then flips the text and squishes it horizontally
 *   * Uses `angle` to set the scale each frame
 *   * When finished, all models are made invisible and the object data is
 *     set to be killed
 * 
 * @param [in, out] object Coin Change object
 * @param [in, out] coin_chg Coin Change object data
 */
static void CoinChgDisappear(omObjData* object, coinChg* coin_chg) {
    const u16 angle = ((coin_chg->angle * 2) % 180);
    f32 rot;
    
    // Set scale. First half of animation stretches up, second half squishes inward (and is upside down)
    OSu16tof32(&angle, &rot);
    if (angle <= 90.0f) {
        object->scale.x = 0.5 * cosd(rot);
        object->scale.y = 2.5 * sind(rot);
    } else {
        object->scale.x = 2.5 * sind(rot);
        object->scale.y = 0.5 * cosd(rot);
    }

    // Ensure object's scale is not 0
    if (0.0f == object->scale.x) {
        object->scale.x = 0.0001f;
    }
    if (0.0f == object->scale.y) {
        object->scale.y = 0.0001f;
    }

    // Set scale for all models
    BoardModelScaleSet(coin_chg->coin_model, object->scale.x, object->scale.y, 1.0f);
    BoardModelScaleSet(coin_chg->sign_model, object->scale.x, object->scale.y, 1.0f);
    BoardModelScaleSet(coin_chg->ones_model, object->scale.x, object->scale.y, 1.0f);
    BoardModelScaleSet(coin_chg->tens_model, object->scale.x, object->scale.y, 1.0f);

    // Increase angle if we haven't moved enough,
    // half of normal amount because animation is twice as long
    if (coin_chg->angle < 90) {
        coin_chg->angle += 3;
        if (coin_chg->angle > 90) {
            coin_chg->angle = 90;
        }
    } else {
        // All animations have played, make invisible and set to be killed
        BoardModelVisibilitySet(coin_chg->sign_model, 0);
        BoardModelVisibilitySet(coin_chg->tens_model, 0);
        BoardModelVisibilitySet(coin_chg->ones_model, 0);
        BoardModelVisibilitySet(coin_chg->coin_model, 0);
        coin_chg->kill = 1;
    }
}
