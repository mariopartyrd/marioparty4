#include "game/chrman.h"
#include "game/disp.h"
#include "game/esprite.h"
#include "game/frand.h"
#include "game/gamework_data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "REL/m401Dll.h"
#include "ext_math.h"
#include "math.h"

#ifndef __MWERKS__
#include "game/audio.h"
#endif

float gravity_acceleration = -7.1875f;

s16 player_character_model_indices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

Vec global_light_position = { 1500, 2500, 1500 };

Vec global_light_direction = { 0, -1, 0 };

GXColor global_light_color = { 255, 255, 255, 255 };

Vec shadow_light_position = { 0, 2500, 0 };

Vec shadow_light_up_vector = { 0, 1, -1 };

Vec shadow_light_target = { 0, 0, 0 };

s32 sound_effect_handle;
OMOBJ **player_objects;
OMOBJ *sequence_controller_object;
OMOBJ *minigame_root_object;
OMOBJ *tunnel_scene_object;
OMOBJ *falling_object_scene_object;
OMOBJ *orbiting_scene_objects[2];
OMOBJ *moving_obstacle_object;
OMOBJ *orbiting_particle_object;
OMOBJ *flocking_particle_object;
OMOBJ *falling_projectile_objects[4];
OMOBJ *score_hud_object;
OMOBJ *camera_controller_object;
OMOBJ *stage_particle_effect_a;
OMOBJ *stage_particle_effect_b;
OMOBJ *stage_particle_effect_c;
OMOBJ *stage_particle_effect_d;
OMOBJ *scene_transition_object;
OMOBJ *shared_particle_model_object;
s16 minigame_sequence_id;
s16 minigame_exit_ready;
s16 reserved_minigame_state;
s16 winner_count;
s16 winner_player_indices[4];
s16 winner_character_indices[4];
s16 global_light_id;
s32 audio_sequence_id;
s32 ambient_sound_emitter_handles[5];
s32 moving_obstacle_sound_emitter;
float sound_emitter_max_distance;
float sound_emitter_far_distance;
Vec sound_emitter_position;
Vec camera_position;
Vec camera_target;
Vec previous_camera_position;
float camera_move_distance;
Vec active_camera_position;
Vec active_camera_target;
Vec camera_up_vector;
Vec reserved_camera_vector;
HUPROCESS *minigame_object_manager;
s16 winner_sequence_timer;
s16 camera_transition_index;
s32 stage_event_counter;
float obstacle_rotation_angle;
s16 stage_section_index;
s16 stage_segment_index;
OMOBJ *unused_object_handle_8;
OMOBJ *unused_object_handle_4;
OMOBJ *unused_object_handle_0;

void update_minigame_flow(OMOBJ *object);
void cleanup_minigame(OMOBJ *object);
void create_score_hud(OMOBJ *object);
void update_score_popups(OMOBJ *object);

void create_tunnel_scene(OMOBJ *object);
void create_player(OMOBJ *object);
void update_player_results(OMOBJ *object);
void create_falling_object(OMOBJ *object);
void create_orbiting_object(OMOBJ *object);
void create_moving_obstacle(OMOBJ *object);
void create_falling_projectiles(HUPROCESS *objman);
void update_start_countdown(OMOBJ *object);
void update_minigame_results(OMOBJ *object);
void create_orbiting_particle_group(OMOBJ *object);
void capture_camera_state(OMOBJ *object);

void create_shared_particle_models(s16 model_count);

void ObjectSetup(void)
{
    s32 i;
    OMOBJ *object;
    HU3DCAMERA *camera;
    HU3DLIGHT *light;
    OSReport("**** M401ObjectSetup ****\n");
    HuMemHeapDump(HuMemHeapPtrGet(HEAP_HEAP), -1);
    HuMemHeapDump(HuMemHeapPtrGet(HEAP_MODEL), -1);
    HuMemHeapDump(HuMemHeapPtrGet(HEAP_DVD), -1);
    minigame_object_manager = omInitObjMan(60, 8192);
    omGameSysInit(minigame_object_manager);
    global_light_id = Hu3DGLightCreateV(&global_light_position, &global_light_direction, &global_light_color);
    Hu3DGLightInfinitytSet(global_light_id);
    light = &Hu3DGlobalLight[global_light_id];
    light->type |= 0x8000;
    Hu3DCameraCreate(1);
    camera = &Hu3DCamera[0];
    Hu3DCameraViewportSet(1, 0, 0, 640, 480, 0, 1);
    sequence_controller_object = omAddObjEx(minigame_object_manager, 1000, 3, 0, -1, update_start_countdown);
    sequence_controller_object->work[0] = 0;
    minigame_root_object = omAddObjEx(minigame_object_manager, 10, 0, 0, -1, update_minigame_flow);
    omMakeGroupEx(minigame_object_manager, 0, 4);
    player_objects = omGetGroupMemberListEx(minigame_object_manager, 0);
    omMakeGroupEx(minigame_object_manager, 1, 28);
    for (i = 0; i < 4; i++) {
        object = omAddObjEx(minigame_object_manager, 1200, 4, 10, 0, create_player);
        object->work[0] = i;
    }
    camera_field_of_view = 60;
    camera_near_plane = 50;
    camera_far_plane = 25000;
    Hu3DShadowCreate(30, 20, 5000);
    Hu3DShadowTPLvlSet(0.35f);
    shadow_light_position.y = camera_target.y + 1500.0f;
    shadow_light_position.z = camera_target.z + 500.0f;
    shadow_light_target.y = camera_target.y;
    shadow_light_target.z = camera_target.z + 500.0f;
    Hu3DShadowPosSet(&shadow_light_position, &shadow_light_up_vector, &shadow_light_target);
    tunnel_scene_object = omAddObjEx(minigame_object_manager, 500, 12, 3, -1, create_tunnel_scene);
    falling_object_scene_object = omAddObjEx(minigame_object_manager, 1100, 1, 1, -1, create_falling_object);
    orbiting_scene_objects[0] = omAddObjEx(minigame_object_manager, 1110, 1, 1, -1, create_orbiting_object);
    orbiting_scene_objects[1] = omAddObjEx(minigame_object_manager, 1110, 1, 1, -1, create_orbiting_object);
    moving_obstacle_object = omAddObjEx(minigame_object_manager, 1120, 1, 2, -1, create_moving_obstacle);
    scene_transition_object = omAddObjEx(minigame_object_manager, 100, 0, 0, -1, capture_camera_state);
    score_hud_object = omAddObjEx(minigame_object_manager, 1500, 0, 0, -1, create_score_hud);
    create_shared_particle_models(90);
    orbiting_particle_object = omAddObjEx(minigame_object_manager, 500, 9, 0, -1, create_orbiting_particle_group);
    create_falling_projectiles(minigame_object_manager);
    load_score_particle_resources();
    create_score_particle_model_pool();
    flocking_particle_object = create_particle_model_manager(minigame_object_manager);
    camera_move_distance = 0;
    previous_camera_position = camera->pos;
    Hu3DReflectNoSet(0);
    camera_aspect_ratio = 0;
    minigame_exit_ready = 0;
    winner_count = 0;
    Hu3DFogSet(3000, 10000, 10, 60, 160);
    Hu3DBGColorSet(10, 60, 160);
    sound_emitter_max_distance = 3000;
    sound_emitter_far_distance = 142000;
    sound_effect_handle = HuAudFXPlay(1290);
}

void update_minigame_flow(OMOBJ *object)
{
    s32 player_index;
    M401WorkPlayer *player_work;
    s16 highest_score;
    switch (camera_aspect_ratio) {
        case 0:
            break;

        case 1:
            if (minigame_exit_ready == 1) {
                camera_aspect_ratio = 2;
                minigame_sequence_id = MGSeqFinishCreate();
                HuAudSeqFadeOut(audio_sequence_id, 100);
            }
            break;

        case 2:
            if (sequence_controller_object == NULL) {
                sequence_controller_object = omAddObjEx(HuPrcCurrentGet(), 1000, 0, 0, -1, update_minigame_results);
                sequence_controller_object->work[0] = 0;
                highest_score = 0;
                winner_count = 0;
                for (player_index = 0; player_index < 4; player_index++) {
                    player_work = player_objects[player_index]->data;
                    player_objects[player_index]->objFunc = update_player_results;
                    player_work->player_state = 5;
                    player_work->is_round_winner = 0;
                    if (player_work->score > highest_score) {
                        highest_score = player_work->score;
                    }
                    winner_player_indices[player_index] = -1;
                    winner_character_indices[player_index] = -1;
                }
                if (highest_score > 0) {
                    for (player_index = 0; player_index < 4; player_index++) {
                        player_work = player_objects[player_index]->data;
                        if (player_work->score == highest_score) {
                            winner_character_indices[winner_count] = GWPlayerCfg[player_index].character;
                            winner_player_indices[winner_count++] = player_index;
                            player_work->is_round_winner = 1;
                        }
                    }
                }
                OSReport("winnercnt:%d\n", winner_count);
            }
            break;
    }
    if (omSysExitReq) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        HuAudSeqFadeOut(audio_sequence_id, 100);
        HuAudFXStop(sound_effect_handle);
        object->objFunc = cleanup_minigame;
    }
}

void cleanup_minigame(OMOBJ *object)
{
    s32 i;
    if (!WipeStatGet()) {
        free_score_particle_resources();
        for (i = 0; i < 4; i++) {
            CharModelKill(player_character_model_indices[GWPlayerCfg[i].character]);
        }
        HuAudFXListnerKill();
        omOvlReturnEx(1, 1);
    }
}

void reset_scene_fog(void)
{
    Hu3DFogSet(3000, 10000, 10, 60, 160);
    Hu3DBGColorSet(10, 60, 160);
}

typedef struct m401_score_hud_work {
    s16 player_portrait_sprites[4];
    s16 score_digit_sprites[4][3];
    u8 reserved_score_display_data[0x30];
    s16 rising_score_sprites[4][3];
    s16 falling_score_sprites[4][3];
    s16 player_status_sprites[4];
    s16 player_status_shadow_sprites[4];
    float rising_score_alpha[4];
    float falling_score_alpha[4];
    float rising_score_base_x[4];
    float rising_score_base_y[4];
    float falling_score_base_x[4];
    float falling_score_base_y[4];
    float rising_score_offset_x[4];
    float rising_score_offset_y[4];
    float falling_score_offset_x[4];
    float falling_score_offset_y[4];
    s16 rising_score_timer[4];
    s16 falling_score_timer[4];
    s16 falling_score_value[4];
} M401ScoreHudWork;

void set_score_hud_visible(s16 is_visible)
{
    M401ScoreHudWork *display_work;
    s32 i;
    s32 j;
    display_work = score_hud_object->data;
    if (is_visible) {
        for (i = 0; i < 4; i++) {
            espDispOn(display_work->player_portrait_sprites[i]);
            espDispOn(display_work->player_status_sprites[i]);
            espDispOn(display_work->player_status_shadow_sprites[i]);
            for (j = 0; j < 2; j++) {
                espDispOn(display_work->score_digit_sprites[i][j]);
            }
        }
    }
    else {
        for (i = 0; i < 4; i++) {
            espDispOff(display_work->player_portrait_sprites[i]);
            espDispOff(display_work->player_status_sprites[i]);
            espDispOff(display_work->player_status_shadow_sprites[i]);
            for (j = 0; j < 2; j++) {
                espDispOff(display_work->score_digit_sprites[i][j]);
            }
        }
    }
}

s32 player_portrait_asset_ids[] = {
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x00),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x01),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x02),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x03),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x04),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x05),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x06),
    DATA_MAKE_NUM(DATADIR_MGCONST, 0x07),
};

#define PLAYER_POS_X(index, left, width) ((((index)&1) * width) + left)
#define PLAYER_POS_Y(index, top, height) ((((index) > 1) * height) + top)

void create_score_hud(OMOBJ *object)
{
    M401ScoreHudWork *display_work;
    s32 i;
    s32 j;
    object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M401ScoreHudWork), HU_MEMNUM_OVL);
    display_work = object->data;
    for (i = 0; i < 4; i++) {
        display_work->player_portrait_sprites[i] = espEntry(player_portrait_asset_ids[GWPlayerCfg[i].character], 2, 0);
        espDispOff(display_work->player_portrait_sprites[i]);
        espDrawNoSet(display_work->player_portrait_sprites[i], 0);
        espPosSet(display_work->player_portrait_sprites[i], PLAYER_POS_X(i, 37, 438), PLAYER_POS_Y(i, 59, 358));
        display_work->player_status_sprites[i] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2F), 3, 0);
        espDispOff(display_work->player_status_sprites[i]);
        espDrawNoSet(display_work->player_status_sprites[i], 0);
        espPosSet(display_work->player_status_sprites[i], PLAYER_POS_X(i, 73, 438), PLAYER_POS_Y(i, 61, 358));
        display_work->player_status_shadow_sprites[i] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x30), 4, 0);
        espDispOff(display_work->player_status_shadow_sprites[i]);
        espDrawNoSet(display_work->player_status_shadow_sprites[i], 0);
        espPosSet(display_work->player_status_shadow_sprites[i], PLAYER_POS_X(i, 73, 438), PLAYER_POS_Y(i, 61, 358));
        espColorSet(display_work->player_status_shadow_sprites[i], 0, 0, 0);
        espTPLvlSet(display_work->player_status_shadow_sprites[i], 0.5f);
        for (j = 0; j < 2; j++) {
            display_work->score_digit_sprites[i][j] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2E), 1, 0);
            espDispOff(display_work->score_digit_sprites[i][j]);
            espDrawNoSet(display_work->score_digit_sprites[i][j], 0);
            espPosSet(display_work->score_digit_sprites[i][j], PLAYER_POS_X(i, 69 + (j * 20), 438), PLAYER_POS_Y(i, 63, 358));
            espAttrSet(display_work->score_digit_sprites[i][j], HUSPR_ATTR_NOANIM);
        }
        for (j = 0; j < 3; j++) {
            display_work->rising_score_sprites[i][j] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2D), 0, 0);
            espDispOff(display_work->rising_score_sprites[i][j]);
            espDrawNoSet(display_work->rising_score_sprites[i][j], 0);
            espAttrSet(display_work->rising_score_sprites[i][j], HUSPR_ATTR_NOANIM);
            display_work->falling_score_sprites[i][j] = espEntry(DATA_MAKE_NUM(DATADIR_M401, 0x2D), 0, 0);
            espDispOff(display_work->falling_score_sprites[i][j]);
            espDrawNoSet(display_work->falling_score_sprites[i][j], 0);
            espAttrSet(display_work->falling_score_sprites[i][j], HUSPR_ATTR_NOANIM);
        }
        espBankSet(display_work->rising_score_sprites[i][0], 10);
        espBankSet(display_work->falling_score_sprites[i][0], 11);
        display_work->rising_score_alpha[i] = 1.0f;
        display_work->falling_score_alpha[i] = 1.0f;
        display_work->rising_score_timer[i] = 0;
        display_work->falling_score_timer[i] = 0;
    }
    object->objFunc = update_score_popups;
}

void update_player_score_digits(s16 player_index);

void update_score_popups(OMOBJ *object)
{
    M401ScoreHudWork *display_work;
    s32 i;
    s32 j;
    OMOBJ *player_object;
    Vec world_position;
    Vec screen_position;
    M401WorkPlayer *player_work;
    display_work = object->data;
    for (i = 0; i < 4; i++) {
        player_work = player_objects[i]->data;
        if (display_work->rising_score_timer[i]) {
            player_object = player_objects[i];
            world_position.x = player_object->trans.x;
            world_position.y = player_object->trans.y;
            world_position.z = player_object->trans.z;
            project_world_position_to_screen(&world_position, &screen_position);
            for (j = 0; j < 3; j++) {
                espPosSet(display_work->rising_score_sprites[i][j], (-20.0f + screen_position.x + display_work->rising_score_offset_x[i]) + (j * 16), 20.0f + screen_position.y + display_work->rising_score_offset_y[i]);
                espTPLvlSet(display_work->rising_score_sprites[i][j], display_work->rising_score_alpha[i]);
            }
            display_work->rising_score_base_y[i] -= 0.5f;
            display_work->rising_score_offset_y[i] -= 1.0f;
            if (display_work->rising_score_timer[i] < 15) {
                display_work->rising_score_alpha[i] -= 1.0f / 15.0f;
            }
            if (--display_work->rising_score_timer[i] == 0) {
                espDispOff(display_work->rising_score_sprites[i][0]);
                espDispOff(display_work->rising_score_sprites[i][1]);
            }
        }
        if (display_work->falling_score_timer[i]) {
            player_object = player_objects[i];
            world_position.x = player_object->trans.x;
            world_position.y = player_object->trans.y;
            world_position.z = player_object->trans.z;
            project_world_position_to_screen(&world_position, &screen_position);
            for (j = 0; j < 2; j++) {
                espPosSet(display_work->falling_score_sprites[i][j], (-20.0f + screen_position.x + display_work->falling_score_offset_x[i]) + (j * 16), -20.0f + screen_position.y + display_work->falling_score_offset_y[i]);
                espTPLvlSet(display_work->falling_score_sprites[i][j], display_work->falling_score_alpha[i]);
            }
            display_work->falling_score_base_y[i] += 0.5f;
            display_work->falling_score_offset_y[i] += 1.0f;
            if (display_work->falling_score_timer[i] < 15) {
                display_work->falling_score_alpha[i] -= 1.0f / 15.0f;
            }
            if (--display_work->falling_score_timer[i] == 0) {
                espDispOff(display_work->falling_score_sprites[i][0]);
                espDispOff(display_work->falling_score_sprites[i][1]);
            }
        }
        update_player_score_digits(i);
    }
}

void update_player_score_digits(s16 player_index)
{
    M401ScoreHudWork *display_work;
    s32 score_value;
    M401WorkPlayer *player_work;
    display_work = score_hud_object->data;
    player_work = player_objects[player_index]->data;
    score_value = player_work->score;
    espBankSet(display_work->score_digit_sprites[player_index][0], score_value / 10);
    espBankSet(display_work->score_digit_sprites[player_index][1], score_value % 10);
}

void show_score_gain_popup(s16 player_index)
{
    M401ScoreHudWork *display_work;
    s32 i;
    M401WorkPlayer *player_work;
    display_work = score_hud_object->data;
    player_work = player_objects[player_index]->data;
    for (i = 0; i < 2; i++) {
        espDispOn(display_work->rising_score_sprites[player_index][i]);
    }
    display_work->rising_score_alpha[player_index] = 1;
    display_work->rising_score_base_y[player_index] = PLAYER_POS_Y(player_index, 52, 398);
    display_work->rising_score_base_x[player_index] = PLAYER_POS_X(player_index, 41, 442);
    display_work->rising_score_offset_y[player_index] = 0;
    display_work->rising_score_offset_x[player_index] = 0;
    espBankSet(display_work->rising_score_sprites[player_index][1], player_work->score_popup_value);
    display_work->rising_score_timer[player_index] = 45;
}

void show_score_loss_popup(s16 player_index, s16 score_loss)
{
    M401ScoreHudWork *display_work;
    M401WorkPlayer *player_work;
    s32 i;
    display_work = score_hud_object->data;
    player_work = player_objects[player_index]->data;
    for (i = 0; i < 2; i++) {
        espDispOn(display_work->falling_score_sprites[player_index][i]);
    }
    display_work->falling_score_alpha[player_index] = 1;
    display_work->falling_score_base_y[player_index] = PLAYER_POS_Y(player_index, 20, 398);
    display_work->falling_score_base_x[player_index] = PLAYER_POS_X(player_index, 41, 442);
    display_work->falling_score_offset_y[player_index] = 0;
    display_work->falling_score_offset_x[player_index] = 0;
    espBankSet(display_work->falling_score_sprites[player_index][1], score_loss);
    display_work->falling_score_timer[player_index] = 45;
    display_work->falling_score_value[player_index] = score_loss;
    player_work->score -= score_loss;
    if (player_work->score < 0) {
        player_work->score = 0;
    }
}

float stage_event_start_distances[] = { -500, -8500, -17500, -26500, -99000 };

float stage_event_end_distances[] = { -9100, -18100, -27100, -36100, -45100, -100000 };

void setup_scene_section_one(OMOBJ *object);
void setup_scene_section_two(OMOBJ *object);
void setup_scene_section_three(OMOBJ *object);
void setup_scene_section_four(OMOBJ *object);
void setup_scene_section_five(OMOBJ *object);
void cleanup_scene_section_one(OMOBJ *object);
void cleanup_scene_section_two(OMOBJ *object);
void cleanup_scene_section_three(OMOBJ *object);
void cleanup_scene_section_four(OMOBJ *object);
void cleanup_scene_section_five(OMOBJ *object);

OMOBJFUNC stage_event_callbacks[][2] = { setup_scene_section_one, cleanup_scene_section_one, setup_scene_section_two, cleanup_scene_section_two, setup_scene_section_three, cleanup_scene_section_three, setup_scene_section_four, cleanup_scene_section_four, setup_scene_section_five, cleanup_scene_section_five };

char *stage_model_resource_names[] = { "kaitei01", "kaitei02", "kaitei03", "kaitei04", "kaitei05" };

s32 player_motion_resource_ids[] = {
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
    DATA_MAKE_NUM(DATADIR_MARIO, 0x02),
};

OMOBJ *create_flocking_particle_effect(s16 particle_count, Vec *spawn_origin, Vec *spawn_radius, Vec *effect_origin);
void set_flocking_particle_weights(OMOBJ *object, float separation_weight, float obstacle_weight, float alignment_weight, float cohesion_weight, float origin_weight);

void setup_scene_section_one(OMOBJ *object)
{
    Vec model_position;
    Vec model_scale;
    Vec particle_position;
    HSFOBJECT *model_object_data = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[0]);
    OMOBJ *particle_object;
    model_object_data->type = 2;
    model_position.x = -2500;
    model_position.y = 150;
    model_position.z = -6800;
    model_scale.x = 50;
    model_scale.y = 50;
    model_scale.z = 50;
    particle_position.x = 1500;
    particle_position.y = 150;
    particle_position.z = -4800;
    particle_object = create_flocking_particle_effect(18, &model_position, &model_scale, &particle_position);
    set_flocking_particle_weights((OMOBJ *)particle_object->work[0], 5, 1.5, 0.2, 0.8, 3);
}

void setup_scene_section_two(OMOBJ *object)
{
    Vec model_position;
    Vec model_scale;
    OMOBJ *particle_object;
    HSFOBJECT *model_object_data = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[1]);
    model_object_data->type = 2;
    model_position.x = -1000;
    model_position.y = 0;
    model_position.z = -9100;
    model_scale.x = 150;
    model_scale.y = 100;
    model_scale.z = 100;
    particle_object = create_flocking_particle_effect(14, &model_position, &model_scale, &model_position);
    omSetRot(particle_object, 3, 0, 0);
    omSetSca(particle_object, 0, 0, 50);
    set_flocking_particle_weights((OMOBJ *)particle_object->work[0], 4.5, 2.5, 0.08, 0.9, 1);
}

void setup_scene_section_three(OMOBJ *object)
{
    Vec model_position;
    Vec model_scale;
    Vec particle_position;
    HSFOBJECT *model_object_data = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[2]);
    model_object_data->type = 2;
    model_position.x = 500;
    model_position.y = 0;
    model_position.z = -24300;
    model_scale.x = 200;
    model_scale.y = 100;
    model_scale.z = 100;
    particle_position.x = 1000;
    particle_position.y = 0;
    particle_position.z = -16300;
    create_flocking_particle_effect(40, &model_position, &model_scale, &particle_position);
}

void start_orbiting_object(OMOBJ *object, Vec *pos);

void setup_scene_section_four(OMOBJ *object)
{
    Vec particle_position;
    Vec model_scale;
    Vec model_position;
    Vec audio_emitter_position;
    OMOBJ *particle_object;
    HSFOBJECT *model_object_data = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[3]);
    model_object_data->type = 2;
    particle_position.x = 0;
    particle_position.y = -150.0f + ((1.0f / 255.0f) * (300.0f * frandu8()));
    particle_position.z = -23000;
    start_orbiting_object(orbiting_scene_objects[0], &particle_position);
    particle_position.x = 0;
    particle_position.y = -150.0f + ((1.0f / 255.0f) * (300.0f * frandu8()));
    particle_position.z = -25000;
    start_orbiting_object(orbiting_scene_objects[1], &particle_position);
    particle_position.x = 5500;
    particle_position.y = 0;
    particle_position.z = -29800;
    model_scale.x = 100;
    model_scale.y = 100;
    model_scale.z = 100;
    model_position.x = -1500;
    model_position.y = 0;
    model_position.z = -24900;
    particle_object = create_flocking_particle_effect(20, &particle_position, &model_scale, &model_position);
    set_flocking_particle_weights((OMOBJ *)particle_object->work[0], 6, 1.5f, 0.2f, 0.8f, 3.5f);
    audio_emitter_position.x = -650;
    audio_emitter_position.y = -360;
    audio_emitter_position.z = -26300;
    stage_particle_effect_c = create_score_particle_effect(&audio_emitter_position, 3);
    ambient_sound_emitter_handles[0] = HuAudFXEmiterPlay(1291, &audio_emitter_position);
}

void setup_scene_section_five(OMOBJ *object)
{
    Vec audio_emitter_position;
    HSFOBJECT *model_object_data = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[4]);
    model_object_data->type = 2;
    Hu3DModelAttrReset(object->mdlId[7], HU3D_ATTR_DISPOFF);
    audio_emitter_position.x = 0;
    audio_emitter_position.y = -370;
    audio_emitter_position.z = -43000;
    unused_object_handle_8 = create_score_particle_effect(&audio_emitter_position, 3);
    ambient_sound_emitter_handles[1] = HuAudFXEmiterPlay(1291, &audio_emitter_position);
    audio_emitter_position.x = 380;
    audio_emitter_position.y = -440;
    audio_emitter_position.z = -32000;
    stage_particle_effect_d = create_score_particle_effect(&audio_emitter_position, 3);
    ambient_sound_emitter_handles[2] = HuAudFXEmiterPlay(1291, &audio_emitter_position);
    Hu3DModelAttrReset(object->mdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[2], HU3D_CLUSTER_ATTR_LOOP);
}

void configure_stage_scene(OMOBJ *object)
{
    Vec camera_direction;
    Vec camera_position;
    Vec audio_emitter_position;
    Vec particle_position;
    s32 particle_index;
    HSFOBJECT *model_object_data = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[0]);
    s32 particle_count;
    model_object_data->type = 2;
    Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(object->mdlId[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->mdlId[1], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(object->mdlId[3], HU3D_ATTR_DISPOFF);
    active_camera_position.x = 0;
    active_camera_position.y = 100;
    active_camera_position.z = 0;
    active_camera_target.x = 0;
    active_camera_target.y = 1000;
    active_camera_target.z = -1500;
    camera_up_vector.x = 0;
    camera_up_vector.y = 1;
    camera_up_vector.z = 0;
    Hu3DCameraPosSetV(1, &active_camera_position, &camera_up_vector, &active_camera_target);
    Hu3DCameraPerspectiveSet(1, camera_field_of_view, camera_near_plane, camera_far_plane, 1.2f);
    previous_camera_position = active_camera_position;
    capture_camera_state(NULL);
    camera_position = active_camera_position;
    VECSubtract(&active_camera_target, &active_camera_position, &camera_direction);
    VECNormalize(&camera_direction, &camera_direction);
    HuAudFXListnerSetEX(&camera_position, &camera_direction, sound_emitter_max_distance, sound_emitter_far_distance, 300, 300, 300);
    audio_emitter_position.x = 300;
    audio_emitter_position.y = -450;
    audio_emitter_position.z = -3100;
    stage_particle_effect_a = create_score_particle_effect(&audio_emitter_position, 3);
    ambient_sound_emitter_handles[0] = HuAudFXEmiterPlay(1291, &audio_emitter_position);
    audio_emitter_position.x = -300;
    audio_emitter_position.y = -340;
    audio_emitter_position.z = -4720;
    stage_particle_effect_b = create_score_particle_effect(&audio_emitter_position, 3);
    ambient_sound_emitter_handles[1] = HuAudFXEmiterPlay(1291, &audio_emitter_position);
    Hu3DModelAttrReset(object->mdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[2], HU3D_CLUSTER_ATTR_LOOP);
    particle_count = 4;
    for (particle_index = 0; particle_index < particle_count; particle_index++) {
        particle_position.x = -340.0f + ((1.0f / 255.0f) * (680.0f * frandu8()));
        particle_position.y = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
        particle_position.z = ((-1550.0f - (particle_index * 260)) - 40.0f) + ((1.0f / 255.0f) * (80.0f * frandu8()));
        create_score_particle_effect(&particle_position, 0);
    }
}

typedef struct tunnel_scene_work {
    s32 intro_triggered;
    float bridge_vertical_offset;
    Vec bridge_motion_state;
    Vec side_model_positions[2];
    s16 particle_spawn_timer;
} TunnelSceneWork;

void configure_tunnel_scene(OMOBJ *object)
{
    Vec camera_position;
    Vec camera_target;
    Vec audio_emitter_position;
    Vec particle_position;
    TunnelSceneWork *tunnel_work;
    s32 model_index;
    Hu3DModelAttrReset(object->mdlId[4], HU3D_ATTR_DISPOFF);
    Hu3DModelClusterAttrSet(object->mdlId[4], 0, 0xC0000001);
    Hu3DModelAttrReset(object->mdlId[8], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[8], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->mdlId[4], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowMapSet(object->mdlId[4]);
    Hu3DModelAttrReset(object->mdlId[5], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(object->mdlId[4], 0, 0, 0);
    Hu3DModelAmbSet(object->mdlId[4], 1, 1, 1);
    Hu3DModelPosSet(object->mdlId[5], 0, 0, 0);
    Hu3DModelPosSet(object->mdlId[6], 0, 0, 0);
    tunnel_work = tunnel_scene_object->data;
    if (winner_count) {
        tunnel_work->side_model_positions[0].x = 210;
        tunnel_work->side_model_positions[0].y = 1018;
        tunnel_work->side_model_positions[0].z = 0;
        tunnel_work->side_model_positions[1].x = -160;
        tunnel_work->side_model_positions[1].y = 1020;
        tunnel_work->side_model_positions[1].z = -50;
        for (model_index = 0; model_index < 2; model_index++) {
            Hu3DModelPosSet(object->mdlId[model_index + 9], tunnel_work->side_model_positions[model_index].x, tunnel_work->side_model_positions[model_index].y, tunnel_work->side_model_positions[model_index].z);
            Hu3DModelAttrReset(object->mdlId[model_index + 9], HU3D_ATTR_DISPOFF);
        }
        Hu3DMotionSet(object->mdlId[10], object->mtnId[0]);
        Hu3DMotionSet(object->mdlId[9], object->mtnId[2]);
    }
    else {
        tunnel_work->side_model_positions[0].x = 210;
        tunnel_work->side_model_positions[0].y = 1018;
        tunnel_work->side_model_positions[0].z = 0;
        tunnel_work->side_model_positions[1].x = -160;
        tunnel_work->side_model_positions[1].y = 1020;
        tunnel_work->side_model_positions[1].z = -50;
        for (model_index = 0; model_index < 2; model_index++) {
            Hu3DModelPosSet(object->mdlId[model_index + 9], tunnel_work->side_model_positions[model_index].x, tunnel_work->side_model_positions[model_index].y, tunnel_work->side_model_positions[model_index].z);
            Hu3DModelAttrReset(object->mdlId[model_index + 9], HU3D_ATTR_DISPOFF);
        }
        Hu3DMotionSet(object->mdlId[10], object->mtnId[1]);
        Hu3DMotionSet(object->mdlId[9], object->mtnId[2]);
    }
    Hu3DModelAttrSet(object->mdlId[9], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->mdlId[10], HU3D_MOTATTR_LOOP);
    Hu3DModelRotSet(object->mdlId[9], 0, 90, 0);
    Hu3DModelPosSet(object->mdlId[11], 210, 1018, 0);
    Hu3DModelRotSet(object->mdlId[11], 0, 90, 0);
    Hu3DModelAttrReset(object->mdlId[11], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[11], HU3D_MOTATTR_LOOP);
    camera_position.x = 0;
    camera_position.y = 1300;
    camera_position.z = 1300;
    camera_target.x = 0;
    camera_target.y = 920;
    camera_target.z = -100;
    audio_emitter_position.x = 0;
    audio_emitter_position.y = 1;
    audio_emitter_position.z = 0;
    Hu3DCameraPosSetV(1, &camera_position, &audio_emitter_position, &camera_target);
    camera_field_of_view = 45;
    Hu3DShadowData.fov = camera_field_of_view;
    MTXLightPerspective(Hu3DShadowData.projMtx, camera_field_of_view, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    Hu3DCameraPerspectiveSet(1, camera_field_of_view, camera_near_plane, camera_far_plane, 1.2f);
    VECSubtract(&camera_target, &camera_position, &particle_position);
    VECNormalize(&particle_position, &particle_position);
    HuAudFXListnerUpdate(&camera_position, &particle_position);
}

void cleanup_scene_section_one(OMOBJ *object)
{
    HSFOBJECT *temp_r30 = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[0]);
    temp_r30->type = -1;
    Hu3DModelAttrSet(object->mdlId[3], HU3D_ATTR_DISPOFF);
    stage_particle_effect_a->work[0] = 1;
    Hu3DModelAttrSet(object->mdlId[2], HU3D_ATTR_DISPOFF);
    HuAudFXStop(ambient_sound_emitter_handles[0]);
    HuAudFXStop(ambient_sound_emitter_handles[1]);
}

void cleanup_scene_section_two(OMOBJ *object)
{
    HSFOBJECT *temp_r31 = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[1]);
    temp_r31->type = -1;
    stage_particle_effect_b->work[0] = 1;
}

void cleanup_scene_section_three(OMOBJ *object)
{
    HSFOBJECT *temp_r31 = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[2]);
    temp_r31->type = -1;
}

void cleanup_scene_section_four(OMOBJ *object)
{
    HSFOBJECT *temp_r30 = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[3]);
    temp_r30->type = -1;
    Hu3DModelAttrSet(orbiting_scene_objects[0]->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(orbiting_scene_objects[1]->mdlId[0], HU3D_ATTR_DISPOFF);
    stage_particle_effect_c->work[0] = 1;
    HuAudFXStop(ambient_sound_emitter_handles[0]);
}

void cleanup_scene_section_five(OMOBJ *object)
{
    HSFOBJECT *temp_r30 = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[4]);
    temp_r30->type = -1;
    Hu3DModelAttrSet(object->mdlId[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    unused_object_handle_8->work[0] = 1;
    stage_particle_effect_d->work[0] = 1;
    Hu3DModelAttrSet(object->mdlId[2], HU3D_ATTR_DISPOFF);
    HuAudFXStop(ambient_sound_emitter_handles[1]);
    HuAudFXStop(ambient_sound_emitter_handles[2]);
}

void empty_object_callback(OMOBJ *object) { }

void empty_process_callback(OMOBJ *object) { }

void update_tunnel_prop(OMOBJ *object);

void create_tunnel_scene(OMOBJ *object)
{
    TunnelSceneWork *tunnel_work;
    s32 model_index;
    HSFOBJECT *model_object;
    object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(TunnelSceneWork), HU_MEMNUM_OVL);
    tunnel_work = object->data;
    capture_camera_state(NULL);
    tunnel_work->intro_triggered = 0;
    tunnel_work->bridge_motion_state.x = 0;
    tunnel_work->bridge_motion_state.y = 0;
    tunnel_work->bridge_motion_state.z = 0;
    tunnel_work->particle_spawn_timer = 0;
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x00));
    Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    object->mdlId[1] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x01));
    Hu3DModelAttrSet(object->mdlId[1], HU3D_ATTR_DISPOFF);
    object->mdlId[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x07));
    Hu3DModelAttrSet(object->mdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[2], HU3D_MOTATTR_LOOP);
    object->mdlId[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x1F));
    Hu3DModelAttrSet(object->mdlId[3], HU3D_ATTR_DISPOFF);
    object->mdlId[4] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x20));
    Hu3DModelAttrSet(object->mdlId[4], HU3D_ATTR_DISPOFF);
    object->mdlId[11] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x2C));
    Hu3DModelAttrSet(object->mdlId[11], HU3D_ATTR_DISPOFF);
    object->mdlId[7] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x03));
    Hu3DModelAttrSet(object->mdlId[7], HU3D_ATTR_DISPOFF);
    object->mdlId[8] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x23));
    Hu3DModelAttrSet(object->mdlId[8], HU3D_ATTR_DISPOFF);
    object->mdlId[9] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x28));
    Hu3DModelAttrSet(object->mdlId[9], HU3D_ATTR_DISPOFF);
    object->mdlId[10] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x28));
    Hu3DModelAttrSet(object->mdlId[10], HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(object->mdlId[10]);
    object->mdlId[5] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x21));
    Hu3DModelAttrSet(object->mdlId[5], HU3D_ATTR_DISPOFF);
    object->mdlId[6] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x22));
    Hu3DModelAttrSet(object->mdlId[6], HU3D_ATTR_DISPOFF);
    object->mtnId[0] = Hu3DJointMotionFile(object->mdlId[10], DATA_MAKE_NUM(DATADIR_M401, 0x29));
    object->mtnId[1] = Hu3DJointMotionFile(object->mdlId[10], DATA_MAKE_NUM(DATADIR_M401, 0x2A));
    object->mtnId[2] = Hu3DJointMotionFile(object->mdlId[9], DATA_MAKE_NUM(DATADIR_M401, 0x2B));
    Hu3DModelPosSet(object->mdlId[1], 0, 0, -1500);
    Hu3DModelShadowMapSet(object->mdlId[0]);
    for (model_index = 0; model_index < 5; model_index++) {
        model_object = Hu3DModelObjPtrGet(object->mdlId[0], stage_model_resource_names[model_index]);
        model_object->type = -1;
    }
    configure_stage_scene(object);
    object->objFunc = update_tunnel_prop;
}

void update_tunnel_prop(OMOBJ *object)
{
    Hu3DModelPosSet(object->mdlId[3], 110, 5.0 * sind(obstacle_rotation_angle), -1500);
    obstacle_rotation_angle += 2.0f;
    if (obstacle_rotation_angle >= 360.0f) {
        obstacle_rotation_angle -= 360.0f;
    }
}

void initialize_projectile_distribution(float minimum_spacing, float maximum_spacing);

void update_tunnel_scene_events(OMOBJ *object)
{
    Vec particle_position;
    TunnelSceneWork *tunnel_work;
    s32 particle_index;
    s32 particle_count;
    tunnel_work = object->data;
    if (camera_target.z < -5000.0f && tunnel_work->intro_triggered == 0) {
        tunnel_work->intro_triggered = 1;
        initialize_projectile_distribution(-15500, -20000);
    }
    if (camera_position.z <= stage_event_start_distances[stage_segment_index]) {
        stage_segment_index++;
        stage_event_callbacks[stage_segment_index][0](object);
    }
    if (camera_position.z <= stage_event_end_distances[stage_section_index]) {
        stage_event_callbacks[stage_section_index][1](object);
        stage_section_index++;
    }
    if (camera_position.z <= -40000.0f) {
        minigame_exit_ready = 1;
    }
    if (tunnel_work->particle_spawn_timer) {
        tunnel_work->particle_spawn_timer--;
    }
    else {
        tunnel_work->particle_spawn_timer = 274;
        if (camera_target.z > -31260.0f) {
            particle_count = 4;
            for (particle_index = 0; particle_index < particle_count; particle_index++) {
                particle_position.x = -340.0f + ((1.0f / 255.0f) * (680.0f * frandu8()));
                particle_position.y = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
                particle_position.z = ((-4000.0f - (particle_index * 240)) - 40.0f) + ((1.0f / 255.0f) * (80.0f * frandu8()));
                create_score_particle_effect(&particle_position, 0);
            }
        }
    }
}

void update_bridge_scene(OMOBJ *object)
{
    TunnelSceneWork *tunnel_work;
    s32 model_index;
    float model_height;
    tunnel_work = object->data;
    tunnel_work->bridge_vertical_offset = 5.0 * sind(tunnel_work->bridge_motion_state.x);
    tunnel_work->bridge_motion_state.y += tunnel_work->bridge_motion_state.z;
    Hu3DModelPosSet(object->mdlId[4], tunnel_work->bridge_motion_state.y, tunnel_work->bridge_vertical_offset, 0);
    Hu3DModelPosSet(object->mdlId[5], tunnel_work->bridge_motion_state.y, 0, 0);
    Hu3DModelScaleSet(object->mdlId[5], 1.0f - (0.09f * (tunnel_work->bridge_vertical_offset / 5.0f)), 1.0f, 1.0f - (0.09f * (tunnel_work->bridge_vertical_offset / 5.0f)));
    for (model_index = 0; model_index < 2; model_index++) {
        model_height = tunnel_work->side_model_positions[model_index].y + (5.0 * sind(tunnel_work->bridge_motion_state.x));
        tunnel_work->side_model_positions[model_index].x += tunnel_work->bridge_motion_state.z;
        Hu3DModelPosSet(object->mdlId[model_index + 9], tunnel_work->side_model_positions[model_index].x, model_height, tunnel_work->side_model_positions[model_index].z);
    }
    Hu3DModelPosSet(object->mdlId[11], tunnel_work->side_model_positions[0].x, model_height, tunnel_work->side_model_positions[0].z);
    tunnel_work->bridge_motion_state.z *= 1.04f;
    if (tunnel_work->bridge_motion_state.z > 12.0f) {
        tunnel_work->bridge_motion_state.z = 12.0f;
    }
    tunnel_work->bridge_motion_state.x += 2.0f;
    if (tunnel_work->bridge_motion_state.x >= 360.0f) {
        tunnel_work->bridge_motion_state.x -= 360.0f;
    }
    shadow_light_position.x = tunnel_work->bridge_motion_state.y;
    shadow_light_target.x = tunnel_work->bridge_motion_state.y;
    Hu3DShadowPosSet(&shadow_light_position, &shadow_light_up_vector, &shadow_light_target);
}

void update_player_intro(OMOBJ *object);

s32 player_motion_lookup[][10] = {
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x31),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x39),
    DATA_MAKE_NUM(DATADIR_M401, 0x41),
    DATA_MAKE_NUM(DATADIR_MARIOMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x49),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x32),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3A),
    DATA_MAKE_NUM(DATADIR_M401, 0x42),
    DATA_MAKE_NUM(DATADIR_LUIGIMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4A),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x33),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3B),
    DATA_MAKE_NUM(DATADIR_M401, 0x43),
    DATA_MAKE_NUM(DATADIR_PEACHMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4B),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x34),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3C),
    DATA_MAKE_NUM(DATADIR_M401, 0x44),
    DATA_MAKE_NUM(DATADIR_YOSHIMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4C),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x35),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3D),
    DATA_MAKE_NUM(DATADIR_M401, 0x45),
    DATA_MAKE_NUM(DATADIR_WARIOMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4D),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x36),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3E),
    DATA_MAKE_NUM(DATADIR_M401, 0x46),
    DATA_MAKE_NUM(DATADIR_DONKEYMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4E),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x37),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x3F),
    DATA_MAKE_NUM(DATADIR_M401, 0x47),
    DATA_MAKE_NUM(DATADIR_DAISYMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x4F),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x2A),
    DATA_MAKE_NUM(DATADIR_M401, 0x38),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x00),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x2B),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x05),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x17),
    DATA_MAKE_NUM(DATADIR_M401, 0x40),
    DATA_MAKE_NUM(DATADIR_M401, 0x48),
    DATA_MAKE_NUM(DATADIR_WALUIGIMOT, 0x22),
    DATA_MAKE_NUM(DATADIR_M401, 0x50),
};

Vec player_spawn_positions[] = {
    -150,
    1250,
    -1400,
    -50,
    1250,
    -1400,
    50,
    1250,
    -1400,
    150,
    1250,
    -1400,
};

Vec player_target_positions[] = {
    -300,
    0,
    -1500,
    -100,
    0,
    -1500,
    100,
    0,
    -1500,
    300,
    0,
    -1500,
};

void update_player_intro(OMOBJ *object);

void create_player(OMOBJ *object)
{
    M401WorkPlayer *player_work;
    s32 player_index;
    s32 motion_index;
    s32 character_index;
    object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M401WorkPlayer), HU_MEMNUM_OVL);
    player_work = object->data;
    player_index = object->work[0];
    player_work->player_index = player_index;
    player_work->controller_index = GWPlayerCfg[player_index].pad_idx;
    character_index = GWPlayerCfg[player_index].character;
    player_work->character_model_index = player_character_model_indices[character_index];
    object->mdlId[0] = CharModelCreate(player_work->character_model_index, 4);
    if (player_index == 0) {
        object->mdlId[2] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x25));
        object->mdlId[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x27));
    }
    else {
        object->mdlId[2] = Hu3DModelLink(player_objects[0]->mdlId[2]);
        object->mdlId[3] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x27));
    }
    Hu3DModelAttrSet(object->mdlId[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelClusterAttrSet(object->mdlId[3], 0, 0xC0000002);
    Hu3DModelLayerSet(object->mdlId[3], 7);
    for (motion_index = 0; motion_index < 10; motion_index++) {
        object->mtnId[motion_index] = CharMotionCreate(player_character_model_indices[character_index], player_motion_lookup[character_index][motion_index]);
    }
    CharMotionSet(player_work->character_model_index, object->mtnId[2]);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->mdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[2], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(object->mdlId[2], 2);
    Hu3DModelAmbSet(object->mdlId[0], 1, 1, 1);
    Hu3DModelShadowSet(object->mdlId[0]);
    CharMotionVoiceOnSet(player_character_model_indices[character_index], object->mtnId[4], 0);
    player_work->world_position = player_target_positions[player_index];
    player_work->movement_parameters.z = 0;
    omSetTra(object, player_spawn_positions[player_index].x, player_spawn_positions[player_index].y, player_spawn_positions[player_index].z);
    player_work->player_state = 0;
    player_work->state_timer = 70;
    player_work->target_position.x = player_target_positions[player_index].x;
    player_work->target_position.y = player_target_positions[player_index].y;
    player_work->target_position.z = 800 + player_target_positions[player_index].z;
    player_work->is_walking = 0;
    player_work->score = 0;
    player_work->score_popup_value = 0;
    player_work->is_stunned = 0;
    player_work->stun_timer = 0;
    player_work->ai_decision_timer = 0;
    player_work->reserved_state_76 = 0;
    player_work->jump_velocity = 0;
    player_work->collision_cooldown = 0;
    player_work->run_timer = 0;
    player_work->idle_timer = 0;
    player_work->reserved_vector_94.x = player_work->reserved_vector_94.y = player_work->reserved_vector_94.z = 0;
    player_work->ai_input_cooldown = 0;
    player_work->reserved_byte_a0 = player_work->reserved_byte_a1 = 0;
    CharMotionDataClose(player_work->character_model_index);
    object->objFunc = update_player_intro;
}

void update_player_effect_anchor(OMOBJ *object);
void update_camera_transition(OMOBJ *object);

void update_player_intro(OMOBJ *object)
{
    Vec target_direction;
    Vec normalized_direction;
    Vec movement_direction;
    M401WorkPlayer *player_work;
    HU3DCAMERA *camera;
    OMOBJ *particle_object;
    ScoreParticleWork *particle_work;
    float speed;
    player_work = object->data;
    switch (player_work->player_state) {
        case 0:
            if (--player_work->state_timer == 0) {
                player_work->player_state = 1;
                CharMotionShiftSet(player_work->character_model_index, object->mtnId[4], 0, 20, HU3D_MOTATTR_NONE);
                player_work->movement_parameters.x = 16;
                player_work->movement_parameters.y = 0;
            }
            break;

        case 1:
            if (object->trans.y < 1100) {
                player_work->player_state = 2;
                speed = VECMagPoint(object->trans.x - player_work->target_position.x, object->trans.y - player_work->target_position.y, object->trans.z - player_work->target_position.z);
                player_work->movement_parameters.z = speed;
                player_work->movement_parameters.y = 0;
                player_work->state_timer = 110;
                particle_object = create_score_particle_effect(&player_spawn_positions[player_work->player_index], 2);
                player_work->score_effect = particle_object;
                particle_work = particle_object->data;
                particle_work->owner_object = object;
                update_player_effect_anchor(object);
                particle_object = create_score_particle_effect(&player_spawn_positions[player_work->player_index], 4);
                particle_work = particle_object->data;
                particle_work->owner_object = object;
                player_work->landing_effect = particle_object;
                particle_object = create_score_particle_effect(&player_spawn_positions[player_work->player_index], 5);
                particle_work = particle_object->data;
                particle_work->owner_object = object;
                player_work->trail_effect = particle_object;
                CharMotionShiftSet(player_work->character_model_index, object->mtnId[1], 0, 80, HU3D_MOTATTR_LOOP);
                player_work->movement_origin.x = object->trans.x;
                player_work->movement_origin.y = object->trans.y;
                player_work->movement_origin.z = object->trans.z;
                Hu3DModelAttrReset(object->mdlId[3], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(object->mdlId[3], HU3D_MOTATTR_PAUSE);
                Hu3DModelClusterAttrReset(object->mdlId[3], 0, 0xC0000002);
                Hu3DModelPosSet(object->mdlId[3], object->trans.x, 100, 100 + object->trans.z);
                Hu3DMotionTimeSet(object->mdlId[3], 0);
                if (player_work->player_index == 0) {
                    HuAudFXPlay(1281);
                }
                omVibrate(player_work->player_index, 12, 4, 2);
            }
            else {
                object->trans.y += player_work->movement_parameters.x - (0.07f * player_work->movement_parameters.y * player_work->movement_parameters.y);
                object->trans.z += 2.0f;
                player_work->movement_parameters.y += 1.0f;
            }
            break;

        case 2:
            camera = &Hu3DCamera[0];
            normalized_direction = player_work->target_position;
            movement_direction = player_work->movement_origin;
            VECSubtract(&normalized_direction, &movement_direction, &target_direction);
            VECNormalize(&target_direction, &target_direction);
            object->trans.x = player_work->movement_origin.x + (player_work->movement_parameters.z * (target_direction.x * sind(player_work->movement_parameters.y)));
            object->trans.y = player_work->movement_origin.y + (player_work->movement_parameters.z * (target_direction.y * sind(player_work->movement_parameters.y)));
            object->trans.z = player_work->movement_origin.z + (player_work->movement_parameters.z * (target_direction.z * sind(player_work->movement_parameters.y)));
            player_work->movement_parameters.y += 9.0f / 11.0f;
            omSetRot(object, atan2d(target_direction.y, target_direction.z) + 90.0, 0, 0);
            speed = VECMagPoint(object->trans.x - normalized_direction.x, object->trans.y - normalized_direction.y, object->trans.z - normalized_direction.z);
            if (--player_work->state_timer == 60 && player_work->player_index == 0 && unused_object_handle_4 == NULL) {
                camera = &Hu3DCamera[0];
                unused_object_handle_4 = omAddObjEx(HuPrcCurrentGet(), 1400, 0, 0, -1, update_camera_transition);
                unused_object_handle_4->trans.x = camera->pos.x;
                unused_object_handle_4->trans.y = camera->pos.y;
                unused_object_handle_4->trans.z = camera->pos.z;
                unused_object_handle_4->rot.x = camera->target.x;
                unused_object_handle_4->rot.y = camera->target.y;
                unused_object_handle_4->rot.z = camera->target.z;
                unused_object_handle_4->scale.x = 0;
            }
            if (player_work->state_timer == 0) {
                player_work->player_state = 3;
                player_work->landing_effect->work[0] = 1;
                player_work->trail_effect->work[0] = 1;
            }
            update_player_effect_anchor(object);
            break;

        case 3:
            normalized_direction.x = falling_object_scene_object->trans.x;
            normalized_direction.y = player_spawn_positions[player_work->player_index].y;
            normalized_direction.z = falling_object_scene_object->trans.z;
            movement_direction.x = object->trans.x;
            movement_direction.y = object->trans.y;
            movement_direction.z = object->trans.z;
            VECSubtract(&normalized_direction, &movement_direction, &target_direction);
            VECNormalize(&target_direction, &target_direction);
            object->rot.x *= 0.95f;
            if (object->rot.x < 1.0f) {
                object->rot.x = 0.0f;
            }
            omSetRot(object, object->rot.x, atan2d(target_direction.x, target_direction.z), 0);
            update_player_effect_anchor(object);
            break;
    }
}

void update_player_effect_anchor(OMOBJ *object);

void update_player_results(OMOBJ *object)
{
    M401WorkPlayer *player_work;
    TunnelSceneWork *tunnel_work;
    float vertical_distance;
    Vec player_direction;
    Vec player_position;
    s32 score_offsets[] = { -10, -50, -80, -130 };
    Vec camera_direction;
    Vec camera_position;
    Vec camera_up;
    player_work = object->data;
    tunnel_work = tunnel_scene_object->data;
    if (player_work->player_index == 0) {
        winner_sequence_timer--;
    }
    switch (player_work->player_state) {
        case 5:
            if (player_work->is_walking == 1) {
                CharMotionShiftSet(player_work->character_model_index, object->mtnId[1], 0, 8, HU3D_MOTATTR_LOOP);
                player_work->is_walking = 0;
            }
            omSetRot(object, 0, 180, 0);
            object->trans.z -= 5.0f;
            update_player_effect_anchor(object);
            break;

        case 6:
            object->trans.y += player_work->movement_parameters.x;
            if (object->trans.y >= 910.0f) {
                if (player_work->state_initialized == 0) {
                    player_work->state_initialized = 1;
                    Hu3DModelAttrReset(object->mdlId[2], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(object->mdlId[2], HU3D_MOTATTR_LOOP);
                    Hu3DModelPosSet(object->mdlId[2], object->trans.x, 950, 30 + object->trans.z);
                    Hu3DModelScaleSet(object->mdlId[2], 1, 1, 1);
                    Hu3DMotionTimeSet(object->mdlId[2], 0);
                    player_direction.x = object->trans.x;
                    player_direction.y = 950;
                    player_direction.z = 30 + object->trans.z;
                    create_score_particle_effect(&player_direction, 7);
                    HuAudFXEmiterPlay(1289, &player_direction);
                }
                player_work->movement_parameters.x *= 0.7f;
                if (player_work->movement_parameters.x <= 0.5f) {
                    player_work->player_state = 7;
                    player_work->movement_parameters.x = -0.5f;
                    CharMotionShiftSet(player_work->character_model_index, object->mtnId[0], 0, 30, HU3D_MOTATTR_LOOP);
                    player_work->animation_angle = 0;
                    player_work->state_initialized = 0;
                }
            }

            break;

        case 7:
            object->trans.y += player_work->movement_parameters.x;
            if (object->trans.y <= 890) {
                object->trans.y = 890;
                if (winner_count) {
                    if (player_work->is_round_winner) {
                        player_work->player_state = 16;
                    }
                    else {
                        player_work->player_state = 9;
                    }
                }
                else {
                    player_work->player_state = 8;
                    tunnel_work->bridge_motion_state.z = 0.5f;
                    player_work->state_timer = 0;
                    HuAudSStreamPlay(4);
                    minigame_sequence_id = MGSeqDrawCreate();
                    winner_sequence_timer = 210;
                }
            }
            player_work->movement_parameters.x *= 1.17f;
            object->trans.y -= 0.35f * sind(player_work->animation_angle);
            player_work->animation_angle += 3.0f;
            if (player_work->animation_angle >= 360.0f) {
                player_work->animation_angle -= 360.0f;
            }
            break;

        case 8:
            object->trans.y -= 0.35f * sind(player_work->animation_angle);
            player_work->animation_angle += 3.0f;
            if (player_work->animation_angle >= 360.0f) {
                player_work->animation_angle -= 360.0f;
            }
            if (player_work->state_timer == 13) {
                Hu3DModelAttrReset(tunnel_scene_object->mdlId[6], HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(tunnel_scene_object->mdlId[6], 0);
            }
            else if (player_work->state_timer == 50) {
                Hu3DMotionOverlaySet(object->mdlId[0], object->mtnId[8]);
                Hu3DMotionOverlayTimeSet(object->mdlId[0], 31.0f);
                Hu3DData[object->mdlId[0]].motOvlWork.speed = 1;
            }
            if (player_work->state_timer >= 70) {
                if (object->rot.y < 90.0f) {
                    object->rot.y += 2.25f;
                }
                else {
                    object->rot.y = 90.0f;
                }
            }
            player_work->state_timer++;
            if (tunnel_work->bridge_motion_state.y >= 1500.0f) {
                tunnel_work->bridge_motion_state.z = 0;
                if (player_work->player_index == 0) {
                    player_work->player_state = 14;
                }
            }
            break;

        case 16:
            if (!player_work->state_initialized) {
                player_work->state_initialized = 1;
                PlayerFXPlay(player_work->player_index, 292);
                Hu3DMotionOverlaySet(object->mdlId[0], object->mtnId[9]);
                if (player_work->player_index == winner_player_indices[0]) {
                    HuAudSStreamPlay(1);
                    minigame_sequence_id = MGSeqWinCreate(winner_character_indices[0], winner_character_indices[1], winner_character_indices[2], winner_character_indices[3]);
                    winner_sequence_timer = 210;
                    player_work->state_timer = 160;
                    player_work->player_state = 13;
                }
            }
            player_work->movement_parameters.x *= 1.17f;
            object->trans.y -= 0.35f * sind(player_work->animation_angle);
            player_work->animation_angle += 3.0f;
            if (player_work->animation_angle >= 360.0f) {
                player_work->animation_angle -= 360.0f;
            }
            if (73.0f <= Hu3DMotionOverlayTimeGet(object->mdlId[0])) {
                Hu3DMotionOverlayTimeSet(object->mdlId[0], 35.0f);
            }
            break;

        case 10:
            object->trans.y += player_work->movement_parameters.x;
            if (object->trans.y >= 910.0f) {
                if (player_work->state_initialized == 0) {
                    player_work->state_initialized = 1;
                    omVibrate(player_work->player_index, 12, 4, 2);
                    Hu3DModelAttrReset(object->mdlId[2], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(object->mdlId[2], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(object->mdlId[2], HU3D_MOTATTR_LOOP);
                    Hu3DModelPosSet(object->mdlId[2], object->trans.x, 950, 30 + object->trans.z);
                    Hu3DModelScaleSet(object->mdlId[2], 1, 1, 1);
                    Hu3DMotionTimeSet(object->mdlId[2], 0);
                    Hu3DModelAttrReset(object->mdlId[3], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(object->mdlId[3], HU3D_ATTR_DISPOFF);
                    Hu3DModelClusterAttrReset(object->mdlId[3], 0, 0xC0000002);
                    Hu3DModelPosSet(object->mdlId[3], object->trans.x, 0, 30 + object->trans.z);
                    Hu3DMotionTimeSet(object->mdlId[3], 0);
                    player_direction.x = object->trans.x;
                    player_direction.y = 950;
                    player_direction.z = 30 + object->trans.z;
                    create_score_particle_effect(&player_direction, 7);
                    HuAudFXEmiterPlay(1289, &player_direction);
                }
                player_work->player_state = 11;
                player_work->target_position.x = score_offsets[player_work->player_index];
                player_work->target_position.y = 1030;
                player_work->target_position.z = 40;
                player_direction.x = object->trans.x;
                player_direction.y = object->trans.y;
                player_direction.z = object->trans.z;
                VECSubtract(&player_work->target_position, &player_direction, &player_position);
                VECNormalize(&player_position, &player_position);
                vertical_distance = VECDistanceXZ(&player_work->target_position, &object->trans);
                player_work->movement_origin.x = (player_position.x * vertical_distance) / 60.0f;
                player_work->movement_origin.z = (player_position.z * vertical_distance) / 60.0f;
                player_work->movement_origin.y = 18.75f;
                player_work->movement_parameters.y = 0;
            }
            break;

        case 11:
            vertical_distance = player_work->movement_origin.y - (0.020833334f * player_work->movement_parameters.y * player_work->movement_parameters.y);
            object->trans.x += player_work->movement_origin.x;
            object->trans.z += player_work->movement_origin.z;
            object->trans.y += vertical_distance;
            player_work->movement_parameters.y += 1.0f;
            if (object->trans.y <= 1030.0f && vertical_distance < 0) {
                player_work->player_state = 12;
                object->trans.y = 1030 + tunnel_work->bridge_vertical_offset;
                CharMotionShiftSet(player_work->character_model_index, object->mtnId[2], 0, 15, HU3D_MOTATTR_LOOP);
                player_work->movement_parameters.x = 0;
            }
            break;

        case 12:
            object->trans.y = 1030 + tunnel_work->bridge_vertical_offset;
            camera_direction.x = (sind(player_work->movement_parameters.x), 0.0);
            camera_direction.y = -100 * sind(player_work->movement_parameters.x) + 1300;
            camera_direction.z = -500 * sind(player_work->movement_parameters.x) + 1300;
            camera_position.x = (sind(player_work->movement_parameters.x), 0.0);
            camera_position.y = 330 * sind(player_work->movement_parameters.x) + 920;
            camera_position.z = (sind(player_work->movement_parameters.x), 0.0) + -100.0;
            camera_up.x = 0;
            camera_up.y = 1;
            camera_up.z = 0;
            Hu3DCameraPosSetV(1, &camera_direction, &camera_up, &camera_position);
            player_work->movement_parameters.x += 3.0f;
            if (player_work->movement_parameters.x > 90.0f) {
                player_work->player_state = 13;
                CharMotionShiftSet(player_work->character_model_index, object->mtnId[5], 0, 20, HU3D_MOTATTR_NONE);
                HuAudSStreamPlay(1);
                minigame_sequence_id = MGSeqWinCreate(winner_character_indices[0], -1, -1, -1);
                winner_sequence_timer = 210;
            }
            player_work->state_timer = 160;
            break;

        case 13:
            if (winner_count == 1) {
                object->trans.y = 1030 + tunnel_work->bridge_vertical_offset;
            }
            else {
                player_work->movement_parameters.x *= 1.17f;
                object->trans.y -= 0.35f * sind(player_work->animation_angle);
                player_work->animation_angle += 3.0f;
                if (player_work->animation_angle >= 360.0f) {
                    player_work->animation_angle -= 360.0f;
                }
                if (73.0f <= Hu3DMotionOverlayTimeGet(object->mdlId[0])) {
                    Hu3DMotionOverlayTimeSet(object->mdlId[0], 35.0f);
                }
            }
            if (--player_work->state_timer == 0) {
                player_work->player_state = 14;
            }

            break;

        case 14:
            if (player_work->is_round_winner) {
                if (winner_count == 1) {
                    object->trans.y = 1030 + tunnel_work->bridge_vertical_offset;
                }
                else {
                    player_work->movement_parameters.x *= 1.17f;
                    object->trans.y -= 0.35f * sind(player_work->animation_angle);
                    player_work->animation_angle += 3.0f;
                    if (player_work->animation_angle >= 360.0f) {
                        player_work->animation_angle -= 360.0f;
                    }
                    if (73.0f <= Hu3DMotionOverlayTimeGet(object->mdlId[0])) {
                        Hu3DMotionOverlayTimeSet(object->mdlId[0], 35.0f);
                    }
                }
            }
            if (winner_sequence_timer <= 0) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                HuAudSeqFadeOut(audio_sequence_id, 100);
                HuAudFXStop(sound_effect_handle);
                player_work->player_state = 15;
            }
            break;

        case 15:
            if (player_work->is_round_winner) {
                if (winner_count == 1) {
                    object->trans.y = 1030 + tunnel_work->bridge_vertical_offset;
                }
                else {
                    player_work->movement_parameters.x *= 1.17f;
                    object->trans.y -= 0.35f * sind(player_work->animation_angle);
                    player_work->animation_angle += 3.0f;
                    if (player_work->animation_angle >= 360.0f) {
                        player_work->animation_angle -= 360.0f;
                    }
                    if (73.0f <= Hu3DMotionOverlayTimeGet(object->mdlId[0])) {
                        Hu3DMotionOverlayTimeSet(object->mdlId[0], 35.0f);
                    }
                }
            }
            if (!WipeStatGet()) {
                minigame_root_object->objFunc = cleanup_minigame;
            }
            break;
    }
}

void constrain_player_movement(OMOBJ *object);
void update_player_model_position(OMOBJ *object);
void check_player_obstacle_collisions(OMOBJ *object);

void read_cpu_player_input(OMOBJ *object, s8 *x, s8 *y, u16 *btn);

void update_player_control(OMOBJ *object)
{
    M401WorkPlayer *player_work;
    float movement_speed;
    Vec player_position;
    Vec movement_direction;
    s32 button_input;
    u16 pressed_buttons;
    s8 stick_x;
    s8 stick_y;
    movement_speed = 0;
    player_work = object->data;
    stick_x = stick_y = pressed_buttons = 0;
    if (player_work->is_stunned == 0) {
        if (GWPlayerCfg[player_work->player_index].iscom) {
            read_cpu_player_input(object, &stick_x, &stick_y, &pressed_buttons);
        }
        else {
            stick_x = HuPadStkX[player_work->controller_index];
            stick_y = HuPadStkY[player_work->controller_index];
            pressed_buttons = HuPadBtnDown[player_work->controller_index];
        }
        if (stick_x != 0 || stick_y != 0) {
            player_work->movement_parameters.z = sqrtf((stick_x * stick_x) + (stick_y * stick_y)) / 9.0f;
        }
        player_work->facing_angle = atan2d(stick_x, stick_y);
        if (pressed_buttons & PAD_BUTTON_A) {
            player_work->jump_velocity += 1.51f * gravity_acceleration;
            if (player_work->jump_velocity < 1.51f * gravity_acceleration) {
                player_work->jump_velocity = 1.51f * gravity_acceleration;
            }
        }
        if (player_work->jump_velocity >= 0.0f) {
            movement_speed = 0;
        }
        else {
            movement_speed = fabs(player_work->jump_velocity / (1.51f * gravity_acceleration));
        }
        if (player_work->collision_cooldown) {
            if (--player_work->collision_cooldown == 0) {
                CharMotionShiftSet(player_work->character_model_index, object->mtnId[1], 0, 8, HU3D_MOTATTR_LOOP);
                player_work->is_walking = 0;
            }
        }
    }
    else {
        player_work->collision_cooldown = 0;
        if (--player_work->stun_timer == 0) {
            button_input = GWPlayerCfg[player_work->player_index].character;
            CharMotionShiftSet(player_work->character_model_index, object->mtnId[1], 0, 8, HU3D_MOTATTR_LOOP);
            player_work->is_stunned = 0;
            player_work->is_walking = 0;
        }
        if (player_work->stun_timer & 0x1) {
            Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
        }
    }
    if (movement_speed != 0) {
        if (++player_work->run_timer > 15) {
            player_work->run_timer = 15;
        }
        player_work->idle_timer = 0;
    }
    else {
        if (++player_work->idle_timer > 5) {
            player_work->idle_timer = 5;
            player_work->run_timer = 0;
        }
    }
    if (player_work->is_stunned == 0 && player_work->collision_cooldown == 0) {
        if (player_work->movement_parameters.z > 0 || player_work->run_timer >= 5) {
            if (player_work->is_walking == 0) {
                player_work->is_walking = 1;
                CharMotionShiftSet(player_work->character_model_index, object->mtnId[3], 0, 8, HU3D_MOTATTR_LOOP);
            }
        }
        else {
            if (player_work->is_walking == 1) {
                CharMotionShiftSet(player_work->character_model_index, object->mtnId[1], 0, 8, HU3D_MOTATTR_LOOP);
                player_work->is_walking = 0;
            }
        }
    }
    CharMotionSpeedSet(player_work->character_model_index, 1.0f + movement_speed);
    constrain_player_movement(object);
    if (player_work->movement_parameters.z > 0.1f) {
        player_work->movement_parameters.z *= 0.9f;
    }
    else {
        player_work->movement_parameters.z = 0.0f;
    }
    player_work->jump_velocity -= 0.15f * gravity_acceleration;
    if (player_work->jump_velocity > -gravity_acceleration) {
        player_work->jump_velocity = -gravity_acceleration;
    }
    player_position.x = object->trans.x;
    player_position.y = object->trans.y;
    player_position.z = object->trans.z;
    omSetTra(object, player_work->world_position.x, player_work->world_position.y, camera_target.z + player_work->world_position.z);
    movement_direction.x = object->trans.x;
    movement_direction.y = object->trans.y;
    movement_direction.z = object->trans.z;
    if (stick_y != 0) {
        object->rot.x -= 0.05f * stick_y;
    }
    else {
        object->rot.x *= 0.8f;
        if (object->rot.x < 0.01f) {
            object->rot.x = 0;
        }
    }
    if (stick_x != 0) {
        object->rot.z -= 0.05f * stick_x;
    }
    else {
        object->rot.z *= 0.8f;
        if (object->rot.z < 0.01f) {
            object->rot.z = 0;
        }
    }
    if (object->rot.x < -30.0f) {
        object->rot.x = -30.0f;
    }
    if (object->rot.x > 30.0f) {
        object->rot.x = 30.0f;
    }
    if (object->rot.z < -30.0f) {
        object->rot.z = -30.0f;
    }
    if (object->rot.z > 30.0f) {
        object->rot.z = 30.0f;
    }
    object->rot.y = 180;
    update_player_model_position(object);
    check_player_obstacle_collisions(object);
    player_work->reserved_state_70 = 0;
}

void constrain_player_movement(OMOBJ *object)
{
    M401WorkPlayer *other_player_work;
    M401WorkPlayer *player_work;
    s32 player_index;
    OMOBJ *player_object;
    float next_x;
    float next_y;
    float next_z;
    float movement_speed;
    float unused_distance;

    Vec movement_vector;
    Vec normalized_vector;
    Vec player_position;
    player_work = object->data;
    movement_speed = player_work->movement_parameters.z;
    movement_vector.x = sind(player_work->facing_angle);
    movement_vector.y = cosd(player_work->facing_angle);
    movement_vector.z = player_work->jump_velocity + gravity_acceleration;
    VECNormalize(&movement_vector, &normalized_vector);
    movement_vector.x *= movement_speed;
    movement_vector.y *= movement_speed;
    movement_vector.z -= gravity_acceleration;
    next_x = player_work->world_position.x + movement_vector.x;
    next_y = player_work->world_position.y + movement_vector.y;
    next_z = player_work->world_position.z + movement_vector.z;
    if (next_x < -400) {
        next_x = -400;
    }
    if (next_x > 400) {
        next_x = 400;
    }
    if (next_y < -300) {
        next_y = -300;
    }
    if (next_y > 300) {
        next_y = 300;
    }
    if (next_z < 400) {
        next_z = 400;
    }
    if (next_z > 800) {
        next_z = 800;
    }
    for (player_index = 0; player_index < 4; player_index++) {
        if (player_objects[player_index] != object) {
            player_object = player_objects[player_index];
            other_player_work = player_object->data;
            unused_distance = VECMagPoint(next_x - other_player_work->world_position.x, next_y - other_player_work->world_position.y, next_z - other_player_work->world_position.z);
            if (unused_distance < 127.0f) {
                player_position.x = next_x - other_player_work->world_position.x;
                player_position.y = next_y - other_player_work->world_position.y;
                player_position.z = next_z - other_player_work->world_position.z;
                VECNormalize(&player_position, &player_position);
                next_x = other_player_work->world_position.x + 127.0f * player_position.x;
                next_y = other_player_work->world_position.y + 127.0f * player_position.y;
                next_z = other_player_work->world_position.z + 127.0f * player_position.z;
            }
        }
    }
    if (next_x < -400) {
        next_x = -400;
    }
    if (next_x > 400) {
        next_x = 400;
    }
    if (next_y < -300) {
        next_y = -300;
    }
    if (next_y > 300) {
        next_y = 300;
    }
    if (next_z < 400) {
        next_z = 400;
    }
    if (next_z > 800) {
        next_z = 800;
    }
    player_work->world_position.x = next_x;
    player_work->world_position.y = next_y;
    player_work->world_position.z = next_z;
}

void update_player_model_position(OMOBJ *object)
{
    M401WorkPlayer *player_work = object->data;
    player_work->effect_anchor_position.x = player_work->world_position.x + camera_target.x;
    player_work->effect_anchor_position.y = object->trans.y;
    player_work->effect_anchor_position.z = 80 + object->trans.z;
}

void update_player_effect_anchor(OMOBJ *object)
{
    M401WorkPlayer *player_work;
    float horizontal_offset;
    float vertical_offset;
    float depth_offset;
    player_work = object->data;
    horizontal_offset = 80.0 * sind(object->rot.y + 180.0f);
    depth_offset = 80.0 * -cosd(object->rot.y);
    vertical_offset = 80.0 * sind(object->rot.x);
    player_work->effect_anchor_position.x = object->trans.x + horizontal_offset;
    player_work->effect_anchor_position.y = object->trans.y + vertical_offset;
    player_work->effect_anchor_position.z = object->trans.z + depth_offset;
}

OMOBJ *find_closest_player(OMOBJ *object);

void read_cpu_player_input(OMOBJ *object, s8 *x, s8 *y, u16 *btn)
{
    M401WorkPlayer *player_work;
    s32 player_index;
    OMOBJ *target_object;
    s32 other_player_index;
    u16 avoidance_flags = 0;
    float separation_distance;
    float movement_speed;
    float movement_angle;
    s16 behavior_table[][8] = {
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        2,
        0,
        0,
        0,
        2,
        0,
        0,
        0,
        2,
        0,
        0,
        0,
        2,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };
    Vec steering_vector;
    Vec player_position;
    Vec separation_vector;
    Vec obstacle_position;
    s16 horizontal_input_chance[] = { 50, 125, 200, 245 };
    s16 vertical_input_chance[] = { 75, 150, 200, 250 };
    s16 input_delay_by_difficulty[] = { 9, 6, 4, 2 };
    player_work = object->data;
    *x = *y = 0;
    *btn = 0;
    if (player_work->ai_decision_timer == 0) {
        player_work->ai_behavior = behavior_table[GWPlayerCfg[player_work->player_index].diff][frand() & 0x7];
        player_work->ai_decision_timer = (frand() % 60) + 30;
        player_work->ai_avoidance_flags = 0;
        if (frandu8() < horizontal_input_chance[GWPlayerCfg[player_work->player_index].diff]) {
            player_work->ai_avoidance_flags |= 1;
        }
        if (frandu8() < vertical_input_chance[GWPlayerCfg[player_work->player_index].diff]) {
            player_work->ai_avoidance_flags |= 2;
        }
    }
    else {
        player_work->ai_decision_timer--;
    }
    avoidance_flags = player_work->ai_avoidance_flags;
    steering_vector.x = steering_vector.y = steering_vector.z = 0;
    switch (player_work->ai_behavior) {
        case 0:
            target_object = find_closest_player(object);
            if (target_object) {
                steering_vector.x = target_object->trans.x - object->trans.x;
                steering_vector.y = target_object->trans.y - object->trans.y;
                steering_vector.z = target_object->trans.z - object->trans.z;
            }
            break;

        case 2:
            break;
    }
    if (avoidance_flags & 0x1) {
        player_position.x = object->trans.x;
        player_position.y = object->trans.y;
        player_position.z = object->trans.z;
        for (other_player_index = 0; other_player_index < 4; other_player_index++) {
            if (player_objects[other_player_index] != object) {
                obstacle_position.x = player_objects[other_player_index]->trans.x;
                obstacle_position.y = player_objects[other_player_index]->trans.y;
                obstacle_position.z = player_objects[other_player_index]->trans.z;
                VECSubtract(&player_position, &obstacle_position, &separation_vector);
                separation_distance = VECMag(&separation_vector) - 110.0f;
                if (separation_distance < 110.0f) {
                    separation_distance -= 60.0f;
                    if (separation_distance < 0.01f) {
                        separation_distance = 0.01;
                    }
                    VECScale(&separation_vector, &separation_vector, 1.0f / separation_distance);
                    VECAdd(&steering_vector, &separation_vector, &steering_vector);
                }
            }
        }
    }
    if (avoidance_flags & 0x2) {
        for (player_index = 0; player_index < 4; player_index++) {
            if (falling_projectile_objects[player_index]->objFunc != NULL) {
                obstacle_position.x = falling_projectile_objects[player_index]->trans.x;
                obstacle_position.y = falling_projectile_objects[player_index]->trans.y;
                obstacle_position.z = falling_projectile_objects[player_index]->trans.z;
                VECSubtract(&player_position, &obstacle_position, &separation_vector);
                separation_distance = VECMag(&separation_vector) - 110.0f;
                if (separation_distance < 110.0f) {
                    separation_distance -= 60.0f;
                    if (separation_distance < 0.01f) {
                        separation_distance = 0.01;
                    }
                    VECScale(&separation_vector, &separation_vector, 1.0f / separation_distance);
                    VECAdd(&steering_vector, &separation_vector, &steering_vector);
                }
            }
        }
        for (player_index = 0; player_index < 2; player_index++) {
            if (orbiting_scene_objects[player_index]->objFunc != NULL) {
                obstacle_position.x = orbiting_scene_objects[player_index]->trans.x;
                obstacle_position.y = orbiting_scene_objects[player_index]->trans.y;
                obstacle_position.z = orbiting_scene_objects[player_index]->trans.z;
                VECSubtract(&player_position, &obstacle_position, &separation_vector);
                separation_distance = VECMag(&separation_vector) - 110.0f;
                if (separation_distance < 110.0f) {
                    separation_distance -= 60.0f;
                    if (separation_distance < 0.01f) {
                        separation_distance = 0.01;
                    }
                    VECScale(&separation_vector, &separation_vector, 1.0f / separation_distance);
                    VECAdd(&steering_vector, &separation_vector, &steering_vector);
                }
            }
        }
        obstacle_position.x = moving_obstacle_object->trans.x;
        obstacle_position.y = moving_obstacle_object->trans.y;
        obstacle_position.z = moving_obstacle_object->trans.z;
        VECSubtract(&player_position, &obstacle_position, &separation_vector);
        separation_vector.x = 0;
        separation_distance = VECMag(&separation_vector) - 220.0f;
        if (separation_distance < 220.0f) {
            separation_distance -= 160.0f;
            if (separation_distance < 0.01f) {
                separation_distance = 0.01;
            }
            VECScale(&separation_vector, &separation_vector, 1.0f / separation_distance);
            VECAdd(&steering_vector, &separation_vector, &steering_vector);
        }
    }

    if (steering_vector.z < 0.0f) {
        if (player_work->ai_input_cooldown == 0) {
            *btn |= 0x100;
            player_work->ai_input_cooldown = (frand() % input_delay_by_difficulty[GWPlayerCfg[player_work->player_index].diff]) + 3;
        }
        else {
            player_work->ai_input_cooldown--;
        }
    }
    steering_vector.z = 0;
    movement_speed = VECMag(&steering_vector);
    movement_speed *= 0.2f;
    movement_angle = atan2d(steering_vector.y, steering_vector.x);
    if (movement_speed > 72.0f) {
        movement_speed = 72.0f;
    }
    if (movement_speed < 10.0f) {
        movement_speed = 0.0f;
    }
    *x = movement_speed * cosd(movement_angle);
    *y = movement_speed * sind(movement_angle);
}

s32 find_nearby_obstacle(Vec *pos, float dist, OMOBJ **newobj);

s32 find_nearby_obstacle_for_player(OMOBJ *object, OMOBJ **newobj)
{
    Vec target_position;
    target_position.x = object->trans.x;
    target_position.y = object->trans.y;
    target_position.z = object->trans.z - 100.0f;
    return find_nearby_obstacle(&target_position, 270.0f, newobj);
}

void set_cpu_avoidance_response(OMOBJ *object, s32 avoidance_direction)
{
    M401WorkPlayer *player_work;
    if (avoidance_direction) {
        player_work = object->data;
        player_work->ai_behavior = 1;
        player_work->ai_decision_timer = 5;
        switch (avoidance_direction) {
            case 1:
                player_work->animation_angle = 180.0 + atan2d(player_work->target_object->trans.x - object->trans.x, player_work->target_object->trans.y - object->trans.y);
                break;

            case 2:
                if (player_work->world_position.y > player_work->target_object->trans.y) {
                    player_work->animation_angle = 80.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                else {
                    player_work->animation_angle = 260.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                break;

            case 3:
                if (player_work->world_position.y > player_work->target_object->trans.y) {
                    player_work->animation_angle = 80.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                else {
                    player_work->animation_angle = 260.0f + ((1.0f / 255.0f) * (20.0f * frandu8()));
                }
                break;
        }
    }
}

OMOBJ *find_closest_player(OMOBJ *object)
{
    OMOBJ **player_objects;
    s32 player_index;
    OMOBJ *closest_player;
    float depth_distance, horizontal_distance, vertical_distance;
    float weighted_distance, closest_distance;
    player_objects = omGetGroupMemberListEx(HuPrcCurrentGet(), 1);
    closest_distance = 100000;
    closest_player = NULL;
    for (player_index = 0; player_index < 28; player_index++) {
        if (player_objects[player_index] == NULL || player_objects[player_index]->trans.z - camera_target.z > 850.0f
            || player_objects[player_index]->trans.z - camera_target.z < -2500.0f) {
            continue;
        }
        horizontal_distance = player_objects[player_index]->trans.x - object->trans.x;
        vertical_distance = player_objects[player_index]->trans.y - object->trans.y;
        depth_distance = player_objects[player_index]->trans.z - object->trans.z;
        depth_distance *= 0.15f;
        weighted_distance = VECMagPoint(horizontal_distance, vertical_distance, depth_distance);
        if (weighted_distance < closest_distance && weighted_distance < 2000.0f) {
            closest_distance = weighted_distance;
            closest_player = player_objects[player_index];
        }
    }
    return closest_player;
}

void play_player_effects(s32 player);

void stun_player(OMOBJ *object)
{
    M401WorkPlayer *player_work = object->data;
    player_work->is_stunned = 1;
    player_work->stun_timer = 120;
    CharMotionShiftSet(player_work->character_model_index, object->mtnId[7], 0, 10, HU3D_MOTATTR_NONE);
    play_player_effects(player_work->player_index);
}

typedef struct falling_object_work {
    s16 object_state;
    Vec object_position;
    Vec object_velocity;
    s16 active_duration;
    s16 effect_cooldown;
    s16 effect_count;
    s16 state_timer;
    s16 effect_state;
    float effect_value;
    s16 path_index;
    s16 path_point_index;
    float remaining_path_distance;
} FallingObjectWork;

void update_falling_object(OMOBJ *object);

void create_falling_object(OMOBJ *object)
{
    FallingObjectWork *falling_object_work;
    object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(FallingObjectWork), HU_MEMNUM_OVL);
    falling_object_work = object->data;
    falling_object_work->object_velocity.x = 0;
    falling_object_work->object_velocity.y = 200;
    falling_object_work->object_velocity.z = 0;
    falling_object_work->effect_cooldown = 0;
    falling_object_work->state_timer = 100;
    falling_object_work->object_position.x = 0;
    falling_object_work->object_position.y = 200;
    falling_object_work->effect_state = 0;
    falling_object_work->effect_value = 0;
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x0B));
    Hu3DModelClusterAttrSet(object->mdlId[0], 0, 0xC0000001);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAmbSet(object->mdlId[0], 0.6f, 0.6f, 0.6f);
    Hu3DModelShadowSet(object->mdlId[0]);
    falling_object_work->object_state = 0;
    falling_object_work->state_timer = 180;
    omSetTra(object, 0, 200, 200);
    omSetRot(object, 0, 180, 0);
    object->objFunc = update_falling_object;
}

void update_falling_object(OMOBJ *object)
{
    FallingObjectWork *falling_object_work;
    falling_object_work = object->data;
    switch (falling_object_work->object_state) {
        case 0:
            if (--falling_object_work->state_timer == 0) {
                falling_object_work->object_state = 1;
            }
            break;

        case 1:
            object->trans.z += -11.333333f;
            break;
    }
}

s32 gap_04_00000328_data = DATA_MAKE_NUM(DATADIR_M401, 0x0C);
s32 path_last_point_indices[] = { 4, 6 };
Vec falling_object_path_points[][10] = { {
                                 { 1400, -600, -21500 },
                                 { -100, 100, -22000 },
                                 { -1000, -200, -23000 },
                                 { -2000, -200, -23500 },
                                 { -2200, -200, -23500 },
                                 { -2300, -200, -23500 },
                             },
    {
        { -1000, 500, -29500 },
        { -300, 300, -31500 },
        { 300, -150, -32500 },
        { -200, 250, -34000 },
        { -300, 300, -35000 },
        { -600, 300, -36000 },
        { 1000, -180, -40000 },
        { 1000, -180, -40000 },
    }

};

void interpolate_falling_object_path(s32 path_index, s32 point_index, float interpolation_t, Vec *position)
{
    Vec *previous_path_point;
    Vec *start_path_point;
    Vec *end_path_point;
    Vec *next_path_point;
    float curve_parameter_squared = interpolation_t * interpolation_t;
    if (point_index == 0) {
        previous_path_point = &falling_object_path_points[path_index][point_index];
        start_path_point = &falling_object_path_points[path_index][point_index + 1];
        end_path_point = &falling_object_path_points[path_index][point_index + 2];
        next_path_point = &falling_object_path_points[path_index][point_index + 3];
        position->x = (0.5f
            * ((2.0f * previous_path_point->x)
                + ((curve_parameter_squared * (end_path_point->x + (previous_path_point->x - (2.0f * start_path_point->x))))
                    + (interpolation_t * (((-3.0f * previous_path_point->x) + (4.0f * start_path_point->x)) - end_path_point->x)))));
        position->y = (0.5f
            * ((2.0f * previous_path_point->y)
                + ((curve_parameter_squared * (end_path_point->y + (previous_path_point->y - (2.0f * start_path_point->y))))
                    + (interpolation_t * (((-3.0f * previous_path_point->y) + (4.0f * start_path_point->y)) - end_path_point->y)))));
        position->z = (0.5f
            * ((2.0f * previous_path_point->z)
                + ((curve_parameter_squared * (end_path_point->z + (previous_path_point->z - (2.0f * start_path_point->z))))
                    + (interpolation_t * (((-3.0f * previous_path_point->z) + (4.0f * start_path_point->z)) - end_path_point->z)))));
    }
    else {
        previous_path_point = &falling_object_path_points[path_index][point_index - 1];
        start_path_point = &falling_object_path_points[path_index][point_index];
        end_path_point = &falling_object_path_points[path_index][point_index + 1];
        next_path_point = &falling_object_path_points[path_index][point_index + 2];
        position->x = (0.5f
            * ((2.0f * start_path_point->x)
                + ((interpolation_t * (-previous_path_point->x + end_path_point->x))
                    + ((interpolation_t * (curve_parameter_squared * (next_path_point->x + ((-previous_path_point->x + (3.0f * start_path_point->x)) - (3.0f * end_path_point->x)))))
                        + (curve_parameter_squared * (((4.0f * end_path_point->x) + ((2.0f * previous_path_point->x) - (5.0f * start_path_point->x))) - next_path_point->x))))));
        position->y = (0.5f
            * ((2.0f * start_path_point->y)
                + ((interpolation_t * (-previous_path_point->y + end_path_point->y))
                    + ((interpolation_t * (curve_parameter_squared * (next_path_point->y + ((-previous_path_point->y + (3.0f * start_path_point->y)) - (3.0f * end_path_point->y)))))
                        + (curve_parameter_squared * (((4.0f * end_path_point->y) + ((2.0f * previous_path_point->y) - (5.0f * start_path_point->y))) - next_path_point->y))))));
        position->z = (0.5f
            * ((2.0f * start_path_point->z)
                + ((interpolation_t * (-previous_path_point->z + end_path_point->z))
                    + ((interpolation_t * (curve_parameter_squared * (next_path_point->z + ((-previous_path_point->z + (3.0f * start_path_point->z)) - (3.0f * end_path_point->z)))))
                        + (curve_parameter_squared * (((4.0f * end_path_point->z) + ((2.0f * previous_path_point->z) - (5.0f * start_path_point->z))) - next_path_point->z))))));
    }
}

s32 advance_falling_object_path(OMOBJ *object)
{
    FallingObjectWork *falling_object_work;
    Vec *next_path_point;
    Vec *current_path_point;
    float segment_length;
    Vec direction_vector;
    Vec curve_position;
    falling_object_work = object->data;
    while (1) {
        if (falling_object_work->path_point_index == path_last_point_indices[falling_object_work->path_index]) {
            return 1;
        }
        current_path_point = &falling_object_path_points[falling_object_work->path_index][falling_object_work->path_point_index + 1];
        next_path_point = &falling_object_path_points[falling_object_work->path_index][falling_object_work->path_point_index];
        direction_vector.x = current_path_point->x - next_path_point->x;
        direction_vector.y = current_path_point->y - next_path_point->y;
        direction_vector.z = current_path_point->z - next_path_point->z;
        segment_length = VECMagPoint(direction_vector.x, direction_vector.y, direction_vector.z);
        if (falling_object_work->remaining_path_distance > segment_length) {
            falling_object_work->remaining_path_distance -= segment_length;
            falling_object_work->path_point_index++;
            continue;
        }
        break;
    }
    interpolate_falling_object_path(falling_object_work->path_index, falling_object_work->path_point_index, falling_object_work->remaining_path_distance / segment_length, &curve_position);
    direction_vector.x = curve_position.x - object->trans.x;
    direction_vector.y = curve_position.y - object->trans.y;
    direction_vector.z = curve_position.z - object->trans.z;
    VECNormalize(&direction_vector, &direction_vector);
    object->trans.x = curve_position.x;
    object->trans.y = curve_position.y;
    object->trans.z = curve_position.z;
    object->rot.y = atan2d(direction_vector.x, direction_vector.z);
    object->rot.x = -90.0f * direction_vector.y;
    return 0;
}

s32 spawn_falling_object_effect(OMOBJ *object)
{
    FallingObjectWork *falling_object_work;
    Vec particle_position;
    falling_object_work = object->data;
    if (object->trans.x > -400.0f && object->trans.x < 400.0f && object->trans.z - camera_target.z < 300.0f && object->trans.y > -300.0f
        && object->trans.y < 300.0f) {
        if (falling_object_work->effect_cooldown == 0) {
            if (falling_object_work->effect_count != 0) {
                falling_object_work->effect_count--;
                particle_position.x = object->trans.x;
                particle_position.y = object->trans.y;
                particle_position.z = object->trans.z - camera_target.z;
                create_score_particle_effect(&particle_position, 1);
                return 1;
            }
        }
        else {
            falling_object_work->effect_cooldown--;
        }
    }
    return 0;
}

void update_first_falling_object_path(OMOBJ *object);

void start_first_falling_object_path(OMOBJ *object)
{
    FallingObjectWork *falling_object_work;
    falling_object_work = object->data;
    if (camera_target.z < -20800.0f) {
        Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
        falling_object_work->path_index = 0;
        falling_object_work->path_point_index = 0;
        falling_object_work->remaining_path_distance = 0;
        falling_object_work->effect_cooldown = ((frand() % 10) + 13) * 0.43478262f;
        falling_object_work->effect_count = 2;
        advance_falling_object_path(object);
        object->objFunc = update_first_falling_object_path;
    }
}

void start_second_falling_object_path(OMOBJ *object);

void update_first_falling_object_path(OMOBJ *object)
{
    FallingObjectWork *falling_object_work;
    falling_object_work = object->data;
    falling_object_work->remaining_path_distance += 25.875;
    if (spawn_falling_object_effect(object)) {
        falling_object_work->effect_cooldown = ((frand() % 15) + 22) * 0.43478262f;
    }
    if (advance_falling_object_path(object)) {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        object->objFunc = start_second_falling_object_path;
    }
}

void update_second_falling_object_path(OMOBJ *object);

void start_second_falling_object_path(OMOBJ *object)
{
    FallingObjectWork *falling_object_work;
    falling_object_work = object->data;
    if (camera_target.z < -30500.0f) {
        Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
        falling_object_work->path_index = 1;
        falling_object_work->path_point_index = 0;
        falling_object_work->remaining_path_distance = 0;
        falling_object_work->effect_cooldown = ((frand() % 60) + 50) * 0.43478262f;
        falling_object_work->effect_count = 3;
        advance_falling_object_path(object);
        object->objFunc = update_second_falling_object_path;
    }
}

s32 falling_object_effect_cooldowns[] = { 50, 95 };

void update_second_falling_object_path(OMOBJ *object)
{
    FallingObjectWork *falling_object_work;
    falling_object_work = object->data;
    falling_object_work->remaining_path_distance += 25.875;
    if (spawn_falling_object_effect(object)) {
        falling_object_work->effect_cooldown = ((frand() % 15) + falling_object_effect_cooldowns[stage_event_counter++]) * 0.43478262f;
    }
    if (advance_falling_object_path(object)) {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        object->objFunc = NULL;
    }
}

typedef struct orbiting_object_work {
    Vec normalized_direction;
    Vec direction_vector;
    Vec origin_position;
    Vec target_position;
    float travel_distance;
    Vec orbit_parameters;
} OrbitingObjectWork;

void update_orbiting_object(OMOBJ *object);

void create_orbiting_object(OMOBJ *object)
{
    OrbitingObjectWork *orbit_work;
    object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(OrbitingObjectWork), HU_MEMNUM_OVL);
    orbit_work = object->data;
    orbit_work->target_position.x = 6;
    orbit_work->target_position.z = 90;
    orbit_work->target_position.y = 100;
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x0D));
    object->mtnId[0] = Hu3DJointMotionFile(object->mdlId[0], DATA_MAKE_NUM(DATADIR_M401, 0x10));
    Hu3DMotionSet(object->mdlId[0], object->mtnId[0]);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    omSetTra(object, -1000, 0, -23000);
    omSetRot(object, 0, 90, 0);
    orbit_work->direction_vector.x = 1000.0f - object->trans.x;
    orbit_work->direction_vector.y = orbit_work->target_position.y - object->trans.y;
    orbit_work->direction_vector.z = 0;
    orbit_work->orbit_parameters.x = 1000;
    orbit_work->orbit_parameters.y = 30;
    orbit_work->orbit_parameters.z = 360.0f + ((1.0f / 255.0f) * frandu8());
    orbit_work->travel_distance = VECMagPoint(orbit_work->direction_vector.x, orbit_work->direction_vector.y, orbit_work->direction_vector.z);
    VECNormalize(&orbit_work->direction_vector, &orbit_work->normalized_direction);
    Hu3DModelShadowSet(object->mdlId[0]);
    object->work[3] = 2;
    object->objFunc = update_orbiting_object;
}

void start_orbiting_object(OMOBJ *object, Vec *pos)
{
    OrbitingObjectWork *orbit_work;
    orbit_work = object->data;
    orbit_work->origin_position = *pos;
    orbit_work->orbit_parameters.z = (1.0f / 255.0f) * (360.0f * frandu8());
    Hu3DModelAttrReset(object->mdlId[0], HU3D_ATTR_DISPOFF);
    omSetTra(object, pos->x, pos->y, pos->z);
    object->work[2] = HuAudFXEmiterPlay(1284, &pos);
    object->objFunc = update_orbiting_object;
}

void update_orbiting_object(OMOBJ *object)
{
    OrbitingObjectWork *orbit_work;
    float orbit_height;
    Vec sound_emitter_position;
    orbit_work = object->data;
    object->trans.x = orbit_work->origin_position.x + 1000.0f * sind(orbit_work->orbit_parameters.z);
    orbit_height = (orbit_work->orbit_parameters.y / orbit_work->orbit_parameters.x) * sqrtf((orbit_work->orbit_parameters.x * orbit_work->orbit_parameters.x) - (object->trans.x * object->trans.x));
    if (orbit_work->orbit_parameters.z >= 90.0f && orbit_work->orbit_parameters.z <= 270.0f) {
        orbit_height = -orbit_height;
    }
    object->trans.z = orbit_work->origin_position.z + orbit_height;
    orbit_work->orbit_parameters.z += 0.6f + (0.6f * fabs(cosd(orbit_work->orbit_parameters.z)));
    if (orbit_work->orbit_parameters.z >= 360.0f) {
        orbit_work->orbit_parameters.z -= 360.0f;
    }
    omSetRot(object, 0, 90.0f + orbit_work->orbit_parameters.z, 0);
    sound_emitter_position.x = object->trans.x;
    sound_emitter_position.y = object->trans.y;
    sound_emitter_position.z = object->trans.z;
    HuAudFXEmiterUpDate(object->work[2], &sound_emitter_position);
    if (object->trans.z > camera_position.z - 220.0f) {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        HuAudFXStop(object->work[2]);
        object->objFunc = NULL;
    }
}

void wait_for_stage_threshold(OMOBJ *object);

void create_moving_obstacle(OMOBJ *object)
{
    object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x18));
    object->mtnId[0] = Hu3DJointMotionFile(object->mdlId[0], DATA_MAKE_NUM(DATADIR_M401, 0x19));
    object->mtnId[1] = Hu3DJointMotionFile(object->mdlId[0], DATA_MAKE_NUM(DATADIR_M401, 0x1A));
    omSetTra(object, 3000, 0, -37000);
    omSetRot(object, 0, 270, 0);
    Hu3DMotionSet(object->mdlId[0], object->mtnId[0]);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
    object->work[3] = 3;
    Hu3DModelShadowSet(object->mdlId[0]);
    object->objFunc = wait_for_stage_threshold;
}

void set_moving_obstacle_visible(s32 flag)
{
    if (flag) {
        Hu3DModelAttrReset(moving_obstacle_object->mdlId[0], HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrSet(moving_obstacle_object->mdlId[0], HU3D_ATTR_DISPOFF);
    }
}

void move_obstacle_forward(OMOBJ *object);

void wait_for_stage_threshold(OMOBJ *object)
{
    if (camera_target.z < -19000.0f) {
        set_moving_obstacle_visible(1);
        omSetTra(object, -2500, -800, -21000);
        omSetRot(object, 0, 125, 0);
        Hu3DMotionSet(object->mdlId[0], object->mtnId[0]);
        Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
        object->objFunc = move_obstacle_forward;
    }
}

void respawn_obstacle(OMOBJ *object);

void move_obstacle_forward(OMOBJ *object)
{
    object->trans.x += 2.3f * (26.0 * sind(object->rot.y));
    object->trans.z += 2.3f * (26.0 * cosd(object->rot.y));
    if (object->trans.x > 6000.0f) {
        set_moving_obstacle_visible(0);
        object->objFunc = respawn_obstacle;
    }
}

void move_obstacle_backward(OMOBJ *object);

void respawn_obstacle(OMOBJ *object)
{
    float spawn_height;
    if (camera_target.z <= -36200.0f + ((1.0f / 255.0f) * (200.0f * frandu8()))) {
        spawn_height = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
        set_moving_obstacle_visible(1);
        omSetTra(object, 3000, spawn_height, -37000);
        omSetRot(object, 0, 270, 0);
        Hu3DMotionSet(object->mdlId[0], object->mtnId[0]);
        Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
        object->objFunc = move_obstacle_backward;
        sound_emitter_position.x = object->trans.x;
        sound_emitter_position.y = object->trans.y;
        sound_emitter_position.z = object->trans.z;
        moving_obstacle_sound_emitter = HuAudFXEmiterPlay(1286, &sound_emitter_position);
    }
}

void move_obstacle_backward(OMOBJ *object)
{
    object->trans.x += 2.3f * (17.0 * sind(object->rot.y));
    object->trans.z += 2.3f * (17.0 * cosd(object->rot.y));
    sound_emitter_position.x = object->trans.x;
    sound_emitter_position.y = object->trans.y;
    sound_emitter_position.z = object->trans.z;
    HuAudFXEmiterUpDate(moving_obstacle_sound_emitter, &sound_emitter_position);
    if (object->trans.x <= -3000.0f) {
        set_moving_obstacle_visible(0);
        object->objFunc = NULL;
        HuAudFXStop(moving_obstacle_sound_emitter);
    }
}

typedef struct falling_projectile_work {
    Vec projectile_motion;
    s16 spawn_delay;
} FallingProjectileWork;

s32 falling_projectile_motion_ids[] = { DATA_MAKE_NUM(DATADIR_M401, 0x1C), DATA_MAKE_NUM(DATADIR_M401, 0x1D) };

void create_falling_projectiles(HUPROCESS *objman)
{
    OMOBJ *falling_object;
    s32 motion_index;
    s32 object_index;
    for (object_index = 0; object_index < 4; object_index++) {
        falling_object = omAddObjEx(objman, 1130, 1, 2, -1, NULL);
        falling_projectile_objects[object_index] = falling_object;
        falling_object->mdlId[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x1B));
        for (motion_index = 0; motion_index < 2; motion_index++) {
            falling_object->mtnId[motion_index] = Hu3DJointMotionFile(falling_object->mdlId[0], falling_projectile_motion_ids[motion_index]);
        }
        Hu3DModelAttrSet(falling_object->mdlId[0], HU3D_ATTR_DISPOFF);
        falling_object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(FallingProjectileWork), HU_MEMNUM_OVL);
        Hu3DModelShadowSet(falling_object->mdlId[0]);
        falling_object->work[3] = 1;
    }
}

void update_falling_projectile(OMOBJ *object);

void initialize_projectile_distribution(float minimum_spacing, float maximum_spacing)
{
    s32 object_index;
    FallingProjectileWork *falling_object_work;
    float object_spacing;
    float height_step;
    float spawn_height;
    height_step = (maximum_spacing - minimum_spacing) / 4;
    object_spacing = minimum_spacing;
    for (object_index = 0; object_index < 4; object_index++) {
        falling_object_work = falling_projectile_objects[object_index]->data;
        Hu3DModelAttrReset(falling_projectile_objects[object_index]->mdlId[0], HU3D_ATTR_DISPOFF);
        spawn_height = -400.0f + ((1.0f / 255.0f) * (800.0f * frandu8()));
        falling_object_work->projectile_motion.x = -250.0f + ((1.0f / 255.0f) * (500.0f * frandu8()));
        omSetTra(falling_projectile_objects[object_index], spawn_height, falling_object_work->projectile_motion.x + camera_target.y, object_spacing);
        Hu3DMotionSet(falling_projectile_objects[object_index]->mdlId[0], falling_projectile_objects[object_index]->mtnId[0]);
        Hu3DModelAttrSet(falling_projectile_objects[object_index]->mdlId[0], HU3D_MOTATTR_LOOP);
        object_spacing += height_step;
        falling_object_work->spawn_delay = (frand() % 30) + 30;
        falling_object_work->projectile_motion.z = 0;
        falling_projectile_objects[object_index]->objFunc = update_falling_projectile;
    }
}

OMOBJ *find_nearest_player_to_object(OMOBJ *object)
{
    OMOBJ *player_object;
    s32 player_index;
    OMOBJ *closest_player;
    M401WorkPlayer *player_work;

    float candidate_distance;
    float closest_distance;
    closest_distance = 999999;
    for (player_index = 0; player_index < 4; player_index++) {
        float horizontal_distance;
        float vertical_distance;
        float depth_distance;
        player_object = player_objects[player_index];
        player_work = player_object->data;
        horizontal_distance = player_object->trans.x - object->trans.x;
        vertical_distance = player_object->trans.y - object->trans.y;
        depth_distance = 0.4f * (player_object->trans.z - object->trans.z);
        candidate_distance = VECMagPoint(horizontal_distance, vertical_distance, depth_distance);
        if (candidate_distance < closest_distance) {
            closest_player = player_objects[player_index];
            closest_distance = candidate_distance;
        }
    }
    return closest_player;
}

void update_falling_projectile(OMOBJ *object)
{
    FallingProjectileWork *falling_object_work;
    OMOBJ *target_object;
    M401WorkPlayer *target_player_work;
    falling_object_work = object->data;
    if (0.0f == falling_object_work->projectile_motion.z) {
        if (falling_object_work->spawn_delay == 0) {
            target_object = find_nearest_player_to_object(object);
            target_player_work = target_object->data;
            falling_object_work->projectile_motion.y = atan2d(target_object->trans.y - object->trans.y, target_object->trans.x - object->trans.x);
            falling_object_work->projectile_motion.z = 8.0f + ((1.0f / 255.0f) * ((9.0f * frandu8())));
            Hu3DMotionSet(object->mdlId[0], object->mtnId[1]);
            Hu3DModelAttrReset(object->mdlId[0], HU3D_MOTATTR_LOOP);
            sound_emitter_position.x = object->trans.x;
            sound_emitter_position.y = object->trans.y;
            sound_emitter_position.z = object->trans.z;
            HuAudFXEmiterPlay(1282, &sound_emitter_position);
        }
        else {
            falling_object_work->spawn_delay--;
            falling_object_work->projectile_motion.x -= 2.5f;
        }
    }
    else {
        falling_object_work->projectile_motion.x = falling_object_work->projectile_motion.x + (falling_object_work->projectile_motion.z * sind(falling_object_work->projectile_motion.y));
        object->trans.x += falling_object_work->projectile_motion.z * cosd(falling_object_work->projectile_motion.y);
        falling_object_work->projectile_motion.z *= 0.94f;
        if (falling_object_work->projectile_motion.z < 0.1f) {
            falling_object_work->projectile_motion.z = 0;
            falling_object_work->spawn_delay = (frand() % 30) + 25;
            Hu3DMotionSet(object->mdlId[0], object->mtnId[0]);
            Hu3DModelAttrSet(object->mdlId[0], HU3D_MOTATTR_LOOP);
        }
    }
    if (falling_object_work->projectile_motion.x < -300.0f) {
        falling_object_work->projectile_motion.x = -300.0f;
    }
    if (falling_object_work->projectile_motion.x > 300.0f) {
        falling_object_work->projectile_motion.x = 300.0f;
    }
    if (object->trans.x < -400.0f) {
        object->trans.x = -400.0f;
    }
    if (object->trans.x > 400.0f) {
        object->trans.x = 400.0f;
    }
    omSetTra(object, object->trans.x, falling_object_work->projectile_motion.x + camera_target.y, object->trans.z);
    if (object->trans.z > camera_position.z - 160.0f) {
        Hu3DModelAttrSet(object->mdlId[0], HU3D_ATTR_DISPOFF);
        object->objFunc = NULL;
    }
}

void set_object_position(OMOBJ *object, float x, float y, float z)
{
    omSetTra(object, camera_target.x + x, camera_target.y + y, camera_target.z + z);
}

s32 player_effect_model_ids[] = { 0x12D, 0x16D, 0x1AD, 0x1ED, 0x22D, 0x26D, 0x2AD, 0x2ED };

void play_player_effects(s32 player)
{
    PlayerFXPlay(player, 301);
}

void check_player_obstacle_collisions(OMOBJ *object)
{
    Vec player_position;
    OMOBJ *target_object;
    M401WorkPlayer *player_work;
    s32 player_index;
    player_work = object->data;
    if (player_work->is_stunned != 0) {
        return;
    }
    player_position.x = object->trans.x;
    player_position.y = object->trans.y;
    player_position.z = object->trans.z;
    if ((player_index = find_nearby_obstacle(&player_position, 90, &target_object)) != 0) {
        if (player_index == 1) {
            omVibrate(player_work->player_index, 12, 4, 2);
        }
        else if (player_index == 3) {
            omVibrate(player_work->player_index, 12, 4, 2);
        }
        else {
            omVibrate(player_work->player_index, 12, 12, 0);
        }
        stun_player(object);
        show_score_loss_popup(player_work->player_index, target_object->work[3]);
    }
}

s32 find_nearby_obstacle(Vec *pos, float dist, OMOBJ **newobj)
{
    OMOBJ *obstacle_object;
    s32 obstacle_index;
    float obstacle_distance;
    float obstacle_x;
    float obstacle_z;
    FallingProjectileWork *falling_object_work;
    float obstacle_y;

    *newobj = NULL;
    for (obstacle_index = 0; obstacle_index < 4; obstacle_index++) {
        obstacle_object = falling_projectile_objects[obstacle_index];
        if (obstacle_object->objFunc != NULL) {
            falling_object_work = obstacle_object->data;
            obstacle_distance = VECMagPoint(pos->x - obstacle_object->trans.x, pos->y - obstacle_object->trans.y, pos->z - obstacle_object->trans.z);
            if (obstacle_distance < sqrtf(1024.0f + (dist * dist))) {
                *newobj = obstacle_object;
                return 1;
            }
        }
    }
    obstacle_object = moving_obstacle_object;
    obstacle_distance = VECDistanceZY(pos, &obstacle_object->trans);
    if (obstacle_distance < sqrtf(6400.0f + (dist * dist)) && obstacle_object->trans.x < pos->x - (dist / 2.0f)
        && 1500.0f + obstacle_object->trans.x > pos->x + (dist / 2.0f)) {
        *newobj = obstacle_object;
        return 2;
    }
    for (obstacle_index = 0; obstacle_index < 2; obstacle_index++) {
        if (orbiting_scene_objects[obstacle_index]->objFunc != NULL) {
            obstacle_x = orbiting_scene_objects[obstacle_index]->trans.x + (70.0 * sind(orbiting_scene_objects[obstacle_index]->rot.y));
            obstacle_z = orbiting_scene_objects[obstacle_index]->trans.z + (70.0 * cosd(orbiting_scene_objects[obstacle_index]->rot.y));
            obstacle_y = orbiting_scene_objects[obstacle_index]->trans.y - 10.0f;
            obstacle_distance = VECMagPoint(pos->x - obstacle_x, pos->y - obstacle_y, pos->z - obstacle_z);
            if (obstacle_distance < sqrtf(4900.0f + (dist * dist))) {
                *newobj = orbiting_scene_objects[obstacle_index];
                return 3;
            }
            obstacle_x = orbiting_scene_objects[obstacle_index]->trans.x;
            obstacle_z = orbiting_scene_objects[obstacle_index]->trans.z;
            obstacle_y = orbiting_scene_objects[obstacle_index]->trans.y - 10.0f;
            obstacle_distance = VECMagPoint(pos->x - obstacle_x, pos->y - obstacle_y, pos->z - obstacle_z);
            if (obstacle_distance < sqrtf(4900.0f + (dist * dist))) {
                *newobj = orbiting_scene_objects[obstacle_index];
                return 3;
            }
            obstacle_x = orbiting_scene_objects[obstacle_index]->trans.x + (70.0 * sind(orbiting_scene_objects[obstacle_index]->rot.y + 180.0f));
            obstacle_z = orbiting_scene_objects[obstacle_index]->trans.z + (70.0 * cosd(orbiting_scene_objects[obstacle_index]->rot.y + 180.0f));
            obstacle_y = orbiting_scene_objects[obstacle_index]->trans.y - 10.0f;
            obstacle_distance = VECMagPoint(pos->x - obstacle_x, pos->y - obstacle_y, pos->z - obstacle_z);
            if (obstacle_distance < sqrtf(4410.0f + (dist * dist))) {
                *newobj = orbiting_scene_objects[obstacle_index];
                return 3;
            }
        }
    }
    return 0;
}

void update_falling_camera(OMOBJ *object);

void update_start_countdown(OMOBJ *object)
{
    s32 player_index;
    M401WorkPlayer *player_work;
    switch (object->work[0]) {
        case 0:
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            ;
            object->work[0] = 1;
            break;

        case 1:
            if (!WipeStatGet()) {
                object->work[0] = 2;
                object->work[1] = 180;
            }
            break;

        case 2:
            if (object->work[1] == 0) {
                minigame_sequence_id = MGSeqStartCreate();
                object->work[0] = 3;
                audio_sequence_id = HuAudSeqPlay(68);
            }
            else {
                object->work[1]--;
            }
            break;

        case 3:
            if (!MGSeqStatGet(minigame_sequence_id)) {
                set_score_hud_visible(1);
                camera_aspect_ratio = 1;
                setup_scene_section_one(tunnel_scene_object);

                tunnel_scene_object->objFunc = update_tunnel_scene_events;
                for (player_index = 0; player_index < 4; player_index++) {
                    player_work = player_objects[player_index]->data;
                    player_work->movement_parameters.z = 0;
                    player_work->target_position.z = 800;
                    player_objects[player_index]->objFunc = update_player_control;
                    object->trans.x = object->trans.y = object->trans.z = 0;
                }
                falling_object_scene_object->objFunc = start_first_falling_object_path;
                omDelObjEx(HuPrcCurrentGet(), object);
                sequence_controller_object = NULL;
                unused_object_handle_4->objFunc = update_falling_camera;
            }

            break;
    }
}

void update_minigame_results(OMOBJ *object)
{
    M401WorkPlayer *player_work;
    s32 player_index;
    HU3DLIGHT *light;
    Vec camera_position;
    Vec camera_direction;
    switch (object->work[0]) {
        case 0:
            if (!MGSeqStatGet(minigame_sequence_id)) {
                object->work[0] = 1;
                #if VERSION_NTSC
                HuAudFXStop(sound_effect_handle);
                #else
                HuAudFXFadeOut(sound_effect_handle, 500);
                #endif
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                WipeColorSet(255, 255, 255);
            }
            break;

        case 1:
            if (WipeStatGet()) {
                return;
            }
            Hu3DFogClear();
            light = &Hu3DGlobalLight[0];
            light->color.r = 255;
            light->color.g = 255;
            light->color.b = 255;
            camera_position.x = 0;
            camera_position.y = 2500;
            camera_position.z = 1000;
            camera_direction.x = 0;
            camera_direction.y = 1030;
            camera_direction.z = 0;
            Hu3DGLightPosAimSetV(global_light_id, &camera_position, &camera_direction);
            shadow_light_position.x = 0;
            shadow_light_position.y = 2500;
            shadow_light_position.z = 1000;
            shadow_light_target.x = 0;
            shadow_light_target.y = 1030;
            shadow_light_target.z = 0;
            Hu3DShadowPosSet(&shadow_light_position, &shadow_light_up_vector, &shadow_light_target);
            HuAudAUXVolSet(-1, -1);
            cleanup_scene_section_five(tunnel_scene_object);
            for (player_index = 0; player_index < 4; player_index++) {
                player_work = player_objects[player_index]->data;
                player_work->score_effect->work[0] = 1;
                player_work->state_initialized = 0;
                CharMotionSet(((M401WorkPlayer *)(player_objects[player_index]->data))->character_model_index, player_objects[player_index]->mtnId[4]);
                Hu3DModelAttrReset(player_objects[player_index]->mdlId[0], HU3D_MOTATTR_LOOP);
                player_objects[player_index]->objFunc = update_player_results;
                Hu3DModelAmbSet(player_objects[player_index]->mdlId[0], 0.7f, 0.7f, 0.7f);
                omSetTra(player_objects[player_index], -225.0f + (player_index * 150), 740, 400);
                omSetRot(player_objects[player_index], 0, 0, 0);
                if (player_work->is_round_winner) {
                    if (winner_count == 1) {
                        player_work->player_state = 10;
                        player_work->movement_parameters.x = 13;
                    }
                    else {
                        player_work->movement_parameters.x = 10;
                        player_work->player_state = 6;
                    }
                    OSReport("GetCoin:%d\n", player_index);
                    GWPlayerCoinWinSet(player_index, 10);
                }
                else {
                    player_work->movement_parameters.x = 10;
                    player_work->player_state = 6;
                }
            }
            configure_tunnel_scene(tunnel_scene_object);
            object->work[0] = 2;
            flocking_particle_object->work[0] = 1;
            create_particle_effect_controller();
            tunnel_scene_object->objFunc = update_bridge_scene;
            sound_effect_handle = HuAudFXPlay(1280);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            omDelObjEx(HuPrcCurrentGet(), scene_transition_object);
            break;

        case 2:
            WipeStatGet() == 0;
            break;
    }
}

typedef struct orbiting_particle_group_work {
    Vec particle_positions[9];
    float particle_opacity[9];
} OrbitingParticleGroupWork;

void set_orbiting_particle_motion_time(s16 model_index);

void update_orbiting_particle_group(OMOBJ *object);

void create_orbiting_particle_group(OMOBJ *object)
{
    s32 model_index;
    float motion_time;
    OrbitingParticleGroupWork *particle_work;
    particle_work = object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(OrbitingParticleGroupWork), HU_MEMNUM_OVL);
    for (model_index = 0; model_index < 9; model_index++) {
        if (model_index == 0) {
            object->mdlId[model_index] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x02));
        }
        else {
            object->mdlId[model_index] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_M401, 0x02));
        }
        Hu3DModelLayerSet(object->mdlId[model_index], 1);
        set_orbiting_particle_motion_time(model_index);
        motion_time = (1.0f / 255.0f) * (Hu3DMotionMaxTimeGet(object->mdlId[model_index]) * frandu8());
        Hu3DMotionTimeSet(object->mdlId[model_index], motion_time);
    }
    omSetStatBit(object, 0x100);
    object->objFunc = update_orbiting_particle_group;
}

void set_orbiting_particle_motion_time(s16 model_index)
{
    OrbitingParticleGroupWork *particle_work;
    float particle_distance, particle_angle;
    particle_work = orbiting_particle_object->data;
    particle_angle = (1.0f / 255.0f) * (360.0f * frandu8());
    particle_distance = (1.0f / 255.0f) * (200.0f * frandu8());
    particle_work->particle_positions[model_index].x = particle_distance * cosd(particle_angle);
    particle_work->particle_positions[model_index].z = particle_distance * sind(particle_angle);
    particle_work->particle_positions[model_index].y = 1000;
    particle_work->particle_opacity[model_index] = 1.0f;
    particle_distance *= 0.25f;
    Hu3DModelRotSet(orbiting_particle_object->mdlId[model_index], particle_distance * sind(particle_angle), 0, particle_distance * cosd(particle_angle));
    Hu3DMotionTimeSet(orbiting_particle_object->mdlId[model_index], 0);
}

void update_orbiting_particle_group(OMOBJ *object)
{
    s32 model_index;
    OrbitingParticleGroupWork *particle_work;
    u8 particle_index;
    float particle_lifetime;
    particle_work = object->data;
    for (model_index = 0; model_index < 9; model_index++) {
        Hu3DModelPosSet(
            object->mdlId[model_index], particle_work->particle_positions[model_index].x, particle_work->particle_positions[model_index].y, active_camera_target.z + particle_work->particle_positions[model_index].z - 500);
        Hu3DModelTPLvlSet(object->mdlId[model_index], particle_work->particle_opacity[model_index]);
        particle_lifetime = Hu3DMotionTimeGet(object->mdlId[model_index]) / Hu3DMotionMaxTimeGet(object->mdlId[model_index]);
        particle_work->particle_opacity[model_index] = 1.0f - particle_lifetime;
        if (Hu3DMotionTimeGet(object->mdlId[model_index]) >= Hu3DMotionMaxTimeGet(object->mdlId[model_index])) {
            set_orbiting_particle_motion_time(model_index);
        }
    }
    if (camera_target.z <= -26800.0f && camera_target.z >= -27400.0f) {
        particle_index = 255.0f - (223.0f * (-(camera_target.z + 26800.0f) / 600.0f));
        if (particle_index < 32) {
            particle_index = 32;
        }
    }
    else if (camera_target.z <= -27700.0f && camera_target.z >= -28300.0f) {
        particle_index = 32.0f + (223.0f * (-(camera_target.z + 27700.0f) / 600.0f));
    }
    else if (camera_target.z < -27400.0f && camera_target.z > -28300.0f) {
        particle_index = 32;
    }
    else {
        particle_index = 255;
    }
    Hu3DGLightColorSet(global_light_id, particle_index, particle_index, particle_index, 255);
    if (camera_target.z < -26600.0f && camera_target.z > -27500.0f) {
        for (model_index = 0; model_index < 9; model_index++) {
            Hu3DModelAttrSet(object->mdlId[model_index], HU3D_ATTR_DISPOFF);
        }
    }
    else {
        for (model_index = 0; model_index < 9; model_index++) {
            Hu3DModelAttrReset(object->mdlId[model_index], HU3D_ATTR_DISPOFF);
        }
    }
}

void capture_camera_state(OMOBJ *object)
{
    HU3DCAMERA *camera = &Hu3DCamera[0];
    Vec camera_direction;

    camera_position = camera->pos;
    camera_target = camera->target;
    VECSubtract(&camera_position, &previous_camera_position, &camera_direction);
    camera_move_distance = VECMag(&camera_direction);
    previous_camera_position = camera_position;

    reset_scene_fog();
}

void set_camera_vertical_offset(float vertical_offset)
{
    Vec camera_position;
    Vec camera_direction;
    active_camera_position.x = 0;
    active_camera_position.y = 0;
    active_camera_position.z = vertical_offset;
    active_camera_target.x = 0;
    active_camera_target.y = 0;
    active_camera_target.z = -1500 + vertical_offset;
    camera_up_vector.x = 0;
    camera_up_vector.y = 1;
    camera_up_vector.z = 0;
    Hu3DCameraPosSetV(1, &active_camera_position, &camera_up_vector, &active_camera_target);
    Hu3DModelPosSet(tunnel_scene_object->mdlId[1], 0, 0, -1500 + vertical_offset);
    shadow_light_position.y = 3500 + active_camera_target.y;
    shadow_light_position.z = 1500 + active_camera_target.z;
    shadow_light_target.y = active_camera_target.y - 200;
    shadow_light_target.z = 500 + active_camera_target.z;
    Hu3DShadowPosSet(&shadow_light_position, &shadow_light_up_vector, &shadow_light_target);
    camera_position = active_camera_position;
    VECSubtract(&active_camera_target, &camera_position, &camera_direction);
    VECNormalize(&camera_direction, &camera_direction);
    HuAudFXListnerUpdate(&camera_position, &camera_direction);
}

void update_camera_transition(OMOBJ *object)
{
    Vec camera_position;
    Vec camera_direction;
    float wipe_progress = 1.5f * object->scale.x;
    active_camera_position.x = object->trans.x + (-object->trans.x * sind(wipe_progress));
    active_camera_position.y = object->trans.y + (-object->trans.y * sind(wipe_progress));
    active_camera_position.z = object->trans.z + (-object->trans.z * sind(wipe_progress));
    active_camera_target.x = object->rot.x + (-object->rot.x * sind(wipe_progress));
    active_camera_target.y = object->rot.y + (-object->rot.y * sind(wipe_progress));
    active_camera_target.z = object->rot.z + ((-1500.0f - object->rot.z) * sind(wipe_progress));
    camera_up_vector.x = 0;
    camera_up_vector.y = 1;
    camera_up_vector.z = 0;
    object->scale.x += 1.0f;
    if (object->scale.x > 60.0f) {
        active_camera_position.x = 0;
        active_camera_position.y = 0;
        active_camera_position.z = 0;
        active_camera_target.x = 0;
        active_camera_target.y = 0;
        active_camera_target.z = -1500;
    }
    Hu3DCameraPosSetV(1, &active_camera_position, &camera_up_vector, &active_camera_target);
    previous_camera_position = active_camera_position;
    shadow_light_position.y = 3500 + active_camera_target.y;
    shadow_light_position.z = 1500 + active_camera_target.z;
    shadow_light_target.y = active_camera_target.y - 200;
    shadow_light_target.z = 500 + active_camera_target.z;
    Hu3DShadowPosSet(&shadow_light_position, &shadow_light_up_vector, &shadow_light_target);
    camera_position = active_camera_position;
    VECSubtract(&active_camera_target, &active_camera_position, &camera_direction);
    VECNormalize(&camera_direction, &camera_direction);
    HuAudFXListnerUpdate(&camera_position, &camera_direction);
    if (object->scale.x > 60.0f) {
        camera_near_plane = 100;
        Hu3DCameraPerspectiveSet(1, camera_field_of_view, camera_near_plane, camera_far_plane, 1.2f);
        object->scale.x = 0;
        object->objFunc = NULL;
    }
}

void update_falling_camera(OMOBJ *object)
{
    if (minigame_exit_ready != 0) {
        return;
    }
    gravity_acceleration *= 1.05f;
    if (gravity_acceleration < -14.375f) {
        gravity_acceleration = -14.375f;
    }
    object->scale.x += gravity_acceleration;
    set_camera_vertical_offset(object->scale.x);
}

s32 flocking_particle_model_ids[] = { DATA_MAKE_NUM(DATADIR_M401, 0x04), DATA_MAKE_NUM(DATADIR_M401, 0x05), DATA_MAKE_NUM(DATADIR_M401, 0x06) };

typedef struct flocking_particle_effect_work {
    s16 particle_count;
    Vec spawn_origin;
    float current_lifetime;
    float neighbor_radius;
    float base_speed;
    float separation_weight;
    float obstacle_weight;
    float alignment_weight;
    float cohesion_weight;
    float origin_weight;
    s8 *particle_slot_used;
    Vec *particle_positions;
    Vec *particle_directions;
    Vec *separation_forces;
    Vec *alignment_forces;
    Vec *neighbor_centers;
    Vec *origin_forces;
    Vec *obstacle_forces;
    s16 *neighbor_counts;
    s16 *particle_groups;
    float *particle_speeds;
    float *particle_yaw_angles;
    float *particle_pitch_angles;
    float *particle_roll_angles;
    float *particle_roll_velocities;
} FlockingParticleEffectWork;

void create_shared_particle_models(s16 model_count)
{
    OMOBJ *effect_object;
    s32 model_index;
    s8 *model_visibility;
    float model_scale;
    effect_object = shared_particle_model_object = omAddObjEx(minigame_object_manager, 1145, model_count, 0, -1, NULL);
    omSetStatBit(effect_object, 0x100);
    effect_object->data = HuMemDirectMallocNum(HEAP_HEAP, model_count * sizeof(s8), HU_MEMNUM_OVL);
    model_visibility = effect_object->data;
    effect_object->work[0] = model_count;
    for (model_index = 0; model_index < model_count; model_index++) {
        if (model_index < 3) {
            effect_object->mdlId[model_index] = Hu3DModelCreateFile(flocking_particle_model_ids[model_index]);
        }
        else {
            effect_object->mdlId[model_index] = Hu3DModelLink(effect_object->mdlId[model_index % 3]);
        }
        model_scale = 0.5f + ((1.0f / 255.0f) * (0.5f * frandu8()));
        Hu3DModelScaleSet(effect_object->mdlId[model_index], model_scale, model_scale, model_scale);
        Hu3DModelAttrSet(effect_object->mdlId[model_index], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(effect_object->mdlId[model_index], HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(effect_object->mdlId[model_index], (1.0f / 255.0f) * (Hu3DMotionMaxTimeGet(effect_object->mdlId[model_index]) * frandu8()));
        model_visibility[model_index] = 0;
    }
}

void free_flocking_particle_work(FlockingParticleEffectWork *effect_work)
{
    HuMemDirectFree(effect_work->particle_positions);
    HuMemDirectFree(effect_work->particle_directions);
    HuMemDirectFree(effect_work->alignment_forces);
    HuMemDirectFree(effect_work->neighbor_centers);
    HuMemDirectFree(effect_work->origin_forces);
    HuMemDirectFree(effect_work->obstacle_forces);
    HuMemDirectFree(effect_work->separation_forces);
    HuMemDirectFree(effect_work->neighbor_counts);
    HuMemDirectFree(effect_work->particle_groups);
    HuMemDirectFree(effect_work->particle_speeds);
    HuMemDirectFree(effect_work->particle_yaw_angles);
    HuMemDirectFree(effect_work->particle_pitch_angles);
    HuMemDirectFree(effect_work->particle_roll_angles);
    HuMemDirectFree(effect_work->particle_roll_velocities);
    HuMemDirectFree(effect_work->particle_slot_used);
}

OMOBJ *create_flocking_particle_work(s16 particle_count)
{
    FlockingParticleEffectWork *effect_work;
    s32 slot_index;
    OMOBJ *effect_object;
    s32 effect_index;
    s8 *available_slots;
    if (particle_count <= 0) {
        return NULL;
    }
    effect_object = omAddObjEx(minigame_object_manager, 1145, particle_count, 0, -1, NULL);
    omSetStatBit(effect_object, 0x100);
    effect_object->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(FlockingParticleEffectWork), HU_MEMNUM_OVL);
    effect_work = effect_object->data;
    effect_work->particle_positions = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(Vec), HU_MEMNUM_OVL);
    effect_work->particle_directions = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(Vec), HU_MEMNUM_OVL);
    effect_work->alignment_forces = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(Vec), HU_MEMNUM_OVL);
    effect_work->neighbor_centers = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(Vec), HU_MEMNUM_OVL);
    effect_work->origin_forces = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(Vec), HU_MEMNUM_OVL);
    effect_work->obstacle_forces = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(Vec), HU_MEMNUM_OVL);
    effect_work->separation_forces = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(Vec), HU_MEMNUM_OVL);
    effect_work->neighbor_counts = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(s16), HU_MEMNUM_OVL);
    effect_work->particle_groups = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(s16), HU_MEMNUM_OVL);
    effect_work->particle_speeds = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(float), HU_MEMNUM_OVL);
    effect_work->particle_yaw_angles = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(float), HU_MEMNUM_OVL);
    effect_work->particle_pitch_angles = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(float), HU_MEMNUM_OVL);
    effect_work->particle_roll_angles = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(float), HU_MEMNUM_OVL);
    effect_work->particle_roll_velocities = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(float), HU_MEMNUM_OVL);
    effect_work->particle_slot_used = HuMemDirectMallocNum(HEAP_HEAP, particle_count * sizeof(s8), HU_MEMNUM_OVL);
    for (effect_index = 0; effect_index < particle_count; effect_index++) {
        available_slots = shared_particle_model_object->data;
        for (slot_index = 0; slot_index < shared_particle_model_object->work[0]; slot_index++) {
            if (available_slots[slot_index] == 0) {
                available_slots[slot_index] = 1;
                effect_object->mdlId[effect_index] = shared_particle_model_object->mdlId[slot_index];
                effect_work->particle_groups[effect_index] = slot_index % 3;
                effect_work->particle_slot_used[effect_index] = slot_index;
                break;
            }
        }
        if (slot_index == shared_particle_model_object->work[0]) {
            particle_count -= (s32)particle_count - effect_index;
            break;
        }
    }
    if (particle_count == 0) {
        free_flocking_particle_work(effect_work);
        omDelObjEx(HuPrcCurrentGet(), effect_object);
        effect_object = NULL;
    }
    else {
        effect_work->particle_count = particle_count;
        effect_work->current_lifetime = 0;
    }
    return effect_object;
}

void destroy_flocking_particle_effect(OMOBJ *object)
{
    FlockingParticleEffectWork *effect_work;
    s32 model_index;
    s8 *available_slots;
    effect_work = object->data;
    available_slots = shared_particle_model_object->data;
    for (model_index = 0; model_index < effect_work->particle_count; model_index++) {
        available_slots[effect_work->particle_slot_used[model_index]] = 0;
        Hu3DModelAttrSet(object->mdlId[model_index], HU3D_ATTR_DISPOFF);
    }
    free_flocking_particle_work(effect_work);
    omDelObjEx(HuPrcCurrentGet(), object);
}

void update_flocking_particles(OMOBJ *object);

void set_flocking_particles_visible(OMOBJ *object, s16 is_visible)
{
    s32 model_index;
    FlockingParticleEffectWork *effect_work = object->data;
    if (is_visible == 1) {
        for (model_index = 0; model_index < effect_work->particle_count; model_index++) {
            Hu3DModelAttrReset(object->mdlId[model_index], HU3D_ATTR_DISPOFF);
        }
        object->objFunc = update_flocking_particles;
    }
    else {
        for (model_index = 0; model_index < effect_work->particle_count; model_index++) {
            Hu3DModelAttrSet(object->mdlId[model_index], HU3D_ATTR_DISPOFF);
        }
        object->objFunc = NULL;
    }
}

void initialize_flocking_particles(OMOBJ *object, Vec *spawn_origin, Vec *spawn_radius)
{
    FlockingParticleEffectWork *effect_work = object->data;
    s32 effect_index;
    for (effect_index = 0; effect_index < effect_work->particle_count; effect_index++) {
        effect_work->particle_positions[effect_index].x = (spawn_origin->x - spawn_radius->x) + ((1.0f / 255.0f) * (2.0f * spawn_radius->x * frandu8()));
        effect_work->particle_positions[effect_index].y = (spawn_origin->y - spawn_radius->y) + ((1.0f / 255.0f) * (2.0f * spawn_radius->y * frandu8()));
        effect_work->particle_positions[effect_index].z = (spawn_origin->z - spawn_radius->z) + ((1.0f / 255.0f) * (2.0f * spawn_radius->z * frandu8()));
        VECNormalize(&effect_work->particle_positions[effect_index], &effect_work->particle_directions[effect_index]);
        effect_work->particle_yaw_angles[effect_index] = effect_work->particle_roll_angles[effect_index] = effect_work->particle_pitch_angles[effect_index] = effect_work->particle_roll_velocities[effect_index] = 0;
        effect_work->particle_speeds[effect_index] = 0.1f;
        Hu3DModelPosSet(object->mdlId[effect_index], effect_work->particle_positions[effect_index].x, effect_work->particle_positions[effect_index].y, effect_work->particle_positions[effect_index].z);
    }
}

void set_flocking_particle_origin(OMOBJ *object, Vec *pos)
{
    FlockingParticleEffectWork *effect_work = object->data;
    effect_work->spawn_origin = *pos;
}

void set_flocking_particle_motion(OMOBJ *object, float neighbor_radius, float base_speed)
{
    FlockingParticleEffectWork *effect_work = object->data;
    effect_work->neighbor_radius = neighbor_radius;
    effect_work->base_speed = base_speed;
}

void set_flocking_particle_weights(OMOBJ *object, float separation_weight, float obstacle_weight, float alignment_weight, float cohesion_weight, float origin_weight)
{
    FlockingParticleEffectWork *effect_work = object->data;
    effect_work->separation_weight = separation_weight;
    effect_work->obstacle_weight = obstacle_weight;
    effect_work->alignment_weight = alignment_weight;
    effect_work->cohesion_weight = cohesion_weight;
    effect_work->origin_weight = origin_weight;
}

void update_flocking_particles(OMOBJ *object)
{
    FlockingParticleEffectWork *effect_work = object->data;
    s32 effect_index;
    s32 neighbor_index;
    float alignment_dot_product;
    float obstacle_distance;
    float normalization_length;
    float neighbor_distance;
    float combined_force_magnitude;
    Mtx translation_matrix, pitch_matrix, yaw_matrix, roll_matrix, combined_rotation_matrix, particle_matrix;
    Vec particle_difference, force_vector, player_position, obstacle_difference, origin_difference, combined_force, horizontal_force, direction_vector;
    for (effect_index = 0; effect_index < effect_work->particle_count; effect_index++) {
        effect_work->separation_forces[effect_index].x = 0;
        effect_work->separation_forces[effect_index].y = 0;
        effect_work->separation_forces[effect_index].z = 0;
        effect_work->alignment_forces[effect_index].x = 0;
        effect_work->alignment_forces[effect_index].y = 0;
        effect_work->alignment_forces[effect_index].z = 0;
        effect_work->neighbor_centers[effect_index].x = 0;
        effect_work->neighbor_centers[effect_index].y = 0;
        effect_work->neighbor_centers[effect_index].z = 0;
        effect_work->origin_forces[effect_index].x = 0;
        effect_work->origin_forces[effect_index].y = 0;
        effect_work->origin_forces[effect_index].z = 0;
        effect_work->obstacle_forces[effect_index].x = 0;
        effect_work->obstacle_forces[effect_index].y = 0;
        effect_work->obstacle_forces[effect_index].z = 0;
        effect_work->neighbor_counts[effect_index] = 0;
    }
    for (effect_index = 0; effect_index < effect_work->particle_count; effect_index++) {
        for (neighbor_index = effect_index + 1; neighbor_index < effect_work->particle_count; neighbor_index++) {
            VECSubtract(&effect_work->particle_positions[effect_index], &effect_work->particle_positions[neighbor_index], &particle_difference);
            neighbor_distance = VECMag(&particle_difference);
            if (neighbor_distance < effect_work->neighbor_radius) {
                VECScale(&particle_difference, &force_vector, 1.0f / (neighbor_distance * neighbor_distance));
                VECAdd(&effect_work->separation_forces[effect_index], &force_vector, &effect_work->separation_forces[effect_index]);
                VECSubtract(&effect_work->separation_forces[neighbor_index], &force_vector, &effect_work->separation_forces[neighbor_index]);
                if (effect_work->particle_groups[effect_index] == effect_work->particle_groups[neighbor_index]) {
                    VECScale(&effect_work->particle_directions[neighbor_index], &force_vector, 1.0f / neighbor_distance);
                    VECAdd(&effect_work->alignment_forces[effect_index], &force_vector, &effect_work->alignment_forces[effect_index]);
                    VECScale(&effect_work->particle_directions[effect_index], &force_vector, 1.0f / neighbor_distance);
                    VECAdd(&effect_work->alignment_forces[neighbor_index], &force_vector, &effect_work->alignment_forces[neighbor_index]);
                    VECAdd(&effect_work->neighbor_centers[effect_index], &effect_work->particle_positions[neighbor_index], &effect_work->neighbor_centers[effect_index]);
                    VECAdd(&effect_work->neighbor_centers[neighbor_index], &effect_work->particle_positions[effect_index], &effect_work->neighbor_centers[neighbor_index]);
                }
                effect_work->neighbor_counts[effect_index]++;
                effect_work->neighbor_counts[neighbor_index]++;
            }
        }
        for (neighbor_index = 0; neighbor_index < 4; neighbor_index++) {
            player_position.x = player_objects[neighbor_index]->trans.x;
            player_position.y = player_objects[neighbor_index]->trans.y;
            player_position.z = player_objects[neighbor_index]->trans.z;
            VECSubtract(&effect_work->particle_positions[effect_index], &player_position, &obstacle_difference);
            if (!(VECDotProduct(&obstacle_difference, &effect_work->particle_directions[effect_index]) > 0)) {
                obstacle_distance = VECMag(&obstacle_difference) - 200;
                if (obstacle_distance < effect_work->neighbor_radius) {
                    obstacle_distance -= 100;
                    if (obstacle_distance < 0.01f) {
                        obstacle_distance = 0.01f;
                    }
                    VECScale(&obstacle_difference, &obstacle_difference, 1.0f / obstacle_distance);
                    VECAdd(&effect_work->obstacle_forces[effect_index], &obstacle_difference, &effect_work->obstacle_forces[effect_index]);
                }
            }
        }
        if (effect_work->neighbor_counts[effect_index] != 0) {
            VECScale(&effect_work->neighbor_centers[effect_index], &effect_work->neighbor_centers[effect_index], 1.0f / effect_work->neighbor_counts[effect_index]);
            VECSubtract(&effect_work->neighbor_centers[effect_index], &effect_work->particle_positions[effect_index], &origin_difference);
            normalization_length = VECMag(&origin_difference);
            if (normalization_length > 0.0f) {
                VECScale(&origin_difference, &effect_work->neighbor_centers[effect_index], 1.0f / normalization_length);
            }
            else {
                effect_work->neighbor_centers[effect_index].x = 0;
                effect_work->neighbor_centers[effect_index].y = 0;
                effect_work->neighbor_centers[effect_index].z = 0;
            }
            VECScale(&effect_work->alignment_forces[effect_index], &effect_work->alignment_forces[effect_index], 1.0f / effect_work->neighbor_counts[effect_index]);
            normalization_length = VECMag(&effect_work->alignment_forces[effect_index]);
            if (normalization_length > 0) {
                VECScale(&effect_work->alignment_forces[effect_index], &effect_work->alignment_forces[effect_index], 1.0f / normalization_length);
                VECSubtract(&effect_work->alignment_forces[effect_index], &effect_work->particle_directions[effect_index], &origin_difference);
                VECScale(&origin_difference, &effect_work->alignment_forces[effect_index], 1.0f / normalization_length);
            }
        }
        VECSubtract(&effect_work->spawn_origin, &effect_work->particle_positions[effect_index], &effect_work->origin_forces[effect_index]);
        VECNormalize(&effect_work->origin_forces[effect_index], &effect_work->origin_forces[effect_index]);
    }
    for (effect_index = 0; effect_index < effect_work->particle_count; effect_index++) {
        combined_force.x = 0;
        combined_force.y = 0;
        combined_force.z = 0;
        VECScale(&effect_work->separation_forces[effect_index], &direction_vector, effect_work->separation_weight);
        VECAdd(&direction_vector, &combined_force, &combined_force);
        VECScale(&effect_work->obstacle_forces[effect_index], &direction_vector, effect_work->obstacle_weight);
        VECAdd(&direction_vector, &combined_force, &combined_force);
        VECScale(&effect_work->alignment_forces[effect_index], &direction_vector, effect_work->alignment_weight);
        VECAdd(&direction_vector, &combined_force, &combined_force);
        VECScale(&effect_work->neighbor_centers[effect_index], &direction_vector, effect_work->cohesion_weight);
        VECAdd(&direction_vector, &combined_force, &combined_force);
        VECScale(&effect_work->origin_forces[effect_index], &direction_vector, effect_work->origin_weight);
        VECAdd(&direction_vector, &combined_force, &combined_force);
        combined_force_magnitude = VECMag(&combined_force);
        if (combined_force_magnitude > 1.0f) {
            VECScale(&combined_force, &combined_force, 1.0f / combined_force_magnitude);
        }
        if (combined_force.y > 0.01f) {
            effect_work->particle_pitch_angles[effect_index] += 0.02f;
            if (effect_work->particle_pitch_angles[effect_index] > 0.8f) {
                effect_work->particle_pitch_angles[effect_index] = 0.8f;
            }
        }
        else {
            if (combined_force.y < -0.01f) {
                effect_work->particle_pitch_angles[effect_index] -= 0.02f;
                if (effect_work->particle_pitch_angles[effect_index] < -0.8f) {
                    effect_work->particle_pitch_angles[effect_index] = -0.8f;
                }
            }
            else {
                effect_work->particle_pitch_angles[effect_index] *= 0.98f;
            }
        }
        effect_work->particle_speeds[effect_index] -= 0.002 * effect_work->particle_pitch_angles[effect_index];
        effect_work->particle_speeds[effect_index] = effect_work->base_speed + (0.99f * (effect_work->particle_speeds[effect_index] - effect_work->base_speed));
        if (effect_work->particle_speeds[effect_index] < 0.4f * effect_work->base_speed) {
            effect_work->particle_speeds[effect_index] = 0.4f * effect_work->base_speed;
        }
        if (effect_work->particle_speeds[effect_index] > 5.0f * effect_work->base_speed) {
            effect_work->particle_speeds[effect_index] = 5.0f * effect_work->base_speed;
        }
        horizontal_force = combined_force;
        horizontal_force.y = 0;
        direction_vector = effect_work->particle_directions[effect_index];
        if (VECMag(&horizontal_force) > 0) {
            VECNormalize(&horizontal_force, &horizontal_force);
        }
        alignment_dot_product = VECDotProduct(&horizontal_force, &direction_vector);
        if (alignment_dot_product > 0.7f) {
            alignment_dot_product -= 0.7f;
            effect_work->particle_speeds[effect_index] += 0.005f * alignment_dot_product;
        }
        VECCrossProduct(&horizontal_force, &direction_vector, &horizontal_force);
        alignment_dot_product = 0.07f * ((1.0f - alignment_dot_product) / 2);
        if (horizontal_force.y > 0.05f) {
            effect_work->particle_roll_velocities[effect_index] = 0.05f * (alignment_dot_product + (19.0f * effect_work->particle_roll_velocities[effect_index]));
        }
        else if (horizontal_force.y < -0.05f) {
            effect_work->particle_roll_velocities[effect_index] = 0.05f * ((19.0f * effect_work->particle_roll_velocities[effect_index]) - alignment_dot_product);
        }
        else {
            effect_work->particle_roll_velocities[effect_index] *= 0.98f;
        }
        effect_work->particle_yaw_angles[effect_index] += effect_work->particle_roll_velocities[effect_index];
        effect_work->particle_roll_angles[effect_index] = 20.0f * -effect_work->particle_roll_velocities[effect_index];
        MTXTrans(translation_matrix, effect_work->particle_positions[effect_index].x, effect_work->particle_positions[effect_index].y, effect_work->particle_positions[effect_index].z);
        MTXRotDeg(pitch_matrix, 'x', (effect_work->particle_pitch_angles[effect_index] / M_PI) * 180.0);
        MTXRotDeg(yaw_matrix, 'y', (effect_work->particle_yaw_angles[effect_index] / M_PI) * 180.0);
        MTXRotDeg(roll_matrix, 'z', (effect_work->particle_roll_angles[effect_index] / M_PI) * 180.0);
        MTXConcat(pitch_matrix, yaw_matrix, combined_rotation_matrix);
        MTXConcat(roll_matrix, combined_rotation_matrix, particle_matrix);
        MTXConcat(particle_matrix, translation_matrix, combined_rotation_matrix);
        effect_work->particle_directions[effect_index].x = MTXRowCol(combined_rotation_matrix, 2, 0);
        effect_work->particle_directions[effect_index].y = MTXRowCol(combined_rotation_matrix, 2, 1);
        effect_work->particle_directions[effect_index].z = MTXRowCol(combined_rotation_matrix, 2, 2);
        effect_work->particle_positions[effect_index].x += 100.0f * (effect_work->particle_directions[effect_index].x * effect_work->particle_speeds[effect_index]);
        effect_work->particle_positions[effect_index].y += 100.0f * (effect_work->particle_directions[effect_index].y * effect_work->particle_speeds[effect_index]);
        effect_work->particle_positions[effect_index].z += 100.0f * (effect_work->particle_directions[effect_index].z * effect_work->particle_speeds[effect_index]);
        if (effect_work->particle_positions[effect_index].y < -350.0f) {
            effect_work->particle_positions[effect_index].y = -350.0f;
        }
        Hu3DModelPosSet(object->mdlId[effect_index], effect_work->particle_positions[effect_index].x, effect_work->particle_positions[effect_index].y, effect_work->particle_positions[effect_index].z);
        Hu3DModelRotSet(object->mdlId[effect_index], (-effect_work->particle_pitch_angles[effect_index] / M_PI) * 180.0, (-effect_work->particle_yaw_angles[effect_index] / M_PI) * 180.0, 0);
    }
}

void cleanup_player_effects()
{
    HU3DCAMERA *camera;
    s32 camera_component_index;
    float camera_values[7];
    camera = camera_controller_object->data;
    camera_values[0] = camera->pos.x;
    camera_values[1] = camera->pos.y;
    camera_values[2] = camera->pos.z;
    camera_values[3] = camera->up.x;
    camera_values[4] = camera->up.y;
    camera_values[5] = camera->up.z;
    camera_values[6] = camera->target.x;
    fontcolor = FONT_COLOR_WHITE;
    for (camera_component_index = 0; camera_component_index < 7; camera_component_index++) {
        if (camera_component_index == camera_transition_index) {
            print8(24.0 + (1.5 * ((camera_component_index * 8) * 7)), 384, 1.5f, "____");
        }
        print8(24.0 + (1.5 * ((camera_component_index * 8) * 7)), 400, 1.5f, "%.2f", camera_values[camera_component_index]);
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_LEFT) {
        if (--camera_transition_index < 0) {
            camera_transition_index = 6;
        }
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_RIGHT) {
        if (++camera_transition_index > 6) {
            camera_transition_index = 0;
        }
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_UP) {
        if (HuPadBtn[0] & PAD_TRIGGER_R) {
            camera_values[camera_transition_index] += 1.0f;
        }
        else if (HuPadBtn[0] & PAD_TRIGGER_L) {
            camera_values[camera_transition_index] += 0.1f;
        }
        else {
            camera_values[camera_transition_index] += 0.01f;
        }
        if (camera_values[camera_transition_index] > 999.99f) {
            camera_values[camera_transition_index] = 999.99f;
        }
    }
    if (HuPadBtnRep[0] & PAD_BUTTON_DOWN) {
        if (HuPadBtn[0] & PAD_TRIGGER_R) {
            camera_values[camera_transition_index] -= 1.0f;
        }
        else if (HuPadBtn[0] & PAD_TRIGGER_L) {
            camera_values[camera_transition_index] -= 0.1f;
        }
        else {
            camera_values[camera_transition_index] -= 0.01f;
        }
        if (camera_values[camera_transition_index] < 0) {
            camera_values[camera_transition_index] = 0;
        }
    }
    camera->pos.x = camera_values[0];
    camera->pos.y = camera_values[1];
    camera->pos.z = camera_values[2];
    camera->up.x = camera_values[3];
    camera->up.y = camera_values[4];
    camera->up.z = camera_values[5];
    camera->target.x = camera_values[6];
}

void update_flocking_particle_effect(OMOBJ *object);

OMOBJ *create_flocking_particle_effect(s16 particle_count, Vec *spawn_origin, Vec *spawn_radius, Vec *effect_origin)
{
    OMOBJ *effect_index;
    OMOBJ *priority;
    priority = omAddObjEx(HuPrcCurrentGet(), 1140, 0, 0, -1, update_flocking_particle_effect);
    effect_index = create_flocking_particle_work(particle_count);
    priority->work[0] = (u32)effect_index;
    initialize_flocking_particles(effect_index, spawn_origin, spawn_radius);
    set_flocking_particle_origin(effect_index, effect_origin);
    set_flocking_particle_motion(effect_index, 90.0f, 0.045999996f);
    set_flocking_particle_weights(effect_index, 5.0f, 1.5f, 0.08f, 0.8f, 0.8f);
    set_flocking_particles_visible(effect_index, 1);
    return priority;
}

void update_flocking_particle_effect(OMOBJ *object)
{
    FlockingParticleEffectWork *model_index;
    OMOBJ *model_data;
    s32 motion_index;
    s32 motion_count;
    motion_count = 0;
    model_data = (OMOBJ *)(object->work[0]);
    model_index = model_data->data;
    model_index->spawn_origin.x += object->scale.x * sind(object->trans.x);
    model_index->spawn_origin.y += object->scale.y * sind(object->trans.x);
    model_index->spawn_origin.z += object->scale.z * sind(object->trans.x);
    object->trans.x += object->rot.x;
    if (object->trans.x >= 360.0f) {
        object->trans.x -= 360.0f;
    }
    if (object->trans.x < 0.0f) {
        object->trans.x += 360.0f;
    }
    for (motion_index = 0; motion_index < model_index->particle_count; motion_index++) {
        if (model_index->particle_positions[motion_index].z >= camera_position.z) {
            motion_count++;
        }
    }
    if (motion_count == model_index->particle_count) {
        destroy_flocking_particle_effect(model_data);
        omDelObjEx(HuPrcCurrentGet(), object);
    }
}
